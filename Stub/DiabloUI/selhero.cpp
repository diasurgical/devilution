#include "selhero.h"
#include <iconv.h>

int selhero_SaveCount = 0;
_uiheroinfo heros[MAX_CHARACTERS];
_uiheroinfo heroInfo;
char listItems[6][16];
char textStats[5][4];
char title[32];
char selhero_Lable[32];
char selhero_Description[256];
int selhero_result;
bool selhero_return;
bool selhero_endMenu;
bool selhero_endMenu_Single;
int submenu = 0;
bool isMultiPlayer;
bool heroIsCreated;

BOOL(__stdcall *gfnHeroStats)
(unsigned int, _uidefaultstats *);

UI_Item SELHERO_DIALOG[] = {
	{ { 0, 0, 640, 480 }, UI_IMAGE, 0, 0, NULL, &ArtBackground },
	{ { 24, 161, 590, 35 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, title },
	{ { 30, 211, 180, 76 }, UI_IMAGE, 0, UI_NUM_CLASSES, NULL, &ArtHero },
	{ { 39, 323, 110, 21 }, UI_TEXT, UIS_RIGHT, 0, "Level:" },
	{ { 159, 323, 40, 21 }, UI_TEXT, UIS_CENTER, 0, textStats[0] },
	{ { 39, 358, 110, 21 }, UI_TEXT, UIS_RIGHT, 0, "Strength:" },
	{ { 159, 358, 40, 21 }, UI_TEXT, UIS_CENTER, 0, textStats[1] },
	{ { 39, 380, 110, 21 }, UI_TEXT, UIS_RIGHT, 0, "Magic:" },
	{ { 159, 380, 40, 21 }, UI_TEXT, UIS_CENTER, 0, textStats[2] },
	{ { 39, 401, 110, 21 }, UI_TEXT, UIS_RIGHT, 0, "Dexterity:" },
	{ { 159, 401, 40, 21 }, UI_TEXT, UIS_CENTER, 0, textStats[3] },
	{ { 39, 422, 110, 21 }, UI_TEXT, UIS_RIGHT, 0, "Vitality:" },
	{ { 159, 422, 40, 21 }, UI_TEXT, UIS_CENTER, 0, textStats[4] },
};

UI_Item SELLIST_DIALOG[] = {
	{ { 264, 211, 320, 33 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Select Hero" },
	{ { 265, 256, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 0, listItems[0] },
	{ { 265, 282, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 1, listItems[1] },
	{ { 265, 308, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 2, listItems[2] },
	{ { 265, 334, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 3, listItems[3] },
	{ { 265, 360, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 4, listItems[4] },
	{ { 265, 386, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 5, listItems[5] },
	{ { 239, 429, 120, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_GOLD, 0, "OK", UiFocusNavigationSelect },
	{ { 364, 429, 120, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_DISABLED, 0, "Delete" },
	{ { 489, 429, 120, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_GOLD, 0, "Cancel" },
};

UI_Item SELCLASS_DIALOG[] = {
	{ { 264, 211, 320, 33 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Choose Class" },
	{ { 264, 285, 320, 33 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, UI_WARRIOR, "Warrior" },
	{ { 264, 318, 320, 33 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, UI_ROGUE, "Rogue" },
	{ { 264, 352, 320, 33 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, UI_SORCERER, "Sorcerer" },
	{ { 279, 429, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_GOLD, 0, "OK", UiFocusNavigationSelect },
	{ { 429, 429, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_GOLD, 0, "Cancel" },
};

UI_Item ENTERNAME_DIALOG[] = {
	{ { 264, 211, 320, 33 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Enter Name" },
	{ { 265, 317, 320, 33 }, UI_EDIT, UIS_LIST | UIS_MED | UIS_GOLD, 0, heroInfo.name, 15 },
	{ { 279, 429, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_GOLD, 0, "OK", UiFocusNavigationSelect },
	{ { 429, 429, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_BIG | UIS_GOLD, 0, "Cancel" },
};

UI_Item SELLOAD_DIALOG[] = {
	{ { 264, 211, 320, 33 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Save File Exists" },
	{ { 265, 285, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 0, "Load Game" },
	{ { 265, 318, 320, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 1, "New Game" },
	{ { 279, 427, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_VCENTER | UIS_BIG | UIS_GOLD, 0, "OK", UiFocusNavigationSelect },
	{ { 429, 427, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_VCENTER | UIS_BIG | UIS_GOLD, 0, "Cancel" },
};

UI_Item SELUDPGAME_DIALOG[] = {
	{ { 0, 0, 640, 480 }, UI_IMAGE, 0, 0, NULL, &ArtBackground },
	{ { 25, 161, 590, 35 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Join UDP Games" },
	{ { 300, 211, 295, 33 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Select Action" },
	{ { 305, 255, 285, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 0, "Create Game" },
	{ { 305, 281, 285, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 1, "Enter IP" },
	{ { 305, 307, 285, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, 2, "Localhost" },
	{ { 305, 333, 285, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD },
	{ { 305, 359, 285, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD },
	{ { 305, 385, 285, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD },
	{ { 35, 211, 205, 33 }, UI_TEXT, UIS_MED, 0, "Description:" },
	{ { 35, 256, 205, 192 }, UI_TEXT, 0, 0, selhero_Description }, // Description
	{ { 299, 427, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_VCENTER | UIS_BIG | UIS_GOLD, 0, "OK", UiFocusNavigationSelect },
	{ { 449, 427, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_VCENTER | UIS_BIG | UIS_GOLD, 0, "Cancel" },
};

UI_Item SELDIFF_DIALOG[] = {
	{ { 0, 0, 640, 480 }, UI_IMAGE, 0, 0, NULL, &ArtBackground },
	{ { 24, 161, 590, 35 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Create Game" },
	{ { 299, 211, 295, 35 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, "Select Difficulty" },
	{ { 300, 282, 295, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, DIFF_NORMAL, "Normal" },
	{ { 300, 308, 295, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, DIFF_NIGHTMARE, "Nightmare" },
	{ { 300, 334, 295, 26 }, UI_LIST, UIS_CENTER | UIS_MED | UIS_GOLD, DIFF_HELL, "Hell" },
	{ { 34, 211, 205, 33 }, UI_TEXT, UIS_CENTER | UIS_BIG, 0, selhero_Lable }, // DIFF
	{ { 35, 256, 205, 192 }, UI_TEXT, 0, 0, selhero_Description },             // Description
	{ { 299, 427, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_VCENTER | UIS_BIG | UIS_GOLD, 0, "OK", UiFocusNavigationSelect },
	{ { 449, 427, 140, 35 }, UI_BUTTON, UIS_CENTER | UIS_VCENTER | UIS_BIG | UIS_GOLD, 0, "Cancel" },
};

void selhero_SetStats()
{
	SELHERO_DIALOG[2].value = heroInfo.heroclass;
	sprintf(textStats[0], "%d", heroInfo.level);
	sprintf(textStats[1], "%d", heroInfo.strength);
	sprintf(textStats[2], "%d", heroInfo.magic);
	sprintf(textStats[3], "%d", heroInfo.dexterity);
	sprintf(textStats[4], "%d", heroInfo.vitality);
}

void selhero_Render_Name()
{
	char lable[17];
	strcpy(lable, heroInfo.name);
	if (GetAnimationFrame(2, 500)) {
		int len = strlen(lable);
		lable[len] = '|';
		lable[len + 1] = '\0';
	}
	ENTERNAME_DIALOG[1].caption = lable;

	UiRenderItems(ENTERNAME_DIALOG, size(ENTERNAME_DIALOG));
}

BOOL __stdcall SelHero_GetHeroInfo(_uiheroinfo *pInfo)
{
	heros[selhero_SaveCount] = *pInfo;
	selhero_SaveCount++;

	return TRUE;
}

void selhero_Focus_List(int value)
{
	if (selhero_SaveCount && value < selhero_SaveCount) {
		memcpy(&heroInfo, &heros[value], sizeof(heroInfo));
		selhero_SetStats();
		return;
	}

	SELHERO_DIALOG[2].value = UI_NUM_CLASSES;
	sprintf(textStats[0], "--");
	sprintf(textStats[1], "--");
	sprintf(textStats[2], "--");
	sprintf(textStats[3], "--");
	sprintf(textStats[4], "--");
}

void selhero_Select_ClassSelector(int value)
{
	submenu = SELHERO_NAME;
	sprintf(title, "New Single Player Hero");
	if (isMultiPlayer) {
		sprintf(title, "New Multi Player Hero");
	}
	memset(heroInfo.name, '\0', 16);
	SDL_StartTextInput();
}

void selhero_Focus_ClassSelector(int value)
{
	_uidefaultstats defaults;
	gfnHeroStats(value, &defaults);

	heroInfo.level = 1;
	heroInfo.heroclass = value;
	heroInfo.strength = defaults.strength;
	heroInfo.magic = defaults.magic;
	heroInfo.dexterity = defaults.dexterity;
	heroInfo.vitality = defaults.vitality;

	selhero_SetStats();
}

void selhero_Select_List(int value)
{
	if (value == selhero_SaveCount) {
		submenu = SELHERO_CLASSES;
		UiInitList(0, 2, selhero_Focus_ClassSelector, selhero_Select_ClassSelector);
		memset(&heroInfo.name, 0, sizeof(heroInfo.name));
		sprintf(title, "New Single Player Hero");
		if (isMultiPlayer) {
			sprintf(title, "New Multi Player Hero");
		}
		return;
	}

	heroIsCreated = true;
	selhero_return = false;
	selhero_endMenu = true;
}

void selhero_Load(BOOL(__stdcall *fninfo)(BOOL(__stdcall *fninfofunc)(_uiheroinfo *)))
{
	LoadBackgroundArt("ui_art\\selhero.pcx");

	selhero_SaveCount = 0;
	fninfo(SelHero_GetHeroInfo);
}

void selhero_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
	memset(listItems, 0, sizeof(listItems));
}

void selhero_List_Esc()
{
	selhero_return = true;
	selhero_endMenu = true;
}

void selhero_Event_List()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (UiFocusNavigation(&event))
			continue;
		if (UiItemMouseEvents(&event, SELLIST_DIALOG, size(SELLIST_DIALOG)))
			continue;
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				selhero_List_Esc();
				break;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

void selhero_init_List()
{
	submenu = SELHERO_LIST;
	UiInitList(0, selhero_SaveCount, selhero_Focus_List, selhero_Select_List);
	int i;
	for (i = 0; i < selhero_SaveCount && i < 6; i++) {
		sprintf(listItems[i], heros[i].name);
	}
	if (i < 6)
		sprintf(listItems[i], "New Hero");

	sprintf(title, "Single Player Characters");
	if (isMultiPlayer) {
		sprintf(title, "Multi Player Characters");
	}
}

void selhero_Event_ClassSelector()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (UiFocusNavigation(&event))
			continue;
		if (UiItemMouseEvents(&event, SELCLASS_DIALOG, size(SELCLASS_DIALOG)))
			continue;
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				if (selhero_SaveCount) {
					selhero_init_List();
					break;
				}
				selhero_return = true;
				selhero_endMenu = true;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

void selhero_CatToName(char *in_buf)
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

void selhero_Event_Name()
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
				selhero_Select_List(selhero_SaveCount);
				break;
			case SDLK_RETURN:
			case SDLK_RETURN2:
			case SDLK_KP_ENTER:
				SDL_StopTextInput();
				selhero_endMenu = true;
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
}

void selhero_Event_Load()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (UiFocusNavigation(&event, true))
			continue;
		if (UiItemMouseEvents(&event, SELLOAD_DIALOG, size(SELLOAD_DIALOG)))
			continue;
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				selhero_result = EXIT_MENU;
				selhero_endMenu_Single = true;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

bool UiSelHeroDialog(
    BOOL(__stdcall *fncreate)(_uiheroinfo *),
    BOOL(__stdcall *fnremove)(_uiheroinfo *),
    bool multiPlayer)
{
	isMultiPlayer = multiPlayer;
	selhero_return = false;
	selhero_endMenu = false;
	heroIsCreated = false;

	if (selhero_SaveCount) {
		selhero_init_List();
	} else {
		selhero_Select_List(selhero_SaveCount);
	}

	while (!selhero_endMenu) {
		UiRenderItems(SELHERO_DIALOG, size(SELHERO_DIALOG));
		switch (submenu) {
		case SELHERO_LIST:
			UiRenderItems(SELLIST_DIALOG, size(SELLIST_DIALOG));
			selhero_Event_List();
			break;
		case SELHERO_CLASSES:
			UiRenderItems(SELCLASS_DIALOG, size(SELCLASS_DIALOG));
			selhero_Event_ClassSelector();
			break;
		case SELHERO_NAME:
			selhero_Render_Name();
			selhero_Event_Name();
			break;
		}

		DrawLogo();
		DrawMouse();
		UiFadeIn();
	}

	if (!heroIsCreated) {
		fncreate(&heroInfo);
	}

	return selhero_return;
}

void selhero_Select_Load(int value)
{
	selhero_endMenu_Single = true;
	if (value == 0) {
		selhero_result = LOAD_GAME;
		return;
	}

	selhero_result = NEW_GAME;
}

void selhero_Focus_Load(int value)
{
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
	gfnHeroStats = fnstats;

	selhero_Load(fninfo);
	bool abort = UiSelHeroDialog(fncreate, fnremove, false);
	if (abort) {
		BlackPalette();
		selhero_Free();
		*dlgresult = EXIT_MENU;
		return TRUE;
	}

	strcpy(name, heroInfo.name);

	if (heroInfo.hassaved) {
		UiInitList(0, 1, selhero_Focus_Load, selhero_Select_Load);
		sprintf(title, "Single Player Characters");

		selhero_endMenu_Single = false;
		while (!selhero_endMenu_Single) {
			UiRenderItems(SELHERO_DIALOG, size(SELHERO_DIALOG));
			UiRenderItems(SELLOAD_DIALOG, size(SELLOAD_DIALOG));
			DrawLogo();
			DrawMouse();
			UiFadeIn();
			selhero_Event_Load();
		}
	}

	BlackPalette();
	selhero_Free();

	*dlgresult = selhero_result;
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

void selhero_Focus_Diff(int value)
{
	switch (value) {
	case DIFF_NORMAL:
		sprintf(selhero_Lable, "Normal");
		sprintf(selhero_Description, "Normal Difficulty\nThis is where a starting character should begin the quest to defeat Diablo.");
		break;
	case DIFF_NIGHTMARE:
		sprintf(selhero_Lable, "Nightmare");
		sprintf(selhero_Description, "Nightmare Difficulty\nThe denizens of the Labyrinth have been bolstered and will prove to be a greater challenge. This is recommended for experienced characters only.");
		break;
	case DIFF_HELL:
		sprintf(selhero_Lable, "Hell");
		sprintf(selhero_Description, "Hell Difficulty\nThe most powerful of the underworld's creatures lurk at the gateway into Hell. Only the most experienced characters should venture in this realm.");
		break;
	}

	for (auto &item : SELDIFF_DIALOG) {
		if (item.caption != NULL && !(item.flags & (UIS_VCENTER | UIS_CENTER)))
			WordWrap(&item);
	}
}

void selhero_Select_Diff(int value)
{
	gnDifficulty = value;
	selhero_result = NEW_GAME;
}

void selhero_Select_GameSelection(int value)
{
	submenu = SELHERO_DIFFICULTY;
	UiInitList(0, 2, selhero_Focus_Diff, selhero_Select_Diff);
}

void selhero_Event_GameSelection()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (UiFocusNavigation(&event))
			continue;
		if (UiItemMouseEvents(&event, SELUDPGAME_DIALOG, size(SELUDPGAME_DIALOG)))
			continue;
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				selhero_result = EXIT_MENU;
				selhero_endMenu_Single = true;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
	}
}

void selhero_Focus_GameSelection(int value)
{
	switch (value) {
	case 0:
		sprintf(selhero_Description, "Create a new game with a difficulty setting of your choice.");
		break;
	case 1:
		sprintf(selhero_Description, "Join a game directly via a know host IP.");
		break;
	default:
		sprintf(selhero_Description, "%s.\nCreated by %s, a level %d %s.", "Normal Difficulty", "Localhost", 1, "Warrior");
		break;
	}

	for (auto &item : SELUDPGAME_DIALOG) {
		if (item.caption != NULL && !(item.flags & (UIS_VCENTER | UIS_CENTER)))
			WordWrap(&item);
	}
}

void selhero_Event_DifficultySelection()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (UiFocusNavigation(&event))
			continue;
		if (UiItemMouseEvents(&event, SELDIFF_DIALOG, size(SELDIFF_DIALOG)))
			continue;
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				submenu = SELHERO_SELECT_GAME;
				UiInitList(0, 2, selhero_Focus_GameSelection, selhero_Select_GameSelection);
				break;
			case SDLK_RETURN:
			case SDLK_KP_ENTER:
			case SDLK_SPACE:
				selhero_endMenu_Single = true;
			}
			break;
		case SDL_QUIT:
			exit(0);
		}
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
	gfnHeroStats = fnstats;
	*hero_is_created = false;

	selhero_Load(fninfo);
	bool abort = UiSelHeroDialog(fncreate, fnremove, true);
	BlackPalette();
	selhero_Free();
	if (abort) {
		*dlgresult = EXIT_MENU;
		return TRUE;
	}

	strcpy(name, heroInfo.name);

	selhero_multi_Load();

	submenu = SELHERO_SELECT_GAME;
	UiInitList(0, 2, selhero_Focus_GameSelection, selhero_Select_GameSelection);

	selhero_endMenu_Single = false;
	while (!selhero_endMenu_Single) {
		switch (submenu) {
		case SELHERO_SELECT_GAME:
			UiRenderItems(SELUDPGAME_DIALOG, size(SELUDPGAME_DIALOG));
			selhero_Event_GameSelection();
			break;
		case SELHERO_DIFFICULTY:
			UiRenderItems(SELDIFF_DIALOG, size(SELDIFF_DIALOG));
			selhero_Event_DifficultySelection();
			break;
		}
		DrawLogo();
		DrawMouse();
		UiFadeIn();
	}

	BlackPalette();
	selhero_Free();

	*dlgresult = selhero_result;
	return TRUE;
}
