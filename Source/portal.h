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

//portal
extern PortalStruct portal[4];
extern int portalindex;
// int END_portalstruct; // weak

void __cdecl InitPortals();
void __fastcall SetPortalStats(int i, int o, int x, int y, int lvl, int lvltype);
void __fastcall AddWarpMissile(int i, int x, int y);
void __cdecl SyncPortals();
void __fastcall AddInTownPortal(int i);
void __fastcall ActivatePortal(int i, int x, int y, int lvl, int lvltype, int sp);
void __fastcall DeactivatePortal(int i);
bool __fastcall PortalOnLevel(int i);
void __fastcall RemovePortalMissile(int id);
void __fastcall SetCurrentPortal(int p);
void __cdecl GetPortalLevel();
void __cdecl GetPortalLvlPos();
bool __fastcall PosOkPortal(int level, int x, int y);

/* rdata */
extern int WarpDropX[4];
extern int WarpDropY[4];
