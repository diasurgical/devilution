/**
 * @file gendung.cpp
 *
 * Implementation of general dungeon generation code.
 */
#include "all.h"

/** Contains the tile IDs of the map. */
BYTE dungeon[DMAXX][DMAXY];
/** Contains a backup of the tile IDs of the map. */
BYTE pdungeon[DMAXX][DMAXY];
char dflags[DMAXX][DMAXY];
/** Specifies the active set level X-coordinate of the map. */
int setpc_x;
/** Specifies the active set level Y-coordinate of the map. */
int setpc_y;
/** Specifies the width of the active set level of the map. */
int setpc_w;
/** Specifies the height of the active set level of the map. */
int setpc_h;
/** Contains the contents of the single player quest DUN file. */
BYTE *pSetPiece;
/** Specifies whether a single player quest DUN has been loaded. */
BOOL setloadflag;
BYTE *pSpecialCels;
/** Specifies the tile definitions of the active dungeon type; (e.g. levels/l1data/l1.til). */
BYTE *pMegaTiles;
BYTE *pLevelPieces;
BYTE *pDungeonCels;
BYTE *pSpeedCels;
/**
 * Returns the frame number of the speed CEL, an in memory decoding
 * of level CEL frames, based on original frame number and light index.
 * Note, given light index 0, the original frame number is returned.
 */
int SpeedFrameTbl[128][16];
/**
 * List of transparancy masks to use for dPieces
 */
char block_lvid[MAXTILES + 1];
/** Specifies the CEL frame occurrence for each frame of the level CEL (e.g. "levels/l1data/l1.cel"). */
int level_frame_count[MAXTILES];
int tile_defs[MAXTILES];
/**
 * Secifies the CEL frame decoder type for each frame of the
 * level CEL (e.g. "levels/l1data/l1.cel"), Indexed by frame numbers starting at 1.
 * The decoder type may be one of the following.
 *  0x0000 - cel.decodeType0
 *  0x1000 - cel.decodeType1
 *  0x2000 - cel.decodeType2
 *  0x3000 - cel.decodeType3
 *  0x4000 - cel.decodeType4
 *  0x5000 - cel.decodeType5
 *  0x6000 - cel.decodeType6
 */
WORD level_frame_types[MAXTILES];
/**
 * Specifies the size of each frame of the level cel (e.g.
 * "levels/l1data/l1.cel"). Indexed by frame numbers starting at 1.
 */
int level_frame_sizes[MAXTILES];
/** Specifies the number of frames in the level cel (e.g. "levels/l1data/l1.cel"). */
int nlevel_frames;
/**
 * List of light blocking dPieces
 */
BOOLEAN nBlockTable[MAXTILES + 1];
/**
 * List of path blocking dPieces
 */
BOOLEAN nSolidTable[MAXTILES + 1];
/**
 * List of transparent dPieces
 */
BOOLEAN nTransTable[MAXTILES + 1];
/**
 * List of missile blocking dPieces
 */
BOOLEAN nMissileTable[MAXTILES + 1];
BOOLEAN nTrapTable[MAXTILES + 1];
/** Specifies the minimum X-coordinate of the map. */
int dminx;
/** Specifies the minimum Y-coordinate of the map. */
int dminy;
/** Specifies the maximum X-coordinate of the map. */
int dmaxx;
/** Specifies the maximum Y-coordinate of the map. */
int dmaxy;
int gnDifficulty;
/** Specifies the active dungeon type of the current game. */
BYTE leveltype;
/** Specifies the active dungeon level of the current game. */
BYTE currlevel;
BOOLEAN setlevel;
/** Specifies the active quest level of the current game. */
BYTE setlvlnum;
char setlvltype;
/** Specifies the player viewpoint X-coordinate of the map. */
int ViewX;
/** Specifies the player viewpoint Y-coordinate of the map. */
int ViewY;
int ViewBX;
int ViewBY;
int ViewDX;
int ViewDY;
ScrollStruct ScrollInfo;
/** Specifies the level viewpoint X-coordinate of the map. */
int LvlViewX;
/** Specifies the level viewpoint Y-coordinate of the map. */
int LvlViewY;
int MicroTileLen;
char TransVal;
/** Specifies the active transparency indices. */
BOOLEAN TransList[256];
/** Contains the piece IDs of each tile on the map. */
int dPiece[MAXDUNX][MAXDUNY];
/** Specifies the dungeon piece information for a given coordinate and block number. */
MICROS dpiece_defs_map_2[MAXDUNX][MAXDUNY];
/** Specifies the dungeon piece information for a given coordinate and block number, optimized for diagonal access. */
MICROS dpiece_defs_map_1[MAXDUNX * MAXDUNY];
/** Specifies the transparency at each coordinate of the map. */
char dTransVal[MAXDUNX][MAXDUNY];
char dLight[MAXDUNX][MAXDUNY];
char dPreLight[MAXDUNX][MAXDUNY];
char dFlags[MAXDUNX][MAXDUNY];
/** Contains the player numbers (players array indices) of the map. */
char dPlayer[MAXDUNX][MAXDUNY];
/**
 * Contains the NPC numbers of the map. The NPC number represents a
 * towner number (towners array index) in Tristram and a monster number
 * (monsters array index) in the dungeon.
 */
int dMonster[MAXDUNX][MAXDUNY];
/**
 * Contains the dead numbers (deads array indices) and dead direction of
 * the map, encoded as specified by the pseudo-code below.
 * dDead[x][y] & 0x1F - index of dead
 * dDead[x][y] >> 0x5 - direction
 */
char dDead[MAXDUNX][MAXDUNY];
/** Contains the object numbers (objects array indices) of the map. */
char dObject[MAXDUNX][MAXDUNY];
/** Contains the item numbers (items array indices) of the map. */
char dItem[MAXDUNX][MAXDUNY];
/** Contains the missile numbers (missiles array indices) of the map. */
char dMissile[MAXDUNX][MAXDUNY];
/**
 * Contains the arch frame numbers of the map from the special tileset
 * (e.g. "levels/l1data/l1s.cel"). Note, the special tileset of Tristram (i.e.
 * "levels/towndata/towns.cel") contains trees rather than arches.
 */
char dSpecial[MAXDUNX][MAXDUNY];
int themeCount;
THEME_LOC themeLoc[MAXTHEMES];

void FillSolidBlockTbls()
{
	BYTE bv;
	DWORD dwTiles;
	BYTE *pSBFile, *pTmp;
	int i;

	memset(nBlockTable, 0, sizeof(nBlockTable));
	memset(nSolidTable, 0, sizeof(nSolidTable));
	memset(nTransTable, 0, sizeof(nTransTable));
	memset(nMissileTable, 0, sizeof(nMissileTable));
	memset(nTrapTable, 0, sizeof(nTrapTable));

	switch (leveltype) {
	case DTYPE_TOWN:
#ifdef HELLFIRE
		pSBFile = LoadFileInMem("NLevels\\TownData\\Town.SOL", &dwTiles);
#else
		pSBFile = LoadFileInMem("Levels\\TownData\\Town.SOL", &dwTiles);
#endif
		break;
	case DTYPE_CATHEDRAL:
#ifdef HELLFIRE
		if (currlevel < 17)
			pSBFile = LoadFileInMem("Levels\\L1Data\\L1.SOL", &dwTiles);
		else
			pSBFile = LoadFileInMem("NLevels\\L5Data\\L5.SOL", &dwTiles);
#else
		pSBFile = LoadFileInMem("Levels\\L1Data\\L1.SOL", &dwTiles);
#endif
		break;
	case DTYPE_CATACOMBS:
		pSBFile = LoadFileInMem("Levels\\L2Data\\L2.SOL", &dwTiles);
		break;
	case DTYPE_CAVES:
#ifdef HELLFIRE
		if (currlevel < 17)
			pSBFile = LoadFileInMem("Levels\\L3Data\\L3.SOL", &dwTiles);
		else
			pSBFile = LoadFileInMem("NLevels\\L6Data\\L6.SOL", &dwTiles);
#else
		pSBFile = LoadFileInMem("Levels\\L3Data\\L3.SOL", &dwTiles);
#endif
		break;
	case DTYPE_HELL:
		pSBFile = LoadFileInMem("Levels\\L4Data\\L4.SOL", &dwTiles);
		break;
	default:
		app_fatal("FillSolidBlockTbls");
	}

	pTmp = pSBFile;

	for (i = 1; i <= dwTiles; i++) {
		bv = *pTmp++;
		if (bv & 1)
			nSolidTable[i] = TRUE;
		if (bv & 2)
			nBlockTable[i] = TRUE;
		if (bv & 4)
			nMissileTable[i] = TRUE;
		if (bv & 8)
			nTransTable[i] = TRUE;
		if (bv & 0x80)
			nTrapTable[i] = TRUE;
		block_lvid[i] = (bv & 0x70) >> 4; /* beta: (bv >> 4) & 7 */
	}

	mem_free_dbg(pSBFile);
}

static void SwapTile(int f1, int f2)
{
	int swap;

	swap = level_frame_count[f1];
	level_frame_count[f1] = level_frame_count[f2];
	level_frame_count[f2] = swap;
	swap = tile_defs[f1];
	tile_defs[f1] = tile_defs[f2];
	tile_defs[f2] = swap;
	swap = level_frame_types[f1];
	level_frame_types[f1] = level_frame_types[f2];
	level_frame_types[f2] = swap;
	swap = level_frame_sizes[f1];
	level_frame_sizes[f1] = level_frame_sizes[f2];
	level_frame_sizes[f2] = swap;
}

static void SortTiles(int frames)
{
	int i;
	BOOL doneflag;

	doneflag = FALSE;
	while (frames > 0 && !doneflag) {
		doneflag = TRUE;
		for (i = 0; i < frames; i++) {
			if (level_frame_count[i] < level_frame_count[i + 1]) {
				SwapTile(i, i + 1);
				doneflag = FALSE;
			}
		}
		frames--;
	}
}

void MakeSpeedCels()
{
	int i, j, x, y, mt, t, z;
	int total_frames, blocks, total_size, frameidx, blk_cnt, nDataSize;
	WORD m;
	BOOL blood_flag;
	DWORD *pFrameTable;
	MICROS *pMap;
#ifndef USE_ASM
	int l, k;
	BYTE width, pix;
	BYTE *src, *dst, *tbl;
#endif

	for (i = 0; i < MAXTILES; i++) {
		tile_defs[i] = i;
		level_frame_count[i] = 0;
		level_frame_types[i] = 0;
	}

	if (leveltype != DTYPE_HELL)
		blocks = 10;
	else
		blocks = 12;

	for (y = 0; y < MAXDUNY; y++) {
		for (x = 0; x < MAXDUNX; x++) {
			pMap = &dpiece_defs_map_2[x][y];
			for (j = 0; j < blocks; j++) {
				mt = pMap->mt[j];
				if (mt) {
					level_frame_count[pMap->mt[j] & 0xFFF]++;
					level_frame_types[pMap->mt[j] & 0xFFF] = mt & 0x7000;
				}
			}
		}
	}

#if defined HELLFIRE && defined USE_ASM
	__asm {
		mov		ebx, pDungeonCels
		mov		eax, [ebx]
		mov		nDataSize, eax
	}
#else
	pFrameTable = (DWORD *)pDungeonCels;
	nDataSize = pFrameTable[0];
#endif
	nlevel_frames = nDataSize & 0xFFFF;

#ifdef HELLFIRE
	for (i = 0; i < nlevel_frames; i++) {
#else
	for (i = 1; i < nlevel_frames; i++) {
#endif
		z = i;
#ifdef USE_ASM
		__asm {
			mov		ebx, pDungeonCels
			mov		eax, z
			shl		eax, 2
			add		ebx, eax
			mov		eax, [ebx+4]
			sub		eax, [ebx]
			mov		nDataSize, eax
		}
#else
		nDataSize = pFrameTable[i + 1] - pFrameTable[i];
#endif
		level_frame_sizes[i] = nDataSize & 0xFFFF;
	}

	level_frame_sizes[0] = 0;

	if (leveltype == DTYPE_HELL) {
		for (i = 0; i < nlevel_frames; i++) {
#ifndef HELLFIRE
			if (i == 0)
				level_frame_count[0] = 0;
#endif
			z = i;
			blood_flag = TRUE;
			if (level_frame_count[i] != 0) {
				if (level_frame_types[i] != 0x1000) {
#ifdef USE_ASM
					t = level_frame_sizes[i];
					__asm {
						mov		ebx, pDungeonCels
						mov		eax, z
						shl		eax, 2
						add		ebx, eax
						mov		esi, pDungeonCels
						add		esi, [ebx]
						xor		ebx, ebx
						mov		ecx, t
						jecxz	l1_label3
					l1_label1:
						lodsb
						cmp		al, 0
						jz		l1_label2
						cmp		al, 32
						jnb		l1_label2
						mov		blood_flag, ebx
					l1_label2:
						loop	l1_label1
					l1_label3:
						nop
					}
#else
					src = &pDungeonCels[pFrameTable[i]];
					for (j = level_frame_sizes[i]; j; j--) {
						pix = *src++;
						if (pix && pix < 32)
							blood_flag = FALSE;
					}
#endif
				} else {
#ifdef USE_ASM
					__asm {
						mov		ebx, pDungeonCels
						mov		eax, z
						shl		eax, 2
						add		ebx, eax
						mov		esi, pDungeonCels
						add		esi, [ebx]
						xor		ebx, ebx
						mov		ecx, 32
					l2_label1:
						push	ecx
						mov		edx, 32
					l2_label2:
						xor		eax, eax
						lodsb
						or		al, al
						js		l2_label5
						sub		edx, eax
						mov		ecx, eax
					l2_label3:
						lodsb
						cmp		al, 0
						jz		l2_label4
						cmp		al, 32
						jnb		l2_label4
						mov		blood_flag, ebx
					l2_label4:
						loop	l2_label3
						or		edx, edx
						jz		l2_label6
						jmp		l2_label2
					l2_label5:
						neg		al
						sub		edx, eax
						jnz		l2_label2
					l2_label6:
						pop		ecx
						loop	l2_label1
					}
#else
					src = &pDungeonCels[pFrameTable[i]];
					for (k = 32; k; k--) {
						for (l = 32; l;) {
							width = *src++;
							if (!(width & 0x80)) {
								l -= width;
								while (width) {
									pix = *src++;
									if (pix && pix < 32)
										blood_flag = FALSE;
									width--;
								}
							} else {
								width = -(char)width;
								l -= width;
							}
						}
					}
#endif
				}
				if (!blood_flag)
					level_frame_count[i] = 0;
			}
		}
	}

	SortTiles(MAXTILES - 1);
	total_size = 0;
	total_frames = 0;

	if (light4flag) {
		while (total_size < 0x100000) {
			total_size += level_frame_sizes[total_frames] << 1;
			total_frames++;
		}
	} else {
		while (total_size < 0x100000) {
			total_size += (level_frame_sizes[total_frames] << 4) - (level_frame_sizes[total_frames] << 1);
			total_frames++;
		}
	}

	total_frames--;
	if (total_frames > 128)
		total_frames = 128;

	frameidx = 0;

	if (light4flag)
		blk_cnt = 3;
	else
		blk_cnt = 15;

	for (i = 0; i < total_frames; i++) {
		z = tile_defs[i];
		SpeedFrameTbl[i][0] = z;
		if (level_frame_types[i] != 0x1000) {
			t = level_frame_sizes[i];
			for (j = 1; j < blk_cnt; j++) {
				SpeedFrameTbl[i][j] = frameidx;
#ifdef USE_ASM
				__asm {
					mov		ebx, pDungeonCels
					mov		eax, z
					shl		eax, 2
					add		ebx, eax
					mov		esi, pDungeonCels
					add		esi, [ebx]
					mov		edi, pSpeedCels
					add		edi, frameidx
					mov		ebx, j
					shl		ebx, 8
					add		ebx, pLightTbl
					mov		ecx, t
					jecxz	l3_label2
				l3_label1:
					lodsb
					xlat
					stosb
					loop	l3_label1
				l3_label2:
					nop
				}
#else
				src = &pDungeonCels[pFrameTable[z]];
				dst = &pSpeedCels[frameidx];
				tbl = &pLightTbl[256 * j];
				for (k = t; k; k--) {
					*dst++ = tbl[*src++];
				}
#endif
				frameidx += t;
			}
		} else {
			for (j = 1; j < blk_cnt; j++) {
				SpeedFrameTbl[i][j] = frameidx;
#ifdef USE_ASM
				__asm {
					mov		ebx, pDungeonCels
					mov		eax, z
					shl		eax, 2
					add		ebx, eax
					mov		esi, pDungeonCels
					add		esi, [ebx]
					mov		edi, pSpeedCels
					add		edi, frameidx
					mov		ebx, j
					shl		ebx, 8
					add		ebx, pLightTbl
					mov		ecx, 32
				l4_label1:
					push	ecx
					mov		edx, 32
				l4_label2:
					xor		eax, eax
					lodsb
					stosb
					or		al, al
					js		l4_label4
					sub		edx, eax
					mov		ecx, eax
				l4_label3:
					lodsb
					xlat
					stosb
					loop	l4_label3
					or		edx, edx
					jz		l4_label5
					jmp		l4_label2
				l4_label4:
					neg		al
					sub		edx, eax
					jnz		l4_label2
				l4_label5:
					pop		ecx
					loop	l4_label1
				}
#else
				src = &pDungeonCels[pFrameTable[z]];
				dst = &pSpeedCels[frameidx];
				tbl = &pLightTbl[256 * j];
				for (k = 32; k; k--) {
					for (l = 32; l;) {
						width = *src++;
						*dst++ = width;
						if (!(width & 0x80)) {
							l -= width;
							while (width) {
								*dst++ = tbl[*src++];
								width--;
							}
						} else {
							width = -(char)width;
							l -= width;
						}
					}
				}
#endif
				frameidx += level_frame_sizes[i];
			}
		}
	}

	for (y = 0; y < MAXDUNY; y++) {
		for (x = 0; x < MAXDUNX; x++) {
			if (dPiece[x][y] != 0) {
				pMap = &dpiece_defs_map_2[x][y];
				for (i = 0; i < blocks; i++) {
					if (pMap->mt[i]) {
						for (m = 0; m < total_frames; m++) {
							if ((pMap->mt[i] & 0xFFF) == tile_defs[m]) {
								pMap->mt[i] = m + level_frame_types[m] + 0x8000;
								m = total_frames;
							}
						}
					}
				}
			}
		}
	}
}

int IsometricCoord(int x, int y)
{
	if (x < MAXDUNY - y)
		return (y + y * y + x * (x + 2 * y + 3)) / 2;

	x = MAXDUNX - x - 1;
	y = MAXDUNY - y - 1;
	return MAXDUNX * MAXDUNY - ((y + y * y + x * (x + 2 * y + 3)) / 2) - 1;
}

void SetSpeedCels()
{
	int x, y;

	for (x = 0; x < MAXDUNX; x++) {
		for (y = 0; y < MAXDUNY; y++) {
			dpiece_defs_map_1[IsometricCoord(x, y)] = dpiece_defs_map_2[x][y];
		}
	}
}

void SetDungeonMicros()
{
	int i, x, y, lv, blocks;
	WORD *pPiece;
	MICROS *pMap;

	if (leveltype != DTYPE_HELL) {
		MicroTileLen = 10;
		blocks = 10;
	} else {
		MicroTileLen = 12;
		blocks = 16;
	}

	for (y = 0; y < MAXDUNY; y++) {
		for (x = 0; x < MAXDUNX; x++) {
			lv = dPiece[x][y];
			pMap = &dpiece_defs_map_2[x][y];
			if (lv != 0) {
				lv--;
				if (leveltype != DTYPE_HELL)
					pPiece = (WORD *)&pLevelPieces[20 * lv];
				else
					pPiece = (WORD *)&pLevelPieces[32 * lv];
				for (i = 0; i < blocks; i++)
					pMap->mt[i] = pPiece[(i & 1) + blocks - 2 - (i & 0xE)];
			} else {
				for (i = 0; i < blocks; i++)
					pMap->mt[i] = 0;
			}
		}
	}

	MakeSpeedCels();
	SetSpeedCels();

	if (zoomflag) {
		ViewDX = SCREEN_WIDTH;
		ViewDY = VIEWPORT_HEIGHT;
		ViewBX = SCREEN_WIDTH / TILE_WIDTH;
		ViewBY = VIEWPORT_HEIGHT / TILE_HEIGHT;
	} else {
		ViewDX = ZOOM_WIDTH;
		ViewDY = ZOOM_HEIGHT;
		ViewBX = ZOOM_WIDTH / TILE_WIDTH;
		ViewBY = ZOOM_HEIGHT / TILE_HEIGHT;
	}
}

void DRLG_InitTrans()
{
	memset(dTransVal, 0, sizeof(dTransVal));
	memset(TransList, 0, sizeof(TransList));
	TransVal = 1;
}

void DRLG_MRectTrans(int x1, int y1, int x2, int y2)
{
	int i, j;

	x1 = 2 * x1 + 17;
	y1 = 2 * y1 + 17;
	x2 = 2 * x2 + 16;
	y2 = 2 * y2 + 16;

	for (j = y1; j <= y2; j++) {
		for (i = x1; i <= x2; i++) {
			dTransVal[i][j] = TransVal;
		}
	}

	TransVal++;
}

void DRLG_RectTrans(int x1, int y1, int x2, int y2)
{
	int i, j;

	for (j = y1; j <= y2; j++) {
		for (i = x1; i <= x2; i++) {
			dTransVal[i][j] = TransVal;
		}
	}
	TransVal++;
}

void DRLG_CopyTrans(int sx, int sy, int dx, int dy)
{
	dTransVal[dx][dy] = dTransVal[sx][sy];
}

#ifndef SPAWN
void DRLG_ListTrans(int num, BYTE *List)
{
	int i;
	BYTE x1, y1, x2, y2;

	for (i = 0; i < num; i++) {
		x1 = *List++;
		y1 = *List++;
		x2 = *List++;
		y2 = *List++;
		DRLG_RectTrans(x1, y1, x2, y2);
	}
}

void DRLG_AreaTrans(int num, BYTE *List)
{
	int i;
	BYTE x1, y1, x2, y2;

	for (i = 0; i < num; i++) {
		x1 = *List++;
		y1 = *List++;
		x2 = *List++;
		y2 = *List++;
		DRLG_RectTrans(x1, y1, x2, y2);
		TransVal--;
	}
	TransVal++;
}
#endif

void DRLG_InitSetPC()
{
	setpc_x = 0;
	setpc_y = 0;
	setpc_w = 0;
	setpc_h = 0;
}

void DRLG_SetPC()
{
	int i, j, x, y, w, h;

	w = 2 * setpc_w;
	h = 2 * setpc_h;
	x = 2 * setpc_x + 16;
	y = 2 * setpc_y + 16;

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			dFlags[i + x][j + y] |= BFLAG_POPULATED;
		}
	}
}

#ifndef SPAWN
void Make_SetPC(int x, int y, int w, int h)
{
	int i, j, dx, dy, dh, dw;

	dw = 2 * w;
	dh = 2 * h;
	dx = 2 * x + 16;
	dy = 2 * y + 16;

	for (j = 0; j < dh; j++) {
		for (i = 0; i < dw; i++) {
			dFlags[i + dx][j + dy] |= BFLAG_POPULATED;
		}
	}
}

BOOL DRLG_WillThemeRoomFit(int floor, int x, int y, int minSize, int maxSize, int *width, int *height)
{
	int ii, xx, yy;
	int xSmallest, ySmallest;
	int xArray[20], yArray[20];
	int xCount, yCount;
	BOOL yFlag, xFlag;

	yFlag = TRUE;
	xFlag = TRUE;
	xCount = 0;
	yCount = 0;

	// BUGFIX: change '&&' to '||'
	if (x > DMAXX - maxSize && y > DMAXY - maxSize) {
		return FALSE;
	}
	if (!SkipThemeRoom(x, y)) {
		return FALSE;
	}

	memset(xArray, 0, sizeof(xArray));
	memset(yArray, 0, sizeof(yArray));

	for (ii = 0; ii < maxSize; ii++) {
		if (xFlag) {
			for (xx = x; xx < x + maxSize; xx++) {
				if (dungeon[xx][y + ii] != floor) {
					if (xx >= minSize) {
						break;
					}
					xFlag = FALSE;
				} else {
					xCount++;
				}
			}
			if (xFlag) {
				xArray[ii] = xCount;
				xCount = 0;
			}
		}
		if (yFlag) {
			for (yy = y; yy < y + maxSize; yy++) {
				if (dungeon[x + ii][yy] != floor) {
					if (yy >= minSize) {
						break;
					}
					yFlag = FALSE;
				} else {
					yCount++;
				}
			}
			if (yFlag) {
				yArray[ii] = yCount;
				yCount = 0;
			}
		}
	}

	for (ii = 0; ii < minSize; ii++) {
		if (xArray[ii] < minSize || yArray[ii] < minSize) {
			return FALSE;
		}
	}

	xSmallest = xArray[0];
	ySmallest = yArray[0];

	for (ii = 0; ii < maxSize; ii++) {
		if (xArray[ii] < minSize || yArray[ii] < minSize) {
			break;
		}
		if (xArray[ii] < xSmallest) {
			xSmallest = xArray[ii];
		}
		if (yArray[ii] < ySmallest) {
			ySmallest = yArray[ii];
		}
	}

	*width = xSmallest - 2;
	*height = ySmallest - 2;
	return TRUE;
}

void DRLG_CreateThemeRoom(int themeIndex)
{
	int xx, yy;

	for (yy = themeLoc[themeIndex].y; yy < themeLoc[themeIndex].y + themeLoc[themeIndex].height; yy++) {
		for (xx = themeLoc[themeIndex].x; xx < themeLoc[themeIndex].x + themeLoc[themeIndex].width; xx++) {
			if (leveltype == DTYPE_CATACOMBS) {
				if (yy == themeLoc[themeIndex].y
				        && xx >= themeLoc[themeIndex].x
				        && xx <= themeLoc[themeIndex].x + themeLoc[themeIndex].width
				    || yy == themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1
				        && xx >= themeLoc[themeIndex].x
				        && xx <= themeLoc[themeIndex].x + themeLoc[themeIndex].width) {
					dungeon[xx][yy] = 2;
				} else if (xx == themeLoc[themeIndex].x
				        && yy >= themeLoc[themeIndex].y
				        && yy <= themeLoc[themeIndex].y + themeLoc[themeIndex].height
				    || xx == themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1
				        && yy >= themeLoc[themeIndex].y
				        && yy <= themeLoc[themeIndex].y + themeLoc[themeIndex].height) {
					dungeon[xx][yy] = 1;
				} else {
					dungeon[xx][yy] = 3;
				}
			}
			if (leveltype == DTYPE_CAVES) {
				if (yy == themeLoc[themeIndex].y
				        && xx >= themeLoc[themeIndex].x
				        && xx <= themeLoc[themeIndex].x + themeLoc[themeIndex].width
				    || yy == themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1
				        && xx >= themeLoc[themeIndex].x
				        && xx <= themeLoc[themeIndex].x + themeLoc[themeIndex].width) {
					dungeon[xx][yy] = 134;
				} else if (xx == themeLoc[themeIndex].x
				        && yy >= themeLoc[themeIndex].y
				        && yy <= themeLoc[themeIndex].y + themeLoc[themeIndex].height
				    || xx == themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1
				        && yy >= themeLoc[themeIndex].y
				        && yy <= themeLoc[themeIndex].y + themeLoc[themeIndex].height) {
					dungeon[xx][yy] = 137;
				} else {
					dungeon[xx][yy] = 7;
				}
			}
			if (leveltype == DTYPE_HELL) {
				if (yy == themeLoc[themeIndex].y
				        && xx >= themeLoc[themeIndex].x
				        && xx <= themeLoc[themeIndex].x + themeLoc[themeIndex].width
				    || yy == themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1
				        && xx >= themeLoc[themeIndex].x
				        && xx <= themeLoc[themeIndex].x + themeLoc[themeIndex].width) {
					dungeon[xx][yy] = 2;
				} else if (xx == themeLoc[themeIndex].x
				        && yy >= themeLoc[themeIndex].y
				        && yy <= themeLoc[themeIndex].y + themeLoc[themeIndex].height
				    || xx == themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1
				        && yy >= themeLoc[themeIndex].y
				        && yy <= themeLoc[themeIndex].y + themeLoc[themeIndex].height) {
					dungeon[xx][yy] = 1;
				} else {
					dungeon[xx][yy] = 6;
				}
			}
		}
	}

	if (leveltype == DTYPE_CATACOMBS) {
		dungeon[themeLoc[themeIndex].x][themeLoc[themeIndex].y] = 8;
		dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y] = 7;
		dungeon[themeLoc[themeIndex].x][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 9;
		dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 6;
	}
	if (leveltype == DTYPE_CAVES) {
		dungeon[themeLoc[themeIndex].x][themeLoc[themeIndex].y] = 150;
		dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y] = 151;
		dungeon[themeLoc[themeIndex].x][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 152;
		dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 138;
	}
	if (leveltype == DTYPE_HELL) {
		dungeon[themeLoc[themeIndex].x][themeLoc[themeIndex].y] = 9;
		dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y] = 16;
		dungeon[themeLoc[themeIndex].x][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 15;
		dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 12;
	}

	if (leveltype == DTYPE_CATACOMBS) {
		switch (random_(0, 2)) {
		case 0:
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height / 2] = 4;
			break;
		case 1:
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 5;
			break;
		}
	}
	if (leveltype == DTYPE_CAVES) {
		switch (random_(0, 2)) {
		case 0:
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height / 2] = 147;
			break;
		case 1:
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 146;
			break;
		}
	}
	if (leveltype == DTYPE_HELL) {
		switch (random_(0, 2)) {
		case 0:
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height / 2 - 1] = 53;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height / 2] = 6;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height / 2 + 1] = 52;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width - 2][themeLoc[themeIndex].y + themeLoc[themeIndex].height / 2 - 1] = 54;
			break;
		case 1:
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2 - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 57;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 6;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2 + 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 1] = 56;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 2] = 59;
			dungeon[themeLoc[themeIndex].x + themeLoc[themeIndex].width / 2 - 1][themeLoc[themeIndex].y + themeLoc[themeIndex].height - 2] = 58;
			break;
		}
	}
}

void DRLG_PlaceThemeRooms(int minSize, int maxSize, int floor, int freq, int rndSize)
{
	int i, j;
	int themeW, themeH;
	int rv2, min, max;

	themeCount = 0;
	memset(themeLoc, 0, sizeof(*themeLoc));
	for (j = 0; j < DMAXY; j++) {
		for (i = 0; i < DMAXX; i++) {
			if (dungeon[i][j] == floor && !random_(0, freq) && DRLG_WillThemeRoomFit(floor, i, j, minSize, maxSize, &themeW, &themeH)) {
				if (rndSize) {
					min = minSize - 2;
					max = maxSize - 2;
					rv2 = min + random_(0, random_(0, themeW - min + 1));
					if (rv2 >= min && rv2 <= max)
						themeW = rv2;
					else
						themeW = min;
					rv2 = min + random_(0, random_(0, themeH - min + 1));
					if (rv2 >= min && rv2 <= max)
						themeH = rv2;
					else
						themeH = min;
				}
				themeLoc[themeCount].x = i + 1;
				themeLoc[themeCount].y = j + 1;
				themeLoc[themeCount].width = themeW;
				themeLoc[themeCount].height = themeH;
				if (leveltype == DTYPE_CAVES)
					DRLG_RectTrans(2 * i + 20, 2 * j + 20, 2 * (i + themeW) + 15, 2 * (j + themeH) + 15);
				else
					DRLG_MRectTrans(i + 1, j + 1, i + themeW, j + themeH);
				themeLoc[themeCount].ttval = TransVal - 1;
				DRLG_CreateThemeRoom(themeCount);
				themeCount++;
			}
		}
	}
}
#endif

void DRLG_HoldThemeRooms()
{
	int i, x, y, xx, yy;

	for (i = 0; i < themeCount; i++) {
		for (y = themeLoc[i].y; y < themeLoc[i].y + themeLoc[i].height - 1; y++) {
			for (x = themeLoc[i].x; x < themeLoc[i].x + themeLoc[i].width - 1; x++) {
				xx = 2 * x + 16;
				yy = 2 * y + 16;
				dFlags[xx][yy] |= BFLAG_POPULATED;
				dFlags[xx + 1][yy] |= BFLAG_POPULATED;
				dFlags[xx][yy + 1] |= BFLAG_POPULATED;
				dFlags[xx + 1][yy + 1] |= BFLAG_POPULATED;
			}
		}
	}
}

BOOL SkipThemeRoom(int x, int y)
{
	int i;

	for (i = 0; i < themeCount; i++) {
		if (x >= themeLoc[i].x - 2 && x <= themeLoc[i].x + themeLoc[i].width + 2
		    && y >= themeLoc[i].y - 2 && y <= themeLoc[i].y + themeLoc[i].height + 2)
			return FALSE;
	}

	return TRUE;
}

void InitLevels()
{
	if (!leveldebug) {
		currlevel = 0;
		leveltype = DTYPE_TOWN;
		setlevel = FALSE;
	}
}
