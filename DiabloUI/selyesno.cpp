// ref: 0x1000FA49
int __fastcall SelYesNo_1000FA49(int a1, const CHAR *a2, int a3, int a4) { return 0; }
/* {
	dword_1002A4F8 = a2;
	dword_1002A504 = a3;
	dword_1002A500 = a4;
	dword_1002A50C = 0;
	dword_1002A508 = 0;
	return SDlgDialogBoxParam(hInstance, "SELYESNO_DIALOG", a1, SelYesNo_1000FA87, 0);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A500: using guessed type int dword_1002A500;
// 1002A504: using guessed type int dword_1002A504;
// 1002A508: using guessed type int (*dword_1002A508)(void);
// 1002A50C: using guessed type int dword_1002A50C;

// ref: 0x1000FA87
int __stdcall SelYesNo_1000FA87(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v4; // eax
	HWND v5; // eax
	LONG v7; // edx
	HWND v8; // eax
	LONG v9; // eax
	HWND v10; // ecx
	HWND v11; // eax

	if ( Msg == 2 )
	{
		SelYesNo_1000FBC7(hDlg);
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	}
	if ( Msg > 0x103 )
	{
		if ( Msg <= 0x105 )
		{
			v11 = (HWND)SDrawGetFrameWindow();
			SendMessageA(v11, Msg, wParam, lParam);
			return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
		}
		switch ( Msg )
		{
			case 0x110u:
				SelYesNo_1000FC1C(hDlg);
				return 0;
			case 0x111u:
				if ( HIWORD(wParam) == 7 )
				{
					Focus_100075B7(hDlg, (HWND)lParam);
				}
				else if ( HIWORD(wParam) == 6 )
				{
					Focus_10007458((void *)lParam);
					Focus_100075DC(hDlg, (HWND)lParam);
				}
				else
				{
					v7 = 1;
					if ( (_WORD)wParam == 1 )
					{
						v8 = GetFocus();
						v9 = GetWindowLongA(v8, -12);
						v10 = hDlg;
						if ( v9 == 1109 )
							v7 = 1;
						else
							v7 = 2;
					}
					else
					{
						if ( (_WORD)wParam == 2 )
						{
							v7 = 2;
						}
						else if ( (_WORD)wParam != 1109 )
						{
							return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
						}
						v10 = hDlg;
					}
					SelYesNo_1000FCF6((int)v10, v7);
				}
				break;
			case 0x113u:
				v4 = GetFocus();
				if ( !Focus_100075DC(hDlg, v4) )
				{
					v5 = GetDlgItem(hDlg, 1109);
					if ( !v5 )
						v5 = GetDlgItem(hDlg, 2);
					SetFocus(v5);
				}
				return 0;
		}
	}
	return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x1000FBC7
HWND UNKCALL SelYesNo_1000FBC7(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	_DWORD *v2; // eax
	HWND result; // eax
	HWND v4; // eax

	v1 = hDlg;
	v2 = (_DWORD *)GetWindowLongA(hDlg, -21);
	local_10007F72(v2);
	if ( dword_1002A500 )
		Focus_100076C3();
	Doom_10006C53(v1, (int *)&unk_100232DC);
	result = (HWND)Doom_10006C53(v1, (int *)&unk_100232D4);
	if ( dword_1002A504 )
	{
		v4 = GetParent(v1);
		result = SelHero_1000BA7B(v4, 0);
	}
	return result;
} */
// 1002A500: using guessed type int dword_1002A500;
// 1002A504: using guessed type int dword_1002A504;

// ref: 0x1000FC1C
void UNKCALL SelYesNo_1000FC1C(HWND hWnd) { return; }
/* {
	HWND v1; // esi
	HWND v2; // eax
	int v3; // eax
	int *v4; // edi
	const char *v5; // eax
	const CHAR *v6; // ST18_4
	HWND v7; // eax

	v1 = hWnd;
	v2 = GetParent(hWnd);
	if ( dword_1002A504 )
		SelHero_1000BA7B(v2, (const char *)dword_1002A504);
	v3 = local_10007F46();
	v4 = (int *)v3;
	if ( v3 )
	{
		SetWindowLongA(v1, -21, v3);
		if ( dword_1002A50C )
		{
			if ( DiabloUI_10005C2A() )
				v5 = "ui_art\\swmmpop.pcx";
			else
				v5 = "ui_art\\mmpopup.pcx";
		}
		else
		{
			v5 = "ui_art\\black.pcx";
		}
		local_10007944((int)v1, 0, "Popup", -1, 1, (int)v5, v4, v4 + 1, 1);
	}
	v6 = dword_1002A4F8;
	v7 = GetDlgItem(v1, 1026);
	SetWindowTextA(v7, v6);
	Doom_100068AB(v1, (int *)&unk_100232D4, 3);
	Doom_1000658C(v1, (int *)&unk_100232DC, 4, 1);
	if ( dword_1002A500 )
		Focus_10007719("ui_art\\focus.pcx");
	else
		Focus_100076FA();
	SDlgSetTimer(v1, 1, 55, 0);
	return local_10007DE9(v1, (int *)&unk_100232DC);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);
// 1002A500: using guessed type int dword_1002A500;
// 1002A504: using guessed type int dword_1002A504;
// 1002A50C: using guessed type int dword_1002A50C;

// ref: 0x1000FCF6
int __fastcall SelYesNo_1000FCF6(int a1, LONG a2) { return 0; }
/* {
	LONG v2; // esi
	int v3; // edi
	HWND v4; // eax

	v2 = a2;
	v3 = a1;
	TitleSnd_1001031F();
	SDlgKillTimer(v3, 1);
	if ( v2 == 2 )
	{
		if ( !dword_1002A508 )
			return SDlgEndDialog(v3, v2);
		dword_1002A508();
	}
	if ( v2 == 1 )
	{
		v4 = GetFocus();
		v2 = GetWindowLongA(v4, -12);
	}
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);
// 1002A508: using guessed type int (*dword_1002A508)(void);

// ref: 0x1000FD39
int __fastcall SelYesNo_1000FD39(int a1, const CHAR *a2, int a3, int a4) { return 0; }
/* {
	dword_1002A4F8 = a2;
	dword_1002A504 = a3;
	dword_1002A500 = a4;
	dword_1002A50C = 0;
	dword_1002A508 = 0;
	return SDlgDialogBoxParam(hInstance, "SELOK_DIALOG", a1, SelYesNo_1000FA87, 0);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A500: using guessed type int dword_1002A500;
// 1002A504: using guessed type int dword_1002A504;
// 1002A508: using guessed type int (*dword_1002A508)(void);
// 1002A50C: using guessed type int dword_1002A50C;

// ref: 0x1000FD77
int __fastcall SelYesNo_1000FD77(int a1, UINT a2, int a3) { return 0; }
/* {
	int v3; // esi
	CHAR Buffer; // [esp+4h] [ebp-100h]

	v3 = a1;
	LoadStringA(hInstance, a2, &Buffer, 255);
	dword_1002A50C = a3;
	dword_1002A500 = 0;
	dword_1002A504 = 0;
	dword_1002A4F8 = &Buffer;
	dword_1002A508 = 0;
	return SDlgDialogBoxParam(hInstance, "SPAWNERR_DIALOG", v3, SelYesNo_1000FA87, 0);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A500: using guessed type int dword_1002A500;
// 1002A504: using guessed type int dword_1002A504;
// 1002A508: using guessed type int (*dword_1002A508)(void);
// 1002A50C: using guessed type int dword_1002A50C;

// ref: 0x1000FDE3
signed int SelYesNo_1000FDE3() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A4FC = 2139095040;
	return result;
} */
// 1002A4FC: using guessed type int dword_1002A4FC;
