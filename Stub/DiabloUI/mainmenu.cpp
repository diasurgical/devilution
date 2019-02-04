#include "../../types.h"

void mainmenu_Render(char *name)
{
	DrawArt(0, 0, &ArtBackground);

	DrawLogo();

	int menuTop = 192;
	char *MENIITEMS[5] = { "Single Player", "Multi Player", "Replay Intro", "Show Credits", "Exit Diablo" };

	int spacing = 43;
	for (int i = 0; i < 5; i++) {
		int y = menuTop + i * spacing;
		DrawArtStr(0, y, AFT_HUGE, AFC_GOLD, MENIITEMS[i], 1);
	}

	DrawSelector(0, menuTop, 0, 65, spacing, FOCUS_BIG);

	DrawArtStr(17, 444, AFT_SMALL, AFC_SILVER, name);
}

void mainmenu_Load()
{
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

BOOL __stdcall UiMainMenuDialog(char *name, int *pdwResult, void(__stdcall *fnSound)(char *file), int a4)
{
	gfnSoundFunction = fnSound;
	mainmenu_Load();

	SelectedItem = 1;
	SelectedItemMax = 5;
	SDL_Event event;

	int ItemHeight = 43;
	SDL_Rect SinglePlayer = { 0, 191, 515, ItemHeight };
	SinglePlayer.x = GetCenterOffset(SinglePlayer.w);
	SDL_Rect MultiPlayer = SinglePlayer;
	MultiPlayer.y += ItemHeight * 1;
	SDL_Rect ReplayIntro = MultiPlayer;
	ReplayIntro.y += ItemHeight * 2;
	SDL_Rect ShowCredits = ReplayIntro;
	ShowCredits.y += ItemHeight * 3;
	SDL_Rect ExitDiablo = ShowCredits;
	ExitDiablo.y += ItemHeight * 4;

	bool endMenu = false;

	while (!endMenu) {
		CapFPS();
		mainmenu_Render(name);
		DrawMouse();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (UiFocuseNavigation(&event, true))
					break;
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					*pdwResult = MAINMENU_EXIT_DIABLO;
					UiPlaySelectSound();
					Sleep(250); // Wait for soudn to play
					endMenu = true;
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					switch (SelectedItem) {
					case MAINMENU_SINGLE_PLAYER:
						UiPlaySelectSound();
						*pdwResult = MAINMENU_SINGLE_PLAYER;
						endMenu = true;
						break;
					case MAINMENU_MULTIPLAYER:
						UiPlaySelectSound();
						*pdwResult = MAINMENU_MULTIPLAYER;
						endMenu = true;
						break;
					case MAINMENU_REPLAY_INTRO:
						UiPlaySelectSound();
						*pdwResult = MAINMENU_REPLAY_INTRO;
						endMenu = true;
						break;
					case MAINMENU_SHOW_CREDITS:
						UiPlaySelectSound();
						*pdwResult = MAINMENU_SHOW_CREDITS;
						endMenu = true;
						break;
					case MAINMENU_EXIT_DIABLO:
						UiPlaySelectSound();
						Sleep(250); // Wait for sound to play
						*pdwResult = MAINMENU_EXIT_DIABLO;
						endMenu = true;
						break;
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (IsInsideRect(&event, &SinglePlayer)) {
						UiPlaySelectSound();
						*pdwResult = MAINMENU_SINGLE_PLAYER;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &MultiPlayer)) {
						UiPlaySelectSound();
						*pdwResult = MAINMENU_MULTIPLAYER;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &ReplayIntro)) {
						UiPlaySelectSound();
						*pdwResult = MAINMENU_REPLAY_INTRO;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &ShowCredits)) {
						UiPlaySelectSound();
						*pdwResult = MAINMENU_SHOW_CREDITS;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &ExitDiablo)) {
						UiPlaySelectSound();
						Sleep(250); // Wait for soudn to play
						*pdwResult = MAINMENU_EXIT_DIABLO;
						endMenu = true;
						break;
					}
				}
				break;
			case SDL_QUIT:
				*pdwResult = MAINMENU_EXIT_DIABLO;
				endMenu = true;
				break;
			}
		}
	}

	BlackPalette();

	mainmenu_Free();

	return TRUE;
}
