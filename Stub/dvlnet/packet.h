#pragma once

namespace dvlnet {
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
	typedef std::vector<unsigned char> buffer_t;
	typedef std::array<unsigned char, crypto_secretbox_KEYBYTES> key_t;

	class packet_exception : public std::exception {};

	class packet {
	protected:
		packet_type m_type;
		plr_t m_src;
		plr_t m_dest;
		buffer_t m_message;
		turn_t m_turn;
		cookie_t m_cookie;
		plr_t m_newplr;
		plr_t m_oldplr;
		buffer_t m_info;

		const key_t &key;
		bool have_encrypted = false;
		bool have_decrypted = false;
		buffer_t encrypted_buffer;
		buffer_t decrypted_buffer;

	public:
		packet(const key_t &k) : key(k) {};

		const buffer_t &data();

		packet_type type();
		plr_t src();
		plr_t dest();
		const buffer_t &message();
		turn_t turn();
		cookie_t cookie();
		plr_t newplr();
		plr_t oldplr();
		const buffer_t &info();
	};

	template<class P> class packet_proc : public packet {
	public:
		using packet::packet;
		void process_data();
	};

	typedef std::unique_ptr<packet> upacket;

	class packet_in : public packet_proc<packet_in> {
	public:
		using packet_proc<packet_in>::packet_proc;
		void create(buffer_t buf);
		void process_element(buffer_t &x);
		template <class T> void process_element(T &x);
		void decrypt();
	};

	class packet_out : public packet_proc<packet_out> {
	public:
		using packet_proc<packet_out>::packet_proc;
		void create(packet_type t, plr_t s, plr_t d, buffer_t m);
		void create(packet_type t, plr_t s, plr_t d, turn_t u);
		void create(packet_type t, plr_t s, plr_t d, cookie_t c);
		void create(packet_type t, plr_t s, plr_t d, cookie_t c, plr_t n, buffer_t i);
		void create(packet_type t, plr_t s, plr_t d, plr_t o);
		void process_element(buffer_t &x);
		template <class T> void process_element(T &x);
		template <class T> static const unsigned char *begin(const T &x);
		template <class T> static const unsigned char *end(const T &x);
		void encrypt();
	};

	template<class P> void packet_proc<P>::process_data()
	{
		P &self = static_cast<P&>(*this);
		self.process_element(m_type);
		self.process_element(m_src);
		self.process_element(m_dest);
		switch (m_type) {
		case PT_MESSAGE:
			self.process_element(m_message);
			break;
		case PT_TURN:
			self.process_element(m_turn);
			break;
		case PT_JOIN_REQUEST:
			self.process_element(m_cookie);
			break;
		case PT_JOIN_ACCEPT:
			self.process_element(m_cookie);
			self.process_element(m_newplr);
			self.process_element(m_info);
			break;
		case PT_LEAVE_GAME:
			break;
		}
	}

	inline void packet_in::process_element(buffer_t &x)
	{
		x.insert(x.begin(), decrypted_buffer.begin(), decrypted_buffer.end());
		decrypted_buffer.resize(0);
	}

	template <class T> void packet_in::process_element(T &x)
	{
		if (decrypted_buffer.size() < sizeof(T))
			throw packet_exception();
		x = *reinterpret_cast<T *>(decrypted_buffer.data());
		decrypted_buffer.erase(decrypted_buffer.begin(), decrypted_buffer.begin() + sizeof(T));
	}

	inline void packet_out::process_element(buffer_t &x)
	{
		encrypted_buffer.insert(encrypted_buffer.end(), x.begin(), x.end());
	}

	template <class T> void packet_out::process_element(T &x)
	{
		encrypted_buffer.insert(encrypted_buffer.end(), begin(x), end(x));
	}

	template <class T> const unsigned char* packet_out::begin(const T &x)
	{
		return reinterpret_cast<const unsigned char *>(&x);
	}

	template <class T> const unsigned char* packet_out::end(const T &x)
	{
		return reinterpret_cast<const unsigned char *>(&x) + sizeof(T);
	}
}
