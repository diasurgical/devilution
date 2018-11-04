// ref: 0x1000D769
signed int SelList_1000D769() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A4C0 = 2139095040;
	return result;
} */
// 1002A4C0: using guessed type int dword_1002A4C0;

// ref: 0x1000D774
LRESULT __stdcall SelList_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v4; // eax
	char *v5; // eax
	int v6; // edx
	HWND v8; // eax
	HWND v9; // eax

	if ( Msg > 0x111 )
	{
		if ( Msg == 275 )
		{
			v9 = GetFocus();
			Focus_100075DC(hDlg, v9);
			return 0;
		}
		if ( Msg != 513 )
		{
			if ( Msg == 514 )
			{
				v8 = GetDlgItem(hDlg, 1105);
				if ( !Sbar_100099C0(v8) )
					return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
				goto LABEL_23;
			}
			if ( Msg != 515 )
				return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
		}
		SelList_1000E0CA(hDlg, (unsigned short)lParam, (unsigned int)lParam >> 16);
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	}
	switch ( Msg )
	{
		case 0x111u:
			if ( HIWORD(wParam) == 7 )
			{
				Focus_100075B7(hDlg, (HWND)lParam);
				return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
			}
			if ( HIWORD(wParam) != 6 )
			{
				v6 = 1;
				if ( wParam != 327681 )
				{
					v6 = 2;
					if ( (_WORD)wParam != 2 )
						return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
				}
LABEL_25:
				OkCancel_100092F5((int)hDlg, v6);
				return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
			}
			Focus_10007458((void *)lParam);
			Focus_100075DC(hDlg, (HWND)lParam);
			SelList_1000D964(hDlg, (unsigned short)wParam);
LABEL_23:
			SelList_1000D9CF(hDlg);
			return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
		case 2u:
			SelList_1000D916(hDlg);
			return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
		case 6u:
			if ( (_WORD)wParam == 1 || (_WORD)wParam == 2 )
				SelList_1000DA2D(hDlg);
			else
				SelList_1000DA48(hDlg);
			return 0;
		case 0x100u:
			if ( wParam != 46 )
				return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
			v5 = SelHero_1000B7B3();
			if ( !strlen(v5) )
				return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
			v6 = 1006;
			goto LABEL_25;
	}
	if ( Msg <= 0x103 )
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	if ( Msg <= 0x105 )
	{
		v4 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v4, Msg, wParam, lParam);
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	}
	if ( Msg != 272 )
		return SDlgDefDialogProc(hDlg, Msg, wParam, lParam);
	SelList_1000DA55(hDlg);
	return 0;
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x1000D916
HWND UNKCALL SelList_1000D916(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // eax

	v1 = hDlg;
	Sbar_10009CD2(hDlg, 1105);
	Doom_10006C53(v1, &dword_10023190);
	Doom_10006C53(v1, (int *)&unk_10023188);
	Doom_10006C53(v1, (int *)&unk_1002317C);
	Doom_10006C53(v1, (int *)&unk_10023174);
	v2 = GetParent(v1);
	return SelHero_1000BA7B(v2, 0);
} */
// 10023190: using guessed type int dword_10023190;

// ref: 0x1000D964
HWND __fastcall SelList_1000D964(HWND hDlg, int nIDDlgItem) { return 0; }
/* {
	HWND v2; // ebp
	HWND v3; // eax
	int v4; // eax
	HWND v5; // eax
	int v6; // eax
	HWND v7; // eax
	int v8; // eax
	HWND v9; // eax
	int v10; // eax
	HWND v11; // eax
	int v12; // eax
	HWND v13; // esi
	HWND result; // eax
	int v15; // edi
	HWND v16; // eax
	HWND v17; // eax

	v13 = hDlg;
	result = GetDlgItem(hDlg, nIDDlgItem);
	if ( result )
	{
		result = (HWND)GetWindowLongA(result, -21);
		if ( result )
		{
			v15 = *((_DWORD *)result + 3);
			if ( v15 )
			{
				if ( *(_WORD *)(v15 + 20) )
					Doom_1000680A(v13, (int *)&unk_10023188, 4, 0);
				else
					Doom_1000680A(v13, (int *)&unk_10023188, 5, 0);
				v16 = GetParent(v13);
				result = (HWND)SelHero_1000B905(v16, v15);
			}
			else
			{
				Doom_1000680A(v13, (int *)&unk_10023188, 5, 0);
				v17 = GetParent(v13);
				dword_1002A424 = 0;
				byte_1002A440 = 0;
				v2 = v17;
				v3 = GetDlgItem(v17, 1014);
				v4 = GetWindowLongA(v3, -21);
				local_10007FA4(v4, "--");
				v5 = GetDlgItem(v2, 1018);
				v6 = GetWindowLongA(v5, -21);
				local_10007FA4(v6, "--");
				v7 = GetDlgItem(v2, 1017);
				v8 = GetWindowLongA(v7, -21);
				local_10007FA4(v8, "--");
				v9 = GetDlgItem(v2, 1016);
				v10 = GetWindowLongA(v9, -21);
				local_10007FA4(v10, "--");
				v11 = GetDlgItem(v2, 1015);
				v12 = GetWindowLongA(v11, -21);
				local_10007FA4(v12, "--");
				SelHero_1000B899(v2, 3);
				result = (HWND)Doom_10006A13(v2, (int *)&unk_10023020, 1);
			}
		}
	}
	return result;
} */
// 1002A424: using guessed type int dword_1002A424;

// ref: 0x1000D9CF
HWND UNKCALL SelList_1000D9CF(HWND hDlg) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // eax
	int v3; // ST04_4
	int v4; // eax

	v1 = hDlg;
	v2 = GetFocus();
	v3 = SelList_1000D9F4(v2);
	v4 = SelHero_1000B7A6();
	return Sbar_10009A99(v1, 1105, v4, v3);
} */

// ref: 0x1000D9F4
int UNKCALL SelList_1000D9F4(HWND hWnd) { return 0; }
/* {
	LONG v1; // esi
	_DWORD *v2; // eax
	_DWORD *v3; // esi
	int v5; // ecx

	if ( !hWnd )
		return 0;
	v1 = GetWindowLongA(hWnd, -21);
	if ( !v1 )
		return 0;
	v2 = (_DWORD *)SelHero_1000B7A0();
	if ( !v2 )
		return 0;
	v3 = *(_DWORD **)(v1 + 12);
	if ( !v3 )
		return 0;
	v5 = 0;
	do
	{
		if ( v2 == v3 )
			break;
		v2 = (_DWORD *)*v2;
		++v5;
	}
	while ( v2 );
	return v5;
} */

// ref: 0x1000DA2D
int UNKCALL SelList_1000DA2D(void *arg) { return 0; }
/* {
	void *v1; // esi

	v1 = arg;
	Focus_10007719("ui_art\\focus16.pcx");
	return SDlgSetTimer(v1, 1, 55, 0);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000DA48
int UNKCALL SelList_1000DA48(void *arg) { return 0; }
/* {
	SDlgKillTimer(arg, 1);
	return Focus_100076C3();
} */
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);

// ref: 0x1000DA55
int UNKCALL SelList_1000DA55(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	HWND v2; // edi
	LONG v3; // eax
	int result; // eax
	HWND v5; // eax
	CHAR Buffer; // [esp+8h] [ebp-20h]

	v1 = hWnd;
	v2 = GetParent(hWnd);
	SelList_1000DBAC(v1);
	if ( SelHero_1000B7CA() == 1 )
		LoadStringA(hInstance, 0x1Cu, &Buffer, 31);
	else
		LoadStringA(hInstance, 0x1Du, &Buffer, 31);
	SelHero_1000BA7B(v2, &Buffer);
	v3 = GetWindowLongA(v2, -21);
	SetWindowLongA(v1, -21, v3);
	Doom_100068AB(v1, (int *)&unk_10023174, 5);
	Doom_1000658C(v1, (int *)&unk_1002317C, 4, 0);
	Doom_1000658C(v1, (int *)&unk_10023188, 4, 0);
	Doom_1000658C(v1, &dword_10023190, 2, 1);
	dword_1002A4C4 = SelHero_1000B7A0();
	SelList_1000DB2C(v1, (const char *)dword_1002A4C4);
	Sbar_10009BF1(v1, 1105);
	result = SelHero_1000B7A6();
	if ( result <= 6 )
	{
		v5 = GetDlgItem(v1, 1105);
		result = ShowWindow(v5, 0);
	}
	return result;
} */
// 10023190: using guessed type int dword_10023190;
// 1002A4C4: using guessed type int dword_1002A4C4;

// ref: 0x1000DB2C
int __fastcall SelList_1000DB2C(HWND a1, const char *a2) { return 0; }
/* {
	const char *v2; // edi
	int *v3; // ebp
	HWND v4; // eax
	HWND v5; // esi
	int v6; // esi
	HWND hDlg; // [esp+8h] [ebp-4h]

	v2 = a2;
	hDlg = a1;
	v3 = &dword_10023190;
	if ( dword_10023190 )
	{
		do
		{
			v4 = GetDlgItem(hDlg, *v3);
			v5 = v4;
			if ( v4 )
			{
				if ( v2 )
				{
					EnableWindow(v4, 1);
					v6 = GetWindowLongA(v5, -21);
					local_10007FA4(v6, v2 + 4);
					if ( v6 )
						*(_DWORD *)(v6 + 12) = v2;
					v2 = *(const char **)v2;
				}
				else
				{
					EnableWindow(v4, 0);
				}
			}
			++v3;
		}
		while ( *v3 );
	}
	return Doom_1000680A(hDlg, &dword_10023190, 2, 1);
} */
// 10023190: using guessed type int dword_10023190;

// ref: 0x1000DBAC
void UNKCALL SelList_1000DBAC(HWND hDlg) { return; }
/* {
	HWND v1; // ebx
	int *v2; // edi
	HWND v3; // eax
	HWND v4; // esi
	void *v5; // eax

	v1 = hDlg;
	v2 = &dword_10023190;
	if ( dword_10023190 )
	{
		do
		{
			v3 = GetDlgItem(v1, *v2);
			v4 = v3;
			if ( v3 )
			{
				v5 = (void *)GetWindowLongA(v3, -4);
				SetPropA(v4, "UIOLDPROC", v5);
				SetWindowLongA(v4, -4, (LONG)SelList_1000DBFE);
			}
			++v2;
		}
		while ( *v2 );
	}
} */
// 10023190: using guessed type int dword_10023190;

// ref: 0x1000DBFE
LRESULT __stdcall SelList_1000DBFE(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	LRESULT (__stdcall *v4)(HWND, UINT, WPARAM, LPARAM); // edi
	HWND v5; // eax
	UINT v7; // [esp-Ch] [ebp-18h]
	WPARAM v8; // [esp-8h] [ebp-14h]
	LPARAM v9; // [esp-4h] [ebp-10h]

	v4 = (LRESULT (__stdcall *)(HWND, UINT, WPARAM, LPARAM))GetPropA(hWnd, "UIOLDPROC");
	switch ( Msg )
	{
		case 2u:
			RemovePropA(hWnd, "UIOLDPROC");
			if ( !v4 )
				return DefWindowProcA(hWnd, Msg, wParam, lParam);
			SetWindowLongA(hWnd, -4, (LONG)v4);
			break;
		case 0xFu:
			local_10007C95(hWnd);
			return 0;
		case 0x87u:
			return 4;
		case 0x100u:
			if ( wParam > 0x21 )
			{
				if ( wParam == 34 )
				{
					SelList_1000DE18(hWnd);
					return 0;
				}
				if ( wParam > 0x24 )
				{
					if ( wParam <= 0x26 )
					{
						SelList_1000E043(hWnd);
						return 0;
					}
					if ( wParam <= 0x28 )
					{
						SelList_1000DFAB(hWnd);
						return 0;
					}
					if ( wParam == 46 )
					{
						v9 = lParam;
						v8 = 46;
						v7 = 256;
						goto LABEL_24;
					}
				}
			}
			else
			{
				switch ( wParam )
				{
					case 0x21u:
						SelList_1000DEF4(hWnd);
						break;
					case 9u:
						if ( GetKeyState(16) >= 0 )
							SelList_1000DD36(hWnd);
						else
							SelList_1000DDA7(hWnd);
						return 0;
					case 0xDu:
						goto LABEL_38;
					case 0x1Bu:
						v9 = 0;
						v8 = 2;
						goto LABEL_12;
					case 0x20u:
LABEL_38:
						v9 = 0;
						v8 = 1;
LABEL_12:
						v7 = 273;
LABEL_24:
						v5 = GetParent(hWnd);
						SendMessageA(v5, v7, v8, v9);
						return 0;
				}
			}
			return 0;
	}
	if ( v4 )
		return CallWindowProcA(v4, hWnd, Msg, wParam, lParam);
	return DefWindowProcA(hWnd, Msg, wParam, lParam);
} */

// ref: 0x1000DD36
HWND UNKCALL SelList_1000DD36(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	HWND v2; // ebx
	int nIDDlgItem[1044]; // [esp+0h] [ebp-1074h]
	int v5; // [esp+1050h] [ebp-24h]
	int v6; // [esp+105Ch] [ebp-18h]
	int v7; // [esp+1060h] [ebp-14h]
	int v8; // [esp+1064h] [ebp-10h]
	int v9; // [esp+1068h] [ebp-Ch]
	int v10; // [esp+106Ch] [ebp-8h]
	int v11; // [esp+1070h] [ebp-4h]

	v1 = hWnd;
	v6 = 1048;
	v7 = 1049;
	v8 = 1050;
	v9 = 1051;
	v10 = 1052;
	v11 = 1047;
	v2 = GetParent(hWnd);
	do
	{
		v5 = nIDDlgItem[GetWindowLongA(v1, -12)];
		v1 = GetDlgItem(v2, v5);
	}
	while ( !IsWindowEnabled(v1) );
	return SetFocus(v1);
} */
// 1000DD36: using guessed type int nIDDlgItem[1044];

// ref: 0x1000DDA7
HWND UNKCALL SelList_1000DDA7(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	HWND v2; // ebx
	int nIDDlgItem[1044]; // [esp+0h] [ebp-1074h]
	int v5; // [esp+1050h] [ebp-24h]
	int v6; // [esp+105Ch] [ebp-18h]
	int v7; // [esp+1060h] [ebp-14h]
	int v8; // [esp+1064h] [ebp-10h]
	int v9; // [esp+1068h] [ebp-Ch]
	int v10; // [esp+106Ch] [ebp-8h]
	int v11; // [esp+1070h] [ebp-4h]

	v1 = hWnd;
	v6 = 1052;
	v7 = 1047;
	v8 = 1048;
	v9 = 1049;
	v10 = 1050;
	v11 = 1051;
	v2 = GetParent(hWnd);
	do
	{
		v5 = nIDDlgItem[GetWindowLongA(v1, -12)];
		v1 = GetDlgItem(v2, v5);
	}
	while ( !IsWindowEnabled(v1) );
	return SetFocus(v1);
} */
// 1000DDA7: using guessed type int nIDDlgItem[1044];

// ref: 0x1000DE18
HWND UNKCALL SelList_1000DE18(HWND hWnd) { return 0; }
/* {
	HWND result; // eax
	HWND v2; // edi
	HWND v3; // ebp
	HWND v4; // eax
	_DWORD *v5; // eax
	char *v6; // esi
	const char *v7; // esi
	int v8; // eax
	HWND hWnda; // [esp+10h] [ebp-4h]

	hWnda = hWnd;
	result = GetParent(hWnd);
	v2 = result;
	if ( result )
	{
		result = GetDlgItem(result, 1047);
		v3 = result;
		if ( result )
		{
			v4 = GetDlgItem(v2, 1052);
			result = (HWND)GetWindowLongA(v4, -21);
			if ( result )
			{
				v5 = (_DWORD *)*((_DWORD *)result + 3);
				if ( v5 && *v5 )
				{
					v6 = (char *)(SelList_1000D9F4(v3) + 6);
					if ( (signed int)v6 > SelHero_1000B7A6() - 6 )
						v6 = (char *)(SelHero_1000B7A6() - 6);
					result = (HWND)SelList_1000DEDD(v6);
					v7 = (const char *)result;
					if ( result )
					{
						TitleSnd_10010315();
						SelList_1000DB2C(v2, v7);
						v8 = GetWindowLongA(hWnda, -12);
						SelList_1000D964(v2, v8);
						result = SelList_1000D9CF(v2);
					}
				}
				else
				{
					result = SelList_1000DDA7(v3);
				}
			}
		}
	}
	return result;
} */

// ref: 0x1000DEDD
_DWORD *UNKCALL SelList_1000DEDD(char *arg) { return 0; }
/* {
	char *v1; // esi
	_DWORD *result; // eax

	v1 = arg;
	result = (_DWORD *)SelHero_1000B7A0();
	while ( result && v1 )
	{
		result = (_DWORD *)*result;
		--v1;
	}
	return result;
} */

// ref: 0x1000DEF4
HWND UNKCALL SelList_1000DEF4(HWND hWnd) { return 0; }
/* {
	HWND result; // eax
	HWND v2; // esi
	HWND v3; // edi
	int v4; // ebp
	HWND v5; // eax
	char *v6; // eax
	const char *v7; // edi
	int v8; // eax
	HWND hWnda; // [esp+10h] [ebp-4h]

	hWnda = hWnd;
	result = GetParent(hWnd);
	v2 = result;
	if ( result )
	{
		result = GetDlgItem(result, 1047);
		v3 = result;
		if ( result )
		{
			result = (HWND)GetWindowLongA(result, -21);
			if ( result )
			{
				v4 = *((_DWORD *)result + 3);
				if ( v4 )
				{
					if ( v4 == SelHero_1000B7A0() )
					{
						v5 = GetDlgItem(v2, 1052);
						result = SelList_1000DD36(v5);
					}
					else
					{
						v6 = (char *)(SelList_1000D9F4(v3) - 6);
						if ( (signed int)v6 < 0 )
							v6 = 0;
						result = (HWND)SelList_1000DEDD(v6);
						v7 = (const char *)result;
						if ( result )
						{
							TitleSnd_10010315();
							SelList_1000DB2C(v2, v7);
							v8 = GetWindowLongA(hWnda, -12);
							SelList_1000D964(v2, v8);
							result = SelList_1000D9CF(v2);
						}
					}
				}
			}
		}
	}
	return result;
} */

// ref: 0x1000DFAB
HWND UNKCALL SelList_1000DFAB(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	HWND result; // eax
	HWND v3; // eax
	const char *v4; // ebp
	HWND v5; // eax
	int v6; // ebx
	HWND v7; // eax
	HWND v8; // eax

	v1 = hWnd;
	result = (HWND)GetWindowLongA(hWnd, -21);
	if ( result )
	{
		result = (HWND)*((_DWORD *)result + 3);
		if ( result )
		{
			if ( *(_DWORD *)result )
			{
				if ( GetWindowLongA(v1, -12) >= 1052 )
				{
					v3 = GetParent(v1);
					result = GetDlgItem(v3, 1048);
					if ( result )
					{
						result = (HWND)GetWindowLongA(result, -21);
						if ( result )
						{
							v4 = (const char *)*((_DWORD *)result + 3);
							if ( v4 )
							{
								TitleSnd_10010315();
								v5 = GetParent(v1);
								SelList_1000DB2C(v5, v4);
								v6 = GetWindowLongA(v1, -12);
								v7 = GetParent(v1);
								SelList_1000D964(v7, v6);
								v8 = GetParent(v1);
								result = SelList_1000D9CF(v8);
							}
						}
					}
				}
				else
				{
					result = SelList_1000DD36(v1);
				}
			}
		}
	}
	return result;
} */

// ref: 0x1000E043
HWND UNKCALL SelList_1000E043(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	HWND result; // eax
	HWND v3; // esi
	const char *v4; // ebx
	HWND v5; // eax
	int v6; // ebx
	HWND v7; // eax
	HWND v8; // eax

	v1 = hWnd;
	if ( GetWindowLongA(hWnd, -12) > 1047 )
		return SelList_1000DDA7(v1);
	result = (HWND)GetWindowLongA(v1, -21);
	if ( result )
	{
		v3 = (HWND)*((_DWORD *)result + 3);
		if ( v3 )
		{
			result = (HWND)SelHero_1000B7A0();
			v4 = (const char *)result;
			if ( v3 != result )
			{
				while ( v4 && *(HWND *)v4 != v3 )
					v4 = *(const char **)v4;
				TitleSnd_10010315();
				v5 = GetParent(v1);
				SelList_1000DB2C(v5, v4);
				v6 = GetWindowLongA(v1, -12);
				v7 = GetParent(v1);
				SelList_1000D964(v7, v6);
				v8 = GetParent(v1);
				result = SelList_1000D9CF(v8);
			}
		}
	}
	return result;
} */

// ref: 0x1000E0CA
int __fastcall SelList_1000E0CA(HWND hWnd, int a2, int a3) { return 0; }
/* {
	int v3; // ebx
	HWND v4; // esi
	int v5; // ST08_4
	HWND v6; // eax
	int v7; // edx
	int result; // eax
	HWND v9; // eax
	HWND v10; // eax
	char *v11; // eax
	HWND v12; // eax
	HWND v13; // eax
	int v14; // eax
	int v15; // eax
	int v16; // eax
	HWND v17; // eax
	HWND v18; // eax
	HWND v19; // eax
	HWND v20; // eax

	v3 = a2;
	v4 = hWnd;
	v5 = a2;
	v6 = GetDlgItem(hWnd, 1056);
	if ( local_10007C3B(v4, v6, v5, a3) )
	{
		v7 = 1;
		return OkCancel_100092F5((int)v4, v7);
	}
	v9 = GetDlgItem(v4, 1054);
	if ( local_10007C3B(v4, v9, v3, a3) )
	{
		v7 = 2;
		return OkCancel_100092F5((int)v4, v7);
	}
	v10 = GetDlgItem(v4, 1006);
	if ( local_10007C3B(v4, v10, v3, a3) )
	{
		v11 = SelHero_1000B7B3();
		result = strlen(v11);
		if ( result )
		{
			v7 = 1006;
			return OkCancel_100092F5((int)v4, v7);
		}
	}
	else
	{
		v12 = GetDlgItem(v4, 1105);
		result = local_10007C3B(v4, v12, v3, a3);
		if ( result )
		{
			v13 = GetDlgItem(v4, 1105);
			v14 = Sbar_100099DC(v13, v3, a3) - 1;
			if ( v14 )
			{
				v15 = v14 - 1;
				if ( v15 )
				{
					v16 = v15 - 1;
					if ( v16 )
					{
						result = v16 - 1;
						if ( !result )
						{
							v17 = GetFocus();
							result = (int)SelList_1000DE18(v17);
						}
					}
					else
					{
						v18 = GetFocus();
						result = (int)SelList_1000DEF4(v18);
					}
				}
				else
				{
					v19 = GetFocus();
					result = (int)SelList_1000DFAB(v19);
				}
			}
			else
			{
				v20 = GetFocus();
				result = (int)SelList_1000E043(v20);
			}
		}
	}
	return result;
} */
