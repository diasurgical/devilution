// ref: 0x10007825
LOGPALETTE *local_10007825() { return 0; }
/* {
	LOGPALETTE *result; // eax
	const LOGPALETTE *v1; // esi
	int v2; // eax
	signed int v3; // ecx

	result = (LOGPALETTE *)SMemAlloc(1028, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 27, 0);
	v1 = result;
	if ( result )
	{
		result->palVersion = 768;
		result->palNumEntries = 256;
		v2 = (int)result->palPalEntry;
		v3 = 0;
		do
		{
			*(_DWORD *)v2 = v3;
			*(_BYTE *)(v2 + 3) = 2;
			++v3;
			v2 += 4;
		}
		while ( v3 < 256 );
		dword_1002A0C8 = CreatePalette(v1);
		result = (LOGPALETTE *)SMemFree(v1, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 41, 0);
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000787D
HGDIOBJ local_1000787D() { return 0; }
/* {
	HGDIOBJ result; // eax

	result = dword_1002A0C8;
	if ( dword_1002A0C8 )
	{
		result = (HGDIOBJ)DeleteObject(dword_1002A0C8);
		dword_1002A0C8 = 0;
	}
	return result;
} */

// ref: 0x10007895
char *__fastcall local_10007895(int a1) { return 0; }
/* {
	return (char *)&unk_10029CC8 + 4 * a1;
} */

// ref: 0x1000789D
_BYTE *UNKCALL local_1000789D(char *arg) { return 0; }
/* {
	_BYTE *result; // eax
	signed int v2; // ecx

	result = arg + 2;
	v2 = 256;
	do
	{
		*(result - 2) = 0;
		*(result - 1) = 0;
		*result = 0;
		result += 4;
		--v2;
	}
	while ( v2 );
	return result;
} */

// ref: 0x100078B6
int local_100078B6() { return 0; }
/* {
	return SDrawClearSurface();
} */
// 1001043C: using guessed type _DWORD __stdcall SDrawClearSurface();

// ref: 0x100078BE
signed int __fastcall local_100078BE(int a1, int *a2, _DWORD *a3) { return 0; }
/* {
	int *v3; // edi
	int v4; // eax
	int v5; // ecx
	int v7; // [esp+Ch] [ebp-Ch]
	int v8; // [esp+10h] [ebp-8h]
	int v9; // [esp+14h] [ebp-4h]

	v3 = a2;
	v7 = a1;
	*a2 = 0;
	if ( !SBmpLoadImage(a1, 0, 0, 0, &v9, &v8, 0) )
		return 0;
	v4 = SMemAlloc(v8 * v9, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 93, 0);
	v5 = v9;
	*v3 = v4;
	if ( !SBmpLoadImage(v7, 0, v4, v8 * v5, 0, 0, 0) )
	{
		SMemFree(*v3, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 95, 0);
		*v3 = 0;
		return 0;
	}
	if ( a3 )
	{
		*a3 = v9;
		a3[1] = v8;
	}
	return 1;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 100103BE: using guessed type int __stdcall SBmpLoadImage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007944
signed int __fastcall local_10007944(int a1, int a2, _BYTE *a3, int a4, int a5, int a6, int *a7, _DWORD *a8, int a9) { return 0; }
/* {
	int v9; // edi
	int v10; // eax
	int v11; // ST18_4
	HPALETTE v13; // edi
	struct tagPALETTEENTRY pPalEntries; // [esp+Ch] [ebp-40Ch]
	struct tagPALETTEENTRY v15; // [esp+3E4h] [ebp-34h]
	int v16; // [esp+40Ch] [ebp-Ch]
	int v17; // [esp+410h] [ebp-8h]
	int v18; // [esp+414h] [ebp-4h]

	v9 = a2;
	v16 = a1;
	if ( !SBmpLoadImage(a6, 0, 0, 0, &v17, &v18, 0) )
		return 0;
	v10 = SMemAlloc(v18 * v17, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 129, 0);
	v11 = v18 * v17;
	*a7 = v10;
	if ( !SBmpLoadImage(a6, &pPalEntries, v10, v11, 0, 0, 0)
	  || !SDlgSetBitmapI(v16, v9, a3, a4, a5, *a7, 0, v17, v18, -1) )
	{
		return 0;
	}
	if ( !a3 || !*a3 )
	{
		v13 = (HPALETTE)GetStockObject(15);
		GetPaletteEntries(v13, 0, 0xAu, &pPalEntries);
		GetPaletteEntries(v13, 0xAu, 0xAu, &v15);
		memcpy(&unk_10029CC8, &pPalEntries, 0x400u);
		if ( a9 )
		{
			SDrawUpdatePalette(0, 255, &unk_10029CC8, 1);
		}
		else
		{
			local_1000789D((char *)&pPalEntries);
			SDrawUpdatePalette(0, 256, &pPalEntries, 1);
		}
	}
	if ( a8 )
	{
		*a8 = v17;
		a8[1] = v18;
	}
	return 1;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 100103BE: using guessed type int __stdcall SBmpLoadImage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100103FA: using guessed type int __stdcall SDrawUpdatePalette(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007A68
int __fastcall local_10007A68(_DWORD *a1, int a2, int a3) { return 0; }
/* {
	int v3; // eax
	int result; // eax
	int v5; // edx

	v3 = a2 - *a1;
	*a1 = a2;
	a1[2] += v3 - 1;
	result = a3;
	v5 = a3 - a1[1];
	a1[1] = a3;
	a1[3] += v5 - 1;
	return result;
} */

// ref: 0x10007A85
int __fastcall local_10007A85(HWND hWnd, int nIDDlgItem, int a3, int a4) { return 0; }
/* {
	HWND v4; // edi
	HWND v5; // ebx
	struct tagRECT Rect; // [esp+Ch] [ebp-10h]

	v4 = hWnd;
	v5 = GetDlgItem(hWnd, nIDDlgItem);
	GetWindowRect(v5, &Rect);
	ScreenToClient(v4, (LPPOINT)&Rect);
	ScreenToClient(v4, (LPPOINT)&Rect.right);
	SDlgSetBitmapI(v5, 0, "Static", -1, 1, a3, &Rect, *(_DWORD *)a4, *(_DWORD *)(a4 + 4), -1);
	return 1;
} */
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007AEA
signed int local_10007AEA() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029CB8 = 2139095040;
	return result;
} */
// 10029CB8: using guessed type int dword_10029CB8;

// ref: 0x10007AF5
int __fastcall local_10007AF5(int a1, int a2, int a3, int a4, _DWORD *a5) { return 0; }
/* {
	return SDlgSetBitmapI(a1, 0, "Button", -1, a2, a4, a3, *a5, a5[1], -1);
} */
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007B1B
int __fastcall local_10007B1B(HWND a1, int *a2, int a3, _DWORD *a4) { return 0; }
/* {
	int result; // eax
	HWND v5; // esi
	struct tagRECT Rect; // [esp+0h] [ebp-1Ch]
	HWND hDlg; // [esp+10h] [ebp-Ch]
	int v8; // [esp+14h] [ebp-8h]
	int *v9; // [esp+18h] [ebp-4h]

	result = *a2;
	v8 = 0;
	v9 = a2;
	hDlg = a1;
	if ( result )
	{
		do
		{
			v5 = GetDlgItem(hDlg, result);
			if ( v5 )
			{
				GetClientRect(v5, &Rect);
				local_10007A68(&Rect, 0, v8);
				local_10007AF5((int)v5, 16, (int)&Rect, a3, a4);
				++Rect.bottom;
				++Rect.right;
				local_10007A68(&Rect, 0, Rect.bottom);
				local_10007AF5((int)v5, 64, (int)&Rect, a3, a4);
				++Rect.bottom;
				++Rect.right;
				local_10007A68(&Rect, 0, Rect.bottom);
				local_10007AF5((int)v5, 32, (int)&Rect, a3, a4);
				++Rect.bottom;
				++Rect.right;
				local_10007A68(&Rect, 0, Rect.bottom);
				local_10007AF5((int)v5, 128, (int)&Rect, a3, a4);
				++Rect.bottom;
				++Rect.right;
				local_10007A68(&Rect, 0, Rect.bottom);
				local_10007AF5((int)v5, 1280, (int)&Rect, a3, a4);
				++Rect.bottom;
				++Rect.right;
				v8 = Rect.bottom;
			}
			++v9;
			result = *v9;
		}
		while ( *v9 );
	}
	return result;
} */

// ref: 0x10007C2E
COLORREF UNKCALL local_10007C2E(HDC hdc) { return 0; }
/* {
	return SetTextColor(hdc, 0xFFFFu);
} */

// ref: 0x10007C3B
BOOL __fastcall local_10007C3B(HWND hWnd, HWND a2, int a3, int a4) { return 0; }
/* {
	HWND v4; // edi
	BOOL result; // eax
	struct tagRECT Rect; // [esp+4h] [ebp-10h]

	v4 = hWnd;
	if ( hWnd
	  && a2
	  && (GetWindowRect(a2, &Rect),
		  ScreenToClient(v4, (LPPOINT)&Rect),
		  ScreenToClient(v4, (LPPOINT)&Rect.right),
		  a3 >= Rect.left)
	  && a3 < Rect.right
	  && a4 >= Rect.top )
	{
		result = a4 < Rect.bottom;
	}
	else
	{
		result = 0;
	}
	return result;
} */

// ref: 0x10007C95
int UNKCALL local_10007C95(void *arg) { return 0; }
/* {
	void *v1; // esi
	char v3; // [esp+4h] [ebp-40h]

	v1 = arg;
	SDlgBeginPaint(arg, &v3);
	return SDlgEndPaint(v1, &v3);
} */
// 10010442: using guessed type int __stdcall SDlgEndPaint(_DWORD, _DWORD);
// 10010448: using guessed type int __stdcall SDlgBeginPaint(_DWORD, _DWORD);

// ref: 0x10007CB5
int __fastcall local_10007CB5(HWND hDlg, int *a2) { return 0; }
/* {
	int *v2; // edi
	HWND v3; // ebx
	int result; // eax
	HWND v5; // eax
	HWND v6; // esi
	void *v7; // eax

	v2 = a2;
	v3 = hDlg;
	for ( result = *a2; *v2; result = *v2 )
	{
		v5 = GetDlgItem(v3, result);
		v6 = v5;
		if ( v5 )
		{
			v7 = (void *)GetWindowLongA(v5, -4);
			SetPropA(v6, "UIWNDPROC", v7);
			SetWindowLongA(v6, -4, (LONG)local_10007D01);
		}
		++v2;
	}
	return result;
} */

// ref: 0x10007D01
LRESULT __stdcall local_10007D01(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	LRESULT (__stdcall *v4)(HWND, UINT, WPARAM, LPARAM); // ebx
	HWND v5; // eax
	HWND v6; // eax
	HWND v7; // eax
	WPARAM v9; // [esp-8h] [ebp-14h]
	BOOL v10; // [esp-4h] [ebp-10h]

	v4 = (LRESULT (__stdcall *)(HWND, UINT, WPARAM, LPARAM))GetPropA(hWnd, "UIWNDPROC");
	switch ( Msg )
	{
		case 2u:
			RemovePropA(hWnd, "UIWNDPROC");
			if ( !v4 )
				return DefWindowProcA(hWnd, Msg, wParam, lParam);
			SetWindowLongA(hWnd, -4, (LONG)v4);
			goto LABEL_21;
		case 0xFu:
			local_10007C95(hWnd);
			return 0;
		case 0x87u:
			return 4;
	}
	if ( Msg != 256 )
		goto LABEL_21;
	switch ( wParam )
	{
		case 0xDu:
			goto LABEL_26;
		case 0x1Bu:
			v9 = 2;
LABEL_15:
			v7 = GetParent(hWnd);
			SendMessageA(v7, 0x111u, v9, 0);
			goto LABEL_21;
		case 0x20u:
LABEL_26:
			v9 = 1;
			goto LABEL_15;
	}
	if ( wParam <= 0x24 )
		goto LABEL_21;
	if ( wParam <= 0x26 )
	{
		v10 = 1;
	}
	else
	{
		if ( wParam > 0x28 )
			goto LABEL_21;
		v10 = 0;
	}
	v5 = GetParent(hWnd);
	v6 = GetNextDlgGroupItem(v5, hWnd, v10);
	SetFocus(v6);
LABEL_21:
	if ( v4 )
		return CallWindowProcA(v4, hWnd, Msg, wParam, lParam);
	return DefWindowProcA(hWnd, Msg, wParam, lParam);
} */

// ref: 0x10007DE9
int __fastcall local_10007DE9(HWND hDlg, int *a2) { return 0; }
/* {
	int *v2; // edi
	HWND v3; // ebx
	int result; // eax
	HWND v5; // eax
	HWND v6; // esi
	void *v7; // eax

	v2 = a2;
	v3 = hDlg;
	for ( result = *a2; *v2; result = *v2 )
	{
		v5 = GetDlgItem(v3, result);
		v6 = v5;
		if ( v5 )
		{
			v7 = (void *)GetWindowLongA(v5, -4);
			SetPropA(v6, "UIWNDPROC", v7);
			SetWindowLongA(v6, -4, (LONG)local_10007E35);
		}
		++v2;
	}
	return result;
} */

// ref: 0x10007E35
LRESULT __stdcall local_10007E35(HWND hWnd, HWND a2, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	LRESULT (__stdcall *v4)(HWND, UINT, WPARAM, LPARAM); // ebx
	WPARAM v5; // ST0C_4
	HWND v6; // eax
	HWND v8; // [esp+18h] [ebp+Ch]

	v4 = (LRESULT (__stdcall *)(HWND, UINT, WPARAM, LPARAM))GetPropA(hWnd, "UIWNDPROC");
	if ( a2 == (HWND)2 )
	{
		RemovePropA(hWnd, "UIWNDPROC");
		if ( !v4 )
			return DefWindowProcA(hWnd, (UINT)a2, wParam, lParam);
		SetWindowLongA(hWnd, -4, (LONG)v4);
	}
	else
	{
		if ( a2 == (HWND)15 )
		{
			local_10007C95(hWnd);
			return 0;
		}
		if ( (HWND)((char *)a2 - 15) == (HWND)498 )
		{
			v8 = GetFocus();
			SetFocus(hWnd);
			InvalidateRect(v8, 0, 0);
			InvalidateRect(hWnd, 0, 0);
			UpdateWindow(v8);
			UpdateWindow(hWnd);
			v5 = (unsigned short)GetWindowLongA(hWnd, -12);
			v6 = GetParent(hWnd);
			PostMessageA(v6, 0x111u, v5, (LPARAM)hWnd);
			return 0;
		}
	}
	if ( v4 )
		return CallWindowProcA(v4, hWnd, (UINT)a2, wParam, lParam);
	return DefWindowProcA(hWnd, (UINT)a2, wParam, lParam);
} */

// ref: 0x10007F04
BOOL UNKCALL local_10007F04(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	BOOL result; // eax
	struct tagMSG Msg; // [esp+8h] [ebp-1Ch]

	v1 = hWnd;
	do
	{
		while ( PeekMessageA(&Msg, v1, 0x100u, 0x108u, 1u) )
			;
		result = PeekMessageA(&Msg, v1, 0x200u, 0x209u, 1u);
	}
	while ( result );
	return result;
} */

// ref: 0x10007F46
int local_10007F46() { return 0; }
/* {
	int result; // eax

	result = SMemAlloc(272, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 480, 0);
	if ( result )
	{
		*(_DWORD *)result = 0;
		*(_DWORD *)(result + 4) = 0;
		*(_DWORD *)(result + 8) = 0;
		*(_DWORD *)(result + 12) = 0;
		*(_BYTE *)(result + 16) = 0;
	}
	return result;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007F72
void UNKCALL local_10007F72(_DWORD *arg) { return; }
/* {
	_DWORD *v1; // esi

	v1 = arg;
	if ( arg )
	{
		if ( *arg )
			SMemFree(*arg, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 498, 0);
		SMemFree(v1, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 499, 0);
	}
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007FA4
char *__fastcall local_10007FA4(int a1, const char *a2) { return 0; }
/* {
	int v2; // esi
	char *result; // eax

	v2 = a1;
	if ( a1 )
	{
		if ( a2 )
		{
			result = strncpy((char *)(a1 + 16), a2, 0xFFu);
			*(_BYTE *)(v2 + 271) = 0;
		}
		else
		{
			*(_BYTE *)(a1 + 16) = 0;
		}
	}
	return result;
} */

// ref: 0x10007FD0
_BYTE *local_10007FD0() { return 0; }
/* {
	_BYTE *result; // eax
	int v1; // [esp+8h] [ebp-8h]
	int v2; // [esp+Ch] [ebp-4h]

	result = (_BYTE *)SBmpLoadImage("ui_art\\cursor.pcx", 0, 0, 0, &v2, &v1, 0);
	if ( result )
	{
		dword_1002A0CC = SMemAlloc(v1 * v2, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 553, 0);
		dword_1002A0D0 = SMemAlloc(v1 * v2, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 554, 0);
		result = (_BYTE *)SBmpLoadImage("ui_art\\cursor.pcx", 0, dword_1002A0CC, v1 * v2, 0, 0, 0);
		if ( result )
		{
			dword_10029CC0 = v2;
			dword_10029CC4 = v1;
			result = local_10008062();
		}
	}
	return result;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 100103BE: using guessed type int __stdcall SBmpLoadImage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029CC0: using guessed type int dword_10029CC0;
// 10029CC4: using guessed type int dword_10029CC4;
// 1002A0CC: using guessed type int dword_1002A0CC;
// 1002A0D0: using guessed type int dword_1002A0D0;

// ref: 0x10008062
_BYTE *local_10008062() { return 0; }
/* {
	_BYTE *result; // eax
	char *v1; // ecx
	int i; // esi
	char v3; // dl

	result = (_BYTE *)dword_1002A0D0;
	v1 = (char *)dword_1002A0CC;
	if ( dword_1002A0D0 )
	{
		if ( dword_1002A0CC )
		{
			for ( i = 0; i < dword_10029CC0 * dword_10029CC4; ++i )
			{
				v3 = *v1++;
				if ( v3 )
					*result = 0;
				else
					*result = -1;
				++result;
			}
		}
	}
	return result;
} */
// 10029CC0: using guessed type int dword_10029CC0;
// 10029CC4: using guessed type int dword_10029CC4;
// 1002A0CC: using guessed type int dword_1002A0CC;
// 1002A0D0: using guessed type int dword_1002A0D0;

// ref: 0x100080AD
int local_100080AD() { return 0; }
/* {
	int result; // eax

	if ( dword_1002A0CC )
	{
		SMemFree(dword_1002A0CC, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 571, 0);
		dword_1002A0CC = 0;
	}
	result = dword_1002A0D0;
	if ( dword_1002A0D0 )
	{
		result = SMemFree(dword_1002A0D0, "C:\\Src\\Diablo\\DiabloUI\\local.cpp", 575, 0);
		dword_1002A0D0 = 0;
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 1002A0CC: using guessed type int dword_1002A0CC;
// 1002A0D0: using guessed type int dword_1002A0D0;

// ref: 0x100080F1
int local_100080F1() { return 0; }
/* {
	if ( !dword_1002A0CC )
		local_10007FD0();
	return SDlgSetSystemCursor(dword_1002A0D0, dword_1002A0CC, &dword_10029CC0, 32512);
} */
// 1001044E: using guessed type int __stdcall SDlgSetSystemCursor(_DWORD, _DWORD, _DWORD, _DWORD);
// 10029CC0: using guessed type int dword_10029CC0;
// 1002A0CC: using guessed type int dword_1002A0CC;
// 1002A0D0: using guessed type int dword_1002A0D0;

// ref: 0x1000811B
int local_1000811B() { return 0; }
/* {
	return SDlgSetSystemCursor(0, 0, 0, 32512);
} */
// 1001044E: using guessed type int __stdcall SDlgSetSystemCursor(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000812B
int UNKCALL local_1000812B(void *arg) { return 0; }
/* {
	void *v1; // esi
	HCURSOR v2; // eax
	int v4; // [esp+4h] [ebp-4h]

	v4 = 0;
	v1 = arg;
	local_1000811B();
	v2 = LoadCursorA(hInstance, "DIABLOCURSOR");
	return SDlgSetCursor(v1, v2, 32512, &v4);
} */
// 10010454: using guessed type int __stdcall SDlgSetCursor(_DWORD, _DWORD, _DWORD, _DWORD);
