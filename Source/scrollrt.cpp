#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

/**
 * Specifies the current light entry.
 */
int light_table_index;
int PitchTbl[1024];
DWORD sgdwCursWdtOld;
DWORD sgdwCursX;
DWORD sgdwCursY;
/**
 * Lower bound of back buffer.
 */
BYTE *gpBufEnd;
DWORD sgdwCursHgt;

/**
 * Specifies the current MIN block of the level CEL file, as used during rendering of the level tiles.
 *
 * frameNum  := block & 0x0FFF
 * frameType := block & 0x7000 >> 12
 */
DWORD level_cel_block;
DWORD sgdwCursXOld;
DWORD sgdwCursYOld;
/**
 * Specifies the type of arches to render.
 */
char arch_draw_type;
/**
 * Describes the surface being rendered.
 */
DDSURFACEDESC DDS_desc;
/**
 * Specifies whether transparency is active for the current CEL file being decoded.
 */
int cel_transparency_active;
/**
 * Specifies the current dungeon piece ID of the level, as used during rendering of the level tiles.
 */
int level_piece_id;
DWORD sgdwCursWdt;
void (*DrawPlrProc)(int, int, int, int, int, BYTE *, int, int, int, int);
BYTE sgSaveBack[8192];
/**
 * Specifies the monster_num to render.
 */
int draw_monster_num;
DWORD sgdwCursHgtOld;

/* data */

/* used in 1.00 debug */
char *szMonModeAssert[18] = {
	"standing",
	"walking (1)",
	"walking (2)",
	"walking (3)",
	"attacking",
	"getting hit",
	"dying",
	"attacking (special)",
	"fading in",
	"fading out",
	"attacking (ranged)",
	"standing (special)",
	"attacking (special ranged)",
	"delaying",
	"charging",
	"stoned",
	"healing",
	"talking"
};

char *szPlrModeAssert[12] = {
	"standing",
	"walking (1)",
	"walking (2)",
	"walking (3)",
	"attacking (melee)",
	"attacking (ranged)",
	"blocking",
	"getting hit",
	"dying",
	"casting a spell",
	"changing levels",
	"quitting"
};

/**
 * @brief Clear cursor state
 */
void ClearCursor() // CODE_FIX: this was supposed to be in cursor.cpp
{
	sgdwCursWdt = 0;
	sgdwCursWdtOld = 0;
}

/**
 * @brief Remove the cursor from the back buffer
 */
static void scrollrt_draw_cursor_back_buffer()
{
	int i;
	BYTE *src, *dst;

	if (sgdwCursWdt == 0) {
		return;
	}

	/// ASSERT: assert(gpBuffer);
	src = sgSaveBack;
	dst = &gpBuffer[SCREENXY(sgdwCursX, sgdwCursY)];
	i = sgdwCursHgt;

	if (sgdwCursHgt != 0) {
		while (i--) {
			memcpy(dst, src, sgdwCursWdt);
			src += sgdwCursWdt;
			dst += BUFFER_WIDTH;
		}
	}

	sgdwCursXOld = sgdwCursX;
	sgdwCursYOld = sgdwCursY;
	sgdwCursWdtOld = sgdwCursWdt;
	sgdwCursHgtOld = sgdwCursHgt;
	sgdwCursWdt = 0;
}

/**
 * @brief Draw the cursor on the back buffer
 */
static void scrollrt_draw_cursor_item()
{
	int i, mx, my, col;
	BYTE *src, *dst;

	/// ASSERT: assert(! sgdwCursWdt);

	if (pcurs <= CURSOR_NONE || cursW == 0 || cursH == 0) {
		return;
	}

	mx = MouseX - 1;
	if (mx < 0) {
		mx = 0;
	} else if (mx > SCREEN_WIDTH - 1) {
		return;
	}
	my = MouseY - 1;
	if (my < 0) {
		my = 0;
	} else if (my > SCREEN_HEIGHT - 1) {
		return;
	}

	sgdwCursX = mx;
	sgdwCursWdt = sgdwCursX + cursW + 1;
	if (sgdwCursWdt > SCREEN_WIDTH - 1) {
		sgdwCursWdt = SCREEN_WIDTH - 1;
	}
	sgdwCursX &= ~3;
	sgdwCursWdt |= 3;
	sgdwCursWdt -= sgdwCursX;
	sgdwCursWdt++;

	sgdwCursY = my;
	sgdwCursHgt = sgdwCursY + cursH + 1;
	if (sgdwCursHgt > SCREEN_HEIGHT - 1) {
		sgdwCursHgt = SCREEN_HEIGHT - 1;
	}
	sgdwCursHgt -= sgdwCursY;
	sgdwCursHgt++;

	/// ASSERT: assert(sgdwCursWdt * sgdwCursHgt < sizeof sgSaveBack);
	/// ASSERT: assert(gpBuffer);
	dst = sgSaveBack;
	src = &gpBuffer[SCREENXY(sgdwCursX, sgdwCursY)];

	for (i = sgdwCursHgt; i != 0; i--, dst += sgdwCursWdt, src += BUFFER_WIDTH) {
		memcpy(dst, src, sgdwCursWdt);
	}

	mx++;
	my++;
	gpBufEnd = &gpBuffer[PitchTbl[SCREEN_HEIGHT + SCREEN_Y] - cursW - 2];

	if (pcurs >= CURSOR_FIRSTITEM) {
		col = PAL16_YELLOW + 5;
		if (plr[myplr].HoldItem._iMagical != 0) {
			col = PAL16_BLUE + 5;
		}
		if (!plr[myplr].HoldItem._iStatFlag) {
			col = PAL16_RED + 5;
		}
		CelBlitOutlineSafe(col, mx + SCREEN_X, my + cursH + SCREEN_Y - 1, pCursCels, pcurs, cursW, 0, 8);
		if (col != PAL16_RED + 5) {
			CelClippedDrawSafe(mx + SCREEN_X, my + cursH + SCREEN_Y - 1, pCursCels, pcurs, cursW, 0, 8);
		} else {
			CelDrawLightRedSafe(mx + SCREEN_X, my + cursH + SCREEN_Y - 1, pCursCels, pcurs, cursW, 0, 8, 1);
		}
	} else {
		CelClippedDrawSafe(mx + SCREEN_X, my + cursH + SCREEN_Y - 1, pCursCels, pcurs, cursW, 0, 8);
	}
}

/**
 * @brief Render a missile sprites for a given tile
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 * @param pre Is the sprite in the background
 */
void DrawMissile(int x, int y, int sx, int sy, int CelSkip, int CelCap, BOOL pre)
{
	int i, mx, my, nCel;
	MissileStruct *m;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if (dMissile[x][y] == -1) {
		for (i = 0; i < nummissiles; i++) {
			/// ASSERT: assert(missileactive[i] < MAXMISSILES);
			if (missileactive[i] >= MAXMISSILES)
				break;
			m = &missile[missileactive[i]];
			if (m->_mix == x && m->_miy == y && m->_miPreFlag == pre && m->_miDrawFlag) {
				pCelBuff = m->_miAnimData;
				if (!pCelBuff) {
					// app_fatal("Draw Missile type %d: NULL Cel Buffer", m->_mitype);
					return;
				}
				nCel = m->_miAnimFrame;
				pFrameTable = (DWORD *)pCelBuff;
				if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
					// app_fatal("Draw Missile: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
					return;
				}
				mx = sx + m->_mixoff - m->_miAnimWidth2;
				my = sy + m->_miyoff;
				if (m->_miUniqTrans)
					Cl2DrawLightTbl(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap, m->_miUniqTrans + 3);
				else if (m->_miLightFlag)
					Cl2DrawLight(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
				else
					Cl2Draw(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
			}
		}
	} else {
		m = &missile[dMissile[x][y] - 1];
		if (m->_miPreFlag == pre && m->_miDrawFlag) {
			pCelBuff = m->_miAnimData;
			if (!pCelBuff) {
				// app_fatal("Draw Missile 2 type %d: NULL Cel Buffer", m->_mitype);
				return;
			}
			nCel = m->_miAnimFrame;
			pFrameTable = (DWORD *)pCelBuff;
			if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
				// app_fatal("Draw Missile 2: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
				return;
			}
			mx = sx + m->_mixoff - m->_miAnimWidth2;
			my = sy + m->_miyoff;
			if (m->_miUniqTrans)
				Cl2DrawLightTbl(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap, m->_miUniqTrans + 3);
			else if (m->_miLightFlag)
				Cl2DrawLight(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
			else
				Cl2Draw(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
		}
	}
}

/**
 * @brief Render a missile sprite, check for overdraw on lower screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 * @param pre Is the sprite in the background
 */
void DrawClippedMissile(int x, int y, int sx, int sy, int CelSkip, int CelCap, BOOL pre)
{
	int i, mx, my, nCel;
	MissileStruct *m;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if (dMissile[x][y] == -1) {
		for (i = 0; i < nummissiles; i++) {
			/// ASSERT: assert(missileactive[i] < MAXMISSILES);
			if (missileactive[i] >= MAXMISSILES)
				break;
			m = &missile[missileactive[i]];
			if (m->_mix == x && m->_miy == y && m->_miPreFlag == pre && m->_miDrawFlag) {
				pCelBuff = m->_miAnimData;
				if (!pCelBuff) {
					// app_fatal("Draw Missile type %d Clipped: NULL Cel Buffer", m->_mitype);
					return;
				}
				nCel = m->_miAnimFrame;
				pFrameTable = (DWORD *)pCelBuff;
				if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
					// app_fatal("Draw Clipped Missile: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
					return;
				}
				mx = sx + m->_mixoff - m->_miAnimWidth2;
				my = sy + m->_miyoff;
				if (m->_miUniqTrans)
					Cl2DrawLightTblSafe(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap, m->_miUniqTrans + 3);
				else if (m->_miLightFlag)
					Cl2DrawLightSafe(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
				else
					Cl2DrawSafe(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
			}
		}
	} else {
		m = &missile[dMissile[x][y] - 1];
		if (m->_miPreFlag == pre && m->_miDrawFlag) {
			pCelBuff = m->_miAnimData;
			if (!pCelBuff) {
				// app_fatal("Draw Missile 2 type %d Clipped: NULL Cel Buffer", m->_mitype);
				return;
			}
			nCel = m->_miAnimFrame;
			pFrameTable = (DWORD *)pCelBuff;
			if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
				// app_fatal("Draw Clipped Missile 2: frame %d of %d, missile type==%d", nCel, pFrameTable[0], m->_mitype);
				return;
			}
			mx = sx + m->_mixoff - m->_miAnimWidth2;
			my = sy + m->_miyoff;
			if (m->_miUniqTrans)
				Cl2DrawLightTblSafe(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap, m->_miUniqTrans + 3);
			else if (m->_miLightFlag)
				Cl2DrawLightSafe(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
			else
				Cl2DrawSafe(mx, my, m->_miAnimData, m->_miAnimFrame, m->_miAnimWidth, CelSkip, CelCap);
		}
	}
}

/**
 * @brief Render a monster sprite
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param mx Back buffer coordinate
 * @param my Back buffer coordinate
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 */
static void DrawMonster(int x, int y, int mx, int my, int m, int CelSkip, int CelCap)
{
	int nCel;
	char trans;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if ((DWORD)m >= MAXMONSTERS) {
		// app_fatal("Draw Monster: tried to draw illegal monster %d", m);
		return;
	}

	pCelBuff = monster[m]._mAnimData;
	if (!pCelBuff) {
		// app_fatal("Draw Monster \"%s\": NULL Cel Buffer", monster[m].mName);
		return;
	}

	nCel = monster[m]._mAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		/*
		const char *szMode = "unknown action";
		if(monster[m]._mmode <= 17)
			szMode = szMonModeAssert[monster[m]._mmode];
		app_fatal(
			"Draw Monster \"%s\" %s: facing %d, frame %d of %d",
			monster[m].mName,
			szMode,
			monster[m]._mdir,
			nCel,
			pFrameTable[0]);
		*/
		return;
	}

	if (!(dFlags[x][y] & BFLAG_LIT)) {
		Cl2DrawLightTbl(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->width, CelSkip, CelCap, 1);
	} else {
		trans = 0;
		if (monster[m]._uniqtype)
			trans = monster[m]._uniqtrans + 4;
		if (monster[m]._mmode == MM_STONE)
			trans = 2;
		if (plr[myplr]._pInfraFlag && light_table_index > 8)
			trans = 1;
		if (trans)
			Cl2DrawLightTbl(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->width, CelSkip, CelCap, trans);
		else
			Cl2DrawLight(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->width, CelSkip, CelCap);
	}
}

/**
 * @brief Render a monster sprite, check for overdraw on lower screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param mx Back buffer coordinate
 * @param my Back buffer coordinate
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 */
static void DrawClippedMonster(int x, int y, int mx, int my, int m, int CelSkip, int CelCap)
{
	int nCel;
	char trans;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if ((DWORD)m >= MAXMONSTERS) {
		// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", m);
		return;
	}

	pCelBuff = monster[m]._mAnimData;
	if (!pCelBuff) {
		// app_fatal("Draw Monster \"%s\" Clipped: NULL Cel Buffer", monster[m].mName);
		return;
	}

	nCel = monster[m]._mAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		/*
		const char *szMode = "unknown action";
		if(monster[m]._mmode <= 17)
			szMode = szMonModeAssert[monster[m]._mmode];
		app_fatal(
			"Draw Monster \"%s\" %s Clipped: facing %d, frame %d of %d",
			monster[m].mName,
			szMode,
			monster[m]._mdir,
			nCel,
			pFrameTable[0]);
		*/
		return;
	}

	if (!(dFlags[x][y] & BFLAG_LIT)) {
		Cl2DrawLightTblSafe(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->width, CelSkip, CelCap, 1);
	} else {
		trans = 0;
		if (monster[m]._uniqtype)
			trans = monster[m]._uniqtrans + 4;
		if (monster[m]._mmode == MM_STONE)
			trans = 2;
		if (plr[myplr]._pInfraFlag && light_table_index > 8)
			trans = 1;
		if (trans)
			Cl2DrawLightTblSafe(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->width, CelSkip, CelCap, trans);
		else
			Cl2DrawLightSafe(mx, my, monster[m]._mAnimData, monster[m]._mAnimFrame, monster[m].MType->width, CelSkip, CelCap);
	}
}

/**
 * @brief Render a player sprite
 * @param pnum Player id
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param px Back buffer coordinate
 * @param py Back buffer coordinate
 * @param pCelBuff sprite buffer
 * @param nCel frame
 * @param nWidth width
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 */
static void DrawPlayer(int pnum, int x, int y, int px, int py, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int l;
	DWORD *pFrameTable;

	if (dFlags[x][y] & BFLAG_LIT || plr[myplr]._pInfraFlag || !setlevel && !currlevel) {
		if (!pCelBuff) {
			// app_fatal("Drawing player %d \"%s\": NULL Cel Buffer", pnum, plr[pnum]._pName);
			return;
		}
		pFrameTable = (DWORD *)pCelBuff;
		if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
			/*
			const char *szMode = "unknown action";
			if(plr[pnum]._pmode <= PM_QUIT)
				szMode = szPlrModeAssert[plr[pnum]._pmode];
			app_fatal(
				"Drawing player %d \"%s\" %s: facing %d, frame %d of %d",
				pnum,
				plr[pnum]._pName,
				szMode,
				plr[pnum]._pdir,
				nCel,
				pFrameTable[0]);
			*/
			return;
		}
		if (pnum == pcursplr)
			Cl2DrawOutline(165, px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap);
		if (pnum == myplr) {
			Cl2Draw(px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap);
			if (plr[pnum].pManaShield)
				Cl2Draw(
				    px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
				    py,
				    misfiledata[MFILE_MANASHLD].mAnimData[0],
				    1,
				    misfiledata[MFILE_MANASHLD].mAnimWidth[0],
				    CelSkip,
				    CelCap);
		} else if (!(dFlags[x][y] & BFLAG_LIT) || plr[myplr]._pInfraFlag && light_table_index > 8) {
			Cl2DrawLightTbl(px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap, 1);
			if (plr[pnum].pManaShield)
				Cl2DrawLightTbl(
				    px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
				    py,
				    misfiledata[MFILE_MANASHLD].mAnimData[0],
				    1,
				    misfiledata[MFILE_MANASHLD].mAnimWidth[0],
				    CelSkip,
				    CelCap,
				    1);
		} else {
			l = light_table_index;
			if (light_table_index < 5)
				light_table_index = 0;
			else
				light_table_index -= 5;
			Cl2DrawLight(px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap);
			if (plr[pnum].pManaShield)
				Cl2DrawLight(
				    px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
				    py,
				    misfiledata[MFILE_MANASHLD].mAnimData[0],
				    1,
				    misfiledata[MFILE_MANASHLD].mAnimWidth[0],
				    CelSkip,
				    CelCap);
			light_table_index = l;
		}
	}
}

/**
 * @brief Render a monster sprite, check for overdraw on lower screen
 * @param pnum Player id
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param px Back buffer coordinate
 * @param py Back buffer coordinate
 * @param pCelBuff sprite buffer
 * @param nCel frame
 * @param nWidth width
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 */
static void DrawClippedPlayer(int pnum, int x, int y, int px, int py, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int l;
	DWORD *pFrameTable;

	if (dFlags[x][y] & BFLAG_LIT || plr[myplr]._pInfraFlag) {
		if (!pCelBuff) {
			// app_fatal("Drawing player %d \"%s\" clipped: NULL Cel Buffer", pnum, plr[pnum]._pName);
			return;
		}
		pFrameTable = (DWORD *)pCelBuff;
		if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
			/*
			const char *szMode = "unknown action";
			if(plr[pnum]._pmode <= PM_QUIT)
				szMode = szPlrModeAssert[plr[pnum]._pmode];
			app_fatal(
				"Drawing player %d \"%s\" %s clipped: facing %d, frame %d of %d",
				pnum,
				plr[pnum]._pName,
				szMode,
				plr[pnum]._pdir,
				nCel,
				pFrameTable[0]);
			*/
			return;
		}
		if (pnum == pcursplr)
			Cl2DrawOutlineSafe(165, px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap);
		if (pnum == myplr) {
			Cl2DrawSafe(px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap);
			if (plr[pnum].pManaShield)
				Cl2DrawSafe(
				    px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
				    py,
				    misfiledata[MFILE_MANASHLD].mAnimData[0],
				    1,
				    misfiledata[MFILE_MANASHLD].mAnimWidth[0],
				    CelSkip,
				    CelCap);
		} else if (!(dFlags[x][y] & BFLAG_LIT) || plr[myplr]._pInfraFlag && light_table_index > 8) {
			Cl2DrawLightTblSafe(px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap, 1);
			if (plr[pnum].pManaShield)
				Cl2DrawLightTblSafe(
				    px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
				    py,
				    misfiledata[MFILE_MANASHLD].mAnimData[0],
				    1,
				    misfiledata[MFILE_MANASHLD].mAnimWidth[0],
				    CelSkip,
				    CelCap,
				    1);
		} else {
			l = light_table_index;
			if (light_table_index < 5)
				light_table_index = 0;
			else
				light_table_index -= 5;
			Cl2DrawLightSafe(px, py, pCelBuff, nCel, nWidth, CelSkip, CelCap);
			if (plr[pnum].pManaShield)
				Cl2DrawLightSafe(
				    px + plr[pnum]._pAnimWidth2 - misfiledata[MFILE_MANASHLD].mAnimWidth2[0],
				    py,
				    misfiledata[MFILE_MANASHLD].mAnimData[0],
				    1,
				    misfiledata[MFILE_MANASHLD].mAnimWidth[0],
				    CelSkip,
				    CelCap);
			light_table_index = l;
		}
	}
}

/**
 * @brief Render a player sprite
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 * @param clipped check for overdraw on lower screen
 */
void DrawDeadPlayer(int x, int y, int sx, int sy, int CelSkip, int CelCap, BOOL clipped)
{
	int i, px, py, nCel;
	PlayerStruct *p;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if (clipped)
		DrawPlrProc = DrawClippedPlayer;
	else
		DrawPlrProc = DrawPlayer;

	dFlags[x][y] &= ~BFLAG_DEAD_PLAYER;

	for (i = 0; i < MAX_PLRS; i++) {
		p = &plr[i];
		if (p->plractive && !p->_pHitPoints && p->plrlevel == (BYTE)currlevel && p->WorldX == x && p->WorldY == y) {
			pCelBuff = p->_pAnimData;
			if (!pCelBuff) {
				// app_fatal("Drawing dead player %d \"%s\": NULL Cel Buffer", i, p->_pName);
				break;
			}
			nCel = p->_pAnimFrame;
			pFrameTable = (DWORD *)pCelBuff;
			if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
				// app_fatal("Drawing dead player %d \"%s\": facing %d, frame %d of %d", i, p->_pName, p->_pdir, nCel, pFrameTable[0]);
				break;
			}
			dFlags[x][y] |= BFLAG_DEAD_PLAYER;
			px = sx + p->_pxoff - p->_pAnimWidth2;
			py = sy + p->_pyoff;
			DrawPlrProc(i, x, y, px, py, p->_pAnimData, p->_pAnimFrame, p->_pAnimWidth, CelSkip, CelCap);
		}
	}
}

/**
 * @brief Render an object sprite
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param ox Back buffer coordinate
 * @param oy Back buffer coordinate
 * @param pre Is the sprite in the background
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 */
static void DrawObject(int x, int y, int ox, int oy, BOOL pre, int CelSkip, int CelCap)
{
	int sx, sy, xx, yy, nCel;
	char bv;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if (dObject[x][y] > 0) {
		bv = dObject[x][y] - 1;
		if (object[bv]._oPreFlag != pre)
			return;
		sx = ox - object[bv]._oAnimWidth2;
		sy = oy;
	} else {
		bv = -(dObject[x][y] + 1);
		if (object[bv]._oPreFlag != pre)
			return;
		xx = object[bv]._ox - x;
		yy = object[bv]._oy - y;
		sx = (xx << 5) + ox - object[bv]._oAnimWidth2 - (yy << 5);
		sy = oy + (yy << 4) + (xx << 4);
		CelSkip = 0;
		CelCap = 8;
	}

	/// ASSERT: assert((unsigned char)bv < MAXOBJECTS);
	if ((BYTE)bv >= MAXOBJECTS)
		return;

	pCelBuff = object[bv]._oAnimData;
	if (!pCelBuff) {
		// app_fatal("Draw Object type %d: NULL Cel Buffer", object[bv]._otype);
		return;
	}

	nCel = object[bv]._oAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		// app_fatal("Draw Object: frame %d of %d, object type==%d", nCel, pFrameTable[0], object[bv]._otype);
		return;
	}

	if (bv == pcursobj)
		CelBlitOutline(194, sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, CelSkip, CelCap);
	if (object[bv]._oLight) {
		CelClippedDrawLight(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, CelSkip, CelCap);
	} else {
		/// ASSERT: assert(object[bv]._oAnimData);
		if (object[bv]._oAnimData) // BUGFIX: _oAnimData was already checked, this is redundant
			CelClippedDraw(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, CelSkip, CelCap);
	}
}

/**
 * @brief Render an object sprite, check for overdraw on lower screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param ox Back buffer coordinate
 * @param oy Back buffer coordinate
 * @param pre Is the sprite in the background
 * @param CelSkip Skip part of sprite, see Cl2Draw
 * @param CelCap  Skip part of sprite, see Cl2Draw
 */
static void DrawClippedObject(int x, int y, int ox, int oy, BOOL pre, int CelSkip, int CelCap)
{
	int sx, sy, xx, yy, nCel;
	char bv;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	if (dObject[x][y] > 0) {
		bv = dObject[x][y] - 1;
		if (object[bv]._oPreFlag != pre)
			return;
		sx = ox - object[bv]._oAnimWidth2;
		sy = oy;
	} else {
		bv = -(dObject[x][y] + 1);
		if (object[bv]._oPreFlag != pre)
			return;
		xx = object[bv]._ox - x;
		yy = object[bv]._oy - y;
		sx = (xx << 5) + ox - object[bv]._oAnimWidth2 - (yy << 5);
		sy = oy + (yy << 4) + (xx << 4);
		CelSkip = 0;
		CelCap = 8;
	}

	/// ASSERT: assert((unsigned char)bv < MAXOBJECTS);
	if ((BYTE)bv >= MAXOBJECTS)
		return;

	pCelBuff = object[bv]._oAnimData;
	if (!pCelBuff) {
		// app_fatal("Draw Object type %d Clipped: NULL Cel Buffer", object[bv]._otype);
		return;
	}

	nCel = object[bv]._oAnimFrame;
	pFrameTable = (DWORD *)pCelBuff;
	if (nCel < 1 || pFrameTable[0] > 50 || nCel > (int)pFrameTable[0]) {
		// app_fatal("Draw Clipped Object: frame %d of %d, object type==%d", nCel, pFrameTable[0], object[bv]._otype);
		return;
	}

	if (bv == pcursobj)
		CelBlitOutlineSafe(194, sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, CelSkip, CelCap);
	if (object[bv]._oLight)
		CelDrawLightSafe(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, CelSkip, CelCap);
	else
		CelClippedDrawSafe(sx, sy, object[bv]._oAnimData, object[bv]._oAnimFrame, object[bv]._oAnimWidth, CelSkip, CelCap);
}

static void scrollrt_draw_clipped_dungeon(BYTE *pBuff, int sx, int sy, int dx, int dy, int eflag);

/**
 * This variant checks for of screen element on the lower screen
 * This function it self causes rendering issues since it will render on top of objects on the other side of walls
 * @brief Re render tile to workaround sorting issues with players walking east/west
 * @param pBuff Pointer to output buffer at location sx,sy
 * @param y dPiece coordinate
 * @param x dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 */
static void scrollrt_draw_clipped_e_flag(BYTE *pBuff, int x, int y, int sx, int sy)
{
	int i, lti_old, cta_old, lpi_old;
	BYTE *dst;
	MICROS *pMap;

	lti_old = light_table_index;
	cta_old = cel_transparency_active;
	lpi_old = level_piece_id;

	level_piece_id = dPiece[x][y];
	light_table_index = dLight[x][y];
	cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	dst = pBuff;
	arch_draw_type = 1;
	level_cel_block = pMap->mt[0];
	if (level_cel_block != 0) {
		drawLowerScreen(dst);
	}
	arch_draw_type = 2;
	level_cel_block = pMap->mt[1];
	if (level_cel_block != 0) {
		drawLowerScreen(dst + 32);
	}

	dst = pBuff;
	arch_draw_type = 0;
	for (i = 2; i < MicroTileLen; i += 2) {
		dst -= BUFFER_WIDTH * 32;
		level_cel_block = pMap->mt[i];
		if (level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[i + 1];
		if (level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	}

	scrollrt_draw_clipped_dungeon(pBuff, x, y, sx, sy, 0);

	light_table_index = lti_old;
	cel_transparency_active = cta_old;
	level_piece_id = lpi_old;
}

/**
 * @brief Render object sprites
 * @param pBuff where to render to with sx,sy already applied
 * @param sx dPiece coordinate
 * @param sy dPiece coordinate
 * @param dx Back buffer coordinate
 * @param dy Back buffer coordinate
 * @param eflag Should the sorting workaround be applied
 */
static void scrollrt_draw_clipped_dungeon(BYTE *pBuff, int sx, int sy, int dx, int dy, int eflag)
{
	int px, py, nCel, nMon, negMon, p;
	char bFlag, bDead, bObj, bItem, bPlr, bArch, bMap, negPlr, dd;
	DeadStruct *pDeadGuy;
	ItemStruct *pItem;
	PlayerStruct *pPlayer;
	MonsterStruct *pMonster;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	/// ASSERT: assert((DWORD)sx < MAXDUNX);
	/// ASSERT: assert((DWORD)sy < MAXDUNY);
	bFlag = dFlags[sx][sy];
	bDead = dDead[sx][sy];
	bObj = dObject[sx][sy];
	bItem = dItem[sx][sy];
	bPlr = dPlayer[sx][sy];
	bArch = dSpecial[sx][sy];
	bMap = dTransVal[sx][sy];
	nMon = dMonster[sx][sy];

	/// ASSERT: assert((DWORD)(sy-1) < MAXDUNY);
	negPlr = dPlayer[sx][sy - 1];
	negMon = dMonster[sx][sy - 1];

	if (visiondebug && bFlag & BFLAG_LIT) {
		CelClippedBlitSafe(pBuff, pSquareCel, 1, 64, 0, 8);
	}
	if (MissilePreFlag && bFlag & BFLAG_MISSILE) {
		DrawClippedMissile(sx, sy, dx, dy, 0, 8, TRUE);
	}
	if (light_table_index < lightmax) {
		if (bDead != 0) {
			pDeadGuy = &dead[(bDead & 0x1F) - 1];
			dd = (bDead >> 5) & 7;
			px = dx - pDeadGuy->_deadWidth2;
			pCelBuff = pDeadGuy->_deadData[dd];
			/// ASSERT: assert(pDeadGuy->_deadData[dd] != NULL);
			if (pCelBuff != NULL) {
				pFrameTable = (DWORD *)pDeadGuy->_deadData[dd];
				nCel = pDeadGuy->_deadFrame;
				if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
					if (pDeadGuy->_deadtrans != 0) {
						Cl2DrawLightTblSafe(px, dy, pCelBuff, nCel, pDeadGuy->_deadWidth, 0, 8, pDeadGuy->_deadtrans);
					} else {
						Cl2DrawLightSafe(px, dy, pCelBuff, pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, 0, 8);
					}
				} else {
					// app_fatal("Clipped dead sub: frame %d of %d, deadnum==%d", nCel, pFrameTable[0], (bDead & 0x1F) - 1);
				}
			}
		}
		if (bObj != 0) {
			DrawClippedObject(sx, sy, dx, dy, 1, 0, 8);
		}
	}
	if (bItem != 0) {
		pItem = &item[bItem - 1];
		if (!pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if ((BYTE)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if (pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if (bItem - 1 == pcursitem) {
							CelBlitOutlineSafe(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, 0, 8);
						}
						CelDrawLightSafe(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 1: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if (bFlag & BFLAG_PLAYERLR) {
		p = -(negPlr + 1);
		if ((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy - 1, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, 8);
			if (eflag && pPlayer->_peflag != 0) {
				if (pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag(pBuff - (BUFFER_WIDTH * 16 + 96), sx - 2, sy + 1, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if (bFlag & BFLAG_MONSTLR && (bFlag & BFLAG_LIT || plr[myplr]._pInfraFlag) && negMon < 0) {
		draw_monster_num = -(negMon + 1);
		if ((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if (!(pMonster->_mFlags & MFLAG_HIDDEN)) {
				if (pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->width2;
					py = dy + pMonster->_myoff;
					if (draw_monster_num == pcursmonst) {
						Cl2DrawOutlineSafe(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->width, 0, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, 0, 8);
					if (eflag && pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if (bFlag & BFLAG_DEAD_PLAYER) {
		DrawDeadPlayer(sx, sy, dx, dy, 0, 8, TRUE);
	}
	if (bPlr > 0) {
		p = bPlr - 1;
		if ((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, 8);
			if (eflag && pPlayer->_peflag != 0) {
				if (pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag(pBuff - (BUFFER_WIDTH * 16 + 96), sx - 2, sy + 1, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if (nMon > 0 && (bFlag & BFLAG_LIT || plr[myplr]._pInfraFlag)) {
		draw_monster_num = nMon - 1;
		if ((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if (!(pMonster->_mFlags & MFLAG_HIDDEN)) {
				if (pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->width2;
					py = dy + pMonster->_myoff;
					if (draw_monster_num == pcursmonst) {
						Cl2DrawOutlineSafe(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->width, 0, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, 0, 8);
					if (eflag && pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag(pBuff - 64, sx - 1, sy + 1, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if (bFlag & BFLAG_MISSILE) {
		DrawClippedMissile(sx, sy, dx, dy, 0, 8, FALSE);
	}
	if (bObj != 0 && light_table_index < lightmax) {
		DrawClippedObject(sx, sy, dx, dy, 0, 0, 8);
	}
	if (bItem != 0) {
		pItem = &item[bItem - 1];
		if (pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if ((BYTE)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if (pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if (bItem - 1 == pcursitem) {
							CelBlitOutlineSafe(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, 0, 8);
						}
						CelDrawLightSafe(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item 2: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 2: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if (bArch != 0) {
		cel_transparency_active = TransList[bMap];
		CelClippedBlitLightTransSafe(pBuff, pSpecialCels, bArch, 64, 0, 8);
	}
}

/**
 * @brief Render a row of tile
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param chunks tile width of row
 * @param eflag is it an even (0) or odd (1) row
 */
static void scrollrt_draw_lower(int x, int y, int sx, int sy, int chunks, int eflag)
{
	int i, j;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	if (eflag) {
		if ((DWORD)y < MAXDUNY && (DWORD)x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx + 32 + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 2;
				level_cel_block = pMap->mt[1];
				if (level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				arch_draw_type = 0;
				dst -= BUFFER_WIDTH * 32;
				level_cel_block = pMap->mt[3];
				if (level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= BUFFER_WIDTH * 32;
				level_cel_block = pMap->mt[5];
				if (level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= BUFFER_WIDTH * 32;
				level_cel_block = pMap->mt[7];
				if (level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= BUFFER_WIDTH * 32;
				level_cel_block = pMap->mt[9];
				if (level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				dst -= BUFFER_WIDTH * 32;
				level_cel_block = pMap->mt[11];
				if (level_cel_block != 0 && leveltype == DTYPE_HELL) {
					drawLowerScreen(dst);
				}
				scrollrt_draw_clipped_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 0);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
		chunks--;
	}

	j = chunks;
	while (j-- != 0) {
		if (y < 0 || x >= MAXDUNX) {
			break;
		}
		if (y < MAXDUNY && x >= 0) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id == 0) {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			} else {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 1;
				level_cel_block = pMap->mt[0];
				if (level_cel_block != 0) {
					drawLowerScreen(dst);
				}
				arch_draw_type = 2;
				level_cel_block = pMap->mt[1];
				if (level_cel_block != 0) {
					drawLowerScreen(dst + 32);
				}
				arch_draw_type = 0;
				for (i = 2; i < MicroTileLen; i += 2) {
					dst -= BUFFER_WIDTH * 32;
					level_cel_block = pMap->mt[i];
					if (level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					level_cel_block = pMap->mt[i + 1];
					if (level_cel_block != 0) {
						drawLowerScreen(dst + 32);
					}
				}
				scrollrt_draw_clipped_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 1);
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
	}

	if (eflag && (DWORD)y < MAXDUNY && (DWORD)x < MAXDUNX) {
		level_piece_id = dPiece[x][y];
		light_table_index = dLight[x][y];
		if (level_piece_id == 0) {
			world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
		} else {
			dst = &gpBuffer[sx + PitchTbl[sy]];
			cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
			arch_draw_type = 1;
			level_cel_block = pMap->mt[0];
			if (level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			arch_draw_type = 0;
			dst -= BUFFER_WIDTH * 32;
			level_cel_block = pMap->mt[2];
			if (level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= BUFFER_WIDTH * 32;
			level_cel_block = pMap->mt[4];
			if (level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= BUFFER_WIDTH * 32;
			level_cel_block = pMap->mt[6];
			if (level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= BUFFER_WIDTH * 32;
			level_cel_block = pMap->mt[8];
			if (level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			dst -= BUFFER_WIDTH * 32;
			level_cel_block = pMap->mt[10];
			if (level_cel_block != 0 && leveltype == DTYPE_HELL) {
				drawLowerScreen(dst);
			}
			scrollrt_draw_clipped_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 0);
		}
	}
}

static void scrollrt_draw_clipped_dungeon_2(BYTE *pBuff, int sx, int sy, int row, int CelSkip, int dx, int dy, int eflag);

/**
 * This variant checks for of screen element on the lower screen
 * This function it self causes rendering issues since it will render on top of objects on the other side of walls
 * @brief Re render tile to workaround sorting issues with players walking east/west
 * @param pBuff Pointer to output buffer at location sx,sy
 * @param y dPiece coordinate
 * @param x dPiece coordinate
 * @param row The current row being rendered
 * @param CelSkip chunks of cell to skip
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 */
static void scrollrt_draw_clipped_e_flag_2(BYTE *pBuff, int x, int y, int row, int CelSkip, int sx, int sy)
{
	int lti_old, cta_old, lpi_old;
	BYTE *dst;
	MICROS *pMap;

	lti_old = light_table_index;
	cta_old = cel_transparency_active;
	lpi_old = level_piece_id;

	level_piece_id = dPiece[x][y];
	light_table_index = dLight[x][y];
	dst = &pBuff[BUFFER_WIDTH * 32 * row];
	cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	switch (row) {
	case 0:
		level_cel_block = pMap->mt[2];
		if (level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[3];
		if (level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	case 1:
		dst -= BUFFER_WIDTH * 32;
		level_cel_block = pMap->mt[4];
		if (level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[5];
		if (level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	case 2:
		dst -= BUFFER_WIDTH * 32;
		level_cel_block = pMap->mt[6];
		if (level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[7];
		if (level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
	case 3:
		dst -= BUFFER_WIDTH * 32;
		level_cel_block = pMap->mt[8];
		if (level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[9];
		if (level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
		break;
	}

	if (CelSkip < 8) {
		scrollrt_draw_clipped_dungeon_2(pBuff, x, y, row, CelSkip, sx, sy, 0);
	}

	light_table_index = lti_old;
	cel_transparency_active = cta_old;
	level_piece_id = lpi_old;
}

/**
 * This variant checks for of screen element on the lower screen
 * @brief Render object sprites, skip offscreen parts for lower screen
 * @param pBuff where to render to with sx,sy already applied
 * @param sx dPiece coordinate
 * @param sy dPiece coordinate
 * @param row The current row being rendered
 * @param CelSkip chunks of cell to skip
 * @param dx Back buffer coordinate
 * @param dy Back buffer coordinate
 * @param eflag Should the sorting workaround be applied
 */
static void scrollrt_draw_clipped_dungeon_2(BYTE *pBuff, int sx, int sy, int row, int CelSkip, int dx, int dy, int eflag)
{
	int px, py, nCel, nMon, negMon, p;
	char bFlag, bDead, bObj, bItem, bPlr, bArch, bMap, negPlr, dd;
	DeadStruct *pDeadGuy;
	ItemStruct *pItem;
	PlayerStruct *pPlayer;
	MonsterStruct *pMonster;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	/// ASSERT: assert((DWORD)sx < MAXDUNX);
	/// ASSERT: assert((DWORD)sy < MAXDUNY);
	bFlag = dFlags[sx][sy];
	bDead = dDead[sx][sy];
	bObj = dObject[sx][sy];
	bItem = dItem[sx][sy];
	bPlr = dPlayer[sx][sy];
	bArch = dSpecial[sx][sy];
	bMap = dTransVal[sx][sy];
	nMon = dMonster[sx][sy];

	/// ASSERT: assert((DWORD)(sy-1) < MAXDUNY);
	negPlr = dPlayer[sx][sy - 1];
	negMon = dMonster[sx][sy - 1];

	if (visiondebug && bFlag & BFLAG_LIT) {
		CelClippedBlitSafe(pBuff, pSquareCel, 1, 64, CelSkip, 8);
	}
	if (MissilePreFlag && bFlag & BFLAG_MISSILE) {
		DrawClippedMissile(sx, sy, dx, dy, CelSkip, 8, TRUE);
	}
	if (light_table_index < lightmax) {
		if (bDead != 0) {
			pDeadGuy = &dead[(bDead & 0x1F) - 1];
			dd = (bDead >> 5) & 7;
			px = dx - pDeadGuy->_deadWidth2;
			pCelBuff = pDeadGuy->_deadData[dd];
			/// ASSERT: assert(pDeadGuy->_deadData[dd] != NULL);
			if (pCelBuff != NULL) {
				pFrameTable = (DWORD *)pDeadGuy->_deadData[dd];
				nCel = pDeadGuy->_deadFrame;
				if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
					if (pDeadGuy->_deadtrans != 0) {
						Cl2DrawLightTblSafe(px, dy, pCelBuff, nCel, pDeadGuy->_deadWidth, CelSkip, 8, pDeadGuy->_deadtrans);
					} else {
						Cl2DrawLightSafe(px, dy, pCelBuff, pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, CelSkip, 8);
					}
				} else {
					// app_fatal("Clipped dead sub2: frame %d of %d, deadnum==%d", nCel, pFrameTable[0], (bDead & 0x1F) - 1);
				}
			}
		}
		if (bObj != 0) {
			DrawClippedObject(sx, sy, dx, dy, 1, CelSkip, 8);
		}
	}
	if (bItem != 0) {
		pItem = &item[bItem - 1];
		if (!pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if ((BYTE)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if (pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if (bItem - 1 == pcursitem) {
							CelBlitOutlineSafe(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, CelSkip, 8);
						}
						CelDrawLightSafe(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, CelSkip, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item 3: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 3: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if (bFlag & BFLAG_PLAYERLR) {
		p = -(negPlr + 1);
		if ((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy - 1, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, CelSkip, 8);
			if (eflag && pPlayer->_peflag != 0) {
				if (pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag_2(pBuff - (BUFFER_WIDTH * 16 + 96), sx - 2, sy + 1, row, CelSkip, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, row, CelSkip, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if (bFlag & BFLAG_MONSTLR && (bFlag & BFLAG_LIT || plr[myplr]._pInfraFlag) && negMon < 0) {
		draw_monster_num = -(negMon + 1);
		if ((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if (!(pMonster->_mFlags & MFLAG_HIDDEN)) {
				if (pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->width2;
					py = dy + pMonster->_myoff;
					if (draw_monster_num == pcursmonst) {
						Cl2DrawOutlineSafe(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->width, CelSkip, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, CelSkip, 8);
					if (eflag && !pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, row, CelSkip, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if (bFlag & BFLAG_DEAD_PLAYER) {
		DrawDeadPlayer(sx, sy, dx, dy, CelSkip, 8, TRUE);
	}
	if (bPlr > 0) {
		p = bPlr - 1;
		if ((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawClippedPlayer(p, sx, sy, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, CelSkip, 8);
			if (eflag && pPlayer->_peflag != 0) {
				if (pPlayer->_peflag == 2) {
					scrollrt_draw_clipped_e_flag_2(pBuff - (BUFFER_WIDTH * 16 + 96), sx - 2, sy + 1, row, CelSkip, dx - 96, dy - 16);
				}
				scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, row, CelSkip, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player clipped: tried to draw illegal player %d", p);
		}
	}
	if (nMon > 0 && (bFlag & BFLAG_LIT || plr[myplr]._pInfraFlag)) {
		draw_monster_num = nMon - 1;
		if ((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if (!(pMonster->_mFlags & MFLAG_HIDDEN)) {
				if (pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->width2;
					py = dy + pMonster->_myoff;
					if (draw_monster_num == pcursmonst) {
						Cl2DrawOutlineSafe(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->width, CelSkip, 8);
					}
					DrawClippedMonster(sx, sy, px, py, draw_monster_num, CelSkip, 8);
					if (eflag && !pMonster->_meflag) {
						scrollrt_draw_clipped_e_flag_2(pBuff - 64, sx - 1, sy + 1, row, CelSkip, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\" Clipped: uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster Clipped: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if (bFlag & BFLAG_MISSILE) {
		DrawClippedMissile(sx, sy, dx, dy, CelSkip, 8, FALSE);
	}
	if (bObj != 0 && light_table_index < lightmax) {
		DrawClippedObject(sx, sy, dx, dy, 0, CelSkip, 8);
	}
	if (bItem != 0) {
		pItem = &item[bItem - 1];
		if (pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if ((BYTE)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if (pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if (bItem - 1 == pcursitem) {
							CelBlitOutlineSafe(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, CelSkip, 8);
						}
						CelDrawLightSafe(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, CelSkip, 8);
					} else {
						/*
						app_fatal(
							"Draw Clipped \"%s\" Item 4: frame %d of %d, item type==%d",
							pItem->_iIName,
							nCel,
							pFrameTable[0],
							pItem->_itype);
						*/
					}
				} else {
					// app_fatal("Draw Item \"%s\" Clipped 4: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if (bArch != 0) {
		cel_transparency_active = TransList[bMap];
		CelClippedBlitLightTransSafe(pBuff, pSpecialCels, bArch, 64, CelSkip, 8);
	}
}

/**
 * @brief Render a row of tile, checking for overdrawing on lower part of screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param chunks tile width of row
 * @param row current row being rendered
 * @param eflag is it an even (0) or odd (1) row
 */
static void scrollrt_draw_lower_2(int x, int y, int sx, int sy, int chunks, int row, int eflag)
{
	int i, j, CelSkip;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
	CelSkip = 2 * row + 2;

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx - (BUFFER_WIDTH * 32 - 32) + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				for (i = 0; i < (MicroTileLen >> 1) - 1; i++) {
					if (row <= i) {
						level_cel_block = pMap->mt[2 * i + 3];
						if (level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= BUFFER_WIDTH * 32;
				}
				if (CelSkip < 8) {
					scrollrt_draw_clipped_dungeon_2(&gpBuffer[sx + PitchTbl[sy] - BUFFER_WIDTH * 16 * CelSkip], x, y, row, CelSkip, sx, sy, 0);
				}
			}
		}
		x++;
		y--;
		sx += 64;
		chunks--;
		pMap++;
	}

	j = chunks;
	while (j-- != 0) {
		if (x >= MAXDUNX || y < 0) {
			break;
		}
		if (y < MAXDUNY && x >= 0) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx - BUFFER_WIDTH * 32 + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				i = 0;
				while (i < (MicroTileLen >> 1) - 1) {
					if (row <= i) {
						level_cel_block = pMap->mt[2 * i + 2];
						if (level_cel_block != 0) {
							drawLowerScreen(dst);
						}
						level_cel_block = pMap->mt[2 * i + 3];
						if (level_cel_block != 0) {
							drawLowerScreen(dst + 32);
						}
					}
					i++;
					dst -= BUFFER_WIDTH * 32;
				}
				if (CelSkip < 8) {
					scrollrt_draw_clipped_dungeon_2(&gpBuffer[sx + PitchTbl[sy] - BUFFER_WIDTH * 32 * (row + 1)], x, y, row, CelSkip, sx, sy, 1);
				}
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
	}

	if (eflag) {
		if ((DWORD)y < MAXDUNY && (DWORD)x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx - BUFFER_WIDTH * 32 + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				for (i = 0; i < (MicroTileLen >> 1) - 1; i++) {
					if (row <= i) {
						level_cel_block = pMap->mt[2 * i + 2];
						if (level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= BUFFER_WIDTH * 32;
				}
				if (CelSkip < 8) {
					scrollrt_draw_clipped_dungeon_2(&gpBuffer[sx + PitchTbl[sy] - BUFFER_WIDTH * 16 * CelSkip], x, y, row, CelSkip, sx, sy, 0);
				}
			}
		}
	}
}

static void scrollrt_draw_dungeon(BYTE *pBuff, int sx, int sy, int row, int CelCap, int dx, int dy, int eflag);

/**
 * This variant checks for of screen element on the upper screen
 * This function it self causes rendering issues since it will render on top of objects on the other side of walls
 * @brief Re render tile to workaround sorting issues with players walking east/west
 * @param pBuff Pointer to output buffer at location sx,sy
 * @param y dPiece coordinate
 * @param x dPiece coordinate
 * @param row The current row being rendered
 * @param CelCap chunks of cell to skip
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 */
static void scrollrt_draw_e_flag(BYTE *pBuff, int x, int y, int row, int CelCap, int sx, int sy)
{
	int i, lti_old, cta_old, lpi_old;
	BYTE *dst;
	MICROS *pMap;

	lti_old = light_table_index;
	cta_old = cel_transparency_active;
	lpi_old = level_piece_id;

	level_piece_id = dPiece[x][y];
	light_table_index = dLight[x][y];
	dst = pBuff;
	cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	arch_draw_type = 1;
	level_cel_block = pMap->mt[0];
	if (level_cel_block != 0) {
		drawUpperScreen(dst);
	}
	arch_draw_type = 2;
	level_cel_block = pMap->mt[1];
	if (level_cel_block != 0) {
		drawUpperScreen(dst + 32);
	}

	arch_draw_type = 0;
	for (i = 1; i < (MicroTileLen >> 1) - 1; i++) {
		dst -= BUFFER_WIDTH * 32;
		if (row >= i) {
			level_cel_block = pMap->mt[2 * i];
			if (level_cel_block != 0) {
				drawUpperScreen(dst);
			}
			level_cel_block = pMap->mt[2 * i + 1];
			if (level_cel_block != 0) {
				drawUpperScreen(dst + 32);
			}
		}
	}

	scrollrt_draw_dungeon(pBuff, x, y, row, CelCap, sx, sy, 0);

	light_table_index = lti_old;
	cel_transparency_active = cta_old;
	level_piece_id = lpi_old;
}

/**
 * @brief Render object sprites, skip offscreen parts for upper screen
 * @param pBuff where to render to with sx,sx already applied
 * @param sx dPiece coordinate
 * @param sy dPiece coordinate
 * @param row The current row being rendered
 * @param CelCap chunks of cell to skip
 * @param dx Back buffer coordinate
 * @param dy Back buffer coordinate
 * @param eflag Should the sorting workaround be applied
 */
static void scrollrt_draw_dungeon(BYTE *pBuff, int sx, int sy, int row, int CelCap, int dx, int dy, int eflag)
{
	int px, py, nCel, nMon, negMon, p, tx, ty;
	char bFlag, bDead, bObj, bItem, bPlr, bArch, bMap, negPlr, dd;
	DeadStruct *pDeadGuy;
	ItemStruct *pItem;
	PlayerStruct *pPlayer;
	MonsterStruct *pMonster;
	BYTE *pCelBuff;
	DWORD *pFrameTable;

	/// ASSERT: assert((DWORD)sx < MAXDUNX);
	/// ASSERT: assert((DWORD)sy < MAXDUNY);
	bFlag = dFlags[sx][sy];
	bDead = dDead[sx][sy];
	bObj = dObject[sx][sy];
	bItem = dItem[sx][sy];
	bPlr = dPlayer[sx][sy];
	bArch = dSpecial[sx][sy];
	bMap = dTransVal[sx][sy];
	nMon = dMonster[sx][sy];

	/// ASSERT: assert((DWORD)(sy-1) < MAXDUNY);
	negPlr = dPlayer[sx][sy - 1];
	negMon = dMonster[sx][sy - 1];

	if (visiondebug && bFlag & BFLAG_LIT) {
		CelClippedBlit(pBuff, pSquareCel, 1, 64, 0, CelCap);
	}
	tx = dx - 96;
	ty = dy - 16;

	if (MissilePreFlag && bFlag & BFLAG_MISSILE) {
		DrawMissile(sx, sy, dx, dy, 0, CelCap, TRUE);
	}

	if (light_table_index < lightmax) {
		if (bDead != 0) {
			pDeadGuy = &dead[(bDead & 0x1F) - 1];
			dd = (bDead >> 5) & 7;
			px = dx - pDeadGuy->_deadWidth2;
			pCelBuff = pDeadGuy->_deadData[dd];
			/// ASSERT: assert(pDeadGuy->_deadData[dd] != NULL);
			if (pCelBuff != NULL) {
				pFrameTable = (DWORD *)pDeadGuy->_deadData[dd];
				nCel = pDeadGuy->_deadFrame;
				if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
					if (pDeadGuy->_deadtrans != 0) {
						Cl2DrawLightTbl(px, dy, pCelBuff, nCel, pDeadGuy->_deadWidth, 0, CelCap, pDeadGuy->_deadtrans);
					} else {
						Cl2DrawLight(px, dy, pCelBuff, pDeadGuy->_deadFrame, pDeadGuy->_deadWidth, 0, CelCap);
					}
				} else {
					// app_fatal("Unclipped dead: frame %d of %d, deadnum==%d", nCel, pFrameTable[0], (bDead & 0x1F) - 1);
				}
			}
		}
		if (bObj != 0) {
			DrawObject(sx, sy, dx, dy, 1, 0, CelCap);
		}
	}
	if (bItem != 0) {
		pItem = &item[bItem - 1];
		if (!pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if ((BYTE)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if (pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if (bItem - 1 == pcursitem) {
							CelBlitOutline(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, 0, CelCap);
						}
						CelClippedDrawLight(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, CelCap);
					} else {
						// app_fatal("Draw \"%s\" Item 1: frame %d of %d, item type==%d", pItem->_iIName, nCel, pFrameTable[0], pItem->_itype);
					}
				} else {
					// app_fatal("Draw Item \"%s\" 1: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if (bFlag & BFLAG_PLAYERLR) {
		p = -(negPlr + 1);
		if ((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawPlayer(p, sx, sy - 1, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, CelCap);
			if (eflag && pPlayer->_peflag != 0) {
				if (pPlayer->_peflag == 2) {
					scrollrt_draw_e_flag(pBuff - (BUFFER_WIDTH * 16 + 96), sx - 2, sy + 1, row, CelCap, tx, ty);
				}
				scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, row, CelCap, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player: tried to draw illegal player %d", p);
		}
	}
	if (bFlag & BFLAG_MONSTLR && (bFlag & BFLAG_LIT || plr[myplr]._pInfraFlag) && negMon < 0) {
		draw_monster_num = -(negMon + 1);
		if ((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if (!(pMonster->_mFlags & MFLAG_HIDDEN)) {
				if (pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->width2;
					py = dy + pMonster->_myoff;
					if (draw_monster_num == pcursmonst) {
						Cl2DrawOutline(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->width, 0, CelCap);
					}
					DrawMonster(sx, sy, px, py, draw_monster_num, 0, CelCap);
					if (eflag && !pMonster->_meflag) {
						scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, row, CelCap, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\": uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if (bFlag & BFLAG_DEAD_PLAYER) {
		DrawDeadPlayer(sx, sy, dx, dy, 0, CelCap, FALSE);
	}
	if (bPlr > 0) {
		p = bPlr - 1;
		if ((DWORD)p < MAX_PLRS) {
			pPlayer = &plr[p];
			px = dx + pPlayer->_pxoff - pPlayer->_pAnimWidth2;
			py = dy + pPlayer->_pyoff;
			DrawPlayer(p, sx, sy, px, py, pPlayer->_pAnimData, pPlayer->_pAnimFrame, pPlayer->_pAnimWidth, 0, CelCap);
			if (eflag && pPlayer->_peflag != 0) {
				if (pPlayer->_peflag == 2) {
					scrollrt_draw_e_flag(pBuff - (BUFFER_WIDTH * 16 + 96), sx - 2, sy + 1, row, CelCap, dx - 96, dy - 16);
				}
				scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, row, CelCap, dx - 64, dy);
			}
		} else {
			// app_fatal("draw player: tried to draw illegal player %d", p);
		}
	}
	if (nMon > 0 && (bFlag & BFLAG_LIT || plr[myplr]._pInfraFlag)) {
		draw_monster_num = nMon - 1;
		if ((DWORD)draw_monster_num < MAXMONSTERS) {
			pMonster = &monster[draw_monster_num];
			if (!(pMonster->_mFlags & MFLAG_HIDDEN)) {
				if (pMonster->MType != NULL) {
					px = dx + pMonster->_mxoff - pMonster->MType->width2;
					py = dy + pMonster->_myoff;
					if (draw_monster_num == pcursmonst) {
						Cl2DrawOutline(233, px, py, pMonster->_mAnimData, pMonster->_mAnimFrame, pMonster->MType->width, 0, CelCap);
					}
					DrawMonster(sx, sy, px, py, draw_monster_num, 0, CelCap);
					if (eflag && !pMonster->_meflag) {
						scrollrt_draw_e_flag(pBuff - 64, sx - 1, sy + 1, row, CelCap, dx - 64, dy);
					}
				} else {
					// app_fatal("Draw Monster \"%s\": uninitialized monster", pMonster->mName);
				}
			}
		} else {
			// app_fatal("Draw Monster: tried to draw illegal monster %d", draw_monster_num);
		}
	}
	if (bFlag & BFLAG_MISSILE) {
		DrawMissile(sx, sy, dx, dy, 0, CelCap, FALSE);
	}
	if (bObj != 0 && light_table_index < lightmax) {
		DrawObject(sx, sy, dx, dy, 0, 0, CelCap);
	}
	if (bItem != 0) {
		pItem = &item[bItem - 1];
		if (pItem->_iPostDraw) {
			/// ASSERT: assert((unsigned char)bItem <= MAXITEMS);
			if ((BYTE)bItem <= MAXITEMS) {
				pCelBuff = pItem->_iAnimData;
				if (pCelBuff != NULL) {
					pFrameTable = (DWORD *)pCelBuff;
					nCel = pItem->_iAnimFrame;
					if (nCel >= 1 && pFrameTable[0] <= 50 && nCel <= (int)pFrameTable[0]) {
						px = dx - pItem->_iAnimWidth2;
						if (bItem - 1 == pcursitem) {
							CelBlitOutline(181, px, dy, pCelBuff, nCel, pItem->_iAnimWidth, 0, CelCap);
						}
						CelClippedDrawLight(px, dy, pItem->_iAnimData, pItem->_iAnimFrame, pItem->_iAnimWidth, 0, CelCap);
					} else {
						// app_fatal("Draw \"%s\" Item 2: frame %d of %d, item type==%d", pItem->_iIName, nCel, pFrameTable[0], pItem->_itype);
					}
				} else {
					// app_fatal("Draw Item \"%s\" 2: NULL Cel Buffer", pItem->_iIName);
				}
			}
		}
	}
	if (bArch != 0) {
		cel_transparency_active = TransList[bMap];
		CelClippedBlitLightTrans(pBuff, pSpecialCels, bArch, 64, 0, CelCap);
	}
}

/**
 * @brief Render a row of tile, checking for overdrawing on upper part of screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param chunks tile width of row
 * @param row current row being rendered
 * @param eflag is it an even (0) or odd (1) row
 */
static void scrollrt_draw_upper(int x, int y, int sx, int sy, int chunks, int row, int eflag)
{
	int i, j, CelCap;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
	CelCap = 2 * row + 2;
	if (CelCap > 8) {
		CelCap = 8;
	}

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx + 32 + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				if (row >= 0) {
					level_cel_block = pMap->mt[1];
					if (level_cel_block != 0) {
						arch_draw_type = 2;
						drawUpperScreen(dst);
						arch_draw_type = 0;
					}
				}
				dst -= BUFFER_WIDTH * 32;
				if (row >= 1) {
					level_cel_block = pMap->mt[3];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				dst -= BUFFER_WIDTH * 32;
				if (row >= 2) {
					level_cel_block = pMap->mt[5];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				dst -= BUFFER_WIDTH * 32;
				if (row >= 3) {
					level_cel_block = pMap->mt[7];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				scrollrt_draw_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelCap, sx, sy, 0);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
		x++;
		y--;
		sx += 64;
		chunks--;
		pMap++;
	}

	for (j = 0; j < chunks; j++) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 1;
				level_cel_block = pMap->mt[0];
				if (level_cel_block != 0) {
					drawUpperScreen(dst);
				}
				arch_draw_type = 2;
				level_cel_block = pMap->mt[1];
				if (level_cel_block != 0) {
					drawUpperScreen(dst + 32);
				}
				arch_draw_type = 0;
				for (i = 1; i < (MicroTileLen >> 1) - 1; i++) {
					dst -= BUFFER_WIDTH * 32;
					if (row >= i) {
						level_cel_block = pMap->mt[2 * i];
						if (level_cel_block != 0) {
							drawUpperScreen(dst);
						}
						level_cel_block = pMap->mt[2 * i + 1];
						if (level_cel_block != 0) {
							drawUpperScreen(dst + 32);
						}
					}
				}
				scrollrt_draw_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelCap, sx, sy, 1);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
		x++;
		y--;
		sx += 64;
		pMap++;
	}

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_piece_id = dPiece[x][y];
			light_table_index = dLight[x][y];
			if (level_piece_id != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				cel_transparency_active = (BYTE)(nTransTable[level_piece_id] & TransList[dTransVal[x][y]]);
				arch_draw_type = 1;
				if (row >= 0) {
					level_cel_block = pMap->mt[0];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				arch_draw_type = 0;
				dst -= BUFFER_WIDTH * 32;
				if (row >= 1) {
					level_cel_block = pMap->mt[2];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				dst -= BUFFER_WIDTH * 32;
				if (row >= 2) {
					level_cel_block = pMap->mt[4];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				dst -= BUFFER_WIDTH * 32;
				if (row >= 3) {
					level_cel_block = pMap->mt[6];
					if (level_cel_block != 0) {
						drawUpperScreen(dst);
					}
				}
				scrollrt_draw_dungeon(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelCap, sx, sy, 0);
			} else {
				world_draw_black_tile(&gpBuffer[sx + PitchTbl[sy]]);
			}
		}
	}
}

/**
 * @brief Configure render and process screen rows
 * @param x Center of view in dPiece coordinate
 * @param y Center of view in dPiece coordinate
 */
static void DrawGame(int x, int y)
{
	int i, sx, sy, chunks, blocks;

	ViewDX = SCREEN_WIDTH;
	ViewDY = VIEWPORT_HEIGHT;
	ViewBX = SCREEN_WIDTH / 64;
	ViewBY = VIEWPORT_HEIGHT / 32;

	sx = ScrollInfo._sxoff + SCREEN_X;
	sy = ScrollInfo._syoff + SCREEN_Y + 15;
	x -= SCREEN_WIDTH / 64;
	y--;
	chunks = SCREEN_WIDTH / 64;
	blocks = 8;

	if (chrflag || questlog) {
		x += 2;
		y -= 2;
		sx += (SCREEN_WIDTH / 2) - 32;
		chunks = (SCREEN_WIDTH / 64) - 4;
	}
	if (invflag || sbookflag) {
		x += 2;
		y -= 2;
		sx -= 32;
		chunks = (SCREEN_WIDTH / 64) - 4;
	}

	switch (ScrollInfo._sdir) {
	case SDIR_NONE:
		break;
	case SDIR_NE:
		chunks++;
	case SDIR_N:
		sy -= 32;
		x--;
		y--;
		blocks++;
		break;
	case SDIR_SE:
		blocks++;
	case SDIR_E:
		chunks++;
		break;
	case SDIR_S:
		blocks++;
		break;
	case SDIR_SW:
		blocks++;
	case SDIR_W:
		sx -= 64;
		x--;
		y++;
		chunks++;
		break;
	case SDIR_NW:
		sx -= 64;
		sy -= 32;
		x -= 2;
		chunks++;
		blocks++;
		break;
	}

	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[0 + SCREEN_Y]];
	for (i = 0; i < 4; i++) {
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[VIEWPORT_HEIGHT + SCREEN_Y]];
	for (i = 0; i < blocks; i++) {
		scrollrt_draw_lower(x, y, sx, sy, chunks, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower(x, y, sx, sy, chunks, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	arch_draw_type = 0;
	for (i = 0; i < 4; i++) {
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}
}

/**
 * @brief Configure render for zoomed view and process screen rows
 * @param x Center of view in dPiece coordinate
 * @param y Center of view in dPiece coordinate
 */
static void DrawZoom(int x, int y)
{
	int i, sx, sy, chunks, blocks;
	int wdt, nSrcOff, nDstOff;

	ViewDX = ZOOM_WIDTH;
	ViewDY = ZOOM_HEIGHT - 32;
	ViewBX = ZOOM_WIDTH / 64;
	ViewBY = (ZOOM_HEIGHT - 32) / 32;

	sx = ScrollInfo._sxoff + SCREEN_X;
	sy = ScrollInfo._syoff + SCREEN_Y - 17;
	x -= ZOOM_WIDTH / 64;
	y--;
	chunks = ZOOM_WIDTH / 64;
	blocks = 3;

	switch (ScrollInfo._sdir) {
	case SDIR_NE:
		chunks++;
	case SDIR_N:
		sy -= 32;
		x--;
		y--;
		blocks++;
		break;
	case SDIR_SE:
		blocks++;
	case SDIR_E:
		chunks++;
		break;
	case SDIR_S:
		blocks++;
		break;
	case SDIR_SW:
		blocks++;
	case SDIR_W:
		sx -= 64;
		x--;
		y++;
		chunks++;
		break;
	case SDIR_NW:
		sx -= 64;
		sy -= 32;
		x -= 2;
		chunks++;
		blocks++;
		break;
	}

	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[-17 + SCREEN_Y]];
	for (i = 0; i < 4; i++) {
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_upper(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[160 + SCREEN_Y]];
	for (i = 0; i < blocks; i++) {
		scrollrt_draw_lower(x, y, sx, sy, chunks, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower(x, y, sx, sy, chunks, 1);
		x++;
		sx += 32;
		sy += 16;
	}
	arch_draw_type = 0;
	for (i = 0; i < 4; i++) {
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= 32;
		sy += 16;
		scrollrt_draw_lower_2(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += 32;
		sy += 16;
	}

	if (chrflag || questlog) {
		nSrcOff = SCREENXY(112, VIEWPORT_HEIGHT / 2 - 17);
		nDstOff = SCREENXY(320, VIEWPORT_HEIGHT - 2);
		wdt = (SCREEN_WIDTH - 320) / 2;
	} else if (invflag || sbookflag) {
		nSrcOff = SCREENXY(112, VIEWPORT_HEIGHT / 2 - 17);
		nDstOff = SCREENXY(0, VIEWPORT_HEIGHT - 2);
		wdt = (SCREEN_WIDTH - 320) / 2;
	} else {
		nSrcOff = SCREENXY(32, VIEWPORT_HEIGHT / 2 - 17);
		nDstOff = SCREENXY(0, VIEWPORT_HEIGHT - 2);
		wdt = SCREEN_WIDTH / 2;
	}

	/// ASSERT: assert(gpBuffer);

#ifdef USE_ASM
	__asm {
		mov		esi, gpBuffer
		mov		edx, nDstOff
		mov		edi, esi
		mov		ecx, nSrcOff
		add		edi, edx
		add		esi, ecx
		mov		ebx, edi
		add		ebx, BUFFER_WIDTH
		mov		edx, (VIEWPORT_HEIGHT / 2)
	label1:
		mov		ecx, wdt
	label2:
		mov		al, [esi]
		inc		esi
		mov		ah, al
		mov		[edi], ax
		mov		[ebx], ax
		add		edi, 2
		add		ebx, 2
		dec		ecx
		jnz		label2
		mov		eax, BUFFER_WIDTH
		add		eax, wdt
		sub		esi, eax
		add		eax, eax
		sub		ebx, eax
		sub		edi, eax
		dec		edx
		jnz		label1
	}
#else
	int hgt;
	BYTE *src, *dst1, *dst2;

	src = &gpBuffer[nSrcOff];
	dst1 = &gpBuffer[nDstOff];
	dst2 = &gpBuffer[nDstOff + BUFFER_WIDTH];

	for (hgt = VIEWPORT_HEIGHT / 2; hgt != 0; hgt--, src -= BUFFER_WIDTH + wdt, dst1 -= 2 * (BUFFER_WIDTH + wdt), dst2 -= 2 * (BUFFER_WIDTH + wdt)) {
		for (i = wdt; i != 0; i--) {
			*dst1++ = *src;
			*dst1++ = *src;
			*dst2++ = *src;
			*dst2++ = *src;
			src++;
		}
	}
#endif
}

/**
 * @brief Start rendering of screen, town variation
 * @param StartX Center of view in dPiece coordinate
 * @param StartY Center of view in dPiece coordinate
 */
void DrawView(int StartX, int StartY)
{
	if (zoomflag) {
		DrawGame(StartX, StartY);
	} else {
		DrawZoom(StartX, StartY);
	}
	if (automapflag) {
		DrawAutomap();
	}
	if (invflag) {
		DrawInv();
	} else if (sbookflag) {
		DrawSpellBook();
	}

	DrawDurIcon();

	if (chrflag) {
		DrawChr();
	} else if (questlog) {
		DrawQuestLog();
	} else if (plr[myplr]._pStatPts != 0 && !spselflag) {
		DrawLevelUpIcon();
	}
	if (uitemflag) {
		DrawUniqueInfo();
	}
	if (qtextflag) {
		DrawQText();
	}
	if (spselflag) {
		DrawSpellList();
	}
	if (dropGoldFlag) {
		DrawGoldSplit(dropGoldValue);
	}
	if (helpflag) {
		DrawHelp();
	}
	if (msgflag) {
		DrawDiabloMsg();
	}
	if (deathflag) {
		RedBack();
	} else if (PauseMode != 0) {
		gmenu_draw_pause();
	}

	DrawPlrMsg();
	gmenu_draw();
	doom_draw();
	DrawInfoBox();
	DrawLifeFlask();
	DrawManaFlask();
}

/**
 * @brief Render the whole screen black
 */
void ClearScreenBuffer()
{
	lock_buf(3);

	/// ASSERT: assert(gpBuffer);

#ifdef USE_ASM
	__asm {
		mov		edi, gpBuffer
		add		edi, SCREENXY(0, 0)
		mov		edx, SCREEN_HEIGHT
		xor		eax, eax
	zeroline:
		mov		ecx, SCREEN_WIDTH / 4
		rep stosd
		add		edi, BUFFER_WIDTH - SCREEN_WIDTH
		dec		edx
		jnz		zeroline
	}
#else
	int i;
	BYTE *dst;

	dst = &gpBuffer[SCREENXY(0, 0)];

	for (i = 0; i < SCREEN_HEIGHT; i++, dst += BUFFER_WIDTH) {
		memset(dst, 0, SCREEN_WIDTH);
	}
#endif

	unlock_buf(3);
}

#ifdef _DEBUG
/**
 * @brief Scroll the screen when mouse is close to the edge
 */
void ScrollView()
{
	BOOL scroll;

	if (pcurs >= CURSOR_FIRSTITEM)
		return;

	scroll = FALSE;

	if (MouseX < 20) {
		if (dmaxy - 1 <= ViewY || dminx >= ViewX) {
			if (dmaxy - 1 > ViewY) {
				ViewY++;
				scroll = TRUE;
			}
			if (dminx < ViewX) {
				ViewX--;
				scroll = TRUE;
			}
		} else {
			ViewY++;
			ViewX--;
			scroll = TRUE;
		}
	}
	if (MouseX > SCREEN_WIDTH - 20) {
		if (dmaxx - 1 <= ViewX || dminy >= ViewY) {
			if (dmaxx - 1 > ViewX) {
				ViewX++;
				scroll = TRUE;
			}
			if (dminy < ViewY) {
				ViewY--;
				scroll = TRUE;
			}
		} else {
			ViewY--;
			ViewX++;
			scroll = TRUE;
		}
	}
	if (MouseY < 20) {
		if (dminy >= ViewY || dminx >= ViewX) {
			if (dminy < ViewY) {
				ViewY--;
				scroll = TRUE;
			}
			if (dminx < ViewX) {
				ViewX--;
				scroll = TRUE;
			}
		} else {
			ViewX--;
			ViewY--;
			scroll = TRUE;
		}
	}
	if (MouseY > SCREEN_HEIGHT - 20) {
		if (dmaxy - 1 <= ViewY || dmaxx - 1 <= ViewX) {
			if (dmaxy - 1 > ViewY) {
				ViewY++;
				scroll = TRUE;
			}
			if (dmaxx - 1 > ViewX) {
				ViewX++;
				scroll = TRUE;
			}
		} else {
			ViewX++;
			ViewY++;
			scroll = TRUE;
		}
	}

	if (scroll)
		ScrollInfo._sdir = SDIR_NONE;
}

/**
 * @brief Initialize the FPS meter
 */
void EnableFrameCount()
{
	frameflag = frameflag == 0;
	framestart = GetTickCount();
}

/**
 * @brief Display the current average FPS over 1 sec
 */
static void DrawFPS()
{
	DWORD tc, frames;
	char String[12];
	HDC hdc;

	if (frameflag && gbActive) {
		frameend++;
		tc = GetTickCount();
		frames = tc - framestart;
		if (tc - framestart >= 1000) {
			framestart = tc;
			framerate = 1000 * frameend / frames;
			frameend = 0;
		}
		if (framerate > 99)
			framerate = 99;
		wsprintf(String, "%2d", framerate);
		if (!lpDDSPrimary->GetDC(&hdc)) {
			TextOut(hdc, 0, 400, String, strlen(String));
			lpDDSPrimary->ReleaseDC(hdc);
		}
	}
}
#endif

/**
 * @brief Update part of the screen from the back buffer
 * @param dwX Back buffer coordinate
 * @param dwY Back buffer coordinate
 * @param dwWdt Back buffer coordinate
 * @param dwHgt Back buffer coordinate
 */
static void DoBlitScreen(DWORD dwX, DWORD dwY, DWORD dwWdt, DWORD dwHgt)
{
	int nSrcOff, nDstOff, nSrcWdt, nDstWdt;
	DWORD dwTicks;
	HRESULT hDDVal;
	RECT SrcRect;

	/// ASSERT: assert(! (dwX & 3));
	/// ASSERT: assert(! (dwWdt & 3));

	if (lpDDSBackBuf != NULL) {
		SrcRect.left = dwX + SCREEN_X;
		SrcRect.top = dwY + SCREEN_Y;
		SrcRect.right = SrcRect.left + dwWdt - 1;
		SrcRect.bottom = SrcRect.top + dwHgt - 1;
		/// ASSERT: assert(! gpBuffer);
		dwTicks = GetTickCount();
		while (1) {
#ifdef __cplusplus
			hDDVal = lpDDSPrimary->BltFast(dwX, dwY, lpDDSBackBuf, &SrcRect, DDBLTFAST_WAIT);
#else
			hDDVal = lpDDSPrimary->lpVtbl->BltFast(lpDDSPrimary, dwX, dwY, lpDDSBackBuf, &SrcRect, DDBLTFAST_WAIT);
#endif
			if (hDDVal == DD_OK) {
				break;
			}
			if (dwTicks - GetTickCount() > 5000) {
				break;
			}
			Sleep(1);
			if (hDDVal == DDERR_SURFACELOST) {
				return;
			}
			if (hDDVal != DDERR_WASSTILLDRAWING && hDDVal != DDERR_SURFACEBUSY) {
				break;
			}
		}
		if (hDDVal != DDERR_SURFACELOST
		    && hDDVal != DDERR_WASSTILLDRAWING
		    && hDDVal != DDERR_SURFACEBUSY
		    && hDDVal != DD_OK) {
			DDErrMsg(hDDVal, 3596, "C:\\Src\\Diablo\\Source\\SCROLLRT.CPP");
		}
	} else {
		nSrcOff = SCREENXY(dwX, dwY);
		nDstOff = dwX * (SCREEN_BPP / 8) + dwY * DDS_desc.lPitch;
		nSrcWdt = BUFFER_WIDTH - dwWdt;
		nDstWdt = DDS_desc.lPitch - dwWdt * (SCREEN_BPP / 8);
		dwWdt >>= 2;

		lock_buf(6);

		/// ASSERT: assert(gpBuffer);

#if defined(USE_ASM) && !defined(RGBMODE)
		__asm {
			mov		esi, gpBuffer
			mov		edi, DDS_desc.lpSurface
			add		esi, nSrcOff
			add		edi, nDstOff
			mov		eax, nSrcWdt
			mov		ebx, nDstWdt
			mov		edx, dwHgt
		blitline:
			mov		ecx, dwWdt
			rep movsd
			add		esi, eax
			add		edi, ebx
			dec		edx
			jnz		blitline
		}
#else
		int wdt, hgt;
		BYTE *src, *dst;

		src = &gpBuffer[nSrcOff];
		dst = (BYTE *)DDS_desc.lpSurface + nDstOff;

		for (hgt = 0; hgt < dwHgt; hgt++, src += nSrcWdt, dst += nDstWdt) {
			for (wdt = 0; wdt < 4 * dwWdt; wdt++) {
#ifndef RGBMODE
				*dst++ = *src++;
#else
				PALETTEENTRY pal = system_palette[*src++];
				dst[0] = pal.peBlue;
				dst[1] = pal.peGreen;
				dst[2] = pal.peRed;
				dst += 4;
#endif
			}
		}
#endif

		unlock_buf(6);
	}
}

/**
 * @brief Check render pipline and blit indivudal screen parts
 * @param dwHgt Section of screen to update from top to bottom
 * @param draw_desc Render info box
 * @param draw_hp Render halth bar
 * @param draw_mana Render mana bar
 * @param draw_sbar Render belt
 * @param draw_btn Render panel buttons
 */
static void DrawMain(int dwHgt, BOOL draw_desc, BOOL draw_hp, BOOL draw_mana, BOOL draw_sbar, BOOL draw_btn)
{
	int ysize;
	DWORD dwTicks;
	BOOL retry;
	HRESULT hDDVal;

	ysize = dwHgt;

	if (!gbActive || lpDDSPrimary == NULL) {
		return;
	}

#ifdef __cplusplus
	if (lpDDSPrimary->IsLost() == DDERR_SURFACELOST) {
		if (lpDDSPrimary->Restore() != DD_OK) {
			return;
		}
#else
	if (lpDDSPrimary->lpVtbl->IsLost(lpDDSPrimary) == DDERR_SURFACELOST) {
		if (lpDDSPrimary->lpVtbl->Restore(lpDDSPrimary) != DD_OK) {
			return;
		}
#endif
		ResetPal();
		ysize = SCREEN_HEIGHT;
	}

	if (lpDDSBackBuf == NULL) {
		retry = TRUE;
		dwTicks = GetTickCount();
		while (1) {
			DDS_desc.dwSize = sizeof(DDS_desc);
#ifdef __cplusplus
			hDDVal = lpDDSPrimary->Lock(NULL, &DDS_desc, DDLOCK_WRITEONLY | DDLOCK_WAIT, NULL);
#else
			hDDVal = lpDDSPrimary->lpVtbl->Lock(lpDDSPrimary, NULL, &DDS_desc, DDLOCK_WRITEONLY | DDLOCK_WAIT, NULL);
#endif
			if (hDDVal == DD_OK) {
				break;
			}
			if (dwTicks - GetTickCount() > 5000) {
				break;
			}
			Sleep(1);
			if (hDDVal == DDERR_SURFACELOST) {
				return;
			}
			if (hDDVal != DDERR_WASSTILLDRAWING && hDDVal != DDERR_SURFACEBUSY) {
				if (!retry || hDDVal != DDERR_GENERIC) {
					break;
				}
				retry = FALSE;
				j_dx_reinit();
				ysize = SCREEN_HEIGHT;
				dwTicks = GetTickCount();
			}
		}
		if (hDDVal == DDERR_SURFACELOST
		    || hDDVal == DDERR_WASSTILLDRAWING
		    || hDDVal == DDERR_SURFACEBUSY) {
			return;
		}
		if (hDDVal != DD_OK) {
			DDErrMsg(hDDVal, 3707, "C:\\Src\\Diablo\\Source\\SCROLLRT.CPP");
		}
	}

	/// ASSERT: assert(ysize >= 0 && ysize <= 480); // SCREEN_HEIGHT

	if (ysize > 0) {
		DoBlitScreen(0, 0, SCREEN_WIDTH, ysize);
	}
	if (ysize < SCREEN_HEIGHT) {
		if (draw_sbar) {
			DoBlitScreen(PANEL_LEFT + 204, PANEL_TOP + 5, 232, 28);
		}
		if (draw_desc) {
			DoBlitScreen(PANEL_LEFT + 176, PANEL_TOP + 46, 288, 60);
		}
		if (draw_mana) {
			DoBlitScreen(PANEL_LEFT + 460, PANEL_TOP, 88, 72);
			DoBlitScreen(PANEL_LEFT + 564, PANEL_TOP + 64, 56, 56);
		}
		if (draw_hp) {
			DoBlitScreen(PANEL_LEFT + 96, PANEL_TOP, 88, 72);
		}
		if (draw_btn) {
			DoBlitScreen(PANEL_LEFT + 8, PANEL_TOP + 5, 72, 119);
			DoBlitScreen(PANEL_LEFT + 556, PANEL_TOP + 5, 72, 48);
			if (gbMaxPlayers > 1) {
				DoBlitScreen(PANEL_LEFT + 84, PANEL_TOP + 91, 36, 32);
				DoBlitScreen(PANEL_LEFT + 524, PANEL_TOP + 91, 36, 32);
			}
		}
		if (sgdwCursWdtOld != 0) {
			DoBlitScreen(sgdwCursXOld, sgdwCursYOld, sgdwCursWdtOld, sgdwCursHgtOld);
		}
		if (sgdwCursWdt != 0) {
			DoBlitScreen(sgdwCursX, sgdwCursY, sgdwCursWdt, sgdwCursHgt);
		}
	}

	if (lpDDSBackBuf == NULL) {
#ifdef __cplusplus
		hDDVal = lpDDSPrimary->Unlock(NULL);
#else
		hDDVal = lpDDSPrimary->lpVtbl->Unlock(lpDDSPrimary, NULL);
#endif
		if (hDDVal != DDERR_SURFACELOST && hDDVal != DD_OK) {
			DDErrMsg(hDDVal, 3779, "C:\\Src\\Diablo\\Source\\SCROLLRT.CPP");
		}
	}

#ifdef _DEBUG
	DrawFPS();
#endif
}

/**
 * @brief Redraw screen
 * @param draw_cursor
 */
void scrollrt_draw_game_screen(BOOL draw_cursor)
{
	int hgt;

	if (force_redraw == 255) {
		force_redraw = 0;
		hgt = SCREEN_HEIGHT;
	} else {
		hgt = 0;
	}

	if (draw_cursor) {
		lock_buf(0);
		scrollrt_draw_cursor_item();
		unlock_buf(0);
	}

	DrawMain(hgt, 0, 0, 0, 0, 0);

	if (draw_cursor) {
		lock_buf(0);
		scrollrt_draw_cursor_back_buffer();
		unlock_buf(0);
	}
}

/**
 * @brief Render the game
 */
void DrawAndBlit()
{
	int hgt;
	BOOL ddsdesc, ctrlPan;

	if (!gbRunGame) {
		return;
	}

	if (force_redraw == 255) {
		drawhpflag = TRUE;
		drawmanaflag = TRUE;
		drawbtnflag = TRUE;
		drawsbarflag = TRUE;
		ddsdesc = FALSE;
		ctrlPan = TRUE;
		hgt = SCREEN_HEIGHT;
	} else if (force_redraw == 1) {
		ddsdesc = TRUE;
		ctrlPan = FALSE;
		hgt = VIEWPORT_HEIGHT;
	} else {
		return;
	}

	force_redraw = 0;

	lock_buf(0);
	if (leveltype != DTYPE_TOWN) {
		DrawView(ViewX, ViewY);
	} else {
		T_DrawView(ViewX, ViewY);
	}
	if (ctrlPan) {
		DrawCtrlPan();
	}
	if (drawhpflag) {
		UpdateLifeFlask();
	}
	if (drawmanaflag) {
		UpdateManaFlask();
	}
	if (drawbtnflag) {
		DrawCtrlBtns();
	}
	if (drawsbarflag) {
		DrawInvBelt();
	}
	if (talkflag) {
		DrawTalkPan();
		hgt = SCREEN_HEIGHT;
	}
	scrollrt_draw_cursor_item();
	unlock_buf(0);

	DrawMain(hgt, ddsdesc, drawhpflag, drawmanaflag, drawsbarflag, drawbtnflag);

	lock_buf(0);
	scrollrt_draw_cursor_back_buffer();
	unlock_buf(0);

	drawhpflag = FALSE;
	drawmanaflag = FALSE;
	drawbtnflag = FALSE;
	drawsbarflag = FALSE;
}
