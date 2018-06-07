/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

#include "../types.h"

int doom_quest_time; // weak
int doom_stars_drawn; // weak
void *pDoomCel;
int doomflag; // weak
int DoomQuestState; // idb

//----- (0040ACAD) --------------------------------------------------------
int __cdecl doom_get_frame_from_time()
{
	int result; // eax

	if ( DoomQuestState == 36001 )
		result = 31;
	else
		result = DoomQuestState / 1200;
	return result;
}

//----- (0040ACC6) --------------------------------------------------------
void __cdecl doom_alloc_cel()
{
	pDoomCel = DiabloAllocPtr(229376);
}

//----- (0040ACD6) --------------------------------------------------------
void __cdecl doom_cleanup()
{
	void *v0; // ecx

	v0 = pDoomCel;
	pDoomCel = 0;
	mem_free_dbg(v0);
}

//----- (0040ACE8) --------------------------------------------------------
void __cdecl doom_load_graphics()
{
	if ( doom_quest_time == 31 )
	{
		strcpy(tempstr, "Items\\Map\\MapZDoom.CEL");
	}
	else if ( doom_quest_time >= 10 )
	{
		sprintf(tempstr, "Items\\Map\\MapZ00%i.CEL", doom_quest_time);
	}
	else
	{
		sprintf(tempstr, "Items\\Map\\MapZ000%i.CEL", doom_quest_time);
	}
	LoadFileWithMem(tempstr, pDoomCel);
}
// 525750: using guessed type int doom_quest_time;

//----- (0040AD34) --------------------------------------------------------
void __cdecl doom_init()
{
	int v0; // eax

	doomflag = 1;
	doom_alloc_cel();
	v0 = -(doom_get_frame_from_time() != 31);
	_LOBYTE(v0) = v0 & 0xE1;
	doom_quest_time = v0 + 31;
	doom_load_graphics();
}
// 525750: using guessed type int doom_quest_time;
// 52575C: using guessed type int doomflag;

//----- (0040AD5E) --------------------------------------------------------
void __cdecl doom_close()
{
	if ( doomflag )
	{
		doomflag = 0;
		doom_cleanup();
	}
}
// 52575C: using guessed type int doomflag;

//----- (0040AD74) --------------------------------------------------------
void __cdecl doom_draw()
{
	if ( doomflag )
	{
		if ( doom_quest_time != 31 && ++doom_stars_drawn >= 5 )
		{
			doom_stars_drawn = 0;
			if ( ++doom_quest_time > doom_get_frame_from_time() )
				doom_quest_time = 0;
			doom_load_graphics();
		}
		CelDecodeOnly(64, 511, pDoomCel, 1, 640);
	}
}
// 525750: using guessed type int doom_quest_time;
// 525754: using guessed type int doom_stars_drawn;
// 52575C: using guessed type int doomflag;
