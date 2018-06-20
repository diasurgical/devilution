//HEADER_GOES_HERE
#ifndef __DIABLO_H__
#define __DIABLO_H__

extern int diablo_cpp_init_value; // weak
extern HWND ghMainWnd;
extern int glMid1Seed[17];
extern int glMid2Seed[17];
extern int gnLevelTypeTbl[17];
extern int MouseY; // idb
extern int MouseX; // idb
extern bool gbGameLoopStartup; // idb
extern int glSeedTbl[17];
extern int gbRunGame; // weak
extern int glMid3Seed[17];
extern int gbRunGameResult; // weak
extern int zoomflag; // weak
extern int gbProcessPlayers; // weak
extern int glEndSeed[17];
extern int dword_5256E8; // weak
extern HINSTANCE ghInst; // idb
extern int DebugMonsters[10];
extern char cineflag; // weak
extern int drawpanflag; // weak
extern int visiondebug; // weak
extern int scrollflag; /* unused */
extern int light4flag; // weak
extern int leveldebug; // weak
extern int monstdebug; // weak
extern int trigdebug; /* unused */
extern int setseed; // weak
extern int debugmonsttypes; // weak
extern int PauseMode; // weak
extern int sgnTimeoutCurs;
extern char sgbMouseDown; // weak
extern int color_cycle_timer; // weak

void __cdecl diablo_cpp_init();
void __cdecl FreeGameMem();
int __fastcall diablo_init_menu(int a1, int bSinglePlayer);
void __fastcall run_game_loop(int uMsg);
void __fastcall start_game(int uMsg);
void __cdecl free_game();
bool __cdecl diablo_get_not_running();
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
void __fastcall diablo_parse_flags(char *args);
void __cdecl diablo_init_screen();
HWND __fastcall diablo_find_window(LPCSTR lpClassName);
void __fastcall diablo_reload_process(HMODULE hModule);
int __cdecl PressEscKey();
LRESULT __stdcall DisableInputWndProc(HWND hWnd, int uMsg, int wParam, int lParam);
int __stdcall GM_Game(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool __fastcall LeftMouseDown(int a1);
bool __cdecl TryIconCurs();
void __cdecl LeftMouseUp();
void __cdecl RightMouseDown();
void __fastcall j_gmenu_on_mouse_move(LPARAM lParam);
bool __fastcall PressSysKey(int wParam);
void __fastcall diablo_hotkey_msg(int dwMsg);
void __fastcall ReleaseKey(int vkey);
void __fastcall PressKey(int vkey);
void __cdecl diablo_pause_game();
void __fastcall PressChar(int vkey);
void __cdecl LoadLvlGFX();
void __cdecl LoadAllGFX();
void __fastcall CreateLevel(int lvldir);
void __fastcall LoadGameLevel(bool firstflag, int lvldir);
void __fastcall game_loop(bool startup);
void __cdecl game_logic();
void __fastcall timeout_cursor(bool timeout);
void __cdecl diablo_color_cyc_logic();

/* data */

extern int diablo_inf; // weak

/* rdata */

extern int fullscreen; // weak
#ifdef _DEBUG
extern int showintrodebug;
extern int questdebug;
extern int debug_mode_key_s;
extern int debug_mode_key_w;
extern int debug_mode_key_inverted_v;
extern int debug_mode_dollar_sign;
extern int debug_mode_key_d;
extern int debug_mode_key_i;
extern int dbgplr;
extern int dbgqst;
extern int dbgmon;
extern int frameflag;
extern int frameend;
extern int framerate;
extern int framestart;
#endif
extern int FriendlyMode; // weak
extern char *spszMsgTbl[4]; // weak
extern char *spszMsgKeyTbl[4]; // weak

#endif /* __DIABLO_H__ */
