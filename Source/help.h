/**
 * @file help.h
 *
 * Interface of the in-game help text.
 */
#ifndef __HELP_H__
#define __HELP_H__

extern int help_select_line;
extern int dword_634494;
extern BOOL helpflag;
extern int displayinghelp[22];
extern int HelpTop;

void InitHelp();
void DrawHelp();
void DrawHelpLine(int x, int y, char *text, char color);
void DisplayHelp();
void HelpScrollUp();
void HelpScrollDown();

/* rdata */
extern const char gszHelpText[];

#endif /* __HELP_H__ */
