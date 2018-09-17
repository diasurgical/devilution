// ref: 0x10002E2B
void *Connect_10002E2B() { return 0; }
/* {
	int *v0; // edi
	int result; // eax

	if ( dword_100295D8 )
	{
		SMemFree(dword_100295D8, "C:\\Src\\Diablo\\DiabloUI\\Connect.cpp", 124, 0);
		dword_100295D8 = 0;
	}
	if ( dword_100295DC )
	{
		SMemFree(dword_100295DC, "C:\\Src\\Diablo\\DiabloUI\\Connect.cpp", 129, 0);
		dword_100295DC = 0;
	}
	v0 = dword_100295E8;
	do
	{
		if ( *v0 )
		{
			STransDelete(*v0);
			*v0 = 0;
		}
		++v0;
	}
	while ( (signed int)v0 < (signed int)&dword_10029610 );
	if ( dword_100295E0 )
	{
		SMemFree(dword_100295E0, "C:\\Src\\Diablo\\DiabloUI\\Connect.cpp", 141, 0);
		dword_100295E0 = 0;
	}
	result = dword_100295E4;
	if ( dword_100295E4 )
	{
		result = SMemFree(dword_100295E4, "C:\\Src\\Diablo\\DiabloUI\\Connect.cpp", 146, 0);
		dword_100295E4 = 0;
	}
	return result;
} */
// 1001033A: using guessed type int __stdcall STransDelete(_DWORD);
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 100295D8: using guessed type int dword_100295D8;
// 100295DC: using guessed type int dword_100295DC;
// 100295E0: using guessed type int dword_100295E0;
// 100295E4: using guessed type int dword_100295E4;
// 10029610: using guessed type int dword_10029610;

// ref: 0x10002EC4
signed int Connect_10002EC4() { return 0; }
/* {
	int *v0; // esi
	int v1; // ebx
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int v5; // [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int v7; // [esp+14h] [ebp-4h]

	v7 = 0;
	if ( !dword_100295D8 && !dword_100295E8[0] )
	{
		local_100078BE((int)"ui_art\\heroport.pcx", &dword_100295D8, &dword_100294A8);
		local_100078BE((int)"ui_art\\spwnport.pcx", &dword_100295DC, 0);
		local_100078BE((int)"ui_art\\heronum.pcx", &v7, &dword_100295C8);
		local_100078BE((int)"ui_art\\special.pcx", &dword_100295E0, &dword_100295B8);
		dword_100295D4 = 14;
		dword_100295D0 = dword_100295CC / 10;
		dword_100294A4 = dword_100295BC / 8;
		dword_100295B0 = dword_100295CC / 10 * dword_100295C8;
		dword_100295C0 = 14 * dword_100294A8;
		v0 = dword_100295E8;
		dword_100295E4 = SMemAlloc(14 * dword_100294A8, "C:\\Src\\Diablo\\DiabloUI\\Connect.cpp", 194, 0);
		memset(dword_100295E8, 0, 0x28u);
		if ( v7 )
		{
			v1 = 0;
			do
			{
				v3 = 0;
				v5 = dword_100295C8 - 1;
				v4 = v1 * dword_100295D0;
				v6 = dword_100295D0 + v1 * dword_100295D0 - 1;
				STransCreateI(v7, dword_100295C8, dword_100295D0, 8, &v3, 16777455, v0);
				++v0;
				++v1;
			}
			while ( (signed int)v0 < (signed int)&dword_10029610 );
			SMemFree(v7, "C:\\Src\\Diablo\\DiabloUI\\Connect.cpp", 218, 0);
		}
	}
	return 1;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010346: using guessed type int __stdcall STransCreateI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010364: using guessed type int __stdcall SMemAlloc(_DWORD, _DWORD, _DWORD, _DWORD);
// 100294A4: using guessed type int dword_100294A4;
// 100294A8: using guessed type int dword_100294A8;
// 100295B0: using guessed type int dword_100295B0;
// 100295B8: using guessed type int dword_100295B8;
// 100295BC: using guessed type int dword_100295BC;
// 100295C0: using guessed type int dword_100295C0;
// 100295C8: using guessed type int dword_100295C8;
// 100295CC: using guessed type int dword_100295CC;
// 100295D0: using guessed type int dword_100295D0;
// 100295D4: using guessed type int dword_100295D4;
// 100295D8: using guessed type int dword_100295D8;
// 100295DC: using guessed type int dword_100295DC;
// 100295E0: using guessed type int dword_100295E0;
// 100295E4: using guessed type int dword_100295E4;
// 10029610: using guessed type int dword_10029610;

// ref: 0x10003009
void __cdecl UiArtCallback() { return; }
//int __stdcall UiArtCallback(int a1, unsigned int a2, int a3, int a4, int a5, int a6, int a7, int a8) { return 0; }
/* {
	int result; // eax
	CHAR v9; // [esp+8h] [ebp-104h]
	char v10; // [esp+9h] [ebp-103h]
	short v11; // [esp+109h] [ebp-3h]
	char v12; // [esp+10Bh] [ebp-1h]

	v9 = byte_10029448;
	memset(&v10, 0, 0x100u);
	v11 = 0;
	v12 = 0;
	SStrCopy(&v9, "ui_art\\", 260);
	if ( a1 == 1112425812 )
	{
		if ( a2 > 0x80000004 )
		{
			switch ( a2 )
			{
				case 0x80000005:
					SStrPack(&v9, "bnconnbg.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x80000006:
					SStrPack(&v9, "bnselchn.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x80000007:
					SStrPack(&v9, "bnlogin.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x80000008:
					SStrPack(&v9, "newaccount.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x80000009:
					SStrPack(&v9, "changepassword.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x8000000A:
					SStrPack(&v9, "bnladder.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x8000000B:
					SStrPack(&v9, "badconn.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x8000000C:
					SStrPack(&v9, "welcome.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x8000000D:
					SStrPack(&v9, "lepopup.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				case 0x8000000E:
					SStrPack(&v9, "tos.pcx", 0x104u);
					return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				default:
					break;
			}
		}
		else
		{
			if ( a2 == -2147483644 )
			{
				SStrPack(&v9, "redlag.pcx", 0x104u);
				return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
			}
			if ( a2 > 7 )
			{
				switch ( a2 )
				{
					case 8u:
LABEL_48:
						SStrPack(&v9, "but_lrg.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 0x80000000:
						SStrPack(&v9, "bnbuttns.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 0x80000001:
						SStrPack(&v9, "chat_bkg.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 0x80000002:
						SStrPack(&v9, "greenlag.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 0x80000003:
						SStrPack(&v9, "yellolag.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				}
			}
			else
			{
				switch ( a2 )
				{
					case 7u:
LABEL_47:
						SStrPack(&v9, "but_med.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 0u:
						SStrPack(&v9, "bn_bkg.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 2u:
						SStrPack(&v9, "bnjoinbg.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 3u:
						SStrPack(&v9, "hpopup.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 5u:
LABEL_46:
						SStrPack(&v9, "but_xsm.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
					case 6u:
LABEL_11:
						SStrPack(&v9, "but_sml.pcx", 0x104u);
						return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
				}
			}
		}
	}
	else if ( a1 == 1230002254 )
	{
		if ( !a2 )
		{
			SStrPack(&v9, "ipx_bkg.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		}
	}
	else if ( !a1 && !a2 )
	{
		SStrPack(&v9, "connect.pcx", 0x104u);
		return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
	}
	switch ( a2 )
	{
		case 0u:
		case 2u:
			SStrPack(&v9, "menu.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 1u:
		case 8u:
			goto LABEL_48;
		case 3u:
		case 4u:
			SStrPack(&v9, "lpopup.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 5u:
			goto LABEL_46;
		case 6u:
			goto LABEL_11;
		case 7u:
			goto LABEL_47;
		case 9u:
			SStrPack(&v9, "xsmlogo.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0xAu:
			SStrPack(&v9, "prog_bg.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0xBu:
			SStrPack(&v9, "prog_fil.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0xCu:
			SStrPack(&v9, "spopup.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0xDu:
			SStrPack(&v9, "scrlarrw.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0xEu:
			SStrPack(&v9, "scrlthmb.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0xFu:
			SStrPack(&v9, "scrlbar.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x10u:
			SStrPack(&v9, "cmel.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x11u:
			SStrPack(&v9, "cmml.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x12u:
			SStrPack(&v9, "cmbl.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x13u:
			SStrPack(&v9, "cmec.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x14u:
			SStrPack(&v9, "cmmc.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x15u:
			SStrPack(&v9, "cmbc.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x16u:
			SStrPack(&v9, "cmer.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x17u:
			SStrPack(&v9, "cmmr.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x18u:
			SStrPack(&v9, "cmbr.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x19u:
			SStrPack(&v9, "slgray.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x1Au:
			SStrPack(&v9, "slthumb.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x1Bu:
			SStrPack(&v9, "slfocus.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x1Cu:
			SStrPack(&v9, "slleft.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x1Du:
			SStrPack(&v9, "slmiddle.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x1Eu:
			SStrPack(&v9, "slright.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x20u:
			SStrPack(&v9, "but_checkoff.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		case 0x21u:
			SStrPack(&v9, "but_checkon.pcx", 0x104u);
			return SBmpLoadImage(&v9, a3, a4, a5, a6, a7, a8);
		default:
			result = 0;
			break;
	}
	return result;
} */
// 100103BE: using guessed type int __stdcall SBmpLoadImage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100103E2: using guessed type unsigned int __stdcall SStrPack(char *, const char *, unsigned int);
// 100103E8: using guessed type int __stdcall SStrCopy(_DWORD, _DWORD, _DWORD);

// ref: 0x100033D1
signed int Connect_100033D1() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_100294A0 = 2139095040;
	return result;
} */
// 100294A0: using guessed type int dword_100294A0;

// ref: 0x100033DC
void __cdecl UiGetDataCallback() { return; }
//BOOL __stdcall UiGetDataCallback(int a1, int a2, void *a3, int a4, int a5) { return 0; }
/* {
	signed int v5; // edi
	_DWORD *v6; // esi
	HCURSOR v7; // eax

	v5 = 0;
	if ( a1 != 1112425812 || a2 != 0x80000000 )
	{
		switch ( a2 )
		{
			case 1:
				v5 = 16;
				if ( !a3 )
					goto LABEL_24;
				if ( (unsigned int)a4 >= 0x10 )
				{
					memcpy(a3, "\r", 0x10u);
					goto LABEL_24;
				}
				return 0;
			case 2:
				v6 = a3;
				v5 = 4;
				if ( !a3 )
					goto LABEL_24;
				if ( (unsigned int)a4 < 4 )
					return 0;
				v7 = LoadCursorA(hInstance, "DIABLO_LINKCURSOR");
				break;
			case 3:
				v6 = a3;
				v5 = 4;
				if ( !a3 )
					goto LABEL_24;
				if ( (unsigned int)a4 < 4 )
					return 0;
				v7 = LoadCursorA(hInstance, "DIABLO_ARROWCURSOR");
				break;
			case 4:
				v6 = a3;
				v5 = 4;
				if ( !a3 )
					goto LABEL_24;
				if ( (unsigned int)a4 < 4 )
					return 0;
				v7 = LoadCursorA(hInstance, "DIABLOIBEAM");
				break;
			default:
				goto LABEL_24;
		}
		*v6 = v7;
		if ( v7 )
			goto LABEL_24;
		return 0;
	}
	v5 = 4;
	if ( a3 )
	{
		if ( (unsigned int)a4 >= 4 )
		{
			*(_DWORD *)a3 = 54;
			goto LABEL_24;
		}
		return 0;
	}
LABEL_24:
	if ( a5 )
		*(_DWORD *)a5 = v5;
	return v5 != 0;
} */

// ref: 0x100034AB
void __cdecl UiSoundCallback() { return; }
//int __stdcall UiSoundCallback(int a1, int a2, int a3) { return 0; }
/* {
	if ( a2 )
	{
		if ( a2 == 1 )
			TitleSnd_1001031F();
	}
	else
	{
		TitleSnd_10010315();
	}
	return 0;
} */

// ref: 0x100034C8
void __cdecl UiAuthCallback() { return; }
//int __stdcall UiAuthCallback(int a1, int a2, char *a3, char a4, char *a5, LPSTR lpBuffer, int cchBufferMax) { return 0; }
/* {
	size_t v7; // edi
	size_t v8; // ebx
	int v9; // ebx
	char *v10; // ebx
	size_t v11; // eax
	int v12; // eax
	int v14; // eax
	CHAR v15; // [esp+0h] [ebp-434h]
	char v16; // [esp+100h] [ebp-334h]
	char v17; // [esp+200h] [ebp-234h]
	CHAR Buffer; // [esp+300h] [ebp-134h]
	char v19; // [esp+400h] [ebp-34h]
	unsigned short v20; // [esp+414h] [ebp-20h]
	unsigned char v21; // [esp+416h] [ebp-1Eh]
	char v22; // [esp+42Ch] [ebp-8h]
	int v23; // [esp+430h] [ebp-4h]

	v23 = 0;
	if ( cchBufferMax )
		*lpBuffer = 0;
	v7 = strlen(a3) + 1;
	v8 = strlen(a5) + 1;
	if ( v7 > 0x100 || v8 > 0x100 )
	{
		if ( lpBuffer )
			LoadStringA(hInstance, 0x413u, lpBuffer, cchBufferMax);
		return 0;
	}
	memcpy(&v16, a3, v7);
	memcpy(&v17, a5, v8);
	if ( Connect_10003E61(&v16, &v19) )
	{
		if ( a1 == 1 )
		{
			if ( !(a4 & 9) )
			{
				v9 = 0;
				while ( 1 )
				{
					LoadStringA(hInstance, v9 + 4, &Buffer, 256);
					if ( strstr(&v17, &Buffer) )
						break;
					if ( ++v9 >= 3 )
						goto LABEL_16;
				}
				if ( v21 != v9 )
					goto LABEL_20;
				v23 = 1;
LABEL_16:
				LoadStringA(hInstance, 0x408u, &Buffer, 256);
				v10 = strstr(&v17, &Buffer);
				if ( v10 )
				{
					v11 = strlen(&Buffer);
					v12 = atoi(&v10[v11]);
					if ( v20 >= v12 )
						return 1;
				}
				if ( v23 )
					return 1;
LABEL_20:
				if ( lpBuffer )
				{
					LoadStringA(hInstance, 0x415u, &v15, 256);
					v14 = sprintf(&Buffer, &v15, &v17) + 1;
					if ( cchBufferMax >= v14 )
					{
						memcpy(lpBuffer, &Buffer, v14);
					}
					else
					{
						memcpy(lpBuffer, &Buffer, cchBufferMax);
						lpBuffer[cchBufferMax - 1] = 0;
					}
				}
				return 0;
			}
		}
		else if ( !(a4 & 8) )
		{
			Connect_10003DAF(&v17, (int)&v22, 0, 0);
			if ( (_BYTE)v23 == 1 )
			{
				if ( v20 < 0x14u )
				{
					if ( lpBuffer )
						LoadStringA(hInstance, 0x411u, lpBuffer, cchBufferMax);
					return 0;
				}
			}
			else if ( (_BYTE)v23 == 2 && v20 < 0x1Eu )
			{
				if ( lpBuffer )
					LoadStringA(hInstance, 0x412u, lpBuffer, cchBufferMax);
				return 0;
			}
		}
		return 1;
	}
	if ( lpBuffer )
		LoadStringA(hInstance, 0x414u, lpBuffer, cchBufferMax);
	return 0;
} */

// ref: 0x10003710
void __cdecl UiDrawDescCallback() { return; }
//int __stdcall UiDrawDescCallback(int a1, COLORREF color, LPCSTR lpString, char *a4, int a5, UINT align, time_t a7, int a8) { return 0; }
/* {
	int v8; // ebx
	int v9; // esi
	int v10; // esi
	size_t v11; // eax
	UINT v13; // eax
	BOOL v14; // esi
	int v15; // eax
	int v16; // eax
	HDC v17; // ST20_4
	struct tm *v18; // eax
	struct tm *v19; // edi
	signed int v20; // eax
	int v21; // eax
	int v22; // eax
	UINT v23; // eax
	int v24; // esi
	int v25; // eax
	int v26; // eax
	signed int v27; // [esp-4h] [ebp-2E8h]
	char v28[4]; // [esp+Ch] [ebp-2D8h]
	CHAR String; // [esp+10Ch] [ebp-1D8h]
	CHAR Buffer; // [esp+18Ch] [ebp-158h]
	char v31; // [esp+18Dh] [ebp-157h]
	short v32; // [esp+209h] [ebp-DBh]
	char v33; // [esp+20Bh] [ebp-D9h]
	CHAR v34; // [esp+20Ch] [ebp-D8h]
	int v35; // [esp+22Ch] [ebp-B8h]
	struct tagPOINT v36; // [esp+248h] [ebp-9Ch]
	struct tagTEXTMETRICA tm; // [esp+25Ch] [ebp-88h]
	char v38; // [esp+294h] [ebp-50h]
	CHAR v39; // [esp+2A0h] [ebp-44h]
	unsigned short v40; // [esp+2A8h] [ebp-3Ch]
	unsigned char v41; // [esp+2AAh] [ebp-3Ah]
	unsigned char v42; // [esp+2ABh] [ebp-39h]
	int v43; // [esp+2BCh] [ebp-28h]
	struct tagPOINT pt; // [esp+2C0h] [ebp-24h]
	char v45; // [esp+2C8h] [ebp-1Ch]
	unsigned char v46; // [esp+2CCh] [ebp-18h]
	struct tagRECT rc; // [esp+2D0h] [ebp-14h]
	COLORREF v48; // [esp+2E0h] [ebp-4h]
	LPCSTR lpStringa; // [esp+2F4h] [ebp+10h]

	Buffer = byte_10029448;
	v8 = a8;
	memset(&v31, 0, 0x7Cu);
	v9 = *(_DWORD *)(a8 + 16);
	v32 = 0;
	v33 = 0;
	v10 = v9 & 1;
	v11 = strlen(a4) + 1;
	if ( v11 > 0x100 )
		return 0;
	memcpy(v28, a4, v11);
	if ( color == 1 )
	{
		a8 = 0;
		a4 = 0;
		if ( !Connect_10003DAF(v28, (int)&v45, (int)&a8, (int)&a4) )
			return 0;
		color = SetTextColor(*(HDC *)(v8 + 24), 0xFFFFFFu);
		v48 = SetBkColor(*(HDC *)(v8 + 24), v10 != 0 ? 0x808080 : 0);
		if ( align & 1 )
		{
			v13 = strlen(lpString);
			ExtTextOutA(
				*(HDC *)(v8 + 24),
				*(_DWORD *)(v8 + 28),
				*(_DWORD *)(v8 + 32),
				6u,
				(const RECT *)(v8 + 28),
				lpString,
				v13,
				0);
		}
		else
		{
			v14 = a8 && a4;
			if ( v46 < 3u )
				LoadStringA(hInstance, v46 + 1003, &Buffer, 128);
			if ( align & 2 && v14 )
			{
				GetTextMetricsA(*(HDC *)(v8 + 24), &tm);
				lpStringa = (LPCSTR)(tm.tmHeight + tm.tmExternalLeading);
				MoveToEx(*(HDC *)(v8 + 24), *(_DWORD *)(v8 + 28), *(_DWORD *)(v8 + 32), &pt);
				align = SetTextAlign(*(HDC *)(v8 + 24), 1u);
				v15 = strlen(&Buffer);
				TextOutA(*(HDC *)(v8 + 24), 0, 0, &Buffer, v15);
				LoadStringA(hInstance, 0x409u, &String, 128);
				MoveToEx(*(HDC *)(v8 + 24), *(_DWORD *)(v8 + 28), (int)&lpStringa[*(_DWORD *)(v8 + 32)], 0);
				v16 = strlen(&String);
				TextOutA(*(HDC *)(v8 + 24), 0, 0, &String, v16);
				v17 = *(HDC *)(v8 + 24);
				qmemcpy(&v35, (const void *)v8, 0x30u);
				GetCurrentPositionEx(v17, &v36);
				SetTextAlign(*(HDC *)(v8 + 24), 0);
				dword_10029614 = 1;
				UiDrawDescCallback(a1, 2u, (LPCSTR)a8, a4, 0, 1u, 0, (int)&v35);
				dword_10029614 = 0;
				if ( a7 )
				{
					SetTextAlign(*(HDC *)(v8 + 24), 1u);
					LoadStringA(hInstance, 0x40Cu, &v39, 32);
					LoadStringA(hInstance, 0x40Du, &v34, 32);
					v18 = localtime(&a7);
					v19 = v18;
					if ( v18 )
					{
						LoadStringA(hInstance, (v18->tm_hour > 12) + 1034, (LPSTR)&rc.top, 10);
						v20 = v19->tm_hour;
						if ( v20 > 12 )
							v19->tm_hour = v20 - 12;
						if ( !v19->tm_hour )
							v19->tm_hour = 12;
						sprintf(&String, &v39, &v34, v19->tm_hour, v19->tm_min, &rc.top);
						MoveToEx(
							*(HDC *)(v8 + 24),
							*(_DWORD *)(v8 + 28),
							*(_DWORD *)(v8 + 32) + 2 * (_DWORD)lpStringa,
							0);
						v21 = strlen(&String);
						TextOutA(*(HDC *)(v8 + 24), 0, 0, &String, v21);
					}
				}
				MoveToEx(*(HDC *)(v8 + 24), pt.x, pt.y, 0);
				SetTextAlign(*(HDC *)(v8 + 24), align);
			}
			else
			{
				v22 = strlen(&Buffer);
				TextOutA(*(HDC *)(v8 + 24), *(_DWORD *)(v8 + 28), *(_DWORD *)(v8 + 32), &Buffer, v22);
			}
		}
		goto LABEL_56;
	}
	GetTextMetricsA(*(HDC *)(v8 + 24), &tm);
	a4 = (char *)((tm.tmHeight - dword_100295D4) / 2 + 1);
	if ( !dword_10029614 )
	{
		color = SetTextColor(*(HDC *)(v8 + 24), 0xFFFFu);
		v48 = SetBkColor(*(HDC *)(v8 + 24), v10 != 0 ? 0x808080 : 0);
	}
	if ( align & 1 )
	{
		v23 = strlen(lpString);
		ExtTextOutA(
			*(HDC *)(v8 + 24),
			*(_DWORD *)(v8 + 28) + dword_100294A8 + 2,
			*(_DWORD *)(v8 + 32),
			6u,
			(const RECT *)(v8 + 28),
			lpString,
			v23,
			0);
	}
	if ( a5 )
	{
		if ( a5 & 0x20 )
		{
			v27 = 5;
LABEL_45:
			v24 = v27;
			goto LABEL_46;
		}
		if ( a5 & 1 )
		{
			v24 = 0;
LABEL_46:
			SetRect(&rc, 0, 0, dword_100295B8 - 1, dword_100294A4 - 1);
			OffsetRect(&rc, 0, dword_100294A4 * v24);
			SDlgBltToWindowI(
				*(_DWORD *)(v8 + 20),
				0,
				*(_DWORD *)(v8 + 28),
				&a4[*(_DWORD *)(v8 + 32)],
				dword_100295E0,
				&rc,
				&dword_100295B8,
				-1,
				0,
				13369376);
			goto LABEL_55;
		}
		if ( a5 & 2 )
		{
			v27 = 2;
			goto LABEL_45;
		}
		if ( a5 & 4 )
		{
			v27 = 3;
			goto LABEL_45;
		}
		if ( a5 & 8 )
		{
			v25 = (a1 != 1112425812) - 1;
			LOBYTE(v25) = v25 & 0xFD;
			v24 = v25 + 4;
			goto LABEL_46;
		}
	}
	if ( *(_DWORD *)v28 == 1128808788 )
	{
		v27 = 6;
		goto LABEL_45;
	}
	if ( *(_DWORD *)v28 == 1397053520 || *(_DWORD *)v28 == 1397966930 || *(_DWORD *)v28 == 1398030674 )
	{
		v27 = 7;
		goto LABEL_45;
	}
	if ( Connect_10003E61(v28, &v38) )
	{
		if ( v43 )
		{
			if ( dword_100295DC )
				SBltROP3(
					dword_100295E4,
					dword_100295DC,
					dword_100294A8,
					dword_100295D4,
					dword_100294A8,
					dword_100294A8,
					0,
					13369376);
		}
		else
		{
			SBltROP3(
				dword_100295E4,
				dword_100295D8 + dword_100295C0 * (v41 + 3 * v42),
				dword_100294A8,
				dword_100295D4,
				dword_100294A8,
				dword_100294A8,
				0,
				13369376);
		}
		v26 = v40 / 10;
		if ( v26 )
			STransBlt(
				dword_100294A8 + dword_100295E4 + 4 * dword_100294A8 + 14,
				0,
				0,
				dword_100294A8,
				dword_100295E8[v26]);
		STransBlt(
			dword_100295E4 + 4 * (dword_100294A8 + 4) + dword_100294A8 + 4,
			0,
			0,
			dword_100294A8,
			dword_100295E8[v40 % 10]);
		SetRect(&rc, 0, 0, dword_100294A8 - 1, dword_100295D4 - 1);
		SDlgBltToWindowI(
			*(_DWORD *)(v8 + 20),
			0,
			*(_DWORD *)(v8 + 28),
			&a4[*(_DWORD *)(v8 + 32)],
			dword_100295E4,
			&rc,
			&dword_100294A8,
			-1,
			0,
			13369376);
	}
LABEL_55:
	if ( !dword_10029614 )
	{
LABEL_56:
		SetTextColor(*(HDC *)(v8 + 24), color);
		SetBkColor(*(HDC *)(v8 + 24), v48);
	}
	return 1;
} */
// 1001036A: using guessed type int __stdcall STransBlt(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100103EE: using guessed type int __stdcall SDlgBltToWindowI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100103F4: using guessed type int __stdcall SBltROP3(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100294A4: using guessed type int dword_100294A4;
// 100294A8: using guessed type int dword_100294A8;
// 100295B8: using guessed type int dword_100295B8;
// 100295C0: using guessed type int dword_100295C0;
// 100295D4: using guessed type int dword_100295D4;
// 100295D8: using guessed type int dword_100295D8;
// 100295DC: using guessed type int dword_100295DC;
// 100295E0: using guessed type int dword_100295E0;
// 100295E4: using guessed type int dword_100295E4;
// 10029614: using guessed type int dword_10029614;

// ref: 0x10003CE4
void __cdecl UiCategoryCallback() { return; }
//signed int __stdcall UiCategoryCallback(int a1, int a2, int a3, int a4, int a5, _DWORD *a6, _DWORD *a7) { return 0; }
/* {
	*a7 = 0xFFFF;
	*a6 = Connect_10003D04(byte_100294B0);
	return 1;
} */

// ref: 0x10003D04
int UNKCALL Connect_10003D04(char *arg) { return 0; }
/* {
	char v3; // [esp+0h] [ebp-22Ch]
	char v4; // [esp+200h] [ebp-2Ch]
	unsigned short v5; // [esp+214h] [ebp-18h]

	strcpy(&v3, arg);
	if ( !Connect_10003E61(&v3, &v4) || v5 == 1 )
		return 0;
	if ( (signed int)v5 < 4 )
		return 1;
	if ( (signed int)v5 < 6 )
		return 2;
	if ( (signed int)v5 < 8 )
		return 3;
	if ( (signed int)v5 < 10 )
		return 4;
	if ( (signed int)v5 < 13 )
		return 5;
	if ( (signed int)v5 < 17 )
		return 6;
	if ( (signed int)v5 < 20 )
		return 7;
	if ( (signed int)v5 < 25 )
		return 8;
	if ( (signed int)v5 < 30 )
		return 9;
	if ( (signed int)v5 < 35 )
		return 10;
	if ( (signed int)v5 < 40 )
		return 11;
	return ((signed int)v5 >= 48) + 12;
} */

// ref: 0x10003DAF
int __fastcall Connect_10003DAF(char *a1, int a2, int a3, int a4) { return 0; }
/* {
	char *v4; // esi
	int v5; // edi
	unsigned char v6; // al
	char *v8; // eax
	const char *v9; // eax
	char *v10; // eax

	v4 = a1;
	v5 = a2;
	if ( !*a1 )
		return 0;
	v6 = atoi(a1);
	*(_BYTE *)(v5 + 4) = v6;
	if ( v6 >= 3u )
		return 0;
	v8 = strchr(v4, 13);
	if ( v8 )
	{
		*v8 = 0;
		v9 = v8 + 1;
		if ( a3 )
			*(_DWORD *)a3 = v9;
		v10 = strchr(v9, 13);
		if ( v10 )
		{
			*v10 = 0;
			if ( a4 )
				*(_DWORD *)a4 = v10 + 1;
		}
	}
	return 1;
} */

// ref: 0x10003E0C
char *__fastcall Connect_10003E0C(int a1, const char *a2, char *a3, char *a4, int a5) { return 0; }
/* {
	const char *v5; // edi
	int v6; // esi
	size_t v7; // ebx
	size_t v8; // eax
	bool v9; // zf
	bool v10; // sf
	unsigned char v11; // of
	int v12; // eax
	char *result; // eax

	v5 = a2;
	v6 = a1;
	v7 = strlen(a2);
	v8 = v7 + strlen(a3) + 5;
	v11 = __OFSUB__(a5, v8);
	v9 = a5 == v8;
	v10 = (signed int)(a5 - v8) < 0;
	v12 = *(unsigned char *)(v6 + 4);
	if ( (unsigned char)(v10 ^ v11) | v9 )
		result = _itoa(v12, a4, 10);
	else
		result = (char *)sprintf(a4, "%d\r%s\r%s", v12, v5, a3);
	return result;
} */

// ref: 0x10003E61
signed int __fastcall Connect_10003E61(const char *a1, _BYTE *a2) { return 0; }
/* {
	_BYTE *v2; // esi
	const char *v3; // edi
	int v4; // eax
	int v5; // edi
	int v6; // edx
	short v7; // di
	char v8; // cl
	int v10; // [esp+Ch] [ebp-24h]
	unsigned int v11; // [esp+10h] [ebp-20h]
	unsigned int v12; // [esp+14h] [ebp-1Ch]
	unsigned int v13; // [esp+18h] [ebp-18h]
	int v14; // [esp+1Ch] [ebp-14h]
	int v15; // [esp+20h] [ebp-10h]
	int v16; // [esp+24h] [ebp-Ch]
	int v17; // [esp+28h] [ebp-8h]
	int v18; // [esp+2Ch] [ebp-4h]

	v2 = a2;
	v3 = a1;
	memset(a2, 0, 0x2Cu);
	if ( !*v3 )
		return 0;
	v4 = *(_DWORD *)v3;
	if ( *(_DWORD *)v3 != 1146246220 && v4 != 1146308690 && v4 != 1146377044 )
		return 0;
	if ( sscanf(v3 + 4, "%d %d %d %d %d %d %d %d %d", &v13, &v12, &v11, &v18, &v17, &v16, &v15, &v10, &v14) != 9 )
		return 0;
	v5 = *(_DWORD *)v3;
	v6 = v14;
	if ( v5 == 1146246220 )
	{
		if ( v14 )
			return 0;
	}
	if ( v5 == 1146308690 && !v14 )
		return 0;
	v7 = v13;
	if ( !v13 )
		return 0;
	if ( v13 > 0x63 )
		return 0;
	v8 = v12;
	if ( v12 >= 3 || v11 > 3 || v18 < 0 || v17 < 0 || v16 < 0 || v15 < 0 )
		return 0;
	v2[23] = v11;
	*((_WORD *)v2 + 10) = v7;
	*((_WORD *)v2 + 12) = (unsigned char)v18;
	v2[22] = v8;
	*((_WORD *)v2 + 13) = (unsigned char)v17;
	*((_DWORD *)v2 + 10) = v6;
	*((_WORD *)v2 + 14) = (unsigned char)v16;
	*((_WORD *)v2 + 15) = (unsigned char)v15;
	*((_DWORD *)v2 + 8) = v10;
	return 1;
} */

// ref: 0x10003F6F
int __fastcall Connect_10003F6F(int a1, int a2, size_t a3) { return 0; }
/* {
	*(_DWORD *)a2 = dword_10029610;
	return _snprintf(
			   (char *)(a2 + 4),
			   a3,
			   " %d %d %d %d %d %d %d %d %d",
			   *(unsigned short *)(a1 + 20),
			   *(unsigned char *)(a1 + 22),
			   *(unsigned char *)(a1 + 23),
			   *(unsigned short *)(a1 + 24),
			   *(unsigned short *)(a1 + 26),
			   *(unsigned short *)(a1 + 28),
			   *(unsigned short *)(a1 + 30),
			   *(_DWORD *)(a1 + 32),
			   *(_DWORD *)(a1 + 40));
} */
// 10029610: using guessed type int dword_10029610;

// ref: 0x10003FB7
int __stdcall UiCreateGameCriteria(int a1, char *a2) { return 0; }
/* {
	return sprintf(a2, "#%d?%d", 3, *(unsigned short *)(a1 + 20));
} */

// ref: 0x10003FD6
int __stdcall UiCreatePlayerDescription(_uiheroinfo *info, int mode, char *desc) { return 0; }
/* {
	dword_10029610 = a2;
	Connect_10003F6F(a1, a3, 0x80u);
	return 1;
} */
// 10029610: using guessed type int dword_10029610;

// ref: 0x10003FF7
int __stdcall UiSetupPlayerInfo(char *str, _uiheroinfo *info, int mode) { return 0; }
/* {
	dword_10029610 = a3;
	SStrCopy(&unk_10029530, a1, 128);
	return Connect_10003F6F(a2, (int)byte_100294B0, 0x80u);
} */
// 100103E8: using guessed type int __stdcall SStrCopy(_DWORD, _DWORD, _DWORD);
// 10029610: using guessed type int dword_10029610;

// ref: 0x10004028
int __fastcall Connect_10004028(int a1, int a2, int a3, int a4) { return 0; }
/* {
	int result; // eax

	if ( a1 )
		result = SStrCopy(a1, &unk_10029530, a2);
	if ( a3 )
		result = SStrCopy(a3, byte_100294B0, a4);
	return result;
} */
// 100103E8: using guessed type int __stdcall SStrCopy(_DWORD, _DWORD, _DWORD);
