#include "diablo.h"

int itemactive[MAXITEMS];
int uitemflag;
int itemavail[MAXITEMS];
ItemStruct curruitem;
ItemGetRecordStruct itemrecord[MAXITEMS];
ItemStruct item[MAXITEMS + 1];
BOOL itemhold[3][3];
unsigned char *itemanims[35];
int UniqueItemFlag[128];
int numitems;
int gnNumGetRecords;

/* data */

unsigned char ItemCAnimTbl[169] = {
	20, 16, 16, 16, 4, 4, 4, 12, 12, 12,
	12, 12, 12, 12, 12, 21, 21, 25, 12, 28,
	28, 28, 0, 0, 0, 32, 0, 0, 0, 24,
	24, 26, 2, 25, 22, 23, 24, 25, 27, 27,
	29, 0, 0, 0, 12, 12, 12, 12, 12, 0,
	8, 8, 0, 8, 8, 8, 8, 8, 8, 6,
	8, 8, 8, 6, 8, 8, 6, 8, 8, 6,
	6, 6, 8, 8, 8, 5, 9, 13, 13, 13,
	5, 5, 5, 15, 5, 5, 18, 18, 18, 30,
	5, 5, 14, 5, 14, 13, 16, 18, 5, 5,
	7, 1, 3, 17, 1, 15, 10, 14, 3, 11,
	8, 0, 1, 7, 0, 7, 15, 7, 3, 3,
	3, 6, 6, 11, 11, 11, 31, 14, 14, 14,
	6, 6, 7, 3, 8, 14, 0, 14, 14, 0,
	33, 1, 1, 1, 1, 1, 7, 7, 7, 14,
	14, 17, 17, 17, 0, 34, 1, 0, 3, 17,
	8, 8, 6, 1, 3, 3, 11, 3, 4
};
char *ItemDropStrs[35] = {
	"Armor2",
	"Axe",
	"FBttle",
	"Bow",
	"GoldFlip",
	"Helmut",
	"Mace",
	"Shield",
	"SwrdFlip",
	"Rock",
	"Cleaver",
	"Staff",
	"Ring",
	"CrownF",
	"LArmor",
	"WShield",
	"Scroll",
	"FPlateAr",
	"FBook",
	"Food",
	"FBttleBB",
	"FBttleDY",
	"FBttleOR",
	"FBttleBR",
	"FBttleBL",
	"FBttleBY",
	"FBttleWH",
	"FBttleDB",
	"FEar",
	"FBrain",
	"FMush",
	"Innsign",
	"Bldstn",
	"Fanvil",
	"FLazStaf"
};
unsigned char ItemAnimLs[35] = {
	15u,
	13u,
	16u,
	13u,
	10u,
	13u,
	13u,
	13u,
	13u,
	10u,
	13u,
	13u,
	13u,
	13u,
	13u,
	13u,
	13u,
	13u,
	13u,
	1u,
	16u,
	16u,
	16u,
	16u,
	16u,
	16u,
	16u,
	16u,
	13u,
	12u,
	12u,
	13u,
	13u,
	13u,
	8u
};
int ItemDropSnds[35] = {
	IS_FHARM,
	IS_FAXE,
	IS_FPOT,
	IS_FBOW,
	IS_GOLD,
	IS_FCAP,
	IS_FSWOR,
	IS_FSHLD,
	IS_FSWOR,
	IS_FROCK,
	IS_FAXE,
	IS_FSTAF,
	IS_FRING,
	IS_FCAP,
	IS_FLARM,
	IS_FSHLD,
	IS_FSCRL,
	IS_FHARM,
	IS_FBOOK,
	IS_FLARM,
	IS_FPOT,
	IS_FPOT,
	IS_FPOT,
	IS_FPOT,
	IS_FPOT,
	IS_FPOT,
	IS_FPOT,
	IS_FPOT,
	IS_FBODY,
	IS_FBODY,
	IS_FMUSH,
	IS_ISIGN,
	IS_FBLST,
	IS_FANVL,
	IS_FSTAF
};
int ItemInvSnds[35] = {
	IS_IHARM,
	IS_IAXE,
	IS_IPOT,
	IS_IBOW,
	IS_GOLD,
	IS_ICAP,
	IS_ISWORD,
	IS_ISHIEL,
	IS_ISWORD,
	IS_IROCK,
	IS_IAXE,
	IS_ISTAF,
	IS_IRING,
	IS_ICAP,
	IS_ILARM,
	IS_ISHIEL,
	IS_ISCROL,
	IS_IHARM,
	IS_IBOOK,
	IS_IHARM,
	IS_IPOT,
	IS_IPOT,
	IS_IPOT,
	IS_IPOT,
	IS_IPOT,
	IS_IPOT,
	IS_IPOT,
	IS_IPOT,
	IS_IBODY,
	IS_IBODY,
	IS_IMUSH,
	IS_ISIGN,
	IS_IBLST,
	IS_IANVL,
	IS_ISTAF
};
int idoppely = 16; // weak
int premiumlvladd[6] = { -1, -1, 0, 0, 1, 2 };

void InitItemGFX()
{
	int i;
	char arglist[64];

	for (i = 0; i < 35; i++) {
		sprintf(arglist, "Items\\%s.CEL", ItemDropStrs[i]);
		itemanims[i] = LoadFileInMem(arglist, 0);
	}
	memset(UniqueItemFlag, 0, sizeof(UniqueItemFlag));
}

BOOL ItemPlace(int xp, int yp)
{
	if (dMonster[xp][yp])
		return FALSE;
	if (dPlayer[xp][yp])
		return FALSE;
	if (dItem[xp][yp])
		return FALSE;
	if (dObject[xp][yp])
		return FALSE;
	if (dFlags[xp][yp] & DFLAG_POPULATED)
		return FALSE;
	if (nSolidTable[dPiece[xp][yp]])
		return FALSE;

	return TRUE;
}

void AddInitItems()
{
	int x, y, i, j, rnd;

	rnd = random(11, 3) + 3;
	for (j = 0; j < rnd; j++) {
		i = itemavail[0];
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		itemactive[numitems] = i;
		x = random(12, 80) + 16;
		y = random(12, 80) + 16;
		while (!ItemPlace(x, y)) {
			x = random(12, 80) + 16;
			y = random(12, 80) + 16;
		}
		item[i]._ix = x;
		item[i]._iy = y;
		dItem[x][y] = i + 1;
		item[i]._iSeed = GetRndSeed();
		SetRndSeed(item[i]._iSeed);
		if (random(12, 2))
			GetItemAttrs(i, IDI_HEAL, currlevel);
		else
			GetItemAttrs(i, IDI_MANA, currlevel);
		item[i]._iCreateInfo = currlevel - 32768;
		SetupItem(i);
		item[i]._iAnimFrame = item[i]._iAnimLen;
		item[i]._iAnimFlag = 0;
		item[i]._iSelFlag = 1;
		DeltaAddItem(i);
		numitems++;
	}
}

void InitItems()
{
	int i;

	GetItemAttrs(0, IDI_GOLD, 1);
	golditem = item[0];
	golditem._iStatFlag = 1;
	numitems = 0;

	for (i = 0; i < MAXITEMS; i++) {
		item[i]._itype = ITYPE_MISC;
		item[i]._ix = 0;
		item[i]._iy = 0;
		item[i]._isin = 0;
		item[i]._iSelFlag = 0;
		item[i]._iIdentified = FALSE;
		item[i]._iPostDraw = 0;
	}

	for (i = 0; i < MAXITEMS; i++) {
		itemavail[i] = i;
		itemactive[i] = 0;
	}

	if (!setlevel) {
		GetRndSeed();
		if (QuestStatus(QTYPE_INFRA))
			SpawnRock();
		if (QuestStatus(QTYPE_ANVIL))
			SpawnQuestItem(16, 2 * setpc_x + 27, 2 * setpc_y + 27, 0, 1);
		if (currlevel > 0u && currlevel < 0x10u)
			AddInitItems();
	}

	uitemflag = 0;
}
// 5CF31D: using guessed type char setlevel;

void CalcPlrItemVals(int p, BOOL Loadgfx)
{
	int pvid, d;

	int mind = 0; // min damage
	int maxd = 0; // max damage
	int tac = 0;  // accuracy

	int g;
	int i;
	int mi;

	int bdam = 0;   // bonus damage
	int btohit = 0; // bonus chance to hit
	int bac = 0;    // bonus accuracy

	int iflgs = 0; // item_special_effect flags

	int sadd = 0; // added stregth
	int madd = 0; // added magic
	int dadd = 0; // added dexterity
	int vadd = 0; // added vitality

	unsigned __int64 spl = 0; // bitarray for all enabled/active spells

	signed int fr = 0; // fire resistance
	signed int lr = 0; // lightning resistance
	signed int mr = 0; // magic resistance

	int dmod = 0; // bonus damage mod?
	int ghit = 0; // (reduced) chance to get hit

	signed int lrad = 10; // light radius

	int ihp = 0;   // increased HP
	int imana = 0; // increased mana

	int spllvladd = 0; // increased spell level
	int enac = 0;      // enhanced accuracy

	int fmin = 0; // minimum fire damage
	int fmax = 0; // maximum fire damage
	int lmin = 0; // minimum lightning damage
	int lmax = 0; // maximum lightning damage

	// didn't find a use for t for now
	// int t;

	for (i = 0; i < NUM_INVLOC; i++) {
		ItemStruct *itm = &plr[p].InvBody[i];
		if (itm->_itype != ITYPE_NONE && itm->_iStatFlag) {

			mind += itm->_iMinDam;
			tac += itm->_iAC;
			maxd += itm->_iMaxDam;

			if (itm->_iSpell != SPL_NULL) {
				spl |= (unsigned __int64)1 << (itm->_iSpell - 1);
			}

			if (itm->_iMagical == ITEM_QUALITY_NORMAL || itm->_iIdentified) {
				bdam += itm->_iPLDam;
				btohit += itm->_iPLToHit;
				if (itm->_iPLAC) {
					int tmpac = itm->_iPLAC * itm->_iAC / 100;
					if (tmpac == 0)
						tmpac = 1;
					bac += tmpac;
				}
				dmod += itm->_iPLDamMod;
				iflgs |= itm->_iFlags;
				sadd += itm->_iPLStr;
				madd += itm->_iPLMag;
				dadd += itm->_iPLDex;
				vadd += itm->_iPLVit;
				fr += itm->_iPLFR;
				lr += itm->_iPLLR;
				mr += itm->_iPLMR;
				ghit += itm->_iPLGetHit;
				lrad += itm->_iPLLight;
				ihp += itm->_iPLHP;
				imana += itm->_iPLMana;
				spllvladd += itm->_iSplLvlAdd;
				enac += itm->_iPLEnAc;
				fmin += itm->_iFMinDam;
				fmax += itm->_iFMaxDam;
				lmin += itm->_iLMinDam;
				lmax += itm->_iLMaxDam;
			}
		}
	}

	if (mind == 0 && maxd == 0) {
		mind = 1;
		maxd = 1;

		if (plr[p].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_SHIELD && plr[p].InvBody[INVLOC_HAND_LEFT]._iStatFlag) {
			maxd = 3;
		}

		if (plr[p].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_SHIELD && plr[p].InvBody[INVLOC_HAND_RIGHT]._iStatFlag) {
			maxd = 3;
		}
	}

	plr[p]._pIMaxDam = maxd;
	plr[p]._pIAC = tac;
	plr[p]._pIBonusDam = bdam;
	plr[p]._pIBonusToHit = btohit;
	plr[p]._pIBonusAC = bac;
	plr[p]._pIFlags = iflgs;
	plr[p]._pIGetHit = ghit;
	plr[p]._pIMinDam = mind;
	plr[p]._pIBonusDamMod = dmod;

	if (lrad < 2) {
		lrad = 2;
	}
	if (lrad > 15) {
		lrad = 15;
	}

	if (plr[p]._pLightRad != lrad && p == myplr) {
		ChangeLightRadius(plr[p]._plid, lrad);

		pvid = plr[p]._pvid;
		if (lrad >= 10) {
			ChangeVisionRadius(pvid, lrad);
		} else {
			ChangeVisionRadius(pvid, 10);
		}

		plr[p]._pLightRad = lrad;
	}

	plr[p]._pStrength = sadd + plr[p]._pBaseStr;
	if (plr[myplr]._pStrength <= 0) {
		plr[myplr]._pStrength = 0;
	}

	plr[p]._pMagic = madd + plr[p]._pBaseMag;
	if (plr[myplr]._pMagic <= 0) {
		plr[myplr]._pMagic = 0;
	}

	plr[p]._pDexterity = dadd + plr[p]._pBaseDex;
	if (plr[myplr]._pDexterity <= 0) {
		plr[myplr]._pDexterity = 0;
	}

	plr[p]._pVitality = vadd + plr[p]._pBaseVit;
	if (plr[myplr]._pVitality <= 0) {
		plr[myplr]._pVitality = 0;
	}

	if (plr[p]._pClass == PC_ROGUE) {
		plr[p]._pDamageMod = plr[p]._pLevel * (plr[p]._pStrength + plr[p]._pDexterity) / 200;
	} else {
		plr[p]._pDamageMod = plr[p]._pLevel * plr[p]._pStrength / 100;
	}

	plr[p]._pISpells = spl;

	// check if the current RSplType is a valid/allowed spell
	if (plr[p]._pRSplType == RSPLTYPE_CHARGES
	    && !(spl & ((unsigned __int64)1 << (plr[p]._pRSpell - 1)))) {
		plr[p]._pRSpell = SPL_INVALID;
		plr[p]._pRSplType = RSPLTYPE_INVALID;
		drawpanflag = 255;
	}

	plr[p]._pISplLvlAdd = spllvladd;
	plr[p]._pIEnAc = enac;

	if (iflgs & ISPL_ALLRESZERO) {
		// reset resistances to zero if the respective special effect is active
		mr = 0;
		fr = 0;
		lr = 0;
	}

	if (mr > 75) {
		mr = 75;
	}
	plr[p]._pMagResist = mr;

	if (fr > 75) {
		fr = 75;
	}
	plr[p]._pFireResist = fr;

	if (lr > 75) {
		lr = 75;
	}
	plr[p]._pLghtResist = lr;

	if (plr[p]._pClass == PC_WARRIOR) {
		vadd *= 2;
	}
	if (plr[p]._pClass == PC_ROGUE) {
		vadd += vadd >> 1;
	}
	ihp += (vadd << 6);

	if (plr[p]._pClass == PC_SORCERER) {
		madd *= 2;
	}
	if (plr[p]._pClass == PC_ROGUE) {
		madd += madd >> 1;
	}
	imana += (madd << 6);

	plr[p]._pHitPoints = ihp + plr[p]._pHPBase;
	plr[p]._pMaxHP = ihp + plr[p]._pMaxHPBase;

	if (p == myplr && (plr[p]._pHitPoints >> 6) <= 0) {
		SetPlayerHitPoints(p, 0);
	}

	plr[p]._pMana = imana + plr[p]._pManaBase;
	plr[p]._pMaxMana = imana + plr[p]._pMaxManaBase;

	plr[p]._pIFMinDam = fmin;
	plr[p]._pIFMaxDam = fmax;
	plr[p]._pILMinDam = lmin;
	plr[p]._pILMaxDam = lmax;

	if (iflgs & ISPL_INFRAVISION) {
		plr[p]._pInfraFlag = 1;
	} else {
		plr[p]._pInfraFlag = 0;
	}

	plr[p]._pBlockFlag = 0;
	plr[p]._pwtype = WT_MELEE;

	g = 0;

	if (plr[p].InvBody[INVLOC_HAND_LEFT]._itype != ITYPE_NONE
	    && plr[p].InvBody[INVLOC_HAND_LEFT]._iClass == ICLASS_WEAPON
	    && plr[p].InvBody[INVLOC_HAND_LEFT]._iStatFlag) {
		g = plr[p].InvBody[INVLOC_HAND_LEFT]._itype;
	}

	if (plr[p].InvBody[INVLOC_HAND_RIGHT]._itype != ITYPE_NONE
	    && plr[p].InvBody[INVLOC_HAND_RIGHT]._iClass == ICLASS_WEAPON
	    && plr[p].InvBody[INVLOC_HAND_RIGHT]._iStatFlag) {
		g = plr[p].InvBody[INVLOC_HAND_RIGHT]._itype;
	}

	switch (g) {
	case ITYPE_SWORD:
		g = ANIM_ID_SWORD;
		break;
	case ITYPE_AXE:
		g = ANIM_ID_AXE;
		break;
	case ITYPE_BOW:
		plr[p]._pwtype = WT_RANGED;
		g = ANIM_ID_BOW;
		break;
	case ITYPE_MACE:
		g = ANIM_ID_MACE;
		break;
	case ITYPE_STAFF:
		g = ANIM_ID_STAFF;
		break;
	}

	if (plr[p].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_SHIELD && plr[p].InvBody[INVLOC_HAND_LEFT]._iStatFlag) {
		plr[p]._pBlockFlag = 1;
		g++;
	}
	if (plr[p].InvBody[INVLOC_HAND_RIGHT]._itype == ITYPE_SHIELD && plr[p].InvBody[INVLOC_HAND_RIGHT]._iStatFlag) {
		plr[p]._pBlockFlag = 1;
		g++;
	}

	if (plr[p].InvBody[INVLOC_CHEST]._itype == ITYPE_MARMOR && plr[p].InvBody[INVLOC_CHEST]._iStatFlag) {
		g += ANIM_ID_MEDIUM_ARMOR;
	}
	if (plr[p].InvBody[INVLOC_CHEST]._itype == ITYPE_HARMOR && plr[p].InvBody[INVLOC_CHEST]._iStatFlag) {
		g += ANIM_ID_HEAVY_ARMOR;
	}

	if (plr[p]._pgfxnum != g && Loadgfx) {
		plr[p]._pgfxnum = g;
		plr[p]._pGFXLoad = 0;
		LoadPlrGFX(p, PFILE_STAND);
		SetPlrAnims(p);

		d = plr[p]._pdir;

		// TODO: Add debug assert here ( plr[p]._pNAnim[d] != NULL )
		plr[p]._pAnimData = plr[p]._pNAnim[d];

		plr[p]._pAnimLen = plr[p]._pNFrames;
		plr[p]._pAnimFrame = 1;
		plr[p]._pAnimCnt = 0;
		plr[p]._pAnimDelay = 3;
		plr[p]._pAnimWidth = plr[p]._pNWidth;
		plr[p]._pAnimWidth2 = (plr[p]._pNWidth - 64) >> 1;
	} else {
		plr[p]._pgfxnum = g;
	}

	for (i = 0; i < nummissiles; i++) {
		mi = missileactive[i];
		if (missile[mi]._mitype == MIS_MANASHIELD && missile[mi]._misource == p) {
			missile[mi]._miVar1 = plr[p]._pHitPoints;
			missile[mi]._miVar2 = plr[p]._pHPBase;
		}
	}

	drawmanaflag = TRUE;
	drawhpflag = TRUE;
}

void CalcPlrScrolls(int p)
{
	int i, j;

	plr[p]._pScrlSpells = 0;
	for (i = 0; i < plr[p]._pNumInv; i++) {
		if (plr[p].InvList[i]._itype != ITYPE_NONE && (plr[p].InvList[i]._iMiscId == IMISC_SCROLL || plr[p].InvList[i]._iMiscId == IMISC_SCROLLT)) {
			if (plr[p].InvList[i]._iStatFlag)
				plr[p]._pScrlSpells |= (__int64)1 << (plr[p].InvList[i]._iSpell - 1);
		}
	}

	for (j = 0; j < MAXBELTITEMS; j++) {
		if (plr[p].SpdList[j]._itype != ITYPE_NONE && (plr[p].SpdList[j]._iMiscId == IMISC_SCROLL || plr[p].SpdList[j]._iMiscId == IMISC_SCROLLT)) {
			if (plr[p].SpdList[j]._iStatFlag)
				plr[p]._pScrlSpells |= (__int64)1 << (plr[p].SpdList[j]._iSpell - 1);
		}
	}
	if (plr[p]._pRSplType == RSPLTYPE_SCROLL) {
		if (!(plr[p]._pScrlSpells & 1 << (plr[p]._pRSpell - 1))) {
			plr[p]._pRSpell = SPL_INVALID;
			plr[p]._pRSplType = RSPLTYPE_INVALID;
			drawpanflag = 255;
		}
	}
}
// 52571C: using guessed type int drawpanflag;

void CalcPlrStaff(int pnum)
{
	plr[pnum]._pISpells = 0;
	if (plr[pnum].InvBody[INVLOC_HAND_LEFT]._itype != ITYPE_NONE
	    && plr[pnum].InvBody[INVLOC_HAND_LEFT]._iStatFlag
	    && plr[pnum].InvBody[INVLOC_HAND_LEFT]._iCharges > 0) {
		plr[pnum]._pISpells |= (__int64)1 << (plr[pnum].InvBody[INVLOC_HAND_LEFT]._iSpell - 1);
	}
}

void CalcSelfItems(int pnum)
{
	int i;
	PlayerStruct *p;
	BOOL sf, changeflag;
	int sa, ma, da;

	p = &plr[pnum];

	sa = 0;
	ma = 0;
	da = 0;
	for (i = 0; i < NUM_INVLOC; i++) {
		if (p->InvBody[i]._itype != ITYPE_NONE) {
			p->InvBody[i]._iStatFlag = TRUE;
			if (p->InvBody[i]._iIdentified) {
				sa += p->InvBody[i]._iPLStr;
				ma += p->InvBody[i]._iPLMag;
				da += p->InvBody[i]._iPLDex;
			}
		}
	}
	do {
		changeflag = FALSE;
		for (i = 0; i < NUM_INVLOC; i++) {
			if (p->InvBody[i]._itype != ITYPE_NONE && p->InvBody[i]._iStatFlag) {
				sf = TRUE;
				if (sa + p->_pBaseStr < p->InvBody[i]._iMinStr)
					sf = FALSE;
				if (ma + p->_pBaseMag < p->InvBody[i]._iMinMag)
					sf = FALSE;
				if (da + p->_pBaseDex < p->InvBody[i]._iMinDex)
					sf = FALSE;
				if (!sf) {
					changeflag = TRUE;
					p->InvBody[i]._iStatFlag = FALSE;
					if (p->InvBody[i]._iIdentified) {
						sa -= p->InvBody[i]._iPLStr;
						ma -= p->InvBody[i]._iPLMag;
						da -= p->InvBody[i]._iPLDex;
					}
				}
			}
		}
	} while (changeflag);
}

void CalcPlrItemMin(int pnum)
{
	PlayerStruct *p;
	ItemStruct *pi;
	int i;

	p = &plr[pnum];
	pi = p->InvList;

	for (i = p->_pNumInv; i; i--) {
		pi->_iStatFlag = ItemMinStats(p, pi);
		pi++;
	}

	pi = p->SpdList;
	for (i = MAXBELTITEMS; i != 0; i--) {
		if (pi->_itype != ITYPE_NONE) {
			pi->_iStatFlag = ItemMinStats(p, pi);
		}
		pi++;
	}
}

BOOL ItemMinStats(PlayerStruct *p, ItemStruct *x)
{
	if (p->_pMagic < x->_iMinMag)
		return FALSE;

	if (p->_pStrength < x->_iMinStr)
		return FALSE;

	if (p->_pDexterity < x->_iMinDex)
		return FALSE;

	return TRUE;
}

void CalcPlrBookVals(int p)
{
	int i, slvl;

	if (!currlevel) {
		for (i = 1; witchitem[i]._itype != ITYPE_NONE; i++) {
			WitchBookLevel(i);
			witchitem[i]._iStatFlag = StoreStatOk(&witchitem[i]);
		}
	}

	for (i = 0; i < plr[p]._pNumInv; i++) {
		if (plr[p].InvList[i]._itype == ITYPE_NONE && plr[p].InvList[i]._iMiscId == IMISC_BOOK) {
			plr[p].InvList[i]._iMinMag = spelldata[plr[p].InvList[i]._iSpell].sMinInt;
			slvl = plr[p]._pSplLvl[plr[p].InvList[i]._iSpell];

			while (slvl) {
				plr[p].InvList[i]._iMinMag += 20 * plr[p].InvList[i]._iMinMag / 100;
				slvl--;
				if (plr[p].InvList[i]._iMinMag + 20 * plr[p].InvList[i]._iMinMag / 100 > 255) {
					plr[p].InvList[i]._iMinMag = 255;
					slvl = 0;
				}
			}
			plr[p].InvList[i]._iStatFlag = ItemMinStats(&plr[p], &plr[p].InvList[i]);
		}
	}
}

void CalcPlrInv(int p, BOOL Loadgfx)
{
	CalcPlrItemMin(p);
	CalcSelfItems(p);
	CalcPlrItemVals(p, Loadgfx);
	CalcPlrItemMin(p);
	if (p == myplr) {
		CalcPlrBookVals(p);
		CalcPlrScrolls(p);
		CalcPlrStaff(p);
		if (p == myplr && !currlevel)
			RecalcStoreStats();
	}
}

void SetPlrHandItem(ItemStruct *h, int idata)
{
	ItemDataStruct *pAllItem;

	pAllItem = &AllItemsList[idata];

	// zero-initialize struct
	memset(h, 0, sizeof(*h));

	h->_itype = pAllItem->itype;
	h->_iCurs = pAllItem->iCurs;
	strcpy(h->_iName, pAllItem->iName);
	strcpy(h->_iIName, pAllItem->iName);
	h->_iLoc = pAllItem->iLoc;
	h->_iClass = pAllItem->iClass;
	h->_iMinDam = pAllItem->iMinDam;
	h->_iMaxDam = pAllItem->iMaxDam;
	h->_iAC = pAllItem->iMinAC;
	h->_iMiscId = pAllItem->iMiscId;
	h->_iSpell = pAllItem->iSpell;

	if (pAllItem->iMiscId == IMISC_STAFF) {
		h->_iCharges = 40;
	}

	h->_iMaxCharges = h->_iCharges;
	h->_iDurability = pAllItem->iDurability;
	h->_iMaxDur = pAllItem->iDurability;
	h->_iMinStr = pAllItem->iMinStr;
	h->_iMinMag = pAllItem->iMinMag;
	h->_iMinDex = pAllItem->iMinDex;
	h->_ivalue = pAllItem->iValue;
	h->_iIvalue = pAllItem->iValue;
	h->_iPrePower = -1;
	h->_iSufPower = -1;
	h->_iMagical = ITEM_QUALITY_NORMAL;
	h->IDidx = idata;
}

void GetPlrHandSeed(ItemStruct *h)
{
	h->_iSeed = GetRndSeed();
}

void GetGoldSeed(int pnum, ItemStruct *h)
{
	int i, ii, s;
	BOOL doneflag;

	do {
		doneflag = TRUE;
		s = GetRndSeed();
		for (i = 0; i < numitems; i++) {
			ii = itemactive[i];
			if (item[ii]._iSeed == s)
				doneflag = FALSE;
		}
		if (pnum == myplr) {
			for (i = 0; i < plr[pnum]._pNumInv; i++) {
				if (plr[pnum].InvList[i]._iSeed == s)
					doneflag = FALSE;
			}
		}
	} while (!doneflag);

	h->_iSeed = s;
}

void SetPlrHandSeed(ItemStruct *h, int iseed)
{
	h->_iSeed = iseed;
}

void SetPlrHandGoldCurs(ItemStruct *h)
{
	if (h->_ivalue >= 2500)
		h->_iCurs = ICURS_GOLD_LARGE;
	else if (h->_ivalue <= 1000)
		h->_iCurs = ICURS_GOLD_SMALL;
	else
		h->_iCurs = ICURS_GOLD_MEDIUM;
}

void CreatePlrItems(int p)
{
	int i;
	ItemStruct *pi = plr[p].InvBody;

	for (i = 0; i < NUM_INVLOC; i++) {
		pi[i]._itype = ITYPE_NONE;
	}

	// converting this to a for loop creates a `rep stosd` instruction,
	// so this probably actually was a memset
	memset(&plr[p].InvGrid, 0, sizeof(plr[p].InvGrid));

	pi = plr[p].InvList;
	for (i = 0; i < NUM_INV_GRID_ELEM; i++) {
		pi[i]._itype = ITYPE_NONE;
	}

	plr[p]._pNumInv = 0;

	pi = plr[p].SpdList;
	for (i = 0; i < MAXBELTITEMS; i++) {
		pi[i]._itype = ITYPE_NONE;
	}

	switch (plr[p]._pClass) {
	case PC_WARRIOR:
		SetPlrHandItem(&plr[p].InvBody[INVLOC_HAND_LEFT], IDI_WARRIOR);
		GetPlrHandSeed(&plr[p].InvBody[INVLOC_HAND_LEFT]);

		SetPlrHandItem(&plr[p].InvBody[INVLOC_HAND_RIGHT], IDI_WARRSHLD);
		GetPlrHandSeed(&plr[p].InvBody[INVLOC_HAND_RIGHT]);

#ifdef _DEBUG
		if (!debug_mode_key_w) {
#endif
			SetPlrHandItem(&plr[p].HoldItem, IDI_WARRCLUB);
			GetPlrHandSeed(&plr[p].HoldItem);
			AutoPlace(p, 0, 1, 3, TRUE);
#ifdef _DEBUG
		}
#endif

		SetPlrHandItem(&plr[p].SpdList[0], IDI_HEAL);
		GetPlrHandSeed(&plr[p].SpdList[0]);

		SetPlrHandItem(&plr[p].SpdList[1], IDI_HEAL);
		GetPlrHandSeed(&plr[p].SpdList[1]);
		break;
	case PC_ROGUE:
		SetPlrHandItem(&plr[p].InvBody[INVLOC_HAND_LEFT], IDI_ROGUE);
		GetPlrHandSeed(&plr[p].InvBody[INVLOC_HAND_LEFT]);

		SetPlrHandItem(&plr[p].SpdList[0], IDI_HEAL);
		GetPlrHandSeed(&plr[p].SpdList[0]);

		SetPlrHandItem(&plr[p].SpdList[1], IDI_HEAL);
		GetPlrHandSeed(&plr[p].SpdList[1]);
		break;
	case PC_SORCERER:
		SetPlrHandItem(&plr[p].InvBody[INVLOC_HAND_LEFT], IDI_SORCEROR);
		GetPlrHandSeed(&plr[p].InvBody[INVLOC_HAND_LEFT]);

		SetPlrHandItem(&plr[p].SpdList[0], IDI_MANA);
		GetPlrHandSeed(&plr[p].SpdList[0]);

		SetPlrHandItem(&plr[p].SpdList[1], IDI_MANA);
		GetPlrHandSeed(&plr[p].SpdList[1]);
		break;
	}

	SetPlrHandItem(&plr[p].HoldItem, IDI_GOLD);
	GetPlrHandSeed(&plr[p].HoldItem);

#ifdef _DEBUG
	if (!debug_mode_key_w) {
#endif
		plr[p].HoldItem._ivalue = 100;
		plr[p].HoldItem._iCurs = ICURS_GOLD_SMALL;
		plr[p]._pGold = plr[p].HoldItem._ivalue;
		plr[p].InvList[plr[p]._pNumInv++] = plr[p].HoldItem;
		plr[p].InvGrid[30] = plr[p]._pNumInv;
#ifdef _DEBUG
	} else {
		plr[p].HoldItem._ivalue = 5000;
		plr[p].HoldItem._iCurs = ICURS_GOLD_LARGE;
		plr[p]._pGold = plr[p].HoldItem._ivalue * 40;
		for (i = 0; i < 40; i++) {
			GetPlrHandSeed(&plr[p].HoldItem);
			plr[p].InvList[plr[p]._pNumInv++] = plr[p].HoldItem;
			plr[p].InvGrid[i] = plr[p]._pNumInv;
		}
	}
#endif

	CalcPlrItemVals(p, FALSE);
}

BOOL ItemSpaceOk(int i, int j)
{
	int oi;

	if (i < 0 || i >= MAXDUNX || j < 0 || j >= MAXDUNY)
		return FALSE;

	if (dMonster[i][j])
		return FALSE;

	if (dPlayer[i][j])
		return FALSE;

	if (dItem[i][j])
		return FALSE;

	if (dObject[i][j]) {
		oi = dObject[i][j] > 0 ? dObject[i][j] - 1 : -(dObject[i][j] + 1);
		if (object[oi]._oSolidFlag)
			return FALSE;
	}

	if (dObject[i + 1][j + 1] > 0 && object[dObject[i + 1][j + 1] - 1]._oSelFlag)
		return FALSE;

	if (dObject[i + 1][j + 1] < 0 && object[-(dObject[i + 1][j + 1] + 1)]._oSelFlag)
		return FALSE;

	if (dObject[i + 1][j] > 0
	    && dObject[i][j + 1] > 0
	    && object[dObject[i + 1][j] - 1]._oSelFlag
	    && object[dObject[i][j + 1] - 1]._oSelFlag) {
		return FALSE;
	}

	return !nSolidTable[dPiece[i][j]];
}

BOOL GetItemSpace(int x, int y, char inum)
{
	int i, j, rs;
	int xx, yy;
	BOOL savail;

	yy = 0;
	for (j = y - 1; j <= y + 1; j++) {
		xx = 0;
		for (i = x - 1; i <= x + 1; i++) {
			itemhold[xx][yy] = ItemSpaceOk(i, j);
			xx++;
		}
		yy++;
	}

	savail = FALSE;
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			if (itemhold[i][j])
				savail = TRUE;
		}
	}

	rs = random(13, 15) + 1;

	if (!savail)
		return FALSE;

	xx = 0;
	yy = 0;
	while (rs > 0) {
		if (itemhold[xx][yy])
			rs--;
		if (rs > 0) {
			xx++;
			if (xx == 3) {
				xx = 0;
				yy++;
				if (yy == 3)
					yy = 0;
			}
		}
	}

	xx += x - 1;
	yy += y - 1;
	item[inum]._ix = xx;
	item[inum]._iy = yy;
	dItem[xx][yy] = inum + 1;

	return TRUE;
}

void GetSuperItemSpace(int x, int y, char inum)
{
	int xx, yy;
	int i, j, k;

	if (!GetItemSpace(x, y, inum)) {
		for (k = 2; k < 50; k++) {
			for (j = -k; j <= k; j++) {
				yy = y + j;
				for (i = -k; i <= k; i++) {
					xx = i + x;
					if (ItemSpaceOk(xx, yy)) {
						item[inum]._ix = xx;
						item[inum]._iy = yy;
						dItem[xx][yy] = inum + 1;
						return;
					}
				}
			}
		}
	}
}

void GetSuperItemLoc(int x, int y, int *xx, int *yy)
{
	int i, j, k;

	for (k = 1; k < 50; k++) {
		for (j = -k; j <= k; j++) {
			*yy = y + j;
			for (i = -k; i <= k; i++) {
				*xx = i + x;
				if (ItemSpaceOk(*xx, *yy)) {
					return;
				}
			}
		}
	}
}

void CalcItemValue(int i)
{
	int v;

	v = item[i]._iVMult1 + item[i]._iVMult2;
	if (v > 0) {
		v *= item[i]._ivalue;
	}
	if (v < 0) {
		v = item[i]._ivalue / v;
	}
	v = item[i]._iVAdd1 + item[i]._iVAdd2 + v;
	if (v <= 0) {
		v = 1;
	}
	item[i]._iIvalue = v;
}

void GetBookSpell(int i, int lvl)
{
	int rv, s, bs;

	if (!lvl)
		lvl = 1;
	rv = random(14, MAX_SPELLS) + 1;
	s = 1;
	while (rv > 0) {
		if (spelldata[s].sBookLvl != -1 && lvl >= spelldata[s].sBookLvl) {
			rv--;
			bs = s;
		}
		s++;
		if (gbMaxPlayers == 1) {
			if (s == SPL_RESURRECT)
				s = SPL_TELEKINESIS;
			if (s == SPL_HEALOTHER)
				s = SPL_FLARE;
		}
		if (s == MAX_SPELLS)
			s = 1;
	}
	strcat(item[i]._iName, spelldata[bs].sNameText);
	strcat(item[i]._iIName, spelldata[bs].sNameText);
	item[i]._iSpell = bs;
	item[i]._iMinMag = spelldata[bs].sMinInt;
	item[i]._ivalue += spelldata[bs].sBookCost;
	item[i]._iIvalue += spelldata[bs].sBookCost;
	if (spelldata[bs].sType == STYPE_FIRE)
		item[i]._iCurs = ICURS_BOOK_RED;
	if (spelldata[bs].sType == STYPE_LIGHTNING)
		item[i]._iCurs = ICURS_BOOK_BLUE;
	if (spelldata[bs].sType == STYPE_MAGIC)
		item[i]._iCurs = ICURS_BOOK_GREY;
}

void GetStaffPower(int i, int lvl, int bs, unsigned char onlygood)
{
	int v4;         // esi
	int v5;         // ebx
	int v6;         // edx
	int v7;         // ecx
	int v9;         // edi
	int v10;        // ecx
	int v11;        // ST14_4
	int v12;        // esi
	char *v13;      // edi
	int l[256];     // [esp+Ch] [ebp-484h]
	char istr[128]; // [esp+40Ch] [ebp-84h]
	int ia;         // [esp+48Ch] [ebp-4h]
	char *v17;      // [esp+49Ch] [ebp+Ch]

	v4 = lvl;
	ia = i;
	v5 = -1;
	if (!random(15, 10) || onlygood) {
		v6 = 0;
		v7 = 0;
		if (PL_Prefix[0].PLPower != -1) {
			do {
				if (PL_Prefix[v7].PLIType & 0x100 && PL_Prefix[v7].PLMinLvl <= v4 && (!onlygood || PL_Prefix[v7].PLOk)) {
					l[v6++] = v7;
					if (PL_Prefix[v7].PLDouble)
						l[v6++] = v7;
				}
				++v7;
			} while (PL_Prefix[v7].PLPower != -1);
			if (v6) {
				v5 = l[random(16, v6)];
				v9 = ia;
				v17 = item[ia]._iIName;
				sprintf(istr, "%s %s", PL_Prefix[v5].PLName, item[ia]._iIName);
				strcpy(v17, istr);
				v10 = ia;
				v11 = PL_Prefix[v5].PLMultVal;
				item[v9]._iMagical = ITEM_QUALITY_MAGIC;
				SaveItemPower(
				    v10,
				    PL_Prefix[v5].PLPower,
				    PL_Prefix[v5].PLParam1,
				    PL_Prefix[v5].PLParam2,
				    PL_Prefix[v5].PLMinVal,
				    PL_Prefix[v5].PLMaxVal,
				    v11);
				item[v9]._iPrePower = PL_Prefix[v5].PLPower;
			}
		}
	}
	v12 = ia;
	v13 = item[ia]._iIName;
	if (!control_WriteStringToBuffer((BYTE *)item[ia]._iIName)) {
		strcpy(v13, AllItemsList[item[v12].IDidx].iSName);
		if (v5 != -1) {
			sprintf(istr, "%s %s", PL_Prefix[v5].PLName, v13);
			strcpy(v13, istr);
		}
		sprintf(istr, "%s of %s", v13, spelldata[bs].sNameText);
		strcpy(v13, istr);
		if (item[v12]._iMagical == ITEM_QUALITY_NORMAL)
			strcpy(item[v12]._iName, v13);
	}
	CalcItemValue(ia);
}
// 420514: using guessed type int var_484[256];

void GetStaffSpell(int i, int lvl, unsigned char onlygood)
{
	int l;         // esi
	int rv;        // eax
	int s;         // ecx
	int minc;      // ebx
	int maxc;      // edx
	int v;         // eax
	char istr[64]; // [esp+4h] [ebp-4Ch]
	int bs;        // [esp+4Ch] [ebp-4h]

	if (random(17, 4)) {
		l = lvl >> 1;
		if (!l)
			l = 1;
		rv = random(18, MAX_SPELLS) + 1;
	LABEL_15:
		s = 1;
		while (rv > 0) {
			if (spelldata[s].sStaffLvl != -1 && l >= spelldata[s].sStaffLvl) {
				--rv;
				bs = s;
			}
			++s;
			if (gbMaxPlayers == 1) {
				if (s == SPL_RESURRECT)
					s = SPL_TELEKINESIS;
				if (s == SPL_HEALOTHER)
					s = SPL_FLARE;
			}
			if (s == MAX_SPELLS)
				goto LABEL_15;
		}
		sprintf(istr, "%s of %s", item[i]._iName, spelldata[bs].sNameText);
		if (!control_WriteStringToBuffer((BYTE *)istr))
			sprintf(istr, "Staff of %s", spelldata[bs].sNameText);
		strcpy(item[i]._iName, istr);
		strcpy(item[i]._iIName, istr);
		minc = spelldata[bs].sStaffMin;
		maxc = spelldata[bs].sStaffMax - minc + 1;
		item[i]._iSpell = bs;
		v = random(19, maxc) + minc;
		item[i]._iMinMag = spelldata[bs].sMinInt;
		item[i]._iCharges = v;
		item[i]._iMaxCharges = v;
		v = (v * spelldata[bs].sStaffCost) / 5;
		item[i]._ivalue += v;
		item[i]._iIvalue += v;
		GetStaffPower(i, lvl, bs, onlygood);
	} else {
		GetItemPower(i, lvl >> 1, lvl, 256, onlygood);
	}
}
// 679660: using guessed type char gbMaxPlayers;

void GetItemAttrs(int i, int idata, int lvl)
{
	int rndv;

	item[i]._itype = AllItemsList[idata].itype;
	item[i]._iCurs = AllItemsList[idata].iCurs;
	strcpy(item[i]._iName, AllItemsList[idata].iName);
	strcpy(item[i]._iIName, AllItemsList[idata].iName);
	item[i]._iLoc = AllItemsList[idata].iLoc;
	item[i]._iClass = AllItemsList[idata].iClass;
	item[i]._iMinDam = AllItemsList[idata].iMinDam;
	item[i]._iMaxDam = AllItemsList[idata].iMaxDam;
	item[i]._iAC = AllItemsList[idata].iMinAC + random(20, AllItemsList[idata].iMaxAC - AllItemsList[idata].iMinAC + 1);
	item[i]._iFlags = AllItemsList[idata].iFlags;
	item[i]._iMiscId = AllItemsList[idata].iMiscId;
	item[i]._iSpell = AllItemsList[idata].iSpell;
	item[i]._iMagical = ITEM_QUALITY_NORMAL;
	item[i]._ivalue = AllItemsList[idata].iValue;
	item[i]._iIvalue = AllItemsList[idata].iValue;
	item[i]._iVAdd1 = 0;
	item[i]._iVMult1 = 0;
	item[i]._iVAdd2 = 0;
	item[i]._iVMult2 = 0;
	item[i]._iPLDam = 0;
	item[i]._iPLToHit = 0;
	item[i]._iPLAC = 0;
	item[i]._iPLStr = 0;
	item[i]._iPLMag = 0;
	item[i]._iPLDex = 0;
	item[i]._iPLVit = 0;
	item[i]._iCharges = 0;
	item[i]._iMaxCharges = 0;
	item[i]._iDurability = AllItemsList[idata].iDurability;
	item[i]._iMaxDur = AllItemsList[idata].iDurability;
	item[i]._iMinStr = AllItemsList[idata].iMinStr;
	item[i]._iMinMag = AllItemsList[idata].iMinMag;
	item[i]._iMinDex = AllItemsList[idata].iMinDex;
	item[i]._iPLFR = 0;
	item[i]._iPLLR = 0;
	item[i]._iPLMR = 0;
	item[i].IDidx = idata;
	item[i]._iPLDamMod = 0;
	item[i]._iPLGetHit = 0;
	item[i]._iPLLight = 0;
	item[i]._iSplLvlAdd = 0;
	item[i]._iRequest = FALSE;
	item[i]._iFMinDam = 0;
	item[i]._iFMaxDam = 0;
	item[i]._iLMinDam = 0;
	item[i]._iLMaxDam = 0;
	item[i]._iPLEnAc = 0;
	item[i]._iPLMana = 0;
	item[i]._iPLHP = 0;
	item[i]._iPrePower = -1;
	item[i]._iSufPower = -1;

	if (AllItemsList[idata].iMiscId == IMISC_BOOK)
		GetBookSpell(i, lvl);

	if (item[i]._itype == ITYPE_GOLD) {
		if (gnDifficulty == DIFF_NORMAL)
			rndv = 5 * currlevel + random(21, 10 * currlevel);
		else
			rndv = lvl;

		if (gnDifficulty == DIFF_NIGHTMARE)
			rndv = 5 * (currlevel + 16) + random(21, 10 * (currlevel + 16));
		if (gnDifficulty == DIFF_HELL)
			rndv = 5 * (currlevel + 32) + random(21, 10 * (currlevel + 32));

		if (leveltype == DTYPE_HELL)
			rndv += rndv >> 3;
		if (rndv > 5000)
			rndv = 5000;

		item[i]._ivalue = rndv;

		if (rndv >= 2500)
			item[i]._iCurs = ICURS_GOLD_LARGE;
		else
			item[i]._iCurs = (rndv > 1000) + 4;
	}
}

int RndPL(int param1, int param2)
{
	return param1 + random(22, param2 - param1 + 1);
}

int PLVal(int pv, int p1, int p2, int minv, int maxv)
{
	if (p1 == p2)
		return minv;
	if (minv == maxv)
		return minv;
	return minv + (maxv - minv) * (100 * (pv - p1) / (p2 - p1)) / 100;
}

void SaveItemPower(int i, int power, int param1, int param2, int minval, int maxval, int multval)
{
	int v7;         // edi
	int v8;         // esi
	int v9;         // eax
	int v10;        // ebx
	int *v11;       // eax
	int *v12;       // eax
	int v13;        // edi
	int v14;        // eax
	int v15;        // edi
	int v16;        // eax
	int v17;        // eax
	int v18;        // ecx
	int v19;        // edx
	int v20;        // edi
	int *v21;       // edx
	int v22;        // eax
	int v23;        // eax
	int v24;        // eax
	int v25;        // eax
	int v26;        // eax
	int v27;        // eax
	int v28;        // ecx
	int *v29;       // eax
	int v30;        // ecx
	int *v31;       // eax
	int v32;        // ecx
	int v33;        // eax
	int v34;        // ST18_4
	int v35;        // eax
	int v36;        // ecx
	int v37;        // edx
	signed int v38; // ecx
	int v39;        // eax
	int v40;        // eax
	int v41;        // ecx
	int *v42;       // eax
	int v43;        // esi

	v7 = power;
	v8 = i;
	v9 = RndPL(param1, param2);
	v10 = v9;
	switch (v7) {
	case IPL_TOHIT:
		v11 = &item[v8]._iPLToHit;
		goto LABEL_115;
	case IPL_TOHIT_CURSE:
		v12 = &item[v8]._iPLToHit;
		goto LABEL_62;
	case IPL_DAMP:
		v11 = &item[v8]._iPLDam;
		goto LABEL_115;
	case IPL_DAMP_CURSE:
		v12 = &item[v8]._iPLDam;
		goto LABEL_62;
	case IPL_TOHIT_DAMP:
		v10 = RndPL(param1, param2);
		v13 = v8;
		item[v13]._iPLDam += v10;
		if (param1 == 20)
			v14 = RndPL(1, 5);
		else
			v14 = param1;
		if (param1 == 36)
			v14 = RndPL(6, 10);
		if (param1 == 51)
			v14 = RndPL(11, 15);
		if (param1 == 66)
			v14 = RndPL(16, 20);
		if (param1 == 81)
			v14 = RndPL(21, 30);
		if (param1 == 96)
			v14 = RndPL(31, 40);
		if (param1 == 111)
			v14 = RndPL(41, 50);
		if (param1 == 126)
			v14 = RndPL(51, 75);
		if (param1 == 151)
			v14 = RndPL(76, 100);
		item[v13]._iPLToHit += v14;
		break;
	case IPL_TOHIT_DAMP_CURSE:
		v15 = v8;
		item[v15]._iPLDam -= v9;
		if (param1 == 25)
			v16 = RndPL(1, 5);
		else
			v16 = param1;
		if (param1 == 50)
			v16 = RndPL(6, 10);
		item[v15]._iPLToHit -= v16;
		break;
	case IPL_ACP:
		v11 = &item[v8]._iPLAC;
		goto LABEL_115;
	case IPL_ACP_CURSE:
		v12 = &item[v8]._iPLAC;
		goto LABEL_62;
	case IPL_FIRERES:
		v11 = &item[v8]._iPLFR;
		goto LABEL_115;
	case IPL_LIGHTRES:
		v11 = &item[v8]._iPLLR;
		goto LABEL_115;
	case IPL_MAGICRES:
		v11 = &item[v8]._iPLMR;
		goto LABEL_115;
	case IPL_ALLRES:
		v17 = v8;
		item[v17]._iPLFR += v10;
		v18 = item[v8]._iPLFR;
		item[v17]._iPLLR += v10;
		item[v17]._iPLMR += v10;
		v19 = item[v8]._iPLLR;
		v20 = item[v8]._iPLMR;
		if (v18 < 0)
			item[v17]._iPLFR = 0;
		if (v19 < 0)
			item[v17]._iPLLR = 0;
		if (v20 < 0)
			item[v17]._iPLMR = 0;
		break;
	case IPL_SPLLVLADD:
		item[v8]._iSplLvlAdd = v9;
		break;
	case IPL_CHARGES:
		v21 = &item[v8]._iCharges;
		v22 = param1 * *v21;
		*v21 = v22;
		item[v8]._iMaxCharges = v22;
		break;
	case IPL_FIREDAM:
		v24 = v8;
		item[v24]._iFlags |= 0x10u;
		goto LABEL_77;
	case IPL_LIGHTDAM:
		v25 = v8;
		item[v25]._iFlags |= 0x20u;
		goto LABEL_79;
	case IPL_STR:
		v11 = &item[v8]._iPLStr;
		goto LABEL_115;
	case IPL_STR_CURSE:
		v12 = &item[v8]._iPLStr;
		goto LABEL_62;
	case IPL_MAG:
		v11 = &item[v8]._iPLMag;
		goto LABEL_115;
	case IPL_MAG_CURSE:
		v12 = &item[v8]._iPLMag;
		goto LABEL_62;
	case IPL_DEX:
		v11 = &item[v8]._iPLDex;
		goto LABEL_115;
	case IPL_DEX_CURSE:
		v12 = &item[v8]._iPLDex;
		goto LABEL_62;
	case IPL_VIT:
		v11 = &item[v8]._iPLVit;
		goto LABEL_115;
	case IPL_VIT_CURSE:
		v12 = &item[v8]._iPLVit;
		goto LABEL_62;
	case IPL_ATTRIBS:
		v26 = v8;
		item[v26]._iPLStr += v10;
		item[v26]._iPLMag += v10;
		item[v26]._iPLDex += v10;
		item[v26]._iPLVit += v10;
		break;
	case IPL_ATTRIBS_CURSE:
		v27 = v8;
		item[v27]._iPLStr -= v10;
		item[v27]._iPLMag -= v10;
		item[v27]._iPLDex -= v10;
		item[v27]._iPLVit -= v10;
		break;
	case IPL_GETHIT_CURSE:
		v11 = &item[v8]._iPLGetHit;
		goto LABEL_115;
	case IPL_GETHIT:
		v12 = &item[v8]._iPLGetHit;
		goto LABEL_62;
	case IPL_LIFE:
		v28 = v9 << 6;
		v29 = &item[v8]._iPLHP;
		goto LABEL_73;
	case IPL_LIFE_CURSE:
		v30 = v9 << 6;
		v31 = &item[v8]._iPLHP;
		goto LABEL_75;
	case IPL_MANA:
		item[v8]._iPLMana += v9 << 6;
		goto LABEL_92;
	case IPL_MANA_CURSE:
		item[v8]._iPLMana -= v9 << 6;
		goto LABEL_92;
	case IPL_DUR:
		v32 = v8;
		v33 = item[v8]._iMaxDur;
		v34 = v33;
		v35 = v10 * v33 / 100;
		item[v32]._iDurability += v35;
		item[v32]._iMaxDur = v35 + v34;
		break;
	case IPL_DUR_CURSE:
		v36 = v8;
		v37 = item[v8]._iMaxDur - v9 * item[v8]._iMaxDur / 100;
		item[v8]._iMaxDur = v37;
		if (v37 < 1)
			item[v36]._iMaxDur = 1;
		item[v36]._iDurability = item[v36]._iMaxDur;
		break;
	case IPL_INDESTRUCTIBLE:
		v38 = DUR_INDESTRUCTIBLE;
		goto LABEL_119;
	case IPL_LIGHT:
		v28 = param1;
		v29 = &item[v8]._iPLLight;
	LABEL_73:
		*v29 += v28;
		break;
	case IPL_LIGHT_CURSE:
		v30 = param1;
		v31 = &item[v8]._iPLLight;
	LABEL_75:
		*v31 -= v30;
		break;
	case IPL_FIRE_ARROWS:
		v24 = v8;
		item[v24]._iFlags |= 8u;
	LABEL_77:
		item[v24]._iFMinDam = param1;
		item[v24]._iFMaxDam = param2;
		break;
	case IPL_LIGHT_ARROWS:
		v25 = v8;
		_HIBYTE(item[v8]._iFlags) |= 2u;
	LABEL_79:
		item[v25]._iLMinDam = param1;
		item[v25]._iLMaxDam = param2;
		break;
	case IPL_INVCURS:
		item[v8]._iCurs = param1;
		break;
	case IPL_THORNS:
		_HIBYTE(item[v8]._iFlags) |= 4u;
		break;
	case IPL_NOMANA:
		_HIBYTE(item[v8]._iFlags) |= 8u;
		goto LABEL_92;
	case IPL_NOHEALPLR:
		BYTE1(item[v8]._iFlags) |= 1u;
		break;
	case IPL_ABSHALFTRAP:
		_HIBYTE(item[v8]._iFlags) |= 0x10u;
		break;
	case IPL_KNOCKBACK:
		BYTE1(item[v8]._iFlags) |= 8u;
		break;
	case IPL_NOHEALMON:
		BYTE1(item[v8]._iFlags) |= 0x10u;
		break;
	case IPL_STEALMANA:
		if (param1 == 3)
			BYTE1(item[v8]._iFlags) |= 0x20u;
		if (param1 == 5)
			BYTE1(item[v8]._iFlags) |= 0x40u;
	LABEL_92:
		drawmanaflag = TRUE;
		break;
	case IPL_STEALLIFE:
		if (param1 == 3)
			BYTE1(item[v8]._iFlags) |= 0x80u;
		if (param1 == 5)
			BYTE2(item[v8]._iFlags) |= 1u;
		drawhpflag = TRUE;
		break;
	case IPL_TARGAC:
		v11 = &item[v8]._iPLEnAc;
		goto LABEL_115;
	case IPL_FASTATTACK:
		if (param1 == 1)
			BYTE2(item[v8]._iFlags) |= 2u;
		if (param1 == 2)
			BYTE2(item[v8]._iFlags) |= 4u;
		if (param1 == 3)
			BYTE2(item[v8]._iFlags) |= 8u;
		if (param1 == 4)
			BYTE2(item[v8]._iFlags) |= 0x10u;
		break;
	case IPL_FASTRECOVER:
		if (param1 == 1)
			BYTE2(item[v8]._iFlags) |= 0x20u;
		if (param1 == 2)
			BYTE2(item[v8]._iFlags) |= 0x40u;
		if (param1 == 3)
			BYTE2(item[v8]._iFlags) |= 0x80u;
		break;
	case IPL_FASTBLOCK:
		_HIBYTE(item[v8]._iFlags) |= 1u;
		break;
	case IPL_DAMMOD:
		v11 = &item[v8]._iPLDamMod;
	LABEL_115:
		*v11 += v10;
		break;
	case IPL_RNDARROWVEL:
		item[v8]._iFlags |= 4u;
		break;
	case IPL_SETDAM:
		v39 = v8;
		item[v39]._iMinDam = param1;
		item[v39]._iMaxDam = param2;
		break;
	case IPL_SETDUR:
		v38 = param1;
	LABEL_119:
		v40 = v8;
		item[v40]._iDurability = v38;
		item[v40]._iMaxDur = v38;
		break;
	case IPL_NOMINSTR:
		item[v8]._iMinStr = 0;
		break;
	case IPL_SPELL:
		v23 = v8;
		item[v23]._iSpell = param1;
		item[v23]._iCharges = param1;
		item[v23]._iMaxCharges = param2;
		break;
	case IPL_FASTSWING:
		BYTE2(item[v8]._iFlags) |= 8u;
		break;
	case IPL_ONEHAND:
		item[v8]._iLoc = ILOC_ONEHAND;
		break;
	case IPL_3XDAMVDEM:
		_HIBYTE(item[v8]._iFlags) |= 0x40u;
		break;
	case IPL_ALLRESZERO:
		_HIBYTE(item[v8]._iFlags) |= 0x80u;
		break;
	case IPL_DRAINLIFE:
		item[v8]._iFlags |= 0x40u;
		break;
	case IPL_RNDSTEALLIFE:
		item[v8]._iFlags |= 2u;
		break;
	case IPL_INFRAVISION:
		item[v8]._iFlags |= 1u;
		break;
	case IPL_SETAC:
		item[v8]._iAC = v9;
		break;
	case IPL_ADDACLIFE:
		item[v8]._iPLHP = (plr[myplr]._pIBonusAC + plr[myplr]._pIAC + plr[myplr]._pDexterity / 5) << 6;
		break;
	case IPL_ADDMANAAC:
		item[v8]._iAC += (plr[myplr]._pMaxManaBase >> 6) / 10;
		break;
	case IPL_FIRERESCLVL:
		v41 = 30 - plr[myplr]._pLevel;
		v42 = &item[v8]._iPLFR;
		*v42 = v41;
		if (v41 < 0)
			*v42 = 0;
		break;
	case IPL_AC_CURSE:
		v12 = &item[v8]._iAC;
	LABEL_62:
		*v12 -= v10;
		break;
	}
	v43 = v8;
	if (item[v43]._iVAdd1 || item[v43]._iVMult1) {
		item[v43]._iVAdd2 = PLVal(v10, param1, param2, minval, maxval);
		item[v43]._iVMult2 = multval;
	} else {
		item[v43]._iVAdd1 = PLVal(v10, param1, param2, minval, maxval);
		item[v43]._iVMult1 = multval;
	}
}

void GetItemPower(int i, int minlvl, int maxlvl, int flgs, int onlygood)
{
	//int v6; // ecx
	int pre; // esi
	//int v9; // ecx
	unsigned char goe; // bl
	int v11;           // edx
	int v14;           // ecx
	int l[256];        // [esp+4h] [ebp-494h]
	char istr[128];    // [esp+404h] [ebp-94h]
	int post;          // [esp+488h] [ebp-10h]
	int sufidx;        // [esp+48Ch] [ebp-Ch]
	int preidx;        // [esp+490h] [ebp-8h]

	pre = random(23, 4);
	post = random(23, 3);
	if (pre && !post) {
		if (random(23, 2))
			post = 1;
		else
			pre = 0;
	}
	preidx = -1;
	sufidx = -1;
	goe = 0;
	if (!onlygood) {
		if (random(0, 3))
			onlygood = 1;
	}
	if (!pre) {
		v11 = 0;
		if (PL_Prefix[0].PLPower != -1) {
			v14 = 0;
			do {
				if (flgs & PL_Prefix[v14].PLIType) {
					if (PL_Prefix[v14].PLMinLvl >= minlvl && PL_Prefix[v14].PLMinLvl <= maxlvl && (!onlygood || PL_Prefix[v14].PLOk) && (flgs != 256 || PL_Prefix[v14].PLPower != 15)) {
						l[v11++] = v14;
						if (PL_Prefix[v14].PLDouble)
							l[v11++] = v14;
					}
				}
				v14++;
			} while (PL_Prefix[v14].PLPower != -1);
			if (v11) {
				preidx = l[random(23, v11)];
				sprintf(istr, "%s %s", PL_Prefix[preidx].PLName, item[i]._iIName);
				strcpy(item[i]._iIName, istr);
				item[i]._iMagical = ITEM_QUALITY_MAGIC;
				SaveItemPower(
				    i,
				    PL_Prefix[preidx].PLPower,
				    PL_Prefix[preidx].PLParam1,
				    PL_Prefix[preidx].PLParam2,
				    PL_Prefix[preidx].PLMinVal,
				    PL_Prefix[preidx].PLMaxVal,
				    PL_Prefix[preidx].PLMultVal);
				goe = PL_Prefix[preidx].PLGOE;
				item[i]._iPrePower = PL_Prefix[preidx].PLPower;
			}
		}
	}
	if (post) {
		v11 = 0;
		if (PL_Suffix[0].PLPower != -1) {
			v14 = 0;
			do {
				if (flgs & PL_Suffix[v14].PLIType) {
					if (PL_Suffix[v14].PLMinLvl >= minlvl && PL_Suffix[v14].PLMinLvl <= maxlvl && (goe | PL_Suffix[v14].PLGOE) != 0x11 && (!onlygood || PL_Suffix[v14].PLOk))
						l[v11++] = v14;
				}
				v14++;
			} while (PL_Suffix[v14].PLPower != -1);
			if (v11) {
				sufidx = l[random(23, v11)];
				sprintf(istr, "%s of %s", item[i]._iIName, PL_Suffix[sufidx].PLName);
				strcpy(item[i]._iIName, istr);
				item[i]._iMagical = ITEM_QUALITY_MAGIC;
				SaveItemPower(
				    i,
				    PL_Suffix[sufidx].PLPower,
				    PL_Suffix[sufidx].PLParam1,
				    PL_Suffix[sufidx].PLParam2,
				    PL_Suffix[sufidx].PLMinVal,
				    PL_Suffix[sufidx].PLMaxVal,
				    PL_Suffix[sufidx].PLMultVal);
				item[i]._iSufPower = PL_Suffix[sufidx].PLPower;
			}
		}
	}
	if (!control_WriteStringToBuffer((BYTE *)item[i]._iIName)) {
		strcpy(item[i]._iIName, AllItemsList[item[i].IDidx].iSName);
		if (preidx != -1) {
			sprintf(istr, "%s %s", PL_Prefix[preidx].PLName, item[i]._iIName);
			strcpy(item[i]._iIName, istr);
		}
		if (sufidx != -1) {
			sprintf(istr, "%s of %s", item[i]._iIName, PL_Suffix[sufidx].PLName);
			strcpy(item[i]._iIName, istr);
		}
	}
	if (preidx != -1 || sufidx != -1)
		CalcItemValue(i);
}
// 4215EF: using guessed type int var_494[256];

void GetItemBonus(int i, int idata, int minlvl, int maxlvl, int onlygood)
{
	if (item[i]._iClass != ICLASS_GOLD) {
		if (minlvl > 25)
			minlvl = 25;

		switch (item[i]._itype) {
		case ITYPE_SWORD:
		case ITYPE_AXE:
		case ITYPE_MACE:
			GetItemPower(i, minlvl, maxlvl, 0x1000, onlygood);
			break;
		case ITYPE_BOW:
			GetItemPower(i, minlvl, maxlvl, 0x10, onlygood);
			break;
		case ITYPE_SHIELD:
			GetItemPower(i, minlvl, maxlvl, 0x10000, onlygood);
			break;
		case ITYPE_LARMOR:
		case ITYPE_HELM:
		case ITYPE_MARMOR:
		case ITYPE_HARMOR:
			GetItemPower(i, minlvl, maxlvl, 0x100000, onlygood);
			break;
		case ITYPE_STAFF:
			GetStaffSpell(i, maxlvl, onlygood);
			break;
		case ITYPE_RING:
		case ITYPE_AMULET:
			GetItemPower(i, minlvl, maxlvl, 1, onlygood);
			break;
		}
	}
}

void SetupItem(int i)
{
	int it, il;

	it = ItemCAnimTbl[item[i]._iCurs];
	item[i]._iAnimWidth = 96;
	item[i]._iAnimWidth2 = 16;
	item[i]._iAnimData = itemanims[it];
	il = ItemAnimLs[it];
	item[i]._iAnimLen = il;
	item[i]._iIdentified = FALSE;
	item[i]._iPostDraw = FALSE;

	if (!plr[myplr].pLvlLoad) {
		item[i]._iSelFlag = 0;
		il = 1;
		item[i]._iAnimFlag = TRUE;
	} else {
		item[i]._iAnimFlag = FALSE;
		item[i]._iSelFlag = 1;
	}

	item[i]._iAnimFrame = il;
}

int RndItem(int m)
{
	int i, ri;
	int ril[512];

	if ((monster[m].MData->mTreasure & 0x8000) != 0)
		return -1 - (monster[m].MData->mTreasure & 0xFFF);

	if (monster[m].MData->mTreasure & 0x4000)
		return 0;

	if (random(24, 100) > 40)
		return 0;

	if (random(24, 100) > 25)
		return 1;

	ri = 0;
	for (i = 0; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd == 2 && monster[m].mLevel >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
		}
		if (AllItemsList[i].iRnd && monster[m].mLevel >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
		}
		if (AllItemsList[i].iSpell == SPL_RESURRECT && gbMaxPlayers == 1)
			ri--;
		if (AllItemsList[i].iSpell == SPL_HEALOTHER && gbMaxPlayers == 1)
			ri--;
	}

	return ril[random(24, ri)] + 1;
}
// 679660: using guessed type char gbMaxPlayers;

int RndUItem(int m)
{
	int i, ri;
	int ril[512];
	BOOL okflag;

	if (m != -1 && (monster[m].MData->mTreasure & 0x8000) != 0 && gbMaxPlayers == 1)
		return -1 - (monster[m].MData->mTreasure & 0xFFF);

	ri = 0;
	for (i = 0; AllItemsList[i].iLoc != -1; i++) {
		okflag = TRUE;
		if (!AllItemsList[i].iRnd)
			okflag = FALSE;
		if (m != -1) {
			if (monster[m].mLevel < AllItemsList[i].iMinMLvl)
				okflag = FALSE;
		} else {
			if (2 * currlevel < AllItemsList[i].iMinMLvl)
				okflag = FALSE;
		}
		if (AllItemsList[i].itype == ITYPE_MISC)
			okflag = FALSE;
		if (AllItemsList[i].itype == ITYPE_GOLD)
			okflag = FALSE;
		if (AllItemsList[i].itype == ITYPE_0E)
			okflag = FALSE;
		if (AllItemsList[i].iMiscId == IMISC_BOOK)
			okflag = TRUE;
		if (AllItemsList[i].iSpell == SPL_RESURRECT && gbMaxPlayers == 1)
			okflag = FALSE;
		if (AllItemsList[i].iSpell == SPL_HEALOTHER && gbMaxPlayers == 1)
			okflag = FALSE;
		if (okflag) {
			ril[ri] = i;
			ri++;
		}
	}

	return ril[random(25, ri)];
}
// 679660: using guessed type char gbMaxPlayers;

int RndAllItems()
{
	int i, ri;
	int ril[512];

	if (random(26, 100) > 25)
		return 0;

	ri = 0;
	for (i = 0; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd && 2 * currlevel >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
		}
		if (AllItemsList[i].iSpell == SPL_RESURRECT && gbMaxPlayers == 1)
			ri--;
		if (AllItemsList[i].iSpell == SPL_HEALOTHER && gbMaxPlayers == 1)
			ri--;
	}

	return ril[random(26, ri)];
}
// 679660: using guessed type char gbMaxPlayers;

int RndTypeItems(int itype, int imid)
{
	int i;          // edi
	BOOLEAN okflag; // esi
	int ril[512];   // [esp+4h] [ebp-80Ch]
	int ri;         // [esp+80Ch] [ebp-4h]

	ri = 0;
	i = 0;

	if (AllItemsList[0].iLoc != -1) {
		do {
			okflag = 1;
			if (!AllItemsList[i].iRnd)
				okflag = 0;
			if (2 * currlevel < AllItemsList[i].iMinMLvl)
				okflag = 0;
			if (AllItemsList[i].itype != itype)
				okflag = 0;
			if (imid != -1 && AllItemsList[i].iMiscId != imid)
				okflag = 0;
			if (okflag)
				ril[ri++] = i;
			++i;
		} while (AllItemsList[i].iLoc != -1);
	}

	return ril[random(27, ri)];
}
// 421CB7: using guessed type int var_80C[512];

int CheckUnique(int i, int lvl, int uper, BOOLEAN recreate)
{
	int numu;      // ebx
	int j;         // esi
	int idata;     // eax
	char uok[128]; // [esp+8h] [ebp-84h]

	if (random(28, 100) > uper)
		return -1;
	numu = 0;
	memset(uok, 0, sizeof(uok));

	if (UniqueItemList[0].UIItemId == -1)
		return -1;
	j = 0;
	do {
		if (UniqueItemList[j].UIItemId == AllItemsList[item[i].IDidx].iItemId
		    && lvl >= UniqueItemList[j].UIMinLvl
		    && (recreate || !UniqueItemFlag[j] || gbMaxPlayers != 1)) {
			uok[j] = 1;
			++numu;
		}
		j++;
	} while (UniqueItemList[j].UIItemId != -1);
	if (!numu)
		return -1;

	random(29, 10);
	idata = 0;
	if (numu > 0) {
		while (1) {
			if (uok[idata])
				--numu;
			if (numu <= 0)
				break;
			if (++idata == 128)
				idata = 0;
		}
	}
	return idata;
}
// 679660: using guessed type char gbMaxPlayers;
// 421D41: using guessed type char var_84[128];

void GetUniqueItem(int i, int uid)
{
	UniqueItemFlag[uid] = 1;
	SaveItemPower(i, UniqueItemList[uid].UIPower1, UniqueItemList[uid].UIParam1, UniqueItemList[uid].UIParam2, 0, 0, 1);

	if (UniqueItemList[uid].UINumPL > 1)
		SaveItemPower(i, UniqueItemList[uid].UIPower2, UniqueItemList[uid].UIParam3, UniqueItemList[uid].UIParam4, 0, 0, 1);
	if (UniqueItemList[uid].UINumPL > 2)
		SaveItemPower(i, UniqueItemList[uid].UIPower3, UniqueItemList[uid].UIParam5, UniqueItemList[uid].UIParam6, 0, 0, 1);
	if (UniqueItemList[uid].UINumPL > 3)
		SaveItemPower(i, UniqueItemList[uid].UIPower4, UniqueItemList[uid].UIParam7, UniqueItemList[uid].UIParam8, 0, 0, 1);
	if (UniqueItemList[uid].UINumPL > 4)
		SaveItemPower(i, UniqueItemList[uid].UIPower5, UniqueItemList[uid].UIParam9, UniqueItemList[uid].UIParam10, 0, 0, 1);
	if (UniqueItemList[uid].UINumPL > 5)
		SaveItemPower(i, UniqueItemList[uid].UIPower6, UniqueItemList[uid].UIParam11, UniqueItemList[uid].UIParam12, 0, 0, 1);

	strcpy(item[i]._iIName, UniqueItemList[uid].UIName);
	item[i]._iIvalue = UniqueItemList[uid].UIValue;

	if (item[i]._iMiscId == IMISC_UNIQUE)
		item[i]._iSeed = uid;

	item[i]._iCreateInfo |= 0x0200;
	item[i]._iUid = uid;
	item[i]._iMagical = ITEM_QUALITY_UNIQUE;
}

void SpawnUnique(int uid, int x, int y)
{
	int ii;    // esi
	int itype; // edx

	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, itemavail[0]);
		itype = 0;
		itemactive[numitems] = ii;
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];

		if (AllItemsList[0].iItemId != UniqueItemList[uid].UIItemId) {
			while (AllItemsList[itype].iItemId != UniqueItemList[uid].UIItemId) {
				itype++;
			}
		}

		GetItemAttrs(ii, itype, currlevel);
		GetUniqueItem(ii, uid);
		SetupItem(ii);
		++numitems;
	}
}
// 421F5C: could not find valid save-restore pair for esi

void ItemRndDur(int ii)
{
	if (item[ii]._iDurability && item[ii]._iDurability != DUR_INDESTRUCTIBLE)
		item[ii]._iDurability = random(0, item[ii]._iMaxDur >> 1) + (item[ii]._iMaxDur >> 2) + 1;
}

void SetupAllItems(int ii, int idx, int iseed, int lvl, int uper, int onlygood, int recreate, int pregen)
{
	int iblvl;
	int uid;

	item[ii]._iSeed = iseed;
	SetRndSeed(iseed);
	GetItemAttrs(ii, idx, lvl >> 1);
	item[ii]._iCreateInfo = lvl;

	if (pregen)
		item[ii]._iCreateInfo = lvl | 0x8000;
	if (onlygood)
		item[ii]._iCreateInfo |= 0x40;

	if (uper == 15)
		item[ii]._iCreateInfo |= 0x80;
	else if (uper == 1)
		item[ii]._iCreateInfo |= 0x0100;

	if (item[ii]._iMiscId != IMISC_UNIQUE) {
		iblvl = -1;
		if (random(32, 100) > 10 && random(33, 100) > lvl || (iblvl = lvl, lvl == -1)) {

			if (item[ii]._iMiscId != IMISC_STAFF || (iblvl = lvl, lvl == -1)) {
				if (item[ii]._iMiscId != IMISC_RING || (iblvl = lvl, lvl == -1)) {
					if (item[ii]._iMiscId == IMISC_AMULET)
						iblvl = lvl;
				}
			}
		}
		if (onlygood)
			iblvl = lvl;
		if (uper == 15)
			iblvl = lvl + 4;
		if (iblvl != -1) {
			uid = CheckUnique(ii, iblvl, uper, recreate);
			if (uid == -1) {
				GetItemBonus(ii, idx, iblvl >> 1, iblvl, onlygood);
			} else {
				GetUniqueItem(ii, uid);
				item[ii]._iCreateInfo |= 0x0200;
			}
		}
		if (item[ii]._iMagical != ITEM_QUALITY_UNIQUE)
			ItemRndDur(ii);
	} else {
		if (item[ii]._iLoc != ILOC_UNEQUIPABLE)
			GetUniqueItem(ii, iseed);
	}
	SetupItem(ii);
}

void SpawnItem(int m, int x, int y, BOOL sendmsg)
{
	int ii;       // edi
	int onlygood; // [esp+Ch] [ebp-Ch]
	int idx;      // [esp+14h] [ebp-4h]

	if (!monster[m]._uniqtype && ((monster[m].MData->mTreasure & 0x8000) == 0 || gbMaxPlayers == 1)) {
		if (quests[QTYPE_BLKM]._qactive == 2 && quests[QTYPE_BLKM]._qvar1 == QS_MUSHGIVEN) {
			idx = IDI_BRAIN;
			quests[QTYPE_BLKM]._qvar1 = QS_BRAINSPAWNED;
			goto LABEL_13;
		}
		idx = RndItem(m);
		if (!idx)
			return;
		if (idx > 0) {
			onlygood = 0;
			idx--;
			goto LABEL_13;
		}
	LABEL_10:
		SpawnUnique(-1 - idx, x, y);
		return;
	}
	idx = RndUItem(m);
	if (idx < 0)
		goto LABEL_10;
	onlygood = 1;
LABEL_13:
	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, itemavail[0]);
		itemactive[numitems] = ii;
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];

		if (!monster[m]._uniqtype)
			SetupAllItems(ii, idx, GetRndSeed(), monster[m].MData->mLevel, 1, onlygood, 0, 0);
		else
			SetupAllItems(ii, idx, GetRndSeed(), monster[m].MData->mLevel, 15, onlygood, 0, 0);

		++numitems;
		if (sendmsg)
			NetSendCmdDItem(FALSE, ii);
	}
}
// 679660: using guessed type char gbMaxPlayers;

void CreateItem(int uid, int x, int y)
{
	int ii;  // esi
	int idx; // edx

	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, itemavail[0]);
		idx = 0;
		itemactive[numitems] = ii;
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];

		if (AllItemsList[0].iItemId != UniqueItemList[uid].UIItemId) {
			while (AllItemsList[idx].iItemId != UniqueItemList[uid].UIItemId) {
				idx++;
			}
		}

		GetItemAttrs(ii, idx, currlevel);
		GetUniqueItem(ii, uid);
		SetupItem(ii);
		++numitems;
		item[ii]._iMagical = ITEM_QUALITY_UNIQUE;
	}
}
// 422290: could not find valid save-restore pair for esi

void CreateRndItem(int x, int y, unsigned char onlygood, unsigned char sendmsg, int delta)
{
	int idx; // edi
	int ii;  // esi

	if (onlygood)
		idx = RndUItem(-1);
	else
		idx = RndAllItems();

	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, itemavail[0]);
		itemactive[numitems] = ii;
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		SetupAllItems(ii, idx, GetRndSeed(), 2 * currlevel, 1, onlygood, 0, delta);

		if (sendmsg)
			NetSendCmdDItem(FALSE, ii);
		if (delta)
			DeltaAddItem(ii);

		++numitems;
	}
}

void SetupAllUseful(int ii, int iseed, int lvl)
{
	int idx; // esi

	item[ii]._iSeed = iseed;
	SetRndSeed(iseed);
	idx = 25 - (random(34, 2) != 0);

	if (lvl > 1) {
		if (!random(34, 3))
			idx = 27; // unique?
	}

	GetItemAttrs(ii, idx, lvl);
	item[ii]._iCreateInfo = lvl + 0x180;
	SetupItem(ii);
}

void CreateRndUseful(int pnum, int x, int y, BOOL sendmsg)
{
	int ii;

	if (numitems < MAXITEMS) {
		ii = itemactive[0];
		GetSuperItemSpace(x, y, ii);
		itemactive[0]       = itemactive[MAXITEMS - numitems -1];
		itemavail[numitems] = ii;
		SetupAllUseful(ii, GetRndSeed(), currlevel);
		if (sendmsg) {
			NetSendCmdDItem(FALSE, ii);
		}
		numitems++;
	}
}

void CreateTypeItem(int x, int y, unsigned char onlygood, int itype, int imisc, int sendmsg, int delta)
{
	int idx; // edi
	int ii;  // esi

	if (itype == ITYPE_GOLD)
		idx = 0;
	else
		idx = RndTypeItems(itype, imisc);

	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, itemavail[0]);
		itemactive[numitems] = ii;
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		SetupAllItems(ii, idx, GetRndSeed(), 2 * currlevel, 1, onlygood, 0, delta);

		if (sendmsg)
			NetSendCmdDItem(FALSE, ii);
		if (delta)
			DeltaAddItem(ii);

		++numitems;
	}
}

void RecreateItem(int ii, int idx, unsigned short ic, int iseed, int ivalue)
{
	int uper, onlygood, recreate, pregen;

	if (!idx) {
		SetPlrHandItem(&item[ii], IDI_GOLD);
		item[ii]._iSeed = iseed;
		item[ii]._iCreateInfo = ic;
		item[ii]._ivalue = ivalue;
		if (ivalue >= 2500)
			item[ii]._iCurs = ICURS_GOLD_LARGE;
		else if (ivalue <= 1000)
			item[ii]._iCurs = ICURS_GOLD_SMALL;
		else
			item[ii]._iCurs = ICURS_GOLD_MEDIUM;
	} else {
		if (!ic) {
			SetPlrHandItem(&item[ii], idx);
			SetPlrHandSeed(&item[ii], iseed);
		} else {
			if (ic & 0x7C00) {
				RecreateTownItem(ii, idx, ic, iseed, ivalue);
			} else if ((ic & 0x0180) == 0x0180) {
				SetupAllUseful(ii, iseed, ic & 0x3F);
			} else {
				uper = 0;
				onlygood = 0;
				recreate = 0;
				pregen = 0;
				if (ic & 0x0100)
					uper = 1;
				if (ic & 0x80)
					uper = 15;
				if (ic & 0x40)
					onlygood = 1;
				if (ic & 0x0200)
					recreate = 1;
				if (ic & 0x8000)
					pregen = 1;
				SetupAllItems(ii, idx, iseed, ic & 0x3F, uper, onlygood, recreate, pregen);
			}
		}
	}
}

void RecreateEar(int ii, unsigned short ic, int iseed, int Id, int dur, int mdur, int ch, int mch, int ivalue, int ibuff)
{
	SetPlrHandItem(&item[ii], IDI_EAR);
	tempstr[0] = (ic >> 8) & 0x7F;
	tempstr[1] = ic & 0x7F;
	tempstr[2] = (iseed >> 24) & 0x7F;
	tempstr[3] = (iseed >> 16) & 0x7F;
	tempstr[4] = (iseed >> 8) & 0x7F;
	tempstr[5] = iseed & 0x7F;
	tempstr[6] = Id & 0x7F;
	tempstr[7] = dur & 0x7F;
	tempstr[8] = mdur & 0x7F;
	tempstr[9] = ch & 0x7F;
	tempstr[10] = mch & 0x7F;
	tempstr[11] = (ivalue >> 8) & 0x7F;
	tempstr[12] = (ibuff >> 24) & 0x7F;
	tempstr[13] = (ibuff >> 16) & 0x7F;
	tempstr[14] = (ibuff >> 8) & 0x7F;
	tempstr[15] = ibuff & 0x7F;
	tempstr[16] = '\0';
	sprintf(item[ii]._iName, "Ear of %s", tempstr);
	item[ii]._iCurs = ((ivalue >> 6) & 3) + 19;
	item[ii]._iCreateInfo = ic;
	item[ii]._ivalue = ivalue & 0x3F;
	item[ii]._iSeed = iseed;
}

void SpawnQuestItem(int itemid, int x, int y, int randarea, int selflag)
{
	BOOL failed;
	int i, j, tries;

	if (randarea) {
		tries = 0;
		while (1) {
			tries++;
			if (tries > 1000 && randarea > 1)
				randarea--;
			x = random(0, MAXDUNX);
			y = random(0, MAXDUNY);
			failed = FALSE;
			for (i = 0; i < randarea && !failed; i++) {
				for (j = 0; j < randarea && !failed; j++) {
					failed = !ItemSpaceOk(i + x, j + y);
				}
			}
			if (!failed)
				break;
		}
	}

	if (numitems < MAXITEMS) {
		i = itemavail[0];
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		itemactive[numitems] = i;
		item[i]._ix = x;
		item[i]._iy = y;
		dItem[x][y] = i + 1;
		GetItemAttrs(i, itemid, currlevel);
		SetupItem(i);
		item[i]._iPostDraw = TRUE;
		if (selflag) {
			item[i]._iAnimFlag = FALSE;
			item[i]._iSelFlag = selflag;
			item[i]._iAnimFrame = item[i]._iAnimLen;
		}
		++numitems;
	}
}

void SpawnRock()
{
	BOOL v0; // edx
	int v1;  // eax
	int v2;  // ecx
	BOOL v3; // ebx
	int v4;  // ebx
	int v5;  // ecx
	int v6;  // esi
	int *v7; // edx
	int v8;  // eax
	int v9;  // edi
	int v10; // ST04_4
	//int v11; // [esp+8h] [ebp-4h]

	v0 = 0;
	v1 = 0;
	if (nobjects > 0) {
		v2 = 0; //v11; /* chceck */
		while (!v0) {
			v2 = objectactive[v1];
			v3 = object[objectactive[v1++]]._otype == OBJ_STAND;
			v0 = v3;
			if (v1 >= nobjects) {
				if (!v3)
					return;
				break;
			}
		}
		v4 = itemavail[0];
		v5 = v2;
		v6 = itemavail[0];
		v7 = &itemavail[MAXITEMS - numitems - 1];
		itemactive[numitems] = itemavail[0];
		v8 = object[v5]._ox;
		item[v6]._ix = v8;
		v9 = object[v5]._oy;
		itemavail[0] = *v7;
		dItem[v8][v9] = v4 + 1;
		v10 = currlevel;
		item[v6]._iy = v9;
		GetItemAttrs(v4, IDI_ROCK, v10);
		SetupItem(v4);
		++numitems;
		item[v6]._iSelFlag = 2;
		item[v6]._iPostDraw = TRUE;
		item[v6]._iAnimFrame = 11;
	}
}

void RespawnItem(int i, BOOL FlipFlag)
{
	int it; // ecx
	int il; // eax

	item[i]._iAnimWidth = 96;
	item[i]._iAnimWidth2 = 16;
	it = ItemCAnimTbl[item[i]._iCurs];
	il = ItemAnimLs[it];
	item[i]._iAnimLen = il;
	item[i]._iAnimData = itemanims[it];
	item[i]._iPostDraw = FALSE;
	item[i]._iRequest = FALSE;

	if (FlipFlag) {
		item[i]._iSelFlag = 0;
		il = 1;
		item[i]._iAnimFlag = TRUE;
	} else {
		item[i]._iAnimFlag = FALSE;
		item[i]._iSelFlag = 1;
	}

	item[i]._iAnimFrame = il;

	if (item[i]._iCurs == ICURS_MAGIC_ROCK) {
		item[i]._iSelFlag = 1;
		PlaySfxLoc(ItemDropSnds[it], item[i]._ix, item[i]._iy);
	}
	if (item[i]._iCurs == ICURS_TAVERN_SIGN)
		item[i]._iSelFlag = 1;
	if (item[i]._iCurs == ICURS_ANVIL_OF_FURY)
		item[i]._iSelFlag = 1;
}

void DeleteItem(int ii, int i)
{
	itemavail[MAXITEMS - numitems] = ii;
	numitems--;
	if (numitems > 0 && i != numitems)
		itemactive[i] = itemactive[numitems];
}

void ItemDoppel()
{
	int idoppelx;  // esi
	ItemStruct *i; // edx

	if (gbMaxPlayers != 1) {
		for (idoppelx = 16; idoppelx < 96; idoppelx++) {
			if (dItem[idoppelx][idoppely]) {
				i = &item[dItem[idoppelx][idoppely] - 1];
				if (i->_ix != idoppelx || i->_iy != idoppely)
					dItem[idoppelx][idoppely] = 0;
			}
		}
		idoppely++;
		if (idoppely == 96)
			idoppely = 16;
	}
}

void ProcessItems()
{
	int i;  // edi
	int ii; // esi

	for (i = 0; i < numitems; i++) {
		ii = itemactive[i];
		if (item[ii]._iAnimFlag) {
			item[ii]._iAnimFrame++;
			if (item[ii]._iCurs == ICURS_MAGIC_ROCK) {
				if (item[ii]._iSelFlag == 1 && item[ii]._iAnimFrame == 11)
					item[ii]._iAnimFrame = 1;
				if (item[ii]._iSelFlag == 2 && item[ii]._iAnimFrame == 21)
					item[ii]._iAnimFrame = 11;
			} else {
				if (item[ii]._iAnimFrame == item[ii]._iAnimLen >> 1)
					PlaySfxLoc(ItemDropSnds[ItemCAnimTbl[item[ii]._iCurs]], item[ii]._ix, item[ii]._iy);

				if (item[ii]._iAnimFrame >= item[ii]._iAnimLen) {
					item[ii]._iAnimFlag = FALSE;
					item[ii]._iAnimFrame = item[ii]._iAnimLen;
					item[ii]._iSelFlag = 1;
				}
			}
		}
	}
	ItemDoppel();
}

void FreeItemGFX()
{
	int i;

	for (i = 0; i < 35; i++) {
		MemFreeDbg(itemanims[i]);
	}
}

void GetItemFrm(int i)
{
	item[i]._iAnimData = itemanims[ItemCAnimTbl[item[i]._iCurs]];
}

void GetItemStr(int i)
{
	int nGold; // esi

	if (item[i]._itype == ITYPE_GOLD) {
		nGold = item[i]._ivalue;
		sprintf(infostr, "%i gold %s", nGold, get_pieces_str(nGold));
	} else {
		if (!item[i]._iIdentified)
			strcpy(infostr, item[i]._iName);
		else
			strcpy(infostr, item[i]._iIName);

		if (item[i]._iMagical == ITEM_QUALITY_MAGIC)
			infoclr = COL_BLUE;
		if (item[i]._iMagical == ITEM_QUALITY_UNIQUE)
			infoclr = COL_GOLD;
	}
}
// 4B883C: using guessed type int infoclr;

void CheckIdentify(int pnum, int cii)
{
	ItemStruct *pi; // esi

	pi = &plr[pnum].InvBody[cii];
	pi->_iIdentified = TRUE;

	CalcPlrInv(pnum, 1);

	if (pnum == myplr)
		SetCursor_(CURSOR_HAND);
}

void DoRepair(int pnum, int cii)
{
	PlayerStruct *p; // eax
	ItemStruct *pi;  // esi

	p = &plr[pnum];
	pi = &p->InvBody[cii];

	PlaySfxLoc(IS_REPAIR, p->WorldX, p->WorldY);
	RepairItem(pi, p->_pLevel);
	CalcPlrInv(pnum, 1);

	if (pnum == myplr)
		SetCursor_(CURSOR_HAND);
}

void RepairItem(ItemStruct *i, int lvl)
{
	int rep; // edi
	int d;   // eax

	if (i->_iDurability != i->_iMaxDur) {
		if (i->_iMaxDur > 0) {
			rep = 0;
			while (1) {
				rep += lvl + random(37, lvl);
				d = i->_iMaxDur / (lvl + 9);

				if (d < 1)
					d = 1;
				if (i->_iMaxDur == d)
					break;

				i->_iMaxDur -= d;

				if (rep + i->_iDurability >= i->_iMaxDur) {
					i->_iDurability += rep;
					if (i->_iDurability > i->_iMaxDur)
						i->_iDurability = i->_iMaxDur;
					return;
				}
			}
		}
		i->_itype = ITYPE_NONE;
	}
}

void DoRecharge(int pnum, int cii)
{
	PlayerStruct *p; // eax
	ItemStruct *pi;  // esi

	p = &plr[pnum];
	pi = &p->InvBody[cii];

	if (pi->_itype == ITYPE_STAFF && pi->_iSpell) {
		RechargeItem(pi, random(38, p->_pLevel / spelldata[pi->_iSpell].sBookLvl) + 1);
		CalcPlrInv(pnum, 1);
	}

	if (pnum == myplr)
		SetCursor_(CURSOR_HAND);
}

void RechargeItem(ItemStruct *i, int r)
{
	if (i->_iCharges != i->_iMaxCharges) {
		while (1) {
			if (i->_iMaxCharges-- == 1)
				break;

			i->_iCharges += r;

			if (i->_iCharges >= i->_iMaxCharges) {
				if (i->_iCharges > i->_iMaxCharges)
					i->_iCharges = i->_iMaxCharges;
				return;
			}
		}
	}
}

void PrintItemOil(char IDidx)
{
	switch (IDidx) {
	case IMISC_FULLHEAL:
		strcpy(tempstr, "fully recover life");
		break;
	case IMISC_HEAL:
		strcpy(tempstr, "recover partial life");
		break;
	case IMISC_OLDHEAL:
		strcpy(tempstr, "recover life");
		break;
	case IMISC_DEADHEAL:
		strcpy(tempstr, "deadly heal");
		break;
	case IMISC_MANA:
		strcpy(tempstr, "recover mana");
		break;
	case IMISC_FULLMANA:
		strcpy(tempstr, "fully recover mana");
		break;
	case IMISC_ELIXSTR:
		strcpy(tempstr, "increase strength");
		break;
	case IMISC_ELIXMAG:
		strcpy(tempstr, "increase magic");
		break;
	case IMISC_ELIXDEX:
		strcpy(tempstr, "increase dexterity");
		break;
	case IMISC_ELIXVIT:
		strcpy(tempstr, "increase vitality");
		break;
	case IMISC_ELIXWEAK:
	case IMISC_ELIXDIS:
		strcpy(tempstr, "decrease strength");
		break;
	case IMISC_ELIXCLUM:
		strcpy(tempstr, "decrease dexterity");
		break;
	case IMISC_ELIXSICK:
		strcpy(tempstr, "decrease vitality");
		break;
	case IMISC_REJUV:
		strcpy(tempstr, "recover life and mana");
		break;
	case IMISC_FULLREJUV:
		strcpy(tempstr, "fully recover life and mana");
		break;
	default:
		return;
	}

	AddPanelString(tempstr, 1);
}

void PrintItemPower(char plidx, ItemStruct *x)
{
	ItemStruct *v2; // esi
	int *v3;        // esi
	int *v4;        // esi
	int v5;         // esi
	const char *v6; // [esp-4h] [ebp-Ch]
	const char *v7; // [esp-4h] [ebp-Ch]
	const char *v8; // [esp-4h] [ebp-Ch]
	const char *v9; // [esp-4h] [ebp-Ch]

	v2 = x;
	switch (plidx) {
	case IPL_TOHIT:
	case IPL_TOHIT_CURSE:
		sprintf(tempstr, "chance to hit : %+i%%", x->_iPLToHit);
		return;
	case IPL_DAMP:
	case IPL_DAMP_CURSE:
		sprintf(tempstr, "%+i%% damage", x->_iPLDam);
		return;
	case IPL_TOHIT_DAMP:
	case IPL_TOHIT_DAMP_CURSE:
		sprintf(tempstr, "to hit: %+i%%, %+i%% damage", x->_iPLToHit, x->_iPLDam);
		return;
	case IPL_ACP:
	case IPL_ACP_CURSE:
		sprintf(tempstr, "%+i%% armor", x->_iPLAC);
		return;
	case IPL_FIRERES:
		if (x->_iPLFR < 75)
			sprintf(tempstr, "Resist Fire : %+i%%", x->_iPLFR);
		if (v2->_iPLFR >= 75) {
			v6 = "Resist Fire : 75%% MAX";
			goto LABEL_11;
		}
		return;
	case IPL_LIGHTRES:
		if (x->_iPLLR < 75)
			sprintf(tempstr, "Resist Lightning : %+i%%", x->_iPLLR);
		if (v2->_iPLLR >= 75) {
			v6 = "Resist Lightning : 75%% MAX";
			goto LABEL_11;
		}
		return;
	case IPL_MAGICRES:
		if (x->_iPLMR < 75)
			sprintf(tempstr, "Resist Magic : %+i%%", x->_iPLMR);
		if (v2->_iPLMR >= 75) {
			v6 = "Resist Magic : 75%% MAX";
			goto LABEL_11;
		}
		return;
	case IPL_ALLRES:
		if (x->_iPLFR < 75)
			sprintf(tempstr, "Resist All : %+i%%", x->_iPLFR);
		if (v2->_iPLFR >= 75) {
			v6 = "Resist All : 75%% MAX";
		LABEL_11:
			sprintf(tempstr, v6);
		}
		return;
	case IPL_SPLLVLADD:
		if (x->_iSplLvlAdd == 1)
			strcpy(tempstr, "spells are increased 1 level");
		if (v2->_iSplLvlAdd == 2)
			strcpy(tempstr, "spells are increased 2 levels");
		if (v2->_iSplLvlAdd < 1) {
			v7 = "spells are decreased 1 level";
			goto LABEL_81;
		}
		return;
	case IPL_CHARGES:
		v8 = "Extra charges";
		goto LABEL_104;
	case IPL_FIREDAM:
		sprintf(tempstr, "Fire hit damage: %i-%i", x->_iFMinDam, x->_iFMaxDam);
		return;
	case IPL_LIGHTDAM:
		sprintf(tempstr, "Lightning hit damage: %i-%i", x->_iLMinDam, x->_iLMaxDam);
		return;
	case IPL_STR:
	case IPL_STR_CURSE:
		sprintf(tempstr, "%+i to strength", x->_iPLStr);
		return;
	case IPL_MAG:
	case IPL_MAG_CURSE:
		sprintf(tempstr, "%+i to magic", x->_iPLMag);
		return;
	case IPL_DEX:
	case IPL_DEX_CURSE:
		sprintf(tempstr, "%+i to dexterity", x->_iPLDex);
		return;
	case IPL_VIT:
	case IPL_VIT_CURSE:
		sprintf(tempstr, "%+i to vitality", x->_iPLVit);
		return;
	case IPL_ATTRIBS:
	case IPL_ATTRIBS_CURSE:
		sprintf(tempstr, "%+i to all attributes", x->_iPLStr);
		return;
	case IPL_GETHIT_CURSE:
	case IPL_GETHIT:
		sprintf(tempstr, "%+i damage from enemies", x->_iPLGetHit);
		return;
	case IPL_LIFE:
	case IPL_LIFE_CURSE:
		sprintf(tempstr, "Hit Points : %+i", x->_iPLHP >> 6);
		return;
	case IPL_MANA:
	case IPL_MANA_CURSE:
		sprintf(tempstr, "Mana : %+i", x->_iPLMana >> 6);
		return;
	case IPL_DUR:
		v8 = "high durability";
		goto LABEL_104;
	case IPL_DUR_CURSE:
		v8 = "decreased durability";
		goto LABEL_104;
	case IPL_INDESTRUCTIBLE:
		v8 = "indestructible";
		goto LABEL_104;
	case IPL_LIGHT:
		sprintf(tempstr, "+%i%% light radius", 10 * x->_iPLLight);
		return;
	case IPL_LIGHT_CURSE:
		sprintf(tempstr, "-%i%% light radius", -10 * x->_iPLLight);
		return;
	case IPL_FIRE_ARROWS:
		sprintf(tempstr, "fire arrows damage: %i-%i", x->_iFMinDam, x->_iFMaxDam);
		return;
	case IPL_LIGHT_ARROWS:
		sprintf(tempstr, "lightning arrows damage %i-%i", x->_iLMinDam, x->_iLMaxDam);
		return;
	case IPL_INVCURS:
		v8 = " ";
		goto LABEL_104;
	case IPL_THORNS:
		v8 = "attacker takes 1-3 damage";
		goto LABEL_104;
	case IPL_NOMANA:
		v8 = "user loses all mana";
		goto LABEL_104;
	case IPL_NOHEALPLR:
		v8 = "you can't heal";
		goto LABEL_104;
	case IPL_ABSHALFTRAP:
		v8 = "absorbs half of trap damage";
		goto LABEL_104;
	case IPL_KNOCKBACK:
		v8 = "knocks target back";
		goto LABEL_104;
	case IPL_NOHEALMON:
		v8 = "hit monster doesn't heal";
		goto LABEL_104;
	case IPL_STEALMANA:
		v3 = &x->_iFlags;
		if (x->_iFlags & 0x2000)
			strcpy(tempstr, "hit steals 3% mana");
		if (!(*((_BYTE *)v3 + 1) & 0x40))
			return;
		v7 = "hit steals 5% mana";
		goto LABEL_81;
	case IPL_STEALLIFE:
		v4 = &x->_iFlags;
		if ((x->_iFlags & 0x8000) != 0)
			strcpy(tempstr, "hit steals 3% life");
		if (!(*((_BYTE *)v4 + 2) & 1))
			return;
		v7 = "hit steals 5% life";
		goto LABEL_81;
	case IPL_TARGAC:
		v8 = "damages target's armor";
		goto LABEL_104;
	case IPL_FASTATTACK:
		if (x->_iFlags & 0x20000)
			strcpy(tempstr, "quick attack");
		if (v2->_iFlags & 0x40000)
			strcpy(tempstr, "fast attack");
		if (v2->_iFlags & 0x80000)
			strcpy(tempstr, "faster attack");
		if (!(v2->_iFlags & 0x100000))
			return;
		v7 = "fastest attack";
		goto LABEL_81;
	case IPL_FASTRECOVER:
		if (x->_iFlags & 0x200000)
			strcpy(tempstr, "fast hit recovery");
		if (v2->_iFlags & 0x400000)
			strcpy(tempstr, "faster hit recovery");
		if ((v2->_iFlags & 0x800000) != 0) {
			v7 = "fastest hit recovery";
		LABEL_81:
			strcpy(tempstr, v7);
		}
		return;
	case IPL_FASTBLOCK:
		v8 = "fast block";
		goto LABEL_104;
	case IPL_DAMMOD:
		sprintf(tempstr, "adds %i points to damage", x->_iPLDamMod);
		return;
	case IPL_RNDARROWVEL:
		v8 = "fires random speed arrows";
		goto LABEL_104;
	case IPL_SETDAM:
		v9 = "unusual item damage";
		goto LABEL_98;
	case IPL_SETDUR:
		v8 = "altered durability";
		goto LABEL_104;
	case IPL_NOMINSTR:
		v8 = "no strength requirement";
		goto LABEL_104;
	case IPL_SPELL:
		sprintf(tempstr, "%i %s charges", x->_iMaxCharges, spelldata[x->_iSpell].sNameText);
		return;
	case IPL_FASTSWING:
		v8 = "Faster attack swing";
		goto LABEL_104;
	case IPL_ONEHAND:
		v8 = "one handed sword";
		goto LABEL_104;
	case IPL_3XDAMVDEM:
		v8 = "+200% damage vs. demons";
		goto LABEL_104;
	case IPL_ALLRESZERO:
		v8 = "All Resistance equals 0";
		goto LABEL_104;
	case IPL_DRAINLIFE:
		v8 = "constantly lose hit points";
		goto LABEL_104;
	case IPL_RNDSTEALLIFE:
		v8 = "life stealing";
		goto LABEL_104;
	case IPL_INFRAVISION:
		v8 = "see with infravision";
		goto LABEL_104;
	case IPL_SETAC:
	case IPL_AC_CURSE:
		sprintf(tempstr, "armor class: %i", x->_iAC);
		return;
	case IPL_ADDACLIFE:
		v8 = "Armor class added to life";
		goto LABEL_104;
	case IPL_ADDMANAAC:
		v8 = "10% of mana added to armor";
		goto LABEL_104;
	case IPL_FIRERESCLVL:
		v5 = x->_iPLFR;
		if (v5 > 0) {
			if (v5 >= 1)
				sprintf(tempstr, "Resist Fire : %+i%%", v5);
		} else {
			v9 = " ";
		LABEL_98:
			sprintf(tempstr, v9);
		}
		break;
	default:
		v8 = "Another ability (NW)";
	LABEL_104:
		strcpy(tempstr, v8);
		break;
	}
}

void DrawUTextBack()
{
	CelDecodeOnly(88, 487, (BYTE *)pSTextBoxCels, 1, 271);

#define TRANS_RECT_X 27
#define TRANS_RECT_Y 28
#define TRANS_RECT_WIDTH 265
#define TRANS_RECT_HEIGHT 297
#include "asm_trans_rect.inc"
}

void PrintUString(int x, int y, int cjustflag, char *str, int col)
{
	char *v5;          // edi
	int v6;            // ebx
	size_t v7;         // eax
	int v8;            // esi
	int v9;            // ecx
	signed int v10;    // eax
	int v11;           // edx
	int v12;           // eax
	unsigned char v13; // al
	int v14;           // edi
	int v15;           // [esp+Ch] [ebp-4h]
	int a3;            // [esp+18h] [ebp+8h]

	v5 = str;
	v6 = PitchTbl[SStringY[y] + 204] + x + 96;
	v7 = strlen(str);
	v8 = 0;
	v9 = 0;
	v15 = v7;
	if (cjustflag) {
		v10 = 0;
		if (v15 <= 0)
			goto LABEL_16;
		do {
			v11 = (unsigned char)str[v9++];
			v10 += fontkern[fontframe[gbFontTransTbl[v11]]] + 1;
		} while (v9 < v15);
		if (v10 < 257)
		LABEL_16:
			v8 = (257 - v10) >> 1;
		v6 += v8;
	}
	v12 = 0;
	a3 = 0;
	if (v15 > 0) {
		while (1) {
			v13 = fontframe[gbFontTransTbl[(unsigned char)v5[v12]]];
			v14 = v13;
			v8 += fontkern[v13] + 1;
			if (v13) {
				if (v8 <= 257)
					CPrintString(v6, v13, col);
			}
			v6 += fontkern[v14] + 1;
			v12 = a3++ + 1;
			if (a3 >= v15)
				break;
			v5 = str;
		}
	}
}

void DrawULine(int y)
{
	/// ASSERT: assert(gpBuffer);

#ifdef USE_ASM
	int yy;

	yy = PitchTbl[SStringY[y] + 198] + 26 + 64;

	__asm {
		mov		esi, gpBuffer
		mov		edi, esi
		add		esi, SCREENXY(26, 25)
		add		edi, yy
		mov		ebx, 768 - 266
		mov		edx, 3
	copyline:
		mov		ecx, 266 / 4
		rep movsd
		movsw
		add		esi, ebx
		add		edi, ebx
		dec		edx
		jnz		copyline
	}
#else
	int i;
	BYTE *src, *dst;

	src = &gpBuffer[SCREENXY(26, 25)];
	dst = &gpBuffer[PitchTbl[SStringY[y] + 198] + 26 + 64];

	for (i = 0; i < 3; i++, src += 768, dst += 768)
		memcpy(dst, src, 266);
#endif
}

void DrawUniqueInfo()
{
	int v0; // esi
	int v1; // esi
	int v2; // edi

	if (!chrflag && !questlog) {
		v0 = curruitem._iUid;
		DrawUTextBack();
		v1 = v0;
		PrintUString(0, 2, 1, UniqueItemList[v1].UIName, 3);
		DrawULine(5);
		PrintItemPower(UniqueItemList[v1].UIPower1, &curruitem);
		v2 = 14 - (char)UniqueItemList[v1].UINumPL;
		PrintUString(0, v2, 1, tempstr, 0);
		if (UniqueItemList[v1].UINumPL > 1) {
			PrintItemPower(UniqueItemList[v1].UIPower2, &curruitem);
			PrintUString(0, v2 + 2, 1, tempstr, 0);
		}
		if (UniqueItemList[v1].UINumPL > 2) {
			PrintItemPower(UniqueItemList[v1].UIPower3, &curruitem);
			PrintUString(0, v2 + 4, 1, tempstr, 0);
		}
		if (UniqueItemList[v1].UINumPL > 3) {
			PrintItemPower(UniqueItemList[v1].UIPower4, &curruitem);
			PrintUString(0, v2 + 6, 1, tempstr, 0);
		}
		if (UniqueItemList[v1].UINumPL > 4) {
			PrintItemPower(UniqueItemList[v1].UIPower5, &curruitem);
			PrintUString(0, v2 + 8, 1, tempstr, 0);
		}
		if (UniqueItemList[v1].UINumPL > 5) {
			PrintItemPower(UniqueItemList[v1].UIPower6, &curruitem);
			PrintUString(0, v2 + 10, 1, tempstr, 0);
		}
	}
}

void PrintItemMisc(ItemStruct *x)
{
	if (x->_iMiscId == IMISC_SCROLL) {
		strcpy(tempstr, "Right-click to read");
		AddPanelString(tempstr, 1);
	}
	if (x->_iMiscId == IMISC_SCROLLT) {
		strcpy(tempstr, "Right-click to read, then");
		AddPanelString(tempstr, 1);
		strcpy(tempstr, "left-click to target");
		AddPanelString(tempstr, 1);
	}
	if (x->_iMiscId >= IMISC_USEFIRST && x->_iMiscId <= IMISC_USELAST) {
		PrintItemOil(x->_iMiscId);
		strcpy(tempstr, "Right click to use");
		AddPanelString(tempstr, 1);
	}
	if (x->_iMiscId == IMISC_BOOK) {
		strcpy(tempstr, "Right click to read");
		AddPanelString(tempstr, 1);
	}
	if (x->_iMiscId == IMISC_MAPOFDOOM) {
		strcpy(tempstr, "Right click to view");
		AddPanelString(tempstr, 1);
	}
	if (x->_iMiscId == IMISC_EAR) {
		sprintf(tempstr, "Level : %i", x->_ivalue);
		AddPanelString(tempstr, 1);
	}
}

void PrintItemDetails(ItemStruct *x)
{
	if (x->_iClass == ICLASS_WEAPON) {
		if (x->_iMaxDur == 255)
			sprintf(tempstr, "damage: %i-%i  Indestructible", x->_iMinDam, x->_iMaxDam);
		else
			sprintf(tempstr, "damage: %i-%i  Dur: %i/%i", x->_iMinDam, x->_iMaxDam, x->_iDurability, x->_iMaxDur);
		AddPanelString(tempstr, 1);
	}
	if (x->_iClass == ICLASS_ARMOR) {
		if (x->_iMaxDur == 255)
			sprintf(tempstr, "armor: %i  Indestructible", x->_iAC);
		else
			sprintf(tempstr, "armor: %i  Dur: %i/%i", x->_iAC, x->_iDurability, x->_iMaxDur);
		AddPanelString(tempstr, 1);
	}
	if (x->_iMiscId == IMISC_STAFF && x->_iMaxCharges) {
		sprintf(tempstr, "dam: %i-%i  Dur: %i/%i", x->_iMinDam, x->_iMaxDam, x->_iDurability, x->_iMaxDur);
		sprintf(tempstr, "Charges: %i/%i", x->_iCharges, x->_iMaxCharges);
		AddPanelString(tempstr, 1);
	}
	if (x->_iPrePower != -1) {
		PrintItemPower(x->_iPrePower, x);
		AddPanelString(tempstr, 1);
	}
	if (x->_iSufPower != -1) {
		PrintItemPower(x->_iSufPower, x);
		AddPanelString(tempstr, 1);
	}
	if (x->_iMagical == ITEM_QUALITY_UNIQUE) {
		AddPanelString("unique item", 1);
		uitemflag = 1;
		curruitem = *x;
	}
	PrintItemMisc(x);
	if (x->_iMinMag + x->_iMinDex + x->_iMinStr) {
		strcpy(tempstr, "Required:");
		if (x->_iMinStr)
			sprintf(tempstr, "%s %i Str", tempstr, x->_iMinStr);
		if (x->_iMinMag)
			sprintf(tempstr, "%s %i Mag", tempstr, x->_iMinMag);
		if (x->_iMinDex)
			sprintf(tempstr, "%s %i Dex", tempstr, x->_iMinDex);
		AddPanelString(tempstr, 1);
	}
	pinfoflag = TRUE;
}

void PrintItemDur(ItemStruct *x)
{
	ItemStruct *v1;   // esi
	int v2;           // eax
	char v3;          // al
	unsigned char v4; // al
	char v5;          // al

	v1 = x;
	if (x->_iClass == ICLASS_WEAPON) {
		if (x->_iMaxDur == 255)
			sprintf(tempstr, "damage: %i-%i  Indestructible", x->_iMinDam, x->_iMaxDam);
		else
			sprintf(tempstr, "damage: %i-%i  Dur: %i/%i", x->_iMinDam, x->_iMaxDam, x->_iDurability, x->_iMaxDur);
		AddPanelString(tempstr, 1);
		if (v1->_iMiscId == IMISC_STAFF && v1->_iMaxCharges) {
			sprintf(tempstr, "Charges: %i/%i", v1->_iCharges, v1->_iMaxCharges);
			AddPanelString(tempstr, 1);
		}
		if (v1->_iMagical != ITEM_QUALITY_NORMAL)
			AddPanelString("Not Identified", 1);
	}
	if (v1->_iClass == ICLASS_ARMOR) {
		if (v1->_iMaxDur == 255)
			sprintf(tempstr, "armor: %i  Indestructible", v1->_iAC);
		else
			sprintf(tempstr, "armor: %i  Dur: %i/%i", v1->_iAC, v1->_iDurability, v1->_iMaxDur);
		AddPanelString(tempstr, 1);
		if (v1->_iMagical != ITEM_QUALITY_NORMAL)
			AddPanelString("Not Identified", 1);
		if (v1->_iMiscId == IMISC_STAFF && v1->_iMaxCharges) {
			sprintf(tempstr, "Charges: %i/%i", v1->_iCharges, v1->_iMaxCharges);
			AddPanelString(tempstr, 1);
		}
	}
	v2 = v1->_itype;
	if (v2 == ITYPE_RING || v2 == ITYPE_AMULET)
		AddPanelString("Not Identified", 1);
	PrintItemMisc(v1);
	if ((unsigned char)v1->_iMinMag + v1->_iMinDex + v1->_iMinStr) {
		strcpy(tempstr, "Required:");
		v3 = v1->_iMinStr;
		if (v3)
			sprintf(tempstr, "%s %i Str", tempstr, v3);
		v4 = v1->_iMinMag;
		if (v4)
			sprintf(tempstr, "%s %i Mag", tempstr, v4);
		v5 = v1->_iMinDex;
		if (v5)
			sprintf(tempstr, "%s %i Dex", tempstr, v5);
		AddPanelString(tempstr, TRUE);
	}
	pinfoflag = TRUE;
}

void UseItem(int p, int Mid, int spl)
{
	int l, j;

	switch (Mid) {
	case IMISC_HEAL:
	case IMISC_HEAL_1C:
		j = plr[p]._pMaxHP >> 8;
		l = ((j >> 1) + random(39, j)) << 6;
		if (plr[p]._pClass == PC_WARRIOR)
			l *= 2;
		if (plr[p]._pClass == PC_ROGUE)
			l += l >> 1;
		plr[p]._pHitPoints += l;
		if (plr[p]._pHitPoints > plr[p]._pMaxHP)
			plr[p]._pHitPoints = plr[p]._pMaxHP;
		plr[p]._pHPBase += l;
		if (plr[p]._pHPBase > plr[p]._pMaxHPBase)
			plr[p]._pHPBase = plr[p]._pMaxHPBase;
		drawhpflag = TRUE;
		break;
	case IMISC_FULLHEAL:
		plr[p]._pHitPoints = plr[p]._pMaxHP;
		plr[p]._pHPBase = plr[p]._pMaxHPBase;
		drawhpflag = TRUE;
		break;
	case IMISC_MANA:
		j = plr[p]._pMaxMana >> 8;
		l = ((j >> 1) + random(40, j)) << 6;
		if (plr[p]._pClass == PC_SORCERER)
			l *= 2;
		if (plr[p]._pClass == PC_ROGUE)
			l += l >> 1;
		if (!(plr[p]._pIFlags & ISPL_NOMANA)) {
			plr[p]._pMana += l;
			if (plr[p]._pMana > plr[p]._pMaxMana)
				plr[p]._pMana = plr[p]._pMaxMana;
			plr[p]._pManaBase += l;
			if (plr[p]._pManaBase > plr[p]._pMaxManaBase)
				plr[p]._pManaBase = plr[p]._pMaxManaBase;
			drawmanaflag = TRUE;
		}
		break;
	case IMISC_FULLMANA:
		if (!(plr[p]._pIFlags & ISPL_NOMANA)) {
			plr[p]._pMana = plr[p]._pMaxMana;
			plr[p]._pManaBase = plr[p]._pMaxManaBase;
			drawmanaflag = TRUE;
		}
		break;
	case IMISC_ELIXSTR:
		ModifyPlrStr(p, 1);
		break;
	case IMISC_ELIXMAG:
		ModifyPlrMag(p, 1);
		break;
	case IMISC_ELIXDEX:
		ModifyPlrDex(p, 1);
		break;
	case IMISC_ELIXVIT:
		ModifyPlrVit(p, 1);
		break;
	case IMISC_REJUV:
		j = plr[p]._pMaxHP >> 8;
		l = ((j >> 1) + random(39, j)) << 6;
		if (plr[p]._pClass == PC_WARRIOR)
			l *= 2;
		if (plr[p]._pClass == PC_ROGUE)
			l += l >> 1;
		plr[p]._pHitPoints += l;
		if (plr[p]._pHitPoints > plr[p]._pMaxHP)
			plr[p]._pHitPoints = plr[p]._pMaxHP;
		plr[p]._pHPBase += l;
		if (plr[p]._pHPBase > plr[p]._pMaxHPBase)
			plr[p]._pHPBase = plr[p]._pMaxHPBase;
		drawhpflag = TRUE;
		j = plr[p]._pMaxMana >> 8;
		l = ((j >> 1) + random(40, j)) << 6;
		if (plr[p]._pClass == PC_SORCERER)
			l *= 2;
		if (plr[p]._pClass == PC_ROGUE)
			l += l >> 1;
		if (!(plr[p]._pIFlags & ISPL_NOMANA)) {
			plr[p]._pMana += l;
			if (plr[p]._pMana > plr[p]._pMaxMana)
				plr[p]._pMana = plr[p]._pMaxMana;
			plr[p]._pManaBase += l;
			if (plr[p]._pManaBase > plr[p]._pMaxManaBase)
				plr[p]._pManaBase = plr[p]._pMaxManaBase;
			drawmanaflag = TRUE;
		}
		break;
	case IMISC_FULLREJUV:
		plr[p]._pHitPoints = plr[p]._pMaxHP;
		plr[p]._pHPBase = plr[p]._pMaxHPBase;
		drawhpflag = TRUE;
		if (!(plr[p]._pIFlags & ISPL_NOMANA)) {
			plr[p]._pMana = plr[p]._pMaxMana;
			plr[p]._pManaBase = plr[p]._pMaxManaBase;
			drawmanaflag = TRUE;
		}
		break;
	case IMISC_SCROLL:
		if (spelldata[spl].sTargeted) {
			plr[p]._pTSpell = spl;
			plr[p]._pTSplType = RSPLTYPE_INVALID;
			if (p == myplr)
				NewCursor(CURSOR_TELEPORT);
		} else {
			ClrPlrPath(p);
			plr[p]._pSpell = spl;
			plr[p]._pSplType = RSPLTYPE_INVALID;
			plr[p]._pSplFrom = 3;
			plr[p].destAction = ACTION_SPELL;
			plr[p].destParam1 = cursmx;
			plr[p].destParam2 = cursmy;
			if (p == myplr && spl == SPL_NOVA)
				NetSendCmdLoc(TRUE, CMD_NOVA, cursmx, cursmy);
		}
		break;
	case IMISC_SCROLLT:
		if (spelldata[spl].sTargeted) {
			plr[p]._pTSpell = spl;
			plr[p]._pTSplType = RSPLTYPE_INVALID;
			if (p == myplr)
				NewCursor(CURSOR_TELEPORT);
		} else {
			ClrPlrPath(p);
			plr[p]._pSpell = spl;
			plr[p]._pSplType = RSPLTYPE_INVALID;
			plr[p]._pSplFrom = 3;
			plr[p].destAction = ACTION_SPELL;
			plr[p].destParam1 = cursmx;
			plr[p].destParam2 = cursmy;
		}
		break;
	case IMISC_BOOK:
		plr[p]._pMemSpells |= (__int64)1 << (spl - 1);
		if (plr[p]._pSplLvl[spl] < 15)
			plr[p]._pSplLvl[spl]++;
		plr[p]._pMana += spelldata[spl].sManaCost << 6;
		if (plr[p]._pMana > plr[p]._pMaxMana)
			plr[p]._pMana = plr[p]._pMaxMana;
		plr[p]._pManaBase += spelldata[spl].sManaCost << 6;
		if (plr[p]._pManaBase > plr[p]._pMaxManaBase)
			plr[p]._pManaBase = plr[p]._pMaxManaBase;
		if (p == myplr)
			CalcPlrBookVals(p);
		drawmanaflag = TRUE;
		break;
	case IMISC_MAPOFDOOM:
		doom_init();
		break;
	case IMISC_SPECELIX:
		ModifyPlrStr(p, 3);
		ModifyPlrMag(p, 3);
		ModifyPlrDex(p, 3);
		ModifyPlrVit(p, 3);
		break;
	}
}

BOOL StoreStatOk(ItemStruct *h)
{
	BOOL sf;

	sf = TRUE;
	if (plr[myplr]._pStrength < h->_iMinStr)
		sf = FALSE;
	if (plr[myplr]._pMagic < h->_iMinMag)
		sf = FALSE;
	if (plr[myplr]._pDexterity < h->_iMinDex)
		sf = FALSE;

	return sf;
}

BOOL SmithItemOk(int i)
{
	BOOL rv;

	rv = TRUE;
	if (AllItemsList[i].itype == ITYPE_MISC)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_GOLD)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_0E)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_STAFF)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_RING)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_AMULET)
		rv = FALSE;

	return rv;
}

int RndSmithItem(int lvl)
{
	int i, ri;
	int ril[512];

	ri = 0;
	for (i = 1; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd && SmithItemOk(i) && lvl >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
			if (AllItemsList[i].iRnd == 2) {
				ril[ri] = i;
				ri++;
			}
		}
	}

	return ril[random(50, ri)] + 1;
}

void BubbleSwapItem(ItemStruct *a, ItemStruct *b)
{
	ItemStruct h;

	h = *a;
	*a = *b;
	*b = h;
}

void SortSmith()
{
	int j, k;
	BOOL sorted;

	j = 0;
	while (smithitem[j + 1]._itype != ITYPE_NONE) {
		j++;
	}

	sorted = FALSE;
	while (j > 0 && !sorted) {
		sorted = TRUE;
		if (j > 0) {
			for (k = 0; k < j; k++) {
				if (smithitem[k].IDidx > smithitem[k + 1].IDidx) {
					BubbleSwapItem(&smithitem[k], &smithitem[k + 1]);
					sorted = FALSE;
				}
			}
		}
		j--;
	}
}

void SpawnSmith(int lvl)
{
	int i, iCnt, idata;

	iCnt = random(50, 10) + 10;
	for (i = 0; i < iCnt; i++) {
		do {
			item[0]._iSeed = GetRndSeed();
			SetRndSeed(item[0]._iSeed);
			idata = RndSmithItem(lvl) - 1;
			GetItemAttrs(0, idata, lvl);
		} while (item[0]._iIvalue > 140000);
		smithitem[i] = item[0];
		smithitem[i]._iCreateInfo = lvl | 0x400;
		smithitem[i]._iIdentified = TRUE;
		smithitem[i]._iStatFlag = StoreStatOk(&smithitem[i]);
	}
	for (i = iCnt; i < 20; i++)
		smithitem[i]._itype = ITYPE_NONE;

	SortSmith();
}

BOOL PremiumItemOk(int i)
{
	BOOL rv;

	rv = TRUE;
	if (AllItemsList[i].itype == ITYPE_MISC)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_GOLD)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_0E)
		rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_STAFF)
		rv = FALSE;

	if (gbMaxPlayers != 1) {
		if (AllItemsList[i].itype == ITYPE_RING)
			rv = FALSE;
		if (AllItemsList[i].itype == ITYPE_AMULET)
			rv = FALSE;
	}

	return rv;
}
// 679660: using guessed type char gbMaxPlayers;

int RndPremiumItem(int minlvl, int maxlvl)
{
	int i, ri;
	int ril[512];

	ri = 0;
	for (i = 1; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd) {
			if (PremiumItemOk(i)) {
				if (AllItemsList[i].iMinMLvl >= minlvl && AllItemsList[i].iMinMLvl <= maxlvl)
					ril[ri++] = i;
			}
		}
	}

	return ril[random(50, ri)] + 1;
}
// 42445F: using guessed type int ril[512];

void SpawnOnePremium(int i, int plvl)
{
	int itype;
	ItemStruct holditem;

	holditem = item[0];
	if (plvl > 30)
		plvl = 30;
	if (plvl < 1)
		plvl = 1;
	do {
		item[0]._iSeed = GetRndSeed();
		SetRndSeed(item[0]._iSeed);
		itype = RndPremiumItem(plvl >> 2, plvl) - 1;
		GetItemAttrs(0, itype, plvl);
		GetItemBonus(0, itype, plvl >> 1, plvl, 1);
	} while (item[0]._iIvalue > 140000);
	premiumitem[i] = item[0];
	premiumitem[i]._iCreateInfo = plvl | 0x800;
	premiumitem[i]._iIdentified = TRUE;
	premiumitem[i]._iStatFlag = StoreStatOk(&premiumitem[i]);
	item[0] = holditem;
}

void SpawnPremium(int lvl)
{
	int i;

	if (numpremium < 6) {
		for (i = 0; i < 6; i++) {
			if (premiumitem[i]._itype == ITYPE_NONE)
				SpawnOnePremium(i, premiumlevel + premiumlvladd[i]);
		}
		numpremium = 6;
	}
	while (premiumlevel < lvl) {
		premiumlevel++;
		premiumitem[0] = premiumitem[2];
		premiumitem[1] = premiumitem[3];
		premiumitem[2] = premiumitem[4];
		SpawnOnePremium(3, premiumlevel + premiumlvladd[3]);
		premiumitem[4] = premiumitem[5];
		SpawnOnePremium(5, premiumlevel + premiumlvladd[5]);
	}
}
// 69FB38: using guessed type int talker;

BOOL WitchItemOk(int i)
{
	BOOL rv;

	rv = FALSE;
	if (AllItemsList[i].itype == ITYPE_MISC)
		rv = TRUE;
	if (AllItemsList[i].itype == ITYPE_STAFF)
		rv = TRUE;
	if (AllItemsList[i].iMiscId == IMISC_MANA)
		rv = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_FULLMANA)
		rv = FALSE;
	if (AllItemsList[i].iSpell == SPL_TOWN)
		rv = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_FULLHEAL)
		rv = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_HEAL)
		rv = FALSE;
	if (AllItemsList[i].iSpell == SPL_RESURRECT && gbMaxPlayers == 1)
		rv = FALSE;
	if (AllItemsList[i].iSpell == SPL_HEALOTHER && gbMaxPlayers == 1)
		rv = FALSE;

	return rv;
}
// 679660: using guessed type char gbMaxPlayers;

int RndWitchItem(int lvl)
{
	int i, ri;
	int ril[512];

	ri = 0;
	for (i = 1; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd && WitchItemOk(i) && lvl >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
		}
	}

	return ril[random(51, ri)] + 1;
}

void SortWitch()
{
	int j, k;
	BOOL sorted;

	j = 3;
	while (witchitem[j + 1]._itype != ITYPE_NONE) {
		j++;
	}

	sorted = FALSE;
	while (j > 3 && !sorted) {
		sorted = TRUE;
		if (j > 3) {
			for (k = 3; k < j; k++) {
				if (witchitem[k].IDidx > witchitem[k + 1].IDidx) {
					BubbleSwapItem(&witchitem[k], &witchitem[k + 1]);
					sorted = FALSE;
				}
			}
		}
		j--;
	}
}

void WitchBookLevel(int ii)
{
	int slvl; // edi

	if (witchitem[ii]._iMiscId == IMISC_BOOK) {
		witchitem[ii]._iMinMag = spelldata[witchitem[ii]._iSpell].sMinInt;
		slvl = plr[myplr]._pSplLvl[witchitem[ii]._iSpell];
		if (slvl) {
			do {
				witchitem[ii]._iMinMag += 20 * witchitem[ii]._iMinMag / 100;
				--slvl;
				if (witchitem[ii]._iMinMag > 255) {
					witchitem[ii]._iMinMag = -1;
					slvl = 0;
				}
			} while (slvl);
		}
	}
}

void SpawnWitch(int lvl)
{
	int i, iCnt;
	int idata, maxlvl;

	GetItemAttrs(0, IDI_MANA, 1);
	witchitem[0] = item[0];
	witchitem[0]._iCreateInfo = lvl;
	witchitem[0]._iStatFlag = 1;
	GetItemAttrs(0, IDI_FULLMANA, 1);
	witchitem[1] = item[0];
	witchitem[1]._iCreateInfo = lvl;
	witchitem[1]._iStatFlag = 1;
	GetItemAttrs(0, IDI_PORTAL, 1);
	witchitem[2] = item[0];
	witchitem[2]._iCreateInfo = lvl;
	witchitem[2]._iStatFlag = 1;
	iCnt = random(51, 8) + 10;

	for (i = 3; i < iCnt; i++) {
		do {
			item[0]._iSeed = GetRndSeed();
			SetRndSeed(item[0]._iSeed);
			idata = RndWitchItem(lvl) - 1;
			GetItemAttrs(0, idata, lvl);
			maxlvl = -1;
			if (random(51, 100) <= 5)
				maxlvl = 2 * lvl;
			if (maxlvl == -1 && item[0]._iMiscId == IMISC_STAFF)
				maxlvl = 2 * lvl;
			if (maxlvl != -1)
				GetItemBonus(0, idata, maxlvl >> 1, maxlvl, 1);
		} while (item[0]._iIvalue > 140000);
		witchitem[i] = item[0];
		witchitem[i]._iCreateInfo = lvl | 0x2000;
		witchitem[i]._iIdentified = TRUE;
		WitchBookLevel(i);
		witchitem[i]._iStatFlag = StoreStatOk(&witchitem[i]);
	}

	for (i = iCnt; i < 20; i++)
		witchitem[i]._itype = ITYPE_NONE;

	SortWitch();
}

int RndBoyItem(int lvl)
{
	int i, ri;
	int ril[512];

	ri = 0;
	for (i = 1; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd && PremiumItemOk(i) && lvl >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
		}
	}

	return ril[random(49, ri)] + 1;
}
// 4249A4: using guessed type int var_800[512];

void SpawnBoy(int lvl)
{
	int itype;

	if (boylevel<lvl>> 1 || boyitem._itype == ITYPE_NONE) {
		do {
			item[0]._iSeed = GetRndSeed();
			SetRndSeed(item[0]._iSeed);
			itype = RndBoyItem(lvl) - 1;
			GetItemAttrs(0, itype, lvl);
			GetItemBonus(0, itype, lvl, 2 * lvl, 1);
		} while (item[0]._iIvalue > 90000);
		boyitem = item[0];
		boyitem._iCreateInfo = lvl | 0x1000;
		boyitem._iIdentified = TRUE;
		boyitem._iStatFlag = StoreStatOk(&boyitem);
		boylevel = lvl >> 1;
	}
}
// 6A8A3C: using guessed type int boylevel;

BOOL HealerItemOk(int i)
{
	BOOL result;

	result = FALSE;
	if (AllItemsList[i].itype != ITYPE_MISC)
		return FALSE;

	if (AllItemsList[i].iMiscId == IMISC_SCROLL && AllItemsList[i].iSpell == SPL_HEAL)
		result = TRUE;
	if (AllItemsList[i].iMiscId == IMISC_SCROLLT && AllItemsList[i].iSpell == SPL_RESURRECT && gbMaxPlayers != 1)
		result = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_SCROLLT && AllItemsList[i].iSpell == SPL_HEALOTHER && gbMaxPlayers != 1)
		result = TRUE;

	if (gbMaxPlayers == 1) {
		if (AllItemsList[i].iMiscId == IMISC_ELIXSTR)
			result = TRUE;
		if (AllItemsList[i].iMiscId == IMISC_ELIXMAG)
			result = TRUE;
		if (AllItemsList[i].iMiscId == IMISC_ELIXDEX)
			result = TRUE;
		if (AllItemsList[i].iMiscId == IMISC_ELIXVIT)
			result = TRUE;
	}

	if (AllItemsList[i].iMiscId == IMISC_FULLHEAL) // BUGFIX this is a duplicate with the wrong case
		result = TRUE;

	if (AllItemsList[i].iMiscId == IMISC_REJUV)
		result = TRUE;
	if (AllItemsList[i].iMiscId == IMISC_FULLREJUV)
		result = TRUE;
	if (AllItemsList[i].iMiscId == IMISC_HEAL)
		result = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_FULLHEAL)
		result = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_MANA)
		result = FALSE;
	if (AllItemsList[i].iMiscId == IMISC_FULLMANA)
		result = FALSE;

	return result;
}
// 679660: using guessed type char gbMaxPlayers;

int RndHealerItem(int lvl)
{
	int i, ri;
	int ril[512];

	ri = 0;
	for (i = 1; AllItemsList[i].iLoc != -1; i++) {
		if (AllItemsList[i].iRnd && HealerItemOk(i) && lvl >= AllItemsList[i].iMinMLvl) {
			ril[ri] = i;
			ri++;
		}
	}

	return ril[random(50, ri)] + 1;
}

void SortHealer()
{
	int j, k;
	BOOL sorted;

	j = 2;
	while (healitem[j + 1]._itype != ITYPE_NONE) {
		j++;
	}

	sorted = FALSE;
	while (j > 2 && !sorted) {
		sorted = TRUE;
		if (j > 2) {
			for (k = 2; k < j; k++) {
				if (healitem[k].IDidx > healitem[k + 1].IDidx) {
					BubbleSwapItem(&healitem[k], &healitem[k + 1]);
					sorted = FALSE;
				}
			}
		}
		j--;
	}
}

void SpawnHealer(int lvl)
{
	int i, nsi, srnd;

	GetItemAttrs(0, IDI_HEAL, 1);
	healitem[0] = item[0];
	healitem[0]._iCreateInfo = lvl;
	healitem[0]._iStatFlag = TRUE;

	GetItemAttrs(0, IDI_FULLHEAL, 1);
	healitem[1] = item[0];
	healitem[1]._iCreateInfo = lvl;
	healitem[1]._iStatFlag = TRUE;

	if (gbMaxPlayers != 1) {
		GetItemAttrs(0, IDI_RESURRECT, 1);
		healitem[2] = item[0];
		healitem[2]._iCreateInfo = lvl;
		healitem[2]._iStatFlag = TRUE;

		i = 3;
	} else {
		i = 2;
	}
	nsi = random(50, 8) + 10;
	for (; i < nsi; i++) {
		item[0]._iSeed = GetRndSeed();
		SetRndSeed(item[0]._iSeed);
		srnd = RndHealerItem(lvl) - 1;
		GetItemAttrs(0, srnd, lvl);
		healitem[i] = item[0];
		healitem[i]._iCreateInfo = lvl | 0x4000;
		healitem[i]._iIdentified = TRUE;
		healitem[i]._iStatFlag = StoreStatOk(&healitem[i]);
	}
	for (i = nsi; i < 20; i++) {
		healitem[i]._itype = ITYPE_NONE;
	}
	SortHealer();
}
// 679660: using guessed type char gbMaxPlayers;

void SpawnStoreGold()
{
	GetItemAttrs(0, IDI_GOLD, 1);
	golditem = item[0];
	golditem._iStatFlag = 1;
}

void RecreateSmithItem(int ii, int idx, int plvl, int iseed)
{
	SetRndSeed(iseed);
	GetItemAttrs(ii, RndSmithItem(plvl) - 1, plvl);
	item[ii]._iSeed = iseed;
	item[ii]._iCreateInfo = plvl | 0x400;
	item[ii]._iIdentified = TRUE;
}

void RecreatePremiumItem(int ii, int idx, int lvl, int iseed)
{
	int itype; // edi

	SetRndSeed(iseed);
	itype = RndPremiumItem(lvl >> 2, lvl) - 1;
	GetItemAttrs(ii, itype, lvl);
	GetItemBonus(ii, itype, lvl >> 1, lvl, 1);
	item[ii]._iCreateInfo = lvl | 0x800;
	item[ii]._iSeed = iseed;
	item[ii]._iIdentified = TRUE;
}

void RecreateBoyItem(int ii, int idx, int lvl, int iseed)
{
	int itype; // edi

	SetRndSeed(iseed);
	itype = RndBoyItem(lvl) - 1;
	GetItemAttrs(ii, itype, lvl);
	GetItemBonus(ii, itype, lvl, 2 * lvl, 1);
	item[ii]._iCreateInfo = lvl | 0x1000;
	item[ii]._iSeed = iseed;
	item[ii]._iIdentified = TRUE;
}

void RecreateWitchItem(int ii, int idx, int lvl, int iseed)
{
	int itype; // edi
	int iblvl; // eax

	if (idx == IDI_MANA || idx == IDI_FULLMANA || idx == IDI_PORTAL) {
		GetItemAttrs(ii, idx, lvl);
	} else {
		SetRndSeed(iseed);
		itype = RndWitchItem(lvl) - 1;
		GetItemAttrs(ii, itype, lvl);
		iblvl = 2 * lvl;
		if (iblvl != -1 && (random(51, 100) <= 5 || item[ii]._iMiscId == IMISC_STAFF)) {
			GetItemBonus(ii, itype, iblvl >> 1, iblvl, 1);
		}
	}
	item[ii]._iCreateInfo = lvl | 0x2000;
	item[ii]._iSeed = iseed;
	item[ii]._iIdentified = TRUE;
}

void RecreateHealerItem(int ii, int idx, int lvl, int iseed)
{
	if (idx == IDI_HEAL || idx == IDI_FULLHEAL || idx == IDI_RESURRECT) {
		GetItemAttrs(ii, idx, lvl);
	} else {
		SetRndSeed(iseed);
		idx = RndHealerItem(lvl) - 1;
		GetItemAttrs(ii, idx, lvl);
	}

	item[ii]._iCreateInfo = lvl | 0x4000;
	item[ii]._iSeed       = iseed;
	item[ii]._iIdentified = TRUE;
}


void RecreateTownItem(int ii, int idx, unsigned short icreateinfo, int iseed, int ivalue)
{
	if (icreateinfo & 0x400)
		RecreateSmithItem(ii, idx, icreateinfo & 0x3F, iseed);
	else if (icreateinfo & 0x800)
		RecreatePremiumItem(ii, idx, icreateinfo & 0x3F, iseed);
	else if (icreateinfo & 0x1000)
		RecreateBoyItem(ii, idx, icreateinfo & 0x3F, iseed);
	else if (icreateinfo & 0x2000)
		RecreateWitchItem(ii, idx, icreateinfo & 0x3F, iseed);
	else if (icreateinfo & 0x4000)
		RecreateHealerItem(ii, idx, icreateinfo & 0x3F, iseed);
}

void RecalcStoreStats()
{
	int i;

	for (i = 0; i < 20; i++) {
		if (smithitem[i]._itype != ITYPE_NONE) {
			smithitem[i]._iStatFlag = StoreStatOk(&smithitem[i]);
		}
	}
	for (i = 0; i < 6; i++) {
		if (premiumitem[i]._itype != ITYPE_NONE) {
			premiumitem[i]._iStatFlag = StoreStatOk(&premiumitem[i]);
		}
	}
	for (i = 0; i < 20; i++) {
		if (witchitem[i]._itype != ITYPE_NONE) {
			witchitem[i]._iStatFlag = StoreStatOk(&witchitem[i]);
		}
	}
	for (i = 0; i < 20; i++) {
		if (healitem[i]._itype != ITYPE_NONE) {
			healitem[i]._iStatFlag = StoreStatOk(&healitem[i]);
		}
	}
	boyitem._iStatFlag = StoreStatOk(&boyitem);
}

// 6A6BB8: using guessed type int stextscrl;
// 6AA700: using guessed type int stextdown;

int ItemNoFlippy()
{
	int r; // ecx

	r = itemactive[numitems - 1];
	item[r]._iAnimFlag = FALSE;
	item[r]._iAnimFrame = item[r]._iAnimLen;
	item[r]._iSelFlag = 1;

	return r;
}

void CreateSpellBook(int x, int y, int ispell, BOOLEAN sendmsg, int delta)
{
	int ii;       // edi
	int idx;      // [esp+8h] [ebp-8h]
	BOOLEAN done; // [esp+Ch] [ebp-4h]

	done = 0;
	idx = RndTypeItems(0, 24);
	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, itemavail[0]);
		itemactive[numitems] = ii;
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		do {
			SetupAllItems(ii, idx, GetRndSeed(), 2 * currlevel, 1, 1, 0, delta);
			if (item[ii]._iMiscId == IMISC_BOOK && item[ii]._iSpell == ispell)
				done = 1;
		} while (!done);
		if (sendmsg)
			NetSendCmdDItem(FALSE, ii);
		if (delta)
			DeltaAddItem(ii);
		++numitems;
	}
}

void CreateMagicArmor(int x, int y, int imisc, int icurs, int sendmsg, int delta)
{
	int ii;    // esi
	int idx;   // ebx
	BOOL done; // [esp+Ch] [ebp-4h]

	done = 0;
	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, ii);
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		itemactive[numitems] = ii;
		idx = RndTypeItems(imisc, 0);
		do {
			SetupAllItems(ii, idx, GetRndSeed(), 2 * currlevel, 1, 1, 0, delta);
			if (item[ii]._iCurs == icurs)
				done = 1;
			else
				idx = RndTypeItems(imisc, 0);
		} while (!done);
		if (sendmsg)
			NetSendCmdDItem(FALSE, ii);
		if (delta)
			DeltaAddItem(ii);
		numitems++;
	}
}

void CreateMagicWeapon(int x, int y, int imisc, int icurs, int sendmsg, int delta)
{
	int ii;    // esi
	int idx;   // ebx
	BOOL done; // [esp+Ch] [ebp-4h]

	done = 0;
	if (numitems < MAXITEMS) {
		ii = itemavail[0];
		GetSuperItemSpace(x, y, ii);
		itemavail[0] = itemavail[MAXITEMS - numitems - 1];
		itemactive[numitems] = ii;
		idx = RndTypeItems(imisc, 0);
		do {
			SetupAllItems(ii, idx, GetRndSeed(), 2 * currlevel, 1, 1, 0, delta);
			if (item[ii]._iCurs == icurs)
				done = 1;
			else
				idx = RndTypeItems(imisc, 0);
		} while (!done);
		if (sendmsg)
			NetSendCmdDItem(FALSE, ii);
		if (delta)
			DeltaAddItem(ii);
		numitems++;
	}
}

BOOL GetItemRecord(int nSeed, WORD wCI, int nIndex)
{
	int i;
	DWORD dwTicks;

	dwTicks = GetTickCount();

	for (i = 0; i < gnNumGetRecords; i++) {
		if (dwTicks - itemrecord[i].dwTimestamp > 6000) {
			NextItemRecord(i);
			i--;
		} else if (nSeed == itemrecord[i].nSeed && wCI == itemrecord[i].wCI && nIndex == itemrecord[i].nIndex) {
			return FALSE;
		}
	}

	return TRUE;
}

void NextItemRecord(int i)
{
	gnNumGetRecords--;

	if (gnNumGetRecords == 0) {
		return;
	}

	itemrecord[i].dwTimestamp = itemrecord[gnNumGetRecords].dwTimestamp;
	itemrecord[i].nSeed = itemrecord[gnNumGetRecords].nSeed;
	itemrecord[i].wCI = itemrecord[gnNumGetRecords].wCI;
	itemrecord[i].nIndex = itemrecord[gnNumGetRecords].nIndex;
}

void SetItemRecord(int nSeed, WORD wCI, int nIndex)
{
	DWORD dwTicks;

	dwTicks = GetTickCount();

	if (gnNumGetRecords == MAXITEMS) {
		return;
	}

	itemrecord[gnNumGetRecords].dwTimestamp = dwTicks;
	itemrecord[gnNumGetRecords].nSeed = nSeed;
	itemrecord[gnNumGetRecords].wCI = wCI;
	itemrecord[gnNumGetRecords].nIndex = nIndex;
	gnNumGetRecords++;
}

void PutItemRecord(int nSeed, WORD wCI, int nIndex)
{
	int i;
	DWORD dwTicks;

	dwTicks = GetTickCount();

	for (i = 0; i < gnNumGetRecords; i++) {
		if (dwTicks - itemrecord[i].dwTimestamp > 6000) {
			NextItemRecord(i);
			i--;
		} else if (nSeed == itemrecord[i].nSeed && wCI == itemrecord[i].wCI && nIndex == itemrecord[i].nIndex) {
			NextItemRecord(i);
			break;
		}
	}
}
