/**
 * @file engine.h
 *
 *  of basic engine helper functions:
 * - Sprite blitting
 * - Drawing
 * - Angle calculation
 * - RNG
 * - Memory allocation
 * - File loading
 * - Video playback
 */
#ifndef __ENGINE_H__
#define __ENGINE_H__

__FINLINE BYTE *CelGetFrame(BYTE *pCelBuff, int nCel, int *nDataSize);

void CelBlit(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelDraw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelBlitFrame(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth);
void CelClippedDraw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelClippedBlit(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelBlitLight(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelBlitLightTrans(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelDrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelClippedDrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelClippedBlitLightTrans(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDrawLightRed(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void CelBlitSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelClippedDrawSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelClippedBlitSafe(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelBlitLightSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelBlitLightTransSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelDrawLightSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelClippedBlitLightTransSafe(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDrawLightRedSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void CelBlitWidth(BYTE *pBuff, int x, int y, int wdt, BYTE *pCelBuff, int nCel, int nWidth);
void CelBlitOutline(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelBlitOutlineSafe(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void ENG_set_pixel(int sx, int sy, BYTE col);
void engine_draw_pixel(int sx, int sy);
void DrawLine(int x0, int y0, int x1, int y1, BYTE col);
int GetDirection(int x1, int y1, int x2, int y2);
void SetRndSeed(int s);
int GetRndSeed();
int random_(BYTE idx, int v);
void engine_debug_trap(BOOL show_cursor);
BYTE *DiabloAllocPtr(DWORD dwBytes);
void mem_free_dbg(void *p);
BYTE *LoadFileInMem(const char *pszName, DWORD *pdwFileLen);
DWORD LoadFileWithMem(const char *pszName, BYTE *p);
void Cl2ApplyTrans(BYTE *p, BYTE *ttbl, int nCel);
void Cl2Draw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DrawOutline(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DrawLightTbl(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void Cl2DrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DrawSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DrawOutlineSafe(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DrawLightTblSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void Cl2DrawLightSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void PlayInGameMovie(const char *pszMovie);

#endif /* __ENGINE_H__ */
