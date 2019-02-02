#include "../../types.h"

void selconn_Render()
{
	DrawArtImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, pPcxTitleImage);
	RenderDiabloLogoSm();

	PrintText30Silver(-1, 161, "Multi Player Game", JustCentre);

	int w = 334;
	int x = 280;
	int y = 261;

	PrintText30Silver(x, 211, "Select Connection", JustCentre, w);

	char *connections[5] = {
		"Battle.net",
		"Local Area Network (IPC)",
		"Modem",
		"Direct Cable Connection",
		"Local Area Network (UDP)"
	};

	int selectorTop = y;

	for (int i = 0; i < 5; i++) {
		PrintText16Gold(x - 1, y, connections[i], JustCentre, w);
		y += 26;
	}

	DrawSelector16(x, selectorTop - 2, w, 35, 26);

	PrintText16Silver(35, 218, "Players Supported: 4");

	PrintText16Silver(35, 256, "Requirements:");
	// TODO need a word wrap function
	PrintText16Silver(35, 275, "All computers must be");
	PrintText16Silver(35, 291, "connected to an");
	PrintText16Silver(35, 307, "IPX-compatible network.");

	PrintText24Silver(26, 356, "no gateway needed", JustCentre, 226);

	PrintText30Gold(349, 429, "OK");
	PrintText30Gold(476, 429, "Cancel");
}

void selconn_Loade()
{
	LoadTitelArt("ui_art\\selconn.pcx");
}

void selconn_Free()
{
	mem_free_dbg(pPcxTitleImage);
	pPcxTitleImage = NULL;
}

int __stdcall UiSelectProvider(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info,
    _SNETVERSIONDATA *file_info, int *type)
{
	selconn_Loade();

	SelectedItem = 1;
	SelectedItemMax = 5;
	SDL_Event event;

	bool endMenu = false;
	while (!endMenu) {
		CapFPS();
		selconn_Render();
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
					effects_play_sound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_DOWN:
					SelectedItem++;
					if (SelectedItem > SelectedItemMax) {
						SelectedItem = MAINMENU_SINGLE_PLAYER;
					}
					effects_play_sound("sfx\\items\\titlemov.wav");
					break;
				case SDLK_ESCAPE:
					if (PreviousItem[submenu]) {
						SetMenu(PreviousItem[submenu]);
						break;
					}
					return FALSE;
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
				case SDLK_SPACE:
					effects_play_sound("sfx\\items\\titlslct.wav");
					switch (SelectedItem) {
					case 1:
						endMenu = SNetInitializeProvider('BNET', client_info, user_info, ui_info, file_info);
						break;
					case 2:
						endMenu = SNetInitializeProvider('IPXN', client_info, user_info, ui_info, file_info);
						break;
					case 3:
						endMenu = SNetInitializeProvider('MODM', client_info, user_info, ui_info, file_info);
						break;
					case 4:
						endMenu = SNetInitializeProvider('SCBL', client_info, user_info, ui_info, file_info);
						break;
					case 5:
						endMenu = SNetInitializeProvider('UDPN', client_info, user_info, ui_info, file_info);
						break;
					}
					SelectedItem = 1;
					SelectedItemMax = 3;
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

	return TRUE;
}
