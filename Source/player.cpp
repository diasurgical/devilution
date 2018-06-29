//HEADER_GOES_HERE

#include "../types.h"

int plr_lframe_size; // idb
int plr_wframe_size; // idb
char plr_gfx_flag; // weak
int player_cpp_init_value; // weak
int plr_aframe_size; // idb
int myplr;
PlayerStruct plr[4];
int plr_fframe_size; // idb
int plr_qframe_size; // idb
int deathflag; // idb
int plr_hframe_size; // idb
int plr_bframe_size; // idb
char plr_gfx_bflag; // weak
int plr_sframe_size; // idb
int deathdelay; // weak
int plr_dframe_size; // idb

int player_inf = 0x7F800000; // weak
char ArmourChar[4] = { 'L', 'M', 'H', 0 };
char WepChar[10] = { 'N', 'U', 'S', 'D', 'B', 'A', 'M', 'H', 'T', 0 };
char CharChar[4] = { 'W', 'R', 'S', 0 };

/* rdata */

int plrxoff[9] = { 0, 2, 0, 2, 1, 0, 1, 2, 1 };
int plryoff[9] = { 0, 2, 2, 0, 1, 1, 0, 1, 2 };
int plrxoff2[9] = { 0, 1, 0, 1, 2, 0, 1, 2, 2 };
int plryoff2[9] = { 0, 0, 1, 1, 0, 2, 2, 1, 2 };
char PlrGFXAnimLens[3][11] =
{
  { 10, 16, 8, 2, 20, 20, 6, 20, 8, 9, 14 },
  { 8, 18, 8, 4, 20, 16, 7, 20, 8, 10, 12 },
  { 8, 16, 8, 6, 20, 12, 8, 20, 8, 12, 8 }
};
int PWVel[4][3] = { { 2048, 1024, 512 }, { 2048, 1024, 512 }, { 2048, 1024, 512 }, { 8, 8, 8 } };
int StrengthTbl[3] = { 30, 20, 15 };
int MagicTbl[3] = { 10, 15, 35 };
int DexterityTbl[3] = { 20, 30, 15 };
int VitalityTbl[3] = { 25, 20, 20 };
int ToBlkTbl[3] = { 30, 20, 10 };
char *ClassStrTblOld[3] = { "Warrior", "Rogue", "Sorceror" }; // unused
int MaxStats[3][4] = { { 250, 50, 60, 100 }, { 55, 70, 250, 80 }, { 45, 250, 85, 80 } };
int ExpLvlsTbl[51] =
{
  0,
  2000,
  4620,
  8040,
  12489,
  18258,
  25712,
  35309,
  47622,
  63364,
  83419,
  108879,
  141086,
  181683,
  231075,
  313656,
  424067,
  571190,
  766569,
  1025154,
  1366227,
  1814568,
  2401895,
  3168651,
  4166200,
  5459523,
  7130496,
  9281874,
  12042092,
  15571031,
  20066900,
  25774405,
  32994399,
  42095202,
  53525811,
  67831218,
  85670061,
  107834823,
  135274799,
  169122009,
  210720231,
  261657253,
  323800420,
  399335440,
  490808349,
  601170414,
  733825617,
  892680222,
  1082908612,
  1310707109,
  1583495809
};
char *ClassStrTbl[3] = { "Warrior", "Rogue", "Sorceror" };
unsigned char fix[9] = { 0u, 0u, 3u, 3u, 3u, 6u, 6u, 6u, 8u }; /* PM_ChangeLightOff local type */

struct player_cpp_init
{
	player_cpp_init()
	{
		player_cpp_init_value = player_inf;
	}
} _player_cpp_init;
// 47F204: using guessed type int player_inf;
// 68643C: using guessed type int player_cpp_init_value;

void __fastcall player_init_cl2_hdrs(char *src, char *dst)
{
	char *v2; // eax
	int v3; // esi
	signed int v4; // edx

	v2 = dst;
	v3 = src - dst;
	v4 = 8;
	do
	{
		*(_DWORD *)v2 = (unsigned int)&src[*(_DWORD *)&v2[v3]];
		v2 += 4;
		--v4;
	}
	while ( v4 );
}

void __fastcall LoadPlrGFX(int pnum, int gfxflag)
{
	int v2; // esi
	PlayerStruct *v3; // esi
	unsigned int v4; // ecx
	char v5; // al
	void *v6; // edi
	char *v7; // ebx
	int v8; // ecx
	int v9; // ecx
	int v10; // ecx
	int v11; // ecx
	int v12; // ecx
	int v13; // ecx
	char arglist[256]; // [esp+Ch] [ebp-120h]
	char v15[16]; // [esp+10Ch] [ebp-20h]
	int v16; // [esp+11Ch] [ebp-10h]
	char *v17; // [esp+120h] [ebp-Ch]
	unsigned int v18; // [esp+124h] [ebp-8h]
	const char *v19; // [esp+128h] [ebp-4h]

	v2 = pnum;
	v16 = gfxflag;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("LoadPlrGFX: illegal player %d", pnum);
	v3 = &plr[v2];
	sprintf(
		v15,
		"%c%c%c",
		CharChar[SLOBYTE(v3->_pClass)],
		ArmourChar[v3->_pgfxnum >> 4],
		WepChar[v3->_pgfxnum & 0xF]);
	v4 = 1;
	v17 = ClassStrTbl[SLOBYTE(v3->_pClass)];
	v5 = leveltype;
	v6 = v17;
	v7 = v17;
	v18 = 1;
	do
	{
		if ( !(v4 & v16) )
			goto LABEL_38;
		if ( v4 <= 0x10 )
		{
			if ( v4 == 16 )
			{
				if ( !v5 )
					goto LABEL_38;
				v6 = v3->_pLData;
				v19 = "LM";
				v7 = (char *)v3->_pLAnim;
			}
			else
			{
				v8 = v4 - 1;
				if ( v8 )
				{
					v9 = v8 - 1;
					if ( v9 )
					{
						v10 = v9 - 2;
						if ( v10 )
						{
							if ( v10 == 4 )
							{
								if ( !v5 )
									goto LABEL_38;
								v6 = v3->_pHData;
								v19 = "HT";
								v7 = (char *)v3->_pHAnim;
							}
							else
							{
LABEL_27:
								TermMsg("PLR:2");
							}
						}
						else
						{
							if ( !v5 )
								goto LABEL_38;
							v6 = v3->_pAData;
							v19 = "AT";
							v7 = (char *)v3->_pAAnim;
						}
					}
					else
					{
						v19 = "AW";
						if ( !v5 )
							v19 = "WL";
						v6 = v3->_pWData;
						v7 = (char *)v3->_pWAnim;
					}
				}
				else
				{
					v19 = "AS";
					if ( !v5 )
						v19 = "ST";
					v6 = v3->_pNData;
					v7 = (char *)v3->_pNAnim;
				}
			}
LABEL_37:
			sprintf(arglist, "PlrGFX\\%s\\%s\\%s%s.CL2", v17, v15, v15, v19);
			LoadFileWithMem(arglist, v6);
			player_init_cl2_hdrs((char *)v6, v7);
			v3->_pGFXLoad |= v18;
			v5 = leveltype;
			goto LABEL_38;
		}
		v11 = v4 - 32;
		if ( !v11 )
		{
			if ( !v5 )
				goto LABEL_38;
			v6 = v3->_pFData;
			v19 = "FM";
			v7 = (char *)v3->_pFAnim;
			goto LABEL_37;
		}
		v12 = v11 - 32;
		if ( !v12 )
		{
			if ( !v5 )
				goto LABEL_38;
			v6 = v3->_pTData;
			v19 = "QM";
			v7 = (char *)v3->_pTAnim;
			goto LABEL_37;
		}
		v13 = v12 - 64;
		if ( !v13 )
		{
			if ( v3->_pgfxnum & 0xF )
				goto LABEL_38;
			v6 = v3->_pDData;
			v19 = "DT";
			v7 = (char *)v3->_pDAnim;
			goto LABEL_37;
		}
		if ( v13 != 128 )
			goto LABEL_27;
		if ( v5 && v3->_pBlockFlag )
		{
			v6 = v3->_pBData;
			v19 = "BL";
			v7 = (char *)v3->_pBAnim;
			goto LABEL_37;
		}
LABEL_38:
		v4 = 2 * v18;
		v18 *= 2;
	}
	while ( v18 <= 0x17F );
}
// 5BB1ED: using guessed type char leveltype;

void __fastcall InitPlayerGFX(int pnum)
{
	int v1; // esi
	int v2; // edx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("InitPlayerGFX: illegal player %d", pnum);
	if ( plr[v1]._pHitPoints & 0xFFFFFFC0 )
	{
		v2 = 0x17F;
	}
	else
	{
		plr[v1]._pgfxnum = 0;
		v2 = 0x80;
	}
	LoadPlrGFX(v1, v2);
}

void __fastcall InitPlrGFXMem(int pnum)
{
	int v1; // esi
	unsigned int v2; // ebp
	unsigned int v3; // eax
	char *v4; // ecx
	int v5; // esi
	void *v6; // eax
	bool v7; // zf
	unsigned int v8; // ebx
	unsigned int v9; // eax
	char *v10; // ecx
	void *v11; // eax
	void *v12; // eax
	void *v13; // eax
	void *v14; // eax
	void *v15; // eax
	void *v16; // eax
	void *v17; // eax
	void *v18; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("InitPlrGFXMem: illegal player %d", pnum);
	if ( !(plr_gfx_flag & 1) )
	{
		plr_gfx_flag |= 1u;
		v2 = GetPlrGFXSize("ST");
		v3 = GetPlrGFXSize("AS");
		v4 = "AS";
		if ( v3 <= v2 )
			v4 = "ST";
		plr_sframe_size = GetPlrGFXSize(v4);
	}
	v5 = v1;
	v6 = DiabloAllocPtr(plr_sframe_size);
	v7 = (plr_gfx_flag & 2) == 0;
	plr[v5]._pNData = v6;
	if ( v7 )
	{
		plr_gfx_flag |= 2u;
		v8 = GetPlrGFXSize("WL");
		v9 = GetPlrGFXSize("AW");
		v10 = "AW";
		if ( v9 <= v8 )
			v10 = "WL";
		plr_wframe_size = GetPlrGFXSize(v10);
	}
	v11 = DiabloAllocPtr(plr_wframe_size);
	v7 = (plr_gfx_flag & 4) == 0;
	plr[v5]._pWData = v11;
	if ( v7 )
	{
		plr_gfx_flag |= 4u;
		plr_aframe_size = GetPlrGFXSize("AT");
	}
	v12 = DiabloAllocPtr(plr_aframe_size);
	v7 = (plr_gfx_flag & 8) == 0;
	plr[v5]._pAData = v12;
	if ( v7 )
	{
		plr_gfx_flag |= 8u;
		plr_hframe_size = GetPlrGFXSize("HT");
	}
	v13 = DiabloAllocPtr(plr_hframe_size);
	v7 = (plr_gfx_flag & 0x10) == 0;
	plr[v5]._pHData = v13;
	if ( v7 )
	{
		plr_gfx_flag |= 0x10u;
		plr_lframe_size = GetPlrGFXSize("LM");
	}
	v14 = DiabloAllocPtr(plr_lframe_size);
	v7 = (plr_gfx_flag & 0x20) == 0;
	plr[v5]._pLData = v14;
	if ( v7 )
	{
		plr_gfx_flag |= 0x20u;
		plr_fframe_size = GetPlrGFXSize("FM");
	}
	v15 = DiabloAllocPtr(plr_fframe_size);
	v7 = (plr_gfx_flag & 0x40) == 0;
	plr[v5]._pFData = v15;
	if ( v7 )
	{
		plr_gfx_flag |= 0x40u;
		plr_qframe_size = GetPlrGFXSize("QM");
	}
	v16 = DiabloAllocPtr(plr_qframe_size);
	v7 = plr_gfx_flag >= 0;
	plr[v5]._pTData = v16;
	if ( v7 )
	{
		plr_gfx_flag |= 0x80u;
		plr_dframe_size = GetPlrGFXSize("DT");
	}
	v17 = DiabloAllocPtr(plr_dframe_size);
	v7 = (plr_gfx_bflag & 1) == 0;
	plr[v5]._pDData = v17;
	if ( v7 )
	{
		plr_gfx_bflag |= 1u;
		plr_bframe_size = GetPlrGFXSize("BL");
	}
	v18 = DiabloAllocPtr(plr_bframe_size);
	plr[v5]._pGFXLoad = 0;
	plr[v5]._pBData = v18;
}
// 686438: using guessed type char plr_gfx_flag;
// 69B7BC: using guessed type char plr_gfx_bflag;

int __fastcall GetPlrGFXSize(char *szCel)
{
	unsigned int v1; // ebx
	char *v2; // edi
	char *v3; // esi
	char dwInitParam[256]; // [esp+Ch] [ebp-124h]
	char v6[16]; // [esp+10Ch] [ebp-24h]
	unsigned int v7; // [esp+11Ch] [ebp-14h]
	char *v8; // [esp+120h] [ebp-10h]
	void *a1; // [esp+124h] [ebp-Ch]
	char **v10; // [esp+128h] [ebp-8h]
	unsigned int v11; // [esp+12Ch] [ebp-4h]

	v1 = 0;
	v8 = szCel;
	v11 = 0;
	v10 = ClassStrTbl;
	do
	{
		v2 = ArmourChar;
		do
		{
			v3 = WepChar;
			do
			{
				sprintf(v6, "%c%c%c", CharChar[v1], *v2, *v3);
				sprintf(dwInitParam, "PlrGFX\\%s\\%s\\%s%s.CL2", *v10, v6, v6, v8);
				if ( WOpenFile(dwInitParam, &a1, 1) )
				{
					v7 = WGetFileSize(a1, 0);
					WCloseFile(a1);
					if ( v11 <= v7 )
						v11 = v7;
				}
				++v3;
			}
			while ( *v3 );
			++v2;
		}
		while ( *v2 );
		++v10;
		++v1;
	}
	while ( v1 < 3 );
	return v11;
}

void __fastcall FreePlayerGFX(int pnum)
{
	int v1; // esi
	int v2; // esi
	void *v3; // ecx
	void *v4; // ecx
	void *v5; // ecx
	void *v6; // ecx
	void *v7; // ecx
	void *v8; // ecx
	void *v9; // ecx
	void *v10; // ecx
	void *v11; // ecx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("FreePlayerGFX: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v2]._pNData;
	plr[v2]._pNData = 0;
	mem_free_dbg(v3);
	v4 = plr[v2]._pWData;
	plr[v2]._pWData = 0;
	mem_free_dbg(v4);
	v5 = plr[v2]._pAData;
	plr[v2]._pAData = 0;
	mem_free_dbg(v5);
	v6 = plr[v2]._pHData;
	plr[v2]._pHData = 0;
	mem_free_dbg(v6);
	v7 = plr[v2]._pLData;
	plr[v2]._pLData = 0;
	mem_free_dbg(v7);
	v8 = plr[v2]._pFData;
	plr[v2]._pFData = 0;
	mem_free_dbg(v8);
	v9 = plr[v2]._pTData;
	plr[v2]._pTData = 0;
	mem_free_dbg(v9);
	v10 = plr[v2]._pDData;
	plr[v2]._pDData = 0;
	mem_free_dbg(v10);
	v11 = plr[v2]._pBData;
	plr[v2]._pBData = 0;
	mem_free_dbg(v11);
	plr[v2]._pGFXLoad = 0;
}

void __fastcall NewPlrAnim(int pnum, int Peq, int numFrames, int Delay, int width)
{
	int v5; // edi
	int v6; // esi
	int v7; // eax

	v5 = pnum;
	v6 = Peq;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("NewPlrAnim: illegal player %d", pnum);
	v7 = v5;
	plr[v7]._pAnimLen = numFrames;
	plr[v7]._pAnimCnt = 0;
	plr[v7]._pAnimDelay = Delay;
	plr[v7]._pAnimData = v6;
	plr[v7]._pAnimWidth = width;
	plr[v7]._pAnimFrame = 1;
	plr[v7]._pAnimWidth2 = (width - 64) >> 1;
}

void __fastcall ClearPlrPVars(int pnum)
{
	int v1; // esi
	int v2; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("ClearPlrPVars: illegal player %d", pnum);
	v2 = v1;
	plr[v2]._pVar1 = 0;
	plr[v2]._pVar2 = 0;
	plr[v2]._pVar3 = 0;
	plr[v2]._pVar4 = 0;
	plr[v2]._pVar5 = 0;
	plr[v2]._pVar6 = 0;
	plr[v2]._pVar7 = 0;
	plr[v2]._pVar8 = 0;
}

void __fastcall SetPlrAnims(int pnum)
{
	int v1; // esi
	char v2; // bl
	int v3; // eax
	int v4; // esi
	int v5; // ecx
	bool v6; // zf
	int v7; // ecx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlrAnims: illegal player %d", pnum);
	v2 = leveltype;
	v3 = v1;
	v4 = SLOBYTE(plr[v1]._pClass);
	v5 = v4;
	v6 = leveltype == DTYPE_TOWN;
	plr[v3]._pNWidth = 96;
	plr[v3]._pWWidth = 96;
	plr[v3]._pAWidth = 128;
	plr[v3]._pHWidth = 96;
	plr[v3]._pSWidth = 96;
	plr[v3]._pDWidth = 128;
	plr[v3]._pBWidth = 96;
	if ( v6 )
	{
		plr[v3]._pNFrames = PlrGFXAnimLens[v5][7];
		plr[v3]._pWFrames = PlrGFXAnimLens[v5][8];
		plr[v3]._pDFrames = PlrGFXAnimLens[v5][4];
		plr[v3]._pSFrames = PlrGFXAnimLens[v5][5];
	}
	else
	{
		plr[v3]._pNFrames = PlrGFXAnimLens[v5][0];
		plr[v3]._pWFrames = PlrGFXAnimLens[v5][2];
		plr[v3]._pAFrames = PlrGFXAnimLens[v5][1];
		plr[v3]._pHFrames = PlrGFXAnimLens[v5][6];
		plr[v3]._pSFrames = PlrGFXAnimLens[v5][5];
		plr[v3]._pDFrames = PlrGFXAnimLens[v5][4];
		plr[v3]._pBFrames = PlrGFXAnimLens[v5][3];
		plr[v3]._pAFNum = PlrGFXAnimLens[v5][9];
	}
	plr[v3]._pSFNum = PlrGFXAnimLens[v5][10];
	v7 = plr[v3]._pgfxnum & 0xF;
	if ( !v4 )
	{
		if ( v7 == 4 )
		{
			if ( v2 )
				plr[v3]._pNFrames = 8;
			plr[v3]._pAWidth = 96;
			goto LABEL_11;
		}
		if ( v7 == 5 )
		{
			plr[v3]._pAFrames = 20;
			plr[v3]._pAFNum = 10;
			return;
		}
LABEL_19:
		if ( v7 == 8 )
		{
			plr[v3]._pAFrames = 16;
LABEL_11:
			plr[v3]._pAFNum = 11;
			return;
		}
		return;
	}
	if ( v4 == 1 )
	{
		if ( v7 == 5 )
		{
			plr[v3]._pAFrames = 22;
			plr[v3]._pAFNum = 13;
			return;
		}
		if ( v7 == 4 )
		{
			plr[v3]._pAFrames = 12;
			plr[v3]._pAFNum = 7;
			return;
		}
		goto LABEL_19;
	}
	if ( v4 != 2 )
		return;
	plr[v3]._pSWidth = 128;
	switch ( v7 )
	{
		case 0:
			plr[v3]._pAFrames = 20;
			return;
		case 1:
			plr[v3]._pAFNum = 9;
			return;
		case 4:
			plr[v3]._pAFrames = 20;
			break;
		case 5:
			plr[v3]._pAFrames = 24;
			break;
		default:
			return;
	}
	plr[v3]._pAFNum = 16;
}
// 5BB1ED: using guessed type char leveltype;

void __fastcall ClearPlrRVars(PlayerStruct *pPlayer)
{
	pPlayer->bReserved[0] = 0;
	pPlayer->bReserved[1] = 0;
	pPlayer->bReserved[2] = 0;
	pPlayer->wReserved[0] = 0;
	pPlayer->wReserved[1] = 0;
	pPlayer->wReserved[2] = 0;
	pPlayer->wReserved[3] = 0;
	pPlayer->wReserved[4] = 0;
	pPlayer->wReserved[5] = 0;
	pPlayer->wReserved[6] = 0;
	pPlayer->wReserved[7] = 0;
	pPlayer->dwReserved[0] = 0;
	pPlayer->dwReserved[1] = 0;
	pPlayer->dwReserved[2] = 0;
	pPlayer->dwReserved[3] = 0;
	pPlayer->dwReserved[4] = 0;
	pPlayer->dwReserved[5] = 0;
	pPlayer->dwReserved[6] = 0;
}

void __fastcall CreatePlayer(int pnum, char c)
{
	unsigned int v2; // edi
	char v3; // bl
	int v4; // esi
	int v5; // eax
	int v6; // ecx
	char v7; // al
	char v8; // al
	char v9; // al
	char v10; // al
	int v11; // edi
	signed int v12; // ebp
	int v13; // eax
	int v14; // eax
	int v15; // eax
	int v16; // eax
	int v17; // eax
	bool v18; // zf
	char v19; // [esp+Ch] [ebp-8h]
	int arglist; // [esp+10h] [ebp-4h]

	v2 = pnum;
	v3 = c;
	v4 = pnum;
	v19 = c;
	arglist = pnum;
	ClearPlrRVars(&plr[pnum]);
	v5 = GetTickCount();
	SetRndSeed(v5);
	if ( v2 >= 4 )
		TermMsg("CreatePlayer: illegal player %d", v2);
	v6 = v3;
	_LOBYTE(plr[v4]._pClass) = v3;
	v7 = StrengthTbl[v6];
	if ( v7 < 0 )
		v7 = 0;
	plr[v4]._pStrength = v7;
	plr[v4]._pBaseStr = v7;
	v8 = MagicTbl[v6];
	if ( v8 < 0 )
		v8 = 0;
	plr[v4]._pMagic = v8;
	plr[v4]._pBaseMag = v8;
	v9 = DexterityTbl[v6];
	if ( v9 < 0 )
		v9 = 0;
	plr[v4]._pDexterity = v9;
	plr[v4]._pBaseDex = v9;
	v10 = VitalityTbl[v6];
	if ( v10 < 0 )
		v10 = 0;
	v11 = v10;
	plr[v4]._pVitality = v10;
	plr[v4]._pBaseVit = v10;
	plr[v4]._pStatPts = 0;
	plr[v4].pTownWarps = 0;
	plr[v4].pDungMsgs = 0;
	plr[v4].pLvlLoad = 0;
	plr[v4].pDiabloKillLevel = 0;
	if ( v19 == 1 )
	{
		v12 = 200;
		v13 = plr[v4]._pLevel * (plr[v4]._pStrength + plr[v4]._pDexterity);
	}
	else
	{
		v13 = plr[v4]._pStrength * plr[v4]._pLevel;
		v12 = 100;
	}
	plr[v4]._pDamageMod = v13 / v12;
	plr[v4]._pBaseToBlk = ToBlkTbl[v6];
	plr[v4]._pHitPoints = (v11 + 10) << 6;
	if ( !v19 )
		plr[v4]._pHitPoints = (v11 + 10) << 7;
	if ( v19 == 1 )
		plr[v4]._pHitPoints += plr[v4]._pHitPoints >> 1;
	v14 = plr[v4]._pHitPoints;
	plr[v4]._pMaxHP = v14;
	plr[v4]._pHPBase = v14;
	plr[v4]._pMaxHPBase = v14;
	v15 = plr[v4]._pMagic << 6;
	plr[v4]._pMana = v15;
	if ( v19 == 2 )
		plr[v4]._pMana = 2 * v15;
	if ( v19 == 1 )
		plr[v4]._pMana += plr[v4]._pMana >> 1;
	v16 = plr[v4]._pMana;
	plr[v4]._pMaxMana = v16;
	plr[v4]._pManaBase = v16;
	plr[v4]._pMaxManaBase = v16;
	v17 = ExpLvlsTbl[1];
	plr[v4]._pLevel = 1;
	plr[v4]._pMaxLvl = 1;
	plr[v4]._pExperience = 0;
	plr[v4]._pMaxExp = 0;
	plr[v4]._pNextExper = v17;
	plr[v4]._pArmorClass = 0;
	plr[v4]._pMagResist = 0;
	plr[v4]._pFireResist = 0;
	plr[v4]._pLghtResist = 0;
	plr[v4]._pLightRad = 10;
	plr[v4]._pInfraFlag = 0;
	if ( !v19 )
	{
		plr[v4]._pAblSpells[0] = 0x2000000;
LABEL_26:
		plr[v4]._pAblSpells[1] = 0;
LABEL_27:
		plr[v4]._pMemSpells[0] = 0;
		goto LABEL_28;
	}
	if ( v19 == 1 )
	{
		plr[v4]._pAblSpells[0] = 0x8000000;
		goto LABEL_26;
	}
	if ( v19 != 2 )
		goto LABEL_27;
	plr[v4]._pAblSpells[0] = 0x4000000;
	plr[v4]._pAblSpells[1] = 0;
	plr[v4]._pMemSpells[0] = 1;
LABEL_28:
	plr[v4]._pMemSpells[1] = 0;
	memset(plr[v4]._pSplLvl, 0, sizeof(plr[v4]._pSplLvl));
	v18 = _LOBYTE(plr[v4]._pClass) == 2;
	_LOBYTE(plr[v4]._pSpellFlags) = 0;
	if ( v18 )
		plr[v4]._pSplLvl[1] = 2;
	plr[v4]._pSplHotKey[0] = -1;
	plr[v4]._pSplHotKey[1] = -1;
	plr[v4]._pSplHotKey[2] = -1;
	if ( v19 )
	{
		if ( v19 == 1 )
		{
			plr[v4]._pgfxnum = 4;
		}
		else if ( v19 == 2 )
		{
			plr[v4]._pgfxnum = 8;
		}
	}
	else
	{
		plr[v4]._pgfxnum = 3;
	}
	*(_DWORD *)plr[v4]._pLvlVisited = 0;
	*(_DWORD *)&plr[v4]._pLvlVisited[4] = 0;
	*(_DWORD *)&plr[v4]._pLvlVisited[8] = 0;
	*(_DWORD *)&plr[v4]._pLvlVisited[12] = 0;
	plr[v4]._pLvlVisited[16] = 0;
	*(_DWORD *)plr[v4]._pSLvlVisited = 0;
	*(_DWORD *)&plr[v4]._pSLvlVisited[4] = 0;
	*(_WORD *)&plr[v4]._pSLvlVisited[8] = 0;
	plr[v4]._pLvlChanging = 0;
	plr[v4].pTownWarps = 0;
	plr[v4].pLvlLoad = 0;
	plr[v4].pBattleNet = 0;
	plr[v4].pManaShield = 0;
	InitDungMsgs(arglist);
	CreatePlrItems(arglist);
	SetRndSeed(0);
}

int __fastcall CalcStatDiff(int pnum)
{
	int v1; // ecx
	int v2; // edx

	v1 = pnum;
	v2 = SLOBYTE(plr[v1]._pClass);
	return MaxStats[v2][0]
		 + MaxStats[v2][1]
		 + MaxStats[v2][2]
		 + MaxStats[v2][3]
		 - plr[v1]._pBaseVit
		 - plr[v1]._pBaseDex
		 - plr[v1]._pBaseMag
		 - plr[v1]._pBaseStr;
}

void __fastcall NextPlrLevel(int pnum)
{
	int v1; // edi
	int v2; // esi
	char *v3; // eax
	char v4; // bl
	int v5; // eax
	char v6; // bl
	char v7; // al
	signed int v8; // edx
	int v9; // ebp
	signed int v10; // eax
	int v11; // edx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("NextPlrLevel: illegal player %d", pnum);
	v2 = v1;
	v3 = &plr[v1]._pLevel;
	v4 = ++*v3;
	++plr[v2]._pMaxLvl;
	if ( CalcStatDiff(v1) >= 5 )
		plr[v2]._pStatPts += 5;
	else
		plr[v2]._pStatPts = CalcStatDiff(v1);
	v5 = v4;
	v6 = gbMaxPlayers;
	plr[v2]._pNextExper = ExpLvlsTbl[v5];
	v7 = plr[v2]._pClass;
	v8 = v7 != 2 ? 128 : 64;
	if ( v6 == 1 )
		v8 = v7 != 2 ? 129 : 65;
	v9 = myplr;
	plr[v2]._pMaxHP += v8;
	plr[v2]._pHitPoints = plr[v2]._pMaxHP;
	plr[v2]._pMaxHPBase += v8;
	plr[v2]._pHPBase = plr[v2]._pMaxHPBase;
	if ( v1 == v9 )
		drawhpflag = 1;
	v10 = v7 != 0 ? 128 : 64;
	if ( v6 == 1 )
		++v10;
	plr[v2]._pMaxMana += v10;
	plr[v2]._pMaxManaBase += v10;
	v11 = plr[v2]._pMaxManaBase;
	if ( !(plr[v1]._pIFlags & 0x8000000) )
	{
		plr[v2]._pMana = plr[v2]._pMaxMana;
		plr[v2]._pManaBase = v11;
	}
	if ( v1 == v9 )
		drawmanaflag = 1;
}
// 679660: using guessed type char gbMaxPlayers;

void __fastcall AddPlrExperience(int pnum, int lvl, int exp)
{
	int v3; // eax
	int v4; // esi
	int v5; // esi
	char v6; // bl
	int v7; // edi
	signed int v8; // ecx
	int v9; // ecx
	int *v10; // eax
	int v11; // eax
	int v12; // ecx
	int v13; // ecx
	int v14; // esi
	int arglist; // [esp+4h] [ebp-Ch]
	int v16; // [esp+8h] [ebp-8h]

	v3 = myplr;
	v4 = pnum;
	v16 = lvl;
	arglist = pnum;
	if ( pnum == myplr )
	{
		if ( (unsigned int)myplr >= 4 )
		{
			TermMsg("AddPlrExperience: illegal player %d", myplr);
			v3 = myplr;
		}
		if ( plr[v3]._pHitPoints > 0 )
		{
			v5 = v4;
			v6 = plr[v5]._pLevel;
			v7 = (signed __int64)((((double)v16 - (double)v6) * 0.1 + 1.0) * (double)exp);
			if ( v7 < 0 )
				v7 = 0;
			if ( (unsigned char)gbMaxPlayers > 1u )
			{
				if ( v6 >= 0 )
				{
					v8 = v6;
					if ( v6 >= 50 )
						v8 = 50;
				}
				else
				{
					v8 = 0;
				}
				if ( v7 >= ExpLvlsTbl[v8] / 20 )
					v7 = ExpLvlsTbl[v8] / 20;
				v9 = 200 * v8;
				if ( v7 >= v9 )
					v7 = v9;
			}
			v10 = &plr[v5]._pExperience;
			*v10 += v7;
			if ( plr[v5]._pExperience > 2000000000u )
				*v10 = 2000000000;
			v11 = *v10;
			if ( v11 < ExpLvlsTbl[49] )
			{
				v12 = 0;
				if ( v11 >= ExpLvlsTbl[0] )
				{
					do
						++v12;
					while ( v11 >= ExpLvlsTbl[v12] );
				}
				if ( v12 != v6 )
				{
					v13 = v12 - v6;
					if ( v13 > 0 )
					{
						v14 = v13;
						do
						{
							NextPlrLevel(arglist);
							--v14;
						}
						while ( v14 );
					}
				}
				NetSendCmdParam1(0, CMD_PLRLEVEL, plr[myplr]._pLevel);
			}
			else
			{
				plr[v5]._pLevel = 50;
			}
		}
	}
}
// 679660: using guessed type char gbMaxPlayers;

void __fastcall AddPlrMonstExper(int lvl, int exp, char pmask)
{
	int v3; // ebx
	int v4; // edi
	signed int v5; // ecx

	v3 = lvl;
	v4 = 0;
	v5 = 0;
	do
	{
		if ( (1 << v5) & pmask )
			++v4;
		++v5;
	}
	while ( v5 < 4 );
	if ( v4 )
	{
		if ( (1 << myplr) & pmask )
			AddPlrExperience(myplr, v3, exp / v4);
	}
}

void __fastcall InitPlayer(int pnum, bool FirstTime)
{
	int v2; // ebx
	int v3; // esi
	PlayerStruct *v4; // edi
	int v5; // eax
	int v6; // ST08_4
	int v7; // ecx
	int v8; // eax
	int v9; // ecx
	int v10; // ST08_4
	int v11; // edx
	int v12; // eax
	unsigned int v13; // edi
	bool v14; // zf
	int v15; // eax
	int v16; // ecx
	int v17; // edx
	char v18; // al
	int v19; // eax
	BOOL v20; // [esp+8h] [ebp-4h]

	v2 = pnum;
	v20 = FirstTime;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("InitPlayer: illegal player %d", pnum);
	v3 = v2;
	v4 = &plr[v2];
	ClearPlrRVars(&plr[v2]);
	if ( v20 )
	{
		v5 = plr[v3]._pgfxnum;
		plr[v3]._pRSpell = -1;
		plr[v3]._pSBkSpell = -1;
		plr[v3]._pSpell = -1;
		_LOBYTE(plr[v3]._pRSplType) = 4;
		plr[v3]._pSplType = 4;
		plr[v3]._pwtype = (v5 & 0xF) == 4;
		plr[v3].pManaShield = 0;
	}
	if ( plr[v3].plrlevel == currlevel || leveldebug )
	{
		SetPlrAnims(v2);
		plr[v3]._pxoff = 0;
		plr[v3]._pyoff = 0;
		plr[v3]._pxvel = 0;
		plr[v3]._pyvel = 0;
		ClearPlrPVars(v2);
		if ( (signed int)(plr[v3]._pHitPoints & 0xFFFFFFC0) <= 0 )
		{
			v10 = plr[v3]._pDWidth;
			v11 = plr[v3]._pDAnim[0];
			v4->_pmode = 8;
			NewPlrAnim(v2, v11, plr[v3]._pDFrames, 1, v10);
			v12 = plr[v3]._pAnimLen;
			plr[v3]._pAnimFrame = v12 - 1;
			plr[v3]._pVar8 = 2 * v12;
		}
		else
		{
			v6 = plr[v3]._pNWidth;
			v4->_pmode = 0;
			NewPlrAnim(v2, plr[v3]._pNAnim[0], plr[v3]._pNFrames, 3, v6);
			_LOBYTE(v7) = 2;
			v8 = random(v7, plr[v3]._pNFrames - 1);
			_LOBYTE(v9) = 2;
			plr[v3]._pAnimFrame = v8 + 1;
			plr[v3]._pAnimCnt = random(v9, 3);
		}
		v13 = 0;
		v14 = v2 == myplr;
		plr[v3]._pdir = 0;
		plr[v3]._peflag = 0;
		if ( v14 )
		{
			if ( !v20 || currlevel )
			{
				plr[v3].WorldX = ViewX;
				plr[v3].WorldY = ViewY;
			}
			plr[v3]._ptargx = plr[v3].WorldX;
			plr[v3]._ptargy = plr[v3].WorldY;
		}
		else
		{
			plr[v3]._ptargx = plr[v3].WorldX;
			plr[v3]._ptargy = plr[v3].WorldY;
			do
			{
				if ( PosOkPlayer(v2, plr[v3].WorldX + plrxoff2[v13], plr[v3].WorldY + plryoff2[v13]) )
					break;
				++v13;
			}
			while ( v13 < 8 );
			v15 = plryoff2[v13];
			plr[v3].WorldX += plrxoff2[v13];
			plr[v3].WorldY += v15;
		}
		v16 = plr[v3].WorldX;
		v17 = plr[v3].WorldY;
		plr[v3].walkpath[0] = -1;
		plr[v3].destAction = -1;
		v14 = v2 == myplr;
		plr[v3]._px = v16;
		plr[v3]._py = v17;
		if ( v14 )
			plr[v3]._plid = AddLight(v16, v17, plr[v3]._pLightRad);
		else
			plr[v3]._plid = -1;
		plr[v3]._pvid = AddVision(plr[v3].WorldX, plr[v3].WorldY, plr[v3]._pLightRad, v2 == myplr);
	}
	v18 = plr[v3]._pClass;
	if ( v18 )
	{
		if ( v18 == 1 )
		{
			plr[v3]._pAblSpells[0] = 0x8000000;
		}
		else
		{
			if ( v18 != 2 )
				goto LABEL_33;
			plr[v3]._pAblSpells[0] = 0x4000000;
		}
	}
	else
	{
		plr[v3]._pAblSpells[0] = 0x2000000;
	}
	plr[v3]._pAblSpells[1] = 0;
LABEL_33:
	v19 = plr[v3]._pLevel;
	plr[v3]._pInvincible = 0;
	v14 = v2 == myplr;
#ifdef _DEBUG
	if ( debug_mode_dollar_sign && FirstTime )
	{
		plr[pnum]._pMemSpells[0] |= 0x800000;
		plr[pnum]._pMemSpells[1] |= 0;
		if ( !plr[myplr]._pSplLvl[SPL_TELEPORT] )
			plr[myplr]._pSplLvl[SPL_TELEPORT] = 1;
	}
	if ( debug_mode_key_inverted_v && FirstTime )
	{
		plr[pnum]._pMemSpells[0] = -1;
		plr[pnum]._pMemSpells[1] = 0xFFFFFFF;
	}
#endif
	plr[v3]._pNextExper = ExpLvlsTbl[v19];
	if ( v14 )
	{
		deathdelay = 0;
		deathflag = 0;
		ScrollInfo._sxoff = 0;
		ScrollInfo._syoff = 0;
		ScrollInfo._sdir = 0;
	}
}
// 44B83C: could not find valid save-restore pair for edi
// 52572C: using guessed type int leveldebug;
// 69B7C4: using guessed type int deathdelay;

void __cdecl InitMultiView()
{
	int v0; // eax

	if ( (unsigned int)myplr >= 4 )
		TermMsg("InitPlayer: illegal player %d", myplr);
	v0 = plr[myplr].WorldY;
	ViewX = plr[myplr].WorldX;
	ViewY = v0;
}

void __fastcall InitPlayerLoc(int pnum, bool flag)
{
	int v2; // esi
	int v3; // esi
	int v4; // edi
	int v5; // ebx
	char *v6; // eax
	int v7; // ebx
	int v8; // edi
	char *v9; // eax
	int v10; // edi
	int v11; // ebx
	char *v12; // eax
	bool v13; // [esp+Ch] [ebp-Ch]
	int v14; // [esp+10h] [ebp-8h]
	int v15; // [esp+10h] [ebp-8h]
	int v16; // [esp+10h] [ebp-8h]
	signed int v17; // [esp+14h] [ebp-4h]
	signed int v18; // [esp+14h] [ebp-4h]
	signed int v19; // [esp+14h] [ebp-4h]

	v2 = pnum;
	v13 = flag;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("InitPlayer: illegal player %d", pnum);
	v3 = v2;
	v14 = 0;
	v4 = plr[v3].WorldX - 1;
	v5 = plr[v3].WorldY + 1;
	v6 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(v4, v5);
	v17 = 2;
	do
		v14 |= *(unsigned short *)&v6[2 * v17++];
	while ( v17 < 10 );
	if ( v14 | dArch[v4][v5] | (unsigned char)nSolidTable[dPiece[0][v5 + 112 * v4]] )
		plr[v3]._peflag = 1;
	else
		plr[v3]._peflag = 0;
	if ( v13 == 1 && plr[v3]._peflag == 1 )
	{
		v7 = plr[v3].WorldX;
		v15 = 0;
		v8 = plr[v3].WorldY + 2;
		v9 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(plr[v3].WorldX, v8);
		v18 = 2;
		do
			v15 |= *(unsigned short *)&v9[2 * v18++];
		while ( v18 < 10 );
		if ( !(v15 | dArch[v7][v8]) )
		{
			v16 = 0;
			v10 = plr[v3].WorldX - 2;
			v11 = plr[v3].WorldY + 1;
			v12 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(v10, v11);
			v19 = 2;
			do
				v16 |= *(unsigned short *)&v12[2 * v19++];
			while ( v19 < 10 );
			if ( v16 | dArch[v10][v11] )
				plr[v3]._peflag = 2;
		}
	}
}

bool __fastcall SolidLoc(int x, int y)
{
	bool result; // eax

	if ( x < 0 || y < 0 || x >= 112 || y >= 112 )
		result = 0;
	else
		result = (unsigned char)nSolidTable[dPiece[0][y + 112 * x]];
	return result;
}

bool __fastcall PlrDirOK(int pnum, int dir)
{
	int v2; // esi
	int v3; // ebx
	int v4; // eax
	int v5; // esi
	int v6; // edi
	int v7; // ebp
	bool result; // eax
	bool v9; // zf
	int p; // [esp+10h] [ebp-4h]

	v2 = pnum;
	v3 = dir;
	p = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PlrDirOK: illegal player %d", pnum);
	v4 = v2;
	v5 = plr[v2].WorldX + offset_x[v3];
	v6 = plr[v4].WorldY + offset_y[v3];
	if ( v5 < 0 )
		return 0;
	v7 = 112 * v5 + v6;
	if ( !dPiece[0][v7] || !PosOkPlayer(p, v5, v6) )
		return 0;
	result = 1;
	if ( v3 == 6 )
	{
		if ( SolidLoc(v5, v6 + 1) )
			return 0;
		v9 = (dFlags[0][v7 + 1] & 0x20) == 0;
	}
	else
	{
		if ( v3 != 2 )
			return result;
		if ( SolidLoc(v5 + 1, v6) )
			return 0;
		v9 = (dFlags[1][v7] & 0x20) == 0;
	}
	if ( v9 )
		return 1;
	return 0;
}

void __fastcall PlrClrTrans(int x, int y)
{
	int v2; // esi
	int v3; // ebx
	int v4; // edx
	int v5; // edi
	char *v6; // ecx
	int v7; // eax
	int v8; // ebp

	v2 = y - 1;
	v3 = y + 1;
	if ( (unsigned char)(__OFSUB__(y - 1, y + 1) ^ 1) | (y - 1 == y + 1) )
	{
		v4 = x - 1;
		v5 = x + 1;
		do
		{
			if ( v4 <= v5 )
			{
				v6 = &dung_map[v4][v2];
				v7 = v5 - v4 + 1;
				do
				{
					v8 = *v6;
					v6 += 112;
					TransList[v8] = 0;
					--v7;
				}
				while ( v7 );
			}
			++v2;
		}
		while ( v2 <= v3 );
	}
}

void __fastcall PlrDoTrans(int x, int y)
{
	int v2; // edi
	int v3; // ebx
	int v4; // eax
	_BYTE *v5; // ecx
	_DWORD *v6; // esi
	int v7; // eax
	int v8; // [esp+8h] [ebp-4h]

	if ( leveltype == DTYPE_CATHEDRAL || leveltype == DTYPE_CATACOMBS )
	{
		v2 = y - 1;
		if ( y - 1 <= y + 1 )
		{
			v3 = x - 1;
			v8 = x + 1;
			do
			{
				if ( v3 <= v8 )
				{
					v4 = v2 + 112 * v3;
					v5 = (unsigned char *)dung_map + v4;
					v6 = (_DWORD *)((char *)dPiece + 4 * v4);
					v7 = v8 - v3 + 1;
					do
					{
						if ( !nSolidTable[*v6] )
						{
							if ( *v5 )
								TransList[(char)*v5] = 1;
						}
						v6 += 112;
						v5 += 112;
						--v7;
					}
					while ( v7 );
				}
				++v2;
			}
			while ( v2 <= y + 1 );
		}
	}
	else
	{
		TransList[1] = 1;
	}
}
// 5BB1ED: using guessed type char leveltype;

void __fastcall SetPlayerOld(int pnum)
{
	int v1; // esi
	int v2; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlayerOld: illegal player %d", pnum);
	v2 = v1;
	plr[v2]._poldx = plr[v1].WorldX;
	plr[v2]._poldy = plr[v1].WorldY;
}

void __fastcall FixPlayerLocation(int pnum, int dir)
{
	int v2; // edi
	int v3; // ebx
	int v4; // esi
	int v5; // ecx
	int v6; // eax
	bool v7; // zf
	int v8; // eax
	int v9; // eax

	v2 = pnum;
	v3 = dir;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("FixPlayerLocation: illegal player %d", pnum);
	v4 = v2;
	v5 = plr[v2].WorldY;
	v6 = plr[v2].WorldX;
	plr[v4]._py = v5;
	plr[v4]._ptargy = v5;
	plr[v4]._px = v6;
	plr[v4]._ptargx = v6;
	plr[v4]._pxoff = 0;
	plr[v4]._pyoff = 0;
	InitPlayerLoc(v2, 0);
	v7 = v2 == myplr;
	plr[v4]._pdir = v3;
	if ( v7 )
	{
		v8 = plr[v4].WorldX;
		ScrollInfo._sxoff = 0;
		ViewX = v8;
		v9 = plr[v4].WorldY;
		ScrollInfo._syoff = 0;
		ScrollInfo._sdir = 0;
		ViewY = v9;
	}
}

void __fastcall StartStand(int pnum, int dir)
{
	int v2; // ebx
	int v3; // edi
	int v4; // esi

	v2 = pnum;
	v3 = dir;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartStand: illegal player %d", pnum);
	v4 = v2;
	if ( !plr[v2]._pInvincible || plr[v4]._pHitPoints || v2 != myplr )
	{
		if ( !(plr[v4]._pGFXLoad & 1) )
			LoadPlrGFX(v2, 1);
		NewPlrAnim(v2, plr[0]._pNAnim[v3 + 5430 * v2], plr[v4]._pNFrames, 3, plr[v4]._pNWidth);
		plr[v4]._pmode = PM_STAND;
		FixPlayerLocation(v2, v3);
		FixPlrWalkTags(v2);
		dPlayer[plr[v4].WorldX][plr[v4].WorldY] = v2 + 1;
		SetPlayerOld(v2);
	}
	else
	{
		SyncPlrKill(v2, -1);
	}
}

void __fastcall StartWalkStand(int pnum)
{
	int v1; // edi
	int v2; // esi
	int v3; // eax
	int v4; // eax
	int v5; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartWalkStand: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1].WorldX;
	plr[v2]._pmode = 0;
	plr[v2]._px = v3;
	plr[v2]._py = plr[v1].WorldY;
	plr[v2]._pxoff = 0;
	plr[v2]._pyoff = 0;
	InitPlayerLoc(v1, 0);
	if ( v1 == myplr )
	{
		v4 = plr[v2].WorldX;
		ScrollInfo._sxoff = 0;
		ViewX = v4;
		v5 = plr[v2].WorldY;
		ScrollInfo._syoff = 0;
		ScrollInfo._sdir = 0;
		ViewY = v5;
	}
}

void __fastcall PM_ChangeLightOff(int pnum)
{
	int v1; // esi
	int v2; // esi
	signed int v3; // ebx
	int v4; // edi
	int v5; // edx
	LightListStruct *v6; // eax
	int v7; // ecx
	int v8; // edx
	signed int v9; // edi
	int v10; // ebx
	int v11; // edx
	int v12; // ecx
	int v13; // ebp
	int ly; // [esp+10h] [ebp-Ch]
	int lx; // [esp+18h] [ebp-4h]

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_ChangeLightOff: illegal player %d", pnum);
	v2 = v1;
	v3 = -1;
	v4 = plr[v2]._pxoff;
	v5 = 2 * plr[v2]._pyoff;
	v6 = &LightList[plr[v2]._plid];
	v7 = v4 + v5;
	v8 = v5 - v4;
	if ( v7 >= 0 )
	{
		v9 = 1;
	}
	else
	{
		v9 = -1;
		v7 = -v7;
	}
	if ( v8 >= 0 )
		v3 = 1;
	else
		v8 = -v8;
	v10 = v3 * (v8 >> 3);
	v11 = 8 * v6->_ly;
	ly = v11 + v10;
	lx = v9 * (v7 >> 3);
	v12 = 8 * v6->_lx;
	v13 = v11 + v6->_yoff;
	if ( abs(lx - v6->_xoff) >= 3 || abs(ly - v13) >= 3 )
		ChangeLightOff(plr[v2]._plid, lx, v10);
}

void __fastcall PM_ChangeOffset(int pnum)
{
	int v1; // esi
	int v2; // eax
	int v3; // edi
	int v4; // ebx
	int v5; // ecx
	int *v6; // esi
	int v7; // edi
	int v8; // ebx
	int v9; // edx
	int v10; // edi
	int v11; // edi
	int v12; // edi
	int v13; // ecx
	int v14; // edx
	int arglist; // [esp+8h] [ebp-8h]
	int v16; // [esp+Ch] [ebp-4h]

	v1 = pnum;
	arglist = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_ChangeOffset: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pVar6;
	v4 = plr[v1]._pxvel;
	v5 = v3;
	v6 = &plr[v1]._pVar7;
	v7 = v4 + v3;
	v8 = plr[v2]._pyvel;
	v9 = *v6;
	v16 = v7;
	plr[v2]._pVar6 = v7;
	v10 = *v6;
	++plr[v2]._pVar8;
	v11 = v8 + v10;
	*v6 = v11;
	v12 = v11 >> 8;
	plr[v2]._pxoff = v16 >> 8;
	plr[v2]._pyoff = v12;
	v13 = v5 >> 8;
	v14 = v9 >> 8;
	if ( arglist == myplr && ScrollInfo._sdir )
	{
		ScrollInfo._sxoff += v13 - (v16 >> 8);
		ScrollInfo._syoff += v14 - v12;
	}
	PM_ChangeLightOff(arglist);
}

void __fastcall StartWalk(int pnum, int xvel, int yvel, int xadd, int yadd, int EndDir, int sdir)
{
	int v7; // edi
	int v8; // esi
	int v9; // edi
	int v10; // ebx
	int v11; // ecx
	bool v12; // zf
	int v13; // ST08_4
	int v14; // eax
	bool v15; // sf
	unsigned char v16; // of
	int v17; // eax
	int v18; // [esp+Ch] [ebp-8h]
	int arglist; // [esp+10h] [ebp-4h]

	v7 = pnum;
	v18 = xvel;
	arglist = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartWalk: illegal player %d", pnum);
	v8 = v7;
	if ( plr[v7]._pInvincible && !plr[v8]._pHitPoints && v7 == myplr )
	{
		SyncPlrKill(v7, -1);
		return;
	}
	SetPlayerOld(v7);
	v9 = xadd + plr[v8].WorldX;
	v10 = yadd + plr[v8].WorldY;
	if ( PlrDirOK(arglist, EndDir) )
	{
		v11 = arglist;
		plr[v8]._px = v9;
		v12 = arglist == myplr;
		plr[v8]._py = v10;
		if ( v12 )
		{
			ScrollInfo._sdx = plr[v8].WorldX - ViewX;
			ScrollInfo._sdy = plr[v8].WorldY - ViewY;
		}
		plr[v8]._pmode = PM_WALK;
		dPlayer[v9][v10] = -1 - arglist;
		plr[v8]._pxvel = v18;
		v12 = (plr[v8]._pGFXLoad & 2) == 0;
		plr[v8]._pyvel = yvel;
		plr[v8]._pVar1 = xadd;
		plr[v8]._pxoff = 0;
		plr[v8]._pyoff = 0;
		plr[v8]._pVar2 = yadd;
		plr[v8]._pVar3 = EndDir;
		if ( v12 )
		{
			LoadPlrGFX(arglist, 2);
			v11 = arglist;
		}
		v13 = plr[v8]._pWWidth;
		NewPlrAnim(v11, plr[0]._pWAnim[EndDir + 5430 * v11], plr[v8]._pWFrames, 0, v13);
		plr[v8]._pdir = EndDir;
		plr[v8]._pVar6 = 0;
		plr[v8]._pVar7 = 0;
		plr[v8]._pVar8 = 0;
		InitPlayerLoc(arglist, 0);
		if ( arglist == myplr )
		{
			if ( zoomflag )
			{
				if ( abs(ScrollInfo._sdx) < 3 )
				{
					v14 = abs(ScrollInfo._sdy);
					v16 = __OFSUB__(v14, 3);
					v15 = v14 - 3 < 0;
					goto LABEL_18;
				}
			}
			else if ( abs(ScrollInfo._sdx) < 2 )
			{
				v17 = abs(ScrollInfo._sdy);
				v16 = __OFSUB__(v17, 2);
				v15 = v17 - 2 < 0;
LABEL_18:
				if ( v15 ^ v16 )
				{
					ScrollInfo._sdir = sdir;
					return;
				}
				goto LABEL_20;
			}
LABEL_20:
			ScrollInfo._sdir = 0;
			return;
		}
	}
}
// 52569C: using guessed type int zoomflag;

void __fastcall StartWalk2(int pnum, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int EndDir, int sdir)
{
	int v9; // edi
	int v10; // esi
	int v11; // ebx
	int v12; // edi
	bool v13; // zf
	int v14; // eax
	int v15; // ecx
	int v16; // ecx
	int v17; // ecx
	int v18; // ST08_4
	bool v19; // edx
	int v20; // eax
	bool v21; // sf
	unsigned char v22; // of
	int v23; // eax
	int v24; // [esp+Ch] [ebp-8h]
	int arglist; // [esp+10h] [ebp-4h]
	int x; // [esp+28h] [ebp+14h]

	v9 = pnum;
	v24 = xvel;
	arglist = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartWalk2: illegal player %d", pnum);
	v10 = v9;
	if ( plr[v9]._pInvincible && !plr[v10]._pHitPoints && v9 == myplr )
	{
		SyncPlrKill(v9, -1);
		return;
	}
	SetPlayerOld(v9);
	v11 = xadd + plr[v10].WorldX;
	v12 = yadd + plr[v10].WorldY;
	x = xadd + plr[v10].WorldX;
	if ( PlrDirOK(arglist, EndDir) )
	{
		plr[v10]._px = v11;
		v13 = arglist == myplr;
		plr[v10]._py = v12;
		if ( v13 )
		{
			ScrollInfo._sdx = plr[v10].WorldX - ViewX;
			ScrollInfo._sdy = plr[v10].WorldY - ViewY;
		}
		v14 = plr[v10].WorldY;
		v15 = plr[v10].WorldX;
		plr[v10]._pVar2 = v14;
		dPlayer[v15][v14] = -1 - arglist;
		v16 = plr[v10].WorldX;
		plr[v10].WorldX = v11;
		dPlayer[v11][v12] = arglist + 1;
		plr[v10]._pVar1 = v16;
		v17 = plr[v10]._plid;
		plr[v10].WorldY = v12;
		plr[v10]._pxoff = xoff;
		plr[v10]._pyoff = yoff;
		ChangeLightXY(v17, x, v12);
		PM_ChangeLightOff(arglist);
		plr[v10]._pxvel = v24;
		plr[v10]._pyvel = yvel;
		plr[v10]._pVar6 = xoff << 8;
		v13 = (plr[v10]._pGFXLoad & 2) == 0;
		plr[v10]._pmode = PM_WALK2;
		plr[v10]._pVar7 = yoff << 8;
		plr[v10]._pVar3 = EndDir;
		if ( v13 )
			LoadPlrGFX(arglist, PM_WALK2);
		v18 = plr[v10]._pWWidth;
		NewPlrAnim(arglist, plr[0]._pWAnim[EndDir + 5430 * arglist], plr[v10]._pWFrames, 0, v18);
		plr[v10]._pVar8 = 0;
		v19 = 0;
		plr[v10]._pdir = EndDir;
		if ( EndDir == 7 )
			v19 = 1;
		InitPlayerLoc(arglist, v19);
		if ( arglist == myplr )
		{
			if ( zoomflag )
			{
				if ( abs(ScrollInfo._sdx) < 3 )
				{
					v20 = abs(ScrollInfo._sdy);
					v22 = __OFSUB__(v20, 3);
					v21 = v20 - 3 < 0;
					goto LABEL_20;
				}
			}
			else if ( abs(ScrollInfo._sdx) < PM_WALK2 )
			{
				v23 = abs(ScrollInfo._sdy);
				v22 = __OFSUB__(v23, 2);
				v21 = v23 - PM_WALK2 < 0;
LABEL_20:
				if ( v21 ^ v22 )
				{
					ScrollInfo._sdir = sdir;
					return;
				}
				goto LABEL_22;
			}
LABEL_22:
			ScrollInfo._sdir = 0;
			return;
		}
	}
}
// 52569C: using guessed type int zoomflag;

void __fastcall StartWalk3(int pnum, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int mapx, int mapy, int EndDir, int sdir)
{
	int v11; // edi
	int v12; // esi
	int v13; // eax
	int v14; // ecx
	int v15; // ebx
	int v16; // edi
	bool v17; // zf
	int v18; // edx
	int v19; // ecx
	int v20; // ST08_4
	int v21; // eax
	bool v22; // sf
	unsigned char v23; // of
	int v24; // eax
	int v25; // [esp+10h] [ebp-8h]
	int arglist; // [esp+14h] [ebp-4h]
	int a6; // [esp+2Ch] [ebp+14h]
	int x; // [esp+30h] [ebp+18h]
	int y; // [esp+34h] [ebp+1Ch]

	v11 = pnum;
	v25 = xvel;
	arglist = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartWalk3: illegal player %d", pnum);
	v12 = v11;
	if ( plr[v11]._pInvincible && !plr[v12]._pHitPoints && v11 == myplr )
	{
		SyncPlrKill(v11, -1);
		return;
	}
	SetPlayerOld(v11);
	v13 = plr[v12].WorldX;
	a6 = v13 + xadd;
	v14 = plr[v12].WorldY;
	v15 = v14 + yadd;
	x = mapx + v13;
	v16 = v14 + mapy;
	y = v14 + mapy;
	if ( PlrDirOK(arglist, EndDir) )
	{
		v17 = arglist == myplr;
		plr[v12]._px = a6;
		plr[v12]._py = v15;
		if ( v17 )
		{
			ScrollInfo._sdx = plr[v12].WorldX - ViewX;
			ScrollInfo._sdy = plr[v12].WorldY - ViewY;
		}
		v18 = plr[v12].WorldY;
		v19 = plr[v12].WorldX;
		plr[v12]._pVar5 = v16;
		dPlayer[v19][v18] = -1 - arglist;
		dPlayer[a6][v15] = -1 - arglist;
		plr[v12]._pVar4 = x;
		plr[v12]._pyoff = yoff;
		dFlags[x][v16] |= 0x20u;
		v17 = leveltype == DTYPE_TOWN;
		plr[v12]._pxoff = xoff;
		if ( !v17 )
		{
			ChangeLightXY(plr[v12]._plid, x, y);
			PM_ChangeLightOff(arglist);
		}
		plr[v12]._pmode = PM_WALK3;
		plr[v12]._pxvel = v25;
		plr[v12]._pyvel = yvel;
		plr[v12]._pVar1 = a6;
		plr[v12]._pVar6 = xoff << 8;
		v17 = (plr[v12]._pGFXLoad & 2) == 0;
		plr[v12]._pVar7 = yoff << 8;
		plr[v12]._pVar2 = v15;
		plr[v12]._pVar3 = EndDir;
		if ( v17 )
			LoadPlrGFX(arglist, 2);
		v20 = plr[v12]._pWWidth;
		NewPlrAnim(arglist, plr[0]._pWAnim[EndDir + 5430 * arglist], plr[v12]._pWFrames, 0, v20);
		plr[v12]._pdir = EndDir;
		plr[v12]._pVar8 = 0;
		InitPlayerLoc(arglist, 0);
		if ( arglist == myplr )
		{
			if ( zoomflag )
			{
				if ( abs(ScrollInfo._sdx) < 3 )
				{
					v21 = abs(ScrollInfo._sdy);
					v23 = __OFSUB__(v21, 3);
					v22 = v21 - 3 < 0;
					goto LABEL_20;
				}
			}
			else if ( abs(ScrollInfo._sdx) < 2 )
			{
				v24 = abs(ScrollInfo._sdy);
				v23 = __OFSUB__(v24, 2);
				v22 = v24 - 2 < 0;
LABEL_20:
				if ( v22 ^ v23 )
				{
					ScrollInfo._sdir = sdir;
					return;
				}
				goto LABEL_22;
			}
LABEL_22:
			ScrollInfo._sdir = 0;
			return;
		}
	}
}
// 52569C: using guessed type int zoomflag;
// 5BB1ED: using guessed type char leveltype;

void __fastcall StartAttack(int pnum, int d)
{
	int v2; // edi
	int v3; // ebp
	int v4; // esi
	int v5; // ST08_4

	v2 = pnum;
	v3 = d;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartAttack: illegal player %d", pnum);
	v4 = v2;
	if ( !plr[v2]._pInvincible || plr[v4]._pHitPoints || v2 != myplr )
	{
		if ( !(plr[v4]._pGFXLoad & 4) )
			LoadPlrGFX(v2, 4);
		v5 = plr[v4]._pAWidth;
		NewPlrAnim(v2, plr[0]._pAAnim[v3 + 5430 * v2], plr[v4]._pAFrames, 0, v5);
		plr[v4]._pmode = 4;
		FixPlayerLocation(v2, v3);
		SetPlayerOld(v2);
	}
	else
	{
		SyncPlrKill(v2, -1);
	}
}

void __fastcall StartRangeAttack(int pnum, int d, int cx, int cy)
{
	int v4; // edi
	int v5; // esi
	int v6; // ST08_4
	int a2a; // [esp+8h] [ebp-4h]

	v4 = pnum;
	a2a = d;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartRangeAttack: illegal player %d", pnum);
	v5 = v4;
	if ( !plr[v4]._pInvincible || plr[v5]._pHitPoints || v4 != myplr )
	{
		if ( !(plr[v5]._pGFXLoad & 4) )
			LoadPlrGFX(v4, 4);
		v6 = plr[v5]._pAWidth;
		NewPlrAnim(v4, plr[0]._pAAnim[a2a + 5430 * v4], plr[v5]._pAFrames, 0, v6);
		plr[v5]._pmode = PM_RATTACK;
		FixPlayerLocation(v4, a2a);
		SetPlayerOld(v4);
		plr[v5]._pVar1 = cx;
		plr[v5]._pVar2 = cy;
	}
	else
	{
		SyncPlrKill(v4, -1);
	}
}

void __fastcall StartPlrBlock(int pnum, int dir)
{
	int v2; // edi
	int v3; // ebx
	int v4; // esi
	int v5; // ST08_4

	v2 = pnum;
	v3 = dir;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartPlrBlock: illegal player %d", pnum);
	v4 = v2;
	if ( !plr[v2]._pInvincible || plr[v4]._pHitPoints || v2 != myplr )
	{
		PlaySfxLoc(IS_ISWORD, plr[v4].WorldX, plr[v4].WorldY);
		if ( !(plr[v4]._pGFXLoad & 0x100) )
			LoadPlrGFX(v2, 256);
		v5 = plr[v4]._pBWidth;
		NewPlrAnim(v2, plr[0]._pBAnim[v3 + 5430 * v2], plr[v4]._pBFrames, 2, v5);
		plr[v4]._pmode = PM_BLOCK;
		FixPlayerLocation(v2, v3);
		SetPlayerOld(v2);
	}
	else
	{
		SyncPlrKill(v2, -1);
	}
}

void __fastcall StartSpell(int pnum, int d, int cx, int cy)
{
	int v4; // edi
	int v5; // esi
	int v6; // edx
	int v7; // ST08_4
	int v8; // edx
	int a2; // [esp+Ch] [ebp-4h]

	v4 = pnum;
	a2 = d;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartSpell: illegal player %d", pnum);
	v5 = v4;
	if ( plr[v4]._pInvincible && !plr[v5]._pHitPoints && v4 == myplr )
	{
		SyncPlrKill(v4, -1);
		return;
	}
	if ( leveltype )
	{
		switch ( spelldata[plr[v5]._pSpell].sType )
		{
			case STYPE_FIRE:
				if ( !(plr[v5]._pGFXLoad & 0x20) )
					LoadPlrGFX(v4, 32);
				v6 = plr[0]._pFAnim[a2 + 5430 * v4];
				goto LABEL_20;
			case STYPE_LIGHTNING:
				if ( !(plr[v5]._pGFXLoad & 0x10) )
					LoadPlrGFX(v4, 16);
				v6 = plr[0]._pLAnim[a2 + 5430 * v4];
				goto LABEL_20;
			case STYPE_MAGIC:
				if ( !(plr[v5]._pGFXLoad & 0x40) )
					LoadPlrGFX(v4, 64);
				v6 = plr[0]._pTAnim[a2 + 5430 * v4];
LABEL_20:
				v7 = plr[v5]._pSWidth;
				NewPlrAnim(v4, v6, plr[v5]._pSFrames, 0, v7);
				break;
		}
	}
	PlaySfxLoc((unsigned char)spelldata[plr[v5]._pSpell].sSFX, plr[v5].WorldX, plr[v5].WorldY);
	plr[v5]._pmode = PM_SPELL;
	FixPlayerLocation(v4, a2);
	SetPlayerOld(v4);
	v8 = plr[v5]._pSpell;
	plr[v5]._pVar1 = cx;
	plr[v5]._pVar2 = cy;
	plr[v5]._pVar4 = GetSpellLevel(v4, v8);
	plr[v5]._pVar8 = 1;
}
// 5BB1ED: using guessed type char leveltype;

void __fastcall FixPlrWalkTags(int pnum)
{
	int v1; // esi
	int v2; // edx
	int v3; // ecx
	int v4; // eax
	int v5; // esi
	int v6; // edi
	int v7; // ebx
	int v8; // edi
	bool v9; // zf
	bool v10; // sf
	unsigned char v11; // of
	int v12; // eax
	int v13; // [esp+8h] [ebp-Ch]
	int v14; // [esp+Ch] [ebp-8h]
	char *v15; // [esp+10h] [ebp-4h]

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("FixPlrWalkTags: illegal player %d", pnum);
	v13 = v1 + 1;
	v2 = -1 - v1;
	v3 = plr[v1]._poldx;
	v4 = plr[v1]._poldy;
	v5 = v4 - 1;
	if ( (unsigned char)(__OFSUB__(v4 - 1, v4 + 1) ^ 1) | (v4 - 1 == v4 + 1) )
	{
		v6 = v3 + 1;
		do
		{
			v7 = v3 - 1;
			v14 = v3 - 1;
			if ( v3 - 1 <= v6 )
			{
				v15 = &dPlayer[v7][v5];
				do
				{
					if ( v7 >= 0 && v7 < 112 && v5 >= 0 && v5 < 112 )
					{
						v8 = *v15;
						if ( v8 == v13 || v8 == v2 )
							*v15 = 0;
					}
					v15 += 112;
					v7 = v14 + 1;
					v6 = v3 + 1;
					v11 = __OFSUB__(v14 + 1, v3 + 1);
					v9 = v14 + 1 == v3 + 1;
					v10 = v14++ - v3 < 0;
				}
				while ( (unsigned char)(v10 ^ v11) | v9 );
			}
			++v5;
		}
		while ( v5 <= v4 + 1 );
	}
	if ( v3 >= 0 && v3 < 111 && v4 >= 0 && v4 < 111 )
	{
		v12 = 112 * v3 + v4;
		dFlags[1][v12] &= 0xDFu;
		dFlags[0][v12 + 1] &= 0xDFu;
	}
}

void __fastcall RemovePlrFromMap(int pnum)
{
	int v1; // esi
	signed int v2; // edi
	signed int v3; // edx
	signed int v4; // ebx
	char v5; // al
	signed int v6; // edx
	_BYTE *v7; // eax
	signed int v8; // edi
	int v9; // ecx
	int v10; // [esp+Ch] [ebp-4h]

	v1 = -1 - pnum;
	v10 = pnum + 1;
	v2 = 1;
	do
	{
		v3 = v2;
		v4 = 111;
		do
		{
			if ( dPlayer[0][v3 + 111] == v1 || dPlayer[0][v3] == v1 )
			{
				v5 = dFlags[1][v3];
				if ( v5 & 0x20 )
					dFlags[1][v3] = v5 & 0xDF;
			}
			v3 += 112;
			--v4;
		}
		while ( v4 );
		++v2;
	}
	while ( v2 < 112 );
	v6 = 0;
	do
	{
		v7 = (unsigned char *)dPlayer + v6;
		v8 = 112;
		do
		{
			v9 = (char)*v7;
			if ( v9 == v10 || v9 == v1 )
				*v7 = 0;
			v7 += 112;
			--v8;
		}
		while ( v8 );
		++v6;
	}
	while ( v6 < 112 );
}

void __fastcall StartPlrHit(int pnum, int dam, unsigned char forcehit)
{
	int v3; // ebx
	int v4; // edi
	int v5; // esi
	char v6; // al
	int v7; // ecx
	int v8; // eax
	int v9; // edi
	int v10; // ST08_4

	v3 = pnum;
	v4 = dam;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("StartPlrHit: illegal player %d", pnum);
	v5 = v3;
	if ( plr[v3]._pInvincible && !plr[v5]._pHitPoints && v3 == myplr )
	{
		SyncPlrKill(v3, -1);
		return;
	}
	v6 = plr[v5]._pClass;
	switch ( v6 )
	{
		case UI_WARRIOR:
			v7 = PS_WARR69;
LABEL_13:
			PlaySfxLoc(v7, plr[v5].WorldX, plr[v5].WorldY);
			break;
		case UI_ROGUE:
			v7 = PS_ROGUE69;
			goto LABEL_13;
		case UI_SORCERER:
			v7 = PS_MAGE69;
			goto LABEL_13;
	}
	v8 = plr[v5]._pLevel;
	drawhpflag = 1;
	if ( v4 >> 6 >= v8 || forcehit )
	{
		v9 = plr[v5]._pdir;
		if ( !(plr[v5]._pGFXLoad & 8) )
			LoadPlrGFX(v3, 8);
		v10 = plr[v5]._pHWidth;
		NewPlrAnim(v3, plr[0]._pHAnim[v9 + 5430 * v3], plr[v5]._pHFrames, 0, v10);
		plr[v5]._pmode = PM_GOTHIT;
		FixPlayerLocation(v3, v9);
		plr[v5]._pVar8 = 1;
		FixPlrWalkTags(v3);
		dPlayer[plr[v5].WorldX][plr[v5].WorldY] = v3 + 1;
		SetPlayerOld(v3);
	}
}

void __fastcall RespawnDeadItem(ItemStruct *itm, int x, int y)
{
	ItemStruct *v3; // ebx
	int v4; // eax
	int i; // ST10_4
	//unsigned int v6; // ecx

	v3 = itm;
	if ( numitems < 127 )
	{
		if ( FindGetItem(itm->IDidx, itm->_iCreateInfo, itm->_iSeed) >= 0 )
		{
			DrawInvMsg("A duplicate item has been detected.  Destroying duplicate...");
			SyncGetItem(x, y, v3->IDidx, v3->_iCreateInfo, v3->_iSeed);
		}
		v4 = itemavail[0];
		i = itemavail[0];
		dItem[x][y] = _LOBYTE(itemavail[0]) + 1;
		//v6 = 4 * numitems;
		itemactive[numitems] = v4;
		v4 *= 368;
		itemavail[0] = itemavail[-numitems + 126]; /* double check */
		qmemcpy((char *)item + v4, v3, sizeof(ItemStruct));
		*(int *)((char *)&item[0]._ix + v4) = x;
		*(int *)((char *)&item[0]._iy + v4) = y;
		RespawnItem(i, 1);
		++numitems;
		v3->_itype = -1;
	}
}

void __fastcall StartPlayerKill(int pnum, int earflag)
{
	unsigned int v2; // edi
	unsigned int v3; // esi
	char v4; // al
	int v5; // ecx
	int v6; // ST0C_4
	bool v7; // zf
	int *v8; // eax
	signed int v9; // ecx
	char *v10; // eax
	char v11; // al
	short v12; // cx
	short v13; // ax
	int v14; // ecx
	int v15; // eax
	signed int v17; // ebx
	int v18; // eax
	ItemStruct ear; // [esp+Ch] [ebp-178h]
	BOOL v20; // [esp+17Ch] [ebp-8h]
	struct ItemStruct *itm; // [esp+180h] [ebp-4h]

	v2 = pnum;
	v3 = 21720 * pnum;
	itm = (struct ItemStruct *)earflag;
	if ( plr[pnum]._pHitPoints <= 0 && plr[v3 / 0x54D8]._pmode == PM_DEATH )
		return;
	if ( myplr == pnum )
		NetSendCmdParam1(1u, CMD_PLRDEAD, earflag);
	v20 = (unsigned char)gbMaxPlayers > 1u && plr[v3 / 0x54D8].plrlevel == 16;
	if ( v2 >= 4 )
		TermMsg("StartPlayerKill: illegal player %d", v2);
	v4 = plr[v3 / 0x54D8]._pClass;
	if ( v4 )
	{
		if ( v4 == 1 )
		{
			v5 = PS_ROGUE71;
		}
		else
		{
			if ( v4 != 2 )
				goto LABEL_18;
			v5 = PS_MAGE71;
		}
		PlaySfxLoc(v5, plr[v3 / 0x54D8].WorldX, plr[v3 / 0x54D8].WorldY);
		goto LABEL_18;
	}
	PlaySfxLoc(PS_DEAD, plr[v3 / 0x54D8].WorldX, plr[v3 / 0x54D8].WorldY); /* BUG_FIX: uses wrong sound, should use PS_WARR71 */
LABEL_18:
	if ( plr[v3 / 0x54D8]._pgfxnum )
	{
		plr[v3 / 0x54D8]._pgfxnum = 0;
		plr[v3 / 0x54D8]._pGFXLoad = 0;
		SetPlrAnims(v2);
	}
	if ( SLOBYTE(plr[v3 / 0x54D8]._pGFXLoad) >= 0 )
		LoadPlrGFX(v2, 128);
	v6 = plr[v3 / 0x54D8]._pDWidth;
	NewPlrAnim(v2, plr[0]._pDAnim[plr[v3 / 0x54D8]._pdir + v3 / 4], plr[v3 / 0x54D8]._pDFrames, 1, v6);
	plr[v3 / 0x54D8]._pBlockFlag = 0;
	plr[v3 / 0x54D8]._pmode = PM_DEATH;
	plr[v3 / 0x54D8]._pInvincible = 1;
	SetPlayerHitPoints(v2, 0);
	v7 = v2 == myplr;
	plr[v3 / 0x54D8]._pVar8 = 1;
	if ( !v7 && !itm && !v20 )
	{
		v8 = &plr[v3 / 0x54D8].InvBody[0]._itype;
		v9 = 7;
		do
		{
			*v8 = -1;
			v8 += 92;
			--v9;
		}
		while ( v9 );
		CalcPlrInv(v2, 0);
	}
	if ( plr[v3 / 0x54D8].plrlevel == currlevel )
	{
		FixPlayerLocation(v2, plr[v3 / 0x54D8]._pdir);
		RemovePlrFromMap(v2);
		v10 = &dFlags[plr[v3 / 0x54D8].WorldX][plr[v3 / 0x54D8].WorldY];
		*v10 |= 4u;
		SetPlayerOld(v2);
		if ( v2 == myplr )
		{
			drawhpflag = 1;
			deathdelay = 30;
			if ( pcurs >= CURSOR_FIRSTITEM )
			{
				PlrDeadItem(v2, &plr[v3 / 0x54D8].HoldItem, 0, 0);
				SetCursor(CURSOR_HAND);
			}
			if ( !v20 )
			{
				DropHalfPlayersGold(v2);
				if ( itm != (struct ItemStruct *)-1 )
				{
					if ( itm )
					{
						SetPlrHandItem(&ear, IDI_EAR);
						sprintf(ear._iName, "Ear of %s", plr[v3 / 0x54D8]._pName);
						v11 = plr[v3 / 0x54D8]._pClass;
						if ( v11 == 2 )
						{
							ear._iCurs = 19;
						}
						else if ( v11 )
						{
							if ( v11 == 1 )
								ear._iCurs = 21;
						}
						else
						{
							ear._iCurs = 20;
						}
						_LOBYTE(v12) = 0;
						_HIBYTE(v12) = plr[v3 / 0x54D8]._pName[0];
						v13 = v12 | plr[v3 / 0x54D8]._pName[1];
						v14 = plr[v3 / 0x54D8]._pName[3];
						ear._iCreateInfo = v13;
						v15 = plr[v3 / 0x54D8]._pName[5] | ((plr[v3 / 0x54D8]._pName[4] | ((v14 | (plr[v3 / 0x54D8]._pName[2] << 8)) << 8)) << 8);
						ear._ivalue = plr[v3 / 0x54D8]._pLevel;
						ear._iSeed = v15;
						if ( FindGetItem(IDI_EAR, *(int *)&ear._iCreateInfo, v15) == -1 )
							PlrDeadItem(v2, &ear, 0, 0);
					}
					else
					{
						itm = plr[v3 / 0x54D8].InvBody;
						v17 = 7;
						do
						{
							v18 = ((_BYTE)--v17 + (unsigned char)plr[v3 / 0x54D8]._pdir) & 7;
							PlrDeadItem(v2, itm, offset_x[v18], offset_y[v18]);
							++itm;
						}
						while ( v17 );
						CalcPlrInv(v2, 0);
					}
				}
			}
		}
	}
	SetPlayerHitPoints(v2, 0);
}
// 679660: using guessed type char gbMaxPlayers;
// 69B7C4: using guessed type int deathdelay;

void __fastcall PlrDeadItem(int pnum, struct ItemStruct *itm, int xx, int yy)
{
	int v4; // edi
	int v5; // edi
	int v6; // esi
	int v7; // ebx
	int v8; // eax
	int v9; // ST04_4
	ItemStruct *v10; // esi
	int v11; // eax
	int v12; // ebx
	int v13; // esi
	//int v14; // eax
	int v15; // edx
	unsigned char v16; // [esp-8h] [ebp-24h]
	unsigned char v17; // [esp-4h] [ebp-20h]
	int x; // [esp+Ch] [ebp-10h]
	ItemStruct *pItem; // [esp+10h] [ebp-Ch]
	int v20; // [esp+14h] [ebp-8h]
	int v21; // [esp+14h] [ebp-8h]
	int v22; // [esp+18h] [ebp-4h]
	int xxa; // [esp+24h] [ebp+8h]
	int yya; // [esp+28h] [ebp+Ch]

	pItem = itm;
	v4 = pnum;
	if ( itm->_itype != -1 )
	{
		if ( (unsigned int)pnum >= 4 )
			TermMsg("PlrDeadItem: illegal player %d", pnum);
		v5 = v4;
		v6 = yy + plr[v5].WorldY;
		v7 = xx + plr[v5].WorldX;
		v20 = yy + plr[v5].WorldY;
		if ( (xx || yy) && (v8 = ItemSpaceOk(v7, v6), v8) )
		{
			v9 = v6;
			v10 = pItem;
			RespawnDeadItem(pItem, v7, v9);
			v17 = v20;
			v16 = v7;
		}
		else
		{
			yya = -1;
			xxa = 1;
			while ( 1 )
			{
				v11 = yya;
				v21 = yya;
LABEL_14:
				if ( v11 <= xxa )
					break;
				++xxa;
				if ( --yya <= -50 )
					return;
			}
			v12 = v21 + plr[v5].WorldY;
			v22 = yya;
			while ( 1 )
			{
				v13 = v22 + plr[v5].WorldX;
				x = v22 + plr[v5].WorldX;
				//_LOBYTE(v14) = ItemSpaceOk(v13, v12);
				if ( ItemSpaceOk(v13, v12) )
					break;
				if ( ++v22 > xxa )
				{
					v11 = ++v21;
					goto LABEL_14;
				}
			}
			v15 = v13;
			v10 = pItem;
			RespawnDeadItem(pItem, v15, v12);
			v17 = v12;
			v16 = x;
		}
		qmemcpy(&plr[v5].HoldItem, v10, sizeof(plr[v5].HoldItem));
		NetSendCmdPItem(0, CMD_RESPAWNITEM, v16, v17);
	}
}

void __fastcall DropHalfPlayersGold(int pnum)
{
	int v1; // ebx
	int v2; // esi
	int v3; // edi
	int v4; // ecx
	int v5; // eax
	int v6; // ecx
	int v7; // eax
	int v8; // edx
	int v9; // ecx
	int v10; // eax
	int v11; // edx
	int v12; // ecx
	int v13; // eax
	int v14; // [esp+Ch] [ebp-8h]
	int v15; // [esp+Ch] [ebp-8h]
	int v16; // [esp+Ch] [ebp-8h]
	int v17; // [esp+Ch] [ebp-8h]
	signed int i; // [esp+10h] [ebp-4h]
	signed int ia; // [esp+10h] [ebp-4h]
	signed int ib; // [esp+10h] [ebp-4h]
	signed int ic; // [esp+10h] [ebp-4h]

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("DropHalfPlayersGold: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pGold >> 1;
	i = 0;
	while ( v3 > 0 )
	{
		v4 = 368 * i + v2 * 21720;
		v14 = v4;
		if ( *(int *)((char *)&plr[0].SpdList[0]._itype + v4) == ITYPE_GOLD )
		{
			v5 = *(int *)((char *)&plr[0].SpdList[0]._ivalue + v4);
			if ( v5 != 5000 )
			{
				if ( v3 >= v5 )
				{
					v3 -= v5;
					RemoveSpdBarItem(v1, i);
					SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
					GetGoldSeed(v1, &plr[v2].HoldItem);
					SetPlrHandGoldCurs(&plr[v2].HoldItem);
					plr[v2].HoldItem._ivalue = *(int *)((char *)&plr[0].SpdList[0]._ivalue + v14);
					PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
					i = -1;
				}
				else
				{
					*(int *)((char *)&plr[0].SpdList[0]._ivalue + v4) = v5 - v3;
					SetSpdbarGoldCurs(v1, i);
					SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
					GetGoldSeed(v1, &plr[v2].HoldItem);
					SetPlrHandGoldCurs(&plr[v2].HoldItem);
					plr[v2].HoldItem._ivalue = v3;
					v3 = 0;
					PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
				}
			}
		}
		if ( ++i >= 8 )
		{
			if ( v3 > 0 )
			{
				ia = 0;
				do
				{
					if ( v3 <= 0 )
						break;
					v6 = 368 * ia + v2 * 21720;
					v15 = v6;
					if ( *(int *)((char *)&plr[0].SpdList[0]._itype + v6) == ITYPE_GOLD )
					{
						v7 = *(int *)((char *)&plr[0].SpdList[0]._ivalue + v6);
						if ( v3 >= v7 )
						{
							v3 -= v7;
							RemoveSpdBarItem(v1, ia);
							SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
							GetGoldSeed(v1, &plr[v2].HoldItem);
							SetPlrHandGoldCurs(&plr[v2].HoldItem);
							plr[v2].HoldItem._ivalue = *(int *)((char *)&plr[0].SpdList[0]._ivalue + v15);
							PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
							ia = -1;
						}
						else
						{
							*(int *)((char *)&plr[0].SpdList[0]._ivalue + v6) = v7 - v3;
							SetSpdbarGoldCurs(v1, ia);
							SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
							GetGoldSeed(v1, &plr[v2].HoldItem);
							SetPlrHandGoldCurs(&plr[v2].HoldItem);
							plr[v2].HoldItem._ivalue = v3;
							v3 = 0;
							PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
						}
					}
					++ia;
				}
				while ( ia < 8 );
			}
			break;
		}
	}
	v8 = 0;
	drawpanflag = 255;
	if ( v3 > 0 )
	{
		ib = 0;
		if ( plr[v2]._pNumInv <= 0 )
		{
LABEL_28:
			if ( v3 > 0 )
			{
				v11 = 0;
				for ( ic = 0; ic < plr[v2]._pNumInv; v11 = ic++ + 1 )
				{
					if ( v3 <= 0 )
						break;
					v12 = 368 * v11 + v2 * 21720;
					v17 = v12;
					if ( *(int *)((char *)&plr[0].InvList[0]._itype + v12) == ITYPE_GOLD )
					{
						v13 = *(int *)((char *)&plr[0].InvList[0]._ivalue + v12);
						if ( v3 >= v13 )
						{
							v3 -= v13;
							RemoveInvItem(v1, v11);
							SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
							GetGoldSeed(v1, &plr[v2].HoldItem);
							SetPlrHandGoldCurs(&plr[v2].HoldItem);
							plr[v2].HoldItem._ivalue = *(int *)((char *)&plr[0].InvList[0]._ivalue + v17);
							PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
							ic = -1;
						}
						else
						{
							*(int *)((char *)&plr[0].InvList[0]._ivalue + v12) = v13 - v3;
							SetGoldCurs(v1, v11);
							SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
							GetGoldSeed(v1, &plr[v2].HoldItem);
							SetPlrHandGoldCurs(&plr[v2].HoldItem);
							plr[v2].HoldItem._ivalue = v3;
							v3 = 0;
							PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
						}
					}
				}
			}
		}
		else
		{
			while ( v3 > 0 )
			{
				v9 = 368 * v8 + v2 * 21720;
				v16 = v9;
				if ( *(int *)((char *)&plr[0].InvList[0]._itype + v9) == ITYPE_GOLD )
				{
					v10 = *(int *)((char *)&plr[0].InvList[0]._ivalue + v9);
					if ( v10 != 5000 )
					{
						if ( v3 >= v10 )
						{
							v3 -= v10;
							RemoveInvItem(v1, v8);
							SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
							GetGoldSeed(v1, &plr[v2].HoldItem);
							SetPlrHandGoldCurs(&plr[v2].HoldItem);
							plr[v2].HoldItem._ivalue = *(int *)((char *)&plr[0].InvList[0]._ivalue + v16);
							PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
							ib = -1;
						}
						else
						{
							*(int *)((char *)&plr[0].InvList[0]._ivalue + v9) = v10 - v3;
							SetGoldCurs(v1, v8);
							SetPlrHandItem(&plr[v2].HoldItem, IDI_GOLD);
							GetGoldSeed(v1, &plr[v2].HoldItem);
							SetPlrHandGoldCurs(&plr[v2].HoldItem);
							plr[v2].HoldItem._ivalue = v3;
							v3 = 0;
							PlrDeadItem(v1, &plr[v2].HoldItem, 0, 0);
						}
					}
				}
				v8 = ib++ + 1;
				if ( ib >= plr[v2]._pNumInv )
					goto LABEL_28;
			}
		}
	}
	plr[v2]._pGold = CalculateGold(v1);
}
// 52571C: using guessed type int drawpanflag;

void __fastcall SyncPlrKill(int pnum, int earflag)
{
	int v2; // esi
	int v3; // ebx
	int v4; // edx
	int v5; // eax

	v2 = pnum;
	v3 = earflag;
	if ( plr[pnum]._pHitPoints || currlevel )
	{
		v4 = 0;
		if ( nummissiles <= 0 )
		{
LABEL_9:
			SetPlayerHitPoints(pnum, 0);
			StartPlayerKill(v2, v3);
		}
		else
		{
			while ( 1 )
			{
				v5 = missileactive[v4];
				if ( missile[v5]._mitype == 13 && missile[v5]._misource == pnum && !missile[v5]._miDelFlag )
					break;
				if ( ++v4 >= nummissiles )
					goto LABEL_9;
			}
			if ( v3 != -1 )
				missile[missileactive[v4]]._miVar8 = v3;
		}
	}
	else
	{
		SetPlayerHitPoints(pnum, 64);
	}
}

void __fastcall RemovePlrMissiles(int pnum)
{
	int v1; // ebx
	int v2; // ebp
	int v3; // ecx
	int v4; // edi
	int v5; // esi
	int v6; // eax

	v1 = 0;
	v2 = pnum;
	if ( currlevel && pnum == myplr && (monster[myplr]._mx != 1 || monster[myplr]._my) )
	{
		M_StartKill(myplr, myplr);
		AddDead(monster[myplr]._mx, monster[myplr]._my, monster[myplr].MType->mdeadval, (direction)monster[myplr]._mdir);
		v3 = monster[myplr]._my + 112 * monster[myplr]._mx;
		monster[myplr]._mDelFlag = 1;
		dMonster[0][v3] = 0;
		DeleteMonsterList();
	}
	if ( nummissiles > 0 )
	{
		do
		{
			v4 = missileactive[v1];
			v5 = missileactive[v1];
			v6 = missile[v5]._mitype;
			if ( v6 == MIS_STONE && missile[v5]._misource == v2 )
				monster[missile[v5]._miVar2]._mmode = missile[v5]._miVar1;
			if ( v6 == MIS_MANASHIELD && missile[v5]._misource == v2 )
			{
				ClearMissileSpot(v4);
				DeleteMissile(v4, v1);
			}
			if ( missile[v5]._mitype == MIS_ETHEREALIZE && missile[v5]._misource == v2 )
			{
				ClearMissileSpot(v4);
				DeleteMissile(v4, v1);
			}
			++v1;
		}
		while ( v1 < nummissiles );
	}
}

void __fastcall InitLevelChange(int pnum)
{
	int v1; // esi
	int v2; // eax
	bool v3; // zf

	v1 = pnum;
	RemovePlrMissiles(pnum);
	if ( v1 == myplr && qtextflag )
	{
		qtextflag = 0;
		sfx_stop();
	}
	RemovePlrFromMap(v1);
	SetPlayerOld(v1);
	if ( v1 == myplr )
		dPlayer[plr[myplr].WorldX][plr[myplr].WorldY] = myplr + 1;
	else
		plr[v1]._pLvlVisited[plr[v1].plrlevel] = 1;
	ClrPlrPath(v1);
	v2 = v1;
	plr[v2].destAction = -1;
	v3 = v1 == myplr;
	plr[v2]._pLvlChanging = 1;
	if ( v3 )
		plr[v2].pLvlLoad = 10;
}
// 646D00: using guessed type char qtextflag;

void __fastcall StartNewLvl(int pnum, int fom, int lvl)
{
	int v3; // edi
	unsigned int v4; // esi
	unsigned int v5; // eax
	HWND v6; // ST00_4

	v3 = fom;
	v4 = pnum;
	InitLevelChange(pnum);
	if ( v4 >= 4 )
		TermMsg("StartNewLvl: illegal player %d", v4);
	if ( v3 < WM_DIABNEXTLVL )
	{
LABEL_10:
		TermMsg("StartNewLvl");
		goto LABEL_11;
	}
	if ( v3 <= WM_DIABPREVLVL || v3 == WM_DIABRTNLVL )
		goto LABEL_16;
	if ( v3 != WM_DIABSETLVL )
	{
		if ( v3 != WM_DIABTOWNWARP )
		{
			if ( v3 != WM_DIABTWARPUP )
			{
				if ( v3 == WM_DIABRETOWN )
					goto LABEL_11;
				goto LABEL_10;
			}
			plr[myplr].pTownWarps |= 1 << (leveltype - 2);
		}
LABEL_16:
		plr[v4].plrlevel = lvl;
		goto LABEL_11;
	}
	setlvlnum = lvl;
LABEL_11:
	if ( v4 == myplr )
	{
		v5 = v4;
		v6 = ghMainWnd;
		plr[v5]._pmode = PM_NEWLVL;
		plr[v5]._pInvincible = 1;
		PostMessageA(v6, v3, 0, 0);
		if ( (unsigned char)gbMaxPlayers > 1u )
			NetSendCmdParam2(1u, CMD_NEWLVL, v3, lvl);
	}
}
// 5BB1ED: using guessed type char leveltype;
// 5CCB10: using guessed type char setlvlnum;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall RestartTownLvl(int pnum)
{
	unsigned int v1; // edi
	unsigned int v2; // esi
	int v3; // eax
	HWND v4; // ST00_4

	v1 = pnum;
	InitLevelChange(pnum);
	if ( v1 >= 4 )
		TermMsg("RestartTownLvl: illegal player %d", v1);
	v2 = v1;
	plr[v2].plrlevel = 0;
	plr[v2]._pInvincible = 0;
	SetPlayerHitPoints(v1, 64);
	v3 = plr[v2]._pMaxManaBase - plr[v2]._pMaxMana;
	plr[v2]._pMana = 0;
	plr[v2]._pManaBase = v3;
	CalcPlrInv(v1, 0);
	if ( v1 == myplr )
	{
		plr[v2]._pmode = PM_NEWLVL;
		v4 = ghMainWnd;
		plr[v2]._pInvincible = 1;
		PostMessageA(v4, WM_DIABRETOWN, 0, 0);
	}
}

void __fastcall StartWarpLvl(int pnum, int pidx)
{
	int v2; // edi
	int v3; // esi
	int *v4; // eax
	int v5; // eax
	HWND v6; // ST00_4

	v2 = pidx;
	v3 = pnum;
	InitLevelChange(pnum);
	if ( gbMaxPlayers != 1 )
	{
		v4 = &plr[v3].plrlevel;
		if ( *v4 )
			*v4 = 0;
		else
			*v4 = portal[v2].level;
	}
	if ( v3 == myplr )
	{
		SetCurrentPortal(v2);
		v5 = v3;
		plr[v5]._pmode = PM_NEWLVL;
		v6 = ghMainWnd;
		plr[v5]._pInvincible = 1;
		PostMessageA(v6, WM_DIABWARPLVL, 0, 0);
	}
}
// 679660: using guessed type char gbMaxPlayers;

int __fastcall PM_DoStand(int pnum)
{
	return 0;
}

int __fastcall PM_DoWalk(int pnum)
{
	int v1; // ebx
	int v2; // esi
	int v3; // eax
	int v4; // eax
	int v5; // ecx
	int v6; // eax
	int v7; // edx
	int v8; // eax
	bool v9; // zf
	int result; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoWalk: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pAnimFrame;
	if ( v3 == 3 )
		goto LABEL_8;
	if ( plr[v2]._pWFrames != 8 )
	{
		if ( v3 != 4 )
			goto LABEL_9;
		goto LABEL_8;
	}
	if ( v3 == 7 )
LABEL_8:
		PlaySfxLoc(0, plr[v2].WorldX, plr[v2].WorldY);
LABEL_9:
	v4 = 8;
	if ( currlevel )
		v4 = PWVel[3][SLOBYTE(plr[v2]._pClass)];
	if ( plr[v2]._pVar8 == v4 )
	{
		v5 = plr[v2].WorldX;
		v6 = plr[v2].WorldY;
		dPlayer[plr[v2].WorldX][v6] = 0;
		v7 = v5 + plr[v2]._pVar1;
		v8 = plr[v2]._pVar2 + v6;
		plr[v2].WorldX = v7;
		v9 = leveltype == DTYPE_TOWN;
		dPlayer[v7][v8] = v1 + 1;
		plr[v2].WorldY = v8;
		if ( !v9 )
		{
			ChangeLightXY(plr[v2]._plid, v7, v8);
			ChangeVisionXY(plr[v2]._pvid, plr[v2].WorldX, plr[v2].WorldY);
		}
		if ( v1 == myplr && ScrollInfo._sdir )
		{
			ViewX = plr[v2].WorldX - ScrollInfo._sdx;
			ViewY = plr[v2].WorldY - ScrollInfo._sdy;
		}
		if ( plr[v2].walkpath[0] == -1 )
			StartStand(v1, plr[v2]._pVar3);
		else
			StartWalkStand(v1);
		ClearPlrPVars(v1);
		if ( leveltype )
			ChangeLightOff(plr[v2]._plid, 0, 0);
		result = 1;
	}
	else
	{
		PM_ChangeOffset(v1);
		result = 0;
	}
	return result;
}
// 5BB1ED: using guessed type char leveltype;

int __fastcall PM_DoWalk2(int pnum)
{
	int v1; // ebx
	int v2; // esi
	int v3; // eax
	int v4; // eax
	int result; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoWalk2: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pAnimFrame;
	if ( v3 == 3 )
		goto LABEL_8;
	if ( plr[v2]._pWFrames != 8 )
	{
		if ( v3 != 4 )
			goto LABEL_9;
		goto LABEL_8;
	}
	if ( v3 == 7 )
LABEL_8:
		PlaySfxLoc(0, plr[v2].WorldX, plr[v2].WorldY);
LABEL_9:
	v4 = 8;
	if ( currlevel )
		v4 = PWVel[3][SLOBYTE(plr[v2]._pClass)];
	if ( plr[v2]._pVar8 == v4 )
	{
		dPlayer[plr[v2]._pVar1][plr[v2]._pVar2] = 0;
		if ( leveltype )
		{
			ChangeLightXY(plr[v2]._plid, plr[v2].WorldX, plr[v2].WorldY);
			ChangeVisionXY(plr[v2]._pvid, plr[v2].WorldX, plr[v2].WorldY);
		}
		if ( v1 == myplr && ScrollInfo._sdir )
		{
			ViewX = plr[v2].WorldX - ScrollInfo._sdx;
			ViewY = plr[v2].WorldY - ScrollInfo._sdy;
		}
		if ( plr[v2].walkpath[0] == -1 )
			StartStand(v1, plr[v2]._pVar3);
		else
			StartWalkStand(v1);
		ClearPlrPVars(v1);
		if ( leveltype )
			ChangeLightOff(plr[v2]._plid, 0, 0);
		result = 1;
	}
	else
	{
		PM_ChangeOffset(v1);
		result = 0;
	}
	return result;
}
// 5BB1ED: using guessed type char leveltype;

int __fastcall PM_DoWalk3(int pnum)
{
	int v1; // ebx
	int v2; // esi
	int v3; // eax
	int v4; // eax
	int v5; // edx
	char *v6; // eax
	int v7; // eax
	bool v8; // zf
	int result; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoWalk3: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pAnimFrame;
	if ( v3 == 3 )
		goto LABEL_8;
	if ( plr[v2]._pWFrames != 8 )
	{
		if ( v3 != 4 )
			goto LABEL_9;
		goto LABEL_8;
	}
	if ( v3 == 7 )
LABEL_8:
		PlaySfxLoc(0, plr[v2].WorldX, plr[v2].WorldY);
LABEL_9:
	v4 = 8;
	if ( currlevel )
		v4 = PWVel[3][SLOBYTE(plr[v2]._pClass)];
	if ( plr[v2]._pVar8 == v4 )
	{
		v5 = plr[v2]._pVar1;
		dPlayer[plr[v2].WorldX][plr[v2].WorldY] = 0;
		v6 = &dFlags[plr[v2]._pVar4][plr[v2]._pVar5];
		plr[v2].WorldX = v5;
		*v6 &= 0xDFu;
		v7 = plr[v2]._pVar2;
		v8 = leveltype == DTYPE_TOWN;
		dPlayer[v5][v7] = v1 + 1;
		plr[v2].WorldY = v7;
		if ( !v8 )
		{
			ChangeLightXY(plr[v2]._plid, v5, v7);
			ChangeVisionXY(plr[v2]._pvid, plr[v2].WorldX, plr[v2].WorldY);
		}
		if ( v1 == myplr && ScrollInfo._sdir )
		{
			ViewX = plr[v2].WorldX - ScrollInfo._sdx;
			ViewY = plr[v2].WorldY - ScrollInfo._sdy;
		}
		if ( plr[v2].walkpath[0] == -1 )
			StartStand(v1, plr[v2]._pVar3);
		else
			StartWalkStand(v1);
		ClearPlrPVars(v1);
		if ( leveltype )
			ChangeLightOff(plr[v2]._plid, 0, 0);
		result = 1;
	}
	else
	{
		PM_ChangeOffset(v1);
		result = 0;
	}
	return result;
}
// 5BB1ED: using guessed type char leveltype;

bool __fastcall WeaponDur(int pnum, int durrnd)
{
	unsigned int v2; // edi
	unsigned int v3; // esi
	int v4; // ebp
	int v5; // ecx
	int v6; // ecx
	int v7; // ecx
	int v8; // ecx
	int v9; // ecx
	int v10; // ecx
	int v11; // ecx
	int v12; // ecx

	v2 = pnum;
	if ( pnum != myplr )
		return 0;
	_LOBYTE(pnum) = 3;
	if ( random(pnum, durrnd) )
		return 0;
	if ( v2 >= 4 )
		TermMsg("WeaponDur: illegal player %d", v2);
	v3 = v2;
	v4 = plr[v2].InvBody[4]._itype;
	if ( v4 != ITYPE_NONE && plr[v3].InvBody[4]._iClass == 1 )
	{
		v5 = plr[v3].InvBody[4]._iDurability;
		if ( v5 == 255 )
			return 0;
		v6 = v5 - 1;
		plr[v3].InvBody[4]._iDurability = v6;
		if ( !v6 )
		{
LABEL_22:
			NetSendCmdDelItem(1u, 4u);
			plr[v3].InvBody[4]._itype = -1;
			goto LABEL_23;
		}
	}
	if ( plr[v3].InvBody[5]._itype != -1 && plr[v3].InvBody[5]._iClass == 1 )
	{
		v7 = plr[v3].InvBody[5]._iDurability;
		if ( v7 == 255 )
			return 0;
		v8 = v7 - 1;
		plr[v3].InvBody[5]._iDurability = v8;
		if ( !v8 )
		{
LABEL_13:
			NetSendCmdDelItem(1u, 5u);
			plr[v3].InvBody[5]._itype = -1;
LABEL_23:
			CalcPlrInv(v2, 1u);
			return 1;
		}
	}
	if ( v4 == -1 && plr[v3].InvBody[5]._itype == ITYPE_SHIELD )
	{
		v9 = plr[v3].InvBody[5]._iDurability;
		if ( v9 == 255 )
			return 0;
		v10 = v9 - 1;
		plr[v3].InvBody[5]._iDurability = v10;
		if ( !v10 )
			goto LABEL_13;
	}
	if ( plr[v3].InvBody[5]._itype == -1 && v4 == 5 )
	{
		v11 = plr[v3].InvBody[4]._iDurability;
		if ( v11 != 255 )
		{
			v12 = v11 - 1;
			plr[v3].InvBody[4]._iDurability = v12;
			if ( !v12 )
				goto LABEL_22;
		}
	}
	return 0;
}

bool __fastcall PlrHitMonst(int pnum, int m)
{
	int v2; // ebx
	unsigned int v3; // esi
	//int v4; // ST04_4
	int v5; // ebx
	//int v7; // ST04_4
	int v8; // eax
	unsigned int v9; // esi
	int v10; // ecx
	int v11; // eax
	int v12; // edi
	int v13; // edi
	//int v14; // eax
	int v15; // ecx
	int v16; // edx
	int v17; // eax
	int v18; // ecx
	int v19; // edi
	int v20; // eax
	int v21; // eax
	char v22; // dl
	bool v23; // zf
	int v24; // eax
	int v25; // ecx
	int v26; // edi
	int v27; // eax
	int v28; // edx
	int *v29; // ecx
	int v30; // edx
	int *v31; // ecx
	int v32; // ecx
	int v33; // edx
	int *v34; // ecx
	int v35; // edx
	int *v36; // ecx
	int v37; // edx
	int *v38; // ecx
	int *v39; // ecx
	int v40; // esi
	bool ret; // [esp+Ch] [ebp-18h]
	bool v42; // [esp+10h] [ebp-14h]
	int v48;
	int v43; // [esp+14h] [ebp-10h]
	int pnuma; // [esp+18h] [ebp-Ch]
	int arglist; // [esp+1Ch] [ebp-8h]
	int v46; // [esp+20h] [ebp-4h]

	v2 = m;
	v3 = pnum;
	arglist = m;
	pnuma = pnum;
	if ( (unsigned int)m >= 0xC8 )
	{
		TermMsg("PlrHitMonst: illegal monster %d", m);
		//pnum = v4;
	}
	v5 = 228 * v2;
	v43 = v5;
	if ( (signed int)(*(int *)((_BYTE *)&monster[0]._mhitpoints + v5) & 0xFFFFFFC0) <= 0
	  || **(_BYTE **)((char *)&monster[0].MType + v5) == MT_ILLWEAV && *((_BYTE *)&monster[0]._mgoal + v5) == 2
	  || *(MON_MODE *)((char *)&monster[0]._mmode + v5) == MM_CHARGE )
	{
		return 0;
	}
	if ( v3 >= 4 )
	{
		TermMsg("PlrHitMonst: illegal player %d", v3);
		//pnum = v7;
	}
	v42 = 0;
	_LOBYTE(pnum) = 4;
	v8 = random(pnum, 100);
	v23 = *(MON_MODE *)((char *)&monster[0]._mmode + v5) == MM_STONE;
	v46 = v8;
	if ( v23 )
		v46 = 0;
	v9 = v3;
	v10 = plr[v9]._pLevel;
	v11 = plr[v9]._pIEnAc + (plr[v9]._pDexterity >> 1) - *((unsigned char *)&monster[0].mArmorClass + v5);
	v12 = v11 + v10 + 50;
	if ( !_LOBYTE(plr[v9]._pClass) )
		v12 = v11 + v10 + 70;
	v13 = plr[v9]._pIBonusToHit + v12;
	if ( v13 < 5 )
		v13 = 5;
	if ( v13 > 95 )
		v13 = 95;
	if ( CheckMonsterHit(arglist, &ret) )
		return ret;
#ifdef _DEBUG
	if ( (signed int)v46 < v13 || debug_mode_key_inverted_v || debug_mode_dollar_sign )
#else
	if ( (signed int)v46 < v13 )
#endif
	{
		_LOBYTE(v15) = 5;
		v16 = plr[v9]._pIMaxDam - plr[v9]._pIMinDam + 1;
		v48 = plr[v9]._pIMinDam;
		v17 = random(v15, v16);
		v18 = 100;
		v19 = plr[v9]._pIBonusDamMod + plr[v9]._pDamageMod + (v48 + v17) * plr[v9]._pIBonusDam / 100 + v48 + v17;
		if ( !_LOBYTE(plr[v9]._pClass) )
		{
			_LOBYTE(v18) = 6;
			v48 = plr[v9]._pLevel;
			v20 = random(v18, 100);
			if ( v20 < v48 )
				v19 *= 2;
		}
		v21 = plr[v9].InvBody[4]._itype;
		v46 = -1;
		if ( v21 == 1 || plr[v9].InvBody[5]._itype == 1 )
			v46 = 1;
		if ( v21 == ITYPE_MACE || plr[v9].InvBody[5]._itype == ITYPE_MACE )
			v46 = ITYPE_MACE;
		v22 = (*(MonsterData **)((char *)&monster[0].MData + v5))->mMonstClass;
		if ( v22 )
		{
			if ( v22 != 2 )
				goto LABEL_40;
			if ( v46 == ITYPE_MACE )
				v19 -= v19 >> 1;
			v23 = v46 == 1;
		}
		else
		{
			if ( v46 == 1 )
				v19 -= v19 >> 1;
			v23 = v46 == ITYPE_MACE;
		}
		if ( v23 )
			v19 += v19 >> 1;
LABEL_40:
		v24 = plr[v9]._pIFlags;
		if ( v24 & 0x40000000 && v22 == 1 )
			v19 *= 3;
		v25 = pnuma;
		v26 = v19 << 6;
		if ( pnuma == myplr )
			*(int *)((char *)&monster[0]._mhitpoints + v5) -= v26;
		if ( v24 & 2 )
		{
			_LOBYTE(v25) = 7;
			v27 = random(v25, v26 >> 3);
			v28 = plr[v9]._pMaxHP;
			v29 = &plr[v9]._pHitPoints;
			*v29 += v27;
			if ( plr[v9]._pHitPoints > v28 )
				*v29 = v28;
			v30 = plr[v9]._pMaxHPBase;
			v31 = &plr[v9]._pHPBase;
			*v31 += v27;
			if ( plr[v9]._pHPBase > v30 )
				*v31 = v30;
			v5 = v43;
			drawhpflag = 1;
		}
		else
		{
			v27 = ret;
		}
		v46 = plr[v9]._pIFlags;
		v32 = v46;
		if ( v32 & 0x6000 && !(v46 & 0x8000000) )
		{
			if ( v32 & 0x2000 )
				v27 = 3 * v26 / 100;
			if ( v32 & 0x4000 )
				v27 = 5 * v26 / 100;
			v33 = plr[v9]._pMaxMana;
			v34 = &plr[v9]._pMana;
			*v34 += v27;
			if ( plr[v9]._pMana > v33 )
				*v34 = v33;
			v35 = plr[v9]._pMaxManaBase;
			v36 = &plr[v9]._pManaBase;
			*v36 += v27;
			if ( plr[v9]._pManaBase > v35 )
				*v36 = v35;
			v5 = v43;
			v32 = v46;
			drawmanaflag = 1;
		}
		if ( v32 & 0x18000 )
		{
			if ( (v32 & 0x8000) != 0 )
				v27 = 3 * v26 / 100;
			if ( v32 & 0x10000 )
				v27 = 5 * v26 / 100;
			v37 = plr[v9]._pMaxHP;
			v38 = &plr[v9]._pHitPoints;
			*v38 += v27;
			if ( plr[v9]._pHitPoints > v37 )
				*v38 = v37;
			v39 = &plr[v9]._pHPBase;
			v40 = plr[v9]._pMaxHPBase;
			*v39 += v27;
			if ( *v39 > v40 )
				*v39 = v40;
			BYTE1(v32) = BYTE1(v46);
			v5 = v43;
			drawhpflag = 1;
		}
		if ( v32 & 0x100 )
			*(int *)((char *)&monster[0]._mFlags + v5) |= 8u;
#ifdef _DEBUG
		if ( debug_mode_dollar_sign || debug_mode_key_inverted_v )
			monster[m]._mhitpoints = 0; /* double check */
#endif
		if ( (signed int)(*(int *)((_BYTE *)&monster[0]._mhitpoints + v5) & 0xFFFFFFC0) > 0 )
		{
			if ( *(MON_MODE *)((char *)&monster[0]._mmode + v5) != MM_STONE )
			{
				if ( v32 & 0x800 )
					M_GetKnockback(arglist);
				M_StartHit(arglist, pnuma, v26);
				goto LABEL_85;
			}
			M_StartHit(arglist, pnuma, v26);
		}
		else
		{
			if ( *(MON_MODE *)((char *)&monster[0]._mmode + v5) != MM_STONE )
			{
				M_StartKill(arglist, pnuma);
				goto LABEL_85;
			}
			M_StartKill(arglist, pnuma);
		}
		*(MON_MODE *)((char *)&monster[0]._mmode + v5) = MM_STONE;
LABEL_85:
		v42 = 1;
	}
	return v42;
}

bool __fastcall PlrHitPlr(int pnum, char p)
{
	char v2; // bl
	unsigned int v3; // esi
	//int v4; // ST04_4
	int v5; // edi
	//int v7; // ST04_4
	unsigned int v8; // esi
	int v9; // ecx
	int v10; // eax
	int v11; // ebx
	int v12; // ebx
	int v13; // eax
	int v14; // eax
	int v15; // ecx
	int v16; // eax
	int v17; // ebx
	int v18; // eax
	int v19; // ecx
	int v20; // edi
	int v21; // ebx
	signed int v22; // edi
	int v23; // eax
	int v24; // edx
	int *v25; // ecx
	int *v26; // ecx
	int v27; // esi
	int v28; // [esp+Ch] [ebp-14h]
	int v29; // [esp+10h] [ebp-10h]
	bool v30; // [esp+14h] [ebp-Ch]
	int arglist; // [esp+18h] [ebp-8h]
	char bPlr; // [esp+1Ch] [ebp-4h]

	v2 = p;
	v3 = pnum;
	bPlr = p;
	v28 = pnum;
	if ( (unsigned char)p >= 4u )
	{
		TermMsg("PlrHitPlr: illegal target player %d", p);
		//pnum = v4;
	}
	arglist = v2;
	v5 = v2;
	v30 = 0;
	if ( plr[v5]._pInvincible || plr[v5]._pSpellFlags & 1 )
		return 0;
	if ( v3 >= 4 )
	{
		TermMsg("PlrHitPlr: illegal attacking player %d", v3);
		//pnum = v7;
	}
	_LOBYTE(pnum) = 4;
	v8 = v3;
	v29 = random(pnum, 100);
	v9 = (plr[v8]._pDexterity >> 1) - plr[v5]._pIBonusAC - plr[v5]._pIAC - plr[v5]._pDexterity / 5;
	v10 = plr[v8]._pLevel;
	v11 = v9 + v10 + 50;
	if ( !_LOBYTE(plr[v8]._pClass) )
		v11 = v9 + v10 + 70;
	v12 = plr[v8]._pIBonusToHit + v11;
	if ( v12 < 5 )
		v12 = 5;
	if ( v12 > 95 )
		v12 = 95;
	v13 = plr[v5]._pmode;
	if ( v13 && v13 != 4 || !plr[v5]._pBlockFlag )
	{
		v14 = 100;
	}
	else
	{
		_LOBYTE(v9) = 5;
		v14 = random(v9, 100);
	}
	v15 = plr[v5]._pDexterity + plr[v5]._pBaseToBlk + 2 * plr[v5]._pLevel - 2 * plr[v8]._pLevel;
	if ( v15 < 0 )
		v15 = 0;
	if ( v15 > 100 )
		v15 = 100;
	if ( v29 < v12 )
	{
		if ( v14 >= v15 )
		{
			v17 = plr[v8]._pIMinDam;
			_LOBYTE(v15) = 5;
			v18 = random(v15, plr[v8]._pIMaxDam - v17 + 1);
			v19 = 100;
			v20 = plr[v8]._pIBonusDamMod + plr[v8]._pDamageMod + (v17 + v18) * plr[v8]._pIBonusDam / 100 + v17 + v18;
			if ( !_LOBYTE(plr[v8]._pClass) )
			{
				v21 = plr[v8]._pLevel;
				_LOBYTE(v19) = 6;
				if ( random(v19, 100) < v21 )
					v20 *= 2;
			}
			v22 = v20 << 6;
			if ( plr[v8]._pIFlags & 2 )
			{
				_LOBYTE(v19) = 7;
				v23 = random(v19, v22 >> 3);
				v24 = plr[v8]._pMaxHP;
				v25 = &plr[v8]._pHitPoints;
				*v25 += v23;
				if ( plr[v8]._pHitPoints > v24 )
					*v25 = v24;
				v26 = &plr[v8]._pHPBase;
				v27 = plr[v8]._pMaxHPBase;
				*v26 += v23;
				if ( *v26 > v27 )
					*v26 = v27;
				drawhpflag = 1;
			}
			if ( v28 == myplr )
				NetSendCmdDamage(1u, bPlr, v22);
			StartPlrHit(arglist, v22, 0);
		}
		else
		{
			v16 = GetDirection(plr[v5].WorldX, plr[v5].WorldY, plr[v8].WorldX, plr[v8].WorldY);
			StartPlrBlock(arglist, v16);
		}
		v30 = 1;
	}
	return v30;
}

bool __fastcall PlrHitObj(int pnum, int mx, int my)
{
	int oi; // edx

	if ( dObject[mx][my] <= 0 )
		oi = -1 - dObject[mx][my];
	else
		oi = dObject[mx][my] - 1;

	if ( object[oi]._oBreak != 1 )
		return 0;

	BreakObject(pnum, oi);
	return 1;
}

int __fastcall PM_DoAttack(int pnum)
{
	int v1; // esi
	int v2; // esi
	int v3; // ecx
	int v4; // eax
	int v5; // eax
	int v6; // ebx
	int v7; // edi
	int v8; // eax
	int v9; // edx
	int v10; // ecx
	//int v11; // eax
	int v12; // edx
	int v13; // eax
	bool v14; // eax
	int v15; // edx
	char v16; // al
	//int v17; // eax
	int v19; // [esp+Ch] [ebp-8h]
	int arglist; // [esp+10h] [ebp-4h]

	v1 = pnum;
	arglist = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoAttack: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v2]._pIFlags;
	v4 = plr[v2]._pAnimFrame;
	if ( v3 & 0x20000 && v4 == 1 ) // quick attack
		plr[v2]._pAnimFrame = 2;
	if ( v3 & 0x40000 && (v4 == 1 || v4 == 3) ) // fast attack
		++plr[v2]._pAnimFrame;
	if ( v3 & 0x80000 && (v4 == 1 || v4 == 3 || v4 == 5) ) // faster attack
		++plr[v2]._pAnimFrame;
	if ( v3 & 0x100000 && (v4 == 1 || v4 == 4) ) // fastest attack
		plr[v2]._pAnimFrame += 2;
	if ( plr[v2]._pAnimFrame == plr[v2]._pAFNum - 1 )
		PlaySfxLoc(PS_SWING, plr[v2].WorldX, plr[v2].WorldY);
	if ( plr[v2]._pAnimFrame != plr[v2]._pAFNum )
		goto LABEL_49;
	v5 = plr[v2]._pdir;
	v6 = plr[v2].WorldX + offset_x[v5];
	v7 = plr[v2].WorldY + offset_y[v5];
	v8 = v7 + 112 * v6;
	v19 = v8;
	v9 = dMonster[0][v8];
	if ( !v9 )
	{
LABEL_29:
		if ( plr[v2]._pIFlags & 0x10 )
		{
			AddMissile(v6, v7, 1, 0, 0, MIS_WEAPEXP, 0, arglist, 0, 0);
			v8 = v19;
		}
		if ( plr[v2]._pIFlags & 0x20 )
		{
			AddMissile(v6, v7, 2, 0, 0, MIS_WEAPEXP, 0, arglist, 0, 0);
			v8 = v19;
		}
		v12 = dMonster[0][v8];
		if ( v12 )
		{
			if ( v12 <= 0 )
				v13 = -1 - v12;
			else
				v13 = v12 - 1;
			v14 = PlrHitMonst(arglist, v13);
			goto LABEL_46;
		}
		v15 = (unsigned char)dPlayer[0][v8];
		if ( (_BYTE)v15 && !FriendlyMode )
		{
			if ( (char)v15 <= 0 )
				v16 = -1 - v15;
			else
				v16 = v15 - 1;
			v14 = PlrHitPlr(arglist, v16);
LABEL_46:
			if ( v14 )
			{
				//_LOBYTE(v17) = WeaponDur(arglist, 30);
				if ( WeaponDur(arglist, 30) )
					goto LABEL_48;
			}
			goto LABEL_49;
		}
		if ( dObject[0][v8] > 0 )
		{
			v14 = PlrHitObj(arglist, v6, v7);
			goto LABEL_46;
		}
LABEL_49:
		if ( plr[v2]._pAnimFrame != plr[v2]._pAFrames )
			return 0;
LABEL_48:
		StartStand(arglist, plr[v2]._pdir);
		ClearPlrPVars(arglist);
		return 1;
	}
	if ( v9 <= 0 )
		v10 = -1 - v9;
	else
		v10 = v9 - 1;
	//_LOBYTE(v11) = CanTalkToMonst(v10);
	if ( !CanTalkToMonst(v10) )
	{
		v8 = v19;
		goto LABEL_29;
	}
	plr[v2]._pVar1 = 0;
	return 0;
}
// 484368: using guessed type int FriendlyMode;

int __fastcall PM_DoRangeAttack(int pnum)
{
	int v1; // edi
	int v2; // esi
	int v3; // ecx
	int v4; // eax
	int v5; // eax
	//int v6; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoRangeAttack: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pIFlags;
	v4 = plr[v1]._pAnimFrame;
	if ( v3 & 0x20000 && v4 == 1 )
		plr[v2]._pAnimFrame = 2;
	if ( v3 & 0x40000 && (v4 == 1 || v4 == 3) )
		++plr[v2]._pAnimFrame;
	if ( plr[v2]._pAnimFrame != plr[v2]._pAFNum )
		goto LABEL_21;
	v5 = 0;
	if ( v3 & 8 )
		v5 = MIS_FARROW;
	if ( v3 & 0x2000000 )
		v5 = MIS_LARROW;
	AddMissile(plr[v2].WorldX, plr[v2].WorldY, plr[v2]._pVar1, plr[v2]._pVar2, plr[v2]._pdir, v5, 0, v1, 4, 0);
	PlaySfxLoc(PS_BFIRE, plr[v2].WorldX, plr[v2].WorldY);
	//_LOBYTE(v6) = WeaponDur(v1, 40);
	if ( !WeaponDur(v1, 40) )
	{
LABEL_21:
		if ( plr[v2]._pAnimFrame < plr[v2]._pAFrames )
			return 0;
	}
	StartStand(v1, plr[v2]._pdir);
	ClearPlrPVars(v1);
	return 1;
}

void __fastcall ShieldDur(int pnum)
{
	int v1; // edi
	int v2; // esi
	int v3; // ecx
	int v4; // ecx
	int v5; // ecx
	int v6; // ecx

	v1 = pnum;
	if ( pnum == myplr )
	{
		if ( (unsigned int)pnum >= 4 )
			TermMsg("ShieldDur: illegal player %d", pnum);
		v2 = v1;
		if ( plr[v1].InvBody[4]._itype == ITYPE_SHIELD )
		{
			v3 = plr[v2].InvBody[4]._iDurability;
			if ( v3 == 255 )
				return;
			v4 = v3 - 1;
			plr[v2].InvBody[4]._iDurability = v4;
			if ( !v4 )
			{
				NetSendCmdDelItem(1u, 4u);
				plr[v2].InvBody[4]._itype = ITYPE_NONE;
				CalcPlrInv(v1, 1u);
			}
		}
		if ( plr[v2].InvBody[5]._itype == ITYPE_SHIELD )
		{
			v5 = plr[v2].InvBody[5]._iDurability;
			if ( v5 != 255 )
			{
				v6 = v5 - 1;
				plr[v2].InvBody[5]._iDurability = v6;
				if ( !v6 )
				{
					NetSendCmdDelItem(1u, 5u);
					plr[v2].InvBody[5]._itype = ITYPE_NONE;
					CalcPlrInv(v1, 1u);
				}
			}
		}
	}
}

int __fastcall PM_DoBlock(int pnum)
{
	int v1; // esi
	int v2; // eax
	int v3; // ecx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoBlock: illegal player %d", pnum);
	v2 = v1;
	if ( plr[v1]._pIFlags & 0x1000000 && plr[v2]._pAnimFrame != 1 )
		plr[v2]._pAnimFrame = plr[v2]._pBFrames;
	if ( plr[v2]._pAnimFrame < plr[v2]._pBFrames )
		return 0;
	StartStand(v1, plr[v2]._pdir);
	ClearPlrPVars(v1);
	_LOBYTE(v3) = 3;
	if ( !random(v3, 10) )
		ShieldDur(v1);
	return 1;
}

int __fastcall PM_DoSpell(int pnum)
{
	int v1; // edi
	int v2; // esi

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoSpell: illegal player %d", pnum);
	v2 = v1;
	if ( plr[v1]._pVar8 == plr[v1]._pSFNum )
	{
		CastSpell(
			v1,
			plr[v2]._pSpell,
			plr[v2].WorldX,
			plr[v2].WorldY,
			plr[v2]._pVar1,
			plr[v2]._pVar2,
			0,
			plr[v2]._pVar4);
		if ( !plr[v2]._pSplFrom )
		{
			if ( _LOBYTE(plr[v2]._pRSplType) == 2
			  && !(plr[v2]._pScrlSpells[1] & ((unsigned __int64)((__int64)1 << (_LOBYTE(plr[v2]._pRSpell) - 1)) >> 32) | plr[v2]._pScrlSpells[0] & (unsigned int)((__int64)1 << (_LOBYTE(plr[v2]._pRSpell) - 1))) )
			{
				plr[v2]._pRSpell = -1;
				_LOBYTE(plr[v2]._pRSplType) = 4;
				drawpanflag = 255;
			}
			if ( _LOBYTE(plr[v2]._pRSplType) == 3
			  && !(plr[v2]._pISpells[1] & ((unsigned __int64)((__int64)1 << (_LOBYTE(plr[v2]._pRSpell) - 1)) >> 32) | plr[v2]._pISpells[0] & (unsigned int)((__int64)1 << (_LOBYTE(plr[v2]._pRSpell) - 1))) )
			{
				plr[v2]._pRSpell = -1;
				_LOBYTE(plr[v2]._pRSplType) = 4;
				drawpanflag = 255;
			}
		}
	}
	++plr[v2]._pVar8;
	if ( leveltype )
	{
		if ( plr[v2]._pAnimFrame == plr[v2]._pSFrames )
		{
			StartStand(v1, plr[v2]._pdir);
			goto LABEL_16;
		}
	}
	else if ( plr[v2]._pVar8 > plr[v2]._pSFrames )
	{
		StartWalkStand(v1);
LABEL_16:
		ClearPlrPVars(v1);
		return 1;
	}
	return 0;
}
// 52571C: using guessed type int drawpanflag;
// 5BB1ED: using guessed type char leveltype;

int __fastcall PM_DoGotHit(int pnum)
{
	int v1; // esi
	int v2; // eax
	int v3; // edx
	int v4; // ecx
	int v5; // ecx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoGotHit: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pIFlags;
	v4 = plr[v1]._pAnimFrame;
	if ( v3 & 0x200000 && v4 == 3 )
		plr[v2]._pAnimFrame = 4;
	if ( v3 & 0x400000 && (v4 == 3 || v4 == 5) )
		++plr[v2]._pAnimFrame;
	if ( v3 & 0x800000 && (v4 == 1 || v4 == 3 || v4 == 5) )
		++plr[v2]._pAnimFrame;
	if ( plr[v2]._pAnimFrame < plr[v2]._pHFrames )
		return 0;
	StartStand(v1, plr[v2]._pdir);
	ClearPlrPVars(v1);
	_LOBYTE(v5) = 3;
	if ( random(v5, 4) )
		ArmorDur(v1);
	return 1;
}

void __fastcall ArmorDur(int pnum)
{
	int v1; // ebp
	//int v2; // ST04_4
	PlayerStruct *v3; // esi
	int v4; // eax
	int v5; // edi
	int v6; // esi
	int v7; // ecx
	int v8; // ecx
	unsigned char v9; // dl

	v1 = pnum;
	if ( pnum == myplr )
	{
		if ( (unsigned int)pnum >= 4 )
		{
			TermMsg("ArmorDur: illegal player %d", pnum);
			//pnum = v2;
		}
		v3 = &plr[v1];
		if ( v3->InvBody[6]._itype != -1 || v3->InvBody[0]._itype != -1 )
		{
			_LOBYTE(pnum) = 8;
			v4 = random(pnum, 3);
			v5 = v3->InvBody[6]._itype;
			if ( v5 == -1 )
				goto LABEL_23;
			if ( v3->InvBody[0]._itype == -1 )
				v4 = 1;
			if ( v5 == -1 )
			{
LABEL_23:
				if ( v3->InvBody[0]._itype != -1 )
					v4 = 0;
			}
			if ( v4 )
				v6 = (int)&v3->InvBody[6];
			else
				v6 = (int)v3->InvBody;
			v7 = *(_DWORD *)(v6 + 236);
			if ( v7 != 255 )
			{
				v8 = v7 - 1;
				*(_DWORD *)(v6 + 236) = v8;
				if ( !v8 )
				{
					if ( v4 )
						v9 = 6;
					else
						v9 = 0;
					NetSendCmdDelItem(1u, v9);
					*(_DWORD *)(v6 + 8) = -1;
					CalcPlrInv(v1, 1u);
				}
			}
		}
	}
}

int __fastcall PM_DoDeath(int pnum)
{
	int v1; // edi
	int v2; // esi
	int v3; // ecx
	int v4; // eax
	int v5; // eax

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PM_DoDeath: illegal player %d", pnum);
	v2 = v1;
	if ( plr[v1]._pVar8 >= 2 * plr[v1]._pDFrames )
	{
		if ( deathdelay > 1 && v1 == myplr && --deathdelay == 1 )
		{
			deathflag = 1;
			if ( gbMaxPlayers == 1 )
				gamemenu_previous();
		}
		v3 = plr[v2].WorldY;
		plr[v2]._pAnimFrame = plr[v2]._pAnimLen;
		v4 = plr[v2].WorldX;
		plr[v2]._pAnimDelay = 10000;
		dFlags[v4][v3] |= 4u;
	}
	v5 = plr[v2]._pVar8;
	if ( v5 < 100 )
		plr[v2]._pVar8 = v5 + 1;
	return 0;
}
// 679660: using guessed type char gbMaxPlayers;
// 69B7C4: using guessed type int deathdelay;

void __fastcall CheckNewPath(int pnum)
{
	int v1; // edi
	int v2; // ebx
	int v3; // eax
	int v4; // ecx
	bool v5; // zf
	int v6; // eax
	int v7; // esi
	int v8; // eax
	int v9; // edx
	int v10; // esi
	int v11; // esi
	int v12; // eax
	int v13; // eax
	int v14; // ecx
	int v15; // edx
	int v16; // eax
	int v17; // eax
	int v18; // eax
	int v19; // ecx
	int v20; // eax
	int v21; // edi
	int v22; // esi
	int v23; // ST38_4
	int v24; // eax
	int v25; // esi
	int v26; // esi
	int v27; // ST38_4
	int v28; // eax
	int v29; // ecx
	int v30; // edx
	int v31; // ecx
	int *v32; // esi
	int *v33; // edi
	int v34; // esi
	int v35; // eax
	int v36; // ecx
	int v37; // eax
	int v38; // eax
	int v39; // eax
	int v40; // eax
	int v41; // eax
	int *v42; // esi
	int *v43; // edi
	int v44; // eax
	int v45; // eax
	int v46; // esi
	int v47; // esi
	int v48; // eax
	int v49; // ecx
	int v50; // esi
	int v51; // eax
	int v52; // ecx
	int v53; // edi
	int v54; // esi
	int v55; // ST38_4
	int v56; // eax
	int v57; // edi
	int v58; // esi
	int v59; // ST38_4
	int v60; // eax
	int v61; // eax
	int v62; // ecx
	int v63; // esi
	int v64; // ST38_4
	int v65; // eax
	int v66; // esi
	int v67; // edi
	int v68; // eax
	int v69; // esi
	int v70; // esi
	int v71; // eax
	int v72; // ecx
	int v73; // eax
	int v74; // eax
	int *v75; // esi
	int *v76; // edi
	int v77; // eax
	int v78; // eax
	int v79; // eax
	int v80; // eax
	int *v81; // esi
	int *v82; // edi
	int v83; // eax
	int v84; // eax
	int v85; // eax
	int v86; // [esp-18h] [ebp-34h]
	int v87; // [esp-10h] [ebp-2Ch]
	int v88; // [esp-10h] [ebp-2Ch]
	int v89; // [esp-Ch] [ebp-28h]
	int v90; // [esp-Ch] [ebp-28h]
	int v91; // [esp-8h] [ebp-24h]
	int v92; // [esp-8h] [ebp-24h]
	int v93; // [esp-8h] [ebp-24h]
	int v94; // [esp-4h] [ebp-20h]
	int v95; // [esp-4h] [ebp-20h]
	int v96; // [esp-4h] [ebp-20h]
	signed int v97; // [esp+Ch] [ebp-10h]
	int arglist; // [esp+10h] [ebp-Ch]
	int arglista; // [esp+10h] [ebp-Ch]
	int arglistb; // [esp+10h] [ebp-Ch]
	int v101; // [esp+14h] [ebp-8h]
	int v102; // [esp+14h] [ebp-8h]
	int v103; // [esp+14h] [ebp-8h]
	int v104; // [esp+14h] [ebp-8h]
	int p; // [esp+18h] [ebp-4h]

	v1 = pnum;
	p = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("CheckNewPath: illegal player %d", pnum);
	v2 = v1;
	if ( plr[v1].destAction == 20 )
		MakePlrPath(v1, monster[plr[v2].destParam1]._mfutx, monster[plr[v2].destParam1]._mfuty, 0);
	if ( plr[v2].destAction == 21 )
		MakePlrPath(v1, plr[plr[v2].destParam1]._px, plr[plr[v2].destParam1]._py, 0);
	if ( plr[v2].walkpath[0] == -1 )
	{
		v18 = plr[v2].destAction;
		if ( v18 == -1 )
			return;
		v19 = plr[v2]._pmode;
		if ( v19 == PM_STAND )
		{
			switch ( v18 )
			{
				case 9:
					v20 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, plr[v2].destParam1, plr[v2].destParam2);
					goto LABEL_52;
				case 10:
					v30 = plr[v2].WorldY;
					v31 = plr[v2].WorldX;
					v32 = &plr[v2].destParam2;
					v33 = &plr[v2].destParam1;
					goto LABEL_59;
				case 12:
					v39 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, plr[v2].destParam1, plr[v2].destParam2);
					StartSpell(p, v39, plr[v2].destParam1, plr[v2].destParam2);
					v40 = plr[v2].destParam3;
					goto LABEL_66;
				case 13:
					v46 = plr[v2].destParam1;
					arglista = v46;
					v47 = v46;
					v102 = abs(plr[v2].WorldX - object[v47]._ox);
					v48 = abs(plr[v2].WorldY - object[v47]._oy);
					if ( v48 > 1 )
					{
						v49 = object[v47]._oy;
						if ( dObject[object[v47]._ox-1][v49-1] == -1 - arglista ) /* dungeon[39][112 * object[v47]._ox + 39 + v49] check */
							v48 = abs(plr[v2].WorldY - v49 + 1);
					}
					if ( v102 > 1 || v48 > 1 )
						break;
					if ( object[v47]._oBreak != 1 )
						goto LABEL_73;
					goto LABEL_80;
				case 14:
					v50 = plr[v2].destParam1;
					arglista = v50;
					v47 = v50;
					v103 = abs(plr[v2].WorldX - object[v47]._ox);
					v51 = abs(plr[v2].WorldY - object[v47]._oy);
					if ( v51 > 1 )
					{
						v52 = object[v47]._oy;
						if ( dObject[object[v47]._ox-1][v52-1] == -1 - arglista ) /* dungeon[39][112 * object[v47]._ox + 39 + v52] check */
							v51 = abs(plr[v2].WorldY - v52 + 1);
					}
					if ( v103 > 1 || v51 > 1 )
						break;
					if ( object[v47]._oBreak == 1 )
					{
LABEL_80:
						v20 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, object[v47]._ox, object[v47]._oy);
LABEL_81:
						v29 = p;
LABEL_82:
						StartAttack(v29, v20);
					}
					else
					{
						TryDisarm(p, arglista);
LABEL_73:
						OperateObject(p, arglista, 0);
					}
					break;
				case 15:
					if ( v1 == myplr )
					{
						v53 = plr[v2].destParam1;
						v54 = plr[v2].destParam1;
						v55 = abs(plr[v2].WorldX - item[v54]._ix);
						v56 = abs(plr[v2].WorldY - item[v54]._iy);
						if ( v55 <= 1 && v56 <= 1 && pcurs == 1 && !item[v54]._iRequest )
						{
							NetSendCmdGItem(1u, CMD_REQUESTGITEM, myplr, myplr, v53);
							item[v54]._iRequest = 1;
						}
					}
					break;
				case 16:
					if ( v1 == myplr )
					{
						v57 = plr[v2].destParam1;
						v58 = plr[v2].destParam1;
						v59 = abs(plr[v2].WorldX - item[v58]._ix);
						v60 = abs(plr[v2].WorldY - item[v58]._iy);
						if ( v59 <= 1 && v60 <= 1 && pcurs == 1 )
							NetSendCmdGItem(1u, CMD_REQUESTAGITEM, myplr, myplr, v57);
					}
					break;
				case 17:
					if ( v1 == myplr )
						TalkToTowner(v1, plr[v2].destParam1);
					break;
				case 18:
					if ( object[plr[v2].destParam1]._oBreak != 1 )
						OperateObject(v1, plr[v2].destParam1, 1u);
					break;
				case 20:
					v21 = plr[v2].destParam1;
					v22 = plr[v2].destParam1;
					v23 = abs(plr[v2].WorldX - monster[v22]._mfutx);
					v24 = abs(plr[v2].WorldY - monster[v22]._mfuty);
					if ( v23 > 1 || v24 > 1 )
						break;
					v20 = GetDirection(plr[v2]._px, plr[v2]._py, monster[v22]._mfutx, monster[v22]._mfuty);
					v25 = monster[v22].mtalkmsg;
					if ( v25 && v25 != QUEST_VILE14 )
						goto LABEL_56;
					goto LABEL_81;
				case 21:
					v26 = plr[v2].destParam1;
					v27 = abs(plr[v2].WorldX - plr[v26]._px);
					v28 = abs(plr[v2].WorldY - plr[v26]._py);
					if ( v27 > 1 || v28 > 1 )
						break;
					v20 = GetDirection(plr[v2]._px, plr[v2]._py, plr[v26]._px, plr[v26]._py);
LABEL_52:
					v29 = v1;
					goto LABEL_82;
				case 22:
					v21 = plr[v2].destParam1;
					v34 = plr[v2].destParam1;
					v35 = GetDirection(plr[v2]._px, plr[v2]._py, monster[v34]._mfutx, monster[v34]._mfuty);
					v36 = monster[v34].mtalkmsg;
					if ( v36 && v36 != QUEST_VILE14 )
LABEL_56:
						TalktoMonster(v21);
					else
						StartRangeAttack(p, v35, monster[v34]._mfutx, monster[v34]._mfuty);
					break;
				case 23:
					v30 = plr[v2]._py;
					v37 = plr[v2].destParam1;
					v31 = plr[v2]._px;
					v32 = &plr[v37]._py;
					v33 = &plr[v37]._px;
LABEL_59:
					v38 = GetDirection(v31, v30, *v33, *v32);
					StartRangeAttack(p, v38, *v33, *v32);
					break;
				case 24:
					v41 = plr[v2].destParam1;
					v42 = &monster[v41]._mfuty;
					v43 = &monster[v41]._mfutx;
					goto LABEL_65;
				case 25:
					v44 = plr[v2].destParam1;
					v42 = &plr[v44]._py;
					v43 = &plr[v44]._px;
LABEL_65:
					v45 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, *v43, *v42);
					StartSpell(p, v45, *v43, *v42);
					v40 = plr[v2].destParam2;
					goto LABEL_66;
				case 26:
					StartSpell(v1, plr[v2].destParam3, plr[v2].destParam1, plr[v2].destParam2);
					plr[v2]._pVar3 = plr[v2].destParam3;
					v40 = plr[v2].destParam4;
LABEL_66:
					plr[v2]._pVar4 = v40;
					break;
				default:
					break;
			}
			FixPlayerLocation(p, plr[v2]._pdir);
			goto LABEL_143;
		}
		if ( v19 == 4 && plr[v2]._pAnimFrame > plr[myplr]._pAFNum )
		{
			switch ( v18 )
			{
				case 9:
					v61 = GetDirection(plr[v2]._px, plr[v2]._py, plr[v2].destParam1, plr[v2].destParam2);
LABEL_105:
					v62 = v1;
LABEL_106:
					StartAttack(v62, v61);
LABEL_107:
					plr[v2].destAction = -1;
					break;
				case 20:
					v63 = plr[v2].destParam1;
					v64 = abs(plr[v2].WorldX - monster[v63]._mfutx);
					v65 = abs(plr[v2].WorldY - monster[v63]._mfuty);
					if ( v64 > 1 || v65 > 1 )
						goto LABEL_107;
					v61 = GetDirection(plr[v2]._px, plr[v2]._py, monster[v63]._mfutx, monster[v63]._mfuty);
					goto LABEL_105;
				case 21:
					v66 = plr[v2].destParam1;
					v67 = abs(plr[v2].WorldX - plr[v66]._px);
					v68 = abs(plr[v2].WorldY - plr[v66]._py);
					if ( v67 > 1 || v68 > 1 )
						goto LABEL_107;
					v61 = GetDirection(plr[v2]._px, plr[v2]._py, plr[v66]._px, plr[v66]._py);
					v62 = p;
					goto LABEL_106;
				case 13:
					v69 = plr[v2].destParam1;
					arglistb = v69;
					v70 = v69;
					v104 = abs(plr[v2].WorldX - object[v70]._ox);
					v71 = abs(plr[v2].WorldY - object[v70]._oy);
					if ( v71 > 1 )
					{
						v72 = object[v70]._oy;
						if ( dObject[object[v70]._ox-1][v72-1] == -1 - arglistb ) /* dungeon[39][112 * object[v70]._ox + 39 + v72] check */
							v71 = abs(plr[v2].WorldY - v72 + 1);
					}
					if ( v104 <= 1 && v71 <= 1 )
					{
						if ( object[v70]._oBreak == 1 )
						{
							v73 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, object[v70]._ox, object[v70]._oy);
							StartAttack(p, v73);
						}
						else
						{
							OperateObject(p, arglistb, 0);
						}
					}
					break;
			}
		}
		if ( plr[v2]._pmode == PM_RATTACK && plr[v2]._pAnimFrame > plr[myplr]._pAFNum )
		{
			v74 = plr[v2].destAction;
			switch ( v74 )
			{
				case 10:
					v75 = &plr[v2].destParam2;
					v76 = &plr[v2].destParam1;
LABEL_133:
					v79 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, *v76, *v75);
					StartRangeAttack(p, v79, *v76, *v75);
					plr[v2].destAction = -1;
					break;
				case 22:
					v77 = plr[v2].destParam1;
					v75 = &monster[v77]._mfuty;
					v76 = &monster[v77]._mfutx;
					goto LABEL_133;
				case 23:
					v78 = plr[v2].destParam1;
					v75 = &plr[v78]._py;
					v76 = &plr[v78]._px;
					goto LABEL_133;
			}
		}
		if ( plr[v2]._pmode == PM_SPELL && plr[v2]._pAnimFrame > plr[v2]._pSFNum )
		{
			v80 = plr[v2].destAction;
			switch ( v80 )
			{
				case 12:
					v81 = &plr[v2].destParam2;
					v82 = &plr[v2].destParam1;
					break;
				case 24:
					v83 = plr[v2].destParam1;
					v81 = &monster[v83]._mfuty;
					v82 = &monster[v83]._mfutx;
					break;
				case 25:
					v84 = plr[v2].destParam1;
					v81 = &plr[v84]._py;
					v82 = &plr[v84]._px;
					break;
				default:
					return;
			}
			v85 = GetDirection(plr[v2].WorldX, plr[v2].WorldY, *v82, *v81);
			StartSpell(p, v85, *v82, *v81);
			goto LABEL_143;
		}
		return;
	}
	if ( plr[v2]._pmode == PM_STAND )
	{
		if ( v1 == myplr )
		{
			v3 = plr[v2].destAction;
			if ( v3 == 20 || v3 == 21 )
			{
				v4 = plr[v2].destParam1;
				v5 = v3 == 20;
				v6 = plr[v2]._px;
				arglist = plr[v2].destParam1;
				if ( v5 )
				{
					v7 = v4;
					v101 = abs(v6 - monster[v4]._mfutx);
					v8 = abs(plr[v2]._py - monster[v7]._mfuty);
					v9 = plr[v2]._py;
					v94 = monster[v7]._mfuty;
					v91 = monster[v7]._mfutx;
				}
				else
				{
					v10 = v4;
					v101 = abs(v6 - plr[v4]._px);
					v8 = abs(plr[v2]._py - plr[v10]._py);
					v9 = plr[v2]._py;
					v94 = plr[v10]._py;
					v91 = plr[v10]._px;
				}
				v97 = v8;
				v11 = GetDirection(plr[v2]._px, v9, v91, v94);
				if ( v101 < 2 && v97 < 2 )
				{
					ClrPlrPath(p);
					v12 = monster[arglist].mtalkmsg;
					if ( v12 && v12 != QUEST_VILE14 )
						TalktoMonster(arglist);
					else
						StartAttack(p, v11);
					plr[v2].destAction = -1;
				}
			}
		}
		if ( currlevel )
		{
			v13 = SLOBYTE(plr[v2]._pClass);
			v14 = PWVel[v13][0];
			v15 = PWVel[v13][1];
			v16 = PWVel[v13][2];
		}
		else
		{
			v14 = 2048;
			v15 = 1024;
			v16 = 512;
		}
		switch ( plr[v2].walkpath[0] )
		{
			case WALK_NE:
				v95 = 2;
				v92 = DIR_NE;
				v89 = -1;
				v87 = 0;
				v17 = -v16;
				goto LABEL_37;
			case WALK_NW:
				v95 = 8;
				v92 = DIR_NW;
				v89 = 0;
				v87 = -1;
				v17 = -v16;
				v15 = -v15;
LABEL_37:
				StartWalk(p, v15, v17, v87, v89, v92, v95);
				break;
			case WALK_SE:
				v96 = 4;
				v93 = DIR_SE;
				v90 = 0;
				v88 = 1;
				v86 = -32;
				goto LABEL_32;
			case WALK_SW:
				v96 = 6;
				v93 = DIR_SW;
				v90 = 1;
				v88 = 0;
				v86 = 32;
				v15 = -v15;
LABEL_32:
				StartWalk2(p, v15, v16, v86, -16, v88, v90, v93, v96);
				break;
			case WALK_N:
				StartWalk(p, 0, -v15, -1, -1, DIR_N, 1);
				break;
			case WALK_E:
				StartWalk3(p, v14, 0, -32, -16, 1, -1, 1, 0, DIR_E, 3);
				break;
			case WALK_S:
				StartWalk2(p, 0, v15, 0, -32, 1, 1, DIR_S, 5);
				break;
			case WALK_W:
				StartWalk3(p, -v14, 0, 32, -16, -1, 1, 0, 1, DIR_W, 7);
				break;
			default:
				break;
		}
		qmemcpy(plr[v2].walkpath, &plr[v2].walkpath[1], 0x18u);
		plr[v2].walkpath[24] = -1;
		if ( plr[v2]._pmode == PM_STAND )
		{
			StartStand(p, plr[v2]._pdir);
LABEL_143:
			plr[v2].destAction = -1;
			return;
		}
	}
}

bool __fastcall PlrDeathModeOK(int pnum)
{
	int v1; // esi
	bool result; // al
	int v3; // esi

	v1 = pnum;
	if ( pnum != myplr )
		goto LABEL_10;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("PlrDeathModeOK: illegal player %d", pnum);
	v3 = plr[v1]._pmode;
	if ( v3 == PM_DEATH || v3 == PM_QUIT )
LABEL_10:
		result = 1;
	else
		result = v3 == PM_NEWLVL;
	return result;
}

void __cdecl ValidatePlayer()
{
	int v0; // edi
	int v1; // esi
	char *v2; // eax
	int v3; // ecx
	int v4; // ecx
	int *v5; // eax
	int v6; // eax
	int v7; // edx
	int v8; // edx
	int v9; // edx
	int v10; // eax
	int *v11; // ebx
	signed int v12; // edi
	char *v13; // eax
	__int64 v14; // [esp+Ch] [ebp-8h]

	v0 = 0;
	v14 = (__int64)0;
	if ( (unsigned int)myplr >= 4 )
		TermMsg("ValidatePlayer: illegal player %d", myplr);
	v1 = myplr;
	v2 = &plr[myplr]._pLevel;
	if ( *v2 > 50 )
		*v2 = 50;
	v3 = plr[v1]._pNextExper;
	if ( plr[v1]._pExperience > v3 )
		plr[v1]._pExperience = v3;
	v4 = 0;
	if ( plr[v1]._pNumInv > 0 )
	{
		v5 = &plr[v1].InvList[0]._ivalue;
		do
		{
			if ( *(v5 - 47) == 11 )
			{
				if ( *v5 > 5000 )
					*v5 = 5000;
				v4 += *v5;
			}
			++v0;
			v5 += 92;
		}
		while ( v0 < plr[v1]._pNumInv );
	}
	if ( v4 != plr[v1]._pGold )
		plr[v1]._pGold = v4;
	v6 = SLOBYTE(plr[v1]._pClass);
	v7 = MaxStats[v6][0];
	if ( plr[v1]._pBaseStr > v7 )
		plr[v1]._pBaseStr = v7;
	v8 = MaxStats[v6][1];
	if ( plr[v1]._pBaseMag > v8 )
		plr[v1]._pBaseMag = v8;
	v9 = MaxStats[v6][2];
	if ( plr[v1]._pBaseDex > v9 )
		plr[v1]._pBaseDex = v9;
	v10 = MaxStats[v6][3];
	if ( plr[v1]._pBaseVit > v10 )
		plr[v1]._pBaseVit = v10;
	v11 = &spelldata[1].sBookLvl;
	v12 = 1;
	do
	{
		if ( *v11 != -1 )
		{
			v14 |= (__int64)1 << ((unsigned char)v12 - 1);
			v13 = &plr[v1]._pSplLvl[v12];
			if ( *v13 > 15 )
				*v13 = 15;
		}
		v11 += 14;
		++v12;
	}
	while ( (signed int)v11 < (signed int)&spelldata[37].sBookLvl );
	*(_QWORD *)plr[v1]._pMemSpells &= v14;
}

void __cdecl ProcessPlayers()
{
	int v0; // eax
	int v1; // eax
	unsigned char *v2; // ecx
	char v3; // al
	int v4; // ebp
	int *v5; // esi
	int v6; // eax
	//int v7; // eax
	int v8; // eax
	int v9; // eax
	int v10; // eax
	int v11; // edi
	int v12; // eax
	char *v13; // eax
	char *v14; // eax

	v0 = myplr;
	if ( (unsigned int)myplr >= 4 )
	{
		TermMsg("ProcessPlayers: illegal player %d", myplr);
		v0 = myplr;
	}
	v1 = v0;
	v2 = &plr[v1].pLvlLoad;
	v3 = plr[v1].pLvlLoad;
	if ( v3 )
		*v2 = v3 - 1;
	v4 = 0;
	if ( sfxdelay > 0 && !--sfxdelay )
		PlaySFX(sfxdnum);
	ValidatePlayer();
	v5 = &plr[0]._pHitPoints;
	do
	{
		v6 = (int)(v5 - 89);
		if ( *((_BYTE *)v5 - 379) && currlevel == *(_DWORD *)v6 && (v4 == myplr || !*(_BYTE *)(v6 + 267)) )
		{
			CheckCheatStats(v4);
			//_LOBYTE(v7) = PlrDeathModeOK(v4);
			if ( !PlrDeathModeOK(v4) && (signed int)(*v5 & 0xFFFFFFC0) <= 0 )
				SyncPlrKill(v4, -1);
			if ( v4 == myplr )
			{
				if ( v5[5294] & 0x40 && currlevel )
				{
					*v5 -= 4;
					v8 = *v5;
					*(v5 - 2) -= 4;
					if ( (signed int)(v8 & 0xFFFFFFC0) <= 0 )
						SyncPlrKill(v4, 0);
					drawhpflag = 1;
				}
				if ( *((_BYTE *)v5 + 21179) & 8 )
				{
					v9 = v5[3];
					if ( v9 > 0 )
					{
						v10 = v9 - v5[5];
						v5[5] = 0;
						drawmanaflag = 1;
						v5[3] = v10;
					}
				}
			}
			v11 = 0;
			do
			{
				switch ( *(v5 - 102) )
				{
					case PM_STAND:
						v12 = PM_DoStand(v4);
						goto LABEL_38;
					case PM_WALK:
						v12 = PM_DoWalk(v4);
						goto LABEL_38;
					case PM_WALK2:
						v12 = PM_DoWalk2(v4);
						goto LABEL_38;
					case PM_WALK3:
						v12 = PM_DoWalk3(v4);
						goto LABEL_38;
					case PM_ATTACK:
						v12 = PM_DoAttack(v4);
						goto LABEL_38;
					case PM_RATTACK:
						v12 = PM_DoRangeAttack(v4);
						goto LABEL_38;
					case PM_BLOCK:
						v12 = PM_DoBlock(v4);
						goto LABEL_38;
					case PM_GOTHIT:
						v12 = PM_DoGotHit(v4);
						goto LABEL_38;
					case PM_DEATH:
						v12 = PM_DoDeath(v4);
						goto LABEL_38;
					case PM_SPELL:
						v12 = PM_DoSpell(v4);
						goto LABEL_38;
					case PM_NEWLVL:
						v12 = PM_DoStand(v4);
LABEL_38:
						v11 = v12;
						break;
					default:
						break;
				}
				CheckNewPath(v4);
			}
			while ( v11 );
			v13 = (char *)(v5 - 69);
			++*(_DWORD *)v13;
			if ( *(v5 - 69) > *(v5 - 70) )
			{
				*(_DWORD *)v13 = 0;
				v14 = (char *)(v5 - 67);
				++*(_DWORD *)v14;
				if ( *(v5 - 67) > *(v5 - 68) )
					*(_DWORD *)v14 = 1;
			}
		}
		v5 += 5430;
		++v4;
	}
	while ( (signed int)v5 < (signed int)&plr[4]._pHitPoints );
}
// 52A554: using guessed type int sfxdelay;

void __fastcall CheckCheatStats(int pnum)
{
	int v1; // ecx
	int *v2; // ecx

	v1 = pnum;
	if ( plr[v1]._pStrength > 750 )
		plr[v1]._pStrength = 750;
	if ( plr[v1]._pDexterity > 750 )
		plr[v1]._pDexterity = 750;
	if ( plr[v1]._pMagic > 750 )
		plr[v1]._pMagic = 750;
	if ( plr[v1]._pVitality > 750 )
		plr[v1]._pVitality = 750;
	if ( plr[v1]._pHitPoints > 128000 )
		plr[v1]._pHitPoints = 128000;
	v2 = &plr[v1]._pMana;
	if ( *v2 > 128000 )
		*v2 = 128000;
}

void __fastcall ClrPlrPath(int pnum)
{
	int v1; // esi

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("ClrPlrPath: illegal player %d", pnum);
	memset(plr[v1].walkpath, -1, 0x19u);
}

bool __fastcall PosOkPlayer(int pnum, int px, int py)
{
	char v8; // cl
	unsigned int v9; // ecx
	int v10; // esi
	char v11; // al
	char v12; // cl
	bool result; // eax

	result = 0;
	if ( px >= 0 && px < 112 && py >= 0 && py < 112 && !SolidLoc(px, py) )
	{
		if ( dPiece[px][py] )
		{
			v8 = dPlayer[px][py];
			if ( !v8 || (v8 <= 0 ? (v9 = -1 - v8) : (v9 = v8 - 1), v9 == pnum || v9 >= 4 || !plr[v9]._pHitPoints) )
			{
				v10 = dMonster[px][py];
				if ( !v10 || currlevel && v10 > 0 && (signed int)(monster[v10-1]._mhitpoints & 0xFFFFFFC0) <= 0 ) /* fix */
				{
					v11 = dObject[px][py];
					if ( !v11 || (v11 <= 0 ? (v12 = -1 - v11) : (v12 = v11 - 1), !object[v12]._oSolidFlag) )
						result = 1;
				}
			}
		}
	}
	return result;
}

void __fastcall MakePlrPath(int pnum, int xx, int yy, unsigned char endspace)
{
	int v4; // esi
	int v5; // ebx
	int v6; // esi
	int v7; // edi
	int v8; // eax
	int v9; // eax
	int v10; // ecx
	int a2; // [esp+Ch] [ebp-4h]

	v4 = pnum;
	v5 = xx;
	a2 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("MakePlrPath: illegal player %d", pnum);
	v6 = v4;
	v7 = yy;
	v8 = plr[v6]._px;
	plr[v6]._ptargx = v5;
	plr[v6]._ptargy = yy;
	if ( v8 != v5 || plr[v6]._py != yy )
	{
		v9 = FindPath(PosOkPlayer, a2, v8, plr[v6]._py, v5, yy, plr[v6].walkpath);
		if ( v9 )
		{
			if ( !endspace )
			{
				v10 = *((char *)&plr[v6]._pmode + v9-- + 3);
				switch ( v10 )
				{
					case PM_WALK:
						goto LABEL_12;
					case PM_WALK2:
						++v5;
						break;
					case PM_WALK3:
						--v5;
						break;
					case PM_ATTACK:
						goto LABEL_15;
					case PM_RATTACK:
						++v5;
						goto LABEL_12;
					case PM_BLOCK:
						--v5;
LABEL_12:
						v7 = yy + 1;
						break;
					case PM_GOTHIT:
						--v5;
						goto LABEL_15;
					case PM_DEATH:
						++v5;
LABEL_15:
						v7 = yy - 1;
						break;
					default:
						break;
				}
				plr[v6]._ptargx = v5;
				plr[v6]._ptargy = v7;
			}
			plr[v6].walkpath[v9] = -1;
		}
	}
}

void __fastcall CheckPlrSpell()
{
	int v0; // ecx
	int v1; // eax
	int v2; // edx
	char v3; // al
	int v4; // ecx
	char v5; // al
	int v6; // eax
	int v7; // edx
	int v8; // esi
	int v9; // ST10_4
	int v10; // eax
	int v11; // eax
	int v12; // eax
	int v13; // ST10_4
	int v14; // eax
	char v15; // al

	v0 = myplr;
	if ( (unsigned int)myplr >= 4 )
	{
		TermMsg("CheckPlrSpell: illegal player %d", myplr);
		v0 = myplr;
	}
	v1 = 21720 * v0;
	v2 = plr[v0]._pRSpell;
	if ( v2 != -1 )
	{
		if ( leveltype == DTYPE_TOWN && !*(_DWORD *)&spelldata[v2].sTownSpell )
		{
			v5 = *((_BYTE *)&plr[0]._pClass + v1);
			switch ( v5 )
			{
				case UI_WARRIOR:
					v4 = PS_WARR27;
					goto LABEL_53;
				case UI_ROGUE:
					v4 = PS_ROGUE27;
					goto LABEL_53;
				case UI_SORCERER:
					v4 = PS_MAGE27;
					goto LABEL_53;
			}
			return;
		}
		if ( pcurs != CURSOR_HAND
		  || MouseY >= 352
		  || (chrflag && MouseX < 320 || invflag && MouseX > 320)
		  && v2 != 2
		  && v2 != 5
		  && v2 != 26
		  && v2 != 9
		  && v2 != 27 )
		{
			return;
		}
		_LOBYTE(v1) = *((_BYTE *)&plr[0]._pRSplType + v1);
		if ( (v1 & 0x80u) != 0 )
			goto LABEL_46;
		if ( (char)v1 <= 1 )
		{
			v6 = CheckSpell(v0, v2, v1, 0);
		}
		else
		{
			if ( (_BYTE)v1 != 2 )
			{
				if ( (_BYTE)v1 == 3 )
				{
					v6 = UseStaff();
					goto LABEL_36;
				}
LABEL_46:
				if ( _LOBYTE(plr[v0]._pRSplType) == 1 )
				{
					v15 = plr[v0]._pClass;
					switch ( v15 )
					{
						case UI_WARRIOR:
							v4 = PS_WARR35;
							goto LABEL_53;
						case UI_ROGUE:
							v4 = PS_ROGUE35;
							goto LABEL_53;
						case UI_SORCERER:
							v4 = PS_MAGE35;
							goto LABEL_53;
					}
				}
				return;
			}
			v6 = UseScroll();
		}
LABEL_36:
		v0 = myplr;
		if ( v6 )
		{
			v7 = plr[myplr]._pRSpell;
			if ( v7 == 6 )
			{
				v8 = GetDirection(plr[myplr].WorldX, plr[myplr].WorldY, cursmx, cursmy);
				v9 = GetSpellLevel(myplr, plr[myplr]._pRSpell);
				v10 = 21720 * myplr;
				_LOWORD(v10) = plr[myplr]._pRSpell;
				NetSendCmdLocParam3(1u, CMD_SPELLXYD, cursmx, cursmy, v10, v8, v9);
			}
			else if ( pcursmonst == -1 )
			{
				if ( pcursplr == -1 )
				{
					v13 = GetSpellLevel(myplr, v7);
					v14 = 21720 * myplr;
					_LOWORD(v14) = plr[myplr]._pRSpell;
					NetSendCmdLocParam2(1u, CMD_SPELLXY, cursmx, cursmy, v14, v13);
				}
				else
				{
					v12 = GetSpellLevel(myplr, v7);
					NetSendCmdParam3(1u, CMD_SPELLPID, pcursplr, plr[myplr]._pRSpell, v12);
				}
			}
			else
			{
				v11 = GetSpellLevel(myplr, v7);
				NetSendCmdParam3(1u, CMD_SPELLID, pcursmonst, plr[myplr]._pRSpell, v11);
			}
			return;
		}
		goto LABEL_46;
	}
	v3 = *((_BYTE *)&plr[0]._pClass + v1);
	switch ( v3 )
	{
		case UI_WARRIOR:
			v4 = PS_WARR34;
LABEL_53:
			PlaySFX(v4);
			return;
		case UI_ROGUE:
			v4 = PS_ROGUE34;
			goto LABEL_53;
		case UI_SORCERER:
			v4 = PS_MAGE34;
			goto LABEL_53;
	}
}
// 4B8CC2: using guessed type char pcursplr;
// 5BB1ED: using guessed type char leveltype;

void __fastcall SyncPlrAnim(int pnum)
{
	int v1; // esi
	int v2; // eax
	int v3; // ecx
	int v4; // ecx
	int v5; // edx

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SyncPlrAnim: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pdir;
	switch ( plr[v1]._pmode )
	{
		case PM_STAND:
		case PM_NEWLVL:
		case PM_QUIT:
			v4 = plr[0]._pNAnim[v3 + 5430 * v1];
			goto LABEL_19;
		case PM_WALK:
		case PM_WALK2:
		case PM_WALK3:
			v4 = plr[0]._pWAnim[v3 + 5430 * v1];
			goto LABEL_19;
		case PM_ATTACK:
		case PM_RATTACK:
			v4 = plr[0]._pAAnim[v3 + 5430 * v1];
			goto LABEL_19;
		case PM_BLOCK:
			v4 = plr[0]._pBAnim[v3 + 5430 * v1];
			goto LABEL_19;
		case PM_GOTHIT:
			v4 = plr[0]._pHAnim[v3 + 5430 * v1];
			goto LABEL_19;
		case PM_DEATH:
			v4 = plr[0]._pDAnim[v3 + 5430 * v1];
			goto LABEL_19;
		case PM_SPELL:
			if ( v1 == myplr )
				v5 = (unsigned char)spelldata[plr[v2]._pSpell].sType;
			else
				v5 = 0;
			if ( !v5 )
				plr[v2]._pAnimData = plr[0]._pFAnim[v3 + 5430 * v1];
			if ( v5 == STYPE_LIGHTNING )
				plr[v2]._pAnimData = plr[0]._pLAnim[v3 + 5430 * v1];
			if ( v5 == STYPE_MAGIC )
			{
				v4 = plr[0]._pTAnim[v3 + 5430 * v1];
LABEL_19:
				plr[v2]._pAnimData = v4;
			}
			break;
		default:
			TermMsg("SyncPlrAnim");
			break;
	}
}

void __fastcall SyncInitPlrPos(int pnum)
{
	int v1; // esi
	bool v2; // zf
	unsigned int v3; // eax
	int v4; // ebx
	int v5; // edi
	int v6; // eax
	signed int v7; // [esp+Ch] [ebp-18h]
	int p; // [esp+10h] [ebp-14h]
	int v9; // [esp+14h] [ebp-10h]
	signed int v10; // [esp+18h] [ebp-Ch]
	signed int v11; // [esp+1Ch] [ebp-8h]
	unsigned int i; // [esp+20h] [ebp-4h]
	signed int v13; // [esp+20h] [ebp-4h]

	p = pnum;
	v1 = pnum;
	v2 = gbMaxPlayers == 1;
	plr[v1]._ptargx = plr[pnum].WorldX;
	plr[v1]._ptargy = plr[pnum].WorldY;
	if ( !v2 && plr[v1].plrlevel == currlevel )
	{
		v3 = 0;
		for ( i = 0; ; v3 = i )
		{
			v4 = plr[v1].WorldX + *(int *)((char *)plrxoff2 + v3);
			v5 = plr[v1].WorldY + *(int *)((char *)plryoff2 + v3);
			if ( PosOkPlayer(p, v4, v5) )
				break;
			i += 4;
			if ( i >= 0x20 )
				break;
		}
		if ( !PosOkPlayer(p, v4, v5) )
		{
			v11 = 0;
			v6 = -1;
			v13 = 1;
			v7 = -1;
			do
			{
				if ( v11 )
					break;
				v9 = v6;
				while ( v6 <= v13 && !v11 )
				{
					v5 = v9 + plr[v1].WorldY;
					v10 = v7;
					do
					{
						if ( v11 )
							break;
						v4 = v10 + plr[v1].WorldX;
						if ( PosOkPlayer(p, v10 + plr[v1].WorldX, v5) && !PosOkPortal(currlevel, v4, v5) )
							v11 = 1;
						++v10;
					}
					while ( v10 <= v13 );
					v6 = ++v9;
				}
				++v13;
				v6 = v7-- - 1;
			}
			while ( v7 > -50 );
		}
		plr[v1].WorldX = v4;
		v2 = p == myplr;
		plr[v1].WorldY = v5;
		dPlayer[v4][v5] = p + 1;
		if ( v2 )
		{
			plr[v1]._px = v4;
			plr[v1]._py = v5;
			plr[v1]._ptargx = v4;
			plr[v1]._ptargy = v5;
			ViewX = v4;
			ViewY = v5;
		}
	}
}
// 679660: using guessed type char gbMaxPlayers;

void __fastcall SyncInitPlr(int pnum)
{
	int v1; // esi

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SyncInitPlr: illegal player %d", pnum);
	SetPlrAnims(v1);
	SyncInitPlrPos(v1);
}

void __fastcall CheckStats(int pnum)
{
	int v1; // esi
	int v2; // eax
	char v3; // cl
	signed int v4; // esi
	signed int v5; // edi
	int v6; // edx
	int v7; // ecx
	int v8; // edx
	int v9; // ecx
	int v10; // edx
	int v11; // ecx
	int v12; // edx
	int v13; // ecx
	//signed int v14; // [esp+Ch] [ebp-4h]

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("CheckStats: illegal player %d", pnum);
	v2 = v1;
	v3 = plr[v1]._pClass;
	if ( v3 )
	{
		if ( v3 == 1 )
		{
			v4 = 1;
		}
		else if ( v3 == 2 )
		{
			v4 = 2;
		}
		/*else
		{
			v4 = v14;
		}*/
	}
	else
	{
		v4 = 0;
	}
	v5 = 0;
	do
	{
		if ( v5 )
		{
			switch ( v5 )
			{
				case ATTRIB_MAG:
					v10 = plr[v2]._pBaseMag;
					v11 = MaxStats[v4][1];
					if ( v10 <= v11 )
					{
						if ( v10 < 0 )
							plr[v2]._pBaseMag = 0;
					}
					else
					{
						plr[v2]._pBaseMag = v11;
					}
					break;
				case ATTRIB_DEX:
					v8 = plr[v2]._pBaseDex;
					v9 = MaxStats[v4][2];
					if ( v8 <= v9 )
					{
						if ( v8 < 0 )
							plr[v2]._pBaseDex = 0;
					}
					else
					{
						plr[v2]._pBaseDex = v9;
					}
					break;
				case ATTRIB_VIT:
					v6 = plr[v2]._pBaseVit;
					v7 = MaxStats[v4][3];
					if ( v6 <= v7 )
					{
						if ( v6 < 0 )
							plr[v2]._pBaseVit = 0;
					}
					else
					{
						plr[v2]._pBaseVit = v7;
					}
					break;
			}
		}
		else
		{
			v12 = plr[v2]._pBaseStr;
			v13 = MaxStats[v4][0];
			if ( v12 <= v13 )
			{
				if ( v12 < 0 )
					plr[v2]._pBaseStr = 0;
			}
			else
			{
				plr[v2]._pBaseStr = v13;
			}
		}
		++v5;
	}
	while ( v5 < 4 );
}

void __fastcall ModifyPlrStr(int pnum, int l)
{
	int v2; // esi
	int v3; // edi
	int v4; // esi
	char v5; // dl
	int v6; // ecx
	int v7; // eax
	int v8; // ebx
	int v9; // eax
	signed int v10; // ecx
	int p; // [esp+8h] [ebp-4h]

	v2 = pnum;
	v3 = l;
	p = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("ModifyPlrStr: illegal player %d", pnum);
	v4 = v2;
	v5 = plr[v4]._pClass;
	v6 = plr[v4]._pBaseStr;
	v7 = MaxStats[v5][0];
	if ( v6 + v3 > v7 )
		v3 = v7 - v6;
	plr[v4]._pBaseStr = v3 + v6;
	plr[v4]._pStrength += v3;
	v8 = plr[v4]._pStrength;
	if ( v5 == 1 )
	{
		v9 = plr[v4]._pLevel * (v8 + plr[v4]._pDexterity);
		v10 = 200;
	}
	else
	{
		v9 = v8 * plr[v4]._pLevel;
		v10 = 100;
	}
	plr[v4]._pDamageMod = v9 / v10;
	CalcPlrInv(p, 1u);
	if ( p == myplr )
		NetSendCmdParam1(0, CMD_SETSTR, plr[v4]._pBaseStr);
}

void __fastcall ModifyPlrMag(int pnum, int l)
{
	int v2; // esi
	int v3; // edi
	int v4; // esi
	char v5; // dl
	int v6; // ecx
	int v7; // eax
	int v8; // eax
	int v9; // edi
	int p; // [esp+8h] [ebp-4h]

	v2 = pnum;
	v3 = l;
	p = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("ModifyPlrMag: illegal player %d", pnum);
	v4 = v2;
	v5 = plr[v4]._pClass;
	v6 = MaxStats[v5][1];
	v7 = plr[v4]._pBaseMag;
	if ( v7 + v3 > v6 )
		v3 = v6 - v7;
	plr[v4]._pMagic += v3;
	v8 = v3 + v7;
	v9 = v3 << 6;
	plr[v4]._pBaseMag = v8;
	if ( v5 == 2 )
		v9 *= 2;
	plr[v4]._pMaxManaBase += v9;
	plr[v4]._pMaxMana += v9;
	if ( !(plr[v4]._pIFlags & 0x8000000) )
	{
		plr[v4]._pManaBase += v9;
		plr[v4]._pMana += v9;
	}
	CalcPlrInv(p, 1u);
	if ( p == myplr )
		NetSendCmdParam1(0, CMD_SETMAG, plr[v4]._pBaseMag);
}

void __fastcall ModifyPlrDex(int pnum, int l)
{
	int v2; // ebx
	int v3; // edi
	int v4; // esi
	int v5; // ecx
	int v6; // eax

	v2 = pnum;
	v3 = l;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("ModifyPlrDex: illegal player %d", pnum);
	v4 = v2;
	v5 = MaxStats[SLOBYTE(plr[v2]._pClass)][2];
	v6 = plr[v2]._pBaseDex;
	if ( v6 + v3 > v5 )
		v3 = v5 - v6;
	plr[v4]._pDexterity += v3;
	plr[v4]._pBaseDex = v3 + v6;
	CalcPlrInv(v2, 1u);
	if ( _LOBYTE(plr[v4]._pClass) == 1 )
		plr[v4]._pDamageMod = plr[v4]._pLevel * (plr[v4]._pDexterity + plr[v4]._pStrength) / 200;
	if ( v2 == myplr )
		NetSendCmdParam1(0, CMD_SETDEX, plr[v4]._pBaseDex);
}

void __fastcall ModifyPlrVit(int pnum, int l)
{
	int v2; // esi
	int v3; // edi
	int v4; // esi
	char v5; // dl
	int v6; // ecx
	int v7; // eax
	int v8; // eax
	int v9; // edi
	int p; // [esp+8h] [ebp-4h]

	v2 = pnum;
	v3 = l;
	p = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("ModifyPlrVit: illegal player %d", pnum);
	v4 = v2;
	v5 = plr[v4]._pClass;
	v6 = MaxStats[v5][3];
	v7 = plr[v4]._pBaseVit;
	if ( v7 + v3 > v6 )
		v3 = v6 - v7;
	plr[v4]._pVitality += v3;
	v8 = v3 + v7;
	v9 = v3 << 6;
	plr[v4]._pBaseVit = v8;
	if ( !v5 )
		v9 *= 2;
	plr[v4]._pHPBase += v9;
	plr[v4]._pMaxHPBase += v9;
	plr[v4]._pHitPoints += v9;
	plr[v4]._pMaxHP += v9;
	CalcPlrInv(p, 1u);
	if ( p == myplr )
		NetSendCmdParam1(0, CMD_SETVIT, plr[v4]._pBaseVit);
}

void __fastcall SetPlayerHitPoints(int pnum, int newhp)
{
	int v2; // esi
	int v3; // edi
	int v4; // eax
	int v5; // ecx
	bool v6; // zf

	v2 = pnum;
	v3 = newhp;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlayerHitPoints: illegal player %d", pnum);
	v4 = v2;
	v5 = plr[v2]._pMaxHPBase;
	plr[v4]._pHitPoints = v3;
	v6 = v2 == myplr;
	plr[v4]._pHPBase = v3 + v5 - plr[v2]._pMaxHP;
	if ( v6 )
		drawhpflag = 1;
}

void __fastcall SetPlrStr(int pnum, int v)
{
	int v2; // edi
	int v3; // ebx
	int v4; // esi
	int v5; // eax
	signed int v6; // ecx

	v2 = pnum;
	v3 = v;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlrStr: illegal player %d", pnum);
	v4 = v2;
	plr[v2]._pBaseStr = v3;
	CalcPlrInv(v2, 1u);
	if ( _LOBYTE(plr[v2]._pClass) == 1 )
	{
		v5 = plr[v4]._pLevel * (plr[v4]._pStrength + plr[v4]._pDexterity);
		v6 = 200;
	}
	else
	{
		v5 = plr[v4]._pStrength * plr[v4]._pLevel;
		v6 = 100;
	}
	plr[v4]._pDamageMod = v5 / v6;
}

void __fastcall SetPlrMag(int pnum, int v)
{
	int v2; // edi
	int v3; // esi
	int v4; // eax
	int v5; // esi

	v2 = pnum;
	v3 = v;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlrMag: illegal player %d", pnum);
	v4 = v2;
	plr[v2]._pBaseMag = v3;
	v5 = v3 << 6;
	if ( _LOBYTE(plr[v2]._pClass) == 2 )
		v5 *= 2;
	plr[v4]._pMaxManaBase = v5;
	plr[v4]._pMaxMana = v5;
	CalcPlrInv(v2, 1u);
}

void __fastcall SetPlrDex(int pnum, int v)
{
	int v2; // edi
	int v3; // ebx
	int v4; // esi
	int v5; // eax
	signed int v6; // ecx

	v2 = pnum;
	v3 = v;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlrDex: illegal player %d", pnum);
	v4 = v2;
	plr[v2]._pBaseDex = v3;
	CalcPlrInv(v2, 1u);
	if ( _LOBYTE(plr[v2]._pClass) == 1 )
	{
		v5 = plr[v4]._pLevel * (plr[v4]._pStrength + plr[v4]._pDexterity);
		v6 = 200;
	}
	else
	{
		v5 = plr[v4]._pStrength * plr[v4]._pLevel;
		v6 = 100;
	}
	plr[v4]._pDamageMod = v5 / v6;
}

void __fastcall SetPlrVit(int pnum, int v)
{
	int v2; // edi
	int v3; // esi
	int v4; // eax
	int v5; // esi

	v2 = pnum;
	v3 = v;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("SetPlrVit: illegal player %d", pnum);
	v4 = v2;
	plr[v2]._pBaseVit = v3;
	v5 = v3 << 6;
	if ( !_LOBYTE(plr[v2]._pClass) )
		v5 *= 2;
	plr[v4]._pHPBase = v5;
	plr[v4]._pMaxHPBase = v5;
	CalcPlrInv(v2, 1u);
}

void __fastcall InitDungMsgs(int pnum)
{
	int v1; // esi

	v1 = pnum;
	if ( (unsigned int)pnum >= 4 )
		TermMsg("InitDungMsgs: illegal player %d", pnum);
	plr[v1].pDungMsgs = 0;
}

void __cdecl PlayDungMsgs()
{
	int v0; // eax
	int v1; // eax
	char v2; // cl
	char v3; // dl
	char v4; // cl
	char v5; // cl
	char v6; // dl
	char v7; // cl
	char v8; // dl
	char v9; // cl
	char v10; // dl
	char v11; // cl
	char v12; // dl

	v0 = myplr;
	if ( (unsigned int)myplr >= 4 )
	{
		TermMsg("PlayDungMsgs: illegal player %d", myplr);
		v0 = myplr;
	}
	switch ( currlevel )
	{
		case 1u:
			v1 = v0;
			if ( !plr[v1]._pLvlVisited[1] && gbMaxPlayers == currlevel )
			{
				v2 = plr[v1].pDungMsgs;
				if ( !(v2 & 1) )
				{
					v3 = plr[v1]._pClass;
					sfxdelay = 40;
					if ( v3 )
					{
						if ( v3 == 1 )
						{
							sfxdnum = PS_ROGUE97;
						}
						else if ( v3 == 2 )
						{
							sfxdnum = PS_MAGE97;
						}
					}
					else
					{
						sfxdnum = PS_WARR97;
					}
					v4 = v2 | 1;
LABEL_14:
					plr[v1].pDungMsgs = v4;
					return;
				}
			}
			break;
		case 5u:
			v1 = v0;
			if ( !plr[v1]._pLvlVisited[5] && gbMaxPlayers == 1 )
			{
				v5 = plr[v1].pDungMsgs;
				if ( !(v5 & 2) )
				{
					v6 = plr[v1]._pClass;
					sfxdelay = 40;
					if ( v6 )
					{
						if ( v6 == 1 )
						{
							sfxdnum = PS_ROGUE96;
						}
						else if ( v6 == 2 )
						{
							sfxdnum = PS_MAGE96;
						}
					}
					else
					{
						sfxdnum = PS_WARR96B;
					}
					v4 = v5 | 2;
					goto LABEL_14;
				}
			}
			break;
		case 9u:
			v1 = v0;
			if ( !plr[v1]._pLvlVisited[9] && gbMaxPlayers == 1 )
			{
				v7 = plr[v1].pDungMsgs;
				if ( !(v7 & 4) )
				{
					v8 = plr[v1]._pClass;
					sfxdelay = 40;
					if ( v8 )
					{
						if ( v8 == 1 )
						{
							sfxdnum = PS_ROGUE98;
						}
						else if ( v8 == 2 )
						{
							sfxdnum = PS_MAGE98;
						}
					}
					else
					{
						sfxdnum = PS_WARR98;
					}
					v4 = v7 | 4;
					goto LABEL_14;
				}
			}
			break;
		case 13u:
			v1 = v0;
			if ( !plr[v1]._pLvlVisited[13] && gbMaxPlayers == 1 )
			{
				v9 = plr[v1].pDungMsgs;
				if ( !(v9 & 8) )
				{
					v10 = plr[v1]._pClass;
					sfxdelay = 40;
					if ( v10 )
					{
						if ( v10 == 1 )
						{
							sfxdnum = PS_ROGUE99;
						}
						else if ( v10 == 2 )
						{
							sfxdnum = PS_MAGE99;
						}
					}
					else
					{
						sfxdnum = PS_WARR99;
					}
					v4 = v9 | 8;
					goto LABEL_14;
				}
			}
			break;
		case 16u:
			v1 = v0;
			if ( !plr[v1]._pLvlVisited[15] && gbMaxPlayers == 1 )
			{
				v11 = plr[v1].pDungMsgs;
				if ( !(v11 & 0x10) )
				{
					v12 = plr[v1]._pClass;
					sfxdelay = 40;
					if ( !v12 || v12 == 1 || v12 == 2 )
						sfxdnum = PS_DIABLVLINT;
					v4 = v11 | 0x10;
					goto LABEL_14;
				}
			}
			break;
	}
	sfxdelay = 0;
}
// 52A554: using guessed type int sfxdelay;
// 679660: using guessed type char gbMaxPlayers;
