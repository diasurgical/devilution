//HEADER_GOES_HERE

#include "../types.h"

int plr_lframe_size;
int plr_wframe_size;
UCHAR plr_gfx_flag = 0;
int plr_aframe_size;
int myplr;
PlayerStruct plr[MAX_PLRS];
int plr_fframe_size;
int plr_qframe_size;
BOOL deathflag;
int plr_hframe_size;
int plr_bframe_size;
UCHAR plr_gfx_bflag = 0;
int plr_sframe_size;
int deathdelay;
int plr_dframe_size;

const char ArmourChar[4] = { 'L', 'M', 'H', 0 };
const char WepChar[10] = { 'N', 'U', 'S', 'D', 'B', 'A', 'M', 'H', 'T', 0 };
const char CharChar[4] = { 'W', 'R', 'S', 0 };

/* data */

int plrxoff[9] = { 0, 2, 0, 2, 1, 0, 1, 2, 1 };
int plryoff[9] = { 0, 2, 2, 0, 1, 1, 0, 1, 2 };
int plrxoff2[9] = { 0, 1, 0, 1, 2, 0, 1, 2, 2 };
int plryoff2[9] = { 0, 0, 1, 1, 0, 2, 2, 1, 2 };
char PlrGFXAnimLens[3][11] = {
	{ 10, 16, 8, 2, 20, 20, 6, 20, 8, 9, 14 },
	{ 8, 18, 8, 4, 20, 16, 7, 20, 8, 10, 12 },
	{ 8, 16, 8, 6, 20, 12, 8, 20, 8, 12, 8 }
};
int PWVel[4][3] = {
	{ 2048, 1024, 512 },
	{ 2048, 1024, 512 },
	{ 2048, 1024, 512 },
	{ 8, 8, 8 }
};
int StrengthTbl[3] = { 30, 20, 15 };
int MagicTbl[3] = { 10, 15, 35 };
int DexterityTbl[3] = { 20, 30, 15 };
int VitalityTbl[3] = { 25, 20, 20 };
int ToBlkTbl[3] = { 30, 20, 10 };
char *ClassStrTblOld[3] = { "Warrior", "Rogue", "Sorceror" }; // unused
int MaxStats[3][4] = {
	{ 250, 50, 60, 100 },
	{ 55, 70, 250, 80 },
	{ 45, 250, 85, 80 }
};
int ExpLvlsTbl[MAXCHARLEVEL] = {
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

void __fastcall SetPlayerGPtrs(UCHAR *pData, UCHAR **pAnim)
{
	int i;

	for (i = 0; i < 8; i++) {
		pAnim[i] = pData + ((DWORD *)pData)[i];
	}
}

void __fastcall LoadPlrGFX(int pnum, player_graphic gfxflag)
{
	char prefix[16];
	char pszName[256];
	char *szCel;
	PlayerStruct *p;
	char *cs;
	UCHAR *pData, *pAnim;
	DWORD i;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("LoadPlrGFX: illegal player %d", pnum);
	}

	p = &plr[pnum];
	sprintf(prefix, "%c%c%c", CharChar[p->_pClass], ArmourChar[p->_pgfxnum >> 4], WepChar[p->_pgfxnum & 0xF]);
	cs = ClassStrTbl[p->_pClass];

	for (i = 1; i <= PFILE_NONDEATH; i <<= 1) {
		if (!(i & gfxflag)) {
			continue;
		}

		switch (i) {
		case PFILE_STAND:
			szCel = "AS";
			if (leveltype == DTYPE_TOWN) {
				szCel = "ST";
			}
			pData = p->_pNData;
			pAnim = (UCHAR *)p->_pNAnim;
			break;
		case PFILE_WALK:
			szCel = "AW";
			if (leveltype == DTYPE_TOWN) {
				szCel = "WL";
			}
			pData = p->_pWData;
			pAnim = (UCHAR *)p->_pWAnim;
			break;
		case PFILE_ATTACK:
			if (leveltype == DTYPE_TOWN) {
				continue;
			}
			szCel = "AT";
			pData = p->_pAData;
			pAnim = (UCHAR *)p->_pAAnim;
			break;
		case PFILE_HIT:
			if (leveltype == DTYPE_TOWN) {
				continue;
			}
			szCel = "HT";
			pData = p->_pHData;
			pAnim = (UCHAR *)p->_pHAnim;
			break;
		case PFILE_LIGHTNING:
			if (leveltype == DTYPE_TOWN) {
				continue;
			}
			szCel = "LM";
			pData = p->_pLData;
			pAnim = (UCHAR *)p->_pLAnim;
			break;
		case PFILE_FIRE:
			if (leveltype == DTYPE_TOWN) {
				continue;
			}
			szCel = "FM";
			pData = p->_pFData;
			pAnim = (UCHAR *)p->_pFAnim;
			break;
		case PFILE_MAGIC:
			if (leveltype == DTYPE_TOWN) {
				continue;
			}
			szCel = "QM";
			pData = p->_pTData;
			pAnim = (UCHAR *)p->_pTAnim;
			break;
		case PFILE_DEATH:
			if (p->_pgfxnum & 0xF) {
				continue;
			}
			szCel = "DT";
			pData = p->_pDData;
			pAnim = (UCHAR *)p->_pDAnim;
			break;
		case PFILE_BLOCK:
			if (leveltype == DTYPE_TOWN) {
				continue;
			}
			if (!p->_pBlockFlag) {
				continue;
			}

			szCel = "BL";
			pData = p->_pBData;
			pAnim = (UCHAR *)p->_pBAnim;
			break;
		default:
			TermMsg("PLR:2");
			break;
		}

		sprintf(pszName, "PlrGFX\\%s\\%s\\%s%s.CL2", cs, prefix, prefix, szCel);
		LoadFileWithMem(pszName, pData);
		SetPlayerGPtrs((UCHAR *)pData, (UCHAR **)pAnim);
		p->_pGFXLoad |= i;
	}
}

void __fastcall InitPlayerGFX(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("InitPlayerGFX: illegal player %d", pnum);
	}

	if (plr[pnum]._pHitPoints >> 6 == 0) {
		plr[pnum]._pgfxnum = 0;
		LoadPlrGFX(pnum, PFILE_DEATH);
	} else {
		LoadPlrGFX(pnum, PFILE_NONDEATH);
	}
}

void __fastcall InitPlrGFXMem(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("InitPlrGFXMem: illegal player %d", pnum);
	}

	if (!(plr_gfx_flag & 0x1)) { //STAND
		plr_gfx_flag |= 0x1;
		if (GetPlrGFXSize("ST") > GetPlrGFXSize("AS")) {
			plr_sframe_size = GetPlrGFXSize("ST"); //TOWN
		} else {
			plr_sframe_size = GetPlrGFXSize("AS"); //DUNGION
		}
	}
	plr[pnum]._pNData = DiabloAllocPtr(plr_sframe_size);

	if (!(plr_gfx_flag & 0x2)) { //WALK
		plr_gfx_flag |= 0x2;
		if (GetPlrGFXSize("WL") > GetPlrGFXSize("AW")) {
			plr_wframe_size = GetPlrGFXSize("WL"); //TOWN
		} else {
			plr_wframe_size = GetPlrGFXSize("AW"); //DUNGION
		}
	}
	plr[pnum]._pWData = DiabloAllocPtr(plr_wframe_size);

	if (!(plr_gfx_flag & 0x4)) { //ATTACK
		plr_gfx_flag |= 0x4;
		plr_aframe_size = GetPlrGFXSize("AT");
	}
	plr[pnum]._pAData = DiabloAllocPtr(plr_aframe_size);

	if (!(plr_gfx_flag & 0x8)) { //HIT
		plr_gfx_flag |= 0x8;
		plr_hframe_size = GetPlrGFXSize("HT");
	}
	plr[pnum]._pHData = DiabloAllocPtr(plr_hframe_size);

	if (!(plr_gfx_flag & 0x10)) { //LIGHTNING
		plr_gfx_flag |= 0x10;
		plr_lframe_size = GetPlrGFXSize("LM");
	}
	plr[pnum]._pLData = DiabloAllocPtr(plr_lframe_size);

	if (!(plr_gfx_flag & 0x20)) { //FIRE
		plr_gfx_flag |= 0x20;
		plr_fframe_size = GetPlrGFXSize("FM");
	}
	plr[pnum]._pFData = DiabloAllocPtr(plr_fframe_size);

	if (!(plr_gfx_flag & 0x40)) { //MAGIC
		plr_gfx_flag |= 0x40;
		plr_qframe_size = GetPlrGFXSize("QM");
	}
	plr[pnum]._pTData = DiabloAllocPtr(plr_qframe_size);

	if (!(plr_gfx_flag & 0x80)) { //DEATH
		plr_gfx_flag |= 0x80;
		plr_dframe_size = GetPlrGFXSize("DT");
	}
	plr[pnum]._pDData = DiabloAllocPtr(plr_dframe_size);

	if (!(plr_gfx_bflag & 0x1)) { //BLOCK
		plr_gfx_bflag |= 0x1;
		plr_bframe_size = GetPlrGFXSize("BL");
	}
	plr[pnum]._pBData = DiabloAllocPtr(plr_bframe_size);

	plr[pnum]._pGFXLoad = 0;
}

DWORD __fastcall GetPlrGFXSize(char *szCel)
{
	char prefix[16];
	char pszName[256];
	HANDLE file;
	int c, a, w;
	DWORD size, result;

	size = 0;
	result = 0;
	a = 0;
	w = 0;

	for (c = 0; c < sizeof(ClassStrTbl) / sizeof(ClassStrTbl[0]); c++) {
		for (a = 0; ArmourChar[a]; a++) {
			for (w = 0; WepChar[w]; w++) { // BUGFIX loads non-existing animagions; DT is only for N, BT is only for U, D & H
				sprintf(prefix, "%c%c%c", CharChar[c], ArmourChar[a], WepChar[w]);
				sprintf(pszName, "PlrGFX\\%s\\%s\\%s%s.CL2", ClassStrTbl[c], prefix, prefix, szCel);
				if (WOpenFile(pszName, &file, TRUE)) {
					size = WGetFileSize(file, 0);
					WCloseFile(file);
					if (result <= size) {
						result = size;
					}
				}
			}
		}
	}

	return result;
}

void __fastcall FreePlayerGFX(int pnum)
{
	void *ptr;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("FreePlayerGFX: illegal player %d", pnum);
	}

	ptr = plr[pnum]._pNData;
	plr[pnum]._pNData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pWData;
	plr[pnum]._pWData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pAData;
	plr[pnum]._pAData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pHData;
	plr[pnum]._pHData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pLData;
	plr[pnum]._pLData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pFData;
	plr[pnum]._pFData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pTData;
	plr[pnum]._pTData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pDData;
	plr[pnum]._pDData = NULL;
	mem_free_dbg(ptr);
	ptr = plr[pnum]._pBData;
	plr[pnum]._pBData = NULL;
	mem_free_dbg(ptr);
	plr[pnum]._pGFXLoad = 0;
}

void __fastcall NewPlrAnim(int pnum, unsigned char *Peq, int numFrames, int Delay, int width)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("NewPlrAnim: illegal player %d", pnum);
	}

	plr[pnum]._pAnimData = Peq;
	plr[pnum]._pAnimLen = numFrames;
	plr[pnum]._pAnimFrame = 1;
	plr[pnum]._pAnimCnt = 0;
	plr[pnum]._pAnimDelay = Delay;
	plr[pnum]._pAnimWidth = width;
	plr[pnum]._pAnimWidth2 = (width - 64) >> 1;
}

void __fastcall ClearPlrPVars(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ClearPlrPVars: illegal player %d", pnum);
	}

	plr[pnum]._pVar1 = 0;
	plr[pnum]._pVar2 = 0;
	plr[pnum]._pVar3 = 0;
	plr[pnum]._pVar4 = 0;
	plr[pnum]._pVar5 = 0;
	plr[pnum]._pVar6 = 0;
	plr[pnum]._pVar7 = 0;
	plr[pnum]._pVar8 = 0;
}

void __fastcall SetPlrAnims(int pnum)
{
	int pc, gn;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlrAnims: illegal player %d", pnum);
	}

	pc = plr[pnum]._pClass;

	plr[pnum]._pNWidth = 96;
	plr[pnum]._pWWidth = 96;
	plr[pnum]._pAWidth = 128;
	plr[pnum]._pHWidth = 96;
	plr[pnum]._pSWidth = 96;
	plr[pnum]._pDWidth = 128;
	plr[pnum]._pBWidth = 96;

	if (leveltype == DTYPE_TOWN) {
		plr[pnum]._pNFrames = PlrGFXAnimLens[pc][7];
		plr[pnum]._pWFrames = PlrGFXAnimLens[pc][8];
		plr[pnum]._pDFrames = PlrGFXAnimLens[pc][4];
		plr[pnum]._pSFrames = PlrGFXAnimLens[pc][5];
	} else {
		plr[pnum]._pNFrames = PlrGFXAnimLens[pc][0];
		plr[pnum]._pWFrames = PlrGFXAnimLens[pc][2];
		plr[pnum]._pAFrames = PlrGFXAnimLens[pc][1];
		plr[pnum]._pHFrames = PlrGFXAnimLens[pc][6];
		plr[pnum]._pSFrames = PlrGFXAnimLens[pc][5];
		plr[pnum]._pDFrames = PlrGFXAnimLens[pc][4];
		plr[pnum]._pBFrames = PlrGFXAnimLens[pc][3];
		plr[pnum]._pAFNum = PlrGFXAnimLens[pc][9];
	}
	plr[pnum]._pSFNum = PlrGFXAnimLens[pc][10];

	gn = plr[pnum]._pgfxnum & 0xF;
	if (pc == PC_WARRIOR) {
		if (gn == ANIM_ID_BOW) {
			if (leveltype != DTYPE_TOWN) {
				plr[pnum]._pNFrames = 8;
			}
			plr[pnum]._pAWidth = 96;
			plr[pnum]._pAFNum = 11;
		} else if (gn == ANIM_ID_AXE) {
			plr[pnum]._pAFrames = 20;
			plr[pnum]._pAFNum = 10;
		} else if (gn == ANIM_ID_STAFF) {
			plr[pnum]._pAFrames = 16;
			plr[pnum]._pAFNum = 11;
		}
	} else if (pc == PC_ROGUE) {
		if (gn == ANIM_ID_AXE) {
			plr[pnum]._pAFrames = 22;
			plr[pnum]._pAFNum = 13;
		} else if (gn == ANIM_ID_BOW) {
			plr[pnum]._pAFrames = 12;
			plr[pnum]._pAFNum = 7;
		} else if (gn == ANIM_ID_STAFF) {
			plr[pnum]._pAFrames = 16;
			plr[pnum]._pAFNum = 11;
		}
	} else if (pc == PC_SORCERER) {
		plr[pnum]._pSWidth = 128;
		if (gn == ANIM_ID_UNARMED) {
			plr[pnum]._pAFrames = 20;
		} else if (gn == ANIM_ID_UNARMED_SHIELD) {
			plr[pnum]._pAFNum = 9;
		} else if (gn == ANIM_ID_BOW) {
			plr[pnum]._pAFrames = 20;
			plr[pnum]._pAFNum = 16;
		} else if (gn == ANIM_ID_AXE) {
			plr[pnum]._pAFrames = 24;
			plr[pnum]._pAFNum = 16;
		}
	}
}

void __fastcall ClearPlrRVars(PlayerStruct *p)
{
	// TODO: Missing debug assert p != NULL
	p->bReserved[0] = 0;
	p->bReserved[1] = 0;
	p->bReserved[2] = 0;
	p->wReserved[0] = 0;
	p->wReserved[1] = 0;
	p->wReserved[2] = 0;
	p->wReserved[3] = 0;
	p->wReserved[4] = 0;
	p->wReserved[5] = 0;
	p->wReserved[6] = 0;
	p->wReserved[7] = 0;
	p->dwReserved[0] = 0;
	p->dwReserved[1] = 0;
	p->dwReserved[2] = 0;
	p->dwReserved[3] = 0;
	p->dwReserved[4] = 0;
	p->dwReserved[5] = 0;
	p->dwReserved[6] = 0;
}

// c: plr_classes value
void __fastcall CreatePlayer(int pnum, char c)
{
	char val;
	int hp, mana;
	int i;

	ClearPlrRVars(&plr[pnum]);
	SetRndSeed(GetTickCount());

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("CreatePlayer: illegal player %d", pnum);
	}
	plr[pnum]._pClass = c;

	val = StrengthTbl[c];
	if (val < 0) {
		val = 0;
	}
	plr[pnum]._pStrength = val;
	plr[pnum]._pBaseStr = val;

	val = MagicTbl[c];
	if (val < 0) {
		val = 0;
	}
	plr[pnum]._pMagic = val;
	plr[pnum]._pBaseMag = val;

	val = DexterityTbl[c];
	if (val < 0) {
		val = 0;
	}
	plr[pnum]._pDexterity = val;
	plr[pnum]._pBaseDex = val;

	val = VitalityTbl[c];
	if (val < 0) {
		val = 0;
	}
	plr[pnum]._pVitality = val;
	plr[pnum]._pBaseVit = val;

	plr[pnum]._pStatPts = 0;
	plr[pnum].pTownWarps = 0;
	plr[pnum].pDungMsgs = 0;
	plr[pnum].pLvlLoad = 0;
	plr[pnum].pDiabloKillLevel = 0;

	if (c == PC_ROGUE) {
		plr[pnum]._pDamageMod = plr[pnum]._pLevel * (plr[pnum]._pStrength + plr[pnum]._pDexterity) / 200;
	} else {
		plr[pnum]._pDamageMod = plr[pnum]._pStrength * plr[pnum]._pLevel / 100;
	}

	plr[pnum]._pBaseToBlk = ToBlkTbl[c];

	plr[pnum]._pHitPoints = (val + 10) << 6;
	if (c == PC_WARRIOR) {
		plr[pnum]._pHitPoints *= 2;
	}
	if (c == PC_ROGUE) {
		plr[pnum]._pHitPoints += plr[pnum]._pHitPoints >> 1;
	}

	hp = plr[pnum]._pHitPoints;
	plr[pnum]._pMaxHP = hp;
	plr[pnum]._pHPBase = hp;
	plr[pnum]._pMaxHPBase = hp;

	plr[pnum]._pMana = plr[pnum]._pMagic << 6;
	if (c == PC_SORCERER) {
		plr[pnum]._pMana *= 2;
	}
	if (c == PC_ROGUE) {
		plr[pnum]._pMana += plr[pnum]._pMana >> 1;
	}

	mana = plr[pnum]._pMana;
	plr[pnum]._pMaxMana = mana;
	plr[pnum]._pManaBase = mana;
	plr[pnum]._pMaxManaBase = mana;

	plr[pnum]._pLevel = 1;
	plr[pnum]._pMaxLvl = 1;
	plr[pnum]._pExperience = 0;
	plr[pnum]._pMaxExp = 0;
	plr[pnum]._pNextExper = ExpLvlsTbl[1];
	plr[pnum]._pArmorClass = 0;
	plr[pnum]._pMagResist = 0;
	plr[pnum]._pFireResist = 0;
	plr[pnum]._pLghtResist = 0;
	plr[pnum]._pLightRad = 10;
	plr[pnum]._pInfraFlag = 0;

	if (c == PC_WARRIOR) {
		plr[pnum]._pAblSpells = (__int64)1 << (SPL_REPAIR - 1);
	} else if (c == PC_ROGUE) {
		plr[pnum]._pAblSpells = (__int64)1 << (SPL_DISARM - 1);
	} else if (c == PC_SORCERER) {
		plr[pnum]._pAblSpells = (__int64)1 << (SPL_RECHARGE - 1);
	}

	if (c == PC_SORCERER) {
		plr[pnum]._pMemSpells = 1;
	} else {
		plr[pnum]._pMemSpells = 0;
	}

	for (i = 0; i < sizeof(plr[pnum]._pSplLvl); i++) {
		plr[pnum]._pSplLvl[i] = 0;
	}

	plr[pnum]._pSpellFlags = 0;

	if (plr[pnum]._pClass == PC_SORCERER) {
		plr[pnum]._pSplLvl[SPL_FIREBOLT] = 2;
	}

	// interestingly, only the first three hotkeys are reset
	// TODO: BUGFIX: clear all 4 hotkeys instead of 3 (demo leftover)
	for (i = 0; i < 3; i++) {
		plr[pnum]._pSplHotKey[i] = -1;
	}

	if (c == PC_WARRIOR) {
		plr[pnum]._pgfxnum = ANIM_ID_SWORD_SHIELD;
	} else if (c == PC_ROGUE) {
		plr[pnum]._pgfxnum = ANIM_ID_BOW;
	} else if (c == PC_SORCERER) {
		plr[pnum]._pgfxnum = ANIM_ID_STAFF;
	}

	for (i = 0; i < sizeof(plr[pnum]._pLvlVisited); i++) {
		plr[pnum]._pLvlVisited[i] = 0;
	}

	for (i = 0; i < 10; i++) {
		plr[pnum]._pSLvlVisited[i] = 0; // TODO double check size of _pSLvlVisited
	}

	plr[pnum]._pLvlChanging = 0;
	plr[pnum].pTownWarps = 0;
	plr[pnum].pLvlLoad = 0;
	plr[pnum].pBattleNet = 0;
	plr[pnum].pManaShield = 0;

	InitDungMsgs(pnum);
	CreatePlrItems(pnum);
	SetRndSeed(0);
}

int __fastcall CalcStatDiff(int pnum)
{
	int c;

	c = plr[pnum]._pClass;
	return MaxStats[c][ATTRIB_STR]
	    - plr[pnum]._pBaseStr
	    + MaxStats[c][ATTRIB_MAG]
	    - plr[pnum]._pBaseMag
	    + MaxStats[c][ATTRIB_DEX]
	    - plr[pnum]._pBaseDex
	    + MaxStats[c][ATTRIB_VIT]
	    - plr[pnum]._pBaseVit;
}

void __fastcall NextPlrLevel(int pnum)
{
	char l, c;
	int hp, mana;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("NextPlrLevel: illegal player %d", pnum);
	}

	plr[pnum]._pLevel++;
	l = plr[pnum]._pLevel;

	plr[pnum]._pMaxLvl++;

	if (CalcStatDiff(pnum) < 5) {
		plr[pnum]._pStatPts = CalcStatDiff(pnum);
	} else {
		plr[pnum]._pStatPts += 5;
	}

	plr[pnum]._pNextExper = ExpLvlsTbl[l];

	c = plr[pnum]._pClass;

	hp = c == PC_SORCERER ? 64 : 128;
	if (gbMaxPlayers == 1) {
		hp++;
	}
	plr[pnum]._pMaxHP += hp;
	plr[pnum]._pHitPoints = plr[pnum]._pMaxHP;
	plr[pnum]._pMaxHPBase += hp;
	plr[pnum]._pHPBase = plr[pnum]._pMaxHPBase;

	if (pnum == myplr) {
		drawhpflag = TRUE;
	}

	mana = c != PC_WARRIOR ? 128 : 64;
	if (gbMaxPlayers == 1) {
		mana++;
	}
	plr[pnum]._pMaxMana += mana;
	plr[pnum]._pMaxManaBase += mana;

	if (!(plr[pnum]._pIFlags & ISPL_NOMANA)) {
		plr[pnum]._pMana = plr[pnum]._pMaxMana;
		plr[pnum]._pManaBase = plr[pnum]._pMaxManaBase;
	}

	if (pnum == myplr) {
		drawmanaflag = TRUE;
	}
}

void __fastcall AddPlrExperience(int pnum, int lvl, int exp)
{
	int powerLvlCap, expCap, newLvl, i;

	if (pnum != myplr) {
		return;
	}

	if ((DWORD)myplr >= MAX_PLRS) {
		TermMsg("AddPlrExperience: illegal player %d", myplr);
	}

	if (plr[myplr]._pHitPoints <= 0) {
		return;
	}

	// Adjust xp based on difference in level between player and monster
	exp *= 1 + ((double)lvl - plr[pnum]._pLevel) / 10;
	if (exp < 0) {
		exp = 0;
	}

	// Prevent power leveling
	if (gbMaxPlayers > 1) {
		powerLvlCap = plr[pnum]._pLevel < 0 ? 0 : plr[pnum]._pLevel;
		if (powerLvlCap >= 50) {
			powerLvlCap = 50;
		}
		// cap to 1/20 of current levels xp
		if (exp >= ExpLvlsTbl[powerLvlCap] / 20) {
			exp = ExpLvlsTbl[powerLvlCap] / 20;
		}
		// cap to 200 * current level
		expCap = 200 * powerLvlCap;
		if (exp >= expCap) {
			exp = expCap;
		}
	}

	plr[pnum]._pExperience += exp;
	if ((DWORD)plr[pnum]._pExperience > MAXEXP) {
		plr[pnum]._pExperience = MAXEXP;
	}

	if (plr[pnum]._pExperience >= ExpLvlsTbl[49]) {
		plr[pnum]._pLevel = 50;
		return;
	}

	// Increase player level if applicable
	newLvl = 0;
	while (plr[pnum]._pExperience >= ExpLvlsTbl[newLvl]) {
		newLvl++;
	}
	if (newLvl != plr[pnum]._pLevel) {
		for (i = newLvl - plr[pnum]._pLevel; i > 0; i--) {
			NextPlrLevel(pnum);
		}
	}

	NetSendCmdParam1(FALSE, CMD_PLRLEVEL, plr[myplr]._pLevel);
}

void __fastcall AddPlrMonstExper(int lvl, int exp, char pmask)
{
	int totplrs, i;

	totplrs = 0;
	for (i = 0; i < MAX_PLRS; i++) {
		if ((1 << i) & pmask) {
			totplrs++;
		}
	}

	if (totplrs && (1 << myplr) & pmask) {
		AddPlrExperience(myplr, lvl, exp / totplrs);
	}
}

void __fastcall InitPlayer(int pnum, BOOL FirstTime)
{
	DWORD i;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("InitPlayer: illegal player %d", pnum);
	}

	ClearPlrRVars(&plr[pnum]);

	if (FirstTime) {
		plr[pnum]._pRSpell = SPL_INVALID;
		plr[pnum]._pSBkSpell = SPL_INVALID;
		plr[pnum]._pSpell = SPL_INVALID;
		plr[pnum]._pRSplType = RSPLTYPE_INVALID;
		plr[pnum]._pSplType = RSPLTYPE_INVALID;
		if ((plr[pnum]._pgfxnum & 0xF) == ANIM_ID_BOW) {
			plr[pnum]._pwtype = WT_RANGED;
		} else {
			plr[pnum]._pwtype = WT_MELEE;
		}
		plr[pnum].pManaShield = 0;
	}

	if (plr[pnum].plrlevel == currlevel || leveldebug) {

		SetPlrAnims(pnum);

		plr[pnum]._pxoff = 0;
		plr[pnum]._pyoff = 0;
		plr[pnum]._pxvel = 0;
		plr[pnum]._pyvel = 0;

		ClearPlrPVars(pnum);

		if (plr[pnum]._pHitPoints >> 6 > 0) {
			plr[pnum]._pmode = PM_STAND;
			NewPlrAnim(pnum, plr[pnum]._pNAnim[DIR_S], plr[pnum]._pNFrames, 3, plr[pnum]._pNWidth);
			plr[pnum]._pAnimFrame = random(2, plr[pnum]._pNFrames - 1) + 1;
			plr[pnum]._pAnimCnt = random(2, 3);
		} else {
			plr[pnum]._pmode = PM_DEATH;
			NewPlrAnim(pnum, plr[pnum]._pDAnim[DIR_S], plr[pnum]._pDFrames, 1, plr[pnum]._pDWidth);
			plr[pnum]._pAnimFrame = plr[pnum]._pAnimLen - 1;
			plr[pnum]._pVar8 = 2 * plr[pnum]._pAnimLen;
		}

		plr[pnum]._pdir = DIR_S;
		plr[pnum]._peflag = 0;

		if (pnum == myplr) {
			if (!FirstTime || currlevel != 0) {
				plr[pnum].WorldX = ViewX;
				plr[pnum].WorldY = ViewY;
			}
			plr[pnum]._ptargx = plr[pnum].WorldX;
			plr[pnum]._ptargy = plr[pnum].WorldY;
		} else {
			plr[pnum]._ptargx = plr[pnum].WorldX;
			plr[pnum]._ptargy = plr[pnum].WorldY;
			for (i = 0; i < 8 && !PosOkPlayer(pnum, plrxoff2[i] + plr[pnum].WorldX, plryoff2[i] + plr[pnum].WorldY); i++)
				;
			plr[pnum].WorldX += plrxoff2[i];
			plr[pnum].WorldY += plryoff2[i];
		}

		plr[pnum]._px = plr[pnum].WorldX;
		plr[pnum]._py = plr[pnum].WorldY;
		plr[pnum].walkpath[0] = WALK_NONE;
		plr[pnum].destAction = ACTION_NONE;

		if (pnum == myplr) {
			plr[pnum]._plid = AddLight(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum]._pLightRad);
		} else {
			plr[pnum]._plid = WALK_NONE;
		}
		plr[pnum]._pvid = AddVision(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum]._pLightRad, pnum == myplr);
	}

	if (plr[pnum]._pClass == PC_WARRIOR) {
		plr[pnum]._pAblSpells = 1 << (SPL_REPAIR - 1);
	} else if (plr[pnum]._pClass == PC_ROGUE) {
		plr[pnum]._pAblSpells = 1 << (SPL_DISARM - 1);
	} else if (plr[pnum]._pClass == PC_SORCERER) {
		plr[pnum]._pAblSpells = 1 << (SPL_RECHARGE - 1);
	}

#ifdef _DEBUG
	if (debug_mode_dollar_sign && FirstTime) {
		plr[pnum]._pMemSpells |= 1 << (SPL_TELEPORT - 1);
		if (!plr[myplr]._pSplLvl[SPL_TELEPORT]) {
			plr[myplr]._pSplLvl[SPL_TELEPORT] = 1;
		}
	}
	if (debug_mode_key_inverted_v && FirstTime) {
		plr[pnum]._pMemSpells = SPL_INVALID;
	}
#endif

	plr[pnum]._pNextExper = ExpLvlsTbl[plr[pnum]._pLevel];
	plr[pnum]._pInvincible = FALSE;

	if (pnum == myplr) {
		deathdelay = 0;
		deathflag = FALSE;
		ScrollInfo._sxoff = 0;
		ScrollInfo._syoff = 0;
		ScrollInfo._sdir = SDIR_NONE;
	}
}
// 52572C: using guessed type int leveldebug;

void __cdecl InitMultiView()
{
	if ((DWORD)myplr >= MAX_PLRS) {
		TermMsg("InitPlayer: illegal player %d", myplr);
	}

	ViewX = plr[myplr].WorldX;
	ViewY = plr[myplr].WorldY;
}

void __fastcall InitPlayerLoc(int pnum, BOOL flag)
{
	int x, y, i;
	int bitflags;
	USHORT *pieces;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("InitPlayer: illegal player %d", pnum);
	}

	x = plr[pnum].WorldX - 1;
	y = plr[pnum].WorldY + 1;
	bitflags = 0;
	pieces = dpiece_defs_map_1[gendung_get_dpiece_num_from_coord(x, y)];

	for (i = 2; i < 10; i++) {
		bitflags |= pieces[i];
	}

	if (bitflags | nSolidTable[dPiece[x][y]] | dArch[x][y]) {
		plr[pnum]._peflag = 1;
	} else {
		plr[pnum]._peflag = 0;
	}

	if (flag != 1 || plr[pnum]._peflag != 1) {
		return;
	}

	x = plr[pnum].WorldX;
	y = plr[pnum].WorldY + 2;
	bitflags = 0;
	pieces = dpiece_defs_map_1[gendung_get_dpiece_num_from_coord(x, y)];

	for (i = 2; i < 10; i++) {
		bitflags |= pieces[i];
	}

	if (bitflags | dArch[x][y]) {
		return;
	}

	x = plr[pnum].WorldX - 2;
	y = plr[pnum].WorldY + 1;
	bitflags = 0;
	pieces = dpiece_defs_map_1[gendung_get_dpiece_num_from_coord(x, y)];

	for (i = 2; i < 10; i++) {
		bitflags |= pieces[i];
	}

	if (bitflags | dArch[x][y]) {
		plr[pnum]._peflag = 2;
	}
}

BOOL __fastcall SolidLoc(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAXDUNX || y >= MAXDUNY) {
		return FALSE;
	}

	return nSolidTable[dPiece[x][y]];
}

BOOL __fastcall PlrDirOK(int pnum, int dir)
{
	int px, py;
	BOOL isOk;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PlrDirOK: illegal player %d", pnum);
	}

	px = plr[pnum].WorldX + offset_x[dir];
	py = plr[pnum].WorldY + offset_y[dir];

	if (px < 0 || !dPiece[px][py] || !PosOkPlayer(pnum, px, py)) {
		return FALSE;
	}

	isOk = TRUE;
	if (dir == DIR_E) {
		isOk = !SolidLoc(px, py + 1) && !(dFlags[px][py + 1] & DFLAG_PLAYER);
	}

	if (isOk && dir == DIR_W) {
		isOk = !SolidLoc(px + 1, py) && !(dFlags[px + 1][py] & DFLAG_PLAYER);
	}

	return isOk;
}

void __fastcall PlrClrTrans(int x, int y)
{
	int i, j;

	for (i = y - 1; i <= y + 1; i++) {
		for (j = x - 1; j <= x + 1; j++) {
			TransList[dung_map[j][i]] = 0;
		}
	}
}

void __fastcall PlrDoTrans(int x, int y)
{
	int i, j;

	if (leveltype != DTYPE_CATHEDRAL && leveltype != DTYPE_CATACOMBS) {
		TransList[1] = 1;
	} else {
		for (i = y - 1; i <= y + 1; i++) {
			for (j = x - 1; j <= x + 1; j++) {
				if (!nSolidTable[dPiece[j][i]] && dung_map[j][i]) {
					TransList[dung_map[j][i]] = 1;
				}
			}
		}
	}
}

void __fastcall SetPlayerOld(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlayerOld: illegal player %d", pnum);
	}

	plr[pnum]._poldx = plr[pnum].WorldX;
	plr[pnum]._poldy = plr[pnum].WorldY;
}

void __fastcall FixPlayerLocation(int pnum, int dir)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("FixPlayerLocation: illegal player %d", pnum);
	}

	plr[pnum]._px = plr[pnum].WorldX;
	plr[pnum]._py = plr[pnum].WorldY;
	plr[pnum]._ptargx = plr[pnum].WorldX;
	plr[pnum]._ptargy = plr[pnum].WorldY;
	plr[pnum]._pxoff = 0;
	plr[pnum]._pyoff = 0;
	InitPlayerLoc(pnum, FALSE);
	plr[pnum]._pdir = dir;
	if (pnum == myplr) {
		ScrollInfo._sxoff = 0;
		ScrollInfo._syoff = 0;
		ScrollInfo._sdir = SDIR_NONE;
		ViewX = plr[pnum].WorldX;
		ViewY = plr[pnum].WorldY;
	}
}

void __fastcall StartStand(int pnum, int dir)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartStand: illegal player %d", pnum);
	}

	if (!plr[pnum]._pInvincible || plr[pnum]._pHitPoints || pnum != myplr) {
		if (!(plr[pnum]._pGFXLoad & PFILE_STAND)) {
			LoadPlrGFX(pnum, PFILE_STAND);
		}

		NewPlrAnim(pnum, plr[pnum]._pNAnim[dir], plr[pnum]._pNFrames, 3, plr[pnum]._pNWidth);
		plr[pnum]._pmode = PM_STAND;
		FixPlayerLocation(pnum, dir);
		FixPlrWalkTags(pnum);
		dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = pnum + 1;
		SetPlayerOld(pnum);
	} else {
		SyncPlrKill(pnum, -1);
	}
}

void __fastcall StartWalkStand(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartWalkStand: illegal player %d", pnum);
	}

	plr[pnum]._pmode = 0;
	plr[pnum]._px = plr[pnum].WorldX;
	plr[pnum]._py = plr[pnum].WorldY;
	plr[pnum]._pxoff = 0;
	plr[pnum]._pyoff = 0;

	InitPlayerLoc(pnum, 0);

	if (pnum == myplr) {
		ScrollInfo._sxoff = 0;
		ScrollInfo._syoff = 0;
		ScrollInfo._sdir = SDIR_NONE;
		ViewX = plr[pnum].WorldX;
		ViewY = plr[pnum].WorldY;
	}
}

void __fastcall PM_ChangeLightOff(int pnum)
{
	int x, y;
	int xmul, ymul;
	int lx, ly;
	int offx, offy;
	const LightListStruct *l;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_ChangeLightOff: illegal player %d", pnum);
	}

	l = &LightList[plr[pnum]._plid];
	ymul = -1;
	x = 2 * plr[pnum]._pyoff + plr[pnum]._pxoff;
	y = 2 * plr[pnum]._pyoff - plr[pnum]._pxoff;
	if (x < 0) {
		xmul = -1;
		x = -x;
	} else {
		xmul = 1;
	}
	if (y < 0) {
		y = -y;
	} else {
		ymul = 1;
	}

	x = (x >> 3) * xmul;
	y = (y >> 3) * ymul;
	lx = x + (l->_lx << 3);
	ly = y + (l->_ly << 3);
	offx = l->_xoff + (l->_lx << 3);
	offy = l->_yoff + (l->_ly << 3);

	if (abs(lx - offx) < 3 && abs(ly - offy) < 3)
		return;

	ChangeLightOff(plr[pnum]._plid, x, y);
}

void __fastcall PM_ChangeOffset(int pnum)
{
	int px, py;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_ChangeOffset: illegal player %d", pnum);
	}

	plr[pnum]._pVar8++;
	px = plr[pnum]._pVar6 >> 8;
	py = plr[pnum]._pVar7 >> 8;

	plr[pnum]._pVar6 += plr[pnum]._pxvel;
	plr[pnum]._pVar7 += plr[pnum]._pyvel;
	plr[pnum]._pxoff = plr[pnum]._pVar6 >> 8;
	plr[pnum]._pyoff = plr[pnum]._pVar7 >> 8;

	if (pnum == myplr && ScrollInfo._sdir) {
		ScrollInfo._sxoff += px - plr[pnum]._pxoff;
		ScrollInfo._syoff += py - plr[pnum]._pyoff;
	}

	PM_ChangeLightOff(pnum);
}

void __fastcall StartWalk(int pnum, int xvel, int yvel, int xadd, int yadd, int EndDir, int sdir)
{
	int px, py;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartWalk: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	SetPlayerOld(pnum);

	px = xadd + plr[pnum].WorldX;
	py = yadd + plr[pnum].WorldY;

	if (!PlrDirOK(pnum, EndDir)) {
		return;
	}

	plr[pnum]._px = px;
	plr[pnum]._py = py;

	if (pnum == myplr) {
		ScrollInfo._sdx = plr[pnum].WorldX - ViewX;
		ScrollInfo._sdy = plr[pnum].WorldY - ViewY;
	}

	dPlayer[px][py] = -(pnum + 1);
	plr[pnum]._pmode = PM_WALK;
	plr[pnum]._pxvel = xvel;
	plr[pnum]._pyvel = yvel;
	plr[pnum]._pxoff = 0;
	plr[pnum]._pyoff = 0;
	plr[pnum]._pVar1 = xadd;
	plr[pnum]._pVar2 = yadd;
	plr[pnum]._pVar3 = EndDir;

	if (!(plr[pnum]._pGFXLoad & PFILE_WALK)) {
		LoadPlrGFX(pnum, PFILE_WALK);
	}

	NewPlrAnim(pnum, plr[pnum]._pWAnim[EndDir], plr[pnum]._pWFrames, 0, plr[pnum]._pWWidth);

	plr[pnum]._pdir = EndDir;
	plr[pnum]._pVar6 = 0;
	plr[pnum]._pVar7 = 0;
	plr[pnum]._pVar8 = 0;

	InitPlayerLoc(pnum, FALSE);

	if (pnum != myplr) {
		return;
	}

	if (zoomflag) {
		if (abs(ScrollInfo._sdx) >= 3 || abs(ScrollInfo._sdy) >= 3) {
			ScrollInfo._sdir = SDIR_NONE;
		} else {
			ScrollInfo._sdir = sdir;
		}
	} else if (abs(ScrollInfo._sdx) >= 2 || abs(ScrollInfo._sdy) >= 2) {
		ScrollInfo._sdir = SDIR_NONE;
	} else {
		ScrollInfo._sdir = sdir;
	}
}
// 52569C: using guessed type int zoomflag;

void __fastcall StartWalk2(int pnum, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int EndDir, int sdir)
{
	int px, py;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartWalk2: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	SetPlayerOld(pnum);
	px = xadd + plr[pnum].WorldX;
	py = yadd + plr[pnum].WorldY;

	if (!PlrDirOK(pnum, EndDir)) {
		return;
	}

	plr[pnum]._px = px;
	plr[pnum]._py = py;

	if (pnum == myplr) {
		ScrollInfo._sdx = plr[pnum].WorldX - ViewX;
		ScrollInfo._sdy = plr[pnum].WorldY - ViewY;
	}

	dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = -1 - pnum;
	plr[pnum]._pVar1 = plr[pnum].WorldX;
	plr[pnum]._pVar2 = plr[pnum].WorldY;
	plr[pnum].WorldX = px;
	plr[pnum].WorldY = py;
	dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = pnum + 1;
	plr[pnum]._pxoff = xoff;
	plr[pnum]._pyoff = yoff;

	ChangeLightXY(plr[pnum]._plid, plr[pnum].WorldX, plr[pnum].WorldY);
	PM_ChangeLightOff(pnum);

	plr[pnum]._pmode = PM_WALK2;
	plr[pnum]._pxvel = xvel;
	plr[pnum]._pyvel = yvel;
	plr[pnum]._pVar6 = xoff << 8;
	plr[pnum]._pVar7 = yoff << 8;
	plr[pnum]._pVar3 = EndDir;

	if (!(plr[pnum]._pGFXLoad & PFILE_WALK)) {
		LoadPlrGFX(pnum, PFILE_WALK);
	}
	NewPlrAnim(pnum, plr[pnum]._pWAnim[EndDir], plr[pnum]._pWFrames, 0, plr[pnum]._pWWidth);

	plr[pnum]._pdir = EndDir;
	plr[pnum]._pVar8 = 0;

	if (EndDir == DIR_SE) {
		InitPlayerLoc(pnum, TRUE);
	} else {
		InitPlayerLoc(pnum, FALSE);
	}

	if (pnum != myplr) {
		return;
	}

	if (zoomflag) {
		if (abs(ScrollInfo._sdx) >= 3 || abs(ScrollInfo._sdy) >= 3) {
			ScrollInfo._sdir = SDIR_NONE;
		} else {
			ScrollInfo._sdir = sdir;
		}
	} else if (abs(ScrollInfo._sdx) >= 2 || abs(ScrollInfo._sdy) >= 2) {
		ScrollInfo._sdir = SDIR_NONE;
	} else {
		ScrollInfo._sdir = sdir;
	}
}
// 52569C: using guessed type int zoomflag;

void __fastcall StartWalk3(int pnum, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int mapx, int mapy, int EndDir, int sdir)
{
	int px, py, x, y;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartWalk3: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	SetPlayerOld(pnum);
	px = xadd + plr[pnum].WorldX;
	py = yadd + plr[pnum].WorldY;
	x = mapx + plr[pnum].WorldX;
	y = mapy + plr[pnum].WorldY;

	if (!PlrDirOK(pnum, EndDir)) {
		return;
	}

	plr[pnum]._px = px;
	plr[pnum]._py = py;

	if (pnum == myplr) {
		ScrollInfo._sdx = plr[pnum].WorldX - ViewX;
		ScrollInfo._sdy = plr[pnum].WorldY - ViewY;
	}

	dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = -1 - pnum;
	dPlayer[px][py] = -1 - pnum;
	plr[pnum]._pVar4 = x;
	plr[pnum]._pVar5 = y;
	dFlags[x][y] |= DFLAG_PLAYER;
	plr[pnum]._pxoff = xoff;
	plr[pnum]._pyoff = yoff;

	if (leveltype) {
		ChangeLightXY(plr[pnum]._plid, x, y);
		PM_ChangeLightOff(pnum);
	}

	plr[pnum]._pmode = PM_WALK3;
	plr[pnum]._pxvel = xvel;
	plr[pnum]._pyvel = yvel;
	plr[pnum]._pVar1 = px;
	plr[pnum]._pVar2 = py;
	plr[pnum]._pVar6 = xoff << 8;
	plr[pnum]._pVar7 = yoff << 8;
	plr[pnum]._pVar3 = EndDir;

	if (!(plr[pnum]._pGFXLoad & PFILE_WALK)) {
		LoadPlrGFX(pnum, PFILE_WALK);
	}
	NewPlrAnim(pnum, plr[pnum]._pWAnim[EndDir], plr[pnum]._pWFrames, 0, plr[pnum]._pWWidth);

	plr[pnum]._pdir = EndDir;
	plr[pnum]._pVar8 = 0;

	InitPlayerLoc(pnum, FALSE);

	if (pnum != myplr) {
		return;
	}

	if (zoomflag) {
		if (abs(ScrollInfo._sdx) >= 3 || abs(ScrollInfo._sdy) >= 3) {
			ScrollInfo._sdir = SDIR_NONE;
		} else {
			ScrollInfo._sdir = sdir;
		}
	} else if (abs(ScrollInfo._sdx) >= 2 || abs(ScrollInfo._sdy) >= 2) {
		ScrollInfo._sdir = SDIR_NONE;
	} else {
		ScrollInfo._sdir = sdir;
	}
}
// 52569C: using guessed type int zoomflag;

void __fastcall StartAttack(int pnum, int d)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartAttack: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	if (!(plr[pnum]._pGFXLoad & PFILE_ATTACK)) {
		LoadPlrGFX(pnum, PFILE_ATTACK);
	}

	NewPlrAnim(pnum, plr[pnum]._pAAnim[d], plr[pnum]._pAFrames, 0, plr[pnum]._pAWidth);
	plr[pnum]._pmode = PM_ATTACK;
	FixPlayerLocation(pnum, d);
	SetPlayerOld(pnum);
}

void __fastcall StartRangeAttack(int pnum, int d, int cx, int cy)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartRangeAttack: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	if (!(plr[pnum]._pGFXLoad & PFILE_ATTACK)) {
		LoadPlrGFX(pnum, PFILE_ATTACK);
	}
	NewPlrAnim(pnum, plr[pnum]._pAAnim[d], plr[pnum]._pAFrames, 0, plr[pnum]._pAWidth);

	plr[pnum]._pmode = PM_RATTACK;
	FixPlayerLocation(pnum, d);
	SetPlayerOld(pnum);
	plr[pnum]._pVar1 = cx;
	plr[pnum]._pVar2 = cy;
}

void __fastcall StartPlrBlock(int pnum, int dir)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartPlrBlock: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	PlaySfxLoc(IS_ISWORD, plr[pnum].WorldX, plr[pnum].WorldY);

	if (!(plr[pnum]._pGFXLoad & PFILE_BLOCK)) {
		LoadPlrGFX(pnum, PFILE_BLOCK);
	}
	NewPlrAnim(pnum, plr[pnum]._pBAnim[dir], plr[pnum]._pBFrames, 2, plr[pnum]._pBWidth);

	plr[pnum]._pmode = PM_BLOCK;
	FixPlayerLocation(pnum, dir);
	SetPlayerOld(pnum);
}

void __fastcall StartSpell(int pnum, int d, int cx, int cy)
{
	if ((DWORD)pnum >= MAX_PLRS)
		TermMsg("StartSpell: illegal player %d", pnum);

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	if (leveltype != DTYPE_TOWN) {
		switch (spelldata[plr[pnum]._pSpell].sType) {
		case STYPE_FIRE:
			if (!(plr[pnum]._pGFXLoad & PFILE_FIRE)) {
				LoadPlrGFX(pnum, PFILE_FIRE);
			}
			NewPlrAnim(pnum, plr[pnum]._pFAnim[d], plr[pnum]._pSFrames, 0, plr[pnum]._pSWidth);
			break;
		case STYPE_LIGHTNING:
			if (!(plr[pnum]._pGFXLoad & PFILE_LIGHTNING)) {
				LoadPlrGFX(pnum, PFILE_LIGHTNING);
			}
			NewPlrAnim(pnum, plr[pnum]._pLAnim[d], plr[pnum]._pSFrames, 0, plr[pnum]._pSWidth);
			break;
		case STYPE_MAGIC:
			if (!(plr[pnum]._pGFXLoad & PFILE_MAGIC)) {
				LoadPlrGFX(pnum, PFILE_MAGIC);
			}
			NewPlrAnim(pnum, plr[pnum]._pTAnim[d], plr[pnum]._pSFrames, 0, plr[pnum]._pSWidth);
			break;
		}
	}

	PlaySfxLoc(spelldata[plr[pnum]._pSpell].sSFX, plr[pnum].WorldX, plr[pnum].WorldY);

	plr[pnum]._pmode = PM_SPELL;

	FixPlayerLocation(pnum, d);
	SetPlayerOld(pnum);

	plr[pnum]._pVar1 = cx;
	plr[pnum]._pVar2 = cy;
	plr[pnum]._pVar4 = GetSpellLevel(pnum, plr[pnum]._pSpell);
	plr[pnum]._pVar8 = 1;
}

void __fastcall FixPlrWalkTags(int pnum)
{
	int pp, pn;
	int dx, dy, y, x;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("FixPlrWalkTags: illegal player %d", pnum);
	}

	pp = pnum + 1;
	pn = -(pnum + 1);
	dx = plr[pnum]._poldx;
	dy = plr[pnum]._poldy;
	for (y = dy - 1; y <= dy + 1; y++) {
		for (x = dx - 1; x <= dx + 1; x++) {
			if (x >= 0 && x < MAXDUNX && y >= 0 && y < MAXDUNY && (dPlayer[x][y] == pp || dPlayer[x][y] == pn)) {
				dPlayer[x][y] = 0;
			}
		}
	}

	if (dx >= 0 && dx < MAXDUNX - 1 && dy >= 0 && dy < MAXDUNY - 1) {
		dFlags[dx + 1][dy] &= ~DFLAG_PLAYER;
		dFlags[dx][dy + 1] &= ~DFLAG_PLAYER;
	}
}

void __fastcall RemovePlrFromMap(int pnum)
{
	int x, y;
	int pp, pn;

	pp = pnum + 1;
	pn = -(pnum + 1);

	for (y = 1; y < MAXDUNY; y++)
		for (x = 1; x < MAXDUNX; x++)
			if (dPlayer[x][y - 1] == pn || dPlayer[x - 1][y] == pn)
				if (dFlags[x][y] & DFLAG_PLAYER)
					dFlags[x][y] &= ~DFLAG_PLAYER;

	for (y = 0; y < MAXDUNY; y++)
		for (x = 0; x < MAXDUNX; x++)
			if (dPlayer[x][y] == pp || dPlayer[x][y] == pn)
				dPlayer[x][y] = 0;
}

void __fastcall StartPlrHit(int pnum, int dam, BOOL forcehit)
{
	int pd;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartPlrHit: illegal player %d", pnum);
	}

	if (plr[pnum]._pInvincible && !plr[pnum]._pHitPoints && pnum == myplr) {
		SyncPlrKill(pnum, -1);
		return;
	}

	if (plr[pnum]._pClass == PC_WARRIOR) {
		PlaySfxLoc(PS_WARR69, plr[pnum].WorldX, plr[pnum].WorldY);
	} else if (plr[pnum]._pClass == PC_ROGUE) {
		PlaySfxLoc(PS_ROGUE69, plr[pnum].WorldX, plr[pnum].WorldY);
	} else if (plr[pnum]._pClass == PC_SORCERER) {
		PlaySfxLoc(PS_MAGE69, plr[pnum].WorldX, plr[pnum].WorldY);
	}

	drawhpflag = TRUE;
	if (dam >> 6 >= plr[pnum]._pLevel || forcehit) {
		pd = plr[pnum]._pdir;

		if (!(plr[pnum]._pGFXLoad & PFILE_HIT)) {
			LoadPlrGFX(pnum, PFILE_HIT);
		}
		NewPlrAnim(pnum, plr[pnum]._pHAnim[pd], plr[pnum]._pHFrames, 0, plr[pnum]._pHWidth);

		plr[pnum]._pmode = PM_GOTHIT;
		FixPlayerLocation(pnum, pd);
		plr[pnum]._pVar8 = 1;
		FixPlrWalkTags(pnum);
		dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = pnum + 1;
		SetPlayerOld(pnum);
	}
}

void __fastcall RespawnDeadItem(ItemStruct *itm, int x, int y)
{
	int ii;

	if (numitems >= MAXITEMS) {
		return;
	}

	if (FindGetItem(itm->IDidx, itm->_iCreateInfo, itm->_iSeed) >= 0) {
		DrawInvMsg("A duplicate item has been detected.  Destroying duplicate...");
		SyncGetItem(x, y, itm->IDidx, itm->_iCreateInfo, itm->_iSeed);
	}

	ii = itemavail[0];
	dItem[x][y] = ii + 1;
	itemavail[0] = itemavail[MAXITEMS - numitems - 1];
	itemactive[numitems] = ii;
	item[ii] = *itm;
	item[ii]._ix = x;
	item[ii]._iy = y;
	RespawnItem(ii, TRUE);
	numitems++;
	itm->_itype = ITYPE_NONE;
}

void __fastcall StartPlayerKill(int pnum, int earflag)
{
	BOOL diablolevel;
	int i, pdd;
	PlayerStruct *p;
	ItemStruct ear;
	ItemStruct *pi;

	if (plr[pnum]._pHitPoints <= 0 && plr[pnum]._pmode == PM_DEATH) {
		return;
	}

	if (myplr == pnum) {
		NetSendCmdParam1(TRUE, CMD_PLRDEAD, earflag);
	}

	diablolevel = gbMaxPlayers > 1 && plr[pnum].plrlevel == 16;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartPlayerKill: illegal player %d", pnum);
	}

	if (plr[pnum]._pClass == PC_WARRIOR) {
		PlaySfxLoc(PS_DEAD, plr[pnum].WorldX, plr[pnum].WorldY); // BUGFIX: should use `PS_WARR71` like other classes
	} else if (plr[pnum]._pClass == PC_ROGUE) {
		PlaySfxLoc(PS_ROGUE71, plr[pnum].WorldX, plr[pnum].WorldY);
	} else if (plr[pnum]._pClass == PC_SORCERER) {
		PlaySfxLoc(PS_MAGE71, plr[pnum].WorldX, plr[pnum].WorldY);
	}

	if (plr[pnum]._pgfxnum) {
		plr[pnum]._pgfxnum = 0;
		plr[pnum]._pGFXLoad = 0;
		SetPlrAnims(pnum);
	}

	if (!(plr[pnum]._pGFXLoad & PFILE_DEATH)) {
		LoadPlrGFX(pnum, PFILE_DEATH);
	}

	p = &plr[pnum];
	NewPlrAnim(pnum, p->_pDAnim[plr[pnum]._pdir], p->_pDFrames, 1, p->_pDWidth);

	plr[pnum]._pBlockFlag = FALSE;
	plr[pnum]._pmode = PM_DEATH;
	plr[pnum]._pInvincible = TRUE;
	SetPlayerHitPoints(pnum, 0);
	plr[pnum]._pVar8 = 1;

	if (pnum != myplr && !earflag && !diablolevel) {
		for (i = 0; i < NUM_INVLOC; i++) {
			plr[pnum].InvBody[i]._itype = ITYPE_NONE;
		}
		CalcPlrInv(pnum, FALSE);
	}

	if (plr[pnum].plrlevel == currlevel) {
		FixPlayerLocation(pnum, plr[pnum]._pdir);
		RemovePlrFromMap(pnum);
		dFlags[plr[pnum].WorldX][plr[pnum].WorldY] |= DFLAG_DEAD_PLAYER;
		SetPlayerOld(pnum);

		if (pnum == myplr) {
			drawhpflag = TRUE;
			deathdelay = 30;

			if (pcurs >= CURSOR_FIRSTITEM) {
				PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
				SetCursor_(CURSOR_HAND);
			}

			if (!diablolevel) {
				DropHalfPlayersGold(pnum);
				if (earflag != -1) {
					if (earflag != 0) {
						SetPlrHandItem(&ear, IDI_EAR);
						sprintf(ear._iName, "Ear of %s", plr[pnum]._pName);
						if (plr[pnum]._pClass == PC_SORCERER) {
							ear._iCurs = ICURS_EAR_SORCEROR;
						} else if (plr[pnum]._pClass == PC_WARRIOR) {
							ear._iCurs = ICURS_EAR_WARRIOR;
						} else if (plr[pnum]._pClass == PC_ROGUE) {
							ear._iCurs = ICURS_EAR_ROGUE;
						}

						ear._iCreateInfo = plr[pnum]._pName[0] << 8 | plr[pnum]._pName[1];
						ear._iSeed = plr[pnum]._pName[2] << 24 | plr[pnum]._pName[3] << 16 | plr[pnum]._pName[4] << 8 | plr[pnum]._pName[5];
						ear._ivalue = plr[pnum]._pLevel;

						if (FindGetItem(IDI_EAR, ear._iCreateInfo, ear._iSeed) == -1) {
							PlrDeadItem(pnum, &ear, 0, 0);
						}
					} else {
						pi = &plr[pnum].InvBody[0];
						i = NUM_INVLOC;
						while (i != 0) {
							i--;
							pdd = (i + plr[pnum]._pdir) & 7;
							PlrDeadItem(pnum, pi, offset_x[pdd], offset_y[pdd]);
							pi++;
						}

						CalcPlrInv(pnum, FALSE);
					}
				}
			}
		}
	}
	SetPlayerHitPoints(pnum, 0);
}

void __fastcall PlrDeadItem(int pnum, ItemStruct *itm, int xx, int yy)
{
	int x, y;
	int i, j, k;

	if (itm->_itype == ITYPE_NONE)
		return;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PlrDeadItem: illegal player %d", pnum);
	}

	x = xx + plr[pnum].WorldX;
	y = yy + plr[pnum].WorldY;
	if ((xx || yy) && ItemSpaceOk(x, y)) {
		RespawnDeadItem(itm, x, y);
		plr[pnum].HoldItem = *itm;
		NetSendCmdPItem(FALSE, CMD_RESPAWNITEM, x, y);
		return;
	}

	for (k = 1; k < 50; k++) {
		for (j = -k; j <= k; j++) {
			y = j + plr[pnum].WorldY;
			for (i = -k; i <= k; i++) {
				x = i + plr[pnum].WorldX;
				if (ItemSpaceOk(x, y)) {
					RespawnDeadItem(itm, x, y);
					plr[pnum].HoldItem = *itm;
					NetSendCmdPItem(FALSE, CMD_RESPAWNITEM, x, y);
					return;
				}
			}
		}
	}
}

void __fastcall DropHalfPlayersGold(int pnum)
{
	int i, hGold;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("DropHalfPlayersGold: illegal player %d", pnum);
	}

	hGold = plr[pnum]._pGold >> 1;
	for (i = 0; i < MAXBELTITEMS && hGold > 0; i++) {
		if (plr[pnum].SpdList[i]._itype == ITYPE_GOLD && plr[pnum].SpdList[i]._ivalue != 5000) {
			if (hGold < plr[pnum].SpdList[i]._ivalue) {
				plr[pnum].SpdList[i]._ivalue -= hGold;
				SetSpdbarGoldCurs(pnum, i);
				SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
				GetGoldSeed(pnum, &plr[pnum].HoldItem);
				SetPlrHandGoldCurs(&plr[pnum].HoldItem);
				plr[pnum].HoldItem._ivalue = hGold;
				PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
				hGold = 0;
			} else {
				hGold -= plr[pnum].SpdList[i]._ivalue;
				RemoveSpdBarItem(pnum, i);
				SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
				GetGoldSeed(pnum, &plr[pnum].HoldItem);
				SetPlrHandGoldCurs(&plr[pnum].HoldItem);
				plr[pnum].HoldItem._ivalue = plr[pnum].SpdList[i]._ivalue;
				PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
				i = -1;
			}
		}
	}
	if (hGold > 0) {
		for (i = 0; i < MAXBELTITEMS && hGold > 0; i++) {
			if (plr[pnum].SpdList[i]._itype == ITYPE_GOLD) {
				if (hGold < plr[pnum].SpdList[i]._ivalue) {
					plr[pnum].SpdList[i]._ivalue -= hGold;
					SetSpdbarGoldCurs(pnum, i);
					SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
					GetGoldSeed(pnum, &plr[pnum].HoldItem);
					SetPlrHandGoldCurs(&plr[pnum].HoldItem);
					plr[pnum].HoldItem._ivalue = hGold;
					PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
					hGold = 0;
				} else {
					hGold -= plr[pnum].SpdList[i]._ivalue;
					RemoveSpdBarItem(pnum, i);
					SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
					GetGoldSeed(pnum, &plr[pnum].HoldItem);
					SetPlrHandGoldCurs(&plr[pnum].HoldItem);
					plr[pnum].HoldItem._ivalue = plr[pnum].SpdList[i]._ivalue;
					PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
					i = -1;
				}
			}
		}
	}
	drawpanflag = 255;
	if (hGold > 0) {
		for (i = 0; i < plr[pnum]._pNumInv && hGold > 0; i++) {
			if (plr[pnum].InvList[i]._itype == ITYPE_GOLD && plr[pnum].InvList[i]._ivalue != 5000) {
				if (hGold < plr[pnum].InvList[i]._ivalue) {
					plr[pnum].InvList[i]._ivalue -= hGold;
					SetGoldCurs(pnum, i);
					SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
					GetGoldSeed(pnum, &plr[pnum].HoldItem);
					SetPlrHandGoldCurs(&plr[pnum].HoldItem);
					plr[pnum].HoldItem._ivalue = hGold;
					PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
					hGold = 0;
				} else {
					hGold -= plr[pnum].InvList[i]._ivalue;
					RemoveInvItem(pnum, i);
					SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
					GetGoldSeed(pnum, &plr[pnum].HoldItem);
					SetPlrHandGoldCurs(&plr[pnum].HoldItem);
					plr[pnum].HoldItem._ivalue = plr[pnum].InvList[i]._ivalue;
					PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
					i = -1;
				}
			}
		}
	}
	if (hGold > 0) {
		for (i = 0; i < plr[pnum]._pNumInv && hGold > 0; i++) {
			if (plr[pnum].InvList[i]._itype == ITYPE_GOLD) {
				if (hGold < plr[pnum].InvList[i]._ivalue) {
					plr[pnum].InvList[i]._ivalue -= hGold;
					SetGoldCurs(pnum, i);
					SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
					GetGoldSeed(pnum, &plr[pnum].HoldItem);
					SetPlrHandGoldCurs(&plr[pnum].HoldItem);
					plr[pnum].HoldItem._ivalue = hGold;
					PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
					hGold = 0;
				} else {
					hGold -= plr[pnum].InvList[i]._ivalue;
					RemoveInvItem(pnum, i);
					SetPlrHandItem(&plr[pnum].HoldItem, IDI_GOLD);
					GetGoldSeed(pnum, &plr[pnum].HoldItem);
					SetPlrHandGoldCurs(&plr[pnum].HoldItem);
					plr[pnum].HoldItem._ivalue = plr[pnum].InvList[i]._ivalue;
					PlrDeadItem(pnum, &plr[pnum].HoldItem, 0, 0);
					i = -1;
				}
			}
		}
	}
	plr[pnum]._pGold = CalculateGold(pnum);
}
// 52571C: using guessed type int drawpanflag;

void __fastcall SyncPlrKill(int pnum, int earflag)
{
	int ma, i;

	if (plr[pnum]._pHitPoints == 0 && currlevel == 0) {
		SetPlayerHitPoints(pnum, 64);
		return;
	}

	for (i = 0; i < nummissiles; i++) {
		ma = missileactive[i];
		if (missile[ma]._mitype == MIS_MANASHIELD && missile[ma]._misource == pnum && missile[ma]._miDelFlag == FALSE) {
			if (earflag != -1) {
				missile[ma]._miVar8 = earflag;
			}

			return;
		}
	}

	SetPlayerHitPoints(pnum, 0);
	StartPlayerKill(pnum, earflag);
}

void __fastcall RemovePlrMissiles(int pnum)
{
	int mi, am;

	if (currlevel != 0 && pnum == myplr && (monster[myplr]._mx != 1 || monster[myplr]._my != 0)) {
		M_StartKill(myplr, myplr);
		AddDead(monster[myplr]._mx, monster[myplr]._my, monster[myplr].MType->mdeadval, (direction)monster[myplr]._mdir);
		dMonster[monster[myplr]._mx][monster[myplr]._my] = 0;
		monster[myplr]._mDelFlag = TRUE;
		DeleteMonsterList();
	}

	for (mi = 0; mi < nummissiles; mi++) {
		am = missileactive[mi];
		if (missile[am]._mitype == MIS_STONE && missile[am]._misource == pnum) {
			monster[missile[am]._miVar2]._mmode = missile[am]._miVar1;
		}
		if (missile[am]._mitype == MIS_MANASHIELD && missile[am]._misource == pnum) {
			ClearMissileSpot(am);
			DeleteMissile(am, mi);
		}
		if (missile[am]._mitype == MIS_ETHEREALIZE && missile[am]._misource == pnum) {
			ClearMissileSpot(am);
			DeleteMissile(am, mi);
		}
	}
}

void __fastcall InitLevelChange(int pnum)
{
	RemovePlrMissiles(pnum);
	if (pnum == myplr && qtextflag) {
		qtextflag = FALSE;
		sfx_stop();
	}

	RemovePlrFromMap(pnum);
	SetPlayerOld(pnum);
	if (pnum == myplr) {
		dPlayer[plr[myplr].WorldX][plr[myplr].WorldY] = myplr + 1;
	} else {
		plr[pnum]._pLvlVisited[plr[pnum].plrlevel] = 1;
	}

	ClrPlrPath(pnum);
	plr[pnum].destAction = ACTION_NONE;
	plr[pnum]._pLvlChanging = 1;

	if (pnum == myplr) {
		plr[pnum].pLvlLoad = 10;
	}
}
// 646D00: using guessed type char qtextflag;

void __fastcall StartNewLvl(int pnum, int fom, int lvl)
{
	InitLevelChange(pnum);

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("StartNewLvl: illegal player %d", pnum);
	}

	switch (fom) {
	case WM_DIABNEXTLVL:
	case WM_DIABPREVLVL:
		plr[pnum].plrlevel = lvl;
		break;
	case WM_DIABRTNLVL:
	case WM_DIABTOWNWARP:
		plr[pnum].plrlevel = lvl;
		break;
	case WM_DIABSETLVL:
		setlvlnum = lvl;
		break;
	case WM_DIABTWARPUP:
		plr[myplr].pTownWarps |= 1 << (leveltype - 2);
		plr[pnum].plrlevel = lvl;
		break;
	case WM_DIABRETOWN:
		break;
	default:
		TermMsg("StartNewLvl");
		break;
	}

	if (pnum == myplr) {
		plr[pnum]._pmode = PM_NEWLVL;
		plr[pnum]._pInvincible = TRUE;
		PostMessage(ghMainWnd, fom, 0, 0);
		if (gbMaxPlayers > 1) {
			NetSendCmdParam2(TRUE, CMD_NEWLVL, fom, lvl);
		}
	}
}
void __fastcall RestartTownLvl(int pnum)
{
	InitLevelChange(pnum);
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("RestartTownLvl: illegal player %d", pnum);
	}

	plr[pnum].plrlevel = 0;
	plr[pnum]._pInvincible = FALSE;

	SetPlayerHitPoints(pnum, 64);

	plr[pnum]._pMana = 0;
	plr[pnum]._pManaBase = plr[pnum]._pMaxManaBase - plr[pnum]._pMaxMana;

	CalcPlrInv(pnum, FALSE);

	if (pnum == myplr) {
		plr[pnum]._pmode = PM_NEWLVL;
		plr[pnum]._pInvincible = TRUE;
		PostMessage(ghMainWnd, WM_DIABRETOWN, 0, 0);
	}
}

void __fastcall StartWarpLvl(int pnum, int pidx)
{
	InitLevelChange(pnum);

	if (gbMaxPlayers != 1) {
		if (plr[pnum].plrlevel != 0) {
			plr[pnum].plrlevel = 0;
		} else {
			plr[pnum].plrlevel = portal[pidx].level;
		}
	}

	if (pnum == myplr) {
		SetCurrentPortal(pidx);
		plr[pnum]._pmode = PM_NEWLVL;
		plr[pnum]._pInvincible = TRUE;
		PostMessage(ghMainWnd, WM_DIABWARPLVL, 0, 0);
	}
}

BOOL __fastcall PM_DoStand(int pnum)
{
	return FALSE;
}

BOOL __fastcall PM_DoWalk(int pnum)
{
	int vel;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoWalk: illegal player %d", pnum);
	}

	if (plr[pnum]._pAnimFrame == 3
	    || (plr[pnum]._pWFrames == 8 && plr[pnum]._pAnimFrame == 7)
	    || (plr[pnum]._pWFrames != 8 && plr[pnum]._pAnimFrame == 4)) {
		PlaySfxLoc(PS_WALK1, plr[pnum].WorldX, plr[pnum].WorldY);
	}

	vel = 8;
	if (currlevel != 0) {
		vel = PWVel[3][plr[pnum]._pClass];
	}

	if (plr[pnum]._pVar8 == vel) {
		dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = 0;
		plr[pnum].WorldX += plr[pnum]._pVar1;
		plr[pnum].WorldY += plr[pnum]._pVar2;
		dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = pnum + 1;

		if (leveltype != DTYPE_TOWN) {
			ChangeLightXY(plr[pnum]._plid, plr[pnum].WorldX, plr[pnum].WorldY);
			ChangeVisionXY(plr[pnum]._pvid, plr[pnum].WorldX, plr[pnum].WorldY);
		}

		if (pnum == myplr && ScrollInfo._sdir) {
			ViewX = plr[pnum].WorldX - ScrollInfo._sdx;
			ViewY = plr[pnum].WorldY - ScrollInfo._sdy;
		}

		if (plr[pnum].walkpath[0] != WALK_NONE) {
			StartWalkStand(pnum);
		} else {
			StartStand(pnum, plr[pnum]._pVar3);
		}

		ClearPlrPVars(pnum);
		if (leveltype != DTYPE_TOWN) {
			ChangeLightOff(plr[pnum]._plid, 0, 0);
		}

		return TRUE;
	}

	PM_ChangeOffset(pnum);
	return FALSE;
}

BOOL __fastcall PM_DoWalk2(int pnum)
{
	int vel;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoWalk2: illegal player %d", pnum);
	}

	if (plr[pnum]._pAnimFrame == 3
	    || (plr[pnum]._pWFrames == 8 && plr[pnum]._pAnimFrame == 7)
	    || (plr[pnum]._pWFrames != 8 && plr[pnum]._pAnimFrame == 4)) {
		PlaySfxLoc(PS_WALK1, plr[pnum].WorldX, plr[pnum].WorldY);
	}

	vel = 8;
	if (currlevel != 0) {
		vel = PWVel[3][plr[pnum]._pClass];
	}

	if (plr[pnum]._pVar8 == vel) {
		dPlayer[plr[pnum]._pVar1][plr[pnum]._pVar2] = 0;
		if (leveltype != DTYPE_TOWN) {
			ChangeLightXY(plr[pnum]._plid, plr[pnum].WorldX, plr[pnum].WorldY);
			ChangeVisionXY(plr[pnum]._pvid, plr[pnum].WorldX, plr[pnum].WorldY);
		}

		if (pnum == myplr && ScrollInfo._sdir) {
			ViewX = plr[pnum].WorldX - ScrollInfo._sdx;
			ViewY = plr[pnum].WorldY - ScrollInfo._sdy;
		}

		if (plr[pnum].walkpath[0] != WALK_NONE) {
			StartWalkStand(pnum);
		} else {
			StartStand(pnum, plr[pnum]._pVar3);
		}

		ClearPlrPVars(pnum);

		if (leveltype != DTYPE_TOWN) {
			ChangeLightOff(plr[pnum]._plid, 0, 0);
		}

		return TRUE;
	}

	PM_ChangeOffset(pnum);
	return FALSE;
}

BOOL __fastcall PM_DoWalk3(int pnum)
{
	int vel;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoWalk3: illegal player %d", pnum);
	}

	if (plr[pnum]._pAnimFrame == 3
	    || (plr[pnum]._pWFrames == 8 && plr[pnum]._pAnimFrame == 7)
	    || (plr[pnum]._pWFrames != 8 && plr[pnum]._pAnimFrame == 4)) {
		PlaySfxLoc(PS_WALK1, plr[pnum].WorldX, plr[pnum].WorldY);
	}

	vel = 8;
	if (currlevel != 0) {
		vel = PWVel[3][plr[pnum]._pClass];
	}

	if (plr[pnum]._pVar8 == vel) {
		dPlayer[plr[pnum].WorldX][plr[pnum].WorldY] = 0;
		dFlags[plr[pnum]._pVar4][plr[pnum]._pVar5] &= ~DFLAG_PLAYER;
		plr[pnum].WorldX = plr[pnum]._pVar1;
		plr[pnum].WorldY = plr[pnum]._pVar2;
		dPlayer[plr[pnum]._pVar1][plr[pnum]._pVar2] = pnum + 1;

		if (leveltype != DTYPE_TOWN) {
			ChangeLightXY(plr[pnum]._plid, plr[pnum]._pVar1, plr[pnum]._pVar2);
			ChangeVisionXY(plr[pnum]._pvid, plr[pnum].WorldX, plr[pnum].WorldY);
		}

		if (pnum == myplr && ScrollInfo._sdir) {
			ViewX = plr[pnum].WorldX - ScrollInfo._sdx;
			ViewY = plr[pnum].WorldY - ScrollInfo._sdy;
		}

		if (plr[pnum].walkpath[0] != WALK_NONE) {
			StartWalkStand(pnum);
		} else {
			StartStand(pnum, plr[pnum]._pVar3);
		}

		ClearPlrPVars(pnum);

		if (leveltype != DTYPE_TOWN) {
			ChangeLightOff(plr[pnum]._plid, 0, 0);
		}

		return TRUE;
	}

	PM_ChangeOffset(pnum);
	return FALSE;
}

BOOL __fastcall WeaponDur(int pnum, int durrnd)
{
	if (pnum != myplr) {
		return FALSE;
	}

	if (random(3, durrnd) != 0) {
		return FALSE;
	}

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("WeaponDur: illegal player %d", pnum);
	}

	if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype != ITYPE_NONE && plr[pnum].InvBody[INVLOC_HAND_LEFT]._iClass == ICLASS_WEAPON) {
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability == DUR_INDESTRUCTIBLE) {
			return FALSE;
		}

		plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability--;
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability == 0) {
			NetSendCmdDelItem(TRUE, INVLOC_HAND_LEFT);
			plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype = ITYPE_NONE;
			CalcPlrInv(pnum, TRUE);
			return TRUE;
		}
	}

	if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype != ITYPE_NONE && plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iClass == ICLASS_WEAPON) {
		if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability == DUR_INDESTRUCTIBLE) {
			return FALSE;
		}

		plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability--;
		if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability == 0) {
			NetSendCmdDelItem(TRUE, INVLOC_HAND_RIGHT);
			plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype = ITYPE_NONE;
			CalcPlrInv(pnum, TRUE);
			return TRUE;
		}
	}

	if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_NONE && plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_SHIELD) {
		if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability == DUR_INDESTRUCTIBLE) {
			return FALSE;
		}

		plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability--;
		if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability == 0) {
			NetSendCmdDelItem(TRUE, INVLOC_HAND_RIGHT);
			plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype = ITYPE_NONE;
			CalcPlrInv(pnum, TRUE);
			return TRUE;
		}
	}

	if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_NONE && plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_SHIELD) {
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability == DUR_INDESTRUCTIBLE) {
			return FALSE;
		}

		plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability--;
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability == 0) {
			NetSendCmdDelItem(TRUE, INVLOC_HAND_LEFT);
			plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype = ITYPE_NONE;
			CalcPlrInv(pnum, TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL __fastcall PlrHitMonst(int pnum, int m)
{
	BOOL rv, ret;
	int hit, hper, mind, maxd, dam, lvl, phanditype, mClass, skdam, tac;

	if ((DWORD)m >= MAXMONSTERS) {
		TermMsg("PlrHitMonst: illegal monster %d", m);
	}

	if ((monster[m]._mhitpoints >> 6) <= 0) {
		return FALSE;
	}

	if (monster[m].MType->mtype == MT_ILLWEAV && monster[m]._mgoal == MGOAL_RETREAT) {
		return FALSE;
	}

	if (monster[m]._mmode == MM_CHARGE) {
		return FALSE;
	}

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PlrHitMonst: illegal player %d", pnum);
	}

	rv = FALSE;

	hit = random(4, 100);
	if (monster[m]._mmode == MM_STONE) {
		hit = 0;
	}

	hper = (plr[pnum]._pDexterity >> 1) + plr[pnum]._pLevel + 50 - (monster[m].mArmorClass - plr[pnum]._pIEnAc);
	if (plr[pnum]._pClass == PC_WARRIOR) {
		hper += 20;
	}
	hper += plr[pnum]._pIBonusToHit;
	if (hper < 5) {
		hper = 5;
	}
	if (hper > 95) {
		hper = 95;
	}

	if (CheckMonsterHit(m, &ret)) {
		return ret;
	}
#ifdef _DEBUG
	if (hit < hper || debug_mode_key_inverted_v || debug_mode_dollar_sign) {
#else
	if (hit < hper) {
#endif
		mind = plr[pnum]._pIMinDam;
		maxd = random(5, plr[pnum]._pIMaxDam - mind + 1);
		dam = maxd + mind;
		dam += plr[pnum]._pDamageMod + plr[pnum]._pIBonusDamMod + dam * plr[pnum]._pIBonusDam / 100;
		if (plr[pnum]._pClass == PC_WARRIOR) {
			lvl = plr[pnum]._pLevel;
			if (random(6, 100) < lvl) {
				dam *= 2;
			}
		}

		phanditype = ITYPE_NONE;
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_SWORD || plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_SWORD) {
			phanditype = ITYPE_SWORD;
		}
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_MACE || plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_MACE) {
			phanditype = ITYPE_MACE;
		}

		mClass = monster[m].MData->mMonstClass;
		switch (mClass) {
		case MC_UNDEAD:
			if (phanditype == ITYPE_SWORD) {
				dam -= dam >> 1;
			}
			if (phanditype == ITYPE_MACE) {
				dam += dam >> 1;
			}
			break;
		case MC_ANIMAL:
			if (phanditype == ITYPE_MACE) {
				dam -= dam >> 1;
			}
			if (phanditype == ITYPE_SWORD) {
				dam += dam >> 1;
			}
			break;
		}

		if (plr[pnum]._pIFlags & ISPL_3XDAMVDEM && monster[m].MData->mMonstClass == MC_DEMON) {
			dam *= 3;
		}

		skdam = dam << 6;
		if (pnum == myplr) {
			monster[m]._mhitpoints -= skdam;
		}

		if (plr[pnum]._pIFlags & ISPL_RNDSTEALLIFE) {
			tac = random(7, skdam >> 3);
			plr[pnum]._pHitPoints += tac;
			if (plr[pnum]._pHitPoints > plr[pnum]._pMaxHP) {
				plr[pnum]._pHitPoints = plr[pnum]._pMaxHP;
			}
			plr[pnum]._pHPBase += tac;
			if (plr[pnum]._pHPBase > plr[pnum]._pMaxHPBase) {
				plr[pnum]._pHPBase = plr[pnum]._pMaxHPBase;
			}
			drawhpflag = TRUE;
		}
		if (plr[pnum]._pIFlags & (ISPL_STEALMANA_3 | ISPL_STEALMANA_5) && !(plr[pnum]._pIFlags & ISPL_NOMANA)) {
			if (plr[pnum]._pIFlags & ISPL_STEALMANA_3) {
				tac = 3 * skdam / 100;
			}
			if (plr[pnum]._pIFlags & ISPL_STEALMANA_5) {
				tac = 5 * skdam / 100;
			}
			plr[pnum]._pMana += tac;
			if (plr[pnum]._pMana > plr[pnum]._pMaxMana) {
				plr[pnum]._pMana = plr[pnum]._pMaxMana;
			}
			plr[pnum]._pManaBase += tac;
			if (plr[pnum]._pManaBase > plr[pnum]._pMaxManaBase) {
				plr[pnum]._pManaBase = plr[pnum]._pMaxManaBase;
			}
			drawmanaflag = TRUE;
		}
		if (plr[pnum]._pIFlags & (ISPL_STEALLIFE_3 | ISPL_STEALLIFE_5)) {
			if (plr[pnum]._pIFlags & ISPL_STEALLIFE_3) {
				tac = 3 * skdam / 100;
			}
			if (plr[pnum]._pIFlags & ISPL_STEALLIFE_5) {
				tac = 5 * skdam / 100;
			}
			plr[pnum]._pHitPoints += tac;
			if (plr[pnum]._pHitPoints > plr[pnum]._pMaxHP) {
				plr[pnum]._pHitPoints = plr[pnum]._pMaxHP;
			}
			plr[pnum]._pHPBase += tac;
			if (plr[pnum]._pHPBase > plr[pnum]._pMaxHPBase) {
				plr[pnum]._pHPBase = plr[pnum]._pMaxHPBase;
			}
			drawhpflag = TRUE;
		}
		if (plr[pnum]._pIFlags & ISPL_NOHEALPLR) {
			monster[m]._mFlags |= MFLAG_NOHEAL;
		}
#ifdef _DEBUG
		if (debug_mode_dollar_sign || debug_mode_key_inverted_v) {
			monster[m]._mhitpoints = 0; /* double check */
		}
#endif
		if ((monster[m]._mhitpoints >> 6) <= 0) {
			if (monster[m]._mmode == MM_STONE) {
				M_StartKill(m, pnum);
				monster[m]._mmode = MM_STONE;
			} else {
				M_StartKill(m, pnum);
			}
		} else {
			if (monster[m]._mmode == MM_STONE) {
				M_StartHit(m, pnum, skdam);
				monster[m]._mmode = MM_STONE;
			} else {
				if (plr[pnum]._pIFlags & ISPL_KNOCKBACK) {
					M_GetKnockback(m);
				}
				M_StartHit(m, pnum, skdam);
			}
		}
		rv = TRUE;
	}

	return rv;
}

BOOL __fastcall PlrHitPlr(int pnum, char p)
{
	BOOL rv;
	int hit, hper, blk, blkper, dir, mind, maxd, dam, lvl, skdam, tac;

	if ((DWORD)p >= MAX_PLRS) {
		TermMsg("PlrHitPlr: illegal target player %d", p);
	}

	rv = FALSE;

	if (plr[p]._pInvincible) {
		return rv;
	}

	if (plr[p]._pSpellFlags & 1) {
		return rv;
	}

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PlrHitPlr: illegal attacking player %d", pnum);
	}

	hit = random(4, 100);

	hper = (plr[pnum]._pDexterity >> 1) + plr[pnum]._pLevel + 50 - (plr[p]._pIBonusAC + plr[p]._pIAC + plr[p]._pDexterity / 5);

	if (plr[pnum]._pClass == PC_WARRIOR) {
		hper += 20;
	}
	hper += plr[pnum]._pIBonusToHit;
	if (hper < 5) {
		hper = 5;
	}
	if (hper > 95) {
		hper = 95;
	}

	if ((plr[p]._pmode == PM_STAND || plr[p]._pmode == PM_ATTACK) && plr[p]._pBlockFlag) {
		blk = random(5, 100);
	} else {
		blk = 100;
	}

	blkper = plr[p]._pDexterity + plr[p]._pBaseToBlk + (plr[p]._pLevel << 1) - (plr[pnum]._pLevel << 1);
	if (blkper < 0) {
		blkper = 0;
	}
	if (blkper > 100) {
		blkper = 100;
	}

	if (hit < hper) {
		if (blk < blkper) {
			dir = GetDirection(plr[p].WorldX, plr[p].WorldY, plr[pnum].WorldX, plr[pnum].WorldY);
			StartPlrBlock(p, dir);
		} else {
			mind = plr[pnum]._pIMinDam;
			maxd = random(5, plr[pnum]._pIMaxDam - mind + 1);
			dam = maxd + mind;
			dam += plr[pnum]._pDamageMod + plr[pnum]._pIBonusDamMod + dam * plr[pnum]._pIBonusDam / 100;

			if (plr[pnum]._pClass == PC_WARRIOR) {
				lvl = plr[pnum]._pLevel;
				if (random(6, 100) < lvl) {
					dam *= 2;
				}
			}
			skdam = dam << 6;
			if (plr[pnum]._pIFlags & ISPL_RNDSTEALLIFE) {
				tac = random(7, skdam >> 3);
				plr[pnum]._pHitPoints += tac;
				if (plr[pnum]._pHitPoints > plr[pnum]._pMaxHP) {
					plr[pnum]._pHitPoints = plr[pnum]._pMaxHP;
				}
				plr[pnum]._pHPBase += tac;
				if (plr[pnum]._pHPBase > plr[pnum]._pMaxHPBase) {
					plr[pnum]._pHPBase = plr[pnum]._pMaxHPBase;
				}
				drawhpflag = TRUE;
			}
			if (pnum == myplr) {
				NetSendCmdDamage(TRUE, p, skdam);
			}
			StartPlrHit(p, skdam, FALSE);
		}

		rv = TRUE;
	}

	return rv;
}

BOOL __fastcall PlrHitObj(int pnum, int mx, int my)
{
	int oi;

	if (dObject[mx][my] > 0) {
		oi = dObject[mx][my] - 1;
	} else {
		oi = -dObject[mx][my] - 1;
	}

	if (object[oi]._oBreak == 1) {
		BreakObject(pnum, oi);
		return TRUE;
	}

	return FALSE;
}

BOOL __fastcall PM_DoAttack(int pnum)
{
	int frame, dir, dx, dy, m;
	BOOL didhit;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoAttack: illegal player %d", pnum);
	}

	frame = plr[pnum]._pAnimFrame;
	if (plr[pnum]._pIFlags & ISPL_QUICKATTACK && frame == 1) {
		plr[pnum]._pAnimFrame++;
	}
	if (plr[pnum]._pIFlags & ISPL_FASTATTACK && (frame == 1 || frame == 3)) {
		plr[pnum]._pAnimFrame++;
	}
	if (plr[pnum]._pIFlags & ISPL_FASTERATTACK && (frame == 1 || frame == 3 || frame == 5)) {
		plr[pnum]._pAnimFrame++;
	}
	if (plr[pnum]._pIFlags & ISPL_FASTESTATTACK && (frame == 1 || frame == 4)) {
		plr[pnum]._pAnimFrame += 2;
	}
	if (plr[pnum]._pAnimFrame == plr[pnum]._pAFNum - 1) {
		PlaySfxLoc(PS_SWING, plr[pnum].WorldX, plr[pnum].WorldY);
	}

	if (plr[pnum]._pAnimFrame == plr[pnum]._pAFNum) {
		dir = plr[pnum]._pdir;
		dx = plr[pnum].WorldX + offset_x[dir];
		dy = plr[pnum].WorldY + offset_y[dir];

		if (dMonster[dx][dy]) {
			if (dMonster[dx][dy] > 0) {
				m = dMonster[dx][dy] - 1;
			} else {
				m = -(dMonster[dx][dy] + 1);
			}
			if (CanTalkToMonst(m)) {
				plr[pnum]._pVar1 = 0;
				return FALSE;
			}
		}

		if (plr[pnum]._pIFlags & ISPL_FIREDAM) {
			AddMissile(dx, dy, 1, 0, 0, MIS_WEAPEXP, 0, pnum, 0, 0);
		}
		if (plr[pnum]._pIFlags & ISPL_LIGHTDAM) {
			AddMissile(dx, dy, 2, 0, 0, MIS_WEAPEXP, 0, pnum, 0, 0);
		}

		didhit = FALSE;
		if (dMonster[dx][dy]) {
			m = dMonster[dx][dy];
			if (dMonster[dx][dy] > 0) {
				m = dMonster[dx][dy] - 1;
			} else {
				m = -(dMonster[dx][dy] + 1);
			}
			didhit = PlrHitMonst(pnum, m);
		} else if (dPlayer[dx][dy] && !FriendlyMode) {
			UCHAR p = dPlayer[dx][dy];
			if (dPlayer[dx][dy] > 0) {
				p = dPlayer[dx][dy] - 1;
			} else {
				p = -(dPlayer[dx][dy] + 1);
			}
			didhit = PlrHitPlr(pnum, p);
		} else if (dObject[dx][dy] > 0) {
			didhit = PlrHitObj(pnum, dx, dy);
		}

		if (didhit && WeaponDur(pnum, 30)) {
			StartStand(pnum, plr[pnum]._pdir);
			ClearPlrPVars(pnum);
			return TRUE;
		}
	}

	if (plr[pnum]._pAnimFrame == plr[pnum]._pAFrames) {
		StartStand(pnum, plr[pnum]._pdir);
		ClearPlrPVars(pnum);
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL __fastcall PM_DoRangeAttack(int pnum)
{
	int origFrame, mistype;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoRangeAttack: illegal player %d", pnum);
	}

	origFrame = plr[pnum]._pAnimFrame;
	if (plr[pnum]._pIFlags & ISPL_QUICKATTACK && origFrame == 1) {
		plr[pnum]._pAnimFrame++;
	}
	if (plr[pnum]._pIFlags & ISPL_FASTATTACK && (origFrame == 1 || origFrame == 3)) {
		plr[pnum]._pAnimFrame++;
	}

	if (plr[pnum]._pAnimFrame == plr[pnum]._pAFNum) {
		mistype = MIS_ARROW;
		if (plr[pnum]._pIFlags & ISPL_FIRE_ARROWS) {
			mistype = MIS_FARROW;
		}
		if (plr[pnum]._pIFlags & ISPL_LIGHT_ARROWS) {
			mistype = MIS_LARROW;
		}
		AddMissile(
		    plr[pnum].WorldX,
		    plr[pnum].WorldY,
		    plr[pnum]._pVar1,
		    plr[pnum]._pVar2,
		    plr[pnum]._pdir,
		    mistype,
		    0,
		    pnum,
		    4,
		    0);

		PlaySfxLoc(PS_BFIRE, plr[pnum].WorldX, plr[pnum].WorldY);

		if (WeaponDur(pnum, 40)) {
			StartStand(pnum, plr[pnum]._pdir);
			ClearPlrPVars(pnum);
			return TRUE;
		}
	}

	if (plr[pnum]._pAnimFrame >= plr[pnum]._pAFrames) {
		StartStand(pnum, plr[pnum]._pdir);
		ClearPlrPVars(pnum);
		return TRUE;
	} else {
		return FALSE;
	}
}

void __fastcall ShieldDur(int pnum)
{
	if (pnum != myplr) {
		return;
	}

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ShieldDur: illegal player %d", pnum);
	}

	if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_SHIELD) {
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability == DUR_INDESTRUCTIBLE) {
			return;
		}

		plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability--;
		if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iDurability == 0) {
			NetSendCmdDelItem(TRUE, INVLOC_HAND_LEFT);
			plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype = ITYPE_NONE;
			CalcPlrInv(pnum, TRUE);
		}
	}

	if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_SHIELD) {
		if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability != DUR_INDESTRUCTIBLE) {
			plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability--;
			if (plr[pnum].InvBody[INVLOC_HAND_RIGHT]._iDurability == 0) {
				NetSendCmdDelItem(TRUE, INVLOC_HAND_RIGHT);
				plr[pnum].InvBody[INVLOC_HAND_RIGHT]._itype = ITYPE_NONE;
				CalcPlrInv(pnum, TRUE);
			}
		}
	}
}

BOOL __fastcall PM_DoBlock(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoBlock: illegal player %d", pnum);
	}

	if (plr[pnum]._pIFlags & ISPL_FASTBLOCK && plr[pnum]._pAnimFrame != 1) {
		plr[pnum]._pAnimFrame = plr[pnum]._pBFrames;
	}

	if (plr[pnum]._pAnimFrame >= plr[pnum]._pBFrames) {
		StartStand(pnum, plr[pnum]._pdir);
		ClearPlrPVars(pnum);

		if (!random(3, 10)) {
			ShieldDur(pnum);
		}
		return TRUE;
	}

	return FALSE;
}

BOOL __fastcall PM_DoSpell(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoSpell: illegal player %d", pnum);
	}

	if (plr[pnum]._pVar8 == plr[pnum]._pSFNum) {
		CastSpell(
		    pnum,
		    plr[pnum]._pSpell,
		    plr[pnum].WorldX,
		    plr[pnum].WorldY,
		    plr[pnum]._pVar1,
		    plr[pnum]._pVar2,
		    FALSE,
		    plr[pnum]._pVar4);

		if (!plr[pnum]._pSplFrom) {
			if (plr[pnum]._pRSplType == RSPLTYPE_SCROLL) {
				if (!(plr[pnum]._pScrlSpells
				        & (unsigned __int64)1 << (plr[pnum]._pRSpell - 1))) {
					plr[pnum]._pRSpell = SPL_INVALID;
					plr[pnum]._pRSplType = RSPLTYPE_INVALID;
					drawpanflag = 255;
				}
			}

			if (plr[pnum]._pRSplType == RSPLTYPE_CHARGES) {
				if (!(plr[pnum]._pISpells
				        & (unsigned __int64)1 << (plr[pnum]._pRSpell - 1))) {
					plr[pnum]._pRSpell = SPL_INVALID;
					plr[pnum]._pRSplType = RSPLTYPE_INVALID;
					drawpanflag = 255;
				}
			}
		}
	}

	plr[pnum]._pVar8++;

	if (leveltype == DTYPE_TOWN) {
		if (plr[pnum]._pVar8 > plr[pnum]._pSFrames) {
			StartWalkStand(pnum);
			ClearPlrPVars(pnum);
			return TRUE;
		}
	} else if (plr[pnum]._pAnimFrame == plr[pnum]._pSFrames) {
		StartStand(pnum, plr[pnum]._pdir);
		ClearPlrPVars(pnum);
		return TRUE;
	}

	return FALSE;
}
// 52571C: using guessed type int drawpanflag;

BOOL __fastcall PM_DoGotHit(int pnum)
{
	int frame;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoGotHit: illegal player %d", pnum);
	}

	frame = plr[pnum]._pAnimFrame;
	if (plr[pnum]._pIFlags & ISPL_FASTRECOVER && frame == 3) {
		plr[pnum]._pAnimFrame++;
	}
	if (plr[pnum]._pIFlags & ISPL_FASTERRECOVER && (frame == 3 || frame == 5)) {
		plr[pnum]._pAnimFrame++;
	}
	if (plr[pnum]._pIFlags & ISPL_FASTESTRECOVER && (frame == 1 || frame == 3 || frame == 5)) {
		plr[pnum]._pAnimFrame++;
	}

	if (plr[pnum]._pAnimFrame >= plr[pnum]._pHFrames) {
		StartStand(pnum, plr[pnum]._pdir);
		ClearPlrPVars(pnum);
		if (random(3, 4)) {
			ArmorDur(pnum);
		}

		return TRUE;
	}

	return FALSE;
}

void __fastcall ArmorDur(int pnum)
{
	int a;
	ItemStruct *pi;
	PlayerStruct *p;

	if (pnum != myplr) {
		return;
	}

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ArmorDur: illegal player %d", pnum);
	}

	p = &plr[pnum];
	if (p->InvBody[INVLOC_CHEST]._itype == ITYPE_NONE && p->InvBody[INVLOC_HEAD]._itype == ITYPE_NONE) {
		return;
	}

	a = random(8, 3);
	if (p->InvBody[INVLOC_CHEST]._itype != ITYPE_NONE && p->InvBody[INVLOC_HEAD]._itype == ITYPE_NONE) {
		a = 1;
	}
	if (p->InvBody[INVLOC_CHEST]._itype == ITYPE_NONE && p->InvBody[INVLOC_HEAD]._itype != ITYPE_NONE) {
		a = 0;
	}

	if (a != 0) {
		pi = &p->InvBody[INVLOC_CHEST];
	} else {
		pi = &p->InvBody[INVLOC_HEAD];
	}
	if (pi->_iDurability == DUR_INDESTRUCTIBLE) {
		return;
	}

	pi->_iDurability--;
	if (pi->_iDurability != 0) {
		return;
	}

	if (a != 0) {
		NetSendCmdDelItem(TRUE, INVLOC_CHEST);
	} else {
		NetSendCmdDelItem(TRUE, INVLOC_HEAD);
	}
	pi->_itype = ITYPE_NONE;
	CalcPlrInv(pnum, TRUE);
}

BOOL __fastcall PM_DoDeath(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PM_DoDeath: illegal player %d", pnum);
	}

	if (plr[pnum]._pVar8 >= 2 * plr[pnum]._pDFrames) {
		if (deathdelay > 1 && pnum == myplr) {
			deathdelay--;
			if (deathdelay) {
				deathflag = TRUE;
				if (gbMaxPlayers == 1) {
					gamemenu_previous();
				}
			}
		}

		plr[pnum]._pAnimFrame = plr[pnum]._pAnimLen;
		plr[pnum]._pAnimDelay = 10000;
		dFlags[plr[pnum].WorldX][plr[pnum].WorldY] |= DFLAG_DEAD_PLAYER;
	}

	if (plr[pnum]._pVar8 < 100) {
		plr[pnum]._pVar8++;
	}

	return FALSE;
}
// 69B7C4: using guessed type int deathdelay;

BOOL __fastcall PM_DoNewLvl(int pnum)
{
	return FALSE;
}

void __fastcall CheckNewPath(int pnum)
{
	int i, x, y, d;
	int xvel3, xvel, yvel;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("CheckNewPath: illegal player %d", pnum);
	}

	if (plr[pnum].destAction == ACTION_ATTACKMON) {
		MakePlrPath(pnum, monster[plr[pnum].destParam1]._mfutx, monster[plr[pnum].destParam1]._mfuty, FALSE);
	}

	if (plr[pnum].destAction == ACTION_ATTACKPLR) {
		MakePlrPath(pnum, plr[plr[pnum].destParam1]._px, plr[plr[pnum].destParam1]._py, FALSE);
	}

	if (plr[pnum].walkpath[0] != WALK_NONE) {
		if (plr[pnum]._pmode == PM_STAND) {
			if (pnum == myplr) {
				if (plr[pnum].destAction == ACTION_ATTACKMON || plr[pnum].destAction == ACTION_ATTACKPLR) {
					i = plr[pnum].destParam1;

					if (plr[pnum].destAction == ACTION_ATTACKMON) {
						x = abs(plr[pnum]._px - monster[i]._mfutx);
						y = abs(plr[pnum]._py - monster[i]._mfuty);
						d = GetDirection(plr[pnum]._px, plr[pnum]._py, monster[i]._mfutx, monster[i]._mfuty);
					} else {
						x = abs(plr[pnum]._px - plr[i]._px);
						y = abs(plr[pnum]._py - plr[i]._py);
						d = GetDirection(plr[pnum]._px, plr[pnum]._py, plr[i]._px, plr[i]._py);
					}

					if (x < 2 && y < 2) {
						ClrPlrPath(pnum);
						if (monster[i].mtalkmsg && monster[i].mtalkmsg != QUEST_VILE14) {
							TalktoMonster(i);
						} else {
							StartAttack(pnum, d);
						}
						plr[pnum].destAction = ACTION_NONE;
					}
				}
			}

			if (currlevel != 0) {
				xvel3 = PWVel[plr[pnum]._pClass][0];
				xvel = PWVel[plr[pnum]._pClass][1];
				yvel = PWVel[plr[pnum]._pClass][2];
			} else {
				xvel3 = 2048;
				xvel = 1024;
				yvel = 512;
			}

			switch (plr[pnum].walkpath[0]) {
			case WALK_N:
				StartWalk(pnum, 0, -xvel, -1, -1, DIR_N, SDIR_N);
				break;
			case WALK_NE:
				StartWalk(pnum, xvel, -yvel, 0, -1, DIR_NE, SDIR_NE);
				break;
			case WALK_E:
				StartWalk3(pnum, xvel3, 0, -32, -16, 1, -1, 1, 0, DIR_E, SDIR_E);
				break;
			case WALK_SE:
				StartWalk2(pnum, xvel, yvel, -32, -16, 1, 0, DIR_SE, SDIR_SE);
				break;
			case WALK_S:
				StartWalk2(pnum, 0, xvel, 0, -32, 1, 1, DIR_S, SDIR_S);
				break;
			case WALK_SW:
				StartWalk2(pnum, -xvel, yvel, 32, -16, 0, 1, DIR_SW, SDIR_SW);
				break;
			case WALK_W:
				StartWalk3(pnum, -xvel3, 0, 32, -16, -1, 1, 0, 1, DIR_W, SDIR_W);
				break;
			case WALK_NW:
				StartWalk(pnum, -xvel, -yvel, -1, 0, DIR_NW, SDIR_NW);
				break;
			}

			for (i = 1; i < 25; i++) {
				plr[pnum].walkpath[i - 1] = plr[pnum].walkpath[i];
			}

			plr[pnum].walkpath[24] = WALK_NONE;

			if (plr[pnum]._pmode == PM_STAND) {
				StartStand(pnum, plr[pnum]._pdir);
				plr[pnum].destAction = ACTION_NONE;
			}
		}

		return;
	}
	if (plr[pnum].destAction == ACTION_NONE) {
		return;
	}

	if (plr[pnum]._pmode == PM_STAND) {
		switch (plr[pnum].destAction) {
		case ACTION_ATTACK:
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum].destParam1, plr[pnum].destParam2);
			StartAttack(pnum, d);
			break;
		case ACTION_ATTACKMON:
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - monster[i]._mfutx);
			y = abs(plr[pnum].WorldY - monster[i]._mfuty);
			if (x <= 1 && y <= 1) {
				d = GetDirection(plr[pnum]._px, plr[pnum]._py, monster[i]._mfutx, monster[i]._mfuty);
				if (monster[i].mtalkmsg && monster[i].mtalkmsg != QUEST_VILE14) {
					TalktoMonster(i);
				} else {
					StartAttack(pnum, d);
				}
			}
			break;
		case ACTION_ATTACKPLR:
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - plr[i]._px);
			y = abs(plr[pnum].WorldY - plr[i]._py);
			if (x <= 1 && y <= 1) {
				d = GetDirection(plr[pnum]._px, plr[pnum]._py, plr[i]._px, plr[i]._py);
				StartAttack(pnum, d);
			}
			break;
		case ACTION_RATTACK:
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum].destParam1, plr[pnum].destParam2);
			StartRangeAttack(pnum, d, plr[pnum].destParam1, plr[pnum].destParam2);
			break;
		case ACTION_RATTACKMON:
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum]._px, plr[pnum]._py, monster[i]._mfutx, monster[i]._mfuty);
			if (monster[i].mtalkmsg && monster[i].mtalkmsg != QUEST_VILE14) {
				TalktoMonster(i);
			} else {
				StartRangeAttack(pnum, d, monster[i]._mfutx, monster[i]._mfuty);
			}
			break;
		case ACTION_RATTACKPLR:
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum]._px, plr[pnum]._py, plr[i]._px, plr[i]._py);
			StartRangeAttack(pnum, d, plr[i]._px, plr[i]._py);
			break;
		case ACTION_SPELL:
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum].destParam1, plr[pnum].destParam2);
			StartSpell(pnum, d, plr[pnum].destParam1, plr[pnum].destParam2);
			plr[pnum]._pVar4 = plr[pnum].destParam3;
			break;
		case ACTION_SPELLWALL:
			StartSpell(pnum, plr[pnum].destParam3, plr[pnum].destParam1, plr[pnum].destParam2);
			plr[pnum]._pVar3 = plr[pnum].destParam3;
			plr[pnum]._pVar4 = plr[pnum].destParam4;
			break;
		case ACTION_SPELLMON:
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, monster[i]._mfutx, monster[i]._mfuty);
			StartSpell(pnum, d, monster[i]._mfutx, monster[i]._mfuty);
			plr[pnum]._pVar4 = plr[pnum].destParam2;
			break;
		case ACTION_SPELLPLR:
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[i]._px, plr[i]._py);
			StartSpell(pnum, d, plr[i]._px, plr[i]._py);
			plr[pnum]._pVar4 = plr[pnum].destParam2;
			break;
		case ACTION_OPERATE:
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - object[i]._ox);
			y = abs(plr[pnum].WorldY - object[i]._oy);
			if (y > 1 && dObject[object[i]._ox][object[i]._oy - 1] == -1 - i) {
				y = abs(plr[pnum].WorldY - object[i]._oy + 1);
			}
			if (x <= 1 && y <= 1) {
				if (object[i]._oBreak == 1) {
					d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, object[i]._ox, object[i]._oy);
					StartAttack(pnum, d);
				} else {
					OperateObject(pnum, i, FALSE);
				}
			}
			break;
		case ACTION_DISARM:
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - object[i]._ox);
			y = abs(plr[pnum].WorldY - object[i]._oy);
			if (y > 1 && dObject[object[i]._ox][object[i]._oy - 1] == -1 - i) {
				y = abs(plr[pnum].WorldY - object[i]._oy + 1);
			}
			if (x <= 1 && y <= 1) {
				if (object[i]._oBreak == 1) {
					d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, object[i]._ox, object[i]._oy);
					StartAttack(pnum, d);
				} else {
					TryDisarm(pnum, i);
					OperateObject(pnum, i, FALSE);
				}
			}
			break;
		case ACTION_OPERATETK:
			i = plr[pnum].destParam1;
			if (object[i]._oBreak != 1) {
				OperateObject(pnum, i, TRUE);
			}
			break;
		case ACTION_PICKUPITEM:
			if (pnum == myplr) {
				i = plr[pnum].destParam1;
				x = abs(plr[pnum].WorldX - item[i]._ix);
				y = abs(plr[pnum].WorldY - item[i]._iy);
				if (x <= 1 && y <= 1 && pcurs == 1 && !item[i]._iRequest) {
					NetSendCmdGItem(TRUE, CMD_REQUESTGITEM, myplr, myplr, i);
					item[i]._iRequest = TRUE;
				}
			}
			break;
		case ACTION_PICKUPAITEM:
			if (pnum == myplr) {
				i = plr[pnum].destParam1;
				x = abs(plr[pnum].WorldX - item[i]._ix);
				y = abs(plr[pnum].WorldY - item[i]._iy);
				if (x <= 1 && y <= 1 && pcurs == 1) {
					NetSendCmdGItem(TRUE, CMD_REQUESTAGITEM, myplr, myplr, i);
				}
			}
			break;
		case ACTION_TALK:
			if (pnum == myplr) {
				TalkToTowner(pnum, plr[pnum].destParam1);
			}
			break;
		}

		FixPlayerLocation(pnum, plr[pnum]._pdir);
		plr[pnum].destAction = ACTION_NONE;

		return;
	}

	if (plr[pnum]._pmode == PM_ATTACK && plr[pnum]._pAnimFrame > plr[myplr]._pAFNum) {
		if (plr[pnum].destAction == ACTION_ATTACK) {
			d = GetDirection(plr[pnum]._px, plr[pnum]._py, plr[pnum].destParam1, plr[pnum].destParam2);
			StartAttack(pnum, d);
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_ATTACKMON) {
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - monster[i]._mfutx);
			y = abs(plr[pnum].WorldY - monster[i]._mfuty);
			if (x <= 1 && y <= 1) {
				d = GetDirection(plr[pnum]._px, plr[pnum]._py, monster[i]._mfutx, monster[i]._mfuty);
				StartAttack(pnum, d);
			}
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_ATTACKPLR) {
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - plr[i]._px);
			y = abs(plr[pnum].WorldY - plr[i]._py);
			if (x <= 1 && y <= 1) {
				d = GetDirection(plr[pnum]._px, plr[pnum]._py, plr[i]._px, plr[i]._py);
				StartAttack(pnum, d);
			}
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_OPERATE) {
			i = plr[pnum].destParam1;
			x = abs(plr[pnum].WorldX - object[i]._ox);
			y = abs(plr[pnum].WorldY - object[i]._oy);
			if (y > 1 && dObject[object[i]._ox][object[i]._oy - 1] == -1 - i) {
				y = abs(plr[pnum].WorldY - object[i]._oy + 1);
			}
			if (x <= 1 && y <= 1) {
				if (object[i]._oBreak == 1) {
					d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, object[i]._ox, object[i]._oy);
					StartAttack(pnum, d);
				} else {
					OperateObject(pnum, i, FALSE);
				}
			}
		}
	}

	if (plr[pnum]._pmode == PM_RATTACK && plr[pnum]._pAnimFrame > plr[myplr]._pAFNum) {
		if (plr[pnum].destAction == ACTION_RATTACK) {
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum].destParam1, plr[pnum].destParam2);
			StartRangeAttack(pnum, d, plr[pnum].destParam1, plr[pnum].destParam2);
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_RATTACKMON) {
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, monster[i]._mfutx, monster[i]._mfuty);
			StartRangeAttack(pnum, d, monster[i]._mfutx, monster[i]._mfuty);
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_RATTACKPLR) {
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[i]._px, plr[i]._py);
			StartRangeAttack(pnum, d, plr[i]._px, plr[i]._py);
			plr[pnum].destAction = ACTION_NONE;
		}
	}

	if (plr[pnum]._pmode == PM_SPELL && plr[pnum]._pAnimFrame > plr[pnum]._pSFNum) {
		if (plr[pnum].destAction == ACTION_SPELL) {
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum].destParam1, plr[pnum].destParam2);
			StartSpell(pnum, d, plr[pnum].destParam1, plr[pnum].destParam2);
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_SPELLMON) {
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, monster[i]._mfutx, monster[i]._mfuty);
			StartSpell(pnum, d, monster[i]._mfutx, monster[i]._mfuty);
			plr[pnum].destAction = ACTION_NONE;
		} else if (plr[pnum].destAction == ACTION_SPELLPLR) {
			i = plr[pnum].destParam1;
			d = GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, plr[i]._px, plr[i]._py);
			StartSpell(pnum, d, plr[i]._px, plr[i]._py);
			plr[pnum].destAction = ACTION_NONE;
		}
	}
}

BOOL __fastcall PlrDeathModeOK(int pnum)
{
	if (pnum != myplr) {
		return TRUE;
	}

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("PlrDeathModeOK: illegal player %d", pnum);
	}

	if (plr[pnum]._pmode == PM_DEATH) {
		return TRUE;
	} else if (plr[pnum]._pmode == PM_QUIT) {
		return TRUE;
	} else if (plr[pnum]._pmode == PM_NEWLVL) {
		return TRUE;
	}

	return FALSE;
}

void __cdecl ValidatePlayer()
{
	__int64 msk;
	int gt, pc, i, b;

	msk = 0;

	if ((DWORD)myplr >= MAX_PLRS) {
		TermMsg("ValidatePlayer: illegal player %d", myplr);
	}
	if (plr[myplr]._pLevel > 50)
		plr[myplr]._pLevel = 50;
	if (plr[myplr]._pExperience > plr[myplr]._pNextExper)
		plr[myplr]._pExperience = plr[myplr]._pNextExper;

	gt = 0;
	for (i = 0; i < plr[myplr]._pNumInv; i++) {
		if (plr[myplr].InvList[i]._itype == ITYPE_GOLD) {
			if (plr[myplr].InvList[i]._ivalue > 5000) {
				plr[myplr].InvList[i]._ivalue = 5000;
			}
			gt += plr[myplr].InvList[i]._ivalue;
		}
	}
	if (gt != plr[myplr]._pGold)
		plr[myplr]._pGold = gt;

	pc = plr[myplr]._pClass;
	if (plr[myplr]._pBaseStr > MaxStats[pc][ATTRIB_STR]) {
		plr[myplr]._pBaseStr = MaxStats[pc][ATTRIB_STR];
	}
	if (plr[myplr]._pBaseMag > MaxStats[pc][ATTRIB_MAG]) {
		plr[myplr]._pBaseMag = MaxStats[pc][ATTRIB_MAG];
	}
	if (plr[myplr]._pBaseDex > MaxStats[pc][ATTRIB_DEX]) {
		plr[myplr]._pBaseDex = MaxStats[pc][ATTRIB_DEX];
	}
	if (plr[myplr]._pBaseVit > MaxStats[pc][ATTRIB_VIT]) {
		plr[myplr]._pBaseVit = MaxStats[pc][ATTRIB_VIT];
	}

	for (b = 1; b < MAX_SPELLS; b++) {
		if (spelldata[b].sBookLvl != -1) {
			msk |= (__int64)1 << (b - 1);
			if (plr[myplr]._pSplLvl[b] > 15)
				plr[myplr]._pSplLvl[b] = 15;
		}
	}

	plr[myplr]._pMemSpells &= msk;
}

void __cdecl ProcessPlayers()
{
	int pnum;
	BOOL tplayer;

	if ((DWORD)myplr >= MAX_PLRS) {
		TermMsg("ProcessPlayers: illegal player %d", myplr);
	}

	if (plr[myplr].pLvlLoad > 0) {
		plr[myplr].pLvlLoad--;
	}

	if (sfxdelay > 0) {
		sfxdelay--;
		if (sfxdelay == 0) {
			PlaySFX(sfxdnum);
		}
	}

	ValidatePlayer();

	for (pnum = 0; pnum < MAX_PLRS; pnum++) {
		if (plr[pnum].plractive && currlevel == plr[pnum].plrlevel && (pnum == myplr || !plr[pnum]._pLvlChanging)) {
			CheckCheatStats(pnum);

			if (!PlrDeathModeOK(pnum) && (plr[pnum]._pHitPoints >> 6) <= 0) {
				SyncPlrKill(pnum, -1);
			}

			if (pnum == myplr) {
				if ((plr[pnum]._pIFlags & ISPL_DRAINLIFE) && currlevel != 0) {
					plr[pnum]._pHitPoints -= 4;
					plr[pnum]._pHPBase -= 4;
					if ((plr[pnum]._pHitPoints >> 6) <= 0) {
						SyncPlrKill(pnum, 0);
					}
					drawhpflag = TRUE;
				}
				if (plr[pnum]._pIFlags & ISPL_NOMANA && plr[pnum]._pManaBase > 0) {
					plr[pnum]._pManaBase -= plr[pnum]._pMana;
					plr[pnum]._pMana = 0;
					drawmanaflag = TRUE;
				}
			}

			tplayer = FALSE;
			do {
				switch (plr[pnum]._pmode) {
				case PM_STAND:
					tplayer = PM_DoStand(pnum);
					break;
				case PM_WALK:
					tplayer = PM_DoWalk(pnum);
					break;
				case PM_WALK2:
					tplayer = PM_DoWalk2(pnum);
					break;
				case PM_WALK3:
					tplayer = PM_DoWalk3(pnum);
					break;
				case PM_ATTACK:
					tplayer = PM_DoAttack(pnum);
					break;
				case PM_RATTACK:
					tplayer = PM_DoRangeAttack(pnum);
					break;
				case PM_BLOCK:
					tplayer = PM_DoBlock(pnum);
					break;
				case PM_SPELL:
					tplayer = PM_DoSpell(pnum);
					break;
				case PM_GOTHIT:
					tplayer = PM_DoGotHit(pnum);
					break;
				case PM_DEATH:
					tplayer = PM_DoDeath(pnum);
					break;
				case PM_NEWLVL:
					tplayer = PM_DoNewLvl(pnum);
					break;
				}
				CheckNewPath(pnum);
			} while (tplayer);

			plr[pnum]._pAnimCnt++;
			if (plr[pnum]._pAnimCnt > plr[pnum]._pAnimDelay) {
				plr[pnum]._pAnimCnt = 0;
				plr[pnum]._pAnimFrame++;
				if (plr[pnum]._pAnimFrame > plr[pnum]._pAnimLen) {
					plr[pnum]._pAnimFrame = 1;
				}
			}
		}
	}
}
// 52A554: using guessed type int sfxdelay;

void __fastcall CheckCheatStats(int pnum)
{
	if (plr[pnum]._pStrength > 750) {
		plr[pnum]._pStrength = 750;
	}

	if (plr[pnum]._pDexterity > 750) {
		plr[pnum]._pDexterity = 750;
	}

	if (plr[pnum]._pMagic > 750) {
		plr[pnum]._pMagic = 750;
	}

	if (plr[pnum]._pVitality > 750) {
		plr[pnum]._pVitality = 750;
	}

	if (plr[pnum]._pHitPoints > 128000) {
		plr[pnum]._pHitPoints = 128000;
	}

	if (plr[pnum]._pMana > 128000) {
		plr[pnum]._pMana = 128000;
	}
}

void __fastcall ClrPlrPath(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ClrPlrPath: illegal player %d", pnum);
	}

	memset(plr[pnum].walkpath, WALK_NONE, sizeof(plr[pnum].walkpath));
}

BOOL __fastcall PosOkPlayer(int pnum, int px, int py)
{
	BOOL PosOK;
	DWORD p;
	char bv;

	PosOK = FALSE;
	if (px >= 0 && px < MAXDUNX && py >= 0 && py < MAXDUNY && !SolidLoc(px, py) && dPiece[px][py]) {

		if (dPlayer[px][py]) {
			if (dPlayer[px][py] > 0) {
				p = dPlayer[px][py] - 1;
			} else {
				p = -(dPlayer[px][py] + 1);
			}
			if (p != pnum && p < MAX_PLRS && plr[p]._pHitPoints) {
				return FALSE;
			}
		}

		if (dMonster[px][py]) {
			if (currlevel == 0) {
				return FALSE;
			}
			if (dMonster[px][py] <= 0) {
				return FALSE;
			}
			if ((monster[dMonster[px][py] - 1]._mhitpoints >> 6) > 0) {
				return FALSE;
			}
		}

		if (dObject[px][py]) {
			if (dObject[px][py] > 0) {
				bv = dObject[px][py] - 1;
			} else {
				bv = -(dObject[px][py] + 1);
			}
			if (object[bv]._oSolidFlag) {
				return FALSE;
			}
		}

		PosOK = TRUE;
	}

	if (!PosOK)
		return FALSE;
	return TRUE;
}

void __fastcall MakePlrPath(int pnum, int xx, int yy, BOOL endspace)
{
	int path;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("MakePlrPath: illegal player %d", pnum);
	}

	plr[pnum]._ptargx = xx;
	plr[pnum]._ptargy = yy;
	if (plr[pnum]._px == xx && plr[pnum]._py == yy) {
		return;
	}

	path = FindPath(PosOkPlayer, pnum, plr[pnum]._px, plr[pnum]._py, xx, yy, plr[pnum].walkpath);
	if (!path) {
		return;
	}

	if (!endspace) {
		path--;

		switch (plr[pnum].walkpath[path]) {
		case WALK_NE:
			yy++;
			break;
		case WALK_NW:
			xx++;
			break;
		case WALK_SE:
			xx--;
			break;
		case WALK_SW:
			yy--;
			break;
		case WALK_N:
			xx++;
			yy++;
			break;
		case WALK_E:
			xx--;
			yy++;
			break;
		case WALK_S:
			xx--;
			yy--;
			break;
		case WALK_W:
			xx++;
			yy--;
			break;
		}

		plr[pnum]._ptargx = xx;
		plr[pnum]._ptargy = yy;
	}

	plr[pnum].walkpath[path] = WALK_NONE;
}

void __fastcall CheckPlrSpell()
{
	BOOL addflag;
	int rspell, sd, sl;

	if ((DWORD)myplr >= MAX_PLRS) {
		TermMsg("CheckPlrSpell: illegal player %d", myplr);
	}

	rspell = plr[myplr]._pRSpell;
	if (rspell == SPL_INVALID) {
		if (plr[myplr]._pClass == PC_WARRIOR) {
			PlaySFX(PS_WARR34);
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			PlaySFX(PS_ROGUE34);
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			PlaySFX(PS_MAGE34);
		}
		return;
	}

	if (leveltype == DTYPE_TOWN && !spelldata[rspell].sTownSpell) {
		if (plr[myplr]._pClass == PC_WARRIOR) {
			PlaySFX(PS_WARR27);
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			PlaySFX(PS_ROGUE27);
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			PlaySFX(PS_MAGE27);
		}
		return;
	}

	if (pcurs != CURSOR_HAND
	    || MouseY >= 352
	    || (chrflag && MouseX < 320 || invflag && MouseX > 320)
	        && rspell != SPL_HEAL
	        && rspell != SPL_IDENTIFY
	        && rspell != SPL_REPAIR
	        && rspell != SPL_INFRA
	        && rspell != SPL_RECHARGE) {
		return;
	}

	addflag = FALSE;
	switch (plr[myplr]._pRSplType) {
	case RSPLTYPE_SKILL:
	case RSPLTYPE_SPELL:
		addflag = CheckSpell(myplr, rspell, plr[myplr]._pRSplType, FALSE);
		break;
	case RSPLTYPE_SCROLL:
		addflag = UseScroll();
		break;
	case RSPLTYPE_CHARGES:
		addflag = UseStaff();
		break;
	}

	if (addflag) {
		if (plr[myplr]._pRSpell == SPL_FIREWALL) {
			sd = GetDirection(plr[myplr].WorldX, plr[myplr].WorldY, cursmx, cursmy);
			sl = GetSpellLevel(myplr, plr[myplr]._pRSpell);
			NetSendCmdLocParam3(TRUE, CMD_SPELLXYD, cursmx, cursmy, plr[myplr]._pRSpell, sd, sl);
		} else if (pcursmonst != -1) {
			sl = GetSpellLevel(myplr, plr[myplr]._pRSpell);
			NetSendCmdParam3(TRUE, CMD_SPELLID, pcursmonst, plr[myplr]._pRSpell, sl);
		} else if (pcursplr != -1) {
			sl = GetSpellLevel(myplr, plr[myplr]._pRSpell);
			NetSendCmdParam3(TRUE, CMD_SPELLPID, pcursplr, plr[myplr]._pRSpell, sl);
		} else { //145
			sl = GetSpellLevel(myplr, plr[myplr]._pRSpell);
			NetSendCmdLocParam2(TRUE, CMD_SPELLXY, cursmx, cursmy, plr[myplr]._pRSpell, sl);
		}
		return;
	}

	if (plr[myplr]._pRSplType == RSPLTYPE_SPELL) {
		if (plr[myplr]._pClass == PC_WARRIOR) {
			PlaySFX(PS_WARR35);
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			PlaySFX(PS_ROGUE35);
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			PlaySFX(PS_MAGE35);
		}
	}
}
// 4B8CC2: using guessed type char pcursplr;

void __fastcall SyncPlrAnim(int pnum)
{
	int dir, sType;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SyncPlrAnim: illegal player %d", pnum);
	}

	dir = plr[pnum]._pdir;
	switch (plr[pnum]._pmode) {
	case PM_BLOCK:
		plr[pnum]._pAnimData = plr[pnum]._pBAnim[dir];
		break;
	case PM_GOTHIT:
		plr[pnum]._pAnimData = plr[pnum]._pHAnim[dir];
		break;
	case PM_DEATH:
		plr[pnum]._pAnimData = plr[pnum]._pDAnim[dir];
		break;
	case PM_SPELL:
		if (pnum == myplr) {
			sType = spelldata[plr[pnum]._pSpell].sType;
		} else {
			sType = STYPE_FIRE;
		}
		if (sType == STYPE_FIRE)
			plr[pnum]._pAnimData = plr[pnum]._pFAnim[dir];
		if (sType == STYPE_LIGHTNING)
			plr[pnum]._pAnimData = plr[pnum]._pLAnim[dir];
		if (sType == STYPE_MAGIC) {
			plr[pnum]._pAnimData = plr[pnum]._pTAnim[dir];
		}
		break;
	case PM_STAND:
	case PM_NEWLVL:
	case PM_QUIT:
		plr[pnum]._pAnimData = plr[pnum]._pNAnim[dir];
		break;
	case PM_WALK:
	case PM_WALK2:
	case PM_WALK3:
		plr[pnum]._pAnimData = plr[pnum]._pWAnim[dir];
		break;
	case PM_ATTACK:
	case PM_RATTACK:
		plr[pnum]._pAnimData = plr[pnum]._pAAnim[dir];
		break;
	default:
		TermMsg("SyncPlrAnim");
		break;
	}
}

void __fastcall SyncInitPlrPos(int pnum)
{
	int x, y, xx, yy, range;
	DWORD i;
	BOOL posOk;

	plr[pnum]._ptargx = plr[pnum].WorldX;
	plr[pnum]._ptargy = plr[pnum].WorldY;

	if (gbMaxPlayers == 1 || plr[pnum].plrlevel != currlevel) {
		return;
	}

	for (i = 0; i < 8; i++) {
		x = plr[pnum].WorldX + plrxoff2[i];
		y = plr[pnum].WorldY + plryoff2[i];
		if (PosOkPlayer(pnum, x, y)) {
			break;
		}
	}

	if (!PosOkPlayer(pnum, x, y)) {
		posOk = FALSE;
		for (range = 1; range < 50 && !posOk; range++) {
			for (yy = -range; yy <= range && !posOk; yy++) {
				y = yy + plr[pnum].WorldY;
				for (xx = -range; xx <= range && !posOk; xx++) {
					x = xx + plr[pnum].WorldX;
					if (PosOkPlayer(pnum, x, y) && !PosOkPortal(currlevel, x, y)) {
						posOk = TRUE;
					}
				}
			}
		}
	}

	plr[pnum].WorldX = x;
	plr[pnum].WorldY = y;
	dPlayer[x][y] = pnum + 1;

	if (pnum == myplr) {
		plr[pnum]._px = x;
		plr[pnum]._py = y;
		plr[pnum]._ptargx = x;
		plr[pnum]._ptargy = y;
		ViewX = x;
		ViewY = y;
	}
}

void __fastcall SyncInitPlr(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SyncInitPlr: illegal player %d", pnum);
	}

	SetPlrAnims(pnum);
	SyncInitPlrPos(pnum);
}

void __fastcall CheckStats(int pnum)
{
	int c, i;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("CheckStats: illegal player %d", pnum);
	}

	if (plr[pnum]._pClass == PC_WARRIOR) {
		c = PC_WARRIOR;
	} else if (plr[pnum]._pClass == PC_ROGUE) {
		c = PC_ROGUE;
	} else if (plr[pnum]._pClass == PC_SORCERER) {
		c = PC_SORCERER;
	}

	for (i = 0; i < 4; i++) {
		switch (i) {
		case ATTRIB_STR:
			if (plr[pnum]._pBaseStr > MaxStats[c][ATTRIB_STR]) {
				plr[pnum]._pBaseStr = MaxStats[c][ATTRIB_STR];
			} else if (plr[pnum]._pBaseStr < 0) {
				plr[pnum]._pBaseStr = 0;
			}
			break;
		case ATTRIB_MAG:
			if (plr[pnum]._pBaseMag > MaxStats[c][ATTRIB_MAG]) {
				plr[pnum]._pBaseMag = MaxStats[c][ATTRIB_MAG];
			} else if (plr[pnum]._pBaseMag < 0) {
				plr[pnum]._pBaseMag = 0;
			}
			break;
		case ATTRIB_DEX:
			if (plr[pnum]._pBaseDex > MaxStats[c][ATTRIB_DEX]) {
				plr[pnum]._pBaseDex = MaxStats[c][ATTRIB_DEX];
			} else if (plr[pnum]._pBaseDex < 0) {
				plr[pnum]._pBaseDex = 0;
			}
			break;
		case ATTRIB_VIT:
			if (plr[pnum]._pBaseVit > MaxStats[c][ATTRIB_VIT]) {
				plr[pnum]._pBaseVit = MaxStats[c][ATTRIB_VIT];
			} else if (plr[pnum]._pBaseVit < 0) {
				plr[pnum]._pBaseVit = 0;
			}
			break;
		}
	}
}

void __fastcall ModifyPlrStr(int pnum, int l)
{
	int max;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ModifyPlrStr: illegal player %d", pnum);
	}

	max = MaxStats[plr[pnum]._pClass][ATTRIB_STR];
	if (plr[pnum]._pBaseStr + l > max) {
		l = max - plr[pnum]._pBaseStr;
	}

	plr[pnum]._pStrength += l;
	plr[pnum]._pBaseStr += l;

	if (plr[pnum]._pClass == PC_ROGUE) {
		plr[pnum]._pDamageMod = plr[pnum]._pLevel * (plr[pnum]._pStrength + plr[pnum]._pDexterity) / 200;
	} else {
		plr[pnum]._pDamageMod = plr[pnum]._pLevel * plr[pnum]._pStrength / 100;
	}

	CalcPlrInv(pnum, TRUE);

	if (pnum == myplr) {
		NetSendCmdParam1(FALSE, CMD_SETSTR, plr[pnum]._pBaseStr); //60
	}
}

void __fastcall ModifyPlrMag(int pnum, int l)
{
	int max, ms;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ModifyPlrMag: illegal player %d", pnum);
	}

	max = MaxStats[plr[pnum]._pClass][ATTRIB_MAG];
	if (plr[pnum]._pBaseMag + l > max) {
		l = max - plr[pnum]._pBaseMag;
	}

	plr[pnum]._pMagic += l;
	plr[pnum]._pBaseMag += l;

	ms = l << 6;
	if (plr[pnum]._pClass == PC_SORCERER) {
		ms *= 2;
	}

	plr[pnum]._pMaxManaBase += ms;
	plr[pnum]._pMaxMana += ms;
	if (!(plr[pnum]._pIFlags & ISPL_NOMANA)) {
		plr[pnum]._pManaBase += ms;
		plr[pnum]._pMana += ms;
	}

	CalcPlrInv(pnum, TRUE);

	if (pnum == myplr) {
		NetSendCmdParam1(FALSE, CMD_SETMAG, plr[pnum]._pBaseMag);
	}
}

void __fastcall ModifyPlrDex(int pnum, int l)
{
	int max;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ModifyPlrDex: illegal player %d", pnum);
	}

	max = MaxStats[plr[pnum]._pClass][ATTRIB_DEX];
	if (plr[pnum]._pBaseDex + l > max) {
		l = max - plr[pnum]._pBaseDex;
	}

	plr[pnum]._pDexterity += l;
	plr[pnum]._pBaseDex += l;
	CalcPlrInv(pnum, TRUE);

	if (plr[pnum]._pClass == PC_ROGUE) {
		plr[pnum]._pDamageMod = plr[pnum]._pLevel * (plr[pnum]._pDexterity + plr[pnum]._pStrength) / 200;
	}

	if (pnum == myplr) {
		NetSendCmdParam1(FALSE, CMD_SETDEX, plr[pnum]._pBaseDex);
	}
}

void __fastcall ModifyPlrVit(int pnum, int l)
{
	int max, ms;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("ModifyPlrVit: illegal player %d", pnum);
	}

	max = MaxStats[plr[pnum]._pClass][ATTRIB_VIT];
	if (plr[pnum]._pBaseVit + l > max) {
		l = max - plr[pnum]._pBaseVit;
	}

	plr[pnum]._pVitality += l;
	plr[pnum]._pBaseVit += l;

	ms = l << 6;
	if (plr[pnum]._pClass == PC_WARRIOR) {
		ms *= 2;
	}

	plr[pnum]._pHPBase += ms;
	plr[pnum]._pMaxHPBase += ms;
	plr[pnum]._pHitPoints += ms;
	plr[pnum]._pMaxHP += ms;

	CalcPlrInv(pnum, TRUE);

	if (pnum == myplr) {
		NetSendCmdParam1(FALSE, CMD_SETVIT, plr[pnum]._pBaseVit);
	}
}

void __fastcall SetPlayerHitPoints(int pnum, int newhp)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlayerHitPoints: illegal player %d", pnum);
	}

	plr[pnum]._pHitPoints = newhp;
	plr[pnum]._pHPBase = newhp + plr[pnum]._pMaxHPBase - plr[pnum]._pMaxHP;

	if (pnum == myplr) {
		drawhpflag = TRUE;
	}
}

void __fastcall SetPlrStr(int pnum, int v)
{
	int dm;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlrStr: illegal player %d", pnum);
	}

	plr[pnum]._pBaseStr = v;
	CalcPlrInv(pnum, TRUE);

	if (plr[pnum]._pClass == PC_ROGUE) {
		dm = plr[pnum]._pLevel * (plr[pnum]._pStrength + plr[pnum]._pDexterity) / 200;
	} else {
		dm = plr[pnum]._pLevel * plr[pnum]._pStrength / 100;
	}

	plr[pnum]._pDamageMod = dm;
}

void __fastcall SetPlrMag(int pnum, int v)
{
	int m;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlrMag: illegal player %d", pnum);
	}

	plr[pnum]._pBaseMag = v;

	m = v << 6;
	if (plr[pnum]._pClass == PC_SORCERER) {
		m *= 2;
	}

	plr[pnum]._pMaxManaBase = m;
	plr[pnum]._pMaxMana = m;
	CalcPlrInv(pnum, TRUE);
}

void __fastcall SetPlrDex(int pnum, int v)
{
	int dm;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlrDex: illegal player %d", pnum);
	}

	plr[pnum]._pBaseDex = v;
	CalcPlrInv(pnum, TRUE);

	if (plr[pnum]._pClass == PC_ROGUE) {
		dm = plr[pnum]._pLevel * (plr[pnum]._pStrength + plr[pnum]._pDexterity) / 200;
	} else {
		dm = plr[pnum]._pStrength * plr[pnum]._pLevel / 100;
	}

	plr[pnum]._pDamageMod = dm;
}

void __fastcall SetPlrVit(int pnum, int v)
{
	int hp;

	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("SetPlrVit: illegal player %d", pnum);
	}

	plr[pnum]._pBaseVit = v;

	hp = v << 6;
	if (plr[pnum]._pClass == PC_WARRIOR) {
		hp *= 2;
	}

	plr[pnum]._pHPBase = hp;
	plr[pnum]._pMaxHPBase = hp;
	CalcPlrInv(pnum, TRUE);
}

void __fastcall InitDungMsgs(int pnum)
{
	if ((DWORD)pnum >= MAX_PLRS) {
		TermMsg("InitDungMsgs: illegal player %d", pnum);
	}

	plr[pnum].pDungMsgs = 0;
}

void __cdecl PlayDungMsgs()
{
	if ((DWORD)myplr >= MAX_PLRS) {
		TermMsg("PlayDungMsgs: illegal player %d", myplr);
	}

	if (currlevel == 1 && !plr[myplr]._pLvlVisited[1] && gbMaxPlayers == 1 && !(plr[myplr].pDungMsgs & DMSG_CATHEDRAL)) {
		sfxdelay = 40;
		if (plr[myplr]._pClass == PC_WARRIOR) {
			sfxdnum = PS_WARR97;
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			sfxdnum = PS_ROGUE97;
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			sfxdnum = PS_MAGE97;
		}
		plr[myplr].pDungMsgs = plr[myplr].pDungMsgs | DMSG_CATHEDRAL;
	} else if (currlevel == 5 && !plr[myplr]._pLvlVisited[5] && gbMaxPlayers == 1 && !(plr[myplr].pDungMsgs & DMSG_CATACOMBS)) {
		sfxdelay = 40;
		if (plr[myplr]._pClass == PC_WARRIOR) {
			sfxdnum = PS_WARR96B;
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			sfxdnum = PS_ROGUE96;
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			sfxdnum = PS_MAGE96;
		}
		plr[myplr].pDungMsgs |= DMSG_CATACOMBS;
	} else if (currlevel == 9 && !plr[myplr]._pLvlVisited[9] && gbMaxPlayers == 1 && !(plr[myplr].pDungMsgs & DMSG_CAVES)) {
		sfxdelay = 40;
		if (plr[myplr]._pClass == PC_WARRIOR) {
			sfxdnum = PS_WARR98;
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			sfxdnum = PS_ROGUE98;
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			sfxdnum = PS_MAGE98;
		}
		plr[myplr].pDungMsgs |= DMSG_CAVES;
	} else if (currlevel == 13 && !plr[myplr]._pLvlVisited[13] && gbMaxPlayers == 1 && !(plr[myplr].pDungMsgs & DMSG_HELL)) {
		sfxdelay = 40;
		if (plr[myplr]._pClass == PC_WARRIOR) {
			sfxdnum = PS_WARR99;
		} else if (plr[myplr]._pClass == PC_ROGUE) {
			sfxdnum = PS_ROGUE99;
		} else if (plr[myplr]._pClass == PC_SORCERER) {
			sfxdnum = PS_MAGE99;
		}
		plr[myplr].pDungMsgs |= DMSG_HELL;
	} else if (currlevel == 16 && !plr[myplr]._pLvlVisited[15] && gbMaxPlayers == 1 && !(plr[myplr].pDungMsgs & DMSG_DIABLO)) { // BUGFIX: _pLvlVisited should check 16 or this message will never play
		sfxdelay = 40;
		if (plr[myplr]._pClass == PC_WARRIOR || plr[myplr]._pClass == PC_ROGUE || plr[myplr]._pClass == PC_SORCERER) {
			sfxdnum = PS_DIABLVLINT;
		}
		plr[myplr].pDungMsgs |= DMSG_DIABLO;
	} else {
		sfxdelay = 0;
	}
}
// 52A554: using guessed type int sfxdelay;
