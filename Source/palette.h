//HEADER_GOES_HERE
#ifndef __PALETTE_H__
#define __PALETTE_H__

extern PALETTEENTRY logical_palette[256];
extern int palette_cpp_init_value; // weak
extern PALETTEENTRY system_palette[256];
extern PALETTEENTRY orig_palette[256];
extern UINT gdwPalEntries;

void __cdecl palette_cpp_init();
void __cdecl palette_save_gamme();
void __cdecl palette_init();
void __cdecl palette_load_gamma();
void __cdecl LoadSysPal();
void __fastcall LoadPalette(char *pszFileName);
void __fastcall LoadRndLvlPal(int l);
void __cdecl ResetPal();
void __cdecl palette_inc_gamma();
void __cdecl palette_update();
void __fastcall palette_apply_gamma_correction(PALETTEENTRY *dst, PALETTEENTRY *src, int n);
void __cdecl palette_dec_gamma();
int __fastcall palette_update_gamma(int gamma);
void __cdecl BlackPalette();
void __fastcall SetFadeLevel(int brightness);
void __fastcall PaletteFadeIn(int fr);
void __fastcall PaletteFadeOut(int fr);
void __cdecl palette_update_caves();
void __fastcall palette_update_quest_palette(int n);
bool __cdecl palette_get_colour_cycling();
void __fastcall palette_set_color_cycling(bool enabled);

/* data */

extern int palette_inf; // weak

/* rdata */

extern int gamma_correction; // idb
extern int color_cycling_enabled; // idb
extern bool sgbFadedIn;

#endif /* __PALETTE_H__ */
