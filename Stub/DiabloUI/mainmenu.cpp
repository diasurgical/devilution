#include "../../types.h"

int MainMenuResult;

void UiMainMenuSelect(int value)
{
	MainMenuResult = value;
}

void mainmenu_Load()
{
	MainMenuResult = 0;
	UiInitList(MAINMENU_SINGLE_PLAYER, MAINMENU_EXIT_DIABLO, NULL, UiMainMenuSelect);

	char *pszFile = "ui_art\\mainmenu.pcx";
	if (false) //DiabloUI_GetSpawned()
		pszFile = "ui_art\\swmmenu.pcx";

	LoadBackgroundArt(pszFile);
}

void mainmenu_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
}

bool UiMainMenuEvent(SDL_Event *event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		if (UiFocusNavigation(event, true))
			return true;
		if (event->key.keysym.sym == SDLK_ESCAPE) {
			UiMainMenuSelect(MAINMENU_EXIT_DIABLO);
			return true;
		}
		break;
	case SDL_QUIT:
		exit(0);
	}

	return false;
}

BOOL __stdcall UiMainMenuDialog(char *name, int *pdwResult, void(__stdcall *fnSound)(char *file), int a4)
{
	SDL_Event event;

	UI_Item MAINMENU_DIALOG[] = {
		{ { 0, 0, 640, 480 }, UI_IMAGE, 0, 0, NULL, &ArtBackground },
		{ { 64, 192, 510, 43 }, UI_LIST, UIS_HUGE | UIS_GOLD | UIS_CENTER, MAINMENU_SINGLE_PLAYER, "Single Player" },
		{ { 64, 235, 510, 43 }, UI_LIST, UIS_HUGE | UIS_GOLD | UIS_CENTER, MAINMENU_MULTIPLAYER, "Multi Player" },
		{ { 64, 277, 510, 43 }, UI_LIST, UIS_HUGE | UIS_GOLD | UIS_CENTER, MAINMENU_REPLAY_INTRO, "Replay Intro" },
		{ { 64, 320, 510, 43 }, UI_LIST, UIS_HUGE | UIS_GOLD | UIS_CENTER, MAINMENU_SHOW_CREDITS, "Show Credits" },
		{ { 64, 363, 510, 43 }, UI_LIST, UIS_HUGE | UIS_GOLD | UIS_CENTER, MAINMENU_EXIT_DIABLO, "Exit Diablo" },
		{ { 17, 444, 605, 21 }, UI_TEXT, UIS_SMALL, 0, name },
	};

	gfnSoundFunction = fnSound;
	mainmenu_Load();

	while (MainMenuResult == 0) {
		UiRenderItems(MAINMENU_DIALOG, size(MAINMENU_DIALOG));
		DrawLogo();
		DrawMouse();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			if (UiMainMenuEvent(&event))
				continue;
			UiItemMouseEvents(&event, MAINMENU_DIALOG, size(MAINMENU_DIALOG));
		}
	}

	BlackPalette();
	mainmenu_Free();

	*pdwResult = MainMenuResult;
	return TRUE;
}
