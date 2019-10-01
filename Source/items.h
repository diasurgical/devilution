//HEADER_GOES_HERE
#ifndef __ITEMS_H__
#define __ITEMS_H__

extern int itemactive[MAXITEMS];
extern BOOL uitemflag;
extern int itemavail[MAXITEMS];
extern ItemStruct curruitem;
extern ItemGetRecordStruct itemrecord[MAXITEMS];
extern ItemStruct item[MAXITEMS + 1];
extern BOOL itemhold[3][3];
#ifdef HELLFIRE
extern int RowOfCornerStone;
extern int ColOfCornerStone;
extern int dword_691CB0;
extern ItemStruct CornerItemMaybe;
#endif
extern BYTE *itemanims[35];
extern BOOL UniqueItemFlag[128];
extern int numitems;
extern int gnNumGetRecords;

#ifdef HELLFIRE
int items_4231CA(int i);
int items_423230(int i);
int items_423296(int i);
int items_4232FC(int i);
int items_423362(int i);
int items_4233C8(int i);
int items_42342E(int i);
int items_4234B2(int i);
int items_423518(int i);
int items_42357E(int i);
int items_get_currlevel();
#endif
void InitItemGFX();
BOOL ItemPlace(int xp, int yp);
void AddInitItems();
void InitItems();
void CalcPlrItemVals(int p, BOOL Loadgfx);
void CalcPlrScrolls(int p);
void CalcPlrStaff(int p);
void CalcSelfItems(int pnum);
void CalcPlrItemMin(int pnum);
BOOL ItemMinStats(PlayerStruct *p, ItemStruct *x);
void CalcPlrBookVals(int p);
void CalcPlrInv(int p, BOOL Loadgfx);
void SetPlrHandItem(ItemStruct *h, int idata);
void GetPlrHandSeed(ItemStruct *h);
void GetGoldSeed(int pnum, ItemStruct *h);
void SetPlrHandSeed(ItemStruct *h, int iseed);
void SetPlrHandGoldCurs(ItemStruct *h);
void CreatePlrItems(int p);
BOOL ItemSpaceOk(int i, int j);
BOOL GetItemSpace(int x, int y, char inum);
void GetSuperItemSpace(int x, int y, char inum);
void GetSuperItemLoc(int x, int y, int *xx, int *yy);
void CalcItemValue(int i);
void GetBookSpell(int i, int lvl);
void GetStaffPower(int i, int lvl, int bs, BOOL onlygood);
void GetStaffSpell(int i, int lvl, BOOL onlygood);
void GetItemAttrs(int i, int idata, int lvl);
int RndPL(int param1, int param2);
int PLVal(int pv, int p1, int p2, int minv, int maxv);
void SaveItemPower(int i, int power, int param1, int param2, int minval, int maxval, int multval);
void GetItemPower(int i, int minlvl, int maxlvl, int flgs, int onlygood);
void GetItemBonus(int i, int idata, int minlvl, int maxlvl, BOOL onlygood);
void SetupItem(int i);
int RndItem(int m);
int RndUItem(int m);
int RndAllItems();
#ifdef HELLFIRE
int RndTypeItems(int itype, int imid, int lvl);
#else
int RndTypeItems(int itype, int imid);
#endif
int CheckUnique(int i, int lvl, int uper, BOOL recreate);
void GetUniqueItem(int i, int uid);
void SpawnUnique(int uid, int x, int y);
void ItemRndDur(int ii);
void SetupAllItems(int ii, int idx, int iseed, int lvl, int uper, int onlygood, BOOL recreate, BOOL pregen);
void SpawnItem(int m, int x, int y, BOOL sendmsg);
void CreateItem(int uid, int x, int y);
void CreateRndItem(int x, int y, BOOL onlygood, BOOL sendmsg, BOOL delta);
void SetupAllUseful(int ii, int iseed, int lvl);
void CreateRndUseful(int pnum, int x, int y, BOOL sendmsg);
void CreateTypeItem(int x, int y, BOOL onlygood, int itype, int imisc, BOOL sendmsg, BOOL delta);
void RecreateItem(int ii, int idx, WORD icreateinfo, int iseed, int ivalue);
void RecreateEar(int ii, WORD ic, int iseed, int Id, int dur, int mdur, int ch, int mch, int ivalue, int ibuff);
#ifdef HELLFIRE
void items_427ABA(int x, int y);
#endif
void SpawnQuestItem(int itemid, int x, int y, int randarea, int selflag);
void SpawnRock();
#ifdef HELLFIRE
void items_427DC6(int itemid, int xx, int yy);
void items_427E61(int xx, int yy);
void items_427E6F(int xx, int yy);
void items_427E7D(int xx, int yy);
#endif
void RespawnItem(int i, BOOL FlipFlag);
void DeleteItem(int ii, int i);
void ItemDoppel();
void ProcessItems();
void FreeItemGFX();
void GetItemFrm(int i);
void GetItemStr(int i);
void CheckIdentify(int pnum, int cii);
void DoRepair(int pnum, int cii);
void RepairItem(ItemStruct *i, int lvl);
void DoRecharge(int pnum, int cii);
void RechargeItem(ItemStruct *i, int r);
void PrintItemOil(char IDidx);
void PrintItemPower(char plidx, ItemStruct *x);
void DrawUTextBack();
void PrintUString(int x, int y, BOOL cjustflag, char *str, int col);
void DrawULine(int y);
void DrawUniqueInfo();
void PrintItemMisc(ItemStruct *x);
void PrintItemDetails(ItemStruct *x);
void PrintItemDur(ItemStruct *x);
void UseItem(int p, int Mid, int spl);
BOOL StoreStatOk(ItemStruct *h);
BOOL SmithItemOk(int i);
int RndSmithItem(int lvl);
void BubbleSwapItem(ItemStruct *a, ItemStruct *b);
void SortSmith();
void SpawnSmith(int lvl);
BOOL PremiumItemOk(int i);
int RndPremiumItem(int minlvl, int maxlvl);
void SpawnOnePremium(int i, int plvl);
void SpawnPremium(int lvl);
BOOL WitchItemOk(int i);
int RndWitchItem(int lvl);
void SortWitch();
void WitchBookLevel(int ii);
void SpawnWitch(int lvl);
int RndBoyItem(int lvl);
void SpawnBoy(int lvl);
BOOL HealerItemOk(int i);
int RndHealerItem(int lvl);
void SortHealer();
void SpawnHealer(int lvl);
void SpawnStoreGold();
void RecreateSmithItem(int ii, int idx, int lvl, int iseed);
void RecreatePremiumItem(int ii, int idx, int plvl, int iseed);
void RecreateBoyItem(int ii, int idx, int lvl, int iseed);
void RecreateWitchItem(int ii, int idx, int lvl, int iseed);
void RecreateHealerItem(int ii, int idx, int lvl, int iseed);
void RecreateTownItem(int ii, int idx, WORD icreateinfo, int iseed, int ivalue);
void RecalcStoreStats();
int ItemNoFlippy();
void CreateSpellBook(int x, int y, int ispell, BOOL sendmsg, BOOL delta);
void CreateMagicArmor(int x, int y, int imisc, int icurs, BOOL sendmsg, BOOL delta);
void CreateMagicWeapon(int x, int y, int imisc, int icurs, BOOL sendmsg, BOOL delta);
BOOL GetItemRecord(int nSeed, WORD wCI, int nIndex);
void NextItemRecord(int i);
void SetItemRecord(int nSeed, WORD wCI, int nIndex);
void PutItemRecord(int nSeed, WORD wCI, int nIndex);

/* data */

#ifdef HELLFIRE
extern int OilLevels[10];
extern int OilValues[10];
extern int OilMagic[10];
extern char OilNames[10][25];
extern int MaxGold;
#endif

extern BYTE ItemCAnimTbl[169];
extern char *ItemDropNames[35];
extern BYTE ItemAnimLs[35];
extern int ItemDropSnds[35];
extern int ItemInvSnds[35];
extern int idoppely;
extern int premiumlvladd[6];

#endif /* __ITEMS_H__ */
