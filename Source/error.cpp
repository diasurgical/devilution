//HEADER_GOES_HERE

#include "../types.h"

DEVILUTION_BEGIN_NAMESPACE

char msgtable[80];
char msgdelay;
char msgflag;
char msgcnt;

char *MsgStrings[44] = {
	"",
	"No automap available in town",
	"No multiplayer functions in demo",
	"Direct Sound Creation Failed",
	"Not available in shareware version",
	"Not enough space to save",
	"No Pause in town",
	"Copying to a hard disk is recommended",
	"Multiplayer sync problem",
	"No pause in multiplayer",
	"Loading...",
	"Saving...",
	"Some are weakened as one grows strong",
	"New strength is forged through destruction",
	"Those who defend seldom attack",
	"The sword of justice is swift and sharp",
	"While the spirit is vigilant the body thrives",
	"The powers of mana refocused renews",
	"Time cannot diminish the power of steel",
	"Magic is not always what it seems to be",
	"What once was opened now is closed",
	"Intensity comes at the cost of wisdom",
	"Arcane power brings destruction",
	"That which cannot be held cannot be harmed",
	"Crimson and Azure become as the sun",
	"Knowledge and wisdom at the cost of self",
	"Drink and be refreshed",
	"Wherever you go, there you are",
	"Energy comes at the cost of wisdom",
	"Riches abound when least expected",
	"Where avarice fails, patience gains reward",
	"Blessed by a benevolent companion!",
	"The hands of men may be guided by fate",
	"Strength is bolstered by heavenly faith",
	"The essence of life flows from within",
	"The way is made clear when viewed from above",
	"Salvation comes at the cost of wisdom",
	"Mysteries are revealed in the light of reason",
	"Those who are last may yet be first",
	"Generosity brings its own rewards",
	"You must be at least level 8 to use this.",
	"You must be at least level 13 to use this.",
	"You must be at least level 17 to use this.",
	"Arcane knowledge gained!"
};

void __fastcall InitDiabloMsg(char e)
{
	int i;

	for (i = 0; i < msgcnt; i++) {
		if (msgtable[i] == e)
			return;
	}

	msgtable[msgcnt] = e;
	if (msgcnt < (BYTE)sizeof(msgtable))
		msgcnt++;

	msgflag = msgtable[0];
	msgdelay = 70;
}

void __cdecl ClrDiabloMsg()
{
	int i;

	for (i = 0; i < sizeof(msgtable); i++)
		msgtable[i] = 0;

	msgflag = 0;
	msgcnt = 0;
}

void __cdecl DrawDiabloMsg()
{
	int v0;              // esi
	signed int v1;       // edi
	int v8;              // edi
	signed int v9;       // ebx
	signed int v10;      // eax
	signed int v11;      // ecx
	int v12;             // esi
	signed int v13;      // esi
	unsigned char v14;   // bl
	BOOLEAN v15;         // zf
	signed int v16;      // [esp+Ch] [ebp-8h]
	signed int v17;      // [esp+Ch] [ebp-8h]
	signed int screen_x; // [esp+10h] [ebp-4h]

	CelDecodeOnly(165, 318, (BYTE *)pSTextSlidCels, 1, 12);
	CelDecodeOnly(591, 318, (BYTE *)pSTextSlidCels, 4, 12);
	CelDecodeOnly(165, 366, (BYTE *)pSTextSlidCels, 2, 12);
	CelDecodeOnly(591, 366, (BYTE *)pSTextSlidCels, 3, 12);
	screen_x = 173;
	v16 = 35;
	do {
		CelDecodeOnly(screen_x, 318, (BYTE *)pSTextSlidCels, 5, 12);
		CelDecodeOnly(screen_x, 366, (BYTE *)pSTextSlidCels, 7, 12);
		screen_x += 12;
		--v16;
	} while (v16);
	v0 = 330;
	v1 = 3;
	do {
		CelDecodeOnly(165, v0, (BYTE *)pSTextSlidCels, 6, 12);
		CelDecodeOnly(591, v0, (BYTE *)pSTextSlidCels, 8, 12);
		v0 += 12;
		--v1;
	} while (v1);

#define TRANS_RECT_X 104
#define TRANS_RECT_Y 150
#define TRANS_RECT_WIDTH 432
#define TRANS_RECT_HEIGHT 54
#include "asm_trans_rect.inc"

	strcpy(tempstr, MsgStrings[msgflag]);
	v8 = screen_y_times_768[342] + 165;
	v9 = strlen(tempstr);
	v10 = 0;
	v11 = 0;
	v17 = v9;
	if (v9 <= 0)
		goto LABEL_27;
	do {
		v12 = (unsigned char)tempstr[v11++];
		v10 += fontkern[fontframe[gbFontTransTbl[v12]]] + 1;
	} while (v11 < v9);
	if (v10 < 442)
	LABEL_27:
		v8 += (442 - v10) >> 1;
	v13 = 0;
	if (v9 > 0) {
		do {
			v14 = fontframe[gbFontTransTbl[(unsigned char)tempstr[v13]]];
			if (v14)
				CPrintString(v8, v14, 3);
			++v13;
			v8 += fontkern[v14] + 1;
		} while (v13 < v17);
	}
	v15 = msgdelay == 0;
	if (msgdelay > 0)
		v15 = --msgdelay == 0;
	if (v15) {
		v15 = msgcnt-- == 1;
		msgdelay = 70;
		if (v15)
			msgflag = 0;
		else
			msgflag = msgtable[msgcnt];
	}
}

DEVILUTION_END_NAMESPACE
