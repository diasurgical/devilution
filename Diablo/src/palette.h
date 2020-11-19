/**
 * @file palette.h
 *
 * Interface of functions for handling the engines color palette.
 */
#ifndef __PALETTE_H__
#define __PALETTE_H__

extern PALETTEENTRY system_palette[256];

void SaveGamma();
void palette_init();
void LoadPalette(const char *pszFileName);
void LoadRndLvlPal(int l);
void ResetPal();
void IncreaseGamma();
void DecreaseGamma();
int UpdateGamma(int gamma);
void BlackPalette();
void PaletteFadeIn(int fr);
void PaletteFadeOut(int fr);
void palette_update_caves();
#ifdef HELLFIRE
void palette_update_crypt();
void palette_update_hive();
#endif
void palette_update_quest_palette(int n);
#ifndef HELLFIRE
BOOL palette_get_color_cycling();
BOOL palette_set_color_cycling(BOOL enabled);
#endif

#endif /* __PALETTE_H__ */
