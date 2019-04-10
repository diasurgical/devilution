//HEADER_GOES_HERE

#include "../types.h"

TMenuItem sgSingleMenu[6] = {
	// clang-format off
	//   dwFlags, pszStr,        fnMenu
	{ 0x80000000, "Save Game",   &gamemenu_save_game },
	{ 0x80000000, "Options",     &gamemenu_options   },
	{ 0x80000000, "New Game",    &gamemenu_new_game  },
	{ 0x80000000, "Load Game",   &gamemenu_load_game },
	{ 0x80000000, "Quit Diablo", &gamemenu_quit_game },
	{ 0x80000000, NULL, NULL }
	// clang-format on
};
TMenuItem sgMultiMenu[5] = {
	// clang-format off
	//   dwFlags, pszStr,            fnMenu
	{ 0x80000000, "Options",         &gamemenu_options      },
	{ 0x80000000, "New Game",        &gamemenu_new_game     },
	{ 0x80000000, "Restart In Town", &gamemenu_restart_town },
	{ 0x80000000, "Quit Diablo",     &gamemenu_quit_game    },
	{ 0x80000000, NULL,              NULL                   }
	// clang-format on
};
TMenuItem sgOptionMenu[6] = {
	// clang-format off
	//   dwFlags, pszStr,          fnMenu
	{ 0xC0000000, NULL,            &gamemenu_music_volume  },
	{ 0xC0000000, NULL,            &gamemenu_sound_volume  },
	{ 0xC0000000, "Gamma",         &gamemenu_gamma         },
	{ 0x80000000, NULL,            &gamemenu_color_cycling },
	{ 0x80000000, "Previous Menu", &j_gamemenu_previous    },
	{ 0x80000000, NULL,            NULL                    }
	// clang-format on
};
char *music_toggle_names[] = { "Music", "Music Disabled" };
char *sound_toggle_names[] = { "Sound", "Sound Disabled" };
char *color_cycling_toggle_names[] = { "Color Cycling Off", "Color Cycling On" };

void gamemenu_previous()
{
	void(* proc)(TMenuItem *);
	TMenuItem *item;

	if (gbMaxPlayers == 1) {
		proc = gamemenu_enable_single;
		item = sgSingleMenu;
	} else {
		proc = gamemenu_enable_multi;
		item = sgMultiMenu;
	}
	gmenu_call_proc(item, proc);
	PressEscKey();
}

void gamemenu_enable_single(TMenuItem *a1)
{
	BOOL enable;

	gmenu_enable(&sgSingleMenu[3], gbValidSaveFile);

	enable = FALSE;
	if (plr[myplr]._pmode != PM_DEATH && !deathflag)
		enable = TRUE;

	gmenu_enable(sgSingleMenu, enable);
}

void gamemenu_enable_multi(TMenuItem *a1)
{
	gmenu_enable(&sgMultiMenu[2], deathflag);
}

void gamemenu_off()
{
	gmenu_call_proc(0, NULL);
}

void gamemenu_handle_previous()
{
	if (gmenu_exception())
		gamemenu_off();
	else
		gamemenu_previous();
}

void j_gamemenu_previous(BOOL a1)
{
	gamemenu_previous();
}

void gamemenu_new_game(BOOL a1)
{
	int i;

	for (i = 0; i < MAX_PLRS; i++) {
		plr[i]._pmode = PM_QUIT;
		plr[i]._pInvincible = TRUE;
	}

	deathflag = FALSE;
	drawpanflag = 255;
	scrollrt_draw_game_screen(TRUE);
	gbRunGame = FALSE;
	gamemenu_off();
}
// 52571C: using guessed type int drawpanflag;

void gamemenu_quit_game(BOOL a1)
{
	gamemenu_new_game(a1);
	gbRunGameResult = FALSE;
}

void gamemenu_load_game(BOOL a1)
{
	WNDPROC saveProc = SetWindowProc(DisableInputWndProc);
	gamemenu_off();
	SetCursor_(CURSOR_NONE);
	InitDiabloMsg(EMSG_LOADING);
	drawpanflag = 255;
	DrawAndBlit();
	LoadGame(FALSE);
	ClrDiabloMsg();
	PaletteFadeOut(8);
	deathflag = FALSE;
	drawpanflag = 255;
	DrawAndBlit();
	PaletteFadeIn(8);
	SetCursor_(CURSOR_HAND);
	interface_msg_pump();
	SetWindowProc(saveProc);
}
// 52571C: using guessed type int drawpanflag;

void gamemenu_save_game(BOOL a1)
{
	if (pcurs == CURSOR_HAND) {
		if (plr[myplr]._pmode == PM_DEATH || deathflag) {
			gamemenu_off();
		} else {
			WNDPROC saveProc = SetWindowProc(DisableInputWndProc);
			SetCursor_(CURSOR_NONE);
			gamemenu_off();
			InitDiabloMsg(EMSG_SAVING);
			drawpanflag = 255;
			DrawAndBlit();
			SaveGame();
			ClrDiabloMsg();
			drawpanflag = 255;
			SetCursor_(CURSOR_HAND);
			interface_msg_pump();
			SetWindowProc(saveProc);
		}
	}
}
// 52571C: using guessed type int drawpanflag;

void gamemenu_restart_town(BOOL a1)
{
	NetSendCmd(TRUE, CMD_RETOWN);
}

void gamemenu_options(BOOL a1)
{
	gamemenu_get_music();
	gamemenu_get_sound();
	gamemenu_get_gamma();
	gamemenu_get_color_cycling();
	gmenu_call_proc(sgOptionMenu, NULL);
}

void gamemenu_get_music()
{
	gamemenu_sound_music_toggle(music_toggle_names, sgOptionMenu, sound_get_or_set_music_volume(1));
}

void gamemenu_sound_music_toggle(char **names, TMenuItem *menu_item, int volume)
{
	if (gbSndInited) {
		menu_item->dwFlags |= 0xC0000000;
		menu_item->pszStr = *names;
		gmenu_slider_3(menu_item, 17);
		gmenu_slider_1(menu_item, VOLUME_MIN, VOLUME_MAX, volume);
	} else {
		menu_item->dwFlags &= 0x3FFFFFFF;
		menu_item->pszStr = names[1];
	}
}

void gamemenu_get_sound()
{
	gamemenu_sound_music_toggle(sound_toggle_names, &sgOptionMenu[1], sound_get_or_set_sound_volume(1));
}

void gamemenu_get_color_cycling()
{
	sgOptionMenu[3].pszStr = color_cycling_toggle_names[palette_get_colour_cycling() & 1];
}

void gamemenu_get_gamma()
{
	gmenu_slider_3(&sgOptionMenu[2], 15);
	gmenu_slider_1(&sgOptionMenu[2], 30, 100, UpdateGamma(0));
}

void gamemenu_music_volume(BOOL a1)
{
	int volume;
	if (a1) {
		if (gbMusicOn) {
			gbMusicOn = FALSE;
			music_stop();
			sound_get_or_set_music_volume(VOLUME_MIN);
			gamemenu_get_music();
			return;
		}
		gbMusicOn = TRUE;
		sound_get_or_set_music_volume(VOLUME_MAX);
		music_start(leveltype);
		gamemenu_get_music();
		return;
	}

	volume = gamemenu_slider_music_sound(sgOptionMenu);
	sound_get_or_set_music_volume(volume);

	if (volume == VOLUME_MIN) {

		if (gbMusicOn) {
			gbMusicOn = FALSE;
			music_stop();
		}

		gamemenu_get_music();
		return;
	}

	if (gbMusicOn) {
		gamemenu_get_music();
		return;
	}

	gbMusicOn = TRUE;
	music_start(leveltype);
	gamemenu_get_music();
}

int gamemenu_slider_music_sound(TMenuItem *menu_item)
{
	return gmenu_slider_get(menu_item, VOLUME_MIN, VOLUME_MAX);
}

void gamemenu_sound_volume(BOOL a1)
{
	int volume;
	if (a1) {
		if (gbSoundOn) {
			gbSoundOn = FALSE;
			FreeMonsterSnd();
			sound_get_or_set_sound_volume(VOLUME_MIN);
		} else {
			gbSoundOn = TRUE;
			sound_get_or_set_sound_volume(VOLUME_MAX);
		}
	} else {
		volume = gamemenu_slider_music_sound(&sgOptionMenu[1]);
		sound_get_or_set_sound_volume(volume);
		if (volume == VOLUME_MIN) {
			if (gbSoundOn) {
				gbSoundOn = FALSE;
				FreeMonsterSnd();
			}
		} else if (!gbSoundOn) {
			gbSoundOn = TRUE;
		}
	}
	PlaySFX(IS_TITLEMOV);
	gamemenu_get_sound();
}

void gamemenu_gamma(BOOL a1)
{
	int gamma;
	if (a1) {
		if (UpdateGamma(0) == 30)
			gamma = 100;
		else
			gamma = 30;
	} else {
		gamma = gamemenu_slider_gamma();
	}

	UpdateGamma(gamma);
	gamemenu_get_gamma();
}

int gamemenu_slider_gamma()
{
	return gmenu_slider_get(&sgOptionMenu[2], 30, 100);
}

void gamemenu_color_cycling(BOOL a1)
{
	BOOL color_cycling;

	color_cycling = palette_set_color_cycling(palette_get_colour_cycling() == 0);
	sgOptionMenu[3].pszStr = color_cycling_toggle_names[color_cycling & 1];
}
