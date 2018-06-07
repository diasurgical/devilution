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

//debug
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