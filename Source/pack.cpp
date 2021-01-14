/**
 * @file pack.cpp
 *
 * Implementation of functions for minifying player data structure.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

#ifndef HELLFIRE
static
#endif
    void
    PackItem(PkItemStruct *id, ItemStruct *is)
{
	if (is->_itype == ITYPE_NONE) {
		id->idx = 0xFFFF;
	} else {
		id->idx = is->IDidx;
		if (is->IDidx == IDI_EAR) {
			id->iCreateInfo = is->_iName[8] | (is->_iName[7] << 8);
			id->iSeed = is->_iName[12] | ((is->_iName[11] | ((is->_iName[10] | (is->_iName[9] << 8)) << 8)) << 8);
			id->bId = is->_iName[13];
			id->bDur = is->_iName[14];
			id->bMDur = is->_iName[15];
			id->bCh = is->_iName[16];
			id->bMCh = is->_iName[17];
			id->wValue = is->_ivalue | (is->_iName[18] << 8) | ((is->_iCurs - ICURS_EAR_SORCEROR) << 6);
			id->dwBuff = is->_iName[22] | ((is->_iName[21] | ((is->_iName[20] | (is->_iName[19] << 8)) << 8)) << 8);
		} else {
			id->iSeed = is->_iSeed;
			id->iCreateInfo = is->_iCreateInfo;
			id->bId = is->_iIdentified + 2 * is->_iMagical;
			id->bDur = is->_iDurability;
			id->bMDur = is->_iMaxDur;
			id->bCh = is->_iCharges;
			id->bMCh = is->_iMaxCharges;
			if (is->IDidx == IDI_GOLD)
				id->wValue = is->_ivalue;
		}
	}
}

#ifdef HELLFIRE
void PackPlayer(PkPlayerStruct *pPack, int pnum)
#else
void PackPlayer(PkPlayerStruct *pPack, int pnum, BOOL manashield)
#endif
{
	PlayerStruct *pPlayer;
	int i;
	ItemStruct *pi;
	PkItemStruct *pki;

	memset(pPack, 0, sizeof(*pPack));
	pPlayer = &plr[pnum];
	pPack->destAction = pPlayer->destAction;
	pPack->destParam1 = pPlayer->destParam1;
	pPack->destParam2 = pPlayer->destParam2;
	pPack->plrlevel = pPlayer->plrlevel;
	pPack->px = pPlayer->_px;
	pPack->py = pPlayer->_py;
	pPack->targx = pPlayer->_ptargx;
	pPack->targy = pPlayer->_ptargy;
	strcpy(pPack->pName, pPlayer->_pName);
	pPack->pClass = pPlayer->_pClass;
	pPack->pBaseStr = pPlayer->_pBaseStr;
	pPack->pBaseMag = pPlayer->_pBaseMag;
	pPack->pBaseDex = pPlayer->_pBaseDex;
	pPack->pBaseVit = pPlayer->_pBaseVit;
	pPack->pLevel = pPlayer->_pLevel;
	pPack->pStatPts = pPlayer->_pStatPts;
	pPack->pExperience = pPlayer->_pExperience;
	pPack->pGold = pPlayer->_pGold;
	pPack->pHPBase = pPlayer->_pHPBase;
	pPack->pMaxHPBase = pPlayer->_pMaxHPBase;
	pPack->pManaBase = pPlayer->_pManaBase;
	pPack->pMaxManaBase = pPlayer->_pMaxManaBase;
	pPack->pMemSpells = pPlayer->_pMemSpells;

#ifdef HELLFIRE
	for (i = 0; i <= 36; i++) // Should be MAX_SPELLS-1 but set to 36 to make save games compatible
		pPack->pSplLvl[i] = pPlayer->_pSplLvl[i];
	char *p = pPack->pSplLvl2;
	for (i = 37; i < 47; i++)
		p[i - 37] = pPlayer->_pSplLvl[i];
#else
	for (i = 0; i < MAX_SPELLS; i++)
		pPack->pSplLvl[i] = pPlayer->_pSplLvl[i];
#endif

	pki = &pPack->InvBody[0];
	pi = &pPlayer->InvBody[0];

	for (i = 0; i < NUM_INVLOC; i++) {
		PackItem(pki, pi);
		pki++;
		pi++;
	}

	pki = &pPack->InvList[0];
	pi = &pPlayer->InvList[0];

	for (i = 0; i < NUM_INV_GRID_ELEM; i++) {
		PackItem(pki, pi);
		pki++;
		pi++;
	}

	for (i = 0; i < NUM_INV_GRID_ELEM; i++)
		pPack->InvGrid[i] = pPlayer->InvGrid[i];

	pPack->_pNumInv = pPlayer->_pNumInv;
	pki = &pPack->SpdList[0];
	pi = &pPlayer->SpdList[0];

	for (i = 0; i < MAXBELTITEMS; i++) {
		PackItem(pki, pi);
		pki++;
		pi++;
	}

#ifdef HELLFIRE
	pPack->wReflections = pPlayer->wReflections;
	pPack->pDiabloKillLevel = pPlayer->pDiabloKillLevel;
	pPack->pDifficulty = pPlayer->pDifficulty;
	pPack->pDamAcFlags = pPlayer->pDamAcFlags;
#else
	pPack->pDiabloKillLevel = pPlayer->pDiabloKillLevel;

	if (gbMaxPlayers == 1 || manashield)
		pPack->pManaShield = pPlayer->pManaShield;
	else
		pPack->pManaShield = FALSE;
#endif
}

/**
 * Expand a PkItemStruct in to a ItemStruct
 *
 * Note: last slot of item[MAXITEMS+1] used as temporary buffer
 * find real name reference below, possibly [sizeof(item[])/sizeof(ItemStruct)]
 * @param is The source packed item
 * @param id The distination item
 */
#ifndef HELLFIRE
static
#endif
    void
    UnPackItem(PkItemStruct *is, ItemStruct *id)
{
	if (is->idx == 0xFFFF) {
		id->_itype = ITYPE_NONE;
	} else {
		if (is->idx == IDI_EAR) {
			RecreateEar(
			    MAXITEMS,
			    is->iCreateInfo,
			    is->iSeed,
			    is->bId,
			    is->bDur,
			    is->bMDur,
			    is->bCh,
			    is->bMCh,
			    is->wValue,
			    is->dwBuff);
		} else {
			RecreateItem(MAXITEMS, is->idx, is->iCreateInfo, is->iSeed, is->wValue);
			item[MAXITEMS]._iMagical = is->bId >> 1;
			item[MAXITEMS]._iIdentified = is->bId & 1;
			item[MAXITEMS]._iDurability = is->bDur;
			item[MAXITEMS]._iMaxDur = is->bMDur;
			item[MAXITEMS]._iCharges = is->bCh;
			item[MAXITEMS]._iMaxCharges = is->bMCh;
		}
		*id = item[MAXITEMS];
	}
}

void VerifyGoldSeeds(PlayerStruct *pPlayer)
{
	int i, j;

	for (i = 0; i < pPlayer->_pNumInv; i++) {
		if (pPlayer->InvList[i].IDidx == IDI_GOLD) {
			for (j = 0; j < pPlayer->_pNumInv; j++) {
				if (i != j) {
					if (pPlayer->InvList[j].IDidx == IDI_GOLD && pPlayer->InvList[i]._iSeed == pPlayer->InvList[j]._iSeed) {
						pPlayer->InvList[i]._iSeed = GetRndSeed();
						j = -1;
					}
				}
			}
		}
	}
}

void UnPackPlayer(PkPlayerStruct *pPack, int pnum, BOOL killok)
{
	PlayerStruct *pPlayer;
	int i;
	ItemStruct *pi;
	PkItemStruct *pki;

	pPlayer = &plr[pnum];
	ClearPlrRVars(pPlayer);
	pPlayer->_px = pPack->px;
	pPlayer->_py = pPack->py;
	pPlayer->_pfutx = pPack->px;
	pPlayer->_pfuty = pPack->py;
	pPlayer->_ptargx = pPack->targx;
	pPlayer->_ptargy = pPack->targy;
	pPlayer->plrlevel = pPack->plrlevel;
	ClrPlrPath(pnum);
	pPlayer->destAction = ACTION_NONE;
	strcpy(pPlayer->_pName, pPack->pName);
	pPlayer->_pClass = pPack->pClass;
	InitPlayer(pnum, TRUE);
	pPlayer->_pBaseStr = pPack->pBaseStr;
	pPlayer->_pStrength = pPack->pBaseStr;
	pPlayer->_pBaseMag = pPack->pBaseMag;
	pPlayer->_pMagic = pPack->pBaseMag;
	pPlayer->_pBaseDex = pPack->pBaseDex;
	pPlayer->_pDexterity = pPack->pBaseDex;
	pPlayer->_pBaseVit = pPack->pBaseVit;
	pPlayer->_pVitality = pPack->pBaseVit;
	pPlayer->_pLevel = pPack->pLevel;
	pPlayer->_pStatPts = pPack->pStatPts;
	pPlayer->_pExperience = pPack->pExperience;
	pPlayer->_pGold = pPack->pGold;
	pPlayer->_pMaxHPBase = pPack->pMaxHPBase;
	pPlayer->_pHPBase = pPack->pHPBase;
	if (!killok)
		if ((int)(pPlayer->_pHPBase & 0xFFFFFFC0) < 64)
			pPlayer->_pHPBase = 64;

	pPlayer->_pMaxManaBase = pPack->pMaxManaBase;
	pPlayer->_pManaBase = pPack->pManaBase;
	pPlayer->_pMemSpells = pPack->pMemSpells;

#ifdef HELLFIRE
	for (i = 0; i <= 36; i++) // Should be MAX_SPELLS-1 but set to 36 to make save games compatible
		pPlayer->_pSplLvl[i] = pPack->pSplLvl[i];
	char *p = pPack->pSplLvl2;
	for (i = 37; i < 47; i++)
		pPlayer->_pSplLvl[i] = p[i - 37];
#else
	for (i = 0; i < MAX_SPELLS; i++)
		pPlayer->_pSplLvl[i] = pPack->pSplLvl[i];
#endif

	pki = &pPack->InvBody[0];
	pi = &pPlayer->InvBody[0];

	for (i = 0; i < NUM_INVLOC; i++) {
		UnPackItem(pki, pi);
		pki++;
		pi++;
	}

	pki = &pPack->InvList[0];
	pi = &pPlayer->InvList[0];

	for (i = 0; i < NUM_INV_GRID_ELEM; i++) {
		UnPackItem(pki, pi);
		pki++;
		pi++;
	}

	for (i = 0; i < NUM_INV_GRID_ELEM; i++)
		pPlayer->InvGrid[i] = pPack->InvGrid[i];

	pPlayer->_pNumInv = pPack->_pNumInv;
	VerifyGoldSeeds(pPlayer);

	pki = &pPack->SpdList[0];
	pi = &pPlayer->SpdList[0];

	for (i = 0; i < MAXBELTITEMS; i++) {
		UnPackItem(pki, pi);
		pki++;
		pi++;
	}

	if (pnum == myplr) {
		for (i = 0; i < 20; i++)
			witchitem[i]._itype = ITYPE_NONE;
	}

	CalcPlrInv(pnum, FALSE);
#ifdef HELLFIRE
	pPlayer->wReflections = pPack->wReflections;
#endif
	pPlayer->pTownWarps = 0;
	pPlayer->pDungMsgs = 0;
#ifdef HELLFIRE
	pPlayer->pDungMsgs2 = 0;
#endif
	pPlayer->pLvlLoad = 0;
	pPlayer->pDiabloKillLevel = pPack->pDiabloKillLevel;
#ifdef HELLFIRE
	pPlayer->pDifficulty = pPack->pDifficulty;
	pPlayer->pDamAcFlags = pPack->pDamAcFlags;
#else
	pPlayer->pBattleNet = pPack->pBattleNet;
	pPlayer->pManaShield = pPack->pManaShield;
#endif
}
