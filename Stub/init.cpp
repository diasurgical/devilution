//HEADER_GOES_HERE

#include "../types.h"

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
	//sound_cleanup();
	NetClose();
	dx_cleanup();
	MI_Dummy(show_cursor);
	//StormDestroy();

	if (show_cursor)
		ShowCursor(TRUE);
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

void __fastcall init_create_window(int nCmdShow)
{
	DUMMY();

	pfile_init_save_directory();

	dx_init(NULL);
	snd_init(NULL);

	init_archives();
	gmenu_init_menu();
}

LRESULT __stdcall MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	UNIMPLEMENTED();
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
