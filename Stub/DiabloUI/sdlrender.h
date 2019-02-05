#pragma once

#include "../../types.h"

typedef enum _artFocus {
	FOCUS_SMALL,
	FOCUS_MED,
	FOCUS_BIG,
} _artFocus;

typedef enum _artLogo {
	LOGO_SMALL,
	LOGO_MED,
	LOGO_BIG,
} _artLogo;

typedef enum _artFontTables {
	AFT_SMALL,
	AFT_MED,
	AFT_BIG,
	AFT_HUGE,
} _artFontTables;

typedef enum _artFontColors {
	AFC_SILVER,
	AFC_GOLD,
} _artFontColors;

typedef struct Art {
	BYTE *data;
	DWORD width;
	DWORD height;
	bool masked = false;
	BYTE mask;
} Art;

extern TTF_Font *font;

extern BYTE *FontTables[4];
extern Art ArtFonts[4][2];
extern Art ArtLogos[3];
extern Art ArtFocus[3];
extern Art ArtBackground;
extern Art ArtCursor;
extern Art ArtHero;

extern int SelectedItem;
extern int SelectedItemMax;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int submenu;

typedef enum TXT_JUST {
	JustLeft = 0,
	JustCentre = 1,
	JustRight = 2,
} TXT_JUST;

extern void(__stdcall *gfnSoundFunction)(char *file);

DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, char *lpBuffer, DWORD nSize, va_list *Arguments);
int MAKEINTRESOURCE(int i);
int DialogBoxParam(HINSTANCE hInstance, int msgId, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
BOOL SetDlgItemText(HWND hDlg, int nIDDlgItem, LPCSTR lpString);
BOOL EndDialog(HWND hDlg, INT_PTR nResult);
BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);

bool IsInsideRect(const SDL_Event *event, const SDL_Rect *rect);
bool UiFadeIn(int steps = 16);
int GetAnimationFrame(int frames, int fps = 60);
int GetCenterOffset(int w, int bw = 0);
void CapFPS();
void DrawArt(int screenX, int screenY, Art *art, int nFrame = 0, int drawW = 0);
void DrawArtStr(int x, int y, int size, int color, BYTE *str, TXT_JUST align = JustLeft, int bw = 0);
void DrawLogo(int t = 0, int size = LOGO_MED);
void DrawMouse();
void DrawSelector(int x, int y, int width, int padding, int spacing = 0, int size = FOCUS_MED);
void LoadArt(char *pszFile, Art *art, int frames = 1, PALETTEENTRY *pPalette = NULL);
void LoadMaskedArtFont(char *pszFile, Art *art, int frames, int mask = 250);
void LoadBackgroundArt(char *pszFile);
void SetMenu(int MenuId);
void UiFocuse(int move, bool wrap = false);
bool UiFocuseNavigation(SDL_Event *event, bool wrap = false);
void UiPlayMoveSound();
void UiPlaySelectSound();
