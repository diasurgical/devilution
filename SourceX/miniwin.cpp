#include "pch.h"
#include <sys/statvfs.h>

DWORD last_error;

DWORD WINAPI GetLastError(VOID)
{
	return last_error;
}

VOID WINAPI SetLastError(DWORD dwErrCode)
{
	last_error = dwErrCode;
}

char __cdecl *_strlwr(char *str)
{
	for (char *p = str; *p; ++p) {
		*p = tolower(*p);
	}
	return str;
}

int WINAPIV wsprintfA(LPSTR dest, LPCSTR format, ...)
{
	va_list args;
	va_start(args, format);
	return vsprintf(dest, format, args);
}

int WINAPIV wvsprintfA(LPSTR dest, LPCSTR format, va_list arglist)
{
	return vsnprintf(dest, 256, format, arglist);
}

int __cdecl _strcmpi(const char *_Str1, const char *_Str2)
{
	return strcasecmp(_Str1, _Str2);
}

char *__cdecl _itoa(int _Value, char *_Dest, int _Radix)
{
	UNIMPLEMENTED();
}

DWORD WINAPI GetTickCount(VOID)
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

VOID WINAPI Sleep(DWORD dwMilliseconds)
{
	usleep(dwMilliseconds * 1000);
}

HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	DUMMY();
	return (HANDLE)-1;
}

WINBOOL WINAPI FindClose(HANDLE hFindFile)
{
	UNIMPLEMENTED();
}

/**
 * @brief Normally this would get the Windows install, but Diablo uses it to find the old save game folder
 */
UINT WINAPI GetWindowsDirectoryA(LPSTR lpBuffer, UINT uSize)
{
	char *name = SDL_GetPrefPath("diasurgical", "devilution");
	strncpy(lpBuffer, name, uSize);

	return strlen(name);
}

WINBOOL WINAPI GetDiskFreeSpaceA(LPCSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector,
                                 LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters)
{
	struct statvfs fiData;
	int success = statvfs("/", &fiData);
	*lpBytesPerSector = fiData.f_frsize;
	*lpSectorsPerCluster = 1;
	*lpNumberOfFreeClusters = fiData.f_bavail;
	*lpTotalNumberOfClusters = fiData.f_blocks;

	return success >= 0;
}

/**
 * @brief Used for getting save path, by removing up to and including the last "\"
 */
DWORD WINAPI GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
{
	char *name = SDL_GetPrefPath("diasurgical", "devilution");

	if (strlen(name) >= nSize) {
		printf("Save path longer then %d: %s\n", nSize, name);
		ABORT();
	}

	strncpy(lpFilename, name, nSize);
	SDL_free(name);

	int len = strlen(lpFilename);
	lpFilename[len - 1] = '\\';

	return len;
}

WINBOOL WINAPI GetComputerNameA(LPSTR lpBuffer, LPDWORD nSize)
{
	DUMMY();
	strncpy(lpBuffer, "localhost", *nSize);
	*nSize = strlen(lpBuffer);
}

WINBOOL WINAPI DeleteFileA(LPCSTR lpFileName)
{
	UNIMPLEMENTED();
}

WINBOOL WINAPI CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, WINBOOL bFailIfExists)
{
	UNIMPLEMENTED();
}

HFILE WINAPI OpenFile(LPCSTR lpFileName, LPOFSTRUCT lpReOpenBuff, UINT uStyle)
{
	DUMMY();
	return HFILE_ERROR;
}

HWND WINAPI SetCapture(HWND hWnd)
{
	DUMMY_ONCE();
	return hWnd;
}

WINBOOL WINAPI ReleaseCapture(VOID)
{
	DUMMY_ONCE();
	return TRUE;
}

WINBOOL WINAPI DestroyWindow(HWND hWnd)
{
	DUMMY();
	return TRUE;
}

HWND WINAPI GetLastActivePopup(HWND hWnd)
{
	UNIMPLEMENTED();
}

HWND WINAPI GetTopWindow(HWND hWnd)
{
	UNIMPLEMENTED();
}

WINBOOL WINAPI SetForegroundWindow(HWND hWnd)
{
	UNIMPLEMENTED();
}

HWND WINAPI SetFocus(HWND hWnd)
{
	UNIMPLEMENTED();
}

HWND WINAPI FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName)
{
	DUMMY_PRINT("class: %s window: %s", nullstr(lpClassName), nullstr(lpWindowName));
	return NULL;
}

VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo)
{
	DUMMY();
	memset(lpSystemInfo, 0, sizeof(*lpSystemInfo));
	lpSystemInfo->dwPageSize = 4096;
}

HDC WINAPI GetDC(HWND hWnd)
{
	UNIMPLEMENTED();
}

int WINAPI ReleaseDC(HWND hWnd, HDC hDC)
{
	UNIMPLEMENTED();
}

int WINAPI GetDeviceCaps(HDC hdc, int index)
{
	SDL_DisplayMode current;

	SDL_GetCurrentDisplayMode(0, &current);

	if (index == HORZRES) {
		return current.w;
	} else if (index == VERTRES) {
		current.h;
	}

	return 0;
}

BOOL GetWindowRect(HWND hDlg, tagRECT *Rect)
{
	int x, y, w, h;
	SDL_SetWindowPosition(window, &x, &y);
	SDL_GetWindowSize(window, &w, h);

	Rect->right = x;
	Rect->top = y;
	Rect->left = w + x;
	Rect->bottom = h + y;

	return TRUE;
}

UINT WINAPI GetSystemPaletteEntries(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries)
{
	UNIMPLEMENTED();
}

WINBOOL WINAPI CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
                              LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles, DWORD dwCreationFlags,
                              LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo,
                              LPPROCESS_INFORMATION lpProcessInformation)
{
	UNIMPLEMENTED();
}

VOID WINAPI ExitProcess(UINT uExitCode)
{
	UNIMPLEMENTED();
}

DWORD WINAPI GetCurrentProcessId(VOID)
{
	UNIMPLEMENTED();
}

HANDLE WINAPI CreateFileMappingA(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect,
                                 DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName)
{
	DUMMY();
	assert(hFile == (HANDLE)-1);
	return NULL;
}

LPVOID WINAPI MapViewOfFile(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh,
                            DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap)
{
	UNIMPLEMENTED();
}

WINBOOL WINAPI UnmapViewOfFile(LPCVOID lpBaseAddress)
{
	UNIMPLEMENTED();
}

DWORD WINAPI WaitForInputIdle(HANDLE hProcess, DWORD dwMilliseconds)
{
	UNIMPLEMENTED();
}

HWND WINAPI GetForegroundWindow(VOID)
{
	UNIMPLEMENTED();
}

HWND WINAPI GetWindow(HWND hWnd, UINT uCmd)
{
	UNIMPLEMENTED();
}

DWORD WINAPI GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId)
{
	UNIMPLEMENTED();
}

DWORD WINAPI GetPrivateProfileStringA(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString,
                                      DWORD nSize, LPCSTR lpFileName)
{
	if (!SRegLoadString(lpAppName, lpKeyName, 0, lpReturnedString, nSize)) {
		strncpy(lpReturnedString, lpDefault, nSize);
		SRegSaveString(lpAppName, lpKeyName, 0, lpReturnedString);
	}
}

int MessageBoxA(HWND hWnd, const char *Text, const char *Title, UINT Flags)
{
	Uint32 SDLFlags = 0;
	if (Flags & MB_ICONHAND) {
		SDLFlags |= SDL_MESSAGEBOX_ERROR;
	} else if (Flags & MB_ICONEXCLAMATION) {
		SDLFlags |= SDL_MESSAGEBOX_WARNING;
	}

	SDL_ShowSimpleMessageBox(SDLFlags, Title, Text, window) < 0 ? -1 : 0;
}

LSTATUS RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)
{
	return 1;
};

/**
 * @brief This is only ever used to enable or disable the screen saver in a hackish way
 * For all other settings operation SReg* from Storm is used instead.
 */
LSTATUS RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, BYTE *lpData, LPDWORD lpcbData)
{
	if (SDL_IsScreenSaverEnabled()) {
		lpData[0] = '0';
		lpData[1] = '\0';
	}

	return 1;
};

/**
 * @brief This is only ever used to enable or disable the screen saver in a hackish way
 * For all other settings operation SReg* from Storm is used instead.
 */
LSTATUS RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData)
{
	if (lpData[0] == '0') {
		SDL_DisableScreenSaver();
	} else {
		SDL_EnableScreenSaver();
	}

	return 1;
};

LSTATUS RegCloseKeyA(HKEY hKey)
{
	return 1;
};

void PostQuitMessage(int nExitCode)
{
	DUMMY(); // Possibly use SDL_PumpEvents
}

LRESULT DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	DUMMY();
}

LONG GetWindowLongA(HWND hWnd, int nIndex)
{
	DUMMY();
}

LONG SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
	DUMMY();
}
