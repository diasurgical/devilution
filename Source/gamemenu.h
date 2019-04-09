//HEADER_GOES_HERE
#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__

void __cdecl gamemenu_previous();
void __fastcall gamemenu_enable_single(TMenuItem *a1);
void __fastcall gamemenu_enable_multi(TMenuItem *a1);
void __cdecl gamemenu_off();
void __cdecl gamemenu_handle_previous();
void __fastcall j_gamemenu_previous(BOOL a1);
void __fastcall gamemenu_new_game(BOOL a1);
void __fastcall gamemenu_quit_game(BOOL a1);
void __fastcall gamemenu_load_game(BOOL a1);
void __fastcall gamemenu_save_game(BOOL a1);
void __fastcall gamemenu_restart_town(BOOL a1);
void __fastcall gamemenu_options(BOOL a1);
void __cdecl gamemenu_get_music();
void __fastcall gamemenu_sound_music_toggle(char **names, TMenuItem *menu_item, int gamma);
void __cdecl gamemenu_get_sound();
void __cdecl gamemenu_get_color_cycling();
void __cdecl gamemenu_get_gamma();
void __fastcall gamemenu_music_volume(BOOL a1);
int __fastcall gamemenu_slider_music_sound(TMenuItem *menu_item);
void __fastcall gamemenu_sound_volume(BOOL a1);
void __fastcall gamemenu_gamma(BOOL a1);
int __cdecl gamemenu_slider_gamma();
void __fastcall gamemenu_color_cycling(BOOL a1);

/* rdata */
extern char *music_toggle_names[];
extern char *sound_toggle_names[];
extern char *color_cycling_toggle_names[];

#endif /* __GAMEMENU_H__ */
