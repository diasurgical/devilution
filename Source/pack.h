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
