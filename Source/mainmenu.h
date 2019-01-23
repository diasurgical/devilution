//HEADER_GOES_HERE
#ifndef __MAINMENU_H__
#define __MAINMENU_H__

extern char gszHero[16];

void __cdecl mainmenu_refresh_music();
void __stdcall mainmenu_create_hero(char *name_1, char *name_2);
int __stdcall mainmenu_select_hero_dialog(
    const _SNETPROGRAMDATA *client_info,
    const _SNETPLAYERDATA *user_info,
    const _SNETUIDATA *ui_info,
    const _SNETVERSIONDATA *fileinfo,
    DWORD mode,               // 4 chars, e.g. 'IPXN', 'BNET' etc. */
    char *cname, DWORD clen,  // character name will be copied here
    char *cdesc, DWORD cdlen, // character "description" will be copied here (used to advertise games)
    BOOL *multi);             // new character? - unsure about this
void __cdecl mainmenu_loop();
BOOL __cdecl mainmenu_single_player();
BOOL __fastcall mainmenu_init_menu(int a1);
BOOL __cdecl mainmenu_multi_player();
void __cdecl mainmenu_play_intro();

/* rdata */

extern const int mainmenu_inf; // weak

/* data */

extern int menu_music_track_id; // idb

#endif /* __MAINMENU_H__ */
