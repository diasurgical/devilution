/**
 * @file help.h
 *
 * Interface of the in-game help text.
 */
#ifndef __HELP_H__
#define __HELP_H__

extern BOOL helpflag;

void InitHelp();
void DrawHelp();
void DisplayHelp();
void HelpScrollUp();
void HelpScrollDown();

#endif /* __HELP_H__ */
