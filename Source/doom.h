/**
 * @file doom.h
 *
 * Interface of the map of the stars quest.
 */
#ifndef __DOOM_H__
#define __DOOM_H__

extern DIABOOL doomflag;
extern int DoomQuestState;

#ifdef HELLFIRE
BOOLEAN doom_alloc_cel();
BOOLEAN doom_load_graphics();
#else
void doom_alloc_cel();
void doom_load_graphics();
#endif
void doom_cleanup();
void doom_init();
void doom_close();
void doom_draw();

#endif /* __DOOM_H__ */
