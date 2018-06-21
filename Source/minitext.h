//HEADER_GOES_HERE
#ifndef __MINITEXT_H__
#define __MINITEXT_H__

extern int qtexty; // weak
extern char *qtextptr;
extern int qtextSpd; // weak
extern char qtextflag; // weak
extern int scrolltexty; // weak
extern int sgLastScroll; // weak
extern void *pMedTextCels;
extern void *pTextBoxCels;

void __cdecl FreeQuestText();
void __cdecl InitQuestText();
void __fastcall InitQTextMsg(int m);
void __cdecl DrawQTextBack();
void __fastcall PrintQTextChr(int screen_x, int screen_y, char *cel_buf, int frame);
void __cdecl DrawQText();

/* data */

extern unsigned char mfontframe[127];
extern unsigned char mfontkern[56];

/* rdata */

extern int qscroll_spd_tbl[9];

#endif /* __MINITEXT_H__ */
