// ref: 0x10009D66
LRESULT __stdcall SelClass_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v4; // eax
	LONG v5; // edx
	HWND v6; // eax
	HWND v7; // eax
	HWND v9; // eax

	if ( Msg == 2 )
	{
		SelClass_10009EC0(hDlg);
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
	if ( Msg == 272 )
	{
		SelClass_10009EFD(hDlg);
		return 0;
	}
	if ( Msg != 273 )
	{
		if ( Msg != 275 )
		{
			if ( Msg == 513 )
			{
				v4 = GetDlgItem(hDlg, 1056);
				if ( local_10007C3B(hDlg, v4, (unsigned short)lParam, (unsigned int)lParam >> 16) )
				{
					v5 = 1;
LABEL_19:
					SelClass_1000A00D((int)hDlg, v5);
					return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
				}
				v6 = GetDlgItem(hDlg, 1054);
				if ( local_10007C3B(hDlg, v6, (unsigned short)lParam, (unsigned int)lParam >> 16) )
				{
LABEL_21:
					v5 = 2;
					goto LABEL_19;
				}
			}
			return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
		}
		v7 = GetFocus();
		Focus_100075DC(hDlg, v7);
		return 0;
	}
	if ( HIWORD(wParam) == 7 )
	{
		Focus_100075B7(hDlg, (HWND)lParam);
	}
	else
	{
		if ( HIWORD(wParam) != 6 )
		{
			v5 = 1;
			if ( wParam == 327681 )
				goto LABEL_19;
			if ( (_WORD)wParam != 2 )
				return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
			goto LABEL_21;
		}
		Focus_10007458((void *)lParam);
		Focus_100075DC(hDlg, (HWND)lParam);
		SelClass_10009FA2(hDlg, (unsigned short)wParam);
	}
	return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x10009EC0
HWND UNKCALL SelClass_10009EC0(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // eax

	v1 = hDlg;
	Focus_100076C3();
	Doom_10006C53(v1, (int *)&unk_10022EC8);
	Doom_10006C53(v1, (int *)&unk_10022EBC);
	Doom_10006C53(v1, (int *)&unk_10022EB4);
	v2 = GetParent(v1);
	return SelHero_1000BA7B(v2, 0);
} */

// ref: 0x10009EFD
int UNKCALL SelClass_10009EFD(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	HWND v2; // esi
	LONG v3; // eax
	CHAR Buffer; // [esp+8h] [ebp-20h]

	v1 = hWnd;
	v2 = GetParent(hWnd);
	if ( SelHero_1000B7CA() == 1 )
		LoadStringA(hInstance, 0x20u, &Buffer, 31);
	else
		LoadStringA(hInstance, 0x1Fu, &Buffer, 31);
	SelHero_1000BA7B(v2, &Buffer);
	v3 = GetWindowLongA(v2, -21);
	SetWindowLongA(v1, -21, v3);
	local_10007CB5(v1, (int *)&unk_10022EC8);
	Doom_100068AB(v1, (int *)&unk_10022EB4, 5);
	Doom_1000658C(v1, (int *)&unk_10022EBC, 4, 0);
	Doom_1000658C(v1, (int *)&unk_10022EC8, 2, 1);
	Focus_10007719("ui_art\\focus.pcx");
	return SDlgSetTimer(v1, 1, 55, 0);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10009FA2
int __fastcall SelClass_10009FA2(HWND hWnd, int a2) { return 0; }
/* {
	char v2; // bl
	HWND v3; // esi
	HWND v4; // eax
	char v6; // [esp+8h] [ebp-34h]
	short v7; // [esp+1Ch] [ebp-20h]
	char v8; // [esp+1Eh] [ebp-1Eh]
	short v9; // [esp+20h] [ebp-1Ch]
	short v10; // [esp+22h] [ebp-1Ah]
	short v11; // [esp+24h] [ebp-18h]
	short v12; // [esp+26h] [ebp-16h]
	short v13; // [esp+34h] [ebp-8h]
	short v14; // [esp+36h] [ebp-6h]
	short v15; // [esp+38h] [ebp-4h]
	short v16; // [esp+3Ah] [ebp-2h]

	v2 = a2;
	v3 = hWnd;
	SelHero_1000B7D0(a2 - 1062, (int)&v13);
	memset(&v6, 0, 0x2Cu);
	v9 = v13;
	v10 = v14;
	v11 = v15;
	v7 = 1;
	v8 = v2 - 38;
	v12 = v16;
	v4 = GetParent(v3);
	return SelHero_1000B905(v4, (int)&v6);
} */

// ref: 0x1000A00D
int __fastcall SelClass_1000A00D(int a1, LONG a2) { return 0; }
/* {
	LONG v2; // esi
	int v3; // ebp
	HWND v4; // eax
	HWND v6; // eax

	v2 = a2;
	v3 = a1;
	if ( DiabloUI_10005C2A() )
	{
		if ( v2 == 1 )
		{
			v4 = GetFocus();
			if ( GetWindowLongA(v4, -12) != 1062 )
				return SelYesNo_1000FD77(v3, 0x45u, 0);
		}
	}
	TitleSnd_1001031F();
	SDlgKillTimer(v3, 1);
	if ( v2 == 1 )
	{
		v6 = GetFocus();
		v2 = GetWindowLongA(v6, -12);
	}
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);

// ref: 0x1000A077
signed int SelClass_1000A077() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A348 = 2139095040;
	return result;
} */
// 1002A348: using guessed type int dword_1002A348;
