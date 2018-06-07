/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

//logging
extern int log_cpp_init_value; // weak
extern CHAR FileName[260]; // idb
extern char log_buffer[388];
extern LPCVOID lpAddress; // idb
extern DWORD nNumberOfBytesToWrite; // idb

void __cdecl log_cpp_init_1();
void __cdecl log_cpp_init_2();
void __cdecl log_init_mutex();
void __cdecl j_log_cleanup_mutex();
void __cdecl log_cleanup_mutex();
void __cdecl log_flush(bool force_close);
void *__cdecl log_create(); // should be HANDLE
void __fastcall log_get_version(VS_FIXEDFILEINFO *file_info);
void log_printf(char *pszFmt, ...); // LogMessage
void __cdecl log_dump_computer_info();

/* data */

extern int log_inf; // weak

/* rdata */

extern int log_not_created; // weak
extern HANDLE log_file; // idb
