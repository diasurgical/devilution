/**
 * @file scrollrt.h
 *
 * Interface of functionality for rendering the dungeons, monsters and calling other render routines.
 */
#ifndef __SCROLLRT_H__
#define __SCROLLRT_H__

extern int nLVal;
extern int nBuffWTbl[1024];
extern BYTE *glClipY;
extern DWORD gdwPNum;
extern char gbPartialTrans;
extern int nTrans;
extern int gnPieceNum;
#ifdef HELLFIRE
extern BOOLEAN AutoMapShowItems;
#endif

void ClearCursor();
void DrawMissile(int x, int y, int sx, int sy, int CelSkip, int CelCap, BOOL pre);
void DrawClippedMissile(int x, int y, int sx, int sy, int CelSkip, int CelCap, BOOL pre);
void DrawDeadPlayer(int x, int y, int sx, int sy, int CelSkip, int CelCap, BOOL clipped);
void DrawView(int StartX, int StartY);
void ClearScreenBuffer();
#ifdef _DEBUG
void ScrollView();
void EnableFrameCount();
#endif
void scrollrt_draw_game_screen(BOOL draw_cursor);
void DrawAndBlit();

#endif /* __SCROLLRT_H__ */
