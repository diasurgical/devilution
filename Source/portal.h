//HEADER_GOES_HERE
#ifndef __PORTAL_H__
#define __PORTAL_H__

extern PortalStruct portal[MAXPORTAL];
extern int portalindex;

void __cdecl InitPortals();
void __fastcall SetPortalStats(int i, BOOL o, int x, int y, int lvl, int lvltype);
void __fastcall AddWarpMissile(int i, int x, int y);
void __cdecl SyncPortals();
void __fastcall AddInTownPortal(int i);
void __fastcall ActivatePortal(int i, int x, int y, int lvl, int lvltype, BOOL sp);
void __fastcall DeactivatePortal(int i);
BOOL __fastcall PortalOnLevel(int i);
void __fastcall RemovePortalMissile(int id);
void __fastcall SetCurrentPortal(int p);
void __cdecl GetPortalLevel();
void __cdecl GetPortalLvlPos();
BOOL __fastcall PosOkPortal(int lvl, int x, int y);

/* rdata */
extern int WarpDropX[MAXPORTAL];
extern int WarpDropY[MAXPORTAL];

#endif /* __PORTAL_H__ */
