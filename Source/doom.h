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

//doom
extern int doom_quest_time; // weak
extern int doom_stars_drawn; // weak
extern void *pDoomCel;
extern int doomflag; // weak
extern int DoomQuestState; // idb

int __cdecl doom_get_frame_from_time();
void __cdecl doom_alloc_cel();
void __cdecl doom_cleanup();
void __cdecl doom_load_graphics();
void __cdecl doom_init();
void __cdecl doom_close();
void __cdecl doom_draw();