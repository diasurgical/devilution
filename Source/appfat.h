//HEADER_GOES_HERE
#ifndef __APPFAT_H__
#define __APPFAT_H__

extern char sz_error_buf[256];
extern int terminating;
extern int cleanup_thread_id;

void TriggerBreak();
#ifdef _DEBUG
LONG __stdcall BreakFilter(PEXCEPTION_POINTERS pExc);
#endif
char *GetErrorStr(DWORD error_code);
void TraceErrorDD(HRESULT hError, char *pszBuffer, DWORD dwMaxChars);
void TraceErrorDS(HRESULT hError, char *pszBuffer, DWORD dwMaxChars);
char *TraceLastError();
void __cdecl app_fatal(const char *pszFmt, ...);
void MsgBox(const char *pszFmt, va_list va);
void FreeDlg();
void __cdecl DrawDlg(const char *pszFmt, ...);
#ifdef _DEBUG
void assert_fail(int nLineNo, const char *pszFile, const char *pszFail);
#endif
void DDErrMsg(DWORD error_code, int log_line_nr, const char *log_file_path);
void DSErrMsg(DWORD error_code, int log_line_nr, const char *log_file_path);
void center_window(HWND hDlg);
void ErrDlg(int template_id, DWORD error_code, const char *log_file_path, int log_line_nr);
BOOL __stdcall FuncDlg(HWND hDlg, UINT uMsg, WPARAM wParam, const char *text);
void TextDlg(HWND hDlg, const char *text);
void ErrOkDlg(int template_id, DWORD error_code, const char *log_file_path, int log_line_nr);
void FileErrDlg(const char *error);
void DiskFreeDlg(const char *error);
BOOL InsertCDDlg();
void DirErrorDlg(const char *error);

#endif /* __APPFAT_H__ */
