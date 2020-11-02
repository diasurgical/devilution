/**
 * @file doom.h
 *
 * Interface of the map of the stars quest.
 */
#ifndef __DOOM_H__
#define __DOOM_H__

extern DIABOOL doomflag;
extern int DoomQuestState;

void doom_init();
void doom_close();
void doom_draw();

#endif /* __DOOM_H__ */
