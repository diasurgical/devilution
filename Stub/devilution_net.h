#include "sodium.h"
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/ts/io_context.hpp>
#include <asio/ts/net.hpp>

class devilution_net {
public:
	typedef std::vector<unsigned char> buffer_t;

	static std::unique_ptr<devilution_net> inst;

	virtual int create(std::string addrstr, std::string passwd) = 0;
	virtual int join(std::string addrstr, std::string passwd) = 0;

	virtual bool SNetReceiveMessage(int *sender, char **data, int *size) = 0;
	virtual bool SNetSendMessage(int dest, void *data, unsigned int size) = 0;
	virtual bool SNetReceiveTurns(char **data, unsigned int *size, DWORD *status) = 0;
	virtual bool SNetSendTurn(char *data, unsigned int size) = 0;
	virtual int SNetGetProviderCaps(struct _SNETCAPS *caps) = 0;
};

class devilution_net_single : public devilution_net {
private:
	std::queue<buffer_t> message_queue;
	buffer_t message_last;
	const int plr_single = 0;

public:
	virtual int create(std::string addrstr, std::string passwd)
	{
		return plr_single;
	}

	virtual int join(std::string addrstr, std::string passwd)
	{
		ABORT();
	}

	virtual bool SNetReceiveMessage(int *sender, char **data, int *size)
	{
		if (message_queue.empty())
			return false;
		message_last = message_queue.front();
		message_queue.pop();
		*sender = plr_single;
		*size = message_last.size();
		*data = reinterpret_cast<char *>(message_last.data());
		return true;
	}

	virtual bool SNetSendMessage(int dest, void *data, unsigned int size)
	{
		if (dest == plr_single || dest == SNPLAYER_ALL) {
			auto raw_message = reinterpret_cast<unsigned char *>(data);
			buffer_t message(raw_message, raw_message + size);
			message_queue.push(message);
		}
		return true;
	}

	virtual bool SNetReceiveTurns(char **data, unsigned int *size, DWORD *status)
	{
	}
	virtual bool SNetSendTurn(char *data, unsigned int size)
	{
	}
	virtual int SNetGetProviderCaps(struct _SNETCAPS *caps)
	{
	}
};

// exact meaning yet to be worked out
#define PS_HASMSG 0x20000
#define PS_ACTIVE 0x40000
#define PS_CONNECTED 0x10000

class devilution_net_udp : public devilution_net {
public:
	devilution_net_udp();
	virtual int create(std::string addrstr, std::string passwd);
	virtual int join(std::string addrstr, std::string passwd);

	virtual bool SNetReceiveMessage(int *sender, char **data, int *size);
	virtual bool SNetSendMessage(int dest, void *data, unsigned int size);
	virtual bool SNetReceiveTurns(char **data, unsigned int *size, DWORD *status);
	virtual bool SNetSendTurn(char *data, unsigned int size);
	virtual int SNetGetProviderCaps(struct _SNETCAPS *caps);

	static constexpr unsigned short max_packet_size = 0xFFFF;

	enum packet_type : uint8_t {
		PT_MESSAGE = 0x01,
		PT_TURN = 0x02,
		PT_JOIN_REQUEST = 0x11,
		PT_JOIN_ACCEPT = 0x12,
		PT_LEAVE_GAME = 0x13,
	};
	typedef uint8_t plr_t;
	typedef uint32_t cookie_t;
	typedef int turn_t; // change int to something else in devilution code later
	typedef std::array<unsigned char, crypto_secretbox_KEYBYTES> key_t;
	class packet_exception : public std::exception {
	};
	typedef asio::ip::udp::endpoint endpoint;
	static const endpoint none;

	class packet {
	private:
		class encrypt_mode_t {
		};
		class decrypt_mode_t {
		};

		bool have_encrypted = false;
		bool have_decrypted = false;

		const key_t &key;

		packet_type m_type;
		plr_t m_src;
		plr_t m_dest;
		buffer_t m_message;
		turn_t m_turn;
		cookie_t m_cookie;
		plr_t m_newplr;
		plr_t m_oldplr;

		buffer_t encrypted_buffer;
		buffer_t decrypted_buffer;

		template <class mode>
		void process_data();
		template <class T>
		void process_element(encrypt_mode_t, T &x);
		template <class T>
		void process_element(decrypt_mode_t, T &x);
		void process_element(encrypt_mode_t, buffer_t &x);
		void process_element(decrypt_mode_t, buffer_t &x);
		template <class T>
		static const unsigned char *begin(const T &x);
		template <class T>
		static const unsigned char *end(const T &x);

	public:
		packet(const key_t &k)
		    : key(k)
		{
		}

		void create(packet_type t, plr_t s, plr_t d, buffer_t m);
		void create(packet_type t, plr_t s, plr_t d, turn_t u);
		void create(packet_type t, plr_t s, plr_t d, cookie_t c);
		void create(packet_type t, plr_t s, plr_t d, cookie_t c, plr_t n);
		void create(packet_type t, plr_t s, plr_t d, plr_t o);
		void create(std::vector<unsigned char> buf);

		const buffer_t &data();

		packet_type type();
		plr_t src();
		plr_t dest();
		const buffer_t &message();
		turn_t turn();
		cookie_t cookie();
		plr_t newplr();
		plr_t oldplr();

		void encrypt();
		void decrypt();
	};

private:
	static constexpr unsigned short default_port = 6112;
	static constexpr unsigned short try_ports = 512;
	static constexpr daddr_t ADDR_BROADCAST = 0xFF;
	static constexpr daddr_t ADDR_MASTER = 0xFE;
	static constexpr int ACTIVE = 60;

	struct message_t {
		int sender; // change int to something else in devilution code later
		buffer_t payload;
		message_t()
		    : sender(-1)
		    , payload({}){};
		message_t(int s, buffer_t p)
		    : sender(s)
		    , payload(p){};
	};

	message_t message_last;
	std::queue<message_t> message_queue;
	std::array<turn_t, MAX_PLRS> turn_last = { 0 };
	std::array<bool, MAX_PLRS> turn_new = { false };

	plr_t plr_self = ADDR_BROADCAST;
	unsigned short udpport_self = 0;
	cookie_t cookie_self = 0;

	key_t key = { 0 };
	endpoint master;

	std::set<endpoint> connection_requests_pending;
	std::array<endpoint, MAX_PLRS> nexthop_table;
	std::array<int, MAX_PLRS> active_table = { 0 };
	asio::io_context context;
	asio::ip::udp::socket sock = asio::ip::udp::socket(context);

	unsigned short bind();
	void setup_password(std::string pw);

	void handle_join_request(packet &pkt, endpoint sender);
	void handle_accept(packet &pkt);
	void recv();
	void send(packet &pkt, endpoint sender = none);
	void recv_decrypted(packet &pkt, endpoint sender);
	std::set<endpoint> dests_for_addr(plr_t dest, endpoint sender);
};

template <class mode>
void devilution_net_udp::packet::process_data()
{
	process_element(mode(), m_type);
	process_element(mode(), m_src);
	process_element(mode(), m_dest);
	switch (m_type) {
	case PT_MESSAGE:
		process_element(mode(), m_message);
		break;
	case PT_TURN:
		process_element(mode(), m_turn);
		break;
	case PT_JOIN_REQUEST:
		process_element(mode(), m_cookie);
		break;
	case PT_JOIN_ACCEPT:
		process_element(mode(), m_cookie);
		process_element(mode(), m_newplr);
		break;
	case PT_LEAVE_GAME:
		break;
	}
}

template <class T>
void devilution_net_udp::packet::process_element(encrypt_mode_t, T &x)
{
	encrypted_buffer.insert(encrypted_buffer.end(), begin(x), end(x));
}

inline void devilution_net_udp::packet::process_element(encrypt_mode_t, buffer_t &x)
{
	encrypted_buffer.insert(encrypted_buffer.end(), x.begin(), x.end());
}

template <class T>
void devilution_net_udp::packet::process_element(decrypt_mode_t, T &x)
{
	if (decrypted_buffer.size() < sizeof(T))
		throw packet_exception();
	x = *reinterpret_cast<T *>(decrypted_buffer.data());
	decrypted_buffer.erase(decrypted_buffer.begin(), decrypted_buffer.begin() + sizeof(T));
}

inline void devilution_net_udp::packet::process_element(decrypt_mode_t, buffer_t &x)
{
	x.insert(x.begin(), decrypted_buffer.begin(), decrypted_buffer.end());
	decrypted_buffer.resize(0);
}

template <class T>
const unsigned char *devilution_net_udp::packet::begin(const T &x)
{
	return reinterpret_cast<const unsigned char *>(&x);
}

template <class T>
const unsigned char *devilution_net_udp::packet::end(const T &x)
{
	return reinterpret_cast<const unsigned char *>(&x) + sizeof(T);
}
