//HEADER_GOES_HERE
#ifndef __DIABLO_H__
#define __DIABLO_H__

extern HWND ghMainWnd;
extern int glMid1Seed[NUMLEVELS];
extern int glMid2Seed[NUMLEVELS];
extern int gnLevelTypeTbl[NUMLEVELS];
extern int MouseY;             // idb
extern int MouseX;             // idb
extern BOOL gbGameLoopStartup; // idb
extern int glSeedTbl[NUMLEVELS];
extern BOOL gbRunGame;
extern int glMid3Seed[NUMLEVELS];
extern BOOL gbRunGameResult;
extern int zoomflag; // weak
extern BOOL gbProcessPlayers;
extern int glEndSeed[NUMLEVELS];
extern BOOL gbLoadGame;
extern HINSTANCE ghInst; // idb
extern int DebugMonsters[10];
extern char cineflag;   // weak
extern int drawpanflag; // weak
extern int visiondebug; // weak
extern int scrollflag;  /* unused */
extern BOOL light4flag;
extern int leveldebug;        // weak
extern int monstdebug;        // weak
extern int trigdebug;         /* unused */
extern int setseed;           // weak
extern int debugmonsttypes;   // weak
extern int PauseMode;         // weak
extern char sgbMouseDown;     // weak
extern int color_cycle_timer; // weak

void __cdecl FreeGameMem();
BOOL __fastcall StartGame(BOOL bNewGame, BOOL bSinglePlayer);
void __fastcall run_game_loop(unsigned int uMsg);
void __fastcall start_game(unsigned int uMsg);
void __cdecl free_game();
BOOL __cdecl diablo_get_not_running();
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void __fastcall diablo_parse_flags(char *args);
void __cdecl diablo_init_screen();
BOOL __fastcall diablo_find_window(LPCSTR lpClassName);
void __fastcall diablo_reload_process(HMODULE hModule);
BOOL __cdecl PressEscKey();
LRESULT CALLBACK DisableInputWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GM_Game(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL __fastcall LeftMouseDown(int wParam);
BOOL __fastcall LeftMouseCmd(BOOL bShift);
BOOLEAN __cdecl TryIconCurs();
void __cdecl LeftMouseUp();
void __cdecl RightMouseDown();
void __fastcall j_gmenu_on_mouse_move(LPARAM lParam);
BOOL __fastcall PressSysKey(int wParam);
void __fastcall diablo_hotkey_msg(int dwMsg);
void __fastcall ReleaseKey(int vkey);
void __fastcall PressKey(int vkey);
void __cdecl diablo_pause_game();
void __fastcall PressChar(int vkey);
void __cdecl LoadLvlGFX();
void __cdecl LoadAllGFX();
void __fastcall CreateLevel(int lvldir);
void __fastcall LoadGameLevel(BOOL firstflag, int lvldir);
void __fastcall game_loop(BOOL bStartup);
void __cdecl game_logic();
void __fastcall timeout_cursor(BOOL bTimeout);
void __cdecl diablo_color_cyc_logic();

/* data */

extern int diablo_inf; // weak

/* rdata */

extern BOOL fullscreen;
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
extern int arrowdebug;
extern int frameflag;
extern int frameend;
extern int framerate;
extern int framestart;
#endif
extern BOOL FriendlyMode;
extern char *spszMsgTbl[4];    // weak
extern char *spszMsgKeyTbl[4]; // weak

#endif /* __DIABLO_H__ */
