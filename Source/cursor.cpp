/**
 * @file cursor.cpp
 *
 * Implementation of cursor tracking functionality.
 */
#include "all.h"

/** Pixel width of the current cursor image */
int cursW;
/** Pixel height of the current cursor image */
int cursH;
/** Current highlighted monster */
int pcursmonst;
/** Width of current cursor in inventory cells */
int icursW28;
/** Height of current cursor in inventory cells */
int icursH28;
/** Cursor images CEL */
BYTE *pCursCels;
#ifdef HELLFIRE
BYTE *pCursCels2;
#endif

/** inv_item value */
char pcursinvitem;
/** Pixel width of the current cursor image */
int icursW;
/** Pixel height of the current cursor image */
int icursH;
/** Current highlighted item */
char pcursitem;
/** Current highlighted object */
char pcursobj;
/** Current highlighted player */
char pcursplr;
/** Current highlighted tile row */
int cursmx;
/** Current highlighted tile column */
int cursmy;
/** Previously highlighted monster */
int pcurstemp;
/** Index of current cursor image */
int pcurs;

/* rdata */
/** Maps from objcurs.cel frame number to frame width. */
const int InvItemWidth[] = {
	// clang-format off
	// Cursors
	0, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 23,
	// Items
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
#ifdef HELLFIRE
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	2 * 28, 2 * 28, 1 * 28, 1 * 28, 1 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28
#endif
	// clang-format on
};

/** Maps from objcurs.cel frame number to frame height. */
const int InvItemHeight[] = {
	// clang-format off
	// Cursors
	0, 29, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35,
	// Items
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28, 2 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
#ifdef HELLFIRE
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28, 1 * 28,
	2 * 28, 2 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28,
	3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28, 3 * 28
#endif
	// clang-format on
};

void InitCursor()
{
	assert(!pCursCels);
	pCursCels = LoadFileInMem("Data\\Inv\\Objcurs.CEL", NULL);
#ifdef HELLFIRE
	pCursCels2 = LoadFileInMem("Data\\Inv\\Objcurs2.CEL", NULL);
#endif
	ClearCursor();
}

void FreeCursor()
{
	MemFreeDbg(pCursCels);
#ifdef HELLFIRE
	MemFreeDbg(pCursCels2);
#endif
	ClearCursor();
}

void SetICursor(int i)
{
	icursW = InvItemWidth[i];
	icursH = InvItemHeight[i];
	icursW28 = icursW / 28;
	icursH28 = icursH / 28;
}

void SetCursor_(int i)
{
	pcurs = i;
	cursW = InvItemWidth[i];
	cursH = InvItemHeight[i];
	SetICursor(i);
}

void NewCursor(int i)
{
	SetCursor_(i);
}

void InitLevelCursor()
{
	SetCursor_(CURSOR_HAND);
	cursmx = ViewX;
	cursmy = ViewY;
	pcurstemp = -1;
	pcursmonst = -1;
	pcursobj = -1;
	pcursitem = -1;
	pcursplr = -1;
	ClearCursor();
}

void CheckTown()
{
	int i, mx;

	for (i = 0; i < nummissiles; i++) {
		mx = missileactive[i];
		if (missile[mx]._mitype == MIS_TOWN) {
			if (cursmx == missile[mx]._mix - 1 && cursmy == missile[mx]._miy
			    || cursmx == missile[mx]._mix && cursmy == missile[mx]._miy - 1
			    || cursmx == missile[mx]._mix - 1 && cursmy == missile[mx]._miy - 1
			    || cursmx == missile[mx]._mix - 2 && cursmy == missile[mx]._miy - 1
			    || cursmx == missile[mx]._mix - 2 && cursmy == missile[mx]._miy - 2
			    || cursmx == missile[mx]._mix - 1 && cursmy == missile[mx]._miy - 2
			    || cursmx == missile[mx]._mix && cursmy == missile[mx]._miy) {
				trigflag = TRUE;
				ClearPanel();
				strcpy(infostr, "Town Portal");
				sprintf(tempstr, "from %s", plr[missile[mx]._misource]._pName);
				AddPanelString(tempstr, TRUE);
				cursmx = missile[mx]._mix;
				cursmy = missile[mx]._miy;
			}
		}
	}
}

void CheckRportal()
{
	int i, mx;

	for (i = 0; i < nummissiles; i++) {
		mx = missileactive[i];
		if (missile[mx]._mitype == MIS_RPORTAL) {
			if (cursmx == missile[mx]._mix - 1 && cursmy == missile[mx]._miy
			    || cursmx == missile[mx]._mix && cursmy == missile[mx]._miy - 1
			    || cursmx == missile[mx]._mix - 1 && cursmy == missile[mx]._miy - 1
			    || cursmx == missile[mx]._mix - 2 && cursmy == missile[mx]._miy - 1
			    || cursmx == missile[mx]._mix - 2 && cursmy == missile[mx]._miy - 2
			    || cursmx == missile[mx]._mix - 1 && cursmy == missile[mx]._miy - 2
			    || cursmx == missile[mx]._mix && cursmy == missile[mx]._miy) {
				trigflag = TRUE;
				ClearPanel();
				strcpy(infostr, "Portal to");
				if (!setlevel)
					strcpy(tempstr, "The Unholy Altar");
				else
					strcpy(tempstr, "level 15");
				AddPanelString(tempstr, TRUE);
				cursmx = missile[mx]._mix;
				cursmy = missile[mx]._miy;
			}
		}
	}
}

void CheckCursMove()
{
	int i, sx, sy, fx, fy, mx, my, tx, ty, px, py, xx, yy, mi;
	char bv;
	BOOL flipflag, flipx, flipy;

	sx = MouseX;
	sy = MouseY;

	if (chrflag || questlog) {
		if (sx >= SCREEN_WIDTH / 4) { /// BUGFIX: (sx >= SCREEN_WIDTH / 2)

			sx -= SCREEN_WIDTH / 4;
		} else {
			sx = 0;
		}
	} else if (invflag || sbookflag) {
		if (sx <= SCREEN_WIDTH / 2) {
			sx += SCREEN_WIDTH / 4;
		} else {
			sx = 0;
		}
	}
	if (sy > PANEL_TOP - 1 && track_isscrolling()) {
		sy = PANEL_TOP - 1;
	}
	if (!zoomflag) {
		sx >>= 1;
		sy >>= 1;
	}

	// Adjust by player offset
	sx -= ScrollInfo._sxoff;
	sy -= ScrollInfo._syoff;

	// Predict the next frame when walking to avoid input jitter
	fx = plr[myplr]._pVar6 >> 8;
	fy = plr[myplr]._pVar7 >> 8;
	fx -= (plr[myplr]._pVar6 + plr[myplr]._pxvel) >> 8;
	fy -= (plr[myplr]._pVar7 + plr[myplr]._pyvel) >> 8;
	if (ScrollInfo._sdir != SDIR_NONE) {
		sx -= fx;
		sy -= fy;
	}

	if (sx < 0) {
		sx = 0;
	}
	if (sx >= SCREEN_WIDTH) {
		sx = SCREEN_WIDTH;
	}
	if (sy < 0) {
		sy = 0;
	}
	if (sy >= SCREEN_HEIGHT) {
		sy = SCREEN_HEIGHT;
	}

	// Convert to tile grid

	tx = sx >> 6; // sx / TILE_WIDTH
	ty = sy >> 5; // sy / TILE_HEIGHT
	px = sx & (TILE_WIDTH - 1);
	py = sy & (TILE_HEIGHT - 1);

	// Center player tile on screen
	mx = ViewX + tx + ty - (zoomflag ? (SCREEN_WIDTH / TILE_WIDTH) : (SCREEN_WIDTH / 2 / TILE_WIDTH));
	my = ViewY + ty - tx;

	// Shift position to match diamond grid aligment
	flipy = py < (px >> 1);
	if (flipy) {
		my--;
	}
	flipx = py >= TILE_HEIGHT - (px >> 1);
	if (flipx) {
		mx++;
	}

	if (mx < 0) {
		mx = 0;
	}
	if (mx >= MAXDUNX) {
		mx = MAXDUNX - 1;
	}
	if (my < 0) {
		my = 0;
	}
	if (my >= MAXDUNY) {
		my = MAXDUNY - 1;
	}

	flipflag = flipy && flipx || (flipy || flipx) && px < TILE_WIDTH / 2;

	pcurstemp = pcursmonst;
	pcursmonst = -1;
	pcursobj = -1;
	pcursitem = -1;
	if (pcursinvitem != -1) {
		drawsbarflag = TRUE;
	}
	pcursinvitem = -1;
	pcursplr = -1;
	uitemflag = FALSE;
	panelflag = FALSE;
	trigflag = FALSE;

	if (plr[myplr]._pInvincible) {
		return;
	}
	if (pcurs >= CURSOR_FIRSTITEM || spselflag) {
		cursmx = mx;
		cursmy = my;
		return;
	}
	if (MouseY > PANEL_TOP) {
		CheckPanelInfo();
		return;
	}
	if (doomflag) {
		return;
	}
	if (invflag && MouseX > RIGHT_PANEL) {
		pcursinvitem = CheckInvHLight();
		return;
	}
	if (sbookflag && MouseX > RIGHT_PANEL) {
		return;
	}
	if ((chrflag || questlog) && MouseX < SPANEL_WIDTH) {
		return;
	}

	if (leveltype != DTYPE_TOWN) {
		if (pcurstemp != -1) {
			if (!flipflag && dMonster[mx + 2][my + 1] != 0 && dFlags[mx + 2][my + 1] & BFLAG_LIT) {
				mi = dMonster[mx + 2][my + 1] > 0 ? dMonster[mx + 2][my + 1] - 1 : -(dMonster[mx + 2][my + 1] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 4) {
					cursmx = mx + 1; /// BUGFIX: 'mx + 2'
					cursmy = my + 2; /// BUGFIX: 'my + 1'
					pcursmonst = mi;
				}
			}
			if (flipflag && dMonster[mx + 1][my + 2] != 0 && dFlags[mx + 1][my + 2] & BFLAG_LIT) {
				mi = dMonster[mx + 1][my + 2] > 0 ? dMonster[mx + 1][my + 2] - 1 : -(dMonster[mx + 1][my + 2] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 4) {
					cursmx = mx + 1;
					cursmy = my + 2;
					pcursmonst = mi;
				}
			}
			if (dMonster[mx + 2][my + 2] != 0 && dFlags[mx + 2][my + 2] & BFLAG_LIT) {
				mi = dMonster[mx + 2][my + 2] > 0 ? dMonster[mx + 2][my + 2] - 1 : -(dMonster[mx + 2][my + 2] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 4) {
					cursmx = mx + 2;
					cursmy = my + 2;
					pcursmonst = mi;
				}
			}
			if (!flipflag && dMonster[mx + 1][my] != 0 && dFlags[mx + 1][my] & BFLAG_LIT) {
				mi = dMonster[mx + 1][my] > 0 ? dMonster[mx + 1][my] - 1 : -(dMonster[mx + 1][my] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 2) {
					cursmx = mx + 1;
					cursmy = my;
					pcursmonst = mi;
				}
			}
			if (flipflag && dMonster[mx][my + 1] != 0 && dFlags[mx][my + 1] & BFLAG_LIT) {
				mi = dMonster[mx][my + 1] > 0 ? dMonster[mx][my + 1] - 1 : -(dMonster[mx][my + 1] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 2) {
					cursmx = mx;
					cursmy = my + 1;
					pcursmonst = mi;
				}
			}
			if (dMonster[mx][my] != 0 && dFlags[mx][my] & BFLAG_LIT) {
				mi = dMonster[mx][my] > 0 ? dMonster[mx][my] - 1 : -(dMonster[mx][my] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 1) {
					cursmx = mx;
					cursmy = my;
					pcursmonst = mi;
				}
			}
			if (dMonster[mx + 1][my + 1] != 0 && dFlags[mx + 1][my + 1] & BFLAG_LIT) {
				mi = dMonster[mx + 1][my + 1] > 0 ? dMonster[mx + 1][my + 1] - 1 : -(dMonster[mx + 1][my + 1] + 1);
				if (mi == pcurstemp && monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 2) {
					cursmx = mx + 1;
					cursmy = my + 1;
					pcursmonst = mi;
				}
			}
			if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_HIDDEN) {
				pcursmonst = -1;
				cursmx = mx;
				cursmy = my;
			}
#ifdef HELLFIRE
			if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_GOLEM && !(monster[pcursmonst]._mFlags & MFLAG_BERSERK)) {
				pcursmonst = -1;
			}
#else
			if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_GOLEM) {
				pcursmonst = -1;
			}
#endif
			if (pcursmonst != -1) {
				return;
			}
		}
		if (!flipflag && dMonster[mx + 2][my + 1] != 0 && dFlags[mx + 2][my + 1] & BFLAG_LIT) {
			mi = dMonster[mx + 2][my + 1] > 0 ? dMonster[mx + 2][my + 1] - 1 : -(dMonster[mx + 2][my + 1] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 4) {
				cursmx = mx + 2;
				cursmy = my + 1;
				pcursmonst = mi;
			}
		}
		if (flipflag && dMonster[mx + 1][my + 2] != 0 && dFlags[mx + 1][my + 2] & BFLAG_LIT) {
			mi = dMonster[mx + 1][my + 2] > 0 ? dMonster[mx + 1][my + 2] - 1 : -(dMonster[mx + 1][my + 2] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 4) {
				cursmx = mx + 1;
				cursmy = my + 2;
				pcursmonst = mi;
			}
		}
		if (dMonster[mx + 2][my + 2] != 0 && dFlags[mx + 2][my + 2] & BFLAG_LIT) {
			mi = dMonster[mx + 2][my + 2] > 0 ? dMonster[mx + 2][my + 2] - 1 : -(dMonster[mx + 2][my + 2] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 4) {
				cursmx = mx + 2;
				cursmy = my + 2;
				pcursmonst = mi;
			}
		}
		if (!flipflag && dMonster[mx + 1][my] != 0 && dFlags[mx + 1][my] & BFLAG_LIT) {
			mi = dMonster[mx + 1][my] > 0 ? dMonster[mx + 1][my] - 1 : -(dMonster[mx + 1][my] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 2) {
				cursmx = mx + 1;
				cursmy = my;
				pcursmonst = mi;
			}
		}
		if (flipflag && dMonster[mx][my + 1] != 0 && dFlags[mx][my + 1] & BFLAG_LIT) {
			mi = dMonster[mx][my + 1] > 0 ? dMonster[mx][my + 1] - 1 : -(dMonster[mx][my + 1] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 2) {
				cursmx = mx;
				cursmy = my + 1;
				pcursmonst = mi;
			}
		}
		if (dMonster[mx][my] != 0 && dFlags[mx][my] & BFLAG_LIT) {
			mi = dMonster[mx][my] > 0 ? dMonster[mx][my] - 1 : -(dMonster[mx][my] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 1) {
				cursmx = mx;
				cursmy = my;
				pcursmonst = mi;
			}
		}
		if (dMonster[mx + 1][my + 1] != 0 && dFlags[mx + 1][my + 1] & BFLAG_LIT) {
			mi = dMonster[mx + 1][my + 1] > 0 ? dMonster[mx + 1][my + 1] - 1 : -(dMonster[mx + 1][my + 1] + 1);
			if (monster[mi]._mhitpoints >> 6 > 0 && monster[mi].MData->mSelFlag & 2) {
				cursmx = mx + 1;
				cursmy = my + 1;
				pcursmonst = mi;
			}
		}
		if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_HIDDEN) {
			pcursmonst = -1;
			cursmx = mx;
			cursmy = my;
		}
#ifdef HELLFIRE
		if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_GOLEM && !(monster[pcursmonst]._mFlags & MFLAG_BERSERK)) {
			pcursmonst = -1;
		}
#else
		if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_GOLEM) {
			pcursmonst = -1;
		}
#endif
	} else {
		if (!flipflag && dMonster[mx + 1][my] > 0) {
			pcursmonst = dMonster[mx + 1][my] - 1;
			cursmx = mx + 1;
			cursmy = my;
		}
		if (flipflag && dMonster[mx][my + 1] > 0) {
			pcursmonst = dMonster[mx][my + 1] - 1;
			cursmx = mx;
			cursmy = my + 1;
		}
		if (dMonster[mx][my] > 0) {
			pcursmonst = dMonster[mx][my] - 1;
			cursmx = mx;
			cursmy = my;
		}
		if (dMonster[mx + 1][my + 1] > 0) {
			pcursmonst = dMonster[mx + 1][my + 1] - 1;
			cursmx = mx + 1;
			cursmy = my + 1;
		}
		if (!towner[pcursmonst]._tSelFlag) { /// BUGFIX: Add check 'pcursmonst != -1'
			pcursmonst = -1;
		}
	}

	if (pcursmonst == -1) {
		if (!flipflag && dPlayer[mx + 1][my] != 0) {
			bv = dPlayer[mx + 1][my] > 0 ? dPlayer[mx + 1][my] - 1 : -(dPlayer[mx + 1][my] + 1);
			if (bv != myplr && plr[bv]._pHitPoints != 0) {
				cursmx = mx + 1;
				cursmy = my;
				pcursplr = bv;
			}
		}
		if (flipflag && dPlayer[mx][my + 1] != 0) {
			bv = dPlayer[mx][my + 1] > 0 ? dPlayer[mx][my + 1] - 1 : -(dPlayer[mx][my + 1] + 1);
			if (bv != myplr && plr[bv]._pHitPoints != 0) {
				cursmx = mx;
				cursmy = my + 1;
				pcursplr = bv;
			}
		}
		if (dPlayer[mx][my] != 0) {
			bv = dPlayer[mx][my] > 0 ? dPlayer[mx][my] - 1 : -(dPlayer[mx][my] + 1);
			if (bv != myplr) {
				cursmx = mx;
				cursmy = my;
				pcursplr = bv;
			}
		}
		if (dFlags[mx][my] & BFLAG_DEAD_PLAYER) {
			for (i = 0; i < MAX_PLRS; i++) {
				if (plr[i]._px == mx && plr[i]._py == my && i != myplr) {
					cursmx = mx;
					cursmy = my;
					pcursplr = i;
				}
			}
		}
		if (pcurs == CURSOR_RESURRECT) {
			for (xx = -1; xx < 2; xx++) {
				for (yy = -1; yy < 2; yy++) {
					if (dFlags[mx + xx][my + yy] & BFLAG_DEAD_PLAYER) {
						for (i = 0; i < MAX_PLRS; i++) {
							if (plr[i]._px == mx + xx && plr[i]._py == my + yy && i != myplr) {
								cursmx = mx + xx;
								cursmy = my + yy;
								pcursplr = i;
							}
						}
					}
				}
			}
		}
		if (dPlayer[mx + 1][my + 1] != 0) {
			bv = dPlayer[mx + 1][my + 1] > 0 ? dPlayer[mx + 1][my + 1] - 1 : -(dPlayer[mx + 1][my + 1] + 1);
			if (bv != myplr && plr[bv]._pHitPoints != 0) {
				cursmx = mx + 1;
				cursmy = my + 1;
				pcursplr = bv;
			}
		}
	}
	if (pcursmonst == -1 && pcursplr == -1) {
		if (!flipflag && dObject[mx + 1][my] != 0) {
			bv = dObject[mx + 1][my] > 0 ? dObject[mx + 1][my] - 1 : -(dObject[mx + 1][my] + 1);
			if (object[bv]._oSelFlag >= 2) {
				cursmx = mx + 1;
				cursmy = my;
				pcursobj = bv;
			}
		}
		if (flipflag && dObject[mx][my + 1] != 0) {
			bv = dObject[mx][my + 1] > 0 ? dObject[mx][my + 1] - 1 : -(dObject[mx][my + 1] + 1);
			if (object[bv]._oSelFlag >= 2) {
				cursmx = mx;
				cursmy = my + 1;
				pcursobj = bv;
			}
		}
		if (dObject[mx][my] != 0) {
			bv = dObject[mx][my] > 0 ? dObject[mx][my] - 1 : -(dObject[mx][my] + 1);
			if (object[bv]._oSelFlag == 1 || object[bv]._oSelFlag == 3) {
				cursmx = mx;
				cursmy = my;
				pcursobj = bv;
			}
		}
		if (dObject[mx + 1][my + 1] != 0) {
			bv = dObject[mx + 1][my + 1] > 0 ? dObject[mx + 1][my + 1] - 1 : -(dObject[mx + 1][my + 1] + 1);
			if (object[bv]._oSelFlag >= 2) {
				cursmx = mx + 1;
				cursmy = my + 1;
				pcursobj = bv;
			}
		}
	}
	if (pcursplr == -1 && pcursobj == -1 && pcursmonst == -1) {
		if (!flipflag && dItem[mx + 1][my] > 0) {
			bv = dItem[mx + 1][my] - 1;
			if (item[bv]._iSelFlag >= 2) {
				cursmx = mx + 1;
				cursmy = my;
				pcursitem = bv;
			}
		}
		if (flipflag && dItem[mx][my + 1] > 0) {
			bv = dItem[mx][my + 1] - 1;
			if (item[bv]._iSelFlag >= 2) {
				cursmx = mx;
				cursmy = my + 1;
				pcursitem = bv;
			}
		}
		if (dItem[mx][my] > 0) {
			bv = dItem[mx][my] - 1;
			if (item[bv]._iSelFlag == 1 || item[bv]._iSelFlag == 3) {
				cursmx = mx;
				cursmy = my;
				pcursitem = bv;
			}
		}
		if (dItem[mx + 1][my + 1] > 0) {
			bv = dItem[mx + 1][my + 1] - 1;
			if (item[bv]._iSelFlag >= 2) {
				cursmx = mx + 1;
				cursmy = my + 1;
				pcursitem = bv;
			}
		}
		if (pcursitem == -1) {
			cursmx = mx;
			cursmy = my;
			CheckTrigForce();
			CheckTown();
			CheckRportal();
		}
	}

	if (pcurs == CURSOR_IDENTIFY) {
		pcursobj = -1;
		pcursmonst = -1;
		pcursitem = -1;
		cursmx = mx;
		cursmy = my;
	}
#ifdef HELLFIRE
	if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_GOLEM && !(monster[pcursmonst]._mFlags & MFLAG_BERSERK)) {
		pcursmonst = -1;
	}
#else
	if (pcursmonst != -1 && monster[pcursmonst]._mFlags & MFLAG_GOLEM) {
		pcursmonst = -1;
	}
#endif
}
