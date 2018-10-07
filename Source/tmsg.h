//HEADER_GOES_HERE
#ifndef __TMSG_H__
#define __TMSG_H__

int __fastcall tmsg_get(BYTE *pbMsg, DWORD dwMaxLen);
void __fastcall tmsg_add(BYTE *pbMsg, BYTE bLen);
void* __cdecl tmsg_cleanup();

#endif /* __TMSG_H__ */
