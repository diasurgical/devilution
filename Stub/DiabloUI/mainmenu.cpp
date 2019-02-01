#include "../../types.h"

void mainmenu_Render(char *name)
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);

	// scrollrt_draw_cursor_back_buffer(); // Doesn't work?

	RenderDiabloLogoSm();

	int menuTop = 192;
	char *MENIITEMS[5] = { "Single Player", "Multi Player", "Replay Intro", "Show Credits", "Exit Diablo" };

	for (int i = 0; i < 5; i++) {
		int y = menuTop + i * 43;
		if (i > 1) {
			y -= 1; // "Multi Player" and "Replay Intro" has a smaller gap then other items
		}
		PrintText42Gold(-1, y, MENIITEMS[i], 1);
	}

	int selectorTop = menuTop;
	if (SelectedItem > 2) {
		selectorTop -= 1; // "Multi Player" and "Replay Intro" has a smaller gap then other items
	}

	DrawSelector42(0, selectorTop, 0, 85, 43);

	PrintText16Silver(17, 444, name);
}

void mainmenu_Loade()
{
	char *pszFile = "ui_art\\mainmenu.pcx";
	if (false) //DiabloUI_GetSpawned()
		pszFile = "ui_art\\swmmenu.pcx";
	LoadTitelArt(pszFile);
}

void mainmenu_Free()
{
	mem_free_dbg(pPcxTitleImage);
	pPcxTitleImage = NULL;
}

BOOL __stdcall UiMainMenuDialog(char *name, int *pdwResult, void(__stdcall *fnSound)(char *file), int a4)
{
	mainmenu_Loade();

	SelectedItem = 1;
	SelectedItemMax = 5;
	SDL_Event event;

	int ItemHeight = 42;
	SDL_Rect SinglePlayer = { 0, 191, 515, ItemHeight };
	SinglePlayer.x = GetCenterOffset(SinglePlayer.w);
	SDL_Rect MultiPlayer = SinglePlayer;
	MultiPlayer.y += ItemHeight * 1 + 1;
	SDL_Rect ReplayIntro = MultiPlayer;
	ReplayIntro.y += ItemHeight * 2 + 0;
	SDL_Rect ShowCredits = ReplayIntro;
	ShowCredits.y += ItemHeight * 3 + 1;
	SDL_Rect ExitDiablo = ShowCredits;
	ExitDiablo.y += ItemHeight * 4 + 1;

	bool endMenu = false;

	while (!endMenu) {
		CapFPS();
		mainmenu_Render(name);
		DrawMouse();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					SelectedItem--;
					if (SelectedItem < MAINMENU_SINGLE_PLAYER) {
						SelectedItem = SelectedItemMax;
					}
					fnSound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_DOWN:
					SelectedItem++;
					if (SelectedItem > SelectedItemMax) {
						SelectedItem = MAINMENU_SINGLE_PLAYER;
					}
					fnSound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_ESCAPE:
					*pdwResult = MAINMENU_EXIT_DIABLO;
					fnSound("sfx\\items\\titlslct.wav");
					Sleep(250); // Wait for soudn to play
					endMenu = true;
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					switch (SelectedItem) {
					case MAINMENU_SINGLE_PLAYER:
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_SINGLE_PLAYER;
						endMenu = true;
						break;
					case MAINMENU_MULTIPLAYER:
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_MULTIPLAYER;
						endMenu = true;
						break;
					case MAINMENU_REPLAY_INTRO:
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_REPLAY_INTRO;
						endMenu = true;
						break;
					case MAINMENU_SHOW_CREDITS:
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_SHOW_CREDITS;
						endMenu = true;
						break;
					case MAINMENU_EXIT_DIABLO:
						fnSound("sfx\\items\\titlslct.wav");
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
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_SINGLE_PLAYER;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &MultiPlayer)) {
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_MULTIPLAYER;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &ReplayIntro)) {
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_REPLAY_INTRO;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &ShowCredits)) {
						fnSound("sfx\\items\\titlslct.wav");
						*pdwResult = MAINMENU_SHOW_CREDITS;
						endMenu = true;
						break;
					} else if (IsInsideRect(&event, &ExitDiablo)) {
						fnSound("sfx\\items\\titlslct.wav");
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
