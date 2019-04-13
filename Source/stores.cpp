//HEADER_GOES_HERE

#include "../types.h"

int stextup;    // weak
int storenumh;  // weak
int stextlhold; // weak
ItemStruct boyitem;
int stextshold; // idb
ItemStruct premiumitem[6];
void *pSTextBoxCels;
int premiumlevel; // idb
int talker;       // weak
STextStruct stext[24];
char stextsize;  // weak
int stextsmax;   // weak
int InStoreFlag; // idb
ItemStruct storehold[48];
int gossipstart; // weak
ItemStruct witchitem[20];
int stextscrl;
int numpremium; // idb
ItemStruct healitem[20];
ItemStruct golditem;
char storehidx[48];
void *pSTextSlidCels;
int stextvhold;     // weak
int stextsel;       // weak
char stextscrldbtn; // weak
int gossipend;      // weak
void *pCelBuff;
int stextsval; // idb
int boylevel;  // weak
ItemStruct smithitem[20];
int stextdown;      // weak
char stextscrlubtn; // weak
char stextflag;

int SStringY[24] = {
	0,
	12,
	24,
	36,
	48,
	60,
	72,
	84,
	96,
	108,
	120,
	132,
	144,
	156,
	168,
	180,
	192,
	204,
	216,
	228,
	240,
	252,
	264,
	276
};
char *talkname[9] = {
	"Griswold",
	"Pepin",
	"",
	"Ogden",
	"Cain",
	"Farnham",
	"Adria",
	"Gillian",
	"Wirt"
};

void InitStores()
{
	int i; // eax

	pSTextBoxCels = LoadFileInMem("Data\\TextBox2.CEL", 0);
	pCelBuff = LoadFileInMem("Data\\PentSpn2.CEL", 0);
	pSTextSlidCels = LoadFileInMem("Data\\TextSlid.CEL", 0);
	ClearSText(0, 24);
	stextflag = STORE_NONE;
	InStoreFlag = 1;
	stextsize = 0;
	stextscrl = 0;
	numpremium = 0;
	premiumlevel = 1;

	for (i = 0; i < 6; i++)
		premiumitem[i]._itype = -1;

	boyitem._itype = -1;
	boylevel = 0;
}
// 69FB38: using guessed type int talker;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A3C: using guessed type int boylevel;
// 6AA705: using guessed type char stextflag;

void SetupTownStores()
{
	int i; // eax
	int l; // esi

	SetRndSeed(glSeedTbl[currlevel] * GetTickCount());
	if (gbMaxPlayers == 1) {
		l = 0;
		for (i = 0; i < 17; i++) {
			if (plr[myplr]._pLvlVisited[i])
				l = i;
		}
	} else {
		l = plr[myplr]._pLevel >> 1;
	}
	l += 2;
	if (l < 6)
		l = 6;
	if (l > 16)
		l = 16;
	SpawnStoreGold();
	SpawnSmith(l);
	SpawnWitch(l);
	SpawnHealer(l);
	SpawnBoy(plr[myplr]._pLevel);
	SpawnPremium(plr[myplr]._pLevel);
}
// 679660: using guessed type char gbMaxPlayers;

void FreeStoreMem()
{
	void *p;

	p = pSTextBoxCels;
	pSTextBoxCels = NULL;
	mem_free_dbg(p);
	p = pCelBuff;
	pCelBuff = NULL;
	mem_free_dbg(p);
	p = pSTextSlidCels;
	pSTextSlidCels = NULL;
	mem_free_dbg(p);
}

void DrawSTextBack()
{
	CelDecodeOnly(408, 487, (BYTE *)pSTextBoxCels, 1, 271);

#define TRANS_RECT_X 347
#define TRANS_RECT_Y 28
#define TRANS_RECT_WIDTH 265
#define TRANS_RECT_HEIGHT 297
#include "asm_trans_rect.inc"
}

void PrintSString(int x, int y, unsigned char cjustflag, char *str, int col, int val)
{
	int v6;            // edi
	int v7;            // eax
	int v8;            // ebx
	int v9;            // esi
	int v10;           // esi
	int v11;           // ecx
	int v12;           // eax
	int v13;           // edx
	int v14;           // ecx
	unsigned char v15; // al
	int v16;           // ebx
	int v17;           // ecx
	int v18;           // eax
	int v19;           // esi
	size_t v20;        // ebx
	unsigned char v21; // edx
	int v22;           // ecx
	char valstr[32];   // [esp+Ch] [ebp-3Ch]
	int v24;           // [esp+2Ch] [ebp-1Ch]
	int v25;           // [esp+30h] [ebp-18h]
	int v26;           // [esp+34h] [ebp-14h]
	int v27;           // [esp+38h] [ebp-10h]
	int v28;           // [esp+3Ch] [ebp-Ch]
	int v29;           // [esp+40h] [ebp-8h]
	int v30;           // [esp+44h] [ebp-4h]

	v6 = SStringY[y] + stext[y]._syoff;
	v7 = -(stextsize != 0);
	v8 = x;
	v9 = screen_y_times_768[v6 + 204];
	_LOWORD(v7) = v7 & 0xFEC0;
	v24 = y;
	v26 = x;
	v27 = v7 + 416;
	v10 = x + v7 + 416 + v9;
	v28 = strlen(str);
	v11 = 0;
	v25 = stextsize != 0 ? 577 : 257;
	v30 = 0;
	if (cjustflag) {
		v12 = 0;
		if (v28 > 0) {
			do {
				v13 = (unsigned char)str[v11++];
				v12 += fontkern[fontframe[gbFontTransTbl[v13]]] + 1;
			} while (v11 < v28);
		}
		if (v12 < v25)
			v30 = (v25 - v12) >> 1;
		v10 += v30;
	}
	if (stextsel == v24) {
		if (cjustflag)
			v14 = v27 + v30 + v8 - 20;
		else
			v14 = v27 + v8 - 20;
		CelDecodeOnly(v14, v6 + 205, (BYTE *)pCelBuff, InStoreFlag, 12);
	}
	v29 = 0;
	if (v28 > 0) {
		do {
			v15 = fontframe[gbFontTransTbl[(unsigned char)str[v29]]];
			v16 = v15;
			v17 = v30 + fontkern[v15] + 1;
			v30 += fontkern[v15] + 1;
			if (v15 && v17 <= v25)
				CPrintString(v10, v15, col);
			v18 = fontkern[v16];
			++v29;
			v10 += v18 + 1;
		} while (v29 < v28);
		v8 = v26;
	}
	if (!cjustflag && val >= 0) {
		sprintf(valstr, "%i", val);
		v19 = screen_y_times_768[v6 + 204] - v8 + 656;
		v20 = strlen(valstr);
		while ((--v20 & 0x80000000) == 0) {
			v21 = fontframe[gbFontTransTbl[(unsigned char)valstr[v20]]];
			v19 += -1 - fontkern[v21];
			if (fontframe[gbFontTransTbl[(unsigned char)valstr[v20]]])
				CPrintString(v19, v21, col);
		}
		v8 = v26;
	}
	if (stextsel == v24) {
		if (cjustflag)
			v22 = v27 + v30 + v8 + 4;
		else
			v22 = 660 - v8;
		CelDecodeOnly(v22, v6 + 205, (BYTE *)pCelBuff, InStoreFlag, 12);
	}
}
// 6A09E0: using guessed type char stextsize;
// 6A8A28: using guessed type int stextsel;
// 457BD6: using guessed type char valstr[32];

void DrawSLine(int y)
{
	int xy, yy, width, line;

	if (stextsize == 1) {
		xy = SCREENXY(26, 25);
		yy = screen_y_times_768[SStringY[y] + 198] + 26 + 64;
		width = 586 / 4;
		line = 768 - 586;
	} else {
		xy = SCREENXY(346, 25);
		yy = screen_y_times_768[SStringY[y] + 198] + 346 + 64;
		width = 266 / 4;
		line = 768 - 266;
	}

	/// ASSERT: assert(gpBuffer);

#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
	__asm {
		mov		esi, gpBuffer
		mov		edi, esi
		add		esi, xy
		add		edi, yy
		mov		ebx, line
		mov		edx, 3
	copyline:
		mov		ecx, width
		rep movsd
		movsw
		add		esi, ebx
		add		edi, ebx
		dec		edx
		jnz		copyline
	}
#else
	int i;
	BYTE *src, *dst;

	src = &gpBuffer[xy];
	dst = &gpBuffer[yy];

	for (i = 0; i < 3; i++, src += 768, dst += 768)
		memcpy(dst, src, 768 - line);
#endif
}
// 6A09E0: using guessed type char stextsize;

void DrawSArrows(int y1, int y2)
{
	int *v2; // ebp
	int v3;  // ebx
	int v4;  // edi
	int v5;  // esi
	int v6;  // eax
	int v7;  // eax

	v2 = &SStringY[y2];
	v3 = y1;
	v4 = SStringY[y1] + 204;
	v5 = *v2 + 204;
	if (stextscrlubtn == -1)
		CelDecodeOnly(665, v4, (BYTE *)pSTextSlidCels, 10, 12);
	else
		CelDecodeOnly(665, v4, (BYTE *)pSTextSlidCels, 12, 12);
	if (stextscrldbtn == -1)
		CelDecodeOnly(665, v5, (BYTE *)pSTextSlidCels, 9, 12);
	else
		CelDecodeOnly(665, v5, (BYTE *)pSTextSlidCels, 11, 12);
	while (1) {
		v4 += 12;
		if (v4 >= v5)
			break;
		CelDecodeOnly(665, v4, (BYTE *)pSTextSlidCels, 14, 12);
	}
	v6 = stextsel;
	if (stextsel == 22)
		v6 = stextlhold;
	if (storenumh <= 1)
		v7 = 0;
	else
		v7 = (*v2 - SStringY[v3] - 24) * (1000 * (stextsval + ((v6 - stextup) >> 2)) / (storenumh - 1)) / 1000;
	CelDecodeOnly(665, SStringY[v3 + 1] + v7 + 204, (BYTE *)pSTextSlidCels, 13, 12);
}
// 69F108: using guessed type int stextup;
// 69F10C: using guessed type int storenumh;
// 69F110: using guessed type int stextlhold;
// 6A8A28: using guessed type int stextsel;
// 6A8A2C: using guessed type char stextscrldbtn;
// 6AA704: using guessed type char stextscrlubtn;

void DrawSTextHelp()
{
	stextsel = -1;
	stextsize = 1;
}
// 6A09E0: using guessed type char stextsize;
// 6A8A28: using guessed type int stextsel;

void ClearSText(int s, int e)
{
	int i;

	for (i = s; i < e; i++) {
		stext[i]._sx = 0;
		stext[i]._syoff = 0;
		stext[i]._sstr[0] = 0;
		stext[i]._sjust = 0;
		stext[i]._sclr = 0;
		stext[i]._sline = 0;
		stext[i]._ssel = 0;
		stext[i]._sval = -1;
	}
}

void AddSLine(int y)
{
	stext[y]._sx = 0;
	stext[y]._syoff = 0;
	stext[y]._sstr[0] = 0;
	stext[y]._sline = 1;
}

void AddSTextVal(int y, int val)
{
	stext[y]._sval = val;
}

void OffsetSTextY(int y, int yo)
{
	stext[y]._syoff = yo;
}

void AddSText(int x, int y, int j, char *str, char clr, int sel)
{
	stext[y]._sx = x;
	stext[y]._syoff = 0;
	strcpy(stext[y]._sstr, str);
	stext[y]._sjust = j;
	stext[y]._sclr = clr;
	stext[y]._sline = 0;
	stext[y]._ssel = sel;
}

void StoreAutoPlace()
{
	int v0;         // edi
	int v1;         // eax
	int v2;         // edx
	ItemStruct *v3; // ebp
	int v4;         // esi
	int v5;         // esi
	int v6;         // esi
	int v7;         // esi
	int v8;         // esi
	int v9;         // esi
	int v10;        // esi
	int v11;        // esi
	int *v12;       // esi
	int v13;        // esi
	int v14;        // esi
	int v15;        // esi
	int v16;        // esi
	int v17;        // esi
	signed int v19; // [esp+10h] [ebp-Ch]
	int v20;        // [esp+14h] [ebp-8h]
	int v21;        // [esp+18h] [ebp-4h]

	SetICursor(plr[myplr].HoldItem._iCurs + CURSOR_FIRSTITEM);
	v0 = icursH28;
	v1 = 0;
	v21 = icursW28;
	v20 = icursH28;
	if (icursW28 == 1) {
		if (icursH28 == 1) {
			v2 = myplr;
			if (plr[myplr].HoldItem._iStatFlag && AllItemsList[plr[v2].HoldItem.IDidx].iUsable) {
				v19 = 0;
				v3 = plr[v2].SpdList;
				do {
					if (v1)
						break;
					if (v3->_itype == -1) {
						qmemcpy(v3, &plr[v2].HoldItem, sizeof(ItemStruct));
						v0 = v20;
						v1 = 1;
					}
					++v19;
					++v3;
				} while (v19 < 8);
			}
			v4 = 30;
			do {
				if (v1)
					break;
				v1 = AutoPlace(myplr, v4++, 1, 1, 1);
			} while (v4 <= 39);
			v5 = 20;
			do {
				if (v1)
					break;
				v1 = AutoPlace(myplr, v5++, 1, 1, 1);
			} while (v5 <= 29);
			v6 = 10;
			do {
				if (v1)
					break;
				v1 = AutoPlace(myplr, v6++, 1, 1, 1);
			} while (v6 <= 19);
			v7 = 0;
			while (!v1) {
				v1 = AutoPlace(myplr, v7++, 1, 1, 1);
				if (v7 > 9)
					goto LABEL_22;
			}
		} else {
		LABEL_22:
			if (v0 == 2) {
				v8 = 29;
				do {
					if (v1)
						break;
					v1 = AutoPlace(myplr, v8--, 1, 2, 1);
				} while (v8 >= 20);
				v9 = 9;
				do {
					if (v1)
						break;
					v1 = AutoPlace(myplr, v9--, 1, 2, 1);
				} while (v9 >= 0);
				v10 = 19;
				while (!v1) {
					v1 = AutoPlace(myplr, v10--, 1, 2, 1);
					if (v10 < 10)
						goto LABEL_32;
				}
			} else {
			LABEL_32:
				if (v0 == 3) {
					v11 = 0;
					while (!v1) {
						v1 = AutoPlace(myplr, v11++, 1, 3, 1);
						if (v11 >= 20)
							goto LABEL_36;
					}
				}
			}
		}
	} else {
	LABEL_36:
		if (v21 == 2) {
			if (v0 == 2) {
				v12 = AP2x2Tbl;
				do {
					if (v1)
						break;
					v1 = AutoPlace(myplr, *v12, 2, 2, 1);
					++v12;
				} while ((signed int)v12 < (signed int)&AP2x2Tbl[10]);
				v13 = 21;
				do {
					if (v1)
						break;
					v1 = AutoPlace(myplr, v13, 2, 2, 1);
					v13 += 2;
				} while (v13 < 29);
				v14 = 1;
				do {
					if (v1)
						break;
					v1 = AutoPlace(myplr, v14, 2, 2, 1);
					v14 += 2;
				} while (v14 < 9);
				v15 = 10;
				while (!v1) {
					v1 = AutoPlace(myplr, v15++, 2, 2, 1);
					if (v15 >= 19)
						goto LABEL_50;
				}
			} else {
			LABEL_50:
				if (v0 == 3) {
					v16 = 0;
					do {
						if (v1)
							break;
						v1 = AutoPlace(myplr, v16++, 2, 3, 1);
					} while (v16 < 9);
					v17 = 10;
					do {
						if (v1)
							break;
						v1 = AutoPlace(myplr, v17++, 2, 3, 1);
					} while (v17 < 19);
				}
			}
		}
	}
}
// 48E9A8: using guessed type int AP2x2Tbl[10];

void S_StartSmith()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 1, 1u, "Welcome to the", COL_GOLD, 0);
	AddSText(0, 3, 1u, "Blacksmith's shop", COL_GOLD, 0);
	AddSText(0, 7, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 10, 1u, "Talk to Griswold", COL_BLUE, 1);
	AddSText(0, 12, 1u, "Buy basic items", COL_WHITE, 1);
	AddSText(0, 14, 1u, "Buy premium items", COL_WHITE, 1);
	AddSText(0, 16, 1u, "Sell items", COL_WHITE, 1);
	AddSText(0, 18, 1u, "Repair items", COL_WHITE, 1);
	AddSText(0, 20, 1u, "Leave the shop", COL_WHITE, 1);
	AddSLine(5);
	storenumh = 20;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_ScrollSBuy(int idx)
{
	int y;
	char clr;

	ClearSText(5, 21);
	stextup = 5;

	for (y = 5; y < 20; y += 4) {
		if (smithitem[idx]._itype != -1) {
			clr = COL_WHITE;
			if (smithitem[idx]._iMagical) {
				clr = COL_BLUE;
			}

			if (!smithitem[idx]._iStatFlag) {
				clr = COL_RED;
			}

			if (smithitem[idx]._iMagical) {
				AddSText(20, y, 0, smithitem[idx]._iIName, clr, 1);
			} else {
				AddSText(20, y, 0, smithitem[idx]._iName, clr, 1);
			}

			AddSTextVal(y, smithitem[idx]._iIvalue);
			PrintStoreItem(&smithitem[idx], y + 1, clr);
			stextdown = y;
			idx++;
		}
	}

	if (!stext[stextsel]._ssel && stextsel != 22)
		stextsel = stextdown;
}
// 69F108: using guessed type int stextup;
// 6A8A28: using guessed type int stextsel;
// 6AA700: using guessed type int stextdown;

void PrintStoreItem(ItemStruct *x, int l, char iclr)
{
	ItemStruct *v3;   // esi
	char v5;          // cl
	char v6;          // cl
	int v7;           // eax
	char v8;          // al
	unsigned char v9; // al
	char v10;         // al
	int v11;          // edi
	char sstr[128];   // [esp+Ch] [ebp-84h]
	int y;            // [esp+8Ch] [ebp-4h]

	sstr[0] = 0;
	v3 = x;
	y = l;
	if (x->_iIdentified) {
		if (x->_iMagical != ITEM_QUALITY_UNIQUE) {
			v5 = x->_iPrePower;
			if (v5 != -1) {
				PrintItemPower(v5, v3);
				strcat(sstr, tempstr);
			}
		}
		v6 = v3->_iSufPower;
		if (v6 != -1) {
			PrintItemPower(v6, v3);
			if (sstr[0])
				strcat(sstr, ",  ");
			strcat(sstr, tempstr);
		}
	}
	if (v3->_iMiscId == IMISC_STAFF && v3->_iMaxCharges) {
		sprintf(tempstr, "Charges: %i/%i", v3->_iCharges, v3->_iMaxCharges);
		if (sstr[0])
			strcat(sstr, ",  ");
		strcat(sstr, tempstr);
	}
	if (sstr[0])
		AddSText(40, y++, 0, sstr, iclr, 0);
	sstr[0] = 0;
	if (v3->_iClass == ICLASS_WEAPON)
		sprintf(sstr, "Damage: %i-%i  ", v3->_iMinDam, v3->_iMaxDam);
	if (v3->_iClass == ICLASS_ARMOR)
		sprintf(sstr, "Armor: %i  ", v3->_iAC);
	v7 = v3->_iMaxDur;
	if (v7 != 255 && v7) {
		sprintf(tempstr, "Dur: %i/%i,  ", v3->_iDurability, v3->_iMaxDur);
		strcat(sstr, tempstr);
	} else {
		strcat(sstr, "Indestructible,  ");
	}
	if (!v3->_itype)
		sstr[0] = 0;
	if (v3->_iMinStr + (unsigned char)v3->_iMinMag + v3->_iMinDex) {
		strcpy(tempstr, "Required:");
		v8 = v3->_iMinStr;
		if (v8)
			sprintf(tempstr, "%s %i Str", tempstr, v8);
		v9 = v3->_iMinMag;
		if (v9)
			sprintf(tempstr, "%s %i Mag", tempstr, v9);
		v10 = v3->_iMinDex;
		if (v10)
			sprintf(tempstr, "%s %i Dex", tempstr, v10);
		strcat(sstr, tempstr);
	} else {
		strcat(sstr, "No required attributes");
	}
	v11 = y;
	AddSText(40, y, 0, sstr, iclr, 0);
	if (v3->_iMagical == ITEM_QUALITY_UNIQUE) {
		if (v3->_iIdentified)
			AddSText(40, v11 + 1, 0, "Unique Item", iclr, 0);
	}
}

void S_StartSBuy()
{
	int i;

	stextsize = 1;
	stextscrl = 1;
	stextsval = 0;
	sprintf(tempstr, "I have these items for sale :           Your gold : %i", plr[myplr]._pGold);
	AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
	AddSLine(3);
	AddSLine(21);
	S_ScrollSBuy(stextsval);
	AddSText(0, 22, 1, "Back", COL_WHITE, 0);
	OffsetSTextY(22, 6);
	storenumh = 0;
	for (i = 0; smithitem[i]._itype != -1; i++)
		storenumh++;
	stextsmax = storenumh - 4;
	if (stextsmax < 0)
		stextsmax = 0;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

void S_ScrollSPBuy(int idx)
{
	int v1;   // esi
	int v2;   // edi
	int v3;   // eax
	int v4;   // esi
	int *v5;  // ecx
	char *v6; // esi
	int iclr; // [esp+Ch] [ebp-4h]

	v1 = idx;
	v2 = 5;
	ClearSText(5, 21);
	v3 = v1;
	v4 = 0;
	stextup = 5;
	if (v3) {
		v5 = &premiumitem[0]._itype;
		do {
			if (*v5 != -1)
				--v3;
			++v4;
			v5 += 92;
		} while (v3);
	}
	v6 = &premiumitem[v4]._iMagical;
	do {
		if ((signed int)v6 >= (signed int)&premiumitem[6]._iMagical)
			break;
		if (*((_DWORD *)v6 - 13) == -1) {
			v2 -= 4;
		} else {
			_LOBYTE(iclr) = COL_WHITE;
			if (*v6)
				_LOBYTE(iclr) = COL_BLUE;
			if (!*((_DWORD *)v6 + 74))
				_LOBYTE(iclr) = COL_RED;
			AddSText(20, v2, 0, v6 + 65, iclr, 1);
			AddSTextVal(v2, *((_DWORD *)v6 + 35));
			PrintStoreItem((ItemStruct *)(v6 - 60), v2 + 1, iclr);
			stextdown = v2;
		}
		v2 += 4;
		v6 += 368;
	} while (v2 < 20);
	if (!stext[stextsel]._ssel && stextsel != 22)
		stextsel = stextdown;
}
// 69F108: using guessed type int stextup;
// 6A8A28: using guessed type int stextsel;
// 6AA700: using guessed type int stextdown;

BOOL S_StartSPBuy()
{
	int i;

	storenumh = 0;
	for (i = 0; i < 6; i++) {
		if (premiumitem[i]._itype != -1)
			storenumh++;
	}
	if (!storenumh) {
		StartStore(STORE_SMITH);
		stextsel = 14;
		return FALSE;
	}

	stextsize = 1;
	stextscrl = 1;
	stextsval = 0;

	sprintf(tempstr, "I have these premium items for sale :   Your gold : %i", plr[myplr]._pGold);
	AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
	AddSLine(3);
	AddSLine(21);
	AddSText(0, 22, 1, "Back", COL_WHITE, 0);
	OffsetSTextY(22, 6);

	stextsmax = storenumh - 4;
	if (stextsmax < 0)
		stextsmax = 0;

	S_ScrollSPBuy(stextsval);

	return TRUE;
}
// 69F10C: using guessed type int storenumh;
// 69FB38: using guessed type int talker;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A28: using guessed type int stextsel;

BOOL SmithSellOk(int i)
{
	if (plr[myplr].InvList[i]._itype == ITYPE_NONE)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_MISC)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_GOLD)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_0E)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_STAFF)
		return FALSE;
	if (plr[myplr].InvList[i].IDidx == IDI_LAZSTAFF)
		return FALSE;

	return TRUE;
}

void S_ScrollSSell(int idx)
{
	char clr;
	int y;

	ClearSText(5, 21);
	stextup = 5;
	for (y = 5; y < 20; y += 4) {
		if (idx >= storenumh)
			break;
		if (storehold[idx]._itype != -1) {
			clr = 0;
			if (storehold[idx]._iMagical)
				clr = 1;
			if (!storehold[idx]._iStatFlag)
				clr = 2;
			if (storehold[idx]._iMagical && storehold[idx]._iIdentified) {
				AddSText(20, y, 0, storehold[idx]._iIName, clr, 1);
				AddSTextVal(y, storehold[idx]._iIvalue);
			} else {
				AddSText(20, y, 0, storehold[idx]._iName, clr, 1);
				AddSTextVal(y, storehold[idx]._ivalue);
			}
			PrintStoreItem(&storehold[idx], y + 1, clr);
			stextdown = y;
		}
		idx++;
	}

	stextsmax = storenumh - 4;
	if (stextsmax < 0)
		stextsmax = 0;
}
// 69F108: using guessed type int stextup;
// 69F10C: using guessed type int storenumh;
// 6A09E4: using guessed type int stextsmax;
// 6AA700: using guessed type int stextdown;

void S_StartSSell()
{
	int i;
	BOOL sellok;

	stextsize = 1;
	sellok = FALSE;
	storenumh = 0;

	for (i = 0; i < 48; i++)
		storehold[i]._itype = -1;

	for (i = 0; i < plr[myplr]._pNumInv; i++) {
		if (SmithSellOk(i)) {
			sellok = TRUE;
			storehold[storenumh] = plr[myplr].InvList[i];

			if (storehold[storenumh]._iMagical != ITEM_QUALITY_NORMAL && storehold[storenumh]._iIdentified)
				storehold[storenumh]._ivalue = storehold[storenumh]._iIvalue;

			if (!(storehold[storenumh]._ivalue >>= 2))
				storehold[storenumh]._ivalue = 1;

			storehold[storenumh]._iIvalue = storehold[storenumh]._ivalue;
			storehidx[storenumh++] = i;
		}
	}

	if (!sellok) {
		stextscrl = 0;
		sprintf(tempstr, "You have nothing I want.            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	} else {
		stextscrl = 1;
		stextsval = 0;
		stextsmax = plr[myplr]._pNumInv;
		sprintf(tempstr, "Which item is for sale?            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		S_ScrollSSell(stextsval);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	}
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

BOOL SmithRepairOk(int i)
{
	if (plr[myplr].InvList[i]._itype == ITYPE_NONE)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_MISC)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_GOLD)
		return FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_0E)
		return FALSE;
	if (plr[myplr].InvList[i]._iDurability == plr[myplr].InvList[i]._iMaxDur)
		return FALSE;

	return TRUE;
}

void S_StartSRepair()
{
	int v0;  // ebp
	int *v1; // eax
	int v2;  // esi
	int v3;  // eax
	int v4;  // eax
	int v5;  // eax
	int v6;  // eax
	int v7;  // edi
	//int v8; // eax
	int v9;         // esi
	int v10;        // eax
	int v11;        // [esp-4h] [ebp-1Ch]
	signed int v12; // [esp+10h] [ebp-8h]
	int v13;        // [esp+14h] [ebp-4h]

	v0 = 0;
	stextsize = 1;
	v12 = 0;
	storenumh = 0;
	v1 = &storehold[0]._itype;
	do {
		*v1 = -1;
		v1 += 92;
	} while ((signed int)v1 < (signed int)&storehold[48]._itype);
	v2 = myplr;
	v3 = myplr;
	if (plr[myplr].InvBody[INVLOC_HEAD]._itype != -1 && plr[v3].InvBody[INVLOC_HEAD]._iDurability != plr[v3].InvBody[INVLOC_HEAD]._iMaxDur) {
		v12 = 1;
		AddStoreHoldRepair(plr[v3].InvBody, -1);
		v2 = myplr;
	}
	v4 = v2;
	if (plr[v2].InvBody[INVLOC_CHEST]._itype != -1 && plr[v4].InvBody[INVLOC_CHEST]._iDurability != plr[v4].InvBody[INVLOC_CHEST]._iMaxDur) {
		v12 = 1;
		AddStoreHoldRepair(&plr[v4].InvBody[INVLOC_CHEST], -2);
		v2 = myplr;
	}
	v5 = v2;
	if (plr[v2].InvBody[INVLOC_HAND_LEFT]._itype != -1 && plr[v5].InvBody[INVLOC_HAND_LEFT]._iDurability != plr[v5].InvBody[INVLOC_HAND_LEFT]._iMaxDur) {
		v12 = 1;
		AddStoreHoldRepair(&plr[v5].InvBody[INVLOC_HAND_LEFT], -3);
		v2 = myplr;
	}
	v6 = v2;
	if (plr[v2].InvBody[INVLOC_HAND_RIGHT]._itype != -1 && plr[v6].InvBody[INVLOC_HAND_RIGHT]._iDurability != plr[v6].InvBody[INVLOC_HAND_RIGHT]._iMaxDur) {
		v12 = 1;
		AddStoreHoldRepair(&plr[v6].InvBody[INVLOC_HAND_RIGHT], -4);
		v2 = myplr;
	}
	v7 = 21720 * v2;
	if (plr[v2]._pNumInv > 0) {
		v13 = 0;
		do {
			//_LOBYTE(v8) = SmithRepairOk(v0);
			if (SmithRepairOk(v0)) {
				v12 = 1;
				AddStoreHoldRepair((ItemStruct *)((char *)&plr[0].InvList[v13] + v7), v0);
				v2 = myplr;
			}
			++v13;
			v7 = 21720 * v2;
			++v0;
		} while (v0 < plr[v2]._pNumInv);
	}
	v9 = v2;
	v11 = plr[v9]._pGold;
	if (v12) {
		stextsval = 0;
		v10 = plr[v9]._pNumInv;
		stextscrl = 1;
		stextsmax = v10;
		sprintf(tempstr, "Repair which item?            Your gold : %i", v11);
		AddSText(0, 1, 1u, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		S_ScrollSSell(stextsval);
	} else {
		stextscrl = 0;
		sprintf(tempstr, "You have nothing to repair.            Your gold : %i", v11);
		AddSText(0, 1, 1u, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
	}
	AddSText(0, 22, 1u, "Back", COL_WHITE, 1);
	OffsetSTextY(22, 6);
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

void AddStoreHoldRepair(ItemStruct *itm, int i)
{
	ItemStruct *item;
	int v;

	item = &storehold[storenumh];
	storehold[storenumh] = *itm;
	if (item->_iMagical != ITEM_QUALITY_NORMAL && item->_iIdentified)
		item->_ivalue = 30 * item->_iIvalue / 100;
	v = item->_ivalue * (100 * (item->_iMaxDur - item->_iDurability) / item->_iMaxDur) / 100;
	if (!v) {
		if (item->_iMagical != ITEM_QUALITY_NORMAL && item->_iIdentified)
			return;
		v = 1;
	}
	if (v > 1)
		v >>= 1;
	item->_iIvalue = v;
	item->_ivalue = v;
	storehidx[storenumh] = i;
	storenumh++;
}
// 69F10C: using guessed type int storenumh;

void S_StartWitch()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 2, 1u, "Witch's shack", COL_GOLD, 0);
	AddSText(0, 9, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 12, 1u, "Talk to Adria", COL_BLUE, 1);
	AddSText(0, 14, 1u, "Buy items", COL_WHITE, 1);
	AddSText(0, 16, 1u, "Sell items", COL_WHITE, 1);
	AddSText(0, 18, 1u, "Recharge staves", COL_WHITE, 1);
	AddSText(0, 20, 1u, "Leave the shack", COL_WHITE, 1);
	AddSLine(5);
	storenumh = 20;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_ScrollWBuy(int idx)
{
	int v1;   // esi
	int v2;   // edi
	char *v3; // esi
	char *v4; // eax
	int iclr; // [esp+Ch] [ebp-4h]

	v1 = idx;
	v2 = 5;
	ClearSText(5, 21);
	v3 = &witchitem[v1]._iMagical;
	stextup = 5;
	do {
		if (*((_DWORD *)v3 - 13) != -1) {
			_LOBYTE(iclr) = 0;
			if (*v3)
				_LOBYTE(iclr) = 1;
			if (!*((_DWORD *)v3 + 74))
				_LOBYTE(iclr) = 2;
			v4 = v3 + 65;
			if (!*v3)
				v4 = v3 + 1;
			AddSText(20, v2, 0, v4, iclr, 1);
			AddSTextVal(v2, *((_DWORD *)v3 + 35));
			PrintStoreItem((ItemStruct *)(v3 - 60), v2 + 1, iclr);
			stextdown = v2;
			v3 += 368;
		}
		v2 += 4;
	} while (v2 < 20);
	if (!stext[stextsel]._ssel && stextsel != 22)
		stextsel = stextdown;
}
// 69F108: using guessed type int stextup;
// 6A8A28: using guessed type int stextsel;
// 6AA700: using guessed type int stextdown;

void S_StartWBuy()
{
	int v0;  // ST10_4
	int v1;  // eax
	int *v2; // ecx

	v0 = plr[myplr]._pGold;
	stextsize = 1;
	stextscrl = 1;
	stextsval = 0;
	stextsmax = 20;
	sprintf(tempstr, "I have these items for sale :           Your gold : %i", v0);
	AddSText(0, 1, 1u, tempstr, COL_GOLD, 0);
	AddSLine(3);
	AddSLine(21);
	S_ScrollWBuy(stextsval);
	AddSText(0, 22, 1u, "Back", COL_WHITE, 0);
	OffsetSTextY(22, 6);
	v1 = 0;
	storenumh = 0;
	if (witchitem[0]._itype != -1) {
		v2 = &witchitem[0]._itype;
		do {
			v2 += 92;
			++v1;
		} while (*v2 != -1);
		storenumh = v1;
	}
	stextsmax = v1 - 4;
	if (v1 - 4 < 0)
		stextsmax = 0;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

BOOL WitchSellOk(int i)
{
	BOOL rv;
	ItemStruct *pI;

	rv = FALSE;

	if (i >= 0)
		pI = &plr[myplr].InvList[i];
	else
		pI = &plr[myplr].SpdList[-(i + 1)];

	if (pI->_itype == ITYPE_MISC)
		rv = TRUE;
	if (pI->_itype == ITYPE_STAFF)
		rv = TRUE;
	if (pI->IDidx >= IDI_FIRSTQUEST && pI->IDidx <= IDI_LASTQUEST)
		rv = FALSE;
	if (pI->IDidx == IDI_LAZSTAFF)
		rv = FALSE;
	return rv;
}

void S_StartWSell()
{
	int i;
	BOOL sellok;

	stextsize = 1;
	sellok = FALSE;
	storenumh = 0;

	for (i = 0; i < 48; i++)
		storehold[i]._itype = -1;

	for (i = 0; i < plr[myplr]._pNumInv; i++) {
		if (WitchSellOk(i)) {
			sellok = TRUE;
			storehold[storenumh] = plr[myplr].InvList[i];

			if (storehold[storenumh]._iMagical != ITEM_QUALITY_NORMAL && storehold[storenumh]._iIdentified)
				storehold[storenumh]._ivalue = storehold[storenumh]._iIvalue;

			if (!(storehold[storenumh]._ivalue >>= 2))
				storehold[storenumh]._ivalue = 1;

			storehold[storenumh]._iIvalue = storehold[storenumh]._ivalue;
			storehidx[storenumh++] = i;
		}
	}

	for (i = 0; i < MAXBELTITEMS; i++) {
		if (plr[myplr].SpdList[i]._itype != -1 && WitchSellOk(-(i + 1))) {
			sellok = TRUE;
			storehold[storenumh] = plr[myplr].SpdList[i];

			if (storehold[storenumh]._iMagical != ITEM_QUALITY_NORMAL && storehold[storenumh]._iIdentified)
				storehold[storenumh]._ivalue = storehold[storenumh]._iIvalue;

			if (!(storehold[storenumh]._ivalue >>= 2))
				storehold[storenumh]._ivalue = 1;

			storehold[storenumh]._iIvalue = storehold[storenumh]._ivalue;
			storehidx[storenumh++] = -(i + 1);
		}
	}

	if (!sellok) {
		stextscrl = 0;
		sprintf(tempstr, "You have nothing I want.            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	} else {
		stextscrl = 1;
		stextsval = 0;
		stextsmax = plr[myplr]._pNumInv;
		sprintf(tempstr, "Which item is for sale?            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		S_ScrollSSell(stextsval);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	}
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

BOOL WitchRechargeOk(int i)
{
	BOOL rv;

	rv = FALSE;
	if (plr[myplr].InvList[i]._itype == ITYPE_STAFF
	    && plr[myplr].InvList[i]._iCharges != plr[myplr].InvList[i]._iMaxCharges) {
		rv = TRUE;
	}
	return rv;
}

void AddStoreHoldRecharge(ItemStruct itm, int i)
{
	storehold[storenumh] = itm;
	storehold[storenumh]._ivalue += spelldata[itm._iSpell].sStaffCost;
	storehold[storenumh]._ivalue = storehold[storenumh]._ivalue * (100 * (storehold[storenumh]._iMaxCharges - storehold[storenumh]._iCharges) / storehold[storenumh]._iMaxCharges) / 100 >> 1;
	storehold[storenumh]._iIvalue = storehold[storenumh]._ivalue;
	storehidx[storenumh] = i;
	storenumh++;
}
// 69F108: using guessed type int stextup;
// 69F10C: using guessed type int storenumh;

void S_StartWRecharge()
{
	int i;
	BOOL rechargeok;

	stextsize = 1;
	rechargeok = FALSE;
	storenumh = 0;

	for (i = 0; i < 48; i++) {
		storehold[i]._itype = ITYPE_NONE;
	}

	if (plr[myplr].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_STAFF
	    && plr[myplr].InvBody[INVLOC_HAND_LEFT]._iCharges != plr[myplr].InvBody[INVLOC_HAND_LEFT]._iMaxCharges) {
		rechargeok = TRUE;
		AddStoreHoldRecharge(plr[myplr].InvBody[INVLOC_HAND_LEFT], -1);
	}

	for (i = 0; i < plr[myplr]._pNumInv; i++) {
		if (WitchRechargeOk(i)) {
			rechargeok = TRUE;
			AddStoreHoldRecharge(plr[myplr].InvList[i], i);
		}
	}

	if (!rechargeok) {
		stextscrl = 0;
		sprintf(tempstr, "You have nothing to recharge.            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	} else {
		stextscrl = 1;
		stextsval = 0;
		stextsmax = plr[myplr]._pNumInv;
		sprintf(tempstr, "Recharge which item?            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		S_ScrollSSell(stextsval);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	}
}

void S_StartNoMoney()
{
	StartStore((unsigned char)stextshold);
	stextscrl = 0;
	stextsize = 1;
	ClearSText(5, 23);
	AddSText(0, 14, 1u, "You do not have enough gold", COL_WHITE, 1);
}
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_StartNoRoom()
{
	StartStore((unsigned char)stextshold);
	stextscrl = 0;
	ClearSText(5, 23);
	AddSText(0, 14, 1u, "You do not have enough room in inventory", COL_WHITE, 1);
}
// 6A6BB8: using guessed type int stextscrl;

void S_StartConfirm()
{
	BOOL idprint; // esi
	char iclr;    // [esp+Ch] [ebp-4h]

	StartStore(stextshold);
	stextscrl = 0;
	ClearSText(5, 23);
	iclr = COL_WHITE;

	if (plr[myplr].HoldItem._iMagical != ITEM_QUALITY_NORMAL)
		iclr = COL_BLUE;
	if (!plr[myplr].HoldItem._iStatFlag)
		iclr = COL_RED;

	idprint = plr[myplr].HoldItem._iMagical != ITEM_QUALITY_NORMAL;

	if (stextshold == STORE_SIDENTIFY)
		idprint = FALSE;
	if (plr[myplr].HoldItem._iMagical != ITEM_QUALITY_NORMAL && !plr[myplr].HoldItem._iIdentified) {
		if (stextshold == STORE_SSELL)
			idprint = FALSE;
		if (stextshold == STORE_WSELL)
			idprint = FALSE;
		if (stextshold == STORE_SREPAIR)
			idprint = FALSE;
		if (stextshold == STORE_WRECHARGE)
			idprint = FALSE;
	}
	if (idprint)
		AddSText(20, 8, 0, plr[myplr].HoldItem._iIName, iclr, 0);
	else
		AddSText(20, 8, 0, plr[myplr].HoldItem._iName, iclr, 0);

	AddSTextVal(8, plr[myplr].HoldItem._iIvalue);
	PrintStoreItem(&plr[myplr].HoldItem, 9, iclr);

	if (stextshold > STORE_WRECHARGE) {
		if (stextshold == STORE_BBOY) {
			strcpy(tempstr, "Do we have a deal?");
			goto LABEL_37;
		}
		if (stextshold != STORE_HBUY) {
			if (stextshold == STORE_SIDENTIFY) {
				strcpy(tempstr, "Are you sure you want to identify this item?");
				goto LABEL_37;
			}
			if (stextshold != STORE_SPBUY)
				goto LABEL_37;
		}
	LABEL_34:
		strcpy(tempstr, "Are you sure you want to buy this item?");
		goto LABEL_37;
	}
	switch (stextshold) {
	case STORE_WRECHARGE:
		strcpy(tempstr, "Are you sure you want to recharge this item?");
		break;
	case STORE_SBUY:
		goto LABEL_34;
	case STORE_SSELL:
	LABEL_27:
		strcpy(tempstr, "Are you sure you want to sell this item?");
		break;
	case STORE_SREPAIR:
		strcpy(tempstr, "Are you sure you want to repair this item?");
		break;
	case STORE_WBUY:
		goto LABEL_34;
	case STORE_WSELL:
		goto LABEL_27;
	}
LABEL_37:
	AddSText(0, 15, 1u, tempstr, COL_WHITE, 0);
	AddSText(0, 18, 1u, "Yes", COL_WHITE, 1);
	AddSText(0, 20, 1u, "No", COL_WHITE, 1);
}
// 6A6BB8: using guessed type int stextscrl;

void S_StartBoy()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 2, 1u, "Wirt the Peg-legged boy", COL_GOLD, 0);
	AddSLine(5);
	if (boyitem._itype != -1) {
		AddSText(0, 8, 1u, "Talk to Wirt", COL_BLUE, 1);
		AddSText(0, 12, 1u, "I have something for sale,", COL_GOLD, 0);
		AddSText(0, 14, 1u, "but it will cost 50 gold", COL_GOLD, 0);
		AddSText(0, 16, 1u, "just to take a look. ", COL_GOLD, 0);
		AddSText(0, 18, 1u, "What have you got?", COL_WHITE, 1);
		AddSText(0, 20, 1u, "Say goodbye", COL_WHITE, 1);
	} else {
		AddSText(0, 12, 1u, "Talk to Wirt", COL_BLUE, 1);
		AddSText(0, 18, 1u, "Say goodbye", COL_WHITE, 1);
	}
}
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_StartBBoy()
{
	int iclr; // esi

	stextsize = 1;
	stextscrl = 0;
	sprintf(tempstr, "I have this item for sale :           Your gold : %i", plr[myplr]._pGold);
	AddSText(0, 1, 1u, tempstr, COL_GOLD, 0);
	AddSLine(3);
	AddSLine(21);
	iclr = COL_WHITE;

	if (boyitem._iMagical != ITEM_QUALITY_NORMAL)
		iclr = COL_BLUE;
	if (!boyitem._iStatFlag)
		iclr = COL_RED;
	if (boyitem._iMagical != ITEM_QUALITY_NORMAL)
		AddSText(20, 10, 0, boyitem._iIName, iclr, 1);
	else
		AddSText(20, 10, 0, boyitem._iName, iclr, 1);

	AddSTextVal(10, boyitem._iIvalue + (boyitem._iIvalue >> 1));
	PrintStoreItem(&boyitem, 11, iclr);
	AddSText(0, 22, 1u, "Leave", COL_WHITE, 1);
	OffsetSTextY(22, 6);
}
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_StartHealer()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 1, 1u, "Welcome to the", COL_GOLD, 0);
	AddSText(0, 3, 1u, "Healer's home", COL_GOLD, 0);
	AddSText(0, 9, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 12, 1u, "Talk to Pepin", COL_BLUE, 1);
	AddSText(0, 14, 1u, "Receive healing", COL_WHITE, 1);
	AddSText(0, 16, 1u, "Buy items", COL_WHITE, 1);
	AddSText(0, 18, 1u, "Leave Healer's home", COL_WHITE, 1);
	AddSLine(5);
	storenumh = 20;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_ScrollHBuy(int idx)
{
	int i;
	char iclr;

	ClearSText(5, 21);
	stextup = 5;
	for (i = 5; i < 20; i += 4) {
		if (healitem[idx]._itype != -1) {
			iclr = COL_WHITE;
			if (!healitem[idx]._iStatFlag)
				iclr = COL_RED;
			AddSText(20, i, 0, healitem[idx]._iName, iclr, 1);
			AddSTextVal(i, healitem[idx]._iIvalue);
			PrintStoreItem(&healitem[idx], i + 1, iclr);
			stextdown = i;
			idx++;
		}
	}

	if (!stext[stextsel]._ssel && stextsel != 22)
		stextsel = stextdown;
}
// 69F108: using guessed type int stextup;
// 6A8A28: using guessed type int stextsel;
// 6AA700: using guessed type int stextdown;

void S_StartHBuy()
{
	int v0;  // ST10_4
	int v1;  // eax
	int *v2; // ecx

	v0 = plr[myplr]._pGold;
	stextsize = 1;
	stextscrl = 1;
	stextsval = 0;
	sprintf(tempstr, "I have these items for sale :           Your gold : %i", v0);
	AddSText(0, 1, 1u, tempstr, COL_GOLD, 0);
	AddSLine(3);
	AddSLine(21);
	S_ScrollHBuy(stextsval);
	AddSText(0, 22, 1u, "Back", COL_WHITE, 0);
	OffsetSTextY(22, 6);
	v1 = 0;
	storenumh = 0;
	if (healitem[0]._itype != -1) {
		v2 = &healitem[0]._itype;
		do {
			v2 += 92;
			++v1;
		} while (*v2 != -1);
		storenumh = v1;
	}
	stextsmax = v1 - 4;
	if (v1 - 4 < 0)
		stextsmax = 0;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

void S_StartStory()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 2, 1u, "The Town Elder", COL_GOLD, 0);
	AddSText(0, 9, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 12, 1u, "Talk to Cain", COL_BLUE, 1);
	AddSText(0, 14, 1u, "Identify an item", COL_WHITE, 1);
	AddSText(0, 18, 1u, "Say goodbye", COL_WHITE, 1);
	AddSLine(5);
}
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

BOOL IdItemOk(ItemStruct *i)
{
	if (i->_itype == -1) {
		return FALSE;
	}
	if (i->_iMagical == ITEM_QUALITY_NORMAL) {
		return FALSE;
	}
	return !i->_iIdentified;
}

void AddStoreHoldId(ItemStruct itm, int i)
{
	storehold[storenumh] = itm;
	storehold[storenumh]._ivalue = 100;
	storehold[storenumh]._iIvalue = 100;
	storehidx[storenumh] = i;
	storenumh++;
}
// 69F108: using guessed type int stextup;
// 69F10C: using guessed type int storenumh;

void S_StartSIdentify()
{
	BOOL idok;
	int i;

	idok = FALSE;
	stextsize = 1;
	storenumh = 0;

	for (i = 0; i < 48; i++)
		storehold[i]._itype = -1;

	if (IdItemOk(&plr[myplr].InvBody[INVLOC_HEAD])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_HEAD], -1);
	}
	if (IdItemOk(&plr[myplr].InvBody[INVLOC_CHEST])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_CHEST], -2);
	}
	if (IdItemOk(&plr[myplr].InvBody[INVLOC_HAND_LEFT])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_HAND_LEFT], -3);
	}
	if (IdItemOk(&plr[myplr].InvBody[INVLOC_HAND_RIGHT])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_HAND_RIGHT], -4);
	}
	if (IdItemOk(&plr[myplr].InvBody[INVLOC_RING_LEFT])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_RING_LEFT], -5);
	}
	if (IdItemOk(&plr[myplr].InvBody[INVLOC_RING_RIGHT])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_RING_RIGHT], -6);
	}
	if (IdItemOk(&plr[myplr].InvBody[INVLOC_AMULET])) {
		idok = TRUE;
		AddStoreHoldId(plr[myplr].InvBody[INVLOC_AMULET], -7);
	}

	for (i = 0; i < plr[myplr]._pNumInv; i++) {
		if (IdItemOk(&plr[myplr].InvList[i])) {
			idok = TRUE;
			AddStoreHoldId(plr[myplr].InvList[i], i);
		}
	}

	if (!idok) {
		stextscrl = 0;
		sprintf(tempstr, "You have nothing to identify.            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	} else {
		stextscrl = 1;
		stextsval = 0;
		stextsmax = plr[myplr]._pNumInv;
		sprintf(tempstr, "Identify which item?            Your gold : %i", plr[myplr]._pGold);
		AddSText(0, 1, 1, tempstr, COL_GOLD, 0);
		AddSLine(3);
		AddSLine(21);
		S_ScrollSSell(stextsval);
		AddSText(0, 22, 1, "Back", COL_WHITE, 1);
		OffsetSTextY(22, 6);
	}
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;

void S_StartIdShow()
{
	char iclr; // [esp+4h] [ebp-4h]

	StartStore(stextshold);
	stextscrl = 0;
	ClearSText(5, 23);
	iclr = COL_WHITE;

	if (plr[myplr].HoldItem._iMagical != ITEM_QUALITY_NORMAL)
		iclr = COL_BLUE;
	if (!plr[myplr].HoldItem._iStatFlag)
		iclr = COL_RED;

	AddSText(0, 7, 1u, "This item is:", COL_WHITE, 0);
	AddSText(20, 11, 0, plr[myplr].HoldItem._iIName, iclr, 0);
	PrintStoreItem(&plr[myplr].HoldItem, 12, iclr);
	AddSText(0, 18, 1u, "Done", COL_WHITE, 1);
}
// 6A6BB8: using guessed type int stextscrl;

void S_StartTalk()
{
	int *v0;       // edi
	signed int v1; // eax
	int v2;        // edx
	int *v3;       // ecx
	char **v4;     // ebp
	int v5;        // esi
	int v6;        // ebx
	signed int v7; // [esp-4h] [ebp-1Ch]
	signed int v8; // [esp+10h] [ebp-8h]
	int y;         // [esp+14h] [ebp-4h]

	stextsize = 0;
	stextscrl = 0;
	sprintf(tempstr, "Talk to %s", talkname[talker]);
	AddSText(0, 2, 1u, tempstr, COL_GOLD, 0);
	AddSLine(5);
	v0 = &quests[0]._qlog;
	v1 = 0;
	v2 = 0;
	v3 = &quests[0]._qlog;
	do {
		if (*((_BYTE *)v3 - 18) == 2 && *((_DWORD *)&Qtalklist[0]._qinfra + v2 + 16 * talker) != -1 && *v3)
			++v1;
		v3 += 6;
		++v2;
	} while ((signed int)v3 < (signed int)&quests[16]._qlog);
	if (v1 <= 6) {
		v7 = 15;
		v8 = 2;
	} else {
		v1 >>= 1;
		v7 = 14;
		v8 = 1;
	}
	v4 = &questlist[0]._qlstr;
	v5 = v7 - v1;
	v6 = 0;
	y = v7 - v1 - 2;
	do {
		if (*((_BYTE *)v0 - 18) == 2 && *((_DWORD *)&Qtalklist[0]._qinfra + v6 + 16 * talker) != -1 && *v0) {
			AddSText(0, v5, 1u, *v4, COL_WHITE, 1);
			v5 += v8;
		}
		v0 += 6;
		++v6;
		v4 += 5;
	} while ((signed int)v0 < (signed int)&quests[16]._qlog);
	AddSText(0, y, 1u, "Gossip", COL_BLUE, 1);
	AddSText(0, 22, 1u, "Back", COL_WHITE, 1);
}
// 69FB38: using guessed type int talker;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_StartTavern()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 1, 1u, "Welcome to the", COL_GOLD, 0);
	AddSText(0, 3, 1u, "Rising Sun", COL_GOLD, 0);
	AddSText(0, 9, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 12, 1u, "Talk to Ogden", COL_BLUE, 1);
	AddSText(0, 18, 1u, "Leave the tavern", COL_WHITE, 1);
	AddSLine(5);
	storenumh = 20;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_StartBarMaid()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 2, 1u, "Gillian", COL_GOLD, 0);
	AddSText(0, 9, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 12, 1u, "Talk to Gillian", COL_BLUE, 1);
	AddSText(0, 18, 1u, "Say goodbye", COL_WHITE, 1);
	AddSLine(5);
	storenumh = 20;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void S_StartDrunk()
{
	stextsize = 0;
	stextscrl = 0;
	AddSText(0, 2, 1u, "Farnham the Drunk", COL_GOLD, 0);
	AddSText(0, 9, 1u, "Would you like to:", COL_GOLD, 0);
	AddSText(0, 12, 1u, "Talk to Farnham", COL_BLUE, 1);
	AddSText(0, 18, 1u, "Say Goodbye", COL_WHITE, 1);
	AddSLine(5);
	storenumh = 20;
}
// 69F10C: using guessed type int storenumh;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;

void StartStore(char s)
{
	char t; // bl
	int i;  // ecx

	for (t = s;; t = STORE_SMITH) {
		sbookflag = 0;
		invflag = 0;
		chrflag = 0;
		questlog = FALSE;
		dropGoldFlag = FALSE;
		ClearSText(0, 24);
		ReleaseStoreBtn();
		switch (t) {
		case STORE_SMITH:
			S_StartSmith();
			break;
		case STORE_SBUY:
			if (storenumh > 0)
				S_StartSBuy();
			break;
		case STORE_SSELL:
			S_StartSSell();
			break;
		case STORE_SREPAIR:
			S_StartSRepair();
			break;
		case STORE_WITCH:
			S_StartWitch();
			break;
		case STORE_WBUY:
			if (storenumh > 0)
				S_StartWBuy();
			break;
		case STORE_WSELL:
			S_StartWSell();
			break;
		case STORE_WRECHARGE:
			S_StartWRecharge();
			break;
		case STORE_NOMONEY:
			S_StartNoMoney();
			break;
		case STORE_NOROOM:
			S_StartNoRoom();
			break;
		case STORE_CONFIRM:
			S_StartConfirm();
			break;
		case STORE_BOY:
			S_StartBoy();
			break;
		case STORE_BBOY:
			S_StartBBoy();
			break;
		case STORE_HEALER:
			S_StartHealer();
			break;
		case STORE_STORY:
			S_StartStory();
			break;
		case STORE_HBUY:
			if (storenumh > 0)
				S_StartHBuy();
			break;
		case STORE_SIDENTIFY:
			S_StartSIdentify();
			break;
		case STORE_SPBUY:
			if (!S_StartSPBuy())
				return;
			break;
		case STORE_GOSSIP:
			S_StartTalk();
			break;
		case STORE_IDSHOW:
			S_StartIdShow();
			break;
		case STORE_TAVERN:
			S_StartTavern();
			break;
		case STORE_DRUNK:
			S_StartDrunk();
			break;
		case STORE_BARMAID:
			S_StartBarMaid();
			break;
		}

		for (i = 0; i < 24; i++) {
			if (stext[i]._ssel)
				break;
		}

		stextsel = i == 24 ? -1 : i;
		stextflag = t;
		if (t != STORE_SBUY || storenumh)
			break;
	}
}
// 4B8968: using guessed type int sbookflag;
// 69F10C: using guessed type int storenumh;
// 6A8A28: using guessed type int stextsel;
// 6AA705: using guessed type char stextflag;

void DrawSText()
{
	int i; // edi

	if (stextsize)
		DrawQTextBack();
	else
		DrawSTextBack();
	if (!stextscrl)
		goto LABEL_19;
	if (stextflag > (signed int)STORE_WRECHARGE) {
		switch (stextflag) {
		case STORE_HBUY:
			S_ScrollHBuy(stextsval);
			break;
		case STORE_SIDENTIFY:
			goto LABEL_17;
		case STORE_SPBUY:
			S_ScrollSPBuy(stextsval);
			break;
		}
	} else {
		if (stextflag >= (signed int)STORE_WSELL)
			goto LABEL_17;
		if (stextflag == STORE_SBUY) {
			S_ScrollSBuy(stextsval);
			goto LABEL_19;
		}
		if (stextflag > (signed int)STORE_SBUY) {
			if (stextflag > (signed int)STORE_SREPAIR) {
				if (stextflag == STORE_WBUY)
					S_ScrollWBuy(stextsval);
				goto LABEL_19;
			}
		LABEL_17:
			S_ScrollSSell(stextsval);
			goto LABEL_19;
		}
	}
LABEL_19:

	for (i = 0; i < 24; i++) {
		if (stext[i]._sline)
			DrawSLine(i);
		if (stext[i]._sstr)
			PrintSString(stext[i]._sx, i, stext[i]._sjust, stext[i]._sstr, stext[i]._sclr, stext[i]._sval);
	}

	if (stextscrl)
		DrawSArrows(4, 20);
	InStoreFlag = (InStoreFlag & 7) + 1;
}
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;
// 6AA705: using guessed type char stextflag;

void STextESC()
{
	char v0; // cl
	char v1; // cl
	char v2; // cl

	if (qtextflag) {
		qtextflag = FALSE;
		if (leveltype == DTYPE_TOWN)
			sfx_stop();
	} else {
		switch (stextflag) {
		case STORE_SMITH:
		case STORE_WITCH:
		case STORE_BOY:
		case STORE_BBOY:
		case STORE_HEALER:
		case STORE_STORY:
		case STORE_TAVERN:
		case STORE_DRUNK:
		case STORE_BARMAID:
			stextflag = STORE_NONE;
			return;
		case STORE_SBUY:
			StartStore(STORE_SMITH);
			stextsel = 12;
			return;
		case STORE_SSELL:
			v1 = STORE_SMITH;
			goto LABEL_16;
		case STORE_SREPAIR:
			v2 = STORE_SMITH;
			goto LABEL_14;
		case STORE_WBUY:
			v0 = STORE_WITCH;
			goto LABEL_18;
		case STORE_WSELL:
			v1 = STORE_WITCH;
			goto LABEL_16;
		case STORE_WRECHARGE:
			v2 = STORE_WITCH;
		LABEL_14:
			StartStore(v2);
			stextsel = 18;
			return;
		case STORE_NOMONEY:
		case STORE_NOROOM:
		case STORE_CONFIRM:
			StartStore((unsigned char)stextshold);
			stextsel = stextlhold;
			stextsval = stextvhold;
			return;
		case STORE_HBUY:
			v1 = STORE_HEALER;
		LABEL_16:
			StartStore(v1);
			stextsel = 16;
			return;
		case STORE_SIDENTIFY:
			v0 = STORE_STORY;
			goto LABEL_18;
		case STORE_SPBUY:
			v0 = STORE_SMITH;
		LABEL_18:
			StartStore(v0);
			stextsel = 14;
			break;
		case STORE_GOSSIP:
			StartStore((unsigned char)stextshold);
			stextsel = stextlhold;
			break;
		case STORE_IDSHOW:
			StartStore(STORE_SIDENTIFY);
			break;
		}
	}
}
// 646D00: using guessed type char qtextflag;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;
// 6A8A28: using guessed type int stextsel;
// 6AA705: using guessed type char stextflag;

void STextUp()
{
	int v0; // eax

	PlaySFX(IS_TITLEMOV);
	if (stextsel != -1) {
		if (stextscrl) {
			if (stextsel == stextup) {
				if (stextsval)
					--stextsval;
				return;
			}
			v0 = stextsel - 1;
			stextsel = v0;
			if (stext[v0]._ssel)
				return;
			do {
				if (v0)
					--v0;
				else
					v0 = 23;
			} while (!stext[v0]._ssel);
		LABEL_20:
			stextsel = v0;
			return;
		}
		if (stextsel)
			v0 = stextsel - 1;
		else
			v0 = 23;
		stextsel = v0;
		if (!stext[v0]._ssel) {
			do {
				if (v0)
					--v0;
				else
					v0 = 23;
			} while (!stext[v0]._ssel);
			goto LABEL_20;
		}
	}
}
// 69F108: using guessed type int stextup;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A28: using guessed type int stextsel;

void STextDown()
{
	int v0; // eax

	PlaySFX(IS_TITLEMOV);
	if (stextsel != -1) {
		if (stextscrl) {
			if (stextsel == stextdown) {
				if (stextsval < stextsmax)
					++stextsval;
				return;
			}
			v0 = stextsel + 1;
			stextsel = v0;
			if (stext[v0]._ssel)
				return;
			do {
				if (v0 == 23)
					v0 = 0;
				else
					++v0;
			} while (!stext[v0]._ssel);
		LABEL_20:
			stextsel = v0;
			return;
		}
		if (stextsel == 23)
			v0 = 0;
		else
			v0 = stextsel + 1;
		stextsel = v0;
		if (!stext[v0]._ssel) {
			do {
				if (v0 == 23)
					v0 = 0;
				else
					++v0;
			} while (!stext[v0]._ssel);
			goto LABEL_20;
		}
	}
}
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A28: using guessed type int stextsel;
// 6AA700: using guessed type int stextdown;

void STextPrior()
{
	PlaySFX(IS_TITLEMOV);
	if (stextsel != -1 && stextscrl) {
		if (stextsel == stextup) {
			if (stextsval) {
				stextsval -= 4;
				if (stextsval < 0)
					stextsval = 0;
			}
		} else {
			stextsel = stextup;
		}
	}
}
// 69F108: using guessed type int stextup;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A28: using guessed type int stextsel;

void STextNext()
{
	PlaySFX(IS_TITLEMOV);
	if (stextsel != -1 && stextscrl) {
		if (stextsel == stextdown) {
			if (stextsval < stextsmax)
				stextsval += 4;
			if (stextsval > stextsmax)
				stextsval = stextsmax;
		} else {
			stextsel = stextdown;
		}
	}
}
// 6A09E4: using guessed type int stextsmax;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A28: using guessed type int stextsel;
// 6AA700: using guessed type int stextdown;

void S_SmithEnter()
{
	int v0; // ecx

	v0 = 10;
	if (stextsel == 10) {
		talker = 0;
		stextlhold = 10;
		stextshold = 1;
		gossipstart = QUEST_GRISWOLD2;
		gossipend = QUEST_GRISWOLD13;
		_LOBYTE(v0) = STORE_GOSSIP;
		goto LABEL_13;
	}
	v0 = STORE_SBUY;
	switch (stextsel) {
	case 12:
	LABEL_13:
		StartStore(v0);
		return;
	case 14:
		_LOBYTE(v0) = STORE_SPBUY;
		goto LABEL_13;
	case 16:
		_LOBYTE(v0) = STORE_SSELL;
		goto LABEL_13;
	case 18:
		_LOBYTE(v0) = STORE_SREPAIR;
		goto LABEL_13;
	case 20:
		stextflag = STORE_NONE;
		break;
	}
}
// 69F110: using guessed type int stextlhold;
// 69FB38: using guessed type int talker;
// 6A4EF0: using guessed type int gossipstart;
// 6A8A28: using guessed type int stextsel;
// 6A8A30: using guessed type int gossipend;
// 6AA705: using guessed type char stextflag;

void SetGoldCurs(int pnum, int i)
{
	if (plr[pnum].InvList[i]._ivalue >= 2500)
		plr[pnum].InvList[i]._iCurs = ICURS_GOLD_LARGE;
	else if (plr[pnum].InvList[i]._ivalue <= 1000)
		plr[pnum].InvList[i]._iCurs = ICURS_GOLD_SMALL;
	else
		plr[pnum].InvList[i]._iCurs = ICURS_GOLD_MEDIUM;
}

void SetSpdbarGoldCurs(int pnum, int i)
{
	if (plr[pnum].SpdList[i]._ivalue >= 2500)
		plr[pnum].SpdList[i]._iCurs = ICURS_GOLD_LARGE;
	else if (plr[pnum].SpdList[i]._ivalue <= 1000)
		plr[pnum].SpdList[i]._iCurs = ICURS_GOLD_SMALL;
	else
		plr[pnum].SpdList[i]._iCurs = ICURS_GOLD_MEDIUM;
}

void TakePlrsMoney(int cost)
{
	int v1;         // edi
	int v2;         // eax
	int v3;         // esi
	int v4;         // ebx
	int v5;         // eax
	_DWORD *v6;     // ecx
	int v7;         // eax
	int v8;         // ebx
	int v9;         // eax
	_DWORD *v10;    // ecx
	int v11;        // eax
	signed int v12; // ebx
	int v13;        // eax
	int v14;        // eax
	_DWORD *v15;    // ecx
	int v16;        // eax
	signed int v17; // ebx
	int v18;        // eax
	int v19;        // eax
	_DWORD *v20;    // ecx
	int v21;        // eax

	v1 = cost;
	v2 = CalculateGold(myplr);
	v3 = myplr;
	v4 = 0;
	plr[myplr]._pGold = v2 - v1;
	while (v1 > 0) {
		v5 = 368 * v4 + 21720 * v3;
		if (*(int *)((char *)&plr[0].SpdList[0]._itype + v5) == ITYPE_GOLD) {
			v6 = (unsigned int *)((char *)&plr[0].SpdList[0]._ivalue + v5);
			v7 = *(int *)((char *)&plr[0].SpdList[0]._ivalue + v5);
			if (v7 != 5000) {
				if (v1 >= v7) {
					v1 -= v7;
					RemoveSpdBarItem(v3, v4);
					v3 = myplr;
					v4 = -1;
				} else {
					*v6 = v7 - v1;
					SetSpdbarGoldCurs(v3, v4);
					v1 = 0;
				}
			}
		}
		if (++v4 >= MAXBELTITEMS) {
			if (v1 > 0) {
				v8 = 0;
				do {
					if (v1 <= 0)
						break;
					v9 = 368 * v8 + 21720 * v3;
					if (*(int *)((char *)&plr[0].SpdList[0]._itype + v9) == ITYPE_GOLD) {
						v10 = (unsigned int *)((char *)&plr[0].SpdList[0]._ivalue + v9);
						v11 = *(int *)((char *)&plr[0].SpdList[0]._ivalue + v9);
						if (v1 >= v11) {
							v1 -= v11;
							RemoveSpdBarItem(v3, v8);
							v3 = myplr;
							v8 = -1;
						} else {
							*v10 = v11 - v1;
							SetSpdbarGoldCurs(v3, v8);
							v1 = 0;
						}
					}
					++v8;
				} while (v8 < MAXBELTITEMS);
			}
			break;
		}
	}
	v12 = 0;
	drawpanflag = 255;
	if (v1 > 0) {
		v13 = 21720 * v3;
		if (plr[v3]._pNumInv <= 0) {
		LABEL_26:
			v17 = 0;
			if (v1 > 0) {
				v18 = 21720 * v3;
				if (plr[v3]._pNumInv > 0) {
					do {
						if (v1 <= 0)
							break;
						v19 = 368 * v17 + v18;
						if (*(int *)((char *)&plr[0].InvList[0]._itype + v19) == ITYPE_GOLD) {
							v20 = (unsigned int *)((char *)&plr[0].InvList[0]._ivalue + v19);
							v21 = *(int *)((char *)&plr[0].InvList[0]._ivalue + v19);
							if (v1 >= v21) {
								v1 -= v21;
								RemoveInvItem(v3, v17);
								v3 = myplr;
								v17 = -1;
							} else {
								*v20 = v21 - v1;
								SetGoldCurs(v3, v17);
								v1 = 0;
							}
						}
						++v17;
						v18 = 21720 * v3;
					} while (v17 < plr[v3]._pNumInv);
				}
			}
		} else {
			while (v1 > 0) {
				v14 = 368 * v12 + v13;
				if (*(int *)((char *)&plr[0].InvList[0]._itype + v14) == ITYPE_GOLD) {
					v15 = (unsigned int *)((char *)&plr[0].InvList[0]._ivalue + v14);
					v16 = *(int *)((char *)&plr[0].InvList[0]._ivalue + v14);
					if (v16 != 5000) {
						if (v1 >= v16) {
							v1 -= v16;
							RemoveInvItem(v3, v12);
							v3 = myplr;
							v12 = -1;
						} else {
							*v15 = v16 - v1;
							SetGoldCurs(v3, v12);
							v1 = 0;
						}
					}
				}
				++v12;
				v13 = 21720 * v3;
				if (v12 >= plr[v3]._pNumInv)
					goto LABEL_26;
			}
		}
	}
}
// 52571C: using guessed type int drawpanflag;

void SmithBuyItem()
{
	int idx;

	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);
	if (plr[myplr].HoldItem._iMagical == ITEM_QUALITY_NORMAL)
		plr[myplr].HoldItem._iIdentified = FALSE;
	StoreAutoPlace();
	idx = stextvhold + ((stextlhold - stextup) >> 2);
	if (idx == 19) {
		smithitem[19]._itype = -1;
	} else {
		for (; smithitem[idx + 1]._itype != -1; idx++) {
			smithitem[idx] = smithitem[idx + 1];
		}
		smithitem[idx]._itype = -1;
	}
	CalcPlrInv(myplr, 1);
}

void S_SBuyEnter()
{
	int idx, i;
	BOOL done;

	if (stextsel == 22) {
		StartStore(STORE_SMITH);
		stextsel = 12;
	} else {
		stextlhold = stextsel;
		stextvhold = stextsval;
		stextshold = 2;
		idx = stextsval + ((stextsel - stextup) >> 2);
		if (plr[myplr]._pGold < smithitem[idx]._iIvalue) {
			StartStore(STORE_NOMONEY);
		} else {
			plr[myplr].HoldItem = smithitem[idx];
			SetCursor_(plr[myplr].HoldItem._iCurs + CURSOR_FIRSTITEM);
			done = FALSE;

			for (i = 0; i < 40 && !done; i++) {
				done = AutoPlace(myplr, i, cursW / 28, cursH / 28, 0);
			}
			if (done)
				StartStore(STORE_CONFIRM);
			else
				StartStore(STORE_NOROOM);
			SetCursor_(CURSOR_HAND);
		}
	}
}

void SmithBuyPItem()
{
	int xx;     // ecx
	int idx;    // eax
	BOOLEAN v2; // sf
	int v3;     // eax
	int i;      // edx

	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);
	if (plr[myplr].HoldItem._iMagical == ITEM_QUALITY_NORMAL)
		plr[myplr].HoldItem._iIdentified = FALSE;
	StoreAutoPlace();
	xx = 0;
	idx = (stextlhold - stextup) >> 2;
	v2 = stextvhold + idx < 0;
	v3 = stextvhold + idx;
	i = 0;
	if (!v2) {
		do {
			if (premiumitem[i]._itype != -1) {
				--v3;
				xx = i;
			}
			++i;
		} while (v3 >= 0);
	}

	premiumitem[xx]._itype = -1;
	--numpremium;
	SpawnPremium(plr[myplr]._pLevel);
}
// 69F108: using guessed type int stextup;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;

void S_SPBuyEnter()
{
	int i, idx, xx;
	BOOL done;

	if (stextsel == 22) {
		StartStore(STORE_SMITH);
		stextsel = 14;
	} else {
		stextshold = 18;
		stextlhold = stextsel;
		stextvhold = stextsval;
		xx = stextsval + ((stextsel - stextup) >> 2);
		idx = 0;
		for (i = 0; xx >= 0; i++) {
			if (premiumitem[i]._itype != -1) {
				xx--;
				idx = i;
			}
		}
		if (plr[myplr]._pGold < premiumitem[idx]._iIvalue) {
			StartStore(STORE_NOMONEY);
		} else {
			plr[myplr].HoldItem = premiumitem[idx];
			SetCursor_(plr[myplr].HoldItem._iCurs + CURSOR_FIRSTITEM);
			done = FALSE;
			for (i = 0; i < 40 && !done; i++) {
				done = AutoPlace(myplr, i, cursW / 28, cursH / 28, 0);
			}
			if (done)
				StartStore(STORE_CONFIRM);
			else
				StartStore(STORE_NOROOM);
			SetCursor_(CURSOR_HAND);
		}
	}
}

BOOL StoreGoldFit(int idx)
{
	int cost;    // edi
	int i;       // ecx
	int sz;      // eax
	int numsqrs; // [esp+Ch] [ebp-4h]

	cost = storehold[idx]._iIvalue;
	sz = cost / 5000;
	if (cost % 5000)
		sz++;

	SetCursor_(storehold[idx]._iCurs + CURSOR_FIRSTITEM);
	numsqrs = cursW / 28 * (cursH / 28);
	SetCursor_(CURSOR_HAND);

	if (numsqrs >= sz)
		return 1;

	for (i = 0; i < 40; i++) {
		if (!plr[myplr].InvGrid[i])
			numsqrs++;
	}

	for (i = 0; i < plr[myplr]._pNumInv; i++) {
		if (plr[myplr].InvList[i]._itype == ITYPE_GOLD && plr[myplr].InvList[i]._ivalue != 5000) {
			cost += plr[myplr].InvList[i]._ivalue;
			if (cost > 5000)
				cost -= 5000;
			else
				cost = 0;
		}
	}

	sz = cost / 5000;
	if (cost % 5000)
		sz++;
	return numsqrs >= sz;
}
// 4B8C9C: using guessed type int cursH;

void PlaceStoreGold(int v)
{
	BOOL done;
	int ii, xx, yy, i;

	done = FALSE;

	for (i = 0; i < 40 && !done; i++) {
		yy = 10 * (i / 10);
		xx = i % 10;
		if (!plr[myplr].InvGrid[xx + yy]) {
			ii = plr[myplr]._pNumInv;
			GetGoldSeed(myplr, &golditem);
			plr[myplr].InvList[ii] = golditem;
			plr[myplr]._pNumInv++;
			plr[myplr].InvGrid[xx + yy] = plr[myplr]._pNumInv;
			plr[myplr].InvList[ii]._ivalue = v;
			SetGoldCurs(myplr, ii);
			done = TRUE;
		}
	}
}

void StoreSellItem()
{
	int i, idx, cost;

	idx = stextvhold + ((stextlhold - stextup) >> 2);
	if (storehidx[idx] >= 0)
		RemoveInvItem(myplr, storehidx[idx]);
	else
		RemoveSpdBarItem(myplr, -(storehidx[idx] + 1));
	cost = storehold[idx]._iIvalue;
	storenumh--;
	if (idx != storenumh) {
		while (idx < storenumh) {
			storehold[idx] = storehold[idx + 1];
			storehidx[idx] = storehidx[idx + 1];
			idx++;
		}
	}
	plr[myplr]._pGold += cost;
	for (i = 0; i < plr[myplr]._pNumInv && cost > 0; i++) {
		if (plr[myplr].InvList[i]._itype == ITYPE_GOLD && plr[myplr].InvList[i]._ivalue != 5000) {
			if (cost + plr[myplr].InvList[i]._ivalue <= 5000) {
				plr[myplr].InvList[i]._ivalue += cost;
				SetGoldCurs(myplr, i);
				cost = 0;
			} else {
				cost -= 5000 - plr[myplr].InvList[i]._ivalue;
				plr[myplr].InvList[i]._ivalue = 5000;
				SetGoldCurs(myplr, i);
			}
		}
	}
	if (cost > 0) {
		while (cost > 5000) {
			PlaceStoreGold(5000);
			cost -= 5000;
		}
		PlaceStoreGold(cost);
	}
}

void S_SSellEnter()
{
	int idx;

	if (stextsel == 22) {
		StartStore(STORE_SMITH);
		stextsel = 16;
	} else {
		stextlhold = stextsel;
		idx = stextsval + ((stextsel - stextup) >> 2);
		stextshold = 3;
		stextvhold = stextsval;
		plr[myplr].HoldItem = storehold[idx];

		if (StoreGoldFit(idx))
			StartStore(STORE_CONFIRM);
		else
			StartStore(STORE_NOROOM);
	}
}
// 69F108: using guessed type int stextup;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;
// 6A8A28: using guessed type int stextsel;

void SmithRepairItem()
{
	int i;   // edx
	int idx; // eax

	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);

	idx = stextvhold + ((stextlhold - stextup) >> 2);
	i = storehidx[idx];
	storehold[idx]._iDurability = storehold[idx]._iMaxDur;

	if (i >= 0) {
		plr[myplr].InvList[i]._iDurability = plr[myplr].InvList[i]._iMaxDur;
	} else {
		if (i == -1)
			plr[myplr].InvBody[INVLOC_HEAD]._iDurability = plr[myplr].InvBody[INVLOC_HEAD]._iMaxDur;
		if (i == -2)
			plr[myplr].InvBody[INVLOC_CHEST]._iDurability = plr[myplr].InvBody[INVLOC_CHEST]._iMaxDur;
		if (i == -3)
			plr[myplr].InvBody[INVLOC_HAND_LEFT]._iDurability = plr[myplr].InvBody[INVLOC_HAND_LEFT]._iMaxDur;
		if (i == -4)
			plr[myplr].InvBody[INVLOC_HAND_RIGHT]._iDurability = plr[myplr].InvBody[INVLOC_HAND_RIGHT]._iMaxDur;
	}
}
// 69F108: using guessed type int stextup;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;

void S_SRepairEnter()
{
	int idx;

	if (stextsel == 22) {
		StartStore(STORE_SMITH);
		stextsel = 18;
	} else {
		stextshold = 4;
		stextlhold = stextsel;
		stextvhold = stextsval;
		idx = stextsval + ((stextsel - stextup) >> 2);
		plr[myplr].HoldItem = storehold[idx];
		if (plr[myplr]._pGold < storehold[idx]._iIvalue)
			StartStore(STORE_NOMONEY);
		else
			StartStore(STORE_CONFIRM);
	}
}

void S_WitchEnter()
{
	switch (stextsel) {
	case 12:
		stextlhold = 12;
		talker = 6;
		stextshold = 5;
		gossipstart = QUEST_ADRIA2;
		gossipend = QUEST_ADRIA13;
		StartStore(STORE_GOSSIP);
		return;
	case 14:
		StartStore(STORE_WBUY);
		return;
	case 16:
		StartStore(STORE_WSELL);
		return;
	case 18:
		StartStore(STORE_WRECHARGE);
		return;
	case 20:
		stextflag = STORE_NONE;
		break;
	}
}

void WitchBuyItem()
{
	int idx;

	idx = stextvhold + ((stextlhold - stextup) >> 2);

	if (idx < 3)
		plr[myplr].HoldItem._iSeed = GetRndSeed();

	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);
	StoreAutoPlace();

	if (idx >= 3) {
		if (idx == 19) {
			witchitem[19]._itype = -1;
		} else {
			for (; witchitem[idx + 1]._itype != -1; idx++) {
				witchitem[idx] = witchitem[idx + 1];
			}
			witchitem[idx]._itype = -1;
		}
	}

	CalcPlrInv(myplr, TRUE);
}

void S_WBuyEnter()
{
	int i, idx;
	BOOL done;

	if (stextsel == 22) {
		StartStore(STORE_WITCH);
		stextsel = 14;
	} else {
		stextlhold = stextsel;
		stextvhold = stextsval;
		stextshold = 6;
		idx = stextsval + ((stextsel - stextup) >> 2);

		if (plr[myplr]._pGold < witchitem[idx]._iIvalue) {
			StartStore(STORE_NOMONEY);
		} else {
			plr[myplr].HoldItem = witchitem[idx];
			SetCursor_(plr[myplr].HoldItem._iCurs + CURSOR_FIRSTITEM);
			done = FALSE;

			for (i = 0; i < 40 && !done; i++) {
				done = SpecialAutoPlace(myplr, i, cursW / 28, cursH / 28, 0);
			}

			if (done)
				StartStore(STORE_CONFIRM);
			else
				StartStore(STORE_NOROOM);

			SetCursor_(CURSOR_HAND);
		}
	}
}
// 4B8C9C: using guessed type int cursH;
// 69F108: using guessed type int stextup;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;
// 6A8A28: using guessed type int stextsel;

void S_WSellEnter()
{
	int idx;

	if (stextsel == 22) {
		StartStore(STORE_WITCH);
		stextsel = 16;
	} else {
		stextlhold = stextsel;
		idx = stextsval + ((stextsel - stextup) >> 2);
		stextshold = 7;
		stextvhold = stextsval;
		plr[myplr].HoldItem = storehold[idx];
		if (StoreGoldFit(idx))
			StartStore(STORE_CONFIRM);
		else
			StartStore(STORE_NOROOM);
	}
}
// 69F108: using guessed type int stextup;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;
// 6A8A28: using guessed type int stextsel;

void WitchRechargeItem()
{
	int i, idx;

	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);

	idx = stextvhold + ((stextlhold - stextup) >> 2);
	storehold[idx]._iCharges = storehold[idx]._iMaxCharges;

	i = storehidx[idx];
	if (i < 0)
		plr[myplr].InvBody[INVLOC_HAND_LEFT]._iCharges = plr[myplr].InvBody[INVLOC_HAND_LEFT]._iMaxCharges;
	else
		plr[myplr].InvList[i]._iCharges = plr[myplr].InvList[i]._iMaxCharges;

	CalcPlrInv(myplr, 1u);
}
// 69F108: using guessed type int stextup;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;

void S_WRechargeEnter()
{
	int idx;

	if (stextsel == 22) {
		StartStore(STORE_WITCH);
		stextsel = 18;
	} else {
		stextshold = 8;
		stextlhold = stextsel;
		stextvhold = stextsval;
		idx = stextsval + ((stextsel - stextup) >> 2);
		plr[myplr].HoldItem = storehold[idx];
		if (plr[myplr]._pGold < storehold[idx]._iIvalue)
			StartStore(STORE_NOMONEY);
		else
			StartStore(STORE_CONFIRM);
	}
}

void S_BoyEnter()
{
	if (boyitem._itype != ITYPE_NONE && stextsel == 18) {
		if (plr[myplr]._pGold < 50) {
			stextshold = 12;
			stextlhold = 18;
			stextvhold = stextsval;
			StartStore(STORE_NOMONEY);
		} else {
			TakePlrsMoney(50);
			StartStore(STORE_BBOY);
		}
	} else if (stextsel == 8 && boyitem._itype != ITYPE_NONE || stextsel == 12 && boyitem._itype == ITYPE_NONE) {
		talker = 8;
		stextshold = 12;
		stextlhold = stextsel;
		gossipstart = QUEST_WIRT2;
		gossipend = QUEST_WIRT12;
		StartStore(STORE_GOSSIP);
	} else {
		stextflag = STORE_NONE;
	}
}

void BoyBuyItem()
{
	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);
	StoreAutoPlace();
	boyitem._itype = -1;
	stextshold = 12;
	CalcPlrInv(myplr, 1u);
}

void HealerBuyItem()
{
	int idx;
	BOOL ok;

	idx = stextvhold + ((stextlhold - stextup) >> 2);

	ok = FALSE;
	if (gbMaxPlayers == 1) {
		if (idx < 2)
			ok = TRUE;
	} else {
		if (idx < 3)
			ok = TRUE;
	}
	if (ok) {
		plr[myplr].HoldItem._iSeed = GetRndSeed();
	}

	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);
	if (plr[myplr].HoldItem._iMagical == ITEM_QUALITY_NORMAL)
		plr[myplr].HoldItem._iIdentified = FALSE;
	StoreAutoPlace();

	ok = FALSE;
	if (gbMaxPlayers == 1) {
		if (idx >= 2)
			ok = TRUE;
	} else {
		if (idx >= 3)
			ok = TRUE;
	}
	if (ok) {
		idx = stextvhold + ((stextlhold - stextup) >> 2);
		if (idx == 19) {
			healitem[19]._itype = -1;
		} else {
			for (; healitem[idx + 1]._itype != -1; idx++) {
				healitem[idx] = healitem[idx + 1];
			}
			healitem[idx]._itype = -1;
		}
		CalcPlrInv(myplr, TRUE);
	}
}

void S_BBuyEnter()
{
	BOOL done;
	int i;

	if (stextsel == 10) {
		stextlhold = 10;
		stextvhold = stextsval;
		stextshold = 13;
		if (plr[myplr]._pGold >= boyitem._iIvalue + (boyitem._iIvalue >> 1)) {
			StartStore(STORE_NOMONEY);
		} else {
			plr[myplr].HoldItem = boyitem;
			plr[myplr].HoldItem._iIvalue += plr[myplr].HoldItem._iIvalue >> 1;
			SetCursor_(plr[myplr].HoldItem._iCurs + CURSOR_FIRSTITEM);
			done = FALSE;
			for (i = 0; i < 40 && !done; i++) {
				done = AutoPlace(myplr, i, cursW / 28, cursH / 28, 0);
			}
			if (done)
				StartStore(STORE_CONFIRM);
			else
				StartStore(STORE_NOROOM);
			SetCursor_(CURSOR_HAND);
		}
	} else {
		stextflag = STORE_NONE;
	}
}

void StoryIdItem()
{
	int idx;

	idx = storehidx[((stextlhold - stextup) >> 2) + stextvhold];
	if (idx < 0) {
		if (idx == -1)
			plr[myplr].InvBody[INVLOC_HEAD]._iIdentified = TRUE;
		if (idx == -2)
			plr[myplr].InvBody[INVLOC_CHEST]._iIdentified = TRUE;
		if (idx == -3)
			plr[myplr].InvBody[INVLOC_HAND_LEFT]._iIdentified = TRUE;
		if (idx == -4)
			plr[myplr].InvBody[INVLOC_HAND_RIGHT]._iIdentified = TRUE;
		if (idx == -5)
			plr[myplr].InvBody[INVLOC_RING_LEFT]._iIdentified = TRUE;
		if (idx == -6)
			plr[myplr].InvBody[INVLOC_RING_RIGHT]._iIdentified = TRUE;
		if (idx == -7)
			plr[myplr].InvBody[INVLOC_AMULET]._iIdentified = TRUE;
	} else {
		plr[myplr].InvList[idx]._iIdentified = TRUE;
	}
	plr[myplr].HoldItem._iIdentified = TRUE;
	TakePlrsMoney(plr[myplr].HoldItem._iIvalue);
	CalcPlrInv(myplr, TRUE);
}

void S_ConfirmEnter()
{
	if (stextsel == 18) {
		switch (stextshold) {
		case STORE_SBUY:
			SmithBuyItem();
			break;
		case STORE_SSELL:
		case STORE_WSELL:
			StoreSellItem();
			break;
		case STORE_SREPAIR:
			SmithRepairItem();
			break;
		case STORE_WBUY:
			WitchBuyItem();
			break;
		case STORE_WRECHARGE:
			WitchRechargeItem();
			break;
		case STORE_BBOY:
			BoyBuyItem();
			break;
		case STORE_HBUY:
			HealerBuyItem();
			break;
		case STORE_SIDENTIFY:
			StoryIdItem();
			StartStore(STORE_IDSHOW);
			return;
		case STORE_SPBUY:
			SmithBuyPItem();
			break;
		}
		StartStore(stextshold);
	} else {
		StartStore(stextshold);
		stextsel = stextlhold;
		stextsval = stextvhold;
	}
}

void S_HealerEnter()
{
	switch (stextsel) {
	case 12:
		stextlhold = 12;
		talker = 1;
		stextshold = 14;
		gossipstart = QUEST_PEPIN2;
		gossipend = QUEST_PEPIN11;
		StartStore(STORE_GOSSIP);
		return;
	case 14:
		if (plr[myplr]._pHitPoints != plr[myplr]._pMaxHP)
			PlaySFX(IS_CAST8);
		drawhpflag = TRUE;
		plr[myplr]._pHitPoints = plr[myplr]._pMaxHP;
		plr[myplr]._pHPBase = plr[myplr]._pMaxHPBase;
		return;
	case 16:
		StartStore(STORE_HBUY);
		return;
	case 18:
		stextflag = STORE_NONE;
		return;
	}
}
// 69F110: using guessed type int stextlhold;
// 69FB38: using guessed type int talker;
// 6A4EF0: using guessed type int gossipstart;
// 6A8A28: using guessed type int stextsel;
// 6A8A30: using guessed type int gossipend;
// 6AA705: using guessed type char stextflag;

void S_HBuyEnter()
{
	int i, idx;
	BOOL done;

	if (stextsel == 22) {
		StartStore(STORE_HEALER);
		stextsel = 16;
	} else {
		stextlhold = stextsel;
		stextvhold = stextsval;
		stextshold = 16;
		idx = stextsval + ((stextsel - stextup) >> 2);
		if (plr[myplr]._pGold < healitem[idx]._iIvalue) {
			StartStore(STORE_NOMONEY);
		} else {
			plr[myplr].HoldItem = healitem[idx];
			SetCursor_(plr[myplr].HoldItem._iCurs + CURSOR_FIRSTITEM);
			done = FALSE;
			i = 0;
			for (i = 0; i < 40 && !done; i++) {
				done = SpecialAutoPlace(myplr, i, cursW / 28, cursH / 28, 0);
			}
			if (done)
				StartStore(STORE_CONFIRM);
			else
				StartStore(STORE_NOROOM);
			SetCursor_(CURSOR_HAND);
		}
	}
}

void S_StoryEnter()
{
	switch (stextsel) {
	case 12:
		stextlhold = 12;
		talker = 4;
		stextshold = 15;
		gossipstart = QUEST_STORY2;
		gossipend = QUEST_STORY11;
		StartStore(STORE_GOSSIP);
		break;
	case 14:
		StartStore(STORE_SIDENTIFY);
		break;
	case 18:
		stextflag = STORE_NONE;
		break;
	}
}

void S_SIDEnter()
{
	int idx;

	if (stextsel == 22) {
		StartStore(STORE_STORY);
		stextsel = 14;
	} else {
		stextshold = 17;
		stextlhold = stextsel;
		stextvhold = stextsval;
		idx = stextsval + ((stextsel - stextup) >> 2);
		plr[myplr].HoldItem = storehold[idx];
		if (plr[myplr]._pGold < storehold[idx]._iIvalue)
			StartStore(STORE_NOMONEY);
		else
			StartStore(STORE_CONFIRM);
	}
}

void S_TalkEnter()
{
	int v0;        // edx
	int *v1;       // edi
	signed int v2; // eax
	int v3;        // esi
	int *v4;       // ecx
	int v5;        // esi
	signed int v6; // ebp
	int v8;        // eax
	int v9;        // ebx
	int v10;       // ecx

	if (stextsel == 22) {
		StartStore((unsigned char)stextshold);
		stextsel = stextlhold;
	} else {
		v0 = talker;
		v1 = &quests[0]._qlog;
		v2 = 0;
		v3 = 0;
		v4 = &quests[0]._qlog;
		do {
			if (*((_BYTE *)v4 - 18) == 2 && *((_DWORD *)&Qtalklist[0]._qinfra + v3 + 16 * talker) != -1 && *v4)
				++v2;
			v4 += 6;
			++v3;
		} while ((signed int)v4 < (signed int)&quests[16]._qlog);
		if (v2 <= 6) {
			v5 = 15 - v2;
			v6 = 2;
		} else {
			v5 = 14 - (v2 >> 1);
			v6 = 1;
		}
		if (stextsel == v5 - 2) {
			SetRndSeed(towner[talker]._tSeed);
			v8 = random(0, gossipend - gossipstart + 1);
			InitQTextMsg(gossipstart + v8);
		} else {
			v9 = 0;
			do {
				if (*((_BYTE *)v1 - 18) == 2) {
					v10 = *((_DWORD *)&Qtalklist[0]._qinfra + v9 + 16 * v0);
					if (v10 != -1) {
						if (*v1) {
							if (v5 == stextsel) {
								InitQTextMsg(v10);
								v0 = talker;
							}
							v5 += v6;
						}
					}
				}
				v1 += 6;
				++v9;
			} while ((signed int)v1 < (signed int)&quests[16]._qlog);
		}
	}
}
// 69F110: using guessed type int stextlhold;
// 69FB38: using guessed type int talker;
// 6A4EF0: using guessed type int gossipstart;
// 6A8A28: using guessed type int stextsel;
// 6A8A30: using guessed type int gossipend;

void S_TavernEnter()
{
	switch (stextsel) {
	case 12:
		stextlhold = 12;
		talker = 3;
		stextshold = 21;
		gossipstart = QUEST_OGDEN2;
		gossipend = QUEST_OGDEN10;
		StartStore(STORE_GOSSIP);
		break;
	case 18:
		stextflag = STORE_NONE;
		break;
	}
}

void S_BarmaidEnter()
{
	switch (stextsel) {
	case 12:
		stextlhold = 12;
		talker = 7;
		stextshold = 23;
		gossipstart = QUEST_GILLIAN2;
		gossipend = QUEST_GILLIAN10;
		StartStore(STORE_GOSSIP);
		break;
	case 18:
		stextflag = STORE_NONE;
		break;
	}
}

void S_DrunkEnter()
{
	switch (stextsel) {
	case 12:
		stextlhold = 12;
		talker = 5;
		stextshold = 22;
		gossipstart = QUEST_FARNHAM2;
		gossipend = QUEST_FARNHAM13;
		StartStore(STORE_GOSSIP);
		break;
	case 18:
		stextflag = STORE_NONE;
		break;
	}
}

void STextEnter()
{
	if (qtextflag) {
		qtextflag = FALSE;
		if (leveltype == DTYPE_TOWN)
			sfx_stop();
	} else {
		PlaySFX(IS_TITLSLCT);
		switch (stextflag) {
		case STORE_SMITH:
			S_SmithEnter();
			break;
		case STORE_SBUY:
			S_SBuyEnter();
			break;
		case STORE_SSELL:
			S_SSellEnter();
			break;
		case STORE_SREPAIR:
			S_SRepairEnter();
			break;
		case STORE_WITCH:
			S_WitchEnter();
			break;
		case STORE_WBUY:
			S_WBuyEnter();
			break;
		case STORE_WSELL:
			S_WSellEnter();
			break;
		case STORE_WRECHARGE:
			S_WRechargeEnter();
			break;
		case STORE_NOMONEY:
		case STORE_NOROOM:
			StartStore(stextshold);
			stextsel = stextlhold;
			stextsval = stextvhold;
			break;
		case STORE_CONFIRM:
			S_ConfirmEnter();
			break;
		case STORE_BOY:
			S_BoyEnter();
			break;
		case STORE_BBOY:
			S_BBuyEnter();
			break;
		case STORE_HEALER:
			S_HealerEnter();
			break;
		case STORE_STORY:
			S_StoryEnter();
			break;
		case STORE_HBUY:
			S_HBuyEnter();
			break;
		case STORE_SIDENTIFY:
			S_SIDEnter();
			break;
		case STORE_SPBUY:
			S_SPBuyEnter();
			break;
		case STORE_GOSSIP:
			S_TalkEnter();
			break;
		case STORE_IDSHOW:
			StartStore(STORE_SIDENTIFY);
			break;
		case STORE_TAVERN:
			S_TavernEnter();
			break;
		case STORE_DRUNK:
			S_DrunkEnter();
			break;
		case STORE_BARMAID:
			S_BarmaidEnter();
			break;
		}
	}
}
// 646D00: using guessed type char qtextflag;
// 69F110: using guessed type int stextlhold;
// 6A8A24: using guessed type int stextvhold;
// 6A8A28: using guessed type int stextsel;
// 6AA705: using guessed type char stextflag;

void CheckStoreBtn()
{
	BOOLEAN v0; // sf
	//unsigned char v1; // of
	int v2;  // eax
	int *v3; // ecx

	if (qtextflag) {
		qtextflag = FALSE;
		if (leveltype == DTYPE_TOWN)
			sfx_stop();
	} else if (stextsel != -1 && MouseY >= 32 && MouseY <= 320) {
		if (stextsize) {
			//v1 = __OFSUB__(MouseX, 24);
			v0 = MouseX - 24 < 0;
		} else {
			//v1 = __OFSUB__(MouseX, 344);
			v0 = MouseX - 344 < 0;
		}
		if (!v0 && MouseX <= 616) { //if (!(v0 ^ v1) && MouseX <= 616) {
			v2 = (MouseY - 32) / 12;
			if (stextscrl && MouseX > 600) {
				if (v2 == 4) {
					if (stextscrlubtn <= 0) {
						STextUp();
						stextscrlubtn = 10;
						return;
					}
					--stextscrlubtn;
				}
				if (v2 == 20) {
					if (stextscrldbtn > 0) {
						--stextscrldbtn;
					} else {
						STextDown();
						stextscrldbtn = 10;
					}
				}
			} else if (v2 >= 5) {
				if (v2 >= 23)
					v2 = 22;
				if (stextscrl) {
					if (v2 < 21) {
						v3 = &stext[v2]._ssel;
						if (!*v3) {
							if (stext[v2 - 2]._ssel) {
								v2 -= 2;
							} else if (*(v3 - 39)) {
								--v2;
							}
						}
					}
				}
				if (stext[v2]._ssel || stextscrl && v2 == 22) {
					stextsel = v2;
					STextEnter();
				}
			}
		}
	}
}
// 646D00: using guessed type char qtextflag;
// 6A09E0: using guessed type char stextsize;
// 6A6BB8: using guessed type int stextscrl;
// 6A8A28: using guessed type int stextsel;
// 6A8A2C: using guessed type char stextscrldbtn;
// 6AA704: using guessed type char stextscrlubtn;

void ReleaseStoreBtn()
{
	stextscrlubtn = -1;
	stextscrldbtn = -1;
}
// 6A8A2C: using guessed type char stextscrldbtn;
// 6AA704: using guessed type char stextscrlubtn;
