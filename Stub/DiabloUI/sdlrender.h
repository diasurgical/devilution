#pragma once

#include "../../types.h"

extern unsigned char *pFont16;
extern int gdwFont16Width;
extern int gdwFont16Height;
extern void *pPcxFont16sImage;
extern void *pPcxFont16gImage;

extern unsigned char *pFont24;
extern int gdwFont24Width;
extern int gdwFont24Height;
extern void *pPcxFont24sImage;
extern void *pPcxFont24gImage;

extern unsigned char *pFont30;
extern int gdwFont30Width;
extern int gdwFont30Height;
extern void *pPcxFont30sImage;
extern void *pPcxFont30gImage;

extern unsigned char *pFont42;
extern int gdwFont42Width;
extern int gdwFont42Height;
extern void *pPcxFont42gImage;

extern void *pPcxLogoImage;
extern int gdwLogoWidth;
extern int gdwLogoHeight;
extern void *pPcxLogoSmImage;
extern int gdwLogoSmWidth;
extern int gdwLogoSmHeight;

extern void *pPcxTitleImage;
extern int gdwCursorHeight;
extern int gdwCursorWidth;
extern void *pPcxCursorImage;
extern int gdwHeroHeight;
extern int gdwHeroWidth;
extern void *pPcxHeroImage;
extern int gdwSHeroHeight;
extern int gdwSHeroWidth;
extern void *pPcxSHeroImage;
extern void *pMedTextCels;

extern int SelectedItem;
extern int SelectedItemMax;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TotalPlayers;

extern void *MenuPentegram16;
extern void *MenuPentegram;
extern void *MenuPentegram42;

extern char HeroUndecidedName[17];
extern int MenuItem[10];
extern int PreviousItem[10];
extern int submenu;

typedef enum TXT_JUST {
	JustLeft = 0,
	JustCentre = 1,
	JustRight = 2,
} TXT_JUST;

bool IsInsideRect(const SDL_Event *event, const SDL_Rect *rect);
bool LoadArtImage(char *pszFile, void **pBuffer, int frames, DWORD *data, PALETTEENTRY *pPalette = NULL);
bool UiFadeIn(int steps = 10);
bool UiFadeOut(int steps = 5);
int GetAnimationFrame(int frames, int fps = 60);
int GetCenterOffset(int w, int bw = 0);
void DrawArtImage(int SX, int SY, int SW, int SH, int nFrame, void *pBuffer, BYTE *bMask = NULL);
void DrawMouse();
void DrawSelector16(int x, int y, int width, int padding, int spacing);
void DrawSelector(int x, int y, int width, int padding, int spacing);
void DrawSelector42(int x, int y, int width, int padding, int spacing);
void FreeMenuItems();
void LoadHeroStats();
void LoadTitelArt(char *pszFile);
void PrintText16Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void PrintText16Silver(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void PrintText24Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void PrintText24Silver(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void PrintText30Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void PrintText30Silver(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void PrintText42Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0);
void RenderDiabloLogo();
void RenderDiabloLogoSm();
void SdlDiabloMainWindow();
void SetMenu(int MenuId);

