// ref: 0x1000E1C2
LRESULT __stdcall SelLoad_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v4; // eax
	LONG v5; // edx
	HWND v6; // eax
	HWND v7; // eax
	HWND v9; // eax

	if ( Msg == 2 )
	{
		SelLoad_1000E30E(hDlg);
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
		SelLoad_1000E34B(hDlg);
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
					SelLoad_1000E3E2((int)hDlg, v5);
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
	}
	return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x1000E30E
HWND UNKCALL SelLoad_1000E30E(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // eax

	v1 = hDlg;
	Focus_100076C3();
	Doom_10006C53(v1, (int *)&unk_100231C0);
	Doom_10006C53(v1, (int *)&unk_100231B4);
	Doom_10006C53(v1, (int *)&unk_100231AC);
	v2 = GetParent(v1);
	return SelHero_1000BA7B(v2, 0);
} */

// ref: 0x1000E34B
int UNKCALL SelLoad_1000E34B(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // edi
	LONG v3; // eax
	CHAR Buffer; // [esp+8h] [ebp-20h]

	v1 = hWnd;
	v2 = GetParent(hWnd);
	LoadStringA(hInstance, 0x1Du, &Buffer, 31);
	SelHero_1000BA7B(v2, &Buffer);
	v3 = GetWindowLongA(v2, -21);
	SetWindowLongA(v1, -21, v3);
	local_10007CB5(v1, (int *)&unk_100231C0);
	Doom_100068AB(v1, (int *)&unk_100231AC, 5);
	Doom_1000658C(v1, (int *)&unk_100231B4, 4, 0);
	Doom_1000658C(v1, (int *)&unk_100231C0, 2, 1);
	Focus_10007719("ui_art\\focus16.pcx");
	return SDlgSetTimer(v1, 1, 55, 0);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000E3E2
int __fastcall SelLoad_1000E3E2(int a1, LONG a2) { return 0; }
/* {
	LONG v2; // esi
	int v3; // edi
	HWND v4; // eax

	v2 = a2;
	v3 = a1;
	TitleSnd_1001031F();
	SDlgKillTimer(v3, 1);
	if ( v2 == 1 )
	{
		v4 = GetFocus();
		v2 = GetWindowLongA(v4, -12);
	}
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);

// ref: 0x1000E41A
signed int SelLoad_1000E41A() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A4C8 = 2139095040;
	return result;
} */
// 1002A4C8: using guessed type int dword_1002A4C8;
