#include "diablo.h"
#include "../3rdParty/Storm/Source/storm.h"
#include "../DiabloUI/diabloui.h"

HWND ghMainWnd;
int glMid1Seed[NUMLEVELS];
int glMid2Seed[NUMLEVELS];
int gnLevelTypeTbl[NUMLEVELS];
int MouseY;
int MouseX;
BOOL gbGameLoopStartup;
DWORD glSeedTbl[NUMLEVELS];
BOOL gbRunGame;
int glMid3Seed[NUMLEVELS];
BOOL gbRunGameResult;
int zoomflag;
BOOL gbProcessPlayers;
int glEndSeed[NUMLEVELS];
BOOL gbLoadGame;
HINSTANCE ghInst;
int DebugMonsters[10];
BOOLEAN cineflag;
int drawpanflag;
BOOL visiondebug;
BOOL scrollflag; /* unused */
BOOL light4flag;
BOOL leveldebug;
BOOL monstdebug;
BOOL trigdebug; /* unused */
int setseed;
int debugmonsttypes;
int PauseMode;
#ifdef HELLFIRE
BOOLEAN UseTheoQuest;
BOOLEAN UseCowFarmer;
BOOLEAN UseNestArt;
BOOLEAN UseBardTest;
BOOLEAN UseBarbarianTest;
BOOLEAN UseMultiTest;
#endif
int sgnTimeoutCurs;
char sgbMouseDown;
int color_cycle_timer;

/* rdata */

BOOL fullscreen = TRUE;
#ifdef _DEBUG
int showintrodebug = 1;
int questdebug = -1;
int debug_mode_key_s;
int debug_mode_key_w;
int debug_mode_key_inverted_v;
int debug_mode_dollar_sign;
int debug_mode_key_d;
int debug_mode_key_i;
int dbgplr;
int dbgqst;
int dbgmon;
int arrowdebug;
int frameflag;
int frameend;
int framerate;
int framestart;
#endif
BOOL FriendlyMode = TRUE;
char *spszMsgTbl[4] = {
	"I need help! Come Here!",
	"Follow me.",
	"Here's something for you.",
	"Now you DIE!"
};
char *spszMsgHotKeyTbl[4] = { "F9", "F10", "F11", "F12" };

void FreeGameMem()
{
	music_stop();

	MemFreeDbg(pDungeonCels);
	MemFreeDbg(pMegaTiles);
	MemFreeDbg(pLevelPieces);
	MemFreeDbg(pSpecialCels);
	MemFreeDbg(pSpeedCels);

	FreeMissiles();
	FreeMonsters();
	FreeObjectGFX();
	FreeEffects();
	FreeTownerGFX();
}

BOOL StartGame(BOOL bNewGame, BOOL bSinglePlayer)
{
	BOOL fExitProgram;
	unsigned int uMsg;

	gbGameUninitialized = TRUE;

	do {
		fExitProgram = FALSE;
		gbLoadGame = FALSE;

		if (!NetInit(bSinglePlayer, &fExitProgram)) {
			gbRunGameResult = !fExitProgram;
			break;
		}

		gbGameUninitialized = FALSE;

		if (bNewGame || !gbValidSaveFile) {
			InitLevels();
			InitQuests();
			InitPortals();
			InitDungMsgs(myplr);
		}
		if (!gbValidSaveFile || !gbLoadGame)
			uMsg = WM_DIABNEWGAME;
		else
			uMsg = WM_DIABLOADGAME;

		run_game_loop(uMsg);
		NetClose();
		pfile_create_player_description(0, 0);
	} while (gbRunGameResult);

	SNetDestroy();
	return gbRunGameResult;
}

void run_game_loop(unsigned int uMsg)
{
	BOOL bLoop;
	WNDPROC saveProc;
	MSG msg;

	nthread_ignore_mutex(TRUE);
	start_game(uMsg);
	/// ASSERT: assert(ghMainWnd);
	saveProc = SetWindowProc(GM_Game);
	control_update_life_mana();
	msg_process_net_packets();
	gbRunGame = TRUE;
	gbProcessPlayers = TRUE;
	gbRunGameResult = TRUE;
	drawpanflag = 255;
	DrawAndBlit();
	PaletteFadeIn(8);
	drawpanflag = 255;
	gbGameLoopStartup = TRUE;
	nthread_ignore_mutex(FALSE);

	while (gbRunGame) {
		diablo_color_cyc_logic();
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					gbRunGameResult = FALSE;
					gbRunGame = FALSE;
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			bLoop = gbRunGame && nthread_has_500ms_passed(FALSE);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
			if (!bLoop) {
				continue;
			}
		} else if (!nthread_has_500ms_passed(FALSE)) {
#ifdef SLEEPFIX
			Sleep(1);
#endif
			continue;
		}
		multi_process_network_packets();
		game_loop(gbGameLoopStartup);
#ifndef HELLFIRE
		msgcmd_send_chat();
#endif
		gbGameLoopStartup = FALSE;
		DrawAndBlit();
	}

	if (gbMaxPlayers > 1) {
		pfile_write_hero();
	}

	pfile_flush_W();
	PaletteFadeOut(8);
	SetCursor_(0);
	ClearScreenBuffer();
	drawpanflag = 255;
	scrollrt_draw_game_screen(TRUE);
	saveProc = SetWindowProc(saveProc);
	/// ASSERT: assert(saveProc == GM_Game);
	free_game();

	if (cineflag) {
		cineflag = FALSE;
		DoEnding();
	}
}

void start_game(unsigned int uMsg)
{
	zoomflag = 1;
	cineflag = FALSE;
	InitCursor();
	InitLightTable();
	LoadDebugGFX();
	/// ASSERT: assert(ghMainWnd);
	music_stop();
	ShowProgress(uMsg);
	gmenu_init_menu();
	InitLevelCursor();
	sgnTimeoutCurs = 0;
	sgbMouseDown = 0;
	track_repeat_walk(0);
}

void free_game()
{
	int i; // esi

	FreeControlPan();
	FreeInvGFX();
	FreeGMenu();
	FreeQuestText();
	FreeStoreMem();

	for (i = 0; i < MAX_PLRS; i++)
		FreePlayerGFX(i);

	FreeItemGFX();
	FreeCursor();
	FreeLightTable();
	FreeDebugGFX();
	FreeGameMem();
}

BOOL diablo_get_not_running()
{
	SetLastError(0);
	CreateEvent(NULL, FALSE, FALSE, "DiabloEvent");
#ifdef HELLFIRE
	CreateEvent(NULL, FALSE, FALSE, "HellfireEvent");
#endif
	return GetLastError() != ERROR_ALREADY_EXISTS;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;
	int nData;
	char szFileName[MAX_PATH];
	BOOL bNoEvent;

	hInst = hInstance;
#ifndef DEBUGGER
	diablo_reload_process(hInstance);
#endif
	ghInst = hInst;

	if (RestrictedTest())
		ErrOkDlg(IDD_DIALOG10, 0, "C:\\Src\\Diablo\\Source\\DIABLO.CPP", 877);
	if (ReadOnlyTest()) {
		if (!GetModuleFileName(ghInst, szFileName, sizeof(szFileName)))
			szFileName[0] = '\0';
		DirErrorDlg(szFileName);
	}

	ShowCursor(FALSE);
	srand(GetTickCount());
	InitHash();
#ifdef HELLFIRE
	alloc_plr();
#endif
	fault_get_filter();

	bNoEvent = diablo_get_not_running();
	if (!diablo_find_window("DIABLO") && bNoEvent) {
#ifdef _DEBUG
		SFileEnableDirectAccess(TRUE);
#endif
		diablo_init_screen();
		diablo_parse_flags(lpCmdLine);
		init_create_window(nCmdShow);
		sound_init();
		UiInitialize();
#ifdef SPAWN
		UiSetSpawned(TRUE);
#endif

#ifdef _DEBUG
		if (showintrodebug)
#endif
			play_movie("gendata\\logo.smk", TRUE);

#ifndef SPAWN
		{
			char szValueName[] = "Intro";
			if (!SRegLoadValue("Diablo", szValueName, 0, &nData))
				nData = 1;
			if (nData)
				play_movie("gendata\\diablo1.smk", TRUE);
			SRegSaveValue("Diablo", szValueName, 0, 0);
		}
#endif

#ifdef _DEBUG
		if (showintrodebug) {
#endif
			UiTitleDialog(7);
			BlackPalette();
#ifdef _DEBUG
		}
#endif

		mainmenu_loop();
		UiDestroy();
		SaveGamma();

		if (ghMainWnd) {
			Sleep(300);
			DestroyWindow(ghMainWnd);
		}
	}

	return FALSE;
}

void diablo_parse_flags(char *args)
{
	char c;
#ifdef _DEBUG
	int i;
#endif

	while (*args != '\0') {
		while (isspace(*args)) {
			args++;
		}
		if (_strnicmp("dd_emulate", args, strlen("dd_emulate")) == 0) {
			gbEmulate = 1;
			args += strlen("dd_emulate");
		} else if (_strnicmp("dd_backbuf", args, strlen("dd_backbuf")) == 0) {
			gbBackBuf = 1;
			args += strlen("dd_backbuf");
		} else if (_strnicmp("ds_noduplicates", args, strlen("ds_noduplicates")) == 0) {
			gbDupSounds = FALSE;
			args += strlen("ds_noduplicates");
		} else {
			c = tolower(*args);
			args++;
#ifdef _DEBUG
			switch (c) {
			case '^':
				debug_mode_key_inverted_v = 1;
				break;
			case '$':
				debug_mode_dollar_sign = 1;
				break;
			case 'b':
				/*
				debug_mode_key_b = 1;
			*/
				break;
			case 'd':
				showintrodebug = 0;
				debug_mode_key_d = 1;
				break;
			case 'f':
				EnableFrameCount();
				break;
			case 'i':
				debug_mode_key_i = 1;
				break;
			case 'j':
				/*
				while(isspace(*args)) {
					args++;
				}
				i = 0;
				while(isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				debug_mode_key_J_trigger = i;
			*/
				break;
			case 'l':
				setlevel = FALSE;
				leveldebug = TRUE;
				while (isspace(*args)) {
					args++;
				}
				i = 0;
				while (isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				leveltype = i;
				while (isspace(*args)) {
					args++;
				}
				i = 0;
				while (isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				currlevel = i;
				plr[0].plrlevel = i;
				break;
			case 'm':
				monstdebug = TRUE;
				while (isspace(*args)) {
					args++;
				}
				i = 0;
				while (isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				DebugMonsters[debugmonsttypes++] = i;
				break;
			case 'n':
				showintrodebug = 0;
				break;
			case 'q':
				while (isspace(*args)) {
					args++;
				}
				i = 0;
				while (isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				questdebug = i;
				break;
			case 'r':
				while (isspace(*args)) {
					args++;
				}
				i = 0;
				while (isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				setseed = i;
				break;
			case 's':
				debug_mode_key_s = 1;
				break;
			case 't':
				leveldebug = TRUE;
				setlevel = TRUE;
				while (isspace(*args)) {
					args++;
				}
				i = 0;
				while (isdigit(*args)) {
					i = *args + 10 * i - '0';
					args++;
				}
				setlvlnum = i;
				break;
			case 'v':
				visiondebug = TRUE;
				break;
			case 'w':
				debug_mode_key_w = 1;
				break;
			case 'x':
				fullscreen = 0;
				break;
			}
#endif
		}
	}
}

void diablo_init_screen()
{
	int i;

	MouseX = SCREEN_WIDTH / 2;
	MouseY = SCREEN_HEIGHT / 2;
	ScrollInfo._sdx = 0;
	ScrollInfo._sdy = 0;
	ScrollInfo._sxoff = 0;
	ScrollInfo._syoff = 0;
	ScrollInfo._sdir = SDIR_NONE;

	for (i = 0; i < 1024; i++)
		PitchTbl[i] = i * BUFFER_WIDTH;

	ClrDiabloMsg();
}

BOOL diablo_find_window(LPCSTR lpClassName)
{
	HWND hWnd, active;

	hWnd = FindWindow(lpClassName, 0);
	if (!hWnd)
		return FALSE;

	active = GetLastActivePopup(hWnd);
	if (active)
		hWnd = active;

	active = GetTopWindow(hWnd);
	if (!active)
		active = hWnd;

	SetForegroundWindow(hWnd);
	SetFocus(active);

	return TRUE;
}

void diablo_reload_process(HINSTANCE hInstance)
{
	DWORD dwSize, dwProcessId;
	BOOL bNoExist;
	char *s;
	long *plMap;
	HWND hWnd, hPrev;
	HANDLE hMap;
	STARTUPINFO si;
	SYSTEM_INFO sinf;
	PROCESS_INFORMATION pi;
	char szReload[MAX_PATH + 16];
	char szFileName[MAX_PATH] = "";

	GetModuleFileName(hInstance, szFileName, sizeof(szFileName));
	wsprintf(szReload, "Reload-%s", szFileName);
	for (s = szReload; *s != '\0'; s++) {
		if (*s == '\\') {
			*s = '/';
		}
	}

	GetSystemInfo(&sinf);
	dwSize = sinf.dwPageSize;
	if (dwSize < 4096) {
		dwSize = 4096;
	}

	hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, SEC_COMMIT | PAGE_READWRITE, 0, dwSize, szReload);
	bNoExist = GetLastError() != ERROR_ALREADY_EXISTS;
	if (hMap == NULL) {
		return;
	}
	plMap = (long *)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, dwSize);
	if (plMap == NULL) {
		return;
	}

	if (bNoExist) {
		plMap[0] = -1;
		plMap[1] = 0;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		CreateProcess(szFileName, NULL, NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi);
		WaitForInputIdle(pi.hProcess, INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		while (plMap[0] < 0) {
			Sleep(1000);
		}
		UnmapViewOfFile(plMap);
		CloseHandle(hMap);
		ExitProcess(0);
	}

	if (InterlockedIncrement(plMap) == 0) {
		plMap[1] = GetCurrentProcessId();
	} else {
		hPrev = GetForegroundWindow();
		hWnd = hPrev;
		while (1) {
			hPrev = GetWindow(hPrev, GW_HWNDPREV);
			if (hPrev == NULL) {
				break;
			}
			hWnd = hPrev;
		}
		while (1) {
			GetWindowThreadProcessId(hWnd, &dwProcessId);
			if (dwProcessId == plMap[1]) {
				SetForegroundWindow(hWnd);
				break;
			}
			hWnd = GetWindow(hWnd, GW_HWNDNEXT);
			if (hWnd == NULL) {
				break;
			}
		}
		UnmapViewOfFile(plMap);
		CloseHandle(hMap);
		ExitProcess(0);
	}
}

BOOL PressEscKey()
{
	BOOL rv = FALSE;

	if (doomflag) {
		doom_close();
		rv = TRUE;
	}
	if (helpflag) {
		helpflag = 0;
		rv = TRUE;
	}

	if (qtextflag) {
		qtextflag = 0;
		sfx_stop();
		rv = TRUE;
	} else if (stextflag) {
		STextESC();
		rv = TRUE;
	}

	if (msgflag) {
		msgdelay = 0;
		rv = TRUE;
	}
	if (talkflag) {
		control_reset_talk();
		rv = TRUE;
	}
	if (dropGoldFlag) {
		control_drop_gold(VK_ESCAPE);
		rv = TRUE;
	}
	if (spselflag) {
		spselflag = 0;
		rv = TRUE;
	}

	return rv;
}

LRESULT CALLBACK DisableInputWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSCOMMAND:
	case WM_MOUSEMOVE:
		return 0;
	case WM_LBUTTONDOWN:
		if (sgbMouseDown == 0) {
			sgbMouseDown = 1;
			SetCapture(hWnd);
		}
		return 0;
	case WM_LBUTTONUP:
		if (sgbMouseDown == 1) {
			sgbMouseDown = 0;
			ReleaseCapture();
		}
		return 0;
	case WM_RBUTTONDOWN:
		if (sgbMouseDown == 0) {
			sgbMouseDown = 2;
			SetCapture(hWnd);
		}
		return 0;
	case WM_RBUTTONUP:
		if (sgbMouseDown == 2) {
			sgbMouseDown = 0;
			ReleaseCapture();
		}
		return 0;
	case WM_CAPTURECHANGED:
		if (hWnd != (HWND)lParam)
			sgbMouseDown = 0;
		return 0;
	}

	return MainWndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK GM_Game(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		PressKey(wParam);
		return 0;
	case WM_KEYUP:
		ReleaseKey(wParam);
		return 0;
	case WM_CHAR:
		PressChar(wParam);
		return 0;
	case WM_SYSKEYDOWN:
		if (PressSysKey(wParam))
			return 0;
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			gbRunGame = FALSE;
			gbRunGameResult = FALSE;
			return 0;
		}
		break;
	case WM_MOUSEMOVE:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		gmenu_on_mouse_move();
		return 0;
	case WM_LBUTTONDOWN:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		if (sgbMouseDown == 0) {
			sgbMouseDown = 1;
			SetCapture(hWnd);
			track_repeat_walk(LeftMouseDown(wParam));
		}
		return 0;
	case WM_LBUTTONUP:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		if (sgbMouseDown == 1) {
			sgbMouseDown = 0;
			LeftMouseUp();
			track_repeat_walk(FALSE);
			ReleaseCapture();
		}
		return 0;
	case WM_RBUTTONDOWN:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		if (sgbMouseDown == 0) {
			sgbMouseDown = 2;
			SetCapture(hWnd);
			RightMouseDown();
		}
		return 0;
	case WM_RBUTTONUP:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		if (sgbMouseDown == 2) {
			sgbMouseDown = 0;
			ReleaseCapture();
		}
		return 0;
	case WM_CAPTURECHANGED:
		if (hWnd != (HWND)lParam) {
			sgbMouseDown = 0;
			track_repeat_walk(FALSE);
		}
		break;
	case WM_DIABNEXTLVL:
	case WM_DIABPREVLVL:
	case WM_DIABRTNLVL:
	case WM_DIABSETLVL:
	case WM_DIABWARPLVL:
	case WM_DIABTOWNWARP:
	case WM_DIABTWARPUP:
	case WM_DIABRETOWN:
		if (gbMaxPlayers > 1)
			pfile_write_hero();
		nthread_ignore_mutex(TRUE);
		PaletteFadeOut(8);
		FreeMonsterSnd();
		music_stop();
		track_repeat_walk(FALSE);
		sgbMouseDown = 0;
		ReleaseCapture();
		ShowProgress(uMsg);
		drawpanflag = 255;
		DrawAndBlit();
		if (gbRunGame)
			PaletteFadeIn(8);
		nthread_ignore_mutex(FALSE);
		gbGameLoopStartup = TRUE;
		return 0;
	}

	return MainWndProc(hWnd, uMsg, wParam, lParam);
}

BOOL LeftMouseDown(int wParam)
{
	if (!gmenu_left_mouse(TRUE) && !control_check_talk_btn() && !sgnTimeoutCurs) {
		if (deathflag) {
			control_check_btn_press();
		} else if (PauseMode != 2) {
			if (doomflag) {
				doom_close();
			} else if (spselflag) {
				SetSpell();
			} else if (stextflag) {
				CheckStoreBtn();
			} else if (MouseY < PANEL_TOP) {
				if (!gmenu_exception() && !TryIconCurs()) {
					if (questlog && MouseX > 32 && MouseX < 288 && MouseY > 32 && MouseY < 308) {
						QuestlogESC();
					} else if (qtextflag) {
						qtextflag = FALSE;
						sfx_stop();
					} else if (chrflag && MouseX < 320) {
						CheckChrBtns();
					} else if (invflag && MouseX > 320) {
						if (!dropGoldFlag)
							CheckInvItem();
					} else if (sbookflag && MouseX > 320) {
						CheckSBook();
					} else if (pcurs >= CURSOR_FIRSTITEM) {
						if (TryInvPut()) {
							NetSendCmdPItem(TRUE, CMD_PUTITEM, cursmx, cursmy);
							SetCursor_(CURSOR_HAND);
						}
					} else {
						if (plr[myplr]._pStatPts && !spselflag)
							CheckLvlBtn();
						if (!lvlbtndown)
							return LeftMouseCmd(wParam == MK_SHIFT + MK_LBUTTON);
					}
				}
			} else {
				if (!talkflag && !dropGoldFlag && !gmenu_exception())
					CheckInvScrn();
				DoPanBtn();
				if (pcurs > CURSOR_HAND && pcurs < CURSOR_FIRSTITEM)
					SetCursor_(CURSOR_HAND);
			}
		}
	}

	return FALSE;
}

BOOL LeftMouseCmd(BOOL bShift)
{
	BOOL bNear;

	/// ASSERT: assert(MouseY < 352); // PANEL_TOP

	if (leveltype == DTYPE_TOWN) {
		if (pcursitem != -1 && pcurs == CURSOR_HAND)
			NetSendCmdLocParam1(TRUE, invflag ? CMD_GOTOGETITEM : CMD_GOTOAGETITEM, cursmx, cursmy, pcursitem);
		if (pcursmonst != -1)
			NetSendCmdLocParam1(TRUE, CMD_TALKXY, cursmx, cursmy, pcursmonst);
		if (pcursitem == -1 && pcursmonst == -1 && pcursplr == -1)
			return TRUE;
	} else {
		bNear = abs(plr[myplr].WorldX - cursmx) < 2 && abs(plr[myplr].WorldY - cursmy) < 2;
		if (pcursitem != -1 && pcurs == CURSOR_HAND && !bShift) {
			NetSendCmdLocParam1(pcurs, invflag ? CMD_GOTOGETITEM : CMD_GOTOAGETITEM, cursmx, cursmy, pcursitem);
		} else if (pcursobj != -1 && (!bShift || bNear && object[pcursobj]._oBreak == 1)) {
			NetSendCmdLocParam1(TRUE, pcurs == CURSOR_DISARM ? CMD_DISARMXY : CMD_OPOBJXY, cursmx, cursmy, pcursobj);
		} else if (plr[myplr]._pwtype == WT_RANGED) {
			if (bShift) {
				NetSendCmdLoc(TRUE, CMD_RATTACKXY, cursmx, cursmy);
			} else if (pcursmonst != -1) {
				if (CanTalkToMonst(pcursmonst)) {
					NetSendCmdParam1(TRUE, CMD_ATTACKID, pcursmonst);
				} else {
					NetSendCmdParam1(TRUE, CMD_RATTACKID, pcursmonst);
				}
			} else if (pcursplr != -1 && !FriendlyMode) {
				NetSendCmdParam1(TRUE, CMD_RATTACKPID, pcursplr);
			}
		} else {
			if (bShift) {
				if (pcursmonst != -1) {
					if (CanTalkToMonst(pcursmonst)) {
						NetSendCmdParam1(TRUE, CMD_ATTACKID, pcursmonst);
					} else {
						NetSendCmdLoc(TRUE, CMD_SATTACKXY, cursmx, cursmy);
					}
				} else {
					NetSendCmdLoc(TRUE, CMD_SATTACKXY, cursmx, cursmy);
				}
			} else if (pcursmonst != -1) {
				NetSendCmdParam1(TRUE, CMD_ATTACKID, pcursmonst);
			} else if (pcursplr != -1 && !FriendlyMode) {
				NetSendCmdParam1(TRUE, CMD_ATTACKPID, pcursplr);
			}
		}
		if (!bShift && pcursitem == -1 && pcursobj == -1 && pcursmonst == -1 && pcursplr == -1)
			return TRUE;
	}

	return FALSE;
}

BOOL TryIconCurs()
{
	if (pcurs == CURSOR_RESURRECT) {
		NetSendCmdParam1(TRUE, CMD_RESURRECT, pcursplr);
		return TRUE;
	} else if (pcurs == CURSOR_HEALOTHER) {
		NetSendCmdParam1(TRUE, CMD_HEALOTHER, pcursplr);
		return TRUE;
	} else if (pcurs == CURSOR_TELEKINESIS) {
		DoTelekinesis();
		return TRUE;
	} else if (pcurs == CURSOR_IDENTIFY) {
		if (pcursinvitem != -1) {
			CheckIdentify(myplr, pcursinvitem);
		} else {
			SetCursor_(CURSOR_HAND);
		}
		return TRUE;
	} else if (pcurs == CURSOR_REPAIR) {
		if (pcursinvitem != -1) {
			DoRepair(myplr, pcursinvitem);
		} else {
			SetCursor_(CURSOR_HAND);
		}
		return TRUE;
	} else if (pcurs == CURSOR_RECHARGE) {
		if (pcursinvitem != -1) {
			DoRecharge(myplr, pcursinvitem);
		} else {
			SetCursor_(CURSOR_HAND);
		}
		return TRUE;
	} else if (pcurs == CURSOR_TELEPORT) {
		if (pcursmonst != -1) {
			NetSendCmdParam3(TRUE, CMD_TSPELLID, pcursmonst, plr[myplr]._pTSpell, GetSpellLevel(myplr, plr[myplr]._pTSpell));
		} else if (pcursplr != -1) {
			NetSendCmdParam3(TRUE, CMD_TSPELLPID, pcursplr, plr[myplr]._pTSpell, GetSpellLevel(myplr, plr[myplr]._pTSpell));
		} else {
			NetSendCmdLocParam2(TRUE, CMD_TSPELLXY, cursmx, cursmy, plr[myplr]._pTSpell, GetSpellLevel(myplr, plr[myplr]._pTSpell));
		}
		SetCursor_(CURSOR_HAND);
		return TRUE;
	} else if (pcurs == CURSOR_DISARM && pcursobj == -1) {
		SetCursor_(CURSOR_HAND);
		return TRUE;
	}

	return FALSE;
}

void LeftMouseUp()
{
	gmenu_left_mouse(FALSE);
	control_release_talk_btn();
	if (panbtndown)
		CheckBtnUp();
	if (chrbtnactive)
		ReleaseChrBtns();
	if (lvlbtndown)
		ReleaseLvlBtn();
	if (stextflag)
		ReleaseStoreBtn();
}

void RightMouseDown()
{
	if (!gmenu_exception() && sgnTimeoutCurs == CURSOR_NONE && PauseMode != 2 && !plr[myplr]._pInvincible) {
		if (doomflag) {
			doom_close();
		} else if (!stextflag) {
			if (spselflag) {
				SetSpell();
			} else if (MouseY >= PANEL_TOP
			    || (!sbookflag || MouseX <= 320)
			        && !TryIconCurs()
			        && (pcursinvitem == -1 || !UseInvItem(myplr, pcursinvitem))) {
				if (pcurs == 1) {
					if (pcursinvitem == -1 || !UseInvItem(myplr, pcursinvitem))
						CheckPlrSpell();
				} else if (pcurs > 1 && pcurs < 12) {
					SetCursor_(CURSOR_HAND);
				}
			}
		}
	}
}

BOOL PressSysKey(int wParam)
{
	if (gmenu_exception() || wParam != VK_F10)
		return FALSE;
	diablo_hotkey_msg(1);
	return TRUE;
}

void diablo_hotkey_msg(DWORD dwMsg)
{
	char *s;
	char szFileName[MAX_PATH];
	char szMsg[MAX_SEND_STR_LEN];

	if (gbMaxPlayers == 1) {
		return;
	}
	if (GetModuleFileName(ghInst, szFileName, sizeof(szFileName)) == 0) {
		app_fatal("Can't get program name");
	}

	s = strrchr(szFileName, '\\');
	if (s != NULL) {
		*s = '\0';
	}

	strcat(szFileName, "\\Diablo.ini");
	/// ASSERT: assert(dwMsg < sizeof(spszMsgTbl) / sizeof(spszMsgTbl[0]));
	GetPrivateProfileString("NetMsg", spszMsgHotKeyTbl[dwMsg], spszMsgTbl[dwMsg], szMsg, sizeof(szMsg), szFileName);
	NetSendCmdString(-1, szMsg);
}

void ReleaseKey(int vkey)
{
	if (vkey == VK_SNAPSHOT)
		CaptureScreen();
}

void PressKey(int vkey)
{
	if (gmenu_presskeys(vkey) || control_presskeys(vkey)) {
		return;
	}

	if (deathflag) {
		if (sgnTimeoutCurs != 0) {
			return;
		}
		if (vkey == VK_F9) {
			diablo_hotkey_msg(0);
		}
		if (vkey == VK_F10) {
			diablo_hotkey_msg(1);
		}
		if (vkey == VK_F11) {
			diablo_hotkey_msg(2);
		}
		if (vkey == VK_F12) {
			diablo_hotkey_msg(3);
		}
		if (vkey == VK_RETURN) {
			control_type_message();
		}
		if (vkey != VK_ESCAPE) {
			return;
		}
	}
	if (vkey == VK_ESCAPE) {
		if (!PressEscKey()) {
			track_repeat_walk(0);
			gamemenu_previous();
		}
		return;
	}

	if (sgnTimeoutCurs != 0 || dropGoldFlag) {
		return;
	}
	if (vkey == VK_PAUSE) {
		diablo_pause_game();
		return;
	}
	if (PauseMode == 2) {
		return;
	}

	if (vkey == VK_RETURN) {
		if (stextflag) {
			STextEnter();
		} else if (questlog) {
			QuestlogEnter();
		} else {
			control_type_message();
		}
	} else if (vkey == VK_F1) {
		if (helpflag) {
			helpflag = 0;
		} else if (stextflag) {
			ClearPanel();
			AddPanelString("No help available", TRUE); /// BUGFIX: message isn't displayed
			AddPanelString("while in stores", TRUE);
			track_repeat_walk(0);
		} else {
			invflag = 0;
			chrflag = FALSE;
			sbookflag = FALSE;
			spselflag = 0;
			if (qtextflag && leveltype == DTYPE_TOWN) {
				qtextflag = FALSE;
				sfx_stop();
			}
			questlog = FALSE;
			automapflag = 0;
			msgdelay = 0;
			gamemenu_off();
			DisplayHelp();
			doom_close();
		}
	}
#ifdef _DEBUG
	else if (vkey == VK_F2) {
	}
#endif
#ifdef _DEBUG
	else if (vkey == VK_F3) {
		if (pcursitem != -1) {
			sprintf(
			    tempstr,
			    "IDX = %i  :  Seed = %i  :  CF = %i",
			    item[pcursitem].IDidx,
			    item[pcursitem]._iSeed,
			    item[pcursitem]._iCreateInfo);
			NetSendCmdString(1 << myplr, tempstr);
		}
		sprintf(tempstr, "Numitems : %i", numitems);
		NetSendCmdString(1 << myplr, tempstr);
	}
#endif
#ifdef _DEBUG
	else if (vkey == VK_F4) {
		PrintDebugQuest();
	}
#endif
	else if (vkey == VK_F5) {
		if (spselflag) {
			SetSpeedSpell(0);
		} else {
			ToggleSpell(0);
		}
	} else if (vkey == VK_F6) {
		if (spselflag) {
			SetSpeedSpell(1);
		} else {
			ToggleSpell(1);
		}
	} else if (vkey == VK_F7) {
		if (spselflag) {
			SetSpeedSpell(2);
		} else {
			ToggleSpell(2);
		}
	} else if (vkey == VK_F8) {
		if (spselflag) {
			SetSpeedSpell(3);
		} else {
			ToggleSpell(3);
		}
	} else if (vkey == VK_F9) {
		diablo_hotkey_msg(0);
	} else if (vkey == VK_F10) {
		diablo_hotkey_msg(1);
	} else if (vkey == VK_F11) {
		diablo_hotkey_msg(2);
	} else if (vkey == VK_F12) {
		diablo_hotkey_msg(3);
	} else if (vkey == VK_UP) {
		if (stextflag) {
			STextUp();
		} else if (questlog) {
			QuestlogUp();
		} else if (helpflag) {
			HelpScrollUp();
		} else if (automapflag) {
			AutomapUp();
		}
	} else if (vkey == VK_DOWN) {
		if (stextflag) {
			STextDown();
		} else if (questlog) {
			QuestlogDown();
		} else if (helpflag) {
			HelpScrollDown();
		} else if (automapflag) {
			AutomapDown();
		}
	} else if (vkey == VK_PRIOR) {
		if (stextflag) {
			STextPrior();
		}
	} else if (vkey == VK_NEXT) {
		if (stextflag) {
			STextNext();
		}
	} else if (vkey == VK_LEFT) {
		if (automapflag && !talkflag) {
			AutomapLeft();
		}
	} else if (vkey == VK_RIGHT) {
		if (automapflag && !talkflag) {
			AutomapRight();
		}
	} else if (vkey == VK_TAB) {
		DoAutoMap();
	} else if (vkey == VK_SPACE) {
		if (!chrflag && invflag && MouseX < 480 && MouseY < PANEL_TOP) {
			SetCursorPos(MouseX + 160, MouseY);
		}
		if (!invflag && chrflag && MouseX > 160 && MouseY < PANEL_TOP) {
			SetCursorPos(MouseX - 160, MouseY);
		}
		helpflag = 0;
		invflag = 0;
		chrflag = FALSE;
		sbookflag = FALSE;
		spselflag = 0;
		if (qtextflag && leveltype == DTYPE_TOWN) {
			qtextflag = FALSE;
			sfx_stop();
		}
		questlog = FALSE;
		automapflag = 0;
		msgdelay = 0;
		gamemenu_off();
		doom_close();
	}
}

void diablo_pause_game()
{
	if (gbMaxPlayers <= 1) {
		if (PauseMode) {
			PauseMode = 0;
		} else {
			PauseMode = 2;
			FreeMonsterSnd();
			track_repeat_walk(0);
		}
		drawpanflag = 255;
	}
}

/* NOTE: `return` must be used instead of `break` to be bin exact as C++ */
void PressChar(int vkey)
{
	if (gmenu_exception() || control_talk_last_key(vkey) || sgnTimeoutCurs != 0 || deathflag) {
		return;
	}
	if ((char)vkey == 'p' || (char)vkey == 'P') {
		diablo_pause_game();
		return;
	}
	if (PauseMode == 2) {
		return;
	}
	if (doomflag) {
		doom_close();
		return;
	}
	if (dropGoldFlag) {
		control_drop_gold(vkey);
		return;
	}

	switch (vkey) {
	case 'G':
	case 'g':
		DecreaseGamma();
		return;
	case 'F':
	case 'f':
		IncreaseGamma();
		return;
	case 'I':
	case 'i':
		if (!stextflag) {
			sbookflag = FALSE;
			invflag = invflag == 0;
			if (!invflag || chrflag) {
				if (MouseX < 480 && MouseY < PANEL_TOP) {
					SetCursorPos(MouseX + 160, MouseY);
				}
			} else {
				if (MouseX > 160 && MouseY < PANEL_TOP) {
					SetCursorPos(MouseX - 160, MouseY);
				}
			}
		}
		return;
	case 'C':
	case 'c':
		if (!stextflag) {
			questlog = FALSE;
			chrflag = !chrflag;
			if (!chrflag || invflag) {
				if (MouseX > 160 && MouseY < PANEL_TOP) {
					SetCursorPos(MouseX - 160, MouseY);
				}
			} else {
				if (MouseX < 480 && MouseY < PANEL_TOP) {
					SetCursorPos(MouseX + 160, MouseY);
				}
			}
		}
		return;
	case 'Q':
	case 'q':
		if (!stextflag) {
			chrflag = FALSE;
			if (!questlog) {
				StartQuestlog();
			} else {
				questlog = FALSE;
			}
		}
		return;
	case 'Z':
	case 'z':
		zoomflag = zoomflag == 0;
		return;
	case 'S':
	case 's':
		if (!stextflag) {
			invflag = 0;
			if (!spselflag) {
				DoSpeedBook();
			} else {
				spselflag = 0;
			}
			track_repeat_walk(0);
		}
		return;
	case 'B':
	case 'b':
		if (!stextflag) {
			invflag = 0;
			sbookflag = !sbookflag;
		}
		return;
	case '+':
	case '=':
		if (automapflag) {
			AutomapZoomIn();
		}
		return;
	case '-':
	case '_':
		if (automapflag) {
			AutomapZoomOut();
		}
		return;
	case 'v':
		NetSendCmdString(1 << myplr, gszProductName);
		return;
	case 'V':
		NetSendCmdString(1 << myplr, gszVersionNumber);
		return;
	case '!':
	case '1':
		if (plr[myplr].SpdList[0]._itype != -1 && plr[myplr].SpdList[0]._itype != 11) {
			UseInvItem(myplr, 47);
		}
		return;
	case '@':
	case '2':
		if (plr[myplr].SpdList[1]._itype != -1 && plr[myplr].SpdList[1]._itype != 11) {
			UseInvItem(myplr, 48);
		}
		return;
	case '#':
	case '3':
		if (plr[myplr].SpdList[2]._itype != -1 && plr[myplr].SpdList[2]._itype != 11) {
			UseInvItem(myplr, 49);
		}
		return;
	case '$':
	case '4':
		if (plr[myplr].SpdList[3]._itype != -1 && plr[myplr].SpdList[3]._itype != 11) {
			UseInvItem(myplr, 50);
		}
		return;
	case '%':
	case '5':
		if (plr[myplr].SpdList[4]._itype != -1 && plr[myplr].SpdList[4]._itype != 11) {
			UseInvItem(myplr, 51);
		}
		return;
	case '^':
	case '6':
		if (plr[myplr].SpdList[5]._itype != -1 && plr[myplr].SpdList[5]._itype != 11) {
			UseInvItem(myplr, 52);
		}
		return;
	case '&':
	case '7':
		if (plr[myplr].SpdList[6]._itype != -1 && plr[myplr].SpdList[6]._itype != 11) {
			UseInvItem(myplr, 53);
		}
		return;
	case '*':
	case '8':
#ifdef _DEBUG
		if (debug_mode_key_inverted_v || debug_mode_key_w) {
			NetSendCmd(TRUE, CMD_CHEAT_EXPERIENCE);
			return;
		}
#endif
		if (plr[myplr].SpdList[7]._itype != -1 && plr[myplr].SpdList[7]._itype != 11) {
			UseInvItem(myplr, 54);
		}
		return;
#ifdef _DEBUG
	case ')':
	case '0':
		if (debug_mode_key_inverted_v) {
			if (arrowdebug > 2) {
				arrowdebug = 0;
			}
			if (arrowdebug == 0) {
				plr[myplr]._pIFlags &= ~ISPL_FIRE_ARROWS;
				plr[myplr]._pIFlags &= ~ISPL_LIGHT_ARROWS;
			}
			if (arrowdebug == 1) {
				plr[myplr]._pIFlags |= ISPL_FIRE_ARROWS;
			}
			if (arrowdebug == 2) {
				plr[myplr]._pIFlags |= ISPL_LIGHT_ARROWS;
			}
			arrowdebug++;
		}
		return;
	case ':':
		if (currlevel == 0 && debug_mode_key_w) {
			SetAllSpellsCheat();
		}
		return;
	case '[':
		if (currlevel == 0 && debug_mode_key_w) {
			TakeGoldCheat();
		}
		return;
	case ']':
		if (currlevel == 0 && debug_mode_key_w) {
			MaxSpellsCheat();
		}
		return;
	case 'a':
		if (debug_mode_key_inverted_v) {
			spelldata[SPL_TELEPORT].sTownSpell = 1;
			plr[myplr]._pSplLvl[plr[myplr]._pSpell]++;
		}
		return;
	case 'D':
		PrintDebugPlayer(TRUE);
		return;
	case 'd':
		PrintDebugPlayer(FALSE);
		return;
	case 'e':
		if (debug_mode_key_d) {
			sprintf(tempstr, "EFlag = %i", plr[myplr]._peflag);
			NetSendCmdString(1 << myplr, tempstr);
		}
		return;
	case 'L':
	case 'l':
		if (debug_mode_key_inverted_v) {
			ToggleLighting();
		}
		return;
	case 'M':
		NextDebugMonster();
		return;
	case 'm':
		GetDebugMonster();
		return;
	case 'R':
	case 'r':
		sprintf(tempstr, "seed = %i", glSeedTbl[currlevel]);
		NetSendCmdString(1 << myplr, tempstr);
		sprintf(tempstr, "Mid1 = %i : Mid2 = %i : Mid3 = %i", glMid1Seed[currlevel], glMid2Seed[currlevel], glMid3Seed[currlevel]);
		NetSendCmdString(1 << myplr, tempstr);
		sprintf(tempstr, "End = %i", glEndSeed[currlevel]);
		NetSendCmdString(1 << myplr, tempstr);
		return;
	case 'T':
	case 't':
		if (debug_mode_key_inverted_v) {
			sprintf(tempstr, "PX = %i  PY = %i", plr[myplr].WorldX, plr[myplr].WorldY);
			NetSendCmdString(1 << myplr, tempstr);
			sprintf(tempstr, "CX = %i  CY = %i  DP = %i", cursmx, cursmy, dungeon[cursmx][cursmy]);
			NetSendCmdString(1 << myplr, tempstr);
		}
		return;
	case '|':
		if (currlevel == 0 && debug_mode_key_w) {
			GiveGoldCheat();
		}
		return;
	case '~':
		if (currlevel == 0 && debug_mode_key_w) {
			StoresCheat();
		}
		return;
#endif
	}
}

void LoadLvlGFX()
{
	/// ASSERT: assert(! pDungeonCels);

	switch (leveltype) {
	case DTYPE_TOWN:
#ifdef HELLFIRE
		pDungeonCels = LoadFileInMem("NLevels\\TownData\\Town.CEL", NULL);
		pMegaTiles = LoadFileInMem("NLevels\\TownData\\Town.TIL", NULL);
		pLevelPieces = LoadFileInMem("NLevels\\TownData\\Town.MIN", NULL);
#else
		pDungeonCels = LoadFileInMem("Levels\\TownData\\Town.CEL", NULL);
		pMegaTiles = LoadFileInMem("Levels\\TownData\\Town.TIL", NULL);
		pLevelPieces = LoadFileInMem("Levels\\TownData\\Town.MIN", NULL);
#endif
		pSpecialCels = LoadFileInMem("Levels\\TownData\\TownS.CEL", NULL);
		break;
	case DTYPE_CATHEDRAL:
#ifdef HELLFIRE
		if (currlevel < 21) {
#endif
			pDungeonCels = LoadFileInMem("Levels\\L1Data\\L1.CEL", NULL);
			pMegaTiles = LoadFileInMem("Levels\\L1Data\\L1.TIL", NULL);
			pLevelPieces = LoadFileInMem("Levels\\L1Data\\L1.MIN", NULL);
			pSpecialCels = LoadFileInMem("Levels\\L1Data\\L1S.CEL", NULL);
#ifdef HELLFIRE
		} else {
			pDungeonCels = LoadFileInMem("NLevels\\L5Data\\L5.CEL", NULL);
			pMegaTiles = LoadFileInMem("NLevels\\L5Data\\L5.TIL", NULL);
			pLevelPieces = LoadFileInMem("NLevels\\L5Data\\L5.MIN", NULL);
			pSpecialCels = LoadFileInMem("NLevels\\L5Data\\L5S.CEL", NULL);
		}
#endif
		break;
#ifndef SPAWN
	case DTYPE_CATACOMBS:
		pDungeonCels = LoadFileInMem("Levels\\L2Data\\L2.CEL", NULL);
		pMegaTiles = LoadFileInMem("Levels\\L2Data\\L2.TIL", NULL);
		pLevelPieces = LoadFileInMem("Levels\\L2Data\\L2.MIN", NULL);
		pSpecialCels = LoadFileInMem("Levels\\L2Data\\L2S.CEL", NULL);
		break;
	case DTYPE_CAVES:
#ifdef HELLFIRE
		if (currlevel < 17) {
#endif
			pDungeonCels = LoadFileInMem("Levels\\L3Data\\L3.CEL", NULL);
			pMegaTiles = LoadFileInMem("Levels\\L3Data\\L3.TIL", NULL);
			pLevelPieces = LoadFileInMem("Levels\\L3Data\\L3.MIN", NULL);
#ifdef HELLFIRE
		} else {
			pDungeonCels = LoadFileInMem("NLevels\\L6Data\\L6.CEL", NULL);
			pMegaTiles = LoadFileInMem("NLevels\\L6Data\\L6.TIL", NULL);
			pLevelPieces = LoadFileInMem("NLevels\\L6Data\\L6.MIN", NULL);
		}
#endif
		pSpecialCels = LoadFileInMem("Levels\\L1Data\\L1S.CEL", NULL);
		break;
	case DTYPE_HELL:
		pDungeonCels = LoadFileInMem("Levels\\L4Data\\L4.CEL", NULL);
		pMegaTiles = LoadFileInMem("Levels\\L4Data\\L4.TIL", NULL);
		pLevelPieces = LoadFileInMem("Levels\\L4Data\\L4.MIN", NULL);
		pSpecialCels = LoadFileInMem("Levels\\L2Data\\L2S.CEL", NULL);
		break;
#endif
	default:
		app_fatal("LoadLvlGFX");
		break;
	}
}

void LoadAllGFX()
{
	/// ASSERT: assert(! pSpeedCels);
	pSpeedCels = DiabloAllocPtr(0x100000);
	IncProgress();
	IncProgress();
	InitObjectGFX();
	IncProgress();
	InitMissileGFX();
	IncProgress();
}

void CreateLevel(int lvldir)
{
	switch (leveltype) {
	case DTYPE_TOWN:
		CreateTown(lvldir);
		InitTownTriggers();
		LoadRndLvlPal(0);
		break;
	case DTYPE_CATHEDRAL:
		CreateL5Dungeon(glSeedTbl[currlevel], lvldir);
		InitL1Triggers();
		Freeupstairs();
#ifdef HELLFIRE
		if(currlevel < 21) {
			LoadRndLvlPal(1);
		} else {
			LoadRndLvlPal(5);
		}
#else
		LoadRndLvlPal(1);
#endif
		break;
#ifndef SPAWN
	case DTYPE_CATACOMBS:
		CreateL2Dungeon(glSeedTbl[currlevel], lvldir);
		InitL2Triggers();
		Freeupstairs();
		LoadRndLvlPal(2);
		break;
	case DTYPE_CAVES:
		CreateL3Dungeon(glSeedTbl[currlevel], lvldir);
		InitL3Triggers();
		Freeupstairs();
#ifdef HELLFIRE
		if(currlevel < 17) {
			LoadRndLvlPal(3);
		} else {
			LoadRndLvlPal(6);
		}
#else
		LoadRndLvlPal(3);
#endif
		break;
	case DTYPE_HELL:
		CreateL4Dungeon(glSeedTbl[currlevel], lvldir);
		InitL4Triggers();
		Freeupstairs();
		LoadRndLvlPal(4);
		break;
#endif
	default:
		app_fatal("CreateLevel");
		break;
	}
}

void LoadGameLevel(BOOL firstflag, int lvldir)
{
	int i, j;
	BOOL visited;

	if (setseed)
		glSeedTbl[currlevel] = setseed;

	music_stop();
	SetCursor_(CURSOR_HAND);
	SetRndSeed(glSeedTbl[currlevel]);
	IncProgress();
	MakeLightTable();
	LoadLvlGFX();
	IncProgress();

	if (firstflag) {
		InitInv();
		InitItemGFX();
		InitQuestText();

		for (i = 0; i < gbMaxPlayers; i++)
			InitPlrGFXMem(i);

		InitStores();
		InitAutomapOnce();
		InitHelp();
	}

	SetRndSeed(glSeedTbl[currlevel]);

	if (leveltype == DTYPE_TOWN)
		SetupTownStores();

	IncProgress();
	InitAutomap();

	if (leveltype != DTYPE_TOWN && lvldir != 4) {
		InitLighting();
		InitVision();
	}

	InitLevelMonsters();
	IncProgress();

	if (!setlevel) {
		CreateLevel(lvldir);
		IncProgress();
		FillSolidBlockTbls();
		SetRndSeed(glSeedTbl[currlevel]);

		if (leveltype != DTYPE_TOWN) {
			GetLevelMTypes();
			InitThemes();
			LoadAllGFX();
		} else {
			InitMissileGFX();
		}

		IncProgress();

		if (lvldir == 3)
			GetReturnLvlPos();
		if (lvldir == 5)
			GetPortalLvlPos();

		IncProgress();

		for (i = 0; i < MAX_PLRS; i++) {
			if (plr[i].plractive && currlevel == plr[i].plrlevel) {
				InitPlayerGFX(i);
				if (lvldir != 4)
					InitPlayer(i, firstflag);
			}
		}

		PlayDungMsgs();
		InitMultiView();
		IncProgress();

		visited = FALSE;
		for (i = 0; i < gbMaxPlayers; i++) {
			if (plr[i].plractive)
				visited = visited || plr[i]._pLvlVisited[currlevel];
		}

		SetRndSeed(glSeedTbl[currlevel]);

		if (leveltype != DTYPE_TOWN) {
			if (firstflag || lvldir == 4 || !plr[myplr]._pLvlVisited[currlevel] || gbMaxPlayers != 1) {
				HoldThemeRooms();
				glMid1Seed[currlevel] = GetRndSeed();
				InitMonsters();
				glMid2Seed[currlevel] = GetRndSeed();
				InitObjects();
				InitItems();
#ifdef HELLFIRE
				if ( currlevel < 17 )
#endif
					CreateThemeRooms();
				glMid3Seed[currlevel] = GetRndSeed();
				InitMissiles();
				InitDead();
				glEndSeed[currlevel] = GetRndSeed();

				if (gbMaxPlayers != 1)
					DeltaLoadLevel();

				IncProgress();
				SavePreLighting();
			} else {
				InitMonsters();
				InitMissiles();
				InitDead();
				IncProgress();
				LoadLevel();
				IncProgress();
			}
		} else {
			for (i = 0; i < MAXDUNX; i++) {
				for (j = 0; j < MAXDUNY; j++)
					dFlags[i][j] |= BFLAG_LIT;
			}

			InitTowners();
			InitItems();
			InitMissiles();
			IncProgress();

			if (!firstflag && lvldir != 4 && plr[myplr]._pLvlVisited[currlevel] && gbMaxPlayers == 1)
				LoadLevel();
			if (gbMaxPlayers != 1)
				DeltaLoadLevel();

			IncProgress();
		}
		if (gbMaxPlayers == 1)
			ResyncQuests();
		else
			ResyncMPQuests();
#ifndef SPAWN
	} else {
		/// ASSERT: assert(! pSpeedCels);
		pSpeedCels = DiabloAllocPtr(0x100000);
		LoadSetMap();
		IncProgress();
		GetLevelMTypes();
		InitMonsters();
		InitMissileGFX();
		InitDead();
		FillSolidBlockTbls();
		IncProgress();

		if (lvldir == 5)
			GetPortalLvlPos();

		for (i = 0; i < MAX_PLRS; i++) {
			if (plr[i].plractive && currlevel == plr[i].plrlevel) {
				InitPlayerGFX(i);
				if (lvldir != 4)
					InitPlayer(i, firstflag);
			}
		}

		InitMultiView();
		IncProgress();

		if (firstflag || lvldir == 4 || !plr[myplr]._pSLvlVisited[setlvlnum]) {
			InitItems();
			SavePreLighting();
		} else {
			LoadLevel();
		}

		InitMissiles();
		IncProgress();
#endif
	}

	SyncPortals();

	for (i = 0; i < MAX_PLRS; i++) {
		if (plr[i].plractive && plr[i].plrlevel == currlevel && (!plr[i]._pLvlChanging || i == myplr)) {
			if (plr[i]._pHitPoints > 0) {
				if (gbMaxPlayers == 1)
					dPlayer[plr[i].WorldX][plr[i].WorldY] = i + 1;
				else
					SyncInitPlrPos(i);
			} else {
				dFlags[plr[i].WorldX][plr[i].WorldY] |= BFLAG_DEAD_PLAYER;
			}
		}
	}

	if (leveltype != DTYPE_TOWN)
		SetDungeonMicros();

	InitLightMax();
	IncProgress();
	IncProgress();

	if (firstflag) {
		InitControlPan();
		IncProgress();
	}
	if (leveltype != DTYPE_TOWN) {
		ProcessLightList();
		ProcessVisionList();
	}

#ifdef HELLFIRE
	if ( currlevel >= 21 )
	{
		if ( currlevel == 21 )
		{
			items_427ABA(RowOfCornerStone, ColOfCornerStone);
		}
		if ( quests[QTYPE_NAKRUL]._qactive == 3 && currlevel == 24 ) // fix quest struct
		{
			objects_454BA8();
		}
	}
#endif

#ifdef HELLFIRE
	if ( currlevel >= 17 )
		music_start(currlevel > 20 ? TMUSIC_L5 : TMUSIC_L6);
	else
		music_start(leveltype);
#else
	music_start(leveltype);
#endif

	while (!IncProgress())
		;

#ifndef SPAWN
	if (setlevel && setlvlnum == SL_SKELKING && quests[QTYPE_KING]._qactive == 2)
		PlaySFX(USFX_SKING1);
#endif
}

void game_loop(BOOL bStartup)
{
	int i;

	i = bStartup ? 60 : 3;

	while (i--) {
		if (!multi_handle_delta()) {
			timeout_cursor(TRUE);
			break;
		} else {
			timeout_cursor(FALSE);
			game_logic();
		}
		if (!gbRunGame || gbMaxPlayers == 1 || !nthread_has_500ms_passed(TRUE))
			break;
	}
}

void game_logic()
{
	if (PauseMode == 2) {
		return;
	}
	if (PauseMode == 1) {
		PauseMode = 2;
	}
	if (gbMaxPlayers == 1 && gmenu_exception()) {
		drawpanflag |= 1;
		return;
	}

	if (!gmenu_exception() && sgnTimeoutCurs == 0) {
		CheckCursMove();
		track_process();
	}
	if (gbProcessPlayers) {
		ProcessPlayers();
	}
	if (leveltype != DTYPE_TOWN) {
		ProcessMonsters();
		ProcessObjects();
		ProcessMissiles();
		ProcessItems();
		ProcessLightList();
		ProcessVisionList();
	} else {
		ProcessTowners();
		ProcessItems();
		ProcessMissiles();
	}

#ifdef _DEBUG
	if (debug_mode_key_inverted_v && GetAsyncKeyState(VK_SHIFT) & 0x8000) {
		ScrollView();
	}
#endif

	sound_update();
	ClearPlrMsg();
	CheckTriggers();
	CheckQuests();
	drawpanflag |= 1;
	pfile_update(FALSE);
}

void timeout_cursor(BOOL bTimeout)
{
	if (bTimeout) {
		if (sgnTimeoutCurs == CURSOR_NONE && !sgbMouseDown) {
			sgnTimeoutCurs = pcurs;
			multi_net_ping();
			ClearPanel();
			AddPanelString("-- Network timeout --", TRUE);
			AddPanelString("-- Waiting for players --", TRUE);
			SetCursor_(CURSOR_HOURGLASS);
			drawpanflag = 255;
		}
		scrollrt_draw_game_screen(1);
	} else if (sgnTimeoutCurs) {
		SetCursor_(sgnTimeoutCurs);
		sgnTimeoutCurs = 0;
		ClearPanel();
		drawpanflag = 255;
	}
}

void diablo_color_cyc_logic()
{
	DWORD tc;

	tc = GetTickCount();
	if (tc - color_cycle_timer >= 50) {
		color_cycle_timer = tc;
		if (palette_get_colour_cycling()) {
			if (leveltype == DTYPE_HELL) {
				lighting_color_cycling();
			} else if (leveltype == DTYPE_CAVES) {
				if (fullscreen)
					palette_update_caves();
			}
		}
	}
}

#ifdef HELLFIRE
void alloc_plr()
{
	plr = get_plr_mem(NULL);

	if(plr == NULL) {
		app_fatal("Unable to initialize memory");
	}

	memset(plr, 0, sizeof(PlayerStruct) * MAX_PLRS);
}

PlayerStruct *get_plr_mem(PlayerStruct *p)
{
	void *r;
	PlayerStruct *pPlayer;

	r = malloc(rand() & 0x7FFF);
	pPlayer = (PlayerStruct *)malloc(sizeof(PlayerStruct) * MAX_PLRS);

	if(r != NULL) {
		free(r);
	}
	if(pPlayer == NULL) {
		return p;
	}
	if(p != NULL) {
		memcpy(pPlayer, p, sizeof(PlayerStruct) * MAX_PLRS);
		free(p);
	}

	return pPlayer;
}
#endif
