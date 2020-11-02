/**
 * @file debug.h
 *
 * Interface of debug functions.
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

extern BYTE *pSquareCel;

void LoadDebugGFX();
void FreeDebugGFX();
#ifdef _DEBUG
void init_seed_desync();
void seed_desync_index_get();
void seed_desync_index_set();
void seed_desync_check(int seed);
#endif
void CheckDungeonClear();
#ifdef _DEBUG
void GiveGoldCheat();
void StoresCheat();
void TakeGoldCheat();
void MaxSpellsCheat();
void SetAllSpellsCheat();
void PrintDebugPlayer(BOOL bNextPlayer);
void PrintDebugQuest();
void GetDebugMonster();
void NextDebugMonster();
#endif

#endif /* __DEBUG_H__ */
