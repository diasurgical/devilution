//HEADER_GOES_HERE
#ifndef __CURSOR_H__
#define __CURSOR_H__

extern int cursH;      // weak
extern int icursH28;   // idb
extern int cursW;      // idb
extern int pcursmonst; // idb
extern int icursW28;   // idb
extern void *pCursCels;
extern int icursH;        // weak
extern char pcursinvitem; // weak
extern int icursW;        // weak
extern char pcursitem;    // weak
extern char pcursobj;     // weak
extern char pcursplr;     // weak
extern int cursmx;
extern int cursmy;
extern int pcurstemp; // weak
extern int pcurs;        // idb

void InitCursor();
void FreeCursor();
void SetICursor(int i);
void SetCursor_(int i);
void NewCursor(int i);
void InitLevelCursor();
void CheckTown();
void CheckRportal();
void CheckCursMove();

/* rdata */
extern const int InvItemWidth[180];
extern const int InvItemHeight[180];

#endif /* __CURSOR_H__ */
