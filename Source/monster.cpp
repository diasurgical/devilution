#include "diablo.h"
#include "../3rdParty/Storm/Source/storm.h"

DEVILUTION_BEGIN_NAMESPACE

// Tracks which missile files are already loaded
int MissileFileFlag;

int monstkills[MAXMONSTERS];
int monstactive[MAXMONSTERS];
int nummonsters;
BOOLEAN sgbSaveSoundOn;
MonsterStruct monster[MAXMONSTERS];
int totalmonsters; // weak
CMonster Monsters[16];
// int END_Monsters_17; // weak
int monstimgtot; // weak
int uniquetrans;
int nummtypes;

const char plr2monst[9] = { 0, 5, 3, 7, 1, 4, 6, 0, 2 };
const unsigned char counsmiss[4] = { MIS_FIREBOLT, MIS_CBOLT, MIS_LIGHTCTRL, MIS_FIREBALL };

/* data */

int MWVel[24][3] = {
	{ 256, 512, 1024 },
	{ 128, 256, 512 },
	{ 85, 170, 341 },
	{ 64, 128, 256 },
	{ 51, 102, 204 },
	{ 42, 85, 170 },
	{ 36, 73, 146 },
	{ 32, 64, 128 },
	{ 28, 56, 113 },
	{ 26, 51, 102 },
	{ 23, 46, 93 },
	{ 21, 42, 85 },
	{ 19, 39, 78 },
	{ 18, 36, 73 },
	{ 17, 34, 68 },
	{ 16, 32, 64 },
	{ 15, 30, 60 },
	{ 14, 28, 57 },
	{ 13, 26, 54 },
	{ 12, 25, 51 },
	{ 12, 24, 48 },
	{ 11, 23, 46 },
	{ 11, 22, 44 },
	{ 10, 21, 42 }
};
char animletter[7] = "nwahds";
int left[8] = { 7, 0, 1, 2, 3, 4, 5, 6 };
int right[8] = { 1, 2, 3, 4, 5, 6, 7, 0 };
int opposite[8] = { 4, 5, 6, 7, 0, 1, 2, 3 };
int offset_x[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
int offset_y[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };

/* unused */
int rnd5[4] = { 5, 10, 15, 20 };
int rnd10[4] = { 10, 15, 20, 30 };
int rnd20[4] = { 20, 30, 40, 50 };
int rnd60[4] = { 60, 70, 80, 90 };
//

void(*AiProc[])(int i) = {
	&MAI_Zombie,
	&MAI_Fat,
	&MAI_SkelSd,
	&MAI_SkelBow,
	&MAI_Scav,
	&MAI_Rhino,
	&MAI_GoatMc,
	&MAI_GoatBow,
	&MAI_Fallen,
	&MAI_Magma,
	&MAI_SkelKing,
	&MAI_Bat,
	&MAI_Garg,
	&MAI_Cleaver,
	&MAI_Succ,
	&MAI_Sneak,
	&MAI_Storm,
	&MAI_Fireman,
	&MAI_Garbud,
	&MAI_Acid,
	&MAI_AcidUniq,
	&MAI_Golum,
	&MAI_Zhar,
	&MAI_SnotSpil,
	&MAI_Snake,
	&MAI_Counselor,
	&MAI_Mega,
	&MAI_Diablo,
	&MAI_Lazurus,
	&MAI_Lazhelp,
	&MAI_Lachdanan,
	&MAI_Warlord
};

void InitMonsterTRN(int monst, BOOL special)
{
	BYTE *f;
	int i, n, j, k;

	f = Monsters[monst].trans_file;
	for (i = 0; i < 256; i++) {
		if (*f == 255) {
			*f = 0;
		}
		f++;
	}

	n = special ? 6 : 5;
	for (j = 0; j < n; ++j) {
		if (j != 1 || Monsters[monst].mtype < MT_COUNSLR || Monsters[monst].mtype > MT_ADVOCATE) {
			for (k = 0; k < 8; k++) {
				Cl2ApplyTrans(
				    Monsters[monst].Anims[j].Data[k],
				    Monsters[monst].trans_file,
				    Monsters[monst].Anims[j].Frames);
			}
		}
	}
}

void InitLevelMonsters()
{
	int i;

	nummtypes = 0;
	monstimgtot = 0;
	MissileFileFlag = 0;

	for (i = 0; i < MAX_LVLMTYPES; i++) {
		Monsters[i].mPlaceFlags = 0;
	}

	ClrAllMonsters();
	nummonsters = 0;
	totalmonsters = MAXMONSTERS;

	for (i = 0; i < MAXMONSTERS; i++) {
		monstactive[i] = i;
	}

	uniquetrans = 0;
}

int AddMonsterType(int type, int placeflag)
{
	BOOL done = FALSE;
	int i;

	for (i = 0; i < nummtypes && !done; i++) {
		done = Monsters[i].mtype == type;
	}

	i--;

	if (!done) {
		i = nummtypes;
		nummtypes++;
		Monsters[i].mtype = type;
		monstimgtot += monsterdata[type].mImage;
		InitMonsterGFX(i);
		InitMonsterSND(i);
	}

	Monsters[i].mPlaceFlags |= placeflag;
	return i;
}

void GetLevelMTypes()
{
	int i;

	// this array is merged with skeltypes down below.
	int typelist[MAXMONSTERS];
	int skeltypes[NUM_MTYPES];

	int minl; // min level
	int maxl; // max level
	char mamask;
	const int numskeltypes = 19;

	int nt; // number of types

	mamask = 3; // monster availability mask

	AddMonsterType(MT_GOLEM, 2);
	if (currlevel == 16) {
		AddMonsterType(MT_ADVOCATE, 1);
		AddMonsterType(MT_RBLACK, 1);
		AddMonsterType(MT_DIABLO, 2);
		return;
	}

	if (!setlevel) {
		if (QuestStatus(QTYPE_BUTCH))
			AddMonsterType(MT_CLEAVER, 2);
		if (QuestStatus(QTYPE_GARB))
			AddMonsterType(UniqMonst[UMT_GARBUD].mtype, 4);
		if (QuestStatus(QTYPE_ZHAR))
			AddMonsterType(UniqMonst[UMT_ZHAR].mtype, 4);
		if (QuestStatus(QTYPE_BOL))
			AddMonsterType(UniqMonst[UMT_SNOTSPIL].mtype, 4);
		if (QuestStatus(QTYPE_VEIL))
			AddMonsterType(UniqMonst[UMT_LACHDAN].mtype, 4);
		if (QuestStatus(QTYPE_WARLRD))
			AddMonsterType(UniqMonst[UMT_WARLORD].mtype, 4);

		if (gbMaxPlayers != 1 && currlevel == quests[QTYPE_KING]._qlevel) {

			AddMonsterType(MT_SKING, 4);

			nt = 0;
			for (i = MT_WSKELAX; i <= MT_WSKELAX + numskeltypes; i++) {
				if (IsSkel(i)) {
					minl = 15 * monsterdata[i].mMinDLvl / 30 + 1;
					maxl = 15 * monsterdata[i].mMaxDLvl / 30 + 1;

					if (currlevel >= minl && currlevel <= maxl) {
						if (MonstAvailTbl[i] & mamask) {
							skeltypes[nt++] = i;
						}
					}
				}
			}
			AddMonsterType(skeltypes[random(88, nt)], 1);
		}

		nt = 0;
		for (i = 0; i < 111; i++) {
			minl = 15 * monsterdata[i].mMinDLvl / 30 + 1;
			maxl = 15 * monsterdata[i].mMaxDLvl / 30 + 1;

			if (currlevel >= minl && currlevel <= maxl) {
				if (MonstAvailTbl[i] & mamask) {
					typelist[nt++] = i;
				}
			}
		}

		if (monstdebug) {
			for (i = 0; i < debugmonsttypes; i++)
				AddMonsterType(DebugMonsters[i], 1);
		} else {

			while (nt > 0 && nummtypes < MAX_LVLMTYPES && monstimgtot < 4000) {
				for (i = 0; i < nt;) {
					if (monsterdata[typelist[i]].mImage > 4000 - monstimgtot) {
						typelist[i] = typelist[--nt];
						continue;
					}

					i++;
				}

				if (nt != 0) {
					i = random(88, nt);
					AddMonsterType(typelist[i], 1);
					typelist[i] = typelist[--nt];
				}
			}
		}

	} else {
		if (setlvlnum == SL_SKELKING) {
			AddMonsterType(MT_SKING, 4);
		}
	}
}

void InitMonsterGFX(int monst)
{
	int mtype, anim, i;
	char strBuff[256];
	unsigned char *celBuf;
	void *trans_file;

	mtype = (unsigned char)Monsters[monst].mtype;

	for (anim = 0; anim < 6; anim++) {
		if ((animletter[anim] != 's' || monsterdata[mtype].has_special) && monsterdata[mtype].Frames[anim] > 0) {
			sprintf(strBuff, monsterdata[mtype].GraphicType, animletter[anim]);

			celBuf = LoadFileInMem(strBuff, NULL);
			Monsters[monst].Anims[anim].CMem = celBuf;

			if (Monsters[monst].mtype != MT_GOLEM || (animletter[anim] != 's' && animletter[anim] != 'd')) {

				for (i = 0; i < 8; i++) {
					Monsters[monst].Anims[anim].Data[i] = &celBuf[((int *)celBuf)[i]];
				}
			} else {
				for (i = 0; i < 8; i++) {
					Monsters[monst].Anims[anim].Data[i] = celBuf;
				}
			}
		}

		// TODO: either the AnimStruct members have wrong naming or the MonsterData ones it seems
		Monsters[monst].Anims[anim].Frames = monsterdata[mtype].Frames[anim];
		Monsters[monst].Anims[anim].Rate = monsterdata[mtype].Rate[anim];
	}

	Monsters[monst].width = monsterdata[mtype].width;
	Monsters[monst].width2 = (monsterdata[mtype].width - 64) >> 1;
	Monsters[monst].mMinHP = monsterdata[mtype].mMinHP;
	Monsters[monst].mMaxHP = monsterdata[mtype].mMaxHP;
	Monsters[monst].has_special = monsterdata[mtype].has_special;
	Monsters[monst].mAFNum = monsterdata[mtype].mAFNum;
	Monsters[monst].MData = &monsterdata[mtype];

	if (monsterdata[mtype].has_trans) {
		Monsters[monst].trans_file = LoadFileInMem(monsterdata[mtype].TransFile, NULL);
		InitMonsterTRN(monst, monsterdata[mtype].has_special);

		trans_file = Monsters[monst].trans_file;
		Monsters[monst].trans_file = NULL;

		mem_free_dbg(trans_file);
	}

	if (mtype >= MT_NMAGMA && mtype <= MT_WMAGMA && !(MissileFileFlag & 1)) {
		MissileFileFlag |= 1;
		LoadMissileGFX(MFILE_MAGBALL);
	}
	if (mtype >= MT_STORM && mtype <= MT_MAEL && !(MissileFileFlag & 2)) {
		MissileFileFlag |= 2;
		LoadMissileGFX(MFILE_THINLGHT);
	}
	if (mtype == MT_SUCCUBUS) {
		if (MissileFileFlag & 4)
			return;

		MissileFileFlag |= 4;
		LoadMissileGFX(MFILE_FLARE);
		LoadMissileGFX(MFILE_FLAREEXP);
	}
	if (mtype == MT_SNOWWICH) {
		if (MissileFileFlag & 0x20)
			return;

		MissileFileFlag |= 0x20;
		LoadMissileGFX(MFILE_SCUBMISB);
		LoadMissileGFX(MFILE_SCBSEXPB);
	}
	if (mtype == MT_HLSPWN) {
		if (MissileFileFlag & 0x40)
			return;

		MissileFileFlag |= 0x40;
		LoadMissileGFX(MFILE_SCUBMISD);
		LoadMissileGFX(MFILE_SCBSEXPD);
	}
	if (mtype == MT_SOLBRNR) {
		if (MissileFileFlag & 0x80)
			return;

		MissileFileFlag |= 0x80;
		LoadMissileGFX(MFILE_SCUBMISC);
		LoadMissileGFX(MFILE_SCBSEXPC);
	}
	if (mtype >= MT_INCIN && mtype <= MT_HELLBURN && !(MissileFileFlag & 8)) {
		MissileFileFlag |= 8;
		LoadMissileGFX(MFILE_KRULL);
	}
	if (mtype >= MT_NACID && mtype <= MT_XACID && !(MissileFileFlag & 0x10)) {
		MissileFileFlag |= 0x10;
		LoadMissileGFX(MFILE_ACIDBF);
		LoadMissileGFX(MFILE_ACIDSPLA);
		LoadMissileGFX(MFILE_ACIDPUD);
	}
	if (mtype == MT_DIABLO) {
		LoadMissileGFX(MFILE_FIREPLAR);
	}
}

void ClearMVars(int i)
{
	monster[i]._mVar1 = 0;
	monster[i]._mVar2 = 0;
	monster[i]._mVar3 = 0;
	monster[i]._mVar4 = 0;
	monster[i]._mVar5 = 0;
	monster[i]._mVar6 = 0;
	monster[i]._mVar7 = 0;
	monster[i]._mVar8 = 0;
}

void InitMonster(int i, int rd, int mtype, int x, int y)
{
	CMonster *monst = &Monsters[mtype];

	monster[i]._mdir = rd;
	monster[i]._mx = x;
	monster[i]._my = y;
	monster[i]._mfutx = x;
	monster[i]._mfuty = y;
	monster[i]._moldx = x;
	monster[i]._moldy = y;
	monster[i]._mmode = MM_STAND;
	monster[i]._mMTidx = mtype;
	monster[i].mName = monst->MData->mName;
	monster[i].MType = monst;
	monster[i].MData = monst->MData;
	monster[i]._mAnimData = monst->Anims[MA_STAND].Data[rd];
	monster[i]._mAnimDelay = monst->Anims[MA_STAND].Rate;
	monster[i]._mAnimCnt = random(88, monst->Anims[MA_STAND].Rate - 1);
	monster[i]._mAnimLen = monst->Anims[MA_STAND].Frames;
	monster[i]._mAnimFrame = random(88, monst->Anims[MA_STAND].Frames - 1) + 1;

	if (monst->mtype == MT_DIABLO) {
		monster[i]._mmaxhp = (random(88, 1) + 1666) << 6;
	} else {
		monster[i]._mmaxhp = (monst->mMinHP + random(88, monst->mMaxHP - monst->mMinHP + 1)) << 6;
	}

	if (gbMaxPlayers == 1) {
		monster[i]._mmaxhp >>= 1;
		if (monster[i]._mmaxhp < 64) {
			monster[i]._mmaxhp = 64;
		}
	}

	monster[i]._mhitpoints = monster[i]._mmaxhp;
	monster[i]._mAi = monst->MData->mAi;
	monster[i]._mint = monst->MData->mInt;
	monster[i]._mgoal = MGOAL_NORMAL;
	monster[i]._mgoalvar1 = 0;
	monster[i]._mgoalvar2 = 0;
	monster[i]._mgoalvar3 = 0;
	monster[i]._pathcount = 0;
	monster[i]._uniqtype = 0;
	monster[i]._msquelch = 0;
	monster[i].field_18 = 0;
	monster[i]._mDelFlag = FALSE;
	monster[i]._mRndSeed = GetRndSeed();
	monster[i]._mAISeed = GetRndSeed();
	monster[i].mWhoHit = 0;
	monster[i].mLevel = monst->MData->mLevel;
	monster[i].mExp = monst->MData->mExp;
	monster[i].mHit = monst->MData->mHit;
	monster[i].mMinDamage = monst->MData->mMinDamage;
	monster[i].mMaxDamage = monst->MData->mMaxDamage;
	monster[i].mHit2 = monst->MData->mHit2;
	monster[i].mMinDamage2 = monst->MData->mMinDamage2;
	monster[i].mMaxDamage2 = monst->MData->mMaxDamage2;
	monster[i].mArmorClass = monst->MData->mArmorClass;
	monster[i].mMagicRes = monst->MData->mMagicRes;
	monster[i].leader = 0;
	monster[i].leaderflag = 0;
	monster[i]._mFlags = monst->MData->mFlags;
	monster[i].mtalkmsg = 0;

	if (monster[i]._mAi == AI_GARG) {
		monster[i]._mAnimData = monst->Anims[MA_SPECIAL].Data[rd];
		monster[i]._mAnimFrame = 1;
		monster[i]._mFlags |= MFLAG_ALLOW_SPECIAL;
		monster[i]._mmode = MM_SATTACK;
	}

	if (gnDifficulty == DIFF_NIGHTMARE) {
		monster[i].mLevel += 15;
		monster[i].mHit += 85;
		monster[i].mHit2 += 85;
		monster[i]._mmaxhp = 3 * monster[i]._mmaxhp + 64;
		monster[i]._mhitpoints = monster[i]._mmaxhp;
		monster[i].mExp = 2 * (monster[i].mExp + 1000);
		monster[i].mMinDamage = 2 * (monster[i].mMinDamage + 2);
		monster[i].mMaxDamage = 2 * (monster[i].mMaxDamage + 2);
		monster[i].mMinDamage2 = 2 * (monster[i].mMinDamage2 + 2);
		monster[i].mMaxDamage2 = 2 * (monster[i].mMaxDamage2 + 2);
		monster[i].mArmorClass += 50;
	}

	if (gnDifficulty == DIFF_HELL) {
		monster[i].mLevel += 30;
		monster[i]._mmaxhp = 4 * monster[i]._mmaxhp + 192;
		monster[i]._mhitpoints = monster[i]._mmaxhp;
		monster[i].mHit += 120;
		monster[i].mHit2 += 120;
		monster[i].mExp = 4 * (monster[i].mExp + 1000);
		monster[i].mMinDamage = 4 * monster[i].mMinDamage + 6;
		monster[i].mMaxDamage = 4 * monster[i].mMaxDamage + 6;
		monster[i].mMinDamage2 = 4 * monster[i].mMinDamage2 + 6;
		monster[i].mMaxDamage2 = 4 * monster[i].mMaxDamage2 + 6;
		monster[i].mArmorClass += 80;
		monster[i].mMagicRes = monst->MData->mMagicRes2;
	}
}

void ClrAllMonsters()
{
	int i;
	MonsterStruct *Monst;

	for (i = 0; i < MAXMONSTERS; i++) {
		Monst = &monster[i];
		ClearMVars(i);
		Monst->mName = "Invalid Monster";
		Monst->_mgoal = 0;
		Monst->_mmode = MM_STAND;
		Monst->_mVar1 = 0;
		Monst->_mVar2 = 0;
		Monst->_mx = 0;
		Monst->_my = 0;
		Monst->_mfutx = 0;
		Monst->_mfuty = 0;
		Monst->_moldx = 0;
		Monst->_moldy = 0;
		Monst->_mdir = random(89, 8);
		Monst->_mxvel = 0;
		Monst->_myvel = 0;
		Monst->_mAnimData = NULL;
		Monst->_mAnimDelay = 0;
		Monst->_mAnimCnt = 0;
		Monst->_mAnimLen = 0;
		Monst->_mAnimFrame = 0;
		Monst->_mFlags = 0;
		Monst->_mDelFlag = FALSE;
		Monst->_menemy = random(89, gbActivePlayers);
		Monst->_menemyx = plr[Monst->_menemy]._px;
		Monst->_menemyy = plr[Monst->_menemy]._py;
	}
}

BOOL MonstPlace(int xp, int yp)
{
	char f;

	if (xp < 0 || xp >= MAXDUNX
	    || yp < 0 || yp >= MAXDUNY
	    || dMonster[xp][yp]
	    || dPlayer[xp][yp]) {
		return FALSE;
	}

	f = dFlags[xp][yp];

	if (f & DFLAG_VISIBLE) {
		return FALSE;
	}

	if (f & DFLAG_POPULATED) {
		return FALSE;
	}

	return !SolidLoc(xp, yp);
}

void PlaceMonster(int i, int mtype, int x, int y)
{
	int rd;

	dMonster[x][y] = i + 1;

	rd = random(90, 8);
	InitMonster(i, rd, mtype, x, y);
}

void PlaceUniqueMonst(int uniqindex, int miniontype, int packsize)
{
	int xp, yp, x, y, i;
	int uniqtype;
	int count2;
	char filestr[64];
	BOOL zharflag, done;
	UniqMonstStruct *Uniq;
	MonsterStruct *Monst;
	int count;

	Monst = monster + nummonsters;
	count = 0;
	Uniq = UniqMonst + uniqindex;

	if ((uniquetrans + 19) << 8 >= LIGHTSIZE) {
		return;
	}

	for (uniqtype = 0; uniqtype < nummtypes; uniqtype++) {
		if (Monsters[uniqtype].mtype == UniqMonst[uniqindex].mtype) {
			break;
		}
	}

	while (1) {
		xp = random(91, 80) + 16;
		yp = random(91, 80) + 16;
		count2 = 0;
		for (x = xp - 3; x < xp + 3; x++) {
			for (y = yp - 3; y < yp + 3; y++) {
				if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX && MonstPlace(x, y)) {
					count2++;
				}
			}
		}

		if (count2 < 9) {
			count++;
			if (count < 1000) {
				continue;
			}
		}

		if (MonstPlace(xp, yp)) {
			break;
		}
	}

	if (uniqindex == 3) {
		xp = 2 * setpc_x + 24;
		yp = 2 * setpc_y + 28;
	}
	if (uniqindex == 8) {
		xp = 2 * setpc_x + 22;
		yp = 2 * setpc_y + 23;
	}
	if (uniqindex == 2) {
		zharflag = TRUE;
		for (i = 0; i < themeCount; i++) {
			if (i == zharlib && zharflag == TRUE) {
				zharflag = FALSE;
				xp = 2 * themeLoc[i].x + 20;
				yp = 2 * themeLoc[i].y + 20;
			}
		}
	}
	if (gbMaxPlayers == 1) {
		if (uniqindex == 4) {
			xp = 32;
			yp = 46;
		}
		if (uniqindex == 5) {
			xp = 40;
			yp = 45;
		}
		if (uniqindex == 6) {
			xp = 38;
			yp = 49;
		}
		if (uniqindex == 1) {
			xp = 35;
			yp = 47;
		}
	} else {
		if (uniqindex == 4) {
			xp = 2 * setpc_x + 19;
			yp = 2 * setpc_y + 22;
		}
		if (uniqindex == 5) {
			xp = 2 * setpc_x + 21;
			yp = 2 * setpc_y + 19;
		}
		if (uniqindex == 6) {
			xp = 2 * setpc_x + 21;
			yp = 2 * setpc_y + 25;
		}
	}
	if (uniqindex == 9) {
		done = FALSE;
		for (yp = 0; yp < MAXDUNY && !done; yp++) {
			for (xp = 0; xp < MAXDUNX && !done; xp++) {
				done = dPiece[xp][yp] == 367;
			}
		}
	}

	PlaceMonster(nummonsters, uniqtype, xp, yp);
	Monst->_uniqtype = uniqindex + 1;

	if (Uniq->mlevel) {
		Monst->mLevel = 2 * Uniq->mlevel;
	} else {
		Monst->mLevel += 5;
	}

	Monst->mExp *= 2;
	Monst->mName = Uniq->mName;
	Monst->_mmaxhp = Uniq->mmaxhp << 6;

	if (gbMaxPlayers == 1) {
		Monst->_mmaxhp = Monst->_mmaxhp >> 1;
		if (Monst->_mmaxhp < 64) {
			Monst->_mmaxhp = 64;
		}
	}

	Monst->_mhitpoints = Monst->_mmaxhp;
	Monst->_mAi = Uniq->mAi;
	Monst->_mint = Uniq->mint;
	Monst->mMinDamage = Uniq->mMinDamage;
	Monst->mMaxDamage = Uniq->mMaxDamage;
	Monst->mMinDamage2 = Uniq->mMinDamage;
	Monst->mMaxDamage2 = Uniq->mMaxDamage;
	Monst->mMagicRes = Uniq->mMagicRes;
	Monst->mtalkmsg = Uniq->mtalkmsg;
	Monst->mlid = AddLight(Monst->_mx, Monst->_my, 3);

	if (gbMaxPlayers == 1) {
		if (Monst->mtalkmsg) {
			Monst->_mgoal = MGOAL_INQUIRING;
		}
	} else {
		if (Monst->_mAi == AI_LAZHELP) {
			Monst->mtalkmsg = 0;
		}

		if (Monst->_mAi != AI_LAZURUS || quests[QTYPE_VB]._qvar1 <= 3) {
			if (Monst->mtalkmsg) {
				Monst->_mgoal = MGOAL_INQUIRING;
			}
		} else {
			Monst->_mgoal = MGOAL_NORMAL;
		}
	}

	if (gnDifficulty == DIFF_NIGHTMARE) {
		Monst->mLevel += 15;
		Monst->_mmaxhp = 3 * Monst->_mmaxhp + 64;
		Monst->_mhitpoints = Monst->_mmaxhp;
		Monst->mExp = 2 * (Monst->mExp + 1000);
		Monst->mMinDamage = 2 * (Monst->mMinDamage + 2);
		Monst->mMaxDamage = 2 * (Monst->mMaxDamage + 2);
		Monst->mMinDamage2 = 2 * (Monst->mMinDamage2 + 2);
		Monst->mMaxDamage2 = 2 * (Monst->mMaxDamage2 + 2);
	}

	if (gnDifficulty == DIFF_HELL) {
		Monst->mLevel += 30;
		Monst->_mmaxhp = 4 * Monst->_mmaxhp + 192;
		Monst->_mhitpoints = Monst->_mmaxhp;
		Monst->mExp = 4 * (Monst->mExp + 1000);
		Monst->mMinDamage = 4 * Monst->mMinDamage + 6;
		Monst->mMaxDamage = 4 * Monst->mMaxDamage + 6;
		Monst->mMinDamage2 = 4 * Monst->mMinDamage2 + 6;
		Monst->mMaxDamage2 = 4 * Monst->mMaxDamage2 + 6;
	}

	sprintf(filestr, "Monsters\\Monsters\\%s.TRN", Uniq->mTrnName);
	LoadFileWithMem(filestr, &pLightTbl[256 * (uniquetrans + 19)]);

	Monst->_uniqtrans = uniquetrans++;

	if (Uniq->mUnqAttr & 4) {
		Monst->mHit = Uniq->mUnqVar1;
		Monst->mHit2 = Uniq->mUnqVar1;
	}
	if (Uniq->mUnqAttr & 8) {
		Monst->mArmorClass = Uniq->mUnqVar1;
	}

	nummonsters++;

	if (Uniq->mUnqAttr & 1) {
		PlaceGroup(miniontype, packsize, Uniq->mUnqAttr, nummonsters - 1);
	}

	if (Monst->_mAi != AI_GARG) {
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[Monst->_mdir];
		Monst->_mAnimFrame = random(88, Monst->_mAnimLen - 1) + 1;
		Monst->_mFlags &= ~MFLAG_ALLOW_SPECIAL;
		Monst->_mmode = MM_STAND;
	}
}

void PlaceQuestMonsters()
{
	int skeltype;
	unsigned char *setp;

	if (!setlevel) {
		if (QuestStatus(QTYPE_BUTCH)) {
			PlaceUniqueMonst(UMT_BUTCHER, 0, 0);
		}

		if (currlevel == quests[QTYPE_KING]._qlevel && gbMaxPlayers != 1) {
			skeltype = 0;

			for (skeltype = 0; skeltype < nummtypes; skeltype++) {
				if (IsSkel(Monsters[skeltype].mtype)) {
					break;
				}
			}

			PlaceUniqueMonst(UMT_SKELKING, skeltype, 30);
		}

		if (QuestStatus(QTYPE_BOL)) {
			setp = LoadFileInMem("Levels\\L1Data\\Banner1.DUN", 0);
			SetMapMonsters(setp, 2 * setpc_x, 2 * setpc_y);
			mem_free_dbg(setp);
		}
		if (QuestStatus(QTYPE_BLOOD)) {
			setp = LoadFileInMem("Levels\\L2Data\\Blood2.DUN", 0);
			SetMapMonsters(setp, 2 * setpc_x, 2 * setpc_y);
			mem_free_dbg(setp);
		}
		if (QuestStatus(QTYPE_BLIND)) {
			setp = LoadFileInMem("Levels\\L2Data\\Blind2.DUN", 0);
			SetMapMonsters(setp, 2 * setpc_x, 2 * setpc_y);
			mem_free_dbg(setp);
		}
		if (QuestStatus(QTYPE_ANVIL)) {
			setp = LoadFileInMem("Levels\\L3Data\\Anvil.DUN", 0);
			SetMapMonsters(setp, 2 * setpc_x + 2, 2 * setpc_y + 2);
			mem_free_dbg(setp);
		}
		if (QuestStatus(QTYPE_WARLRD)) {
			setp = LoadFileInMem("Levels\\L4Data\\Warlord.DUN", 0);
			SetMapMonsters(setp, 2 * setpc_x, 2 * setpc_y);
			mem_free_dbg(setp);
			AddMonsterType(UniqMonst[UMT_WARLORD].mtype, 1);
		}
		if (QuestStatus(QTYPE_VEIL)) {
			AddMonsterType(UniqMonst[UMT_LACHDAN].mtype, 1);
		}
		if (QuestStatus(QTYPE_ZHAR) && zharlib == -1) {
			quests[QTYPE_ZHAR]._qactive = 0;
		}

		if (currlevel == quests[QTYPE_VB]._qlevel && gbMaxPlayers != 1) {
			AddMonsterType(UniqMonst[UMT_LAZURUS].mtype, 4);
			AddMonsterType(UniqMonst[UMT_RED_VEX].mtype, 4);
			PlaceUniqueMonst(UMT_LAZURUS, 0, 0);
			PlaceUniqueMonst(UMT_RED_VEX, 0, 0);
			PlaceUniqueMonst(UMT_BLACKJADE, 0, 0);
			setp = LoadFileInMem("Levels\\L4Data\\Vile1.DUN", 0);
			SetMapMonsters(setp, 2 * setpc_x, 2 * setpc_y);
			mem_free_dbg(setp);
		}
	} else {
		if (setlvlnum == SL_SKELKING) {
			PlaceUniqueMonst(UMT_SKELKING, 0, 0);
		}
	}
}

void PlaceGroup(int mtype, int num, int leaderf, int leader)
{
	int placed, try1, try2, j;
	int xp, yp, x1, y1;

	placed = 0;

	for (try1 = 0; try1 < 10; try1++) {
		while (placed) {
			nummonsters--;
			placed--;
			dMonster[monster[nummonsters]._mx][monster[nummonsters]._my] = 0;
		}

		x1 = 0;
		y1 = 0;
		xp = 0;
		yp = 0;
		if (leaderf & 1) {
			int offset = random(92, 8);
			xp = monster[leader]._mx + offset_x[offset];
			yp = monster[leader]._my + offset_y[offset];
			x1 = xp;
			y1 = yp;
		} else {
			do {
				xp = random(93, 80) + 16;
				x1 = xp;
				yp = random(93, 80) + 16;
				y1 = yp;
			} while (!MonstPlace(xp, yp));
		}

		if (num + nummonsters > totalmonsters) {
			num = totalmonsters - nummonsters;
		}

		j = 0;
		for (try2 = 0; j < num && try2 < 100; xp += offset_x[random(94, 8)], yp += offset_x[random(94, 8)]) {
			if (!MonstPlace(xp, yp)
			    || (dTransVal[xp][yp] != dTransVal[x1][y1])
			    || (leaderf & 2) && ((abs(xp - x1) >= 4) || (abs(yp - y1) >= 4))) {
				try2++;
				continue;
			}

			PlaceMonster(nummonsters, mtype, xp, yp);
			if (leaderf & 1) {
				monster[nummonsters]._mmaxhp *= 2;
				monster[nummonsters]._mhitpoints = monster[nummonsters]._mmaxhp;
				monster[nummonsters]._mint = monster[leader]._mint;

				if (leaderf & 2) {
					monster[nummonsters].leader = leader;
					monster[nummonsters].leaderflag = 1;
					monster[nummonsters]._mAi = monster[leader]._mAi;
				}

				if (monster[nummonsters]._mAi != AI_GARG) {
					monster[nummonsters]._mAnimData = monster[nummonsters].MType->Anims[MA_STAND].Data[monster[nummonsters]._mdir];
					monster[nummonsters]._mAnimFrame = random(88, monster[nummonsters]._mAnimLen - 1) + 1;
					monster[nummonsters]._mFlags &= ~MFLAG_ALLOW_SPECIAL;
					monster[nummonsters]._mmode = MM_STAND;
				}
			}
			nummonsters++;
			placed++;
			j++;
		}

		if (placed >= num) {
			break;
		}
	}

	if (leaderf & 2) {
		monster[leader].packsize = placed;
	}
}

void LoadDiabMonsts()
{
	unsigned char *lpSetPiece; // esi

	lpSetPiece = LoadFileInMem("Levels\\L4Data\\diab1.DUN", 0);
	SetMapMonsters(lpSetPiece, 2 * diabquad1x, 2 * diabquad1y);
	mem_free_dbg(lpSetPiece);
	lpSetPiece = LoadFileInMem("Levels\\L4Data\\diab2a.DUN", 0);
	SetMapMonsters(lpSetPiece, 2 * diabquad2x, 2 * diabquad2y);
	mem_free_dbg(lpSetPiece);
	lpSetPiece = LoadFileInMem("Levels\\L4Data\\diab3a.DUN", 0);
	SetMapMonsters(lpSetPiece, 2 * diabquad3x, 2 * diabquad3y);
	mem_free_dbg(lpSetPiece);
	lpSetPiece = LoadFileInMem("Levels\\L4Data\\diab4a.DUN", 0);
	SetMapMonsters(lpSetPiece, 2 * diabquad4x, 2 * diabquad4y);
	mem_free_dbg(lpSetPiece);
}
// 5289C4: using guessed type int diabquad1x;
// 5289C8: using guessed type int diabquad1y;

void InitMonsters()
{
	int na, nt;
	int i, s, t;
	int numplacemonsters;
	int mtype;
	int numscattypes;
	int scattertypes[111];

	numscattypes = 0;
	if (gbMaxPlayers != 1)
		CheckDungeonClear();
	if (!setlevel) {
		AddMonster(1, 0, 0, 0, FALSE);
		AddMonster(1, 0, 0, 0, FALSE);
		AddMonster(1, 0, 0, 0, FALSE);
		AddMonster(1, 0, 0, 0, FALSE);
		if (!setlevel && currlevel == 16)
			LoadDiabMonsts();
	}
	nt = trigflag_4;
	if (currlevel == 15)
		nt = 1;
	for (i = 0; i < nt; i++) {
		for (s = -2; s < 2; s++) {
			for (t = -2; t < 2; t++)
				DoVision(s + trigs[i]._tx, t + trigs[i]._ty, 15, FALSE, FALSE);
		}
	}
	PlaceQuestMonsters();
	if (!setlevel) {
		PlaceUniques();
		na = 0;
		for (s = 16; s < 96; s++)
			for (t = 16; t < 96; t++)
				if (!SolidLoc(s, t))
					na++;
		numplacemonsters = na / 30;
		if (gbMaxPlayers != 1)
			numplacemonsters += numplacemonsters >> 1;
		if (nummonsters + numplacemonsters > 190)
			numplacemonsters = 190 - nummonsters;
		totalmonsters = nummonsters + numplacemonsters;
		for (i = 0; i < nummtypes; i++) {
			if (Monsters[i].mPlaceFlags & 1) {
				scattertypes[numscattypes] = i;
				numscattypes++;
			}
		}
		while (nummonsters < totalmonsters) {
			mtype = scattertypes[random(95, numscattypes)];
			if (currlevel == 1 || random(95, 2) == 0)
				na = 1;
			else if (currlevel == 2)
				na = random(95, 2) + 2;
			else
				na = random(95, 3) + 3;
			PlaceGroup(mtype, na, 0, 0);
		}
	}
	for (i = 0; i < nt; i++) {
		for (s = -2; s < 2; s++) {
			for (t = -2; t < 2; t++)
				DoUnVision(s + trigs[i]._tx, t + trigs[i]._ty, 15);
		}
	}
}
// 5CF31D: using guessed type char setlevel;
// 658550: using guessed type int totalmonsters;
// 679660: using guessed type char gbMaxPlayers;
// 432637: using guessed type int var_1BC[111];

void PlaceUniques()
{
	int u;
	BOOL done;
	int mt;

	for (u = 0; UniqMonst[u].mtype != -1; u++) {
		if (UniqMonst[u].mlevel != currlevel)
			continue;
		done = FALSE;
		for (mt = 0; mt < nummtypes; mt++) {
			if (done)
				break;
			done = (Monsters[mt].mtype == UniqMonst[u].mtype);
		}
		mt--;
		if (u == UMT_GARBUD && quests[QTYPE_GARB]._qactive == 0)
			done = FALSE;
		if (u == UMT_ZHAR && quests[QTYPE_ZHAR]._qactive == 0)
			done = FALSE;
		if (u == UMT_SNOTSPIL && quests[QTYPE_BOL]._qactive == 0)
			done = FALSE;
		if (u == UMT_LACHDAN && quests[QTYPE_VEIL]._qactive == 0)
			done = FALSE;
		if (u == UMT_WARLORD && quests[QTYPE_WARLRD]._qactive == 0)
			done = FALSE;
		if (done)
			PlaceUniqueMonst(u, mt, 8);
	}
}

void SetMapMonsters(unsigned char *pMap, int startx, int starty)
{
	WORD rw, rh;
	WORD *lm;
	int i, j;
	int mtype;

	AddMonsterType(MT_GOLEM, 2);
	AddMonster(1, 0, 0, 0, FALSE);
	AddMonster(1, 0, 0, 0, FALSE);
	AddMonster(1, 0, 0, 0, FALSE);
	AddMonster(1, 0, 0, 0, FALSE);
	if (setlevel && setlvlnum == SL_VILEBETRAYER) {
		AddMonsterType(UniqMonst[UMT_LAZURUS].mtype, 4);
		AddMonsterType(UniqMonst[UMT_RED_VEX].mtype, 4);
		AddMonsterType(UniqMonst[UMT_BLACKJADE].mtype, 4);
		PlaceUniqueMonst(UMT_LAZURUS, 0, 0);
		PlaceUniqueMonst(UMT_RED_VEX, 0, 0);
		PlaceUniqueMonst(UMT_BLACKJADE, 0, 0);
	}
	lm = (WORD*)pMap;
	rw = *lm;
	lm++;
	rh = *lm;
	lm += (rw * rh + 1);
	rw = rw << 1;
	rh = rh << 1;
	lm += rw * rh;

	for (j = 0; j < rh; j++) {
		for (i = 0; i < rw; i++) {
			if (*lm) {
				mtype = AddMonsterType(MonstConvTbl[(*lm) - 1], 2);
				PlaceMonster(nummonsters++, mtype, i + startx + 16, j + starty + 16);
			}
			lm++;
		}
	}
}
// 5CF31D: using guessed type char setlevel;

void DeleteMonster(int i)
{
	int temp;

	nummonsters--;
	temp = monstactive[nummonsters];
	monstactive[nummonsters] = monstactive[i];
	monstactive[i] = temp;
}

int AddMonster(int x, int y, int dir, int mtype, BOOL InMap)
{
	if (nummonsters < MAXMONSTERS) {
		int i = monstactive[nummonsters++];
		if (InMap)
			dMonster[x][y] = i + 1;
		InitMonster(i, dir, mtype, x, y);
		return i;
	}

	return -1;
}

void NewMonsterAnim(int i, AnimStruct *anim, int md)
{
	monster[i]._mAnimData = anim->Data[md];
	monster[i]._mAnimCnt = 0;
	monster[i]._mAnimLen = anim->Frames;
	monster[i]._mAnimFrame = 1;
	monster[i]._mFlags &= ~(MFLAG_LOCK_ANIMATION | MFLAG_ALLOW_SPECIAL);
	monster[i]._mAnimDelay = anim->Rate;
	monster[i]._mdir = md;
}

BOOL M_Ranged(int i)
{
	char ai = monster[i]._mAi;
	return ai == AI_SKELBOW || ai == AI_GOATBOW || ai == AI_SUCC || ai == AI_LAZHELP;
}

BOOL M_Talker(int i)
{
	char ai = monster[i]._mAi;
	return ai == AI_LAZURUS
	    || ai == AI_WARLORD
	    || ai == AI_GARBUD
	    || ai == AI_ZHAR
	    || ai == AI_SNOTSPIL
	    || ai == AI_LACHDAN
	    || ai == AI_LAZHELP;
}

void M_Enemy(int i)
{
	int j;
	int mi, pnum;
	int dist, best_dist;
	int _menemy;
	BOOL sameroom, bestsameroom;
	MonsterStruct *Monst;
	BYTE enemyx, enemyy;

	_menemy = -1;
	best_dist = -1;
	bestsameroom = 0;
	Monst = monster + i;
	if (!(Monst->_mFlags & MFLAG_GOLEM)) {
		for (pnum = 0; pnum < MAX_PLRS; pnum++) {
			if (!plr[pnum].plractive || currlevel != plr[pnum].plrlevel || plr[pnum]._pLvlChanging || (plr[pnum]._pHitPoints == 0 && gbMaxPlayers != 1))
				continue;
			if (dTransVal[Monst->_mx][Monst->_my] == dTransVal[plr[pnum].WorldX][plr[pnum].WorldY])
				sameroom = TRUE;
			else
				sameroom = FALSE;
			if (abs(Monst->_mx - plr[pnum].WorldX) > abs(Monst->_my - plr[pnum].WorldY))
				dist = Monst->_mx - plr[pnum].WorldX;
			else
				dist = Monst->_my - plr[pnum].WorldY;
			dist = abs(dist);
			if ((sameroom && !bestsameroom)
			    || ((sameroom || !bestsameroom) && dist < best_dist)
			    || (_menemy == -1)) {
				Monst->_mFlags &= ~MFLAG_TARGETS_MONSTER;
				_menemy = pnum;
				enemyx = plr[pnum]._px;
				enemyy = plr[pnum]._py;
				best_dist = dist;
				bestsameroom = sameroom;
			}
		}
	}
	for (j = 0; j < nummonsters; j++) {
		mi = monstactive[j + 1];
		if (mi == i)
			continue;
		if (monster[mi]._mx == 1 && monster[mi]._my == 0)
			continue;
		if (M_Talker(mi) && monster[mi].mtalkmsg)
			continue;
		if (!(Monst->_mFlags & MFLAG_GOLEM)
		    && ((abs(monster[mi]._mx - Monst->_mx) >= 2 || abs(monster[mi]._my - Monst->_my) >= 2) && !M_Ranged(i)
		           || (!(Monst->_mFlags & MFLAG_GOLEM) && !(monster[mi]._mFlags & MFLAG_GOLEM)))) {
			continue;
		}
		sameroom = dTransVal[Monst->_mx][Monst->_my] == dTransVal[monster[mi]._mx][monster[mi]._my];
		if (abs(Monst->_mx - monster[mi]._mx) > abs(Monst->_my - monster[mi]._my))
			dist = Monst->_mx - monster[mi]._mx;
		else
			dist = Monst->_my - monster[mi]._my;
		dist = abs(dist);
		if ((sameroom && !bestsameroom)
		    || ((sameroom || !bestsameroom) && dist < best_dist)
		    || (_menemy == -1)) {
			Monst->_mFlags |= MFLAG_TARGETS_MONSTER;
			_menemy = mi;
			enemyx = monster[mi]._mfutx;
			enemyy = monster[mi]._mfuty;
			best_dist = dist;
			bestsameroom = sameroom;
		}
	}
	if (_menemy != -1) {
		Monst->_mFlags &= ~MFLAG_NO_ENEMY;
		Monst->_menemy = _menemy;
		Monst->_menemyx = enemyx;
		Monst->_menemyy = enemyy;
	} else {
		Monst->_mFlags |= MFLAG_NO_ENEMY;
	}
}
// 679660: using guessed type char gbMaxPlayers;

int M_GetDir(int i)
{
	return GetDirection(monster[i]._mx, monster[i]._my, monster[i]._menemyx, monster[i]._menemyy);
}

void M_CheckEFlag(int i)
{
	int f, j;
	int x, y;
	WORD *m;

	x = monster[i]._mx - 1;
	y = monster[i]._my + 1;
	f = 0;
	m = dpiece_defs_map_2[x][y].mt;
	if (m >= dpiece_defs_map_2[0][0].mt) {
		for (j = 2; j < 10; j++) {
			f |= m[j];
		}
	} else {
		monster[i]._meflag = FALSE;
		return;
	}

	if (f | dArch[x][y])
		monster[i]._meflag = TRUE;
	else {
		monster[i]._meflag = FALSE;
	}
}

void M_StartStand(int i, int md)
{
	ClearMVars(i);
	if (monster[i].MType->mtype == MT_GOLEM)
		NewMonsterAnim(i, &monster[i].MType->Anims[MA_WALK], md);
	else
		NewMonsterAnim(i, &monster[i].MType->Anims[MA_STAND], md);
	monster[i]._mVar1 = monster[i]._mmode;
	monster[i]._mVar2 = 0;
	monster[i]._mmode = MM_STAND;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mdir = md;
	M_CheckEFlag(i);
	M_Enemy(i);
}

void M_StartDelay(int i, int len)
{
	if (len <= 0) {
		return;
	}

	if (monster[i]._mAi != AI_LAZURUS) {
		monster[i]._mVar2 = len;
		monster[i]._mmode = MM_DELAY;
	}
}

void M_StartSpStand(int i, int md)
{
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_SPECIAL], md);
	monster[i]._mmode = MM_SPSTAND;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mdir = md;
	M_CheckEFlag(i);
}

void M_StartWalk(int i, int xvel, int yvel, int xadd, int yadd, int EndDir)
{
	int fx = xadd + monster[i]._mx;
	int fy = yadd + monster[i]._my;

	dMonster[fx][fy] = -(i + 1);
	monster[i]._mmode = MM_WALK;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mfutx = fx;
	monster[i]._mfuty = fy;
	monster[i]._mxvel = xvel;
	monster[i]._myvel = yvel;
	monster[i]._mVar1 = xadd;
	monster[i]._mVar2 = yadd;
	monster[i]._mVar3 = EndDir;
	monster[i]._mdir = EndDir;
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_WALK], EndDir);
	monster[i]._mVar6 = 0;
	monster[i]._mVar7 = 0;
	monster[i]._mVar8 = 0;
	M_CheckEFlag(i);
}

void M_StartWalk2(int i, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int EndDir)
{
	int fx = xadd + monster[i]._mx;
	int fy = yadd + monster[i]._my;

	dMonster[monster[i]._mx][monster[i]._my] = -(i + 1);
	monster[i]._mVar1 = monster[i]._mx;
	monster[i]._mVar2 = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mx = fx;
	monster[i]._my = fy;
	monster[i]._mfutx = fx;
	monster[i]._mfuty = fy;
	dMonster[fx][fy] = i + 1;
	if (monster[i]._uniqtype != 0)
		ChangeLightXY(monster[i].mlid, monster[i]._mx, monster[i]._my);
	monster[i]._mxoff = xoff;
	monster[i]._myoff = yoff;
	monster[i]._mmode = MM_WALK2;
	monster[i]._mxvel = xvel;
	monster[i]._myvel = yvel;
	monster[i]._mVar3 = EndDir;
	monster[i]._mdir = EndDir;
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_WALK], EndDir);
	monster[i]._mVar6 = 16 * xoff;
	monster[i]._mVar7 = 16 * yoff;
	monster[i]._mVar8 = 0;
	M_CheckEFlag(i);
}

void M_StartWalk3(int i, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int mapx, int mapy, int EndDir)
{
	int fx = xadd + monster[i]._mx;
	int fy = yadd + monster[i]._my;
	int x = mapx + monster[i]._mx;
	int y = mapy + monster[i]._my;

	if (monster[i]._uniqtype != 0)
		ChangeLightXY(monster[i].mlid, x, y);

	dMonster[monster[i]._mx][monster[i]._my] = -(i + 1);
	dMonster[fx][fy] = -(i + 1);
	monster[i]._mVar4 = x;
	monster[i]._mVar5 = y;
	dFlags[x][y] |= DFLAG_MONSTER;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mfutx = fx;
	monster[i]._mfuty = fy;
	monster[i]._mxoff = xoff;
	monster[i]._myoff = yoff;
	monster[i]._mmode = MM_WALK3;
	monster[i]._mxvel = xvel;
	monster[i]._myvel = yvel;
	monster[i]._mVar1 = fx;
	monster[i]._mVar2 = fy;
	monster[i]._mVar3 = EndDir;
	monster[i]._mdir = EndDir;
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_WALK], EndDir);
	monster[i]._mVar6 = 16 * xoff;
	monster[i]._mVar7 = 16 * yoff;
	monster[i]._mVar8 = 0;
	M_CheckEFlag(i);
}

void M_StartAttack(int i)
{
	int md = M_GetDir(i);
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_ATTACK], md);
	monster[i]._mmode = MM_ATTACK;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mdir = md;
	M_CheckEFlag(i);
}

void M_StartRAttack(int i, int missile_type, int dam)
{
	int md = M_GetDir(i);
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_ATTACK], md);
	monster[i]._mmode = MM_RATTACK;
	monster[i]._mVar1 = missile_type;
	monster[i]._mVar2 = dam;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mdir = md;
	M_CheckEFlag(i);
}

void M_StartRSpAttack(int i, int missile_type, int dam)
{
	int md = M_GetDir(i);
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_SPECIAL], md);
	monster[i]._mmode = MM_RSPATTACK;
	monster[i]._mVar1 = missile_type;
	monster[i]._mVar2 = 0;
	monster[i]._mVar3 = dam;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mdir = md;
	M_CheckEFlag(i);
}

void M_StartSpAttack(int i)
{
	int md = M_GetDir(i);
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_SPECIAL], md);
	monster[i]._mmode = MM_SATTACK;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	monster[i]._mdir = md;
	M_CheckEFlag(i);
}

void M_StartEat(int i)
{
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_SPECIAL], monster[i]._mdir);
	monster[i]._mmode = MM_SATTACK;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	M_CheckEFlag(i);
}

void M_ClearSquares(int i)
{
	int x, y, mx, my, m1, m2;

	mx = monster[i]._moldx;
	my = monster[i]._moldy;
	m1 = -1 - i;
	m2 = i + 1;

	for (y = my - 1; y <= my + 1; y++) {
		if (y >= 0 && y < MAXDUNY) {
			for (x = mx - 1; x <= mx + 1; x++) {
				if (x >= 0 && x < MAXDUNX && (dMonster[x][y] == m1 || dMonster[x][y] == m2))
					dMonster[x][y] = 0;
			}
		}
	}

	if (mx + 1 < MAXDUNX)
		dFlags[mx + 1][my] &= ~DFLAG_MONSTER;
	if (my + 1 < MAXDUNY)
		dFlags[mx][my + 1] &= ~DFLAG_MONSTER;
}

void M_GetKnockback(int i)
{
	int d = (monster[i]._mdir - 4) & 7;
	if (DirOK(i, d)) {
		M_ClearSquares(i);
		monster[i]._moldx += offset_x[d];
		monster[i]._moldy += offset_y[d];
		NewMonsterAnim(i, &monster[i].MType->Anims[MA_GOTHIT], monster[i]._mdir);
		monster[i]._mmode = MM_GOTHIT;
		monster[i]._mxoff = 0;
		monster[i]._myoff = 0;
		monster[i]._mx = monster[i]._moldx;
		monster[i]._my = monster[i]._moldy;
		monster[i]._mfutx = monster[i]._moldx;
		monster[i]._mfuty = monster[i]._moldy;
		M_CheckEFlag(i);
		M_ClearSquares(i);
		dMonster[monster[i]._mx][monster[i]._my] = i + 1;
	}
}

void M_StartHit(int i, int pnum, int dam)
{
	if (pnum >= 0)
		monster[i].mWhoHit |= 1 << pnum;
	if (pnum == myplr) {
		delta_monster_hp(i, monster[i]._mhitpoints, currlevel);
		NetSendCmdParam2(FALSE, CMD_MONSTDAMAGE, i, dam);
	}
	PlayEffect(i, 1);
	if (monster[i].MType->mtype >= MT_SNEAK && monster[i].MType->mtype <= MT_ILLWEAV || dam >> 6 >= monster[i].mLevel + 3) {
		if (pnum >= 0) {
			monster[i]._mFlags &= ~MFLAG_TARGETS_MONSTER;
			monster[i]._menemy = pnum;
			monster[i]._menemyx = plr[pnum]._px;
			monster[i]._menemyy = plr[pnum]._py;
			monster[i]._mdir = M_GetDir(i);
		}
		if (monster[i].MType->mtype == MT_BLINK) {
			M_Teleport(i);
		} else if (monster[i].MType->mtype >= MT_NSCAV && monster[i].MType->mtype <= MT_YSCAV) {
			monster[i]._mgoal = MGOAL_NORMAL;
		}
		if (monster[i]._mmode != MM_STONE) {
			NewMonsterAnim(i, &monster[i].MType->Anims[MA_GOTHIT], monster[i]._mdir);
			monster[i]._mmode = MM_GOTHIT;
			monster[i]._mxoff = 0;
			monster[i]._myoff = 0;
			monster[i]._mx = monster[i]._moldx;
			monster[i]._my = monster[i]._moldy;
			monster[i]._mfutx = monster[i]._moldx;
			monster[i]._mfuty = monster[i]._moldy;
			M_CheckEFlag(i);
			M_ClearSquares(i);
			dMonster[monster[i]._mx][monster[i]._my] = i + 1;
		}
	}
}

void M_DiabloDeath(int i, BOOL sendmsg)
{
	MonsterStruct *Monst, *pmonster;
	int dist;
	int j, k;
	int _moldx, _moldy;

	Monst = monster + i;
	PlaySFX(USFX_DIABLOD);
	quests[QTYPE_MOD]._qactive = 3;
	if (sendmsg)
		NetSendCmdQuest(TRUE, QTYPE_MOD);
	gbProcessPlayers = FALSE;
	sgbSaveSoundOn = gbSoundOn;
	for (j = 0; j < nummonsters; j++) {
		k = monstactive[j];
		if (k == i || monster[i]._msquelch == 0)
			continue;

		pmonster = monster + k;
		NewMonsterAnim(k, pmonster->MType->Anims + MA_DEATH, pmonster->_mdir);
		monster[k]._mxoff = 0;
		monster[k]._myoff = 0;
		monster[k]._mVar1 = 0;
		_moldx = monster[k]._moldx;
		_moldy = monster[k]._moldy;
		monster[k]._my = _moldy;
		monster[k]._mfuty = _moldy;
		monster[k]._mmode = MM_DEATH;
		monster[k]._mx = _moldx;
		monster[k]._mfutx = _moldx;
		M_CheckEFlag(k);
		M_ClearSquares(k);
		dMonster[pmonster->_mx][pmonster->_my] = k + 1;
	}
	AddLight(Monst->_mx, Monst->_my, 8);
	DoVision(Monst->_mx, Monst->_my, 8, FALSE, TRUE);
	if (abs(ViewX - Monst->_mx) > abs(ViewY - Monst->_my))
		dist = abs (ViewX - Monst->_mx);
	else
		dist = abs (ViewY - Monst->_my);
	if (dist > 20)
		dist = 20;
	j = ViewX << 16;
	k = ViewY << 16;
	Monst->_mVar3 = j;
	Monst->_mVar4 = k;
	Monst->_mVar5 = (int) ((j - (Monst->_mx << 16)) / (double)dist);
	Monst->_mVar6 = (int) ((k - (Monst->_my << 16)) / (double)dist);
}
// 64D32C: using guessed type int sgbSaveSoundOn;

void M2MStartHit(int mid, int i, int dam)
{
	if ((DWORD)mid >= MAXMONSTERS) {
		app_fatal("Invalid monster %d getting hit by monster", mid);
	}

	if (monster[mid].MType == NULL) {
		app_fatal("Monster %d \"%s\" getting hit by monster: MType NULL", mid, monster[mid].mName);
	}

	if (i >= 0)
		monster[i].mWhoHit |= 1 << i;

	delta_monster_hp(mid, monster[mid]._mhitpoints, currlevel);
	NetSendCmdParam2(FALSE, CMD_MONSTDAMAGE, mid, dam);
	PlayEffect(mid, 1);

	if (monster[mid].MType->mtype >= MT_SNEAK && monster[mid].MType->mtype <= MT_ILLWEAV || dam >> 6 >= monster[mid].mLevel + 3) {
		if (i >= 0)
			monster[mid]._mdir = (monster[i]._mdir - 4) & 7;

		if (monster[mid].MType->mtype == MT_BLINK) {
			M_Teleport(mid);
		} else if (monster[mid].MType->mtype >= MT_NSCAV && monster[mid].MType->mtype <= MT_YSCAV) {
			monster[mid]._mgoal = MGOAL_NORMAL;
		}

		if (monster[mid]._mmode != MM_STONE) {
			if (monster[mid].MType->mtype != MT_GOLEM) {
				NewMonsterAnim(mid, &monster[mid].MType->Anims[MA_GOTHIT], monster[mid]._mdir);
				monster[mid]._mmode = MM_GOTHIT;
			}

			monster[mid]._mxoff = 0;
			monster[mid]._myoff = 0;
			monster[mid]._mx = monster[mid]._moldx;
			monster[mid]._my = monster[mid]._moldy;
			monster[mid]._mfutx = monster[mid]._moldx;
			monster[mid]._mfuty = monster[mid]._moldy;
			M_CheckEFlag(mid);
			M_ClearSquares(mid);
			dMonster[monster[mid]._mx][monster[mid]._my] = mid + 1;
		}
	}
}

void MonstStartKill(int i, int pnum, BOOL sendmsg)
{
	int md;

	if ((DWORD)i >= MAXMONSTERS) {
		app_fatal("MonstStartKill: Invalid monster %d", i);
	}
	if (!monster[i].MType) {
		app_fatal("MonstStartKill: Monster %d \"%s\" MType NULL", i, monster[i].mName);
	}

	if (pnum >= 0)
		monster[i].mWhoHit |= 1 << pnum;
	if (pnum < 4 && i > 4)
		AddPlrMonstExper(monster[i].mLevel, monster[i].mExp, monster[i].mWhoHit);
	monstkills[monster[i].MType->mtype]++;
	monster[i]._mhitpoints = 0;
	SetRndSeed(monster[i]._mRndSeed);
	if (QuestStatus(QTYPE_GARB) && monster[i].mName == UniqMonst[UMT_GARBUD].mName) {
		CreateTypeItem(monster[i]._mx + 1, monster[i]._my + 1, TRUE, 4, FALSE, TRUE, FALSE);
	} else if (i > 3) {
		SpawnItem(i, monster[i]._mx, monster[i]._my, sendmsg);
	}
	if (monster[i].MType->mtype == MT_DIABLO)
		M_DiabloDeath(i, TRUE);
	else
		PlayEffect(i, 2);

	if (pnum >= 0)
		md = M_GetDir(i);
	else
		md = monster[i]._mdir;
	monster[i]._mdir = md;
	NewMonsterAnim(i, &monster[i].MType->Anims[MA_DEATH], md);
	monster[i]._mmode = MM_DEATH;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mVar1 = 0;
	monster[i]._mx = monster[i]._moldx;
	monster[i]._my = monster[i]._moldy;
	monster[i]._mfutx = monster[i]._moldx;
	monster[i]._mfuty = monster[i]._moldy;
	M_CheckEFlag(i);
	M_ClearSquares(i);
	dMonster[monster[i]._mx][monster[i]._my] = i + 1;
	CheckQuestKill(i, sendmsg);
	M_FallenFear(monster[i]._mx, monster[i]._my);
	if (monster[i].MType->mtype >= MT_NACID && monster[i].MType->mtype <= MT_XACID)
		AddMissile(monster[i]._mx, monster[i]._my, 0, 0, 0, MIS_ACIDPUD, 1, i, monster[i]._mint + 1, 0);
}

void M2MStartKill(int i, int mid)
{
	int md;

	if ((DWORD)i >= MAXMONSTERS) {
		app_fatal("M2MStartKill: Invalid monster (attacker) %d", i);
		app_fatal("M2MStartKill: Invalid monster (killed) %d", mid);
	}
	if (!monster[i].MType)
		app_fatal("M2MStartKill: Monster %d \"%s\" MType NULL", mid, monster[mid].mName);

	delta_kill_monster(mid, monster[mid]._mx, monster[mid]._my, currlevel);
	NetSendCmdLocParam1(FALSE, CMD_MONSTDEATH, monster[mid]._mx, monster[mid]._my, mid);

	monster[mid].mWhoHit |= 1 << i;
	if (i < 4)
		AddPlrMonstExper(monster[mid].mLevel, monster[mid].mExp, monster[mid].mWhoHit);

	monstkills[monster[mid].MType->mtype]++;
	monster[mid]._mhitpoints = 0;
	SetRndSeed(monster[mid]._mRndSeed);

	if (mid >= 4)
		SpawnItem(mid, monster[mid]._mx, monster[mid]._my, TRUE);

	if (monster[mid].MType->mtype == MT_DIABLO)
		M_DiabloDeath(mid, TRUE);
	else
		PlayEffect(i, 2);

	PlayEffect(mid, 2);

	md = (monster[i]._mdir - 4) & 7;
	if (monster[mid].MType->mtype == MT_GOLEM)
		md = 0;

	monster[mid]._mdir = md;
	NewMonsterAnim(mid, &monster[mid].MType->Anims[MA_DEATH], md);
	monster[mid]._mmode = MM_DEATH;
	monster[mid]._mxoff = 0;
	monster[mid]._myoff = 0;
	monster[mid]._mx = monster[mid]._moldx;
	monster[mid]._my = monster[mid]._moldy;
	monster[mid]._mfutx = monster[mid]._moldx;
	monster[mid]._mfuty = monster[mid]._moldy;
	M_CheckEFlag(mid);
	M_ClearSquares(mid);
	dMonster[monster[mid]._mx][monster[mid]._my] = mid + 1;
	CheckQuestKill(mid, TRUE);
	M_FallenFear(monster[mid]._mx, monster[mid]._my);
	if (monster[mid].MType->mtype >= MT_NACID && monster[mid].MType->mtype <= MT_XACID)
		AddMissile(monster[mid]._mx, monster[mid]._my, 0, 0, 0, MIS_ACIDPUD, 1, mid, monster[mid]._mint + 1, 0);
}

void M_StartKill(int i, int pnum)
{
	if ((DWORD)i >= MAXMONSTERS) {
		app_fatal("M_StartKill: Invalid monster %d", i);
	}

	if (myplr == pnum) {
		delta_kill_monster(i, monster[i]._mx, monster[i]._my, currlevel);
		if (i != pnum) {
			NetSendCmdLocParam1(FALSE, CMD_MONSTDEATH, monster[i]._mx, monster[i]._my, i);
		} else {
			NetSendCmdLocParam1(FALSE, CMD_KILLGOLEM, monster[i]._mx, monster[i]._my, currlevel);
		}
	}

	MonstStartKill(i, pnum, TRUE);
}

void M_SyncStartKill(int i, int x, int y, int pnum)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_SyncStartKill: Invalid monster %d", i);

	if (monster[i]._mhitpoints == 0 || monster[i]._mmode == MM_DEATH) {
		return;
	}

	if (dMonster[x][y] == 0) {
		M_ClearSquares(i);
		monster[i]._mx = x;
		monster[i]._my = y;
		monster[i]._moldx = x;
		monster[i]._moldy = y;
	}

	if (monster[i]._mmode == MM_STONE) {
		MonstStartKill(i, pnum, FALSE);
		monster[i]._mmode = MM_STONE;
	} else {
		MonstStartKill(i, pnum, FALSE);
	}
}

void M_StartFadein(int i, int md, BOOL backwards)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_StartFadein: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_StartFadein: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	NewMonsterAnim(i, &monster[i].MType->Anims[MA_SPECIAL], md);
	monster[i]._mmode = MM_FADEIN;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	M_CheckEFlag(i);
	monster[i]._mdir = md;
	monster[i]._mFlags &= ~MFLAG_HIDDEN;
	if (backwards) {
		monster[i]._mFlags |= MFLAG_LOCK_ANIMATION;
		monster[i]._mAnimFrame = monster[i]._mAnimLen;
	}
}

void M_StartFadeout(int i, int md, BOOL backwards)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_StartFadeout: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_StartFadeout: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	NewMonsterAnim(i, &monster[i].MType->Anims[MA_SPECIAL], md);
	monster[i]._mmode = MM_FADEOUT;
	monster[i]._mxoff = 0;
	monster[i]._myoff = 0;
	monster[i]._mfutx = monster[i]._mx;
	monster[i]._mfuty = monster[i]._my;
	monster[i]._moldx = monster[i]._mx;
	monster[i]._moldy = monster[i]._my;
	M_CheckEFlag(i);
	monster[i]._mdir = md;
	if (backwards) {
		monster[i]._mFlags |= MFLAG_LOCK_ANIMATION;
		monster[i]._mAnimFrame = monster[i]._mAnimLen;
	}
}

void M_StartHeal(int i)
{
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_StartHeal: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_StartHeal: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	Monst = &monster[i];
	Monst->_mAnimData = Monst->MType->Anims[MA_SPECIAL].Data[Monst->_mdir];
	Monst->_mAnimFrame = Monst->MType->Anims[MA_SPECIAL].Frames;
	Monst->_mFlags |= MFLAG_LOCK_ANIMATION;
	Monst->_mmode = MM_HEAL;
	Monst->_mVar1 = Monst->_mmaxhp / (16 * (random(97, 5) + 4));
}

void M_ChangeLightOffset(int monst)
{
	int lx, ly, _mxoff, _myoff, sign;

	if ((DWORD)monst >= MAXMONSTERS)
		app_fatal("M_ChangeLightOffset: Invalid monster %d", monst);

	lx = monster[monst]._mxoff + 2 * monster[monst]._myoff;
	ly = 2 * monster[monst]._myoff - monster[monst]._mxoff;

	if (lx < 0) {
		sign = -1;
		lx = -lx;
	} else {
		sign = 1;
	}

	_mxoff = sign * (lx >> 3);
	if (ly < 0) {
		_myoff = -1;
		ly = -ly;
	} else {
		_myoff = 1;
	}

	ChangeLightOff(monster[monst].mlid, _mxoff, _myoff * (ly >> 3));
}

int M_DoStand(int i)
{
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoStand: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoStand: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	Monst = &monster[i];
	if (Monst->MType->mtype == MT_GOLEM)
		Monst->_mAnimData = Monst->MType->Anims[MA_WALK].Data[Monst->_mdir];
	else
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[Monst->_mdir];

	if (Monst->_mAnimFrame == Monst->_mAnimLen)
		M_Enemy(i);

	Monst->_mVar2++;

	return FALSE;
}

BOOL M_DoWalk(int i)
{
	BOOL rv;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoWalk: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoWalk: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	rv = FALSE;
	if (monster[i]._mVar8 == monster[i].MType->Anims[MA_WALK].Frames) {
		dMonster[monster[i]._mx][monster[i]._my] = 0;
		monster[i]._mx += monster[i]._mVar1;
		monster[i]._my += monster[i]._mVar2;
		dMonster[monster[i]._mx][monster[i]._my] = i + 1;
		if (monster[i]._uniqtype != 0)
			ChangeLightXY(monster[i].mlid, monster[i]._mx, monster[i]._my);
		M_StartStand(i, monster[i]._mdir);
		rv = TRUE;
	} else if (!monster[i]._mAnimCnt) {
		monster[i]._mVar8++;
		monster[i]._mVar6 += monster[i]._mxvel;
		monster[i]._mVar7 += monster[i]._myvel;
		monster[i]._mxoff = monster[i]._mVar6 >> 4;
		monster[i]._myoff = monster[i]._mVar7 >> 4;
	}

	if (monster[i]._uniqtype != 0)
		M_ChangeLightOffset(i);

	return rv;
}

BOOL M_DoWalk2(int i)
{
	BOOL rv;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoWalk2: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoWalk2: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	if (monster[i]._mVar8 == monster[i].MType->Anims[MA_WALK].Frames) {
		dMonster[monster[i]._mVar1][monster[i]._mVar2] = 0;
		if (monster[i]._uniqtype != 0)
			ChangeLightXY(monster[i].mlid, monster[i]._mx, monster[i]._my);
		M_StartStand(i, monster[i]._mdir);
		rv = TRUE;
	} else {
		if (!monster[i]._mAnimCnt) {
			monster[i]._mVar8++;
			monster[i]._mVar6 += monster[i]._mxvel;
			monster[i]._mVar7 += monster[i]._myvel;
			monster[i]._mxoff = monster[i]._mVar6 >> 4;
			monster[i]._myoff = monster[i]._mVar7 >> 4;
		}
		rv = FALSE;
	}
	if (monster[i]._uniqtype != 0)
		M_ChangeLightOffset(i);

	return rv;
}

BOOL M_DoWalk3(int i)
{
	BOOL rv;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoWalk3: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoWalk3: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	if (monster[i]._mVar8 == monster[i].MType->Anims[MA_WALK].Frames) {
		dMonster[monster[i]._mx][monster[i]._my] = 0;
		monster[i]._mx = monster[i]._mVar1;
		monster[i]._my = monster[i]._mVar2;
		dFlags[monster[i]._mVar4][monster[i]._mVar5] &= ~DFLAG_MONSTER;
		dMonster[monster[i]._mx][monster[i]._my] = i + 1;
		if (monster[i]._uniqtype)
			ChangeLightXY(monster[i].mlid, monster[i]._mx, monster[i]._my);
		M_StartStand(i, monster[i]._mdir);
		rv = TRUE;
	} else {
		if (!monster[i]._mAnimCnt) {
			monster[i]._mVar8++;
			monster[i]._mVar6 += monster[i]._mxvel;
			monster[i]._mVar7 += monster[i]._myvel;
			monster[i]._mxoff = monster[i]._mVar6 >> 4;
			monster[i]._myoff = monster[i]._mVar7 >> 4;
		}
		rv = FALSE;
	}
	if (monster[i]._uniqtype != 0)
		M_ChangeLightOffset(i);

	return rv;
}

void M_TryM2MHit(int i, int mid, int hper, int mind, int maxd)
{
	BOOL ret;

	if ((DWORD)mid >= MAXMONSTERS) {
		app_fatal("M_TryM2MHit: Invalid monster %d", mid);
	}
	if (monster[mid].MType == NULL)
		app_fatal("M_TryM2MHit: Monster %d \"%s\" MType NULL", mid, monster[mid].mName);
	if (monster[mid]._mhitpoints >> 6 > 0 && (monster[mid].MType->mtype != MT_ILLWEAV || monster[mid]._mgoal != MGOAL_RETREAT)) {
		int hit = random(4, 100);
		if (monster[mid]._mmode == MM_STONE)
			hit = 0;
		if (!CheckMonsterHit(mid, &ret) && hit < hper) {
			int dam = (mind + random(5, maxd - mind + 1)) << 6;
			monster[mid]._mhitpoints -= dam;
			if (monster[mid]._mhitpoints >> 6 <= 0) {
				if (monster[mid]._mmode == MM_STONE) {
					M2MStartKill(i, mid);
					monster[mid]._mmode = MM_STONE;
				} else {
					M2MStartKill(i, mid);
				}
			} else {
				if (monster[mid]._mmode == MM_STONE) {
					M2MStartHit(mid, i, dam);
					monster[mid]._mmode = MM_STONE;
				} else {
					M2MStartHit(mid, i, dam);
				}
			}
		}
	}
}

void M_TryH2HHit(int i, int pnum, int Hit, int MinDam, int MaxDam)
{
	int hit, hper;
	int dam;
	int dx, dy;
	int blk, blkper;
	int mdam;
	int newx, newy;
	int j;
	int misnum, ms_num, cur_ms_num;
	int new_hp;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_TryH2HHit: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_TryH2HHit: Monster %d \"%s\" MType NULL", i, monster[i].mName);
	if (monster[i]._mFlags & MFLAG_TARGETS_MONSTER) {
		M_TryM2MHit(i, pnum, Hit, MinDam, MaxDam);
		return;
	}
	if (plr[pnum]._pHitPoints >> 6 <= 0 || plr[pnum]._pInvincible || plr[pnum]._pSpellFlags & 1)
		return;
	dx = abs(monster[i]._mx - plr[pnum].WorldX);
	dy = abs(monster[i]._my - plr[pnum].WorldY);
	if (dx >= 2 || dy >= 2)
		return;

	hper = random(98, 100);
#ifdef _DEBUG
	if (debug_mode_dollar_sign || debug_mode_key_inverted_v)
		hper = 1000;
#endif
	hit = Hit
	    + 2 * (monster[i].mLevel - plr[pnum]._pLevel)
	    + 30
	    - plr[pnum]._pIBonusAC
	    - plr[pnum]._pIAC
	    - plr[pnum]._pDexterity / 5;
	if (hit < 15)
		hit = 15;
	if (currlevel == 14 && hit < 20)
		hit = 20;
	if (currlevel == 15 && hit < 25)
		hit = 25;
	if (currlevel == 16 && hit < 30)
		hit = 30;
	if ((plr[pnum]._pmode == PM_STAND || plr[pnum]._pmode == PM_ATTACK) && plr[pnum]._pBlockFlag) {
		blkper = random(98, 100);
	} else {
		blkper = 100;
	}
	blk = plr[pnum]._pDexterity
	    + plr[pnum]._pBaseToBlk
	    - (monster[i].mLevel << 1)
	    + (plr[pnum]._pLevel << 1);
	if (blk < 0)
		blk = 0;
	if (blk > 100)
		blk = 100;
	if (hper >= hit)
		return;
	if (blkper < blk) {
		StartPlrBlock(pnum, GetDirection(plr[pnum].WorldX, plr[pnum].WorldY, monster[i]._mx, monster[i]._my));
		return;
	}
	if (monster[i].MType->mtype == MT_YZOMBIE && pnum == myplr) {
		ms_num = -1;
		cur_ms_num = -1;
		for (j = 0; j < nummissiles; j++) {
			misnum = missileactive[j];
			if (missile[misnum]._mitype != MIS_MANASHIELD)
				continue;
			if (missile[misnum]._misource == pnum)
				cur_ms_num = misnum;
			else
				ms_num = misnum;
		}
		if (plr[pnum]._pMaxHP > 64) {
			if (plr[pnum]._pMaxHPBase > 64) {
				new_hp = plr[pnum]._pMaxHP - 64;
				plr[pnum]._pMaxHP = new_hp;
				if (plr[pnum]._pHitPoints > new_hp) {
					plr[pnum]._pHitPoints = new_hp;
					if (cur_ms_num >= 0)
						missile[cur_ms_num]._miVar1 = new_hp;
				}
				new_hp = plr[pnum]._pMaxHPBase - 64;
				plr[pnum]._pMaxHPBase = new_hp;
				if (plr[pnum]._pHPBase > new_hp) {
					plr[pnum]._pHPBase = new_hp;
					if (cur_ms_num >= 0)
						missile[cur_ms_num]._miVar2 = new_hp;
				}
			}
		}
	}
	dam = (MinDam << 6) + random(99, (MaxDam - MinDam + 1) << 6);
	dam += (plr[pnum]._pIGetHit << 6);
	if (dam < 64)
		dam = 64;
	if (pnum == myplr) {
		plr[pnum]._pHitPoints -= dam;
		plr[pnum]._pHPBase -= dam;
	}
	if (plr[pnum]._pIFlags & ISPL_THORNS) {
		mdam = (random(99, 3) + 1) << 6;
		monster[i]._mhitpoints -= mdam;
		if (monster[i]._mhitpoints >> 6 <= 0)
			M_StartKill(i, pnum);
		else
			M_StartHit(i, pnum, mdam);
	}
	if (!(monster[i]._mFlags & MFLAG_NOLIFESTEAL) && monster[i].MType->mtype == MT_SKING && gbMaxPlayers != 1)
		monster[i]._mhitpoints += dam;
	if (plr[pnum]._pHitPoints > plr[pnum]._pMaxHP) {
		plr[pnum]._pHitPoints = plr[pnum]._pMaxHP;
		plr[pnum]._pHPBase = plr[pnum]._pMaxHPBase;
	}
	if (plr[pnum]._pHitPoints >> 6 <= 0) {
		SyncPlrKill(pnum, 0);
		return;
	}
	StartPlrHit(pnum, dam, 0);
	if (monster[i]._mFlags & MFLAG_KNOCKBACK) {
		if (plr[pnum]._pmode != PM_GOTHIT)
			StartPlrHit(pnum, 0, 1u);
		newx = plr[pnum].WorldX + offset_x[monster[i]._mdir];
		newy = plr[pnum].WorldY + offset_y[monster[i]._mdir];
		if (PosOkPlayer(pnum, newx, newy)) {
			plr[pnum].WorldX = newx;
			plr[pnum].WorldY = newy;
			FixPlayerLocation(pnum, plr[pnum]._pdir);
			FixPlrWalkTags(pnum);
			dPlayer[newx][newy] = pnum + 1;
			SetPlayerOld(pnum);
		}
	}
}
// 679660: using guessed type char gbMaxPlayers;

BOOL M_DoAttack(int i)
{
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoAttack: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->MType == NULL)
		app_fatal("M_DoAttack: Monster %d \"%s\" MType NULL", i, Monst->mName);
	if (Monst->MType == NULL) // BUGFIX: should check MData
		app_fatal("M_DoAttack: Monster %d \"%s\" MData NULL", i, Monst->mName);

	if (monster[i]._mAnimFrame == monster[i].MData->mAFNum) {
		M_TryH2HHit(i, monster[i]._menemy, monster[i].mHit, monster[i].mMinDamage, monster[i].mMaxDamage);
		if (monster[i]._mAi != AI_SNAKE)
			PlayEffect(i, 0);
	}
	if (monster[i].MType->mtype >= MT_NMAGMA && monster[i].MType->mtype <= MT_WMAGMA && monster[i]._mAnimFrame == 9) {
		M_TryH2HHit(i, monster[i]._menemy, monster[i].mHit + 10, monster[i].mMinDamage - 2, monster[i].mMaxDamage - 2);
		PlayEffect(i, 0);
	}
	if (monster[i].MType->mtype >= MT_STORM && monster[i].MType->mtype <= MT_MAEL && monster[i]._mAnimFrame == 13) {
		M_TryH2HHit(i, monster[i]._menemy, monster[i].mHit - 20, monster[i].mMinDamage + 4, monster[i].mMaxDamage + 4);
		PlayEffect(i, 0);
	}
	if (monster[i]._mAi == AI_SNAKE && monster[i]._mAnimFrame == 1)
		PlayEffect(i, 0);
	if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		M_StartStand(i, monster[i]._mdir);
		return TRUE;
	}

	return FALSE;
}

BOOL M_DoRAttack(int i)
{
	int multimissiles, mi;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoRAttack: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoRAttack: Monster %d \"%s\" MType NULL", i, monster[i].mName);
	if (monster[i].MType == NULL) // BUGFIX: should check MData
		app_fatal("M_DoRAttack: Monster %d \"%s\" MData NULL", i, monster[i].mName);

	if (monster[i]._mAnimFrame == monster[i].MData->mAFNum) {
		if (monster[i]._mVar1 != -1) {
			if (monster[i]._mVar1 != MIS_CBOLT)
				multimissiles = 1;
			else
				multimissiles = 3;
			for (mi = 0; mi < multimissiles; mi++) {
				AddMissile(
				    monster[i]._mx,
				    monster[i]._my,
				    monster[i]._menemyx,
				    monster[i]._menemyy,
				    monster[i]._mdir,
				    monster[i]._mVar1,
				    1,
				    i,
				    monster[i]._mVar2,
				    0);
			}
		}
		PlayEffect(i, 0);
	}

	if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		M_StartStand(i, monster[i]._mdir);
		return TRUE;
	}

	return FALSE;
}

int M_DoRSpAttack(int i)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoRSpAttack: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoRSpAttack: Monster %d \"%s\" MType NULL", i, monster[i].mName);
	if (monster[i].MType == NULL) // BUGFIX: should check MData
		app_fatal("M_DoRSpAttack: Monster %d \"%s\" MData NULL", i, monster[i].mName);

	if (monster[i]._mAnimFrame == monster[i].MData->mAFNum2 && !monster[i]._mAnimCnt) {
		AddMissile(
		    monster[i]._mx,
		    monster[i]._my,
		    monster[i]._menemyx,
		    monster[i]._menemyy,
		    monster[i]._mdir,
		    monster[i]._mVar1,
		    1,
		    i,
		    monster[i]._mVar3,
		    0);
		PlayEffect(i, 3);
	}

	if (monster[i]._mAi == AI_MEGA && monster[i]._mAnimFrame == 3) {
		int hadV2 = monster[i]._mVar2;
		monster[i]._mVar2++;
		if (hadV2 == 0) {
			monster[i]._mFlags |= MFLAG_ALLOW_SPECIAL;
		} else if (monster[i]._mVar2 == 15) {
			monster[i]._mFlags &= ~MFLAG_ALLOW_SPECIAL;
		}
	}

	if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		M_StartStand(i, monster[i]._mdir);
		return TRUE;
	}

	return FALSE;
}

BOOL M_DoSAttack(int i)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoSAttack: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoSAttack: Monster %d \"%s\" MType NULL", i, monster[i].mName);
	if (monster[i].MType == NULL) // BUGFIX: should check MData
		app_fatal("M_DoSAttack: Monster %d \"%s\" MData NULL", i, monster[i].mName);

	if (monster[i]._mAnimFrame == monster[i].MData->mAFNum2)
		M_TryH2HHit(i, monster[i]._menemy, monster[i].mHit2, monster[i].mMinDamage2, monster[i].mMaxDamage2);

	if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		M_StartStand(i, monster[i]._mdir);
		return TRUE;
	}

	return FALSE;
}

BOOL M_DoFadein(int i)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoFadein: Invalid monster %d", i);

	if ((!(monster[i]._mFlags & MFLAG_LOCK_ANIMATION) || monster[i]._mAnimFrame != 1)
	    && (monster[i]._mFlags & MFLAG_LOCK_ANIMATION || monster[i]._mAnimFrame != monster[i]._mAnimLen)) {
		return FALSE;
	}

	M_StartStand(i, monster[i]._mdir);
	monster[i]._mFlags &= ~MFLAG_LOCK_ANIMATION;

	return TRUE;
}

BOOL M_DoFadeout(int i)
{
	int mt;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoFadeout: Invalid monster %d", i);

	if ((!(monster[i]._mFlags & MFLAG_LOCK_ANIMATION) || monster[i]._mAnimFrame != 1)
	    && (monster[i]._mFlags & MFLAG_LOCK_ANIMATION || monster[i]._mAnimFrame != monster[i]._mAnimLen)) {
		return FALSE;
	}

	mt = monster[i].MType->mtype;
	if (mt < MT_INCIN || mt > MT_HELLBURN) {
		monster[i]._mFlags &= ~MFLAG_LOCK_ANIMATION;
		monster[i]._mFlags |= MFLAG_HIDDEN;
	} else {
		monster[i]._mFlags &= ~MFLAG_LOCK_ANIMATION;
	}

	M_StartStand(i, monster[i]._mdir);

	return TRUE;
}

int M_DoHeal(int i)
{
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoHeal: Invalid monster %d", i);
	Monst = monster + i;
	if (monster[i]._mFlags & MFLAG_NOHEAL) {
		Monst->_mFlags &= ~MFLAG_ALLOW_SPECIAL;
		Monst->_mmode = MM_SATTACK;
		return FALSE;
	}

	if (Monst->_mAnimFrame == 1) {
		Monst->_mFlags &= ~MFLAG_LOCK_ANIMATION;
		Monst->_mFlags |= MFLAG_ALLOW_SPECIAL;
		if (Monst->_mVar1 + Monst->_mhitpoints < Monst->_mmaxhp) {
			Monst->_mhitpoints = Monst->_mVar1 + Monst->_mhitpoints;
		} else {
			Monst->_mhitpoints = Monst->_mmaxhp;
			Monst->_mFlags &= ~MFLAG_ALLOW_SPECIAL;
			Monst->_mmode = MM_SATTACK;
		}
	}
	return FALSE;
}

int M_DoTalk(int i)
{
	MonsterStruct *Monst;
	int tren;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoTalk: Invalid monster %d", i);

	Monst = monster + i;
	M_StartStand(i, Monst->_mdir);
	monster[i]._mgoal = MGOAL_TALKING;
	if (effect_is_playing(alltext[Monst->mtalkmsg].sfxnr))
		return FALSE;
	InitQTextMsg(Monst->mtalkmsg);
	if (Monst->mName == UniqMonst[UMT_GARBUD].mName) {
		if (Monst->mtalkmsg == QUEST_GARBUD1)
			quests[QTYPE_GARB]._qactive = 2;
		quests[QTYPE_GARB]._qlog = TRUE;
		if (Monst->mtalkmsg == QUEST_GARBUD2 && !(Monst->_mFlags & MFLAG_QUEST_COMPLETE)) {
			SpawnItem(i, Monst->_mx + 1, Monst->_my + 1, TRUE);
			Monst->_mFlags |= MFLAG_QUEST_COMPLETE;
		}
	}
	if (Monst->mName == UniqMonst[UMT_ZHAR].mName
	    && Monst->mtalkmsg == QUEST_ZHAR1
	    && !(Monst->_mFlags & MFLAG_QUEST_COMPLETE)) {
		quests[QTYPE_ZHAR]._qactive = 2;
		quests[QTYPE_ZHAR]._qlog = TRUE;
		CreateTypeItem(Monst->_mx + 1, Monst->_my + 1, FALSE, 0, 24, TRUE, 0);
		Monst->_mFlags |= MFLAG_QUEST_COMPLETE;
	}
	if (Monst->mName == UniqMonst[UMT_SNOTSPIL].mName) {
		if (Monst->mtalkmsg == QUEST_BANNER10 && !(Monst->_mFlags & MFLAG_QUEST_COMPLETE)) {
			ObjChangeMap(setpc_x, setpc_y, (setpc_w >> 1) + setpc_x + 2, (setpc_h >> 1) + setpc_y - 2);
			tren = TransVal;
			TransVal = 9;
			DRLG_MRectTrans(setpc_x, setpc_y, (setpc_w >> 1) + setpc_x + 4, setpc_y + (setpc_h >> 1));
			TransVal = tren;
			quests[QTYPE_BOL]._qvar1 = 2;
			if (quests[QTYPE_BOL]._qactive == 1)
				quests[QTYPE_BOL]._qactive = 2;
			Monst->_mFlags |= MFLAG_QUEST_COMPLETE;
		}
		if (quests[QTYPE_BOL]._qvar1 < 2) {
			sprintf(tempstr, "SS Talk = %i, Flags = %i", Monst->mtalkmsg, Monst->_mFlags);
			app_fatal(tempstr);
		}
	}
	if (Monst->mName == UniqMonst[UMT_LACHDAN].mName) {
		if (Monst->mtalkmsg == QUEST_VEIL9) {
			quests[QTYPE_VEIL]._qactive = 2;
			quests[QTYPE_VEIL]._qlog = TRUE;
		}
		if (Monst->mtalkmsg == QUEST_VEIL11 && !(Monst->_mFlags & MFLAG_QUEST_COMPLETE)) {
			SpawnUnique(UITEM_STEELVEIL, Monst->_mx + 1, Monst->_my + 1);
			Monst->_mFlags |= MFLAG_QUEST_COMPLETE;
		}
	}
	if (Monst->mName == UniqMonst[UMT_WARLORD].mName)
		quests[QTYPE_WARLRD]._qvar1 = 2;
	if (Monst->mName == UniqMonst[UMT_LAZURUS].mName && gbMaxPlayers != 1) {
		Monst->_msquelch = -1;
		Monst->mtalkmsg = 0;
		quests[QTYPE_VB]._qvar1 = 6;
		Monst->_mgoal = MGOAL_NORMAL;
	}
	return FALSE;
}
// 4351F5: could not find valid save-restore pair for ebp
// 5A5590: using guessed type char TransVal;
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;
// 679660: using guessed type char gbMaxPlayers;

void M_Teleport(int i)
{
	BOOL tren;
	MonsterStruct *Monst;
	int k, j, x, y, _mx, _my, rx, ry;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_Teleport: Invalid monster %d", i);

	tren = FALSE;

	Monst = &monster[i];
	if (Monst->_mmode != MM_STONE) {
		_mx = Monst->_menemyx;
		_my = Monst->_menemyy;
		rx = 2 * random(100, 2) - 1;
		ry = 2 * random(100, 2) - 1;

		for (j = -1; j <= 1 && !tren; j++) {
			for (k = -1; k < 1 && !tren; k++) {
				if (j != 0 || k != 0) {
					x = _mx + rx * j;
					y = _my + ry * k;
					if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX && x != Monst->_mx && y != Monst->_my) {
						if (PosOkMonst(i, x, y))
							tren = TRUE;
					}
				}
			}
		}
	}

	if (tren) {
		M_ClearSquares(i);
		dMonster[Monst->_mx][Monst->_my] = 0;
		dMonster[x][y] = i + 1;
		Monst->_moldx = x;
		Monst->_moldy = y;
		Monst->_mdir = M_GetDir(i);
		M_CheckEFlag(i);
	}
}

BOOL M_DoGotHit(int i)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoGotHit: Invalid monster %d", i);

	if (monster[i].MType == NULL)
		app_fatal("M_DoGotHit: Monster %d \"%s\" MType NULL", i, monster[i].mName);
	if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		M_StartStand(i, monster[i]._mdir);

		return TRUE;
	}

	return FALSE;
}

void M_UpdateLeader(int i)
{
	int ma, j;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_UpdateLeader: Invalid monster %d", i);

	for (j = 0; j < nummonsters; j++) {
		ma = monstactive[j];
		if (monster[ma].leaderflag == 1 && monster[ma].leader == i)
			monster[ma].leaderflag = 0;
	}

	if (monster[i].leaderflag == 1) {
		monster[monster[i].leader].packsize--;
	}
}

void DoEnding()
{
	BOOL bMusicOn;
	int musicVolume;

	if (gbMaxPlayers > 1) {
		SNetLeaveGame(0x40000004);
	}

	music_stop();

	if (gbMaxPlayers > 1) {
		Sleep(1000);
	}

	if (plr[myplr]._pClass == PC_WARRIOR) {
		play_movie("gendata\\DiabVic2.smk", 0);
	} else if (plr[myplr]._pClass == PC_SORCERER) {
		play_movie("gendata\\DiabVic1.smk", 0);
	} else {
		play_movie("gendata\\DiabVic3.smk", 0);
	}
	play_movie("gendata\\Diabend.smk", 0);

	bMusicOn = gbMusicOn;
	gbMusicOn = TRUE;

	musicVolume = sound_get_or_set_music_volume(1);
	sound_get_or_set_music_volume(0);

	music_start(2);
	loop_movie = TRUE;
	play_movie("gendata\\loopdend.smk", 1);
	loop_movie = FALSE;
	music_stop();

	sound_get_or_set_music_volume(musicVolume);
	gbMusicOn = bMusicOn;
}
// 679660: using guessed type char gbMaxPlayers;

void PrepDoEnding()
{
	int newKillLevel, i;
	DWORD *killLevel;

	gbSoundOn = sgbSaveSoundOn;
	gbRunGame = FALSE;
	deathflag = FALSE;
	cineflag = TRUE;

	killLevel = &plr[myplr].pDiabloKillLevel;
	newKillLevel = gnDifficulty + 1;
	if (*killLevel > newKillLevel)
		newKillLevel = *killLevel;
	plr[myplr].pDiabloKillLevel = newKillLevel;

	for (i = 0; i < MAX_PLRS; i++) {
		plr[i]._pmode = PM_QUIT;
		plr[i]._pInvincible = TRUE;
		if (gbMaxPlayers > 1) {
			if (plr[i]._pHitPoints >> 6 == 0)
				plr[i]._pHitPoints = 64;
			if (plr[i]._pMana >> 6 == 0)
				plr[i]._pMana = 64;
		}
	}
}
// 525718: using guessed type char cineflag;
// 64D32C: using guessed type int sgbSaveSoundOn;
// 679660: using guessed type char gbMaxPlayers;

BOOL M_DoDeath(int i)
{
	int var1;
	int x, y;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoDeath: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoDeath: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	monster[i]._mVar1++;
	var1 = monster[i]._mVar1;
	if (monster[i].MType->mtype == MT_DIABLO) {
		x = monster[i]._mx - ViewX;
		if (x < 0)
			x = -1;
		else
			x = x > 0;
		ViewX += x;

		y = monster[i]._my - ViewY;
		if (y < 0) {
			y = -1;
		} else {
			y = y > 0;
		}
		ViewY += y;

		if (var1 == 140)
			PrepDoEnding();
	} else if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		if (monster[i]._uniqtype == 0)
			AddDead(monster[i]._mx, monster[i]._my, monster[i].MType->mdeadval, (direction)monster[i]._mdir);
		else
			AddDead(monster[i]._mx, monster[i]._my, monster[i]._udeadval, (direction)monster[i]._mdir);

		monster[i]._mDelFlag = TRUE;
		dMonster[monster[i]._mx][monster[i]._my] = 0;

		M_UpdateLeader(i);
	}
	return FALSE;
}

BOOL M_DoSpStand(int i)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoSpStand: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoSpStand: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	if (monster[i]._mAnimFrame == monster[i].MData->mAFNum2)
		PlayEffect(i, 3);

	if (monster[i]._mAnimFrame == monster[i]._mAnimLen) {
		M_StartStand(i, monster[i]._mdir);
		return TRUE;
	}

	return FALSE;
}

BOOL M_DoDelay(int i)
{
	int mVar2;
	int oFrame;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoDelay: Invalid monster %d", i);
	if (monster[i].MType == NULL)
		app_fatal("M_DoDelay: Monster %d \"%s\" MType NULL", i, monster[i].mName);

	monster[i]._mAnimData = monster[i].MType->Anims[MA_STAND].Data[M_GetDir(i)];
	if (monster[i]._mAi == AI_LAZURUS) {
		if (monster[i]._mVar2 > 8 || monster[i]._mVar2 < 0)
			monster[i]._mVar2 = 8;
	}

	mVar2 = monster[i]._mVar2;
	monster[i]._mVar2--;

	if (!mVar2) {
		oFrame = monster[i]._mAnimFrame;
		M_StartStand(i, monster[i]._mdir);
		monster[i]._mAnimFrame = oFrame;
		return TRUE;
	}

	return FALSE;
}

BOOL M_DoStone(int i)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_DoStone: Invalid monster %d", i);

	if (!monster[i]._mhitpoints) {
		dMonster[monster[i]._mx][monster[i]._my] = 0;
		monster[i]._mDelFlag = TRUE;
	}

	return FALSE;
}

void M_WalkDir(int i, int md)
{
	int mwi;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_WalkDir: Invalid monster %d", i);

	mwi = monster[i].MType->Anims[MA_WALK].Frames - 1;
	switch (md) {
	case DIR_N:
		M_StartWalk(i, 0, -MWVel[mwi][1], -1, -1, DIR_N);
		break;
	case DIR_NE:
		M_StartWalk(i, MWVel[mwi][1], -MWVel[mwi][0], 0, -1, DIR_NE);
		break;
	case DIR_E:
		M_StartWalk3(i, MWVel[mwi][2], 0, -32, -16, 1, -1, 1, 0, DIR_E);
		break;
	case DIR_SE:
		M_StartWalk2(i, MWVel[mwi][1], MWVel[mwi][0], -32, -16, 1, 0, DIR_SE);
		break;
	case DIR_S:
		M_StartWalk2(i, 0, MWVel[mwi][1], 0, -32, 1, 1, DIR_S);
		break;
	case DIR_SW:
		M_StartWalk2(i, -MWVel[mwi][1], MWVel[mwi][0], 32, -16, 0, 1, DIR_SW);
		break;
	case DIR_W:
		M_StartWalk3(i, -MWVel[mwi][2], 0, 32, -16, -1, 1, 0, 1, DIR_W);
		break;
	case DIR_NW:
		M_StartWalk(i, -MWVel[mwi][1], -MWVel[mwi][0], -1, 0, DIR_NW);
		break;
	}
}

void GroupUnity(int i)
{
	int leader, m, j;
	BOOL clear;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("GroupUnity: Invalid monster %d", i);

	if (monster[i].leaderflag) {
		leader = monster[i].leader;
		clear = LineClearF(CheckNoSolid, monster[i]._mx, monster[i]._my, monster[leader]._mfutx, monster[leader]._mfuty);
		if (clear || monster[i].leaderflag != 1) {
			if (clear
			    && monster[i].leaderflag == 2
			    && abs(monster[i]._mx - monster[leader]._mfutx) < 4
			    && abs(monster[i]._my - monster[leader]._mfuty) < 4) {
				monster[leader].packsize++;
				monster[i].leaderflag = 1;
			}
		} else {
			monster[leader].packsize--;
			monster[i].leaderflag = 2;
		}
	}

	if (monster[i].leaderflag == 1) {
		if ((BYTE)monster[i]._msquelch > (BYTE)monster[leader]._msquelch) {
			monster[leader]._lastx = monster[i]._mx;
			monster[leader]._lasty = monster[i]._my;
			monster[leader]._msquelch = monster[i]._msquelch - 1;
		}
		if (monster[leader]._mAi == AI_GARG) {
			if (monster[leader]._mFlags & MFLAG_ALLOW_SPECIAL) {
				monster[leader]._mmode = MM_SATTACK;
				monster[leader]._mFlags &= ~MFLAG_ALLOW_SPECIAL;
			}
		}
		return;
	}
	if (monster[i]._uniqtype != 0) {
		if (UniqMonst[monster[i]._uniqtype - 1].mUnqAttr & 2) {
			for (j = 0; j < nummonsters; j++) {
				m = monstactive[j];
				if (monster[m].leaderflag == 1 && monster[m].leader == i) {
					if ((BYTE)monster[i]._msquelch > (BYTE)monster[m]._msquelch) {
						monster[m]._lastx = monster[i]._mx;
						monster[m]._lasty = monster[i]._my;
						monster[m]._msquelch = monster[i]._msquelch - 1;
					}
					if (monster[m]._mAi == AI_GARG) {
						if (monster[m]._mFlags & MFLAG_ALLOW_SPECIAL) {
							monster[m]._mmode = MM_SATTACK;
							monster[m]._mFlags &= ~MFLAG_ALLOW_SPECIAL;
						}
					}
				}
			}
		}
	}
}

BOOL M_CallWalk(int i, int md)
{
	int mdtemp;
	BOOL ok;

	mdtemp = md;
	ok = DirOK(i, md);
	if (random(101, 2))
		ok = ok || (md = left[mdtemp], DirOK(i, md)) || (md = right[mdtemp], DirOK(i, md));
	else
		ok = ok || (md = right[mdtemp], DirOK(i, md)) || (md = left[mdtemp], DirOK(i, md));
	if (random(102, 2))
		ok = ok
		    || (md = right[right[mdtemp]], DirOK(i, md))
		    || (md = left[left[mdtemp]], DirOK(i, md));
	else
		ok = ok
		    || (md = left[left[mdtemp]], DirOK(i, md))
		    || (md = right[right[mdtemp]], DirOK(i, md));
	if (ok)
		M_WalkDir(i, md);
	return ok;
}

BOOL M_PathWalk(int i)
{
	char path[25];
	BOOL(* Check)
	(int, int, int);

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("M_PathWalk: Invalid monster %d", i);

	Check = PosOkMonst3;
	if (!(monster[i]._mFlags & MFLAG_CAN_OPEN_DOOR))
		Check = PosOkMonst;

	if (FindPath(Check, i, monster[i]._mx, monster[i]._my, monster[i]._menemyx, monster[i]._menemyy, path)) {
		M_CallWalk(i, plr2monst[path[0]]); /* plr2monst is local */
		return TRUE;
	}

	return FALSE;
}

BOOL M_CallWalk2(int i, int md)
{
	BOOL ok;
	int mdtemp;

	mdtemp = md;
	ok = DirOK(i, md);    // Can we continue in the same direction
	if (random(101, 2)) { // Randomly go left or right
		ok = ok || (mdtemp = left[md], DirOK(i, left[md])) || (mdtemp = right[md], DirOK(i, right[md]));
	} else {
		ok = ok || (mdtemp = right[md], DirOK(i, right[md])) || (mdtemp = left[md], DirOK(i, left[md]));
	}

	if (ok)
		M_WalkDir(i, mdtemp);

	return ok;
}

BOOL M_DumbWalk(int i, int md)
{
	BOOL ok;
	ok = DirOK(i, md);
	if (ok)
		M_WalkDir(i, md);

	return ok;
}

BOOL M_RoundWalk(int i, int md, int *dir)
{
	int mdtemp;
	BOOL ok;
	if (*dir)
		md = left[left[md]];
	else
		md = right[right[md]];

	ok = DirOK(i, md);
	mdtemp = md;
	if (!ok) {
		if (*dir) {
			md = right[mdtemp];
			ok = DirOK(i, md) || (md = right[right[mdtemp]], DirOK(i, md));
		} else {
			md = left[mdtemp];
			ok = (DirOK(i, md) || (md = left[left[mdtemp]], DirOK(i, md)));
		}
	}
	if (ok) {
		M_WalkDir(i, md);
	} else {
		*dir = !*dir;
		ok = M_CallWalk(i, opposite[mdtemp]);
	}
	return ok;
}

void MAI_Zombie(int i)
{
	MonsterStruct *Monst;
	int mx, my;
	int md, v;

	if ((DWORD)i >= MAXMONSTERS) {
		app_fatal("MAI_Zombie: Invalid monster %d", i);
	}

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	if (!(dFlags[mx][my] & DFLAG_VISIBLE)) {
		return;
	}

	mx = mx - Monst->_menemyx;
	my = my - Monst->_menemyy;
	md = Monst->_mdir;
	v = random(103, 100);
	if (abs(mx) >= 2 || abs(my) >= 2) {
		if (v < 2 * Monst->_mint + 10) {
			if (abs(mx) >= 2 * Monst->_mint + 4 || abs(my) >= 2 * Monst->_mint + 4) {
				if (random(104, 100) < 2 * Monst->_mint + 20) {
					md = random(104, 8);
				}
				M_DumbWalk(i, md);
			} else {
				md = M_GetDir(i);
				M_CallWalk(i, md);
			}
		}
	} else if (v < 2 * Monst->_mint + 10) {
		M_StartAttack(i);
	}

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[Monst->_mdir];
}

void MAI_SkelSd(int i)
{
	MonsterStruct *Monst;
	int mx, my, x, y, md;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_SkelSd: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND || !Monst->_msquelch) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	x = mx - Monst->_menemyx;
	y = my - Monst->_menemyy;
	md = GetDirection(mx, my, Monst->_lastx, Monst->_lasty);
	Monst->_mdir = md;
	if (abs(x) >= 2 || abs(y) >= 2) {
		if (Monst->_mVar1 == MM_DELAY || (random(106, 100) >= 35 - 4 * Monst->_mint)) {
			M_CallWalk(i, md);
		} else {
			M_StartDelay(i, 15 - 2 * Monst->_mint + random(106, 10));
		}
	} else {
		if (Monst->_mVar1 == MM_DELAY || (random(105, 100) < 2 * Monst->_mint + 20)) {
			M_StartAttack(i);
		} else {
			M_StartDelay(i, 2 * (5 - Monst->_mint) + random(105, 10));
		}
	}

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

BOOL MAI_Path(int i)
{
	MonsterStruct *Monst;
	BOOL clear;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Path: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->MType->mtype != MT_GOLEM) {
		if (!Monst->_msquelch)
			return FALSE;
		if (Monst->_mmode != MM_STAND)
			return FALSE;
		if (Monst->_mgoal != MGOAL_NORMAL && Monst->_mgoal != MGOAL_MOVE && Monst->_mgoal != MGOAL_SHOOT)
			return FALSE;
		if (Monst->_mx == 1 && Monst->_my == 0)
			return FALSE;
	}

	clear = LineClearF1(
	    PosOkMonst2,
	    i,
	    Monst->_mx,
	    Monst->_my,
	    Monst->_menemyx,
	    Monst->_menemyy);
	if (!clear || Monst->_pathcount >= 5 && Monst->_pathcount < 8) {
		if (Monst->_mFlags & MFLAG_CAN_OPEN_DOOR)
			MonstCheckDoors(i);
		Monst->_pathcount++;
		if (Monst->_pathcount < 5)
			return FALSE;
		if (M_PathWalk(i))
			return TRUE;
	}

	if (Monst->MType->mtype != MT_GOLEM)
		Monst->_pathcount = 0;

	return FALSE;
}

void MAI_Snake(int i)
{
	int esi1;            // esi
	MonsterStruct *esi3; // esi
	BOOLEAN v3;          // zf
	int v4;              // ecx
	int v5;              // eax
	int v6;              // ST1C_4
	int v7;              // edi
	int v8;              // edx
	int v9;              // ST18_4
	int v10;             // ebx
	int v11;             // eax
	//int v12; // ST1C_4
	int v14; // eax
	int v15; // eax
	int v16; // ecx
	int v17; // edx
	int v18; // ecx
	int v19; // eax
	//int v20; // ST1C_4
	int v22; // eax
	//int v23; // ST1C_4
	int v24;         // ebx
	int v26;         // ecx
	int v27;         // eax
	int v28;         // ecx
	int v29;         // ecx
	int v30;         // eax
	int v31;         // edx
	int v32;         // eax
	int v33;         // ecx
	int v34;         // ecx
	int v35;         // eax
	char pattern[6]; // [esp+4h] [ebp-1Ch]
	int micaster;    // [esp+Ch] [ebp-14h]
	int midir;       // [esp+10h] [ebp-10h]
	int v1;          // [esp+14h] [ebp-Ch]
	int v2;          // [esp+18h] [ebp-8h]
	int arglist;     // [esp+1Ch] [ebp-4h]

	esi1 = i;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Snake: Invalid monster %d", i);
	pattern[2] = 0;
	pattern[3] = -1;
	pattern[4] = -1;
	pattern[5] = 0;
	esi3 = &monster[esi1];
	pattern[0] = 1;
	pattern[1] = 1;
	v3 = esi3->_mmode == MM_STAND;
	micaster = esi3->_menemy;
	if (v3 && esi3->_msquelch) {
		v4 = esi3->_mx;
		v5 = (unsigned char)esi3->_menemyy;
		v6 = esi3->_lasty;
		v1 = (unsigned char)esi3->_menemyx;
		v7 = v4 - v1;
		v8 = esi3->_my;
		v9 = esi3->_lastx;
		v2 = v5;
		v10 = v8 - v5;
		midir = GetDirection(v4, v8, v9, v6);
		esi3->_mdir = midir;
		if (abs(v7) < 2) {
			v11 = abs(v10);
			//v13 = v12;
			if (v11 < 2) {
				v14 = esi3->_mVar1;
				if (v14 == MM_DELAY
				    || v14 == MM_CHARGE
				    || (v15 = random(105, 100), v16 = (unsigned char)esi3->_mint + 20, v15 < v16)) {
					M_StartAttack(arglist);
				LABEL_49:
					if (esi3->_mmode == MM_STAND)
						esi3->_mAnimData = esi3->MType->Anims[MA_STAND].Data[esi3->_mdir];
					return;
				}
				v17 = 10 - (unsigned char)esi3->_mint + random(105, 10);
				v18 = arglist;
			LABEL_11:
				M_StartDelay(v18, v17);
				goto LABEL_49;
			}
		}
		v19 = abs(v7);
		//v21 = v20;
		if (v19 >= 3 || (v22 = abs(v10), v22 >= 3)) /* v21 = v23,  */
		{
			v24 = arglist;
		} else {
			v24 = arglist;
			if (LineClearF1(PosOkMonst, arglist, esi3->_mx, esi3->_my, v1, v2) && esi3->_mVar1 != MM_CHARGE) {
				if (AddMissile(esi3->_mx, esi3->_my, v1, v2, midir, MIS_RHINO, micaster, arglist, 0, 0) != -1) {
					PlayEffect(arglist, 0);
					v26 = esi3->_my + 112 * esi3->_mx;
					esi3->_mmode = MM_CHARGE;
					dMonster[0][v26] = -1 - v24;
				}
				goto LABEL_49;
			}
		}
		if (esi3->_mVar1 != MM_DELAY) {
			v27 = random(106, 100);
			v28 = 2 * (unsigned char)esi3->_mint;
			if (v27 < 35 - v28) {
				v17 = 15 - (unsigned char)esi3->_mint + random(106, 10);
				v18 = v24;
				goto LABEL_11;
			}
		}
		v29 = esi3->_mgoalvar1;
		v30 = midir + pattern[v29];
		if (v30 >= 0) {
			v31 = v30 - 8;
			if (v30 < 8)
				v31 = midir + pattern[v29];
		} else {
			v31 = v30 + 8;
		}
		esi3->_mgoalvar1 = v29 + 1;
		if (v29 + 1 > 5)
			esi3->_mgoalvar1 = 0;
		v32 = esi3->_mgoalvar2;
		v33 = v31 - v32;
		if (v31 - v32 >= 0) {
			if (v33 >= 8)
				v33 -= 8;
		} else {
			v33 += 8;
		}
		if (v33 <= 0) {
		LABEL_47:
			if (!M_DumbWalk(v24, esi3->_mgoalvar2))
				M_CallWalk2(v24, esi3->_mdir);
			goto LABEL_49;
		}
		if (v33 >= 4) {
			if (v33 == 4) {
				esi3->_mgoalvar2 = v31;
				goto LABEL_47;
			}
			v34 = v32 - 1;
			if (v32 - 1 < 0) {
				v35 = v32 + 7;
				goto LABEL_46;
			}
			if (v34 >= 8) {
				v35 = v32 - 9;
				goto LABEL_46;
			}
		} else {
			v34 = v32 + 1;
			if (v32 + 1 < 0) {
				v35 = v32 + 9;
			LABEL_46:
				esi3->_mgoalvar2 = v35;
				goto LABEL_47;
			}
			if (v34 >= 8) {
				v35 = v32 - 7;
				goto LABEL_46;
			}
		}
		v35 = v34;
		goto LABEL_46;
	}
}

void MAI_Bat(int i)
{
	MonsterStruct *Monst;
	int md, v, pnum;
	int fx, fy, xd, yd;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Bat: Invalid monster %d", i);

	Monst = &monster[i];
	pnum = Monst->_menemy;
	if (Monst->_mmode != MM_STAND || !Monst->_msquelch) {
		return;
	}

	xd = Monst->_mx - Monst->_menemyx;
	yd = Monst->_my - Monst->_menemyy;
	md = GetDirection(Monst->_mx, Monst->_my, Monst->_lastx, Monst->_lasty);
	Monst->_mdir = md;
	v = random(107, 100);
	if (Monst->_mgoal == MGOAL_RETREAT) {
		if (!Monst->_mgoalvar1) {
			M_CallWalk(i, opposite[md]);
			Monst->_mgoalvar1++;
		} else {
			if (random(108, 2))
				M_CallWalk(i, left[md]);
			else
				M_CallWalk(i, right[md]);
			Monst->_mgoal = MGOAL_NORMAL;
		}
		return;
	}

	fx = Monst->_menemyx;
	fy = Monst->_menemyy;
	if (Monst->MType->mtype == MT_GLOOM
	    && (abs(xd) >= 5 || abs(yd) >= 5)
	    && v < 4 * Monst->_mint + 33
	    && LineClearF1(PosOkMonst, i, Monst->_mx, Monst->_my, fx, fy)) {
		if (AddMissile(Monst->_mx, Monst->_my, fx, fy, md, MIS_RHINO, pnum, i, 0, 0) != -1) {
			dMonster[Monst->_mx][Monst->_my] = -(i + 1);
			Monst->_mmode = MM_CHARGE;
		}
	} else if (abs(xd) >= 2 || abs(yd) >= 2) {
		if (Monst->_mVar2 > 20 && v < Monst->_mint + 13
		    || (Monst->_mVar1 == MM_WALK || Monst->_mVar1 == MM_WALK2 || Monst->_mVar1 == MM_WALK3)
		        && Monst->_mVar2 == 0
		        && v < Monst->_mint + 63) {
			M_CallWalk(i, md);
		}
	} else if (v < 4 * Monst->_mint + 8) {
		M_StartAttack(i);
		Monst->_mgoal = MGOAL_RETREAT;
		Monst->_mgoalvar1 = 0;
		if (Monst->MType->mtype == MT_FAMILIAR) {
			AddMissile(Monst->_menemyx, Monst->_menemyy, Monst->_menemyx + 1, 0, -1, MIS_LIGHTNING, 1, i, random(109, 10) + 1, 0);
		}
	}

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_SkelBow(int i)
{
	MonsterStruct *Monst;
	int mx, my, md, v;
	BOOL walking;

	walking = FALSE;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_SkelBow: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND || !Monst->_msquelch) {
		return;
	}

	mx = Monst->_mx - Monst->_menemyx;
	my = Monst->_my - Monst->_menemyy;

	md = M_GetDir(i);
	Monst->_mdir = md;
	v = random(110, 100);

	if (abs(mx) < 4 && abs(my) < 4) {
		if (Monst->_mVar2 > 20 && v < 2 * Monst->_mint + 13
		    || (Monst->_mVar1 == MM_WALK || Monst->_mVar1 == MM_WALK2 || Monst->_mVar1 == MM_WALK3)
		        && Monst->_mVar2 == 0
		        && v < 2 * Monst->_mint + 63) {
			walking = M_DumbWalk(i, opposite[md]);
		}
	}

	mx = Monst->_menemyx;
	my = Monst->_menemyy;
	if (!walking) {
		if (random(110, 100) < 2 * Monst->_mint + 3) {
			if (LineClear(Monst->_mx, Monst->_my, mx, my))
				M_StartRAttack(i, MIS_ARROW, 4);
		}
	}

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_Fat(int i)
{
	MonsterStruct *Monst;
	int mx, my, md, v;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Fat: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND || !Monst->_msquelch) {
		return;
	}

	mx = Monst->_mx - Monst->_menemyx;
	my = Monst->_my - Monst->_menemyy;
	md = M_GetDir(i);
	Monst->_mdir = md;
	v = random(111, 100);
	if (abs(mx) >= 2 || abs(my) >= 2) {
		if (Monst->_mVar2 > 20 && v < 4 * Monst->_mint + 20
		    || (Monst->_mVar1 == MM_WALK || Monst->_mVar1 == MM_WALK2 || Monst->_mVar1 == MM_WALK3)
		        && Monst->_mVar2 == 0
		        && v < 4 * Monst->_mint + 70) {
			M_CallWalk(i, md);
		}
	} else if (v < 4 * Monst->_mint + 15) {
		M_StartAttack(i);
	} else if (v < 4 * Monst->_mint + 20) {
		M_StartSpAttack(i);
	}

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_Sneak(int i)
{
	int v1;            // edi
	MonsterStruct *v2; // esi
	int v3;            // ebx
	int v4;            // ebx
	int v6;            // edi
	int v7;            // eax
	//int v8; // ST04_4
	int v9; // eax
	//int v10; // ST04_4
	int v11;        // eax
	int v12;        // edi
	signed int v13; // ecx
	int v14;        // eax
	int v15;        // [esp+Ch] [ebp-10h]
	int arglist;    // [esp+10h] [ebp-Ch]
	int v17;        // [esp+14h] [ebp-8h]
	int md;         // [esp+18h] [ebp-4h]

	v1 = i;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS) {
		app_fatal("MAI_Sneak: Invalid monster %d", i);
	}

	v2 = &monster[v1];
	if (v2->_mmode == MM_STAND) {
		v3 = v2->_my;
		if (dLight[v2->_mx][v3] != lightmax) {
			v17 = v2->_mx - (unsigned char)v2->_menemyx;
			v4 = v3 - (unsigned char)v2->_menemyy;
			md = M_GetDir(v1);
			v6 = 5 - (unsigned char)v2->_mint;
			if (v2->_mVar1 == MM_GOTHIT) {
				v2->_mgoalvar1 = 0;
				_LOBYTE(v2->_mgoal) = MGOAL_RETREAT;
			} else {
				v7 = abs(v17);
				//v5 = v8;
				if (v7 >= v6 + 3 || (v9 = abs(v4), v9 >= v6 + 3) || v2->_mgoalvar1 > 8) /* v5 = v10,  */
				{
					v2->_mgoalvar1 = 0;
					_LOBYTE(v2->_mgoal) = MGOAL_NORMAL;
				}
			}
			if (_LOBYTE(v2->_mgoal) == MGOAL_RETREAT) {
				if (v2->_mFlags & MFLAG_TARGETS_MONSTER)
					md = GetDirection(v2->_mx, v2->_my, plr[v2->_menemy]._pownerx, plr[v2->_menemy]._pownery);
				md = opposite[md];
				if (v2->MType->mtype == MT_UNSEEN) {
					if (random(112, 2))
						v11 = left[md];
					else
						v11 = right[md];
					md = v11;
				}
			}
			v2->_mdir = md;
			v15 = random(112, 100);
			if (abs(v17) < v6 && abs(v4) < v6 && v2->_mFlags & MFLAG_HIDDEN) {
				M_StartFadein(arglist, md, FALSE);
			} else {
				v12 = v6 + 1;
				if (abs(v17) < v12 && abs(v4) < v12 || v2->_mFlags & MFLAG_HIDDEN) {
					if (_LOBYTE(v2->_mgoal) == MGOAL_RETREAT
					    || (abs(v17) >= 2 || abs(v4) >= 2)
					        && ((v13 = v2->_mVar2, v13 > 20) && v15 < 4 * (unsigned char)v2->_mint + 14
					               || ((v14 = v2->_mVar1, v14 == MM_WALK) || v14 == MM_WALK2 || v14 == MM_WALK3)
					                   && !v13
					                   && v15 < 4 * (unsigned char)v2->_mint + 64)) {
						++v2->_mgoalvar1;
						M_CallWalk(arglist, md);
					}
				} else {
					M_StartFadeout(arglist, md, TRUE);
				}
			}
			if (v2->_mmode == MM_STAND) {
				if (abs(v17) >= 2 || abs(v4) >= 2 || v15 >= 4 * (unsigned char)v2->_mint + 10)
					v2->_mAnimData = v2->MType->Anims[MA_STAND].Data[md];
				else
					M_StartAttack(arglist);
			}
		}
	}
}
// 642A14: using guessed type char lightmax;

void MAI_Fireman(int i)
{
	int xd, yd;
	int md, pnum;
	int fx, fy;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Fireman: Invalid monster %d", i);

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND || !Monst->_msquelch)
		return;

	pnum = monster[i]._menemy;
	fx = monster[i]._menemyx;
	fy = monster[i]._menemyy;
	xd = monster[i]._mx - fx;
	yd = monster[i]._my - fy;

	md = M_GetDir(i);
	if (Monst->_mgoal == MGOAL_NORMAL) {
		if (LineClear(Monst->_mx, Monst->_my, fx, fy)
		    && AddMissile(Monst->_mx, Monst->_my, fx, fy, md, MIS_FIREMAN, pnum, i, 0, 0) != -1) {
			Monst->_mmode = MM_CHARGE;
			Monst->_mgoal = MGOAL_SHOOT;
			Monst->_mgoalvar1 = 0;
		}
	} else if (Monst->_mgoal == MGOAL_SHOOT) {
		if (Monst->_mgoalvar1 == 3) {
			Monst->_mgoal = MGOAL_NORMAL;
			M_StartFadeout(i, md, TRUE);
		} else if (LineClear(Monst->_mx, Monst->_my, fx, fy)) {
			M_StartRAttack(i, MIS_KRULL, 4);
			Monst->_mgoalvar1++;
		} else {
			M_StartDelay(i, random(112, 10) + 5);
			Monst->_mgoalvar1++;
		}
	} else if (Monst->_mgoal == MGOAL_RETREAT) {
		M_StartFadein(i, md, FALSE);
		Monst->_mgoal = MGOAL_SHOOT;
	}
	Monst->_mdir = md;
	random(112, 100);
	if (Monst->_mmode != MM_STAND)
		return;

	if (abs(xd) < 2 && abs(yd) < 2 && Monst->_mgoal == MGOAL_NORMAL) {
		M_TryH2HHit(i, monster[i]._menemy, monster[i].mHit, monster[i].mMinDamage, monster[i].mMaxDamage);
		Monst->_mgoal = MGOAL_RETREAT;
		if (!M_CallWalk(i, opposite[md])) {
			M_StartFadein(i, md, FALSE);
			Monst->_mgoal = MGOAL_SHOOT;
		}
	} else if (!M_CallWalk(i, md) && (Monst->_mgoal == MGOAL_NORMAL || Monst->_mgoal == MGOAL_RETREAT)) {
		M_StartFadein(i, md, FALSE);
		Monst->_mgoal = MGOAL_SHOOT;
	}
}

void MAI_Fallen(int i)
{
	int x, y, xpos, ypos;
	int m, rad, md;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS) {
		app_fatal("MAI_Fallen: Invalid monster %d", i);
	}
	if (monster[i]._mgoal == MGOAL_SHOOT) {
		if (monster[i]._mgoalvar1)
			monster[i]._mgoalvar1--;
		else
			monster[i]._mgoal = MGOAL_NORMAL;
	}

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND || !monster[i]._msquelch) {
		return;
	}

	if (Monst->_mgoal == MGOAL_RETREAT) {
		if (!Monst->_mgoalvar1--) {
			Monst->_mgoal = MGOAL_NORMAL;
			M_StartStand(i, opposite[Monst->_mdir]);
		}
	}

	if (Monst->_mAnimFrame == Monst->_mAnimLen) {
		if (random(113, 4)) {
			return;
		}
		if (!(Monst->_mFlags & MFLAG_NOHEAL)) {
			M_StartSpStand(i, Monst->_mdir);
			rad = 2 * Monst->_mint + 2;
			if (Monst->_mmaxhp - rad >= Monst->_mhitpoints)
				Monst->_mhitpoints = rad + Monst->_mhitpoints;
			else
				Monst->_mhitpoints = Monst->_mmaxhp;
		}
		rad = 2 * Monst->_mint + 4;
		for (y = -rad; y <= rad; y++) {
			for (x = -rad; x <= rad; x++) {
				if (y >= 0 && y < MAXDUNY && x >= 0 && x < MAXDUNX) {
					m = dMonster[x + Monst->_mx][y + Monst->_my];
					if (m > 0) {
						m--;
						if (monster[m]._mAi == AI_FALLEN) {
							monster[m]._mgoal = MGOAL_SHOOT;
							monster[m]._mgoalvar1 = 30 * Monst->_mint + 105;
						}
					}
				}
			}
		}
	} else if (Monst->_mgoal == MGOAL_RETREAT) {
		md = Monst->_mdir;
		M_CallWalk(i, md);
	} else if (Monst->_mgoal == MGOAL_SHOOT) {
		xpos = Monst->_mx - Monst->_menemyx;
		ypos = Monst->_my - Monst->_menemyy;
		if (abs(xpos) < 2 && abs(ypos) < 2) {
			M_StartAttack(i);
		} else {
			md = M_GetDir(i);
			M_CallWalk(i, md);
		}
	} else {
		MAI_SkelSd(i);
	}
}

void MAI_Cleaver(int i)
{
	MonsterStruct *Monst;
	int x, y, mx, my, md;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Cleaver: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND || !Monst->_msquelch) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	x = mx - Monst->_menemyx;
	y = my - Monst->_menemyy;

	md = GetDirection(mx, my, Monst->_lastx, Monst->_lasty);
	Monst->_mdir = md;

	if (abs(x) >= 2 || abs(y) >= 2)
		M_CallWalk(i, md);
	else
		M_StartAttack(i);

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_Round(int i, BOOL special)
{
	int v2;            // esi
	MonsterStruct *v3; // esi
	int v4;            // edx
	int v5;            // ecx
	int v6;            // edi
	int v7;            // ebx
	int v9;            // eax
	//int v10; // ST04_4
	int v12; // eax
	//int v13; // ST04_4
	int v15;     // edi
	int v16;     // eax
	int v17;     // ecx
	BOOLEAN v18; // eax
	//int v19; // eax
	int v21; // eax
	int v22; // eax
	//int v23; // ST04_4
	signed int v25; // ecx
	int v26;        // eax
	int v27;        // [esp+4h] [ebp-18h]
	int v28;        // [esp+8h] [ebp-14h]
	char *v29;      // [esp+8h] [ebp-14h]
	int v30;        // [esp+Ch] [ebp-10h]
	int md;         // [esp+10h] [ebp-Ch]
	int v32;        // [esp+14h] [ebp-8h]
	int arglist;    // [esp+18h] [ebp-4h]

	v2 = i;
	v27 = special;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Round: Invalid monster %d", i);
	v3 = &monster[v2];
	if (v3->_mmode == MM_STAND && v3->_msquelch) {
		v4 = v3->_my;
		v5 = v3->_mx;
		v28 = (unsigned char)v3->_menemyy;
		v6 = (unsigned char)v3->_menemyx;
		v7 = v5 - v6;
		v32 = v4 - v28;
		md = GetDirection(v5, v4, v3->_lastx, v3->_lasty);
		if (v3->_msquelch < 0xFFu) /* check sign */
			MonstCheckDoors(arglist);
		v30 = random(114, 100);
		if ((abs(v7) >= 2 || abs(v32) >= 2) && v3->_msquelch == -1) {
			v29 = &dTransVal[v6][v28];
			if (dTransVal[v3->_mx][v3->_my] == *v29) {
				if (_LOBYTE(v3->_mgoal) != MGOAL_MOVE) {
					v9 = abs(v7);
					//v11 = v10;
					if (v9 < 4) {
						v12 = abs(v32);
						//v11 = v13;
						if (v12 < 4)
							goto LABEL_26;
					}
					if (random(115, 4))
						goto LABEL_26;
					if (_LOBYTE(v3->_mgoal) != MGOAL_MOVE) {
						v3->_mgoalvar1 = 0;
						v3->_mgoalvar2 = random(116, 2);
					}
				}
				_LOBYTE(v3->_mgoal) = MGOAL_MOVE;
				v15 = abs(v32);
				if (abs(v7) <= v15)
					v16 = abs(v32);
				else
					v16 = abs(v7);
				v17 = v3->_mgoalvar1;
				v3->_mgoalvar1 = v17 + 1;
				if (v17 < 2 * v16 || (v18 = DirOK(arglist, md), !v18)) {
					if (dTransVal[v3->_mx][v3->_my] == *v29) {
						//_LOBYTE(v19) = M_RoundWalk(arglist, md, &v3->_mgoalvar2);
						if (!M_RoundWalk(arglist, md, &v3->_mgoalvar2)) {
							v21 = random(125, 10);
							M_StartDelay(arglist, v21 + 10);
						}
						goto LABEL_26;
					}
				}
			}
		}
		_LOBYTE(v3->_mgoal) = MGOAL_NORMAL;
	LABEL_26:
		if (_LOBYTE(v3->_mgoal) == MGOAL_NORMAL) {
			if (abs(v7) >= 2 || (v22 = abs(v32), v22 >= 2)) /* v24 = v23,  */
			{
				v25 = v3->_mVar2;
				if (v25 > 20 && v30 < 2 * (unsigned char)v3->_mint + 28
				    || ((v26 = v3->_mVar1, v26 == MM_WALK) || v26 == MM_WALK2 || v26 == MM_WALK3)
				        && !v25
				        && v30 < 2 * (unsigned char)v3->_mint + 78) {
					M_CallWalk(arglist, md);
				}
			} else if (v30 < 2 * (unsigned char)v3->_mint + 23) {
				v3->_mdir = md;
				if (v27 && v3->_mhitpoints<v3->_mmaxhp>> 1 && random(117, 2))
					M_StartSpAttack(arglist);
				else
					M_StartAttack(arglist);
			}
		}
		if (v3->_mmode == MM_STAND)
			v3->_mAnimData = v3->MType->Anims[MA_STAND].Data[md];
	}
}

void MAI_GoatMc(int i)
{
	MAI_Round(i, 1u);
}

void MAI_Ranged(int i, int missile_type, BOOL special)
{
	int md;
	int mx, my, fx, fy;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Ranged: Invalid monster %d", i);

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND) {
		return;
	}

	if (Monst->_msquelch == -1 || Monst->_mFlags & MFLAG_TARGETS_MONSTER) {
		mx = Monst->_menemyx;
		my = Monst->_menemyy;
		fx = Monst->_mx - mx;
		fy = Monst->_my - my;
		md = M_GetDir(i);
		if ((DWORD)Monst->_msquelch < -1) /* check sign */
			MonstCheckDoors(i);
		Monst->_mdir = md;
		if (Monst->_mVar1 == MM_RATTACK) {
			M_StartDelay(i, random(118, 20));
		} else if (abs(fx) < 4 && abs(fy) < 4) {
			if (random(119, 100) < 10 * (Monst->_mint + 7))
				M_CallWalk(i, opposite[md]);
		}
		if (Monst->_mmode == MM_STAND) {
			if (LineClear(Monst->_mx, Monst->_my, mx, my)) {
				if (special)
					M_StartRSpAttack(i, missile_type, 4);
				else
					M_StartRAttack(i, missile_type, 4);
			} else {
				Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
			}
		}
	} else if (Monst->_msquelch) {
		md = GetDirection(Monst->_mx, Monst->_my, Monst->_lastx, Monst->_lasty);
		M_CallWalk(i, md);
	}
}

void MAI_GoatBow(int i)
{
	MAI_Ranged(i, MIS_ARROW, 0);
}

void MAI_Succ(int i)
{
	MAI_Ranged(i, MIS_FLARE, 0);
}

void MAI_AcidUniq(int i)
{
	MAI_Ranged(i, MIS_ACID, 1u);
}

void MAI_Scav(int i)
{
	int v1;            // edi
	int v2;            // esi
	unsigned char *v3; // eax
	int v4;            // ecx
	int v5;            // ecx
	signed int v6;     // ebx
	signed int v7;     // edi
	int v8;            // edx
	int v9;            // eax
	BOOLEAN v10;       // eax
	int v11;           // ebx
	int v12;           // edi
	signed int v13;    // edi
	int v14;           // edx
	int v15;           // eax
	BOOLEAN v16;       // eax
	int v17;           // eax
	int v18;           // eax
	int arglist;       // [esp+Ch] [ebp-8h]
	BOOL v20;          // [esp+10h] [ebp-4h]

	v1 = i;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Scav: Invalid monster %d", i);
	v2 = v1;
	v20 = 0;
	if (monster[v1]._mmode == MM_STAND) {
		if (monster[v2]._mhitpoints<monster[v2]._mmaxhp>> 1) {
			if (_LOBYTE(monster[v2]._mgoal) == MGOAL_HEALING)
				goto LABEL_10;
			if (monster[v2].leaderflag) {
				v3 = &monster[(unsigned char)monster[v2].leader].packsize;
				--*v3;
				monster[v2].leaderflag = 0;
			}
			_LOBYTE(monster[v2]._mgoal) = MGOAL_HEALING;
			monster[v2]._mgoalvar3 = 10;
		}
		if (_LOBYTE(monster[v2]._mgoal) != MGOAL_HEALING) {
		LABEL_52:
			if (monster[v2]._mmode == MM_STAND)
				MAI_SkelSd(arglist);
			return;
		}
	LABEL_10:
		v4 = monster[v2]._mgoalvar3;
		if (v4) {
			monster[v2]._mgoalvar3 = v4 - 1;
			v5 = monster[v2]._my;
			if (dDead[monster[v2]._mx][v5]) {
				M_StartEat(v1);
				if (!(monster[v2]._mFlags & MFLAG_NOHEAL))
					monster[v2]._mhitpoints += 64;
				if (monster[v2]._mhitpoints >= (monster[v2]._mmaxhp >> 1) + (monster[v2]._mmaxhp >> 2)) {
					_LOBYTE(monster[v2]._mgoal) = MGOAL_NORMAL;
					monster[v2]._mgoalvar1 = 0;
					monster[v2]._mgoalvar2 = 0;
				}
			} else {
				if (!monster[v2]._mgoalvar1) {
					v6 = arglist;
					if (random(120, 2)) {
						v7 = -4;
						do {
							if (v20)
								break;
							v6 = -4;
							do {
								if (v20)
									break;
								if (v7 >= 0 && v7 < MAXDUNY && v6 >= 0 && v6 < MAXDUNX) {
									v8 = monster[v2]._mx;
									v9 = monster[v2]._my;
									v20 = dDead[v8 + v6][v9 + v7]
									    && (v10 = LineClearF(
									            CheckNoSolid,
									            v8,
									            v9,
									            v8 + v6,
									            v9 + v7),
									           v10);
								}
								++v6;
							} while (v6 <= 4);
							++v7;
						} while (v7 <= 4);
						v11 = v6 - 1;
						v12 = v7 - 1;
					} else {
						v13 = 4;
						do {
							if (v20)
								break;
							v6 = 4;
							do {
								if (v20)
									break;
								if (v13 >= 0 && v13 < MAXDUNY && v6 >= 0 && v6 < MAXDUNX) {
									v14 = monster[v2]._mx;
									v15 = monster[v2]._my;
									v20 = dDead[v14 + v6][v15 + v13]
									    && (v16 = LineClearF(
									            CheckNoSolid,
									            v14,
									            v15,
									            v14 + v6,
									            v15 + v13),
									           v16);
								}
								--v6;
							} while (v6 >= -4);
							--v13;
						} while (v13 >= -4);
						v11 = v6 + 1;
						v12 = v13 + 1;
					}
					if (v20) {
						monster[v2]._mgoalvar1 = monster[v2]._mx + v11 + 1;
						monster[v2]._mgoalvar2 = monster[v2]._my + v12 + 1;
					}
				}
				v17 = monster[v2]._mgoalvar1;
				if (v17) {
					v18 = GetDirection(monster[v2]._mx, monster[v2]._my, v17 - 1, monster[v2]._mgoalvar2 - 1);
					monster[v2]._mdir = v18;
					M_CallWalk(arglist, v18);
				}
			}
		}
		goto LABEL_52;
	}
}

void MAI_Garg(int i)
{
	MonsterStruct *Monst;
	int mx, my, dx, dy, md;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Garg: Invalid monster %d", i);

	Monst = &monster[i];
	dx = Monst->_mx - Monst->_lastx;
	dy = Monst->_my - Monst->_lasty;
	md = M_GetDir(i);
	if (Monst->_msquelch && Monst->_mFlags & MFLAG_ALLOW_SPECIAL) {
		M_Enemy(i);
		mx = Monst->_mx - Monst->_menemyx;
		my = Monst->_my - Monst->_menemyy;
		if (abs(mx) < Monst->_mint + 2 && abs(my) < Monst->_mint + 2) {
			Monst->_mFlags &= ~MFLAG_ALLOW_SPECIAL;
		}
		return;
	}

	if (Monst->_mmode != MM_STAND || !Monst->_msquelch) {
		return;
	}

	if (Monst->_mhitpoints<Monst->_mmaxhp>> 1 && !(Monst->_mFlags & MFLAG_NOHEAL))
		Monst->_mgoal = MGOAL_RETREAT;
	if (Monst->_mgoal == MGOAL_RETREAT) {
		if (abs(dx) >= Monst->_mint + 2 || abs(dy) >= Monst->_mint + 2) {
			Monst->_mgoal = MGOAL_NORMAL;
			M_StartHeal(i);
		} else if (!M_CallWalk(i, opposite[md])) {
			Monst->_mgoal = MGOAL_NORMAL;
		}
	}
	MAI_Round(i, 0);
}

void MAI_RoundRanged(int i, int missile_type, unsigned char checkdoors, int dam, int lessmissiles)
{
	int v5;            // esi
	MonsterStruct *v6; // esi
	int v7;            // edx
	int v8;            // ebx
	int v9;            // edi
	int v11;           // eax
	//int v12; // ST04_4
	int v13; // ecx
	int v14; // eax
	//int v15; // ST04_4
	int v16; // eax
	//int v17; // ST04_4
	int v18;     // ecx
	int v19;     // ebx
	int v20;     // eax
	int v21;     // ecx
	BOOLEAN v22; // eax
	BOOLEAN v23; // eax
	BOOLEAN v24; // eax
	int v25;     // eax
	//int v26; // ST04_4
	int v27; // eax
	//int v28; // ST04_4
	int v29;           // eax
	int v30;           // edx
	int v31;           // eax
	int missile_typea; // [esp+4h] [ebp-18h]
	int v33;           // [esp+8h] [ebp-14h]
	int x2;            // [esp+Ch] [ebp-10h]
	int md;            // [esp+10h] [ebp-Ch]
	int y2;            // [esp+14h] [ebp-8h]
	int arglist;       // [esp+18h] [ebp-4h]
	int checkdoorsa;   // [esp+24h] [ebp+8h]

	v5 = i;
	missile_typea = missile_type;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_RoundRanged: Invalid monster %d", i);
	v6 = &monster[v5];
	if (v6->_mmode == MM_STAND && v6->_msquelch) {
		v7 = v6->_my;
		y2 = (unsigned char)v6->_menemyy;
		v8 = v7 - y2;
		x2 = (unsigned char)v6->_menemyx;
		v9 = v6->_mx - x2;
		v33 = v7 - y2;
		md = GetDirection(v6->_mx, v7, v6->_lastx, v6->_lasty);
		if (checkdoors && v6->_msquelch < 0xFFu) /* check sign */
			MonstCheckDoors(arglist);
		checkdoorsa = random(121, 10000);
		v11 = abs(v9);
		//v13 = v12;
		if (v11 < 2) {
			v14 = abs(v8);
			//v13 = v15;
			if (v14 < 2)
				goto LABEL_50;
		}
		if (v6->_msquelch != -1)
			goto LABEL_50;
		//v13 = y2;
		if (dTransVal[v6->_mx][v6->_my] != dTransVal[x2][y2])
			goto LABEL_50;
		if (_LOBYTE(v6->_mgoal) != MGOAL_MOVE) {
			if (abs(v9) < 3) {
				v16 = abs(v8);
				//v13 = v17;
				if (v16 < 3)
					goto LABEL_28;
			}
			v18 = lessmissiles;
			if (random(122, 4 << lessmissiles))
				goto LABEL_28;
			if (_LOBYTE(v6->_mgoal) != MGOAL_MOVE) {
				v6->_mgoalvar1 = 0;
				v6->_mgoalvar2 = random(123, 2);
			}
		}
		_LOBYTE(v6->_mgoal) = MGOAL_MOVE;
		v19 = abs(v8);
		if (abs(v9) <= v19) {
			v8 = v33;
			v20 = abs(v33);
		} else {
			v20 = abs(v9);
			v8 = v33;
		}
		v21 = v6->_mgoalvar1;
		v6->_mgoalvar1 = v21 + 1;
		if (v21 >= 2 * v20 && (v22 = DirOK(arglist, md), v22)) {
		LABEL_50:
			_LOBYTE(v6->_mgoal) = MGOAL_NORMAL;
		} else if (checkdoorsa<500 * ((unsigned char)v6->_mint + 1)>> lessmissiles
		    && (v23 = LineClear(v6->_mx, v6->_my, x2, y2), v23)) {
			M_StartRSpAttack(arglist, missile_typea, dam);
		} else {
			M_RoundWalk(arglist, md, &v6->_mgoalvar2);
		}
	LABEL_28:
		if (_LOBYTE(v6->_mgoal) == MGOAL_NORMAL) {
			if (((abs(v9) >= 3 || abs(v8) >= 3) && checkdoorsa<500 * ((unsigned char)v6->_mint + 2)>> lessmissiles
			        || checkdoorsa<500 * ((unsigned char)v6->_mint + 1)>> lessmissiles)
			    && (v24 = LineClear(v6->_mx, v6->_my, x2, y2), v24)) {
				M_StartRSpAttack(arglist, missile_typea, dam);
			} else {
				v25 = abs(v9);
				//v13 = v26;
				if (v25 >= 2 || (v27 = abs(v8), v27 >= 2)) /* v13 = v28,  */
				{
					v29 = random(124, 100);
					v30 = (unsigned char)v6->_mint;
					if (v29 < 1000 * (v30 + 5)
					    || ((v13 = v6->_mVar1, v13 == MM_WALK) || v13 == MM_WALK2 || v13 == MM_WALK3) && !v6->_mVar2 && v29 < 1000 * (v30 + 8)) {
						M_CallWalk(arglist, md);
					}
				} else if (checkdoorsa < 1000 * ((unsigned char)v6->_mint + 6)) {
					v6->_mdir = md;
					M_StartAttack(arglist);
				}
			}
		}
		if (v6->_mmode == MM_STAND) {
			v31 = random(125, 10);
			M_StartDelay(arglist, v31 + 5);
		}
	}
}

void MAI_Magma(int i)
{
	MAI_RoundRanged(i, MIS_MAGMABALL, 1u, 4, 0);
}

void MAI_Storm(int i)
{
	MAI_RoundRanged(i, MIS_LIGHTCTRL2, 1u, 4, 0);
}

void MAI_Acid(int i)
{
	MAI_RoundRanged(i, MIS_ACID, 0, 4, 1);
}

void MAI_Diablo(int i)
{
	MAI_RoundRanged(i, MIS_DIABAPOCA, 0, 40, 0);
}

void MAI_RR2(int i, int mistype, int dam)
{
	int v3;            // ebx
	MonsterStruct *v4; // esi
	int v5;            // edi
	int v6;            // edx
	int v7;            // ebx
	int v8;            // edi
	int v10;           // eax
	//int v11; // ST04_4
	int v12; // ecx
	int v13; // eax
	//int v14; // ST04_4
	int v15; // eax
	//int v16; // ST04_4
	int v17; // eax
	//int v18; // ST04_4
	int v19;     // ebx
	int v20;     // eax
	BOOLEAN v21; // eax
	BOOLEAN v22; // eax
	int v23;     // ecx
	int v24;     // eax
	//int v25; // ST04_4
	int v27; // eax
	//int v28; // ST04_4
	int v29;          // eax
	int v30;          // eax
	int v31;          // eax
	int v32;          // edx
	int v33;          // eax
	int missile_type; // [esp+Ch] [ebp-1Ch]
	int x2;           // [esp+10h] [ebp-18h]
	int v36;          // [esp+14h] [ebp-14h]
	int y2;           // [esp+18h] [ebp-10h]
	int v38;          // [esp+1Ch] [ebp-Ch]
	int md;           // [esp+20h] [ebp-8h]
	int arglist;      // [esp+24h] [ebp-4h]

	v3 = i;
	missile_type = mistype;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_RR2: Invalid monster %d", i);
	v4 = &monster[v3];
	v5 = v4->_my - (unsigned char)v4->_menemyy;
	if (abs(v4->_mx - (unsigned char)v4->_menemyx) >= 5 || abs(v5) >= 5) {
		MAI_SkelSd(v3);
		return;
	}
	if (v4->_mmode == MM_STAND && v4->_msquelch) {
		v6 = v4->_my;
		y2 = (unsigned char)v4->_menemyy;
		v7 = v6 - y2;
		x2 = (unsigned char)v4->_menemyx;
		v8 = v4->_mx - x2;
		v36 = v6 - y2;
		md = GetDirection(v4->_mx, v6, v4->_lastx, v4->_lasty);
		if (v4->_msquelch < 0xFFu) /* check sign */
			MonstCheckDoors(arglist);
		v38 = random(121, 100);
		v10 = abs(v8);
		//v12 = v11;
		if (v10 >= 2 || (v13 = abs(v7), v13 >= 2)) /* v12 = v14,  */
		{
			if (v4->_msquelch == -1) {
				//v12 = y2;
				if (dTransVal[v4->_mx][v4->_my] == dTransVal[x2][y2]) {
					if (_LOBYTE(v4->_mgoal) != MGOAL_MOVE) {
						v15 = abs(v8);
						//v12 = v16;
						if (v15 < 3) {
							v17 = abs(v7);
							//v12 = v18;
							if (v17 < 3)
								goto LABEL_26;
						}
						if (_LOBYTE(v4->_mgoal) != MGOAL_MOVE) {
							v4->_mgoalvar1 = 0;
							v4->_mgoalvar2 = random(123, 2);
						}
					}
					_LOBYTE(v4->_mgoal) = MGOAL_MOVE;
					v4->_mgoalvar3 = 4;
					v19 = abs(v7);
					if (abs(v8) <= v19) {
						v7 = v36;
						v20 = abs(v36);
					} else {
						v20 = abs(v8);
						v7 = v36;
					}
					v12 = v4->_mgoalvar1;
					v4->_mgoalvar1 = v12 + 1;
					if (v12 < 2 * v20 || (v21 = DirOK(arglist, md), !v21)) {
						if (v38 < 5 * ((unsigned char)v4->_mint + 16))
							M_RoundWalk(arglist, md, &v4->_mgoalvar2);
					LABEL_26:
						if (_LOBYTE(v4->_mgoal) != MGOAL_NORMAL)
							goto LABEL_48;
						if (((abs(v8) >= 3 || abs(v7) >= 3) && v38 < 5 * ((unsigned char)v4->_mint + 2)
						        || v38 < 5 * ((unsigned char)v4->_mint + 1)
						        || v4->_mgoalvar3 == 4)
						    && (v22 = LineClear(v4->_mx, v4->_my, x2, y2), v22)) {
							v23 = arglist;
						} else {
							v24 = abs(v8);
							//v26 = v25;
							if (v24 >= 2 || (v27 = abs(v7), v27 >= 2)) /* v26 = v28,  */
							{
								v31 = random(124, 100);
								v12 = (unsigned char)v4->_mint;
								if (v31 < 2 * (5 * v12 + 25)
								    || ((v32 = v4->_mVar1, v32 == MM_WALK) || v32 == MM_WALK2 || v32 == MM_WALK3)
								        && !v4->_mVar2
								        && (v12 = 2 * (5 * v12 + 40), v31 < v12)) {
									M_CallWalk(arglist, md);
								}
								goto LABEL_47;
							}
							v29 = random(124, 100);
							v12 = 10 * ((unsigned char)v4->_mint + 4);
							if (v29 >= v12) {
							LABEL_47:
								v4->_mgoalvar3 = 1;
							LABEL_48:
								if (v4->_mmode == MM_STAND) {
									v33 = random(125, 10);
									M_StartDelay(arglist, v33 + 5);
								}
								return;
							}
							v4->_mdir = md;
							v30 = random(124, 2);
							v23 = arglist;
							if (v30) {
								M_StartAttack(arglist);
								goto LABEL_47;
							}
						}
						M_StartRSpAttack(v23, missile_type, dam);
						goto LABEL_47;
					}
				}
			}
		}
		_LOBYTE(v4->_mgoal) = MGOAL_NORMAL;
		goto LABEL_26;
	}
}

void MAI_Mega(int i)
{
	MAI_RR2(i, MIS_FLAMEC, 0);
}

void MAI_Golum(int i)
{
	int mx, my, _mex, _mey;
	int md, j, k, _menemy;
	MonsterStruct *Monst;
	BOOL have_enemy, ok;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Golum: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mx == 1 && Monst->_my == 0) {
		return;
	}

	if (Monst->_mmode == MM_DEATH
	    || Monst->_mmode == MM_SPSTAND
	    || (Monst->_mmode >= MM_WALK && Monst->_mmode <= MM_WALK3)) {
		return;
	}

	if (!(Monst->_mFlags & MFLAG_TARGETS_MONSTER))
		M_Enemy(i);

	have_enemy = !(monster[i]._mFlags & MFLAG_NO_ENEMY);

	if (Monst->_mmode == MM_ATTACK) {
		return;
	}

	_menemy = monster[i]._menemy;

	mx = monster[i]._mx;
	my = monster[i]._my;
	_mex = mx - monster[_menemy]._mfutx;
	_mey = my - monster[_menemy]._mfuty;
	md = GetDirection(mx, my, monster[_menemy]._mx, monster[_menemy]._my);
	monster[i]._mdir = md;
	if (abs(_mex) >= 2 || abs(_mey) >= 2) {
		if (have_enemy && MAI_Path(i))
			return;
	} else if (have_enemy) {
		_menemy = monster[i]._menemy;
		monster[i]._menemyx = monster[_menemy]._mx;
		monster[i]._menemyy = monster[_menemy]._my;
		if (!monster[_menemy]._msquelch) {
			monster[_menemy]._msquelch = -1;
			monster[monster[i]._menemy]._lastx = monster[i]._mx;
			monster[monster[i]._menemy]._lasty = monster[i]._my;
			for (j = 0; j < 5; j++) {
				for (k = 0; k < 5; k++) {
					_menemy = dMonster[monster[i]._mx + k - 2][monster[i]._my + j - 2];
					if (_menemy > 0)
						monster[_menemy]._msquelch = -1;
				}
			}
		}
		M_StartAttack(i);
		return;
	}

	monster[i]._pathcount++;
	if (monster[i]._pathcount > 8)
		monster[i]._pathcount = 5;

	ok = M_CallWalk(i, plr[i]._pdir);
	if (!ok) {
		md = (md - 1) & 7;
		for (j = 0; j < 8 && !ok; j++) {
			md = (md + 1) & 7;
			ok = DirOK(i, md);
		}
		if (!ok) {
			return;
		}
		M_WalkDir(i, md);
	}
}

void MAI_SkelKing(int i)
{
	int v1;            // esi
	MonsterStruct *v2; // esi
	int v3;            // edx
	int v4;            // ebx
	int v5;            // edi
	int v7;            // eax
	//int v8; // ST04_4
	int v10; // eax
	//int v11; // ST04_4
	int v13;     // ebx
	int v14;     // eax
	int v15;     // ecx
	BOOLEAN v16; // eax
	//int v17; // eax
	int v19;     // eax
	BOOLEAN v20; // eax
	int v21;     // edi
	int v22;     // ebx
	int v23;     // eax
	//int v24; // ST04_4
	int v26; // eax
	//int v27; // ST04_4
	int v28;     // eax
	int v29;     // ecx
	int v30;     // edx
	int v31;     // eax
	char *v32;   // [esp+4h] [ebp-1Ch]
	int x2;      // [esp+8h] [ebp-18h]
	int v34;     // [esp+Ch] [ebp-14h]
	int v35;     // [esp+10h] [ebp-10h]
	int y2;      // [esp+14h] [ebp-Ch]
	int md;      // [esp+18h] [ebp-8h]
	int arglist; // [esp+1Ch] [ebp-4h]

	v1 = i;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_SkelKing: Invalid monster %d", i);
	v2 = &monster[v1];
	if (v2->_mmode == MM_STAND && v2->_msquelch) {
		v3 = v2->_my;
		y2 = (unsigned char)v2->_menemyy;
		v4 = v3 - y2;
		x2 = (unsigned char)v2->_menemyx;
		v5 = v2->_mx - x2;
		v34 = v3 - y2;
		md = GetDirection(v2->_mx, v3, v2->_lastx, v2->_lasty);
		if (v2->_msquelch < 0xFFu) /* check sign */
			MonstCheckDoors(arglist);
		v35 = random(126, 100);
		if ((abs(v5) >= 2 || abs(v4) >= 2) && v2->_msquelch == -1) {
			v32 = &dTransVal[x2][y2];
			if (dTransVal[v2->_mx][v2->_my] == *v32) {
				if (_LOBYTE(v2->_mgoal) != MGOAL_MOVE) {
					v7 = abs(v5);
					//v9 = v8;
					if (v7 < 3) {
						v10 = abs(v4);
						//v9 = v11;
						if (v10 < 3)
							goto LABEL_26;
					}
					if (random(127, 4))
						goto LABEL_26;
					if (_LOBYTE(v2->_mgoal) != MGOAL_MOVE) {
						v2->_mgoalvar1 = 0;
						v2->_mgoalvar2 = random(128, 2);
					}
				}
				_LOBYTE(v2->_mgoal) = MGOAL_MOVE;
				v13 = abs(v4);
				if (abs(v5) <= v13) {
					v4 = v34;
					v14 = abs(v34);
				} else {
					v14 = abs(v5);
					v4 = v34;
				}
				v15 = v2->_mgoalvar1;
				v2->_mgoalvar1 = v15 + 1;
				if (v15 < 2 * v14 || (v16 = DirOK(arglist, md), !v16)) {
					if (dTransVal[v2->_mx][v2->_my] == *v32) {
						//_LOBYTE(v17) = M_RoundWalk(arglist, md, &v2->_mgoalvar2);
						if (!M_RoundWalk(arglist, md, &v2->_mgoalvar2)) {
							v19 = random(125, 10);
							M_StartDelay(arglist, v19 + 10);
						}
						goto LABEL_26;
					}
				}
			}
		}
		_LOBYTE(v2->_mgoal) = MGOAL_NORMAL;
	LABEL_26:
		if (_LOBYTE(v2->_mgoal) == MGOAL_NORMAL) {
			if (gbMaxPlayers == 1
			    && ((abs(v5) >= 3 || abs(v4) >= 3) && v35 < 4 * (unsigned char)v2->_mint + 35 || v35 < 6)
			    && (v20 = LineClear(v2->_mx, v2->_my, x2, y2), v20)) {
				v21 = v2->_mx + offset_x[md];
				v22 = v2->_my + offset_y[md];
				if (PosOkMonst(arglist, v21, v22) && nummonsters < MAXMONSTERS) {
					M_SpawnSkel(v21, v22, md);
					M_StartSpStand(arglist, md);
				}
			} else {
				v23 = abs(v5);
				//v25 = v24;
				if (v23 >= 2 || (v26 = abs(v4), v26 >= 2)) /* v25 = v27,  */
				{
					v28 = random(129, 100);
					v29 = (unsigned char)v2->_mint;
					if (v28 >= v29 + 25
					    && ((v30 = v2->_mVar1, v30 != MM_WALK) && v30 != MM_WALK2 && v30 != MM_WALK3 || v2->_mVar2 || (v29 += 75, v28 >= v29))) {
						v31 = random(130, 10);
						M_StartDelay(arglist, v31 + 10);
					} else {
						M_CallWalk(arglist, md);
					}
				} else if (v35 < (unsigned char)v2->_mint + 20) {
					v2->_mdir = md;
					M_StartAttack(arglist);
				}
			}
		}
		if (v2->_mmode == MM_STAND)
			v2->_mAnimData = v2->MType->Anims[MA_STAND].Data[md];
	}
}
// 679660: using guessed type char gbMaxPlayers;

void MAI_Rhino(int i)
{
	int esi1;            // esi
	MonsterStruct *esi3; // esi
	int v3;              // edx
	int v4;              // ebx
	int v5;              // edi
	int v7;              // eax
	//int v8; // ST1C_4
	int v10; // eax
	//int v11; // ST1C_4
	int v13; // ebx
	int v14; // eax
	int v15; // ecx
	//int v16; // eax
	int v18;     // eax
	BOOLEAN v19; // eax
	int v20;     // ecx
	int v21;     // eax
	//int v22; // ST1C_4
	int v24; // eax
	//int v25; // ST1C_4
	int v26;     // eax
	int v27;     // ecx
	int v28;     // edx
	int v29;     // eax
	int v30;     // [esp+4h] [ebp-18h]
	int v31;     // [esp+8h] [ebp-14h]
	int v1;      // [esp+Ch] [ebp-10h]
	int midir;   // [esp+10h] [ebp-Ch]
	int v2;      // [esp+14h] [ebp-8h]
	int arglist; // [esp+18h] [ebp-4h]

	esi1 = i;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Rhino: Invalid monster %d", i);
	esi3 = &monster[esi1];
	if (esi3->_mmode == MM_STAND && esi3->_msquelch) {
		v3 = esi3->_my;
		v2 = (unsigned char)esi3->_menemyy;
		v4 = v3 - v2;
		v1 = (unsigned char)esi3->_menemyx;
		v5 = esi3->_mx - v1;
		v31 = v3 - v2;
		midir = GetDirection(esi3->_mx, v3, esi3->_lastx, esi3->_lasty);
		if (esi3->_msquelch < 0xFFu) /* check sign */
			MonstCheckDoors(arglist);
		v30 = random(131, 100);
		if (abs(v5) >= 2 || abs(v4) >= 2) {
			if (_LOBYTE(esi3->_mgoal) != MGOAL_MOVE) {
				v7 = abs(v5);
				//v9 = v8;
				if (v7 < 5) {
					v10 = abs(v4);
					//v9 = v11;
					if (v10 < 5)
						goto LABEL_23;
				}
				if (!random(132, 4))
					goto LABEL_23;
				if (_LOBYTE(esi3->_mgoal) != MGOAL_MOVE) {
					esi3->_mgoalvar1 = 0;
					esi3->_mgoalvar2 = random(133, 2);
				}
			}
			_LOBYTE(esi3->_mgoal) = 4;
			v13 = abs(v4);
			if (abs(v5) <= v13) {
				v4 = v31;
				v14 = abs(v31);
			} else {
				v14 = abs(v5);
				v4 = v31;
			}
			v15 = esi3->_mgoalvar1;
			esi3->_mgoalvar1 = v15 + 1;
			if (v15 < 2 * v14 && dTransVal[esi3->_mx][esi3->_my] == dTransVal[v1][v2]) {
				//_LOBYTE(v16) = M_RoundWalk(arglist, midir, &esi3->_mgoalvar2);
				if (!M_RoundWalk(arglist, midir, &esi3->_mgoalvar2)) {
					v18 = random(125, 10);
					M_StartDelay(arglist, v18 + 10);
				}
				goto LABEL_23;
			}
		}
		_LOBYTE(esi3->_mgoal) = MGOAL_NORMAL;
	LABEL_23:
		if (_LOBYTE(esi3->_mgoal) == MGOAL_NORMAL) {
			if ((abs(v5) >= 5 || abs(v4) >= 5)
			    && v30 < 2 * (unsigned char)esi3->_mint + 43
			    && (v19 = LineClearF1(
			            PosOkMonst,
			            arglist,
			            esi3->_mx,
			            esi3->_my,
			            v1,
			            v2),
			           v19)) {
				if (AddMissile(esi3->_mx, esi3->_my, v1, v2, midir, MIS_RHINO, esi3->_menemy, arglist, 0, 0) != -1) {
					if (esi3->MData->snd_special)
						PlayEffect(arglist, 3);
					v20 = esi3->_my + 112 * esi3->_mx;
					esi3->_mmode = MM_CHARGE;
					dMonster[0][v20] = -1 - arglist;
				}
			} else {
				v21 = abs(v5);
				//v23 = v22;
				if (v21 >= 2 || (v24 = abs(v4), v24 >= 2)) /* v23 = v25,  */
				{
					v26 = random(134, 100);
					v27 = 2 * (unsigned char)esi3->_mint;
					if (v26 >= v27 + 33
					    && ((v28 = esi3->_mVar1, v28 != MM_WALK) && v28 != MM_WALK2 && v28 != MM_WALK3
					           || esi3->_mVar2
					           || (v27 += 83, v26 >= v27))) {
						v29 = random(135, 10);
						M_StartDelay(arglist, v29 + 10);
					} else {
						M_CallWalk(arglist, midir);
					}
				} else if (v30 < 2 * (unsigned char)esi3->_mint + 28) {
					esi3->_mdir = midir;
					M_StartAttack(arglist);
				}
			}
		}
		if (esi3->_mmode == MM_STAND)
			esi3->_mAnimData = esi3->MType->Anims[MA_STAND].Data[esi3->_mdir];
	}
}

void MAI_Counselor(int i)
{
	int v1;      // ebx
	int v2;      // esi
	int v3;      // ecx
	int v4;      // edi
	int v5;      // edx
	int v6;      // ebp
	char v9;     // al
	int v10;     // ecx
	BOOLEAN v11; // zf
	BOOLEAN v12; // sf
	//unsigned char v13; // of
	int v14; // edx
	int v15; // ecx
	int v16; // ebx
	int v17; // eax
	int v18; // ebx
	int v19; // edx
	int v20; // ecx
	//int v21; // eax
	int v22; // eax
	//int v23; // ST1C_4
	int v25; // eax
	//int v26; // ST1C_4
	int v27; // edx
	int v28; // eax
	int v29; // eax
	int v30; // ecx
	//int v31; // eax
	int v32;     // eax
	int v33;     // eax
	int v34;     // eax
	int md;      // [esp+8h] [ebp-14h]
	int arglist; // [esp+Ch] [ebp-10h]
	int y2;      // [esp+10h] [ebp-Ch]
	int x2;      // [esp+14h] [ebp-8h]
	int v39;     // [esp+18h] [ebp-4h]

	v1 = i;
	arglist = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Counselor: Invalid monster %d", i);
	v2 = v1;
	if (monster[v1]._mmode == MM_STAND && monster[v2]._msquelch) {
		v3 = monster[v2]._mx;
		x2 = (unsigned char)monster[v2]._menemyx;
		v4 = v3 - x2;
		v5 = monster[v2]._my;
		y2 = (unsigned char)monster[v2]._menemyy;
		v6 = v5 - y2;
		md = GetDirection(v3, v5, monster[v2]._lastx, monster[v2]._lasty);
		if (monster[v2]._msquelch < 0xFFu) /* check sign */
			MonstCheckDoors(v1);
		v39 = random(121, 100);
		v9 = monster[v2]._mgoal;
		if (v9 == MGOAL_RETREAT) {
			v10 = monster[v2]._mgoalvar1;
			//v13 = __OFSUB__(v10, 3);
			v11 = v10 == 3;
			v12 = v10 - 3 < 0;
			v14 = v10 + 1;
			v15 = v1;
			monster[v2]._mgoalvar1 = v14;
			if (v12 | v11) { //if ((unsigned char)(v12 ^ v13) | v11) {
				M_CallWalk(v1, opposite[md]);
				goto LABEL_39;
			}
			goto LABEL_21;
		}
		if (v9 == MGOAL_MOVE) {
			v16 = abs(v6);
			if (abs(v4) <= v16)
				v17 = abs(v6);
			else
				v17 = abs(v4);
			v18 = v17;
			if (abs(v4) < 2 && abs(v6) < 2
			    || monster[v2]._msquelch != -1
			    || dTransVal[monster[v2]._mx][monster[v2]._my] != dTransVal[x2][y2]) {
				v1 = arglist;
			LABEL_20:
				v15 = v1;
			LABEL_21:
				_LOBYTE(monster[v2]._mgoal) = MGOAL_NORMAL;
				M_StartFadein(v15, md, TRUE);
				goto LABEL_39;
			}
			v19 = 2 * v18;
			v1 = arglist;
			v20 = monster[v2]._mgoalvar1;
			monster[v2]._mgoalvar1 = v20 + 1;
			if (v20 >= v19) {
				//_LOBYTE(v21) = DirOK(arglist, md);
				if (DirOK(arglist, md))
					goto LABEL_20;
			}
			M_RoundWalk(arglist, md, &monster[v2]._mgoalvar2);
		LABEL_39:
			if (monster[v2]._mmode == MM_STAND) {
				v34 = random(125, 10);
				M_StartDelay(v1, v34 + 5);
			}
			return;
		}
		if (v9 != MGOAL_NORMAL)
			goto LABEL_39;
		v22 = abs(v4);
		//v24 = v23;
		if (v22 >= 2 || (v25 = abs(v6), v25 >= 2)) /* v24 = v26,  */
		{
			if (v39 < 5 * ((unsigned char)monster[v2]._mint + 10)) {
				//_LOBYTE(v31) = LineClear(monster[v2]._mx, monster[v2]._my, x2, y2);
				if (LineClear(monster[v2]._mx, monster[v2]._my, x2, y2)) {
					v32 = random(
					    77,
					    (unsigned char)monster[v2].mMaxDamage - (unsigned char)monster[v2].mMinDamage + 1);
					M_StartRAttack(
					    v1,
					    (unsigned char)counsmiss[(unsigned char)monster[v2]._mint], /* counsmiss is local */
					    (unsigned char)monster[v2].mMinDamage + v32);
					goto LABEL_39;
				}
			}
			if (random(124, 100) < 30) {
				v27 = md;
				_LOBYTE(monster[v2]._mgoal) = MGOAL_MOVE;
				goto LABEL_29;
			}
		} else {
			v27 = md;
			v28 = monster[v2]._mmaxhp >> 1;
			//v13 = __OFSUB__(monster[v2]._mhitpoints, v28);
			v12 = monster[v2]._mhitpoints - v28 < 0;
			monster[v2]._mdir = md;
			if (v12) { //if (v12 ^ v13) {
				_LOBYTE(monster[v2]._mgoal) = MGOAL_RETREAT;
			LABEL_29:
				monster[v2]._mgoalvar1 = 0;
				M_StartFadeout(v1, v27, FALSE);
				goto LABEL_39;
			}
			if (monster[v2]._mVar1 == MM_DELAY
			    || (v29 = random(105, 100),
			           v30 = 2 * (unsigned char)monster[v2]._mint + 20,
			           v29 < v30)) {
				M_StartRAttack(v1, -1, 0);
				AddMissile(monster[v2]._mx, monster[v2]._my, 0, 0, monster[v2]._mdir, MIS_FLASH, 1, v1, 4, 0);
				AddMissile(monster[v2]._mx, monster[v2]._my, 0, 0, monster[v2]._mdir, MIS_FLASH2, 1, v1, 4, 0);
				goto LABEL_39;
			}
		}
		v33 = random(105, 10);
		M_StartDelay(v1, v33 + 2 * (5 - (unsigned char)monster[v2]._mint));
		goto LABEL_39;
	}
}

void MAI_Garbud(int i)
{
	int _mx, _my, md;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Garbud: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND) {
		return;
	}

	_mx = Monst->_mx;
	_my = Monst->_my;
	md = M_GetDir(i);

	if (Monst->mtalkmsg < QUEST_GARBUD4
	    && Monst->mtalkmsg > QUEST_DOOM10
	    && !(dFlags[_mx][_my] & DFLAG_VISIBLE)
	    && Monst->_mgoal == MGOAL_TALKING) {
		Monst->_mgoal = MGOAL_INQUIRING;
		Monst->mtalkmsg++;
	}

	if (dFlags[_mx][_my] & DFLAG_VISIBLE) {
		if (Monst->mtalkmsg == QUEST_GARBUD4) {
			if (!effect_is_playing(USFX_GARBUD4) && Monst->_mgoal == MGOAL_TALKING) {
				Monst->_mgoal = MGOAL_NORMAL;
				Monst->_msquelch = -1;
				Monst->mtalkmsg = 0;
			}
		}
	}

	if (Monst->_mgoal == MGOAL_NORMAL || Monst->_mgoal == MGOAL_MOVE)
		MAI_Round(i, TRUE);

	monster[i]._mdir = md;

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_Zhar(int i)
{
	int mx, my, _mx, _my, md;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Zhar: Invalid monster %d", i);

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND) {
		return;
	}

	my = Monst->_my;
	mx = Monst->_mx;
	md = M_GetDir(i);
	if (Monst->mtalkmsg == QUEST_ZHAR1 && !(dFlags[mx][my] & DFLAG_VISIBLE) && Monst->_mgoal == MGOAL_TALKING) {
		Monst->mtalkmsg = QUEST_ZHAR2;
		Monst->_mgoal = MGOAL_INQUIRING;
	}

	if (dFlags[mx][my] & DFLAG_VISIBLE) {
		_mx = Monst->_mx - Monst->_menemyx;
		_my = Monst->_my - Monst->_menemyy;
		if (abs(_mx) > abs(_my))
			abs(_mx);
		else
			abs(_my);
		if (Monst->mtalkmsg == QUEST_ZHAR2) {
			if (!effect_is_playing(USFX_ZHAR2) && Monst->_mgoal == MGOAL_TALKING) {
				Monst->_msquelch = -1;
				Monst->mtalkmsg = 0;
				Monst->_mgoal = MGOAL_NORMAL;
			}
		}
	}

	if (Monst->_mgoal == MGOAL_NORMAL || Monst->_mgoal == MGOAL_RETREAT || Monst->_mgoal == MGOAL_MOVE)
		MAI_Counselor(i);

	Monst->_mdir = md;

	if (monster[i]._mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_SnotSpil(int i)
{
	int mx, my, md;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_SnotSpil: Invalid monster %d", i);

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	md = M_GetDir(i);

	if (Monst->mtalkmsg == QUEST_BANNER10 && !(dFlags[mx][my] & DFLAG_VISIBLE) && Monst->_mgoal == MGOAL_TALKING) {
		Monst->mtalkmsg = QUEST_BANNER11;
		Monst->_mgoal = MGOAL_INQUIRING;
	}

	if (Monst->mtalkmsg == QUEST_BANNER11 && quests[QTYPE_BOL]._qvar1 == 3) {
		Monst->mtalkmsg = 0;
		Monst->_mgoal = MGOAL_NORMAL;
	}

	if (dFlags[mx][my] & DFLAG_VISIBLE) {
		if (Monst->mtalkmsg == QUEST_BANNER12) {
			if (!effect_is_playing(USFX_SNOT3) && Monst->_mgoal == MGOAL_TALKING) {
				ObjChangeMap(setpc_x, setpc_y, setpc_w + setpc_x + 1, setpc_h + setpc_y + 1);
				quests[QTYPE_BOL]._qvar1 = 3;
				RedoPlayerVision();
				Monst->_msquelch = -1;
				Monst->mtalkmsg = 0;
				Monst->_mgoal = MGOAL_NORMAL;
			}
		}
		if (quests[QTYPE_BOL]._qvar1 == 3) {
			if (Monst->_mgoal == MGOAL_NORMAL || Monst->_mgoal == MGOAL_SHOOT)
				MAI_Fallen(i);
		}
	}

	Monst->_mdir = md;

	if (monster[i]._mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

void MAI_Lazurus(int i)
{
	int mx, my, md;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Lazurus: Invalid monster %d", i);

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	md = M_GetDir(i);
	if (dFlags[mx][my] & DFLAG_VISIBLE) {
		if (gbMaxPlayers == 1) {
			if (Monst->mtalkmsg == QUEST_VILE13 && Monst->_mgoal == MGOAL_INQUIRING && plr[myplr].WorldX == QUEST_VILE13 && plr[myplr].WorldY == 46) {
				PlayInGameMovie("gendata\\fprst3.smk");
				Monst->_mmode = MM_TALK;
				quests[QTYPE_VB]._qvar1 = 5;
			}

			if (Monst->mtalkmsg == QUEST_VILE13 && !effect_is_playing(USFX_LAZ1) && Monst->_mgoal == MGOAL_TALKING) {
				ObjChangeMapResync(1, 18, 20, 24);
				RedoPlayerVision();
				Monst->_msquelch = -1;
				Monst->mtalkmsg = 0;
				quests[QTYPE_VB]._qvar1 = 6;
				Monst->_mgoal = MGOAL_NORMAL;
			}
		}

		if (gbMaxPlayers != 1 && Monst->mtalkmsg == QUEST_VILE13 && Monst->_mgoal == MGOAL_INQUIRING && quests[QTYPE_VB]._qvar1 <= 3) {
			Monst->_mmode = MM_TALK;
		}
	}

	if (Monst->_mgoal == MGOAL_NORMAL || Monst->_mgoal == MGOAL_RETREAT || Monst->_mgoal == MGOAL_MOVE) {
		Monst->mtalkmsg = 0;
		MAI_Counselor(i);
	}

	Monst->_mdir = md;

	if (monster[i]._mmode == MM_STAND || monster[i]._mmode == MM_TALK)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}
// 679660: using guessed type char gbMaxPlayers;

void MAI_Lazhelp(int i)
{
	int v1; // esi
	int v2; // esi
	int v3; // ebx
	int v4; // edi
	int v5; // [esp+4h] [ebp-8h]
	int ia; // [esp+8h] [ebp-4h]

	v1 = i;
	ia = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Lazhelp: Invalid monster %d", i);
	v2 = v1;
	if (monster[v2]._mmode == MM_STAND) {
		v3 = monster[v2]._my;
		v4 = monster[v2]._mx;
		v5 = M_GetDir(ia);
		if (dFlags[v4][v3] & DFLAG_VISIBLE) {
			if (gbMaxPlayers == 1) {
				if (quests[QTYPE_VB]._qvar1 <= 5u) {
					_LOBYTE(monster[v2]._mgoal) = MGOAL_INQUIRING;
					goto LABEL_10;
				}
				monster[v2].mtalkmsg = 0;
			}
			_LOBYTE(monster[v2]._mgoal) = MGOAL_NORMAL;
		}
	LABEL_10:
		if (_LOBYTE(monster[v2]._mgoal) == MGOAL_NORMAL)
			MAI_Succ(ia);
		monster[v2]._mdir = v5;
		if (monster[v2]._mmode == MM_STAND)
			monster[v2]._mAnimData = monster[v2].MType->Anims[MA_STAND].Data[v5];
	}
}
// 679660: using guessed type char gbMaxPlayers;

void MAI_Lachdanan(int i)
{
	int _mx, _my, md;
	MonsterStruct *Monst;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Lachdanan: Invalid monster %d", i);

	Monst = &monster[i];
	if (Monst->_mmode != MM_STAND) {
		return;
	}

	_mx = Monst->_mx;
	_my = Monst->_my;
	md = M_GetDir(i);
	if (Monst->mtalkmsg == QUEST_VEIL9 && !(dFlags[_mx][_my] & DFLAG_VISIBLE) && Monst->_mgoal == MGOAL_TALKING) {
		Monst->mtalkmsg = QUEST_VEIL10;
		Monst->_mgoal = MGOAL_INQUIRING;
	}

	if (dFlags[_mx][_my] & DFLAG_VISIBLE) {
		if (Monst->mtalkmsg == QUEST_VEIL11) {
			if (!effect_is_playing(USFX_LACH3) && Monst->_mgoal == MGOAL_TALKING) {
				Monst->mtalkmsg = 0;
				quests[QTYPE_VEIL]._qactive = 3;
				M_StartKill(i, -1);
			}
		}
	}

	Monst->_mdir = md;

	if (Monst->_mmode == MM_STAND)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[md];
}

void MAI_Warlord(int i)
{
	MonsterStruct *Monst;
	int mx, my, md;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("MAI_Warlord: Invalid monster %d", i);

	Monst = &monster[i];
	if (monster[i]._mmode != MM_STAND) {
		return;
	}

	mx = Monst->_mx;
	my = Monst->_my;
	md = M_GetDir(i);
	if (dFlags[mx][my] & DFLAG_VISIBLE) {
		if (Monst->mtalkmsg == QUEST_WARLRD9 && Monst->_mgoal == MGOAL_INQUIRING)
			Monst->_mmode = MM_TALK;
		if (Monst->mtalkmsg == QUEST_WARLRD9 && !effect_is_playing(USFX_WARLRD1) && Monst->_mgoal == MGOAL_TALKING) {
			Monst->_msquelch = -1;
			Monst->mtalkmsg = 0;
			Monst->_mgoal = MGOAL_NORMAL;
		}
	}

	if (Monst->_mgoal == MGOAL_NORMAL)
		MAI_SkelSd(i);

	Monst->_mdir = md;

	if (monster[i]._mmode == MM_STAND || monster[i]._mmode == MM_TALK)
		Monst->_mAnimData = Monst->MType->Anims[MA_STAND].Data[Monst->_mdir];
}

void DeleteMonsterList()
{
	int i;
	for (i = 0; i < MAX_PLRS; i++) {
		if (monster[i]._mDelFlag) {
			monster[i]._mx = 1;
			monster[i]._my = 0;
			monster[i]._mfutx = 0;
			monster[i]._mfuty = 0;
			monster[i]._moldx = 0;
			monster[i]._moldy = 0;
			monster[i]._mDelFlag = FALSE;
		}
	}

	i = MAX_PLRS;
	while (i < nummonsters) {
		if (monster[monstactive[i]]._mDelFlag) {
			DeleteMonster(i);
			i = 0; // TODO: check if this should be i=4.
		} else {
			i++;
		}
	}
}

void ProcessMonsters()
{
	int v0;          // edi
	int v1;          // esi
	int v2;          // ecx
	int v3;          // eax
	char *v4;        // ebx
	unsigned int v5; // eax
	int v6;          // eax
	int v7;          // edx
	int v8;          // eax
	unsigned int v9; // eax
	int v10;         // eax
	BOOLEAN v11;     // zf
	char *v12;       // ecx
	char *v13;       // eax
	int v14;         // ecx
	int v15;         // eax
	char v16;        // al
	int v17;         // ecx
	BOOLEAN v18;     // eax
	int v19;         // eax
	int v20;         // ecx
	int *v21;        // eax
	int *v22;        // eax
	int v23;         // [esp+0h] [ebp-Ch]
	int v24;         // [esp+4h] [ebp-8h]
	int v25;         // [esp+8h] [ebp-4h]

	DeleteMonsterList();
	v24 = 0;
	if (nummonsters <= 0)
		goto LABEL_60;
	do {
		v25 = 0;
		v23 = monstactive[v24];
		v0 = v23;
		v1 = v23;
		if ((unsigned char)gbMaxPlayers > 1u) {
			SetRndSeed(monster[v1]._mAISeed);
			monster[v1]._mAISeed = GetRndSeed();
		}
		if (!(monster[v1]._mFlags & MFLAG_NOHEAL)) {
			v2 = monster[v1]._mhitpoints;
			if (v2 < monster[v1]._mmaxhp && v2 >> 6 > 0) {
				v3 = SLOBYTE(monster[v1].mLevel);
				if ((char)v3 > 1)
					v3 = (char)v3 >> 1;
				monster[v1]._mhitpoints = v2 + v3;
			}
		}
		v4 = &dFlags[monster[v1]._mx][monster[v1]._my];
		if (*v4 & DFLAG_VISIBLE && !monster[v1]._msquelch && monster[v1].MType->mtype == MT_CLEAVER)
			PlaySFX(USFX_CLEAVER);
		if (monster[v1]._mFlags & MFLAG_TARGETS_MONSTER) {
			v5 = monster[v1]._menemy;
			if (v5 >= MAXMONSTERS)
				app_fatal("Illegal enemy monster %d for monster \"%s\"", v5, monster[v1].mName);
			v6 = monster[v1]._menemy;
			v7 = monster[v6]._mfutx;
			monster[v1]._lastx = v7;
			monster[v1]._menemyx = v7;
			v8 = monster[v6]._mfuty;
			monster[v1]._menemyy = v8;
			monster[v1]._lasty = v8;
		} else {
			v9 = monster[v1]._menemy;
			if (v9 >= MAX_PLRS)
				app_fatal("Illegal enemy player %d for monster \"%s\"", v9, monster[v1].mName);
			v10 = monster[v1]._menemy;
			v11 = (*v4 & DFLAG_VISIBLE) == 0;
			v12 = (char *)&plr[v10]._px;
			v13 = (char *)&plr[v10]._py;
			monster[v1]._menemyx = *v12;
			monster[v1]._menemyy = *v13;
			if (v11) {
				v16 = monster[v1]._msquelch;
				if (v16 && monster[v1]._mAi != MT_DIABLO) /// BUGFIX: test `MT_DIABLO` with 'MType->mtype' instead of '_mAi'
					monster[v1]._msquelch = v16 - 1;
			} else {
				v14 = *(_DWORD *)v12;
				v15 = *(_DWORD *)v13;
				monster[v1]._msquelch = -1;
				monster[v1]._lastx = v14;
				monster[v1]._lasty = v15;
			}
			v0 = v23;
		}
		while (1) {
			v17 = v0;
			if (monster[v1]._mFlags & MFLAG_SEARCH) {
				v18 = MAI_Path(v0);
				if (v18)
					goto LABEL_30;
				v17 = v0;
			}
			AiProc[(unsigned char)monster[v1]._mAi](v17);
		LABEL_30:
			switch (monster[v1]._mmode) {
			case MM_STAND:
				v19 = M_DoStand(v0);
				goto LABEL_48;
			case MM_WALK:
				v19 = M_DoWalk(v0);
				goto LABEL_48;
			case MM_WALK2:
				v19 = M_DoWalk2(v0);
				goto LABEL_48;
			case MM_WALK3:
				v19 = M_DoWalk3(v0);
				goto LABEL_48;
			case MM_ATTACK:
				v19 = M_DoAttack(v0);
				goto LABEL_48;
			case MM_GOTHIT:
				v19 = M_DoGotHit(v0);
				goto LABEL_48;
			case MM_DEATH:
				v19 = M_DoDeath(v0);
				goto LABEL_48;
			case MM_SATTACK:
				v19 = M_DoSAttack(v0);
				goto LABEL_48;
			case MM_FADEIN:
				v19 = M_DoFadein(v0);
				goto LABEL_48;
			case MM_FADEOUT:
				v19 = M_DoFadeout(v0);
				goto LABEL_48;
			case MM_RATTACK:
				v19 = M_DoRAttack(v0);
				goto LABEL_48;
			case MM_SPSTAND:
				v19 = M_DoSpStand(v0);
				goto LABEL_48;
			case MM_RSPATTACK:
				v19 = M_DoRSpAttack(v0);
				goto LABEL_48;
			case MM_DELAY:
				v19 = M_DoDelay(v0);
				goto LABEL_48;
			case MM_CHARGE:
				goto LABEL_51;
			case MM_STONE:
				v19 = M_DoStone(v0);
				goto LABEL_48;
			case MM_HEAL:
				v19 = M_DoHeal(v0);
				goto LABEL_48;
			case MM_TALK:
				v19 = M_DoTalk(v0);
			LABEL_48:
				v25 = v19;
				break;
			}
			if (!v25)
				break;
			GroupUnity(v0);
		}
	LABEL_51:
		if (monster[v1]._mmode != MM_STONE) {
			v20 = monster[v1]._mFlags;
			v21 = &monster[v1]._mAnimCnt;
			++*v21;
			if (!(v20 & MFLAG_ALLOW_SPECIAL) && monster[v1]._mAnimCnt >= monster[v1]._mAnimDelay) {
				*v21 = 0;
				v22 = &monster[v1]._mAnimFrame;
				if (v20 & MFLAG_LOCK_ANIMATION) {
					v11 = (*v22)-- == 1;
					if (v11)
						*v22 = monster[v1]._mAnimLen;
				} else if (++*v22 > monster[v1]._mAnimLen) {
					*v22 = 1;
				}
			}
		}
		++v24;
	} while (v24 < nummonsters);
LABEL_60:
	DeleteMonsterList();
}
// 679660: using guessed type char gbMaxPlayers;

void FreeMonsters()
{
	int mtype;
	int i, j;

	for (i = 0; i < nummtypes; i++) {
		mtype = Monsters[i].mtype;
		for (j = 0; j < 6; j++) {
			if (animletter[j] != 's' || monsterdata[mtype].has_special) {
				MemFreeDbg(Monsters[i].Anims[j].CMem);
			}
		}
	}

	FreeMissiles2();
}

BOOL DirOK(int i, int mdir)
{
	int v2;             // ebx
	int v3;             // esi
	int v4;             // ebx
	int v5;             // edi
	int v6;             // esi
	int v7;             // edi
	BOOLEAN v8;         // zf
	int v9;             // edx
	unsigned char *v11; // ebx
	unsigned char v12;  // al
	int v13;            // edx
	int v14;            // eax
	int v15;            // edi
	int v16;            // ecx
	signed int j;       // esi
	int v18;            // eax
	BOOLEAN v19;        // zf
	int v20;            // eax
	int v21;            // [esp+Ch] [ebp-14h]
	int v22;            // [esp+10h] [ebp-10h]
	int v23;            // [esp+14h] [ebp-Ch]
	int a1;             // [esp+18h] [ebp-8h]
	int v25;            // [esp+1Ch] [ebp-4h]
	int v26;            // [esp+1Ch] [ebp-4h]

	v2 = i;
	v3 = mdir;
	v25 = mdir;
	a1 = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("DirOK: Invalid monster %d", i);
	v4 = v2;
	v5 = offset_y[v3];
	v6 = monster[v4]._mx + offset_x[v3];
	v7 = monster[v4]._my + v5;
	if (v7 < 0 || v7 >= MAXDUNY || v6 < 0 || v6 >= MAXDUNX || !PosOkMonst(a1, v6, v7))
		return 0;
	if (v25 == DIR_E) {
		if (!SolidLoc(v6, v7 + 1)) {
			v8 = (dFlags[v6][v7 + 1] & DFLAG_MONSTER) == 0;
			goto LABEL_18;
		}
		return 0;
	}
	if (v25 == DIR_W) {
		if (SolidLoc(v6 + 1, v7))
			return 0;
		v8 = (dFlags[v6 + 1][v7] & DFLAG_MONSTER) == 0;
	} else {
		if (v25 == DIR_N) {
			if (SolidLoc(v6 + 1, v7))
				return 0;
			v9 = v7 + 1;
		} else {
			if (v25)
				goto LABEL_24;
			if (SolidLoc(v6 - 1, v7))
				return 0;
			v9 = v7 - 1;
		}
		v8 = SolidLoc(v6, v9) == 0;
	}
LABEL_18:
	if (!v8)
		return 0;
LABEL_24:
	if (monster[v4].leaderflag == 1) {
		v11 = &monster[v4].leader;
		if (abs(v6 - monster[(unsigned char)*v11]._mfutx) >= 4
		    || abs(v7 - monster[(unsigned char)*v11]._mfuty) >= 4) {
			return 0;
		}
		return 1;
	}
	v12 = monster[v4]._uniqtype;
	if (v12 == 0 || !(UniqMonst[v12 - 1].mUnqAttr & 2))
		return 1;
	v26 = 0;
	v13 = v6 - 3;
	v21 = v6 + 3;
	if (v6 - 3 <= v6 + 3) {
		v14 = v7 - 3;
		v15 = v7 + 3;
		v23 = v14;
		v22 = v15;
		v16 = 112 * v13;
		do {
			for (j = v23; j <= v15; ++j) {
				if (j >= 0 && j < MAXDUNY && v16 >= 0 && v16 < MAXDUNX * 112) {
					v18 = dMonster[0][v16 + j];
					v19 = v18 == 0;
					if (v18 < 0) {
						v18 = -v18;
						v19 = v18 == 0;
					}
					if (!v19)
						--v18;
					v20 = v18;
					if (monster[v20].leaderflag == 1
					    && (unsigned char)monster[v20].leader == a1
					    && monster[v20]._mfutx == v13
					    && monster[v20]._mfuty == j) {
						++v26;
					}
				}
				v15 = v22;
			}
			++v13;
			v16 += 112;
		} while (v13 <= v21);
	}
	return v26 == (unsigned char)monster[v4].packsize;
}

BOOL PosOkMissile(int x, int y)
{
	return !nMissileTable[dPiece[x][y]] && !(dFlags[x][y] & DFLAG_MONSTER);
}

BOOL CheckNoSolid(int x, int y)
{
	return nSolidTable[dPiece[x][y]] == 0;
}

BOOL LineClearF(BOOL(*Clear)(int, int), int x1, int y1, int x2, int y2)
{
	int v5;         // esi
	int v6;         // edi
	int v7;         // ebx
	int v8;         // eax
	int v9;         // eax
	int v10;        // eax
	int v11;        // ebx
	int v12;        // esi
	signed int v13; // edi
	int v14;        // edx
	int v15;        // ecx
	int v16;        // eax
	int v17;        // eax
	int v18;        // eax
	int v19;        // ebx
	int v20;        // edi
	signed int v21; // esi
	int v22;        // ecx
	int v25;        // [esp+10h] [ebp-10h]
	int v26;        // [esp+14h] [ebp-Ch]
	int v27;        // [esp+18h] [ebp-8h]
	int v28;        // [esp+18h] [ebp-8h]
	int v29;        // [esp+1Ch] [ebp-4h]

	v5 = y2 - y1;
	v29 = x1;
	v25 = x1;
	v26 = y1;
	v6 = x2 - x1;
	v7 = abs(y2 - y1);
	if (abs(v6) <= v7) {
		if (v5 < 0) {
			v16 = y1;
			y1 = y2;
			y2 = v16;
			v17 = v29;
			v5 = -v5;
			v29 = x2;
			x2 = v17;
			v6 = -v6;
		}
		v18 = 2 * v6;
		v28 = 2 * v6;
		if (v6 <= 0) {
			v19 = v18 + v5;
			v20 = 2 * (v5 + v6);
			v21 = -1;
		} else {
			v19 = v18 - v5;
			v20 = 2 * (v6 - v5);
			v21 = 1;
		}
		while (1) {
			v22 = v29;
			if (y1 == y2 && v29 == x2)
				break;
			if (v19 <= 0 == v21 < 0) {
				v19 += v20;
				v22 = v21 + v29;
				v29 += v21;
			} else {
				v19 += v28;
			}
			if ((++y1 != v26 || v22 != v25) && !Clear(v22, y1)) /* check args */
				goto LABEL_29;
		}
	} else {
		if (v6 < 0) {
			v8 = v29;
			v29 = x2;
			x2 = v8;
			v9 = y1;
			v6 = -v6;
			y1 = y2;
			y2 = v9;
			v5 = -v5;
		}
		v10 = 2 * v5;
		v27 = 2 * v5;
		if (v5 <= 0) {
			v11 = v10 + v6;
			v12 = 2 * (v6 + v5);
			v13 = -1;
		} else {
			v11 = v10 - v6;
			v12 = 2 * (v5 - v6);
			v13 = 1;
		}
		do {
			v14 = y1;
			if (v29 == x2 && y1 == y2)
				break;
			if (v11 <= 0 == v13 < 0) {
				v11 += v12;
				v14 = v13 + y1;
				y1 += v13;
			} else {
				v11 += v27;
			}
			v15 = v29 + 1;
		} while (++v29 == v25 && v14 == v26 || Clear(v15, v14));
	LABEL_29:
		if (v29 != x2)
			return 0;
	}
	if (y1 == y2)
		return 1;
	return 0;
}

BOOL LineClear(int x1, int y1, int x2, int y2)
{
	return LineClearF(PosOkMissile, x1, y1, x2, y2);
}

BOOL LineClearF1(BOOL(*Clear)(int, int, int), int monst, int x1, int y1, int x2, int y2)
{
	int v6;         // esi
	int v7;         // edi
	int v8;         // ebx
	int v9;         // eax
	int v10;        // eax
	int v11;        // eax
	int v12;        // ebx
	int v13;        // esi
	signed int v14; // edi
	int v15;        // eax
	int v16;        // eax
	int v17;        // eax
	int v18;        // eax
	int v19;        // ebx
	int v20;        // edi
	signed int v21; // esi
	int v22;        // edx
	int v25;        // [esp+10h] [ebp-10h]
	int v26;        // [esp+14h] [ebp-Ch]
	int v27;        // [esp+18h] [ebp-8h]
	int v28;        // [esp+1Ch] [ebp-4h]
	int v29;        // [esp+1Ch] [ebp-4h]

	v6 = y2 - y1;
	v25 = monst;
	v26 = x1;
	v27 = y1;
	v7 = x2 - x1;
	v8 = abs(y2 - y1);
	if (abs(x2 - x1) <= v8) {
		if (v6 < 0) {
			v16 = y1;
			y1 = y2;
			y2 = v16;
			v17 = x1;
			v6 = -v6;
			x1 = x2;
			x2 = v17;
			v7 = -v7;
		}
		v18 = 2 * v7;
		v29 = 2 * v7;
		if (v7 <= 0) {
			v19 = v18 + v6;
			v20 = 2 * (v6 + v7);
			v21 = -1;
		} else {
			v19 = v18 - v6;
			v20 = 2 * (v7 - v6);
			v21 = 1;
		}
		while (1) {
			v22 = x1;
			if (y1 == y2 && x1 == x2)
				break;
			if (v19 <= 0 == v21 < 0) {
				v19 += v20;
				v22 = v21 + x1;
				x1 += v21;
			} else {
				v19 += v29;
			}
			if ((++y1 != v27 || v22 != v26) && !Clear(v25, v22, y1))
				goto LABEL_29;
		}
	} else {
		if (v7 < 0) {
			v9 = x1;
			x1 = x2;
			x2 = v9;
			v10 = y1;
			v7 = -v7;
			y1 = y2;
			y2 = v10;
			v6 = -v6;
		}
		v11 = 2 * v6;
		v28 = 2 * v6;
		if (v6 <= 0) {
			v12 = v11 + v7;
			v13 = 2 * (v7 + v6);
			v14 = -1;
		} else {
			v12 = v11 - v7;
			v13 = 2 * (v6 - v7);
			v14 = 1;
		}
		do {
			v15 = y1;
			if (x1 == x2 && y1 == y2)
				break;
			if (v12 <= 0 == v14 < 0) {
				v12 += v13;
				v15 = v14 + y1;
				y1 += v14;
			} else {
				v12 += v28;
			}
		} while (++x1 == v26 && v15 == v27 || Clear(v25, x1, v15)); /* check args */
	LABEL_29:
		if (x1 != x2)
			return 0;
	}
	if (y1 == y2)
		return 1;
	return 0;
}

void SyncMonsterAnim(int i)
{
	int v1;             // esi
	int v2;             // eax
	int v3;             // edx
	MonsterData *v4;    // esi
	CMonster *v5;       // ecx
	unsigned char v6;   // dl
	char *v7;           // edx
	int v8;             // esi
	int v9;             // edx
	unsigned char *v10; // ecx
	unsigned char *v11; // edx
	int v12;            // ecx
	unsigned char *v13; // edx

	v1 = i;
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("SyncMonsterAnim: Invalid monster %d", i);
	v2 = v1;
	v3 = monster[v1]._mMTidx;
	v4 = Monsters[v3].MData;
	v5 = &Monsters[v3];
	v6 = monster[v2]._uniqtype;
	monster[v2].MType = v5;
	monster[v2].MData = v4;
	if (v6 != 0)
		v7 = UniqMonst[v6 - 1].mName;
	else
		v7 = v4->mName;
	v8 = monster[v2]._mmode;
	monster[v2].mName = v7;
	v9 = monster[v2]._mdir;
	switch (v8) {
	case MM_STAND:
	case MM_DELAY:
	case MM_TALK:
		v10 = v5->Anims[MA_STAND].Data[v9];
		goto LABEL_13;
	case MM_WALK:
	case MM_WALK2:
	case MM_WALK3:
		v10 = v5->Anims[MA_WALK].Data[v9];
		goto LABEL_13;
	case MM_ATTACK:
	case MM_RATTACK:
		v10 = v5->Anims[MA_ATTACK].Data[v9];
		goto LABEL_13;
	case MM_GOTHIT:
		v10 = v5->Anims[MA_GOTHIT].Data[v9];
		goto LABEL_13;
	case MM_DEATH:
		v10 = v5->Anims[MA_DEATH].Data[v9];
		goto LABEL_13;
	case MM_SATTACK:
	case MM_FADEIN:
	case MM_FADEOUT:
	case MM_SPSTAND:
	case MM_RSPATTACK:
	case MM_HEAL:
		v10 = v5->Anims[MA_SPECIAL].Data[v9];
	LABEL_13:
		monster[v2]._mAnimData = v10;
		return;
	case MM_CHARGE:
		v11 = v5->Anims[MA_ATTACK].Data[v9];
		monster[v2]._mAnimFrame = 1;
		monster[v2]._mAnimData = v11;
		v12 = v5->Anims[MA_ATTACK].Frames;
		break;
	default:
		v13 = v5->Anims[MA_STAND].Data[v9];
		monster[v2]._mAnimFrame = 1;
		monster[v2]._mAnimData = v13;
		v12 = v5->Anims[MA_STAND].Frames;
		break;
	}
	monster[v2]._mAnimLen = v12;
}

void M_FallenFear(int x, int y)
{
	int v2;         // eax
	int *v3;        // ebx
	int v4;         // edi
	int v5;         // esi
	signed int v6;  // eax
	int v7;         // eax
	BOOLEAN v8;     // zf
	int v9;         // eax
	int v10;        // eax
	signed int v11; // [esp-10h] [ebp-1Ch]
	int v12;        // [esp+0h] [ebp-Ch]
	int x1;         // [esp+4h] [ebp-8h]
	int y1;         // [esp+8h] [ebp-4h]

	v2 = 0;
	y1 = y;
	x1 = x;
	v12 = 0;
	if (nummonsters > 0) {
		v3 = &monster[0]._mx;
		do {
			v4 = 0;
			v5 = monstactive[v2];
			v6 = monster[v5].MType->mtype;
			if (v6 > MT_RFALLSD) {
				v9 = v6 - 13;
				v8 = v9 == 0;
			} else {
				if (v6 == MT_RFALLSD || (v7 = v6 - 4) == 0) {
					v11 = 7;
					goto LABEL_15;
				}
				v9 = v7 - 1;
				v8 = v9 == 0;
			}
			if (v8) {
				v11 = 5;
			} else {
				v10 = v9 - 1;
				if (v10) {
					if (v10 != 1)
						goto LABEL_16;
					v11 = 2;
				} else {
					v11 = 3;
				}
			}
		LABEL_15:
			v4 = v11;
		LABEL_16:
			if (monster[v5]._mAi == AI_FALLEN
			    && v4
			    && abs(x1 - monster[v5]._mx) < 5
			    && abs(y1 - monster[v5]._my) < 5
			    && monster[v5]._mhitpoints >> 6 > 0) {
				_LOBYTE(monster[v5]._mgoal) = MGOAL_RETREAT;
				monster[v5]._mgoalvar1 = v4;
				monster[v5]._mdir = GetDirection(x1, y1, *v3, v3[1]);
			}
			v3 += 57;
			v2 = v12++ + 1;
		} while (v12 < nummonsters);
	}
}

void PrintMonstHistory(int mt)
{
	int v1;   // edi
	int *v2;  // ebx
	int v3;   // ecx
	int v4;   // eax
	int v5;   // edi
	short v6; // bx
	int v7;   // ebx

	v1 = mt;
	v2 = &monstkills[mt];
	sprintf(tempstr, "Total kills : %i", *v2);
	AddPanelString(tempstr, 1);
	if (*v2 >= 30) {
		v3 = monsterdata[v1].mMinHP;
		v4 = monsterdata[v1].mMaxHP;
		if (gbMaxPlayers == 1) {
			v3 = monsterdata[v1].mMinHP >> 1;
			v4 = monsterdata[v1].mMaxHP >> 1;
		}
		if (v3 < 1)
			v3 = 1;
		if (v4 < 1)
			v4 = 1;
		if (gnDifficulty == DIFF_NIGHTMARE) {
			v3 = 3 * v3 + 1;
			v4 = 3 * v4 + 1;
		}
		if (gnDifficulty == DIFF_HELL) {
			v3 = 4 * v3 + 3;
			v4 = 4 * v4 + 3;
		}
		sprintf(tempstr, "Hit Points : %i-%i", v3, v4);
		AddPanelString(tempstr, 1);
	}
	if (*v2 >= 15) {
		v5 = v1 << 7;
		if (gnDifficulty == DIFF_HELL)
			v6 = *(short *)((char *)&monsterdata[0].mMagicRes2 + v5);
		else
			v6 = *(short *)((char *)&monsterdata[0].mMagicRes + v5);
		v7 = v6 & (RESIST_MAGIC | RESIST_FIRE | RESIST_LIGHTNING | IMUNE_MAGIC | IMUNE_FIRE | IMUNE_LIGHTNING);
		if (v7) {
			if (v7 & (RESIST_MAGIC | RESIST_FIRE | RESIST_LIGHTNING)) {
				strcpy(tempstr, "Resists : ");
				if (v7 & RESIST_MAGIC)
					strcat(tempstr, "Magic ");
				if (v7 & RESIST_FIRE)
					strcat(tempstr, "Fire ");
				if (v7 & RESIST_LIGHTNING)
					strcat(tempstr, "Lightning ");
				tempstr[strlen(tempstr) - 1] = '\0';
				AddPanelString(tempstr, 1);
			}
			if (v7 & (IMUNE_MAGIC | IMUNE_FIRE | IMUNE_LIGHTNING)) {
				strcpy(tempstr, "Immune : ");
				if (v7 & IMUNE_MAGIC)
					strcat(tempstr, "Magic ");
				if (v7 & IMUNE_FIRE)
					strcat(tempstr, "Fire ");
				if (v7 & IMUNE_LIGHTNING)
					strcat(tempstr, "Lightning ");
				tempstr[strlen(tempstr) - 1] = '\0';
				AddPanelString(tempstr, 1);
			}
		} else {
			strcpy(tempstr, "No magic resistance");
			AddPanelString(tempstr, 1);
		}
	}
	pinfoflag = 1;
}
// 4B8824: using guessed type int pinfoflag;
// 679660: using guessed type char gbMaxPlayers;

void PrintUniqueHistory()
{
	char v0; // bl

	v0 = monster[pcursmonst].mMagicRes & (RESIST_MAGIC | RESIST_FIRE | RESIST_LIGHTNING | IMUNE_MAGIC | IMUNE_FIRE | IMUNE_LIGHTNING);
	if (v0) {
		if (monster[pcursmonst].mMagicRes & (RESIST_MAGIC | RESIST_FIRE | RESIST_LIGHTNING))
			strcpy(tempstr, "Some Magic Resistances");
		else
			strcpy(tempstr, "No resistances");
		AddPanelString(tempstr, 1);
		if (v0 & (IMUNE_MAGIC | IMUNE_FIRE | IMUNE_LIGHTNING)) {
			strcpy(tempstr, "Some Magic Immunities");
			goto LABEL_4;
		}
	} else {
		strcpy(tempstr, "No resistances");
		AddPanelString(tempstr, 1);
	}
	strcpy(tempstr, "No Immunities");
LABEL_4:
	AddPanelString(tempstr, 1);
	pinfoflag = 1;
}
// 4B8824: using guessed type int pinfoflag;

void MissToMonst(int i, int x, int y)
{
	int v3;            // edi
	MissileStruct *v4; // edi
	unsigned int v5;   // ebx
	MonsterStruct *v6; // esi
	int v7;            // edx
	char v8;           // al
	int v9;            // eax
	char *v10;         // edi
	int v11;           // eax
	int v12;           // edx
	char v13;          // al
	char v14;          // al
	int v15;           // ebx
	int v16;           // eax
	int v17;           // esi
	int v18;           // edi
	int v19;           // esi
	int v20;           // edx
	int *v21;          // ebx
	char v22;          // cl
	char v23;          // al
	int v24;           // esi
	int v25;           // edi
	int v26;           // esi
	int v27;           // eax
	int v28;           // eax
	int ia;            // [esp+Ch] [ebp-10h]
	int v30;           // [esp+10h] [ebp-Ch]
	int v31;           // [esp+14h] [ebp-8h]
	int v32;           // [esp+18h] [ebp-4h]
	int arglist;       // [esp+24h] [ebp+8h]

	v3 = i;
	v30 = x;
	if ((DWORD)i >= MAXMISSILES)
		app_fatal("MissToMonst: Invalid missile %d", i);
	v4 = &missile[v3];
	v5 = v4->_misource;
	ia = v4->_misource;
	if (v5 >= MAXMONSTERS)
		app_fatal("MissToMonst: Invalid monster %d", v5);
	v32 = v4->_mix;
	v31 = v4->_miy;
	v6 = &monster[v5];
	v6->_mx = v30;
	dMonster[v30][y] = v5 + 1;
	v7 = v4->_mimfnum;
	v6->_mdir = v7;
	v6->_my = y;
	M_StartStand(v5, v7);
	v8 = v6->MType->mtype;
	if (v8 < MT_INCIN || v8 > MT_HELLBURN) {
		if (v6->_mFlags & MFLAG_TARGETS_MONSTER)
			M2MStartHit(v5, -1, 0);
		else
			M_StartHit(v5, -1, 0);
	} else {
		M_StartFadein(v5, v6->_mdir, FALSE);
	}
	v9 = v32;
	if (v6->_mFlags & MFLAG_TARGETS_MONSTER) {
		v21 = (int *)((char *)dMonster + 4 * (v31 + v9 * 112));
		if (*v21 > 0) {
			v22 = v6->MType->mtype;
			if (v22 != MT_GLOOM && (v22 < MT_INCIN || v22 > MT_HELLBURN)) {
				M_TryM2MHit(ia, *v21 - 1, 500, (unsigned char)v6->mMinDamage2, (unsigned char)v6->mMaxDamage2);
				v23 = v6->MType->mtype;
				if (v23 < MT_NSNAKE || v23 > MT_GSNAKE) {
					v24 = v6->_mdir;
					v25 = v32 + offset_x[v24];
					v26 = v31 + offset_y[v24];
					if (PosOkMonst(*v21 - 1, v25, v26)) {
						v27 = *v21;
						dMonster[v25][v26] = *v21;
						*v21 = 0;
						v28 = v27 - 1;
						monster[v28]._mx = v25;
						monster[v28]._mfutx = v25;
						monster[v28]._my = v26;
						monster[v28]._mfuty = v26;
					}
				}
			}
		}
	} else {
		v10 = &dPlayer[v9][v31];
		v11 = *v10;
		v12 = v11 - 1;
		arglist = v11 - 1;
		if (*v10 > 0) {
			v13 = v6->MType->mtype;
			if (v13 != MT_GLOOM && (v13 < MT_INCIN || v13 > MT_HELLBURN)) {
				M_TryH2HHit(v5, v12, 500, (unsigned char)v6->mMinDamage2, (unsigned char)v6->mMaxDamage2);
				if (arglist == *v10 - 1) {
					v14 = v6->MType->mtype;
					if (v14 < MT_NSNAKE || v14 > MT_GSNAKE) {
						v15 = arglist;
						v16 = plr[arglist]._pmode;
						if (v16 != 7 && v16 != 8)
							StartPlrHit(arglist, 0, 1u);
						v17 = v6->_mdir;
						v18 = v32 + offset_x[v17];
						v19 = v31 + offset_y[v17];
						if (PosOkPlayer(arglist, v18, v19)) {
							v20 = plr[v15]._pdir;
							plr[v15].WorldX = v18;
							plr[v15].WorldY = v19;
							FixPlayerLocation(arglist, v20);
							FixPlrWalkTags(arglist);
							dPlayer[v18][v19] = arglist + 1;
							SetPlayerOld(arglist);
						}
					}
				}
			}
		}
	}
}

BOOL PosOkMonst(int i, int x, int y)
{
	int oi, mi, j;
	BOOL ret, fire;

	fire = FALSE;
	ret = !SolidLoc(x, y) && !dPlayer[x][y] && !dMonster[x][y];
	if (ret && dObject[x][y]) {
		oi = dObject[x][y] > 0 ? dObject[x][y] - 1 : -(dObject[x][y] + 1);
		if (object[oi]._oSolidFlag)
			ret = FALSE;
	}

	if (ret && dMissile[x][y] && i >= 0) {
		mi = dMissile[x][y];
		if (mi > 0) {
			if (missile[mi - 1]._mitype == MIS_FIREWALL) { // BUGFIX: 'mi' should be 'mi - 1' (corrected)
				fire = TRUE;
			} else {
				for (j = 0; j < nummissiles; j++) {
					if (missile[missileactive[j]]._mitype == MIS_FIREWALL)
						fire = TRUE;
				}
			}
		}
		if (fire && (!(monster[i].mMagicRes & IMUNE_FIRE) || monster[i].MType->mtype == MT_DIABLO))
			ret = FALSE;
	}

	return ret;
}

BOOL PosOkMonst2(int i, int x, int y)
{
	int oi, mi, j;
	BOOL ret, fire;

	fire = FALSE;
	ret = !SolidLoc(x, y); //12-15
	if (ret && dObject[x][y]) {
		oi = dObject[x][y] > 0 ? dObject[x][y] - 1 : -(dObject[x][y] + 1);
		if (object[oi]._oSolidFlag)
			ret = FALSE;
	}

	if (ret && dMissile[x][y] && i >= 0) { //37
		mi = dMissile[x][y];
		if (mi > 0) {
			if (missile[mi - 1]._mitype == MIS_FIREWALL) { // BUGFIX: 'mi' should be 'mi - 1' (corrected)
				fire = TRUE;
			} else {
				for (j = 0; j < nummissiles; j++) {
					if (missile[missileactive[j]]._mitype == MIS_FIREWALL)
						fire = TRUE;
				}
			}
		}
		if (fire && (!(monster[i].mMagicRes & IMUNE_FIRE) || monster[i].MType->mtype == MT_DIABLO))
			ret = FALSE;
	}

	return ret;
}

BOOL PosOkMonst3(int i, int x, int y)
{
	int j, oi, objtype, mi;
	BOOL ret, fire, isdoor;

	fire = FALSE;
	ret = TRUE;
	isdoor = FALSE;

	if(ret && dObject[x][y] != 0) {
		oi = dObject[x][y] > 0 ? dObject[x][y] - 1 : -(dObject[x][y] + 1);
		objtype = object[oi]._otype;
		isdoor = objtype == OBJ_L1LDOOR || objtype == OBJ_L1RDOOR
			  || objtype == OBJ_L2LDOOR || objtype == OBJ_L2RDOOR
			  || objtype == OBJ_L3LDOOR || objtype == OBJ_L3RDOOR;
		if(object[oi]._oSolidFlag && !isdoor) {
			ret = FALSE;
		}
	}
	if(ret) {
		ret = (!SolidLoc(x, y) || isdoor) && dPlayer[x][y] == 0 && dMonster[x][y] == 0;
	}
	if(ret && dMissile[x][y] != 0 && i >= 0) {
		mi = dMissile[x][y];
		if(mi > 0) {
			if(missile[mi]._mitype == MIS_FIREWALL) {
				fire = TRUE;
			} else {
				for(j = 0; j < nummissiles; j++) {
					mi = missileactive[j];
					if(missile[mi]._mitype == MIS_FIREWALL) {
						fire = TRUE;
					}
				}
			}
		}
		if(fire && (!(monster[i].mMagicRes & IMUNE_FIRE) || monster[i].MType->mtype == MT_DIABLO)) {
			ret = FALSE;
		}
	}

	return ret;
}

BOOL IsSkel(int mt)
{
	return mt >= MT_WSKELAX && mt <= MT_XSKELAX
	    || mt >= MT_WSKELBW && mt <= MT_XSKELBW
	    || mt >= MT_WSKELSD && mt <= MT_XSKELSD;
}

BOOL IsGoat(int mt)
{
	return mt >= MT_NGOATMC && mt <= MT_GGOATMC
	    || mt >= MT_NGOATBW && mt <= MT_GGOATBW;
}

int M_SpawnSkel(int x, int y, int dir)
{
	int i, j, skeltypes, skel;

	j = 0;
	for (i = 0; i < nummtypes; i++) {
		if (IsSkel(Monsters[i].mtype))
			j++;
	}

	if (j) {
		skeltypes = random(136, j);
		j = 0;
		for (i = 0; i < nummtypes && j <= skeltypes; i++) {
			if (IsSkel(Monsters[i].mtype))
				j++;
		}
		skel = AddMonster(x, y, dir, i - 1, 1);
		if (skel != -1)
			M_StartSpStand(skel, dir);

		return skel;
	}

	return -1;
}

void ActivateSpawn(int i, int x, int y, int dir)
{
	dMonster[x][y] = i + 1;
	monster[i]._mx = x;
	monster[i]._my = y;
	monster[i]._mfutx = x;
	monster[i]._mfuty = y;
	monster[i]._moldx = x;
	monster[i]._moldy = y;
	M_StartSpStand(i, dir);
}

BOOL SpawnSkeleton(int ii, int x, int y)
{
	int dx, dy, xx, yy, dir, j, k, rs;
	BOOL savail;
	int monstok[3][3];

	if (ii == -1)
		return FALSE;

	if (PosOkMonst(-1, x, y)) {
		dir = GetDirection(x, y, x, y);
		ActivateSpawn(ii, x, y, dir);
		return TRUE;
	}

	savail = FALSE;
	yy = 0;
	for (j = y - 1; j <= y + 1; j++) {
		xx = 0;
		for (k = x - 1; k <= x + 1; k++) {
			monstok[xx][yy] = PosOkMonst(-1, k, j);
			savail |= monstok[xx][yy];
			xx++;
		}
		yy++;
	}
	if (!savail) {
		return FALSE;
	}

	rs = random(137, 15) + 1;
	xx = 0;
	yy = 0;
	while (rs > 0) {
		if (monstok[xx][yy])
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

	dx = x - 1 + xx;
	dy = y - 1 + yy;
	dir = GetDirection(dx, dy, x, y);
	ActivateSpawn(ii, dx, dy, dir);

	return TRUE;
}

int PreSpawnSkeleton()
{
	int i, j, skeltypes, skel;

	j = 0;

	if (nummtypes <= 0)
		return -1;

	for (i = 0; i < nummtypes; i++) {
		if (IsSkel(Monsters[i].mtype))
			j++;
	}

	if (j) {
		skeltypes = random(136, j);
		j = 0;
		for (i = 0; i < nummtypes && j <= skeltypes; i++) {
			if (IsSkel(Monsters[i].mtype))
				j++;
		}
		skel = AddMonster(0, 0, 0, i - 1, 0);
		if (skel != -1)
			M_StartStand(skel, 0);

		return skel;
	}

	return -1;
}

void TalktoMonster(int i)
{
	MonsterStruct *Monst;
	int pnum, itm;

	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("TalktoMonster: Invalid monster %d", i);

	Monst = &monster[i];
	pnum = Monst->_menemy;
	Monst->_mmode = MM_TALK;
	if (Monst->_mAi == AI_SNOTSPIL || Monst->_mAi == AI_LACHDAN) {
		if (QuestStatus(QTYPE_BOL) && quests[QTYPE_BOL]._qvar1 == 2 && PlrHasItem(pnum, IDI_BANNER, &itm)) {
			RemoveInvItem(pnum, itm);
			quests[QTYPE_BOL]._qactive = 3;
			Monst->mtalkmsg = QUEST_BANNER12;
			Monst->_mgoal = MGOAL_INQUIRING;
		}
		if (QuestStatus(QTYPE_VEIL) && Monst->mtalkmsg >= QUEST_VEIL9) {
			if (PlrHasItem(pnum, IDI_GLDNELIX, &itm)) {
				RemoveInvItem(pnum, itm);
				Monst->mtalkmsg = QUEST_VEIL11;
				Monst->_mgoal = MGOAL_INQUIRING;
			}
		}
	}
}

void SpawnGolum(int i, int x, int y, int mi)
{
	if ((DWORD)i >= MAXMONSTERS)
		app_fatal("SpawnGolum: Invalid monster %d", i);

	dMonster[x][y] = i + 1;
	monster[i]._mx = x;
	monster[i]._my = y;
	monster[i]._mfutx = x;
	monster[i]._mfuty = y;
	monster[i]._moldx = x;
	monster[i]._moldy = y;
	monster[i]._pathcount = 0;
	monster[i]._mFlags |= MFLAG_GOLEM;
	monster[i].mArmorClass = 25;
	monster[i]._mmaxhp = 2 * (320 * missile[mi]._mispllvl + plr[i]._pMaxMana / 3);
	monster[i]._mhitpoints = monster[i]._mmaxhp;
	monster[i].mHit = 5 * (missile[mi]._mispllvl + 8) + 2 * plr[i]._pLevel;
	monster[i].mMinDamage = 2 * (missile[mi]._mispllvl + 4);
	monster[i].mMaxDamage = 2 * (missile[mi]._mispllvl + 8);
	M_StartSpStand(i, 0);
	M_Enemy(i);
	if (i == myplr) {
		NetSendCmdGolem(
		    monster[i]._mx,
		    monster[i]._my,
		    monster[i]._mdir,
		    monster[i]._menemy,
		    monster[i]._mhitpoints,
		    currlevel);
	}
}

BOOL CanTalkToMonst(int m)
{
	if ((DWORD)m >= MAXMONSTERS) {
		app_fatal("CanTalkToMonst: Invalid monster %d", m);
	}

	if (monster[m]._mgoal == MGOAL_INQUIRING) {
		return TRUE;
	}

	return monster[m]._mgoal == MGOAL_TALKING;
}

BOOL CheckMonsterHit(int m, BOOL *ret)
{
	if ((DWORD)m >= MAXMONSTERS) {
		app_fatal("CheckMonsterHit: Invalid monster %d", m);
	}

	if (monster[m]._mAi == AI_GARG && monster[m]._mFlags & MFLAG_ALLOW_SPECIAL) {
		monster[m]._mmode = MM_SATTACK;
		monster[m]._mFlags &= ~MFLAG_ALLOW_SPECIAL;
		*ret = TRUE;
		return TRUE;
	}

	if (monster[m].MType->mtype < MT_COUNSLR || monster[m].MType->mtype > MT_ADVOCATE || monster[m]._mgoal == MGOAL_NORMAL) {
		return FALSE;
	} else {
		*ret = FALSE;
	}

	return TRUE;
}

int encode_enemy(int m)
{
	int enemy;

	enemy = monster[m]._menemy;
	if (monster[m]._mFlags & MFLAG_TARGETS_MONSTER)
		enemy += 4;

	return enemy;
}

void decode_enemy(int m, int enemy)
{
	if (enemy < 4) {
		monster[m]._mFlags &= ~MFLAG_TARGETS_MONSTER;
		monster[m]._menemy = enemy;
		monster[m]._menemyx = plr[enemy]._px;
		monster[m]._menemyy = plr[enemy]._py;
	} else {
		monster[m]._mFlags |= MFLAG_TARGETS_MONSTER;
		enemy -= 4;
		monster[m]._menemy = enemy;
		monster[m]._menemyx = monster[enemy]._mfutx;
		monster[m]._menemyy = monster[enemy]._mfuty;
	}
}

DEVILUTION_END_NAMESPACE
