//HEADER_GOES_HERE
#ifndef __PLRMSG_H__
#define __PLRMSG_H__

extern _plrmsg plr_msgs[PMSG_COUNT];

void plrmsg_delay(BOOL delay);
char *ErrorPlrMsg(const char *pszMsg);
size_t __cdecl EventPlrMsg(const char *pszFmt, ...);
void SendPlrMsg(int pnum, const char *pszStr);
void ClearPlrMsg();
void InitPlrMsg();
void DrawPlrMsg();
void PrintPlrMsg(unsigned int x, unsigned int y, unsigned int width, const char *str, unsigned char just);

/* rdata */

extern const char text_color_from_player_num[MAX_PLRS + 1];

#endif /* __PLRMSG_H__ */
