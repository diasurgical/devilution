/**
 * @file town.h
 *
 * Implementation of functionality for rendering the town, towners and calling other render routines.
 */
#include "all.h"

/**
 * @brief Render a black tile
 * @brief world_draw_black_tile but limited to upper half of screen
 * @param pBuff location in back buffer to render the tile, must be on upper half of screen
 */
void town_clear_upper_buf(BYTE *pBuff)
{
	assert(gpBuffer);

#ifdef USE_ASM
	__asm {
		mov		edi, pBuff
		mov		edx, TILE_HEIGHT - 2
		mov		ebx, 1
		xor		eax, eax
	label1:
		cmp		edi, gpBufEnd
		jb		label4
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
		sub		edi, BUFFER_WIDTH + TILE_WIDTH
		or		edx, edx
		jz		label2
		sub		edx, 2
		inc		ebx
		jmp		label1
	label2:
		mov		edx, 2
		mov		ebx, TILE_HEIGHT / 2 - 1
	label3:
		cmp		edi, gpBufEnd
		jb		label4
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
		sub		edi, BUFFER_WIDTH + TILE_WIDTH
		dec		ebx
		add		edx, 2
		cmp		edx, TILE_HEIGHT
		jnz		label3
	label4:
		nop
	}
#else
	int i, j, k;
	BYTE *dst;

	dst = pBuff;

	for (i = TILE_HEIGHT - 2, j = 1; i >= 0 && dst >= gpBufEnd; i -= 2, j++, dst -= BUFFER_WIDTH + TILE_WIDTH) {
		dst += i;
		for (k = 0; k < 4 * j; k++)
			*dst++ = 0;
		dst += i;
	}
	for (i = 2, j = TILE_HEIGHT / 2 - 1; i != TILE_HEIGHT && dst >= gpBufEnd; i += 2, j--, dst -= BUFFER_WIDTH + TILE_WIDTH) {
		dst += i;
		for (k = 0; k < 4 * j; k++)
			*dst++ = 0;
		dst += i;
	}
#endif
}

/**
 * @brief Render a black tile
 * @brief world_draw_black_tile but limited to lower half of screen
 * @param pBuff location in back buffer to render the tile, must be on lower half of screen
 */
void town_clear_low_buf(BYTE *pBuff)
{
	assert(gpBuffer);

#ifdef USE_ASM
	__asm {
		mov		edi, pBuff
		mov		edx, TILE_HEIGHT - 2
		mov		ebx, 1
		xor		eax, eax
	label1:
		cmp		edi, gpBufEnd
		jb		label2
		add		edi, TILE_WIDTH
		jmp		label3
	label2:
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
	label3:
		sub		edi, BUFFER_WIDTH + TILE_WIDTH
		or		edx, edx
		jz		label4
		sub		edx, 2
		inc		ebx
		jmp		label1
	label4:
		mov		edx, 2
		mov		ebx, TILE_HEIGHT / 2 - 1
	label5:
		cmp		edi, gpBufEnd
		jb		label6
		add		edi, TILE_WIDTH
		jmp		label7
	label6:
		add		edi, edx
		mov		ecx, ebx
		rep stosd
		add		edi, edx
	label7:
		sub		edi, BUFFER_WIDTH + TILE_WIDTH
		dec		ebx
		add		edx, 2
		cmp		edx, TILE_HEIGHT
		jnz		label5
	}
#else
	int i, j, k;
	BYTE *dst;

	dst = pBuff;

	for (i = TILE_HEIGHT - 2, j = 1; i >= 0; i -= 2, j++, dst -= BUFFER_WIDTH + TILE_WIDTH) {
		if (dst < gpBufEnd) {
			dst += i;
			for (k = 0; k < 4 * j; k++)
				*dst++ = 0;
			dst += i;
		} else {
			dst += TILE_WIDTH;
		}
	}
	for (i = 2, j = TILE_HEIGHT / 2 - 1; i != TILE_HEIGHT; i += 2, j--, dst -= BUFFER_WIDTH + TILE_WIDTH) {
		if (dst < gpBufEnd) {
			dst += i;
			for (k = 0; k < 4 * j; k++)
				*dst++ = 0;
			dst += i;
		} else {
			dst += TILE_WIDTH;
		}
	}
#endif
}

/**
 * @brief Render trees on top of player, buggy disabled in 1.09
 * @param pBuff backbuffer pointing where to render on lower part of screen
 * @param nCel Frame number for pSpecialCels tile to draw
 */
void town_special_lower(BYTE *pBuff, int nCel)
{
#if 0
	int w;
	BYTE *end;

#ifdef USE_ASM
	__asm {
		mov		ebx, pSpecialCels
		mov		eax, nCel
		shl		eax, 2
		add		ebx, eax
		mov		eax, [ebx+4]
		sub		eax, [ebx]
		mov		end, eax
		mov		esi, pSpecialCels
		add		esi, [ebx]
		mov		edi, pBuff
		mov		eax, BUFFER_WIDTH + 64
		mov		w, eax
		mov		ebx, end
		add		ebx, esi
	label1:
		mov		edx, 64
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label7
		sub		edx, eax
		cmp		edi, gpBufEnd
		jb		label3
		add		esi, eax
		add		edi, eax
		jmp		label6
	label3:
		mov		ecx, eax
		shr		ecx, 1
		jnb		label4
		movsb
		jecxz	label6
	label4:
		shr		ecx, 1
		jnb		label5
		movsw
		jecxz	label6
	label5:
		rep movsd
	label6:
		or		edx, edx
		jz		label8
		jmp		label2
	label7:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label8:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	}
#else
	BYTE width;
	BYTE *src, *dst;
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)pSpecialCels;
	src = &pSpecialCels[pFrameTable[nCel]];
	dst = pBuff;
	end = &src[pFrameTable[nCel + 1] - pFrameTable[nCel]];

	for(; src != end; dst -= BUFFER_WIDTH + 64) {
		for(w = 64; w;) {
			width = *src++;
			if(!(width & 0x80)) {
				w -= width;
				if(dst < gpBufEnd) {
					if(width & 1) {
						dst[0] = src[0];
						src++;
						dst++;
					}
					width >>= 1;
					if(width & 1) {
						dst[0] = src[0];
						dst[1] = src[1];
						src += 2;
						dst += 2;
					}
					width >>= 1;
					for(; width; width--) {
						dst[0] = src[0];
						dst[1] = src[1];
						dst[2] = src[2];
						dst[3] = src[3];
						src += 4;
						dst += 4;
					}
				} else {
					src += width;
					dst += width;
				}
			} else {
				width = -(char)width;
				dst += width;
				w -= width;
			}
		}
	}
#endif
#endif
}

/**
 * @brief Render trees on top of player, buggy disabled in 1.09
 * @param pBuff backbuffer pointing where to render on upper part of screen
 * @param nCel Frame number for pSpecialCels tile to draw
 */
void town_special_upper(BYTE *pBuff, int nCel)
{
#if 0
	int w;
	BYTE *end;

#ifdef USE_ASM
	__asm {
		mov		ebx, pSpecialCels
		mov		eax, nCel
		shl		eax, 2
		add		ebx, eax
		mov		eax, [ebx+4]
		sub		eax, [ebx]
		mov		end, eax
		mov		esi, pSpecialCels
		add		esi, [ebx]
		mov		edi, pBuff
		mov		eax, BUFFER_WIDTH + 64
		mov		w, eax
		mov		ebx, end
		add		ebx, esi
	label1:
		mov		edx, 64
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label6
		sub		edx, eax
		cmp		edi, gpBufEnd
		jb		label8
		mov		ecx, eax
		shr		ecx, 1
		jnb		label3
		movsb
		jecxz	label5
	label3:
		shr		ecx, 1
		jnb		label4
		movsw
		jecxz	label5
	label4:
		rep movsd
	label5:
		or		edx, edx
		jz		label7
		jmp		label2
	label6:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label7:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	label8:
		nop
	}
#else
	BYTE width;
	BYTE *src, *dst;
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)pSpecialCels;
	src = &pSpecialCels[pFrameTable[nCel]];
	dst = pBuff;
	end = &src[pFrameTable[nCel + 1] - pFrameTable[nCel]];

	for(; src != end; dst -= BUFFER_WIDTH + 64) {
		for(w = 64; w;) {
			width = *src++;
			if(!(width & 0x80)) {
				w -= width;
				if(dst < gpBufEnd) {
					return;
				}
				if(width & 1) {
					dst[0] = src[0];
					src++;
					dst++;
				}
				width >>= 1;
				if(width & 1) {
					dst[0] = src[0];
					dst[1] = src[1];
					src += 2;
					dst += 2;
				}
				width >>= 1;
				for(; width; width--) {
					dst[0] = src[0];
					dst[1] = src[1];
					dst[2] = src[2];
					dst[3] = src[3];
					src += 4;
					dst += 4;
				}
			} else {
				width = -(char)width;
				dst += width;
				w -= width;
			}
		}
	}
#endif
#endif
}

/**
 * This variant checks for of screen element on the lower screen
 * This function it self causes rendering issues since it will render on top of objects on the other side of walls
 * @brief Re render tile to workaround sorting issues with players walking east/west
 * @param pBuff Pointer to output buffer at location sx,sy
 * @param y dPiece coordinate
 * @param x dPiece coordinate
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 */
void town_draw_clipped_e_flag(BYTE *pBuff, int x, int y, int sx, int sy)
{
	int i;
	BYTE *dst;
	MICROS *pMap;

	dst = pBuff;
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	for (i = 0; i < 12; i += 2) {
		level_cel_block = pMap->mt[i];
		if (level_cel_block != 0) {
			drawLowerScreen(dst);
		}
		level_cel_block = pMap->mt[i + 1];
		if (level_cel_block != 0) {
			drawLowerScreen(dst + TILE_WIDTH / 2);
		}
		dst -= BUFFER_WIDTH * TILE_HEIGHT;
	}

	town_draw_clipped_town(pBuff, x, y, sx, sy, 0);
}

/**
 * @brief Render object sprites
 * @param pBuff where to render to with sx,sy already applied
 * @param sx dPiece coordinate
 * @param sy dPiece coordinate
 * @param dx Backbuffer coordinate
 * @param dy Backbuffer coordinate
 * @param eflag Should the sorting workaround be applied
 */
void town_draw_clipped_town(BYTE *pBuff, int sx, int sy, int dx, int dy, int eflag)
{
	int mi, px, py;
	char bv;

	assert(gpBuffer);

	pBuff = &gpBuffer[dx + PitchTbl[dy]];

	if (dItem[sx][sy] != 0) {
		bv = dItem[sx][sy] - 1;
		px = dx - item[bv]._iAnimWidth2;
		if (bv == pcursitem) {
			CelBlitOutlineSafe(181, px, dy, item[bv]._iAnimData, item[bv]._iAnimFrame, item[bv]._iAnimWidth, 0, 8);
		}
		CelClippedDrawSafe(px, dy, item[bv]._iAnimData, item[bv]._iAnimFrame, item[bv]._iAnimWidth, 0, 8);
	}
	if (dFlags[sx][sy] & BFLAG_MONSTLR) {
		mi = -(dMonster[sx][sy - 1] + 1);
		px = dx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst) {
			CelBlitOutlineSafe(166, px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, 8);
		}
		CelClippedDrawSafe(px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, 8);
	}
	if (dMonster[sx][sy] > 0) {
		mi = dMonster[sx][sy] - 1;
		px = dx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst) {
			CelBlitOutlineSafe(166, px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, 8);
		}
		CelClippedDrawSafe(px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, 8);
	}
	if (dFlags[sx][sy] & BFLAG_PLAYERLR) {
		bv = -(dPlayer[sx][sy - 1] + 1);
		px = dx + plr[bv]._pxoff - plr[bv]._pAnimWidth2;
		py = dy + plr[bv]._pyoff;
		if (bv == pcursplr) {
			Cl2DrawOutlineSafe(165, px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, 8);
		}
		Cl2DrawSafe(px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, 8);
		if (eflag && plr[bv]._peflag) {
			town_draw_clipped_e_flag(pBuff - TILE_WIDTH, sx - 1, sy + 1, dx - TILE_WIDTH, dy);
		}
	}
	if (dFlags[sx][sy] & BFLAG_DEAD_PLAYER) {
		DrawDeadPlayer(sx, sy, dx, dy, 0, 8, TRUE);
	}
	if (dPlayer[sx][sy] > 0) {
		bv = dPlayer[sx][sy] - 1;
		px = dx + plr[bv]._pxoff - plr[bv]._pAnimWidth2;
		py = dy + plr[bv]._pyoff;
		if (bv == pcursplr) {
			Cl2DrawOutlineSafe(165, px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, 8);
		}
		Cl2DrawSafe(px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, 8);
		if (eflag && plr[bv]._peflag) {
			town_draw_clipped_e_flag(pBuff - TILE_WIDTH, sx - 1, sy + 1, dx - TILE_WIDTH, dy);
		}
	}
	if (dFlags[sx][sy] & BFLAG_MISSILE) {
		DrawClippedMissile(sx, sy, dx, dy, 0, 8, 0);
	}
	if (dSpecial[sx][sy] != 0) {
		town_special_lower(pBuff, dSpecial[sx][sy]);
	}
}

/**
 * @brief Render a row of tile
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 * @param chunks tile width of row
 * @param eflag is it an even (0) or odd (1) row
 */
void town_draw_lower(int x, int y, int sx, int sy, int chunks, int eflag)
{
	int i, j;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + TILE_WIDTH / 2 + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 1; i < 17; i += 2) {
					level_cel_block = pMap->mt[i];
					if (level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				town_draw_clipped_town(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 0);
			} else {
				town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
		x++;
		y--;
		sx += TILE_WIDTH;
	}

	for (j = 0; j < chunks - eflag; j++) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 16; i += 2) {
					level_cel_block = pMap->mt[i];
					if (level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					level_cel_block = pMap->mt[i + 1];
					if (level_cel_block != 0) {
						drawLowerScreen(dst + TILE_WIDTH / 2);
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				town_draw_clipped_town(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 1);
			} else {
				town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
		x++;
		y--;
		sx += TILE_WIDTH;
	}

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 16; i += 2) {
					level_cel_block = pMap->mt[i];
					if (level_cel_block != 0) {
						drawLowerScreen(dst);
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				town_draw_clipped_town(&gpBuffer[sx + PitchTbl[sy]], x, y, sx, sy, 0);
			} else {
				town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
	}
}

/**
 * This variant checks for of screen element on the lower screen
 * This function it self causes rendering issues since it will render on top of objects on the other side of walls
 * @brief Re render tile to workaround sorting issues with players walking east/west
 * @param pBuff Pointer to output buffer at location sx,sy
 * @param y dPiece coordinate
 * @param x dPiece coordinate
 * @param row The current row being rendered
 * @param CelSkip chunks of cell to skip
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 */
void town_draw_clipped_e_flag_2(BYTE *pBuff, int x, int y, int row, int CelSkip, int sx, int sy)
{
	int i;
	BYTE *dst;
	MICROS *pMap;

	if (row == 0) {
		dst = pBuff;
	} else {
		dst = &pBuff[BUFFER_WIDTH * TILE_HEIGHT * row];
	}

	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	for (i = 0; i < 6; i++) {
		if (row <= i) {
			level_cel_block = pMap->mt[2 * i + 2];
			if (level_cel_block != 0) {
				drawLowerScreen(dst);
			}
			level_cel_block = pMap->mt[2 * i + 3];
			if (level_cel_block != 0) {
				drawLowerScreen(dst + TILE_WIDTH / 2);
			}
		}
		dst -= BUFFER_WIDTH * TILE_HEIGHT;
	}

	if (CelSkip < 8) {
		town_draw_clipped_town_2(pBuff, x, y, row, CelSkip, sx, sy, 0);
	}
}

/**
 * @brief Render object sprites, skip offscreen parts for lower screen
 * @param pBuff where to render to with sx,sy already applied
 * @param sx dPiece coordinate
 * @param sy dPiece coordinate
 * @param row The current row being rendered
 * @param CelSkip chunks of cell to skip
 * @param dx Backbuffer coordinate
 * @param dy Backbuffer coordinate
 * @param eflag Should the sorting workaround be applied
 */
void town_draw_clipped_town_2(BYTE *pBuff, int sx, int sy, int row, int CelSkip, int dx, int dy, int eflag)
{
	int mi, px, py;
	char bv;

	if (dItem[sx][sy] != 0) {
		bv = dItem[sx][sy] - 1;
		px = dx - item[bv]._iAnimWidth2;
		if (bv == pcursitem) {
			CelBlitOutlineSafe(181, px, dy, item[bv]._iAnimData, item[bv]._iAnimFrame, item[bv]._iAnimWidth, CelSkip, 8);
		}
		CelClippedDrawSafe(px, dy, item[bv]._iAnimData, item[bv]._iAnimFrame, item[bv]._iAnimWidth, CelSkip, 8);
	}
	if (dFlags[sx][sy] & BFLAG_MONSTLR) {
		mi = -(dMonster[sx][sy - 1] + 1);
		px = dx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst) {
			CelBlitOutlineSafe(166, px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, CelSkip, 8);
		}
		CelClippedDrawSafe(px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, CelSkip, 8);
	}
	if (dMonster[sx][sy] > 0) {
		mi = dMonster[sx][sy] - 1;
		px = dx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst) {
			CelBlitOutlineSafe(166, px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, CelSkip, 8);
		}
		CelClippedDrawSafe(px, dy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, CelSkip, 8);
	}
	if (dFlags[sx][sy] & BFLAG_PLAYERLR) {
		bv = -(dPlayer[sx][sy - 1] + 1);
		px = dx + plr[bv]._pxoff - plr[bv]._pAnimWidth2;
		py = dy + plr[bv]._pyoff;
		if (bv == pcursplr) {
			Cl2DrawOutlineSafe(165, px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, CelSkip, 8);
		}
		Cl2DrawSafe(px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, CelSkip, 8);
		if (eflag && plr[bv]._peflag) {
			town_draw_clipped_e_flag_2(pBuff - TILE_WIDTH, sx - 1, sy + 1, row, CelSkip, dx - TILE_WIDTH, dy);
		}
	}
	if (dFlags[sx][sy] & BFLAG_DEAD_PLAYER) {
		DrawDeadPlayer(sx, sy, dx, dy, CelSkip, 8, TRUE);
	}
	if (dPlayer[sx][sy] > 0) {
		bv = dPlayer[sx][sy] - 1;
		px = dx + plr[bv]._pxoff - plr[bv]._pAnimWidth2;
		py = dy + plr[bv]._pyoff;
		if (bv == pcursplr) {
			Cl2DrawOutlineSafe(165, px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, CelSkip, 8);
		}
		Cl2DrawSafe(px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, CelSkip, 8);
		if (eflag && plr[bv]._peflag) {
			town_draw_clipped_e_flag_2(pBuff - TILE_WIDTH, sx - 1, sy + 1, row, CelSkip, dx - TILE_WIDTH, dy);
		}
	}
	if (dFlags[sx][sy] & BFLAG_MISSILE) {
		DrawClippedMissile(sx, sy, dx, dy, CelSkip, 8, 0);
	}
	if (dSpecial[sx][sy] != 0) {
		town_special_lower(&pBuff[PitchTbl[16 * CelSkip]], dSpecial[sx][sy]);
	}
}

/**
 * @brief Render a row of tile, checking for overdrawing on lower part of screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 * @param chunks tile width of row
 * @param row current row being rendered
 * @param eflag is it an even (0) or odd (1) row
 */
void town_draw_lower_2(int x, int y, int sx, int sy, int chunks, int row, int eflag)
{
	int i, j, CelSkip;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	CelSkip = 2 * row + 2;

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + TILE_WIDTH / 2 - BUFFER_WIDTH * TILE_HEIGHT + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 7; i++) {
					if (row <= i) {
						level_cel_block = pMap->mt[2 * i + 3];
						if (level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				if (CelSkip < 8) {
					town_draw_clipped_town_2(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelSkip, sx, sy, 0);
				}
			} else {
				town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
		x++;
		y--;
		sx += TILE_WIDTH;
	}

	for (j = 0; j < chunks - eflag; j++) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx - BUFFER_WIDTH * TILE_HEIGHT + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 7; i++) {
					if (row <= i) {
						level_cel_block = pMap->mt[2 * i + 2];
						if (level_cel_block != 0) {
							drawLowerScreen(dst);
						}
						level_cel_block = pMap->mt[2 * i + 3];
						if (level_cel_block != 0) {
							drawLowerScreen(dst + TILE_WIDTH / 2);
						}
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				if (CelSkip < 8) {
					town_draw_clipped_town_2(&gpBuffer[sx + PitchTbl[sy] - BUFFER_WIDTH * 16 * CelSkip], x, y, row, CelSkip, sx, sy, 1);
				}
			} else {
				town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
		x++;
		y--;
		sx += TILE_WIDTH;
	}

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx - BUFFER_WIDTH * TILE_HEIGHT + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 7; i++) {
					if (row <= i) {
						level_cel_block = pMap->mt[2 * i + 2];
						if (level_cel_block != 0) {
							drawLowerScreen(dst);
						}
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				if (CelSkip < 8) {
					town_draw_clipped_town_2(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelSkip, sx, sy, 0);
				}
			} else {
				town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_low_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
	}
}

/**
 * This variant checks for of screen element on the upper screen
 * This function it self causes rendering issues since it will render on top of objects on the other side of walls
 * @brief Re render tile to workaround sorting issues with players walking east/west
 * @param pBuff Pointer to output buffer at location sx,sy
 * @param y dPiece coordinate
 * @param x dPiece coordinate
 * @param row The current row being rendered
 * @param CelCap chunks of cell to skip
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 */
void town_draw_e_flag(BYTE *pBuff, int x, int y, int row, int CelCap, int sx, int sy)
{
	int i;
	BYTE *dst;
	MICROS *pMap;

	dst = pBuff;
	pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];

	for (i = 0; i < 7; i++) {
		if (row >= i) {
			level_cel_block = pMap->mt[2 * i];
			if (level_cel_block != 0) {
				drawUpperScreen(dst);
			}
			level_cel_block = pMap->mt[2 * i + 1];
			if (level_cel_block != 0) {
				drawUpperScreen(dst + TILE_WIDTH / 2);
			}
		}
		dst -= BUFFER_WIDTH * TILE_HEIGHT;
	}

	town_draw_town_all(pBuff, x, y, row, CelCap, sx, sy, 0);
}

/**
 * @brief Render object sprites, skip offscreen parts for upper screen
 * @param pBuff where to render to with sx,sx already applied
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param row The current row being rendered
 * @param CelCap chunks of cell to skip
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 * @param eflag Should the sorting workaround be applied
 */
void town_draw_town_all(BYTE *pBuff, int x, int y, int row, int CelCap, int sx, int sy, int eflag)
{
	int mi, px, py;
	char bv;

	if (dItem[x][y] != 0) {
		bv = dItem[x][y] - 1;
		px = sx - item[bv]._iAnimWidth2;
		if (bv == pcursitem) {
			CelBlitOutline(181, px, sy, item[bv]._iAnimData, item[bv]._iAnimFrame, item[bv]._iAnimWidth, 0, CelCap);
		}
		/// ASSERT: assert(item[bv]._iAnimData);
		CelClippedDraw(px, sy, item[bv]._iAnimData, item[bv]._iAnimFrame, item[bv]._iAnimWidth, 0, CelCap);
	}
	if (dFlags[x][y] & BFLAG_MONSTLR) {
		mi = -(dMonster[x][y - 1] + 1);
		px = sx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst) {
			CelBlitOutline(166, px, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, CelCap);
		}
		/// ASSERT: assert(towner[mi]._tAnimData);
		CelClippedDraw(px, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, CelCap);
	}
	if (dMonster[x][y] > 0) {
		mi = dMonster[x][y] - 1;
		px = sx - towner[mi]._tAnimWidth2;
		if (mi == pcursmonst) {
			CelBlitOutline(166, px, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, CelCap);
		}
		/// ASSERT: assert(towner[mi]._tAnimData);
		CelClippedDraw(px, sy, towner[mi]._tAnimData, towner[mi]._tAnimFrame, towner[mi]._tAnimWidth, 0, CelCap);
	}
	if (dFlags[x][y] & BFLAG_PLAYERLR) {
		bv = -(dPlayer[x][y - 1] + 1);
		px = sx + plr[bv]._pxoff - plr[bv]._pAnimWidth2;
		py = sy + plr[bv]._pyoff;
		if (bv == pcursplr) {
			Cl2DrawOutline(165, px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, CelCap);
		}
		/// ASSERT: assert(plr[bv]._pAnimData);
		Cl2Draw(px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, CelCap);
		if (eflag && plr[bv]._peflag) {
			town_draw_e_flag(pBuff - TILE_WIDTH, x - 1, y + 1, row, CelCap, sx - TILE_WIDTH, sy);
		}
	}
	if (dFlags[x][y] & BFLAG_DEAD_PLAYER) {
		DrawDeadPlayer(x, y, sx, sy, 0, CelCap, FALSE);
	}
	if (dPlayer[x][y] > 0) {
		bv = dPlayer[x][y] - 1;
		px = sx + plr[bv]._pxoff - plr[bv]._pAnimWidth2;
		py = sy + plr[bv]._pyoff;
		if (bv == pcursplr) {
			Cl2DrawOutline(165, px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, CelCap);
		}
		/// ASSERT: assert(plr[bv]._pAnimData);
		Cl2Draw(px, py, plr[bv]._pAnimData, plr[bv]._pAnimFrame, plr[bv]._pAnimWidth, 0, CelCap);
		if (eflag && plr[bv]._peflag) {
			town_draw_e_flag(pBuff - TILE_WIDTH, x - 1, y + 1, row, CelCap, sx - TILE_WIDTH, sy);
		}
	}
	if (dFlags[x][y] & BFLAG_MISSILE) {
		DrawMissile(x, y, sx, sy, 0, CelCap, FALSE);
	}
	if (dSpecial[x][y] != 0) {
		town_special_upper(pBuff, dSpecial[x][y]);
	}
}

/**
 * @brief Render a row of tile, checking for overdrawing on upper part of screen
 * @param x dPiece coordinate
 * @param y dPiece coordinate
 * @param sx Backbuffer coordinate
 * @param sy Backbuffer coordinate
 * @param chunks tile width of row
 * @param row current row being rendered
 * @param eflag is it an even (0) or odd (1) row
 */
void town_draw_upper(int x, int y, int sx, int sy, int chunks, int row, int eflag)
{
	int i, j, CelCap;
	BYTE *dst;
	MICROS *pMap;

	/// ASSERT: assert(gpBuffer);

	CelCap = 2 * row + 2;
	if (CelCap > 8) {
		CelCap = 8;
	}

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + TILE_WIDTH / 2 + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 7; i++) {
					if (row >= i) {
						level_cel_block = pMap->mt[2 * i + 1];
						if (level_cel_block != 0) {
							drawUpperScreen(dst);
						}
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				town_draw_town_all(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelCap, sx, sy, 0);
			} else {
				town_clear_upper_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_upper_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
		x++;
		y--;
		sx += TILE_WIDTH;
	}

	for (j = 0; j < chunks - eflag; j++) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 7; i++) {
					if (row >= i) {
						level_cel_block = pMap->mt[2 * i];
						if (level_cel_block != 0) {
							drawUpperScreen(dst);
						}
						level_cel_block = pMap->mt[2 * i + 1];
						if (level_cel_block != 0) {
							drawUpperScreen(dst + TILE_WIDTH / 2);
						}
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				town_draw_town_all(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelCap, sx, sy, 1);
			} else {
				town_clear_upper_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_upper_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
		x++;
		y--;
		sx += TILE_WIDTH;
	}

	if (eflag) {
		if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
			level_cel_block = dPiece[x][y];
			if (level_cel_block != 0) {
				dst = &gpBuffer[sx + PitchTbl[sy]];
				pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
				for (i = 0; i < 7; i++) {
					if (row >= i) {
						level_cel_block = pMap->mt[2 * i];
						if (level_cel_block != 0) {
							drawUpperScreen(dst);
						}
					}
					dst -= BUFFER_WIDTH * TILE_HEIGHT;
				}
				town_draw_town_all(&gpBuffer[sx + PitchTbl[sy]], x, y, row, CelCap, sx, sy, 0);
			} else {
				town_clear_upper_buf(&gpBuffer[sx + PitchTbl[sy]]);
			}
		} else {
			town_clear_upper_buf(&gpBuffer[sx + PitchTbl[sy]]);
		}
	}
}

/**
 * @brief Configure render and process screen rows
 * @param x Center of view in dPiece coordinate
 * @param y Center of view in dPiece coordinate
 */
void T_DrawGame(int x, int y)
{
	int i, sx, sy, chunks, blocks;

	ViewDX = SCREEN_WIDTH;
	ViewDY = VIEWPORT_HEIGHT;
	ViewBX = SCREEN_WIDTH / TILE_WIDTH;
	ViewBY = VIEWPORT_HEIGHT / TILE_HEIGHT;

	sx = ScrollInfo._sxoff + TILE_WIDTH;
	sy = ScrollInfo._syoff + SCREEN_Y + (TILE_HEIGHT / 2 - 1);
	x -= SCREEN_WIDTH / TILE_WIDTH;
	y--;
	chunks = SCREEN_WIDTH / TILE_WIDTH;
	blocks = 5;

	if (chrflag || questlog) {
		x += 2;
		y -= 2;
		sx += (SCREEN_WIDTH / 2) - TILE_WIDTH / 2;
		chunks = 6;
	}
	if (invflag || sbookflag) {
		x += 2;
		y -= 2;
		sx -= TILE_WIDTH / 2;
		chunks = 6;
	}

	switch (ScrollInfo._sdir) {
	case SDIR_NONE:
		break;
	case SDIR_N:
		sy -= TILE_HEIGHT;
		x--;
		y--;
		blocks++;
		break;
	case SDIR_NE:
		sy -= TILE_HEIGHT;
		x--;
		y--;
		chunks++;
		blocks++;
		break;
	case SDIR_E:
		chunks++;
		break;
	case SDIR_SE:
		chunks++;
		blocks++;
		break;
	case SDIR_S:
		blocks++;
		break;
	case SDIR_SW:
		sx -= TILE_WIDTH;
		x--;
		y++;
		chunks++;
		blocks++;
		break;
	case SDIR_W:
		sx -= TILE_WIDTH;
		x--;
		y++;
		chunks++;
		break;
	case SDIR_NW:
		sx -= TILE_WIDTH;
		sy -= TILE_HEIGHT;
		x -= 2;
		chunks++;
		blocks++;
		break;
	}

	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[SCREEN_Y]];
	for (i = 0; i < 7; i++) {
		town_draw_upper(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
		town_draw_upper(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
	}
	/// ASSERT: assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[VIEWPORT_HEIGHT + SCREEN_Y]];
	for (i = 0; i < blocks; i++) {
		town_draw_lower(x, y, sx, sy, chunks, 0);
		y++;
		sx -= TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
		town_draw_lower(x, y, sx, sy, chunks, 1);
		x++;
		sx += TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
	}
	for (i = 0; i < 7; i++) {
		town_draw_lower_2(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
		town_draw_lower_2(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
	}
}

/**
 * @brief Configure render for zoomed view and process screen rows
 * @param x Center of view in dPiece coordinate
 * @param y Center of view in dPiece coordinate
 */
void T_DrawZoom(int x, int y)
{
	int i, sx, sy, chunks, blocks;
	int wdt, nSrcOff, nDstOff;

	ViewDX = ZOOM_WIDTH;
	ViewDY = ZOOM_HEIGHT - TILE_HEIGHT;
	ViewBX = ZOOM_WIDTH / TILE_WIDTH;
	ViewBY = (ZOOM_HEIGHT - TILE_HEIGHT) / TILE_HEIGHT;

	sx = ScrollInfo._sxoff + SCREEN_X;
	sy = ScrollInfo._syoff + SCREEN_Y - (TILE_HEIGHT / 2 + 1);
	x -= ZOOM_WIDTH / TILE_WIDTH;
	y--;
	chunks = ZOOM_WIDTH / TILE_WIDTH;
	blocks = 0;

	switch (ScrollInfo._sdir) {
	case SDIR_NONE:
		break;
	case SDIR_N:
		sy -= TILE_HEIGHT;
		x--;
		y--;
		blocks++;
		break;
	case SDIR_NE:
		sy -= TILE_HEIGHT;
		x--;
		y--;
		chunks++;
		blocks++;
		break;
	case SDIR_E:
		chunks++;
		break;
	case SDIR_SE:
		chunks++;
		blocks++;
		break;
	case SDIR_S:
		blocks++;
		break;
	case SDIR_SW:
		sx -= TILE_WIDTH;
		x--;
		y++;
		chunks++;
		blocks++;
		break;
	case SDIR_W:
		sx -= TILE_WIDTH;
		x--;
		y++;
		chunks++;
		break;
	case SDIR_NW:
		sx -= TILE_WIDTH;
		sy -= TILE_HEIGHT;
		x -= 2;
		chunks++;
		blocks++;
		break;
	}

	assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[-17 + SCREEN_Y]];
	for (i = 0; i < 7; i++) {
		town_draw_upper(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
		town_draw_upper(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
	}
	assert(gpBuffer);
	gpBufEnd = &gpBuffer[PitchTbl[160 + SCREEN_Y]];
	for (i = 0; i < blocks; i++) {
		town_draw_lower(x, y, sx, sy, chunks, 0);
		y++;
		sx -= TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
		town_draw_lower(x, y, sx, sy, chunks, 1);
		x++;
		sx += TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
	}
	for (i = 0; i < 7; i++) {
		town_draw_lower_2(x, y, sx, sy, chunks, i, 0);
		y++;
		sx -= TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
		town_draw_lower_2(x, y, sx, sy, chunks, i, 1);
		x++;
		sx += TILE_WIDTH / 2;
		sy += TILE_HEIGHT / 2;
	}

	if (chrflag || questlog) {
		nSrcOff = SCREENXY(TILE_WIDTH / 2 + SPANEL_WIDTH / 4, VIEWPORT_HEIGHT / 2 - (TILE_HEIGHT / 2 + 1));
		nDstOff = SCREENXY(SPANEL_WIDTH, VIEWPORT_HEIGHT - 2);
		wdt = (SCREEN_WIDTH - SPANEL_WIDTH) / 2;
	} else if (invflag || sbookflag) {
		nSrcOff = SCREENXY(TILE_WIDTH / 2 + SPANEL_WIDTH / 4, VIEWPORT_HEIGHT / 2 - (TILE_HEIGHT / 2 + 1));
		nDstOff = SCREENXY(0, VIEWPORT_HEIGHT - 2);
		wdt = (SCREEN_WIDTH - SPANEL_WIDTH) / 2;
	} else {
		nSrcOff = SCREENXY(TILE_WIDTH / 2, VIEWPORT_HEIGHT / 2 - (TILE_HEIGHT / 2 + 1));
		nDstOff = SCREENXY(0, VIEWPORT_HEIGHT - 2);
		wdt = SCREEN_WIDTH / 2;
	}

	assert(gpBuffer);

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
		mov		edx, VIEWPORT_HEIGHT / 2
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
 * Mostly like DrawView but enables stores and lacks death screen
 * @brief Start rendering of screen, town variation
 * @param StartX Center of view in dPiece coordinate
 * @param StartY Center of view in dPiece coordinate
 */
void T_DrawView(int StartX, int StartY)
{
	light_table_index = 0;
	cel_transparency_active = 0;
	if (zoomflag) {
		T_DrawGame(StartX, StartY);
	} else {
		T_DrawZoom(StartX, StartY);
	}
	if (automapflag) {
		DrawAutomap();
	}
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
	if (PauseMode != 0 && !deathflag) {
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
 * @brief Build tile columns
 */
void SetTownMicros()
{
	int i, x, y, lv;
	WORD *pPiece;
	MICROS *pMap;

	for (y = 0; y < MAXDUNY; y++) {
		for (x = 0; x < MAXDUNX; x++) {
			lv = dPiece[x][y];
			pMap = &dpiece_defs_map_1[IsometricCoord(x, y)];
			if (lv != 0) {
				lv--;
				pPiece = (WORD *)&pLevelPieces[32 * lv];
				for (i = 0; i < 16; i++) {
					pMap->mt[i] = pPiece[(i & 1) + 16 - 2 - (i & 0xE)];
				}
			} else {
				for (i = 0; i < 16; i++) {
					pMap->mt[i] = 0;
				}
			}
		}
	}

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

/**
 * @brief Load level data into dPiece
 * @param P3Tiles Tile set
 * @param pSector Sector data
 * @param xi upper left destination
 * @param yi upper left destination
 * @param w width of sector
 * @param h height of sector
 */
void T_FillSector(BYTE *P3Tiles, BYTE *pSector, int xi, int yi, int w, int h)
{
	int i, j, xx, yy;
	long v1, v2, v3, v4, ii;

	ii = 4;
	yy = yi;
	for (j = 0; j < h; j++) {
		xx = xi;
		for (i = 0; i < w; i++) {
#ifdef USE_ASM
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
			if (*Map) {
				v1 = *((WORD *)&P3Tiles[(*Map - 1) * 8] + 0) + 1;
				v2 = *((WORD *)&P3Tiles[(*Map - 1) * 8] + 1) + 1;
				v3 = *((WORD *)&P3Tiles[(*Map - 1) * 8] + 2) + 1;
				v4 = *((WORD *)&P3Tiles[(*Map - 1) * 8] + 3) + 1;
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

/**
 * @brief Load a tile in to dPiece
 * @param P3Tiles Tile set
 * @param xx upper left destination
 * @param yy upper left destination
 * @param t tile id
 */
void T_FillTile(BYTE *P3Tiles, int xx, int yy, int t)
{
	long v1, v2, v3, v4;

#ifdef USE_ASM
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
	v1 = *((WORD *)&P3Tiles[(t - 1) * 8] + 0) + 1;
	v2 = *((WORD *)&P3Tiles[(t - 1) * 8] + 1) + 1;
	v3 = *((WORD *)&P3Tiles[(t - 1) * 8] + 2) + 1;
	v4 = *((WORD *)&P3Tiles[(t - 1) * 8] + 3) + 1;
#endif

	dPiece[xx][yy] = v1;
	dPiece[xx + 1][yy] = v2;
	dPiece[xx][yy + 1] = v3;
	dPiece[xx + 1][yy + 1] = v4;
}

#ifdef HELLFIRE
void TownOpenHive()
{
	dPiece[78][60] = 0x48a;
	dPiece[79][60] = 0x48b;
	dPiece[78][61] = 0x48c;
	dPiece[79][61] = 0x50e;
	dPiece[78][62] = 0x4ee;
	dPiece[78][63] = 0x4f0;
	dPiece[79][62] = 0x510;
	dPiece[79][63] = 0x511;
	dPiece[79][64] = 0x512;
	dPiece[78][64] = 0x11a;
	dPiece[78][65] = 0x11c;
	dPiece[79][65] = 0x11d;
	dPiece[80][60] = 0x513;
	dPiece[80][61] = 0x515;
	dPiece[81][61] = 0x516;
	dPiece[82][60] = 0x517;
	dPiece[83][60] = 0x518;
	dPiece[82][61] = 0x519;
	dPiece[83][61] = 0x51a;
	dPiece[80][62] = 0x51b;
	dPiece[81][62] = 0x51c;
	dPiece[80][63] = 0x51d;
	dPiece[81][63] = 0x51e;
	dPiece[80][64] = 0x51f;
	dPiece[81][64] = 0x520;
	dPiece[80][65] = 0x521;
	dPiece[81][65] = 0x522;
	dPiece[82][64] = 0x527;
	dPiece[83][64] = 0x528;
	dPiece[82][65] = 0x529;
	dPiece[83][65] = 0x52a;
	dPiece[82][62] = 0x523;
	dPiece[83][62] = 0x524;
	dPiece[82][63] = 0x525;
	dPiece[83][63] = 0x526;
	dPiece[84][61] = 0x118;
	dPiece[84][62] = 0x118;
	dPiece[84][63] = 0x118;
	dPiece[85][60] = 0x118;
	dPiece[85][61] = 0x118;
	dPiece[85][63] = 8;
	dPiece[85][64] = 8;
	dPiece[86][60] = 0xd9;
	dPiece[86][61] = 0x18;
	dPiece[85][62] = 0x13;
	dPiece[84][64] = 0x118;
	SetTownMicros();
}

void TownCloseHive()
{
	dPiece[78][60] = 0x48a;
	dPiece[79][60] = 0x4eb;
	dPiece[78][61] = 0x4ec;
	dPiece[79][61] = 0x4ed;
	dPiece[78][62] = 0x4ee;
	dPiece[79][62] = 0x4ef;
	dPiece[78][63] = 0x4f0;
	dPiece[79][63] = 0x4f1;
	dPiece[78][64] = 0x4f2;
	dPiece[79][64] = 0x4f3;
	dPiece[78][65] = 0x4f4;
	dPiece[80][60] = 0x4f5;
	dPiece[81][60] = 0x4f6;
	dPiece[80][61] = 0x4f7;
	dPiece[81][61] = 0x4f8;
	dPiece[82][60] = 0x4f9;
	dPiece[83][60] = 0x4fa;
	dPiece[82][61] = 0x4fb;
	dPiece[83][61] = 0x4fc;
	dPiece[80][62] = 0x4fd;
	dPiece[81][62] = 0x4fe;
	dPiece[80][63] = 0x4ff;
	dPiece[81][63] = 0x500;
	dPiece[80][64] = 0x501;
	dPiece[81][64] = 0x502;
	dPiece[80][65] = 0x503;
	dPiece[81][65] = 0x504;
	dPiece[82][64] = 0x509;
	dPiece[83][64] = 0x50a;
	dPiece[82][65] = 0x50b;
	dPiece[83][65] = 0x50c;
	dPiece[82][62] = 0x505;
	dPiece[83][62] = 0x506;
	dPiece[82][63] = 0x507;
	dPiece[83][63] = 0x508;
	dPiece[84][61] = 0x118;
	dPiece[84][62] = 0x118;
	dPiece[84][63] = 0x118;
	dPiece[85][60] = 0x118;
	dPiece[85][61] = 0x118;
	dPiece[85][63] = 8;
	dPiece[85][64] = 8;
	dPiece[86][60] = 0xd9;
	dPiece[86][61] = 0x18;
	dPiece[85][62] = 0x13;
	dPiece[84][64] = 0x118;
	SetTownMicros();
}

void TownCloseGrave()
{
	dPiece[36][21] = 0x52b;
	dPiece[37][21] = 0x52c;
	dPiece[36][22] = 0x52d;
	dPiece[37][22] = 0x52e;
	dPiece[36][23] = 0x52f;
	dPiece[37][23] = 0x530;
	dPiece[36][24] = 0x531;
	dPiece[37][24] = 0x532;
	dPiece[35][21] = 0x53b;
	dPiece[34][21] = 0x53c;
	SetTownMicros();
}

void TownOpenGrave()
{
	dPiece[36][21] = 0x533;
	dPiece[37][21] = 0x534;
	dPiece[36][22] = 0x535;
	dPiece[37][22] = 0x536;
	dPiece[36][23] = 0x537;
	dPiece[37][23] = 0x538;
	dPiece[36][24] = 0x539;
	dPiece[37][24] = 0x53a;
	dPiece[35][21] = 0x53b;
	dPiece[34][21] = 0x53c;
	SetTownMicros();
}
#endif

/**
 * @brief Initialize all of the levels data
 */
void T_Pass3()
{
	int xx, yy, x;
	BYTE *P3Tiles, *pSector;

	for (yy = 0; yy < MAXDUNY; yy += 2) {
		for (xx = 0; xx < MAXDUNX; xx += 2) {
			dPiece[xx][yy] = 0;
			dPiece[xx + 1][yy] = 0;
			dPiece[xx][yy + 1] = 0;
			dPiece[xx + 1][yy + 1] = 0;
		}
	}

	P3Tiles = LoadFileInMem("Levels\\TownData\\Town.TIL", NULL);
	pSector = LoadFileInMem("Levels\\TownData\\Sector1s.DUN", NULL);
	T_FillSector(P3Tiles, pSector, 46, 46, 25, 25);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector2s.DUN", NULL);
	T_FillSector(P3Tiles, pSector, 46, 0, 25, 23);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector3s.DUN", NULL);
	T_FillSector(P3Tiles, pSector, 0, 46, 23, 25);
	mem_free_dbg(pSector);
	pSector = LoadFileInMem("Levels\\TownData\\Sector4s.DUN", NULL);
	T_FillSector(P3Tiles, pSector, 0, 0, 23, 23);
	mem_free_dbg(pSector);

#ifndef SPAWN
	if (gbMaxPlayers == 1) {
#endif
#ifdef HELLFIRE
		if (quests[Q_FARMER]._qactive == QUEST_DONE || quests[Q_FARMER]._qactive == 10
		    || quests[Q_JERSEY]._qactive == QUEST_DONE || quests[Q_JERSEY]._qactive == 10) {
			TownOpenHive();
		} else {
			TownCloseHive();
		}
		if (quests[Q_GRAVE]._qactive == QUEST_DONE || plr[myplr]._pLvlVisited[21])
			TownOpenGrave();
		else
			TownCloseGrave();
#endif
#ifndef SPAWN
#ifdef HELLFIRE
		if (!(plr[myplr].pTownWarps & 1) && plr[myplr]._pLevel < 10)
#else
		if (!(plr[myplr].pTownWarps & 1))
#endif
#endif
		{
			T_FillTile(P3Tiles, 48, 20, 320);
		}
#ifndef SPAWN
#ifdef HELLFIRE
		if (!(plr[myplr].pTownWarps & 2) && plr[myplr]._pLevel < 15)
#else
		if (!(plr[myplr].pTownWarps & 2))
#endif
#endif
		{
			T_FillTile(P3Tiles, 16, 68, 332);
			T_FillTile(P3Tiles, 16, 70, 331);
		}
#ifndef SPAWN
#ifdef HELLFIRE
		if (!(plr[myplr].pTownWarps & 4) && plr[myplr]._pLevel < 20) {
#else
		if (!(plr[myplr].pTownWarps & 4)) {
#endif
#endif
			for (x = 36; x < 46; x++) {
				T_FillTile(P3Tiles, x, 78, random_(0, 4) + 1);
			}
#ifndef SPAWN
		}
	}
#ifdef HELLFIRE
	else {
		if (quests[Q_FARMER]._qactive == QUEST_DONE || quests[Q_FARMER]._qactive == 10
		    || quests[Q_JERSEY]._qactive == QUEST_DONE || quests[Q_JERSEY]._qactive == 10) {
			TownOpenHive();
		} else {
			TownCloseHive();
		}
		if (quests[Q_GRAVE]._qactive == QUEST_DONE || plr[myplr]._pLvlVisited[21])
			TownOpenGrave();
		else
			TownCloseGrave();
	}
#endif
#endif

	if (quests[Q_PWATER]._qactive != QUEST_DONE && quests[Q_PWATER]._qactive) {
		T_FillTile(P3Tiles, 60, 70, 342);
	} else {
		T_FillTile(P3Tiles, 60, 70, 71);
	}

	mem_free_dbg(P3Tiles);
}

/**
 * @brief Initialize town level
 * @param entry Methode of entry
 */
void CreateTown(int entry)
{
	int x, y;

	dminx = 10;
	dminy = 10;
	dmaxx = 84;
	dmaxy = 84;

	if (entry == ENTRY_MAIN) { // New game
		ViewX = 75;
		ViewY = 68;
	} else if (entry == ENTRY_PREV) { // Cathedral
		ViewX = 25;
		ViewY = 31;
	} else if (entry == ENTRY_TWARPUP) {
		if (TWarpFrom == 5) {
			ViewX = 49;
			ViewY = 22;
		}
		if (TWarpFrom == 9) {
			ViewX = 18;
			ViewY = 69;
		}
		if (TWarpFrom == 13) {
			ViewX = 41;
			ViewY = 81;
		}
#ifdef HELLFIRE
		if (TWarpFrom == 21) {
			ViewX = 36;
			ViewY = 25;
		}
		if (TWarpFrom == 17) {
			ViewX = 79;
			ViewY = 62;
		}
#endif
	}

	T_Pass3();
	memset(dLight, 0, sizeof(dLight));
	memset(dFlags, 0, sizeof(dFlags));
	memset(dPlayer, 0, sizeof(dPlayer));
	memset(dMonster, 0, sizeof(dMonster));
	memset(dObject, 0, sizeof(dObject));
	memset(dItem, 0, sizeof(dItem));
	memset(dSpecial, 0, sizeof(dSpecial));

	for (y = 0; y < MAXDUNY; y++) {
		for (x = 0; x < MAXDUNX; x++) {
			if (dPiece[x][y] == 360) {
				dSpecial[x][y] = 1;
			} else if (dPiece[x][y] == 358) {
				dSpecial[x][y] = 2;
			} else if (dPiece[x][y] == 129) {
				dSpecial[x][y] = 6;
			} else if (dPiece[x][y] == 130) {
				dSpecial[x][y] = 7;
			} else if (dPiece[x][y] == 128) {
				dSpecial[x][y] = 8;
			} else if (dPiece[x][y] == 117) {
				dSpecial[x][y] = 9;
			} else if (dPiece[x][y] == 157) {
				dSpecial[x][y] = 10;
			} else if (dPiece[x][y] == 158) {
				dSpecial[x][y] = 11;
			} else if (dPiece[x][y] == 156) {
				dSpecial[x][y] = 12;
			} else if (dPiece[x][y] == 162) {
				dSpecial[x][y] = 13;
			} else if (dPiece[x][y] == 160) {
				dSpecial[x][y] = 14;
			} else if (dPiece[x][y] == 214) {
				dSpecial[x][y] = 15;
			} else if (dPiece[x][y] == 212) {
				dSpecial[x][y] = 16;
			} else if (dPiece[x][y] == 217) {
				dSpecial[x][y] = 17;
			} else if (dPiece[x][y] == 216) {
				dSpecial[x][y] = 18;
			}
		}
	}

	SetTownMicros();
}
