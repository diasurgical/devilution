#include "../../types.h"
#include <iconv.h>

int selhero_SaveCount = 0;
_uiheroinfo heros[MAX_CHARACTERS];
_uiheroinfo heroInfo;

void RenderStats()
{
	char lvl[4] = "--";
	char str[4] = "--";
	char mag[4] = "--";
	char dex[4] = "--";
	char vit[4] = "--";

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

void selhero_Render(bool multiPlayer)
{
	heroInfo.heroclass = UI_NUM_CLASSES;
	if (SelectedItem <= selhero_SaveCount) {
		memcpy(&heroInfo, &heros[SelectedItem - 1], sizeof(heroInfo));
	}

	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	char *title = "Single Player Characters";
	if (multiPlayer) {
		title = "Multi Player Characters";
	}
	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, title, JustCentre);

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

void selhero_Render_Name(bool multiPlayer)
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	char *title = "New Single Player Hero";
	if (multiPlayer) {
		title = "New Multi Player Hero";
	}

	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, title, JustCentre);

	int w = 369;
	int x = 241;
	int y = 318;

	DrawArtStr(x - 1, 211, AFT_BIG, AFC_SILVER, "Enter Name", JustCentre, w);

	DrawSelector(x, y - 2, w, 39, 26);

	char lable[17];
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
void selhero_Render_ClassSelector(bool multiPlayer)
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArt(30, 211, &ArtHero, heroInfo.heroclass);
	RenderStats();

	char *title = "New Single Player Hero";
	if (multiPlayer) {
		title = "New Multi Player Hero";
	}
	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, title, JustCentre);

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

void selhero_Load(BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)))
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

bool selhero_Event(bool *aborted)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (UiFocuseNavigation(&event))
				break;
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				*aborted = true;
				return true;
			case SDLK_RETURN:
			case SDLK_KP_ENTER:
			case SDLK_SPACE:
				if (SelectedItem == SelectedItemMax) {
					memset(&heroInfo.name, 0, sizeof(heroInfo.name));
					SetMenu(SELHERO_CLASSES);
					break;
				}
				return true;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}

	return false;
}

bool selhero_Event_ClassSelector(bool *aborted)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (UiFocuseNavigation(&event, true))
				break;
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (selhero_SaveCount) {
					SetMenu(SELHERO_LOAD);
					SelectedItemMax = 1 + selhero_SaveCount;
					break;
				}
				*aborted = true;
				return true;
			case SDLK_RETURN:
			case SDLK_KP_ENTER:
			case SDLK_SPACE:
				SetMenu(SELHERO_NAME);
				SDL_StartTextInput();
				break;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}

	return false;
}

bool selhero_CatToName(char *in_buf)
{
	iconv_t cd = iconv_open("ISO_8859-1//TRANSLIT//IGNORE", "UTF-8");
	if (cd == (iconv_t)-1) {
		TermMsg("Failed to load iconv!");
	}

	size_t in_left = strlen(in_buf);
	char output[SDL_TEXTINPUTEVENT_TEXT_SIZE] = "";
	char *out_buf = output;
	size_t out_left = sizeof(output) - 1;

	while (in_left && out_left) {
		iconv(cd, &in_buf, &in_left, &out_buf, &out_left);
	}
	iconv_close(cd);
	strncat(heroInfo.name, output, 15 - strlen(heroInfo.name));
}

bool selhero_Event_Name()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {


		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_v:
				if (SDL_GetModState() & KMOD_CTRL) {
					selhero_CatToName(SDL_GetClipboardText());
				}
				break;
			case SDLK_ESCAPE:
				SDL_StopTextInput();
				SetMenu(SELHERO_CLASSES);
				break;
			case SDLK_RETURN:
			case SDLK_RETURN2:
			case SDLK_KP_ENTER:
				SDL_StopTextInput();
				return true;
				break;
			case SDLK_BACKSPACE:
			case SDLK_LEFT:
				int nameLen = strlen(heroInfo.name);
				if (nameLen > 0) {
					heroInfo.name[nameLen - 1] = '\0';
				}
				break;
			}
			break;
		case SDL_TEXTINPUT:
			selhero_CatToName(event.text.text);
			break;
		}
	}

	return false;
}

bool UiSelHeroDialog(
    BOOL(__stdcall *fncreate)(_uiheroinfo *),
    BOOL(__stdcall *fnremove)(_uiheroinfo *),
    BOOL(__stdcall *fnstats)(unsigned int, _uidefaultstats *),
    bool multiPlayer)
{
	bool aborted = false;
	bool endMenu = false;

	SelectedItem = 1;
	submenu = SELHERO_LOAD;
	SelectedItemMax = 1 + selhero_SaveCount;
	if (!selhero_SaveCount) {
		submenu = SELHERO_CLASSES;
		SelectedItemMax = 3;
	}

	while (endMenu == false) {
		CapFPS();

		switch (submenu) {
		case SELHERO_LOAD:
			selhero_Render(multiPlayer);
			endMenu = selhero_Event(&aborted);
			break;
		case SELHERO_CLASSES:
			selhero_setDefaultStats(fnstats);
			selhero_Render_ClassSelector(multiPlayer);
			endMenu = selhero_Event_ClassSelector(&aborted);
			break;
		case SELHERO_NAME:
			selhero_Render_Name(multiPlayer);
			endMenu = selhero_Event_Name();
			break;
		}

		DrawMouse();
		UiFadeIn();
	}

	return aborted;
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
	selhero_Load(fninfo);
	if (UiSelHeroDialog(fncreate, fnremove, fnstats, false)) {
		*dlgresult = EXIT_MENU;
	} else {
		strcpy(name, heroInfo.name);

		if (!heroInfo.hassaved) {
			fncreate(&heroInfo); // todo don't overwrite
		} else if (heroInfo.hassaved) {
			*dlgresult = LOAD_GAME;
		}
	}

	BlackPalette();
	selhero_Free();

	return TRUE;
}

//////////////////////////////////////////
//            MULTI PLAYER              //
//////////////////////////////////////////

void selhero_multi_Load()
{
	LoadBackgroundArt("ui_art\\selgame.pcx");
}

void selhero_multi_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
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

bool selhero_Event_GameSelection(int *dlgresult)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (UiFocuseNavigation(&event))
				break;
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				*dlgresult = EXIT_MENU;
				return true;
			case SDLK_RETURN:
			case SDLK_KP_ENTER:
			case SDLK_SPACE:
				SetMenu(SELHERO_DIFFICULTY);
				break;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}

	return false;
}

bool selhero_Event_DifficultySelection(int *dlgresult)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (UiFocuseNavigation(&event, true))
				break;
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				SetMenu(SELHERO_SELECT_GAME);
				break;
			case SDLK_RETURN:
			case SDLK_KP_ENTER:
			case SDLK_SPACE:
				*dlgresult = NEW_GAME;
				return true;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_Rect CreateHeroCancelBox;
				CreateHeroCancelBox.y = 550;
				CreateHeroCancelBox.x = 675;
				CreateHeroCancelBox.w = 100;
				CreateHeroCancelBox.h = 30;

				SDL_Rect NormalSelectBox;
				NormalSelectBox.x = 280;
				NormalSelectBox.y = 350;
				NormalSelectBox.w = 300;
				NormalSelectBox.h = 30;

				if (IsInsideRect(&event, &NormalSelectBox)) {
					gnDifficulty = DIFF_NORMAL;
					*dlgresult = LOAD_GAME;
				}
				break;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}

	return false;
}

void selhero_Render_GameSelection()
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

	selhero_Load(fninfo);
	bool abort = UiSelHeroDialog(fncreate, fnremove, fnstats, true);
	BlackPalette();
	selhero_Free();
	if (abort) {
		*dlgresult = EXIT_MENU;
		return TRUE;
	}

	strcpy(name, heroInfo.name);

	selhero_multi_Load();

	submenu = SELHERO_SELECT_GAME;

	SelectedItem = 1;
	SelectedItemMax = 2;

	bool endMenu = false;
	while (endMenu == false) {
		CapFPS();

		switch (submenu) {
		case SELHERO_SELECT_GAME:
			selhero_Render_GameSelection();
			endMenu = selhero_Event_GameSelection(dlgresult);
			break;
		case SELHERO_DIFFICULTY:
			selhero_Render_DifficultySelection();
			endMenu = selhero_Event_DifficultySelection(dlgresult);
			break;
		}

		DrawMouse();
		UiFadeIn();
	}

	if (*dlgresult != EXIT_MENU) {
		strcpy(name, heroInfo.name);
	}

	BlackPalette();
	selhero_Free();

	return TRUE;
}
