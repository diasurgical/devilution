#include "diablo.h"

int doom_quest_time;
int doom_stars_drawn;
BYTE *pDoomCel;
#ifdef HELLFIRE
BOOLEAN doomflag;
#else
BOOL doomflag;
#endif
int DoomQuestState;

/*
void doom_reset_state()
{
    if (DoomQuestState <= 0) {
        DoomQuestState = 0;
    }
}

void doom_play_movie()
{
    if (DoomQuestState < 36001) {
        DoomQuestState++;
        if (DoomQuestState == 36001) {
            PlayInGameMovie("gendata\\doom.smk");
            DoomQuestState++;
        }
    }
}
*/

int doom_get_frame_from_time()
{
	if (DoomQuestState == 36001) {
		return 31;
	}

	return DoomQuestState / 1200;
}

#ifdef HELLFIRE
BOOLEAN doom_alloc_cel()
#else
void doom_alloc_cel()
#endif
{
#ifdef HELLFIRE
	doom_cleanup();
	pDoomCel = DiabloAllocPtr(0x39000);
	return pDoomCel ? TRUE : FALSE;
#else
	pDoomCel = DiabloAllocPtr(0x38000);
#endif
}

void doom_cleanup()
{
#ifdef HELLFIRE
	if (pDoomCel) {
		MemFreeDbg(pDoomCel);
		pDoomCel = NULL;
	}
#else
	MemFreeDbg(pDoomCel);
#endif
}

#ifdef HELLFIRE
BOOLEAN doom_load_graphics()
#else
void doom_load_graphics()
#endif
{
#ifdef HELLFIRE
	BOOLEAN ret;

	ret = FALSE;
	strcpy(tempstr, "Items\\Map\\MapZtown.CEL");
	if (LoadFileWithMem(tempstr, pDoomCel))
		ret = TRUE;
	return ret;
#else
	if (doom_quest_time == 31) {
		strcpy(tempstr, "Items\\Map\\MapZDoom.CEL");
	} else if (doom_quest_time < 10) {
		sprintf(tempstr, "Items\\Map\\MapZ000%i.CEL", doom_quest_time);
	} else {
		sprintf(tempstr, "Items\\Map\\MapZ00%i.CEL", doom_quest_time);
	}
	LoadFileWithMem(tempstr, pDoomCel);
#endif
}

void doom_init()
{
#ifdef HELLFIRE
	if (doom_alloc_cel()) {
		doom_quest_time = doom_get_frame_from_time() == 31 ? 31 : 0;
		if (doom_load_graphics()) {
			doomflag = TRUE;
		} else {
			doom_close();
		}
	}
#else
	doomflag = TRUE;
	doom_alloc_cel();
	doom_quest_time = doom_get_frame_from_time() == 31 ? 31 : 0;
	doom_load_graphics();
#endif
}

void doom_close()
{
#ifndef HELLFIRE
	if (doomflag) {
#endif
		doomflag = FALSE;
		doom_cleanup();
#ifndef HELLFIRE
	}
#endif
}

void doom_draw()
{
	if (!doomflag) {
		return;
	}
#ifndef HELLFIRE
	if (doom_quest_time != 31) {
		doom_stars_drawn++;
		if (doom_stars_drawn >= 5) {
			doom_stars_drawn = 0;
			doom_quest_time++;
			if (doom_quest_time > doom_get_frame_from_time()) {
				doom_quest_time = 0;
			}
			doom_load_graphics();
		}
	}
#endif
	CelDecodeOnly(SCREEN_X, PANEL_Y - 1, pDoomCel, 1, SCREEN_WIDTH);
}
