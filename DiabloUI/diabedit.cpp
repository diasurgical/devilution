// ref: 0x10005765
BOOL UNKCALL DiabEdit_10005765(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	struct tagPAINTSTRUCT Paint; // [esp+4h] [ebp-40h]

	v1 = hWnd;
	BeginPaint(hWnd, &Paint);
	SDlgDrawBitmap(v1, 1, 0, 0, 0, 0, 0);
	return EndPaint(v1, &Paint);
} */
// 1001042A: using guessed type int __stdcall SDlgDrawBitmap(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x1000579B
signed int DiabEdit_1000579B() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002970C = 2139095040;
	return result;
} */
// 1002970C: using guessed type int dword_1002970C;

// ref: 0x100057A6
ATOM DiabEdit_100057A6() { return 0; }
/* {
	WNDCLASSA WndClass; // [esp+0h] [ebp-28h]

	memset(&WndClass, 0, 0x28u);
	WndClass.style = 64;
	WndClass.lpfnWndProc = (WNDPROC)DiabEdit_100057E8;
	WndClass.hInstance = GetModuleHandleA(0);
	WndClass.lpszClassName = "DIABLOEDIT";
	return RegisterClassA(&WndClass);
} */

// ref: 0x100057E8
HANDLE __stdcall DiabEdit_100057E8(HWND hWnd, UINT Msg, HANDLE hData, LPARAM lParam) { return 0; }
/* {
	if ( Msg <= 0x113 )
	{
		if ( Msg == 275 )
		{
			DiabEdit_1000594E((LPARAM)hWnd);
			return 0;
		}
		if ( Msg == 1 )
		{
			DiabEdit_10005B9F(hWnd);
		}
		else if ( Msg == 2 )
		{
			DiabEdit_10005BE7(hWnd);
		}
		else
		{
			if ( Msg != 7 )
			{
				if ( Msg == 15 )
				{
					DiabEdit_10005765(hWnd);
				}
				else
				{
					if ( Msg == 135 )
						return (HANDLE)129;
					if ( Msg != 256 )
					{
						if ( Msg == 258 )
							DiabEdit_10005A0A(hWnd, (unsigned char)hData, lParam);
						return (HANDLE)DefWindowProcA(hWnd, Msg, (WPARAM)hData, lParam);
					}
					DiabEdit_10005AF4((LPARAM)hWnd, (int)hData, lParam);
				}
				return 0;
			}
			DiabEdit_1000591C((LPARAM)hWnd, 1u);
		}
		return (HANDLE)DefWindowProcA(hWnd, Msg, (WPARAM)hData, lParam);
	}
	switch ( Msg )
	{
		case 0x201u:
			SetFocus(hWnd);
			return (HANDLE)DefWindowProcA(hWnd, Msg, (WPARAM)hData, lParam);
		case 0x400u:
			SetWindowTextA(hWnd, &byte_10029448);
			DiabEdit_1000591C((LPARAM)hWnd, 3u);
			return 0;
		case 0x401u:
			SetPropA(hWnd, "LIMIT", hData);
			return 0;
		case 0x402u:
			return GetPropA(hWnd, "LIMIT");
	}
	if ( Msg != 1027 )
	{
		if ( Msg == 1028 )
		{
			DiabEdit_10005B70(hWnd, (char *)lParam);
			return 0;
		}
		return (HANDLE)DefWindowProcA(hWnd, Msg, (WPARAM)hData, lParam);
	}
	return GetPropA(hWnd, "CURSOR");
} */

// ref: 0x1000591C
LRESULT __fastcall DiabEdit_1000591C(LPARAM lParam, unsigned short a2) { return 0; }
/* {
	HWND v2; // esi
	LPARAM v3; // ST0C_4
	int v4; // ST08_4
	HWND v5; // eax

	v2 = (HWND)lParam;
	v3 = lParam;
	v4 = (a2 << 16) | (unsigned short)GetWindowLongA((HWND)lParam, -12);
	v5 = GetParent(v2);
	return SendMessageA(v5, 0x111u, v4, v3);
} */

// ref: 0x1000594E
LRESULT UNKCALL DiabEdit_1000594E(LPARAM lParam) { return 0; }
/* {
	HWND v1; // ebx
	LRESULT result; // eax
	size_t v3; // eax
	CHAR *v4; // esi
	CHAR String; // [esp+Ch] [ebp-100h]
	char v6[252]; // [esp+Dh] [ebp-FFh]
	short v7; // [esp+109h] [ebp-3h]
	char v8; // [esp+10Bh] [ebp-1h]

	v1 = (HWND)lParam;
	String = byte_10029448;
	memset(v6, 0, sizeof(v6));
	v7 = 0;
	v8 = 0;
	if ( GetPropA((HWND)lParam, "CURSOR") )
	{
		SetPropA(v1, "CURSOR", 0);
		result = DiabEdit_1000591C((LPARAM)v1, 3u);
	}
	else
	{
		SetPropA(v1, "CURSOR", HANDLE_FLAG_INHERIT);
		GetWindowTextA(v1, &String, 255);
		HIBYTE(v7) = 0;
		v3 = strlen(&String);
		v6[v3] = 0;
		v4 = &String + v3;
		*(&String + v3) = 124;
		SetWindowTextA(v1, &String);
		DiabEdit_1000591C((LPARAM)v1, 3u);
		*v4 = 0;
		result = SetWindowTextA(v1, &String);
	}
	return result;
} */
// 1000594E: using guessed type char var_FF[252];

// ref: 0x10005A0A
char *__fastcall DiabEdit_10005A0A(HWND a1, unsigned char a2, int a3) { return 0; }
/* {
	char *result; // eax
	unsigned char v4; // bl
	char v5; // cl
	signed int v6; // eax
	signed int v7; // esi
	char v8; // [esp+7h] [ebp-105h]
	CHAR String; // [esp+8h] [ebp-104h]
	char v10[252]; // [esp+9h] [ebp-103h]
	short v11; // [esp+105h] [ebp-7h]
	char v12; // [esp+107h] [ebp-5h]
	HWND hWnd; // [esp+108h] [ebp-4h]

	hWnd = a1;
	String = byte_10029448;
	result = 0;
	v4 = a2;
	memset(v10, 0, sizeof(v10));
	v11 = 0;
	v12 = 0;
	if ( a2 == 8 )
		goto LABEL_9;
	if ( a2 < 0x20u || a2 > 0x7Eu && a2 < 0xC0u )
		return result;
	result = (char *)GetPropA(hWnd, "RESTRICTED");
	if ( !result || (v5 = *result) == 0 )
	{
LABEL_9:
		GetWindowTextA(hWnd, &String, 255);
		HIBYTE(v11) = 0;
		v6 = strlen(&String);
		v7 = v6;
		if ( v4 == 8 )
		{
			if ( v6 )
			{
				*(&v8 + v6) = 0;
				goto LABEL_14;
			}
		}
		else if ( v6 < (signed int)GetPropA(hWnd, "LIMIT") )
		{
			*(&String + v7) = v4;
			v10[v7] = 0;
LABEL_14:
			SetWindowTextA(hWnd, &String);
			return (char *)DiabEdit_1000594E((LPARAM)hWnd);
		}
		return (char *)DiabEdit_1000594E((LPARAM)hWnd);
	}
	while ( v4 != v5 )
	{
		v5 = *++result;
		if ( !*result )
			goto LABEL_9;
	}
	return result;
} */
// 10005A0A: using guessed type char var_103[252];

// ref: 0x10005AF4
int __fastcall DiabEdit_10005AF4(LPARAM lParam, int a2, int a3) { return 0; }
/* {
	HWND v3; // esi
	int v4; // ebx
	int result; // eax
	char v6; // [esp+Bh] [ebp-101h]
	CHAR String; // [esp+Ch] [ebp-100h]
	char v8; // [esp+Dh] [ebp-FFh]
	short v9; // [esp+109h] [ebp-3h]
	char v10; // [esp+10Bh] [ebp-1h]

	v3 = (HWND)lParam;
	String = byte_10029448;
	memset(&v8, 0, 0xFCu);
	v9 = 0;
	v10 = 0;
	v4 = a2;
	GetWindowTextA((HWND)lParam, &String, 255);
	HIBYTE(v9) = 0;
	result = strlen(&String);
	if ( v4 == 37 )
	{
		if ( result )
		{
			*(&v6 + result) = 0;
			SetWindowTextA(v3, &String);
		}
		result = DiabEdit_1000594E((LPARAM)v3);
	}
	return result;
} */

// ref: 0x10005B70
char *__fastcall DiabEdit_10005B70(HWND hWnd, char *a2) { return 0; }
/* {
	char *v2; // edi
	char *result; // eax
	char *v4; // esi

	v2 = a2;
	result = (char *)GetPropA(hWnd, "RESTRICTED");
	v4 = result;
	if ( result )
	{
		result = strncpy(result, v2, 0xFFu);
		v4[255] = 0;
	}
	return result;
} */

// ref: 0x10005B9F
BOOL UNKCALL DiabEdit_10005B9F(HWND hWnd) { return 0; }
/* {
	HWND v1; // esi
	_BYTE *v2; // eax

	v1 = hWnd;
	SDlgSetTimer(hWnd, 1, 500, 0);
	SetPropA(v1, "CURSOR", 0);
	v2 = (_BYTE *)SMemAlloc(256, "C:\\Src\\Diablo\\DiabloUI\\DiabEdit.cpp", 185, 0);
	*v2 = 0;
	return SetPropA(v1, "RESTRICTED", v2);
} */
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10005BE7
HANDLE UNKCALL DiabEdit_10005BE7(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	HANDLE result; // eax

	v1 = hWnd;
	SDlgKillTimer(hWnd, 1);
	RemovePropA(v1, "LIMIT");
	RemovePropA(v1, "CURSOR");
	result = RemovePropA(v1, "RESTRICTED");
	if ( result )
		result = (HANDLE)SMemFree(result, "C:\\Src\\Diablo\\DiabloUI\\DiabEdit.cpp", 200, 0);
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);
