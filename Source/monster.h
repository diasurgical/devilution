/**
 * @file monster.h
 *
 * Interface of monster functionality, AI, actions, spawning, loading, etc.
 */
#ifndef __MONSTER_H__
#define __MONSTER_H__

extern int monstkills[MAXMONSTERS];
extern int monstactive[MAXMONSTERS];
extern int nummonsters;
extern MonsterStruct monster[MAXMONSTERS];
extern CMonster Monsters[MAX_LVLMTYPES];
extern int nummtypes;

void InitLevelMonsters();
void GetLevelMTypes();
void InitMonsterGFX(int monst);
void InitMonster(int i, int rd, int mtype, int x, int y);
void ClrAllMonsters();
#ifdef HELLFIRE
void monster_some_crypt();
#endif
void PlaceGroup(int mtype, int num, int leaderf, int leader);
void InitMonsters();
void SetMapMonsters(BYTE *pMap, int startx, int starty);
void DeleteMonster(int i);
int AddMonster(int x, int y, int dir, int mtype, BOOL InMap);
#ifdef HELLFIRE
void monster_43C785(int i);
#endif
BOOL M_Talker(int i);
void M_StartStand(int i, int md);
void M_ClearSquares(int i);
void M_GetKnockback(int i);
void M_StartHit(int i, int pnum, int dam);
void M_StartKill(int i, int pnum);
void M_SyncStartKill(int i, int x, int y, int pnum);
BOOL M_DoStand(int i);
BOOL M_DoWalk(int i);
BOOL M_DoWalk2(int i);
BOOL M_DoWalk3(int i);
BOOL M_DoAttack(int i);
void M_Teleport(int i);
BOOL M_DoGotHit(int i);
void M_UpdateLeader(int i);
void DoEnding();
void PrepDoEnding();
void M_WalkDir(int i, int md);
void MAI_Zombie(int i);
void MAI_SkelSd(int i);
void MAI_Snake(int i);
void MAI_Bat(int i);
void MAI_SkelBow(int i);
void MAI_Fat(int i);
void MAI_Sneak(int i);
void MAI_Fireman(int i);
void MAI_Fallen(int i);
void MAI_Cleaver(int i);
void MAI_Round(int i, BOOL special);
void MAI_GoatMc(int i);
void MAI_Ranged(int i, int missile_type, BOOL special);
void MAI_GoatBow(int i);
void MAI_Succ(int i);
#ifdef HELLFIRE
void mai_ranged_441649(int i);
void mai_ranged_441654(int i);
void mai_ranged_44165F(int i);
void mai_ranged_44166A(int i);
#endif
void MAI_AcidUniq(int i);
#ifdef HELLFIRE
void mai_ranged_441680(int i);
void mai_ranged_44168B(int i);
#endif
void MAI_Scav(int i);
void MAI_Garg(int i);
void MAI_RoundRanged(int i, int missile_type, BOOL checkdoors, int dam, int lessmissiles);
void MAI_Magma(int i);
void MAI_Storm(int i);
#ifdef HELLFIRE
void mai_roundranged_441EA0(int i);
#endif
void MAI_Acid(int i);
void MAI_Diablo(int i);
void MAI_Mega(int i);
void MAI_Golum(int i);
void MAI_SkelKing(int i);
void MAI_Rhino(int i);
#ifdef HELLFIRE
void mai_horkdemon(int i);
#endif
void MAI_Counselor(int i);
void MAI_Garbud(int i);
void MAI_Zhar(int i);
void MAI_SnotSpil(int i);
void MAI_Lazurus(int i);
void MAI_Lazhelp(int i);
void MAI_Lachdanan(int i);
void MAI_Warlord(int i);
void DeleteMonsterList();
void ProcessMonsters();
void FreeMonsters();
BOOL DirOK(int i, int mdir);
BOOL PosOkMissile(int x, int y);
BOOL CheckNoSolid(int x, int y);
BOOL LineClearF(BOOL (*Clear)(int, int), int x1, int y1, int x2, int y2);
BOOL LineClear(int x1, int y1, int x2, int y2);
BOOL LineClearF1(BOOL (*Clear)(int, int, int), int monst, int x1, int y1, int x2, int y2);
void SyncMonsterAnim(int i);
void M_FallenFear(int x, int y);
void PrintMonstHistory(int mt);
void PrintUniqueHistory();
void MissToMonst(int i, int x, int y);
BOOL PosOkMonst(int i, int x, int y);
#ifdef HELLFIRE
BOOLEAN monster_posok(int i, int x, int y);
#endif
BOOL PosOkMonst2(int i, int x, int y);
BOOL PosOkMonst3(int i, int x, int y);
BOOL IsSkel(int mt);
BOOL IsGoat(int mt);
int M_SpawnSkel(int x, int y, int dir);
BOOL SpawnSkeleton(int ii, int x, int y);
int PreSpawnSkeleton();
void TalktoMonster(int i);
void SpawnGolum(int i, int x, int y, int mi);
BOOL CanTalkToMonst(int m);
BOOL CheckMonsterHit(int m, BOOL &ret);
int encode_enemy(int m);
void decode_enemy(int m, int enemy);

/* data */

extern int opposite[8];
extern int offset_x[8];
extern int offset_y[8];

#endif /* __MONSTER_H__ */
