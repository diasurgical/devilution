#include "../types.h"

using namespace dvlnet;

int tcp_client::create(std::string addrstr, std::string passwd)
{
	local_server = std::make_unique<tcp_server>(ioc, addrstr,
	                                            default_port, passwd);
	return join(local_server->localhost_self(), passwd);
}

int tcp_client::join(std::string addrstr, std::string passwd)
{
	setup_password(passwd);
	auto ipaddr = asio::ip::make_address(addrstr);
	sock.connect(asio::ip::tcp::endpoint(ipaddr, default_port));
	start_recv();
	{ // hack: try to join for 5 seconds
		randombytes_buf(reinterpret_cast<unsigned char*>(&cookie_self),
		                sizeof(cookie_t));
		auto pkt = pktfty->make_packet<PT_JOIN_REQUEST>(PLR_BROADCAST,
		                                                PLR_MASTER, cookie_self,
		                                                game_init_info);
		send(*pkt);
		for (auto i = 0; i < 5; ++i) {
			poll();
			if (plr_self != PLR_BROADCAST)
				break; // join successful
			sleep(1);
		}
	}
	return (plr_self == PLR_BROADCAST ? -1 : plr_self);
}

void tcp_client::poll()
{
	ioc.poll();
}

void tcp_client::handle_recv(const asio::error_code& error, size_t bytes_read)
{
	if(error)
		throw std::runtime_error("");
	if(bytes_read == 0)
		throw std::runtime_error("");
	recv_buffer.resize(bytes_read);
	recv_queue.write(std::move(recv_buffer));
	recv_buffer.resize(frame_queue::max_frame_size);
	while(recv_queue.packet_ready()) {
		auto pkt = pktfty->make_packet(recv_queue.read_packet());
		recv_local(*pkt);
	}
	start_recv();
}

void tcp_client::start_recv()
{
	sock.async_receive(asio::buffer(recv_buffer),
	                   std::bind(&tcp_client::handle_recv, this,
	                             std::placeholders::_1, std::placeholders::_2));
}

void tcp_client::handle_send(const asio::error_code& error, size_t bytes_sent)
{
	// empty for now
}

void tcp_client::send(packet& pkt)
{
	auto frame = frame_queue::make_frame(pkt.data());
	asio::async_write(sock, asio::buffer(frame),
	                  std::bind(&tcp_client::handle_send, this,
	                            std::placeholders::_1, std::placeholders::_2));
}
