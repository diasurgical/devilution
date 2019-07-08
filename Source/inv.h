//HEADER_GOES_HERE
#ifndef __INV_H__
#define __INV_H__

extern BOOL invflag;
extern BOOL drawsbarflag;

void FreeInvGFX();
void InitInv();
void InvDrawSlotBack(int X, int Y, int W, int H);
void DrawInv();
void DrawInvBelt();
BOOL AutoPlace(int pnum, int ii, int sx, int sy, BOOL saveflag);
BOOL SpecialAutoPlace(int pnum, int ii, int sx, int sy, BOOL saveflag);
BOOL GoldAutoPlace(int pnum);
BOOL WeaponAutoPlace(int pnum);
int SwapItem(ItemStruct *a, ItemStruct *b);
void CheckInvPaste(int pnum, int mx, int my);
void CheckInvSwap(int pnum, BYTE bLoc, int idx, WORD wCI, int seed, BOOL bId);
void CheckInvCut(int pnum, int mx, int my);
void inv_update_rem_item(int pnum, BYTE iv);
void RemoveInvItem(int pnum, int iv);
void RemoveSpdBarItem(int pnum, int iv);
void CheckInvItem();
void CheckInvScrn();
void CheckItemStats(int pnum);
void CheckBookLevel(int pnum);
void CheckQuestItem(int pnum);
void InvGetItem(int pnum, int ii);
void AutoGetItem(int pnum, int ii);
int FindGetItem(int idx, WORD ci, int iseed);
void SyncGetItem(int x, int y, int idx, WORD ci, int iseed);
BOOL CanPut(int x, int y);
BOOL TryInvPut();
void DrawInvMsg(char *msg);
int InvPutItem(int pnum, int x, int y);
int SyncPutItem(int pnum, int x, int y, int idx, WORD icreateinfo, int iseed, int Id, int dur, int mdur, int ch, int mch, int ivalue, DWORD ibuff);
char CheckInvHLight();
void RemoveScroll(int pnum);
BOOL UseScroll();
void UseStaffCharge(int pnum);
BOOL UseStaff();
void StartGoldDrop();
BOOL UseInvItem(int pnum, int cii);
void DoTelekinesis();
int CalculateGold(int pnum);
BOOL DropItemBeforeTrig();

/* data */

extern int AP2x2Tbl[10];

#endif /* __INV_H__ */
