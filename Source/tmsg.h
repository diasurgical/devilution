//HEADER_GOES_HERE
#ifndef __TMSG_H__
#define __TMSG_H__

int __fastcall tmsg_get(UCHAR *pbMsg, DWORD dwMaxLen);
void __fastcall tmsg_add(UCHAR *pbMsg, UCHAR bLen);
void* __cdecl tmsg_cleanup();

#endif /* __TMSG_H__ */
