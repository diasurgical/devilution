//HEADER_GOES_HERE
#ifndef __OBJECTS_H__
#define __OBJECTS_H__

extern int trapid;
extern int trapdir;
extern BYTE *pObjCels[40];
extern char ObjFileList[40];
extern int objectactive[MAXOBJECTS];
extern int nobjects;
extern int leverid;
extern int objectavail[MAXOBJECTS];
extern ObjectStruct object[MAXOBJECTS];
extern BOOL InitObjFlag;
extern int numobjfiles;

void InitObjectGFX();
void FreeObjectGFX();
DIABOOL RndLocOk(int xp, int yp);
void InitRndLocObj(int min, int max, int objtype);
void InitRndLocBigObj(int min, int max, int objtype);
void InitRndLocObj5x5(int min, int max, int objtype);
void ClrAllObjects();
void AddTortures();
void AddCandles();
void AddBookLever(int lx1, int ly1, int lx2, int ly2, int x1, int y1, int x2, int y2, int msg);
void InitRndBarrels();
void AddL1Objs(int x1, int y1, int x2, int y2);
#ifdef HELLFIRE
void add_crypt_objs(int x1, int y1, int x2, int y2);
#endif
void AddL2Objs(int x1, int y1, int x2, int y2);
void AddL3Objs(int x1, int y1, int x2, int y2);
DIABOOL WallTrapLocOk(int xp, int yp);
void AddL2Torches();
DIABOOL TorchLocOK(int xp, int yp);
void AddObjTraps();
void AddChestTraps();
void LoadMapObjects(BYTE *pMap, int startx, int starty, int x1, int y1, int w, int h, int leveridx);
void LoadMapObjs(BYTE *pMap, int startx, int starty);
void AddDiabObjs();
#ifdef HELLFIRE
void objects_add_lv22(int s);
void objects_add_lv24();
#endif
void AddStoryBooks();
void AddHookedBodies(int freq);
void AddL4Goodies();
void AddLazStand();
void InitObjects();
void SetMapObjects(BYTE *pMap, int startx, int starty);
void DeleteObject_(int oi, int i);
void SetupObject(int i, int x, int y, int ot);
void SetObjMapRange(int i, int x1, int y1, int x2, int y2, int v);
void SetBookMsg(int i, int msg);
void AddL1Door(int i, int x, int y, int ot);
void AddSCambBook(int i);
void AddChest(int i, int t);
void AddL2Door(int i, int x, int y, int ot);
void AddL3Door(int i, int x, int y, int ot);
void AddSarc(int i);
void AddFlameTrap(int i);
void AddFlameLvr(int i);
void AddTrap(int i, int ot);
void AddObjLight(int i, int r);
void AddBarrel(int i, int t);
void AddShrine(int i);
void AddBookcase(int i);
void AddPurifyingFountain(int i);
void AddArmorStand(int i);
void AddGoatShrine(int i);
void AddCauldron(int i);
void AddMurkyFountain(int i);
void AddTearFountain(int i);
void AddDecap(int i);
void AddVilebook(int i);
void AddMagicCircle(int i);
void AddBrnCross(int i);
void AddBookstand(int i);
void AddBloodFtn(int i);
void AddPedistal(int i);
void AddStoryBook(int i);
void AddWeaponRack(int i);
void AddTorturedBody(int i);
void GetRndObjLoc(int randarea, int &xx, int &yy);
void AddMushPatch();
void AddSlainHero();
#ifdef HELLFIRE
void objects_44D8C5(int a1, int a2, int a3, int a4);
void objects_454AF0(int a1, int a2, int a3);
#endif
void AddObject(int ot, int ox, int oy);
void Obj_Light(int i, int lr);
void Obj_Circle(int i);
void Obj_StopAnim(int i);
void Obj_Door(int i);
void Obj_Sarc(int i);
void ActivateTrapLine(int ttype, int tid);
void Obj_FlameTrap(int i);
void Obj_Trap(int i);
void Obj_BCrossDamage(int i);
void ProcessObjects();
void ObjSetMicro(int dx, int dy, int pn);
void objects_set_door_piece(int x, int y);
void ObjSetMini(int x, int y, int v);
void ObjL1Special(int x1, int y1, int x2, int y2);
void ObjL2Special(int x1, int y1, int x2, int y2);
void DoorSet(int oi, int dx, int dy);
void RedoPlayerVision();
void OperateL1RDoor(int pnum, int oi, DIABOOL sendflag);
void OperateL1LDoor(int pnum, int oi, BOOL sendflag);
void OperateL2RDoor(int pnum, int oi, BOOL sendflag);
void OperateL2LDoor(int pnum, int oi, BOOL sendflag);
void OperateL3RDoor(int pnum, int oi, BOOL sendflag);
void OperateL3LDoor(int pnum, int oi, BOOL sendflag);
void MonstCheckDoors(int m);
void ObjChangeMap(int x1, int y1, int x2, int y2);
void ObjChangeMapResync(int x1, int y1, int x2, int y2);
void OperateL1Door(int pnum, int i, BOOL sendflag);
void OperateLever(int pnum, int i);
void OperateBook(int pnum, int i);
void OperateBookLever(int pnum, int i);
void OperateSChambBk(int pnum, int i);
void OperateChest(int pnum, int i, DIABOOL sendmsg);
void OperateMushPatch(int pnum, int i);
void OperateInnSignChest(int pnum, int i);
void OperateSlainHero(int pnum, int i, BOOL sendmsg);
void OperateTrapLvr(int i);
void OperateSarc(int pnum, int i, DIABOOL sendmsg);
void OperateL2Door(int pnum, int i, BOOL sendflag);
void OperateL3Door(int pnum, int i, BOOL sendflag);
void OperatePedistal(int pnum, int i);
void TryDisarm(int pnum, int i);
int ItemMiscIdIdx(int imiscid);
void OperateShrine(int pnum, int i, int sType);
void OperateSkelBook(int pnum, int i, DIABOOL sendmsg);
void OperateBookCase(int pnum, int i, DIABOOL sendmsg);
void OperateDecap(int pnum, int i, DIABOOL sendmsg);
void OperateArmorStand(int pnum, int i, DIABOOL sendmsg);
int FindValidShrine(int i);
void OperateGoatShrine(int pnum, int i, int sType);
void OperateCauldron(int pnum, int i, int sType);
BOOL OperateFountains(int pnum, int i);
void OperateWeaponRack(int pnum, int i, DIABOOL sendmsg);
void OperateStoryBook(int pnum, int i);
void OperateLazStand(int pnum, int i);
void OperateObject(int pnum, int i, BOOL TeleFlag);
void SyncOpL1Door(int pnum, int cmd, int i);
void SyncOpL2Door(int pnum, int cmd, int i);
void SyncOpL3Door(int pnum, int cmd, int i);
void SyncOpObject(int pnum, int cmd, int i);
void BreakCrux(int i);
void BreakBarrel(int pnum, int i, int dam, BOOL forcebreak, int sendmsg);
void BreakObject(int pnum, int oi);
void SyncBreakObj(int pnum, int oi);
void SyncL1Doors(int i);
void SyncCrux(int i);
void SyncLever(int i);
void SyncQSTLever(int i);
void SyncPedistal(int i);
void SyncL2Doors(int i);
void SyncL3Doors(int i);
void SyncObjectAnim(int o);
void GetObjectStr(int i);
#ifdef HELLFIRE
void operate_lv24_lever();
void objects_454BA8();
void objects_rnd_454BEA();
#endif

/* rdata */

extern int bxadd[8];
extern int byadd[8];
extern char *shrinestrs[NUM_SHRINETYPE];
extern char shrinemin[NUM_SHRINETYPE];
extern char shrinemax[NUM_SHRINETYPE];
extern BYTE shrineavail[NUM_SHRINETYPE];
extern char *StoryBookName[9];
extern int StoryText[3][3];

#endif /* __OBJECTS_H__ */
