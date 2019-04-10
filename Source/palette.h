//HEADER_GOES_HERE
#ifndef __PALETTE_H__
#define __PALETTE_H__

extern PALETTEENTRY logical_palette[256];
extern PALETTEENTRY system_palette[256];
extern PALETTEENTRY orig_palette[256];
extern int gdwPalEntries;

void SaveGamma();
void palette_init();
void LoadGamma();
void LoadSysPal();
void LoadPalette(char *pszFileName);
void LoadRndLvlPal(int l);
void ResetPal();
void IncreaseGamma();
void palette_update();
void ApplyGamma(PALETTEENTRY *dst, PALETTEENTRY *src, int n);
void DecreaseGamma();
int UpdateGamma(int gamma);
void BlackPalette();
void SetFadeLevel(DWORD fadeval);
void PaletteFadeIn(int fr);
void PaletteFadeOut(int fr);
void palette_update_caves();
void palette_update_quest_palette(int n);
BOOL palette_get_colour_cycling();
BOOL palette_set_color_cycling(BOOL enabled);

/* rdata */

/* data */

extern int gamma_correction; // idb
extern BOOL color_cycling_enabled;

#endif /* __PALETTE_H__ */
