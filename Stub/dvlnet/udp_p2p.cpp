#include "../types.h"

using namespace dvlnet;

const udp_p2p::endpoint udp_p2p::none;

udp_p2p::udp_p2p(buffer_t info)
{
	if (sodium_init() < 0)
		abort();
	game_init_info = std::move(info);
}


int udp_p2p::create(std::string addrstr, std::string passwd)
{
	sock = asio::ip::udp::socket(io_context); // to be removed later
	setup_password(passwd);
	auto ipaddr = asio::ip::make_address(addrstr);
	if (ipaddr.is_v4())
		sock.open(asio::ip::udp::v4());
	else if (ipaddr.is_v6())
		sock.open(asio::ip::udp::v6());
	sock.non_blocking(true);
	unsigned short port = default_port;
	/*
	while(port <= default_port+try_ports) {
		try {
			sock.bind(asio::ip::udp::endpoint(asio::ip::address_v6(), port));
		} catch (std::exception e) {
			eprintf("bind: %s,  %s\n", asio::ip::address_v6().to_string(), e.what());
		}
		++port;
	}
	*/
	try {
		sock.bind(endpoint(ipaddr, port));
	} catch (std::exception e) {
		return -1;
	}
	plr_self = 0;
	return plr_self;
}

int udp_p2p::join(std::string addrstr, std::string passwd)
{
	sock = asio::ip::udp::socket(io_context); // to be removed later
	setup_password(passwd);
	auto ipaddr = asio::ip::make_address(addrstr);
	if (ipaddr.is_v4())
		sock.open(asio::ip::udp::v4());
	else if (ipaddr.is_v6())
		sock.open(asio::ip::udp::v6());
	sock.non_blocking(true);
	endpoint themaster(ipaddr, default_port);
	sock.connect(themaster);
	master = themaster;
	{ // hack: try to join for 5 seconds
		randombytes_buf(reinterpret_cast<unsigned char *>(&cookie_self),
		    sizeof(cookie_t));
		upacket pkt = make_packet(PT_JOIN_REQUEST, ADDR_BROADCAST, ADDR_MASTER, cookie_self);
		send(pkt);
		for (auto i = 0; i < 5; ++i) {
			recv();
			if (plr_self != ADDR_BROADCAST)
				break; // join successful
			sleep(1);
		}
	}
	return (plr_self == ADDR_BROADCAST ? 4 : plr_self);
}

void udp_p2p::poll()
{
	recv();
}

void udp_p2p::send(upacket& pkt)
{
	send_internal(pkt, none);
}

bool udp_p2p::connected(plr_t p)
{
	return active_table[p];
}

bool udp_p2p::active(plr_t p)
{
	return active_table[p];
}

void udp_p2p::recv()
{
	try {
		while (1) { // read until kernel buffer is empty?
			try {
				endpoint sender;
				buffer_t pkt_buf(max_packet_size);
				size_t pkt_len;
				pkt_len = sock.receive_from(asio::buffer(pkt_buf), sender);
				pkt_buf.resize(pkt_len);
				upacket pkt = make_packet(pkt_buf);
				recv_decrypted(pkt, sender);
			} catch (packet_exception e) {
				// drop packet
			}
		}
	} catch (std::exception e) {
		return;
	}
}

void udp_p2p::send_internal(upacket &pkt, endpoint sender)
{
	for (auto &dest : dests_for_addr(pkt->dest(), sender)) {
		sock.send_to(asio::buffer(pkt->data()), dest);
	}
}

std::set<udp_p2p::endpoint> udp_p2p::dests_for_addr(plr_t dest, endpoint sender)
{
	auto ret = std::set<endpoint>();
	if (dest == plr_self)
		return ret;

	if (0 <= dest && dest < MAX_PLRS) {
		if (active_table[dest])
			ret.insert(nexthop_table[dest]);
	} else if (dest == ADDR_BROADCAST) {
		for (auto i = 0; i < MAX_PLRS; ++i)
			if (i != plr_self && active_table[i])
				ret.insert(nexthop_table[i]);
		ret.insert(connection_requests_pending.begin(), connection_requests_pending.end());
	} else if (dest == ADDR_MASTER) {
		if (master != none)
			ret.insert(master);
	}
	ret.erase(sender);
	return ret;
}

void udp_p2p::handle_join_request(upacket &pkt, endpoint sender)
{
	plr_t i;
	for (i = 0; i < MAX_PLRS; ++i) {
		if (i != plr_self && nexthop_table[i] == none) {
			nexthop_table[i] = sender;
			break;
		}
	}
	upacket reply = make_packet(PT_JOIN_ACCEPT, plr_self, ADDR_BROADCAST, pkt->cookie(), i, game_init_info);
	send(reply);
}

void udp_p2p::recv_decrypted(upacket &pkt, endpoint sender)
{
	// 1. route
	send_internal(pkt, sender);
	// 2. handle local
	if (pkt->src() == ADDR_BROADCAST && pkt->dest() == ADDR_MASTER) {
		connection_requests_pending.insert(sender);
		if (master == none) {
			handle_join_request(pkt, sender);
		}
	}
	// normal packets
	if (pkt->src() < 0 || pkt->src() >= MAX_PLRS)
		return;                    //drop packet
	if (active_table[pkt->src()]) { //WRONG?!?
		if (sender != nexthop_table[pkt->src()])
			return; //rpfilter fail: drop packet
	} else {
		nexthop_table[pkt->src()] = sender; // new connection: accept
	}
	active_table[pkt->src()] = ACTIVE;
	if (pkt->dest() != plr_self && pkt->dest() != ADDR_BROADCAST)
		return; //packet not for us, drop
	if(pkt->type() == PT_JOIN_ACCEPT)
		handle_accept(pkt);
	else
		recv_local(pkt);
}

void udp_p2p::handle_accept(upacket &pkt)
{
	if (plr_self != ADDR_BROADCAST)
		return; // already have player id
	if (pkt->cookie() == cookie_self)
		plr_self = pkt->newplr();
	_SNETEVENT ev;
	ev.eventid = EVENT_TYPE_PLAYER_CREATE_GAME;
	ev.playerid = plr_self;
	ev.data = const_cast<unsigned char*>(pkt->info().data());
	ev.databytes = pkt->info().size();
	run_event_handler(ev);
}
