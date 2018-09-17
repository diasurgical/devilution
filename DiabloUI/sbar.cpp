// ref: 0x100099B5
signed int Sbar_100099B5() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A338 = 2139095040;
	return result;
} */
// 1002A338: using guessed type int dword_1002A338;

// ref: 0x100099C0
int UNKCALL Sbar_100099C0(HWND hWnd) { return 0; }
/* {
	_DWORD *v1; // eax

	v1 = (_DWORD *)GetWindowLongA(hWnd, -21);
	if ( !v1 || !*v1 )
		return 0;
	*v1 = 0;
	return 1;
} */

// ref: 0x100099DC
int __fastcall Sbar_100099DC(HWND hWnd, LONG a2, int a3) { return 0; }
/* {
	HWND v3; // esi
	_DWORD *v4; // eax
	_DWORD *v5; // esi
	int result; // eax
	signed int v7; // ecx
	LONG v8; // ebx
	LONG v9; // edi
	signed int v10; // [esp-4h] [ebp-1Ch]
	struct tagPOINT Point; // [esp+Ch] [ebp-Ch]
	HWND hWnda; // [esp+14h] [ebp-4h]

	v3 = hWnd;
	hWnda = hWnd;
	Point.x = a2;
	Point.y = a3;
	if ( !hWnd )
		return 0;
	if ( !IsWindowVisible(hWnd) )
		return 0;
	v4 = (_DWORD *)GetWindowLongA(v3, -21);
	v5 = v4;
	if ( !v4 )
		return 0;
	v7 = v4[13];
	if ( v7 <= 1 )
		v8 = 22;
	else
		v8 = v4[14] * (v4[3] - v4[9] - 44) / (v7 - 1) + 22;
	v9 = v8 + v4[9];
	ScreenToClient(hWnda, &Point);
	if ( Point.y >= 22 )
	{
		if ( Point.y >= v8 )
		{
			if ( Point.y >= v9 )
			{
				if ( Point.y >= v5[3] - 22 )
				{
					*v5 = 4;
					v10 = 2;
				}
				else
				{
					*v5 = 8;
					v10 = 4;
				}
			}
			else
			{
				*v5 = 16;
				v10 = 5;
			}
		}
		else
		{
			*v5 = 2;
			v10 = 3;
		}
		result = v10;
	}
	else
	{
		result = 1;
		*v5 = 1;
	}
	return result;
} */

// ref: 0x10009A99
HWND __fastcall Sbar_10009A99(HWND hDlg, int nIDDlgItem, int a3, int a4) { return 0; }
/* {
	HWND result; // eax
	HWND v5; // esi
	bool v6; // zf
	int v7; // eax
	int v8; // [esp+Ch] [ebp-24h]
	int v9; // [esp+10h] [ebp-20h]
	int v10; // [esp+14h] [ebp-1Ch]
	int v11; // [esp+18h] [ebp-18h]
	int v12; // [esp+1Ch] [ebp-14h]
	int v13; // [esp+20h] [ebp-10h]
	int v14; // [esp+24h] [ebp-Ch]
	int v15; // [esp+28h] [ebp-8h]
	HWND hWnd; // [esp+2Ch] [ebp-4h]

	result = GetDlgItem(hDlg, nIDDlgItem);
	hWnd = result;
	if ( result )
	{
		result = (HWND)GetWindowLongA(result, -21);
		v5 = result;
		if ( result )
		{
			if ( *((_DWORD *)result + 1) )
			{
				v6 = *((_DWORD *)result + 4) == 0;
				*((_DWORD *)result + 13) = a3;
				result = (HWND)a4;
				*((_DWORD *)v5 + 14) = a4;
				if ( !v6 )
				{
					v12 = 0;
					v8 = 0;
					v13 = 0;
					v9 = 0;
					v10 = *((_DWORD *)v5 + 2) - 1;
					v11 = *((_DWORD *)v5 + 3) - 1;
					v14 = *((_DWORD *)v5 + 2) - 1;
					v15 = *((_DWORD *)v5 + 6) - 1;
					result = (HWND)SBltROP3Tiled(
									   *((_DWORD *)v5 + 1),
									   &v8,
									   *((_DWORD *)v5 + 2),
									   *((_DWORD *)v5 + 4),
									   &v12,
									   *((_DWORD *)v5 + 5),
									   0,
									   0,
									   0,
									   13369376);
					if ( *((_DWORD *)v5 + 7) )
					{
						if ( a3 <= 1 )
							v7 = 22;
						else
							v7 = a4 * (*((_DWORD *)v5 + 3) - *((_DWORD *)v5 + 9) - 44) / (a3 - 1) + 22;
						SBltROP3(
							v7 * *((_DWORD *)v5 + 2) + *((_DWORD *)v5 + 1) + 3,
							*((_DWORD *)v5 + 7),
							18,
							*((_DWORD *)v5 + 9),
							*((_DWORD *)v5 + 2),
							*((_DWORD *)v5 + 8),
							0,
							13369376);
						SBltROP3(
							*((_DWORD *)v5 + 1),
							*((_DWORD *)v5 + 10) + 22 * (~*(_BYTE *)v5 & 1) * *((_DWORD *)v5 + 11),
							*((_DWORD *)v5 + 2),
							22,
							*((_DWORD *)v5 + 2),
							*((_DWORD *)v5 + 11),
							0,
							13369376);
						SBltROP3(
							*((_DWORD *)v5 + 1) + *((_DWORD *)v5 + 2) * (*((_DWORD *)v5 + 3) - 22),
							*((_DWORD *)v5 + 10) + 22 * ((~*(_BYTE *)v5 & 4 | 8u) >> 2) * *((_DWORD *)v5 + 11),
							*((_DWORD *)v5 + 2),
							22,
							*((_DWORD *)v5 + 2),
							*((_DWORD *)v5 + 11),
							0,
							13369376);
						result = (HWND)InvalidateRect(hWnd, 0, 0);
					}
				}
			}
		}
	}
	return result;
} */
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1001046C: using guessed type int __stdcall SBltROP3Tiled(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10009BF1
HWND __fastcall Sbar_10009BF1(HWND hDlg, int nIDDlgItem) { return 0; }
/* {
	HWND result; // eax
	HWND v3; // esi
	struct tagRECT Rect; // [esp+Ch] [ebp-14h]
	HWND hWnd; // [esp+1Ch] [ebp-4h]

	result = GetDlgItem(hDlg, nIDDlgItem);
	hWnd = result;
	if ( result )
	{
		result = (HWND)SMemAlloc(60, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 221, 0);
		v3 = result;
		if ( result )
		{
			SetWindowLongA(hWnd, -21, (LONG)result);
			*(_DWORD *)v3 = 0;
			GetClientRect(hWnd, &Rect);
			*(_DWORD *)(v3 + 2) = Rect.right;
			*(_DWORD *)(v3 + 3) = Rect.bottom;
			result = (HWND)SMemAlloc(Rect.right * Rect.bottom, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 230, 0);
			*((_DWORD *)v3 + 1) = result;
			if ( result )
			{
				SDlgSetBitmapI(hWnd, 0, &byte_10029448, -1, 1, result, 0, *((_DWORD *)v3 + 2), *((_DWORD *)v3 + 3), -1);
				local_100078BE((int)"ui_art\\sb_bg.pcx", (int *)v3 + 4, (_DWORD *)v3 + 5);
				local_100078BE((int)"ui_art\\sb_thumb.pcx", (int *)v3 + 7, (_DWORD *)v3 + 8);
				result = (HWND)local_100078BE((int)"ui_art\\sb_arrow.pcx", (int *)v3 + 10, (_DWORD *)v3 + 11);
			}
		}
	}
	return result;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10009CC7
signed int Sbar_10009CC7() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A344 = 2139095040;
	return result;
} */
// 1002A344: using guessed type int dword_1002A344;

// ref: 0x10009CD2
HWND __fastcall Sbar_10009CD2(HWND hDlg, int nIDDlgItem) { return 0; }
/* {
	HWND result; // eax
	HWND v3; // ebp
	HWND v4; // esi
	int v5; // eax
	int v6; // eax
	int v7; // eax
	int v8; // eax

	result = GetDlgItem(hDlg, nIDDlgItem);
	v3 = result;
	if ( result )
	{
		result = (HWND)GetWindowLongA(result, -21);
		v4 = result;
		if ( result )
		{
			v5 = *((_DWORD *)result + 1);
			if ( v5 )
				SMemFree(v5, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 267, 0);
			v6 = *((_DWORD *)v4 + 4);
			if ( v6 )
				SMemFree(v6, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 269, 0);
			v7 = *((_DWORD *)v4 + 7);
			if ( v7 )
				SMemFree(v7, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 271, 0);
			v8 = *((_DWORD *)v4 + 10);
			if ( v8 )
				SMemFree(v8, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 273, 0);
			SMemFree(v4, "C:\\Src\\Diablo\\DiabloUI\\Sbar.cpp", 275, 0);
			result = (HWND)SetWindowLongA(v3, -21, 0);
		}
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
