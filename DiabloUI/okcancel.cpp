// ref: 0x10008F31
int __fastcall OkCancel_10008F31(HWND hWnd, const CHAR *a2) { return 0; }
/* {
	HWND v2; // ebx
	HDC v3; // edi
	void *v4; // eax
	int v5; // eax
	int result; // eax
	LONG v7; // [esp+14h] [ebp-20h]
	LONG v8; // [esp+18h] [ebp-1Ch]
	struct tagRECT Rect; // [esp+1Ch] [ebp-18h]
	HGDIOBJ h; // [esp+2Ch] [ebp-8h]
	LPCSTR lpchText; // [esp+30h] [ebp-4h]

	lpchText = a2;
	v2 = hWnd;
	if ( !a2 || !*a2 )
		goto LABEL_13;
	if ( !hWnd )
		goto LABEL_14;
	GetClientRect(hWnd, &Rect);
	--Rect.right;
	--Rect.bottom;
	v7 = Rect.right;
	v8 = Rect.bottom;
	v3 = GetDC(v2);
	v4 = (void *)SendMessageA(v2, 0x31u, 0, 0);
	h = SelectObject(v3, v4);
	if ( !v3 )
		goto LABEL_13;
	v5 = strlen(lpchText);
	DrawTextA(v3, lpchText, v5, &Rect, 0x410u);
	if ( h )
		SelectObject(v3, h);
	ReleaseDC(v2, v3);
	if ( Rect.bottom > v8 || Rect.right > v7 )
LABEL_14:
		result = 1;
	else
LABEL_13:
		result = 0;
	return result;
} */

// ref: 0x10008FEC
signed int OkCancel_10008FEC() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A2E4 = 2139095040;
	return result;
} */
// 1002A2E4: using guessed type int dword_1002A2E4;

// ref: 0x10008FF7
HGDIOBJ __stdcall OkCancel_10008FF7(HWND a1, UINT Msg, WPARAM wParam, HWND hWnd) { return 0; }
/* {
	HWND v5; // ecx
	int v6; // edx
	HWND v7; // eax
	LONG v8; // eax
	HWND v9; // eax

	if ( Msg == 2 )
	{
		ShowCursor(0);
		OkCancel_10009117(a1);
		return (HGDIOBJ)SDlgDefDialogProc(a1, Msg, wParam, hWnd);
	}
	if ( Msg <= 0x103 )
		return (HGDIOBJ)SDlgDefDialogProc(a1, Msg, wParam, hWnd);
	if ( Msg <= 0x105 )
	{
		v9 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v9, Msg, wParam, (LPARAM)hWnd);
		return (HGDIOBJ)SDlgDefDialogProc(a1, Msg, wParam, hWnd);
	}
	if ( Msg != 272 )
	{
		if ( Msg != 273 )
		{
			if ( Msg == 312 && GetWindowLongA(hWnd, -12) == 1038 )
			{
				local_10007C2E((HDC)wParam);
				return GetStockObject(5);
			}
			return (HGDIOBJ)SDlgDefDialogProc(a1, Msg, wParam, hWnd);
		}
		if ( (unsigned short)wParam == 1 )
		{
			v7 = GetFocus();
			v8 = GetWindowLongA(v7, -12);
			v5 = a1;
			if ( v8 == 1109 )
			{
				v6 = 1;
				goto LABEL_16;
			}
		}
		else
		{
			if ( (unsigned short)wParam != 2 )
			{
				if ( (unsigned short)wParam == 1109 )
				{
					v5 = a1;
					v6 = 1;
LABEL_16:
					OkCancel_100092F5((int)v5, v6);
				}
				return (HGDIOBJ)SDlgDefDialogProc(a1, Msg, wParam, hWnd);
			}
			v5 = a1;
		}
		v6 = 2;
		goto LABEL_16;
	}
	ShowCursor(1);
	if ( !OkCancel_10009161(a1, (int)hWnd) )
		SDlgEndDialog(a1, -16777216);
	return (HGDIOBJ)1;
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x10009117
void **UNKCALL OkCancel_10009117(HWND hWnd) { return 0; }
/* {
	_DWORD *result; // eax
	_DWORD *v2; // esi
	int v3; // eax
	int v4; // eax

	result = RemovePropA(hWnd, "DLGBMP");
	v2 = result;
	if ( result )
	{
		v3 = *result;
		if ( v3 )
			SMemFree(v3, "C:\\Src\\Diablo\\DiabloUI\\OkCancel.cpp", 48, 0);
		v4 = v2[1];
		if ( v4 )
			SMemFree(v4, "C:\\Src\\Diablo\\DiabloUI\\OkCancel.cpp", 50, 0);
		result = (_DWORD *)SMemFree(v2, "C:\\Src\\Diablo\\DiabloUI\\OkCancel.cpp", 51, 0);
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10009161
signed int __fastcall OkCancel_10009161(HWND a1, int a2) { return 0; }
/* {
	int v2; // esi
	bool v3; // zf
	HWND v4; // edi
	char *v5; // edi
	HWND v6; // eax
	HWND v7; // edi
	HWND v8; // edi
	HWND v9; // eax
	const CHAR *v10; // ST1C_4
	HWND v11; // eax
	HWND v12; // edi
	int v14; // [esp+Ch] [ebp-20h]
	int v15; // [esp+10h] [ebp-1Ch]
	int v16; // [esp+14h] [ebp-18h]
	char v17; // [esp+18h] [ebp-14h]
	HWND v18; // [esp+20h] [ebp-Ch]
	const char *v19; // [esp+24h] [ebp-8h]
	HWND hWnd; // [esp+28h] [ebp-4h]

	v2 = a2;
	hWnd = a1;
	v14 = 1109;
	v15 = 2;
	v16 = 0;
	v18 = (HWND)SMemAlloc(8, "C:\\Src\\Diablo\\DiabloUI\\OkCancel.cpp", 110, 0);
	SetPropA(hWnd, "DLGBMP", v18);
	if ( *(_DWORD *)(v2 + 8) )
	{
		v3 = *(_DWORD *)(v2 + 12) == 0;
		v19 = "ui_art\\lrpopup.pcx";
		if ( v3 )
			v19 = "ui_art\\lpopup.pcx";
	}
	else if ( *(_DWORD *)(v2 + 12) )
	{
		v19 = "ui_art\\srpopup.pcx";
	}
	else
	{
		v19 = "ui_art\\spopup.pcx";
	}
	v4 = GetParent(hWnd);
	if ( (HWND)SDrawGetFrameWindow() == v4 )
	{
		local_10007944((int)hWnd, 0, &byte_10029448, -1, 1, (int)v19, (int *)v18, 0, 1);
		v5 = local_10007895(0);
		SDrawUpdatePalette(0, 10, v5, 0);
		SDrawUpdatePalette(112, 144, v5 + 448, 1);
	}
	else
	{
		v6 = GetParent(hWnd);
		local_10007944((int)hWnd, (int)v6, "Popup", -1, 1, (int)v19, (int *)v18, 0, 1);
	}
	v7 = GetParent(hWnd);
	if ( (HWND)SDrawGetFrameWindow() == v7 )
		Fade_100073EF(hWnd);
	v8 = v18 + 1;
	local_100078BE((int)"ui_art\\but_sml.pcx", (int *)v18 + 1, &v17);
	local_10007B1B(hWnd, &v14, *(_DWORD *)v8, &v17);
	v9 = GetDlgItem(hWnd, 1026);
	v10 = *(const CHAR **)(v2 + 4);
	v18 = v9;
	SetWindowTextA(v9, v10);
	if ( *(_DWORD *)(v2 + 16) && OkCancel_10008F31(v18, *(const CHAR **)(v2 + 4)) )
		return 0;
	if ( *(_DWORD *)v2 )
	{
		v11 = GetDlgItem(hWnd, 1038);
		v12 = v11;
		if ( *(_DWORD *)(v2 + 16) && OkCancel_10008F31(v11, *(const CHAR **)v2) )
			return 0;
		if ( v12 )
			SetWindowTextA(v12, *(LPCSTR *)v2);
	}
	return 1;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 100103FA: using guessed type int __stdcall SDrawUpdatePalette(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x100092F5
int __fastcall OkCancel_100092F5(int a1, int a2) { return 0; }
/* {
	int v2; // esi
	int v3; // edi

	v2 = a2;
	v3 = a1;
	TitleSnd_1001031F();
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);

// ref: 0x1000930A
int __fastcall OkCancel_1000930A(int a1, int a2, int a3) { return 0; }
/* {
	int v4; // [esp+0h] [ebp-14h]
	int v5; // [esp+4h] [ebp-10h]
	int v6; // [esp+8h] [ebp-Ch]
	int v7; // [esp+Ch] [ebp-8h]
	int v8; // [esp+10h] [ebp-4h]

	v5 = a2;
	v6 = 0;
	v4 = 0;
	v8 = 0;
	v7 = a3;
	return SDlgDialogBoxParam(hInstance, "OK_DIALOG", a1, OkCancel_10008FF7, &v4);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10009342
void __cdecl UiMessageBoxCallback() { return; }
//LPCSTR __stdcall UiMessageBoxCallback(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) { return 0; }
/* {
	int v4; // eax
	bool v5; // sf
	unsigned char v6; // of
	size_t v7; // eax
	CHAR *v8; // eax
	int v9; // ecx
	LPCSTR v11; // [esp+0h] [ebp-24h]
	LPCSTR v12; // [esp+4h] [ebp-20h]
	int v13; // [esp+8h] [ebp-1Ch]
	BOOL v14; // [esp+Ch] [ebp-18h]
	int v15; // [esp+10h] [ebp-14h]
	int v16; // [esp+14h] [ebp-10h]
	LPCSTR v17; // [esp+18h] [ebp-Ch]
	const char *v18; // [esp+1Ch] [ebp-8h]
	LPCSTR v19; // [esp+20h] [ebp-4h]

	v11 = lpCaption;
	v12 = lpText;
	v18 = "OK_DIALOG";
	v15 = 1;
	if ( uType & 0xF )
		v18 = "OKCANCEL_DIALOG";
	v14 = (uType & 0xF0) == 16 || (uType & 0xF0) == 48;
	v4 = 0;
	v13 = 0;
	while ( 1 )
	{
		v19 = (LPCSTR)SDlgDialogBoxParam(hInstance, &v18[32 * v4], hWnd, OkCancel_10008FF7, &v11);
		if ( v19 != (LPCSTR)-16777216 )
			break;
		v4 = v13 + 1;
		v6 = __OFSUB__(v13 + 1, 2);
		v5 = v13++ - 1 < 0;
		if ( !(v5 ^ v6) )
		{
			v7 = strlen(lpText);
			v8 = (CHAR *)SMemAlloc(v7 + 256, "C:\\Src\\Diablo\\DiabloUI\\OkCancel.cpp", 392, 0);
			v16 = 0;
			v17 = v8;
			v19 = lpText;
			if ( *lpText )
			{
				v9 = v16;
				do
				{
					if ( *v19 <= 32 )
						v9 = 0;
					*v8++ = *v19;
					if ( ++v9 > 18 )
					{
						*v8++ = 10;
						v9 = 0;
					}
					++v19;
				}
				while ( *v19 );
			}
			*v8 = 0;
			v12 = v17;
			v19 = (LPCSTR)SDlgDialogBoxParam(hInstance, v18, hWnd, OkCancel_10008FF7, &v11);
			SMemFree(v17, "C:\\Src\\Diablo\\DiabloUI\\OkCancel.cpp", 416, 0);
			if ( v19 == (LPCSTR)-16777216 )
				return (LPCSTR)MessageBoxA(hWnd, lpText, lpCaption, uType);
			return v19;
		}
	}
	return v19;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
