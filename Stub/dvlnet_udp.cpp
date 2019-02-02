#include "../types.h"

const dvlnet_udp::endpoint dvlnet_udp::none;

dvlnet_udp::dvlnet_udp(buffer_t info)
{
	if (sodium_init() < 0)
		abort();
	game_init_info = std::move(info);
}

int dvlnet_udp::create(std::string addrstr, std::string passwd)
{
	sock = asio::ip::udp::socket(context); // to be removed later
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

int dvlnet_udp::join(std::string addrstr, std::string passwd)
{
	setup_password(passwd);
	auto ipaddr = asio::ip::make_address(addrstr);
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

void dvlnet_udp::setup_password(std::string pw)
{
	//pw.resize(std::min(pw.size(), crypto_pwhash_PASSWD_MAX));
	//pw.resize(std::max(pw.size(), crypto_pwhash_PASSWD_MIN), 0);
	std::string salt("devilution-salt");
	salt.resize(crypto_pwhash_SALTBYTES, 0);
	if (crypto_pwhash(key.data(), crypto_secretbox_KEYBYTES,
	        pw.data(), pw.size(),
	        reinterpret_cast<const unsigned char *>(salt.data()),
	        crypto_pwhash_OPSLIMIT_INTERACTIVE,
	        crypto_pwhash_MEMLIMIT_INTERACTIVE,
	        crypto_pwhash_ALG_DEFAULT))
		ABORT();
}

void dvlnet_udp::recv()
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

void dvlnet_udp::send(dvlnet_udp::upacket &pkt, endpoint sender)
{
	for (auto &dest : dests_for_addr(pkt->dest(), sender)) {
		sock.send_to(asio::buffer(pkt->data()), dest);
	}
}

std::set<dvlnet_udp::endpoint> dvlnet_udp::dests_for_addr(plr_t dest, endpoint sender)
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

void dvlnet_udp::handle_join_request(upacket &pkt, endpoint sender)
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

void dvlnet_udp::run_event_handler(_SNETEVENT &ev)
{
	/* disable until UI ready
	auto f = registered_handlers[static_cast<event_type>(ev.eventid)];
	if(f) {
		printf("RUNNING HANDLER");
		f(&ev);
	}
	*/
}

void dvlnet_udp::handle_accept(upacket &pkt)
{
	if (plr_self != ADDR_BROADCAST)
		return; // already have player id
	if (pkt->cookie() == cookie_self)
		plr_self = pkt->newplr();
	_SNETEVENT ev;
	ev.eventid = EVENT_TYPE_PLAYER_CREATE_GAME;
	ev.playerid = plr_self;
	ev.data = pkt->info().data();
	ev.databytes = pkt->info().size();
	printf("GOT SEED!!");
	run_event_handler(ev);
}

void dvlnet_udp::recv_decrypted(upacket &pkt, endpoint sender)
{
	// 1. route
	send(pkt, sender);
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
	switch (pkt->type()) {
	case PT_MESSAGE:
		message_queue.push(message_t(pkt->src(), pkt->message()));
		break;
	case PT_TURN:
		turn_last[pkt->src()] = pkt->turn();
		turn_new[pkt->src()] = true;
		break;
	case PT_JOIN_ACCEPT:
		handle_accept(pkt);
		break;
	case PT_LEAVE_GAME:
		// todo
		break;
		// otherwise drop
	}
}

bool dvlnet_udp::SNetReceiveMessage(int *sender, char **data, int *size)
{
	recv();
	if (message_queue.empty())
		return false;
	message_last = message_queue.front();
	message_queue.pop();
	*sender = message_last.sender;
	*size = message_last.payload.size();
	*data = reinterpret_cast<char *>(message_last.payload.data());
	return true;
}

bool dvlnet_udp::SNetSendMessage(int playerID, void *data, unsigned int size)
{
	if (playerID != SNPLAYER_ALL && playerID != SNPLAYER_OTHERS && (playerID < 0 || playerID >= MAX_PLRS))
		abort();
	auto raw_message = reinterpret_cast<unsigned char *>(data);
	buffer_t message(raw_message, raw_message + size);
	if (playerID == plr_self || playerID == SNPLAYER_ALL)
		message_queue.push(message_t(plr_self, message));
	plr_t dest;
	if (playerID == SNPLAYER_ALL || playerID == SNPLAYER_OTHERS)
		dest = ADDR_BROADCAST;
	else
		dest = playerID;
	upacket pkt = make_packet(PT_MESSAGE, plr_self, dest, message);
	send(pkt);
	return true;
}

bool dvlnet_udp::SNetReceiveTurns(char **data, unsigned int *size, DWORD *status)
{
	recv();
	for (auto i = 0; i < MAX_PLRS; ++i) {
		status[i] = 0;
		if (i == plr_self || nexthop_table[i] != none) {
			status[i] |= (PS_ACTIVE | PS_CONNECTED);
		}
		size[i] = sizeof(turn_t);
		if (turn_new[i] = true) {
			status[i] |= PS_HASMSG;
			data[i] = reinterpret_cast<char *>(&turn_last[i]);
			turn_new[i] = false;
		}
	}
	return true;
}

bool dvlnet_udp::SNetSendTurn(char *data, unsigned int size)
{
	if (size != sizeof(turn_t))
		ABORT();
	upacket pkt = make_packet(PT_TURN, plr_self, ADDR_BROADCAST, *reinterpret_cast<turn_t *>(data));
	send(pkt);
	return true;
}

int dvlnet_udp::SNetGetProviderCaps(struct _SNETCAPS *caps)
{
	caps->size = 0;                  // engine writes only ?!?
	caps->flags = 0;                 // unused
	caps->maxmessagesize = 512;      // capped to 512; underflow if < 24
	caps->maxqueuesize = 0;          // unused
	caps->maxplayers = MAX_PLRS;     // capped to 4
	caps->bytessec = 1000000;        // ?
	caps->latencyms = 0;             // unused
	caps->defaultturnssec = 10;      // ?
	caps->defaultturnsintransit = 1; // maximum acceptable number of turns in queue?
	return 1;
}

void *dvlnet_udp::SNetUnregisterEventHandler(event_type evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	registered_handlers.erase(evtype);
	return (void*)func;
}

void *dvlnet_udp::SNetRegisterEventHandler(event_type evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	registered_handlers[evtype] = func;
	return (void*)func;
	// need to handle:
	// EVENT_TYPE_PLAYER_LEAVE_GAME
	// EVENT_TYPE_PLAYER_CREATE_GAME (raised during SNetCreateGame?)
	// EVENT_TYPE_PLAYER_MESSAGE
	// all by the same function
}
