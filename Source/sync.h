//HEADER_GOES_HERE
#ifndef __SYNC_H__
#define __SYNC_H__

extern short sync_word_6AA708[200];
extern int dword_6AA898; // weak
extern short sync_word_6AA89C[200];
extern int dword_6AAA2C[2];
extern int sgnSyncPInv; // weak

int __fastcall sync_all_monsters(TSyncHeader *packet, int size);
void __cdecl sync_one_monster();
int __fastcall sync_monster_active(TSyncMonster *packet);
int __fastcall sync_monster_pos(TSyncMonster *packet, int mon_id);
int __fastcall sync_monster_active2(TSyncMonster *packet);
char __fastcall SyncPlrInv(TSyncHeader *pItem);
int __fastcall SyncData(int pnum, TSyncHeader *packet);
void __fastcall sync_monster_data(int pnum, TSyncMonster *packet);
void __cdecl sync_clear_pkt();

#endif /* __SYNC_H__ */
