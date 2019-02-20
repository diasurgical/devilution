#pragma once

namespace dvlnet {
	class tcp_client : public base {
	public:
		int create(std::string addrstr, std::string passwd);
		int join(std::string addrstr, std::string passwd);

		static constexpr unsigned short default_port = 6112;

		virtual void poll();
		virtual void send(packet& pkt);
	private:
		std::unique_ptr<tcp_server> local_server;

		frame_queue recv_queue;
		buffer_t recv_buffer = buffer_t(frame_queue::max_frame_size);

		asio::io_context ioc;
		asio::ip::tcp::socket sock = asio::ip::tcp::socket(ioc);

		void handle_recv(const asio::error_code& error, size_t bytes_read);
		void start_recv();
		void handle_send(const asio::error_code& error, size_t bytes_sent);
	};
}
