//HEADER_GOES_HERE
#ifndef __TMSG_H__
#define __TMSG_H__

extern TMsg *sgpTimedMsgHead;

int __fastcall tmsg_get(unsigned char *pbMsg, char bLen);
void __fastcall tmsg_add(unsigned char *pbMsg, char bLen);
void __cdecl tmsg_cleanup();

#endif /* __TMSG_H__ */
