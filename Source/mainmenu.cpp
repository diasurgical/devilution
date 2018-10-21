//HEADER_GOES_HERE

#include "../types.h"

static float mainmenu_cpp_init_value = INFINITY;
char chr_name_str[16];

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
    const struct _SNETPROGRAMDATA *u1,
    const struct _SNETPLAYERDATA *u2,
    const struct _SNETUIDATA *u3,
    const struct _SNETVERSIONDATA *u4,
    DWORD mode,
    char *cname, DWORD clen,
    char *cdesc, DWORD cdlen,
    BOOL *multi)
{
    int a6 = 1;
    int a5 = 0;
    if (gbMaxPlayers == 1) {
        if (!UiSelHeroSingDialog(
                pfile_ui_set_hero_infos,
                pfile_ui_save_create,
                pfile_delete_save,
                pfile_ui_set_class_stats,
                &a5,
                chr_name_str,
                &gnDifficulty))
            TermMsg("Unable to display SelHeroSing");

        if (a5 == 2)
            dword_5256E8 = TRUE;
        else
            dword_5256E8 = FALSE;

    } else if (!UiSelHeroMultDialog(
                   pfile_ui_set_hero_infos,
                   pfile_ui_save_create,
                   pfile_delete_save,
                   pfile_ui_set_class_stats,
                   &a5,
                   &a6,
                   chr_name_str)) {
        TermMsg("Can't load multiplayer dialog");
    }
    if (a5 == 4) {
        SErrSetLastError(1223);
        return 0;
    }

    pfile_create_player_description(cdesc, cdlen);
    if (multi) {
        if (mode == 'BNET')
            *multi = a6 || !plr[myplr].pBattleNet;
        else
            *multi = a6;
    }
    if (cname && clen)
        SStrCopy(cname, chr_name_str, clen);

    return 1;
}

void __cdecl mainmenu_loop()
{
    int v1; // eax
    int a2; // [esp+0h] [ebp-4h]

    mainmenu_refresh_music();
    do {
        while (1) {
            a2 = 0;
            if (!UiMainMenuDialog("Diablo v1.09", &a2, effects_play_sound, 30))
                TermMsg("Unable to display mainmenu");
            if (a2 == 1)
                break;
            switch (a2) {
            case MAINMENU_MULTIPLAYER:
                v1 = mainmenu_multi_player();
                goto LABEL_15;
            case MAINMENU_REPLAY_INTRO:
                goto LABEL_10;
            case MAINMENU_SHOW_CREDITS:
                UiCreditsDialog(16);
                break;
            case MAINMENU_EXIT_DIABLO:
                goto LABEL_16;
            case MAINMENU_ATTRACT_MODE:
            LABEL_10:
                if (gbActive)
                    mainmenu_play_intro();
                break;
            }
        }
        v1 = mainmenu_single_player();
    LABEL_15:;
    } while (v1);
LABEL_16:
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
    if (type == 4)
        return 1;

    music_stop();

    int success = diablo_init_menu(type != 2, type != 3);
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
