//HEADER_GOES_HERE

#include "../types.h"

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
