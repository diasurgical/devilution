#include "../types.h"

using namespace dvlnet;

base::base(buffer_t info)
{
	game_init_info = std::move(info);
}

void base::setup_password(std::string pw)
{
	pktfty = std::make_unique<packet_factory>(pw);
}

void base::run_event_handler(_SNETEVENT& ev)
{
	auto f = registered_handlers[static_cast<event_type>(ev.eventid)];
	if(f) {
		f(&ev);
	}
}

void base::handle_accept(packet& pkt)
{
	if (plr_self != PLR_BROADCAST)
		return; // already have player id
	if (pkt.cookie() == cookie_self)
		plr_self = pkt.newplr();
	if (game_init_info != pkt.info()) {
		// we joined and did not create
		_SNETEVENT ev;
		ev.eventid = EVENT_TYPE_PLAYER_CREATE_GAME;
		ev.playerid = plr_self;
		ev.data = const_cast<unsigned char*>(pkt.info().data());
		ev.databytes = pkt.info().size();
		run_event_handler(ev);
	}
}

void base::recv_local(packet& pkt)
{
	switch (pkt.type()) {
	case PT_MESSAGE:
		message_queue.push(message_t(pkt.src(), pkt.message()));
		break;
	case PT_TURN:
		turn_queue[pkt.src()].push(pkt.turn());
		break;
	case PT_JOIN_ACCEPT:
		handle_accept(pkt);
		break;
	case PT_CONNECT:
		connected_table[pkt.newplr()] = true;
		active_table[pkt.newplr()] = true;
		break;
	case PT_DISCONNECT:
		if (pkt.newplr() != plr_self) {
			auto leaveinfo = pkt.leaveinfo();
			_SNETEVENT ev;
			ev.eventid = EVENT_TYPE_PLAYER_LEAVE_GAME;
			ev.playerid = pkt.newplr();
			ev.data = reinterpret_cast<unsigned char*>(&leaveinfo);
			ev.databytes = sizeof(leaveinfo_t);
			run_event_handler(ev);
		} else {
			// problem
		}
		connected_table[pkt.newplr()] = false;
		active_table[pkt.newplr()] = false;
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
	*data = reinterpret_cast<char*>(message_last.payload.data());
	return true;
}

bool base::SNetSendMessage(int playerID, void* data, unsigned int size)
{
	if (playerID != SNPLAYER_ALL && playerID != SNPLAYER_OTHERS
	    && (playerID < 0 || playerID >= MAX_PLRS))
		abort();
	auto raw_message = reinterpret_cast<unsigned char*>(data);
	buffer_t message(raw_message, raw_message + size);
	if (playerID == plr_self || playerID == SNPLAYER_ALL)
		message_queue.push(message_t(plr_self, message));
	plr_t dest;
	if (playerID == SNPLAYER_ALL || playerID == SNPLAYER_OTHERS)
		dest = PLR_BROADCAST;
	else
		dest = playerID;
	if(dest != plr_self) {
		auto pkt = pktfty->make_packet<PT_MESSAGE>(plr_self, dest, message);
		send(*pkt);
	}
	return true;
}

bool base::SNetReceiveTurns(char** data, unsigned int* size, DWORD* status)
{
	poll();
	for (auto i = 0; i < MAX_PLRS; ++i) {
		status[i] = 0;
		if (active_table[i] || i == plr_self) {
			status[i] |= PS_ACTIVE;
		}
		if (connected_table[i] || i == plr_self) {
			status[i] |= PS_CONNECTED;
		}
		if (!turn_queue[i].empty()) {
			size[i] = sizeof(turn_t);
			status[i] |= PS_TURN_ARRIVED;
			turn_last[i] = turn_queue[i].front();
			turn_queue[i].pop();
			data[i] = reinterpret_cast<char*>(&turn_last[i]);
		}
	}
	return true;
}

bool base::SNetSendTurn(char* data, unsigned int size)
{
	if (size != sizeof(turn_t))
		ABORT();
	auto pkt = pktfty->make_packet<PT_TURN>(plr_self, PLR_BROADCAST,
	                                        *reinterpret_cast<turn_t*>(data));
	send(*pkt);
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
	caps->defaultturnsintransit = 1; // maximum acceptable number
	                                 // of turns in queue?
	return 1;
}

void* base::SNetUnregisterEventHandler(event_type evtype, snet_event_func func)
{
	registered_handlers.erase(evtype);
	return (void*)func;
}

void* base::SNetRegisterEventHandler(event_type evtype, snet_event_func func)
{
	/*
	engine registers handler for:
	EVENT_TYPE_PLAYER_LEAVE_GAME
	EVENT_TYPE_PLAYER_CREATE_GAME (should be raised during SNetCreateGame
	                              for non-creating player)
	EVENT_TYPE_PLAYER_MESSAGE (for bnet? not implemented)
	(engine uses same function for all three)
	*/
	registered_handlers[evtype] = func;
	return (void*)func;
}

bool base::SNetLeaveGame(int type)
{
	auto pkt = pktfty->make_packet<PT_DISCONNECT>(plr_self, PLR_BROADCAST,
	                                              plr_self, type);
	send(*pkt);
	return true;
}
