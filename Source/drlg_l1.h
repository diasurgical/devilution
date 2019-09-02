//HEADER_GOES_HERE
#ifndef __DRLG_L1_H__
#define __DRLG_L1_H__

extern BYTE L5dungeon[80][80];
extern BYTE L5dflags[DMAXX][DMAXY];
extern BOOL setloadflag;
extern int HR1;
extern int HR2;
extern int HR3;
#ifdef HELLFIRE
extern int UberRow;
extern int UberCol;
extern int dword_577368;
extern int IsUberRoomOpened;
extern int UberLeverRow;
extern int UberLeverCol;
extern int IsUberLeverActivated;
extern int UberDiabloMonsterIndex;
#endif
extern int VR1;
extern int VR2;
extern int VR3;
extern BYTE *pSetPiece;

void DRLG_Init_Globals();
void LoadL1Dungeon(char *sFileName, int vx, int vy);
void DRLG_L1Floor();
void DRLG_L1Pass3();
void DRLG_InitL1Vals();
void LoadPreL1Dungeon(char *sFileName, int vx, int vy);
void CreateL5Dungeon(DWORD rseed, int entry);
void DRLG_LoadL1SP();
void DRLG_FreeL1SP();
#ifdef HELLFIRE
void DRLG_InitL5Vals();
#endif
void DRLG_L5(int entry);
void DRLG_PlaceDoor(int x, int y);
#ifdef HELLFIRE
void drlg_l1_crypt_lavafloor();
#endif
void DRLG_L1Shadows();
int DRLG_PlaceMiniSet(const BYTE *miniset, int tmin, int tmax, int cx, int cy, BOOL setview, int noquad, int ldir);
void InitL5Dungeon();
void L5ClearFlags();
void L5firstRoom();
void L5drawRoom(int x, int y, int w, int h);
void L5roomGen(int x, int y, int w, int h, int dir);
BOOL L5checkRoom(int x, int y, int width, int height);
int L5GetArea();
void L5makeDungeon();
void L5makeDmt();
void L5AddWall();
int L5HWallOk(int i, int j);
int L5VWallOk(int i, int j);
void L5HorizWall(int i, int j, char p, int dx);
void L5VertWall(int i, int j, char p, int dy);
void L5tileFix();
#ifdef HELLFIRE
void drlg_l1_crypt_rndset(const BYTE *miniset, int rndper);
#endif
void DRLG_L5Subs();
void L5FillChambers();
void DRLG_L5GChamber(int sx, int sy, BOOL topflag, BOOL bottomflag, BOOL leftflag, BOOL rightflag);
void DRLG_L5GHall(int x1, int y1, int x2, int y2);
void DRLG_L5SetRoom(int rx1, int ry1);
#ifdef HELLFIRE
void drlg_l1_set_crypt_room(int rx1, int ry1);
void drlg_l1_set_corner_room(int rx1, int ry1);
#endif
void DRLG_L5FloodTVal();
void DRLG_L5FTVR(int i, int j, int x, int y, int d);
void DRLG_L5TransFix();
void DRLG_L5DirtFix();
void DRLG_L5CornerFix();
#ifdef HELLFIRE
void drlg_l1_crypt_pattern1(int rndper);
void drlg_l1_crypt_pattern2(int rndper);
void drlg_l1_crypt_pattern3(int rndper);
void drlg_l1_crypt_pattern4(int rndper);
void drlg_l1_crypt_pattern5(int rndper);
void drlg_l1_crypt_pattern6(int rndper);
void drlg_l1_crypt_pattern7(int rndper);
#endif

/* rdata */
extern const ShadowStruct SPATS[37];
extern const BYTE BSTYPES[206];
extern const BYTE L5BTYPES[206];
extern const BYTE STAIRSUP[];
extern const BYTE L5STAIRSUP[];
extern const BYTE STAIRSDOWN[];
extern const BYTE LAMPS[];
extern const BYTE PWATERIN[];

/* data */
extern BYTE L5ConvTbl[16];

#endif /* __DRLG_L1_H__ */
