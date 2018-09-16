// ref: 0x10004C33
void UNKCALL CreaDung_10004C33(void *arg) { return; }
/* {
	dword_100296CC = (int)arg;
} */
// 100296CC: using guessed type int dword_100296CC;

// ref: 0x10004C3F
signed int CreaDung_10004C3F() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_100296C4 = 2139095040;
	return result;
} */
// 100296C4: using guessed type int dword_100296C4;

// ref: 0x10004C4A
int __stdcall CreaDung_10004C4A(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v4; // eax
	HWND v6; // eax
	int savedregs; // [esp+Ch] [ebp+0h]

	if ( Msg == 2 )
	{
		CreaDung_10004E2E(hWnd);
	}
	else if ( Msg > 0x103 )
	{
		if ( Msg > 0x105 )
		{
			if ( Msg == 272 )
			{
				dword_100296D8 = lParam;
				CreaDung_10004E8B(hWnd);
			}
			else
			{
				if ( Msg == 273 )
				{
					if ( HIWORD(wParam) == 7 )
					{
						Focus_100075B7(hWnd, (HWND)lParam);
					}
					else if ( HIWORD(wParam) == 6 )
					{
						Focus_10007458((void *)lParam);
						Focus_100075DC(hWnd, (HWND)lParam);
						CreaDung_10004D75(hWnd, (unsigned short)wParam);
					}
					else if ( wParam == 327681 )
					{
						CreaDung_10004F5D(hWnd, (int)&savedregs);
					}
					else if ( (_WORD)wParam == 2 )
					{
						CreaDung_10004F40((int)hWnd, 2);
					}
					return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
				}
				if ( Msg != 275 )
				{
					if ( Msg == 513 )
						CreaDung_1000517E(hWnd, (unsigned short)lParam, (int)&savedregs, (unsigned int)lParam >> 16);
					return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
				}
				if ( wParam == 1 )
				{
					v4 = GetFocus();
					Focus_100075DC(hWnd, v4);
				}
			}
			return 0;
		}
		v6 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v6, Msg, wParam, lParam);
	}
	return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 100296D8: using guessed type int dword_100296D8;

// ref: 0x10004D75
int __fastcall CreaDung_10004D75(HWND a1, int a2) { return 0; }
/* {
	int v2; // esi
	HWND v3; // eax
	int v4; // eax
	HWND v5; // eax
	int v6; // eax
	HWND hDlg; // [esp+0h] [ebp-104h]
	CHAR Buffer; // [esp+4h] [ebp-100h]

	v2 = a2;
	hDlg = a1;
	LoadStringA(hInstance, a2 - 1055, &Buffer, 255);
	v3 = GetDlgItem(hDlg, 1097);
	if ( v3 )
	{
		v4 = GetWindowLongA(v3, -21);
		local_10007FA4(v4, &Buffer);
	}
	Doom_10006A13(hDlg, (int *)&unk_100228E8, 5);
	LoadStringA(hInstance, v2 - 65, &Buffer, 255);
	v5 = GetDlgItem(hDlg, 1099);
	if ( v5 )
	{
		v6 = GetWindowLongA(v5, -21);
		local_10007FA4(v6, &Buffer);
	}
	return Doom_10006A13(hDlg, (int *)&unk_100228F0, 1);
} */

// ref: 0x10004E2E
void UNKCALL CreaDung_10004E2E(HWND hDlg) { return; }
/* {
	HWND v1; // esi
	_DWORD *v2; // eax

	v1 = hDlg;
	Doom_10006C53(hDlg, (int *)&unk_10022904);
	Doom_10006C53(v1, (int *)&unk_100228F8);
	Doom_10006C53(v1, (int *)&unk_100228F0);
	Doom_10006C53(v1, (int *)&unk_100228E8);
	Doom_10006C53(v1, (int *)&unk_100228DC);
	v2 = (_DWORD *)GetWindowLongA(v1, -21);
	local_10007F72(v2);
	if ( dword_100296CC )
		Focus_100076C3();
} */
// 100296CC: using guessed type int dword_100296CC;

// ref: 0x10004E8B
int UNKCALL CreaDung_10004E8B(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	int v2; // eax
	int *v3; // edi

	v1 = hWnd;
	if ( dword_100296CC )
		Focus_10007719("ui_art\\focus16.pcx");
	else
		Focus_100076FA();
	SDlgSetTimer(v1, 1, 55, 0);
	v2 = local_10007F46();
	v3 = (int *)v2;
	if ( v2 )
	{
		SetWindowLongA(v1, -21, v2);
		local_10007944((int)v1, 0, "popup", -1, 1, (int)"ui_art\\seldiff.pcx", v3, v3 + 1, 0);
	}
	local_10007CB5(v1, (int *)&unk_10022904);
	Doom_100068AB(v1, (int *)&unk_100228DC, 5);
	Doom_100068AB(v1, (int *)&unk_100228E8, 5);
	Doom_100068AB(v1, (int *)&unk_100228F0, 1);
	Doom_1000658C(v1, (int *)&unk_100228F8, 4, 0);
	return Doom_1000658C(v1, (int *)&unk_10022904, 2, 1);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);
// 100296CC: using guessed type int dword_100296CC;

// ref: 0x10004F40
int __fastcall CreaDung_10004F40(int a1, int a2) { return 0; }
/* {
	int v2; // edi
	int v3; // esi

	v2 = a2;
	v3 = a1;
	TitleSnd_1001031F();
	SDlgKillTimer(v3, 1);
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);

// ref: 0x10004F5D
HWND USERCALL CreaDung_10004F5D(HWND a1, int a2) { return 0; }
/* {
	int v2; // esi
	HWND v3; // eax
	LONG v4; // eax
	HWND result; // eax
	HWND v6; // edi
	HWND v7; // eax
	int v8; // [esp-288h] [ebp-28Ch]
	int v9; // [esp-188h] [ebp-18Ch]
	int v10; // [esp-108h] [ebp-10Ch]
	int v11; // [esp-88h] [ebp-8Ch]
	int v12; // [esp-8h] [ebp-Ch]
	char v13; // [esp-4h] [ebp-8h]
	int v14; // [esp+0h] [ebp-4h]

	v2 = (int)a1;
	if ( dword_100296D8 == 1 )
	{
		v14 = a2;
		v6 = a1;
		Connect_10004028((int)&v11, 128, (int)&v10, 128);
		v7 = GetFocus();
		v13 = GetWindowLongA(v7, -12) - 70;
		Connect_10003E0C((int)&v12, (const char *)&v11, (char *)&v10, (char *)&v9, 128);
		if ( UiAuthCallback(2, (int)&v11, (char *)&v10, 0, (char *)&v9, (LPSTR)&v8, 256) )
			result = CreaDung_10005037(v6);
		else
			result = (HWND)SelYesNo_1000FD39((int)v6, (const CHAR *)&v8, 0, 0);
	}
	else
	{
		v3 = GetFocus();
		v4 = GetWindowLongA(v3, -12);
		SelHero_1000B7AC((void *)(v4 - 1094));
		result = (HWND)CreaDung_10004F40(v2, 1);
	}
	return result;
} */
// 10004F5D: could not find valid save-restore pair for ebp
// 100296D8: using guessed type int dword_100296D8;

// ref: 0x10005037
HWND UNKCALL CreaDung_10005037(HWND arg) { return 0; }
/* {
	HWND v1; // eax
	HWND v2; // ebx
	HWND result; // eax
	int v4; // eax
	int v5; // edi
	char v6; // [esp+8h] [ebp-34Ch]
	CHAR v7; // [esp+108h] [ebp-24Ch]
	CHAR Buffer; // [esp+188h] [ebp-1CCh]
	char v9; // [esp+248h] [ebp-10Ch]
	char v10; // [esp+2C8h] [ebp-8Ch]
	char v11; // [esp+348h] [ebp-Ch]
	char v12; // [esp+34Ch] [ebp-8h]
	HWND v13; // [esp+350h] [ebp-4h]

	v13 = arg;
	v1 = GetFocus();
	v2 = v1;
	result = GetParent(v1);
	if ( v13 == result )
	{
		Connect_10004028((int)&v10, 128, (int)&v9, 128);
		v12 = GetWindowLongA(v2, -12) - 70;
		Connect_10003E0C((int)&v11, &v10, &v9, &v6, 256);
		v4 = dword_100296D0;
		if ( *(_DWORD *)(dword_100296D0 + 32) >= 8u )
		{
			v5 = *(_DWORD *)(dword_100296D0 + 28);
			*(_BYTE *)(v5 + 4) = GetWindowLongA(v2, -12) - 70;
			v4 = dword_100296D0;
		}
		if ( SNetCreateGame(
				 dword_100296DC,
				 0,
				 &v6,
				 0,
				 *(_DWORD *)(v4 + 28),
				 *(_DWORD *)(v4 + 32),
				 *(_DWORD *)(dword_100296BC + 8),
				 &v10,
				 0,
				 dword_100296C0) )
		{
			result = (HWND)CreaDung_10004F40((int)v13, 1);
		}
		else
		{
			dword_100296D4 = SErrGetLastError();
			if ( dword_100296D4 == 183 )
			{
				LoadStringA(hInstance, 0x49u, &v7, 127);
				wsprintfA(&Buffer, &v7, dword_100296DC);
			}
			else
			{
				LoadStringA(hInstance, 0x26u, &Buffer, 191);
			}
			result = (HWND)SelYesNo_1000FD39((int)v13, &Buffer, 0, 0);
		}
	}
	return result;
} */
// 10010406: using guessed type _DWORD __stdcall SErrGetLastError();
// 1001040C: using guessed type int __stdcall SNetCreateGame(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100296BC: using guessed type int dword_100296BC;
// 100296C0: using guessed type int dword_100296C0;
// 100296D0: using guessed type int dword_100296D0;
// 100296D4: using guessed type int dword_100296D4;
// 100296DC: using guessed type int dword_100296DC;

// ref: 0x1000517E
HWND USERPURGE CreaDung_1000517E(HWND hWnd, int a2, int a3, int a4) { return 0; }
/* {
	int v4; // ebx
	HWND v5; // esi
	int v6; // ST08_4
	HWND v7; // eax
	HWND result; // eax
	HWND v9; // eax

	v4 = a2;
	v5 = hWnd;
	v6 = a2;
	v7 = GetDlgItem(hWnd, 1056);
	if ( local_10007C3B(v5, v7, v6, a4) )
		return CreaDung_10004F5D(v5, a3);
	v9 = GetDlgItem(v5, 1054);
	result = (HWND)local_10007C3B(v5, v9, v4, a4);
	if ( result )
		result = (HWND)CreaDung_10004F40((int)v5, 2);
	return result;
} */

// ref: 0x100051D8
int __fastcall CreaDung_100051D8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) { return 0; }
/* {
	int v8; // eax
	int result; // eax

	dword_100296BC = a1;
	dword_100296C8 = a3;
	dword_100296C0 = a6;
	dword_100296CC = a7;
	dword_100296D0 = a2;
	dword_100296DC = a8;
	v8 = SelHero_1000B7CA();
	result = SDlgDialogBoxParam(hInstance, "SELDIFF_DIALOG", *(_DWORD *)(a4 + 8), CreaDung_10004C4A, v8);
	if ( result != 1 )
	{
		SErrSetLastError(dword_100296D4);
		result = 0;
	}
	return result;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1001041E: using guessed type int __stdcall SErrSetLastError(_DWORD);
// 100296BC: using guessed type int dword_100296BC;
// 100296C0: using guessed type int dword_100296C0;
// 100296C8: using guessed type int dword_100296C8;
// 100296CC: using guessed type int dword_100296CC;
// 100296D0: using guessed type int dword_100296D0;
// 100296D4: using guessed type int dword_100296D4;
// 100296DC: using guessed type int dword_100296DC;
