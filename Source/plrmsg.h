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

//plrmsg
extern int plrmsg_ticks; // weak
extern char plr_msg_slot; // weak
extern _plrmsg plr_msgs[8];

void __fastcall plrmsg_delay(int a1);
char *__fastcall ErrorPlrMsg(char *pszMsg);
size_t EventPlrMsg(char *pszFmt, ...);
void __fastcall SendPlrMsg(int pnum, const char *pszStr);
void __cdecl ClearPlrMsg();
void __cdecl InitPlrMsg();
void __cdecl DrawPlrMsg();
void __fastcall PrintPlrMsg(int no, int x, int y, char *str, int just);

/* data */

extern text_color text_color_from_player_num[2];
