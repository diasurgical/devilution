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

void FreeGameMem();
BOOL StartGame(BOOL bNewGame, BOOL bSinglePlayer);
void run_game_loop(unsigned int uMsg);
void start_game(unsigned int uMsg);
void free_game();
BOOL diablo_get_not_running();
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void diablo_parse_flags(char *args);
void diablo_init_screen();
BOOL diablo_find_window(LPCSTR lpClassName);
void diablo_reload_process(HMODULE hModule);
BOOL PressEscKey();
LRESULT CALLBACK DisableInputWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GM_Game(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL LeftMouseDown(int wParam);
BOOL LeftMouseCmd(BOOL bShift);
BOOL TryIconCurs();
void LeftMouseUp();
void RightMouseDown();
void j_gmenu_on_mouse_move(LPARAM lParam);
BOOL PressSysKey(int wParam);
void diablo_hotkey_msg(int dwMsg);
void ReleaseKey(int vkey);
void PressKey(int vkey);
void diablo_pause_game();
void PressChar(int vkey);
void LoadLvlGFX();
void LoadAllGFX();
void CreateLevel(int lvldir);
void LoadGameLevel(BOOL firstflag, int lvldir);
void game_loop(BOOL bStartup);
void game_logic();
void timeout_cursor(BOOL bTimeout);
void diablo_color_cyc_logic();

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
