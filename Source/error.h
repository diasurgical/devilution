//HEADER_GOES_HERE
#ifndef __ERROR_H__
#define __ERROR_H__

extern char msgtable[MAX_SEND_STR_LEN];
extern char msgdelay;
extern char msgflag;
extern char msgcnt;

void InitDiabloMsg(char e);
void ClrDiabloMsg();
void DrawDiabloMsg();

/* data */
extern char *MsgStrings[];

#endif /* __ERROR_H__ */
