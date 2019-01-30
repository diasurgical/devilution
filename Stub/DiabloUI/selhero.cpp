#include "../../types.h"

int HeroChosen = 0;
bool StartNewGame = false;
bool timestart = false;
bool CreateSinglePlayerChar = false;
char chr_name_str[16];
int NewHeroNameIndex = 0;

static std::vector<_uiheroinfo> hero_infos;

static BOOL __stdcall ui_add_hero_info(_uiheroinfo *info)
{
	hero_infos.emplace_back(*info);
	return TRUE;
}

void RenderStats(char *lvl, char *str, char *mag, char *dex, char *vit)
{
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

void RenderDefaultStats(int HeroClass)
{
	switch (HeroClass) {
	case UI_WARRIOR:
		RenderStats("1", "30", "10", "20", "25");
		break;
	case UI_ROGUE:
		RenderStats("1", "20", "15", "30", "20");
		break;
	case UI_SORCERER:
		RenderStats("1", "15", "35", "15", "20");
		break;
	}
}

void selhero_Render()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, 3, pPcxHeroImage);

	PrintText30Silver(-1, 161, "Single Player Characters", JustCentre);

	int w = 369;
	int x = 241;

	PrintText30Silver(x - 1, 211, "Select Hero", JustCentre, w);

	int selectorTop = 256;
	int y = selectorTop;
	for (int i = 0; i < 0; i++) {
		PrintText24Gold(x - 1, y, "Hero name", JustCentre, w);
		y += 26;
	}
	PrintText24Gold(x - 1, y, "New Hero", JustCentre, w);

	DrawSelector16(x, selectorTop + 3, w, 32, 26);

	RenderStats("-", "-", "-", "-", "-");

	PrintText30Gold(279, 429, "OK");
	PrintText30Gold(378, 429, "Delete");
	PrintText30Gold(501, 429, "Cancel");
}

void selhero_Render_DifficultySelection(int HeroClass, int ShowClasses)
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, 0, pPcxHeroImage);

	RenderStats("1", "30", "10", "20", "25");

	char *GameOptions[3] = { "Normal", "Nightmare", "Hell" };

	// this should not be hard coded.
	int x = 280;
	int y = 256;
	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, HeroClass, pPcxHeroImage);

	if (ShowClasses == 1) {
		for (int i = 0; i < 3; i++) {
			y += 40;
			PrintText16Silver(x, y, GameOptions[i]);
		}
	}

	RenderDefaultStats(HeroClass);
}

void DrawPreGameOptions(int HeroClass, int ShowClasses)
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, 0, pPcxHeroImage);

	char *GameOptions[2] = { "New Game", "Load Game" };

	// this should not be hard coded.
	int x = 280;
	int y = 256;

	if (ShowClasses == 1) {
		for (int i = 0; i < 2; i++) {
			y += 40;
			PrintText16Silver(x, y, GameOptions[i]);
		}
	}

	RenderDefaultStats(HeroClass);
}

void selhero_Render_Name(int HeroClass)
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, HeroClass, pPcxHeroImage);

	PrintText30Silver(-1, 161, "New Single Player Hero", JustCentre);

	int w = 369;
	int x = 241;
	int y = 318;

	PrintText30Silver(x - 1, 211, "Enter Name", JustCentre, w);

	RenderDefaultStats(HeroClass);

	DrawSelector(x, y - 2, w, 39, 26);
	PrintText24Gold(x + 67, y, (char *)HeroUndecidedName); // todo add blinking "|"

	PrintText30Gold(329, 429, "OK");
	PrintText30Gold(451, 429, "Cancel");
}

// Have this load the function above and then render it in the main menu.
// Cnacel box is also needed.
void selhero_Render_ClassSelector()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	DrawArtImage(30, 211, gdwHeroWidth, gdwHeroHeight, SelectedItem - 1, pPcxHeroImage);

	PrintText30Silver(-1, 161, "New Single Player Hero", JustCentre);

	int w = 369;
	int x = 241;
	int y = 285;

	PrintText30Silver(x - 1, 211, "Choose Class", JustCentre, w);

	RenderDefaultStats(SelectedItem - 1);

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

void selhero_Loade()
{
	LoadTitelArt("ui_art\\selhero.pcx");
}

void selhero_Free()
{
	mem_free_dbg(pPcxTitleImage);
	pPcxTitleImage = NULL;
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
	selhero_Loade();

	bool endMenu = false;

	submenu = SINGLEPLAYER_LOAD;
	if (!TotalPlayers) {
		PreviousItem[SINGLEPLAYER_CLASSES] = 0;
		submenu = SINGLEPLAYER_CLASSES;
	}

	SelectedItem = 1;
	SelectedItemMax = MenuItem[submenu];
	SDL_Event event;
	int x, y;

	bool done = false;
	while (done == false) {
		switch (submenu) {
		case SINGLEPLAYER_LOAD:
			selhero_Render();
			break;
		case SINGLEPLAYER_CLASSES:
			selhero_Render_ClassSelector();
			break;
		case SINGLEPLAYER_NAME:
			selhero_Render_Name(HeroChosen);
			break;
		}

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					if (PreviousItem[submenu]) {
						SetMenu(PreviousItem[submenu]);
						break;
					}

					*dlgresult = 4;
					endMenu = true;
					break;
				case SDLK_BACKSPACE:
					if (NewHeroNameIndex > 0) {
						HeroUndecidedName[NewHeroNameIndex - 1] = 0;
						NewHeroNameIndex--;
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
							SetMenu(SINGLEPLAYER_CLASSES);
						}
						break;
					case SINGLEPLAYER_CLASSES:
						HeroChosen = SelectedItem - 1;
						for (int i = 0; i < 17; i++)
							HeroUndecidedName[i] = 0;
						NewHeroNameIndex = 0;
						SetMenu(SINGLEPLAYER_NAME);
						break;
					case SINGLEPLAYER_NAME:
						CreateSinglePlayerChar = 1;
						const char *test_name = HeroUndecidedName;
						done = true;
						break;
					}
					break;
				default:
					if (submenu != SINGLEPLAYER_NAME) {
						break;
					}

					char letter = event.key.keysym.sym;
					if (int(letter) > 96 && int(letter) < 123 || int(letter) == 32)

						if (NewHeroNameIndex < 17) {
							HeroUndecidedName[NewHeroNameIndex] = letter;
							NewHeroNameIndex++;
						}
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					x = event.button.x;
					y = event.button.y;
					printf("X %d , Y %d\n", x, y);

					SDL_Rect CreateHeroCancelBox;
					CreateHeroCancelBox.y = 550;
					CreateHeroCancelBox.x = 675;
					CreateHeroCancelBox.w = 100;
					CreateHeroCancelBox.h = 30;

					clock_t start, end;
					double cpu_time_used;

					switch (submenu) {
					case SINGLEPLAYER_NAME:
						if (IsInsideRect(&event, &CreateHeroCancelBox)) {
							memset(HeroUndecidedName, 0, 17);
							NewHeroNameIndex = 0;
							SetMenu(SINGLEPLAYER_CLASSES);
						}
						break;
					}
				}
				break;
			case SDL_QUIT:
				exit(0);
			}
		}

		DrawMouse();

		if (!endMenu) {
			UiFadeIn();
		} else if (UiFadeOut()) {
			break;
		}
	}

	if (*dlgresult != 4) {
		hero_infos.clear();
		fninfo(&ui_add_hero_info);

		if (CreateSinglePlayerChar) {
			const char *test_name = HeroUndecidedName;
			DUMMY_PRINT("create hero: %s", test_name);
			strcpy(name, test_name);

			_uiheroinfo hero_info = { 1 };
			strcpy(hero_info.name, test_name);
			hero_info.heroclass = HeroChosen;

			fncreate(&hero_info);
		} else {
			*difficulty = gnDifficulty; // BUGFIX this replicates a bug that allowed setting deficulity in SP
			printf("Difficulty : %d \n", *difficulty);

			const char *test_name = chr_name_str;
			if (!StartNewGame) {
				*dlgresult = 2; // This means load game
			}
			strcpy(name, test_name);
		}
	}

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
	selhero_Loade();

	DUMMY();
	submenu = MULTIPLAYER_LOBBY;

	SelectedItem = 1;
	SelectedItemMax = MenuItem[submenu];
	SDL_Event event;
	bool endMenu = false;

	int done = false;
	while (done == false) {
		switch (submenu) {
		case MULTIPLAYER_LOBBY:
			DrawPreGameOptions(HeroChosen, 1);
			break;
		case MULTIPLAYER_DIFFICULTY:
			selhero_Render_DifficultySelection(HeroChosen, 1);
			break;
		}

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					if (PreviousItem[submenu]) {
						SetMenu(PreviousItem[submenu]);
						break;
					}

					*dlgresult = 4;
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
						CreateSinglePlayerChar = 1;
						done = true;
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

					clock_t start, end;
					double cpu_time_used;

					switch (submenu) {
					case 5:
						if (timestart == 0) {
							start = clock();
							timestart = 1;
						}

						end = clock();

						cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

						printf("TIEM DELAY %f\n", cpu_time_used);

						SDL_Rect NewGameBox;
						NewGameBox.y = 350;
						NewGameBox.x = 280;
						NewGameBox.w = 300;
						NewGameBox.h = 30;

						SDL_Rect LoadGameBox;
						LoadGameBox.y = 392;
						LoadGameBox.x = 280;
						LoadGameBox.w = 300;
						LoadGameBox.h = 30;

						if (cpu_time_used > 0.5 && IsInsideRect(&event, &NewGameBox)) {
							printf(" New Game I was hit\n\n\n");
							SetMenu(MULTIPLAYER_DIFFICULTY);
							cpu_time_used = 0;
							timestart = 0;
							start = 0;
						} else if (cpu_time_used > 0.5 && IsInsideRect(&event, &LoadGameBox)) {

							printf(" Load Game I was hit\n\n\n");
							break;
						} else if (IsInsideRect(&event, &CreateHeroCancelBox)) {
							timestart = 0;
							cpu_time_used = 0;
							start = 0;
							end = 0;
							cpu_time_used = 0;

							SetMenu(SINGLEPLAYER_CLASSES); // TODO skip to main menu if no valid saves
						}
						break;
					case MULTIPLAYER_DIFFICULTY:
						if (timestart == 0) {
							start = clock();
							timestart = 1;
						}

						end = clock();
						cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

						SDL_Rect NormalSelectBox;
						NormalSelectBox.x = 280;
						NormalSelectBox.y = 350;
						NormalSelectBox.w = 300;
						NormalSelectBox.h = 30;

						SDL_Rect NightmareSelectBox;
						NightmareSelectBox.x = 280;
						NightmareSelectBox.y = 392;
						NightmareSelectBox.w = 300;
						NightmareSelectBox.h = 30;

						SDL_Rect HellSelectBox;
						HellSelectBox.x = 280;
						HellSelectBox.y = 428;
						HellSelectBox.w = 300;
						HellSelectBox.h = 30;

						if (cpu_time_used > 0.5 && IsInsideRect(&event, &NormalSelectBox)) {
							StartNewGame = 1;
							gnDifficulty = DIFF_NORMAL;
							break;
						} else if (cpu_time_used > 0.5 && IsInsideRect(&event, &NightmareSelectBox)) {
							StartNewGame = 1;
							gnDifficulty = DIFF_NIGHTMARE;
							break;
						} else if (cpu_time_used > 1 && IsInsideRect(&event, &HellSelectBox)) {
							gnDifficulty = DIFF_HELL;
							StartNewGame = 1;
							break;
						} else if (IsInsideRect(&event, &CreateHeroCancelBox)) {
							timestart = 0;
							cpu_time_used = 0;
							start = 0;
							end = 0;
							cpu_time_used = 0;

							printf("Cancel\n\n\n");
							SetMenu(MULTIPLAYER_LOBBY);
						}
						break;
					}
				}
				break;
			case SDL_QUIT:
				exit(0);
			}
		}

		DrawMouse();

		if (!endMenu) {
			UiFadeIn();
		} else if (UiFadeOut()) {
			break;
		}
	}

	hero_infos.clear();
	fninfo(&ui_add_hero_info);

	if (CreateSinglePlayerChar) {
		strcpy(name, "testname");
		DUMMY_PRINT("create hero: %s", name);

		_uiheroinfo hero_info = { 1 };
		strcpy(hero_info.name, name);
		hero_info.heroclass = HeroChosen;

		fncreate(&hero_info);
	}

	selhero_Free();

	return TRUE;
}
