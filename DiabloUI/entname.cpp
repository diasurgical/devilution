// ref: 0x10006F7C
LRESULT __stdcall EntName_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	int v4; // edx
	HWND v5; // eax
	HWND v6; // eax
	HWND v7; // eax
	HWND v9; // eax

	v4 = 2;
	if ( Msg == 2 )
	{
		EntName_1000709E(hDlg);
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	}
	if ( Msg <= 0x103 )
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	if ( Msg <= 0x105 )
	{
		v9 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v9, Msg, wParam, lParam);
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	}
	switch ( Msg )
	{
		case 0x110u:
			dword_10029864 = (LPSTR)lParam;
			EntName_100070DB(hDlg);
			return 0;
		case 0x111u:
			if ( (unsigned short)wParam != 1 )
			{
				if ( (unsigned short)wParam != 2 )
				{
					if ( (unsigned short)wParam == 1065 )
						EntName_100071ED(hDlg, wParam, lParam);
					return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
				}
				goto LABEL_11;
			}
			goto LABEL_18;
		case 0x113u:
			v7 = GetFocus();
			Focus_100075DC(hDlg, v7);
			return 0;
	}
	if ( Msg != 513 )
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	v5 = GetDlgItem(hDlg, 1056);
	if ( local_10007C3B(hDlg, v5, (unsigned short)lParam, (unsigned int)lParam >> 16) )
	{
LABEL_18:
		v4 = 1;
		goto LABEL_11;
	}
	v6 = GetDlgItem(hDlg, 1054);
	if ( local_10007C3B(hDlg, v6, (unsigned short)lParam, (unsigned int)lParam >> 16) )
	{
		v4 = 2;
LABEL_11:
		EntName_100071AC(hDlg, v4);
	}
	return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x1000709E
HWND UNKCALL EntName_1000709E(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // eax

	v1 = hDlg;
	Focus_100076C3();
	Doom_10006C53(v1, (int *)&unk_10022B48);
	Doom_10006C53(v1, (int *)&unk_10022B3C);
	Doom_10006C53(v1, (int *)&unk_10022B34);
	v2 = GetParent(v1);
	return SelHero_1000BA7B(v2, 0);
} */

// ref: 0x100070DB
int UNKCALL EntName_100070DB(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // edi
	LONG v3; // eax
	HWND v4; // ebx
	int result; // eax
	CHAR Buffer; // [esp+Ch] [ebp-20h]

	v1 = hWnd;
	v2 = GetParent(hWnd);
	if ( SelHero_1000B7CA() == 1 )
		LoadStringA(hInstance, 0x20u, &Buffer, 31);
	else
		LoadStringA(hInstance, 0x1Fu, &Buffer, 31);
	SelHero_1000BA7B(v2, &Buffer);
	v3 = GetWindowLongA(v2, -21);
	SetWindowLongA(v1, -21, v3);
	Doom_100068AB(v1, (int *)&unk_10022B34, 5);
	Doom_1000658C(v1, (int *)&unk_10022B3C, 4, 0);
	Doom_10006AB8(v1, (int *)&unk_10022B48, 2);
	Focus_10007719("ui_art\\focus.pcx");
	SDlgSetTimer(v1, 1, 55, 0);
	v4 = GetDlgItem(v1, 1065);
	SendMessageA(v4, 0x401u, 0xFu, 0);
	result = SelHero_1000B7CA();
	if ( result == 1 )
		result = SendMessageA(v4, 0x404u, 0, (LPARAM)" ,<>%&\\\"?*#/");
	return result;
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x100071AC
int __fastcall EntName_100071AC(HWND hDlg, int a2) { return 0; }
/* {
	int v2; // edi
	HWND v3; // esi
	CHAR *v4; // ST08_4
	HWND v5; // eax

	v2 = a2;
	v3 = hDlg;
	TitleSnd_1001031F();
	SDlgKillTimer(v3, 1);
	v4 = dword_10029864;
	v5 = GetDlgItem(v3, 1065);
	GetWindowTextA(v5, v4, 16);
	dword_10029864[15] = 0;
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);

// ref: 0x100071ED
void __fastcall EntName_100071ED(HWND hWnd, unsigned int a2, int a3) { return; }
/* {
	int v3; // edx
	HWND v4; // esi
	HWND v5; // eax

	v3 = (a2 >> 16) - 1;
	v4 = hWnd;
	if ( v3 )
	{
		if ( v3 == 2 )
			Doom_10006C08(hWnd, (int *)&unk_10022B48, 2);
	}
	else
	{
		v5 = GetFocus();
		Focus_100075DC(v4, v5);
	}
} */

// ref: 0x10007220
signed int EntName_10007220() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029860 = 2139095040;
	return result;
} */
// 10029860: using guessed type int dword_10029860;
