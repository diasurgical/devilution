// ref: 0x10008164
signed int MainMenu_10008164() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A0D4 = 2139095040;
	return result;
} */
// 1002A0D4: using guessed type int dword_1002A0D4;

// ref: 0x1000816F
int __stdcall UiMainMenuDialog(char *name, int *a2, void *fnSound, int a4) { return 0; }
/* {
	int v4; // eax
	int v5; // esi

	dword_1002A118 = a4;
	TitleSnd_10010306((void *)a3);
	artfont_10001159();
	byte_1002A0D8 = 0;
	if ( a1 )
		strncpy((char *)&byte_1002A0D8, a1, 0x40u);
	v4 = SDrawGetFrameWindow();
	v5 = SDlgDialogBoxParam(hInstance, "MAINMENU_DIALOG", v4, MainMenu_100081E3, 0);
	if ( v5 == 5 )
		artfont_100010C8();
	if ( a2 )
		*(_DWORD *)a2 = v5;
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 1002A118: using guessed type int dword_1002A118;

// ref: 0x100081E3
int __stdcall MainMenu_100081E3(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v5; // eax
	int v6; // [esp+0h] [ebp-Ch]

	if ( Msg <= 0x113 )
	{
		if ( Msg != 275 )
		{
			if ( Msg == 2 )
			{
				MainMenu_10008354(hWnd);
			}
			else if ( Msg > 0x103 )
			{
				if ( Msg <= 0x105 )
				{
					v5 = (HWND)SDrawGetFrameWindow();
					SendMessageA(v5, Msg, wParam, lParam);
				}
				else
				{
					if ( Msg == 272 )
					{
						MainMenu_100083A8(hWnd);
						PostMessageA(hWnd, 0x7E8u, 0, 0);
						return 1;
					}
					if ( Msg == 273 )
					{
						MainMenu_10008391(hWnd);
						switch ( HIWORD(wParam) )
						{
							case 7:
								Focus_100075B7(hWnd, (HWND)lParam);
								break;
							case 6:
								Focus_10007458((void *)lParam);
								Focus_100075DC(hWnd, (HWND)lParam);
								break;
							case 0:
								MainMenu_100084FA(hWnd, (unsigned short)wParam);
								break;
						}
					}
				}
			}
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		if ( wParam == 3 && !DiabloUI_10005C2A() )
		{
			if ( dword_10029728 )
				MainMenu_1000845A((int)hWnd, 6, 0);
			else
				MainMenu_10008391(hWnd);
		}
		return 0;
	}
	if ( Msg >= 0x200 )
	{
		if ( Msg <= 0x202 )
			goto LABEL_34;
		if ( Msg <= 0x203 )
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		if ( Msg <= 0x205 )
		{
LABEL_34:
			MainMenu_10008391(hWnd);
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		if ( Msg == 2024 )
		{
			if ( !Fade_1000739F() )
				Fade_100073FD(hWnd, v6);
			return 0;
		}
	}
	return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 10029728: using guessed type int dword_10029728;

// ref: 0x10008354
int UNKCALL MainMenu_10008354(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	_DWORD *v2; // eax

	v1 = hDlg;
	Title_100100E7(hDlg);
	Focus_10007818(v1);
	Doom_10006C53(v1, (int *)&unk_10022BE8);
	Doom_10006C53(v1, (int *)&unk_10022BE0);
	v2 = (_DWORD *)GetWindowLongA(v1, -21);
	local_10007F72(v2);
	return local_1000811B();
} */

// ref: 0x10008391
int UNKCALL MainMenu_10008391(void *arg) { return 0; }
/* {
	return SDlgSetTimer(arg, 3, 1000 * dword_1002A118, 0);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);
// 1002A118: using guessed type int dword_1002A118;

// ref: 0x100083A8
int UNKCALL MainMenu_100083A8(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	int v2; // eax
	int *v3; // edi
	bool v4; // zf
	const char *v5; // eax
	HWND v6; // eax
	HWND v7; // ST1C_4
	HWND v9; // [esp+0h] [ebp-8h]

	v1 = hWnd;
	v2 = local_10007F46();
	v3 = (int *)v2;
	if ( v2 )
	{
		SetWindowLongA(v1, -21, v2);
		v4 = DiabloUI_10005C2A() == 0;
		v5 = "ui_art\\swmmenu.pcx";
		if ( v4 )
			v5 = "ui_art\\mainmenu.pcx";
		local_10007944((int)v1, 0, &byte_10029448, -1, 1, (int)v5, v3, v3 + 1, 0);
		Fade_100073C5(v1, 1);
	}
	v6 = GetDlgItem(v1, 1042);
	SetWindowTextA(v6, &byte_1002A0D8);
	Doom_100068AB(v1, (int *)&unk_10022BE0, 1);
	Doom_1000658C(v1, (int *)&unk_10022BE8, 6, 1);
	Focus_100077E9((int)v1, "ui_art\\focus42.pcx", v9);
	Title_1001009E(v1, (int)"ui_art\\smlogo.pcx", v7);
	MainMenu_10008391(v1);
	return local_10007DE9(v1, (int *)&unk_10022BE8);
} */

// ref: 0x1000845A
int __fastcall MainMenu_1000845A(int a1, int a2, int a3) { return 0; }
/* {
	int v3; // esi
	int v4; // edi

	v3 = a1;
	v4 = a2;
	SDlgKillTimer(a1, 3);
	if ( DiabloUI_10005C2A() && v4 == 3 )
	{
		SelYesNo_1000FD77(v3, 0x46u, 1);
		return SDlgSetTimer(v3, 3, 1000 * dword_1002A118, 0);
	}
	if ( v4 == 2 && !MainMenu_100084D5() )
	{
		SelYesNo_1000FD77(v3, 0x4Eu, 1);
		return SDlgSetTimer(v3, 3, 1000 * dword_1002A118, 0);
	}
	Fade_100073B4();
	if ( a3 )
		TitleSnd_1001031F();
	Fade_100072BE(10);
	return SDlgEndDialog(v3, v4);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);
// 1002A118: using guessed type int dword_1002A118;

// ref: 0x100084D5
BOOL MainMenu_100084D5() { return 0; }
/* {
	struct _MEMORYSTATUS Buffer; // [esp+0h] [ebp-20h]

	Buffer.dwLength = 32;
	GlobalMemoryStatus(&Buffer);
	return Buffer.dwTotalPhys > 0xDAC000;
} */

// ref: 0x100084FA
LRESULT __fastcall MainMenu_100084FA(HWND hWnd, int a2) { return 0; }
/* {
	HWND v2; // esi
	LRESULT result; // eax
	HWND v4; // eax
	LONG v5; // eax
	int v6; // [esp-8h] [ebp-Ch]

	v2 = hWnd;
	switch ( a2 )
	{
		case 1:
			v4 = GetFocus();
			v5 = GetWindowLongA(v4, -12);
			return SendMessageA(v2, 0x111u, v5, 0);
		case 2:
			v6 = 5;
			return MainMenu_1000845A((int)hWnd, v6, 1);
		case 1001:
			v6 = 2;
			return MainMenu_1000845A((int)hWnd, v6, 1);
		case 1002:
			v6 = 3;
			return MainMenu_1000845A((int)hWnd, v6, 1);
		case 1003:
			v6 = 4;
			return MainMenu_1000845A((int)hWnd, v6, 1);
	}
	result = a2 - 1044;
	if ( a2 == 1044 )
		result = MainMenu_1000845A((int)hWnd, 1, 1);
	return result;
} */
