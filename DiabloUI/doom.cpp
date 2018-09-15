// ref: 0x10006581
signed int Doom_10006581() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029854 = 2139095040;
	return result;
} */
// 10029854: using guessed type int dword_10029854;

// ref: 0x1000658C
int __fastcall Doom_1000658C(HWND hWnd, int *a2, int a3, int a4) { return 0; }
/* {
	int *v4; // esi
	HWND v5; // edi
	HWND v6; // eax
	int result; // eax

	v4 = a2;
	v5 = hWnd;
	while ( 1 )
	{
		result = *v4;
		if ( !*v4 )
			break;
		v6 = GetDlgItem(v5, result);
		Doom_100065BB(v5, v6, a3, a4);
		++v4;
	}
	return result;
} */

// ref: 0x100065BB
void __fastcall Doom_100065BB(HWND hWnd, HWND a2, int a3, int a4) { return; }
/* {
	HWND v4; // esi
	HWND v5; // edi
	int v6; // eax
	CHAR String; // [esp+8h] [ebp-100h]

	v4 = a2;
	v5 = hWnd;
	if ( a2 )
	{
		Doom_10006719((int)hWnd, a2, 1521);
		Doom_1000678A(v5, v4);
		artfont_10001058((char *)a3);
		Doom_1000663F(v4, a4);
		GetWindowTextA(v4, &String, 255);
		if ( strlen(&String) )
		{
			v6 = GetWindowLongA(v4, -21);
			local_10007FA4(v6, &String);
			SetWindowTextA(v4, &byte_10029448);
		}
	}
} */

// ref: 0x1000663F
_DWORD *__fastcall Doom_1000663F(HWND hWnd, int a2) { return 0; }
/* {
	int v2; // edi
	_DWORD *result; // eax
	_DWORD *v4; // esi
	unsigned char *v5; // ebx
	int v6; // edi
	size_t v7; // eax
	unsigned char *i; // eax
	int v9; // kr04_4
	int v10; // eax
	CHAR String; // [esp+8h] [ebp-10Ch]
	unsigned char *v12; // [esp+108h] [ebp-Ch]
	HWND hWnda; // [esp+10Ch] [ebp-8h]
	int v14; // [esp+110h] [ebp-4h]

	v2 = a2;
	hWnda = hWnd;
	result = (_DWORD *)GetWindowLongA(hWnd, -21);
	v4 = result;
	if ( result && *result )
	{
		GetWindowTextA(hWnda, &String, 255);
		v5 = (unsigned char *)&String;
		if ( !strlen(&String) )
			v5 = (unsigned char *)(v4 + 4);
		v14 = artfont_10001329(v5);
		if ( v2 )
		{
			v6 = v4[1] - 2 * Focus_10007482();
			v7 = strlen((const char *)v5);
			if ( v14 > v6 )
			{
				for ( i = &v5[v7]; ; i = v12 )
				{
					v12 = i - 1;
					*v12 = 0;
					v14 = artfont_10001329(v5);
					if ( v14 <= v6 )
						break;
				}
			}
		}
		v9 = v4[1] - v14 - 1;
		v10 = artfont_100012F6();
		artfont_100013CD(v5, v4, v9 / 2, (v4[2] - v10) / 2);
		result = (_DWORD *)InvalidateRect(hWnda, 0, 0);
	}
	return result;
} */

// ref: 0x10006719
int __fastcall Doom_10006719(int a1, HWND a2, int a3) { return 0; }
/* {
	HWND v3; // edi
	_DWORD *v4; // eax
	_DWORD *v5; // esi
	struct tagRECT Rect; // [esp+8h] [ebp-10h]

	v3 = a2;
	GetClientRect(a2, &Rect);
	v4 = (_DWORD *)local_10007F46();
	v5 = v4;
	v4[1] = Rect.right;
	v4[2] = Rect.bottom;
	*v4 = SMemAlloc(Rect.right * Rect.bottom, "C:\\Src\\Diablo\\DiabloUI\\Doom.cpp", 139, 0);
	SetWindowLongA(v3, -21, (LONG)v5);
	return SDlgSetBitmapI(v3, 0, &byte_10029448, -1, a3, *v5, 0, v5[1], v5[2], -1);
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000678A
_DWORD *__fastcall Doom_1000678A(HWND hWnd, HWND a2) { return 0; }
/* {
	HWND v2; // edi
	_DWORD *v3; // ebx
	_DWORD *result; // eax
	_DWORD *v5; // esi
	struct tagRECT Rect; // [esp+Ch] [ebp-14h]
	HWND hWnda; // [esp+1Ch] [ebp-4h]

	v2 = a2;
	hWnda = hWnd;
	v3 = (_DWORD *)GetWindowLongA(hWnd, -21);
	result = (_DWORD *)GetWindowLongA(v2, -21);
	v5 = result;
	if ( v3 && *v3 && result )
	{
		if ( *result )
		{
			GetWindowRect(v2, &Rect);
			ScreenToClient(hWnda, (LPPOINT)&Rect);
			ScreenToClient(hWnda, (LPPOINT)&Rect.right);
			result = (_DWORD *)SBltROP3(
								   *v5,
								   Rect.left + *v3 + Rect.top * v3[1],
								   v5[1],
								   v5[2],
								   v5[1],
								   v3[1],
								   0,
								   13369376);
		}
	}
	return result;
} */
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000680A
int __fastcall Doom_1000680A(HWND hDlg, int *a2, int a3, int a4) { return 0; }
/* {
	int *v4; // esi
	HWND v5; // edi
	HWND v6; // eax
	int result; // eax

	v4 = a2;
	v5 = hDlg;
	while ( 1 )
	{
		result = *v4;
		if ( !*v4 )
			break;
		v6 = GetDlgItem(v5, result);
		Doom_10006839(v5, v6, (char *)a3, a4);
		++v4;
	}
	return result;
} */

// ref: 0x10006839
void __fastcall Doom_10006839(HWND a1, HWND a2, char *a3, int a4) { return; }
/* {
	HWND v4; // esi
	int v5; // eax
	CHAR String; // [esp+4h] [ebp-100h]

	v4 = a2;
	if ( a2 )
	{
		Doom_1000678A(a1, a2);
		artfont_10001058(a3);
		Doom_1000663F(v4, a4);
		GetWindowTextA(v4, &String, 255);
		if ( strlen(&String) )
		{
			v5 = GetWindowLongA(v4, -21);
			local_10007FA4(v5, &String);
			SetWindowTextA(v4, &byte_10029448);
		}
	}
} */

// ref: 0x100068AB
int __fastcall Doom_100068AB(HWND hWnd, int *a2, int a3) { return 0; }
/* {
	int *v3; // esi
	HWND v4; // edi
	HWND v5; // eax
	int result; // eax

	v3 = a2;
	v4 = hWnd;
	while ( 1 )
	{
		result = *v3;
		if ( !*v3 )
			break;
		v5 = GetDlgItem(v4, result);
		Doom_100068D6(v4, v5, a3);
		++v3;
	}
	return result;
} */

// ref: 0x100068D6
void __fastcall Doom_100068D6(HWND hWnd, HWND a2, int a3) { return; }
/* {
	HWND v3; // esi
	HWND v4; // edi
	int v5; // eax
	int v6; // eax
	CHAR String; // [esp+8h] [ebp-100h]

	v3 = a2;
	v4 = hWnd;
	if ( a2 )
	{
		Doom_10006719((int)hWnd, a2, 1);
		Doom_1000678A(v4, v3);
		artfont_10001058((char *)a3);
		v5 = GetWindowLongA(v3, -16);
		Doom_1000695D(v3, v5);
		GetWindowTextA(v3, &String, 255);
		if ( strlen(&String) )
		{
			v6 = GetWindowLongA(v3, -21);
			local_10007FA4(v6, &String);
			SetWindowTextA(v3, &byte_10029448);
		}
	}
} */

// ref: 0x1000695D
_DWORD *__fastcall Doom_1000695D(HWND hWnd, int a2) { return 0; }
/* {
	_DWORD *result; // eax
	_DWORD *v3; // esi
	unsigned char *v4; // edi
	int v5; // eax
	CHAR String; // [esp+4h] [ebp-108h]
	int v7; // [esp+104h] [ebp-8h]
	HWND hWnda; // [esp+108h] [ebp-4h]

	v7 = a2;
	hWnda = hWnd;
	result = (_DWORD *)GetWindowLongA(hWnd, -21);
	v3 = result;
	if ( result && *result )
	{
		GetWindowTextA(hWnda, &String, 255);
		v4 = (unsigned char *)&String;
		if ( !strlen(&String) )
			v4 = (unsigned char *)(v3 + 4);
		if ( v7 & 2 )
		{
			v5 = v3[1] - artfont_10001329(v4) - 1;
		}
		else if ( v7 & 1 )
		{
			v5 = (v3[1] - artfont_10001329(v4) - 1) / 2;
		}
		else
		{
			v5 = 0;
		}
		artfont_100013CD(v4, v3, v5, 0);
		result = (_DWORD *)InvalidateRect(hWnda, 0, 0);
	}
	return result;
} */

// ref: 0x10006A13
int __fastcall Doom_10006A13(HWND hDlg, int *a2, int a3) { return 0; }
/* {
	int *v3; // esi
	HWND v4; // edi
	HWND v5; // eax
	int result; // eax

	v3 = a2;
	v4 = hDlg;
	while ( 1 )
	{
		result = *v3;
		if ( !*v3 )
			break;
		v5 = GetDlgItem(v4, result);
		Doom_10006A3E(v4, v5, (char *)a3);
		++v3;
	}
	return result;
} */

// ref: 0x10006A3E
void __fastcall Doom_10006A3E(HWND a1, HWND a2, char *a3) { return; }
/* {
	HWND v3; // edi
	int v4; // eax
	int v5; // eax
	CHAR String; // [esp+8h] [ebp-100h]

	v3 = a2;
	if ( a2 )
	{
		Doom_1000678A(a1, a2);
		artfont_10001058(a3);
		v4 = GetWindowLongA(v3, -16);
		Doom_1000695D(v3, v4);
		GetWindowTextA(v3, &String, 255);
		if ( strlen(&String) )
		{
			v5 = GetWindowLongA(v3, -21);
			local_10007FA4(v5, &String);
			SetWindowTextA(v3, &byte_10029448);
		}
	}
} */

// ref: 0x10006AB8
int __fastcall Doom_10006AB8(HWND hWnd, int *a2, int a3) { return 0; }
/* {
	int *v3; // esi
	HWND v4; // edi
	HWND v5; // eax
	int result; // eax

	v3 = a2;
	v4 = hWnd;
	while ( 1 )
	{
		result = *v3;
		if ( !*v3 )
			break;
		v5 = GetDlgItem(v4, result);
		Doom_10006AE3(v4, v5, a3);
		++v3;
	}
	return result;
} */

// ref: 0x10006AE3
void __fastcall Doom_10006AE3(HWND hWnd, HWND a2, int a3) { return; }
/* {
	HWND v3; // esi
	HWND v4; // edi

	v3 = a2;
	v4 = hWnd;
	if ( a2 )
	{
		Doom_10006719((int)hWnd, a2, 1);
		Doom_1000678A(v4, v3);
		artfont_10001058((char *)a3);
		Doom_10006B12(v3);
	}
} */

// ref: 0x10006B12
void UNKCALL Doom_10006B12(HWND hWnd) { return; }
/* {
	HWND v1; // ebx
	_DWORD *v2; // eax
	int v3; // edi
	int v4; // edi
	int v5; // esi
	int v6; // esi
	unsigned char *v7; // ebx
	int v8; // eax
	char v9; // [esp+3h] [ebp-11Dh]
	CHAR String; // [esp+4h] [ebp-11Ch]
	struct tagRECT Rect; // [esp+104h] [ebp-1Ch]
	LRESULT v12; // [esp+114h] [ebp-Ch]
	_DWORD *v13; // [esp+118h] [ebp-8h]
	size_t v14; // [esp+11Ch] [ebp-4h]

	v1 = hWnd;
	v2 = (_DWORD *)GetWindowLongA(hWnd, -21);
	v13 = v2;
	if ( v2 && *v2 )
	{
		GetWindowTextA(v1, &String, 255);
		v14 = strlen(&String);
		v3 = Focus_10007482();
		v4 = artfont_10001310() + v3;
		GetClientRect(v1, &Rect);
		v5 = Focus_10007482();
		v6 = Rect.right - 2 * (artfont_10001310() + v5);
		v12 = SendMessageA(v1, 0x403u, 0, 0);
		if ( v12 == 1 )
			*(&v9 + v14) = 0;
		v7 = (unsigned char *)&String;
		if ( String )
		{
			do
			{
				if ( artfont_10001329(v7) <= v6 )
					break;
				++v7;
			}
			while ( *v7 );
		}
		if ( v12 )
			*(&v9 + v14) = 124;
		v8 = artfont_100012F6();
		artfont_100013CD(v7, v13, v4, (v13[2] - v8) / 2);
	}
} */

// ref: 0x10006C08
int __fastcall Doom_10006C08(HWND hDlg, int *a2, int a3) { return 0; }
/* {
	int *v3; // esi
	HWND v4; // edi
	HWND v5; // eax
	int result; // eax

	v3 = a2;
	v4 = hDlg;
	while ( 1 )
	{
		result = *v3;
		if ( !*v3 )
			break;
		v5 = GetDlgItem(v4, result);
		Doom_10006C33(v4, v5, (char *)a3);
		++v3;
	}
	return result;
} */

// ref: 0x10006C33
void __fastcall Doom_10006C33(HWND a1, HWND a2, char *a3) { return; }
/* {
	HWND v3; // esi

	v3 = a2;
	if ( a2 )
	{
		Doom_1000678A(a1, a2);
		artfont_10001058(a3);
		Doom_10006B12(v3);
	}
} */

// ref: 0x10006C53
int __fastcall Doom_10006C53(HWND hDlg, int *a2) { return 0; }
/* {
	int *v2; // edi
	HWND v3; // ebx
	int result; // eax
	HWND v5; // eax
	HWND v6; // esi
	_DWORD *v7; // eax

	v2 = a2;
	v3 = hDlg;
	for ( result = *a2; *v2; result = *v2 )
	{
		v5 = GetDlgItem(v3, result);
		v6 = v5;
		if ( v5 )
		{
			v7 = (_DWORD *)GetWindowLongA(v5, -21);
			local_10007F72(v7);
			SetWindowLongA(v6, -21, 0);
		}
		++v2;
	}
	return result;
} */
