//HEADER_GOES_HERE
#ifndef __DOOM_H__
#define __DOOM_H__

extern int doom_quest_time;  // weak
extern int doom_stars_drawn; // weak
extern void *pDoomCel;
extern int doomflag;       // weak
extern int DoomQuestState; // idb

/*
void doom_reset_state();
void doom_play_movie();
*/
int doom_get_frame_from_time();
void doom_alloc_cel();
void doom_cleanup();
void doom_load_graphics();
void doom_init();
void doom_close();
void doom_draw();

#endif /* __DOOM_H__ */
