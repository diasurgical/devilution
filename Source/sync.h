/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

//sync
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