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

//loadsave
extern void *tbuff;

void __fastcall LoadGame(bool firstflag);
char __cdecl BLoad();
int __cdecl ILoad();
int __cdecl ILoad_2();
bool __cdecl OLoad();
void __fastcall LoadPlayer(int i);
void __fastcall LoadMonster(int i);
void __fastcall LoadMissile(int i);
void __fastcall LoadObject(int i);
void __fastcall LoadItem(int i);
void __fastcall LoadPremium(int i);
void __fastcall LoadQuest(int i);
void __fastcall LoadLighting(int i);
void __fastcall LoadVision(int i);
void __fastcall LoadPortal(int i);
void __cdecl SaveGame();
void __fastcall BSave(char v);
void __fastcall ISave(int v);
void __fastcall ISave_2(int v);
void __fastcall OSave(unsigned char v);
void __fastcall SavePlayer(int i);
void __fastcall SaveMonster(int i);
void __fastcall SaveMissile(int i);
void __fastcall SaveObject(int i);
void __fastcall SaveItem(int i);
void __fastcall SavePremium(int i);
void __fastcall SaveQuest(int i);
void __fastcall SaveLighting(int i);
void __fastcall SaveVision(int i);
void __fastcall SavePortal(int i);
void __cdecl SaveLevel();
void __cdecl LoadLevel();