#include <dirent.h>
#include <string>

#include "../types.h"
#include "stubs.h"

#ifndef NO_GLOBALS
void *diabdat_mpq;
void *patch_rt_mpq;

_SNETVERSIONDATA fileinfo;
WNDPROC CurrentProc;
int gbActive;
#endif

char gszVersionNumber[260];
char gszProductName[260];

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
	for (auto dir : {".", "..", "../.."}) {
		auto path = find_file_in_directory(dir, file);
		if (!path.empty()) {
			return path;
		}
	}

	TermMsg("Required file %s not found", file);
}

void __fastcall init_create_window(int nCmdShow)
{
	DUMMY();

	init_get_file_info();

	// pfile_init_save_directory();

	dx_init(NULL);
	snd_init(NULL);

	init_archives();
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
	DUMMY();

	SFileOpenArchive(find_file_in_std_directories("diabdat.mpq").c_str(), 1000, 0, &diabdat_mpq);
	assert(diabdat_mpq);

	SFileOpenArchive(find_file_in_std_directories("patch_rt.mpq").c_str(), 1000, 0, &patch_rt_mpq);
	assert(patch_rt_mpq);
}

void __cdecl init_get_file_info()
{
	strcpy(gszVersionNumber, "0.1");
	strcpy(gszProductName, "devil-test");
}