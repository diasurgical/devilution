//HEADER_GOES_HERE

//pack
extern int pack_cpp_init_value; // weak

void __cdecl pack_cpp_init();
void __fastcall PackPlayer(PkPlayerStruct *pPack, int pnum, bool manashield);
void __fastcall PackItem(PkItemStruct *id, ItemStruct *is);
void __fastcall VerifyGoldSeeds(PlayerStruct *pPlayer);
void __fastcall UnPackPlayer(PkPlayerStruct *pPack, int pnum, bool killok);
void __fastcall UnPackItem(PkItemStruct *is, ItemStruct *id);

/* data */

extern int pack_inf; // weak
