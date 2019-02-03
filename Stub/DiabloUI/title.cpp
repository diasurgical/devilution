#include "../../types.h"

void title_Render()
{
	DrawArt(0, 0, &ArtBackground);

	DrawArtStr(-1, 410, AFT_MED, AFC_SILVER, "Copyright \xA9 1996-2001 Blizzard Entertainment", JustCentre);
	DrawLogo(182, LOGO_BIG);
}

void title_Loade()
{
	LoadBackgroundArt("ui_art\\title.pcx");
}

void title_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
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
