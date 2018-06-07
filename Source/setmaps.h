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

int __fastcall ObjIndex(int x, int y);
void __cdecl AddSKingObjs();
void __cdecl AddSChamObjs();
void __cdecl AddVileObjs();
void __fastcall DRLG_SetMapTrans(char *sFileName);
void __cdecl LoadSetMap();

/* rdata */
extern RECT8 QSRects[32];
extern char *quest_level_names[];