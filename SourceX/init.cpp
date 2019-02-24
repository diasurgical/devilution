#include "pch.h"

_SNETVERSIONDATA fileinfo;
int gbActive; // weak
char diablo_exe_path[260];
void *unused_mpq;
char patch_rt_mpq_path[260];
WNDPROC CurrentProc;
void *diabdat_mpq;
char diabdat_mpq_path[260];
void *patch_rt_mpq;
int killed_mom_parent; // weak
BOOLEAN screensaver_enabled_prev;

/* data */

char gszVersionNumber[260] = "internal version unknown";
char gszProductName[260] = "Diablo v1.09";

void __fastcall init_cleanup(BOOL show_cursor)
{
	pfile_flush_W();
	init_disable_screensaver(0);
	init_run_office_from_start_menu();

	if (diabdat_mpq) {
		SFileCloseArchive(diabdat_mpq);
		diabdat_mpq = NULL;
	}
	if (patch_rt_mpq) {
		SFileCloseArchive(patch_rt_mpq);
		patch_rt_mpq = NULL;
	}
	if (unused_mpq) {
		SFileCloseArchive(unused_mpq);
		unused_mpq = NULL;
	}

	UiDestroy();
	effects_cleanup_sfx();
	sound_cleanup();
	NetClose();
	dx_cleanup();
	MI_Dummy(show_cursor);
	StormDestroy();

	if (show_cursor)
		ShowCursor(TRUE);
}

void __cdecl init_run_office_from_start_menu()
{
	DUMMY();
}
// 634CA0: using guessed type int killed_mom_parent;

// SDL_DisableScreenSaver
void __fastcall init_disable_screensaver(BOOLEAN disable)
{
	BOOLEAN v1;     // al
	char Data[16];  // [esp+4h] [ebp-20h]
	DWORD Type;     // [esp+14h] [ebp-10h]
	DWORD cbData;   // [esp+18h] [ebp-Ch]
	HKEY phkResult; // [esp+1Ch] [ebp-8h]
	BOOLEAN v6;     // [esp+20h] [ebp-4h]

	// BUGFIX: this is probably the worst possible way to do this. Alternatives: ExtEscape() with SETPOWERMANAGEMENT,
	// SystemParametersInfo() with SPI_SETSCREENSAVEACTIVE/SPI_SETPOWEROFFACTIVE/SPI_SETLOWPOWERACTIVE

	v6 = disable;
	if (!RegOpenKeyEx(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, &phkResult)) {
		if (v6) {
			cbData = 16;
			if (!RegQueryValueEx(phkResult, "ScreenSaveActive", 0, &Type, (LPBYTE)Data, &cbData))
				screensaver_enabled_prev = Data[0] != '0';
			v1 = 0;
		} else {
			v1 = screensaver_enabled_prev;
		}
		Data[1] = 0;
		Data[0] = (v1 != 0) + '0';
		RegSetValueEx(phkResult, "ScreenSaveActive", 0, REG_SZ, (const BYTE *)Data, 2u);
		RegCloseKey(phkResult);
	}
}

/**
 * Case insensitive search for a file name in a directory.
 * @return Empty string when not found.
 */
static std::string find_file_in_directory(const char *dirpath, const char *file)
{
	DIR *dir = opendir(dirpath);
	if (!dir) {
		return "";
	}

	struct dirent *entry;
	std::string result;
	while ((entry = readdir(dir)) != NULL) {
		if (strcasecmp(entry->d_name, file) == 0) {
			result = std::string(dirpath) + "/" + entry->d_name;
			break;
		}
	}
	closedir(dir);

	return result;
}

static std::string find_file_in_std_directories(const char *file)
{
	for (auto dir : { ".", "..", "../.." }) {
		auto path = find_file_in_directory(dir, file);

		if (!path.empty()) {
			printf("%s \n", path.c_str());
			return path;
		}
	}

	TermMsg("Required file %s not found", file);
}

void FakeWMDestroy()
{
	MainWndProc(NULL, WM_DESTROY, NULL, NULL);
}

void __fastcall init_create_window(int nCmdShow)
{
	DUMMY();

	pfile_init_save_directory();
	atexit(SDL_Quit);
	atexit(TTF_Quit);
	SDL_Init(SDL_INIT_EVERYTHING);

	int flags = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_INPUT_GRABBED;
	if (!fullscreen) {
		flags = SDL_WINDOW_RESIZABLE;
	}
	window = SDL_CreateWindow("Diablo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	printf("Window And Renderer Created!\n");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	assert(surface);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	assert(texture);

	palette = SDL_AllocPalette(256);

	j_lock_buf_priv(0); //FIXME 0?

	dx_init(NULL);
	snd_init(NULL);

	init_archives();
	gmenu_init_menu();
	atexit(FakeWMDestroy);
}

LRESULT __stdcall MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg > WM_ERASEBKGND) {
		if (Msg == WM_ACTIVATEAPP) {
			init_activate_window(hWnd, wParam);
		} else {
			if (Msg == WM_QUERYNEWPALETTE) {
				SDrawRealizePalette();
				return 1;
			}
			if (Msg == WM_PALETTECHANGED && (HWND)wParam != hWnd)
				SDrawRealizePalette();
		}
	} else {
		switch (Msg) {
		case WM_ERASEBKGND:
			return 0;
		case WM_CREATE:
			ghMainWnd = hWnd;
			break;
		case WM_DESTROY:
			init_cleanup(1);
			ghMainWnd = 0;
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			drawpanflag = 255;
			break;
		case WM_CLOSE:
			return 0;
		}
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void __fastcall init_activate_window(HWND hWnd, BOOLEAN bActive)
{
	LONG dwNewLong; // eax

	gbActive = bActive;
	UiAppActivate(bActive);
	dwNewLong = GetWindowLong(hWnd, GWL_STYLE);

	if (gbActive && fullscreen)
		dwNewLong &= ~WS_SYSMENU;
	else
		dwNewLong |= WS_SYSMENU;

	SetWindowLong(hWnd, GWL_STYLE, dwNewLong);

	if (gbActive) {
		drawpanflag = 255;
		ResetPal();
	}
}
// 52571C: using guessed type int drawpanflag;
// 634980: using guessed type int gbActive;

LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result; // eax

	if (CurrentProc)
		result = CurrentProc(hWnd, Msg, wParam, lParam);
	else
		result = MainWndProc(hWnd, Msg, wParam, lParam);
	return result;
}

WNDPROC __fastcall SetWindowProc(WNDPROC NewProc)
{
	WNDPROC OldProc = CurrentProc;
	CurrentProc = NewProc;
	return OldProc;
}

void __cdecl init_archives()
{
	DUMMY(); // We will need to remove the find_file_in_std_directories funct when it comes to mobile

	SFileOpenArchive(find_file_in_std_directories("diabdat.mpq").c_str(), 1000, MPQ_FLAG_READ_ONLY, &diabdat_mpq);
	assert(diabdat_mpq);

	SFileOpenArchive("patch_rt.mpq", 1000, MPQ_FLAG_READ_ONLY, &patch_rt_mpq);
}

void GetAvailableHeroes()
{
}

void HideCursor()
{
	Uint8 l_data[1];
	Uint8 l_mask[1];

	l_data[0] = 0;
	l_mask[0] = 0;

	SDL_Cursor *g_cursor = SDL_CreateCursor(l_data, l_mask, 1, 1, 0, 0);
	SDL_SetCursor(g_cursor);
}
