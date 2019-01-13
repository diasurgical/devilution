//HEADER_GOES_HERE
#ifndef __PLRMSG_H__
#define __PLRMSG_H__

extern _plrmsg plr_msgs[PMSG_COUNT];

void __fastcall plrmsg_delay(BOOL delay);
char *__fastcall ErrorPlrMsg(const char *pszMsg);
size_t EventPlrMsg(const char *pszFmt, ...);
void __fastcall SendPlrMsg(int pnum, const char *pszStr);
void __cdecl ClearPlrMsg();
void __cdecl InitPlrMsg();
void __cdecl DrawPlrMsg();
void __fastcall PrintPlrMsg(unsigned int x, unsigned int y, unsigned int width, const char *str, unsigned char just);

/* rdata */

extern const char text_color_from_player_num[MAX_PLRS + 1];

#endif /* __PLRMSG_H__ */
