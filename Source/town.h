/**
 * @file town.h
 *
 * Interface of functionality for rendering the town, towners and calling other render routines.
 */
#ifndef __TOWN_H__
#define __TOWN_H__

void town_draw_clipped_town(BYTE *pBuff, int sx, int sy, int dx, int dy, int eflag);
void town_draw_clipped_town_2(BYTE *pBuff, int sx, int sy, int row, int CelSkip, int dx, int dy, int eflag);
void town_draw_town_all(BYTE *pBuff, int x, int y, int row, int CelCap, int sx, int sy, int eflag);
void T_DrawView(int StartX, int StartY);
#ifdef HELLFIRE
void TownOpenHive();
void TownOpenGrave();
#endif
void CreateTown(int entry);

#endif /* __TOWN_H__ */
