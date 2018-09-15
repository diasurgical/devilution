// ref: 0x10004054
void __stdcall UiCopyProtError(int a1) { return; }
//signed int __stdcall UiCopyProtError(int *a1) { return 0; }
/* {
	int v1; // eax
	int v2; // eax
	CHAR Buffer; // [esp+0h] [ebp-80h]

	if ( DiabloUI_10005C2A() )
		LoadStringA(hInstance, 0x3Fu, &Buffer, 127);
	else
		LoadStringA(hInstance, 0x1Bu, &Buffer, 127);
	v1 = SDrawGetFrameWindow();
	v2 = SDlgDialogBoxParam(hInstance, "OKCANCEL_DIALOG", v1, CopyProt_100040AF, &Buffer);
	if ( a1 )
		*a1 = v2;
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x100040AF
int __stdcall CopyProt_100040AF(int a1, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	int v4; // ecx
	int v5; // edx
	HWND v6; // eax
	LONG v7; // eax
	HWND v9; // eax

	if ( Msg == 2 )
	{
		CopyProt_10004173();
		Fade_100072BE(10);
		return SDlgDefDialogProc(a1, Msg, wParam, lParam);
	}
	if ( Msg <= 0x103 )
		return SDlgDefDialogProc(a1, Msg, wParam, lParam);
	if ( Msg <= 0x105 )
	{
		v9 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v9, Msg, wParam, lParam);
		return SDlgDefDialogProc(a1, Msg, wParam, lParam);
	}
	if ( Msg == 272 )
	{
		CopyProt_100041B5((HWND)a1, (const CHAR *)lParam);
		return 1;
	}
	if ( Msg != 273 )
		return SDlgDefDialogProc(a1, Msg, wParam, lParam);
	switch ( (unsigned short)wParam )
	{
		case 1u:
			v6 = GetFocus();
			v7 = GetWindowLongA(v6, -12);
			v4 = a1;
			if ( v7 == 1109 )
			{
				v5 = 1;
				goto LABEL_13;
			}
			goto LABEL_12;
		case 2u:
			v4 = a1;
LABEL_12:
			v5 = 2;
			goto LABEL_13;
		case 0x455u:
			v4 = a1;
			v5 = 1;
LABEL_13:
			CopyProt_1000430C(v4, v5);
			break;
	}
	return SDlgDefDialogProc(a1, Msg, wParam, lParam);
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x10004173
HGLOBAL CopyProt_10004173() { return 0; }
/* {
	HGLOBAL result; // eax

	if ( hResData )
	{
		FreeResource(hResData);
		hResData = 0;
	}
	if ( dword_10029624 )
	{
		FreeResource(dword_10029624);
		dword_10029624 = 0;
	}
	result = dword_10029618;
	if ( dword_10029618 )
	{
		result = (HGLOBAL)FreeResource(dword_10029618);
		dword_10029618 = 0;
	}
	return result;
} */

// ref: 0x100041B5
signed int __fastcall CopyProt_100041B5(HWND a1, const CHAR *a2) { return 0; }
/* {
	HRSRC v2; // eax
	HRSRC v3; // eax
	HRSRC v4; // eax
	LPVOID v5; // edi
	LPVOID v6; // ebx
	HWND v7; // eax
	char v9; // [esp+Ch] [ebp-420h]
	int v10; // [esp+40Ch] [ebp-20h]
	int v11; // [esp+410h] [ebp-1Ch]
	int v12; // [esp+414h] [ebp-18h]
	int v13; // [esp+418h] [ebp-14h]
	int v14; // [esp+41Ch] [ebp-10h]
	LPCSTR lpString; // [esp+420h] [ebp-Ch]
	void *v16; // [esp+424h] [ebp-8h]
	HWND hDlg; // [esp+428h] [ebp-4h]

	v12 = 0;
	lpString = a2;
	hDlg = a1;
	v13 = 112;
	v14 = 140;
	v10 = 1109;
	v11 = 2;
	v2 = FindResourceA(hInstance, "IDR_POPUPART", "ART_FILES");
	dword_10029618 = LoadResource(hInstance, v2);
	v3 = FindResourceA(hInstance, "IDR_BTNART", "ART_FILES");
	dword_10029624 = LoadResource(hInstance, v3);
	v4 = FindResourceA(hInstance, "IDR_ARTPAL", "ART_FILES");
	hResData = LoadResource(hInstance, v4);
	v5 = LockResource(dword_10029618);
	v6 = LockResource(dword_10029624);
	v16 = LockResource(hResData);
	if ( v5 )
		SDlgSetBitmapI(hDlg, 0, &byte_10029448, -1, 1, v5, 0, 284, 148, -1);
	ShowCursor(1);
	Fade_100073EF(hDlg);
	if ( v6 )
		local_10007B1B(hDlg, &v10, (int)v6, &v13);
	if ( v16 )
	{
		memcpy(&v9, v16, 0x400u);
		SDrawUpdatePalette(0, 256, &v9, 1);
	}
	v7 = GetDlgItem(hDlg, 1026);
	SetWindowTextA(v7, lpString);
	return 1;
} */
// 100103FA: using guessed type int __stdcall SDrawUpdatePalette(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000430C
int __fastcall CopyProt_1000430C(int a1, int a2) { return 0; }
/* {
	int v2; // esi
	int v3; // edi

	v2 = a2;
	v3 = a1;
	ShowCursor(0);
	return SDlgEndDialog(v3, v2);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);

// ref: 0x10004329
signed int CopyProt_10004329() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029620 = 2139095040;
	return result;
} */
// 10029620: using guessed type int dword_10029620;
