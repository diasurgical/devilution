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

#include "../types.h"

int qtopline; // idb
int questlog; // weak
void *pQLogCel;
QuestStruct quests[16];
int qline; // weak
int qlist[16];
int numqlines; // weak
int WaterDone; // idb
int ReturnLvlY; // idb
int ReturnLvlX; // idb
int ReturnLvlT; // idb
int ALLQUESTS; // idb
int ReturnLvl; // idb

QuestData questlist[16] =
{
  { 5, -1, DTYPE_NONE, 0, 100, 0, 0, QUEST_INFRA5, "The Magic Rock" },
  { 9, -1, DTYPE_NONE, 1, 100, 0, 0, QUEST_MUSH8, "Black Mushroom" },
  { 4, -1, DTYPE_NONE, 2, 100, 0, 0, QUEST_GARBUD1, "Gharbad The Weak" },
  { 8, -1, DTYPE_NONE, 3, 100, 0, 0, QUEST_ZHAR1, "Zhar the Mad" },
  { 14, -1, DTYPE_NONE, 4, 100, 0, 0, QUEST_VEIL9, "Lachdanan" },
  { 15, -1, DTYPE_NONE, 5, 100, 0, 1, QUEST_VILE3, "Diablo" },
  { 2, 2, DTYPE_NONE, 6, 100, 0, 1, QUEST_BUTCH9, "The Butcher" },
  { 4, -1, DTYPE_NONE, 7, 100, 0, 0, QUEST_BANNER2, "Ogden's Sign" },
  { 7, -1, DTYPE_NONE, 8, 100, 0, 0, QUEST_BLINDING, "Halls of the Blind" },
  { 5, -1, DTYPE_NONE, 9, 100, 0, 0, QUEST_BLOODY, "Valor" },
  { 10, -1, DTYPE_NONE, 10, 100, 0, 0, QUEST_ANVIL5, "Anvil of Fury" },
  { 13, -1, DTYPE_NONE, 11, 100, 0, 0, QUEST_BLOODWAR, "Warlord of Blood" },
  { 3, 3, DTYPE_CATHEDRAL, 12, 100, 1, 1, QUEST_KING2, "The Curse of King Leoric" },
  { 2, -1, DTYPE_CAVES, 13, 100, 4, 0, QUEST_POISON3, "Poisoned Water Supply" },
  { 6, -1, DTYPE_CATACOMBS, 14, 100, 2, 0, QUEST_BONER, "The Chamber of Bone" },
  { 15, 15, DTYPE_CATHEDRAL, 15, 100, 5, 1, QUEST_VILE1, "Archbishop Lazarus" }
};
char questxoff[7] = { 0, -1, 0, -1, -2, -1, -2 };
char questyoff[7] = { 0, 0, -1, -1, -1, -2, -2 };
char *questtrigstr[5] =
{
  "King Leoric's Tomb",
  "The Chamber of Bone",
  "Maze",
  "A Dark Passage",
  "Unholy Altar"
};
int QuestGroup1[3] = { QTYPE_BUTCH, QTYPE_BOL, QTYPE_GARB };
int QuestGroup2[3] = { QTYPE_BLIND, QTYPE_INFRA, QTYPE_BLOOD };
int QuestGroup3[3] = { QTYPE_BLKM, QTYPE_ZHAR, QTYPE_ANVIL };
int QuestGroup4[2] = { QTYPE_VEIL, QTYPE_WARLRD };

//----- (0045138E) --------------------------------------------------------
void __cdecl InitQuests()
{
	char v0; // dl
	unsigned char *v1; // esi
	unsigned char *v2; // eax
	unsigned char *v3; // ecx
	int *v4; // eax
	int v5; // ebp
	unsigned int v6; // edi
	//int v7; // eax
	unsigned char v8; // al
	unsigned char v9; // al
	char v10; // al
	int v11; // ecx
	int v12; // ecx
	int v13; // eax
	int v14; // ecx
	int v15; // eax
	int v16; // ecx
	int v17; // eax
	int v18; // ecx
	int v19; // eax
	char v20; // [esp+8h] [ebp-4h]

	v0 = gbMaxPlayers;
	v1 = &quests[0]._qactive;
	if ( gbMaxPlayers == 1 )
	{
		v2 = &quests[0]._qactive;
		do
		{
			*v2 = 0;
			v2 += 24;
		}
		while ( (signed int)v2 < (signed int)&quests[16]._qactive );
	}
	else
	{
		v3 = &quests[0]._qactive;
		v4 = &questlist[0]._qflags;
		do
		{
			if ( !(*(_BYTE *)v4 & 1) )
				*v3 = 0;
			v4 += 5;
			v3 += 24;
		}
		while ( (signed int)v4 < (signed int)&questlist[16]._qflags );
	}
	v5 = 0;
	questlog = 0;
	ALLQUESTS = 1;
	WaterDone = 0;
	v20 = 0;
	v6 = 0;
	do
	{
		if ( (unsigned char)v0 <= 1u || questlist[v6]._qflags & 1 )
		{
			*(v1 - 1) = questlist[v6]._qdtype;
			if ( (unsigned char)v0 <= 1u )
			{
				v8 = questlist[v6]._qdlvl;
				*v1 = 1;
				*(v1 - 2) = v8;
				v1[13] = 0;
				*(_DWORD *)(v1 + 18) = 0;
			}
			else
			{
				*(v1 - 2) = questlist[v6]._qdmultlvl;
				//_LOBYTE(v7) = delta_quest_inited(v5);
				if ( !delta_quest_inited(v5) )
				{
					*v1 = 1;
					v1[13] = 0;
					*(_DWORD *)(v1 + 18) = 0;
				}
				v0 = gbMaxPlayers;
				++v5;
			}
			v9 = questlist[v6]._qslvl;
			*(_DWORD *)(v1 + 2) = 0;
			v1[10] = v9;
			v1[11] = v20;
			v1[1] = questlist[v6]._qlvlt;
			v10 = questlist[v6]._qdmsg;
			*(_DWORD *)(v1 + 6) = 0;
			v1[14] = 0;
			v1[12] = v10;
		}
		++v20;
		++v6;
		v1 += 24;
	}
	while ( v6 < 16 );
	if ( v0 == 1 )
	{
		SetRndSeed(glSeedTbl[15]);
		_LOBYTE(v11) = 0;
		if ( random(v11, 2) )
			quests[13]._qactive = 0;
		else
			quests[12]._qactive = 0;
		_LOBYTE(v12) = 0;
		v13 = random(v12, 3);
		_LOBYTE(v14) = 0;
		quests[QuestGroup1[v13]]._qactive = 0;
		v15 = random(v14, 3);
		_LOBYTE(v16) = 0;
		quests[QuestGroup2[v15]]._qactive = 0;
		v17 = random(v16, 3);
		_LOBYTE(v18) = 0;
		quests[QuestGroup3[v17]]._qactive = 0;
		v19 = random(v18, 2);
		v0 = gbMaxPlayers;
		quests[QuestGroup4[v19]]._qactive = 0;
	}
#ifdef _DEBUG
	if ( questdebug != -1 )
		quests[questdebug]._qactive = 2;
#endif
	if ( !quests[12]._qactive )
		quests[12]._qvar2 = 2;
	if ( !quests[0]._qactive )
		quests[0]._qvar2 = 2;
	quests[7]._qvar1 = 1;
	if ( v0 != 1 )
		quests[15]._qvar1 = 2;
}
// 679660: using guessed type char gbMaxPlayers;
// 69BD04: using guessed type int questlog;
// 69BE90: using guessed type int qline;

//----- (0045155C) --------------------------------------------------------
void __cdecl CheckQuests()
{
	//int v0; // eax
	unsigned char *v1; // esi
	unsigned char v2; // cl

	//_LOBYTE(v0) = QuestStatus(15);
	if ( QuestStatus(15) )
	{
		if ( gbMaxPlayers == 1 )
			goto LABEL_6;
		if ( quests[15]._qvar1 == 2 )
		{
			AddObject(OBJ_ALTBOY, 2 * setpc_x + 20, 2 * setpc_y + 22);
			quests[15]._qvar1 = 3;
			NetSendCmdQuest(1u, 0xFu);
		}
	}
	if ( gbMaxPlayers != 1 )
		return;
LABEL_6:
	if ( currlevel == quests[15]._qlevel && !setlevel && quests[15]._qvar1 >= 2u )
	{
		if ( quests[15]._qactive != 2 && quests[15]._qactive != 3 )
			goto LABEL_29;
		if ( !quests[15]._qvar2 || quests[15]._qvar2 == 2 )
		{
			quests[15]._qtx = 2 * quests[15]._qtx + 16;
			quests[15]._qty = 2 * quests[15]._qty + 16;
			AddMissile(quests[15]._qtx, quests[15]._qty, quests[15]._qtx, quests[15]._qty, 0, 65, 0, myplr, 0, 0);
			quests[15]._qvar2 = 1;
			if ( quests[15]._qactive == 2 )
				quests[15]._qvar1 = 3;
		}
	}
	if ( quests[15]._qactive == 3 )
	{
		if ( !setlevel )
			goto LABEL_29;
		if ( setlvlnum == SL_VILEBETRAYER && quests[15]._qvar2 == 4 )
		{
			AddMissile(35, 32, 35, 32, 0, 65, 0, myplr, 0, 0);
			quests[15]._qvar2 = 3;
		}
	}
	if ( setlevel )
	{
		if ( setlvlnum == quests[13]._qslvl
		  && quests[13]._qactive != 1
		  && leveltype == quests[13]._qlvltype
		  && nummonsters == 4
		  && quests[13]._qactive != 3 )
		{
			quests[13]._qactive = 3;
			PlaySfxLoc(IS_QUESTDN, plr[myplr].WorldX, plr[myplr].WorldY);
			LoadPalette("Levels\\L3Data\\L3pwater.pal");
			WaterDone = 32;
		}
		if ( WaterDone > 0 )
		{
			palette_update_quest_palette(WaterDone);
			--WaterDone;
		}
		return;
	}
LABEL_29:
	if ( plr[myplr]._pmode == PM_STAND )
	{
		v1 = &quests[0]._qactive;
		do
		{
			if ( currlevel == *(v1 - 2) )
			{
				v2 = v1[10];
				if ( v2 )
				{
					if ( *v1 && plr[myplr].WorldX == *(_DWORD *)(v1 + 2) && plr[myplr].WorldY == *(_DWORD *)(v1 + 6) )
					{
						if ( v1[1] != -1 )
							setlvltype = v1[1];
						StartNewLvl(myplr, WM_DIABSETLVL, v2);
					}
				}
			}
			v1 += 24;
		}
		while ( (signed int)v1 < (signed int)&quests[16]._qactive );
	}
}
// 5BB1ED: using guessed type char leveltype;
// 5CCB10: using guessed type char setlvlnum;
// 5CF31C: using guessed type char setlvltype;
// 5CF31D: using guessed type char setlevel;
// 679660: using guessed type char gbMaxPlayers;
// 69BE90: using guessed type int qline;

//----- (0045178F) --------------------------------------------------------
bool __cdecl ForceQuests()
{
	QuestStruct *v0; // eax
	int v1; // esi
	int v2; // edi
	int v3; // edx

	if ( gbMaxPlayers != 1 )
		return 0;
	v0 = (QuestStruct *)((char *)quests + 12);
	while ( v0 == (QuestStruct *)&quests[15]._qslvl || currlevel != v0[-1]._qslvl || !v0->_qlevel )
	{
LABEL_10:
		++v0;
		if ( (signed int)v0 >= (signed int)&quests[16]._qslvl ) /* fix */
			return 0;
	}
	v1 = *(_DWORD *)&v0[-1]._qvar2;
	v2 = v0[-1]._qlog;
	v3 = 0;
	while ( v1 + questxoff[v3] != cursmx || v2 + questyoff[v3] != cursmy )
	{
		if ( ++v3 >= 7 )
			goto LABEL_10;
	}
	sprintf(infostr, "To %s", questtrigstr[(unsigned char)quests[(unsigned char)v0->_qtype]._qslvl - 1]);
	cursmx = v1;
	cursmy = v2;
	return 1;
}
// 679660: using guessed type char gbMaxPlayers;

//----- (00451831) --------------------------------------------------------
bool __fastcall QuestStatus(int i)
{
	bool result; // al

	if ( setlevel
	  || currlevel != quests[i]._qlevel
	  || !quests[i]._qactive
	  || (result = 1, gbMaxPlayers != 1) && !(questlist[i]._qflags & 1) )
	{
		result = 0;
	}
	return result;
}
// 5CF31D: using guessed type char setlevel;
// 679660: using guessed type char gbMaxPlayers;

//----- (00451871) --------------------------------------------------------
void __fastcall CheckQuestKill(int m, unsigned char sendmsg)
{
	int v2; // ecx
	char v3; // al
	char v4; // al
	unsigned char v5; // dl
	char v6; // al
	char *v7; // ecx
	char v8; // al
	char v9; // al
	int v10; // edi
	int (*v11)[112]; // esi
	signed int v12; // ecx
	int *v13; // eax
	int (*v14)[112]; // ebx
	char v15; // al
	char v16; // al
	char v17; // al

	v2 = m;
	v3 = monster[v2].MType->mtype;
	if ( v3 == MT_SKING )
	{
		quests[12]._qactive = 3;
		sfxdelay = 30;
		v4 = plr[myplr]._pClass;
		if ( v4 )
		{
			if ( v4 == 1 )
			{
				sfxdnum = PS_ROGUE82;
			}
			else if ( v4 == 2 )
			{
				sfxdnum = PS_MAGE82;
			}
		}
		else
		{
			sfxdnum = PS_WARR82;
		}
		if ( sendmsg )
		{
			v5 = 12;
LABEL_10:
			NetSendCmdQuest(1u, v5);
			return;
		}
	}
	else
	{
		if ( v3 != MT_CLEAVER )
		{
			v7 = monster[v2].mName;
			if ( v7 == UniqMonst[0].mName )
			{
				quests[2]._qactive = 3;
				sfxdelay = 30;
				v8 = plr[myplr]._pClass;
				if ( v8 )
				{
					if ( v8 == 1 )
					{
						sfxdnum = PS_ROGUE61;
					}
					else if ( v8 == 2 )
					{
						sfxdnum = PS_MAGE61;
					}
				}
				else
				{
					sfxdnum = PS_WARR61;
				}
				return;
			}
			if ( v7 == UniqMonst[2].mName )
			{
				quests[3]._qactive = 3;
				sfxdelay = 30;
				v9 = plr[myplr]._pClass;
				if ( v9 )
				{
					if ( v9 == 1 )
					{
						sfxdnum = PS_ROGUE62;
					}
					else if ( v9 == 2 )
					{
						sfxdnum = PS_MAGE62;
					}
				}
				else
				{
					sfxdnum = PS_WARR62;
				}
				return;
			}
			if ( v7 == UniqMonst[4].mName )
			{
				if ( gbMaxPlayers != 1 )
				{
					quests[15]._qactive = 3;
					quests[15]._qvar1 = 7;
					sfxdelay = 30;
					quests[5]._qactive = 2;
					v10 = 0;
					v11 = dPiece;
					do
					{
						v12 = 0;
						v13 = &trigs[trigflag[4]]._ty;
						v14 = v11;
						do
						{
							if ( (*v14)[0] == 370 )
							{
								++trigflag[4];
								*(v13 - 1) = v12;
								*v13 = v10;
								v13[1] = 1026;
								v13 += 4;
							}
							++v12;
							++v14;
						}
						while ( v12 < 112 );
						v11 = (int (*)[112])((char *)v11 + 4);
						++v10;
					}
					while ( (signed int)v11 < (signed int)dPiece[1] );
					v15 = plr[myplr]._pClass;
					if ( v15 )
					{
						if ( v15 == 1 )
						{
							sfxdnum = PS_ROGUE83;
						}
						else if ( v15 == 2 )
						{
							sfxdnum = PS_MAGE83;
						}
					}
					else
					{
						sfxdnum = PS_WARR83;
					}
					if ( sendmsg )
					{
						NetSendCmdQuest(1u, 0xFu);
						v5 = 5;
						goto LABEL_10;
					}
					return;
				}
				if ( v7 == UniqMonst[4].mName && gbMaxPlayers == 1 )
				{
					quests[15]._qactive = 3;
					sfxdelay = 30;
					InitVPTriggers();
					quests[15]._qvar1 = 7;
					quests[15]._qvar2 = 4;
					quests[5]._qactive = 2;
					AddMissile(35, 32, 35, 32, 0, 65, 0, myplr, 0, 0);
					v16 = plr[myplr]._pClass;
					if ( v16 )
					{
						if ( v16 == 1 )
						{
							sfxdnum = PS_ROGUE83;
						}
						else if ( v16 == 2 )
						{
							sfxdnum = PS_MAGE83;
						}
					}
					else
					{
						sfxdnum = PS_WARR83;
					}
					return;
				}
			}
			if ( v7 == UniqMonst[8].mName )
			{
				quests[11]._qactive = 3;
				sfxdelay = 30;
				v17 = plr[myplr]._pClass;
				if ( v17 )
				{
					if ( v17 == 1 )
					{
						sfxdnum = PS_ROGUE94;
					}
					else if ( v17 == 2 )
					{
						sfxdnum = PS_MAGE94;
					}
				}
				else
				{
					sfxdnum = PS_WARR94;
				}
			}
			return;
		}
		quests[6]._qactive = 3;
		sfxdelay = 30;
		v6 = plr[myplr]._pClass;
		if ( v6 )
		{
			if ( v6 == 1 )
			{
				sfxdnum = PS_ROGUE80;
			}
			else if ( v6 == 2 )
			{
				sfxdnum = PS_MAGE80;
			}
		}
		else
		{
			sfxdnum = PS_WARR80;
		}
		if ( sendmsg )
		{
			v5 = 6;
			goto LABEL_10;
		}
	}
}
// 52A554: using guessed type int sfxdelay;
// 679660: using guessed type char gbMaxPlayers;

//----- (00451BEA) --------------------------------------------------------
void __cdecl DrawButcher()
{
	DRLG_RectTrans(2 * setpc_x + 19, 2 * setpc_y + 19, 2 * setpc_x + 26, 2 * setpc_y + 26);
}

//----- (00451C11) --------------------------------------------------------
void __fastcall DrawSkelKing(int quest_id, int xx, int yy)
{
	int v3; // eax

	v3 = quest_id;
	quests[v3]._qtx = 2 * xx + 28;
	quests[v3]._qty = 2 * yy + 23;
}

//----- (00451C32) --------------------------------------------------------
void __fastcall DrawWarLord(int xx, int yy)
{
	int v2; // esi
	int v3; // edi
	unsigned char *v4; // eax
	int v5; // ebx
	int v6; // edx
	int v7; // edx
	char *v8; // eax
	int v9; // ecx
	char *v10; // esi
	char v11; // bl
	unsigned char *ptr; // [esp+Ch] [ebp-Ch]
	int v13; // [esp+10h] [ebp-8h]
	int v14; // [esp+14h] [ebp-4h]

	v2 = yy;
	v3 = xx;
	v4 = LoadFileInMem("Levels\\L4Data\\Warlord2.DUN", 0);
	v5 = *v4;
	ptr = v4;
	v4 += 2;
	v14 = v2;
	v6 = *v4;
	setpc_h = v6;
	v7 = v2 + v6;
	v8 = (char *)(v4 + 2);
	setpc_w = v5;
	setpc_x = v3;
	setpc_y = v2;
	if ( v2 < v7 )
	{
		v13 = v3 + v5;
		do
		{
			if ( v3 < v13 )
			{
				v9 = v13 - v3;
				v10 = &dungeon[v3][v14];
				do
				{
					v11 = *v8;
					if ( !*v8 )
						v11 = 6;
					*v10 = v11;
					v8 += 2;
					v10 += 40;
					--v9;
				}
				while ( v9 );
			}
			++v14;
		}
		while ( v14 < v7 );
	}
	mem_free_dbg(ptr);
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

//----- (00451CC2) --------------------------------------------------------
void __fastcall DrawSChamber(int quest_id, int xx, int yy)
{
	int v3; // esi
	unsigned char *v4; // eax
	int v5; // edi
	int v6; // ebx
	int v7; // eax
	char *v8; // ecx
	int v9; // eax
	char *v10; // edx
	char v11; // bl
	int v12; // edx
	unsigned char *ptr; // [esp+Ch] [ebp-10h]
	int v14; // [esp+10h] [ebp-Ch]
	int v15; // [esp+14h] [ebp-8h]
	int v16; // [esp+18h] [ebp-4h]

	v3 = xx;
	v14 = quest_id;
	v4 = LoadFileInMem("Levels\\L2Data\\Bonestr1.DUN", 0);
	v5 = yy;
	ptr = v4;
	v6 = yy;
	v7 = *v4;
	setpc_h = ptr[2];
	v8 = (char *)(ptr + 4);
	setpc_w = v7;
	setpc_x = v3;
	setpc_y = yy;
	v15 = yy + setpc_h;
	if ( yy < yy + setpc_h )
	{
		v16 = v3 + v7;
		do
		{
			if ( v3 < v16 )
			{
				v9 = v16 - v3;
				v10 = &dungeon[v3][v6];
				do
				{
					v11 = *v8;
					if ( !*v8 )
						v11 = 3;
					*v10 = v11;
					v8 += 2;
					v10 += 40;
					--v9;
				}
				while ( v9 );
			}
			v6 = yy++ + 1;
		}
		while ( yy < v15 );
	}
	v12 = v14;
	quests[v12]._qtx = 2 * v3 + 22;
	quests[v12]._qty = 2 * v5 + 23;
	mem_free_dbg(ptr);
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

//----- (00451D7C) --------------------------------------------------------
void __fastcall DrawLTBanner(int xx, int yy)
{
	int v2; // ebx
	int v3; // esi
	unsigned char *v4; // eax
	unsigned char *v5; // ecx
	int v6; // edi
	int v7; // edx
	int v8; // eax
	char *v9; // edx
	char *v10; // ecx
	unsigned char *ptr; // [esp+Ch] [ebp-10h]
	int v12; // [esp+10h] [ebp-Ch]
	int v13; // [esp+14h] [ebp-8h]
	int v14; // [esp+18h] [ebp-4h]

	v2 = yy;
	v3 = xx;
	v12 = yy;
	v4 = LoadFileInMem("Levels\\L1Data\\Banner1.DUN", 0);
	v5 = v4;
	v14 = 0;
	ptr = v4;
	v6 = *v4;
	v7 = (int)(v4 + 2);
	v8 = v4[2];
	setpc_w = v6;
	v9 = (char *)(v7 + 2);
	setpc_h = v8;
	setpc_x = v3;
	setpc_y = v2;
	if ( v8 > 0 )
	{
		do
		{
			if ( v6 > 0 )
			{
				v13 = v6;
				v10 = &pdungeon[v3][v14 + v12];
				do
				{
					if ( *v9 )
						*v10 = *v9;
					v10 += 40;
					v9 += 2;
					--v13;
				}
				while ( v13 );
				v5 = ptr;
			}
			++v14;
		}
		while ( v14 < v8 );
	}
	mem_free_dbg(v5);
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

//----- (00451E08) --------------------------------------------------------
void __fastcall DrawBlind(int xx, int yy)
{
	int v2; // ebx
	int v3; // esi
	unsigned char *v4; // eax
	unsigned char *v5; // ecx
	int v6; // edi
	int v7; // edx
	int v8; // eax
	char *v9; // edx
	char *v10; // ecx
	unsigned char *ptr; // [esp+Ch] [ebp-10h]
	int v12; // [esp+10h] [ebp-Ch]
	int v13; // [esp+14h] [ebp-8h]
	int v14; // [esp+18h] [ebp-4h]

	v2 = yy;
	v3 = xx;
	v12 = yy;
	v4 = LoadFileInMem("Levels\\L2Data\\Blind1.DUN", 0);
	v5 = v4;
	v14 = 0;
	ptr = v4;
	v6 = *v4;
	v7 = (int)(v4 + 2);
	v8 = v4[2];
	setpc_x = v3;
	v9 = (char *)(v7 + 2);
	setpc_y = v2;
	setpc_w = v6;
	setpc_h = v8;
	if ( v8 > 0 )
	{
		do
		{
			if ( v6 > 0 )
			{
				v13 = v6;
				v10 = &pdungeon[v3][v14 + v12];
				do
				{
					if ( *v9 )
						*v10 = *v9;
					v10 += 40;
					v9 += 2;
					--v13;
				}
				while ( v13 );
				v5 = ptr;
			}
			++v14;
		}
		while ( v14 < v8 );
	}
	mem_free_dbg(v5);
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

//----- (00451E94) --------------------------------------------------------
void __fastcall DrawBlood(int xx, int yy)
{
	int v2; // ebx
	int v3; // esi
	unsigned char *v4; // eax
	unsigned char *v5; // ecx
	int v6; // edi
	int v7; // edx
	int v8; // eax
	char *v9; // edx
	char *v10; // ecx
	unsigned char *ptr; // [esp+Ch] [ebp-10h]
	int v12; // [esp+10h] [ebp-Ch]
	int v13; // [esp+14h] [ebp-8h]
	int v14; // [esp+18h] [ebp-4h]

	v2 = yy;
	v3 = xx;
	v12 = yy;
	v4 = LoadFileInMem("Levels\\L2Data\\Blood2.DUN", 0);
	v5 = v4;
	v14 = 0;
	ptr = v4;
	v6 = *v4;
	v7 = (int)(v4 + 2);
	v8 = v4[2];
	setpc_x = v3;
	v9 = (char *)(v7 + 2);
	setpc_y = v2;
	setpc_w = v6;
	setpc_h = v8;
	if ( v8 > 0 )
	{
		do
		{
			if ( v6 > 0 )
			{
				v13 = v6;
				v10 = &dungeon[v3][v14 + v12];
				do
				{
					if ( *v9 )
						*v10 = *v9;
					v10 += 40;
					v9 += 2;
					--v13;
				}
				while ( v13 );
				v5 = ptr;
			}
			++v14;
		}
		while ( v14 < v8 );
	}
	mem_free_dbg(v5);
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

//----- (00451F20) --------------------------------------------------------
void __fastcall DRLG_CheckQuests(int xx, int yy)
{
	int v2; // esi
	int v3; // edi
	int v4; // ebx
	unsigned char *v5; // ebp
	//int v6; // eax

	v2 = yy;
	v3 = xx;
	v4 = 0;
	v5 = &quests[0]._qtype;
	do
	{
		//_LOBYTE(v6) = QuestStatus(v4);
		if ( QuestStatus(v4) )
		{
			switch ( *v5 )
			{
				case QTYPE_BUTCH:
					DrawButcher();
					break;
				case QTYPE_BOL:
					DrawLTBanner(v3, v2);
					break;
				case QTYPE_BLIND:
					DrawBlind(v3, v2);
					break;
				case QTYPE_BLOOD:
					DrawBlood(v3, v2);
					break;
				case QTYPE_WARLRD:
					DrawWarLord(v3, v2);
					break;
				case QTYPE_KING:
					DrawSkelKing(v4, v3, v2);
					break;
				case QTYPE_BONE:
					DrawSChamber(v4, v3, v2);
					break;
			}
		}
		v5 += 24;
		++v4;
	}
	while ( (signed int)v5 < (signed int)&quests[16]._qtype );
}
// 69BE90: using guessed type int qline;

//----- (00451FB1) --------------------------------------------------------
void __cdecl SetReturnLvlPos()
{
	int v0; // eax

	switch ( setlvlnum )
	{
		case SL_SKELKING:
			ReturnLvlX = quests[12]._qtx + 1;
			ReturnLvlY = quests[12]._qty;
			v0 = (unsigned char)quests[12]._qlevel;
			goto LABEL_9;
		case SL_BONECHAMB:
			ReturnLvlT = 2;
			ReturnLvlX = quests[14]._qtx + 1;
			ReturnLvlY = quests[14]._qty;
			v0 = (unsigned char)quests[14]._qlevel;
			goto LABEL_10;
		case SL_POISONWATER:
			ReturnLvlX = quests[13]._qtx;
			ReturnLvlY = quests[13]._qty + 1;
			v0 = (unsigned char)quests[13]._qlevel;
LABEL_9:
			ReturnLvlT = 1;
			goto LABEL_10;
	}
	if ( setlvlnum != 5 )
		return;
	ReturnLvlT = 4;
	ReturnLvlX = quests[15]._qtx + 1;
	ReturnLvlY = quests[15]._qty - 1;
	v0 = (unsigned char)quests[15]._qlevel;
LABEL_10:
	ReturnLvl = v0;
}
// 5CCB10: using guessed type char setlvlnum;

//----- (00452064) --------------------------------------------------------
void __cdecl GetReturnLvlPos()
{
	if ( quests[15]._qactive == 3 )
		quests[15]._qvar2 = 2;
	ViewX = ReturnLvlX;
	ViewY = ReturnLvlY;
	currlevel = ReturnLvl;
	leveltype = ReturnLvlT;
}
// 5BB1ED: using guessed type char leveltype;

//----- (0045209D) --------------------------------------------------------
void __cdecl ResyncMPQuests()
{
	if ( quests[12]._qactive == 1
	  && currlevel >= (unsigned char)quests[12]._qlevel - 1
	  && currlevel <= (unsigned char)quests[12]._qlevel + 1 )
	{
		quests[12]._qactive = 2;
		NetSendCmdQuest(1u, 0xCu);
	}
	if ( quests[6]._qactive == 1
	  && currlevel >= (unsigned char)quests[6]._qlevel - 1
	  && currlevel <= (unsigned char)quests[6]._qlevel + 1 )
	{
		quests[6]._qactive = 2;
		NetSendCmdQuest(1u, 6u);
	}
	if ( quests[15]._qactive == 1 && currlevel == (unsigned char)quests[15]._qlevel - 1 )
	{
		quests[15]._qactive = 2;
		NetSendCmdQuest(1u, 0xFu);
	}
	if ( QuestStatus(15) )
		AddObject(OBJ_ALTBOY, 2 * setpc_x + 20, 2 * setpc_y + 22);
}

//----- (00452159) --------------------------------------------------------
void __cdecl ResyncQuests()
{
	char *v0; // ecx
	int v1; // esi
	//int v2; // eax
	int i; // esi
	char v4; // bl
	int j; // esi
	char v6; // bl
	int k; // esi

	if ( setlevel && setlvlnum == quests[13]._qslvl && quests[13]._qactive != 1 && leveltype == quests[13]._qlvltype )
	{
		v0 = "Levels\\L3Data\\L3pwater.pal";
		if ( quests[13]._qactive != 3 )
			v0 = "Levels\\L3Data\\L3pfoul.pal";
		LoadPalette(v0);
		v1 = 0;
		do
			palette_update_quest_palette(v1++);
		while ( v1 <= 32 );
	}
	//_LOBYTE(v2) = QuestStatus(7);
	if ( QuestStatus(7) )
	{
		if ( quests[7]._qvar1 == 1 )
			ObjChangeMapResync(
				setpc_w + setpc_x - 2,
				setpc_h + setpc_y - 2,
				setpc_w + setpc_x + 1,
				setpc_h + setpc_y + 1);
		if ( quests[7]._qvar1 == 2 )
		{
			ObjChangeMapResync(
				setpc_w + setpc_x - 2,
				setpc_h + setpc_y - 2,
				setpc_w + setpc_x + 1,
				setpc_h + setpc_y + 1);
			ObjChangeMapResync(setpc_x, setpc_y, (setpc_w >> 1) + setpc_x + 2, (setpc_h >> 1) + setpc_y - 2);
			for ( i = 0; i < nobjects; ++i )
				SyncObjectAnim(objectactive[i]);
			v4 = TransVal;
			TransVal = 9;
			DRLG_MRectTrans(setpc_x, setpc_y, (setpc_w >> 1) + setpc_x + 4, setpc_y + (setpc_h >> 1));
			TransVal = v4;
		}
		if ( quests[7]._qvar1 == 3 )
		{
			ObjChangeMapResync(setpc_x, setpc_y, setpc_w + setpc_x + 1, setpc_h + setpc_y + 1);
			for ( j = 0; j < nobjects; ++j )
				SyncObjectAnim(objectactive[j]);
			v6 = TransVal;
			TransVal = 9;
			DRLG_MRectTrans(setpc_x, setpc_y, (setpc_w >> 1) + setpc_x + 4, setpc_y + (setpc_h >> 1));
			TransVal = v6;
		}
	}
	if ( currlevel == quests[1]._qlevel )
	{
		if ( quests[1]._qactive == 1 )
		{
			if ( !quests[1]._qvar1 )
			{
				SpawnQuestItem(19, 0, 0, 5, 1);
				quests[1]._qvar1 = 1;
			}
		}
		else if ( quests[1]._qactive == 2 )
		{
			if ( quests[1]._qvar1 < 5u )
			{
				if ( quests[1]._qvar1 >= 7u )
					Qtalklist[1]._qblkm = -1;
			}
			else
			{
				Qtalklist[6]._qblkm = -1;
				Qtalklist[1]._qblkm = 123;
			}
		}
	}
	if ( currlevel == (unsigned char)quests[4]._qlevel + 1 && quests[4]._qactive == 2 && !quests[4]._qvar1 )
	{
		quests[4]._qvar1 = 1;
		SpawnQuestItem(15, 0, 0, 5, 1);
	}
	if ( setlevel && setlvlnum == 5 )
	{
		if ( quests[15]._qvar1 >= 4u )
			ObjChangeMapResync(1, 11, 20, 18);
		if ( quests[15]._qvar1 >= 6u )
			ObjChangeMapResync(1, 18, 20, 24);
		if ( quests[15]._qvar1 >= 7u )
			InitVPTriggers();
		for ( k = 0; k < nobjects; ++k )
			SyncObjectAnim(objectactive[k]);
	}
	if ( currlevel == quests[15]._qlevel
	  && !setlevel
	  && (quests[15]._qvar2 == 1 || quests[15]._qvar2 >= 3u)
	  && (quests[15]._qactive == 2 || quests[15]._qactive == 3) )
	{
		quests[15]._qvar2 = 2;
	}
}
// 5A5590: using guessed type char TransVal;
// 5BB1ED: using guessed type char leveltype;
// 5CCB10: using guessed type char setlvlnum;
// 5CF31D: using guessed type char setlevel;
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

//----- (0045247F) --------------------------------------------------------
void __fastcall PrintQLString(int x, int y, unsigned char cjustflag, char *str, int col)
{
	int v5; // ebx
	int v6; // edi
	size_t v7; // eax
	int v8; // esi
	signed int v9; // ecx
	signed int v10; // eax
	int v11; // edx
	int v12; // ecx
	signed int v13; // ecx
	unsigned char v14; // al
	int v15; // edi
	int v16; // ecx
	int v17; // [esp+Ch] [ebp-14h]
	int v18; // [esp+10h] [ebp-10h]
	signed int v19; // [esp+14h] [ebp-Ch]
	signed int v20; // [esp+18h] [ebp-8h]
	int width; // [esp+1Ch] [ebp-4h]

	v5 = SStringY[y];
	v6 = x;
	v18 = y;
	v17 = x;
	width = screen_y_times_768[v5 + 204] + x + 96;
	v7 = strlen(str);
	v8 = 0;
	v9 = 0;
	v20 = v7;
	if ( cjustflag )
	{
		v10 = 0;
		if ( v20 <= 0 )
			goto LABEL_24;
		do
		{
			v11 = (unsigned char)str[v9++];
			v10 += fontkern[fontframe[fontidx[v11]]] + 1;
		}
		while ( v9 < v20 );
		if ( v10 < 257 )
LABEL_24:
			v8 = (257 - v10) >> 1;
		width += v8;
	}
	if ( qline == v18 )
	{
		v12 = v8 + v6 + 76;
		if ( !cjustflag )
			v12 = v6 + 76;
		CelDecodeOnly(v12, v5 + 205, pCelBuff, ALLQUESTS, 12);
	}
	v13 = 0;
	v19 = 0;
	if ( v20 > 0 )
	{
		do
		{
			v14 = fontframe[fontidx[(unsigned char)str[v13]]];
			v15 = v14;
			v8 += fontkern[v14] + 1;
			if ( v14 && v8 <= 257 )
			{
				CPrintString(width, v14, col);
				v13 = v19;
			}
			v19 = ++v13;
			width += fontkern[v15] + 1;
		}
		while ( v13 < v20 );
		v6 = v17;
	}
	if ( qline == v18 )
	{
		if ( cjustflag )
			v16 = v8 + v6 + 100;
		else
			v16 = 340 - v6;
		CelDecodeOnly(v16, v5 + 205, pCelBuff, ALLQUESTS, 12);
	}
}
// 69BE90: using guessed type int qline;

//----- (004525CD) --------------------------------------------------------
void __cdecl DrawQuestLog()
{
	int v0; // edi
	int i; // esi

	PrintQLString(0, 2, 1u, "Quest Log", 3);
	CelDecodeOnly(64, 511, pQLogCel, 1, 320);
	v0 = qtopline;
	for ( i = 0; i < numqlines; ++i )
	{
		PrintQLString(0, v0, 1u, questlist[qlist[i]]._qlstr, 0);
		v0 += 2;
	}
	PrintQLString(0, 22, 1u, "Close Quest Log", 0);
	ALLQUESTS = (ALLQUESTS & 7) + 1;
}
// 69BED4: using guessed type int numqlines;

//----- (00452659) --------------------------------------------------------
void __cdecl StartQuestlog()
{
	signed int v0; // eax
	int v1; // edx
	unsigned int v2; // ecx
	int v3; // ecx

	v0 = 0;
	v1 = 0;
	numqlines = 0;
	v2 = 0;
	do
	{
		if ( quests[v2]._qactive == 2 && quests[v2]._qlog )
			qlist[v0++] = v1;
		++v2;
		++v1;
	}
	while ( v2 < 16 );
	numqlines = v0;
	if ( v0 <= 5 )
		v3 = 8;
	else
		v3 = 5 - (v0 >> 1);
	qtopline = v3;
	qline = 22;
	if ( v0 )
		qline = v3;
	questlog = 1;
	ALLQUESTS = 1;
}
// 69BD04: using guessed type int questlog;
// 69BE90: using guessed type int qline;
// 69BED4: using guessed type int numqlines;

//----- (004526C9) --------------------------------------------------------
void __cdecl QuestlogUp()
{
	if ( numqlines )
	{
		if ( qline == qtopline )
		{
			qline = 22;
		}
		else if ( qline == 22 )
		{
			qline = qtopline + 2 * numqlines - 2;
		}
		else
		{
			qline -= 2;
		}
		PlaySFX(IS_TITLEMOV);
	}
}
// 69BE90: using guessed type int qline;
// 69BED4: using guessed type int numqlines;

//----- (00452710) --------------------------------------------------------
void __cdecl QuestlogDown()
{
	if ( numqlines )
	{
		if ( qline == 22 )
		{
			qline = qtopline;
		}
		else if ( qline == qtopline + 2 * numqlines - 2 )
		{
			qline = 22;
		}
		else
		{
			qline += 2;
		}
		PlaySFX(IS_TITLEMOV);
	}
}
// 69BE90: using guessed type int qline;
// 69BED4: using guessed type int numqlines;

//----- (0045275A) --------------------------------------------------------
void __cdecl QuestlogEnter()
{
	PlaySFX(IS_TITLSLCT);
	if ( numqlines && qline != 22 )
		InitQTextMsg((unsigned char)quests[qlist[(qline - qtopline) >> 1]]._qmsg);
	questlog = 0;
}
// 69BD04: using guessed type int questlog;
// 69BE90: using guessed type int qline;
// 69BED4: using guessed type int numqlines;

//----- (0045279C) --------------------------------------------------------
void __cdecl QuestlogESC()
{
	int v0; // esi
	int i; // edi

	v0 = (MouseY - 32) / 12;
	if ( numqlines )
	{
		for ( i = 0; i < numqlines; ++i )
		{
			if ( v0 == qtopline + 2 * i )
			{
				qline = v0;
				QuestlogEnter();
			}
		}
	}
	if ( v0 == 22 )
	{
		qline = 22;
		QuestlogEnter();
	}
}
// 69BE90: using guessed type int qline;
// 69BED4: using guessed type int numqlines;

//----- (004527F1) --------------------------------------------------------
void __fastcall SetMultiQuest(int q, int s, unsigned char l, int v1)
{
	int v4; // eax
	unsigned char *v5; // ecx
	unsigned char *v6; // eax

	v4 = q;
	v5 = &quests[q]._qactive;
	if ( *v5 != 3 )
	{
		if ( s > (unsigned char)*v5 )
			*v5 = s;
		quests[v4]._qlog |= l;
		v6 = &quests[v4]._qvar1;
		if ( v1 > (unsigned char)*v6 )
			*v6 = v1;
	}
}
