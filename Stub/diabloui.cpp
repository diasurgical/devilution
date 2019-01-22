#include <vector>

#include "../types.h"
#include "sdlrender.h"
#include "stubs.h"

char chr_name_str[16];

int SelectedItem = 1;
int SelectedItemMax = 0;
int MenuItem[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PreviousItem[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int submenu = 0;

void __cdecl UiDestroy()
{
	DUMMY();
	FreeMenuItems();
}

BOOL __stdcall UiTitleDialog(int a1)
{
	TitleImageLoaded = false;
	SDL_Event event;
	while (1) {
		RenderDiabloSplashPage();

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_MOUSEBUTTONDOWN:
				return TRUE;
			case SDL_QUIT:
				SDL_Quit();
				exit(0);
			}
		}
	}

	return FALSE;
}

void LoadCharNamesintoMemory()
{
	PkPlayerStruct pkplr;
	HANDLE CharFile;
	char *p_hero_names = *hero_names; // Not sure if this is correct

	memset(hero_names, 0, 0x140u);

	for (int i = 0; i < MAX_CHARACTERS; i++) {
		CharFile = pfile_open_save_archive(NULL, i);
		if (CharFile) {
			if (pfile_read_hero(CharFile, &pkplr)) {
				strcpy(p_hero_names, pkplr.pName);
				UnPackPlayer(&pkplr, 0, 0);
				pfile_archive_contains_game(CharFile, 0); // FIXME: what is the second argument?
			}
			pfile_SFileCloseArchive(CharFile);
		}

		p_hero_names += 32;
	}

	// memcpy(shero_names, hero_names, sizeof(hero_names));
}

void SetMenu(int MenuId)
{
	effects_play_sound("sfx\\items\\titlslct.wav");

	void *tmp = pPcxTitleImage;
	pPcxTitleImage = NULL;
	mem_free_dbg(tmp);
	TitleImageLoaded = false;

	submenu = MenuId;
	SelectedItem = 1;
	SelectedItemMax = MenuItem[MenuId];
}

BOOL IsInside(int x, int y, int ItemLeft, int ItemTop, int ItemWidth, int ItemHeight)
{
	return x > ItemLeft && x < ItemLeft + ItemWidth && y > ItemTop && y < ItemTop + ItemHeight;
}

BOOL IsInsideRect(int x, int y, SDL_Rect rect)
{
	return IsInside(x, y, rect.x, rect.y, rect.w, rect.h);
}

void InitHiracy()
{
	MenuItem[SINGLEPLAYER_CLASSES] = 3;
	MenuItem[MULTIPLAYER_CONNECTIONS] = 4;
	MenuItem[MULTIPLAYER_LOBBY] = 2;
	MenuItem[MULTIPLAYER_DIFFICULTY] = 3;
	MenuItem[MULTIPLAYER_BNET_GATEWAYS] = 3;

	PreviousItem[SINGLEPLAYER_CLASSES] = SINGLEPLAYER_LOAD;
	PreviousItem[SINGLEPLAYER_NAME] = SINGLEPLAYER_CLASSES;
	PreviousItem[MULTIPLAYER_CONNECTIONS] = MAINMENU;
	PreviousItem[MULTIPLAYER_LOBBY] = MULTIPLAYER_CONNECTIONS;
	PreviousItem[MULTIPLAYER_DIFFICULTY] = MULTIPLAYER_LOBBY;
	PreviousItem[MULTIPLAYER_BNET_GATEWAYS] = MULTIPLAYER_CONNECTIONS;
	PreviousItem[MULTIPLAYER_ERROR] = MAINMENU;
}

void LoadUiGFX()
{
	DWORD dwData[2];

	LoadArtImage("ui_art\\focus16.pcx", &MenuPentegram16, 8, NULL);
	LoadArtImage("ui_art\\focus.pcx", &MenuPentegram, 8, NULL);
	LoadArtImage("ui_art\\focus42.pcx", &MenuPentegram42, 8, NULL);

	LoadArtImage("ui_art\\cursor.pcx", &pPcxCursorImage, 1, dwData);
	gdwCursorWidth = dwData[0];
	gdwCursorHeight = dwData[1];

	LoadArtImage("ui_art\\logo.pcx", &pPcxLogoImage, 15, dwData);
	gdwLogoWidth = dwData[0];
	gdwLogoHeight = dwData[1];

	LoadArtImage("ui_art\\smlogo.pcx", &pPcxLogoSmImage, 15, dwData);
	gdwLogoSmWidth = dwData[0];
	gdwLogoSmHeight = dwData[1];

	LoadArtImage("ui_art\\heros.pcx", &pPcxHeroImage, 4, dwData);
	gdwHeroWidth = dwData[0];
	gdwHeroHeight = dwData[1];

	pFont16 = LoadFileInMem("ui_art\\font16.bin", 0);
	LoadArtImage("ui_art\\font16s.pcx", &pPcxFont16sImage, 256, NULL);
	LoadArtImage("ui_art\\font16g.pcx", &pPcxFont16gImage, 256, dwData);
	gdwFont16Width = dwData[0];
	gdwFont16Height = dwData[1];

	pFont24 = LoadFileInMem("ui_art\\font24.bin", 0);
	LoadArtImage("ui_art\\font24s.pcx", &pPcxFont24sImage, 256, NULL);
	LoadArtImage("ui_art\\font24g.pcx", &pPcxFont24gImage, 256, dwData);
	gdwFont24Width = dwData[0];
	gdwFont24Height = dwData[1];

	pFont30 = LoadFileInMem("ui_art\\font30.bin", 0);
	LoadArtImage("ui_art\\font30s.pcx", &pPcxFont30sImage, 256, NULL);
	LoadArtImage("ui_art\\font30g.pcx", &pPcxFont30gImage, 256, dwData);
	gdwFont30Width = dwData[0];
	gdwFont30Height = dwData[1];

	pFont42 = LoadFileInMem("ui_art\\font42.bin", 0);
	LoadArtImage("ui_art\\font42g.pcx", &pPcxFont42gImage, 256, dwData);
	gdwFont42Width = dwData[0];
	gdwFont42Height = dwData[1];
}

BOOL timestart = 0;
int NewHeroNameIndex = 0;
void UiInitialize()
{
	InitHiracy();
	LoadUiGFX();
	snd_init(0);
	music_start(5);

	if (!window) {
		SdlDiabloMainWindow();
	}

	ClearScreenBuffer();

	LoadHeroStats();
	LoadCharNamesintoMemory();
}

BOOL __stdcall UiMainMenuDialog(char *name, int *menu, void(__stdcall *fnSound)(char *file), int a4)
{
	TitleImageLoaded = false;
	SelectedItemMax = 5;
	SDL_Event event;
	int x, y;
	int ItemTop = 191;
	int ItemHeight = 42;
	int ItemWidth = 515;
	int ItemLeft = GetCenterOffset(ItemWidth);

	while (1) {
		RenderDiabloMainPage(name);

		if (SDL_PollEvent(&event)) {
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
					*menu = MAINMENU_EXIT_DIABLO;
					fnSound("sfx\\items\\titlslct.wav");
					Sleep(250); // Wait for soudn to play
					return TRUE;
				case SDLK_RETURN:
					switch (SelectedItem) {
					case MAINMENU_SINGLE_PLAYER:
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_SINGLE_PLAYER;
						return TRUE;
					case MAINMENU_MULTIPLAYER:
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_MULTIPLAYER;
						return TRUE;
					case MAINMENU_REPLAY_INTRO:
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_REPLAY_INTRO;
						return TRUE;
					case MAINMENU_SHOW_CREDITS:
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_SHOW_CREDITS;
						return TRUE;
					case MAINMENU_EXIT_DIABLO:
						fnSound("sfx\\items\\titlslct.wav");
						Sleep(250); // Wait for soudn to play
						*menu = MAINMENU_EXIT_DIABLO;
						return TRUE;
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					x = event.button.x;
					y = event.button.y;

					if (IsInside(x, y, ItemLeft, ItemTop, ItemWidth, ItemHeight)) {
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_SINGLE_PLAYER;
						return TRUE;
					} else if (IsInside(x, y, ItemLeft, ItemTop + ItemHeight + 1, ItemWidth, ItemHeight)) {
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_MULTIPLAYER;
						return TRUE;
					} else if (IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 2 + 1, ItemWidth, ItemHeight)) {
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_REPLAY_INTRO;
						return TRUE;
					} else if (IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 3 + 2, ItemWidth, ItemHeight)) {
						fnSound("sfx\\items\\titlslct.wav");
						*menu = MAINMENU_SHOW_CREDITS;
						return TRUE;
					} else if (IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 4 + 3, ItemWidth, ItemHeight)) {
						fnSound("sfx\\items\\titlslct.wav");
						Sleep(250); // Wait for soudn to play
						*menu = MAINMENU_EXIT_DIABLO;
						return TRUE;
					}
				}
				break;
			case SDL_QUIT:
				fnSound("sfx\\items\\titlslct.wav");
				Sleep(250); // Wait for soudn to play
				*menu = MAINMENU_EXIT_DIABLO;
				return TRUE;
			}
		}
	}

	return TRUE;
}

static std::vector<_uiheroinfo> hero_infos;

static BOOL __stdcall ui_add_hero_info(_uiheroinfo *info)
{
	hero_infos.emplace_back(*info);
	return TRUE;
}

BOOL __stdcall UiSelHeroSingDialog(BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)),
    BOOL(__stdcall *fncreate)(_uiheroinfo *), BOOL(__stdcall *fnremove)(_uiheroinfo *),
    BOOL(__stdcall *fnstats)(unsigned int, _uidefaultstats *), int *dlgresult, char *name,
    int *difficulty)
{
	TitleImageLoaded = false;
	DUMMY();

	submenu = SINGLEPLAYER_LOAD;
	if (!TotalPlayers) {
		PreviousItem[SINGLEPLAYER_CLASSES] = 0;
		submenu = SINGLEPLAYER_CLASSES;
	}

	SelectedItemMax = MenuItem[submenu];
	SDL_Event event;
	int x, y;

	bool done = false;
	while (done == false) {
		switch (submenu) {
		case SINGLEPLAYER_LOAD:
			RenderDiabloSinglePlayerPage();
			break;
		case SINGLEPLAYER_CLASSES:
			CreateHeroMenu();
			break;
		case SINGLEPLAYER_NAME:
			RenderUndecidedHeroName(HeroChosen);
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

					return TRUE;
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
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					x = event.button.x;
					y = event.button.y;
					printf("X %d , Y %d\n", x, y);

					int ItemLeft;
					int ItemTop;
					int ItemHeight;
					int ItemWidth;

					int CreateHeroOkBoxX = 330;
					int CreateHeroOkBoxY = 441;
					int CreateHeroCanBBoxX = 445;
					int CreateHeroCanBBoxY = 473;

					SDL_Rect CreateHeroCancelBox;
					CreateHeroCancelBox.y = 550;
					CreateHeroCancelBox.x = 675;
					CreateHeroCancelBox.w = 100;
					CreateHeroCancelBox.h = 30;

					clock_t start, end;
					double cpu_time_used;

					switch (submenu) {
					case SINGLEPLAYER_LOAD:
						ItemLeft = 440;
						ItemTop = 315;
						ItemHeight = 30;
						ItemWidth = 400;

						int CreateHeroY = 555;
						int CreateHeroX = 305;

						// Render Clicks
						if (TotalPlayers >= 1 && IsInside(x, y, ItemLeft, ItemTop, ItemWidth, ItemHeight)) {
							strcpy(chr_name_str, hero_names[0]);
							printf("Player %s\n", chr_name_str);
							SetMenu(MULTIPLAYER_LOBBY);
						} else if (TotalPlayers >= 2 && IsInside(x, y, ItemLeft, ItemTop + ItemHeight, ItemWidth, ItemHeight)) {
							printf("Player 2 Diablo\n");
							strcpy(chr_name_str, hero_names[1]);
							printf("Player %s\n", chr_name_str);
							SetMenu(MULTIPLAYER_LOBBY);
						} else if (TotalPlayers >= 3 && IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 2, ItemWidth, ItemHeight)) {
							printf("Player 3 Diablo\n");
							strcpy(chr_name_str, hero_names[2]);
							printf("Player %s\n", chr_name_str);
							SetMenu(MULTIPLAYER_LOBBY);
						} else if (TotalPlayers >= 4 && IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 3, ItemWidth, ItemHeight)) {
							printf("Player 4 Diablo\n");
							strcpy(chr_name_str, hero_names[3]);
							printf("Player %s\n", chr_name_str);
							SetMenu(MULTIPLAYER_LOBBY);
						} else if (TotalPlayers >= 5 && IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 4, ItemWidth, ItemHeight)) {
							printf("Player 5 Diablo\n");
							strcpy(chr_name_str, hero_names[4]);
							printf("Player %s\n", chr_name_str);
							SetMenu(MULTIPLAYER_LOBBY);
						} else if (TotalPlayers >= 6 && IsInside(x, y, ItemLeft, ItemTop + ItemHeight * 5, ItemWidth, ItemHeight)) {
							printf("Player 6 Diablo\n");
							strcpy(chr_name_str, hero_names[5]);
							printf("Player %s\n", chr_name_str);
							SetMenu(MULTIPLAYER_LOBBY);
						} else if (TotalPlayers >= 6 && IsInsideRect(x, y, CreateHeroCancelBox)) {
							printf("Cancel\n\n\n");
							SetMenu(MAINMENU);
						} else if (TotalPlayers >= 6 && IsInside(x, y, CreateHeroX + ItemWidth, CreateHeroY, ItemWidth, ItemHeight)) {
							printf("Clicked Create Hero Box\n");
							SetMenu(SINGLEPLAYER_CLASSES);
						}
						break;
					case SINGLEPLAYER_CLASSES:
						printf("\n\nmenu3 X%d Y%d \n ", x, y);

						int WarriorSelectBoxY = 430;
						int WarriorSelectBoxW = 100;
						int WarriorSelectBoxS = 100;

						int RogueSelectBoxX = 450;
						int RogueSelectBoxY = 392;
						int SorcerorSelectBoxX = 383;
						int SorcerorSelectBoxY = 365;

						SDL_Rect WarriorSelectBox;
						WarriorSelectBox.y = 350;
						WarriorSelectBox.x = 280;
						WarriorSelectBox.w = 100;
						WarriorSelectBox.h = 30;

						SDL_Rect RogueSelectBox;
						RogueSelectBox.y = 392;
						RogueSelectBox.x = 280;
						RogueSelectBox.w = 100;
						RogueSelectBox.h = 30;

						SDL_Rect SorcerorSelectBox;
						SorcerorSelectBox.y = 428;
						SorcerorSelectBox.x = 280;
						SorcerorSelectBox.w = 100;
						SorcerorSelectBox.h = 30;

						if (IsInsideRect(x, y, WarriorSelectBox)) {
							printf(" warrior I was hit\n\n\n");
							HeroChosen = 0;
							for (int i = 0; i < 17; i++)
								HeroUndecidedName[i] = 0;
							NewHeroNameIndex = 0;
							SetMenu(SINGLEPLAYER_NAME);
						} else if (IsInsideRect(x, y, RogueSelectBox)) {
							printf(" rogue I was hit\n\n\n");
							HeroChosen = 1;
							for (int i = 0; i < 17; i++)
								HeroUndecidedName[i] = 0;
							NewHeroNameIndex = 0;
							SetMenu(SINGLEPLAYER_NAME);
						} else if (IsInsideRect(x, y, SorcerorSelectBox)) {
							printf("sorceror I was hit\n\n\n");
							HeroChosen = 2;
							for (int i = 0; i < 17; i++)
								HeroUndecidedName[i] = 0;
							NewHeroNameIndex = 0;
							SetMenu(SINGLEPLAYER_NAME);
						} else if (IsInsideRect(x, y, CreateHeroCancelBox)) {
							printf("Cancel\n\n\n");
							SetMenu(SINGLEPLAYER_CLASSES);
						}
						break;
					case SINGLEPLAYER_NAME:
						printf("Create hero");

						SDL_Rect ClickOkBox;
						ClickOkBox.x = 324;
						ClickOkBox.y = 430;
						ClickOkBox.w = 48;
						ClickOkBox.h = 30;

						if (IsInsideRect(x, y, CreateHeroCancelBox)) {
							memset(HeroUndecidedName, 0, 17);

							NewHeroNameIndex = 0;

							printf("Cancel\n\n\n");
							SetMenu(SINGLEPLAYER_CLASSES);
						} else if (IsInsideRect(x, y, ClickOkBox)) {
							printf("Ok\n");
							CreateSinglePlayerChar = 1;
							const char *test_name = HeroUndecidedName;
							printf("%s\n", test_name);
						}
						break;
					}
				}
				break;
			}
		}
	}

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

	return TRUE;
}

int __cdecl UiProfileGetString()
{
	DUMMY();
	return 0;
}

void __stdcall UiSetupPlayerInfo(char *infostr, _uiheroinfo *pInfo, int type)
{
	DUMMY_PRINT("chr: %s", infostr);
}

BOOL __stdcall UiCopyProtError(int *pdwResult)
{
	UNIMPLEMENTED();
}

void __stdcall UiAppActivate(BOOL bActive)
{
	UNIMPLEMENTED();
}

BOOL __fastcall UiValidPlayerName(char *name)
{
	UNIMPLEMENTED();
}

int __stdcall UiProgressDialog(HWND window, char *msg, int a3, void *fnfunc, int a5)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiSelHeroMultDialog(BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)),
    BOOL(__stdcall *fncreate)(_uiheroinfo *), BOOL(__stdcall *fnremove)(_uiheroinfo *),
    BOOL(__stdcall *fnstats)(unsigned int, _uidefaultstats *), int *dlgresult, int *a6,
    char *name)
{
	TitleImageLoaded = false;
	SelectedItemMax = MenuItem[submenu];
	SDL_Event event;
	int x, y;

	switch (submenu) {
	case MULTIPLAYER_LOBBY:
		DrawPreGameOptions(HeroChosen, 1);
		break;
	case MULTIPLAYER_DIFFICULTY:
		DrawPreGameDifficultySelection(HeroChosen, 1);
		break;
	}

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				SetMenu(PreviousItem[submenu]);
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
			default:
				char letter = event.key.keysym.sym;
				if (int(letter) > 96 && int(letter) < 123 || int(letter) == 32)

					if (NewHeroNameIndex < 17) {
						HeroUndecidedName[NewHeroNameIndex] = letter;
						NewHeroNameIndex++;
					}
				break;
			}
		case SDL_KEYUP:
			break;
		}

		// If a key was pressed
		if (event.type == SDL_MOUSEBUTTONDOWN /*&& event.button.clicks == 2*/) {

			if (event.button.button == SDL_BUTTON_LEFT) {
				x = event.button.x;
				y = event.button.y;
				printf("X %d , Y %d\n", x, y);

				int ItemLeft;
				int ItemTop;
				int ItemHeight;
				int ItemWidth;

				int CreateHeroOkBoxX = 330;
				int CreateHeroOkBoxY = 441;
				int CreateHeroCanBBoxX = 445;
				int CreateHeroCanBBoxY = 473;

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
					// X450 Y 392 ;
					// X 447 Y 428

					if (cpu_time_used > 0.5 && IsInsideRect(x, y, NewGameBox)) {
						printf(" New Game I was hit\n\n\n");
						SetMenu(MULTIPLAYER_DIFFICULTY);
						cpu_time_used = 0;
						timestart = 0;
						start = 0;
					} else if (cpu_time_used > 0.5 && IsInsideRect(x, y, LoadGameBox)) {

						printf(" Load Game I was hit\n\n\n");
						break;
					} else if (IsInsideRect(x, y, CreateHeroCancelBox)) {
						timestart = 0;
						cpu_time_used = 0;
						start = 0;
						end = 0;
						cpu_time_used = 0;

						printf("Cancel\n\n\n");

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

					// int x = 280;
					// int y = 430;

					SDL_Rect NormalSelectBox;
					NormalSelectBox.y = 350;
					NormalSelectBox.x = 280;
					NormalSelectBox.w = 300;
					NormalSelectBox.h = 30;

					SDL_Rect NightmareSelectBox;
					NightmareSelectBox.y = 392;
					NightmareSelectBox.x = 280;
					NightmareSelectBox.w = 300;
					NightmareSelectBox.h = 30;
					// X450 Y 392 ;

					SDL_Rect HellSelectBox;
					HellSelectBox.y = 428;
					HellSelectBox.x = 280;
					HellSelectBox.w = 300;
					HellSelectBox.h = 30;
					// X 447 Y 428

					if (cpu_time_used > 0.5 && IsInsideRect(x, y, NormalSelectBox)) {
						StartNewGame = 1;
						gnDifficulty = DIFF_NORMAL;
						break;
					} else if (cpu_time_used > 0.5 && IsInsideRect(x, y, NightmareSelectBox)) {
						StartNewGame = 1;
						gnDifficulty = DIFF_NIGHTMARE;
						break;
					} else if (cpu_time_used > 1 && IsInsideRect(x, y, HellSelectBox)) {
						gnDifficulty = DIFF_HELL;
						StartNewGame = 1;
						break;
					} else if (IsInsideRect(x, y, CreateHeroCancelBox)) {
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
		}
	}

	return TRUE;

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
	}

	return TRUE;
}

BOOL __stdcall UiCreditsDialog(int a1)
{
	TitleImageLoaded = false;
	SDL_Event event;
	while (1) {
		ShowCredts();

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_MOUSEBUTTONDOWN:
				return TRUE;
			case SDL_QUIT:
				SDL_Quit();
				exit(0);
			}
		}
	}

	return FALSE;
}

void __cdecl UiProfileCallback()
{
	UNIMPLEMENTED();
}

void __cdecl UiProfileDraw()
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiCategoryCallback(int a1, int a2, int a3, int a4, int a5, _DWORD *a6, _DWORD *a7)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiGetDataCallback(int game_type, int data_code, void *a3, int a4, int a5)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiAuthCallback(int a1, char *a2, char *a3, char a4, char *a5, LPSTR lpBuffer, int cchBufferMax)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiSoundCallback(int a1, int type, int a3)
{
	UNIMPLEMENTED();
}

void __stdcall UiMessageBoxCallback(HWND hWnd, char *lpText, LPCSTR lpCaption, UINT uType)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiDrawDescCallback(int arg0, COLORREF color, LPCSTR lpString, char *a4, int a5, UINT align, time_t a7,
    HDC *a8)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiCreateGameCallback(int a1, int a2, int a3, int a4, int a5, int a6)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiArtCallback(int game_type, unsigned int art_code, PALETTEENTRY *pPalette, void *pBuffer,
    DWORD dwBuffersize, DWORD *pdwWidth, DWORD *pdwHeight, DWORD *pdwBpp)
{
	UNIMPLEMENTED();
}

int __stdcall UiSelectGame(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info,
    _SNETVERSIONDATA *file_info, int *a6)
{
	UNIMPLEMENTED();
}

int __stdcall UiSelectProvider(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info,
    _SNETVERSIONDATA *file_info, int *type)
{
	UNIMPLEMENTED();
}

int __stdcall UiCreatePlayerDescription(_uiheroinfo *info, int mode, char *desc)
{
	UNIMPLEMENTED();
}
