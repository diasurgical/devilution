//HEADER_GOES_HERE

int __fastcall ObjIndex(int x, int y);
void __cdecl AddSKingObjs();
void __cdecl AddSChamObjs();
void __cdecl AddVileObjs();
void __fastcall DRLG_SetMapTrans(char *sFileName);
void __cdecl LoadSetMap();

/* rdata */
extern RECT8 QSRects[32];
extern char *quest_level_names[];