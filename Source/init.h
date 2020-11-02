/**
 * @file init.h
 *
 * Interface of routines for initializing the environment, disable screen saver, load MPQ.
 */
#ifndef __INIT_H__
#define __INIT_H__

extern _SNETVERSIONDATA fileinfo;
extern int gbActive;
extern WNDPROC CurrentProc;
extern HANDLE diabdat_mpq;
#ifdef HELLFIRE
extern HANDLE hfbard_mpq;
extern HANDLE hfbarb_mpq;
#endif

void init_cleanup(BOOL show_cursor);
void init_create_window(int nCmdShow);
LRESULT __stdcall MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
WNDPROC SetWindowProc(WNDPROC NewProc);

/* data */

extern char gszVersionNumber[MAX_PATH];
extern char gszProductName[MAX_PATH];

#endif /* __INIT_H__ */
