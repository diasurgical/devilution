/**
 * @file init.cpp
 *
 * Implementation of routines for initializing the environment, disable screen saver, load MPQ.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"
#include "../DiabloUI/diabloui.h"

_SNETVERSIONDATA fileinfo;
/** True if the game is the current active window */
int gbActive;
/** Specifies the path to diablo.exe. */
char diablo_exe_path[MAX_PATH];
/** A handle to an unused MPQ archive. */
HANDLE hellfire_mpq;
/** Specifies the path to patch_rt.mpq. */
char patch_rt_mpq_path[MAX_PATH];
/** The current input handler function */
WNDPROC CurrentProc;
/** A handle to the diabdat.mpq archive. */
HANDLE diabdat_mpq;
/** Specifies the path to diabdat.mpq. */
char diabdat_mpq_path[MAX_PATH];
/** A handle to the patch_rt.mpq archive. */
HANDLE patch_rt_mpq;
/** Specifies whether the MS Office Shortcut Bar was killed. */
BOOL killed_mom_parent;
/** Stores the previous state of the screensaver. */
BOOLEAN screensaver_enabled_prev;
#ifdef HELLFIRE
char hellfire_mpq_path[MAX_PATH];
char hfmonk_mpq_path[MAX_PATH];
char hfbard_mpq_path[MAX_PATH];
char hfbarb_mpq_path[MAX_PATH];
char hfmusic_mpq_path[MAX_PATH];
char hfvoice_mpq_path[MAX_PATH];
char hfopt1_mpq_path[MAX_PATH];
char hfopt2_mpq_path[MAX_PATH];
HANDLE hfmonk_mpq;
HANDLE hfbard_mpq;
HANDLE hfbarb_mpq;
HANDLE hfmusic_mpq;
HANDLE hfvoice_mpq;
HANDLE hfopt1_mpq;
HANDLE hfopt2_mpq;
#endif

/* data */

char gszVersionNumber[MAX_PATH] = "internal version unknown";
char gszProductName[MAX_PATH] = "Diablo v1.09";

static void init_run_office(char *dir)
{
	HANDLE hSearch;
	WIN32_FIND_DATA find;
	char szFirst[MAX_PATH];

	strcpy(szFirst, dir);
	if (szFirst[0] != '\0' && szFirst[strlen(szFirst) - 1] == '\\') {
		strcat(szFirst, "*");
	} else {
		strcat(szFirst, "\\*");
	}
	hSearch = FindFirstFile(szFirst, &find);
	if (hSearch == INVALID_HANDLE_VALUE) {
		return;
	}

	while (1) {
		if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (strcmp(find.cFileName, ".") != 0 && strcmp(find.cFileName, "..") != 0) {
				char szNext[MAX_PATH] = "";
				if (dir[0] != '\0' && dir[strlen(dir) - 1] == '\\') {
					sprintf(szNext, "%s%s\\", dir, find.cFileName);
				} else {
					sprintf(szNext, "%s\\%s\\", dir, find.cFileName);
				}
				init_run_office(szNext);
			}
		} else if (_strcmpi(find.cFileName, "Microsoft Office Shortcut Bar.lnk") == 0) {
			ShellExecute(GetDesktopWindow(), "open", find.cFileName, "", dir, SW_SHOWNORMAL);
		}
		if (!FindNextFile(hSearch, &find)) {
			break;
		}
	}

	FindClose(hSearch);
}

static HWND init_find_mom_parent()
{
	HWND i, handle;
	char ClassName[256];

	for (i = GetForegroundWindow();; i = GetWindow(handle, GW_HWNDNEXT)) {
		handle = i;
		if (!i)
			break;
		GetClassName(i, ClassName, 255);
		if (!_strcmpi(ClassName, "MOM Parent"))
			break;
	}
	return handle;
}

static void init_kill_mom_parent()
{
	HWND handle;

	handle = init_find_mom_parent();
	if (handle != NULL) {
		PostMessage(handle, WM_CLOSE, 0, 0);
		killed_mom_parent = TRUE;
	}
}

static void init_await_mom_parent_exit()
{
	DWORD tick;

	tick = GetTickCount();
	if (!init_find_mom_parent()) {
		return;
	}
	do {
		Sleep(250);
	} while (GetTickCount() - tick <= 4000 && init_find_mom_parent() != NULL);
}

static void init_run_office_from_start_menu()
{
	LPITEMIDLIST idl;

	if (!killed_mom_parent) {
		return;
	}

	killed_mom_parent = FALSE;
	char szPath[256] = ""; /// BUGFIX: size should be at least 'MAX_PATH'
	idl = NULL;

	if (SHGetSpecialFolderLocation(GetDesktopWindow(), CSIDL_STARTMENU, &idl) == NOERROR) {
		SHGetPathFromIDList(idl, szPath);
		init_run_office(szPath);
	}
}

static void init_disable_screensaver(BOOLEAN disable)
{
	BOOLEAN enabled;
	char Data[16];
	DWORD Type, cbData;
	HKEY phkResult;
	LRESULT success;

	// BUGFIX: this is probably the worst possible way to do this. Alternatives: ExtEscape() with SETPOWERMANAGEMENT,
	// SystemParametersInfo() with SPI_SETSCREENSAVEACTIVE/SPI_SETPOWEROFFACTIVE/SPI_SETLOWPOWERACTIVE

	success = RegOpenKeyEx(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, (PHKEY)&phkResult);
	if (success != ERROR_SUCCESS) {
		return;
	}

	if (disable) {
		cbData = 16;
		success = RegQueryValueEx(phkResult, "ScreenSaveActive", NULL, &Type, (LPBYTE)Data, &cbData);
		if (success == ERROR_SUCCESS)
			screensaver_enabled_prev = Data[0] != '0';
		enabled = FALSE;
	} else {
		enabled = screensaver_enabled_prev;
	}

	Data[0] = enabled ? '1' : '0';
	Data[1] = 0;
	RegSetValueEx(phkResult, "ScreenSaveActive", NULL, REG_SZ, (const BYTE *)Data, 2);
	RegCloseKey(phkResult);
}

void init_cleanup(BOOL show_cursor)
{
	pfile_flush_W();
	init_disable_screensaver(FALSE);
	init_run_office_from_start_menu();

	if (diabdat_mpq) {
		SFileCloseArchive(diabdat_mpq);
		diabdat_mpq = NULL;
	}
	if (patch_rt_mpq) {
		SFileCloseArchive(patch_rt_mpq);
		patch_rt_mpq = NULL;
	}
	if (hellfire_mpq) {
		SFileCloseArchive(hellfire_mpq);
		hellfire_mpq = NULL;
	}
#ifdef HELLFIRE
	if (hfmonk_mpq) {
		SFileCloseArchive(hfmonk_mpq);
		hfmonk_mpq = NULL;
	}
	if (hfbard_mpq) {
		SFileCloseArchive(hfbard_mpq);
		hfbard_mpq = NULL;
	}
	if (hfbarb_mpq) {
		SFileCloseArchive(hfbarb_mpq);
		hfbarb_mpq = NULL;
	}
	if (hfmusic_mpq) {
		SFileCloseArchive(hfmusic_mpq);
		hfmusic_mpq = NULL;
	}
	if (hfvoice_mpq) {
		SFileCloseArchive(hfvoice_mpq);
		hfvoice_mpq = NULL;
	}
	if (hfopt1_mpq) {
		SFileCloseArchive(hfopt1_mpq);
		hfopt1_mpq = NULL;
	}
	if (hfopt2_mpq) {
		SFileCloseArchive(hfopt2_mpq);
		hfopt2_mpq = NULL;
	}
#endif
	UiDestroy();
	effects_cleanup_sfx();
	sound_cleanup();
	NetClose();
	dx_cleanup();
	engine_debug_trap(show_cursor);
	StormDestroy();

	if (show_cursor)
		ShowCursor(TRUE);
}

static void init_strip_trailing_slash(char *path)
{
	char *result;

	result = strrchr(path, '\\');
	if (result) {
		if (!result[1])
			*result = 0;
	}
}

static BOOL init_read_test_file(char *pszPath, const char *pszArchive, int dwPriority, HANDLE *phArchive)
{
	DWORD dwSize;
	char *pszDrive, *pszRoot;
	char szDrive[MAX_PATH];

	dwSize = GetLogicalDriveStrings(sizeof(szDrive), szDrive);
	if (dwSize == 0 || dwSize > sizeof(szDrive)) {
		return FALSE;
	}

	while (*pszArchive == '\\') {
		pszArchive++;
	}

	pszDrive = szDrive;
	if (*pszDrive == '\0') {
		return FALSE;
	}
	while (1) {
		pszRoot = pszDrive;
		while (*pszDrive++ != '\0')
			;
		if (GetDriveType(pszRoot) == DRIVE_CDROM) {
			strcpy(pszPath, pszRoot);
			strcat(pszPath, pszArchive);
			if (SFileOpenArchive(pszPath, dwPriority, FS_CD, phArchive)) {
				break;
			}
		}
		if (*pszDrive == '\0') {
			return FALSE;
		}
	}

	return TRUE;
}

static HANDLE init_test_access(char *mpq_path, const char *mpq_name, const char *reg_loc, int dwPriority, int fs)
{
	char *last_slash_pos;
	char Filename[MAX_PATH];
	char Buffer[MAX_PATH];
	char archive_path[MAX_PATH];
	HANDLE archive;

	if (!GetCurrentDirectory(sizeof(Buffer), Buffer))
		app_fatal("Can't get program path");
	init_strip_trailing_slash(Buffer);
	if (!SFileSetBasePath(Buffer))
		app_fatal("SFileSetBasePath");
	if (!GetModuleFileName(ghInst, Filename, sizeof(Filename)))
		app_fatal("Can't get program name");
	last_slash_pos = strrchr(Filename, '\\');
	if (last_slash_pos)
		*last_slash_pos = '\0';
	init_strip_trailing_slash(Filename);
	strcpy(mpq_path, Buffer);
	strcat(mpq_path, mpq_name);
	if (SFileOpenArchive(mpq_path, dwPriority, fs, &archive))
		return archive;
	if (strcmp(Filename, Buffer)) {
		strcpy(mpq_path, Filename);
		strcat(mpq_path, mpq_name);
		if (SFileOpenArchive(mpq_path, dwPriority, fs, &archive))
			return archive;
	}
	archive_path[0] = '\0';
	if (reg_loc) {
		if (SRegLoadString("Archives", reg_loc, 0, archive_path, sizeof(archive_path))) {
			init_strip_trailing_slash(archive_path);
			strcpy(mpq_path, archive_path);
			strcat(mpq_path, mpq_name);
			if (SFileOpenArchive(mpq_path, dwPriority, fs, &archive))
				return archive;
		}
	}
	if (fs != FS_PC && init_read_test_file(archive_path, mpq_name, dwPriority, &archive)) {
		strcpy(mpq_path, archive_path);
		return archive;
	}
	return NULL;
}

static void init_get_file_info()
{
	DWORD dwLen;
	void *pBlock;
	unsigned int uBytes;
	DWORD dwHandle;
	VS_FIXEDFILEINFO *lpBuffer;

	if (GetModuleFileName(ghInst, diablo_exe_path, sizeof(diablo_exe_path))) {
		dwLen = GetFileVersionInfoSize(diablo_exe_path, &dwHandle);
		if (dwLen) {
			pBlock = DiabloAllocPtr(dwLen);
			if (GetFileVersionInfo(diablo_exe_path, 0, dwLen, pBlock)) {
				if (VerQueryValue(pBlock, "\\", (LPVOID *)&lpBuffer, &uBytes))
					sprintf(
					    gszVersionNumber,
					    "version %d.%d.%d.%d",
					    lpBuffer->dwProductVersionMS >> 16,
					    lpBuffer->dwProductVersionMS & 0xFFFF,
					    lpBuffer->dwProductVersionLS >> 16,
					    lpBuffer->dwProductVersionLS & 0xFFFF);
			}
			mem_free_dbg(pBlock);
		}
	}
}

static void init_archives()
{
	HANDLE fh;
#ifdef COPYPROT
	int result;
#endif
	memset(&fileinfo, 0, sizeof(fileinfo));
	fileinfo.size = sizeof(fileinfo);
	fileinfo.versionstring = gszVersionNumber;
	fileinfo.executablefile = diablo_exe_path;
	fileinfo.originalarchivefile = diabdat_mpq_path;
	fileinfo.patcharchivefile = patch_rt_mpq_path;
	init_get_file_info();
#ifdef COPYPROT
	while (1) {
#endif
#ifdef SPAWN
		diabdat_mpq = init_test_access(diabdat_mpq_path, "\\spawn.mpq", "DiabloSpawn", 1000, FS_PC);
#else
#ifdef COPYPROT
	diabdat_mpq = init_test_access(diabdat_mpq_path, "\\diabdat.mpq", "DiabloCD", 1000, FS_CD);
#else
	diabdat_mpq = init_test_access(diabdat_mpq_path, "\\diabdat.mpq", "DiabloCD", 1000, FS_PC);
#endif
#endif
#ifdef COPYPROT
		if (diabdat_mpq != NULL)
			break;
		UiCopyProtError(&result);
		if (result == COPYPROT_CANCEL)
			FileErrDlg("diabdat.mpq");
	}
#endif
	if (!WOpenFile("ui_art\\title.pcx", &fh, TRUE))
#ifdef SPAWN
		FileErrDlg("Main program archive: spawn.mpq");
#else
		FileErrDlg("Main program archive: diabdat.mpq");
#endif
	WCloseFile(fh);
#ifdef SPAWN
	patch_rt_mpq = init_test_access(patch_rt_mpq_path, "\\patch_sh.mpq", "DiabloSpawn", 2000, FS_PC);
#else
	patch_rt_mpq = init_test_access(patch_rt_mpq_path, "\\patch_rt.mpq", "DiabloInstall", 2000, FS_PC);
#endif
#ifdef HELLFIRE
	hellfire_mpq = init_test_access(hellfire_mpq_path, "\\hellfire.mpq", "DiabloInstall", 8000, FS_PC);
	hfmonk_mpq = init_test_access(hfmonk_mpq_path, "\\hfmonk.mpq", "DiabloInstall", 8100, FS_PC);
	hfbard_mpq = init_test_access(hfbard_mpq_path, "\\hfbard.mpq", "DiabloInstall", 8110, FS_PC);
	hfbarb_mpq = init_test_access(hfbarb_mpq_path, "\\hfbarb.mpq", "DiabloInstall", 8120, FS_PC);
	hfmusic_mpq = init_test_access(hfmusic_mpq_path, "\\hfmusic.mpq", "DiabloInstall", 8200, FS_PC);
	hfvoice_mpq = init_test_access(hfvoice_mpq_path, "\\hfvoice.mpq", "DiabloInstall", 8500, FS_PC);
	hfopt1_mpq = init_test_access(hfopt1_mpq_path, "\\hfopt1.mpq", "DiabloInstall", 8600, FS_PC);
	hfopt2_mpq = init_test_access(hfopt2_mpq_path, "\\hfopt2.mpq", "DiabloInstall", 8610, FS_PC);
#endif
}

void init_create_window(int nCmdShow)
{
	int nWidth, nHeight;
	HWND hWnd;
	WNDCLASSEXA wcex;

	init_kill_mom_parent();
	pfile_init_save_directory();
	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = ghInst;
	wcex.hIcon = LoadIcon(ghInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = GAME_NAME;
	wcex.lpszClassName = "DIABLO";
	wcex.hIconSm = (HICON)LoadImage(ghInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	if (!RegisterClassEx(&wcex))
		app_fatal("Unable to register window class");
	if (GetSystemMetrics(SM_CXSCREEN) < SCREEN_WIDTH)
		nWidth = SCREEN_WIDTH;
	else
		nWidth = GetSystemMetrics(SM_CXSCREEN);
	if (GetSystemMetrics(SM_CYSCREEN) < SCREEN_HEIGHT)
		nHeight = SCREEN_HEIGHT;
	else
		nHeight = GetSystemMetrics(SM_CYSCREEN);
	hWnd = CreateWindowEx(0, "DIABLO", GAME_NAME, WS_POPUP, 0, 0, nWidth, nHeight, NULL, NULL, ghInst, NULL);
	if (!hWnd)
		app_fatal("Unable to create main window");
	ShowWindow(hWnd, SW_SHOWNORMAL); // nCmdShow used only in beta: ShowWindow(hWnd, nCmdShow)
	UpdateWindow(hWnd);
	init_await_mom_parent_exit();
	dx_init(hWnd);
	BlackPalette();
	snd_init(hWnd);
	init_archives();
	init_disable_screensaver(TRUE);
}

static void init_activate_window(HWND hWnd, BOOL bActive)
{
	LONG dwNewLong;

	gbActive = bActive;
	UiAppActivate(bActive);
	dwNewLong = GetWindowLong(hWnd, GWL_STYLE);

	if (gbActive && fullscreen)
		dwNewLong &= ~WS_SYSMENU;
	else
		dwNewLong |= WS_SYSMENU;

	SetWindowLong(hWnd, GWL_STYLE, dwNewLong);

	if (gbActive) {
		force_redraw = 255;
		ResetPal();
	}
}

LRESULT __stdcall MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
	case WM_ERASEBKGND:
		return 0;
	case WM_CREATE:
		ghMainWnd = hWnd;
		break;
	case WM_DESTROY:
		init_cleanup(TRUE);
		ghMainWnd = NULL;
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		force_redraw = 255;
		break;
	case WM_CLOSE:
		return 0;
	case WM_ACTIVATEAPP:
		init_activate_window(hWnd, wParam);
		break;
#ifdef _DEBUG
	case WM_SYSKEYUP:
		if (wParam == VK_RETURN) {
			fullscreen = !fullscreen;
			dx_reinit();
			return 0;
		}
		break;
#endif
	case WM_QUERYNEWPALETTE:
		SDrawRealizePalette();
		return 1;
	case WM_PALETTECHANGED:
		if ((HWND)wParam != hWnd)
			SDrawRealizePalette();
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (CurrentProc)
		return CurrentProc(hWnd, Msg, wParam, lParam);

	return MainWndProc(hWnd, Msg, wParam, lParam);
}

WNDPROC SetWindowProc(WNDPROC NewProc)
{
	WNDPROC OldProc;

	OldProc = CurrentProc;
	CurrentProc = NewProc;
	return OldProc;
}
