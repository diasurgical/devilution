// ref: 0x10004339
signed int cr8game_10004339() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002962C = 2139095040;
	return result;
} */
// 1002962C: using guessed type int dword_1002962C;

// ref: 0x10004344
int UNKCALL cr8game_10004344(HWND arg) { return 0; }
/* {
	int result; // eax
	int v2; // eax
	int v3; // ST24_4
	int v4; // ST18_4
	int v5; // ST14_4
	int v6; // ST10_4
	int v7; // eax
	CHAR Buffer; // [esp+Ch] [ebp-308h]
	CHAR Text; // [esp+8Ch] [ebp-288h]
	char v10; // [esp+18Ch] [ebp-188h]
	int v11; // [esp+20Ch] [ebp-108h]
	char v12; // [esp+28Ch] [ebp-88h]
	int v13; // [esp+30Ch] [ebp-8h]
	HWND hWnd; // [esp+310h] [ebp-4h]

	hWnd = arg;
	Connect_10004028((int)&v11, 128, (int)&v12, 128);
	Connect_10003E0C((int)&unk_10029648, (const char *)&v11, &v12, &v10, 128);
	if ( UiAuthCallback(2, (int)&v11, &v12, 0, &v10, &Text, 256) )
	{
		v2 = dword_10029634;
		if ( *(_DWORD *)(dword_10029634 + 32) >= 8u )
		{
			*(_BYTE *)(*(_DWORD *)(dword_10029634 + 28) + 4) = byte_1002964C;
			v2 = dword_10029634;
		}
		v3 = dword_10029644;
		v4 = *(_DWORD *)(dword_10029630 + 8);
		v5 = *(_DWORD *)(v2 + 32);
		v6 = *(_DWORD *)(v2 + 28);
		v7 = Connect_10003D04(&v12);
		v13 = SNetCreateGame(&byte_10029670, &byte_10029690, &v10, v7, v6, v5, v4, &v11, 0, v3);
		if ( !v13 )
		{
			if ( SErrGetLastError() == 183 )
			{
				LoadStringA(hInstance, 0x40Fu, &Buffer, 128);
				sprintf(&Text, &Buffer, &byte_10029670);
			}
			else
			{
				LoadStringA(hInstance, 0x410u, &Text, 256);
			}
			UiMessageBoxCallback(hWnd, &Text, 0, 0x30u);
		}
		result = v13;
	}
	else
	{
		UiMessageBoxCallback(hWnd, &Text, 0, 0x30u);
		result = 0;
	}
	return result;
} */
// 10010406: using guessed type _DWORD __stdcall SErrGetLastError();
// 1001040C: using guessed type int __stdcall SNetCreateGame(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029630: using guessed type int dword_10029630;
// 10029634: using guessed type int dword_10029634;
// 10029644: using guessed type int dword_10029644;
// 1002964C: using guessed type char byte_1002964C;
// 10029690: using guessed type char byte_10029690;

// ref: 0x100044AA
void __cdecl UiCreateGameCallback() { return; }
//int __stdcall UiCreateGameCallback(int a1, int a2, int a3, int a4, int a5, int a6) { return 0; }
/* {
	int v6; // eax

	dword_10029630 = a1;
	dword_10029634 = a2;
	dword_10029638 = a3;
	dword_10029640 = a5;
	dword_1002963C = a4;
	dword_10029644 = a6;
	v6 = SDlgDialogBoxParam(hInstance, "DIALOG_CREATE_GAME", *(_DWORD *)(a4 + 8), cr8game_10004506, 0);
	return v6 != -1 ? v6 : 0;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029630: using guessed type int dword_10029630;
// 10029634: using guessed type int dword_10029634;
// 10029638: using guessed type int dword_10029638;
// 1002963C: using guessed type int dword_1002963C;
// 10029640: using guessed type int dword_10029640;
// 10029644: using guessed type int dword_10029644;

// ref: 0x10004506
HGDIOBJ __stdcall cr8game_10004506(HWND hDlg, UINT Msg, WPARAM wParam, HWND hWnd) { return 0; }
/* {
	UINT v4; // ebx
	HWND v6; // eax
	HWND v7; // eax
	HWND v8; // eax
	CHAR Buffer; // [esp+Ch] [ebp-104h]
	int v10; // [esp+10Ch] [ebp-4h]

	v4 = Msg;
	if ( Msg == 2 )
	{
		cr8game_10004828();
		cr8game_10004914(hDlg);
		if ( dword_10029628 )
			DeleteObject(dword_10029628);
		dword_10029650 = 0;
		::hWnd = 0;
		return (HGDIOBJ)SDlgDefDialogProc(hDlg, v4, wParam, hWnd);
	}
	if ( Msg > 0x103 )
	{
		if ( Msg > 0x105 )
		{
			if ( Msg == 272 )
			{
				::hWnd = GetDlgItem(hDlg, 1010);
				dword_10029650 = GetDlgItem(hDlg, 1011);
				cr8game_1000487F(hDlg);
				cr8game_1000497F(hDlg);
				cr8game_10004A93(hDlg);
				dword_10029628 = cr8game_10004BA8(hDlg);
				SendMessageA(::hWnd, 0xC5u, 0x1Fu, 0);
				SendMessageA(dword_10029650, 0xC5u, 0x1Fu, 0);
				return (HGDIOBJ)1;
			}
			if ( Msg != 273 )
			{
				if ( Msg == 312 && GetWindowLongA(hWnd, -12) == 1030 )
				{
					local_10007C2E((HDC)wParam);
					return GetStockObject(5);
				}
				return (HGDIOBJ)SDlgDefDialogProc(hDlg, v4, wParam, hWnd);
			}
			if ( (unsigned short)wParam == 1 )
			{
				if ( SendMessageA(::hWnd, 0xEu, 0, 0) )
				{
					SendMessageA(::hWnd, 0xDu, 0x20u, (LPARAM)&byte_10029670);
					if ( SelHero_1000BAB4(&byte_10029670)
					  || SelHero_1000BB34(&byte_10029670, (char *)&byte_10029448)
					  || !cr8game_10004B3F(&byte_10029670) )
					{
						LoadStringA(hInstance, 0x404u, &Buffer, 256);
						OkCancel_1000930A((int)hDlg, (int)&Buffer, 1);
						byte_10029670 = 0;
					}
					else
					{
						byte_10029690 = 0;
						if ( SendMessageA(dword_10029650, 0xEu, 0, 0) )
							SendMessageA(dword_10029650, 0xDu, 0x20u, (LPARAM)&byte_10029690);
						byte_1002964C = dword_1002966C;
						TitleSnd_1001031F();
						if ( cr8game_10004344(hDlg) )
							SDlgEndDialog(hDlg, 1);
					}
				}
				else
				{
					LoadStringA(hInstance, 0x3F0u, &Buffer, 256);
					OkCancel_1000930A((int)hDlg, (int)&Buffer, 1);
				}
			}
			else
			{
				if ( (unsigned short)wParam != 2 )
				{
					if ( (signed int)(unsigned short)wParam > 1031 && (signed int)(unsigned short)wParam <= 1034 )
					{
						v10 = (unsigned short)wParam - 1032;
						if ( HIWORD(wParam) == 6 )
							SetFocus(::hWnd);
						if ( dword_1002966C != (unsigned short)wParam - 1032 )
						{
							if ( dword_1002966C != -1 )
							{
								v6 = GetDlgItem(hDlg, dword_1002966C + 1032);
								SendMessageA(v6, 0xF3u, 0, 0);
								TitleSnd_10010315();
							}
							cr8game_10004ABA(hDlg, v10);
							v7 = GetDlgItem(hDlg, 1040);
							cr8game_10004B02(v7, 1029, v10);
							v4 = 273;
							dword_1002966C = v10;
						}
						SendMessageA(hWnd, 0xF3u, 1u, 0);
					}
					return (HGDIOBJ)SDlgDefDialogProc(hDlg, v4, wParam, hWnd);
				}
				TitleSnd_1001031F();
				SDlgEndDialog(hDlg, 0);
			}
			return 0;
		}
		v8 = (HWND)SDrawGetFrameWindow();
		SendMessageA(v8, Msg, wParam, (LPARAM)hWnd);
	}
	return (HGDIOBJ)SDlgDefDialogProc(hDlg, v4, wParam, hWnd);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();
// 1002964C: using guessed type char byte_1002964C;
// 1002966C: using guessed type int dword_1002966C;
// 10029690: using guessed type char byte_10029690;

// ref: 0x10004828
BYTE *cr8game_10004828() { return 0; }
/* {
	int result; // eax

	if ( dword_100296B0 )
	{
		SMemFree(dword_100296B0, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 55, 0);
		dword_100296B0 = 0;
	}
	if ( dword_100296B4 )
	{
		SMemFree(dword_100296B4, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 60, 0);
		dword_100296B4 = 0;
	}
	result = dword_100296B8;
	if ( dword_100296B8 )
	{
		result = SMemFree(dword_100296B8, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 65, 0);
		dword_100296B8 = 0;
	}
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 100296B4: using guessed type int dword_100296B4;
// 100296B8: using guessed type int dword_100296B8;

// ref: 0x1000487F
int UNKCALL cr8game_1000487F(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	int v3; // [esp+8h] [ebp-1Ch]
	int v4; // [esp+Ch] [ebp-18h]
	int v5; // [esp+10h] [ebp-14h]
	int v6; // [esp+14h] [ebp-10h]
	char v7; // [esp+1Ch] [ebp-8h]

	v5 = 0;
	v1 = hWnd;
	v3 = 1;
	v4 = 2;
	local_10007944((int)hWnd, 0, "Dialog", -1, 1, (int)"ui_art\\creat_bg.pcx", &dword_100296B0, &v6, 1);
	local_100078BE((int)"ui_art\\but_xsm.pcx", &dword_100296B4, &v7);
	SDlgSetControlBitmaps(v1, &v3, 0, dword_100296B4, &v7, 1, -1);
	local_100078BE((int)"ui_art\\diffbtns.pcx", &dword_100296B8, &dword_10029660);
	local_10007A85(v1, 1040, dword_100296B0, (int)&v6);
	return 1;
} */
// 10010388: using guessed type int __stdcall SDlgSetControlBitmaps(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029660: using guessed type int dword_10029660;
// 100296B4: using guessed type int dword_100296B4;
// 100296B8: using guessed type int dword_100296B8;

// ref: 0x10004914
void **UNKCALL cr8game_10004914(HWND hDlg) { return 0; }
/* {
	HWND v1; // ebp
	signed int v2; // edi
	HWND v3; // esi
	_DWORD *result; // eax
	_DWORD *v5; // esi
	int v6; // eax
	struct tagRECT Rect; // [esp+10h] [ebp-10h]

	v1 = hDlg;
	v2 = 0;
	do
	{
		v3 = GetDlgItem(v1, v2 + 1032);
		GetClientRect(v3, &Rect);
		result = (_DWORD *)GetWindowLongA(v3, -21);
		v5 = result;
		if ( result )
		{
			v6 = *result;
			if ( *v5 )
				SMemFree(v6, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 160, 0);
			result = (_DWORD *)SMemFree(v5, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 162, 0);
		}
		++v2;
	}
	while ( v2 < 3 );
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000497F
_DWORD *UNKCALL cr8game_1000497F(HWND arg) { return 0; }
/* {
	int v1; // ebx
	_DWORD *v2; // esi
	HWND v3; // ST1C_4
	LONG v4; // eax
	_DWORD *result; // eax
	struct tagRECT Rect; // [esp+Ch] [ebp-18h]
	HWND hDlg; // [esp+1Ch] [ebp-8h]
	HWND hWnd; // [esp+20h] [ebp-4h]

	hDlg = arg;
	v1 = 0;
	do
	{
		hWnd = GetDlgItem(hDlg, v1 + 1032);
		GetClientRect(hWnd, &Rect);
		v2 = (_DWORD *)SMemAlloc(272, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 177, 0);
		*v2 = SMemAlloc(Rect.right * Rect.bottom, "C:\\Src\\Diablo\\DiabloUI\\cr8game.cpp", 178, 0);
		v3 = hWnd;
		v2[1] = Rect.right;
		v4 = Rect.bottom;
		v2[3] = 0;
		v2[2] = v4;
		SetWindowLongA(v3, -21, (LONG)v2);
		SDlgSetBitmapI(hWnd, 0, &byte_10029448, -1, 241, *v2, 0, v2[1], v2[2], -1);
		result = cr8game_10004A34(hWnd, v1++, 0);
	}
	while ( v1 < 3 );
	return result;
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010400: using guessed type int __stdcall SDlgSetBitmapI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10004A34
_DWORD *__fastcall cr8game_10004A34(HWND hWnd, int a2, int a3) { return 0; }
/* {
	HWND v3; // ebp
	int v4; // ebx
	_DWORD *result; // eax

	v3 = hWnd;
	v4 = a2;
	result = (_DWORD *)GetWindowLongA(hWnd, -21);
	if ( result )
	{
		if ( dword_100296B8 )
		{
			SBltROP3(
				*result,
				dword_100296B8 + dword_10029660 * result[2] * (a3 + 2 * v4),
				result[1],
				result[2],
				result[1],
				dword_10029660,
				0,
				13369376);
			result = (_DWORD *)InvalidateRect(v3, 0, 0);
		}
	}
	return result;
} */
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029660: using guessed type int dword_10029660;
// 100296B8: using guessed type int dword_100296B8;

// ref: 0x10004A93
LRESULT UNKCALL cr8game_10004A93(HWND hDlg) { return 0; }
/* {
	dword_1002966C = -1;
	dword_10029658 = 0;
	dword_10029668 = 0;
	return SendDlgItemMessageA(hDlg, 1032, 0xF5u, 0, 0);
} */
// 10029658: using guessed type int dword_10029658;
// 10029668: using guessed type int dword_10029668;
// 1002966C: using guessed type int dword_1002966C;

// ref: 0x10004ABA
_DWORD *__fastcall cr8game_10004ABA(HWND hDlg, int a2) { return 0; }
/* {
	int v2; // edi
	HWND v3; // ebx
	HWND v4; // eax
	HWND v5; // eax

	v2 = a2;
	v3 = hDlg;
	if ( dword_1002966C != -1 )
	{
		v4 = GetDlgItem(hDlg, dword_1002966C + 1032);
		cr8game_10004A34(v4, dword_1002966C, 0);
	}
	v5 = GetDlgItem(v3, v2 + 1032);
	return cr8game_10004A34(v5, v2, 1);
} */
// 1002966C: using guessed type int dword_1002966C;

// ref: 0x10004B02
BOOL __fastcall cr8game_10004B02(HWND hWnd, int a2, int a3) { return 0; }
/* {
	HWND v3; // esi
	CHAR Buffer; // [esp+4h] [ebp-100h]

	v3 = hWnd;
	LoadStringA(hInstance, a3 + a2, &Buffer, 256);
	return SetWindowTextA(v3, &Buffer);
} */

// ref: 0x10004B3F
int UNKCALL cr8game_10004B3F(char *arg) { return 0; }
/* {
	signed int v1; // edi
	char v2; // al
	signed int v3; // esi
	int result; // eax
	char v5; // [esp+8h] [ebp-24h]
	char v6[31]; // [esp+9h] [ebp-23h]
	char *v7; // [esp+28h] [ebp-4h]

	v7 = arg;
	strcpy(&v5, arg);
	v1 = 0;
	if ( v5 == 32 )
	{
		v2 = 32;
		while ( v2 )
		{
			v2 = v6[v1++];
			if ( v2 != 32 )
				goto LABEL_5;
		}
LABEL_9:
		result = 0;
	}
	else
	{
LABEL_5:
		v3 = strlen(&v5);
		while ( *(&v5 + --v3) == 32 )
		{
			if ( v3 <= v1 )
				goto LABEL_9;
		}
		v6[v3] = 0;
		strcpy(v7, &v5 + v1);
		result = v3 + 1 - v1;
	}
	return result;
} */
// 10004B3F: using guessed type char var_23[31];

// ref: 0x10004BA8
HFONT UNKCALL cr8game_10004BA8(HWND hWnd) { return 0; }
/* {
	HFONT v1; // edi
	HFONT v2; // eax
	int pv; // [esp+8h] [ebp-40h]
	int v5; // [esp+Ch] [ebp-3Ch]
	HWND hDlg; // [esp+44h] [ebp-4h]

	hDlg = hWnd;
	v1 = (HFONT)SendMessageA(hWnd, 0x31u, 0, 0);
	if ( v1 )
	{
		if ( GetObjectA(v1, 60, &pv) )
		{
			pv = -MulDiv(12, 96, 72);
			v5 = 0;
			v2 = CreateFontIndirectA((const LOGFONTA *)&pv);
			v1 = v2;
			if ( v2 )
			{
				SendDlgItemMessageA(hDlg, 1032, 0x30u, (WPARAM)v2, 0);
				SendDlgItemMessageA(hDlg, 1033, 0x30u, (WPARAM)v1, 0);
				SendDlgItemMessageA(hDlg, 1034, 0x30u, (WPARAM)v1, 0);
			}
		}
	}
	return v1;
} */
