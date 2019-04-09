//HEADER_GOES_HERE
#ifndef __AUTOMAP_H__
#define __AUTOMAP_H__

extern WORD automaptype[512];
extern BOOL automapflag; // idb
extern char AmShiftTab[32];
extern unsigned char automapview[DMAXX][DMAXY];
extern int AutoMapScale;   // idb
extern int AutoMapXOfs;    // weak
extern int AutoMapYOfs;    // weak
extern int AutoMapPosBits; // weak
extern int AutoMapXPos;    // weak
extern int AutoMapYPos;    // weak
extern int AMPlayerX;      // weak
extern int AMPlayerY;      // weak

void InitAutomapOnce();
void InitAutomap();
void StartAutomap();
void AutomapUp();
void AutomapDown();
void AutomapLeft();
void AutomapRight();
void AutomapZoomIn();
void AutomapZoomOut();
void DrawAutomap();
void DrawAutomapType(int screen_x, int screen_y, WORD automap_type);
void DrawAutomapPlr();
WORD GetAutomapType(int x, int y, BOOL view);
void DrawAutomapGame();
void SetAutomapView(int x, int y);
void AutomapZoomReset();

#endif /* __AUTOMAP_H__ */
