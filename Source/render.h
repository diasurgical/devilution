/**
 * @file render.h
 *
 * Interface of functionality for rendering the level tiles.
 */
#ifndef __RENDER_H__
#define __RENDER_H__

void drawUpperScreen(BYTE *pBuff);
void drawLowerScreen(BYTE *pBuff);
void world_draw_black_tile(BYTE *pBuff);

/* rdata */

extern int WorldBoolFlag;
extern DWORD gdwCurrentMask;
extern BYTE *gpCelFrame;
extern DWORD *gpDrawMask;
extern DWORD RightMask[TILE_WIDTH];
extern DWORD LeftMask[TILE_WIDTH];
extern int WorldTbl3x16[48];
extern int WorldTbl17_1[17];
extern int WorldTbl17_2[17];

#endif /* __RENDER_H__ */
