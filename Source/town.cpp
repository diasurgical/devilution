//HEADER_GOES_HERE

#include "../types.h"

void __fastcall town_clear_upper_buf(BYTE *pBuff)
{
	/// ASSERT: assert(gpBuffer);

#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
	__asm {
		mov		edi, pBuff
		mov		edx, 30
		mov		ebx, 1
		xor		eax, eax
	label1:
		cmp		edi, gpBufEnd
		jb		label4
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
		sub		edi, 768 + 64
		or		edx, edx
		jz		label2
		sub		edx, 2
		inc		ebx
		jmp		label1
	label2:
		mov		edx, 2
		mov		ebx, 15
	label3:
		cmp		edi, gpBufEnd
		jb		label4
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
		sub		edi, 768 + 64
		dec		ebx
		add		edx, 2
		cmp		edx, 32
		jnz		label3
	label4:
		nop
	}
#else
	int i, j, k;
	BYTE *dst;

	dst = pBuff;

	for(i = 30, j = 1; i >= 0 && dst >= gpBufEnd; i -= 2, j++, dst -= 768 + 64) {
		dst += i;
		for(k = 0; k < 4 * j; k++)
			*dst++ = 0;
		dst += i;
	}
	for(i = 2, j = 15; i != 32 && dst >= gpBufEnd; i += 2, j--, dst -= 768 + 64) {
		dst += i;
		for(k = 0; k < 4 * j; k++)
			*dst++ = 0;
		dst += i;
	}
#endif
}
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall town_clear_low_buf(BYTE *pBuff)
{
	/// ASSERT: assert(gpBuffer);

#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
	__asm {
		mov		edi, pBuff
		mov		edx, 30
		mov		ebx, 1
		xor		eax, eax
	label1:
		cmp		edi, gpBufEnd
		jb		label2
		add		edi, 64
		jmp		label3
	label2:
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
	label3:
		sub		edi, 768 + 64
		or		edx, edx
		jz		label4
		sub		edx, 2
		inc		ebx
		jmp		label1
	label4:
		mov		edx, 2
		mov		ebx, 15
	label5:
		cmp		edi, gpBufEnd
		jb		label6
		add		edi, 64
		jmp		label7
	label6:
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
	label7:
		sub		edi, 768 + 64
		dec		ebx
		add		edx, 2
		cmp		edx, 32
		jnz		label5
	}
#else
	int i, j, k;
	BYTE *dst;

	dst = pBuff;

	for(i = 30, j = 1; i >= 0; i -= 2, j++, dst -= 768 + 64) {
		if(dst < gpBufEnd) {
			dst += i;
			for(k = 0; k < 4 * j; k++)
				*dst++ = 0;
			dst += i;
		} else {
			dst += 64;
		}
	}
	for(i = 2, j = 15; i != 32; i += 2, j--, dst -= 768 + 64) {
		if(dst < gpBufEnd) {
			dst += i;
			for(k = 0; k < 4 * j; k++)
				*dst++ = 0;
			dst += i;
		} else {
			dst += 64;
		}
	}
#endif
}
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall town_draw_clipped_e_flag(BYTE *pBuff, int x, int y, int sx, int sy)
{
	int i;
	BYTE *dst;
	WORD *pMap;

	dst = pBuff;
	pMap = dpiece_defs_map_1[IsometricCoord(x, y)];

	for(i = 0; i < 12; i += 2) {
		level_cel_block = pMap[i];
		if(level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap[i + 1];
		if(level_cel_block != 0) {
			drawLowerScreen(dst + 32);
		}
		dst -= 768 * 32;
	}

	town_draw_clipped_town(pBuff, x, y, sx, sy, 0);
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_clipped_town(BYTE *buffer, int x, int y, int sx, int sy, int some_flag)
{
	unsigned int v6; // edx
	int v7;          // edi
	char v8;         // al
	char v9;         // al
	int v10;         // esi
	int v11;         // ebx
	int v12;         // esi
	int v13;         // ebx
	int v14;         // eax
	int v15;         // eax
	int v16;         // esi
	int v17;         // ebx
	char v18;        // al
	int v19;         // esi
	int v20;         // ebx
	int v21;         // edi
	char v22;        // al
	char v23;        // al
	int v24;         // esi
	int v25;         // ebx
	int v26;         // edi
	char *v27;       // [esp+Ch] [ebp-Ch]
	int xa;          // [esp+10h] [ebp-8h]
	int v29;         // [esp+14h] [ebp-4h]

	xa = x;
	v6 = 112 * x;
	v27 = (char *)gpBuffer + screen_y_times_768[sy] + sx;
	v7 = v6 + y;
	v29 = v6 + y;
	v8 = dItem[v6 / 0x70][y];
	if (v8) {
		v9 = v8 - 1;
		v10 = v9;
		v11 = sx - item[v10]._iAnimWidth2;
		if (v9 == pcursitem)
			CelDrawHdrClrHL(
			    ICOL_BLUE,
			    v11,
			    sy,
			    item[v10]._iAnimData,
			    item[v10]._iAnimFrame,
			    item[v10]._iAnimWidth,
			    0,
			    8);
		Cel2DrawHdrOnly(v11, sy, item[v10]._iAnimData, item[v10]._iAnimFrame, item[v10]._iAnimWidth, 0, 8);
	}
	if (dFlags[0][v7] & DFLAG_MONSTER) {
		v12 = -1 - dMonster[x][y - 1]; // -1 - *(&dword_52D204 + v7); /* check */
		v13 = sx - towner[v12]._tAnimWidth2;
		if (v12 == pcursmonst)
			CelDrawHdrClrHL(
			    166,
			    v13,
			    sy,
			    towner[v12]._tAnimData,
			    towner[v12]._tAnimFrame,
			    towner[v12]._tAnimWidth,
			    0,
			    8);
		Cel2DrawHdrOnly(v13, sy, towner[v12]._tAnimData, towner[v12]._tAnimFrame, towner[v12]._tAnimWidth, 0, 8);
	}
	v14 = dMonster[0][v7];
	if (v14 > 0) {
		v15 = v14 - 1;
		v16 = v15;
		v17 = sx - towner[v15]._tAnimWidth2;
		if (v15 == pcursmonst)
			CelDrawHdrClrHL(
			    166,
			    v17,
			    sy,
			    towner[v16]._tAnimData,
			    towner[v16]._tAnimFrame,
			    towner[v16]._tAnimWidth,
			    0,
			    8);
		Cel2DrawHdrOnly(v17, sy, towner[v16]._tAnimData, towner[v16]._tAnimFrame, towner[v16]._tAnimWidth, 0, 8);
	}
	if (dFlags[0][v7] & DFLAG_PLAYER) {
		v18 = -1 - dPlayer[x][y - 1]; // -1 - *((_BYTE *)&themeLoc[49].height + v7 + 3);
		v19 = v18;
		v20 = sy + plr[v19]._pyoff;
		v21 = sx + plr[v19]._pxoff - plr[v19]._pAnimWidth2;
		if (v18 == pcursplr)
			Cl2DecodeClrHL(165, v21, v20, plr[v19]._pAnimData, plr[v19]._pAnimFrame, plr[v19]._pAnimWidth, 0, 8);
		Cl2DecodeFrm4(v21, v20, plr[v19]._pAnimData, plr[v19]._pAnimFrame, plr[v19]._pAnimWidth, 0, 8);
		if (some_flag && plr[v19]._peflag)
			town_draw_clipped_e_flag((BYTE *)v27 - 64, xa - 1, y + 1, sx - 64, sy);
		v7 = v29;
	}
	if (dFlags[0][v7] & DFLAG_DEAD_PLAYER)
		DrawDeadPlayer(xa, y, sx, sy, 0, 8, 1);
	v22 = dPlayer[0][v7];
	if (v22 > 0) {
		v23 = v22 - 1;
		v24 = v23;
		v25 = sy + plr[v24]._pyoff;
		v26 = sx + plr[v24]._pxoff - plr[v24]._pAnimWidth2;
		if (v23 == pcursplr)
			Cl2DecodeClrHL(165, v26, v25, plr[v24]._pAnimData, plr[v24]._pAnimFrame, plr[v24]._pAnimWidth, 0, 8);
		Cl2DecodeFrm4(v26, v25, plr[v24]._pAnimData, plr[v24]._pAnimFrame, plr[v24]._pAnimWidth, 0, 8);
		if (some_flag && plr[v24]._peflag)
			town_draw_clipped_e_flag((BYTE *)v27 - 64, xa - 1, y + 1, sx - 64, sy);
		v7 = v29;
	}
	if (dFlags[0][v7] & DFLAG_MISSILE)
		DrawClippedMissile(xa, y, sx, sy, 0, 8, FALSE);
}
// 4B8CC0: using guessed type char pcursitem;
// 4B8CC2: using guessed type char pcursplr;

void __fastcall town_draw_lower(int x, int y, int sx, int sy, int a5, int some_flag)
{
	int i, j;
	BYTE *dst;
	WORD *pMap;

	/// ASSERT: assert(gpBuffer);

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx + 32 + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 1; i < 17; i += 2) {
					level_cel_block = pMap[i];
					if(level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					dst -= 768 * 32;
				}
				town_draw_clipped_town(&gpBuffer[sx + screen_y_times_768[sy]], x, y, sx, sy, 0);
			} else {
				town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
		x++;
		y--;
		sx += 64;
	}

	for(j = 0; j < a5 - some_flag; j++) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 16; i += 2) {
					level_cel_block = pMap[i];
					if(level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					level_cel_block = pMap[i + 1];
					if(level_cel_block != 0) {
						drawLowerScreen(dst + 32);
					}
					dst -= 768 * 32;
				}
				town_draw_clipped_town(&gpBuffer[sx + screen_y_times_768[sy]], x, y, sx, sy, 1);
			} else {
				town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
		x++;
		y--;
		sx += 64;
	}

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 16; i += 2) {
					level_cel_block = pMap[i];
					if(level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					dst -= 768 * 32;
				}
				town_draw_clipped_town(&gpBuffer[sx + screen_y_times_768[sy]], x, y, sx, sy, 0);
			} else {
				town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
	}
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_clipped_e_flag_2(BYTE *pBuff, int x, int y, int a4, int a5, int sx, int sy)
{
	int i;
	BYTE *dst;
	WORD *pMap;

	if(a4 == 0) {
		dst = pBuff;
	} else {
		dst = &pBuff[768 * 32 * a4];
	}

	pMap = dpiece_defs_map_1[IsometricCoord(x, y)];

	for(i = 0; i < 6; i++) {
		if(a4 <= i) {
			level_cel_block = pMap[2 * i + 2];
			if(level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			level_cel_block = pMap[2 * i + 3];
			if(level_cel_block != 0) {
				drawLowerScreen(dst + 32);
			}
		}
		dst -= 768 * 32;
	}

	if(a5 < 8) {
		town_draw_clipped_town_2((int)pBuff, x, y, a4, a5, sx, sy, 0);
	}
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_clipped_town_2(int x, int y, int a3, int a4, int a5, int sx, int sy, int some_flag)
{
	unsigned int v8; // edx
	int v9;          // ebx
	char v10;        // al
	char v11;        // al
	int v12;         // esi
	int v13;         // edi
	int v14;         // esi
	int v15;         // edi
	int v16;         // eax
	int v17;         // eax
	int v18;         // esi
	int v19;         // edi
	char v20;        // al
	int v21;         // esi
	int v22;         // ebx
	int v23;         // edi
	char v24;        // al
	char v25;        // al
	int v26;         // esi
	int v27;         // ebx
	int v28;         // edi
	int v29;         // [esp+Ch] [ebp-Ch]
	int xa;          // [esp+10h] [ebp-8h]
	int v31;         // [esp+14h] [ebp-4h]

	xa = y;
	v8 = 112 * y;
	v9 = v8 + a3;
	v29 = x;
	v31 = v8 + a3;
	v10 = dItem[v8 / 0x70][a3];
	if (v10) {
		v11 = v10 - 1;
		v12 = v11;
		v13 = sx - item[v12]._iAnimWidth2;
		if (v11 == pcursitem)
			CelDrawHdrClrHL(
			    ICOL_BLUE,
			    v13,
			    sy,
			    item[v12]._iAnimData,
			    item[v12]._iAnimFrame,
			    item[v12]._iAnimWidth,
			    a5,
			    8);
		Cel2DrawHdrOnly(v13, sy, item[v12]._iAnimData, item[v12]._iAnimFrame, item[v12]._iAnimWidth, a5, 8);
	}
	if (dFlags[0][v9] & DFLAG_MONSTER) {
		v14 = -1 - dMonster[y][a3 - 1]; // -1 - *(&dword_52D204 + v9); /* check */
		v15 = sx - towner[v14]._tAnimWidth2;
		if (v14 == pcursmonst)
			CelDrawHdrClrHL(
			    166,
			    v15,
			    sy,
			    towner[v14]._tAnimData,
			    towner[v14]._tAnimFrame,
			    towner[v14]._tAnimWidth,
			    a5,
			    8);
		Cel2DrawHdrOnly(v15, sy, towner[v14]._tAnimData, towner[v14]._tAnimFrame, towner[v14]._tAnimWidth, a5, 8);
	}
	v16 = dMonster[0][v9];
	if (v16 > 0) {
		v17 = v16 - 1;
		v18 = v17;
		v19 = sx - towner[v17]._tAnimWidth2;
		if (v17 == pcursmonst)
			CelDrawHdrClrHL(
			    166,
			    v19,
			    sy,
			    towner[v18]._tAnimData,
			    towner[v18]._tAnimFrame,
			    towner[v18]._tAnimWidth,
			    a5,
			    8);
		Cel2DrawHdrOnly(v19, sy, towner[v18]._tAnimData, towner[v18]._tAnimFrame, towner[v18]._tAnimWidth, a5, 8);
	}
	if (dFlags[0][v9] & DFLAG_PLAYER) {
		v20 = -1 - dPlayer[y][a3 - 1]; // -1 - *((_BYTE *)&themeLoc[49].height + v9 + 3);
		v21 = v20;
		v22 = sy + plr[v21]._pyoff;
		v23 = sx + plr[v21]._pxoff - plr[v21]._pAnimWidth2;
		if (v20 == pcursplr)
			Cl2DecodeClrHL(165, v23, v22, plr[v21]._pAnimData, plr[v21]._pAnimFrame, plr[v21]._pAnimWidth, a5, 8);
		Cl2DecodeFrm4(v23, v22, plr[v21]._pAnimData, plr[v21]._pAnimFrame, plr[v21]._pAnimWidth, a5, 8);
		if (some_flag && plr[v21]._peflag)
			town_draw_clipped_e_flag_2((BYTE *)(v29 - 64), xa - 1, a3 + 1, a4, a5, sx - 64, sy);
		v9 = v31;
	}
	if (dFlags[0][v9] & DFLAG_DEAD_PLAYER)
		DrawDeadPlayer(xa, a3, sx, sy, a5, 8, 1);
	v24 = dPlayer[0][v9];
	if (v24 > 0) {
		v25 = v24 - 1;
		v26 = v25;
		v27 = sy + plr[v26]._pyoff;
		v28 = sx + plr[v26]._pxoff - plr[v26]._pAnimWidth2;
		if (v25 == pcursplr)
			Cl2DecodeClrHL(165, v28, v27, plr[v26]._pAnimData, plr[v26]._pAnimFrame, plr[v26]._pAnimWidth, a5, 8);
		Cl2DecodeFrm4(v28, v27, plr[v26]._pAnimData, plr[v26]._pAnimFrame, plr[v26]._pAnimWidth, a5, 8);
		if (some_flag && plr[v26]._peflag)
			town_draw_clipped_e_flag_2((BYTE *)(v29 - 64), xa - 1, a3 + 1, a4, a5, sx - 64, sy);
		v9 = v31;
	}
	if (dFlags[0][v9] & DFLAG_MISSILE)
		DrawClippedMissile(xa, a3, sx, sy, a5, 8, FALSE);
}
// 4B8CC0: using guessed type char pcursitem;
// 4B8CC2: using guessed type char pcursplr;

void __fastcall town_draw_lower_2(int x, int y, int sx, int sy, int a5, int a6, int some_flag)
{
	int i, j, dir;
	BYTE *dst;
	WORD *pMap;

	/// ASSERT: assert(gpBuffer);

	dir = 2 * a6 + 2;

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx - (768 * 32 - 32) + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 7; i++) {
					if(a6 <= i) {
						level_cel_block = pMap[2 * i + 3];
						if(level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= 768 * 32;
				}
				if(dir < 8) {
					town_draw_clipped_town_2((int)&gpBuffer[sx + screen_y_times_768[sy]], x, y, a6, dir, sx, sy, 0);
				}
			} else {
				town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
		x++;
		y--;
		sx += 64;
	}

	for(j = 0; j < a5 - some_flag; j++) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx - 768 * 32 + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 7; i++) {
					if(a6 <= i) {
						level_cel_block = pMap[2 * i + 2];
						if(level_cel_block != 0) {
							drawLowerScreen(dst);
						}
						level_cel_block = pMap[2 * i + 3];
						if(level_cel_block != 0) {
							drawLowerScreen(dst + 32);
						}
					}
					dst -= 768 * 32;
				}
				if(dir < 8) {
					town_draw_clipped_town_2((int)&gpBuffer[sx + screen_y_times_768[sy] - 768 * 16 * dir], x, y, a6, dir, sx, sy, 1);
				}
			} else {
				town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
		x++;
		y--;
		sx += 64;
	}

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx - 768 * 32 + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 7; i++) {
					if(a6 <= i) {
						level_cel_block = pMap[2 * i + 2];
						if(level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= 768 * 32;
				}
				if(dir < 8) {
					town_draw_clipped_town_2((int)&gpBuffer[sx + screen_y_times_768[sy]], x, y, a6, dir, sx, sy, 0);
				}
			} else {
				town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
	}
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_e_flag(BYTE *pBuff, int x, int y, int a4, int dir, int sx, int sy)
{
	int i;
	BYTE *dst;
	WORD *pMap;

	dst = pBuff;
	pMap = dpiece_defs_map_1[IsometricCoord(x, y)];

	for(i = 0; i < 7; i++) {
		if(a4 >= i) {
			level_cel_block = pMap[2 * i];
			if(level_cel_block != 0) {
				drawUpperScreen(dst);
			}
			level_cel_block = pMap[2 * i + 1];
			if(level_cel_block != 0) {
				drawUpperScreen(dst + 32);
			}
		}
		dst -= 768 * 32;
	}

	town_draw_town_all(pBuff, x, y, a4, dir, sx, sy, 0);
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall town_draw_town_all(BYTE *buffer, int x, int y, int a4, int dir, int sx, int sy, int some_flag)
{
	char ii, pnum;
	int mi;
	int xx, yy;

	if (dItem[x][y]) {
		ii = dItem[x][y] - 1;
		xx = sx - item[ii]._iAnimWidth2;
		if (ii == pcursitem)
			CelDecodeClr(ICOL_BLUE, xx, sy, item[ii]._iAnimData, item[ii]._iAnimFrame, item[ii]._iAnimWidth, 0, dir);
		CelDrawHdrOnly(xx, sy, item[ii]._iAnimData, item[ii]._iAnimFrame, item[ii]._iAnimWidth, 0, dir);
	}
	if (dFlags[x][y] & DFLAG_MONSTER) {
		mi = -1 - dMonster[x][y - 1];
		xx = sx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst)
			CelDecodeClr(PAL16_BEIGE + 6, xx, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, dir);
		CelDrawHdrOnly(xx, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, dir);
	}
	if (dMonster[x][y] > 0) {
		mi = dMonster[x][y] - 1;
		xx = sx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst)
			CelDecodeClr(PAL16_BEIGE + 6, xx, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, dir);
		CelDrawHdrOnly(xx, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, dir);
	}
	if (dFlags[x][y] & DFLAG_PLAYER) {
		pnum = -1 - dPlayer[x][y - 1];
		yy = sy + plr[pnum]._pyoff;
		xx = sx + plr[pnum]._pxoff - plr[pnum]._pAnimWidth2;
		if (pnum == pcursplr)
			Cl2DecodeFrm2(PAL16_BEIGE + 5, xx, yy, plr[pnum]._pAnimData, plr[pnum]._pAnimFrame, plr[pnum]._pAnimWidth, 0, dir);
		Cl2DecodeFrm1(xx, yy, plr[pnum]._pAnimData, plr[pnum]._pAnimFrame, plr[pnum]._pAnimWidth, 0, dir);
		if (some_flag && plr[pnum]._peflag)
			town_draw_e_flag(buffer - 64, x - 1, y + 1, a4, dir, sx - 64, sy);
	}
	if (dFlags[x][y] & DFLAG_DEAD_PLAYER)
		DrawDeadPlayer(x, y, sx, sy, 0, dir, 0);
	if (dPlayer[x][y] > 0) {
		pnum = dPlayer[x][y] - 1;
		yy = sy + plr[pnum]._pyoff;
		xx = sx + plr[pnum]._pxoff - plr[pnum]._pAnimWidth2;
		if (pnum == pcursplr)
			Cl2DecodeFrm2(PAL16_BEIGE + 5, xx, yy, plr[pnum]._pAnimData, plr[pnum]._pAnimFrame, plr[pnum]._pAnimWidth, 0, dir);
		Cl2DecodeFrm1(xx, yy, plr[pnum]._pAnimData, plr[pnum]._pAnimFrame, plr[pnum]._pAnimWidth, 0, dir);
		if (some_flag && plr[pnum]._peflag)
			town_draw_e_flag(buffer - 64, x - 1, y + 1, a4, dir, sx - 64, sy);
	}
	if (dFlags[x][y] & DFLAG_MISSILE)
		DrawMissile(x, y, sx, sy, 0, dir, FALSE);
}
// 4B8CC0: using guessed type char pcursitem;
// 4B8CC2: using guessed type char pcursplr;

void __fastcall town_draw_upper(int x, int y, int sx, int sy, int a5, int a6, int some_flag)
{
	int i, j, dir;
	BYTE *dst;
	WORD *pMap;

	/// ASSERT: assert(gpBuffer);

	dir = 2 * a6 + 2;
	if(dir > 8) {
		dir = 8;
	}

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx + 32 + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 7; i++) {
					if(a6 >= i) {
						level_cel_block = pMap[2 * i + 1];
						if(level_cel_block != 0) {
							drawUpperScreen(dst);
						}
					}
					dst -= 768 * 32;
				}
				town_draw_town_all(&gpBuffer[sx + screen_y_times_768[sy]], x, y, a6, dir, sx, sy, 0);
			} else {
				town_clear_upper_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_upper_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
		x++;
		y--;
		sx += 64;
	}

	for(j = 0; j < a5 - some_flag; j++) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 7; i++) {
					if(a6 >= i) {
						level_cel_block = pMap[2 * i];
						if(level_cel_block != 0) {
							drawUpperScreen(dst);
						}
						level_cel_block = pMap[2 * i + 1];
						if(level_cel_block != 0) {
							drawUpperScreen(dst + 32);
						}
					}
					dst -= 768 * 32;
				}
				town_draw_town_all(&gpBuffer[sx + screen_y_times_768[sy]], x, y, a6, dir, sx, sy, 1);
			} else {
				town_clear_upper_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_upper_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
		x++;
		y--;
		sx += 64;
	}

	if(some_flag) {
		if(y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if(level_cel_block != 0) {
				dst = &gpBuffer[sx + screen_y_times_768[sy]];
				pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
				for(i = 0; i < 7; i++) {
					if(a6 >= i) {
						level_cel_block = pMap[2 * i];
						if(level_cel_block != 0) {
							drawUpperScreen(dst);
						}
					}
					dst -= 768 * 32;
				}
				town_draw_town_all(&gpBuffer[sx + screen_y_times_768[sy]], x, y, a6, dir, sx, sy, 0);
			} else {
				town_clear_upper_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
			}
		} else {
			town_clear_upper_buf(&gpBuffer[sx + screen_y_times_768[sy]]);
		}
	}
}
// 69CF14: using guessed type int level_cel_block;

void __fastcall T_DrawGame(int x, int y)
{
	int v2;         // esi
	int v3;         // edi
	int v4;         // ebx
	int v5;         // ebx
	int v6;         // esi
	int v7;         // ebx
	int v8;         // esi
	int v9;         // ebx
	int v10;        // esi
	signed int v11; // [esp+Ch] [ebp-10h]
	signed int a6;  // [esp+10h] [ebp-Ch]
	signed int a6a; // [esp+10h] [ebp-Ch]
	signed int a5;  // [esp+14h] [ebp-8h]
	int ya;         // [esp+18h] [ebp-4h]

	v2 = ScrollInfo._sxoff + 64;
	v3 = x - 10;
	ya = y - 1;
	v4 = ScrollInfo._syoff + 175;
	dword_5C2FF8 = 10;
	a5 = 10;
	scr_pix_width = 640;
	scr_pix_height = 352;
	dword_5C2FFC = 11;
	v11 = 5;
	if (chrflag || questlog) {
		ya = y - 3;
		v3 += 2;
		v2 = ScrollInfo._sxoff + 352;
		a5 = 6;
	}
	if (invflag || sbookflag) {
		ya -= 2;
		v3 += 2;
		v2 -= 32;
		a5 = 6;
	}
	switch (ScrollInfo._sdir) {
	case DIR_SW:
		v4 = ScrollInfo._syoff + 143;
		--v3;
		--ya;
		goto LABEL_15;
	case DIR_W:
		v4 = ScrollInfo._syoff + 143;
		--v3;
		--ya;
		goto LABEL_14;
	case DIR_NW:
		goto LABEL_12;
	case DIR_N:
		goto LABEL_14;
	case DIR_NE:
		goto LABEL_15;
	case DIR_E:
		v2 -= 64;
		--v3;
		++ya;
		goto LABEL_14;
	case DIR_SE:
		v2 -= 64;
		--v3;
		++ya;
	LABEL_12:
		++a5;
		break;
	case DIR_OMNI:
		v2 -= 64;
		v4 = ScrollInfo._syoff + 143;
		v3 -= 2;
	LABEL_14:
		++a5;
	LABEL_15:
		v11 = 6;
		break;
	default:
		break;
	}
	a6 = 0;
	gpBufEnd = (unsigned char *)gpBuffer + screen_y_times_768[160];
	do {
		town_draw_upper(v3, ya++, v2, v4, a5, a6, 0);
		v5 = v4 + 16;
		v6 = v2 - 32;
		town_draw_upper(v3++, ya, v6, v5, a5, a6, 1);
		v2 = v6 + 32;
		v4 = v5 + 16;
		++a6;
	} while (a6 < 7);
	gpBufEnd = (unsigned char *)gpBuffer + screen_y_times_768[512];
	if (v11 > 0) {
		do {
			town_draw_lower(v3, ya++, v2, v4, a5, 0);
			v7 = v4 + 16;
			v8 = v2 - 32;
			town_draw_lower(v3++, ya, v8, v7, a5, 1);
			v2 = v8 + 32;
			v4 = v7 + 16;
			--v11;
		} while (v11);
	}
	a6a = 0;
	do {
		town_draw_lower_2(v3, ya++, v2, v4, a5, a6a, 0);
		v9 = v4 + 16;
		v10 = v2 - 32;
		town_draw_lower_2(v3++, ya, v10, v9, a5, a6a, 1);
		v2 = v10 + 32;
		v4 = v9 + 16;
		++a6a;
	} while (a6a < 7);
}
// 4B8968: using guessed type int sbookflag;
// 5C2FF8: using guessed type int dword_5C2FF8;
// 5C2FFC: using guessed type int dword_5C2FFC;
// 5C3000: using guessed type int scr_pix_width;
// 5C3004: using guessed type int scr_pix_height;
// 69BD04: using guessed type int questlog;
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall T_DrawZoom(int x, int y)
{
	int v2;         // edi
	int v3;         // ebx
	int v4;         // esi
	int v5;         // esi
	int v6;         // edi
	int v7;         // esi
	int v8;         // edi
	int v9;         // esi
	int v10;        // edi
	_WORD *v11;     // edi
	char *v12;      // esi
	char *v13;      // ebx
	signed int v14; // edx
	signed int v15; // ecx
	short v16;      // ax
	int v17;        // eax
	signed int v18; // [esp+Ch] [ebp-10h]
	signed int v19; // [esp+Ch] [ebp-10h]
	signed int a6;  // [esp+10h] [ebp-Ch]
	signed int a6a; // [esp+10h] [ebp-Ch]
	int a6b;        // [esp+10h] [ebp-Ch]
	signed int a5;  // [esp+14h] [ebp-8h]
	int a5a;        // [esp+14h] [ebp-8h]
	int ya;         // [esp+18h] [ebp-4h]

	v18 = 0;
	v2 = ScrollInfo._sxoff + 64;
	dword_5C2FF8 = 6;
	dword_5C2FFC = 6;
	v3 = x - 6;
	a5 = 6;
	v4 = ScrollInfo._syoff + 143;
	ya = y - 1;
	scr_pix_width = 384;
	scr_pix_height = 192;
	switch (ScrollInfo._sdir) {
	case DIR_SW:
		v4 = ScrollInfo._syoff + 111;
		v3 = x - 7;
		ya = y - 2;
		goto LABEL_9;
	case DIR_W:
		v4 = ScrollInfo._syoff + 111;
		v3 = x - 7;
		ya = y - 2;
		goto LABEL_8;
	case DIR_NW:
		goto LABEL_6;
	case DIR_N:
		goto LABEL_8;
	case DIR_NE:
		goto LABEL_9;
	case DIR_E:
		v2 = ScrollInfo._sxoff;
		v3 = x - 7;
		ya = y;
		goto LABEL_8;
	case DIR_SE:
		v2 = ScrollInfo._sxoff;
		v3 = x - 7;
		ya = y;
	LABEL_6:
		a5 = 7;
		break;
	case DIR_OMNI:
		v2 = ScrollInfo._sxoff;
		v4 = ScrollInfo._syoff + 111;
		v3 = x - 8;
	LABEL_8:
		a5 = 7;
	LABEL_9:
		v18 = 1;
		break;
	default:
		break;
	}
	a6 = 0;
	gpBufEnd = (unsigned char *)gpBuffer + screen_y_times_768[143];
	do {
		town_draw_upper(v3, ya++, v2, v4, a5, a6, 0);
		v5 = v4 + 16;
		v6 = v2 - 32;
		town_draw_upper(v3++, ya, v6, v5, a5, a6, 1);
		v2 = v6 + 32;
		v4 = v5 + 16;
		++a6;
	} while (a6 < 7);
	gpBufEnd = (unsigned char *)gpBuffer + screen_y_times_768[320];
	if (v18 > 0) {
		do {
			town_draw_lower(v3, ya++, v2, v4, a5, 0);
			v7 = v4 + 16;
			v8 = v2 - 32;
			town_draw_lower(v3++, ya, v8, v7, a5, 1);
			v2 = v8 + 32;
			v4 = v7 + 16;
			--v18;
		} while (v18);
	}
	a6a = 0;
	do {
		town_draw_lower_2(v3, ya++, v2, v4, a5, a6a, 0);
		v9 = v4 + 16;
		v10 = v2 - 32;
		town_draw_lower_2(v3++, ya, v10, v9, a5, a6a, 1);
		v2 = v10 + 32;
		v4 = v9 + 16;
		++a6a;
	} while (a6a < 7);
	if (chrflag || questlog) {
		a5a = 392064;
		goto LABEL_23;
	}
	if (invflag || sbookflag) {
		a5a = 391744;
	LABEL_23:
		a6b = 245168;
		v19 = 160;
		goto LABEL_24;
	}
	a6b = 245088;
	a5a = 391744;
	v19 = 320;
LABEL_24:
	v11 = (_WORD *)((char *)gpBuffer + a5a);
	v12 = (char *)gpBuffer + a6b;
	v13 = (char *)&gpBuffer[a5a + 768];
	v14 = 176;
	do {
		v15 = v19;
		do {
			_LOBYTE(v16) = *v12++;
			_HIBYTE(v16) = v16;
			*v11 = v16;
			*(_WORD *)v13 = v16;
			++v11;
			v13 += 2;
			--v15;
		} while (v15);
		v12 += -v19 - 768;
		v17 = 2 * (v19 + 768);
		v13 -= v17;
		v11 = (_WORD *)((char *)v11 - v17);
		--v14;
	} while (v14);
}
// 4B8968: using guessed type int sbookflag;
// 5C2FF8: using guessed type int dword_5C2FF8;
// 5C2FFC: using guessed type int dword_5C2FFC;
// 5C3000: using guessed type int scr_pix_width;
// 5C3004: using guessed type int scr_pix_height;
// 69BD04: using guessed type int questlog;
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall T_DrawView(int StartX, int StartY)
{
	light_table_index = 0;
	cel_transparency_active = 0;
	if (zoomflag)
		T_DrawGame(StartX, StartY);
	else
		T_DrawZoom(StartX, StartY);
	if (automapflag)
		DrawAutomap();
	if (stextflag && !qtextflag)
		DrawSText();
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
	} else if (plr[myplr]._pStatPts && !spselflag) {
		DrawLevelUpIcon();
	}
	if (uitemflag)
		DrawUniqueInfo();
	if (qtextflag)
		DrawQText();
	if (spselflag)
		DrawSpellList();
	if (dropGoldFlag)
		DrawGoldSplit(dropGoldValue);
	if (helpflag)
		DrawHelp();
	if (msgflag)
		DrawDiabloMsg();
	if (PauseMode && !deathflag)
		gmenu_draw_pause();
	DrawPlrMsg();
	gmenu_draw();
	doom_draw();
	DrawInfoBox();
	DrawLifeFlask();
	DrawManaFlask();
}
// 4B84DC: using guessed type int dropGoldFlag;
// 4B8968: using guessed type int sbookflag;
// 4B8C98: using guessed type int spselflag;
// 52569C: using guessed type int zoomflag;
// 525740: using guessed type int PauseMode;
// 52B9F1: using guessed type char msgflag;
// 646D00: using guessed type char qtextflag;
// 69BD04: using guessed type int questlog;
// 69BEF8: using guessed type int light_table_index;
// 69CF94: using guessed type int cel_transparency_active;
// 6AA705: using guessed type char stextflag;

void __cdecl SetTownMicros()
{
	int i, x, y, lv;
	WORD *pMap, *pPiece;

	for(y = 0; y < MAXDUNY; y++) {
		for(x = 0; x < MAXDUNX; x++) {
			lv = dPiece[x][y];
			pMap = dpiece_defs_map_1[IsometricCoord(x, y)];
			if(lv != 0) {
				lv--;
				pPiece = (WORD *)&pLevelPieces[32 * lv];
				for(i = 0; i < 16; i++) {
					pMap[i] = pPiece[(i & 1) + 14 - (i & 0xE)];
				}
			} else {
				for(i = 0; i < 16; i++) {
					pMap[i] = 0;
				}
			}
		}
	}

	if(zoomflag) {
		scr_pix_width = 640;
		scr_pix_height = 352;
		dword_5C2FF8 = 10;
		dword_5C2FFC = 11;
	} else {
		scr_pix_width = 384;
		scr_pix_height = 224;
		dword_5C2FF8 = 6;
		dword_5C2FFC = 7;
	}
}
// 52569C: using guessed type int zoomflag;
// 5C2FF8: using guessed type int dword_5C2FF8;
// 5C2FFC: using guessed type int dword_5C2FFC;
// 5C3000: using guessed type int scr_pix_width;
// 5C3004: using guessed type int scr_pix_height;

void __fastcall T_FillSector(unsigned char *P3Tiles, unsigned char *pSector, int xi, int yi, int w, int h)
{
	int i, j, xx, yy;
	long v1, v2, v3, v4, ii;

	ii = 4;
	yy = yi;
	for(j = 0; j < h; j++) {
		xx = xi;
		for(i = 0; i < w; i++) {
#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
			__asm {
				mov		esi, pSector
				mov		eax, ii
				add		esi, eax
				xor		eax, eax
				lodsw
				or		eax, eax
				jz		label1
				dec		eax
				mov		esi, P3Tiles
				shl		eax, 3
				add		esi, eax
				xor		eax, eax
				lodsw
				inc		eax
				mov		v1, eax
				lodsw
				inc		eax
				mov		v2, eax
				lodsw
				inc		eax
				mov		v3, eax
				lodsw
				inc		eax
				mov		v4, eax
				jmp		label2
			label1:
				mov		v1, eax
				mov		v2, eax
				mov		v3, eax
				mov		v4, eax
			label2:
				nop
			}
#else
			WORD *Map;

			Map = (WORD *)&pSector[ii];
			if(*Map) {
				v1 = *((WORD *)&P3Tiles[(*Map-1)*8])+1;
				v2 = *((WORD *)&P3Tiles[(*Map-1)*8]+1)+1;
				v3 = *((WORD *)&P3Tiles[(*Map-1)*8]+2)+1;
				v4 = *((WORD *)&P3Tiles[(*Map-1)*8]+3)+1;
			} else {
				v1 = 0;
				v2 = 0;
				v3 = 0;
				v4 = 0;
			}
#endif
			dPiece[xx][yy] = v1;
			dPiece[xx + 1][yy] = v2;
			dPiece[xx][yy + 1] = v3;
			dPiece[xx + 1][yy + 1] = v4;
			xx += 2;
			ii += 2;
		}
		yy += 2;
	}
}

void __fastcall T_FillTile(unsigned char *P3Tiles, int xx, int yy, int t)
{
	long v1, v2, v3, v4;

#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
	__asm {
		mov		eax, t
		dec		eax
		mov		esi, P3Tiles
		shl		eax, 3
		add		esi, eax
		xor		eax, eax
		lodsw
		inc		eax
		mov		v1, eax
		lodsw
		inc		eax
		mov		v2, eax
		lodsw
		inc		eax
		mov		v3, eax
		lodsw
		inc		eax
		mov		v4, eax
		jmp		label1
		mov		v1, eax
		mov		v2, eax
		mov		v3, eax
		mov		v4, eax
	label1:
		nop
	}
#else
	v1 = *((WORD *)&P3Tiles[(t-1)*8])+1;
	v2 = *((WORD *)&P3Tiles[(t-1)*8]+1)+1;
	v3 = *((WORD *)&P3Tiles[(t-1)*8]+2)+1;
	v4 = *((WORD *)&P3Tiles[(t-1)*8]+3)+1;
#endif

	dPiece[xx][yy] = v1;
	dPiece[xx + 1][yy] = v2;
	dPiece[xx][yy + 1] = v3;
	dPiece[xx + 1][yy + 1] = v4;
}

void __cdecl T_Pass3()
{
	int xx, yy, x;
	unsigned char *P3Tiles, *pSector;

	for(yy = 0; yy < MAXDUNY; yy += 2) {
		for(xx = 0; xx < MAXDUNX; xx += 2) {
			dPiece[xx][yy] = 0;
			dPiece[xx + 1][yy] = 0;
			dPiece[xx][yy + 1] = 0;
			dPiece[xx + 1][yy + 1] = 0;
		}
	}

	P3Tiles = LoadFileInMem("Levels\\TownData\\Town.TIL", 0);
	pSector = LoadFileInMem("Levels\\TownData\\Sector1s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 46, 46, 25, 25);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector2s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 46, 0, 25, 23);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector3s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 0, 46, 23, 25);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector4s.DUN", 0);
	T_FillSector(P3Tiles, pSector, 0, 0, 23, 23);
	mem_free_dbg(pSector);

	if(gbMaxPlayers == 1) {
		if(!(plr[myplr].pTownWarps & 1)) {
			T_FillTile(P3Tiles, 48, 20, 320);
		}
		if(!(plr[myplr].pTownWarps & 2)) {
			T_FillTile(P3Tiles, 16, 68, 332);
			T_FillTile(P3Tiles, 16, 70, 331);
		}
		if(!(plr[myplr].pTownWarps & 4)) {
			for(x = 36; x < 46; x++) {
				T_FillTile(P3Tiles, x, 78, random(0, 4) + 1);
			}
		}
	}

	if(quests[13]._qactive != 3 && quests[13]._qactive) {
		T_FillTile(P3Tiles, 60, 70, 342);
	} else {
		T_FillTile(P3Tiles, 60, 70, 71);
	}

	mem_free_dbg(P3Tiles);
}
// 45FDE6: could not find valid save-restore pair for edi
// 679660: using guessed type char gbMaxPlayers;

void __fastcall CreateTown(int entry)
{
	int x, y;

	dminx = 10;
	dminy = 10;
	dmaxx = 84;
	dmaxy = 84;

	if(entry == 0) {
		ViewX = 75;
		ViewY = 68;
	} else if(entry == 1) {
		ViewX = 25;
		ViewY = 31;
	} else if(entry == 7) {
		if(TWarpFrom == 5) {
			ViewX = 49;
			ViewY = 22;
		}
		if(TWarpFrom == 9) {
			ViewX = 18;
			ViewY = 69;
		}
		if(TWarpFrom == 13) {
			ViewX = 41;
			ViewY = 81;
		}
	}

	T_Pass3();
	memset(dTransVal, 0, sizeof(dTransVal));
	memset(dFlags, 0, sizeof(dFlags));
	memset(dPlayer, 0, sizeof(dPlayer));
	memset(dMonster, 0, sizeof(dMonster));
	memset(dObject, 0, sizeof(dObject));
	memset(dItem, 0, sizeof(dItem));
	memset(dArch, 0, sizeof(dArch));

	for(y = 0; y < MAXDUNY; y++) {
		for(x = 0; x < MAXDUNX; x++) {
			if(dPiece[x][y] == 360) {
				dArch[x][y] = 1;
			} else if(dPiece[x][y] == 358) {
				dArch[x][y] = 2;
			} else if(dPiece[x][y] == 129) {
				dArch[x][y] = 6;
			} else if(dPiece[x][y] == 130) {
				dArch[x][y] = 7;
			} else if(dPiece[x][y] == 128) {
				dArch[x][y] = 8;
			} else if(dPiece[x][y] == 117) {
				dArch[x][y] = 9;
			} else if(dPiece[x][y] == 157) {
				dArch[x][y] = 10;
			} else if(dPiece[x][y] == 158) {
				dArch[x][y] = 11;
			} else if(dPiece[x][y] == 156) {
				dArch[x][y] = 12;
			} else if(dPiece[x][y] == 162) {
				dArch[x][y] = 13;
			} else if(dPiece[x][y] == 160) {
				dArch[x][y] = 14;
			} else if(dPiece[x][y] == 214) {
				dArch[x][y] = 15;
			} else if(dPiece[x][y] == 212) {
				dArch[x][y] = 16;
			} else if(dPiece[x][y] == 217) {
				dArch[x][y] = 17;
			} else if(dPiece[x][y] == 216) {
				dArch[x][y] = 18;
			}
		}
	}

	SetTownMicros();
}
// 5CF328: using guessed type int dmaxx;
// 5CF32C: using guessed type int dmaxy;
// 5D2458: using guessed type int dminx;
// 5D245C: using guessed type int dminy;
// 6ABB30: using guessed type int TWarpFrom;
