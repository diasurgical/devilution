/**
 * @file minitext.cpp
 *
 * Implementation of scrolling dialog text.
 */
#include "all.h"

/** Current y position of text in px */
int qtexty;
/** Pointer to the current text being displayed */
const char *qtextptr;
/** Time of last rendering of the text */
int sgLastScroll;
/** Specify if the quest dialog window is being shown */
BOOLEAN qtextflag;
/** Duplicate of qtextSpd */
int qtextDelay;
/** Vertical speed of the scrolling text, see qscroll_spd_tbl */
int qtextSpd;
/** Graphics for the medium size font */
BYTE *pMedTextCels;
/** Graphics for the window border */
BYTE *pTextBoxCels;

/** Maps from font index to medtexts.cel frame number. */
const BYTE mfontframe[128] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 37, 49, 38, 0, 39, 40, 47,
	42, 43, 41, 45, 52, 44, 53, 55, 36, 27,
	28, 29, 30, 31, 32, 33, 34, 35, 51, 50,
	48, 46, 49, 54, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	26, 42, 0, 43, 0, 0, 0, 1, 2, 3,
	4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 48, 0, 49, 0, 0
};
/**
 * Maps from medtexts.cel frame number to character width. Note, the
 * character width may be distinct from the frame width, which is 22 for every
 * medtexts.cel frame.
 */
const BYTE mfontkern[56] = {
	5, 15, 10, 13, 14, 10, 9, 13, 11, 5,
	5, 11, 10, 16, 13, 16, 10, 15, 12, 10,
	14, 17, 17, 22, 17, 16, 11, 5, 11, 11,
	11, 10, 11, 11, 11, 11, 15, 5, 10, 18,
	15, 8, 6, 6, 7, 10, 9, 6, 10, 10,
	5, 5, 5, 5, 11, 12
};

/* data */

/**
 * Text scroll speeds. Positive numbers will delay scrolling 1 out of n frames,
 * negative numbers will scroll 1+(-n) pixels.
 */
int qscroll_spd_tbl[9] = { 2, 4, 6, 8, 0, -1, -2, -3, -4 };

/**
 * @brief Free the resouces used by the quest dialog window
 */
void FreeQuestText()
{
	MemFreeDbg(pMedTextCels);
	MemFreeDbg(pTextBoxCels);
}

/**
 * @brief Load the resouces used by the quest dialog window, and initialize it's state
 */
void InitQuestText()
{
	pMedTextCels = LoadFileInMem("Data\\MedTextS.CEL", NULL);
	pTextBoxCels = LoadFileInMem("Data\\TextBox.CEL", NULL);
	qtextflag = FALSE;
}

/**
 * @brief Start the given naration
 * @param m Index of narration from the alltext table
 */
void InitQTextMsg(int m)
{
	if (alltext[m].scrlltxt) {
		questlog = FALSE;
		qtextptr = alltext[m].txtstr;
		qtextflag = TRUE;
		qtexty = 340 + SCREEN_Y;
		qtextSpd = qscroll_spd_tbl[alltext[m].txtspd - 1];
		qtextDelay = qtextSpd;
		sgLastScroll = GetTickCount();
	}
	PlaySFX(alltext[m].sfxnr);
}

/**
 * @brief Draw the quest dialog window decoration and background
 */
void DrawQTextBack()
{
	CelDraw(PANEL_X + 24, SCREEN_Y + 327, pTextBoxCels, 1, 591);

#define TRANS_RECT_X (PANEL_LEFT + 27)
#define TRANS_RECT_Y 28
#define TRANS_RECT_WIDTH 585
#define TRANS_RECT_HEIGHT 297
#include "asm_trans_rect.inc"
}

/**
 * @brief Print a character
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 */
void PrintQTextChr(int sx, int sy, BYTE *pCelBuff, int nCel)
{
	BYTE *dst, *pStart, *pEnd, *end;

	/// ASSERT: assert(gpBuffer);

	dst = &gpBuffer[sx + PitchTbl[sy]];
	pStart = &gpBuffer[PitchTbl[209]];
	pEnd = &gpBuffer[PitchTbl[469]];

#ifdef USE_ASM
	__asm {
		mov		ebx, pCelBuff
		mov		eax, nCel
		shl		eax, 2
		add		ebx, eax
		mov		eax, [ebx+4]
		sub		eax, [ebx]
		mov		end, eax
		mov		esi, pCelBuff
		add		esi, [ebx]
		mov		edi, dst
		mov		ebx, end
		add		ebx, esi
	label1:
		mov		edx, 22
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label7
		sub		edx, eax
		cmp		edi, pStart
		jb		label5
		cmp		edi, pEnd
		ja		label5
		mov		ecx, eax
		shr		ecx, 1
		jnb		label3
		movsb
		jecxz	label6
	label3:
		shr		ecx, 1
		jnb		label4
		movsw
		jecxz	label6
	label4:
		rep movsd
		jmp		label6
	label5:
		add		esi, eax
		add		edi, eax
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
		sub		edi, BUFFER_WIDTH + 22
		cmp		ebx, esi
		jnz		label1
	}
#else
	int i;
	BYTE width;
	BYTE *src;
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)&pCelBuff[4 * nCel];
	src = &pCelBuff[pFrameTable[0]];
	end = &src[pFrameTable[1] - pFrameTable[0]];

	for (; src != end; dst -= BUFFER_WIDTH + 22) {
		for (i = 22; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (dst >= pStart && dst <= pEnd) {
					if (width & 1) {
						dst[0] = src[0];
						src++;
						dst++;
					}
					width >>= 1;
					if (width & 1) {
						dst[0] = src[0];
						dst[1] = src[1];
						src += 2;
						dst += 2;
					}
					width >>= 1;
					for (; width; width--) {
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
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Draw the quest dialog window decoration and background
 */
void DrawQText()
{
	int i, l, w, tx, ty;
	BYTE c;
	const char *p, *pnl, *s;
	char tempstr[128];
	BOOL doneflag;
	DWORD currTime;

	DrawQTextBack();

	p = qtextptr;
	pnl = NULL;
	tx = 48 + PANEL_X;
	ty = qtexty;

	doneflag = FALSE;
	while (!doneflag) {
		w = 0;
		s = p;
		l = 0;
		while (*s != '\n' && *s != '|' && w < 543) {
			c = gbFontTransTbl[(BYTE)*s];
			s++;
			if (c != '\0') {
				tempstr[l] = c;
				w += mfontkern[mfontframe[c]] + 2;
			} else {
				l--;
			}
			l++;
		}
		tempstr[l] = '\0';
		if (*s == '|') {
			tempstr[l] = '\0';
			doneflag = TRUE;
		} else if (*s != '\n') {
			while (tempstr[l] != ' ' && l > 0) {
				tempstr[l] = '\0';
				l--;
			}
		}
		for (i = 0; tempstr[i]; i++) {
			p++;
			c = mfontframe[gbFontTransTbl[(BYTE)tempstr[i]]];
			if (*p == '\n') {
				p++;
			}
			if (c != 0) {
				PrintQTextChr(tx, ty, pMedTextCels, c);
			}
			tx += mfontkern[c] + 2;
		}
		if (pnl == NULL) {
			pnl = p;
		}
		tx = 48 + PANEL_X;
		ty += 38;
		if (ty > 341 + SCREEN_Y) {
			doneflag = TRUE;
		}
	}

	currTime = GetTickCount();
	while (1) {
		if (qtextSpd <= 0) {
			qtexty--;
			qtexty += qtextSpd;
		} else {
			qtextDelay--;
			if (qtextDelay != 0) {
				qtexty--;
			}
		}
		if (qtextDelay == 0) {
			qtextDelay = qtextSpd;
		}
		if (qtexty <= 49 + SCREEN_Y) {
			qtexty += 38;
			qtextptr = pnl;
			if (*pnl == '|') {
				qtextflag = FALSE;
			}
			break;
		}
		sgLastScroll += 50;
		if (currTime - sgLastScroll >= 0x7FFFFFFF) {
			break;
		}
	}
}
