// ref: 0x10005297
signed int credits_10005297() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_100296EC = 2139095040;
	return result;
} */
// 100296EC: using guessed type int dword_100296EC;

// ref: 0x100052A2
void __stdcall UiCreditsDialog(int a1) { return; }
/* {
	int v1; // eax

	v1 = SDrawGetFrameWindow();
	SDlgDialogBoxParam(hInstance, "CREDITS_DIALOG", v1, credits_100052C7, 25);
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x100052C7
int __fastcall credits_100052C7(int a1, int a2, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v7; // eax
	int v8; // [esp+0h] [ebp-Ch]

	if ( Msg > 0x111 )
	{
		if ( Msg == 275 )
		{
			credits_100055C0(hWnd);
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		if ( Msg == 513 || Msg == 516 )
			goto LABEL_12;
		if ( Msg != 528 )
		{
			if ( Msg == 2024 )
			{
				if ( !Fade_1000739F() )
					Fade_100073FD(hWnd, v8);
				return 0;
			}
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		if ( (_WORD)wParam != 513 && (_WORD)wParam != 516 )
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
LABEL_25:
		Title_100102D7(hWnd);
		return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
	}
	if ( Msg == 273 )
		goto LABEL_25;
	if ( Msg != 2 )
	{
		if ( Msg == 135 )
			return 4;
		if ( Msg != 256 )
		{
			if ( Msg > 0x103 )
			{
				if ( Msg <= 0x105 )
				{
					v7 = (HWND)SDrawGetFrameWindow();
					SendMessageA(v7, Msg, wParam, lParam);
				}
				else if ( Msg == 272 )
				{
					credits_1000543A(hWnd, lParam);
					PostMessageA(hWnd, 0x7E8u, 0, 0);
					return 1;
				}
			}
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		if ( wParam != 32 )
			return 0;
LABEL_12:
		Title_100102D7(hWnd);
		return 0;
	}
	credits_100053D9(hWnd, a2);
	return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x100053D9
HGLOBAL __fastcall credits_100053D9(HWND hWnd, int a2) { return 0; }
/* {
	HWND v2; // edi
	_DWORD *v3; // eax
	HGLOBAL result; // eax

	v2 = hWnd;
	if ( dword_10029708 )
	{
		SGdiDeleteObject(hWnd, a2, dword_10029708);
		dword_10029708 = 0;
	}
	if ( dword_10029704 )
	{
		SMemFree(dword_10029704, "C:\\Src\\Diablo\\DiabloUI\\credits.cpp", 46, 0);
		dword_10029704 = 0;
	}
	v3 = (_DWORD *)GetWindowLongA(v2, -21);
	local_10007F72(v3);
	result = dword_100296F0;
	if ( dword_100296F0 )
	{
		result = (HGLOBAL)FreeResource(dword_100296F0);
		dword_100296F0 = 0;
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 1001038E: using guessed type int __fastcall SGdiDeleteObject(_DWORD, _DWORD, _DWORD);
// 10029704: using guessed type int dword_10029704;
// 10029708: using guessed type int dword_10029708;

// ref: 0x1000543A
int __fastcall credits_1000543A(HWND a1, int a2) { return 0; }
/* {
	int v2; // eax
	HRSRC v3; // eax
	HRSRC v4; // eax
	int v5; // eax
	int *v6; // esi
	int v7; // ebx
	int v8; // esi
	HFONT v9; // eax
	HFONT v10; // esi
	int v11; // ebx
	int result; // eax
	struct tagRECT Rect; // [esp+Ch] [ebp-18h]
	HWND v14; // [esp+1Ch] [ebp-8h]
	HWND hWnd; // [esp+20h] [ebp-4h]

	hWnd = a1;
	if ( a2 )
		v2 = 1000 / a2;
	else
		v2 = 50;
	SDlgSetTimer(a1, 1, v2, 0);
	v3 = FindResourceA(hInstance, "IDR_CREDITS", "TEXT_FILES");
	dword_100296F0 = LoadResource(hInstance, v3);
	v4 = FindResourceA(hInstance, "IDR_CREDITS", "TEXT_FILES");
	dword_100296E8 = SizeofResource(hInstance, v4);
	v5 = local_10007F46();
	v6 = (int *)v5;
	if ( v5 )
	{
		SetWindowLongA(hWnd, -21, v5);
		local_10007944((int)hWnd, 0, &byte_10029448, -1, 1, (int)"ui_art\\credits.pcx", v6, v6 + 1, 0);
		Fade_100073C5(hWnd, 0);
	}
	v14 = GetDlgItem(hWnd, 1000);
	GetWindowRect(v14, &Rect);
	v7 = Rect.right - Rect.left;
	v8 = Rect.bottom - Rect.top + 60;
	dword_10029704 = SMemAlloc((Rect.right - Rect.left) * v8, "C:\\Src\\Diablo\\DiabloUI\\credits.cpp", 122, 0);
	dword_100296F8 = v7;
	dword_100296FC = v8;
	local_10007A68(&Rect, 0, 30);
	SDlgSetBitmapI(v14, 0, 0, -1, 1, dword_10029704, &Rect, v7, v8, -1);
	dword_100296F4 = v8 - 30;
	credits_100055C0(hWnd);
	v9 = CreateFontA(-17, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0x12u, "Times New Roman");
	v10 = v9;
	if ( !v9 || (v11 = SGdiImportFont(v9, &dword_10029708), result = DeleteObject(v10), !v11) )
		result = Title_100102D7(hWnd);
	return result;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 100103B2: using guessed type int __stdcall SGdiImportFont(_DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);
// 100296E8: using guessed type int dword_100296E8;
// 100296F4: using guessed type int dword_100296F4;
// 100296F8: using guessed type int dword_100296F8;
// 100296FC: using guessed type int dword_100296FC;
// 10029704: using guessed type int dword_10029704;
// 10029708: using guessed type int dword_10029708;

// ref: 0x100055C0
BOOL UNKCALL credits_100055C0(HWND hWnd) { return 0; }
/* {
	HWND v1; // ebx
	_DWORD *v2; // edi
	struct tagRECT Rect; // [esp+Ch] [ebp-14h]
	HWND hWnda; // [esp+1Ch] [ebp-4h]

	v1 = hWnd;
	hWnda = GetDlgItem(hWnd, 1000);
	v2 = (_DWORD *)GetWindowLongA(v1, -21);
	GetWindowRect(hWnda, &Rect);
	ScreenToClient(v1, (LPPOINT)&Rect);
	ScreenToClient(v1, (LPPOINT)&Rect.right);
	SBltROP3(
		dword_10029704 + 30 * dword_100296F8,
		Rect.left + *v2 + Rect.top * v2[1],
		dword_100296F8,
		Rect.bottom - Rect.top,
		dword_100296F8,
		v2[1],
		0,
		13369376);
	--dword_100296F4;
	credits_10005660(v1);
	InvalidateRect(hWnda, 0, 0);
	return UpdateWindow(hWnda);
} */
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100296F4: using guessed type int dword_100296F4;
// 100296F8: using guessed type int dword_100296F8;
// 10029704: using guessed type int dword_10029704;

// ref: 0x10005660
signed int UNKCALL credits_10005660(void *arg) { return 0; }
/* {
	_BYTE *v1; // esi
	signed int result; // eax
	int i; // edi
	int v4; // ebp
	int v5; // ebx
	void *v6; // [esp+38h] [ebp-4h]

	v6 = arg;
	v1 = LockResource(dword_100296F0);
	dword_10029700 = dword_100296E8;
	SGdiSelectObject(dword_10029708);
	result = SGdiSetPitch(dword_100296F8);
	for ( i = dword_100296F4; dword_10029700 > 0; v1 = (_BYTE *)result )
	{
		v4 = 0;
		while ( *v1 == 9 )
		{
			v4 += 40;
			++v1;
			--dword_10029700;
		}
		result = credits_10005736(v1);
		v5 = result;
		if ( result == -1 )
			break;
		if ( i >= 0 )
		{
			result = dword_100296FC - 30;
			if ( i > dword_100296FC - 30 )
				break;
			if ( v5 )
			{
				SGdiTextOut(dword_10029704, v4 + 2, i + 2, 0x1000000, v1, v5);
				SGdiTextOut(dword_10029704, v4, i, 16777440, v1, v5);
			}
		}
		i += 22;
		result = credits_10005755((int)v1, v5);
	}
	if ( i < 0 )
		result = Title_100102D7(v6);
	return result;
} */
// 100103A6: using guessed type int __stdcall SGdiSetPitch(_DWORD);
// 100103AC: using guessed type int __stdcall SGdiSelectObject(_DWORD);
// 10010424: using guessed type int __stdcall SGdiTextOut(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100296E8: using guessed type int dword_100296E8;
// 100296F4: using guessed type int dword_100296F4;
// 100296F8: using guessed type int dword_100296F8;
// 100296FC: using guessed type int dword_100296FC;
// 10029700: using guessed type int dword_10029700;
// 10029704: using guessed type int dword_10029704;
// 10029708: using guessed type int dword_10029708;

// ref: 0x10005736
signed int __fastcall credits_10005736(_BYTE *a1) { return 0; }
/* {
	signed int result; // eax

	result = 0;
	while ( *a1 != 13 && *a1 != 10 )
	{
		++result;
		++a1;
		if ( result > dword_10029700 )
			return -1;
	}
	return result;
} */
// 10029700: using guessed type int dword_10029700;

// ref: 0x10005755
int __fastcall credits_10005755(int a1, int a2) { return 0; }
/* {
	dword_10029700 += -2 - a2;
	return a1 + a2 + 2;
} */
// 10029700: using guessed type int dword_10029700;
