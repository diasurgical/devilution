/**
 * @file nthread.cpp
 *
 * Implementation of functions for managing game ticks.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

BYTE gbGameLoopsPerPacket;
DWORD gdwTurnsInTransit;
DWORD gdwNormalMsgSize;
DWORD gdwLargestMsgSize;
DWORD gdwDeltaBytesSec;
DWORD gdwMsgLenTbl[MAX_PLRS];
int glpMsgTbl[MAX_PLRS];
unsigned int sgThreadID;
int sgdwRequestDeltaFlag;
BOOLEAN sgbRunThread;
BOOLEAN sgbThreadIsRunning;
static CCritSect sgCrit;
BOOLEAN sgbGotPacketOK;
char sgbPacketCountdown;
char sgbSyncCountdown;
int sglGameClock = 0;

/* data */
static HANDLE sghThread = INVALID_HANDLE_VALUE;

void nthread_terminate_game(const char *pszFcn)
{
	DWORD sErr;

	sErr = DERROR();
	if (sErr == STORM_ERROR_INVALID_PLAYER) {
		return;
	} else if (sErr == STORM_ERROR_GAME_TERMINATED) {
		gbGameDestroyed = TRUE;
	} else if (sErr == STORM_ERROR_NOT_IN_GAME) {
		gbGameDestroyed = TRUE;
	} else {
		app_fatal("%s:\n%s", pszFcn, TraceLastError());
	}
}

DWORD nthread_send_and_recv_turn(DWORD cur_turn, int turn_delta)
{
	DWORD new_cur_turn;
	int turn, turn_tmp;
	int curTurnsInTransit;

	new_cur_turn = cur_turn;
	if (!SNetGetTurnsInTransit(&curTurnsInTransit)) {
		nthread_terminate_game("SNetGetTurnsInTransit");
		return 0;
	}
	while (curTurnsInTransit++ < gdwTurnsInTransit) {

		turn_tmp = sgdwRequestDeltaFlag | new_cur_turn & 0x7FFFFFFF;
		sgdwRequestDeltaFlag = 0;
		turn = turn_tmp;

		if (!SNetSendTurn((char *)&turn, sizeof(turn))) {
			nthread_terminate_game("SNetSendTurn");
			return 0;
		}

		new_cur_turn += turn_delta;
		if (new_cur_turn >= 0x7FFFFFFF)
			new_cur_turn &= 0xFFFF;
	}
	return new_cur_turn;
}

BOOL nthread_recv_turns(BOOL *pfSendAsync)
{
	*pfSendAsync = FALSE;
	sgbPacketCountdown--;
	if (sgbPacketCountdown) {
		sglGameClock += 50;
		return TRUE;
	}
	sgbSyncCountdown--;
	sgbPacketCountdown = gbGameLoopsPerPacket;
	if (sgbSyncCountdown != 0) {

		*pfSendAsync = TRUE;
		sglGameClock += 50;
		return TRUE;
	}
	if (!SNetReceiveTurns(0, MAX_PLRS, (char **)glpMsgTbl, gdwMsgLenTbl, (LPDWORD)player_state)) {
		if (DERROR() != STORM_ERROR_NO_MESSAGES_WAITING)
			nthread_terminate_game("SNetReceiveTurns");
		sgbGotPacketOK = FALSE;
		sgbSyncCountdown = 1;
		sgbPacketCountdown = 1;
		return FALSE;
	} else {
		if (!sgbGotPacketOK) {
			sgbGotPacketOK = TRUE;
			sglGameClock = GetTickCount();
		}
		sgbSyncCountdown = 4;
		multi_msg_countdown();
		*pfSendAsync = TRUE;
		sglGameClock += 50;
		return TRUE;
	}
}

static unsigned int __stdcall nthread_handler(void *data)
{
	int delta;
	BOOL received;

	if (sgbRunThread) {
		while (1) {
			sgCrit.Enter();
			if (!sgbRunThread)
				break;
			nthread_send_and_recv_turn(0, 0);
			if (nthread_recv_turns(&received))
				delta = sglGameClock - GetTickCount();
			else
				delta = 50;
			sgCrit.Leave();
			if (delta > 0)
				Sleep(delta);
			if (!sgbRunThread)
				return 0;
		}
		sgCrit.Leave();
	}
	return 0;
}

void nthread_set_turn_upper_bit()
{
	sgdwRequestDeltaFlag = 0x80000000;
}

void nthread_start(BOOL set_turn_upper_bit)
{
	const char *err, *err2;
	DWORD largestMsgSize;
	_SNETCAPS caps;

	sglGameClock = GetTickCount();
	sgbPacketCountdown = 1;
	sgbSyncCountdown = 1;
	sgbGotPacketOK = TRUE;
	if (set_turn_upper_bit)
		nthread_set_turn_upper_bit();
	else
		sgdwRequestDeltaFlag = 0;
	caps.size = 36;
	if (!SNetGetProviderCaps(&caps)) {
		err = TraceLastError();
		app_fatal("SNetGetProviderCaps:\n%s", err);
	}
	gdwTurnsInTransit = caps.defaultturnsintransit;
	if (!caps.defaultturnsintransit)
		gdwTurnsInTransit = 1;
	if (caps.defaultturnssec <= 20 && caps.defaultturnssec)
		gbGameLoopsPerPacket = 20 / caps.defaultturnssec;
	else
		gbGameLoopsPerPacket = 1;
	largestMsgSize = 512;
	if (caps.maxmessagesize < 0x200)
		largestMsgSize = caps.maxmessagesize;
	gdwDeltaBytesSec = caps.bytessec >> 2;
	gdwLargestMsgSize = largestMsgSize;
	gdwNormalMsgSize = caps.bytessec * gbGameLoopsPerPacket / 20;
	gdwNormalMsgSize *= 3;
	gdwNormalMsgSize >>= 2;
	if (caps.maxplayers > MAX_PLRS)
		caps.maxplayers = MAX_PLRS;
	gdwNormalMsgSize /= caps.maxplayers;
	while (gdwNormalMsgSize < 0x80) {
		gdwNormalMsgSize *= 2;
		gbGameLoopsPerPacket *= 2;
	}
	if (gdwNormalMsgSize > largestMsgSize)
		gdwNormalMsgSize = largestMsgSize;
	if (gbMaxPlayers > 1) {
		sgbThreadIsRunning = FALSE;
		sgCrit.Enter();
		sgbRunThread = TRUE;
		sghThread = (HANDLE)_beginthreadex(NULL, 0, nthread_handler, NULL, 0, &sgThreadID);
		if (sghThread == INVALID_HANDLE_VALUE) {
			err2 = TraceLastError();
			app_fatal("nthread2:\n%s", err2);
		}
		SetThreadPriority(sghThread, THREAD_PRIORITY_HIGHEST);
	}
}

void nthread_cleanup()
{
	sgbRunThread = FALSE;
	gdwTurnsInTransit = 0;
	gdwNormalMsgSize = 0;
	gdwLargestMsgSize = 0;
	if (sghThread != INVALID_HANDLE_VALUE && sgThreadID != GetCurrentThreadId()) {
		if (!sgbThreadIsRunning)
			sgCrit.Leave();
		if (WaitForSingleObject(sghThread, INFINITE) == -1) {
			app_fatal("nthread3:\n(%s)", TraceLastError());
		}
		CloseHandle(sghThread);
		sghThread = INVALID_HANDLE_VALUE;
	}
}

void nthread_ignore_mutex(BOOL bStart)
{
	if (sghThread != INVALID_HANDLE_VALUE) {
		if (bStart)
			sgCrit.Leave();
		else
			sgCrit.Enter();
		sgbThreadIsRunning = bStart;
	}
}

/**
 * @brief Checks if it's time for the logic to advance
 * @param unused
 * @return True if the engine should tick

 */
BOOL nthread_has_500ms_passed(BOOL unused)
{
	DWORD currentTickCount;
	int ticksElapsed;

	currentTickCount = GetTickCount();
	ticksElapsed = currentTickCount - sglGameClock;
	if (gbMaxPlayers == 1 && ticksElapsed > 500) {
		sglGameClock = currentTickCount;
		ticksElapsed = 0;
	}
	return ticksElapsed >= 0;
}
