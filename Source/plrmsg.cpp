//HEADER_GOES_HERE

#include "../types.h"

DEVILUTION_BEGIN_NAMESPACE

static unsigned char plr_msg_slot;
_plrmsg plr_msgs[PMSG_COUNT];

const char text_color_from_player_num[MAX_PLRS + 1] = { COL_WHITE, COL_WHITE, COL_WHITE, COL_WHITE, COL_GOLD };

void __fastcall plrmsg_delay(BOOL delay)
{
	int i;
	_plrmsg *pMsg;
	static DWORD plrmsg_ticks;

	if (delay) {
		plrmsg_ticks = -GetTickCount();
		return;
	}

	plrmsg_ticks += GetTickCount();
	pMsg = plr_msgs;
	for (i = 0; i < PMSG_COUNT; i++, pMsg++)
		pMsg->time += plrmsg_ticks;
}

char *__fastcall ErrorPlrMsg(const char *pszMsg)
{
	char *result;
	_plrmsg *pMsg = &plr_msgs[plr_msg_slot];
	plr_msg_slot = (plr_msg_slot + 1) & (PMSG_COUNT - 1);
	pMsg->player = MAX_PLRS;
	pMsg->time = GetTickCount();
	result = strncpy(pMsg->str, pszMsg, sizeof(pMsg->str));
	pMsg->str[sizeof(pMsg->str) - 1] = '\0';
	return result;
}

size_t EventPlrMsg(const char *pszFmt, ...)
{
	_plrmsg *pMsg;
	va_list va;

	va_start(va, pszFmt);
	pMsg = &plr_msgs[plr_msg_slot];
	plr_msg_slot = (plr_msg_slot + 1) & (PMSG_COUNT - 1);
	pMsg->player = MAX_PLRS;
	pMsg->time = GetTickCount();
	vsprintf(pMsg->str, pszFmt, va);
	va_end(va);
	return strlen(pMsg->str);
}

void __fastcall SendPlrMsg(int pnum, const char *pszStr)
{
	_plrmsg *pMsg = &plr_msgs[plr_msg_slot];
	plr_msg_slot = (plr_msg_slot + 1) & (PMSG_COUNT - 1);
	pMsg->player = pnum;
	pMsg->time = GetTickCount();
	strlen(plr[pnum]._pName); /* these are used in debug */
	strlen(pszStr);
	sprintf(pMsg->str, "%s (lvl %d): %s", plr[pnum]._pName, plr[pnum]._pLevel, pszStr);
}

void __cdecl ClearPlrMsg()
{
	int i;
	_plrmsg *pMsg = plr_msgs;
	DWORD tick = GetTickCount();

	for (i = 0; i < PMSG_COUNT; i++, pMsg++) {
		if ((int)(tick - pMsg->time) > 10000)
			pMsg->str[0] = '\0';
	}
}

void __cdecl InitPlrMsg()
{
	memset(plr_msgs, 0, sizeof(plr_msgs));
	plr_msg_slot = 0;
}

void __cdecl DrawPlrMsg()
{
	int i;
	int x = 74;
	int y = 230;
	int width = 620;
	_plrmsg *pMsg;

	if (chrflag || questlog) {
		if (invflag || sbookflag)
			return;
		x = 394;
		width = 300;
	} else if (invflag || sbookflag)
		width = 300;

	pMsg = plr_msgs;
	for (i = 0; i < 8; i++) {
		if (pMsg->str[0])
			PrintPlrMsg(x, y, width, pMsg->str, text_color_from_player_num[pMsg->player]);
		pMsg++;
		y += 35;
	}
}

void __fastcall PrintPlrMsg(unsigned int x, unsigned int y, unsigned int width, const char *str, unsigned char col)
{
	int line = 0;

	while (*str) {
		unsigned char c;
		int screen = screen_y_times_768[y] + x;
		const char *sstr = str;
		unsigned int len = 0;
		const char *endstr = sstr;

		while (1) {
			if (*sstr) {
				c = gbFontTransTbl[(unsigned char)*sstr++];
				c = fontframe[c];
				len += fontkern[c] + 1;
				if (!c) // allow wordwrap on blank glyph
					endstr = sstr;
				else if (len >= width)
					break;
			} else {
				endstr = sstr;
				break;
			}
		}

		while (str < endstr) {
			c = gbFontTransTbl[(unsigned char)*str++];
			c = fontframe[c];
			if (c)
				CPrintString(screen, c, col);
			screen += fontkern[c] + 1;
		}

		y += 10;
		line++;
		if (line == 3)
			break;
	}
}

DEVILUTION_END_NAMESPACE
