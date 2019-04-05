//HEADER_GOES_HERE
#ifndef __INV_H__
#define __INV_H__

extern BOOL invflag;
extern int drawsbarflag; // idb

void __cdecl FreeInvGFX();
void __cdecl InitInv();
void __fastcall InvDrawSlotBack(int X, int Y, int W, int H);
void __cdecl DrawInv();
void __cdecl DrawInvBelt();
int __fastcall AutoPlace(int pnum, int ii, int sx, int sy, int saveflag);
int __fastcall SpecialAutoPlace(int pnum, int ii, int sx, int sy, int saveflag);
int __fastcall GoldAutoPlace(int pnum);
int __fastcall WeaponAutoPlace(int pnum);
int __fastcall SwapItem(ItemStruct *a, ItemStruct *b);
void __fastcall CheckInvPaste(int pnum, int mx, int my);
void __fastcall CheckInvSwap(int pnum, BYTE bLoc, int idx, WORD wCI, int seed, BOOL bId);
void __fastcall CheckInvCut(int pnum, int mx, int my);
void __fastcall inv_update_rem_item(int pnum, BYTE iv);
void __fastcall RemoveInvItem(int pnum, int iv);
void __fastcall RemoveSpdBarItem(int pnum, int iv);
void __cdecl CheckInvItem();
void __cdecl CheckInvScrn();
void __fastcall CheckItemStats(int pnum);
void __fastcall CheckBookLevel(int pnum);
void __fastcall CheckQuestItem(int pnum);
void __fastcall InvGetItem(int pnum, int ii);
void __fastcall AutoGetItem(int pnum, int ii);
int __fastcall FindGetItem(int indx, WORD ci, int iseed);
void __fastcall SyncGetItem(int x, int y, int idx, WORD ci, int iseed);
BOOL __fastcall CanPut(int x, int y);
BOOL __cdecl TryInvPut();
void __fastcall DrawInvMsg(char *msg);
int __fastcall InvPutItem(int pnum, int x, int y);
int __fastcall SyncPutItem(int pnum, int x, int y, int idx, WORD icreateinfo, int iseed, int Id, int dur, int mdur, int ch, int mch, int ivalue, unsigned int ibuff);
int __cdecl CheckInvHLight();
void __fastcall RemoveScroll(int pnum);
BOOL __cdecl UseScroll();
void __fastcall UseStaffCharge(int pnum);
BOOL __cdecl UseStaff();
void __cdecl StartGoldDrop();
int __fastcall UseInvItem(int pnum, int cii);
void __cdecl DoTelekinesis();
int __fastcall CalculateGold(int pnum);
int __cdecl DropItemBeforeTrig();

/* data */

extern int AP2x2Tbl[10]; // weak

#endif /* __INV_H__ */
