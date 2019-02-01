#include "../../types.h"

void title_Render()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);

	PrintText24Silver(-1, 410, "Copyright \xA9 1996-2001 Blizzard Entertainment", JustCentre);
	RenderDiabloLogo();
}

void title_Loade()
{
	LoadTitelArt("ui_art\\title.pcx");
}

void title_Free()
{
	mem_free_dbg(pPcxTitleImage);
	pPcxTitleImage = NULL;
}

BOOL __stdcall UiTitleDialog(int a1)
{
	title_Loade();

	bool endMenu = false;
	int timeOut = SDL_GetTicks() + 7000;

	SDL_Event event;
	while (!endMenu && SDL_GetTicks() < timeOut) {
		CapFPS();
		title_Render();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN: // all except arrow
			case SDL_MOUSEBUTTONDOWN:
				endMenu = true;
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}
	BlackPalette();

	title_Free();

	return TRUE;
}
