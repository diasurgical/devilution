/**
 * @file themes.cpp
 *
 * Implementation of the theme room placing algorithms.
 */
#include "all.h"

int numthemes;
BOOL armorFlag;
BOOL ThemeGoodIn[4];
BOOL weaponFlag;
BOOL treasureFlag;
BOOL mFountainFlag;
BOOL cauldronFlag;
BOOL tFountainFlag;
int zharlib;
int themex;
int themey;
int themeVar1;
ThemeStruct themes[MAXTHEMES];
BOOL pFountainFlag;
BOOL bFountainFlag;
BOOL bCrossFlag;

/** Specifies the set of special theme IDs from which one will be selected at random. */
int ThemeGood[4] = { THEME_GOATSHRINE, THEME_SHRINE, THEME_SKELROOM, THEME_LIBRARY };
/** Specifies a 5x5 area to fit theme objects. */
int trm5x[] = {
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2,
	-2, -1, 0, 1, 2
};
/** Specifies a 5x5 area to fit theme objects. */
int trm5y[] = {
	-2, -2, -2, -2, -2,
	-1, -1, -1, -1, -1,
	0, 0, 0, 0, 0,
	1, 1, 1, 1, 1,
	2, 2, 2, 2, 2
};
/** Specifies a 3x3 area to fit theme objects. */
int trm3x[] = {
	-1, 0, 1,
	-1, 0, 1,
	-1, 0, 1
};
/** Specifies a 3x3 area to fit theme objects. */
int trm3y[] = {
	-1, -1, -1,
	0, 0, 0,
	1, 1, 1
};

BOOL TFit_Shrine(int i)
{
	int xp, yp, found;

	xp = 0;
	yp = 0;
	found = 0;
	while (found == 0) {
		if (dTransVal[xp][yp] == themes[i].ttval) {
			if (nTrapTable[dPiece[xp][yp - 1]]
			    && !nSolidTable[dPiece[xp - 1][yp]]
			    && !nSolidTable[dPiece[xp + 1][yp]]
			    && dTransVal[xp - 1][yp] == themes[i].ttval
			    && dTransVal[xp + 1][yp] == themes[i].ttval
			    && dObject[xp - 1][yp - 1] == 0
			    && dObject[xp + 1][yp - 1] == 0) {
				found = 1;
			}
			if (found == 0
			    && nTrapTable[dPiece[xp - 1][yp]]
			    && !nSolidTable[dPiece[xp][yp - 1]]
			    && !nSolidTable[dPiece[xp][yp + 1]]
			    && dTransVal[xp][yp - 1] == themes[i].ttval
			    && dTransVal[xp][yp + 1] == themes[i].ttval
			    && dObject[xp - 1][yp - 1] == 0
			    && dObject[xp - 1][yp + 1] == 0) {
				found = 2;
			}
		}
		if (found == 0) {
			xp++;
			if (xp == MAXDUNX) {
				xp = 0;
				yp++;
				if (yp == MAXDUNY)
					return FALSE;
			}
		}
	}
	themex = xp;
	themey = yp;
	themeVar1 = found;
	return TRUE;
}

BOOL TFit_Obj5(int t)
{
	int xp, yp;
	int i, r, rs;
	BOOL found;

	xp = 0;
	yp = 0;
	r = random_(0, 5) + 1;
	rs = r;
	while (r > 0) {
		found = FALSE;
		if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
			found = TRUE;
			for (i = 0; found && i < 25; i++) {
				if (nSolidTable[dPiece[xp + trm5x[i]][yp + trm5y[i]]]) {
					found = FALSE;
				}
				if (dTransVal[xp + trm5x[i]][yp + trm5y[i]] != themes[t].ttval) {
					found = FALSE;
				}
			}
		}

		if (!found) {
			xp++;
			if (xp == MAXDUNX) {
				xp = 0;
				yp++;
				if (yp == MAXDUNY) {
					if (r == rs) {
						return FALSE;
					}
					yp = 0;
				}
			}
			continue;
		}

		r--;
	}

	themex = xp;
	themey = yp;

	return TRUE;
}

BOOL TFit_SkelRoom(int t)
{
	int i;

	if (leveltype != DTYPE_CATHEDRAL && leveltype != DTYPE_CATACOMBS) {
		return FALSE;
	}

	for (i = 0; i < nummtypes; i++) {
		if (IsSkel(Monsters[i].mtype)) {
			themeVar1 = i;
			return TFit_Obj5(t);
		}
	}

	return FALSE;
}

BOOL TFit_GoatShrine(int t)
{
	int i;

	for (i = 0; i < nummtypes; i++) {
		if (IsGoat(Monsters[i].mtype)) {
			themeVar1 = i;
			return TFit_Obj5(t);
		}
	}

	return FALSE;
}

BOOL CheckThemeObj3(int xp, int yp, int t, int f)
{
	int i;

	for (i = 0; i < 9; i++) {
		if (xp + trm3x[i] < 0 || yp + trm3y[i] < 0)
			return FALSE;
		if (nSolidTable[dPiece[xp + trm3x[i]][yp + trm3y[i]]])
			return FALSE;
		if (dTransVal[xp + trm3x[i]][yp + trm3y[i]] != themes[t].ttval)
			return FALSE;
		if (dObject[xp + trm3x[i]][yp + trm3y[i]])
			return FALSE;
		if (f != -1 && random_(0, f) == 0)
			return FALSE;
	}

	return TRUE;
}

BOOL TFit_Obj3(int t)
{
	int xp, yp;
	char objrnd[4] = { 4, 4, 3, 5 };

	for (yp = 1; yp < MAXDUNY - 1; yp++) {
		for (xp = 1; xp < MAXDUNX - 1; xp++) {
			if (CheckThemeObj3(xp, yp, t, objrnd[leveltype - 1])) {
				themex = xp;
				themey = yp;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CheckThemeReqs(int t)
{
	BOOL rv;

	rv = TRUE;
	switch (t) {
	case THEME_SHRINE:
	case THEME_SKELROOM:
	case THEME_LIBRARY:
		if (leveltype == DTYPE_CAVES || leveltype == DTYPE_HELL) {
			rv = FALSE;
		}
		break;
	case THEME_BLOODFOUNTAIN:
		if (!bFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_PURIFYINGFOUNTAIN:
		if (!pFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_ARMORSTAND:
		if (leveltype == DTYPE_CATHEDRAL) {
			rv = FALSE;
		}
		break;
	case THEME_CAULDRON:
		if (leveltype != DTYPE_HELL || !cauldronFlag) {
			rv = FALSE;
		}
		break;
	case THEME_MURKYFOUNTAIN:
		if (!mFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_TEARFOUNTAIN:
		if (!tFountainFlag) {
			rv = FALSE;
		}
		break;
	case THEME_WEAPONRACK:
		if (leveltype == DTYPE_CATHEDRAL) {
			rv = FALSE;
		}
		break;
	}

	return rv;
}

BOOL SpecialThemeFit(int i, int t)
{
	BOOL rv;

	rv = CheckThemeReqs(t);
	switch (t) {
	case THEME_SHRINE:
	case THEME_LIBRARY:
		if (rv) {
			rv = TFit_Shrine(i);
		}
		break;
	case THEME_SKELROOM:
		if (rv) {
			rv = TFit_SkelRoom(i);
		}
		break;
	case THEME_BLOODFOUNTAIN:
		if (rv) {
			rv = TFit_Obj5(i);
		}
		if (rv) {
			bFountainFlag = FALSE;
		}
		break;
	case THEME_PURIFYINGFOUNTAIN:
		if (rv) {
			rv = TFit_Obj5(i);
		}
		if (rv) {
			pFountainFlag = FALSE;
		}
		break;
	case THEME_MURKYFOUNTAIN:
		if (rv) {
			rv = TFit_Obj5(i);
		}
		if (rv) {
			mFountainFlag = FALSE;
		}
		break;
	case THEME_TEARFOUNTAIN:
		if (rv) {
			rv = TFit_Obj5(i);
		}
		if (rv) {
			tFountainFlag = FALSE;
		}
		break;
	case THEME_CAULDRON:
		if (rv) {
			rv = TFit_Obj5(i);
		}
		if (rv) {
			cauldronFlag = FALSE;
		}
		break;
	case THEME_GOATSHRINE:
		if (rv) {
			rv = TFit_GoatShrine(i);
		}
		break;
	case THEME_TORTURE:
	case THEME_DECAPITATED:
	case THEME_ARMORSTAND:
	case THEME_BRNCROSS:
	case THEME_WEAPONRACK:
		if (rv) {
			rv = TFit_Obj3(i);
		}
		break;
	case THEME_TREASURE:
		rv = treasureFlag;
		if (rv) {
			treasureFlag = FALSE;
		}
		break;
	}

	return rv;
}

BOOL CheckThemeRoom(int tv)
{
	int i, j, tarea;

	for (i = 0; i < numtrigs; i++) {
		if (dTransVal[trigs[i]._tx][trigs[i]._ty] == tv)
			return FALSE;
	}

	tarea = 0;
	for (j = 0; j < MAXDUNY; j++) {
		for (i = 0; i < MAXDUNX; i++) {
			if (dTransVal[i][j] != tv)
				continue;
			if (dFlags[i][j] & BFLAG_POPULATED)
				return FALSE;

			tarea++;
		}
	}

	if (leveltype == DTYPE_CATHEDRAL && (tarea < 9 || tarea > 100))
		return FALSE;

	for (j = 0; j < MAXDUNY; j++) {
		for (i = 0; i < MAXDUNX; i++) {
			if (dTransVal[i][j] != tv || nSolidTable[dPiece[i][j]])
				continue;
			if (dTransVal[i - 1][j] != tv && !nSolidTable[dPiece[i - 1][j]])
				return FALSE;
			if (dTransVal[i + 1][j] != tv && !nSolidTable[dPiece[i + 1][j]])
				return FALSE;
			if (dTransVal[i][j - 1] != tv && !nSolidTable[dPiece[i][j - 1]])
				return FALSE;
			if (dTransVal[i][j + 1] != tv && !nSolidTable[dPiece[i][j + 1]])
				return FALSE;
		}
	}

	return TRUE;
}

void InitThemes()
{
	int i, j;

	zharlib = -1;
	numthemes = 0;
	armorFlag = TRUE;
	bFountainFlag = TRUE;
	cauldronFlag = TRUE;
	mFountainFlag = TRUE;
	pFountainFlag = TRUE;
	tFountainFlag = TRUE;
	treasureFlag = TRUE;
	bCrossFlag = FALSE;
	weaponFlag = TRUE;

	if (currlevel == 16)
		return;

	if (leveltype == DTYPE_CATHEDRAL) {
		for (i = 0; i < sizeof(ThemeGoodIn) / sizeof(ThemeGoodIn[0]); i++)
			ThemeGoodIn[i] = FALSE;

		for (i = 0; i < 256 && numthemes < MAXTHEMES; i++) {
			if (CheckThemeRoom(i)) {
				themes[numthemes].ttval = i;
				for (j = ThemeGood[random_(0, 4)];; j = random_(0, 17)) {
					if (SpecialThemeFit(numthemes, j)) {
						break;
					}
				}
				themes[numthemes].ttype = j;
				numthemes++;
			}
		}
	}
	if (leveltype == DTYPE_CATACOMBS || leveltype == DTYPE_CAVES || leveltype == DTYPE_HELL) {
		for (i = 0; i < themeCount; i++)
			themes[i].ttype = THEME_NONE;
		if (QuestStatus(Q_ZHAR)) {
			for (j = 0; j < themeCount; j++) {
				themes[j].ttval = themeLoc[j].ttval;
				if (SpecialThemeFit(j, THEME_LIBRARY)) {
					themes[j].ttype = THEME_LIBRARY;
					zharlib = j;
					break;
				}
			}
		}
		for (i = 0; i < themeCount; i++) {
			if (themes[i].ttype == THEME_NONE) {
				themes[i].ttval = themeLoc[i].ttval;
				for (j = ThemeGood[random_(0, 4)];; j = random_(0, 17)) {
					if (SpecialThemeFit(i, j)) {
						break;
					}
				}
				themes[i].ttype = j;
			}
		}
		numthemes += themeCount;
	}
}

/**
 * @brief HoldThemeRooms marks theme rooms as populated.
 */
void HoldThemeRooms()
{
	int i, x, y;
	char v;

	if (currlevel != 16) {
		if (leveltype == DTYPE_CATHEDRAL) {
			for (i = 0; i < numthemes; i++) {
				v = themes[i].ttval;
				for (y = 0; y < MAXDUNY; y++) {
					for (x = 0; x < MAXDUNX; x++) {
						if (dTransVal[x][y] == v) {
							dFlags[x][y] |= BFLAG_POPULATED;
						}
					}
				}
			}
		} else {
			DRLG_HoldThemeRooms();
		}
	}
}

/**
 * PlaceThemeMonsts places theme monsters with the specified frequency.
 *
 * @param t theme number (index into themes array).
 * @param f frequency (1/f likelihood of adding monster).
 */
void PlaceThemeMonsts(int t, int f)
{
	int xp, yp;
#ifdef HELLFIRE
	int scattertypes[138];
#else
	int scattertypes[111];
#endif
	int numscattypes, mtype, i;

	numscattypes = 0;
	for (i = 0; i < nummtypes; i++) {
		if (Monsters[i].mPlaceFlags & PLACE_SCATTER) {
			scattertypes[numscattypes] = i;
			numscattypes++;
		}
	}
	mtype = scattertypes[random_(0, numscattypes)];
	for (yp = 0; yp < MAXDUNY; yp++) {
		for (xp = 0; xp < MAXDUNX; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]] && dItem[xp][yp] == 0 && dObject[xp][yp] == 0) {
				if (random_(0, f) == 0) {
					AddMonster(xp, yp, random_(0, 8), mtype, TRUE);
				}
			}
		}
	}
}

/**
 * Theme_Barrel initializes the barrel theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Barrel(int t)
{
	int xp, yp, r;
	char barrnd[4] = { 2, 6, 4, 8 };
	char monstrnd[4] = { 5, 7, 3, 9 };

	for (yp = 0; yp < MAXDUNY; yp++) {
		for (xp = 0; xp < MAXDUNX; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				if (random_(0, barrnd[leveltype - 1]) == 0) {
					if (random_(0, barrnd[leveltype - 1]) == 0) {
						r = OBJ_BARREL;
					} else {
						r = OBJ_BARRELEX;
					}
					AddObject(r, xp, yp);
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_Shrine initializes the shrine theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Shrine(int t)
{
	char monstrnd[4] = { 6, 6, 3, 9 };

	TFit_Shrine(t);
	if (themeVar1 == 1) {
		AddObject(OBJ_CANDLE2, themex - 1, themey);
		AddObject(OBJ_SHRINER, themex, themey);
		AddObject(OBJ_CANDLE2, themex + 1, themey);
	} else {
		AddObject(OBJ_CANDLE2, themex, themey - 1);
		AddObject(OBJ_SHRINEL, themex, themey);
		AddObject(OBJ_CANDLE2, themex, themey + 1);
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_MonstPit initializes the monster pit theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_MonstPit(int t)
{
	int r;
	int ixp, iyp;
	char monstrnd[4] = { 6, 7, 3, 9 };

	r = random_(0, 100) + 1;
	ixp = 0;
	iyp = 0;
	while (r > 0) {
		if (dTransVal[ixp][iyp] == themes[t].ttval && !nSolidTable[dPiece[ixp][iyp]]) {
			--r;
		}
		if (r <= 0)
			continue;
		ixp++;
		if (ixp == MAXDUNX) {
			ixp = 0;
			iyp++;
			if (iyp == MAXDUNY) {
				iyp = 0;
			}
		}
	}
	CreateRndItem(ixp, iyp, TRUE, FALSE, TRUE);
	ItemNoFlippy();
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_SkelRoom initializes the skeleton room theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_SkelRoom(int t)
{
	int xp, yp, i;
	char monstrnd[4] = { 6, 7, 3, 9 };

	TFit_SkelRoom(t);

	xp = themex;
	yp = themey;

	AddObject(OBJ_SKFIRE, xp, yp);

	if (random_(0, monstrnd[leveltype - 1]) != 0) {
		i = PreSpawnSkeleton();
		SpawnSkeleton(i, xp - 1, yp - 1);
	} else {
		AddObject(OBJ_BANNERL, xp - 1, yp - 1);
	}

	i = PreSpawnSkeleton();
	SpawnSkeleton(i, xp, yp - 1);

	if (random_(0, monstrnd[leveltype - 1]) != 0) {
		i = PreSpawnSkeleton();
		SpawnSkeleton(i, xp + 1, yp - 1);
	} else {
		AddObject(OBJ_BANNERR, xp + 1, yp - 1);
	}
	if (random_(0, monstrnd[leveltype - 1]) != 0) {
		i = PreSpawnSkeleton();
		SpawnSkeleton(i, xp - 1, yp);
	} else {
		AddObject(OBJ_BANNERM, xp - 1, yp);
	}
	if (random_(0, monstrnd[leveltype - 1]) != 0) {
		i = PreSpawnSkeleton();
		SpawnSkeleton(i, xp + 1, yp);
	} else {
		AddObject(OBJ_BANNERM, xp + 1, yp);
	}
	if (random_(0, monstrnd[leveltype - 1]) != 0) {
		i = PreSpawnSkeleton();
		SpawnSkeleton(i, xp - 1, yp + 1);
	} else {
		AddObject(OBJ_BANNERR, xp - 1, yp + 1);
	}

	i = PreSpawnSkeleton();
	SpawnSkeleton(i, xp, yp + 1);

	if (random_(0, monstrnd[leveltype - 1]) != 0) {
		i = PreSpawnSkeleton();
		SpawnSkeleton(i, xp + 1, yp + 1);
	} else {
		AddObject(OBJ_BANNERL, xp + 1, yp + 1);
	}

	if (dObject[xp][yp - 3] == 0) {
		AddObject(OBJ_SKELBOOK, xp, yp - 2);
	}
	if (dObject[xp][yp + 3] == 0) {
		AddObject(OBJ_SKELBOOK, xp, yp + 2);
	}
}

/**
 * Theme_Treasure initializes the treasure theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Treasure(int t)
{
	int xp, yp;
	int i;
	char treasrnd[4] = { 4, 9, 7, 10 };
	char monstrnd[4] = { 6, 8, 3, 7 };

	GetRndSeed();
	for (yp = 0; yp < MAXDUNY; yp++) {
		for (xp = 0; xp < MAXDUNX; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				int rv = random_(0, treasrnd[leveltype - 1]);
				// BUGFIX: the `2*` in `2*random_(0, treasrnd...) == 0` has no effect, should probably be `random_(0, 2*treasrnd...) == 0`
				if ((2 * random_(0, treasrnd[leveltype - 1])) == 0) {
					CreateTypeItem(xp, yp, FALSE, ITYPE_GOLD, IMISC_NONE, FALSE, TRUE);
					ItemNoFlippy();
				}
				if (rv == 0) {
					CreateRndItem(xp, yp, FALSE, FALSE, TRUE);
					ItemNoFlippy();
				}
				if (rv == 0 || rv >= treasrnd[leveltype - 1] - 2) {
					i = ItemNoFlippy();
					if (rv >= treasrnd[leveltype - 1] - 2 && leveltype != DTYPE_CATHEDRAL) {
						item[i]._ivalue >>= 1;
					}
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_Library initializes the library theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Library(int t)
{
	int xp, yp, oi;
	char librnd[4] = { 1, 2, 2, 5 };
	char monstrnd[4] = { 5, 7, 3, 9 };

	TFit_Shrine(t);

	if (themeVar1 == 1) {
		AddObject(OBJ_BOOKCANDLE, themex - 1, themey);
		AddObject(OBJ_BOOKCASER, themex, themey);
		AddObject(OBJ_BOOKCANDLE, themex + 1, themey);
	} else {
		AddObject(OBJ_BOOKCANDLE, themex, themey - 1);
		AddObject(OBJ_BOOKCASEL, themex, themey);
		AddObject(OBJ_BOOKCANDLE, themex, themey + 1);
	}

	for (yp = 1; yp < MAXDUNY - 1; yp++) {
		for (xp = 1; xp < MAXDUNX - 1; xp++) {
			if (CheckThemeObj3(xp, yp, t, -1) && dMonster[xp][yp] == 0 && random_(0, librnd[leveltype - 1]) == 0) {
				AddObject(OBJ_BOOKSTAND, xp, yp);
				if (random_(0, 2 * librnd[leveltype - 1]) != 0) { /// BUGFIX: check dObject[xp][yp] was populated by AddObject
					oi = dObject[xp][yp] - 1;
					object[oi]._oSelFlag = 0;
					object[oi]._oAnimFrame += 2;
				}
			}
		}
	}

	if (QuestStatus(Q_ZHAR)) {
		if (t == zharlib) {
			return;
		}
		PlaceThemeMonsts(t, monstrnd[leveltype]); /// BUGFIX: `leveltype - 1`
	} else {
		PlaceThemeMonsts(t, monstrnd[leveltype]); /// BUGFIX: `leveltype - 1`
	}
}

/**
 * Theme_Torture initializes the torture theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Torture(int t)
{
	int xp, yp;
	char tortrnd[4] = { 6, 8, 3, 8 };
	char monstrnd[4] = { 6, 8, 3, 9 };

	for (yp = 1; yp < MAXDUNY - 1; yp++) {
		for (xp = 1; xp < MAXDUNX - 1; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				if (CheckThemeObj3(xp, yp, t, -1)) {
					if (random_(0, tortrnd[leveltype - 1]) == 0) {
						AddObject(OBJ_TNUDEM2, xp, yp);
					}
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_BloodFountain initializes the blood fountain theme.
 * @param t Theme number (index into themes array).
 */
void Theme_BloodFountain(int t)
{
	char monstrnd[4] = { 6, 8, 3, 9 };

	TFit_Obj5(t);
	AddObject(OBJ_BLOODFTN, themex, themey);
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_Decap initializes the decapitated theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Decap(int t)
{
	int xp, yp;
	char decaprnd[4] = { 6, 8, 3, 8 };
	char monstrnd[4] = { 6, 8, 3, 9 };

	for (yp = 1; yp < MAXDUNY - 1; yp++) {
		for (xp = 1; xp < MAXDUNX - 1; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				if (CheckThemeObj3(xp, yp, t, -1)) {
					if (random_(0, decaprnd[leveltype - 1]) == 0) {
						AddObject(OBJ_DECAP, xp, yp);
					}
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_PurifyingFountain initializes the purifying fountain theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_PurifyingFountain(int t)
{
	char monstrnd[4] = { 6, 7, 3, 9 };

	TFit_Obj5(t);
	AddObject(OBJ_PURIFYINGFTN, themex, themey);
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_ArmorStand initializes the armor stand theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_ArmorStand(int t)
{
	int xp, yp;
	char armorrnd[4] = { 6, 8, 3, 8 };
	char monstrnd[4] = { 6, 7, 3, 9 };

	if (armorFlag) {
		TFit_Obj3(t);
		AddObject(OBJ_ARMORSTAND, themex, themey);
	}
	for (yp = 0; yp < MAXDUNY; yp++) {
		for (xp = 0; xp < MAXDUNX; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				if (CheckThemeObj3(xp, yp, t, -1)) {
					if (random_(0, armorrnd[leveltype - 1]) == 0) {
						AddObject(OBJ_ARMORSTANDN, xp, yp);
					}
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
	armorFlag = FALSE;
}

/**
 * Theme_GoatShrine initializes the goat shrine theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_GoatShrine(int t)
{
	int xx, yy;

	TFit_GoatShrine(t);
	AddObject(OBJ_GOATSHRINE, themex, themey);
	for (yy = themey - 1; yy <= themey + 1; yy++) {
		for (xx = themex - 1; xx <= themex + 1; xx++) {
			if (dTransVal[xx][yy] == themes[t].ttval && !nSolidTable[dPiece[xx][yy]] && (xx != themex || yy != themey)) {
				AddMonster(xx, yy, DIR_SW, themeVar1, TRUE);
			}
		}
	}
}

/**
 * Theme_Cauldron initializes the cauldron theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_Cauldron(int t)
{
	char monstrnd[4] = { 6, 7, 3, 9 };

	TFit_Obj5(t);
	AddObject(OBJ_CAULDRON, themex, themey);
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_MurkyFountain initializes the murky fountain theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_MurkyFountain(int t)
{
	char monstrnd[4] = { 6, 7, 3, 9 };

	TFit_Obj5(t);
	AddObject(OBJ_MURKYFTN, themex, themey);
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_TearFountain initializes the tear fountain theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_TearFountain(int t)
{
	char monstrnd[4] = { 6, 7, 3, 9 };

	TFit_Obj5(t);
	AddObject(OBJ_TEARFTN, themex, themey);
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
}

/**
 * Theme_BrnCross initializes the burning cross theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_BrnCross(int t)
{
	int xp, yp;
	char monstrnd[4] = { 6, 8, 3, 9 };
	char bcrossrnd[4] = { 5, 7, 3, 8 };

	for (yp = 0; yp < MAXDUNY; yp++) {
		for (xp = 0; xp < MAXDUNX; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				if (CheckThemeObj3(xp, yp, t, -1)) {
					if (random_(0, bcrossrnd[leveltype - 1]) == 0) {
						AddObject(OBJ_TBCROSS, xp, yp);
					}
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
	bCrossFlag = TRUE;
}

/**
 * Theme_WeaponRack initializes the weapon rack theme.
 *
 * @param t theme number (index into themes array).
 */
void Theme_WeaponRack(int t)
{
	int xp, yp;
	char weaponrnd[4] = { 6, 8, 5, 8 };
	char monstrnd[4] = { 6, 7, 3, 9 };

	if (weaponFlag) {
		TFit_Obj3(t);
		AddObject(OBJ_WEAPONRACK, themex, themey);
	}
	for (yp = 0; yp < MAXDUNY; yp++) {
		for (xp = 0; xp < MAXDUNX; xp++) {
			if (dTransVal[xp][yp] == themes[t].ttval && !nSolidTable[dPiece[xp][yp]]) {
				if (CheckThemeObj3(xp, yp, t, -1)) {
					if (random_(0, weaponrnd[leveltype - 1]) == 0) {
						AddObject(OBJ_WEAPONRACKN, xp, yp);
					}
				}
			}
		}
	}
	PlaceThemeMonsts(t, monstrnd[leveltype - 1]);
	weaponFlag = FALSE;
}

/**
 * UpdateL4Trans sets each value of the transparency map to 1.
 */
void UpdateL4Trans()
{
	int i, j;

	for (j = 0; j < MAXDUNY; j++) {
		for (i = 0; i < MAXDUNX; i++) {
			if (dTransVal[i][j] != 0) {
				dTransVal[i][j] = 1;
			}
		}
	}
}

/**
 * CreateThemeRooms adds thematic elements to rooms.
 */
void CreateThemeRooms()
{
	int i;

	if (currlevel == 16) {
		return;
	}
	InitObjFlag = TRUE;
	for (i = 0; i < numthemes; i++) {
		themex = 0;
		themey = 0;
		switch (themes[i].ttype) {
		case THEME_BARREL:
			Theme_Barrel(i);
			break;
		case THEME_SHRINE:
			Theme_Shrine(i);
			break;
		case THEME_MONSTPIT:
			Theme_MonstPit(i);
			break;
		case THEME_SKELROOM:
			Theme_SkelRoom(i);
			break;
		case THEME_TREASURE:
			Theme_Treasure(i);
			break;
		case THEME_LIBRARY:
			Theme_Library(i);
			break;
		case THEME_TORTURE:
			Theme_Torture(i);
			break;
		case THEME_BLOODFOUNTAIN:
			Theme_BloodFountain(i);
			break;
		case THEME_DECAPITATED:
			Theme_Decap(i);
			break;
		case THEME_PURIFYINGFOUNTAIN:
			Theme_PurifyingFountain(i);
			break;
		case THEME_ARMORSTAND:
			Theme_ArmorStand(i);
			break;
		case THEME_GOATSHRINE:
			Theme_GoatShrine(i);
			break;
		case THEME_CAULDRON:
			Theme_Cauldron(i);
			break;
		case THEME_MURKYFOUNTAIN:
			Theme_MurkyFountain(i);
			break;
		case THEME_TEARFOUNTAIN:
			Theme_TearFountain(i);
			break;
		case THEME_BRNCROSS:
			Theme_BrnCross(i);
			break;
		case THEME_WEAPONRACK:
			Theme_WeaponRack(i);
			break;
		}
	}
	InitObjFlag = FALSE;
	if (leveltype == DTYPE_HELL && themeCount > 0) {
		UpdateL4Trans();
	}
}
