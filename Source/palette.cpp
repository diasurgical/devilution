/**
 * @file palette.cpp
 *
 * Implementation of functions for handling the engines color palette.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

extern char gszProgKey[];

/** Specifies the gamma correction level. */
int gamma_correction = 100;
#ifndef HELLFIRE
/** Specifies whether colour cycling is enabled. */
BOOL color_cycling_enabled = TRUE;
#endif
/** Specifies whether the palette has max brightness. */
BOOLEAN sgbFadedIn = TRUE;
/** In-memory palette to which gamma corrections are applied. */
PALETTEENTRY sgBase[256];
/** The active palette of the system. */
PALETTEENTRY sgCurr[256];

/* data */

/** The original palette as loaded from file. */
PALETTEENTRY sgLoad[256];
int gdwPalEntries = 0;

/* named constants in 1.09b (they are in .rdata there) */
static const char gszGammaCorrection[] = "Gamma Correction";
static const char gszColorCycling[] = "Color Cycling";

static void palette_update()
{
	int nentries;
	int max_entries;

	if (lpDDPal) {
		nentries = 0;
		max_entries = 256;
		if (!fullscreen) {
			nentries = gdwPalEntries;
			max_entries = 2 * (128 - gdwPalEntries);
		}
		SDrawUpdatePalette(nentries, max_entries, &sgCurr[nentries], 0);
	}
}

static void ApplyGamma(PALETTEENTRY *dst, PALETTEENTRY *src, int n)
{
	int i;
	double g;

	g = gamma_correction / 100.0;

	for (i = 0; i < n; i++) {
		dst->peRed = pow(src->peRed / 256.0, g) * 256.0;
		dst->peGreen = pow(src->peGreen / 256.0, g) * 256.0;
		dst->peBlue = pow(src->peBlue / 256.0, g) * 256.0;
		dst++;
		src++;
	}
}

void SaveGamma()
{
	SRegSaveValue(gszProgKey, gszGammaCorrection, 0, gamma_correction);
#ifndef HELLFIRE
	SRegSaveValue(gszProgKey, gszColorCycling, FALSE, color_cycling_enabled);
#endif
}

static void LoadGamma()
{
	int gamma_value;
	int value;

	value = gamma_correction;
	if (!SRegLoadValue(gszProgKey, gszGammaCorrection, 0, &value))
		value = 100;
	gamma_value = value;
	if (value < 30) {
		gamma_value = 30;
	} else if (value > 100) {
		gamma_value = 100;
	}
	gamma_correction = gamma_value - gamma_value % 5;
#ifndef HELLFIRE
	if (!SRegLoadValue(gszProgKey, gszColorCycling, 0, &value))
		value = 1;
	color_cycling_enabled = value;
#endif
}

static void LoadSysPal()
{
	HDC hDC;
	int i, iStartIndex;

	for (i = 0; i < 256; i++)
		sgCurr[i].peFlags = PC_NOCOLLAPSE | PC_RESERVED;

	if (!fullscreen) {
		hDC = GetDC(NULL);

		gdwPalEntries = GetDeviceCaps(hDC, NUMRESERVED) / 2;
		GetSystemPaletteEntries(hDC, 0, gdwPalEntries, sgCurr);
		for (i = 0; i < gdwPalEntries; i++)
			sgCurr[i].peFlags = 0;

		iStartIndex = 256 - gdwPalEntries;
		GetSystemPaletteEntries(hDC, iStartIndex, gdwPalEntries, &sgCurr[iStartIndex]);
		if (iStartIndex < 256) {
			for (i = iStartIndex; i < 256; i++)
				sgCurr[i].peFlags = 0;
		}

		ReleaseDC(NULL, hDC);
	}
}

void palette_init()
{
	DWORD error_code;

	LoadGamma();
	memcpy(sgCurr, sgLoad, sizeof(sgLoad));
	LoadSysPal();
#ifdef HELLFIRE
	error_code = lpDD->CreatePalette(DDPCAPS_ALLOW256 | DDPCAPS_INITIALIZE | DDPCAPS_8BIT, sgCurr, &lpDDPal, NULL);
#else
	error_code = lpDD->CreatePalette(DDPCAPS_ALLOW256 | DDPCAPS_8BIT, sgCurr, &lpDDPal, NULL);
#endif
	if (error_code)
		ErrDlg(IDD_DIALOG8, error_code, "C:\\Src\\Diablo\\Source\\PALETTE.CPP", 143);
	error_code = lpDDSPrimary->SetPalette(lpDDPal);
#ifndef RGBMODE
	if (error_code)
		ErrDlg(IDD_DIALOG8, error_code, "C:\\Src\\Diablo\\Source\\PALETTE.CPP", 146);
#endif
}

void LoadPalette(const char *pszFileName)
{
	int i;
	void *pBuf;
	BYTE PalData[256][3];

	/// ASSERT: assert(pszFileName);

	WOpenFile(pszFileName, &pBuf, FALSE);
	WReadFile(pBuf, (char *)PalData, sizeof(PalData));
	WCloseFile(pBuf);

	for (i = 0; i < 256; i++) {
		sgLoad[i].peRed = PalData[i][0];
		sgLoad[i].peGreen = PalData[i][1];
		sgLoad[i].peBlue = PalData[i][2];
		sgLoad[i].peFlags = 0;
	}
}

void LoadRndLvlPal(int l)
{
	int rv;
	char szFileName[MAX_PATH];

	if (l == DTYPE_TOWN) {
		LoadPalette("Levels\\TownData\\Town.pal");
	} else {
		rv = random_(0, 4) + 1;
		sprintf(szFileName, "Levels\\L%iData\\L%i_%i.PAL", l, l, rv);
#ifdef HELLFIRE
		if (l == 5) {
			sprintf(szFileName, "NLevels\\L5Data\\L5Base.PAL");
		}
		if (l == 6) {
			if (!UseNestArt) {
				rv++;
			}
			sprintf(szFileName, "NLevels\\L%iData\\L%iBase%i.PAL", 6, 6, rv);
		}
#endif
		LoadPalette(szFileName);
	}
}

void ResetPal()
{
	if (!lpDDSPrimary
	    || lpDDSPrimary->IsLost() != DDERR_SURFACELOST
	    || !lpDDSPrimary->Restore()) {
		SDrawRealizePalette();
	}
}

void IncreaseGamma()
{
	if (gamma_correction < 100) {
		gamma_correction += 5;
		if (gamma_correction > 100)
			gamma_correction = 100;
		ApplyGamma(sgCurr, sgBase, 256);
		palette_update();
	}
}

void DecreaseGamma()
{
	if (gamma_correction > 30) {
		gamma_correction -= 5;
		if (gamma_correction < 30)
			gamma_correction = 30;
		ApplyGamma(sgCurr, sgBase, 256);
		palette_update();
	}
}

int UpdateGamma(int gamma)
{
	if (gamma) {
		gamma_correction = 130 - gamma;
		ApplyGamma(sgCurr, sgBase, 256);
		palette_update();
	}
	return 130 - gamma_correction;
}

static void SetFadeLevel(DWORD fadeval)
{
	int i;

	if (lpDD) {
		for (i = 0; i < 255; i++) { // BUGFIX: should be 256
			sgCurr[i].peRed = (fadeval * sgBase[i].peRed) >> 8;
			sgCurr[i].peGreen = (fadeval * sgBase[i].peGreen) >> 8;
			sgCurr[i].peBlue = (fadeval * sgBase[i].peBlue) >> 8;
		}
		Sleep(3);
		lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL);
		palette_update();
	}
}

void BlackPalette()
{
	SetFadeLevel(0);
}

void PaletteFadeIn(int fr)
{
	int i;

	ApplyGamma(sgBase, sgLoad, 256);
	for (i = 0; i < 256; i += fr) {
		SetFadeLevel(i);
	}
	SetFadeLevel(256);
	memcpy(sgBase, sgLoad, sizeof(sgLoad));
	sgbFadedIn = TRUE;
}

void PaletteFadeOut(int fr)
{
	int i;

	if (sgbFadedIn) {
		for (i = 256; i > 0; i -= fr) {
			SetFadeLevel(i);
		}
		SetFadeLevel(0);
		sgbFadedIn = FALSE;
	}
}

void palette_update_caves()
{
	int i;
	PALETTEENTRY col;

	col = sgCurr[1];
	for (i = 1; i < 31; i++) {
		sgCurr[i].peRed = sgCurr[i + 1].peRed;
		sgCurr[i].peGreen = sgCurr[i + 1].peGreen;
		sgCurr[i].peBlue = sgCurr[i + 1].peBlue;
	}
	sgCurr[i].peRed = col.peRed;
	sgCurr[i].peGreen = col.peGreen;
	sgCurr[i].peBlue = col.peBlue;

	palette_update();
}

#ifdef HELLFIRE
int dword_6E2D58 = 0;
int dword_6E2D54;
void palette_update_crypt()
{
	int i;
	PALETTEENTRY col;

	if (dword_6E2D58 > 1) {
		col = sgCurr[15];
		for (i = 15; i > 1; i--) {
			sgCurr[i].peRed = sgCurr[i - 1].peRed;
			sgCurr[i].peGreen = sgCurr[i - 1].peGreen;
			sgCurr[i].peBlue = sgCurr[i - 1].peBlue;
		}
		sgCurr[i].peRed = col.peRed;
		sgCurr[i].peGreen = col.peGreen;
		sgCurr[i].peBlue = col.peBlue;

		dword_6E2D58 = 0;
	} else {
		dword_6E2D58++;
	}
	if (dword_6E2D54 > 0) {
		col = sgCurr[31];
		for (i = 31; i > 16; i--) {
			sgCurr[i].peRed = sgCurr[i - 1].peRed;
			sgCurr[i].peGreen = sgCurr[i - 1].peGreen;
			sgCurr[i].peBlue = sgCurr[i - 1].peBlue;
		}
		sgCurr[i].peRed = col.peRed;
		sgCurr[i].peGreen = col.peGreen;
		sgCurr[i].peBlue = col.peBlue;
		palette_update();
		dword_6E2D54++;
	} else {
		dword_6E2D54 = 1;
	}
}

int dword_6E2D5C;
int dword_6E2D60;
void palette_update_hive()
{
	int i;
	PALETTEENTRY col;

	if (dword_6E2D60 == 2) {
		col = sgCurr[8];
		for (i = 8; i > 1; i--) {
			sgCurr[i].peRed = sgCurr[i - 1].peRed;
			sgCurr[i].peGreen = sgCurr[i - 1].peGreen;
			sgCurr[i].peBlue = sgCurr[i - 1].peBlue;
		}
		sgCurr[i].peRed = col.peRed;
		sgCurr[i].peGreen = col.peGreen;
		sgCurr[i].peBlue = col.peBlue;
		dword_6E2D60 = 0;
	} else {
		dword_6E2D60++;
	}
	if (dword_6E2D5C == 2) {
		col = sgCurr[15];
		for (i = 15; i > 9; i--) {
			sgCurr[i].peRed = sgCurr[i - 1].peRed;
			sgCurr[i].peGreen = sgCurr[i - 1].peGreen;
			sgCurr[i].peBlue = sgCurr[i - 1].peBlue;
		}
		sgCurr[i].peRed = col.peRed;
		sgCurr[i].peGreen = col.peGreen;
		sgCurr[i].peBlue = col.peBlue;
		palette_update();
		dword_6E2D5C = 0;
	} else {
		dword_6E2D5C++;
	}
}

#endif
#ifndef SPAWN
void palette_update_quest_palette(int n)
{
	int i;

	for (i = 32 - n; i >= 0; i--) {
		sgBase[i] = sgLoad[i];
	}
	ApplyGamma(sgCurr, sgBase, 32);
	palette_update();
}
#endif

#ifndef HELLFIRE
BOOL palette_get_color_cycling()
{
	return color_cycling_enabled;
}

BOOL palette_set_color_cycling(BOOL enabled)
{
	color_cycling_enabled = enabled;
	return enabled;
}
#endif
