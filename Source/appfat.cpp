/**
 * @file appfat.cpp
 *
 * Implementation of error dialogs.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

/** Buffer used by GetErrorStr for its return value */
char sz_error_buf[256];
/** Set to true when a fatal error is encountered and the application should shut down. */
BOOL terminating;
/** Thread id of the last callee to FreeDlg(). */
int cleanup_thread_id;

// delete overloads the delete operator.
void __cdecl operator delete(void *ptr)
{
	if (ptr != NULL) {
		SMemFree(ptr, "delete", -1, 0);
	}
}

#ifdef _DEBUG
static LONG __stdcall BreakFilter(PEXCEPTION_POINTERS pExc)
{
	if (pExc->ExceptionRecord == NULL) {
		return EXCEPTION_CONTINUE_SEARCH;
	}
	if (pExc->ExceptionRecord->ExceptionCode != EXCEPTION_BREAKPOINT) {
		return EXCEPTION_CONTINUE_SEARCH;
	}

	if (((BYTE *)pExc->ContextRecord->Eip)[0] == 0xCC) { // int 3
		pExc->ContextRecord->Eip++;
	}

	return EXCEPTION_CONTINUE_EXECUTION;
}
#endif

void TriggerBreak()
{
#ifdef _DEBUG
	LPTOP_LEVEL_EXCEPTION_FILTER pFilter;

	pFilter = SetUnhandledExceptionFilter(BreakFilter);
#ifdef USE_ASM
	__asm {
		int		3
	}
#else
	__debugbreak();
#endif
	SetUnhandledExceptionFilter(pFilter);
#endif
}

/**
 * @brief Generate a textual message for DirectDraw error codes
 * @param hError DirectDraw error code
 * @param pszBuffer Buffer for the error message
 * @param dwMaxChars Length of pszBuffer
 */
static void TraceErrorDD(HRESULT hError, char *pszBuffer, DWORD dwMaxChars)
{
	const char *szError;

	switch (hError) {
	case DD_OK:
		szError = "DD_OK";
		break;
	case DDERR_ALREADYINITIALIZED:
		szError = "DDERR_ALREADYINITIALIZED";
		break;
	case DDERR_BLTFASTCANTCLIP:
		szError = "DDERR_BLTFASTCANTCLIP";
		break;
	case DDERR_CANNOTATTACHSURFACE:
		szError = "DDERR_CANNOTATTACHSURFACE";
		break;
	case DDERR_CANNOTDETACHSURFACE:
		szError = "DDERR_CANNOTDETACHSURFACE";
		break;
	case DDERR_CANTCREATEDC:
		szError = "DDERR_CANTCREATEDC";
		break;
	case DDERR_CANTDUPLICATE:
		szError = "DDERR_CANTDUPLICATE";
		break;
	case DDERR_CLIPPERISUSINGHWND:
		szError = "DDERR_CLIPPERISUSINGHWND";
		break;
	case DDERR_COLORKEYNOTSET:
		szError = "DDERR_COLORKEYNOTSET";
		break;
	case DDERR_CURRENTLYNOTAVAIL:
		szError = "DDERR_CURRENTLYNOTAVAIL";
		break;
	case DDERR_DIRECTDRAWALREADYCREATED:
		szError = "DDERR_DIRECTDRAWALREADYCREATED";
		break;
	case DDERR_EXCEPTION:
		szError = "DDERR_EXCEPTION";
		break;
	case DDERR_EXCLUSIVEMODEALREADYSET:
		szError = "DDERR_EXCLUSIVEMODEALREADYSET";
		break;
	case DDERR_GENERIC:
		szError = "DDERR_GENERIC";
		break;
	case DDERR_HEIGHTALIGN:
		szError = "DDERR_HEIGHTALIGN";
		break;
	case DDERR_HWNDALREADYSET:
		szError = "DDERR_HWNDALREADYSET";
		break;
	case DDERR_HWNDSUBCLASSED:
		szError = "DDERR_HWNDSUBCLASSED";
		break;
	case DDERR_IMPLICITLYCREATED:
		szError = "DDERR_IMPLICITLYCREATED";
		break;
	case DDERR_INCOMPATIBLEPRIMARY:
		szError = "DDERR_INCOMPATIBLEPRIMARY";
		break;
	case DDERR_INVALIDCAPS:
		szError = "DDERR_INVALIDCAPS";
		break;
	case DDERR_INVALIDCLIPLIST:
		szError = "DDERR_INVALIDCLIPLIST";
		break;
	case DDERR_INVALIDDIRECTDRAWGUID:
		szError = "DDERR_INVALIDDIRECTDRAWGUID";
		break;
	case DDERR_INVALIDMODE:
		szError = "DDERR_INVALIDMODE";
		break;
	case DDERR_INVALIDOBJECT:
		szError = "DDERR_INVALIDOBJECT";
		break;
	case DDERR_INVALIDPARAMS:
		szError = "DDERR_INVALIDPARAMS";
		break;
	case DDERR_INVALIDPIXELFORMAT:
		szError = "DDERR_INVALIDPIXELFORMAT";
		break;
	case DDERR_INVALIDPOSITION:
		szError = "DDERR_INVALIDPOSITION";
		break;
	case DDERR_INVALIDRECT:
		szError = "DDERR_INVALIDRECT";
		break;
	case DDERR_LOCKEDSURFACES:
		szError = "DDERR_LOCKEDSURFACES";
		break;
	case DDERR_NO3D:
		szError = "DDERR_NO3D";
		break;
	case DDERR_NOALPHAHW:
		szError = "DDERR_NOALPHAHW";
		break;
	case DDERR_NOBLTHW:
		szError = "DDERR_NOBLTHW";
		break;
	case DDERR_NOCLIPLIST:
		szError = "DDERR_NOCLIPLIST";
		break;
	case DDERR_NOCLIPPERATTACHED:
		szError = "DDERR_NOCLIPPERATTACHED";
		break;
	case DDERR_NOCOLORCONVHW:
		szError = "DDERR_NOCOLORCONVHW";
		break;
	case DDERR_NOCOLORKEY:
		szError = "DDERR_NOCOLORKEY";
		break;
	case DDERR_NOCOLORKEYHW:
		szError = "DDERR_NOCOLORKEYHW";
		break;
	case DDERR_NOCOOPERATIVELEVELSET:
		szError = "DDERR_NOCOOPERATIVELEVELSET";
		break;
	case DDERR_NODC:
		szError = "DDERR_NODC";
		break;
	case DDERR_NODDROPSHW:
		szError = "DDERR_NODDROPSHW";
		break;
	case DDERR_NODIRECTDRAWHW:
		szError = "DDERR_NODIRECTDRAWHW";
		break;
	case DDERR_NOEMULATION:
		szError = "DDERR_NOEMULATION";
		break;
	case DDERR_NOEXCLUSIVEMODE:
		szError = "DDERR_NOEXCLUSIVEMODE";
		break;
	case DDERR_NOFLIPHW:
		szError = "DDERR_NOFLIPHW";
		break;
	case DDERR_NOGDI:
		szError = "DDERR_NOGDI";
		break;
	case DDERR_NOHWND:
		szError = "DDERR_NOHWND";
		break;
	case DDERR_NOMIRRORHW:
		szError = "DDERR_NOMIRRORHW";
		break;
	case DDERR_NOOVERLAYDEST:
		szError = "DDERR_NOOVERLAYDEST";
		break;
	case DDERR_NOOVERLAYHW:
		szError = "DDERR_NOOVERLAYHW";
		break;
	case DDERR_NOPALETTEATTACHED:
		szError = "DDERR_NOPALETTEATTACHED";
		break;
	case DDERR_NOPALETTEHW:
		szError = "DDERR_NOPALETTEHW";
		break;
	case DDERR_NORASTEROPHW:
		szError = "DDERR_NORASTEROPHW";
		break;
	case DDERR_NOROTATIONHW:
		szError = "DDERR_NOROTATIONHW";
		break;
	case DDERR_NOSTRETCHHW:
		szError = "DDERR_NOSTRETCHHW";
		break;
	case DDERR_NOT4BITCOLOR:
		szError = "DDERR_NOT4BITCOLOR";
		break;
	case DDERR_NOT4BITCOLORINDEX:
		szError = "DDERR_NOT4BITCOLORINDEX";
		break;
	case DDERR_NOT8BITCOLOR:
		szError = "DDERR_NOT8BITCOLOR";
		break;
	case DDERR_NOTAOVERLAYSURFACE:
		szError = "DDERR_NOTAOVERLAYSURFACE";
		break;
	case DDERR_NOTEXTUREHW:
		szError = "DDERR_NOTEXTUREHW";
		break;
	case DDERR_NOTFLIPPABLE:
		szError = "DDERR_NOTFLIPPABLE";
		break;
	case DDERR_NOTFOUND:
		szError = "DDERR_NOTFOUND";
		break;
	case DDERR_NOTLOCKED:
		szError = "DDERR_NOTLOCKED";
		break;
	case DDERR_NOTPALETTIZED:
		szError = "DDERR_NOTPALETTIZED";
		break;
	case DDERR_NOVSYNCHW:
		szError = "DDERR_NOVSYNCHW";
		break;
	case DDERR_NOZBUFFERHW:
		szError = "DDERR_NOZBUFFERHW";
		break;
	case DDERR_NOZOVERLAYHW:
		szError = "DDERR_NOZOVERLAYHW";
		break;
	case DDERR_OUTOFCAPS:
		szError = "DDERR_OUTOFCAPS";
		break;
	case DDERR_OUTOFMEMORY:
		szError = "DDERR_OUTOFMEMORY";
		break;
	case DDERR_OUTOFVIDEOMEMORY:
		szError = "DDERR_OUTOFVIDEOMEMORY";
		break;
	case DDERR_OVERLAYCANTCLIP:
		szError = "DDERR_OVERLAYCANTCLIP";
		break;
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		szError = "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
		break;
	case DDERR_OVERLAYNOTVISIBLE:
		szError = "DDERR_OVERLAYNOTVISIBLE";
		break;
	case DDERR_PALETTEBUSY:
		szError = "DDERR_PALETTEBUSY";
		break;
	case DDERR_PRIMARYSURFACEALREADYEXISTS:
		szError = "DDERR_PRIMARYSURFACEALREADYEXISTS";
		break;
	case DDERR_REGIONTOOSMALL:
		szError = "DDERR_REGIONTOOSMALL";
		break;
	case DDERR_SURFACEALREADYATTACHED:
		szError = "DDERR_SURFACEALREADYATTACHED";
		break;
	case DDERR_SURFACEALREADYDEPENDENT:
		szError = "DDERR_SURFACEALREADYDEPENDENT";
		break;
	case DDERR_SURFACEBUSY:
		szError = "DDERR_SURFACEBUSY";
		break;
	case DDERR_SURFACEISOBSCURED:
		szError = "DDERR_SURFACEISOBSCURED";
		break;
	case DDERR_SURFACELOST:
		szError = "DDERR_SURFACELOST";
		break;
	case DDERR_SURFACENOTATTACHED:
		szError = "DDERR_SURFACENOTATTACHED";
		break;
	case DDERR_TOOBIGHEIGHT:
		szError = "DDERR_TOOBIGHEIGHT";
		break;
	case DDERR_TOOBIGSIZE:
		szError = "DDERR_TOOBIGSIZE";
		break;
	case DDERR_TOOBIGWIDTH:
		szError = "DDERR_TOOBIGWIDTH";
		break;
	case DDERR_UNSUPPORTED:
		szError = "DDERR_UNSUPPORTED";
		break;
	case DDERR_UNSUPPORTEDFORMAT:
		szError = "DDERR_UNSUPPORTEDFORMAT";
		break;
	case DDERR_UNSUPPORTEDMASK:
		szError = "DDERR_UNSUPPORTEDMASK";
		break;
	case DDERR_VERTICALBLANKINPROGRESS:
		szError = "DDERR_VERTICALBLANKINPROGRESS";
		break;
	case DDERR_WASSTILLDRAWING:
		szError = "DDERR_WASSTILLDRAWING";
		break;
	case DDERR_WRONGMODE:
		szError = "DDERR_WRONGMODE";
		break;
	case DDERR_XALIGN:
		szError = "DDERR_XALIGN";
		break;
	case DDERR_CANTLOCKSURFACE:
		szError = "DDERR_CANTLOCKSURFACE";
		break;
	case DDERR_CANTPAGELOCK:
		szError = "DDERR_CANTPAGELOCK";
		break;
	case DDERR_CANTPAGEUNLOCK:
		szError = "DDERR_CANTPAGEUNLOCK";
		break;
	case DDERR_DCALREADYCREATED:
		szError = "DDERR_DCALREADYCREATED";
		break;
	case DDERR_INVALIDSURFACETYPE:
		szError = "DDERR_INVALIDSURFACETYPE";
		break;
	case DDERR_NOMIPMAPHW:
		szError = "DDERR_NOMIPMAPHW";
		break;
	case DDERR_NOTPAGELOCKED:
		szError = "DDERR_NOTPAGELOCKED";
		break;
	default: {
		const char szUnknown[] = "DDERR unknown 0x%x";
		assert(dwMaxChars >= sizeof(szUnknown) + 10);
		sprintf(pszBuffer, szUnknown, hError);
		return;
	}
	}

	strncpy(pszBuffer, szError, dwMaxChars);
}

/**
 * @brief Generate a textual message for DirectSound error codes
 * @param hError DirectSound error code
 * @param pszBuffer Buffer for the error message
 * @param dwMaxChars Length of pszBuffer
 */
static void TraceErrorDS(HRESULT hError, char *pszBuffer, DWORD dwMaxChars)
{
	const char *szError;

	switch (hError) {
	case DSERR_PRIOLEVELNEEDED:
		szError = "DSERR_PRIOLEVELNEEDED";
		break;
	case DSERR_BADFORMAT:
		szError = "DSERR_BADFORMAT";
		break;
	case DSERR_NODRIVER:
		szError = "DSERR_NODRIVER";
		break;
	case DSERR_ALREADYINITIALIZED:
		szError = "DSERR_ALREADYINITIALIZED";
		break;
	case DSERR_BUFFERLOST:
		szError = "DSERR_BUFFERLOST";
		break;
	case DS_OK:
		szError = "DS_OK";
		break;
	case DSERR_INVALIDCALL:
		szError = "DSERR_INVALIDCALL";
		break;
	case E_NOINTERFACE:
		szError = "E_NOINTERFACE";
		break;
	case DSERR_NOAGGREGATION:
		szError = "DSERR_NOAGGREGATION";
		break;
	case DSERR_OUTOFMEMORY:
		szError = "DSERR_OUTOFMEMORY";
		break;
	case DSERR_INVALIDPARAM:
		szError = "DSERR_INVALIDPARAM";
		break;
	case DSERR_ALLOCATED:
		szError = "DSERR_ALLOCATED";
		break;
	case DSERR_CONTROLUNAVAIL:
		szError = "DSERR_CONTROLUNAVAIL";
		break;
	default: {
		const char szUnknown[] = "DSERR unknown 0x%x";
		assert(dwMaxChars >= sizeof(szUnknown) + 10);
		sprintf(pszBuffer, szUnknown, hError);
		return;
	}
	}

	strncpy(pszBuffer, szError, dwMaxChars);
}

/**
 * @brief Returns a formatted error message based on the given error code.
 * @param error_code DirectX error code
 */
const char *GetErrorStr(DWORD error_code)
{
	int size;
	char *chr;

	if (HRESULT_FACILITY(error_code) == _FACDS) {
		TraceErrorDS(error_code, sz_error_buf, sizeof(sz_error_buf) / sizeof(sz_error_buf[0]));
	} else if (HRESULT_FACILITY(error_code) == _FACDD) {
		TraceErrorDD(error_code, sz_error_buf, sizeof(sz_error_buf) / sizeof(sz_error_buf[0]));
	} else if (!SErrGetErrorStr(error_code, sz_error_buf, sizeof(sz_error_buf) / sizeof(sz_error_buf[0]))
	    && !FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sz_error_buf, sizeof(sz_error_buf) / sizeof(sz_error_buf[0]), NULL)) {
		wsprintf(sz_error_buf, "unknown error 0x%08x", error_code);
	}

	size = strlen(sz_error_buf);

	chr = &sz_error_buf[size - 1];
	while (size-- > 0) {
		chr--;

		if (*chr != '\r' && *chr != '\n')
			break;

		*chr = 0x00;
	}

	return sz_error_buf;
}

/**
 * @brief Returns a formatted error message of the last error.
 */
const char *TraceLastError()
{
	return GetErrorStr(GetLastError());
}

/**
 * @brief Displays an error message box based on the given format string and variable argument list.
 * @param pszFmt Error message format
 * @param va Additional parameters for message format
 */
static void MsgBox(const char *pszFmt, va_list va)
{
	char Text[256];

	wvsprintf(Text, pszFmt, va);
	if (ghMainWnd)
		SetWindowPos(ghMainWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
	MessageBox(ghMainWnd, Text, "ERROR", MB_TASKMODAL | MB_ICONHAND);
}

/**
 * @brief Cleans up after a fatal application error.
 */
static void FreeDlg()
{
	if (terminating && cleanup_thread_id != GetCurrentThreadId())
		Sleep(20000);

	terminating = TRUE;
	cleanup_thread_id = GetCurrentThreadId();

	dx_cleanup();

	if (gbMaxPlayers > 1) {
		if (SNetLeaveGame(3))
			Sleep(2000);
	}

	SNetDestroy();
	ShowCursor(TRUE);
}

/**
 * @brief Terminates the game and displays an error message box.
 * @param pszFmt Optional error message.
 * @param ... (see printf)
 */
#ifdef HELLFIRE
__declspec(naked)
#endif
    void __cdecl app_fatal(const char *pszFmt, ...)
{
	va_list va;

	va_start(va, pszFmt);
	FreeDlg();
#if defined(_DEBUG) || defined(HELLFIRE)
	TriggerBreak();
#endif

	if (pszFmt)
		MsgBox(pszFmt, va);

	va_end(va);

	init_cleanup(FALSE);
	exit(1);
	ExitProcess(1);
}

/**
 * @brief Displays a warning message box based on the given formatted error message.
 * @param pszFmt Error message format
 * @param ... Additional parameters for message format
 */
void __cdecl DrawDlg(const char *pszFmt, ...)
{
	char text[256];
	va_list arglist;

	va_start(arglist, pszFmt);
	wvsprintf(text, pszFmt, arglist);
	va_end(arglist);
	SDrawMessageBox(text, APP_NAME, MB_TASKMODAL | MB_ICONEXCLAMATION);
}

#ifdef _DEBUG
/**
 * @brief Show an error and exit the application.
 * @param nLineNo The line number of the assertion
 * @param pszFile File name where the assertion is located
 * @param pszFail Fail message
 */
void assert_fail(int nLineNo, const char *pszFile, const char *pszFail)
{
	app_fatal("assertion failed (%d:%s)\n%s", nLineNo, pszFile, pszFail);
}
#endif

/**
 * @brief Terminates the game with a DirectDraw assertion message box.
 */
void DDErrMsg(DWORD error_code, int log_line_nr, const char *log_file_path)
{
	const char *msg;

	if (error_code) {
		msg = GetErrorStr(error_code);
		app_fatal("Direct draw error (%s:%d)\n%s", log_file_path, log_line_nr, msg);
	}
}

/**
 * @brief Terminates the game with a DirectSound assertion message box.
 */
void DSErrMsg(DWORD error_code, int log_line_nr, const char *log_file_path)
{
	const char *msg;

	if (error_code) {
		msg = GetErrorStr(error_code);
		app_fatal("Direct sound error (%s:%d)\n%s", log_file_path, log_line_nr, msg);
	}
}

/**
 * @brief Centres the given dialog box.
 */
void center_window(HWND hDlg)
{
	LONG w, h;
	int screenW, screenH;
	tagRECT Rect;
	HDC hdc;

	GetWindowRect(hDlg, &Rect);
	w = Rect.right - Rect.left;
	h = Rect.bottom - Rect.top;
	hdc = GetDC(hDlg);
	screenW = GetDeviceCaps(hdc, HORZRES);
	screenH = GetDeviceCaps(hdc, VERTRES);
	ReleaseDC(hDlg, hdc);

	if (!SetWindowPos(hDlg, HWND_TOP, (screenW - w) / 2, (screenH - h) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE)) {
		app_fatal("center_window: %s", TraceLastError());
	}
}

/**
 * @brief Sets the text of the given dialog.
 */
static void TextDlg(HWND hDlg, const char *text)
{
	center_window(hDlg);

	if (text)
		SetDlgItemText(hDlg, 1000, text);
}

/**
 * @brief Callback function which processes messages sent to the given dialog box.
 */
static BOOL CALLBACK FuncDlg(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		TextDlg(hDlg, (char *)lParam);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			EndDialog(hDlg, TRUE);
		} else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, FALSE);
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

/**
 * @brief Terminates the game and displays an error dialog box based on the given dialog_id.
 */
void ErrDlg(int dialog_id, DWORD error_code, const char *log_file_path, int log_line_nr)
{
	const char *size;
	LPARAM dwInitParam[128];

	FreeDlg();

	size = strrchr(log_file_path, '\\');
	if (size)
		log_file_path = size + 1;

	wsprintf((LPSTR)dwInitParam, "%s\nat: %s line %d", GetErrorStr(error_code), log_file_path, log_line_nr);
	if (DialogBoxParam(ghInst, MAKEINTRESOURCE(dialog_id), ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)dwInitParam) == -1)
		app_fatal("ErrDlg: %d", dialog_id);

	app_fatal(NULL);
}

#ifndef HELLFIRE
/**
 * @brief Displays a warning dialog box based on the given dialog_id and error code.
 */
void ErrOkDlg(int dialog_id, DWORD error_code, const char *log_file_path, int log_line_nr)
{
	const char *size;
	LPARAM dwInitParam[128];

	size = strrchr(log_file_path, '\\');
	if (size)
		log_file_path = size + 1;

	wsprintf((LPSTR)dwInitParam, "%s\nat: %s line %d", GetErrorStr(error_code), log_file_path, log_line_nr);
	DialogBoxParam(ghInst, MAKEINTRESOURCE(dialog_id), ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)dwInitParam);
}
#endif

/**
 * @brief Terminates the game with a file not found error dialog.
 */
void FileErrDlg(const char *error)
{
	FreeDlg();

	if (!error)
		error = "";

	if (DialogBoxParam(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)error) == -1)
		app_fatal("FileErrDlg");

	app_fatal(NULL);
}

/**
 * @brief Terminates the game with an out of disk space error dialog.
 */
void DiskFreeDlg(const char *error)
{
	FreeDlg();

	if (DialogBoxParam(ghInst, MAKEINTRESOURCE(IDD_DIALOG7), ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)error) == -1)
		app_fatal("DiskFreeDlg");

	app_fatal(NULL);
}

/**
 * @brief Terminates the game with an insert CD error dialog.
 */
BOOL InsertCDDlg()
{
	int nResult;

	ShowCursor(TRUE);

	nResult = DialogBoxParam(ghInst, MAKEINTRESOURCE(IDD_DIALOG9), ghMainWnd, (DLGPROC)FuncDlg, (LPARAM) "");
	if (nResult == -1)
		app_fatal("InsertCDDlg");

	ShowCursor(FALSE);

	return nResult == IDOK;
}

#ifndef HELLFIRE
/**
 * @brief Terminates the game with a read-only directory error dialog.
 */
void DirErrorDlg(const char *error)
{
	FreeDlg();

	if (DialogBoxParam(ghInst, MAKEINTRESOURCE(IDD_DIALOG11), ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)error) == -1)
		app_fatal("DirErrorDlg");

	app_fatal(NULL);
}
#endif
