//HEADER_GOES_HERE
#ifndef __TOWNERS_H__
#define __TOWNERS_H__

extern TownerStruct towner[16];

int __fastcall GetActiveTowner(int t);
void __fastcall SetTownerGPtrs(BYTE *pData, BYTE **pAnim); /* unsigned char *+** */
void __fastcall NewTownerAnim(int tnum, unsigned char *pAnim, int numFrames, int Delay);
void __fastcall InitTownerInfo(int i, int w, int sel, int t, int x, int y, int ao, int tp);
void __fastcall InitQstSnds(int i);
void __cdecl InitSmith();
void __cdecl InitBarOwner();
void __cdecl InitTownDead();
void __cdecl InitWitch();
void __cdecl InitBarmaid();
void __cdecl InitBoy();
void __cdecl InitHealer();
void __cdecl InitTeller();
void __cdecl InitDrunk();
void __cdecl InitCows();
void __cdecl InitTowners();
void __cdecl FreeTownerGFX();
void __fastcall TownCtrlMsg(int i);
void __cdecl TownBlackSmith();
void __cdecl TownBarOwner();
void __cdecl TownDead();
void __cdecl TownHealer();
void __cdecl TownStory();
void __cdecl TownDrunk();
void __cdecl TownBoy();
void __cdecl TownWitch();
void __cdecl TownBarMaid();
void __cdecl TownCow();
void __cdecl ProcessTowners();
ItemStruct *__fastcall PlrHasItem(int pnum, int item, int *i);
void __fastcall TownerTalk(int t);
void __fastcall TalkToTowner(int p, int t);
void __fastcall CowSFX(int pnum);

/* data */

extern QuestTalkData Qtalklist[11];

#endif /* __TOWNERS_H__ */
