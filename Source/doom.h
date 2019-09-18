//HEADER_GOES_HERE
#ifndef __DOOM_H__
#define __DOOM_H__

extern int doom_quest_time;
extern int doom_stars_drawn;
extern BYTE *pDoomCel;
#ifdef HELLFIRE
extern BOOLEAN doomflag;
#else
extern BOOL doomflag;
#endif
extern int DoomQuestState;

/*
void doom_reset_state();
void doom_play_movie();
*/
int doom_get_frame_from_time();
#ifdef HELLFIRE
BOOLEAN doom_alloc_cel();
void doom_cleanup();
BOOLEAN doom_load_graphics();
#else
void doom_alloc_cel();
void doom_cleanup();
void doom_load_graphics();
#endif
void doom_init();
void doom_close();
void doom_draw();

#endif /* __DOOM_H__ */
