//HEADER_GOES_HERE
#ifndef __ENGINE_H__
#define __ENGINE_H__

//offset 0
//pCelBuff->pFrameTable[0]

extern char gbPixelCol;  // automap pixel color 8-bit (palette entry)
extern int dword_52B970; // bool flip - if y < x
extern int orgseed;      // weak
extern int SeedCount;    // weak
extern int dword_52B99C; // bool valid - if x/y are in bounds

void CelDrawDatOnly(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelDecodeOnly(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelDecDatOnly(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth);
void CelDrawHdrOnly(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDecodeHdrOnly(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDecDatLightOnly(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelDecDatLightTrans(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelDecodeLightOnly(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelDecodeHdrLightOnly(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDecodeHdrLightTrans(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDrawHdrLightRed(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void Cel2DecDatOnly(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void Cel2DrawHdrOnly(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cel2DecodeHdrOnly(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cel2DecDatLightOnly(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void Cel2DecDatLightTrans(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void Cel2DecodeHdrLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cel2DecodeLightTrans(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cel2DrawHdrLightRed(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void CelDecodeRect(BYTE *pBuff, int always_0, int hgt, int wdt, BYTE *pCelBuff, int nCel, int nWidth);
void CelDecodeClr(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void CelDrawHdrClrHL(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void ENG_set_pixel(int sx, int sy, BYTE col);
void engine_draw_pixel(int sx, int sy);
void DrawLine(int x0, int y0, int x1, int y1, UCHAR col);
int GetDirection(int x1, int y1, int x2, int y2);
void SetRndSeed(int s);
int GetRndSeed();
int random(BYTE idx, int v);
void mem_init_mutex();
void mem_atexit_mutex();
void __cdecl mem_free_mutex(void);
unsigned char *DiabloAllocPtr(int dwBytes);
void mem_free_dbg(void *p);
BYTE *LoadFileInMem(char *pszName, int *pdwFileLen);
void LoadFileWithMem(char *pszName, void *buf);
void Cl2ApplyTrans(BYTE *p, BYTE *ttbl, int nCel);
void Cl2DecodeFrm1(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DecDatFrm1(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void Cl2DecodeFrm2(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DecDatFrm2(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, char col);
void Cl2DecodeFrm3(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void Cl2DecDatLightTbl1(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, BYTE *pTable);
void Cl2DecodeLightTbl(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DecodeFrm4(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DecDatFrm4(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void Cl2DecodeClrHL(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void Cl2DecDatClrHL(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, char col);
void Cl2DecodeFrm5(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light);
void Cl2DecDatLightTbl2(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, BYTE *pTable);
void Cl2DecodeFrm6(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap);
void PlayInGameMovie(char *pszMovie);

/* rdata */

extern const int engine_inf;      // weak
extern const int rand_increment;  // unused
extern const int rand_multiplier; // unused

#endif /* __ENGINE_H__ */
