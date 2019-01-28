#pragma once

#include "miniwin.h"

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

extern int gdwTitleWidth;
extern int gdwTitleHeight;
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

extern int fadeValue;
extern int lineCount;
extern int creditline;
extern BOOL nottheend;
extern int lastYbase;

extern bool TitleImageLoaded;
extern int SelectedItem;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TotalPlayers;

extern void *MenuPentegram16;
extern void *MenuPentegram;
extern void *MenuPentegram42;

extern char HeroUndecidedName[17];

void SdlDiabloMainWindow();
void RenderDiabloSplashPage();
void RenderDiabloMainPage(char *name);
void RenderDiabloSinglePlayerPage();
BOOL ShowCredts();
void FreeMenuItems();
BOOL LoadArtImage(char *pszFile, void **pBuffer, int frames, DWORD *data);
void CreateHeroMenu();
void RenderUndecidedHeroName(int HeroClass);
void LoadHeroStats();
void DrawPreGameOptions(int HeroClass, int ShowClasses);
void DrawPreGameDifficultySelection(int HeroClass, int ShowClasses);
void DrawSelMultiConnection();
int GetCenterOffset(int w, int bw = 0);
