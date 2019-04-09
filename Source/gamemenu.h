//HEADER_GOES_HERE
#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__

void gamemenu_previous();
void gamemenu_enable_single(TMenuItem *a1);
void gamemenu_enable_multi(TMenuItem *a1);
void gamemenu_off();
void gamemenu_handle_previous();
void j_gamemenu_previous(BOOL a1);
void gamemenu_new_game(BOOL a1);
void gamemenu_quit_game(BOOL a1);
void gamemenu_load_game(BOOL a1);
void gamemenu_save_game(BOOL a1);
void gamemenu_restart_town(BOOL a1);
void gamemenu_options(BOOL a1);
void gamemenu_get_music();
void gamemenu_sound_music_toggle(char **names, TMenuItem *menu_item, int gamma);
void gamemenu_get_sound();
void gamemenu_get_color_cycling();
void gamemenu_get_gamma();
void gamemenu_music_volume(BOOL a1);
int gamemenu_slider_music_sound(TMenuItem *menu_item);
void gamemenu_sound_volume(BOOL a1);
void gamemenu_gamma(BOOL a1);
int gamemenu_slider_gamma();
void gamemenu_color_cycling(BOOL a1);

/* rdata */
extern char *music_toggle_names[];
extern char *sound_toggle_names[];
extern char *color_cycling_toggle_names[];

#endif /* __GAMEMENU_H__ */
