#pragma once

namespace dvlnet {
	class loopback : public dvlnet {
	private:
		std::queue<buffer_t> message_queue;
		buffer_t message_last;
		const int plr_single = 0;

	public:
		virtual int create(std::string addrstr, std::string passwd);
		virtual int join(std::string addrstr, std::string passwd);
		virtual bool SNetReceiveMessage(int* sender, char** data, int* size);
		virtual bool SNetSendMessage(int dest, void* data, unsigned int size);
		virtual bool SNetReceiveTurns(char** data, unsigned int* size,
		                              DWORD* status);
		virtual bool SNetSendTurn(char* data, unsigned int size);
		virtual int SNetGetProviderCaps(struct _SNETCAPS* caps);
		virtual void *SNetRegisterEventHandler(event_type evtype,
		                                       snet_event_func func);
		virtual void *SNetUnregisterEventHandler(event_type evtype,
		                                         snet_event_func func);
		virtual bool SNetLeaveGame(int type);
	};
}
