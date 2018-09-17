// ref: 0x1000722B
int __fastcall Fade_1000722B(int a1, int a2) { return 0; }
/* {
	int v2; // ebx
	int v3; // edi
	char *v4; // eax
	char *v5; // ecx
	BYTE *v6; // esi
	BYTE v7; // al

	v2 = a1;
	v3 = a2;
	v4 = local_10007895(0);
	v5 = v4;
	if ( v2 == v3 )
	{
		memcpy(&pPalEntries, v4, 0x400u);
	}
	else if ( v3 )
	{
		v6 = &pPalEntries.peGreen;
		do
		{
			v7 = v3 * (unsigned char)*v5 / v2;
			v5 += 4;
			*(v6 - 1) = v7;
			*v6 = v3 * (unsigned char)*(v5 - 3) / v2;
			v6 += 4;
			*(v6 - 3) = v3 * (unsigned char)*(v5 - 2) / v2;
		}
		while ( (signed int)v6 < (signed int)&dword_10029C70 + 1 );
	}
	else
	{
		memcpy(&pPalEntries, v4, 0x400u);
		local_1000789D((char *)&pPalEntries);
	}
	return SDrawUpdatePalette(0, 256, &pPalEntries, 1);
} */
// 100103FA: using guessed type int __stdcall SDrawUpdatePalette(_DWORD, _DWORD, _DWORD, _DWORD);
// 10029C70: using guessed type int dword_10029C70;

// ref: 0x100072BE
int __fastcall Fade_100072BE(int a1) { return 0; }
/* {
	int v1; // ebx
	char *v2; // eax
	char *v3; // edi
	BYTE *v4; // ecx
	char v5; // al
	HPALETTE v6; // ebx
	int v8; // [esp+10h] [ebp-4h]

	v1 = a1;
	v2 = local_10007895(0);
	memcpy(&pPalEntries, v2, 0x400u);
	if ( v1 > 0 )
	{
		v8 = v1;
		do
		{
			v3 = local_10007895(0);
			v4 = &pPalEntries.peGreen;
			do
			{
				v5 = (unsigned char)*v3 / v1;
				v3 += 4;
				*(v4 - 1) -= v5;
				*v4 -= (unsigned char)*(v3 - 3) / v1;
				v4 += 4;
				*(v4 - 3) -= (unsigned char)*(v3 - 2) / v1;
			}
			while ( (signed int)v4 < (signed int)&dword_10029C70 + 1 );
			SDrawUpdatePalette(0, 256, &pPalEntries, 1);
			--v8;
		}
		while ( v8 );
	}
	local_1000789D((char *)&pPalEntries);
	SDrawUpdatePalette(0, 256, &pPalEntries, 1);
	local_1000811B();
	SDrawClearSurface();
	v6 = (HPALETTE)GetStockObject(15);
	GetPaletteEntries(v6, 0, 0xAu, &pPalEntries);
	GetPaletteEntries(v6, 0xAu, 0xAu, &stru_10029C48);
	return SDrawUpdatePalette(0, 256, &pPalEntries, 1);
} */
// 100103FA: using guessed type int __stdcall SDrawUpdatePalette(_DWORD, _DWORD, _DWORD, _DWORD);
// 1001043C: using guessed type _DWORD __stdcall SDrawClearSurface();
// 10029C70: using guessed type int dword_10029C70;

// ref: 0x1000739F
signed int Fade_1000739F() { return 0; }
/* {
	signed int result; // eax

	result = 0;
	if ( dword_10029C70 )
	{
		if ( dword_1002986C <= 5 )
			result = 1;
	}
	return result;
} */
// 1002986C: using guessed type int dword_1002986C;
// 10029C70: using guessed type int dword_10029C70;

// ref: 0x100073B4
signed int Fade_100073B4() { return 0; }
/* {
	signed int result; // eax

	result = Fade_1000739F();
	if ( result )
		dword_10029C70 = 0;
	return result;
} */
// 10029C70: using guessed type int dword_10029C70;

// ref: 0x100073C5
void __fastcall Fade_100073C5(HWND hWnd, int a2) { return; }
/* {
	int v2; // esi
	HWND v3; // eax
	int result; // eax

	v2 = a2;
	v3 = GetParent(hWnd);
	result = local_10007F04(v3);
	if ( v2 )
		result = local_100080F1();
	dword_10029C70 = 0;
	dword_1002986C = 0;
	return result;
} */
// 1002986C: using guessed type int dword_1002986C;
// 10029C70: using guessed type int dword_10029C70;

// ref: 0x100073EF
BOOL UNKCALL Fade_100073EF(HWND hWnd) { return 0; }
/* {
	HWND v1; // eax

	v1 = GetParent(hWnd);
	return local_10007F04(v1);
} */

// ref: 0x100073FD
int UNKCALL Fade_100073FD(void *arg, int a2) { return 0; }
/* {
	int result; // eax

	if ( !dword_10029C70 )
	{
		result = SDlgSetTimer(arg, 16, 50, Fade_10007420);
		dword_10029C70 = 1;
	}
	return result;
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);
// 10029C70: using guessed type int dword_10029C70;

// ref: 0x10007420
int __stdcall Fade_10007420(int a1, int a2, int a3, int a4) { return 0; }
/* {
	int result; // eax

	if ( dword_1002986C > 5 )
		return SDlgKillTimer(a1, 16);
	result = Fade_1000722B(5, dword_1002986C);
	++dword_1002986C;
	return result;
} */
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);
// 1002986C: using guessed type int dword_1002986C;

// ref: 0x1000744D
signed int Fade_1000744D() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029868 = 2139095040;
	return result;
} */
// 10029868: using guessed type int dword_10029868;
