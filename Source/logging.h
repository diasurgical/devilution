//HEADER_GOES_HERE
#ifndef __LOGGING_H__
#define __LOGGING_H__

extern CHAR FileName[MAX_PATH]; // idb
extern char log_buffer[388];
extern LPCVOID lpAddress;           // idb
extern DWORD nNumberOfBytesToWrite; // idb

void __cdecl log_flush(BOOL force_close);
HANDLE log_create(); // should be HANDLE
void log_get_version(VS_FIXEDFILEINFO *file_info);
void __cdecl log_printf(const char *pszFmt, ...); // LogMessage
void log_dump_computer_info();

/* rdata */

extern const int log_inf; // weak

/* data */

extern int log_not_created; // weak
extern HANDLE log_file;     // idb

#endif /* __LOGGING_H__ */
