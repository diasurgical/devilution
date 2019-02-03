#include "../../types.h"

void selconn_Render()
{
	DrawArt(0, 0, &ArtBackground);
	DrawLogo();

	DrawArtStr(-1, 161, AFT_BIG, AFC_SILVER, "Multi Player Game", JustCentre);

	int w = 334;
	int x = 280;
	int y = 261;

	DrawArtStr(x, 211, AFT_BIG, AFC_SILVER, "Select Connection", JustCentre, w);

	char *connections[2] = {
		//"Battle.net",
		//"Local Area Network (IPC)",
		//"Modem",
		//"Direct Cable Connection",
		"Local Area Network (UDP)",
		"Solo",
	};

	int selectorTop = y;

	for (int i = 0; i < 2; i++) {
		DrawArtStr(x - 1, y, AFT_SMALL, AFC_GOLD, connections[i], JustCentre, w);
		y += 26;
	}

	DrawSelector(x, selectorTop - 2, w, 35, 26, FOCUS_SMALL);

	if (SelectedItem == 1) {
		DrawArtStr(35, 218, AFT_SMALL, AFC_SILVER, "Players Supported: 4");
		DrawArtStr(35, 256, AFT_SMALL, AFC_SILVER, "Requirements:");
		// TODO need a word wrap function
		DrawArtStr(35, 275, AFT_SMALL, AFC_SILVER, "All computers must be");
		DrawArtStr(35, 291, AFT_SMALL, AFC_SILVER, "connected to an");
		DrawArtStr(35, 307, AFT_SMALL, AFC_SILVER, "UDP-compatible network.");
	} else {
		DrawArtStr(35, 218, AFT_SMALL, AFC_SILVER, "Players Supported: 1");
		DrawArtStr(35, 256, AFT_SMALL, AFC_SILVER, "Play by your self with");
		DrawArtStr(35, 275, AFT_SMALL, AFC_SILVER, "no network exposure.");
	}

	DrawArtStr(26, 356, AFT_MED, AFC_SILVER, "no gateway needed", JustCentre, 226);

	DrawArtStr(349, 429, AFT_BIG, AFC_GOLD, "OK");
	DrawArtStr(476, 429, AFT_BIG, AFC_GOLD, "Cancel");
}

void selconn_Load()
{
	LoadBackgroundArt("ui_art\\selconn.pcx");
	SelectedItem = 1;
	SelectedItemMax = 2;
}

void selconn_Free()
{
	mem_free_dbg(ArtBackground.data);
	ArtBackground.data = NULL;
}

int __stdcall UiSelectProvider(
    int a1,
    _SNETPROGRAMDATA *client_info,
    _SNETPLAYERDATA *user_info,
    _SNETUIDATA *ui_info,
    _SNETVERSIONDATA *file_info,
    int *type)
{
	selconn_Load();

	SDL_Event event;

	bool rv = true;
	bool endMenu = false;
	while (!endMenu) {
		CapFPS();
		selconn_Render();
		DrawMouse();
		UiFadeIn();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (UiFocuseNavigation(&event))
					break;
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					rv = false;
					endMenu = true;
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					UiPlaySelectSound();
					DWORD provider;
					switch (SelectedItem) {
					/*
					case 1:
						provider = 'BNET';
						break;
					case 2:
						provider = 'IPXN';
						break;
					case 3:
						provider = 'MODM';
						break;
					case 4:
						provider = 'SCBL';
						break;
					case 5:*/
					case 1:
						provider = 'UDPN';
						break;
					case 2:
						provider = 'SCBL';
						break;
					}
					selconn_Free();
					endMenu = SNetInitializeProvider('SCBL', client_info, user_info, ui_info, file_info);
					selconn_Load();
					break;
				}
				break;
			case SDL_QUIT:
				exit(0);
			}
		}
	}
	BlackPalette();

	selconn_Free();

	return rv;
}
