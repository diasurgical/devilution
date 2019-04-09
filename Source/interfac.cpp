//HEADER_GOES_HERE

#include "../types.h"

void *sgpBackCel;
int sgdwProgress;
int progress_id; // idb

const unsigned char progress_bar_colours[3] = { 138u, 43u, 254u };
const int progress_bar_screen_pos[3][2] = { { 53, 37 }, { 53, 421 }, { 53, 37 } };

void interface_msg_pump()
{
	MSG Msg; // [esp+8h] [ebp-1Ch]

	while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
		if (Msg.message != WM_QUIT) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
}

BOOL IncProgress()
{
	interface_msg_pump();
	sgdwProgress += 15;
	if ((unsigned int)sgdwProgress > 0x216)
		sgdwProgress = 534;
	if (sgpBackCel)
		DrawCutscene();
	return (unsigned int)sgdwProgress >= 0x216;
}

void DrawCutscene()
{
	DWORD i;

	j_lock_buf_priv(1);
	CelDecodeOnly(64, 639, (BYTE *)sgpBackCel, 1, 640);

	for (i = 0; i < sgdwProgress; i++) {
		DrawProgress(
		    progress_bar_screen_pos[progress_id][0] + i + 64,
		    progress_bar_screen_pos[progress_id][1] + 160,
		    progress_id);
	}

	j_unlock_buf_priv(1);
	drawpanflag = 255;
	scrollrt_draw_game_screen(0);
}
// 52571C: using guessed type int drawpanflag;

void DrawProgress(int screen_x, int screen_y, int progress_id)
{
	_BYTE *v3;     // eax
	signed int v4; // ecx

	v3 = (unsigned char *)gpBuffer + screen_y_times_768[screen_y] + screen_x;
	v4 = 22;
	do {
		*v3 = progress_bar_colours[progress_id];
		v3 += 768;
		--v4;
	} while (v4);
}

void ShowProgress(unsigned int uMsg)
{
	WNDPROC saveProc;

	gbSomebodyWonGameKludge = FALSE;
	plrmsg_delay(TRUE);

	/// ASSERT: assert(ghMainWnd);
	saveProc = SetWindowProc(DisableInputWndProc);

	interface_msg_pump();
	ClearScreenBuffer();
	scrollrt_draw_game_screen(TRUE);
	InitCutscene(uMsg);
	BlackPalette();
	DrawCutscene();
	PaletteFadeIn(8);
	IncProgress();
	stream_update();
	IncProgress();

	switch (uMsg) {
	case WM_DIABLOADGAME:
		IncProgress();
		LoadGame(TRUE);
		IncProgress();
		break;
	case WM_DIABNEWGAME:
		IncProgress();
		FreeGameMem();
		IncProgress();
		pfile_remove_temp_files();
		LoadGameLevel(TRUE, 0);
		IncProgress();
		break;
	case WM_DIABNEXTLVL:
		IncProgress();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		FreeGameMem();
		currlevel++;
		leveltype = gnLevelTypeTbl[currlevel];
		/// ASSERT: assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, 0);
		IncProgress();
		break;
	case WM_DIABPREVLVL:
		IncProgress();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		IncProgress();
		FreeGameMem();
		currlevel--;
		leveltype = gnLevelTypeTbl[currlevel];
		/// ASSERT: assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, 1);
		IncProgress();
		break;
	case WM_DIABSETLVL:
		SetReturnLvlPos();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		setlevel = TRUE;
		leveltype = setlvltype;
		FreeGameMem();
		IncProgress();
		LoadGameLevel(FALSE, 2);
		IncProgress();
		break;
	case WM_DIABRTNLVL:
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		setlevel = FALSE;
		FreeGameMem();
		IncProgress();
		GetReturnLvlPos();
		LoadGameLevel(FALSE, 3);
		IncProgress();
		break;
	case WM_DIABWARPLVL:
		IncProgress();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		FreeGameMem();
		GetPortalLevel();
		IncProgress();
		LoadGameLevel(FALSE, 5);
		IncProgress();
		break;
	case WM_DIABTOWNWARP:
		IncProgress();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		FreeGameMem();
		currlevel = plr[myplr].plrlevel;
		leveltype = gnLevelTypeTbl[currlevel];
		/// ASSERT: assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, 6);
		IncProgress();
		break;
	case WM_DIABTWARPUP:
		IncProgress();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		FreeGameMem();
		currlevel = plr[myplr].plrlevel;
		leveltype = gnLevelTypeTbl[currlevel];
		/// ASSERT: assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, 7);
		IncProgress();
		break;
	case WM_DIABRETOWN:
		IncProgress();
		if (gbMaxPlayers == 1) {
			SaveLevel();
		} else {
			DeltaSaveLevel();
		}
		FreeGameMem();
		currlevel = plr[myplr].plrlevel;
		leveltype = gnLevelTypeTbl[currlevel];
		/// ASSERT: assert(plr[myplr].plrlevel == currlevel);
		IncProgress();
		LoadGameLevel(FALSE, 0);
		IncProgress();
		break;
	}

	/// ASSERT: assert(ghMainWnd);

	PaletteFadeOut(8);
	FreeInterface();

	saveProc = SetWindowProc(saveProc);
	/// ASSERT: assert(saveProc == DisableInputWndProc);

	NetSendCmdLocParam1(TRUE, CMD_PLAYER_JOINLEVEL, plr[myplr].WorldX, plr[myplr].WorldY, plr[myplr].plrlevel);
	plrmsg_delay(FALSE);
	ResetPal();

	if (gbSomebodyWonGameKludge && plr[myplr].plrlevel == 16) {
		PrepDoEnding();
	}

	gbSomebodyWonGameKludge = FALSE;
}
// 5CF31C: using guessed type char setlvltype;
// 5CF31D: using guessed type char setlevel;
// 6761B8: using guessed type char gbSomebodyWonGameKludge;
// 679660: using guessed type char gbMaxPlayers;

void FreeInterface()
{
	void *ptr;

	ptr = sgpBackCel;
	sgpBackCel = NULL;
	mem_free_dbg(ptr);
}

void InitCutscene(unsigned int uMsg)
{
	/// ASSERT: assert(! sgpBackCel);

	switch(uMsg) {
	case WM_DIABNEXTLVL:
		switch(gnLevelTypeTbl[currlevel]) {
		case 0:
			sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", 0);
			LoadPalette("Gendata\\Cuttt.pal");
			progress_id = 1;
			break;
		case 1:
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", 0);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
			break;
		case 2:
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", 0);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
			break;
		case 3:
			sgpBackCel = LoadFileInMem("Gendata\\Cut3.CEL", 0);
			LoadPalette("Gendata\\Cut3.pal");
			progress_id = 1;
			break;
		case 4:
			if(currlevel < 15) {
				sgpBackCel = LoadFileInMem("Gendata\\Cut4.CEL", 0);
				LoadPalette("Gendata\\Cut4.pal");
				progress_id = 1;
			} else {
				sgpBackCel = LoadFileInMem("Gendata\\Cutgate.CEL", 0);
				LoadPalette("Gendata\\Cutgate.pal");
				progress_id = 1;
			}
			break;
		default:
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", 0);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
			break;
		}
		break;
	case WM_DIABPREVLVL:
		if(gnLevelTypeTbl[currlevel - 1] == 0) {
			sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", 0);
			LoadPalette("Gendata\\Cuttt.pal");
			progress_id = 1;
		} else {
			switch(gnLevelTypeTbl[currlevel]) {
			case 0:
				sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", 0);
				LoadPalette("Gendata\\Cuttt.pal");
				progress_id = 1;
				break;
			case 1:
				sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", 0);
				LoadPalette("Gendata\\Cutl1d.pal");
				progress_id = 0;
				break;
			case 2:
				sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", 0);
				LoadPalette("Gendata\\Cut2.pal");
				progress_id = 2;
				break;
			case 3:
				sgpBackCel = LoadFileInMem("Gendata\\Cut3.CEL", 0);
				LoadPalette("Gendata\\Cut3.pal");
				progress_id = 1;
				break;
			case 4:
				sgpBackCel = LoadFileInMem("Gendata\\Cut4.CEL", 0);
				LoadPalette("Gendata\\Cut4.pal");
				progress_id = 1;
				break;
			default:
				sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", 0);
				LoadPalette("Gendata\\Cutl1d.pal");
				progress_id = 0;
				break;
			}
		}
		break;
	case WM_DIABSETLVL:
		if(setlvlnum == SL_BONECHAMB) {
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", 0);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
		} else if(setlvlnum == SL_VILEBETRAYER) {
			sgpBackCel = LoadFileInMem("Gendata\\Cutportr.CEL", 0);
			LoadPalette("Gendata\\Cutportr.pal");
			progress_id = 1;
		} else {
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", 0);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
		}
		break;
	case WM_DIABRTNLVL:
		if(setlvlnum == SL_BONECHAMB) {
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", 0);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
		} else if(setlvlnum == SL_VILEBETRAYER) {
			sgpBackCel = LoadFileInMem("Gendata\\Cutportr.CEL", 0);
			LoadPalette("Gendata\\Cutportr.pal");
			progress_id = 1;
		} else {
			sgpBackCel = LoadFileInMem("Gendata\\Cutl1d.CEL", 0);
			LoadPalette("Gendata\\Cutl1d.pal");
			progress_id = 0;
		}
		break;
	case WM_DIABWARPLVL:
		sgpBackCel = LoadFileInMem("Gendata\\Cutportl.CEL", 0);
		LoadPalette("Gendata\\Cutportl.pal");
		progress_id = 1;
		break;
	case WM_DIABLOADGAME:
		sgpBackCel = LoadFileInMem("Gendata\\Cutstart.CEL", 0);
		LoadPalette("Gendata\\Cutstart.pal");
		progress_id = 1;
		break;
	case WM_DIABNEWGAME:
		sgpBackCel = LoadFileInMem("Gendata\\Cutstart.CEL", 0);
		LoadPalette("Gendata\\Cutstart.pal");
		progress_id = 1;
		break;
	case WM_DIABTOWNWARP:
	case WM_DIABTWARPUP:
		switch(gnLevelTypeTbl[plr[myplr].plrlevel]) {
		case 0:
			sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", 0);
			LoadPalette("Gendata\\Cuttt.pal");
			progress_id = 1;
			break;
		case 2:
			sgpBackCel = LoadFileInMem("Gendata\\Cut2.CEL", 0);
			LoadPalette("Gendata\\Cut2.pal");
			progress_id = 2;
			break;
		case 3:
			sgpBackCel = LoadFileInMem("Gendata\\Cut3.CEL", 0);
			LoadPalette("Gendata\\Cut3.pal");
			progress_id = 1;
			break;
		case 4:
			sgpBackCel = LoadFileInMem("Gendata\\Cut4.CEL", 0);
			LoadPalette("Gendata\\Cut4.pal");
			progress_id = 1;
			break;
		}
		break;
	case WM_DIABRETOWN:
		sgpBackCel = LoadFileInMem("Gendata\\Cuttt.CEL", 0);
		LoadPalette("Gendata\\Cuttt.pal");
		progress_id = 1;
		break;
	default:
		app_fatal("Unknown progress mode");
		break;
	}

	sgdwProgress = 0;
}
