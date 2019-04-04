//HEADER_GOES_HERE
#ifndef __SYNC_H__
#define __SYNC_H__

extern WORD sync_word_6AA708[MAXMONSTERS];
extern int sgnMonsters; // weak
extern WORD sgwLRU[MAXMONSTERS];
extern int sgnSyncItem;

int __fastcall sync_all_monsters(TSyncHeader *packet, int size);
void __cdecl sync_one_monster();
int __fastcall sync_monster_active(TSyncMonster *packet);
void __fastcall sync_monster_pos(TSyncMonster *packet, int mon_id);
int __fastcall sync_monster_active2(TSyncMonster *packet);
void __fastcall SyncPlrInv(TSyncHeader *pSync);
int __fastcall sync_update(int pnum, TSyncHeader *packet);
void __fastcall sync_monster(int pnum, TSyncMonster *packet);
void __cdecl sync_init();

#endif /* __SYNC_H__ */
