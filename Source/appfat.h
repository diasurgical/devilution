/**
 * @file appfat.h
 *
 * Interface of error dialogs.
 */
#ifndef __APPFAT_H__
#define __APPFAT_H__

void TriggerBreak();
const char *TraceLastError();
void __cdecl app_fatal(const char *pszFmt, ...);
void __cdecl DrawDlg(const char *pszFmt, ...);
#ifdef _DEBUG
void assert_fail(int nLineNo, const char *pszFile, const char *pszFail);
#endif
void DDErrMsg(DWORD error_code, int log_line_nr, const char *log_file_path);
void DSErrMsg(DWORD error_code, int log_line_nr, const char *log_file_path);
void ErrDlg(int template_id, DWORD error_code, const char *log_file_path, int log_line_nr);
void ErrOkDlg(int template_id, DWORD error_code, const char *log_file_path, int log_line_nr);
void FileErrDlg(const char *error);
void DiskFreeDlg(const char *error);
BOOL InsertCDDlg();
void DirErrorDlg(const char *error);

#endif /* __APPFAT_H__ */
