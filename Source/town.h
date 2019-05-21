//HEADER_GOES_HERE
#ifndef __TOWN_H__
#define __TOWN_H__

void town_clear_upper_buf(BYTE *pBuff);
void town_clear_low_buf(BYTE *pBuff);
void town_special_lower(BYTE *pBuff, int nCel);
void town_special_upper(BYTE *pBuff, int nCel);
void town_draw_clipped_e_flag(BYTE *pBuff, int x, int y, int sx, int sy);
void town_draw_clipped_town(BYTE *pBuff, int x, int y, int sx, int sy, BOOL some_flag);
void town_draw_lower(int x, int y, int sx, int sy, int a5, int some_flag);
void town_draw_clipped_e_flag_2(BYTE *pBuff, int x, int y, int a4, int a5, int sx, int sy);
void town_draw_clipped_town_2(BYTE *pBuff, int x, int y, int a4, int a5, int sx, int sy, BOOL some_flag);
void town_draw_lower_2(int x, int y, int sx, int sy, int a5, int a6, int some_flag);
void town_draw_e_flag(BYTE *pBuff, int x, int y, int a4, int dir, int sx, int sy);
void town_draw_town_all(BYTE *pBuff, int x, int y, int a4, int dir, int sx, int sy, BOOL some_flag);
void town_draw_upper(int x, int y, int sx, int sy, int a5, int a6, int some_flag);
void T_DrawGame(int x, int y);
void T_DrawZoom(int x, int y);
void T_DrawView(int StartX, int StartY);
void SetTownMicros();
void T_FillSector(unsigned char *P3Tiles, unsigned char *pSector, int xi, int yi, int w, int h);
void T_FillTile(unsigned char *P3Tiles, int xx, int yy, int t);
void T_Pass3();
void CreateTown(int entry);

#endif /* __TOWN_H__ */
