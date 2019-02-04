namespace dvlnet {
	class udp_p2p : public base {
	public:
		udp_p2p(buffer_t info);
		virtual int create(std::string addrstr, std::string passwd);
		virtual int join(std::string addrstr, std::string passwd);
		virtual void poll();
		virtual void send(upacket& pkt);
		virtual bool connected(plr_t p);
		virtual bool active(plr_t p);

	private:
		typedef asio::ip::udp::endpoint endpoint;
		static const endpoint none;

		unsigned short udpport_self = 0;

		static constexpr unsigned short default_port = 6112;
		static constexpr unsigned short try_ports = 512;
		static constexpr int ACTIVE = 60;

		asio::io_context io_context;
		endpoint master;

		std::set<endpoint> connection_requests_pending;
		std::array<endpoint, MAX_PLRS> nexthop_table;
		std::array<int, MAX_PLRS> active_table = { 0 };

		asio::ip::udp::socket sock = asio::ip::udp::socket(io_context);

		void recv();
		void handle_join_request(upacket &pkt, endpoint sender);
		void handle_accept(upacket &pkt);
		void send_internal(upacket& pkt, endpoint sender = none);
		std::set<endpoint> dests_for_addr(plr_t dest, endpoint sender);
		void recv_decrypted(upacket &pkt, endpoint sender);
	};
}
