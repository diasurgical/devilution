#include "../../types.h"

int selhero_SaveCount = 0;
_uiheroinfo heros[MAX_CHARACTERS];
_uiheroinfo heroInfo;

void RenderStats()
{
	char lvl[3] = "--";
	char str[3] = "--";
	char mag[3] = "--";
	char dex[3] = "--";
	char vit[3] = "--";

	if (heroInfo.heroclass != UI_NUM_CLASSES) {
		sprintf(lvl, "%d", heroInfo.level);
		sprintf(str, "%d", heroInfo.strength);
		sprintf(mag, "%d", heroInfo.magic);
		sprintf(dex, "%d", heroInfo.dexterity);
		sprintf(vit, "%d", heroInfo.vitality);
	}

	DrawArtStr(31, 323, AFT_SMALL, AFC_SILVER, "Level:", JustRight, 118);
	DrawArtStr(149, 323, AFT_SMALL, AFC_SILVER, lvl, JustCentre, 61);
	DrawArtStr(31, 358, AFT_SMALL, AFC_SILVER, "Strength:", JustRight, 118);
	DrawArtStr(149, 358, AFT_SMALL, AFC_SILVER, str, JustCentre, 61);
	DrawArtStr(31, 380, AFT_SMALL, AFC_SILVER, "Magic:", JustRight, 118);
	DrawArtStr(149, 380, AFT_SMALL, AFC_SILVER, mag, JustCentre, 61);
	DrawArtStr(31, 401, AFT_SMALL, AFC_SILVER, "Dexterity:", JustRight, 118);
	DrawArtStr(149, 401, AFT_SMALL, AFC_SILVER, dex, JustCentre, 61);
	DrawArtStr(31, 422, AFT_SMALL, AFC_SILVER, "Vitality:", JustRight, 118);
	DrawArtStr(149, 422, AFT_SMALL, AFC_SILVER, vit, JustCentre, 61);
}

void selhero_Render()
{
	heroInfo.heroclass = UI_NUM_CLASSES;
	if (SelectedItem <= selhero_SaveCount) {
		memcpy(&heroInfo, &heros[SelectedItem - 1], sizeof(heroInfo));
	}

	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, "Single Player Characters", JustCentre);

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	int w = 369;
	int x = 241;

	DrawArtStr(x - 1, 211, AFT_BIG, AFC_SILVER, "Select Hero", JustCentre, w);

	int selectorTop = 256;
	int y = selectorTop;
	for (int i = 0; i < selhero_SaveCount; i++) {
		DrawArtStr(x - 1, y, AFT_MED, AFC_GOLD, heros[i].name, JustCentre, w);
		y += 26;
	}
	DrawArtStr(x - 1, y, AFT_MED, AFC_GOLD, "New Hero", JustCentre, w);

	DrawSelector(x, selectorTop + 3, w, 32, 26, FOCUS_SMALL);

	DrawArtStr(279, 429, AFT_BIG, AFC_GOLD, "OK");
	DrawArtStr(378, 429, AFT_BIG, AFC_GOLD, "Delete");
	DrawArtStr(501, 429, AFT_BIG, AFC_GOLD, "Cancel");
}

void selhero_Render_DifficultySelection()
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	char *GameOptions[3] = { "Normal", "Nightmare", "Hell" };

	// this should not be hard coded.
	int x = 280;
	int y = 256;

	for (int i = 0; i < 3; i++) {
		y += 40;
		DrawArtStr(x, y, AFT_SMALL, AFC_SILVER, GameOptions[i]);
	}
}

void selhero_Render_GameType()
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	char *GameOptions[2] = { "New Game", "Load Game" };

	// this should not be hard coded.
	int x = 280;
	int y = 256;

	for (int i = 0; i < 2; i++) {
		y += 40;
		DrawArtStr(x, y, AFT_SMALL, AFC_SILVER, GameOptions[i]);
	}
}

void selhero_Render_Name()
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, "New Single Player Hero", JustCentre);

	int w = 369;
	int x = 241;
	int y = 318;

	DrawArtStr(x - 1, 211, AFT_BIG, AFC_SILVER, "Enter Name", JustCentre, w);

	DrawSelector(x, y - 2, w, 39, 26);

	char lable[16];
	strcpy(lable, heroInfo.name);
	if (GetAnimationFrame(2, 500)) {
		int len = strlen(lable);
		lable[len] = '|';
		lable[len + 1] = '\0';
	}

	DrawArtStr(x + 67, y, AFT_MED, AFC_GOLD, lable); // todo add blinking "|"

	DrawArtStr(329, 429, AFT_BIG, AFC_GOLD, "OK");
	DrawArtStr(451, 429, AFT_BIG, AFC_GOLD, "Cancel");
}

// Have this load the function above and then render it in the main menu.
// Cnacel box is also needed.
void selhero_Render_ClassSelector()
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, "New Single Player Hero", JustCentre);

	int w = 369;
	int x = 241;
	int y = 285;

	DrawArtStr(x - 1, 211, AFT_BIG, AFC_SILVER, "Choose Class", JustCentre, w);

	char *heroclasses[3] = { "Warrior", "Rogue", "Sorcerer" };

	int selectorTop = y;

	for (int i = 0; i < 3; i++) {
		if (i > 1) {
			y += 1; // "Rouge" and "Sorcerer" has a smaller gap then other items
		}
		DrawArtStr(x - 1, y, AFT_MED, AFC_GOLD, heroclasses[i], JustCentre, w);
		y += 33;
	}

	if (SelectedItem > 1) {
		selectorTop += 1; // "Rouge" and "Sorcerer" has a smaller gap then other items
	}

	DrawSelector(x, selectorTop - 2, w, 39, 33);

	DrawArtStr(329, 429, AFT_BIG, AFC_GOLD, "OK");
	DrawArtStr(451, 429, AFT_BIG, AFC_GOLD, "Cancel");
}

BOOL __stdcall SelHero_GetHeroInfo(_uiheroinfo *pInfo)
{
	heros[selhero_SaveCount] = *pInfo;
	selhero_SaveCount++;

	return TRUE;
}

void selhero_Loade(BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)))
{
	LoadBackgroundArt("ui_art\\selhero.pcx");

	selhero_SaveCount = 0;
	fninfo(SelHero_GetHeroInfo);

	heroInfo.heroclass = UI_NUM_CLASSES;
}

void selhero_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
}

void selhero_setDefaultStats(BOOL(__stdcall *fnstats)(unsigned int, _uidefaultstats *))
{
	_uidefaultstats defaults;
	fnstats(SelectedItem - 1, &defaults);

	heroInfo.heroclass = SelectedItem - 1;
	heroInfo.strength = defaults.strength;
	heroInfo.magic = defaults.magic;
	heroInfo.dexterity = defaults.dexterity;
	heroInfo.vitality = defaults.vitality;
}

BOOL __stdcall UiSelHeroSingDialog(
    BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)),
    BOOL(__stdcall *fncreate)(_uiheroinfo *),
    BOOL(__stdcall *fnremove)(_uiheroinfo *),
    BOOL(__stdcall *fnstats)(unsigned int, _uidefaultstats *),
    int *dlgresult,
    char *name,
    int *difficulty)
{
	selhero_Loade(fninfo);
	MenuItem[SINGLEPLAYER_LOAD] = 1 + selhero_SaveCount;

	submenu = SINGLEPLAYER_LOAD;
	if (!selhero_SaveCount) {
		PreviousItem[SINGLEPLAYER_CLASSES] = 0;
		submenu = SINGLEPLAYER_CLASSES;
	}

	SelectedItem = 1;
	SelectedItemMax = MenuItem[submenu];

	int nameLen;
	SDL_Event event;
	int x, y;

	*difficulty = gnDifficulty; // BUGFIX this replicates a bug that allowed setting deficulity in SP

	bool endMenu = false;
	while (!endMenu) {
		CapFPS();

		switch (submenu) {
		case SINGLEPLAYER_LOAD:
			selhero_Render();
			break;
		case SINGLEPLAYER_CLASSES:
			selhero_setDefaultStats(fnstats);
			selhero_Render_ClassSelector();
			break;
		case SINGLEPLAYER_NAME:
			selhero_Render_Name();
			break;
		}

		DrawMouse();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					if (PreviousItem[submenu]) {
						SetMenu(PreviousItem[submenu]);
						break;
					}

					*dlgresult = EXIT_MENU;
					endMenu = true;
					break;
				case SDLK_BACKSPACE:
					nameLen = strlen(heroInfo.name);
					if (nameLen > 0) {
						heroInfo.name[nameLen - 1] = '\0';
					}
					break;
				case SDLK_UP:
					SelectedItem--;
					if (SelectedItem < 1) {
						SelectedItem = SelectedItemMax ? SelectedItemMax : 1;
					}
					UiPlayMoveSound();
					break;
				case SDLK_DOWN:
					SelectedItem++;
					if (SelectedItem > SelectedItemMax) {
						SelectedItem = 1;
					}
					UiPlayMoveSound();
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					switch (submenu) {
					case SINGLEPLAYER_LOAD:
						if (SelectedItem == SelectedItemMax) {
							memset(&heroInfo.name, 0, sizeof(heroInfo.name));
							SetMenu(SINGLEPLAYER_CLASSES);
							break;
						}

						strcpy(name, heroInfo.name);
						*dlgresult = LOAD_GAME;
						endMenu = true;
						break;
					case SINGLEPLAYER_CLASSES:
						SetMenu(SINGLEPLAYER_NAME);
						break;
					case SINGLEPLAYER_NAME:
						if (!heroInfo.hassaved) {
							fncreate(&heroInfo);
						}
						strcpy(name, heroInfo.name);
						endMenu = true;
						break;
					}
					break;
				default:
					if (submenu != SINGLEPLAYER_NAME) {
						break;
					}

					char letter = event.key.keysym.sym;
					if (int(letter) > 96 && int(letter) < 123 || int(letter) == 32) {
						nameLen = strlen(heroInfo.name);
						if (nameLen < 15) {
							heroInfo.name[nameLen] = letter;
						}
					}
					break;
				}
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}

	BlackPalette();
	selhero_Free();

	return TRUE;
}

BOOL __stdcall UiSelHeroMultDialog(
    BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)),
    BOOL(__stdcall *fncreate)(_uiheroinfo *),
    BOOL(__stdcall *fnremove)(_uiheroinfo *),
    BOOL(__stdcall *fnstats)(unsigned int, _uidefaultstats *),
    int *dlgresult,
    BOOL *hero_is_created,
    char *name)
{
	*hero_is_created = false;
	BOOL success = UiSelHeroSingDialog(fninfo, fncreate, fnremove, fnstats, dlgresult, name, &gnDifficulty);
	if (!success) {
		return FALSE;
	} else if (*dlgresult == EXIT_MENU) {
		return TRUE;
	}

	selhero_Loade(fninfo);

	submenu = MULTIPLAYER_LOBBY;

	SelectedItem = 1;
	SelectedItemMax = MenuItem[submenu];
	SDL_Event event;

	int endMenu = false;
	while (endMenu == false) {
		CapFPS();

		switch (submenu) {
		case MULTIPLAYER_LOBBY:
			selhero_Render_GameType();
			break;
		case MULTIPLAYER_DIFFICULTY:
			selhero_Render_DifficultySelection();
			break;
		}

		DrawMouse();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					if (PreviousItem[submenu]) {
						SetMenu(PreviousItem[submenu]);
						break;
					}

					*dlgresult = EXIT_MENU;
					endMenu = true;
				case SDLK_UP:
					SelectedItem--;
					if (SelectedItem < 1) {
						SelectedItem = SelectedItemMax ? SelectedItemMax : 1;
					}
					UiPlayMoveSound();
					break;
				case SDLK_DOWN:
					SelectedItem++;
					if (SelectedItem > SelectedItemMax) {
						SelectedItem = 1;
					}
					UiPlayMoveSound();
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					switch (submenu) {
					case MULTIPLAYER_LOBBY:
						SetMenu(MULTIPLAYER_DIFFICULTY);
						break;
					case MULTIPLAYER_DIFFICULTY:
						strcpy(name, heroInfo.name);
						*dlgresult = NEW_GAME;
						endMenu = true;
						break;
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_Rect CreateHeroCancelBox;
					CreateHeroCancelBox.y = 550;
					CreateHeroCancelBox.x = 675;
					CreateHeroCancelBox.w = 100;
					CreateHeroCancelBox.h = 30;

					switch (submenu) {
					case MULTIPLAYER_DIFFICULTY:
						SDL_Rect NormalSelectBox;
						NormalSelectBox.x = 280;
						NormalSelectBox.y = 350;
						NormalSelectBox.w = 300;
						NormalSelectBox.h = 30;

						if (IsInsideRect(&event, &NormalSelectBox)) {
							strcpy(name, heroInfo.name);
							gnDifficulty = DIFF_NORMAL;
							*dlgresult = LOAD_GAME;
						}
						break;
					}
				}
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}

	BlackPalette();
	selhero_Free();

	return TRUE;
}
