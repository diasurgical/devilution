/**
 * @file logging.h
 *
 * Interface of logging functionality.
 */
#ifndef __LOGGING_H__
#define __LOGGING_H__

extern CHAR FileName[MAX_PATH];
extern LPCVOID lpAddress;
extern DWORD nNumberOfBytesToWrite;

void __cdecl log_flush(BOOL force_close);
void __cdecl log_printf(const char *pszFmt, ...); // LogMessage
void log_dump_computer_info();

/* data */

extern HANDLE log_file;

#endif /* __LOGGING_H__ */
