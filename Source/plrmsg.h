/**
 * @file plrmsg.h
 *
 * Interface of functionality for printing the ingame chat messages.
 */
#ifndef __PLRMSG_H__
#define __PLRMSG_H__

void plrmsg_delay(BOOL delay);
char *ErrorPlrMsg(const char *pszMsg);
size_t __cdecl EventPlrMsg(const char *pszFmt, ...);
void SendPlrMsg(int pnum, const char *pszStr);
void ClearPlrMsg();
void InitPlrMsg();
void DrawPlrMsg();
void PrintPlrMsg(DWORD x, DWORD y, DWORD width, const char *str, BYTE col);

#endif /* __PLRMSG_H__ */
