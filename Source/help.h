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

//help
extern int help_select_line; // weak
extern int dword_634494; // weak
extern int helpflag;
extern int displayinghelp[22];
extern int HelpTop; // weak

void __cdecl InitHelp();
void __cdecl DrawHelp();
void __fastcall DrawHelpLine(int always_0, int help_line_nr, char *text, text_color color);
void __cdecl DisplayHelp();
void __cdecl HelpScrollUp();
void __cdecl HelpScrollDown();

/* data */
extern char gszHelpText[];
