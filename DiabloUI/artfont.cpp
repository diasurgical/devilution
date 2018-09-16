// ref: 0x10001058
void UNKCALL artfont_10001058(char *arg) { return; }
/* {
	int v1; // ecx
	int v2; // ecx
	int v3; // ecx
	int v4; // ecx
	int v5; // ecx

	if ( arg )
	{
		v1 = (int)(arg - 2);
		if ( v1 )
		{
			v2 = v1 - 1;
			if ( v2 )
			{
				v3 = v2 - 1;
				if ( v3 )
				{
					v4 = v3 - 1;
					if ( v4 )
					{
						v5 = v4 - 1;
						if ( v5 )
						{
							if ( v5 == 1 )
								dword_100270C0 = (int)&unk_10028EF8;
							else
								dword_100270C0 = (int)&unk_100275D0;
						}
						else
						{
							dword_100270C0 = (int)&unk_10026BB8;
						}
					}
					else
					{
						dword_100270C0 = (int)&unk_100289F0;
					}
				}
				else
				{
					dword_100270C0 = (int)&unk_100270C8;
				}
			}
			else
			{
				dword_100270C0 = (int)&unk_10027AD8;
			}
		}
		else
		{
			dword_100270C0 = (int)&unk_100284E8;
		}
	}
	else
	{
		dword_100270C0 = (int)&unk_10027FE0;
	}
} */
// 100270C0: using guessed type int dword_100270C0;

// ref: 0x10001098
int artfont_10001098() { return 0; }
/* {
	int result; // eax

	result = 0;
	dword_100270BC = 0;
	dword_100293FC = 0;
	dword_100275CC = 0;
	dword_10028EF4 = 0;
	dword_100289EC = 0;
	dword_10027FDC = 0;
	dword_100284E4 = 0;
	dword_10027AD4 = 0;
	dword_100270C0 = 0;
	return result;
} */
// 100270BC: using guessed type int dword_100270BC;
// 100270C0: using guessed type int dword_100270C0;
// 100275CC: using guessed type int dword_100275CC;
// 10027AD4: using guessed type int dword_10027AD4;
// 10027FDC: using guessed type int dword_10027FDC;
// 100284E4: using guessed type int dword_100284E4;
// 100289EC: using guessed type int dword_100289EC;
// 10028EF4: using guessed type int dword_10028EF4;
// 100293FC: using guessed type int dword_100293FC;

// ref: 0x100010C8
int artfont_100010C8() { return 0; }
/* {
	int result; // eax

	artfont_10001120(&unk_10026BB8);
	artfont_10001120(&unk_10028EF8);
	artfont_10001120(&unk_100270C8);
	artfont_10001120(&unk_100289F0);
	artfont_10001120(&unk_100284E8);
	artfont_10001120(&unk_10027AD8);
	artfont_10001120(&unk_10027FE0);
	result = artfont_10001120(&unk_100275D0);
	dword_100270C0 = 0;
	return result;
} */
// 100270C0: using guessed type int dword_100270C0;

// ref: 0x10001120
int UNKCALL artfont_10001120(_DWORD *arg) { return 0; }
/* {
	_DWORD *v1; // edi
	int *v2; // esi
	signed int v3; // ebx
	int result; // eax

	v1 = arg;
	if ( arg[321] )
	{
		v2 = arg + 65;
		v3 = 256;
		do
		{
			result = *v2;
			if ( *v2 )
			{
				result = STransDelete(*v2);
				*v2 = 0;
			}
			++v2;
			--v3;
		}
		while ( v3 );
		v1[321] = 0;
	}
	return result;
} */
// 1001033A: using guessed type int __stdcall STransDelete(_DWORD);

// ref: 0x10001159
signed int artfont_10001159() { return 0; }
/* {
	artfont_100011FB((int)&unk_100270C8, (int)"ui_art\\font30.bin", (int)"ui_art\\font30g.pcx");
	artfont_100011FB((int)&unk_100289F0, (int)"ui_art\\font30.bin", (int)"ui_art\\font30s.pcx");
	artfont_100011FB((int)&unk_100284E8, (int)"ui_art\\font24.bin", (int)"ui_art\\font24g.pcx");
	artfont_100011FB((int)&unk_10027AD8, (int)"ui_art\\font24.bin", (int)"ui_art\\font24s.pcx");
	artfont_100011FB((int)&unk_10027FE0, (int)"ui_art\\font16.bin", (int)"ui_art\\font16g.pcx");
	artfont_100011FB((int)&unk_100275D0, (int)"ui_art\\font16.bin", (int)"ui_art\\font16s.pcx");
	artfont_100011FB((int)&unk_10026BB8, (int)"ui_art\\font42.bin", (int)"ui_art\\font42g.pcx");
	artfont_100011FB((int)&unk_10028EF8, (int)"ui_art\\font42.bin", (int)"ui_art\\font42y.pcx");
	return 1;
} */

// ref: 0x100011FB
void __fastcall artfont_100011FB(int a1, int a2, int a3) { return; }
/* {
	int v3; // esi
	int v4; // eax
	signed int v5; // edi
	unsigned char v6; // al
	int v7; // ecx
	int v8; // [esp+8h] [ebp-20h]
	int v9; // [esp+Ch] [ebp-1Ch]
	int v10; // [esp+10h] [ebp-18h]
	int v11; // [esp+14h] [ebp-14h]
	int v12; // [esp+18h] [ebp-10h]
	int v13; // [esp+1Ch] [ebp-Ch]
	int v14; // [esp+20h] [ebp-8h]
	int v15; // [esp+24h] [ebp-4h]
	int v16; // [esp+30h] [ebp+8h]

	v3 = a1;
	if ( !*(_DWORD *)(a1 + 1284) && SFileOpenFile(a2, &v15) )
	{
		v4 = SFileGetFileSize(v15, 0);
		if ( SFileReadFile(v15, v3, v4, 0, 0) )
		{
			SFileCloseFile(v15);
			local_100078BE(a3, &v14, &v12);
			memset((void *)(v3 + 260), 0, 0x400u);
			if ( v14 )
			{
				v5 = 0;
				v16 = v3 + 260;
				do
				{
					v6 = *(_BYTE *)(v3 + v5 + 2);
					if ( v6 )
					{
						v7 = *(unsigned char *)(v3 + 1);
						v10 = v6;
						v9 = v5 * v7;
						v8 = 0;
						v11 = v7 + v5 * v7 - 1;
						STransCreateI(v14, v12, v13, 8, &v8, 16777248, v16);
					}
					v16 += 4;
					++v5;
				}
				while ( v5 <= 256 );
				*(_DWORD *)(v3 + 1284) = 1;
				SMemFree(v14, "C:\\Src\\Diablo\\DiabloUI\\artfont.cpp", 206, 0);
			}
		}
		else
		{
			SFileCloseFile(v15);
		}
	}
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);
// 10010346: using guessed type int __stdcall STransCreateI(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 1001034C: using guessed type int __stdcall SFileCloseFile(_DWORD);
// 10010352: using guessed type int __stdcall SFileReadFile(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 10010358: using guessed type int __stdcall SFileGetFileSize(_DWORD, _DWORD);
// 1001035E: using guessed type int __stdcall SFileOpenFile(_DWORD, _DWORD);

// ref: 0x100012F6
int artfont_100012F6() { return 0; }
/* {
	int result; // eax

	if ( dword_100270C0 && *(_DWORD *)(dword_100270C0 + 1284) )
		result = *(unsigned char *)(dword_100270C0 + 1);
	else
		result = 0;
	return result;
} */
// 100270C0: using guessed type int dword_100270C0;

// ref: 0x10001310
int artfont_10001310() { return 0; }
/* {
	int result; // eax

	if ( dword_100270C0 && *(_DWORD *)(dword_100270C0 + 1284) )
		result = *(unsigned char *)dword_100270C0;
	else
		result = 0;
	return result;
} */
// 100270C0: using guessed type int dword_100270C0;

// ref: 0x10001329
int __fastcall artfont_10001329(unsigned char *a1) { return 0; }
/* {
	int result; // eax
	unsigned char i; // bl
	unsigned char v3; // bl
	int v4; // esi

	result = 0;
	if ( !dword_100270C0 || !*(_DWORD *)(dword_100270C0 + 1284) )
		return 0;
	for ( i = *a1; *a1; i = *a1 )
	{
		v3 = *(_BYTE *)(i + dword_100270C0 + 2);
		if ( v3 )
			v4 = v3;
		else
			v4 = *(unsigned char *)dword_100270C0;
		result += v4;
		++a1;
	}
	return result;
} */
// 100270C0: using guessed type int dword_100270C0;

// ref: 0x1000136C
signed int artfont_1000136C() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10026BB0 = 2139095040;
	return result;
} */
// 10026BB0: using guessed type int dword_10026BB0;

// ref: 0x10001377
int __fastcall artfont_10001377(unsigned char *a1) { return 0; }
/* {
	int result; // eax
	unsigned char v2; // dl
	unsigned char v3; // dl

	result = 0;
	if ( !dword_100270C0 || !*(_DWORD *)(dword_100270C0 + 1284) )
		return 0;
	while ( 1 )
	{
		v3 = *a1;
		if ( !*a1 )
			break;
		if ( v3 == 10 )
			break;
		if ( v3 == 32 )
			break;
		v2 = *(_BYTE *)(v3 + dword_100270C0 + 2);
		if ( !v2 )
			break;
		result += v2;
		++a1;
	}
	return result;
} */
// 100270C0: using guessed type int dword_100270C0;

// ref: 0x100013B3
int __cdecl artfont_100013B3(int a1) { return 0; }
/* {
	int result; // eax

	if ( a1 )
		result = SMemFree(a1, "delete", -1, 0);
	return result;
} */
// 10010340: using guessed type int __stdcall SMemFree(_DWORD, _DWORD, _DWORD, _DWORD);

// ref: 0x100013CD
void __fastcall artfont_100013CD(unsigned char *a1, _DWORD *a2, int a3, int a4) { return; }
/* {
	_DWORD *v4; // ebx
	unsigned char *v5; // esi
	unsigned char v6; // cl
	int v7; // edi
	unsigned char v8; // dl
	int v9; // edi
	int v10; // ecx
	int v11; // [esp+Ch] [ebp-8h]
	int v12; // [esp+Ch] [ebp-8h]
	unsigned char *v13; // [esp+10h] [ebp-4h]

	v4 = a2;
	v13 = a1;
	if ( a2 )
	{
		if ( *a2 )
		{
			v5 = (unsigned char *)dword_100270C0;
			if ( dword_100270C0 )
			{
				if ( *(_DWORD *)(dword_100270C0 + 1284) )
				{
					if ( a3 < 0 )
						a3 = 0;
					if ( a4 < 0 )
						a4 = 0;
					v6 = *a1;
					if ( *v13 )
					{
						while ( 1 )
						{
							v11 = a4 + v5[1];
							if ( a4 + v5[1] > v4[2] )
								return;
							if ( v6 == 10 )
								break;
							v7 = v6;
							v8 = v5[v6 + 2];
							if ( !v8 )
							{
								v9 = *v5;
								if ( a3 + v9 + artfont_10001377(++v13) < v4[1] )
								{
									a3 += v9;
								}
								else
								{
									a3 = 0;
									a4 = v11;
								}
								goto LABEL_23;
							}
							v12 = *(_DWORD *)&v5[4 * v6 + 260];
							if ( *(_DWORD *)&v5[4 * v6 + 260] )
							{
								v10 = v4[1];
								if ( a3 + v8 <= v10 )
								{
									STransBlt(*v4, a3, a4, v10, v12);
									v5 = (unsigned char *)dword_100270C0;
									a3 += *(unsigned char *)(v7 + dword_100270C0 + 2);
									goto LABEL_22;
								}
								a3 = 0;
								a4 += v5[1];
							}
LABEL_23:
							v6 = *v13;
							if ( !*v13 )
								return;
						}
						a3 = 0;
						a4 += v5[1];
LABEL_22:
						++v13;
						goto LABEL_23;
					}
				}
			}
		}
	}
} */
// 1001036A: using guessed type int __stdcall STransBlt(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 100270C0: using guessed type int dword_100270C0;
