// ref: 0x10007458
int (__stdcall *UNKCALL Focus_10007458(void *arg))(_DWORD) { return 0; }
/* {
	int v1; // esi
	int (__stdcall *result)(_DWORD); // eax

	v1 = (int)arg;
	if ( dword_10029CA4 && arg != (void *)dword_10029CA8 )
	{
		if ( dword_10029CAC )
			result = TitleSnd_10010315();
		dword_10029CA8 = v1;
	}
	return result;
} */
// 10029CA4: using guessed type int dword_10029CA4;
// 10029CA8: using guessed type int dword_10029CA8;
// 10029CAC: using guessed type int dword_10029CAC;

// ref: 0x10007482
int Focus_10007482() { return 0; }
/* {
	return dword_10029CA4 != 0 ? dword_10029C98 : 0;
} */
// 10029C98: using guessed type int dword_10029C98;
// 10029CA4: using guessed type int dword_10029CA4;

// ref: 0x10007492
_DWORD *__fastcall Focus_10007492(HWND hWnd, HWND a2) { return 0; }
/* {
	_DWORD *v2; // edi
	_DWORD *result; // eax
	_DWORD *v4; // esi
	int v5; // eax
	int v6; // ST14_4
	int v7; // eax
	struct tagRECT Rect; // [esp+8h] [ebp-18h]
	HWND v9; // [esp+18h] [ebp-8h]
	HWND hWnda; // [esp+1Ch] [ebp-4h]

	hWnda = a2;
	v9 = hWnd;
	v2 = (_DWORD *)GetWindowLongA(hWnd, -21);
	result = (_DWORD *)GetWindowLongA(hWnda, -21);
	v4 = result;
	if ( v2 && result && *v2 )
	{
		if ( *result )
		{
			GetWindowRect(hWnda, &Rect);
			ScreenToClient(v9, (LPPOINT)&Rect);
			ScreenToClient(v9, (LPPOINT)&Rect.right);
			SBltROP3(*v4, Rect.left + *v2 + Rect.top * v2[1], dword_10029C98, v4[2], v4[1], v2[1], 0, 13369376);
			v5 = v2[1];
			v6 = v5;
			v7 = *v2 + Rect.top * v5;
			v9 = (HWND)v4[1];
			SBltROP3(
				(char *)v9 + *v4 - dword_10029C98,
				(char *)v9 + v7 - dword_10029C98 + Rect.left,
				dword_10029C98,
				v4[2],
				v9,
				v6,
				0,
				13369376);
			result = (_DWORD *)Focus_10007566(hWnda);
		}
	}
	return result;
} */
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029C98: using guessed type int dword_10029C98;

// ref: 0x10007566
BOOL UNKCALL Focus_10007566(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	struct tagRECT Rect; // [esp+8h] [ebp-10h]

	v1 = hWnd;
	GetClientRect(hWnd, &Rect);
	--Rect.bottom;
	Rect.left = --Rect.right - dword_10029C98;
	InvalidateRect(v1, &Rect, 0);
	Rect.left = 0;
	Rect.right = dword_10029C98 - 1;
	return InvalidateRect(v1, &Rect, 0);
} */
// 10029C98: using guessed type int dword_10029C98;

// ref: 0x100075B7
_DWORD *__fastcall Focus_100075B7(HWND hWnd, HWND a2) { return 0; }
/* {
	HWND v2; // esi
	HWND v3; // edi
	_DWORD *result; // eax

	v2 = a2;
	v3 = hWnd;
	GetWindowLongA(a2, -12);
	result = Focus_10007492(v3, v2);
	dword_10029CAC = 1;
	return result;
} */
// 10029CAC: using guessed type int dword_10029CAC;

// ref: 0x100075DC
int __fastcall Focus_100075DC(HWND hWnd, HWND a2) { return 0; }
/* {
	HWND v2; // edi
	HWND v3; // ebx
	_DWORD *v4; // eax
	_DWORD *v5; // esi
	int v7; // edi
	struct tagRECT Rect; // [esp+Ch] [ebp-14h]
	HWND hWnda; // [esp+1Ch] [ebp-4h]

	v2 = hWnd;
	v3 = a2;
	hWnda = hWnd;
	if ( !dword_10029CA4 )
		return 0;
	if ( !a2 )
		return 0;
	GetWindowLongA(a2, -12);
	if ( v2 != GetParent(v3) )
		return 0;
	Focus_10007492(v2, v3);
	v4 = (_DWORD *)GetWindowLongA(v3, -21);
	v5 = v4;
	if ( !v4 || !*v4 )
		return 0;
	GetWindowRect(v3, &Rect);
	ScreenToClient(v2, (LPPOINT)&Rect);
	ScreenToClient(hWnda, (LPPOINT)&Rect.right);
	if ( dword_10029C78[dword_10029CB0] )
	{
		v7 = (v5[2] - dword_10029C9C) / 2;
		STransBlt(*v5, 0, v7, v5[1], dword_10029C78[dword_10029CB0]);
		STransBlt(*v5, v5[1] - dword_10029C98, v7, v5[1], dword_10029C78[dword_10029CB0]);
		Focus_10007566(v3);
	}
	if ( ++dword_10029CB0 >= 8 )
		dword_10029CB0 = 0;
	return 1;
} */
// 1001036A: using guessed type int __stdcall STransBlt(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029C98: using guessed type int dword_10029C98;
// 10029C9C: using guessed type int dword_10029C9C;
// 10029CA4: using guessed type int dword_10029CA4;
// 10029CB0: using guessed type int dword_10029CB0;

// ref: 0x100076C3
int Focus_100076C3() { return 0; }
/* {
	int *v0; // esi
	int result; // eax

	v0 = dword_10029C78;
	do
	{
		result = *v0;
		if ( *v0 )
		{
			result = STransDelete(*v0);
			*v0 = 0;
		}
		++v0;
	}
	while ( (signed int)v0 < (signed int)&dword_10029C98 );
	dword_10029CAC = 0;
	dword_10029CA8 = 0;
	dword_10029CA4 = 0;
	return result;
} */
// 1001033A: using guessed type int __stdcall STransDelete(_DWORD);
// 10029C98: using guessed type int dword_10029C98;
// 10029CA4: using guessed type int dword_10029CA4;
// 10029CA8: using guessed type int dword_10029CA8;
// 10029CAC: using guessed type int dword_10029CAC;

// ref: 0x100076FA
void Focus_100076FA() { return; }
/* {
	dword_10029CAC = 0;
	dword_10029CA8 = 0;
} */
// 10029CA8: using guessed type int dword_10029CA8;
// 10029CAC: using guessed type int dword_10029CAC;

// ref: 0x1000770E
signed int Focus_1000770E() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029CA0 = 2139095040;
	return result;
} */
// 10029CA0: using guessed type int dword_10029CA0;

// ref: 0x10007719
void UNKCALL Focus_10007719(void *arg) { return; }
/* {
	int *v1; // esi
	int v2; // ecx
	int v3; // eax
	int v4; // ebx
	int v5; // [esp+4h] [ebp-1Ch]
	int v6; // [esp+8h] [ebp-18h]
	int v7; // [esp+Ch] [ebp-14h]
	int v8; // [esp+10h] [ebp-10h]
	int v9; // [esp+14h] [ebp-Ch]
	int v10; // [esp+18h] [ebp-8h]
	int v11; // [esp+1Ch] [ebp-4h]

	if ( !dword_10029CA4 )
	{
		v11 = 0;
		dword_10029CAC = 0;
		dword_10029CA8 = 0;
		local_100078BE((int)arg, &v11, &v9);
		v1 = dword_10029C78;
		memset(dword_10029C78, 0, 0x20u);
		if ( v11 )
		{
			v2 = v9;
			dword_10029C98 = v9;
			v3 = v10 / 8;
			v4 = 0;
			dword_10029C9C = v10 / 8;
			while ( 1 )
			{
				v7 = v2 - 1;
				v6 = v4 * v3;
				v5 = 0;
				v8 = v3 + v4 * v3 - 1;
				STransCreateI(v11, v2, v3, 8, &v5, 16777466, v1);
				++v1;
				++v4;
				if ( (signed int)v1 >= (signed int)&dword_10029C98 )
					break;
				v3 = dword_10029C9C;
				v2 = dword_10029C98;
			}
			SMemFree(v11, "C:\\Src\\Diablo\\DiabloUI\\Focus.cpp", 246, 0);
		}
		dword_10029CB0 = 0;
		dword_10029CA4 = 1;
	}
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010346: using guessed type int __stdcall STransCreateI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10029C98: using guessed type int dword_10029C98;
// 10029C9C: using guessed type int dword_10029C9C;
// 10029CA4: using guessed type int dword_10029CA4;
// 10029CA8: using guessed type int dword_10029CA8;
// 10029CAC: using guessed type int dword_10029CAC;
// 10029CB0: using guessed type int dword_10029CB0;

// ref: 0x100077E9
int __fastcall Focus_100077E9(int a1, void *a2, HWND hWnd) { return 0; }
/* {
	int v3; // esi

	v3 = a1;
	Focus_10007719(a2);
	return SDlgSetTimer(v3, 1, 55, Focus_10007804);
} */
// 10010412: using guessed type int __stdcall SDlgSetTimer(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x10007804
int __stdcall Focus_10007804(HWND hWnd, int a2, int a3, int a4) { return 0; }
/* {
	HWND v4; // eax

	v4 = GetFocus();
	return Focus_100075DC(hWnd, v4);
} */

// ref: 0x10007818
int UNKCALL Focus_10007818(void *arg) { return 0; }
/* {
	SDlgKillTimer(arg, 1);
	return Focus_100076C3();
} */
// 10010418: using guessed type int __stdcall SDlgKillTimer(_DWORD, _DWORD);
