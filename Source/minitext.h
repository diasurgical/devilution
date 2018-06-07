/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

//minitext
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
