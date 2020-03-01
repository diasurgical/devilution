/**
 * @file error.cpp
 *
 * Implementation of in-game message functions.
 */
#include "all.h"

char msgtable[MAX_SEND_STR_LEN];
char msgdelay;
char msgflag;
char msgcnt;

/** Maps from error_id to error message. */
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

void InitDiabloMsg(char e)
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

void ClrDiabloMsg()
{
	int i;

	for (i = 0; i < sizeof(msgtable); i++)
		msgtable[i] = 0;

	msgflag = 0;
	msgcnt = 0;
}

void DrawDiabloMsg()
{
	int i, len, off, width, sx, sy;
	BYTE c;

	CelDraw(PANEL_X + 101, DIALOG_Y, pSTextSlidCels, 1, 12);
	CelDraw(PANEL_X + 527, DIALOG_Y, pSTextSlidCels, 4, 12);
	CelDraw(PANEL_X + 101, DIALOG_Y + 48, pSTextSlidCels, 2, 12);
	CelDraw(PANEL_X + 527, DIALOG_Y + 48, pSTextSlidCels, 3, 12);

	sx = PANEL_X + 109;
	for (i = 0; i < 35; i++) {
		CelDraw(sx, DIALOG_Y, pSTextSlidCels, 5, 12);
		CelDraw(sx, DIALOG_Y + 48, pSTextSlidCels, 7, 12);
		sx += 12;
	}
	sy = DIALOG_Y + 12;
	for (i = 0; i < 3; i++) {
		CelDraw(PANEL_X + 101, sy, pSTextSlidCels, 6, 12);
		CelDraw(PANEL_X + 527, sy, pSTextSlidCels, 8, 12);
		sy += 12;
	}

	/// ASSERT: assert(gpBuffer);

#define TRANS_RECT_X (PANEL_LEFT + 104)
#define TRANS_RECT_Y (DIALOG_TOP - 8)
#define TRANS_RECT_WIDTH 432
#define TRANS_RECT_HEIGHT 54
#include "asm_trans_rect.inc"

	strcpy(tempstr, MsgStrings[msgflag]);
	off = PANEL_X + 101 + PitchTbl[DIALOG_Y + 24];
	len = strlen(tempstr);
	width = 0;

	for (i = 0; i < len; i++) {
		width += fontkern[fontframe[gbFontTransTbl[(BYTE)tempstr[i]]]] + 1;
	}

	if (width < 442) {
		off += (442 - width) >> 1;
	}

	for (i = 0; i < len; i++) {
		c = fontframe[gbFontTransTbl[(BYTE)tempstr[i]]];
		if (c != '\0') {
			PrintChar(off, c, COL_GOLD);
		}
		off += fontkern[c] + 1;
	}

	if (msgdelay > 0) {
		msgdelay--;
	}
	if (msgdelay == 0) {
		msgcnt--;
		msgdelay = 70;
		if (msgcnt == 0) {
			msgflag = 0;
		} else {
			msgflag = msgtable[msgcnt];
		}
	}
}
