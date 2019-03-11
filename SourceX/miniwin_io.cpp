#include "pch.h"

namespace dvl {

extern "C" void TranslateFileName(char *dst, int dstLen, const char *src)
{
	for (int i = 0; i < dstLen; i++) {
		char c = *src++;
		dst[i] = c == '\\' ? '/' : c;
		if (!c) {
			break;
		}
	}
}

static std::set<HANDLE> files;

HANDLE CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	char name[260];
	TranslateFileName(name, sizeof(name), lpFileName);

	DUMMY_PRINT("file: %s (%s)", lpFileName, name);

	assert(dwDesiredAccess == DVL_GENERIC_READ | DVL_GENERIC_WRITE);

	int flags = O_RDWR;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (dwCreationDisposition == DVL_OPEN_EXISTING) {
		// Nothing
	} else if (dwCreationDisposition == DVL_CREATE_ALWAYS) {
		flags |= O_CREAT | O_TRUNC;
	} else {
		UNIMPLEMENTED();
	}
	HANDLE fd = (HANDLE)open(name, flags, mode);

	files.insert(fd);
	return fd;
}

WINBOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped)
{
	DUMMY_ONCE();

	assert(!lpOverlapped);
	int len = read((intptr_t)hFile, lpBuffer, nNumberOfBytesToRead);
	assert(len != -1);
	*lpNumberOfBytesRead = len;
	return TRUE;
}

DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
{
	DUMMY_ONCE();

	assert(!lpFileSizeHigh);
	struct stat s;
	int ret = fstat((intptr_t)hFile, &s);
	assert(ret == 0);
	return s.st_size;
}

WINBOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped)
{
	DUMMY_ONCE();

	assert(!lpOverlapped);
	ssize_t len = write((intptr_t)hFile, lpBuffer, nNumberOfBytesToWrite);
	if (len == -1) {
		*lpNumberOfBytesWritten = 0;
		return FALSE;
	}
	*lpNumberOfBytesWritten = (DWORD)len;
	return TRUE;
}

DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
	DUMMY_ONCE();

	assert(!lpDistanceToMoveHigh);
	int whence;
	if (dwMoveMethod == DVL_FILE_BEGIN) {
		whence = SEEK_SET;
	} else if (dwMoveMethod == DVL_FILE_CURRENT) {
		whence = SEEK_CUR;
	} else {
		UNIMPLEMENTED();
	}
	off_t ret = lseek((intptr_t)hFile, lDistanceToMove, whence);
	return (DWORD)ret;
}

WINBOOL SetEndOfFile(HANDLE hFile)
{
	DUMMY_ONCE();

	off_t cur = lseek((intptr_t)hFile, 0, SEEK_CUR);
	assert(cur != -1);
	int res = ftruncate((intptr_t)hFile, cur);
	assert(res == 0);
	return TRUE;
}

DWORD GetFileAttributesA(LPCSTR lpFileName)
{
	char name[260];
	TranslateFileName(name, sizeof(name), lpFileName);

	DUMMY_PRINT("file: %s (%s)", lpFileName, name);

	struct stat s;
	int res = stat(name, &s);

	if (res == -1) {
		SetLastError(DVL_ERROR_FILE_NOT_FOUND);
		return (DWORD)-1;
	}

	return 0x80;
}

WINBOOL SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes)
{
	DUMMY_PRINT("file: %s", lpFileName);
	return TRUE;
}

WINBOOL CloseHandle(HANDLE hObject)
{
	if (files.find(hObject) != files.end()) {
		int ret = close((intptr_t)hObject);
		assert(ret == 0);
		files.erase(hObject);
	}
	return TRUE;
}

}
