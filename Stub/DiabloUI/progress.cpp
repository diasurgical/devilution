#include "../../types.h"

void *pPcxSPopupImage;
void *pPcxProgBGImage;
void *pPcxProgFillImage;
void *pPcxSmlButImage;
int dwSmlButWidth, dwSmlButHeight;
SDL_Surface *msgSurface;
SDL_Surface *cancleSurface;
int w;

void progress_Loade(char *msg)
{
	DWORD dwData[2];

	LoadTitelArt("ui_art\\black.pcx");
	LoadArtImage("ui_art\\spopup.pcx", &pPcxSPopupImage, 1);
	LoadArtImage("ui_art\\prog_bg.pcx", &pPcxProgBGImage, 1);
	LoadArtImage("ui_art\\prog_fil.pcx", &pPcxProgFillImage, 1);
	LoadArtImage("ui_art\\but_sml.pcx", &pPcxSmlButImage, 15, dwData);
	dwSmlButWidth = dwData[0];
	dwSmlButHeight = dwData[1];

	if (font != NULL) {
		SDL_Color color = { 243, 243, 243 };

		msgSurface = TTF_RenderUTF8_Solid(font, msg, color);
		cancleSurface = TTF_RenderUTF8_Solid(font, "Cancel", color);
		TTF_SizeUTF8(font, "Cancel", &w, NULL);
	}
}

void progress_Free()
{
	mem_free_dbg(pPcxTitleImage);
	pPcxTitleImage = NULL;
	mem_free_dbg(pPcxSPopupImage);
	pPcxSPopupImage = NULL;
	mem_free_dbg(pPcxProgBGImage);
	pPcxProgBGImage = NULL;
	mem_free_dbg(pPcxProgFillImage);
	pPcxProgFillImage = NULL;
	mem_free_dbg(pPcxSmlButImage);
	pPcxSmlButImage = NULL;
	SDL_FreeSurface(msgSurface);
	msgSurface = NULL;
	SDL_FreeSurface(cancleSurface);
	cancleSurface = NULL;
}

void progress_Render(int progress)
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);

	int x = GetCenterOffset(280);
	int y = GetCenterOffset(144, SCREEN_HEIGHT);

	DrawArtImage(x, y, 284, 148, 0, pPcxSPopupImage);
	DrawArtImage(GetCenterOffset(228), y + 52, 232, 38, 0, pPcxProgBGImage, NULL, 228);
	if (progress) {
		DrawArtImage(GetCenterOffset(228), y + 52, 232, 38, 0, pPcxProgFillImage, NULL, 228 * progress / 100);
	}
	DrawArtImage(GetCenterOffset(dwSmlButWidth - 2), y + 99, dwSmlButWidth, dwSmlButHeight, 2, pPcxSmlButImage, NULL, dwSmlButWidth - 2);

	if (msgSurface) {
		SDL_Rect src_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_Rect dsc_rect = { 64 + x + 50, 160 + y + 8, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_BlitSurface(msgSurface, NULL, pal_surface, &dsc_rect);
		dsc_rect.x = 64 + GetCenterOffset(w) - 1;
		dsc_rect.y = 160 + y + 99 + 4;
		SDL_BlitSurface(cancleSurface, NULL, pal_surface, &dsc_rect);
	}
}

int __stdcall UiProgressDialog(HWND window, char *msg, int enable, int(__cdecl *fnfunc)(), int rate)
{
	progress_Loade(msg);

	bool endMenu = false;
	int progress = 0;

	SDL_Event event;
	while (!endMenu && progress < 100) {
		CapFPS();

		progress = fnfunc();

		progress_Render(progress);
		DrawMouse();
		SetFadeLevel(256);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_MOUSEBUTTONDOWN:
				endMenu = true;
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}
	BlackPalette();

	progress_Free();

	return progress == 100;
}
