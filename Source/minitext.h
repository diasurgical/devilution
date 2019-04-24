//HEADER_GOES_HERE
#ifndef __MINITEXT_H__
#define __MINITEXT_H__

extern int qtexty; // weak
extern char *qtextptr;
extern int qtextSpd;    // weak
extern char qtextflag;  // weak
extern int scrolltexty; // weak
extern void *pMedTextCels;
extern void *pTextBoxCels;

void FreeQuestText();
void InitQuestText();
void InitQTextMsg(int m);
void DrawQTextBack();
void PrintQTextChr(int sx, int sy, BYTE *pCelBuff, int nCel);
void DrawQText();

/* rdata */

extern const unsigned char mfontframe[127];
extern const unsigned char mfontkern[56];

/* data */

extern int qscroll_spd_tbl[9];

#endif /* __MINITEXT_H__ */
