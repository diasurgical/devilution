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

#include "../types.h"

TMenuItem sgSingleMenu[6] =
{
  { 0x80000000, "Save Game", &gamemenu_save_game },
  { 0x80000000, "Options", &gamemenu_options },
  { 0x80000000, "New Game", &gamemenu_new_game },
  { 0x80000000, "Load Game", &gamemenu_load_game },
  { 0x80000000, "Quit Diablo", &gamemenu_quit_game },
  { 0x80000000, NULL, NULL }
};
TMenuItem sgMultiMenu[5] =
{
  { 0x80000000, "Options", &gamemenu_options },
  { 0x80000000, "New Game", &gamemenu_new_game },
  { 0x80000000, "Restart In Town", &gamemenu_restart_town },
  { 0x80000000, "Quit Diablo", &gamemenu_quit_game },
  { 0x80000000, NULL, NULL }
};
TMenuItem sgOptionMenu[6] =
{
  { 0xC0000000, NULL, (void (__cdecl *)(void))&gamemenu_music_volume },
  { 0xC0000000, NULL, (void (__cdecl *)(void))&gamemenu_sound_volume },
  { 0xC0000000, "Gamma", (void (__cdecl *)(void))&gamemenu_gamma },
  { 0x80000000, NULL, &gamemenu_color_cycling },
  { 0x80000000, "Previous Menu", &gamemenu_previous },
  { 0x80000000, NULL, NULL }
};
char *music_toggle_names[] = { "Music", "Music Disabled" };
char *sound_toggle_names[] = { "Sound", "Sound Disabled" };
char *color_cycling_toggle_names[] = { "Color Cycling Off", "Color Cycling On" };

//----- (00418866) --------------------------------------------------------
void __cdecl gamemenu_previous()
{
	void (__cdecl *v0)(); // edx
	TMenuItem *v1; // ecx

	if ( gbMaxPlayers == 1 )
	{
		v0 = gamemenu_enable_single;
		v1 = sgSingleMenu;
	}
	else
	{
		v0 = gamemenu_enable_multi;
		v1 = sgMultiMenu;
	}
	gmenu_call_proc(v1, v0);
	PressEscKey();
}
// 679660: using guessed type char gbMaxPlayers;

//----- (0041888F) --------------------------------------------------------
void __cdecl gamemenu_enable_single()
{
	bool v0; // dl

	gmenu_enable(&sgSingleMenu[3], gbValidSaveFile);
	v0 = 0;
	if ( plr[myplr]._pmode != PM_DEATH && !deathflag )
		v0 = 1;
	gmenu_enable(sgSingleMenu, v0);
}

//----- (004188C8) --------------------------------------------------------
void __cdecl gamemenu_enable_multi()
{
	gmenu_enable(&sgMultiMenu[2], deathflag);
}

//----- (004188D8) --------------------------------------------------------
void __cdecl gamemenu_off()
{
	gmenu_call_proc(0, 0);
}

//----- (004188E1) --------------------------------------------------------
void __cdecl gamemenu_handle_previous()
{
	if ( gmenu_exception() )
		gamemenu_off();
	else
		gamemenu_previous();
}

//----- (004188F9) --------------------------------------------------------
void __cdecl gamemenu_new_game()
{
	int i; // eax

	for(i = 0; i < 4; i++)
	{
		plr[i]._pmode = PM_QUIT;
		plr[i]._pInvincible = 1;
	}

	deathflag = 0;
	drawpanflag = 255;
	scrollrt_draw_game_screen(1);
	gbRunGame = 0;
	gamemenu_off();
}
// 525650: using guessed type int gbRunGame;
// 52571C: using guessed type int drawpanflag;

//----- (0041893B) --------------------------------------------------------
void __cdecl gamemenu_quit_game()
{
	gamemenu_new_game();
	gbRunGameResult = 0;
}
// 525698: using guessed type int gbRunGameResult;

//----- (00418948) --------------------------------------------------------
void __cdecl gamemenu_load_game()
{
	LRESULT (__stdcall *saveProc)(HWND, UINT, WPARAM, LPARAM); // edi

	saveProc = SetWindowProc(DisableInputWndProc);
	gamemenu_off();
	SetCursor(0);
	InitDiabloMsg(10);
	drawpanflag = 255;
	DrawAndBlit();
	LoadGame(0);
	ClrDiabloMsg();
	PaletteFadeOut(8);
	deathflag = 0;
	drawpanflag = 255;
	DrawAndBlit();
	PaletteFadeIn(8);
	SetCursor(CURSOR_HAND);
	interface_msg_pump();
	SetWindowProc(saveProc);
}
// 52571C: using guessed type int drawpanflag;

//----- (004189BE) --------------------------------------------------------
void __cdecl gamemenu_save_game()
{
	LRESULT (__stdcall *saveProc)(HWND, UINT, WPARAM, LPARAM); // edi

	if ( pcurs == CURSOR_HAND )
	{
		if ( plr[myplr]._pmode == PM_DEATH || deathflag )
		{
			gamemenu_off();
		}
		else
		{
			saveProc = SetWindowProc(DisableInputWndProc);
			SetCursor(0);
			gamemenu_off();
			InitDiabloMsg(11);
			drawpanflag = 255;
			DrawAndBlit();
			SaveGame();
			ClrDiabloMsg();
			drawpanflag = 255;
			SetCursor(CURSOR_HAND);
			interface_msg_pump();
			SetWindowProc(saveProc);
		}
	}
}
// 52571C: using guessed type int drawpanflag;

//----- (00418A42) --------------------------------------------------------
void __cdecl gamemenu_restart_town()
{
	NetSendCmd(1u, CMD_RETOWN);
}

//----- (00418A4C) --------------------------------------------------------
void __cdecl gamemenu_options()
{
	gamemenu_get_music();
	gamemenu_get_sound();
	gamemenu_get_gamma();
	gamemenu_get_color_cycling();
	gmenu_call_proc(sgOptionMenu, 0);
}

//----- (00418A6C) --------------------------------------------------------
void __cdecl gamemenu_get_music()
{
	gamemenu_sound_music_toggle(music_toggle_names, sgOptionMenu, sound_get_or_set_music_volume(1));
}

//----- (00418A85) --------------------------------------------------------
void __fastcall gamemenu_sound_music_toggle(char **names, TMenuItem *menu_item, int gamma)
{
	if ( gbSndInited )
	{
		menu_item->dwFlags |= 0xC0000000;
		menu_item->pszStr = *names;
		gmenu_slider_3(menu_item, 17);
		gmenu_slider_1(menu_item, -1600, 0, gamma);
	}
	else
	{
		menu_item->dwFlags &= 0x3F000000;
		menu_item->pszStr = names[1];
	}
}

//----- (00418AC6) --------------------------------------------------------
void __cdecl gamemenu_get_sound()
{
	gamemenu_sound_music_toggle(sound_toggle_names, &sgOptionMenu[1], sound_get_or_set_sound_volume(1));
}

//----- (00418ADF) --------------------------------------------------------
void __cdecl gamemenu_get_color_cycling()
{
	sgOptionMenu[3].pszStr = color_cycling_toggle_names[palette_get_colour_cycling()];
}

//----- (00418AF4) --------------------------------------------------------
void __cdecl gamemenu_get_gamma()
{
	gmenu_slider_3(&sgOptionMenu[2], 15);
	gmenu_slider_1(&sgOptionMenu[2], 30, 100, palette_update_gamma(0));
}

//----- (00418B1A) --------------------------------------------------------
void __fastcall gamemenu_music_volume(int a1)
{
	int v1; // esi

	if ( a1 )
	{
		if ( gbMusicOn )
		{
			gbMusicOn = 0;
			music_stop();
			sound_get_or_set_music_volume(-1600);
			goto LABEL_11;
		}
		gbMusicOn = 1;
		sound_get_or_set_music_volume(0);
LABEL_10:
		music_start((unsigned char)leveltype);
		goto LABEL_11;
	}
	v1 = gamemenu_slider_music_sound(sgOptionMenu);
	sound_get_or_set_music_volume(v1);
	if ( v1 != -1600 )
	{
		if ( gbMusicOn )
			goto LABEL_11;
		gbMusicOn = 1;
		goto LABEL_10;
	}
	if ( gbMusicOn )
	{
		gbMusicOn = 0;
		music_stop();
	}
LABEL_11:
	gamemenu_get_music();
}
// 4A22D4: using guessed type char gbMusicOn;
// 5BB1ED: using guessed type char leveltype;

//----- (00418BA3) --------------------------------------------------------
int __fastcall gamemenu_slider_music_sound(TMenuItem *menu_item)
{
	return gmenu_slider_get(menu_item, -1600, 0);
}

//----- (00418BB0) --------------------------------------------------------
void __fastcall gamemenu_sound_volume(int a1)
{
	int v1; // ecx
	int v2; // esi

	if ( a1 )
	{
		if ( gbSoundOn )
		{
			gbSoundOn = 0;
			FreeMonsterSnd();
			v1 = -1600;
		}
		else
		{
			gbSoundOn = 1;
			v1 = 0;
		}
		sound_get_or_set_sound_volume(v1);
	}
	else
	{
		v2 = gamemenu_slider_music_sound(&sgOptionMenu[1]);
		sound_get_or_set_sound_volume(v2);
		if ( v2 == -1600 )
		{
			if ( gbSoundOn )
			{
				gbSoundOn = 0;
				FreeMonsterSnd();
			}
		}
		else if ( !gbSoundOn )
		{
			gbSoundOn = 1;
		}
	}
	PlaySFX(IS_TITLEMOV);
	gamemenu_get_sound();
}
// 4A22D5: using guessed type char gbSoundOn;

//----- (00418C30) --------------------------------------------------------
void __fastcall gamemenu_gamma(int a1)
{
	int v1; // eax
	int v2; // eax

	if ( a1 )
	{
		v1 = -(palette_update_gamma(0) != 30);
		_LOBYTE(v1) = v1 & 0xBA;
		v2 = v1 + 100;
	}
	else
	{
		v2 = gamemenu_slider_gamma();
	}
	palette_update_gamma(v2);
	gamemenu_get_gamma();
}

//----- (00418C5A) --------------------------------------------------------
int __cdecl gamemenu_slider_gamma()
{
	return gmenu_slider_get(&sgOptionMenu[2], 30, 100);
}

//----- (00418C6A) --------------------------------------------------------
void __cdecl gamemenu_color_cycling()
{
	palette_set_color_cycling(palette_get_colour_cycling() == 0);
	sgOptionMenu[3].pszStr = color_cycling_toggle_names[palette_get_colour_cycling() & 1];
}
