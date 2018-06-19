//HEADER_GOES_HERE

//tmsg
extern TMsg *sgpTimedMsgHead;

int __fastcall tmsg_get(unsigned char *pbMsg, char bLen);
void __fastcall tmsg_add(unsigned char *pbMsg, char bLen);
void __cdecl tmsg_cleanup();