// exact meaning yet to be worked out
#define PS_CONNECTED 0x10000
#define PS_TURN_ARRIVED 0x20000
#define PS_ACTIVE 0x40000

namespace dvlnet {
	class base : public dvlnet {
	public:
		virtual int create(std::string addrstr, std::string passwd) = 0;
		virtual int join(std::string addrstr, std::string passwd) = 0;

		virtual bool SNetReceiveMessage(int* sender, char** data, int* size);
		virtual bool SNetSendMessage(int dest, void* data, unsigned int size);
		virtual bool SNetReceiveTurns(char** data, unsigned int* size, DWORD* status);
		virtual bool SNetSendTurn(char* data, unsigned int size);
		virtual int SNetGetProviderCaps(struct _SNETCAPS* caps);
		virtual void* SNetRegisterEventHandler(event_type evtype, void(__stdcall* func)(struct _SNETEVENT*));
		virtual void* SNetUnregisterEventHandler(event_type evtype, void(__stdcall* func)(struct _SNETEVENT*));

		virtual void poll() = 0;
		virtual void send(upacket& pkt) = 0;
		virtual bool connected(plr_t p) = 0;
		virtual bool active(plr_t p) = 0;

		static constexpr unsigned short max_packet_size = 0xFFFF;
		upacket make_packet(buffer_t buf);
		template<typename T, typename... Args> upacket make_packet(T t, Args... args);

	protected:
		static constexpr daddr_t ADDR_BROADCAST = 0xFF;
		static constexpr daddr_t ADDR_MASTER = 0xFE;

		std::map<event_type, void(__stdcall*)(struct _SNETEVENT*)> registered_handlers;
		buffer_t game_init_info;

		struct message_t {
			int sender; // change int to something else in devilution code later
			buffer_t payload;
			message_t() : sender(-1), payload({}) {}
		    message_t(int s, buffer_t p) : sender(s), payload(p) {}
		};

		message_t message_last;
		std::queue<message_t> message_queue;
		std::array<turn_t, MAX_PLRS> turn_last = { 0 };
		std::array<std::queue<turn_t>, MAX_PLRS> turn_queue;

		plr_t plr_self = ADDR_BROADCAST;
		cookie_t cookie_self = 0;

		key_t key = { 0 };

		void setup_password(std::string pw);
		void recv_local(upacket &pkt);
		void run_event_handler(_SNETEVENT &ev);
	};

	inline upacket base::make_packet(buffer_t buf)
	{
		auto ret = std::make_unique<packet_in>(key);
		ret->create(std::move(buf));
		ret->decrypt();
		return ret;
	}

	template<typename T, typename... Args> upacket base::make_packet(T t, Args... args)
	{
		auto ret = std::make_unique<packet_out>(key);
		ret->create(t, args...);
		ret->encrypt();
		return ret;
	}
}
