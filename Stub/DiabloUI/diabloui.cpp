#include "../../types.h"

char hero_names[MAX_CHARACTERS][PLR_NAME_LEN];

int SelectedItemMax = 0;
int MenuItem[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PreviousItem[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int submenu = 0;

void __cdecl UiDestroy()
{
	DUMMY();
	FreeMenuItems();
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

		p_hero_names += PLR_NAME_LEN;
	}

	// memcpy(shero_names, hero_names, sizeof(hero_names));
}

void SetMenu(int MenuId)
{
	effects_play_sound("sfx\\items\\titlslct.wav");

	submenu = MenuId;
	SelectedItem = 1;
	SelectedItemMax = MenuItem[MenuId];
}

bool IsInsideRect(const SDL_Event *event, const SDL_Rect *rect)
{
	const SDL_Point point = { event->button.x, event->button.y };
	return SDL_PointInRect(&point, rect);
}

void InitHiracy()
{
	MenuItem[SINGLEPLAYER_CLASSES] = 3;
	MenuItem[MULTIPLAYER_CONNECTIONS] = 3;
	MenuItem[MULTIPLAYER_LOBBY] = 2;
	MenuItem[MULTIPLAYER_DIFFICULTY] = 3;
	MenuItem[MULTIPLAYER_BNET_GATEWAYS] = 3;

	PreviousItem[SINGLEPLAYER_CLASSES] = SINGLEPLAYER_LOAD;
	PreviousItem[SINGLEPLAYER_NAME] = SINGLEPLAYER_CLASSES;
	PreviousItem[MULTIPLAYER_CONNECTIONS] = MAINMENU;
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

void UiInitialize()
{
	InitHiracy();
	LoadUiGFX();

	if (!window) {
		SdlDiabloMainWindow();
	}
	ShowCursor(FALSE);

	LoadHeroStats();
	LoadCharNamesintoMemory();
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
	DUMMY();
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

BOOL __stdcall UiDrawDescCallback(int game_type, COLORREF color, LPCSTR lpString, char *a4, int a5, UINT align, time_t a7,
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
    _SNETVERSIONDATA *file_info, int *playerId)
{
	SNetCreateGame(NULL, NULL, NULL, 0, NULL, 0, MAX_PLRS, NULL, NULL, playerId);
	return 1;
}

int __stdcall UiCreatePlayerDescription(_uiheroinfo *info, int mode, char *desc)
{
	UNIMPLEMENTED();
}
