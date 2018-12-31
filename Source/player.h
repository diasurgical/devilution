//HEADER_GOES_HERE
#ifndef __PLAYER_H__
#define __PLAYER_H__

extern int plr_lframe_size; // idb
extern int plr_wframe_size; // idb
extern UCHAR plr_gfx_flag;
extern int plr_aframe_size;       // idb
extern int myplr;
extern PlayerStruct plr[MAX_PLRS];
extern int plr_fframe_size; // idb
extern int plr_qframe_size; // idb
extern BOOL deathflag;      // idb
extern int plr_hframe_size; // idb
extern int plr_bframe_size; // idb
extern UCHAR plr_gfx_bflag;
extern int plr_sframe_size; // idb
extern int deathdelay;      // weak
extern int plr_dframe_size; // idb

void __fastcall SetPlayerGPtrs(UCHAR *pData, UCHAR **pAnim); /* unsigned char *+** */
void __fastcall LoadPlrGFX(int pnum, player_graphic gfxflag);
void __fastcall InitPlayerGFX(int pnum);
void __fastcall InitPlrGFXMem(int pnum);
DWORD __fastcall GetPlrGFXSize(char *szCel);
void __fastcall FreePlayerGFX(int pnum);
void __fastcall NewPlrAnim(int pnum, unsigned char *Peq, int numFrames, int Delay, int width);
void __fastcall ClearPlrPVars(int pnum);
void __fastcall SetPlrAnims(int pnum);
void __fastcall ClearPlrRVars(PlayerStruct *p);
void __fastcall CreatePlayer(int pnum, char c);
int __fastcall CalcStatDiff(int pnum);
void __fastcall NextPlrLevel(int pnum);
void __fastcall AddPlrExperience(int pnum, int lvl, int exp);
void __fastcall AddPlrMonstExper(int lvl, int exp, char pmask);
void __fastcall InitPlayer(int pnum, BOOL FirstTime);
void __cdecl InitMultiView();
void __fastcall InitPlayerLoc(int pnum, BOOL flag);
BOOL __fastcall SolidLoc(int x, int y);
BOOL __fastcall PlrDirOK(int pnum, int dir);
void __fastcall PlrClrTrans(int x, int y);
void __fastcall PlrDoTrans(int x, int y);
void __fastcall SetPlayerOld(int pnum);
void __fastcall FixPlayerLocation(int pnum, int dir);
void __fastcall StartStand(int pnum, int dir);
void __fastcall StartWalkStand(int pnum);
void __fastcall PM_ChangeLightOff(int pnum);
void __fastcall PM_ChangeOffset(int pnum);
void __fastcall StartWalk(int pnum, int xvel, int yvel, int xadd, int yadd, int EndDir, int sdir);
void __fastcall StartWalk2(int pnum, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int EndDir, int sdir);
void __fastcall StartWalk3(int pnum, int xvel, int yvel, int xoff, int yoff, int xadd, int yadd, int mapx, int mapy, int EndDir, int sdir);
void __fastcall StartAttack(int pnum, int d);
void __fastcall StartRangeAttack(int pnum, int d, int cx, int cy);
void __fastcall StartPlrBlock(int pnum, int dir);
void __fastcall StartSpell(int pnum, int d, int cx, int cy);
void __fastcall FixPlrWalkTags(int pnum);
void __fastcall RemovePlrFromMap(int pnum);
void __fastcall StartPlrHit(int pnum, int dam, BOOL forcehit);
void __fastcall RespawnDeadItem(ItemStruct *itm, int x, int y);
void __fastcall StartPlayerKill(int pnum, int earflag);
void __fastcall PlrDeadItem(int pnum, ItemStruct *itm, int xx, int yy);
void __fastcall DropHalfPlayersGold(int pnum);
void __fastcall SyncPlrKill(int pnum, int earflag);
void __fastcall j_StartPlayerKill(int pnum, int earflag);
void __fastcall RemovePlrMissiles(int pnum);
void __fastcall InitLevelChange(int pnum);
void __fastcall StartNewLvl(int pnum, int fom, int lvl);
void __fastcall RestartTownLvl(int pnum);
void __fastcall StartWarpLvl(int pnum, int pidx);
BOOL __fastcall PM_DoStand(int pnum);
BOOL __fastcall PM_DoNewLvl(int pnum);
BOOL __fastcall PM_DoWalk(int pnum);
BOOL __fastcall PM_DoWalk2(int pnum);
BOOL __fastcall PM_DoWalk3(int pnum);
BOOL __fastcall WeaponDur(int pnum, int durrnd);
BOOL __fastcall PlrHitMonst(int pnum, int m);
BOOL __fastcall PlrHitPlr(int pnum, char p);
BOOL __fastcall PlrHitObj(int pnum, int mx, int my);
BOOL __fastcall PM_DoAttack(int pnum);
BOOL __fastcall PM_DoRangeAttack(int pnum);
void __fastcall ShieldDur(int pnum);
BOOL __fastcall PM_DoBlock(int pnum);
BOOL __fastcall PM_DoSpell(int pnum);
BOOL __fastcall PM_DoGotHit(int pnum);
void __fastcall ArmorDur(int pnum);
BOOL __fastcall PM_DoDeath(int pnum);
void __fastcall CheckNewPath(int pnum);
BOOL __fastcall PlrDeathModeOK(int pnum);
void __cdecl ValidatePlayer();
void __cdecl ProcessPlayers();
void __fastcall CheckCheatStats(int pnum);
void __fastcall ClrPlrPath(int pnum);
BOOL __fastcall PosOkPlayer(int pnum, int px, int py);
void __fastcall MakePlrPath(int pnum, int xx, int yy, BOOL endspace);
void __fastcall CheckPlrSpell();
void __fastcall SyncPlrAnim(int pnum);
void __fastcall SyncInitPlrPos(int pnum);
void __fastcall SyncInitPlr(int pnum);
void __fastcall CheckStats(int pnum);
void __fastcall ModifyPlrStr(int pnum, int l);
void __fastcall ModifyPlrMag(int pnum, int l);
void __fastcall ModifyPlrDex(int pnum, int l);
void __fastcall ModifyPlrVit(int pnum, int l);
void __fastcall SetPlayerHitPoints(int pnum, int newhp);
void __fastcall SetPlrStr(int pnum, int v);
void __fastcall SetPlrMag(int pnum, int v);
void __fastcall SetPlrDex(int pnum, int v);
void __fastcall SetPlrVit(int pnum, int v);
void __fastcall InitDungMsgs(int pnum);
void __cdecl PlayDungMsgs();

/* rdata */

extern const char ArmourChar[4];
extern const char WepChar[10];
extern const char CharChar[4];

/* data */

extern int plrxoff[9];
extern int plryoff[9];
extern int plrxoff2[9];
extern int plryoff2[9];
extern char PlrGFXAnimLens[3][11];
extern int PWVel[4][3];
extern int StrengthTbl[3];
extern int MagicTbl[3];
extern int DexterityTbl[3];
extern int VitalityTbl[3];
extern int ToBlkTbl[3];
extern char *ClassStrTblOld[3];
extern int MaxStats[3][4];
extern int ExpLvlsTbl[MAXCHARLEVEL];
extern char *ClassStrTbl[3];
extern unsigned char fix[9];

#endif /* __PLAYER_H__ */
