// ref: 0x1000B7A0
int SelHero_1000B7A0() { return 0; }
/* {
	return dword_1002A458;
} */
// 1002A458: using guessed type int dword_1002A458;

// ref: 0x1000B7A6
int SelHero_1000B7A6() { return 0; }
/* {
	return dword_1002A428;
} */
// 1002A428: using guessed type int dword_1002A428;

// ref: 0x1000B7AC
void UNKCALL SelHero_1000B7AC(void *arg) { return; }
/* {
	dword_1002A420 = (int)arg;
} */
// 1002A420: using guessed type int dword_1002A420;

// ref: 0x1000B7B3
char *SelHero_1000B7B3() { return 0; }
/* {
	return &byte_1002A440;
} */

// ref: 0x1000B7B9
int SelHero_1000B7B9() { return 0; }
/* {
	return SMemAlloc(44, "C:\\Src\\Diablo\\DiabloUI\\SelHero.cpp", 123, 0);
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000B7CA
int SelHero_1000B7CA() { return 0; }
/* {
	return dword_1002A48C;
} */
// 1002A48C: using guessed type int dword_1002A48C;

// ref: 0x1000B7D0
int __fastcall SelHero_1000B7D0(int a1, int a2) { return 0; }
/* {
	return dword_1002A410(a1, a2);
} */
// 1002A410: using guessed type int (__stdcall *dword_1002A410)(_DWORD, _DWORD);

// ref: 0x1000B7DE
signed int SelHero_1000B7DE() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A414 = 2139095040;
	return result;
} */
// 1002A414: using guessed type int dword_1002A414;

// ref: 0x1000B899
int __fastcall SelHero_1000B899(HWND hDlg, int a2) { return 0; }
/* {
	int v2; // ebx
	HWND v3; // esi
	struct tagRECT Rect; // [esp+8h] [ebp-10h]

	v2 = a2;
	v3 = GetDlgItem(hDlg, 1040);
	InvalidateRect(v3, 0, 0);
	GetClientRect(v3, &Rect);
	local_10007A68(&Rect, 0, v2 * Rect.bottom);
	return SDlgSetBitmapI(v3, 0, "Static", -1, 1, dword_1002A498, &Rect, dword_1002A418, dword_1002A41C, -1);
} */
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A418: using guessed type int dword_1002A418;
// 1002A41C: using guessed type int dword_1002A41C;
// 1002A498: using guessed type int dword_1002A498;

// ref: 0x1000B905
int __fastcall SelHero_1000B905(HWND hDlg, int a2) { return 0; }
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
	int result; // eax
	int v14; // esi
	HWND v15; // edi
	HWND v16; // ebp
	int v17; // eax
	HWND hWnd; // ST1C_4
	int v19; // eax
	HWND v20; // ST1C_4
	int v21; // eax
	HWND v22; // ST1C_4
	int v23; // eax
	HWND v24; // ST1C_4
	int v25; // eax
	HWND hDlga; // [esp+Ch] [ebp-4h]

	v14 = a2;
	v15 = hDlg;
	hDlga = hDlg;
	if ( *(_WORD *)(a2 + 20) )
	{
		dword_1002A424 = *(_DWORD *)(a2 + 36);
		strcpy(&byte_1002A440, (const char *)(a2 + 4));
		v16 = GetDlgItem(v15, 1014);
		wsprintfA(byte_1002A42C, "%d", *(unsigned short *)(v14 + 20));
		v17 = GetWindowLongA(v16, -21);
		local_10007FA4(v17, byte_1002A42C);
		hWnd = GetDlgItem(hDlga, 1018);
		wsprintfA(byte_1002A490, "%d", *(unsigned short *)(v14 + 24));
		v19 = GetWindowLongA(hWnd, -21);
		local_10007FA4(v19, byte_1002A490);
		v20 = GetDlgItem(hDlga, 1017);
		wsprintfA(byte_1002A43C, "%d", *(unsigned short *)(v14 + 26));
		v21 = GetWindowLongA(v20, -21);
		local_10007FA4(v21, byte_1002A43C);
		v22 = GetDlgItem(hDlga, 1016);
		wsprintfA(byte_1002A454, "%d", *(unsigned short *)(v14 + 28));
		v23 = GetWindowLongA(v22, -21);
		local_10007FA4(v23, byte_1002A454);
		v24 = GetDlgItem(hDlga, 1015);
		wsprintfA(byte_1002A494, "%d", *(unsigned short *)(v14 + 30));
		v25 = GetWindowLongA(v24, -21);
		local_10007FA4(v25, byte_1002A494);
		SelHero_1000B899(hDlga, *(unsigned char *)(v14 + 22));
		result = Doom_10006A13(hDlga, (int *)&unk_10023020, 1);
	}
	else
	{
		dword_1002A424 = 0;
		byte_1002A440 = 0;
		v2 = hDlg;
		v3 = GetDlgItem(hDlg, 1014);
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
		result = Doom_10006A13(v2, (int *)&unk_10023020, 1);
	}
	return result;
} */
// 1002A424: using guessed type int dword_1002A424;

// ref: 0x1000BA7B
HWND __fastcall SelHero_1000BA7B(HWND hDlg, const char *a2) { return 0; }
/* {
	HWND v2; // esi
	const char *v3; // edi
	HWND result; // eax
	int v5; // eax

	v2 = hDlg;
	v3 = a2;
	result = GetDlgItem(hDlg, 1038);
	if ( result )
	{
		v5 = GetWindowLongA(result, -21);
		local_10007FA4(v5, v3);
		result = (HWND)Doom_10006A13(v2, (int *)&unk_10023000, 5);
	}
	return result;
} */

// ref: 0x1000BAB4
char *UNKCALL SelHero_1000BAB4(char *arg) { return 0; }
/* {
	UINT v1; // esi
	char *result; // eax
	CHAR SrcStr; // [esp+4h] [ebp-90h]
	CHAR Buffer; // [esp+84h] [ebp-10h]

	strcpy(&SrcStr, arg);
	_strlwr(&SrcStr);
	v1 = 19;
	while ( 1 )
	{
		LoadStringA(hInstance, v1, &Buffer, 15);
		SelHero_1000BB26(&Buffer);
		_strlwr(&Buffer);
		result = strstr(&SrcStr, &Buffer);
		if ( result )
			break;
		if ( (signed int)++v1 > 26 )
			return result;
	}
	return (char *)1;
} */

// ref: 0x1000BB26
char __fastcall SelHero_1000BB26(char *a1) { return 0; }
/* {
	char result; // al

	while ( 1 )
	{
		result = *a1;
		if ( !*a1 )
			break;
		*a1++ = result - 1;
	}
	return result;
} */

// ref: 0x1000BB34
int __fastcall SelHero_1000BB34(char *a1, char *a2) { return 0; }
/* {
	char *v2; // esi
	char *v3; // edi
	char v5; // al

	v2 = a1;
	v3 = a2;
	if ( strpbrk(a1, ",<>%&\\\"?*#/:") || strpbrk(v2, v3) )
		return 1;
	while ( 1 )
	{
		v5 = *v2;
		if ( !*v2 )
			break;
		if ( (unsigned char)v5 < 0x20u || (unsigned char)v5 > 0x7Eu && (unsigned char)v5 < 0xC0u )
			return 1;
		++v2;
	}
	return 0;
} */

// ref: 0x1000BB75
int __stdcall UiValidPlayerName(char *arg) { return 0; }
/* {
	char *v1; // esi
	signed int v2; // edi

	v1 = arg;
	v2 = 1;
	if ( !strlen(arg) )
		v2 = 0;
	if ( dword_1002A48C == 1 && (SelHero_1000BAB4(v1) || SelHero_1000BB34(v1, " ")) )
		v2 = 0;
	return v2;
} */
// 1002A48C: using guessed type int dword_1002A48C;

// ref: 0x1000BBB4
int __stdcall UiSelHeroMultDialog(void *fninfo, void *fncreate, void *fnremove, void *fnstats, int *a5, int *a6, char *name) { return 0; }
/* {
	int v7; // eax
	int v8; // eax

	artfont_10001159();
	dword_1002A438 = (int (__stdcall *)(_DWORD))a1;
	dword_1002A450 = (int (UNKCALL *)(_DWORD, _DWORD))a2;
	dword_1002A434 = (int (__stdcall *)(_DWORD))a3;
	dword_1002A410 = (int (__stdcall *)(_DWORD, _DWORD))a4;
	dword_1002A458 = 0;
	dword_1002A48C = 1;
	dword_1002A45C = 0;
	v7 = SDrawGetFrameWindow();
	v8 = SDlgDialogBoxParam(hInstance, "SELHERO_DIALOG", v7, SelHero_1000BC46, 0);
	if ( a5 )
		*(_DWORD *)a5 = v8;
	if ( a7 )
		strcpy(a7, &byte_1002A440);
	if ( a6 )
		*(_DWORD *)a6 = dword_1002A45C;
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 1002A410: using guessed type int (__stdcall *dword_1002A410)(_DWORD, _DWORD);
// 1002A434: using guessed type int (__stdcall *dword_1002A434)(_DWORD);
// 1002A438: using guessed type int (__stdcall *dword_1002A438)(_DWORD);
// 1002A450: using guessed type int (UNKCALL *dword_1002A450)(_DWORD, _DWORD);
// 1002A458: using guessed type int dword_1002A458;
// 1002A45C: using guessed type int dword_1002A45C;
// 1002A48C: using guessed type int dword_1002A48C;

// ref: 0x1000BC46
int __stdcall SelHero_1000BC46(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v4; // eax
	int v6; // edx
	HWND v7; // ecx
	signed int v8; // [esp-4h] [ebp-8h]
	int v9; // [esp+0h] [ebp-4h]

	if ( Msg > 0xBD2 )
	{
		switch ( Msg )
		{
			case 0xBD3u:
				SelHero_1000C21A(hWnd);
				return 0;
			case 0xBD4u:
				SelHero_1000C269(hWnd);
				return 0;
			case 0xBD5u:
				v7 = hWnd;
				if ( dword_1002A48C != 1 )
				{
					v8 = 2;
					goto LABEL_30;
				}
				break;
			case 0xBD6u:
				strcpy(&byte_1002A440, byte_1002A464);
				v6 = 1;
				v7 = hWnd;
				if ( dword_1002A48C != 1 )
				{
					dword_1002A420 = 0;
LABEL_31:
					SelHero_1000C3E2((int)v7, v6);
					return 0;
				}
				break;
			case 0xBD7u:
				SelHero_1000BDAD(hWnd);
				return 0;
			default:
				return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
		v8 = 3;
LABEL_30:
		v6 = v8;
		goto LABEL_31;
	}
	if ( Msg == 3026 )
	{
		SelHero_1000C09B(hWnd);
		return 0;
	}
	if ( Msg == 2 )
	{
		SelHero_1000C364(hWnd);
		return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
	}
	if ( Msg <= 0x103 )
		return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
	if ( Msg <= 0x105 )
	{
		v4 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v4, Msg, wParam, lParam);
		return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
	}
	switch ( Msg )
	{
		case 0x110u:
			SelHero_1000C3FF(hWnd);
			PostMessageA(hWnd, 0x7E8u, 0, 0);
			return 0;
		case 0x7E8u:
			if ( !Fade_1000739F() )
				Fade_100073FD(hWnd, v9);
			return 0;
		case 0xBD0u:
			SelHero_1000BF6D(hWnd);
			return 0;
	}
	if ( Msg != 3025 )
		return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
	SelHero_1000BFF9(hWnd);
	return 0;
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 1002A420: using guessed type int dword_1002A420;
// 1002A48C: using guessed type int dword_1002A48C;

// ref: 0x1000BDAD
BOOL UNKCALL SelHero_1000BDAD(HWND arg) { return 0; }
/* {
	const char *v1; // eax
	CHAR v3; // [esp+Ch] [ebp-B4h]
	CHAR v4; // [esp+5Ch] [ebp-64h]
	CHAR Buffer; // [esp+9Ch] [ebp-24h]
	HWND hWnd; // [esp+BCh] [ebp-4h]

	hWnd = arg;
	if ( SelHero_1000B7CA() == 1 )
		LoadStringA(hInstance, 0x23u, &Buffer, 31);
	else
		LoadStringA(hInstance, 0x22u, &Buffer, 31);
	LoadStringA(hInstance, 7u, &v4, 63);
	wsprintfA(&v3, &v4, &byte_1002A440);
	if ( SelYesNo_1000FA49((int)hWnd, &v3, (int)&Buffer, 1) != 2 )
	{
		v1 = SelHero_1000BF4A((const char *)dword_1002A458, &byte_1002A440);
		if ( v1 )
		{
			if ( dword_1002A434(v1) )
			{
				dword_1002A458 = (int)SelHero_1000BEDB((int *)dword_1002A458, &byte_1002A440);
				--dword_1002A428;
				LoadStringA(hInstance, 0x1Eu, &v4, 15);
				if ( !strcmp(&v4, (const char *)(dword_1002A458 + 4)) )
					return PostMessageA(hWnd, 0xBD1u, 0, 0);
				SelHero_1000B905(hWnd, dword_1002A458);
			}
			else
			{
				LoadStringA(hInstance, 0x11u, &v4, 63);
				SelYesNo_1000FD39((int)hWnd, &v4, (int)&Buffer, 1);
			}
		}
	}
	return PostMessageA(hWnd, 0xBD0u, 0, 0);
} */
// 1002A428: using guessed type int dword_1002A428;
// 1002A434: using guessed type int (__stdcall *dword_1002A434)(_DWORD);
// 1002A458: using guessed type int dword_1002A458;

// ref: 0x1000BEDB
int *__fastcall SelHero_1000BEDB(int *a1, char *a2) { return 0; }
/* {
	int *v2; // ebx
	_DWORD *v3; // ebp
	_DWORD *v4; // edi
	int *v5; // esi
	char *v7; // [esp+10h] [ebp-4h]

	v2 = a1;
	v3 = 0;
	v4 = 0;
	v7 = a2;
	v5 = a1;
	if ( a1 )
	{
		while ( !v4 )
		{
			if ( !strcmp((const char *)v5 + 4, v7) )
			{
				v4 = v5;
			}
			else
			{
				v3 = v5;
				v5 = (int *)*v5;
			}
			if ( !v5 )
			{
				if ( !v4 )
					return v2;
				break;
			}
		}
		if ( v3 )
			*v3 = *v4;
		else
			v2 = (int *)*v4;
		SelHero_1000BF33(v4);
	}
	return v2;
} */

// ref: 0x1000BF33
int UNKCALL SelHero_1000BF33(void *arg) { return 0; }
/* {
	int result; // eax

	if ( arg )
		result = SMemFree(arg, "C:\\Src\\Diablo\\DiabloUI\\SelHero.cpp", 131, 0);
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000BF4A
const char *__fastcall SelHero_1000BF4A(const char *a1, const char *a2) { return 0; }
/* {
	const char *v2; // edi
	const char *i; // esi

	v2 = a2;
	for ( i = a1; i && _strcmpi(i + 4, v2); i = *(const char **)i )
		;
	return i;
} */

// ref: 0x1000BF6D
int UNKCALL SelHero_1000BF6D(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	int v2; // eax
	int v4; // edx

	v1 = hWnd;
	v2 = SDlgDialogBoxParam(hInstance, "SELLIST_DIALOG", hWnd, SelList_1000D774, 0);
	if ( v2 == 1 )
	{
		if ( !strlen(&byte_1002A440) )
			return PostMessageA(v1, 0xBD1u, 0, 0);
		if ( dword_1002A48C == 1 )
			return PostMessageA(v1, 0xBD5u, 0, 0);
		if ( dword_1002A424 )
			return PostMessageA(v1, 0xBD3u, 0, 0);
		dword_1002A420 = 0;
		v4 = 1;
		return SelHero_1000C3E2((int)v1, v4);
	}
	if ( v2 != 1006 )
	{
		v4 = 4;
		return SelHero_1000C3E2((int)v1, v4);
	}
	return PostMessageA(v1, 0xBD7u, 0, 0);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A420: using guessed type int dword_1002A420;
// 1002A424: using guessed type int dword_1002A424;
// 1002A48C: using guessed type int dword_1002A48C;

// ref: 0x1000BFF9
int UNKCALL SelHero_1000BFF9(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	int v2; // eax
	int v3; // eax
	int result; // eax
	CHAR Buffer; // [esp+8h] [ebp-20h]

	v1 = hWnd;
	v2 = SDlgDialogBoxParam(hInstance, "SELCLASS_DIALOG", hWnd, SelClass_10009D66, 0);
	if ( v2 == -1 || v2 == 2 )
	{
		LoadStringA(hInstance, 0x1Eu, &Buffer, 31);
		if ( !strcmp(&Buffer, (const char *)(dword_1002A458 + 4)) )
			result = SelHero_1000C3E2((int)v1, 4);
		else
			result = PostMessageA(v1, 0xBD0u, 0, 0);
	}
	else
	{
		v3 = v2 - 1063;
		if ( v3 )
		{
			if ( v3 == 1 )
				byte_1002A476 = 2;
			else
				byte_1002A476 = 0;
		}
		else
		{
			byte_1002A476 = 1;
		}
		result = PostMessageA(v1, 0xBD2u, 0, 0);
	}
	return result;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A458: using guessed type int dword_1002A458;
// 1002A476: using guessed type char byte_1002A476;

// ref: 0x1000C09B
int UNKCALL SelHero_1000C09B(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	int result; // eax
	char v3; // [esp+8h] [ebp-10h]
	char v4; // [esp+17h] [ebp-1h]

	v1 = hWnd;
	if ( SDlgDialogBoxParam(hInstance, "ENTERNAME_DIALOG", hWnd, EntName_10006F7C, &v3) != 1 )
		return PostMessageA(v1, 0xBD1u, 0, 0);
	v4 = 0;
	if ( SelHero_1000C0F9((int)v1, &v3) )
		result = PostMessageA(v1, 0xBD6u, 0, 0);
	else
		result = PostMessageA(v1, 0xBD2u, 0, 0);
	return result;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000C0F9
signed int __fastcall SelHero_1000C0F9(int a1, char *a2) { return 0; }
/* {
	const char *v2; // edi
	int v3; // ST0C_4
	CHAR v5; // [esp+Ch] [ebp-138h]
	CHAR v6; // [esp+9Ch] [ebp-A8h]
	CHAR Buffer; // [esp+11Ch] [ebp-28h]
	int v8; // [esp+13Ch] [ebp-8h]
	char *v9; // [esp+140h] [ebp-4h]

	v9 = a2;
	v8 = a1;
	if ( SelHero_1000B7CA() == 1 )
		LoadStringA(hInstance, 0x20u, &Buffer, 31);
	else
		LoadStringA(hInstance, 0x1Fu, &Buffer, 31);
	if ( !UiValidPlayerName(v9) )
	{
		LoadStringA(hInstance, 0xFu, &v6, 127);
		SelYesNo_1000FD39(v8, &v6, (int)&Buffer, 1);
		return 0;
	}
	v2 = SelHero_1000BF4A((const char *)dword_1002A458, v9);
	if ( v2 )
	{
		LoadStringA(hInstance, 8u, &v6, 127);
		wsprintfA(&v5, &v6, v2 + 4);
		if ( SelYesNo_1000FA49(v8, &v5, (int)&Buffer, 1) == 2 )
			return 0;
	}
	strcpy(byte_1002A464, v9);
	dword_1002A484 = 0;
	if ( !dword_1002A450(v3, &unk_1002A460) )
	{
		LoadStringA(hInstance, 0x10u, &v6, 127);
		OkCancel_1000930A(v8, (int)&v6, 1);
		return 0;
	}
	dword_1002A45C = 1;
	return 1;
} */
// 1002A450: using guessed type int (UNKCALL *dword_1002A450)(_DWORD, _DWORD);
// 1002A458: using guessed type int dword_1002A458;
// 1002A45C: using guessed type int dword_1002A45C;
// 1002A484: using guessed type int dword_1002A484;

// ref: 0x1000C21A
BOOL UNKCALL SelHero_1000C21A(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	int v2; // eax

	v1 = hWnd;
	v2 = SDlgDialogBoxParam(hInstance, "SELLOAD_DIALOG", hWnd, SelLoad_1000E1C2, 0);
	if ( v2 == -1 || v2 == 2 )
		return PostMessageA(v1, 0xBD0u, 0, 0);
	if ( v2 == 1106 )
		return PostMessageA(v1, 0xBD5u, 0, 0);
	return PostMessageA(v1, 0xBD4u, 0, 0);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000C269
int UNKCALL SelHero_1000C269(HWND hWnd) { return 0; }
/* {
	HWND v1; // ebx
	int v2; // ecx
	const char *v4; // eax
	int v5; // eax
	CHAR Buffer; // [esp+4h] [ebp-208h]
	char v7; // [esp+104h] [ebp-108h]
	char v8; // [esp+184h] [ebp-88h]
	char v9; // [esp+204h] [ebp-8h]
	char v10; // [esp+208h] [ebp-4h]

	v1 = hWnd;
	if ( !SelHero_1000B7CA() )
	{
		SelHero_1000B7AC(0);
		v2 = (int)v1;
		return SelHero_1000C3E2(v2, 1);
	}
	CreaDung_10004C33((void *)1);
	if ( SDlgDialogBoxParam(hInstance, "SELDIFF_DIALOG", v1, CreaDung_10004C4A, dword_1002A48C) != 1 )
		return PostMessageA(v1, 0xBD3u, 0, 0);
	v4 = SelHero_1000BF4A((const char *)dword_1002A458, &byte_1002A440);
	UiCreatePlayerDescription((int)v4, 1145195599, (int)&v8);
	v10 = dword_1002A420;
	Connect_10003E0C((int)&v9, &byte_1002A440, &v8, &v7, 128);
	v5 = UiAuthCallback(2, (int)&byte_1002A440, &v8, 0, &v7, &Buffer, 256);
	v2 = (int)v1;
	if ( v5 )
		return SelHero_1000C3E2(v2, 1);
	SelYesNo_1000FD39((int)v1, &Buffer, 0, 1);
	return PostMessageA(v1, 0xBD4u, 0, 0);
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1002A420: using guessed type int dword_1002A420;
// 1002A458: using guessed type int dword_1002A458;
// 1002A48C: using guessed type int dword_1002A48C;

// ref: 0x1000C364
void UNKCALL SelHero_1000C364(HWND hDlg) { return; }
/* {
	HWND v1; // esi
	_DWORD *v2; // eax

	v1 = hDlg;
	Doom_10006C53(hDlg, (int *)&unk_10023020);
	Doom_10006C53(v1, (int *)&unk_10023008);
	Doom_10006C53(v1, (int *)&unk_10023000);
	Title_100100E7(v1);
	SelHero_1000C3CE((_DWORD *)dword_1002A458);
	if ( dword_1002A498 )
	{
		SMemFree(dword_1002A498, "C:\\Src\\Diablo\\DiabloUI\\SelHero.cpp", 744, 0);
		dword_1002A498 = 0;
	}
	v2 = (_DWORD *)GetWindowLongA(v1, -21);
	local_10007F72(v2);
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 1002A458: using guessed type int dword_1002A458;
// 1002A498: using guessed type int dword_1002A498;

// ref: 0x1000C3CE
int __fastcall SelHero_1000C3CE(_DWORD *a1) { return 0; }
/* {
	_DWORD *v1; // esi
	int result; // eax

	if ( a1 )
	{
		do
		{
			v1 = (_DWORD *)*a1;
			result = SelHero_1000BF33(a1);
			a1 = v1;
		}
		while ( v1 );
	}
	return result;
} */

// ref: 0x1000C3E2
int __fastcall SelHero_1000C3E2(int a1, int a2) { return 0; }
/* {
	int v2; // edi
	int v3; // esi

	v2 = a2;
	v3 = a1;
	Fade_100073B4();
	Fade_100072BE(10);
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);

// ref: 0x1000C3FF
int UNKCALL SelHero_1000C3FF(HWND hWnd) { return 0; }
/* {
	HWND v1; // eax
	int v2; // eax
	HWND v3; // eax
	int v4; // eax
	HWND v5; // eax
	int v6; // eax
	HWND v7; // eax
	int v8; // eax
	HWND v9; // eax
	int v10; // eax
	HWND v12; // esi
	int v13; // eax
	int *v14; // edi
	void *v15; // [esp+0h] [ebp-8h]
	HWND v16; // [esp+0h] [ebp-8h]

	v12 = hWnd;
	SelHero_1000C49F(hWnd, v15);
	v13 = local_10007F46();
	v14 = (int *)v13;
	if ( v13 )
	{
		SetWindowLongA(v12, -21, v13);
		local_10007944((int)v12, 0, &byte_10029448, -1, 1, (int)"ui_art\\selhero.pcx", v14, v14 + 1, 0);
		Fade_100073C5(v12, 1);
	}
	local_100078BE((int)"ui_art\\heros.pcx", &dword_1002A498, &dword_1002A418);
	SetActiveWindow(v12);
	Title_1001009E(v12, (int)"ui_art\\smlogo.pcx", v16);
	Doom_100068AB(v12, (int *)&unk_10023000, 5);
	Doom_100068AB(v12, (int *)&unk_10023008, 1);
	Doom_100068AB(v12, (int *)&unk_10023020, 1);
	dword_1002A424 = 0;
	byte_1002A440 = 0;
	v1 = GetDlgItem(v12, 1014);
	v2 = GetWindowLongA(v1, -21);
	local_10007FA4(v2, "--");
	v3 = GetDlgItem(v12, 1018);
	v4 = GetWindowLongA(v3, -21);
	local_10007FA4(v4, "--");
	v5 = GetDlgItem(v12, 1017);
	v6 = GetWindowLongA(v5, -21);
	local_10007FA4(v6, "--");
	v7 = GetDlgItem(v12, 1016);
	v8 = GetWindowLongA(v7, -21);
	local_10007FA4(v8, "--");
	v9 = GetDlgItem(v12, 1015);
	v10 = GetWindowLongA(v9, -21);
	local_10007FA4(v10, "--");
	SelHero_1000B899(v12, 3);
	return Doom_10006A13(v12, (int *)&unk_10023020, 1);
} */
// 1002A418: using guessed type int dword_1002A418;
// 1002A424: using guessed type int dword_1002A424;
// 1002A498: using guessed type int dword_1002A498;

// ref: 0x1000C49F
BOOL UNKCALL SelHero_1000C49F(HWND hWnd, void *a2) { return 0; }
/* {
	HWND v2; // ebx
	int v3; // esi
	BOOL result; // eax
	int v5; // [esp+10h] [ebp-44h]
	CHAR Buffer; // [esp+14h] [ebp-40h]

	v2 = hWnd;
	v3 = SelHero_1000B7B9();
	*(_DWORD *)v3 = 0;
	LoadStringA(hInstance, 0x1Eu, (LPSTR)(v3 + 4), 15);
	*(_WORD *)(v3 + 20) = 0;
	dword_1002A458 = (int)SelRegn_1000EF56(dword_1002A458, (_DWORD *)v3);
	v5 = dword_1002A458;
	dword_1002A428 = 1;
	if ( !dword_1002A438(SelHero_1000C541) )
	{
		LoadStringA(hInstance, 0x12u, &Buffer, 64);
		OkCancel_1000930A((int)v2, (int)&Buffer, 1);
	}
	if ( v5 == dword_1002A458 )
		result = PostMessageA(v2, 0xBD1u, 0, 0);
	else
		result = PostMessageA(v2, 0xBD0u, 0, 0);
	return result;
} */
// 1002A428: using guessed type int dword_1002A428;
// 1002A438: using guessed type int (__stdcall *dword_1002A438)(_DWORD);
// 1002A458: using guessed type int dword_1002A458;

// ref: 0x1000C541
signed int __stdcall SelHero_1000C541(void *a1) { return 0; }
/* {
	_DWORD *v1; // esi
	_DWORD *v2; // eax

	v1 = (_DWORD *)SelHero_1000B7B9();
	memcpy(v1, a1, 0x2Cu);
	*v1 = 0;
	v2 = SelRegn_1000EF56(dword_1002A458, v1);
	++dword_1002A428;
	dword_1002A458 = (int)v2;
	return 1;
} */
// 1002A428: using guessed type int dword_1002A428;
// 1002A458: using guessed type int dword_1002A458;

// ref: 0x1000C57A
int __stdcall UiSelHeroSingDialog(void *fninfo, void *fncreate, void *fnremove, void *fnstats, int *a5, char *name, int *difficulty) { return 0; }
/* {
	int v7; // eax
	int v8; // edi

	artfont_10001159();
	dword_1002A438 = (int (__stdcall *)(_DWORD))a1;
	dword_1002A450 = (int (UNKCALL *)(_DWORD, _DWORD))a2;
	dword_1002A434 = (int (__stdcall *)(_DWORD))a3;
	dword_1002A410 = (int (__stdcall *)(_DWORD, _DWORD))a4;
	dword_1002A458 = 0;
	dword_1002A48C = 0;
	v7 = SDrawGetFrameWindow();
	v8 = SDlgDialogBoxParam(hInstance, "SELHERO_DIALOG", v7, SelHero_1000BC46, 0);
	if ( a5 )
		*(_DWORD *)a5 = v8;
	if ( a6 )
		strcpy(a6, &byte_1002A440);
	if ( a7 )
		*(_DWORD *)a7 = dword_1002A420;
	if ( v8 != 4 )
		artfont_100010C8();
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 1002A410: using guessed type int (__stdcall *dword_1002A410)(_DWORD, _DWORD);
// 1002A420: using guessed type int dword_1002A420;
// 1002A434: using guessed type int (__stdcall *dword_1002A434)(_DWORD);
// 1002A438: using guessed type int (__stdcall *dword_1002A438)(_DWORD);
// 1002A450: using guessed type int (UNKCALL *dword_1002A450)(_DWORD, _DWORD);
// 1002A458: using guessed type int dword_1002A458;
// 1002A48C: using guessed type int dword_1002A48C;
