// ref: 0x1000FDEE
_DWORD *UNKCALL Title_1000FDEE(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	_DWORD *v2; // edi
	_DWORD *result; // eax
	int v4; // eax
	_DWORD *v5; // esi
	struct tagRECT Rect; // [esp+Ch] [ebp-18h]
	HWND v7; // [esp+1Ch] [ebp-8h]
	HWND hWnda; // [esp+20h] [ebp-4h]

	v1 = hWnd;
	v7 = hWnd;
	v2 = (_DWORD *)GetWindowLongA(hWnd, -21);
	hWnda = GetDlgItem(v1, 1043);
	result = (_DWORD *)IsWindowVisible(v1);
	if ( result && hWnda && v2 && *v2 && dword_1002A510[0] )
	{
		v4 = dword_1002A58C + 1;
		dword_1002A58C = v4;
		if ( !dword_1002A510[v4] || v4 >= 30 )
			dword_1002A58C = 0;
		GetWindowRect(hWnda, &Rect);
		ScreenToClient(v1, (LPPOINT)&Rect);
		ScreenToClient(v7, (LPPOINT)&Rect.right);
		result = GetPropA(v7, "TITLE_BUFFER");
		v5 = result;
		if ( result )
		{
			SBltROP3(*result, Rect.left + *v2 + Rect.top * v2[1], result[1], result[2], result[1], v2[1], 0, 13369376);
			STransBlt(*v5, 0, 0, v5[1], dword_1002A510[dword_1002A58C]);
			result = (_DWORD *)InvalidateRect(hWnda, 0, 0);
		}
	}
	return result;
} */
// 1001036A: using guessed type int __stdcall STransBlt(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A58C: using guessed type int dword_1002A58C;

// ref: 0x1000FEED
int Title_1000FEED() { return 0; }
/* {
	int *v0; // esi
	int result; // eax

	v0 = dword_1002A510;
	do
	{
		result = *v0;
		if ( *v0 )
		{
			result = STransDelete(*v0);
			*v0 = 0;
		}
		++v0;
	}
	while ( (signed int)v0 < (signed int)&dword_1002A588 );
	return result;
} */
// 1001033A: using guessed type int __stdcall STransDelete(_DWORD);
// 1002A588: using guessed type int dword_1002A588;

// ref: 0x1000FF0F
_DWORD *UNKCALL Title_1000FF0F(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	_DWORD *result; // eax
	_DWORD *v3; // esi
	int v4; // eax

	v1 = hWnd;
	Title_1000FEED();
	result = RemovePropA(v1, "TITLE_BUFFER");
	v3 = result;
	if ( result )
	{
		v4 = *result;
		if ( v4 )
		{
			SMemFree(v4, "C:\\Src\\Diablo\\DiabloUI\\Title.cpp", 114, 0);
			*v3 = 0;
		}
		result = (_DWORD *)SMemFree(v3, "C:\\Src\\Diablo\\DiabloUI\\Title.cpp", 117, 0);
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000FF51
HWND UNKCALL Title_1000FF51(HWND arg) { return 0; }
/* {
	HWND result; // eax
	int *v2; // esi
	int v3; // eax
	struct tagRECT Rect; // [esp+0h] [ebp-18h]
	HWND v5; // [esp+10h] [ebp-8h]
	HWND hDlg; // [esp+14h] [ebp-4h]

	hDlg = arg;
	Title_1000FF0F(arg);
	result = GetDlgItem(hDlg, 1043);
	v5 = result;
	if ( result )
	{
		GetClientRect(result, &Rect);
		v2 = (int *)SMemAlloc(12, "C:\\Src\\Diablo\\DiabloUI\\Title.cpp", 134, 0);
		v3 = SMemAlloc(Rect.right * Rect.bottom, "C:\\Src\\Diablo\\DiabloUI\\Title.cpp", 136, 8);
		*v2 = v3;
		v2[1] = Rect.right;
		v2[2] = Rect.bottom;
		SDlgSetBitmapI(v5, 0, 0, -1, 1, v3, 0, Rect.right, Rect.bottom, -1);
		result = (HWND)SetPropA(hDlg, "TITLE_BUFFER", v2);
	}
	return result;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000FFE8
_DWORD *__fastcall Title_1000FFE8(HWND hWnd, int a2) { return 0; }
/* {
	HWND v2; // esi
	int v3; // edi
	_DWORD *result; // eax
	int v5; // esi
	int v6; // ebx
	int v7; // [esp+8h] [ebp-20h]
	int v8; // [esp+Ch] [ebp-1Ch]
	int v9; // [esp+10h] [ebp-18h]
	int v10; // [esp+14h] [ebp-14h]
	char v11; // [esp+18h] [ebp-10h]
	int v12; // [esp+1Ch] [ebp-Ch]
	int *v13; // [esp+20h] [ebp-8h]
	int v14; // [esp+24h] [ebp-4h]

	v2 = hWnd;
	v3 = 0;
	v14 = 0;
	local_100078BE(a2, &v14, &v11);
	result = GetPropA(v2, "TITLE_BUFFER");
	v5 = (int)result;
	if ( v14 )
	{
		if ( result )
		{
			v6 = v12 / result[2];
			if ( v6 > 30 )
				v6 = 30;
			if ( v6 > 0 )
			{
				v13 = dword_1002A510;
				do
				{
					v7 = 0;
					v9 = *(_DWORD *)(v5 + 4) - 1;
					v8 = v3 * *(_DWORD *)(v5 + 8);
					v10 = *(_DWORD *)(v5 + 8) + v8 - 1;
					STransCreateI(v14, *(_DWORD *)(v5 + 4), *(_DWORD *)(v5 + 8), 8, &v7, 16777466, v13);
					++v13;
					++v3;
				}
				while ( v3 < v6 );
			}
		}
		result = (_DWORD *)SMemFree(v14, "C:\\Src\\Diablo\\DiabloUI\\Title.cpp", 197, 0);
	}
	dword_1002A58C = 0;
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010346: using guessed type int __stdcall STransCreateI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A58C: using guessed type int dword_1002A58C;

// ref: 0x1001009E
int __fastcall Title_1001009E(HWND hWnd, int a2, HWND hWnda) { return 0; }
/* {
	int v3; // edi
	HWND v4; // esi

	v3 = a2;
	v4 = hWnd;
	Title_1000FF51(hWnd);
	Title_1000FFE8(v4, v3);
	Title_1000FDEE(v4);
	return SDlgSetTimer(v4, 2, 55, Title_100100CB);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x100100CB
_DWORD *__stdcall Title_100100CB(HWND hWnd, int a2, int a3, int a4) { return 0; }
/* {
	return Title_1000FDEE(hWnd);
} */

// ref: 0x100100DC
signed int Title_100100DC() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A588 = 2139095040;
	return result;
} */
// 1002A588: using guessed type int dword_1002A588;

// ref: 0x100100E7
_DWORD *UNKCALL Title_100100E7(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi

	v1 = hWnd;
	SDlgKillTimer(hWnd, 2);
	return Title_1000FF0F(v1);
} */
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);

// ref: 0x100100FA
void __stdcall UiTitleDialog(int a1) { return; }
/* {
	int v1; // eax

	artfont_10001159();
	v1 = SDrawGetFrameWindow();
	SDlgDialogBoxParam(hInstance, "TITLESCREEN_DIALOG", v1, Title_10010126, a1);
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x10010126
int __stdcall Title_10010126(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v5; // eax
	int v6; // [esp+0h] [ebp-8h]

	if ( Msg <= 0x111 )
	{
		if ( Msg != 273 )
		{
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
							v5 = (HWND)SDrawGetFrameWindow();
							SendMessageA(v5, Msg, wParam, lParam);
						}
						else if ( Msg == 272 )
						{
							Title_1001025A(hWnd, lParam);
							PostMessageA(hWnd, 0x7E8u, 0, 0);
							return 1;
						}
					}
					return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
				}
				goto LABEL_25;
			}
			Title_10010235(hWnd);
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		goto LABEL_25;
	}
	if ( Msg != 275 )
	{
		if ( Msg != 513 && Msg != 516 )
		{
			if ( Msg == 528 )
			{
				if ( (_WORD)wParam == 513 || (_WORD)wParam == 516 )
					Title_100102D7(hWnd);
			}
			else if ( Msg == 2024 )
			{
				if ( !Fade_1000739F() )
					Fade_100073FD(hWnd, v6);
				return 0;
			}
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
LABEL_25:
		Title_100102D7(hWnd);
		return 0;
	}
	if ( wParam == 1 )
		goto LABEL_25;
	return 0;
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x10010235
void UNKCALL Title_10010235(HWND hDlg) { return; }
/* {
	HWND v1; // esi
	_DWORD *v2; // eax

	v1 = hDlg;
	Title_100100E7(hDlg);
	Doom_10006C53(v1, (int *)&unk_10023340);
	v2 = (_DWORD *)GetWindowLongA(v1, -21);
	local_10007F72(v2);
} */

// ref: 0x1001025A
int __fastcall Title_1001025A(HWND hWnd, int a2) { return 0; }
/* {
	int v2; // ebx
	HWND v3; // esi
	int *v4; // edi
	int result; // eax
	HWND v6; // [esp+0h] [ebp-Ch]

	v2 = a2;
	v3 = hWnd;
	v4 = (int *)local_10007F46();
	SetWindowLongA(v3, -21, (LONG)v4);
	if ( v4 )
	{
		local_10007944((int)v3, 0, &byte_10029448, -1, 1, (int)"ui_art\\title.pcx", v4, v4 + 1, 0);
		Fade_100073C5(v3, 0);
	}
	Doom_100068AB(v3, (int *)&unk_10023340, 3);
	Title_1001009E(v3, (int)"ui_art\\logo.pcx", v6);
	if ( v2 )
		result = SDlgSetTimer(v3, 1, 1000 * v2, 0);
	else
		result = SDlgSetTimer(v3, 1, 5000, 0);
	return result;
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x100102D7
int UNKCALL Title_100102D7(void *arg) { return 0; }
/* {
	void *v1; // esi

	v1 = arg;
	Fade_100073B4();
	SDlgKillTimer(v1, 1);
	Fade_100072BE(10);
	return SDlgEndDialog(v1, 1);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);
