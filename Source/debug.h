//HEADER_GOES_HERE
#ifndef __DEBUG_H__
#define __DEBUG_H__

extern void *pSquareCel;
extern char dMonsDbg[17][112][112];
extern char dFlagDbg[17][112][112];

void __cdecl LoadDebugGFX();
void __cdecl FreeDebugGFX();
void __cdecl CheckDungeonClear();
#ifdef _DEBUG
void __cdecl GiveGoldCheat();
void __cdecl StoresCheat();
void __cdecl TakeGoldCheat();
void __cdecl MaxSpellsCheat();
void __fastcall PrintDebugPlayer(bool bNextPlayer);
void __cdecl PrintDebugQuest();
void __fastcall PrintDebugMonster(int m);
void __cdecl GetDebugMonster();
void __cdecl NextDebugMonster();
#endif

#endif /* __DEBUG_H__ */
