struct UItemStruct
{
	char *UIName;
	char UIItemId;
	char UIMinLvl;
	char UINumPL;
	int UIValue;
	char UIPower1;
	int UIParam1;
	int UIParam2;
	char UIPower2;
	int UIParam3;
	int UIParam4;
	char UIPower3;
	int UIParam5;
	int UIParam6;
	char UIPower4;
	int UIParam7;
	int UIParam8;
	char UIPower5;
	int UIParam9;
	int UIParam10;
	char UIPower6;
	int UIParam11;
	int UIParam12;
};

struct PLStruct
{
	const char *PLName;
	char PLPower;
	int PLParam1;
	int PLParam2;
	int PLMinLvl;
	int PLIType;
	int PLGOE;
	int PLDouble;
	int PLOk;
	int PLMinVal;
	int PLMaxVal;
	int PLMultVal;
};

struct TextDataStruct
{
	char *txtstr;
	int scrlltxt;
	int txtspd;
	int sfxnr;
};

struct RECT32
{
	int x;
	int y;
	int w;
	int h;
};

struct TSnd
{
	WAVEFORMATEX fmt;
	int len;
	int offset;
	char *sound_path;
	IDirectSoundBuffer *DSB;
	int start_tc;
};

struct TSFX
{
	unsigned char bFlags;
	char *pszName;
	TSnd *pSnd;
};

struct TMenuItem
{
	unsigned int dwFlags;
	char *pszStr;
	void (__cdecl *fnMenu)(); /* fix, should have one arg */
};

struct ItemDataStruct
{
	int iRnd;
	char iClass;
	char iLoc;
	int iCurs;
	char itype;
	char iItemId;
	char *iName;
	char *iSName;
	int iMinMLvl;
	int iDurability;
	int iMinDam;
	int iMaxDam;
	int iMinAC;
	int iMaxAC;
	char iMinStr;
	char iMinMag;
	char iMinDex;
	int iFlags;
	int iMiscId;
	int iSpell;
	int iUsable;
	int iValue;
	int iMaxValue;
};

struct MissileData
{
	unsigned char mName;
	void (__fastcall *mAddProc)(int, int, int, int, int, int, int, int, int);
	void (__fastcall *mProc)(int);
	int mDraw;
	unsigned char mType;
	unsigned char mResist;
	unsigned char mFileNum;
	int mlSFX;
	int miSFX;
};

struct MisFileData
{
	unsigned char mAnimName;
	unsigned char mAnimFAmt;
	char *mName;
	int mFlags;
	int mAnimData[16]; // unsigned char *
	unsigned char mAnimDelay[16];
	unsigned char mAnimLen[16];
	int mAnimWidth[16];
	int mAnimWidth2[16];
};

struct MonsterData
{
	int flags; // width?
	int mType;
	char *GraphicType;
	int has_special;
	char *sndfile;
	int snd_special;
	int has_trans;
	char *TransFile;
	int Frames[6];
	int Rate[6];
	char *mName;
	char mMinDLvl;
	char mMaxDLvl;
	char mLevel;
	int mMinHP;
	int mMaxHP;
	char mAi;
	int mFlags;
	unsigned char mInt;
	unsigned char mHit;
	unsigned char mAFNum;
	unsigned char mMinDamage;
	unsigned char mMaxDamage;
	unsigned char mHit2;
	unsigned char mAFNum2;
	unsigned char mMinDamage2;
	unsigned char mMaxDamage2;
	char mArmorClass;
	char mMonstClass;
	unsigned short mMagicRes;
	unsigned short mMagicRes2;
	unsigned short mTreasure;
	char mSelFlag;
	unsigned short mExp;
};

struct UniqMonstStruct
{
	char mtype;
	char *mName;
	char *mMode;
	unsigned char mlevel;
	unsigned short mmaxhp;
	unsigned char mAi;
	unsigned char mint;
	unsigned char mMinDamage;
	unsigned char mMaxDamage;
	unsigned short mMagicRes;
	unsigned short mUnqAttr;
	unsigned char mUnqVar1;
	unsigned char mUnqVar2;
	int mtalkmsg;
};

struct ObjDataStruct
{
	char oload;
	char ofindex;
	char ominlvl;
	char omaxlvl;
	char olvltype;
	char otheme;
	char oquest;
	int oAnimFlag;
	int oAnimDelay;
	int oAnimLen;
	int oAnimWidth;
	int oSolidFlag;
	int oMissFlag;
	int oLightFlag;
	char oBreak;
	char oSelFlag;
	int oTrapFlag;
};

struct QuestData
{
	unsigned char _qdlvl;
	char _qdmultlvl;
	unsigned char _qlvlt;
	unsigned char _qdtype;
	unsigned char _qdrnd;
	unsigned char _qslvl;
	int _qflags; //__declspec(align(4)) /* unsigned char */
	int _qdmsg;
	char *_qlstr;
};

struct SpellData
{
	unsigned char sName;
	unsigned char sManaCost;
	unsigned char sType;
	char *sNameText;
	char *sSkillText;
	int sBookLvl;
	int sStaffLvl;
	int sTargeted;
	unsigned char sTownSpell;
	int sMinInt;
	unsigned char sSFX;
	unsigned char sMissiles[3];
	unsigned char sManaAdj;
	unsigned char sMinMana;
	int sStaffMin;
	int sStaffMax;
	int sBookCost;
	int sStaffCost;
};

struct Coord
{
	char x;
	char y;
};

struct RECT8
{
	Coord x;
	Coord y;
};

struct QuestTalkData
{
	int _qinfra;
	int _qblkm;
	int _qgarb;
	int _qzhar;
	int _qveil;
	int _qmod;
	int _qbutch;
	int _qbol;
	int _qblind;
	int _qblood;
	int _qanvil;
	int _qwarlrd;
	int _qking;
	int _qpw;
	int _qbone;
	int _qvb;
};

struct ShadowStruct
{
	unsigned char strig;
	unsigned char s1;
	unsigned char s2;
	unsigned char s3;
	unsigned char nv1;
	unsigned char nv2;
	unsigned char nv3;
};

struct POINT32 /* remove this struct */
{
	int x;
	int y;
};

struct InvXY
{
	int X;
	int Y;
};

struct ItemStruct
{
	int _iSeed;
	unsigned short _iCreateInfo;
	int _itype;
	int _ix;
	int _iy;
	int _iAnimFlag;
	int _iAnimData; // unsigned char *
	int _iAnimLen;
	int _iAnimFrame;
	int _iAnimWidth;
	int _iAnimWidth2; // width 2?
	int offs002C;
	char _iSelFlag;
	int _iPostDraw;
	int _iIdentified;
	char _iMagical;
	char _iName[64];
	char _iIName[64];
	char _iLoc;
	char _iClass;
	int _iCurs;
	int _ivalue;
	int _iIvalue;
	int _iMinDam;
	int _iMaxDam;
	int _iAC;
	int _iFlags;
	int _iMiscId;
	int _iSpell;
	int _iCharges;
	int _iMaxCharges;
	int _iDurability;
	int _iMaxDur;
	int _iPLDam;
	int _iPLToHit;
	int _iPLAC;
	int _iPLStr;
	int _iPLMag;
	int _iPLDex;
	int _iPLVit;
	int _iPLFR;
	int _iPLLR;
	int _iPLMR;
	int _iPLMana;
	int _iPLHP;
	int _iPLDamMod;
	int _iPLGetHit;
	int _iPLLight;
	char _iSplLvlAdd;
	char _iRequest;
	int _iUid;
	int _iFMinDam;
	int _iFMaxDam;
	int _iLMinDam;
	int _iLMaxDam;
	int _iPLEnAc;
	char _iPrePower;
	char _iSufPower;
	int _iVAdd1;
	int _iVMult1;
	int _iVAdd2;
	int _iVMult2;
	char _iMinStr;
	unsigned char _iMinMag;
	char _iMinDex;
	int _iStatFlag;
	int IDidx;
	int offs016C;
};

struct DeadStruct
{
	int _deadData[8]; // unsigned char *
	int _deadFrame;
	int field_24; // width
	int field_28; // cel or fnum _deadtype?
	int _deadtrans;
};

struct ScreenRow
{
	char col_unused_1[64];
	char pixels[640];
	char col_unused_2[64];
};

struct Screen
{
	ScreenRow row_unused_1[160];
	ScreenRow row[480];
	ScreenRow row_unused_2[16];
};

struct Tile
{
	short top;
	short right;
	short left;
	short bottom;
};

struct _SNETVERSIONDATA
{
	int size;
	char *versionstring;
	char *executablefile;
	char *originalarchivefile;
	char *patcharchivefile;
};

struct LightListStruct
{
	int _lx;
	int _ly;
	int _lradius;
	int _lid;
	int _ldel;
	int _lunflag;
	int field_18;
	int _lunx;
	int _luny;
	int _lunr;
	int _xoff;
	int _yoff;
	int _lflags;
};

struct MissileStruct
{
	int _mitype;
	int _mix;
	int _miy;
	int _mixoff;
	int _miyoff;
	int _mixvel;
	int _miyvel;
	int _misx;
	int _misy;
	int _mitxoff;
	int _mityoff;
	int _mimfnum;
	int _mispllvl;
	int _miDelFlag;
	int _miAnimType;
	int _miAnimFlags;
	int _miAnimData; // unsigned char *
	int _miAnimDelay;
	int _miAnimLen;
	int _miAnimWidth;
	int _miAnimWidth2;
	int _miAnimCnt;
	int _miAnimAdd;
	int _miAnimFrame;
	int _miDrawFlag;
	int _miLightFlag;
	int _miPreFlag;
	int _miUniqTrans;
	int _mirange;
	int _misource;
	int _micaster;
	int _midam;
	int _miHitFlag;
	int _midist;
	int _mlid;
	int _mirnd;
	int _miVar1;
	int _miVar2;
	int _miVar3;
	int _miVar4;
	int _miVar5;
	int _miVar6;
	int _miVar7;
	int _miVar8;
};

struct AnimStruct
{
	int CMem; // [unsigned] char * ??
	int Frames[8]; // unsigned char *
	int Rate;
	int Delay;
};

struct CMonster
{
	unsigned char mtype;
	unsigned char mPlaceFlags;
	AnimStruct Anims[6];
	TSnd *Snds[8];
	int flags_1; // width
	int flags_2; // width 2
	unsigned char mMinHP;
	unsigned char mMaxHP;
	int has_special;
	unsigned char mAFNum;
	char mdeadval;
	MonsterData *MData;
	void *trans_file;
};

struct MonsterStruct
{
	int _mMTidx;
	int _mmode;
	int _mgoal;
	int _mgoalvar1;
	int _mgoalvar2;
	int _mgoalvar3;
	int field_18;
	int _pathcount;
	int _mx;
	int _my;
	int _mfutx;
	int _mfuty;
	int _moldx;
	int _moldy;
	int _mxoff;
	int _myoff;
	int _mxvel;
	int _myvel;
	int _mdir;
	int _menemy;
	unsigned char _menemyx;
	unsigned char _menemyy;
	short falign_52;
	int _mAFNum;
	int _mAnimDelay;
	int _mAnimCnt;
	int _mAnimLen;
	int _mAnimFrame;
	int _meflag;
	int _mDelFlag;
	int _mVar1;
	int _mVar2;
	int _mVar3;
	int _mVar4;
	int _mVar5;
	int _mVar6;
	int _mVar7;
	int _mVar8;
	int _mmaxhp;
	int _mhitpoints;
	unsigned char _mAi;
	unsigned char _mint;
	short falign_9A;
	int _mFlags;
	char _msquelch; /* unsigned char */
	int falign_A4;
	int _lastx;
	int _lasty;
	int _mRndSeed;
	int _mAISeed;
	int falign_B8;
	unsigned char _uniqtype;
	unsigned char _uniqtrans;
	char _udeadval;
	char mWhoHit;
	short mLevel; /* char */
	unsigned short mExp;
	unsigned char mHit;
	unsigned char mMinDamage;
	unsigned char mMaxDamage;
	unsigned char mHit2;
	unsigned char mMinDamage2;
	unsigned char mMaxDamage2;
	char mArmorClass;
	char falign_CB;
	int mMagicRes; /* ushort */
	int mtalkmsg;
	unsigned char leader;
	unsigned char leaderflag;
	unsigned char unpackfilesize;
	unsigned char mlid;
	char *mName;
	CMonster *MType;
	MonsterData *MData;
};

struct DObjectStr
{
	unsigned char bCmd;
};

/* __declspec(align(1))*/
#pragma pack(push, 1)
struct  DMonsterStr
{
	char _mx; /* these might be unsigned */
	char _my;
	char _mdir;
	char _menemy;
	char _mactive;
	int _mhitpoints;
};
#pragma pack(pop)

/* __declspec(align(2))*/
#pragma pack(push, 1)
struct  TCmdPItem
{
	char bCmd; /* unsigned */
	unsigned char x;
	unsigned char y;
	unsigned short wIndx;
	unsigned short wCI;
	int dwSeed;
	unsigned char bId;
	unsigned char bDur;
	unsigned char bMDur;
	unsigned char bCh;
	unsigned char bMCh;
	unsigned short wValue;
	int dwBuff;
};
#pragma pack(pop)

/* __declspec(align(1))*/
struct  DLevel
{
	TCmdPItem item[127];
	DObjectStr object[127];
	DMonsterStr monster[200];
};

struct DPortal
{
	unsigned char x;
	unsigned char y;
	unsigned char level;
	unsigned char ltype;
	unsigned char setlvl;
};

struct MultiQuests
{
	unsigned char qstate;
	unsigned char qlog;
	unsigned char qvar1;
};

struct DJunk
{
	DPortal portal[4];
	MultiQuests quests[4];
};

/*  __declspec(align(1)) */
#pragma pack(push, 1)
struct PkItemStruct
{
	int iSeed;
	short iCreateInfo;
	short idx;
	char bId;
	char bDur;
	char bMDur;
	char bCh;
	char bMCh;
	short wValue;
	int dwBuff;
};
#pragma pack(pop)

/* __declspec(align(2)) */
#pragma pack(push, 1)
struct PkPlayerStruct
{
	FILETIME archiveTime;
	char destAction;
	char destParam1;
	char destParam2;
	char plrlevel;
	char px;
	char py;
	char targx;
	char targy;
	char pName[32];
	char pClass;
	char pBaseStr;
	char pBaseMag;
	char pBaseDex;
	char pBaseVit;
	char pLevel;
	char pStatPts;
	int pExperience;
	int pGold;
	int pHPBase;
	int pMaxHPBase;
	int pManaBase;
	int pMaxManaBase;
	char pSplLvl[37];
	int pMemSpells;
	int pMemSpells2;
	PkItemStruct InvBody[7];
	PkItemStruct InvList[40];
	char InvGrid[40];
	char _pNumInv;
	PkItemStruct SpdList[8];
	char pTownWarps;
	char pDungMsgs;
	char pLvlLoad;
	char pBattleNet;
	char pManaShield;
	char bReserved[3];
	short wReserved[8];
	int pDiabloKillLevel;
	int dwReserved[7];
};
#pragma pack(pop)

struct ObjectStruct
{
	int _otype;
	int _ox;
	int _oy;
	int _oLight;
	int _oAnimFlag;
	int _oAnimData; // unsigned char *
	int _oAnimDelay;
	int _oAnimCnt;
	int _oAnimLen;
	int _oAnimFrame;
	int _oAnimWidth;
	int _oAnimWidth2;
	int _oDelFlag;
	char _oBreak; // check
	int _oSolidFlag;
	int _oMissFlag;
	char _oSelFlag; // check
	int _oPreFlag;
	int _oTrapFlag;
	int _oDoorFlag;
	int _olid;
	int _oRndSeed;
	int _oVar1;
	int _oVar2;
	int _oVar3;
	int _oVar4;
	int _oVar5;
	int _oVar6;
	int _oVar7;
	int _oVar8;
};

struct PATHNODE
{
	char f;
	char h;
	short g;
	int x;
	int y;
	struct PATHNODE *Parent;
	struct PATHNODE *Child[8];
	struct PATHNODE *NextNode;
};

struct PlayerStruct
{
	int _pmode;
	char walkpath[25];
	unsigned char plractive;
	int destAction;
	int destParam1;
	int destParam2;
	int destParam3;
	int destParam4;
	int plrlevel;
	int WorldX;
	int WorldY;
	int _px;
	int _py;
	int _ptargx;
	int _ptargy;
	int _pownerx;
	int _pownery;
	int _poldx;
	int _poldy;
	int _pxoff;
	int _pyoff;
	int _pxvel;
	int _pyvel;
	int _pdir;
	int _nextdir;
	int _pgfxnum;
	int _pAnimData; // unsigned char *
	int _pAnimDelay;
	int _pAnimCnt;
	int _pAnimLen;
	int _pAnimFrame;
	int _pAnimWidth;
	int _pAnimWidth2;
	int _peflag;
	int _plid;
	int _pvid;
	int _pSpell;
	char _pSplType;
	char _pSplFrom;
	int _pTSpell;
	int _pTSplType;
	int _pRSpell;
	int _pRSplType;
	int _pSBkSpell;
	char _pSBkSplType;
	char _pSplLvl[64];
	int remove_1;
	int _pMemSpells[2]; // __declspec(align(8))
	int _pAblSpells[2];
	int _pScrlSpells[2];
	int _pSpellFlags;
	int _pSplHotKey[4];
	char _pSplTHotKey[4];
	int _pwtype;
	unsigned char _pBlockFlag;
	unsigned char _pInvincible;
	char _pLightRad;
	unsigned char _pLvlChanging;
	char _pName[32];
	int _pClass;
	int _pStrength;
	int _pBaseStr;
	int _pMagic;
	int _pBaseMag;
	int _pDexterity;
	int _pBaseDex;
	int _pVitality;
	int _pBaseVit;
	int _pStatPts;
	int _pDamageMod;
	int _pBaseToBlk;
	int _pHPBase;
	int _pMaxHPBase;
	int _pHitPoints;
	int _pMaxHP;
	int _pHPPer;
	int _pManaBase;
	int _pMaxManaBase;
	int _pMana;
	int _pMaxMana;
	int _pManaPer;
	char _pLevel;
	char _pMaxLvl;
	int _pExperience;
	int _pMaxExp;
	int _pNextExper;
	char _pArmorClass;
	char _pMagResist;
	char _pFireResist;
	char _pLghtResist;
	int _pGold;
	int _pInfraFlag;
	int _pVar1;
	int _pVar2;
	int _pVar3;
	int _pVar4;
	int _pVar5;
	int _pVar6;
	int _pVar7;
	int _pVar8;
	unsigned char _pLvlVisited[17];
	unsigned char _pSLvlVisited[10];
	char gap20F[9];
	int _pGFXLoad;
	int _pNAnim[8]; // unsigned char *
	int _pNFrames;
	int _pNWidth;
	int _pWAnim[8]; // unsigned char *
	int _pWFrames;
	int _pWWidth;
	int _pAAnim[8]; // unsigned char *
	int _pAFrames;
	int _pAWidth;
	int _pAFNum;
	int _pLAnim[8]; // unsigned char *
	int _pFAnim[8]; // unsigned char *
	int _pTAnim[8]; // unsigned char *
	int _pSFrames;
	int _pSWidth;
	int _pSFNum;
	int _pHAnim[8]; // unsigned char *
	int _pHFrames;
	int _pHWidth;
	int _pDAnim[8]; // unsigned char *
	int _pDFrames;
	int _pDWidth;
	int _pBAnim[8]; // unsigned char *
	int _pBFrames;
	int _pBWidth;
	ItemStruct InvBody[7];
	ItemStruct InvList[40];
	int _pNumInv;
	char InvGrid[40];
	ItemStruct SpdList[8];
	ItemStruct HoldItem;
	int _pIMinDam;
	int _pIMaxDam;
	int _pIAC;
	int _pIBonusDam;
	int _pIBonusToHit;
	int _pIBonusAC;
	int _pIBonusDamMod;
	int remove_2;
	int _pISpells[2]; //__declspec(align(8))
	int _pIFlags;
	int _pIGetHit;
	char _pISplLvlAdd;
	char _pISplCost;
	int _pISplDur;
	int _pIEnAc;
	int _pIFMinDam;
	int _pIFMaxDam;
	int _pILMinDam;
	int _pILMaxDam;
	int _pOilType;
	unsigned char pTownWarps;
	unsigned char pDungMsgs;
	unsigned char pLvlLoad;
	unsigned char pBattleNet;
	unsigned char pManaShield;
	char bReserved[3];
	short wReserved[8];
	int pDiabloKillLevel;
	int dwReserved[7];
	void *_pNData;
	void *_pWData;
	void *_pAData;
	void *_pLData;
	void *_pFData;
	void *_pTData;
	void *_pHData;
	void *_pDData;
	void *_pBData;
	int unused_54D4;
};

struct QuestStruct
{
	unsigned char _qlevel;
	unsigned char _qtype;
	unsigned char _qactive;
	unsigned char _qlvltype;
	int _qtx;
	int _qty;
	unsigned char _qslvl;
	unsigned char _qidx;
	unsigned char _qmsg;
	unsigned char _qvar1;
	unsigned char _qvar2;
	int _qlog; /* char */
};

struct SHA1Context
{
	int state[5];
	int count[2];
	char buffer[64];
};

struct ThemeStruct
{
	char ttype; /* aligned 4 */
	int ttval;
};

struct TMsgHeader
{
	char next;
	char start_tc;
	char len;
};

struct TMsg
{
	TMsgHeader hdr;
	char data;
};

struct TNQ
{
	unsigned char _qsttype;
	unsigned char _qstmsg;
	unsigned char _qstmsgact;
};

struct TownerStruct
{
	int _tmode;
	int _ttype;
	int _tx;
	int _ty;
	int _txoff;
	int _tyoff;
	int _txvel;
	int _tyvel;
	int _tdir;
	void *_tAnimData; // unsigned char *
	int _tAnimDelay;
	int _tAnimCnt;
	int _tAnimLen;
	int _tAnimFrame;
	int _tAnimFrameCnt;
	int _tAnimOrder;
	int _tAnimWidth;
	int _tAnimWidth2;
	int _tTenPer;
	int _teflag;
	int _tbtcnt;
	int _tSelFlag;
	int _tMsgSaid;
	TNQ qsts[16];
	int _tSeed;
	int _tVar1;
	int _tVar2;
	int _tVar3;
	int _tVar4;
	char _tName[32];
	int _tNAnim[8]; // unsigned char *
	int _tNFrames;
	char *_tNData; // unsigned char *
};

struct _SNETUIDATA
{
	int size;
	int uiflags;
	HWND parentwindow;
	void (__cdecl *artcallback)();
	void (__cdecl *authcallback)();
	void (__cdecl *createcallback)();
	void (__cdecl *drawdesccallback)();
	void (__cdecl *selectedcallback)();
	void (__cdecl *messageboxcallback)();
	void (__cdecl *soundcallback)();
	void (__cdecl *statuscallback)();
	void (__cdecl *getdatacallback)();
	void (__cdecl *categorycallback)();
	void (__cdecl *field_34)();
	void (__cdecl *field_38)();
	void (__cdecl *profilecallback)();
	int profilegetstring;
	void (__cdecl *profiledraw)();
	void (__cdecl *selecthero)();
	void (__cdecl *createhero)();
};

struct _SNETPROGRAMDATA
{
	int size;
	char *programname;
	char *programdescription;
	int programid;
	int versionid;
	int reserved1;
	int maxplayers;
	int multi_seed;
	void *initdata;
	int initdatabytes;
	void *reserved2;
	int optcategorybits;
	int reserved3;
	int reserved4;
	int languageid;
};

struct _uiheroinfo
{
	_uiheroinfo *next;
	char name[16];
	unsigned short level;
	unsigned char heroclass;
	unsigned char herorank;
	unsigned short strength;
	unsigned short magic;
	unsigned short dexterity;
	unsigned short vitality;
	int gold;
	int hassaved;
	int spawned;
};

struct _HASHENTRY
{
	int hashcheck[2];
	int lcid;
	int block;
};

struct _BLOCKENTRY
{
	int offset;
	int sizealloc;
	int sizefile;
	int flags;
};

/* __declspec(align(2)) */
#pragma pack(push, 1)
struct TCmdGItem
{
	unsigned char bCmd;
	unsigned char bMaster;
	unsigned char bPnum;
	unsigned char bCursitem;
	unsigned char bLevel;
	unsigned char x;
	unsigned char y;
	unsigned short wIndx;
	unsigned short wCI;
	int dwSeed;
	unsigned char bId;
	unsigned char bDur;
	unsigned char bMDur;
	unsigned char bCh;
	unsigned char bMCh;
	unsigned short wValue;
	int dwBuff;
	int dwTime;
};
#pragma pack(pop)

struct TCmdLoc
{
	unsigned char bCmd;
	unsigned char x;
	unsigned char y;
};

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdParam1
{
	unsigned char bCmd;
	unsigned short wParam1;
};
#pragma pack(pop)

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdLocParam1
{
	unsigned char bCmd;
	unsigned char x;
	unsigned char y;
	unsigned short wParam1;
};
#pragma pack(pop)

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TPktHdr
{
	unsigned char px;
	unsigned char py;
	unsigned char targx;
	unsigned char targy;
	int php;
	int pmhp;
	unsigned char bstr;
	unsigned char bmag;
	unsigned char bdex;
	unsigned short wCheck;
	unsigned short wLen;
};
#pragma pack(pop)

struct _SNETEVENT
{
	int eventid;
	int playerid;
	void *data;
	int databytes;
};

struct _SNETPLAYERDATA
{
	int size;
	char *playername;
	char *playerdescription;
	int field_C;
};

struct _SNETCAPS
{
	int size;
	int flags;
	int maxmessagesize;
	int maxqueuesize;
	int maxplayers;
	int bytessec;
	int latencyms;
	int defaultturnssec;
	int defaultturnsintransit;
};

struct TMPQHeader // _FILEHEADER
{
	int dwID;
	int dwHeaderSize;
	int dwArchiveSize;
	short wFormatVersion;
	short wSectorSize;
	int dwHashTablePos;
	int dwBlockTablePos;
	int dwHashTableSize;
	int dwBlockTableSize;
	char field_20[72];
};

struct _uidefaultstats
{
	unsigned short strength;
	unsigned short magic;
	unsigned short dexterity;
	unsigned short vitality;
};

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdLocParam2
{
	unsigned char bCmd;
	unsigned char x;
	unsigned char y;
	unsigned short wParam1;
	unsigned short wParam2;
};
#pragma pack(pop)

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdLocParam3
{
	unsigned char bCmd;
	unsigned char x;
	unsigned char y;
	unsigned short wParam1;
	unsigned short wParam2;
	unsigned short wParam3;
};
#pragma pack(pop)

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdParam2
{
	unsigned char bCmd;
	unsigned short wParam1;
	unsigned short wParam2;
};
#pragma pack(pop)

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdParam3
{
	unsigned char bCmd;
	unsigned short wParam1;
	unsigned short wParam2;
	unsigned short wParam3;
};
#pragma pack(pop)

struct TCmd
{
	unsigned char bCmd;
};

/* __declspec(align(2)) */
#pragma pack(push, 1)
struct TCmdGolem
{
	unsigned char bCmd;
	unsigned char _mx;
	unsigned char _my;
	unsigned char _mdir;
	unsigned char _menemy;
	int _mhitpoints;
	unsigned char _currlevel;
};
#pragma pack(pop)

struct TCmdQuest
{
	unsigned char bCmd;
	unsigned char q;
	unsigned char qstate;
	unsigned char qlog;
	unsigned char qvar1;
};

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdChItem
{
	unsigned char bCmd;
	unsigned char bLoc;
	unsigned short wIndx;
	unsigned short wCI;
	int dwSeed;
	unsigned char bId;
};
#pragma pack(pop)

struct TCmdDelItem
{
	unsigned char bCmd;
	unsigned char bLoc;
};

/* __declspec(align(2)) */
#pragma pack(push, 1)
struct TCmdDamage
{
	unsigned char bCmd;
	unsigned char bPlr;
	int dwDam;
};
#pragma pack(pop)

struct TFakeCmdPlr
{
	unsigned char bCmd;
	unsigned char bPlr;
};

/* __declspec(align(2)) */
#pragma pack(push, 1)
struct TFakeDropPlr
{
	unsigned char bCmd;
	unsigned char bPlr;
	int dwReason;
};
#pragma pack(pop)

struct TCmdString
{
	unsigned char bCmd;
	char str[80];
};

/* __declspec(align(1)) */
#pragma pack(push, 1)
struct TCmdPlrInfoHdr
{
	unsigned char bCmd;
	unsigned short wOffset;
	unsigned short wBytes;
};
#pragma pack(pop)

struct PortalStruct
{
	int open;
	int x;
	int y;
	int level;
	int ltype;
	int setlvl;
};

struct CircleCoord
{
	unsigned char n_1;
	Coord delta_1[1];
	unsigned char n_4;
	Coord delta_4[4];
	unsigned char n_16;
	Coord delta_16[16];
	unsigned char n_24;
	Coord delta_24[24];
	unsigned char n_32;
	Coord delta_32[32];
	unsigned char n_40;
	Coord delta_40[40];
	unsigned char n_48;
	Coord delta_48[48];
	unsigned char n_56;
	Coord delta_56[56];
	unsigned char n_64;
	Coord delta_64[64];
	unsigned char n_72;
	Coord delta_72[72];
	unsigned char n_80;
	Coord delta_80[80];
	unsigned char n_88;
	Coord delta_88[88];
	unsigned char n_96;
	Coord delta_96[96];
	unsigned char n_104;
	Coord delta_104[104];
	unsigned char n_112;
	Coord delta_112[112];
	unsigned char n_120;
	Coord delta_120[120];
	unsigned char n_128;
	Coord delta_128[128];
	unsigned char n_136;
	Coord delta_136[136];
	unsigned char n_144;
	Coord delta_144[144];
};

struct TriggerStruct
{
	int _tx;
	int _ty;
	int _tmsg;
	int _tlvl;
};

struct THEME_LOC
{
	int x;
	int y;
	int ttval;
	int width;
	int height;
};

struct STextStruct
{
	int _sx;
	int _syoff;
	char _sstr[128];
	int _sjust;
	int _sclr;
	int _sline;
	int _ssel;
	int _sval;
};

struct HALLNODE
{
	int nHallx1;
	int nHally1;
	int nHallx2;
	int nHally2;
	int nHalldir;
	HALLNODE *pNext;
};

struct ROOMNODE
{
	int nRoomx1;
	int nRoomy1;
	int nRoomx2;
	int nRoomy2;
	int nRoomDest;
};

struct LocalLevel
{
	unsigned char automapsv[40][40];
};

struct TMegaPkt
{
	TMegaPkt *pNext;
	int dwSpaceLeft;
	unsigned char data[32000];
};

struct ScrollStruct
{
	int _sxoff;
	int _syoff;
	int _sdx;
	int _sdy;
	int _sdir;
};

struct _gamedata
{
	int dwSeed;
	unsigned char bDiff;
};

struct TPkt
{
	TPktHdr hdr;
	unsigned char body[493];
};

struct MEMFILE
{
	int end;
	int offset;
	int buf_len;
	int dist;
	int bytes_to_read;
	char *buf;
	int file;
};

struct _plrmsg
{
	int time;
	char player;
	char str[144];
};

struct ItemGetRecordStruct
{
	int nSeed;
	unsigned short wCI;
	int nIndex;
	int dwTimestamp;
};

struct unk_missile_struct
{
	int field_0;
	int field_4;
	int field_8;
};

struct TSyncMonster
{
	unsigned char _mndx;
	unsigned char _mx;
	unsigned char _my;
	unsigned char _menemy;
	unsigned char _mdelta;
};

struct TSyncHeader
{
	unsigned char bCmd;
	unsigned char bLevel;
	unsigned short wLen;
	unsigned char bObjId;
	unsigned char bObjCmd;
	unsigned char bItemI;
	unsigned char bItemX;
	unsigned char bItemY;
	unsigned short wItemIndx;
	unsigned short wItemCI;
	int dwItemSeed;
	unsigned char bItemId;
	unsigned char bItemDur;
	unsigned char bItemMDur;
	unsigned char bItemCh;
	unsigned char bItemMCh;
	unsigned short wItemVal;
	unsigned int dwItemBuff;
	unsigned char bPInvLoc;
	unsigned short wPInvIndx;
	unsigned short wPInvCI;
	int dwPInvSeed;
	unsigned char bPInvId;
};

struct PCXHeader
{
	char manufacturer;
	char version;
	char encoding;
	char bitsPerPixel;
	short xmin, ymin;
	short xmax, ymax;
	short horzRes, vertRes;
	char palette[48];
	char reserved;
	char numColorPlanes;
	short bytesPerScanLine;
	short paletteType;
	short horzSize, vertSize;
	char padding[54];
};

typedef struct
{
	unsigned char * pbInBuff;           // Pointer to input data buffer
	unsigned char * pbInBuffEnd;        // End of the input buffer
	unsigned char * pbOutBuff;          // Pointer to output data buffer
	unsigned char * pbOutBuffEnd;       // Pointer to output data buffer
	unsigned char * pbSize;
} TDataInfo;

typedef struct {
	int field_0;
	int field_4;
	char command[128];
} ServerCommand;

typedef struct ChatCmd {
	struct ChatCmd *next;
	ServerCommand *extern_msgs[2];
} ChatCmd;
