/**
 * @file restrict.cpp
 *
 * Implementation of functionality for checking if the game will be able run on the system.
 */
#include "all.h"

/**
 * @brief Check that the OS version is the minimum required by the game
 * @return True if suported
 */
BOOL SystemSupported()
{
	OSVERSIONINFO VersionInformation;
	BOOL ret = FALSE;

	memset(&VersionInformation, 0, sizeof(VersionInformation));
	VersionInformation.dwOSVersionInfoSize = sizeof(VersionInformation);
	if (GetVersionEx(&VersionInformation)
	    && VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT
	    && VersionInformation.dwMajorVersion >= 5) {
		ret = TRUE;
	}
	return ret;
}

/**
 * @brief Check that we have write access to the Windows install folder
 * @return False if we have write access

 */
BOOL RestrictedTest()
{
	FILE *f;
	char Buffer[MAX_PATH];
	BOOL ret = FALSE;

	if (SystemSupported() && GetWindowsDirectory(Buffer, sizeof(Buffer))) {
		strcat(Buffer, "\\Diablo1RestrictedTest.foo");
		f = fopen(Buffer, "wt");
		if (f) {
			fclose(f);
			remove(Buffer);
		} else {
			ret = TRUE;
		}
	}
	return ret;
}

/**
 * @brief Check that we have write access to the game install folder
 * @return False if we have write access

 */
BOOL ReadOnlyTest()
{
	char *c;
	FILE *f;
	char Filename[MAX_PATH];
	BOOL ret = FALSE;

	if (GetModuleFileName(ghInst, Filename, sizeof(Filename))) {
		c = strrchr(Filename, '\\');
		if (c) {
			strcpy(c + 1, "Diablo1ReadOnlyTest.foo");
			f = fopen(Filename, "wt");
			if (f) {
				fclose(f);
				remove(Filename);
			} else {
				ret = TRUE;
			}
		}
	}
	return ret;
}
