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

	SDL_Event event;
	while (1) {
		title_Render();

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_MOUSEBUTTONDOWN:
				endMenu = true;
				break;
			case SDL_QUIT:
				exit(0);
			}
		}

		if (!endMenu) {
			UiFadeIn();
		} else if (UiFadeOut()) {
			break;
		}
	}

	title_Free();

	return TRUE;
}
