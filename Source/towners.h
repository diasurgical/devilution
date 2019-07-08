//HEADER_GOES_HERE
#ifndef __TOWNERS_H__
#define __TOWNERS_H__

extern TownerStruct towner[16];

int GetActiveTowner(int t);
void SetTownerGPtrs(BYTE *pData, BYTE **pAnim);
void NewTownerAnim(int tnum, BYTE *pAnim, int numFrames, int Delay);
void InitTownerInfo(int i, int w, int sel, int t, int x, int y, int ao, int tp);
void InitQstSnds(int i);
void InitSmith();
void InitBarOwner();
void InitTownDead();
void InitWitch();
void InitBarmaid();
void InitBoy();
void InitHealer();
void InitTeller();
void InitDrunk();
void InitCows();
void InitTowners();
void FreeTownerGFX();
void TownCtrlMsg(int i);
void TownBlackSmith();
void TownBarOwner();
void TownDead();
void TownHealer();
void TownStory();
void TownDrunk();
void TownBoy();
void TownWitch();
void TownBarMaid();
void TownCow();
void ProcessTowners();
ItemStruct *PlrHasItem(int pnum, int item, int *i);
void TownerTalk(int first, int t);
void TalkToTowner(int p, int t);
void CowSFX(int pnum);

/* data */

extern QuestTalkData Qtalklist[11];

#endif /* __TOWNERS_H__ */
