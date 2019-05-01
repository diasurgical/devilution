//HEADER_GOES_HERE
#ifndef __HELP_H__
#define __HELP_H__

extern int help_select_line; // weak
extern int dword_634494;     // weak
extern int helpflag;
extern int displayinghelp[22];
extern int HelpTop; // weak

void InitHelp();
void DrawHelp();
void DrawHelpLine(int always_0, int help_line_nr, char *text, char color);
void DisplayHelp();
void HelpScrollUp();
void HelpScrollDown();

/* rdata */
extern const char gszHelpText[];

#endif /* __HELP_H__ */
