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

#include "../types.h"

int appfat_terminated = 0; // weak
char sz_error_buf[256];
int terminating; // weak
int cleanup_thread_id; // weak
char empty_string;

void __cdecl appfat_cpp_init()
{
	appfat_terminated = 0x7F800000;
}

struct j_appfat_cpp_init
{
	j_appfat_cpp_init()
	{
		appfat_cpp_init();
	}
} _j_appfat_cpp_init;
/*
bool __cdecl appfat_cpp_free(void *a1)
{
	bool result; // al

	if ( a1 )
		result = SMemFree(a1, "delete", -1, 0);
	return result;
}
*/

//----- (0040102A) --------------------------------------------------------
char *__fastcall GetErr(int error_code)
{
	int v1; // edi
	unsigned int v2; // eax
	signed int v4; // eax
	char *i; // ecx

	v1 = error_code;
	v2 = ((unsigned int)error_code >> 16) & 0x1FFF;
	if ( v2 == 0x0878 )
	{
		GetDSErr(error_code, sz_error_buf, 256);
	}
	else if ( v2 == 0x0876 )
	{
		GetDDErr(error_code, sz_error_buf, 256);
	}
	else
	{
		if ( !SErrGetErrorStr(error_code, sz_error_buf, 256) && !FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, v1, 0x400u, sz_error_buf, 0x100u, NULL) )
			wsprintfA(sz_error_buf, "unknown error 0x%08x", v1);
	}
	v4 = strlen(sz_error_buf);
	for ( i = &sz_error_buf[v4-1]; v4 > 0; *i = 0 )
	{
		--v4;
		if ( *--i != '\r' && *i != '\n' )
			break;
	}
	return sz_error_buf;
}

//----- (004010CE) --------------------------------------------------------
void __fastcall GetDDErr(int error_code, char *error_buf, int error_buf_len)
{
	const char *v3; // eax
	char v4[4]; // [esp+0h] [ebp-14h]

	if ( error_code > DDERR_SURFACEBUSY )
	{
		if ( error_code > DDERR_NOPALETTEHW )
		{
			if ( error_code > DDERR_CANTPAGELOCK )
			{
				switch ( error_code )
				{
					case DDERR_CANTPAGEUNLOCK:
						v3 = "DDERR_CANTPAGEUNLOCK";
						goto LABEL_182;
					case DDERR_NOTPAGELOCKED:
						v3 = "DDERR_NOTPAGELOCKED";
						goto LABEL_182;
					case DD_OK:
						v3 = "DD_OK";
						goto LABEL_182;
				}
			}
			else
			{
				if ( error_code == DDERR_CANTPAGELOCK )
				{
					v3 = "DDERR_CANTPAGELOCK";
					goto LABEL_182;
				}
				switch ( error_code )
				{
					case DDERR_BLTFASTCANTCLIP:
						v3 = "DDERR_BLTFASTCANTCLIP";
						goto LABEL_182;
					case DDERR_NOBLTHW:
						v3 = "DDERR_NOBLTHW";
						goto LABEL_182;
					case DDERR_NODDROPSHW:
						v3 = "DDERR_NODDROPSHW";
						goto LABEL_182;
					case DDERR_OVERLAYNOTVISIBLE:
						v3 = "DDERR_OVERLAYNOTVISIBLE";
						goto LABEL_182;
					case DDERR_NOOVERLAYDEST:
						v3 = "DDERR_NOOVERLAYDEST";
						goto LABEL_182;
					case DDERR_INVALIDPOSITION:
						v3 = "DDERR_INVALIDPOSITION";
						goto LABEL_182;
					case DDERR_NOTAOVERLAYSURFACE:
						v3 = "DDERR_NOTAOVERLAYSURFACE";
						goto LABEL_182;
					case DDERR_EXCLUSIVEMODEALREADYSET:
						v3 = "DDERR_EXCLUSIVEMODEALREADYSET";
						goto LABEL_182;
					case DDERR_NOTFLIPPABLE:
						v3 = "DDERR_NOTFLIPPABLE";
						goto LABEL_182;
					case DDERR_CANTDUPLICATE:
						v3 = "DDERR_CANTDUPLICATE";
						goto LABEL_182;
					case DDERR_NOTLOCKED:
						v3 = "DDERR_NOTLOCKED";
						goto LABEL_182;
					case DDERR_CANTCREATEDC:
						v3 = "DDERR_CANTCREATEDC";
						goto LABEL_182;
					case DDERR_NODC:
						v3 = "DDERR_NODC";
						goto LABEL_182;
					case DDERR_WRONGMODE:
						v3 = "DDERR_WRONGMODE";
						goto LABEL_182;
					case DDERR_IMPLICITLYCREATED:
						v3 = "DDERR_IMPLICITLYCREATED";
						goto LABEL_182;
					case DDERR_NOTPALETTIZED:
						v3 = "DDERR_NOTPALETTIZED";
						goto LABEL_182;
					case DDERR_NOMIPMAPHW:
						v3 = "DDERR_NOMIPMAPHW";
						goto LABEL_182;
					case DDERR_INVALIDSURFACETYPE:
						v3 = "DDERR_INVALIDSURFACETYPE";
						goto LABEL_182;
					case DDERR_DCALREADYCREATED:
						v3 = "DDERR_DCALREADYCREATED";
						goto LABEL_182;
					default:
						goto LABEL_178;
				}
			}
		}
		else
		{
			if ( error_code == DDERR_NOPALETTEHW )
			{
				v3 = "DDERR_NOPALETTEHW";
				goto LABEL_182;
			}
			if ( error_code > DDERR_INVALIDDIRECTDRAWGUID )
			{
				switch ( error_code )
				{
					case DDERR_DIRECTDRAWALREADYCREATED:
						v3 = "DDERR_DIRECTDRAWALREADYCREATED";
						goto LABEL_182;
					case DDERR_NODIRECTDRAWHW:
						v3 = "DDERR_NODIRECTDRAWHW";
						goto LABEL_182;
					case DDERR_PRIMARYSURFACEALREADYEXISTS:
						v3 = "DDERR_PRIMARYSURFACEALREADYEXISTS";
						goto LABEL_182;
					case DDERR_NOEMULATION:
						v3 = "DDERR_NOEMULATION";
						goto LABEL_182;
					case DDERR_REGIONTOOSMALL:
						v3 = "DDERR_REGIONTOOSMALL";
						goto LABEL_182;
					case DDERR_CLIPPERISUSINGHWND:
						v3 = "DDERR_CLIPPERISUSINGHWND";
						goto LABEL_182;
					case DDERR_NOCLIPPERATTACHED:
						v3 = "DDERR_NOCLIPPERATTACHED";
						goto LABEL_182;
					case DDERR_NOHWND:
						v3 = "DDERR_NOHWND";
						goto LABEL_182;
					case DDERR_HWNDSUBCLASSED:
						v3 = "DDERR_HWNDSUBCLASSED";
						goto LABEL_182;
					case DDERR_HWNDALREADYSET:
						v3 = "DDERR_HWNDALREADYSET";
						goto LABEL_182;
					case DDERR_NOPALETTEATTACHED:
						v3 = "DDERR_NOPALETTEATTACHED";
						goto LABEL_182;
					default:
						goto LABEL_178;
				}
			}
			else
			{
				if ( error_code == DDERR_INVALIDDIRECTDRAWGUID )
				{
					v3 = "DDERR_INVALIDDIRECTDRAWGUID";
					goto LABEL_182;
				}
				if ( error_code > DDERR_TOOBIGWIDTH )
				{
					switch ( error_code )
					{
						case DDERR_UNSUPPORTEDFORMAT:
							v3 = "DDERR_UNSUPPORTEDFORMAT";
							goto LABEL_182;
						case DDERR_UNSUPPORTEDMASK:
							v3 = "DDERR_UNSUPPORTEDMASK";
							goto LABEL_182;
						case DDERR_VERTICALBLANKINPROGRESS:
							v3 = "DDERR_VERTICALBLANKINPROGRESS";
							goto LABEL_182;
						case DDERR_WASSTILLDRAWING:
							v3 = "DDERR_WASSTILLDRAWING";
							goto LABEL_182;
						case DDERR_XALIGN:
							v3 = "DDERR_XALIGN";
							goto LABEL_182;
					}
				}
				else
				{
					switch ( error_code )
					{
						case DDERR_TOOBIGWIDTH:
							v3 = "DDERR_TOOBIGWIDTH";
							goto LABEL_182;
						case DDERR_CANTLOCKSURFACE:
							v3 = "DDERR_CANTLOCKSURFACE";
							goto LABEL_182;
						case DDERR_SURFACEISOBSCURED:
							v3 = "DDERR_SURFACEISOBSCURED";
							goto LABEL_182;
						case DDERR_SURFACELOST:
							v3 = "DDERR_SURFACELOST";
							goto LABEL_182;
						case DDERR_SURFACENOTATTACHED:
							v3 = "DDERR_SURFACENOTATTACHED";
							goto LABEL_182;
						case DDERR_TOOBIGHEIGHT:
							v3 = "DDERR_TOOBIGHEIGHT";
							goto LABEL_182;
						case DDERR_TOOBIGSIZE:
							v3 = "DDERR_TOOBIGSIZE";
							goto LABEL_182;
					}
				}
			}
		}
		goto LABEL_178;
	}
	if ( error_code == DDERR_SURFACEBUSY )
	{
		v3 = "DDERR_SURFACEBUSY";
		goto LABEL_182;
	}
	if ( error_code > DDERR_NOCOLORKEYHW )
	{
		if ( error_code > DDERR_NOTEXTUREHW )
		{
			if ( error_code > DDERR_OVERLAYCANTCLIP )
			{
				switch ( error_code )
				{
					case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
						v3 = "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
						goto LABEL_182;
					case DDERR_PALETTEBUSY:
						v3 = "DDERR_PALETTEBUSY";
						goto LABEL_182;
					case DDERR_COLORKEYNOTSET:
						v3 = "DDERR_COLORKEYNOTSET";
						goto LABEL_182;
					case DDERR_SURFACEALREADYATTACHED:
						v3 = "DDERR_SURFACEALREADYATTACHED";
						goto LABEL_182;
					case DDERR_SURFACEALREADYDEPENDENT:
						v3 = "DDERR_SURFACEALREADYDEPENDENT";
						goto LABEL_182;
				}
			}
			else
			{
				switch ( error_code )
				{
					case DDERR_OVERLAYCANTCLIP:
						v3 = "DDERR_OVERLAYCANTCLIP";
						goto LABEL_182;
					case DDERR_NOVSYNCHW:
						v3 = "DDERR_NOVSYNCHW";
						goto LABEL_182;
					case DDERR_NOZBUFFERHW:
						v3 = "DDERR_NOZBUFFERHW";
						goto LABEL_182;
					case DDERR_NOZOVERLAYHW:
						v3 = "DDERR_NOZOVERLAYHW";
						goto LABEL_182;
					case DDERR_OUTOFCAPS:
						v3 = "DDERR_OUTOFCAPS";
						goto LABEL_182;
					case DDERR_OUTOFVIDEOMEMORY:
						v3 = "DDERR_OUTOFVIDEOMEMORY";
						goto LABEL_182;
				}
			}
		}
		else
		{
			if ( error_code == DDERR_NOTEXTUREHW )
			{
				v3 = "DDERR_NOTEXTUREHW";
				goto LABEL_182;
			}
			if ( error_code > DDERR_NORASTEROPHW )
			{
				switch ( error_code )
				{
					case DDERR_NOROTATIONHW:
						v3 = "DDERR_NOROTATIONHW";
						goto LABEL_182;
					case DDERR_NOSTRETCHHW:
						v3 = "DDERR_NOSTRETCHHW";
						goto LABEL_182;
					case DDERR_NOT4BITCOLOR:
						v3 = "DDERR_NOT4BITCOLOR";
						goto LABEL_182;
					case DDERR_NOT4BITCOLORINDEX:
						v3 = "DDERR_NOT4BITCOLORINDEX";
						goto LABEL_182;
					case DDERR_NOT8BITCOLOR:
						v3 = "DDERR_NOT8BITCOLOR";
						goto LABEL_182;
				}
			}
			else
			{
				switch ( error_code )
				{
					case DDERR_NORASTEROPHW:
						v3 = "DDERR_NORASTEROPHW";
						goto LABEL_182;
					case DDERR_NOEXCLUSIVEMODE:
						v3 = "DDERR_NOEXCLUSIVEMODE";
						goto LABEL_182;
					case DDERR_NOFLIPHW:
						v3 = "DDERR_NOFLIPHW";
						goto LABEL_182;
					case DDERR_NOGDI:
						v3 = "DDERR_NOGDI";
						goto LABEL_182;
					case DDERR_NOMIRRORHW:
						v3 = "DDERR_NOMIRRORHW";
						goto LABEL_182;
					case DDERR_NOTFOUND:
						v3 = "DDERR_NOTFOUND";
						goto LABEL_182;
					case DDERR_NOOVERLAYHW:
						v3 = "DDERR_NOOVERLAYHW";
						goto LABEL_182;
				}
			}
		}
		goto LABEL_178;
	}
	if ( error_code == DDERR_NOCOLORKEYHW )
	{
		v3 = "DDERR_NOCOLORKEYHW";
		goto LABEL_182;
	}
	if ( error_code > DDERR_INVALIDCLIPLIST )
	{
		if ( error_code > DDERR_NO3D )
		{
			switch ( error_code )
			{
				case DDERR_NOALPHAHW:
					v3 = "DDERR_NOALPHAHW";
					goto LABEL_182;
				case DDERR_NOCLIPLIST:
					v3 = "DDERR_NOCLIPLIST";
					goto LABEL_182;
				case DDERR_NOCOLORCONVHW:
					v3 = "DDERR_NOCOLORCONVHW";
					goto LABEL_182;
				case DDERR_NOCOOPERATIVELEVELSET:
					v3 = "DDERR_NOCOOPERATIVELEVELSET";
					goto LABEL_182;
				case DDERR_NOCOLORKEY:
					v3 = "DDERR_NOCOLORKEY";
					goto LABEL_182;
			}
		}
		else
		{
			switch ( error_code )
			{
				case DDERR_NO3D:
					v3 = "DDERR_NO3D";
					goto LABEL_182;
				case DDERR_INVALIDMODE:
					v3 = "DDERR_INVALIDMODE";
					goto LABEL_182;
				case DDERR_INVALIDOBJECT:
					v3 = "DDERR_INVALIDOBJECT";
					goto LABEL_182;
				case DDERR_INVALIDPIXELFORMAT:
					v3 = "DDERR_INVALIDPIXELFORMAT";
					goto LABEL_182;
				case DDERR_INVALIDRECT:
					v3 = "DDERR_INVALIDRECT";
					goto LABEL_182;
				case DDERR_LOCKEDSURFACES:
					v3 = "DDERR_LOCKEDSURFACES";
					goto LABEL_182;
			}
		}
		goto LABEL_178;
	}
	if ( error_code == DDERR_INVALIDCLIPLIST )
	{
		v3 = "DDERR_INVALIDCLIPLIST";
		goto LABEL_182;
	}
	if ( error_code > DDERR_CANNOTDETACHSURFACE )
	{
		switch ( error_code )
		{
			case DDERR_CURRENTLYNOTAVAIL:
				v3 = "DDERR_CURRENTLYNOTAVAIL";
				goto LABEL_182;
			case DDERR_EXCEPTION:
				v3 = "DDERR_EXCEPTION";
				goto LABEL_182;
			case DDERR_HEIGHTALIGN:
				v3 = "DDERR_HEIGHTALIGN";
				goto LABEL_182;
			case DDERR_INCOMPATIBLEPRIMARY:
				v3 = "DDERR_INCOMPATIBLEPRIMARY";
				goto LABEL_182;
			case DDERR_INVALIDCAPS:
				v3 = "DDERR_INVALIDCAPS";
				goto LABEL_182;
		}
		goto LABEL_178;
	}
	switch ( error_code )
	{
		case DDERR_CANNOTDETACHSURFACE:
			v3 = "DDERR_CANNOTDETACHSURFACE";
			goto LABEL_182;
		case DDERR_UNSUPPORTED:
			v3 = "DDERR_UNSUPPORTED";
			goto LABEL_182;
		case DDERR_GENERIC:
			v3 = "DDERR_GENERIC";
			goto LABEL_182;
		case DDERR_OUTOFMEMORY:
			v3 = "DDERR_OUTOFMEMORY";
			goto LABEL_182;
		case DDERR_INVALIDPARAMS:
			v3 = "DDERR_INVALIDPARAMS";
			goto LABEL_182;
		case DDERR_ALREADYINITIALIZED:
			v3 = "DDERR_ALREADYINITIALIZED";
			goto LABEL_182;
	}
	if ( error_code != DDERR_CANNOTATTACHSURFACE )
	{
LABEL_178:
		strcpy(v4, "DDERR unknown 0x%x");
		sprintf(error_buf, v4, error_code);
		return;
	}
	v3 = "DDERR_CANNOTATTACHSURFACE";
LABEL_182:
	strncpy(error_buf, v3, error_buf_len);
}

//----- (00401831) --------------------------------------------------------
void __fastcall GetDSErr(int error_code, char *error_buf, int error_buf_len)
{
	const char *v3; // eax
	char v4[4]; // [esp+0h] [ebp-14h]

	if ( error_code > DSERR_INVALIDCALL )
	{
		switch ( error_code )
		{
			case DSERR_PRIOLEVELNEEDED:
				v3 = "DSERR_PRIOLEVELNEEDED";
				goto LABEL_29;
			case DSERR_BADFORMAT:
				v3 = "DSERR_BADFORMAT";
				goto LABEL_29;
			case DSERR_NODRIVER:
				v3 = "DSERR_NODRIVER";
				goto LABEL_29;
			case DSERR_ALREADYINITIALIZED:
				v3 = "DSERR_ALREADYINITIALIZED";
				goto LABEL_29;
			case DSERR_BUFFERLOST:
				v3 = "DSERR_BUFFERLOST";
				goto LABEL_29;
			case DS_OK:
				v3 = "DS_OK";
				goto LABEL_29;
		}
		goto LABEL_22;
	}
	switch ( error_code )
	{
		case DSERR_INVALIDCALL:
			v3 = "DSERR_INVALIDCALL";
			goto LABEL_29;
		case E_NOINTERFACE:
			v3 = "E_NOINTERFACE";
			goto LABEL_29;
		case DSERR_NOAGGREGATION:
			v3 = "DSERR_NOAGGREGATION";
			goto LABEL_29;
		case DSERR_OUTOFMEMORY:
			v3 = "DSERR_OUTOFMEMORY";
			goto LABEL_29;
		case DSERR_INVALIDPARAM:
			v3 = "DSERR_INVALIDPARAM";
			goto LABEL_29;
		case DSERR_ALLOCATED:
			v3 = "DSERR_ALLOCATED";
			goto LABEL_29;
	}
	if ( error_code != DSERR_CONTROLUNAVAIL )
	{
LABEL_22:
		strcpy(v4, "DSERR unknown 0x%x");
		sprintf(error_buf, v4, error_code);
		return;
	}
	v3 = "DSERR_CONTROLUNAVAIL";
LABEL_29:
	strncpy(error_buf, v3, error_buf_len);
}

//----- (0040193A) --------------------------------------------------------
char *__cdecl GetLastErr()
{
	int v0; // eax

	v0 = GetLastError();
	return GetErr(v0);
}

//----- (00401947) --------------------------------------------------------
void TermMsg(char *pszFmt, ...)
{
	va_list arglist; // [esp+8h] [ebp+8h]

	va_start(arglist, pszFmt);
	FreeDlg();
	if ( pszFmt )
		MsgBox(pszFmt, arglist);
	init_cleanup(0);
	exit(1);
}

//----- (00401975) --------------------------------------------------------
void __fastcall MsgBox(char *pszFmt, va_list va)
{
	char Text[256]; // [esp+0h] [ebp-100h]

	wvsprintfA(Text, pszFmt, va);
	if ( ghMainWnd )
		SetWindowPos(ghMainWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
	MessageBoxA(ghMainWnd, Text, "ERROR", MB_TASKMODAL|MB_ICONHAND);
}

//----- (004019C7) --------------------------------------------------------
void __cdecl FreeDlg()
{
	if ( terminating && cleanup_thread_id != GetCurrentThreadId() )
		Sleep(20000u);
	terminating = 1;
	cleanup_thread_id = GetCurrentThreadId();
	dx_cleanup();
	if ( (unsigned char)gbMaxPlayers > 1u )
	{
		if ( SNetLeaveGame(3) )
			Sleep(2000u);
	}
	SNetDestroy();
	ShowCursor(1);
}
// 4B7A34: using guessed type int terminating;
// 4B7A38: using guessed type int cleanup_thread_id;
// 679660: using guessed type char gbMaxPlayers;

//----- (00401A30) --------------------------------------------------------
void DrawDlg(char *pszFmt, ...)
{
	char text[256]; // [esp+0h] [ebp-100h]
	va_list arglist; // [esp+10Ch] [ebp+Ch]

	va_start(arglist, pszFmt);
	wvsprintfA(text, pszFmt, arglist);
	SDrawMessageBox(text, "Diablo", MB_TASKMODAL|MB_ICONEXCLAMATION);
}

//----- (00401A65) --------------------------------------------------------
void __fastcall DDErrDlg(int error_code, int log_line_nr, char *log_file_path)
{
	int v3; // esi
	char *v4; // eax

	v3 = log_line_nr;
	if ( error_code )
	{
		v4 = GetErr(error_code);
		TermMsg("Direct draw error (%s:%d)\n%s", log_file_path, v3, v4);
	}
}

//----- (00401A88) --------------------------------------------------------
void __fastcall DSErrDlg(int error_code, int log_line_nr, char *log_file_path)
{
	int v3; // esi
	char *v4; // eax

	v3 = log_line_nr;
	if ( error_code )
	{
		v4 = GetErr(error_code);
		TermMsg("Direct sound error (%s:%d)\n%s", log_file_path, v3, v4);
	}
}

//----- (00401AAB) --------------------------------------------------------
void __fastcall CenterDlg(HWND hDlg)
{
	LONG v1; // esi
	LONG v2; // edi
	int v3; // ebx
	char *v4; // eax
	struct tagRECT Rect; // [esp+Ch] [ebp-1Ch]
	int v6; // [esp+1Ch] [ebp-Ch]
	HDC hdc; // [esp+20h] [ebp-8h]
	HWND hWnd; // [esp+24h] [ebp-4h]

	hWnd = hDlg;
	GetWindowRect(hDlg, &Rect);
	v1 = Rect.right - Rect.left;
	v2 = Rect.bottom - Rect.top;
	hdc = GetDC(hWnd);
	v6 = GetDeviceCaps(hdc, HORZRES);
	v3 = GetDeviceCaps(hdc, VERTRES);
	ReleaseDC(hWnd, hdc);
	if ( !SetWindowPos(hWnd, HWND_TOP, (v6 - v1) / 2, (v3 - v2) / 2, 0, 0, SWP_NOZORDER|SWP_NOSIZE) )
	{
		v4 = GetLastErr();
		TermMsg("center_window: %s", v4);
	}
}

//----- (00401B3D) --------------------------------------------------------
void __fastcall TermDlg(int template_id, int error_code, char *log_file_path, int log_line_nr)
{
	int v4; // ebx
	int v5; // edi
	char *v6; // esi
	char *v7; // eax
	char *v8; // eax
	LPARAM dwInitParam[128]; // [esp+Ch] [ebp-200h]

	v4 = error_code;
	v5 = template_id;
	FreeDlg();
	v6 = log_file_path;
	v7 = strrchr(log_file_path, '\\');
	if ( v7 )
		v6 = v7 + 1;
	v8 = GetErr(v4);
	wsprintfA((LPSTR)dwInitParam, "%s\nat: %s line %d", v8, v6, log_line_nr);
	if ( DialogBoxParamA(ghInst, (LPCSTR)(unsigned short)v5, ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)dwInitParam) == -1 )
		TermMsg("ErrDlg: %d", v5);
	TermMsg(0);
}

//----- (00401BCA) --------------------------------------------------------
bool __stdcall FuncDlg(HWND hDlg, UINT uMsg, WPARAM wParam, char *text)
{
	if ( uMsg == WM_INITDIALOG )
	{
		TextDlg(hDlg, text);
	}
	else
	{
		if ( uMsg != WM_COMMAND )
			return 0;
		if ( (_WORD)wParam == 1 )
		{
			EndDialog(hDlg, 1);
		}
		else if ( (_WORD)wParam == 2 )
		{
			EndDialog(hDlg, 0);
		}
	}
	return 1;
}

//----- (00401C0F) --------------------------------------------------------
void __fastcall TextDlg(HWND hDlg, char *text)
{
	char *v2; // esi
	HWND v3; // edi

	v2 = text;
	v3 = hDlg;
	CenterDlg(hDlg);
	if ( v2 )
		SetDlgItemTextA(v3, 1000, v2);
}

//----- (00401C2E) --------------------------------------------------------
void __fastcall ErrDlg(template_id template_id, int error_code, char *log_file_path, int log_line_nr)
{
	char *v4; // esi
	int v5; // edi
	unsigned short v6; // bx
	char *v7; // eax
	char *v8; // eax
	LPARAM dwInitParam[128]; // [esp+Ch] [ebp-200h]

	v4 = log_file_path;
	v5 = error_code;
	v6 = template_id;
	v7 = strrchr(log_file_path, '\\');
	if ( v7 )
		v4 = v7 + 1;
	v8 = GetErr(v5);
	wsprintfA((LPSTR)dwInitParam, "%s\nat: %s line %d", v8, v4, log_line_nr);
	DialogBoxParamA(ghInst, (LPCSTR)v6, ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)dwInitParam);
}

//----- (00401C9C) --------------------------------------------------------
void __fastcall FileErrDlg(char *error)
{
	char *v1; // esi

	v1 = error;
	FreeDlg();
	if ( !v1 )
		v1 = &empty_string;
	if ( DialogBoxParamA(ghInst, (LPCSTR)0x6A, ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)v1) == -1 )
		TermMsg("FileErrDlg");
	TermMsg(0);
}

//----- (00401CE1) --------------------------------------------------------
void __fastcall DiskFreeDlg(char *error)
{
	char *v1; // esi

	v1 = error;
	FreeDlg();
	if ( DialogBoxParamA(ghInst, (LPCSTR)0x6E, ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)v1) == -1 )
		TermMsg("DiskFreeDlg");
	TermMsg(0);
}

//----- (00401D1D) --------------------------------------------------------
bool __cdecl InsertCDDlg()
{
	int v0; // edi

	ShowCursor(1);
	v0 = DialogBoxParamA(ghInst, (LPCSTR)0x70, ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)&empty_string);
	if ( v0 == -1 )
		TermMsg("InsertCDDlg");
	ShowCursor(0);
	return v0 == 1;
}

//----- (00401D68) --------------------------------------------------------
void __fastcall DirErrDlg(char *error)
{
	char *v1; // esi

	v1 = error;
	FreeDlg();
	if ( DialogBoxParamA(ghInst, (LPCSTR)0x72, ghMainWnd, (DLGPROC)FuncDlg, (LPARAM)v1) == -1 )
		TermMsg("DirErrorDlg");
	TermMsg(0);
}
