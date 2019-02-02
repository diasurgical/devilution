#include "../../types.h"

int selhero_SaveCount = 0;
_uiheroinfo heros[MAX_CHARACTERS];
_uiheroinfo heroInfo;

static std::vector<_uiheroinfo> hero_infos;

static BOOL __stdcall ui_add_hero_info(_uiheroinfo *info)
{
	hero_infos.emplace_back(*info);
	return TRUE;
}

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

	PrintText16Silver(31, 323, "Level:", JustRight, 118);
	PrintText16Silver(149, 323, lvl, JustCentre, 61);
	PrintText16Silver(31, 358, "Strength:", JustRight, 118);
	PrintText16Silver(149, 358, str, JustCentre, 61);
	PrintText16Silver(31, 380, "Magic:", JustRight, 118);
	PrintText16Silver(149, 380, mag, JustCentre, 61);
	PrintText16Silver(31, 401, "Dexterity:", JustRight, 118);
	PrintText16Silver(149, 401, dex, JustCentre, 61);
	PrintText16Silver(31, 422, "Vitality:", JustRight, 118);
	PrintText16Silver(149, 422, vit, JustCentre, 61);
}

void selhero_Render()
{
	heroInfo.heroclass = UI_NUM_CLASSES;
	if (SelectedItem <= selhero_SaveCount) {
		memcpy(&heroInfo, &heros[SelectedItem - 1], sizeof(heroInfo));
	}

	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	PrintText30Silver(-1, 161, "Single Player Characters", JustCentre);

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, heroInfo.heroclass, pPcxHeroImage);
	RenderStats();

	int w = 369;
	int x = 241;

	PrintText30Silver(x - 1, 211, "Select Hero", JustCentre, w);

	int selectorTop = 256;
	int y = selectorTop;
	for (int i = 0; i < selhero_SaveCount; i++) {
		PrintText24Gold(x - 1, y, heros[i].name, JustCentre, w);
		y += 26;
	}
	PrintText24Gold(x - 1, y, "New Hero", JustCentre, w);

	DrawSelector16(x, selectorTop + 3, w, 32, 26);

	PrintText30Gold(279, 429, "OK");
	PrintText30Gold(378, 429, "Delete");
	PrintText30Gold(501, 429, "Cancel");
}

void selhero_Render_DifficultySelection()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, heroInfo.heroclass, pPcxHeroImage);
	RenderStats();

	char *GameOptions[3] = { "Normal", "Nightmare", "Hell" };

	// this should not be hard coded.
	int x = 280;
	int y = 256;

	for (int i = 0; i < 3; i++) {
		y += 40;
		PrintText16Silver(x, y, GameOptions[i]);
	}
}

void selhero_Render_GameType()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, heroInfo.heroclass, pPcxHeroImage);
	RenderStats();

	char *GameOptions[2] = { "New Game", "Load Game" };

	// this should not be hard coded.
	int x = 280;
	int y = 256;

	for (int i = 0; i < 2; i++) {
		y += 40;
		PrintText16Silver(x, y, GameOptions[i]);
	}
}

void selhero_Render_Name()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, heroInfo.heroclass, pPcxHeroImage);
	RenderStats();

	PrintText30Silver(-1, 161, "New Single Player Hero", JustCentre);

	int w = 369;
	int x = 241;
	int y = 318;

	PrintText30Silver(x - 1, 211, "Enter Name", JustCentre, w);

	DrawSelector(x, y - 2, w, 39, 26);

	char lable[16];
	strcpy(lable, heroInfo.name);
	if (GetAnimationFrame(2, 500)) {
		lable[strlen(lable)] = '|';
	}

	PrintText24Gold(x + 67, y, lable); // todo add blinking "|"

	PrintText30Gold(329, 429, "OK");
	PrintText30Gold(451, 429, "Cancel");
}

// Have this load the function above and then render it in the main menu.
// Cnacel box is also needed.
void selhero_Render_ClassSelector()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, heroInfo.heroclass, pPcxHeroImage);
	RenderStats();

	PrintText30Silver(-1, 161, "New Single Player Hero", JustCentre);

	int w = 369;
	int x = 241;
	int y = 285;

	PrintText30Silver(x - 1, 211, "Choose Class", JustCentre, w);

	char *heroclasses[3] = { "Warrior", "Rogue", "Sorcerer" };

	int selectorTop = y;

	for (int i = 0; i < 3; i++) {
		if (i > 1) {
			y += 1; // "Rouge" and "Sorcerer" has a smaller gap then other items
		}
		PrintText24Gold(x - 1, y, heroclasses[i], JustCentre, w);
		y += 33;
	}

	if (SelectedItem > 1) {
		selectorTop += 1; // "Rouge" and "Sorcerer" has a smaller gap then other items
	}

	DrawSelector(x, selectorTop - 2, w, 39, 33);

	PrintText30Gold(329, 429, "OK");
	PrintText30Gold(451, 429, "Cancel");
}

BOOL __stdcall SelHero_GetHeroInfo(_uiheroinfo *pInfo)
{
	heros[selhero_SaveCount] = *pInfo;
	selhero_SaveCount++;

	return TRUE;
}

void selhero_Loade(BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)))
{
	LoadTitelArt("ui_art\\selhero.pcx");

	hero_infos.clear();
	fninfo(ui_add_hero_info);

	selhero_SaveCount = 0;
	fninfo(SelHero_GetHeroInfo);

	//memset(heroInfo, 0, sizeof(_uiheroinfo));
	heroInfo.heroclass = UI_NUM_CLASSES;
}

void selhero_Free()
{
	mem_free_dbg(pPcxTitleImage);
	pPcxTitleImage = NULL;
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
						heroInfo.name[nameLen-1] = '\0';
					}
					break;
				case SDLK_UP:
					SelectedItem--;
					if (SelectedItem < 1) {
						SelectedItem = SelectedItemMax ? SelectedItemMax : 1;
					}
					effects_play_sound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_DOWN:
					SelectedItem++;
					if (SelectedItem > SelectedItemMax) {
						SelectedItem = 1;
					}
					effects_play_sound("sfx\\items\\titlemov.wav");
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
					if (int(letter) > 96 && int(letter) < 123 || int(letter) == 32)
						nameLen = strlen(heroInfo.name);
						if (nameLen < 15) {
							heroInfo.name[nameLen] = letter;
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
    int *hero_is_created,
    char *name)
{
	selhero_Loade(fninfo);

	DUMMY();
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
					return TRUE;
				case SDLK_UP:
					SelectedItem--;
					if (SelectedItem < 1) {
						SelectedItem = SelectedItemMax ? SelectedItemMax : 1;
					}
					effects_play_sound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_DOWN:
					SelectedItem++;
					if (SelectedItem > SelectedItemMax) {
						SelectedItem = 1;
					}
					effects_play_sound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					switch (submenu) {
					case MULTIPLAYER_LOBBY:
						SetMenu(MULTIPLAYER_DIFFICULTY);
						break;
					case MULTIPLAYER_DIFFICULTY:
						strcpy(heroInfo.name, "testname");
						strcpy(name, heroInfo.name);
						if (!heroInfo.hassaved) {
							fncreate(&heroInfo);
						}
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
