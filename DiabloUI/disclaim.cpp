// ref: 0x100063B3
signed int __stdcall UiBetaDisclaimer(int a1) { return 0; }
/* {
	int v1; // eax

	v1 = SDrawGetFrameWindow();
	SDlgDialogBoxParam(hInstance, "DISCLAIMER_DIALOG", v1, disclaim_100063DA, a1);
	return 1;
} */
// 10010370: using guessed type int __stdcall SDlgDialogBoxParam(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x100063DA
int __stdcall disclaim_100063DA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0; }
/* {
	HWND v5; // eax
	int v6; // [esp+0h] [ebp-8h]

	if ( Msg > 0x111 )
	{
		if ( Msg != 513 && Msg != 516 )
		{
			if ( Msg == 528 )
			{
				if ( (_WORD)wParam == 513 || (_WORD)wParam == 516 )
					disclaim_10006552(hWnd);
			}
			else if ( Msg == 2024 )
			{
				if ( !Fade_1000739F() )
					Fade_100073FD(hWnd, v6);
				return 0;
			}
			return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
		}
	}
	else if ( Msg != 273 )
	{
		if ( Msg != 2 )
		{
			if ( Msg != 256 )
			{
				if ( Msg > 0x103 )
				{
					if ( Msg <= 0x105 )
					{
						v5 = (HWND)SDrawGetFrameWindow();
						SendMessageA(v5, Msg, wParam, lParam);
					}
					else if ( Msg == 272 )
					{
						disclaim_100064F3(hWnd);
						PostMessageA(hWnd, 0x7E8u, 0, 0);
						return 1;
					}
				}
				return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
			}
			goto LABEL_21;
		}
		disclaim_100064C9(hWnd);
		return SDlgDefDialogProc(hWnd, Msg, wParam, lParam);
	}
LABEL_21:
	disclaim_10006552(hWnd);
	return 0;
} */
// 1001037C: using guessed type int __stdcall SDlgDefDialogProc(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010382: using guessed type _DWORD __stdcall SDrawGetFrameWindow();

// ref: 0x100064C9
void UNKCALL disclaim_100064C9(HWND hDlg) { return; }
/* {
	HWND v1; // esi
	_DWORD *v2; // eax

	v1 = hDlg;
	Doom_10006C53(hDlg, (int *)&unk_10022AA4);
	Doom_10006C53(v1, (int *)&unk_10022A98);
	v2 = (_DWORD *)GetWindowLongA(v1, -21);
	local_10007F72(v2);
} */

// ref: 0x100064F3
int UNKCALL disclaim_100064F3(HWND hWnd) { return 0; }
/* {
	HWND v1; // edi
	int v2; // eax
	int *v3; // esi

	v1 = hWnd;
	v2 = local_10007F46();
	v3 = (int *)v2;
	if ( v2 )
	{
		SetWindowLongA(v1, -21, v2);
		local_10007944((int)v1, 0, &byte_10029448, -1, 1, (int)"ui_art\\disclaim.pcx", v3, v3 + 1, 0);
		Fade_100073C5(v1, 0);
	}
	Doom_100068AB(v1, (int *)&unk_10022A98, 5);
	return Doom_100068AB(v1, (int *)&unk_10022AA4, 2);
} */

// ref: 0x10006552
int UNKCALL disclaim_10006552(void *arg) { return 0; }
/* {
	void *v1; // esi

	v1 = arg;
	Fade_100073B4();
	Fade_100072BE(10);
	return SDlgEndDialog(v1, 1);
} */
// 10010376: using guessed type int __stdcall SDlgEndDialog(_DWORD, _DWORD);

// ref: 0x10006571
signed int disclaim_10006571() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029850 = 2139095040;
	return result;
} */
// 10029850: using guessed type int dword_10029850;
