#include "../types.h"

using namespace dvlnet;

void base::setup_password(std::string pw)
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

void base::run_event_handler(_SNETEVENT& ev)
{
	auto f = registered_handlers[static_cast<event_type>(ev.eventid)];
	if(f) {
		f(&ev);
	}
}

void base::recv_local(upacket& pkt)
{
	switch (pkt->type()) {
	case PT_MESSAGE:
		message_queue.push(message_t(pkt->src(), pkt->message()));
		break;
	case PT_TURN:
		turn_queue[pkt->src()].push(pkt->turn());
		break;
	case PT_LEAVE_GAME:
		// todo
		break;
		// otherwise drop
	}
}

bool base::SNetReceiveMessage(int* sender, char** data, int* size)
{
	poll();
	if (message_queue.empty())
		return false;
	message_last = message_queue.front();
	message_queue.pop();
	*sender = message_last.sender;
	*size = message_last.payload.size();
	*data = reinterpret_cast<char *>(message_last.payload.data());
	return true;
}

bool base::SNetSendMessage(int playerID, void* data, unsigned int size)
{
	if (playerID != SNPLAYER_ALL && playerID != SNPLAYER_OTHERS && (playerID < 0 || playerID >= MAX_PLRS))
		abort();
	auto raw_message = reinterpret_cast<unsigned char*>(data);
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

bool base::SNetReceiveTurns(char **data, unsigned int *size, DWORD *status)
{
	poll();
	for (auto i = 0; i < MAX_PLRS; ++i) {
		status[i] = 0;
		if (i == plr_self || active(i)) {
			status[i] |= PS_ACTIVE;
		}
		if (i == plr_self || connected(i)) {
			status[i] |= PS_CONNECTED;
		}
		if (!turn_queue[i].empty()) {
			size[i] = sizeof(turn_t);
			status[i] |= PS_TURN_ARRIVED;
			turn_last[i] = turn_queue[i].front();
			turn_queue[i].pop();
			data[i] = reinterpret_cast<char *>(&turn_last[i]);
		}
	}
	return true;
}

bool base::SNetSendTurn(char* data, unsigned int size)
{
	if (size != sizeof(turn_t))
		ABORT();
	upacket pkt = make_packet(PT_TURN, plr_self, ADDR_BROADCAST, *reinterpret_cast<turn_t*>(data));
	send(pkt);
	return true;
}

int base::SNetGetProviderCaps(struct _SNETCAPS* caps)
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

void* base::SNetUnregisterEventHandler(event_type evtype, void(__stdcall* func)(struct _SNETEVENT *))
{
	registered_handlers.erase(evtype);
	return (void*)func;
}

void* base::SNetRegisterEventHandler(event_type evtype, void(__stdcall* func)(struct _SNETEVENT *))
{
	registered_handlers[evtype] = func;
	return (void*)func;
	// need to handle:
	// EVENT_TYPE_PLAYER_LEAVE_GAME
	// EVENT_TYPE_PLAYER_CREATE_GAME (raised during SNetCreateGame?)
	// EVENT_TYPE_PLAYER_MESSAGE
	// all by the same function
}
