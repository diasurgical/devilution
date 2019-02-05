#include "../../types.h"

void title_Render()
{
	DrawArt(0, 0, &ArtBackground);
	DrawArtStr(0, 409, AFT_MED, AFC_SILVER, "Copyright \xA9 1996-2001 Blizzard Entertainment", JustCentre);
	DrawLogo(182, LOGO_BIG);
}

void title_Load()
{
	LoadBackgroundArt("ui_art\\title.pcx");
	LoadMaskedArtFont("ui_art\\logo.pcx", &ArtLogos[LOGO_BIG], 15);
}

void title_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
	mem_free_dbg(ArtLogos[LOGO_BIG].data);
	ArtLogos[LOGO_BIG].data = NULL;
}

BOOL __stdcall UiTitleDialog(int a1)
{
	title_Load();

	bool endMenu = false;
	int timeOut = SDL_GetTicks() + 7000;

	SDL_Event event;
	while (!endMenu && SDL_GetTicks() < timeOut) {
		CapFPS();
		title_Render();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:/*
				if (event.key.keysym.sym == SDLK_UP
				    || event.key.keysym.sym == SDLK_UP
				    || event.key.keysym.sym == SDLK_LEFT
				    || event.key.keysym.sym == SDLK_RIGHT) {
					break;
				}*/
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
