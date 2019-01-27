//HEADER_GOES_HERE

#include "../types.h"

char gszHero[16];

/* data */

int menu_music_track_id = 5;

void __cdecl mainmenu_refresh_music()
{
	music_start(menu_music_track_id);
	do {
		menu_music_track_id++;
		if (menu_music_track_id == 6)
			menu_music_track_id = 0;
	} while (!menu_music_track_id || menu_music_track_id == 1);
}

void __stdcall mainmenu_create_hero(char *name_1, char *name_2)
{
	if (UiValidPlayerName(name_1))
		pfile_create_save_file(name_1, name_2);
}

int __stdcall mainmenu_select_hero_dialog(
    const _SNETPROGRAMDATA *client_info,
    const _SNETPLAYERDATA *user_info,
    const _SNETUIDATA *ui_info,
    const _SNETVERSIONDATA *fileinfo,
    DWORD mode,
    char *cname, DWORD clen,
    char *cdesc, DWORD cdlen,
    BOOL *multi)
{
	BOOL hero_is_created = TRUE;
	int dlgresult = 0;
	if (gbMaxPlayers == 1) {
		if (!UiSelHeroSingDialog(
		        pfile_ui_set_hero_infos,
		        pfile_ui_save_create,
		        pfile_delete_save,
		        pfile_ui_set_class_stats,
		        &dlgresult,
		        gszHero,
		        &gnDifficulty))
			TermMsg("Unable to display SelHeroSing");

		if (dlgresult == 2)
			gbLoadGame = TRUE;
		else
			gbLoadGame = FALSE;

	} else if (!UiSelHeroMultDialog(
	               pfile_ui_set_hero_infos,
	               pfile_ui_save_create,
	               pfile_delete_save,
	               pfile_ui_set_class_stats,
	               &dlgresult,
	               &hero_is_created,
	               gszHero)) {
		TermMsg("Can't load multiplayer dialog");
	}
	if (dlgresult == 4) {
		SErrSetLastError(1223);
		return 0;
	}

	pfile_create_player_description(cdesc, cdlen);
	if (multi) {
		if (mode == 'BNET')
			*multi = hero_is_created || !plr[myplr].pBattleNet;
		else
			*multi = hero_is_created;
	}
	if (cname && clen)
		SStrCopy(cname, gszHero, clen);

	return 1;
}

void __cdecl mainmenu_loop()
{
	BOOL done;
	int menu;

	done = FALSE;
	mainmenu_refresh_music();

	do {
		menu = 0;
		if (!UiMainMenuDialog("Diablo v1.09", &menu, effects_play_sound, 30))
			TermMsg("Unable to display mainmenu");

		switch (menu) {
		case MAINMENU_SINGLE_PLAYER:
			if (!mainmenu_single_player())
				done = TRUE;
			break;
		case MAINMENU_MULTIPLAYER:
			if (!mainmenu_multi_player())
				done = TRUE;
			break;
		case MAINMENU_REPLAY_INTRO:
		case MAINMENU_ATTRACT_MODE:
			if (gbActive)
				mainmenu_play_intro();
			break;
		case MAINMENU_SHOW_CREDITS:
			UiCreditsDialog(16);
			break;
		case MAINMENU_EXIT_DIABLO:
			done = TRUE;
			break;
		}
	} while (done == FALSE);

	music_stop();
}
// 634980: using guessed type int gbActive;

BOOL __cdecl mainmenu_single_player()
{
	gbMaxPlayers = 1;
	return mainmenu_init_menu(1);
}
// 679660: using guessed type char gbMaxPlayers;

BOOL __fastcall mainmenu_init_menu(int type)
{
	BOOL success;

	if (type == 4)
		return TRUE;

	music_stop();

	success = StartGame(type != 2, type != 3);
	if (success)
		mainmenu_refresh_music();

	return success;
}

BOOL __cdecl mainmenu_multi_player()
{
	gbMaxPlayers = MAX_PLRS;
	return mainmenu_init_menu(3);
}

void __cdecl mainmenu_play_intro()
{
	music_stop();
	play_movie("gendata\\diablo1.smk", 1);
	mainmenu_refresh_music();
}
