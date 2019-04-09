//HEADER_GOES_HERE
#ifndef __SYNC_H__
#define __SYNC_H__

extern WORD sync_word_6AA708[MAXMONSTERS];
extern int sgnMonsters;
extern WORD sgwLRU[MAXMONSTERS];
extern int sgnSyncItem;

DWORD sync_all_monsters(const BYTE *pbBuf, DWORD dwMaxLen);
void sync_one_monster();
BOOL sync_monster_active(TSyncMonster *p);
void sync_monster_pos(TSyncMonster *p, int ndx);
BOOL sync_monster_active2(TSyncMonster *p);
void SyncPlrInv(TSyncHeader *pHdr);
DWORD sync_update(int pnum, const BYTE *pbBuf);
void sync_monster(int pnum, const TSyncMonster *p);
void sync_init();

#endif /* __SYNC_H__ */
