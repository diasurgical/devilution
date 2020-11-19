/**
 * @file towners.h
 *
 * Interface of functionality for loading and spawning towners.
 */
#ifndef __TOWNERS_H__
#define __TOWNERS_H__

extern TownerStruct towner[NUM_TOWNERS];

void InitTowners();
void FreeTownerGFX();
void ProcessTowners();
ItemStruct *PlrHasItem(int pnum, int item, int &i);
void TalkToTowner(int p, int t);

/* data */

extern QuestTalkData Qtalklist[];

#endif /* __TOWNERS_H__ */
