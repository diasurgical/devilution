/**
 * @file track.cpp
 *
 * Implementation of functionality tracking what the mouse cursor is pointing at.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

/** 1.09b name (Hellfire source); uninitialised, so it is placed by name */
static BYTE sgbTrackMode;
static DWORD sgdwLastWalk = 0;
static BOOL sgbIsWalking = 0;

void track_process()
{
	if (!sgbIsWalking)
		return;

	if (cursmx < 0 || cursmx >= MAXDUNX - 1 || cursmy < 0 || cursmy >= MAXDUNY - 1)
		return;

	if (plr[myplr]._pVar8 <= 6 && plr[myplr]._pmode != PM_STAND)
		return;

	if (cursmx != plr[myplr]._ptargx || cursmy != plr[myplr]._ptargy) {
		DWORD tick = GetTickCount();
		if ((int)(tick - sgdwLastWalk) >= 300) {
			sgdwLastWalk = tick;
			NetSendCmdLoc(TRUE, CMD_WALKXY, cursmx, cursmy);
			if (!sgbTrackMode)
				sgbTrackMode = TRUE;
		}
	}
}

void track_repeat_walk(BOOL rep)
{
	if (sgbIsWalking == rep)
		return;

	sgbIsWalking = rep;
	if (rep) {
		sgbTrackMode = FALSE;
		sgdwLastWalk = GetTickCount() - 50;
		NetSendCmdLoc(TRUE, CMD_WALKXY, cursmx, cursmy);
	} else if (sgbTrackMode) {
		sgbTrackMode = FALSE;
	}
}

BOOL track_isscrolling()
{
	return sgbTrackMode;
}
