//HEADER_GOES_HERE
#ifndef __ERROR_H__
#define __ERROR_H__

extern char msgtable[MAX_SEND_STR_LEN];
extern char msgdelay;
extern char msgflag;
extern char msgcnt;

void __fastcall InitDiabloMsg(char e);
void __cdecl ClrDiabloMsg();
void __cdecl DrawDiabloMsg();

/* data */
extern char *MsgStrings[44];

#endif /* __ERROR_H__ */
