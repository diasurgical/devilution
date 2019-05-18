#include "diablo.h"
#include "../3rdParty/Storm/Source/storm.h"

#ifdef __cplusplus
static CCritSect sgMemCrit;
#endif
CHAR FileName[MAX_PATH]; // idb
char log_buffer[388];
LPCVOID lpAddress;           // idb
DWORD nNumberOfBytesToWrite; // idb

/* data */

int log_not_created = 1;              // weak
HANDLE log_file = INVALID_HANDLE_VALUE;

void __cdecl log_flush(BOOL force_close)
{
	DWORD NumberOfBytesWritten;

#ifdef __cplusplus
	sgMemCrit.Enter();
#endif
	if (nNumberOfBytesToWrite) {
		if (log_file == INVALID_HANDLE_VALUE) {
			log_file = log_create();
			if (log_file == INVALID_HANDLE_VALUE) {
				nNumberOfBytesToWrite = 0;
				return;
			}
			SetFilePointer(log_file, 0, NULL, FILE_END);
		}
		WriteFile(log_file, lpAddress, nNumberOfBytesToWrite, &NumberOfBytesWritten, 0);
		nNumberOfBytesToWrite = 0;
	}
	if (force_close && log_file != INVALID_HANDLE_VALUE) {
		CloseHandle(log_file);
		log_file = INVALID_HANDLE_VALUE;
	}
#ifdef __cplusplus
	sgMemCrit.Leave();
#endif
}

HANDLE log_create()
{
	char *v0;                   // eax
	HANDLE v1;                  // ebx
	HANDLE v2;                  // eax
	char *v3;                   // edx
	char Filename[MAX_PATH];         // [esp+Ch] [ebp-15Ch]
	VS_FIXEDFILEINFO file_info; // [esp+110h] [ebp-58h]
	char Buffer[32];            // [esp+144h] [ebp-24h]
	DWORD pcbBuffer;            // [esp+164h] [ebp-4h]

	if (log_not_created) {
		if (GetModuleFileName(0, Filename, sizeof(Filename)) && (v0 = strrchr(Filename, '\\')) != 0)
			v0[1] = 0;
		else
			Filename[0] = 0;
		pcbBuffer = 32;
		if (!GetUserName(Buffer, &pcbBuffer))
			Buffer[0] = 0;
		log_get_version(&file_info);
		_snprintf(
		    FileName,
		    sizeof(Filename),
		    "%s%s%02u%02u%02u.ERR",
		    Filename,
		    Buffer,
		    _LOWORD(file_info.dwProductVersionMS),
		    file_info.dwProductVersionLS >> 16,
		    _LOWORD(file_info.dwProductVersionLS));
	}
	v1 = INVALID_HANDLE_VALUE;
	for (pcbBuffer = log_not_created == 0; (signed int)pcbBuffer < 2; ++pcbBuffer) {
		v2 = CreateFile(FileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		v1 = v2;
		if (v2 != INVALID_HANDLE_VALUE) {
			if (GetFileSize(v2, 0) > 0x10000)
				SetEndOfFile(v1);
			break;
		}
		v3 = strrchr(FileName, '\\');
		if (!v3)
			v3 = FileName;
		strcpy(Filename, "c:\\");
		memset(&Filename[4], 0, 0x100u);
		strcat(Filename, v3);
		strcpy(FileName, Filename);
	}
	log_not_created = 0;
	return v1;
}
// 4947D4: using guessed type int log_not_created;

void log_get_version(VS_FIXEDFILEINFO *file_info)
{
	DWORD size, len, dwHandle;
	unsigned int puLen;
	void *version;
	char Filename[MAX_PATH];
	LPVOID lpBuffer;

	memset(file_info, 0, sizeof(*file_info));
	if (GetModuleFileName(0, Filename, sizeof(Filename))) {
		size = GetFileVersionInfoSize(Filename, &dwHandle);
		if (size) {
			version = VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
			if (GetFileVersionInfo(Filename, 0, size, version) && VerQueryValue(version, "\\", &lpBuffer, &puLen)) {
				len = puLen;
				if (puLen >= 52)
					len = 52;
				memcpy(file_info, lpBuffer, len);
			}
			VirtualFree(version, 0, MEM_RELEASE);
		}
	}
}

void __cdecl log_printf(const char *pszFmt, ...)
{
	size_t size;
	char *pBuffer;
	char msg[512];
	va_list va;

#ifdef __cplusplus
	sgMemCrit.Enter();
#endif
	va_start(va, pszFmt);
	_vsnprintf(msg, 0x200, pszFmt, va);
	va_end(va);
	msg[511] = 0;
	size = strlen(msg);
	if (size + nNumberOfBytesToWrite > 0x1000) {
		log_flush(0);
	}

	if (lpAddress == NULL) {
		lpAddress = (char *)VirtualAlloc((LPVOID)lpAddress, 0x1000, MEM_COMMIT, PAGE_READWRITE);
		pBuffer = (char *)lpAddress;
		nNumberOfBytesToWrite = 0;
	}
	if (lpAddress != NULL) {
		pBuffer = (char *)lpAddress;
		memcpy(&pBuffer[nNumberOfBytesToWrite], msg, size);
		nNumberOfBytesToWrite += size;
	}
#ifdef __cplusplus
	sgMemCrit.Leave();
#endif
}

void log_dump_computer_info()
{
	char Buffer[64];            // [esp+0h] [ebp-88h]
	VS_FIXEDFILEINFO file_info; // [esp+40h] [ebp-48h]
	SYSTEMTIME SystemTime;      // [esp+74h] [ebp-14h]
	DWORD pcbBuffer;            // [esp+84h] [ebp-4h]

	GetLocalTime(&SystemTime);
	pcbBuffer = 64;
	if (!GetUserName(Buffer, &pcbBuffer))
		Buffer[0] = 0;
	log_get_version(&file_info);
	log_printf(
	    "\r\n"
	    "------------------------------------------------------\r\n"
	    "PROGRAM VERSION: %d.%d.%d.%d\r\n"
	    "COMPUTER NAME: %s\r\n"
	    "TIME: %02u/%02u/%02u %02u:%02u:%02u\r\n"
	    "INFO: %s\r\n"
	    "\r\n",
	    file_info.dwProductVersionMS >> 16,
	    file_info.dwProductVersionMS & 0xFFFF,
	    file_info.dwProductVersionLS >> 16,
	    file_info.dwProductVersionLS & 0xFFFF,
	    Buffer,
	    SystemTime.wMonth,
	    SystemTime.wDay,
	    SystemTime.wYear % 100,
	    SystemTime.wHour,
	    SystemTime.wMinute,
	    SystemTime.wSecond,
	    log_buffer);
}
