//HEADER_GOES_HERE

#include "../types.h"

RECT8 QSRects[32] =
{
  { { 19u, 47u }, { 26u, 55u } },
  { { 26u, 49u }, { 30u, 53u } },
  { { 33u, 19u }, { 47u, 29u } },
  { { 37u, 29u }, { 43u, 39u } },
  { { 27u, 53u }, { 35u, 61u } },
  { { 27u, 35u }, { 34u, 42u } },
  { { 45u, 35u }, { 53u, 43u } },
  { { 45u, 53u }, { 53u, 61u } },
  { { 31u, 39u }, { 49u, 57u } },
  { { 49u, 45u }, { 58u, 51u } },
  { { 57u, 31u }, { 62u, 37u } },
  { { 63u, 31u }, { 69u, 40u } },
  { { 59u, 41u }, { 73u, 55u } },
  { { 63u, 55u }, { 69u, 65u } },
  { { 73u, 45u }, { 78u, 51u } },
  { { 79u, 43u }, { 89u, 53u } },
  { { 43u, 19u }, { 50u, 26u } },
  { { 51u, 19u }, { 59u, 26u } },
  { { 35u, 27u }, { 42u, 34u } },
  { { 43u, 27u }, { 49u, 34u } },
  { { 50u, 27u }, { 59u, 34u } },
  { { 19u, 31u }, { 34u, 47u } },
  { { 34u, 35u }, { 42u, 42u } },
  { { 43u, 35u }, { 50u, 42u } },
  { { 51u, 35u }, { 62u, 42u } },
  { { 63u, 31u }, { 66u, 46u } },
  { { 67u, 31u }, { 78u, 34u } },
  { { 67u, 35u }, { 78u, 42u } },
  { { 67u, 43u }, { 78u, 46u } },
  { { 35u, 43u }, { 42u, 51u } },
  { { 43u, 43u }, { 49u, 51u } },
  { { 50u, 43u }, { 59u, 51u } }
};
char *quest_level_names[] =
{
  &empty_string,
  "Skeleton King's Lair",
  "Bone Chamber",
  "Maze",
  "Poisoned Water Supply",
  "Archbishop Lazarus' Lair"
};

//----- (00456625) --------------------------------------------------------
int __fastcall ObjIndex(int x, int y)
{
	int i; // edi
	int oi; // esi

	i = 0;

	if ( nobjects > 0 )
	{
		while ( 1 )
		{
			oi = objectactive[i];
			if ( object[oi]._ox == x && object[oi]._oy == y )
				return oi;
			if ( ++i >= nobjects )
				break;
		}
	}
	TermMsg("ObjIndex: Active object not found at (%d,%d)", x, y);
	return -1;
}

//----- (0045666B) --------------------------------------------------------
void __cdecl AddSKingObjs()
{
	SetObjMapRange(ObjIndex(64, 34), 20, 7, 23, 10, 1);
	SetObjMapRange(ObjIndex(64, 59), 20, 14, 21, 16, 2);
	SetObjMapRange(ObjIndex(27, 37), 8, 1, 15, 11, 3);
	SetObjMapRange(ObjIndex(46, 35), 8, 1, 15, 11, 3);
	SetObjMapRange(ObjIndex(49, 53), 8, 1, 15, 11, 3);
	SetObjMapRange(ObjIndex(27, 53), 8, 1, 15, 11, 3);
}

//----- (0045671A) --------------------------------------------------------
void __cdecl AddSChamObjs()
{
	SetObjMapRange(ObjIndex(37, 30), 17, 0, 21, 5, 1);
	SetObjMapRange(ObjIndex(37, 46), 13, 0, 16, 5, 2);
}

//----- (00456755) --------------------------------------------------------
void __cdecl AddVileObjs()
{
	SetObjMapRange(ObjIndex(26, 45), 1, 1, 9, 10, 1);
	SetObjMapRange(ObjIndex(45, 46), 11, 1, 20, 10, 2);
	SetObjMapRange(ObjIndex(35, 36), 7, 11, 13, 18, 3);
}

//----- (004567AD) --------------------------------------------------------
void __fastcall DRLG_SetMapTrans(char *sFileName)
{
	unsigned char *pLevelMap; // ecx
	int v2; // ebx
	int v3; // edi
	int v4; // eax
	int v5; // edi
	int v6; // eax
	int v7; // ebx
	char *v8; // esi
	char *v9; // eax
	int v10; // [esp+Ch] [ebp-8h]
	int v11; // [esp+10h] [ebp-4h]

	pLevelMap = LoadFileInMem(sFileName, 0);
	v11 = 0;
	v2 = *pLevelMap;
	v3 = pLevelMap[2];
	v4 = v3;
	v5 = 2 * v3;
	v6 = v2 * v4;
	v7 = 2 * v2;
	v8 = (char *)&pLevelMap[6 * v7 * v5 + 4 + 2 * v6];
	if ( v5 > 0 )
	{
		do
		{
			if ( v7 > 0 )
			{
				v10 = v7;
				v9 = &dung_map[16][v11 + 16];
				do
				{
					*v9 = *v8;
					v8 += 2;
					v9 += 112;
					--v10;
				}
				while ( v10 );
			}
			++v11;
		}
		while ( v11 < v5 );
	}
	mem_free_dbg(pLevelMap);
}

//----- (00456819) --------------------------------------------------------
void __cdecl LoadSetMap()
{
	switch ( setlvlnum )
	{
		case SL_SKELKING:
			if ( quests[12]._qactive == 1 )
			{
				quests[12]._qactive = 2;
				quests[12]._qvar1 = 1;
			}
			LoadPreL1Dungeon("Levels\\L1Data\\SklKng1.DUN", 83, 45);
			LoadL1Dungeon("Levels\\L1Data\\SklKng2.DUN", 83, 45);
			LoadPalette("Levels\\L1Data\\L1_2.pal");
			DRLG_AreaTrans(2, (unsigned char *)QSRects);
			DRLG_ListTrans(2, (unsigned char *)&QSRects[2]);
			DRLG_AreaTrans(5, (unsigned char *)&QSRects[4]);
			DRLG_ListTrans(7, (unsigned char *)&QSRects[9]);
			AddL1Objs(0, 0, 112, 112);
			AddSKingObjs();
			InitSKingTriggers();
			break;
		case SL_BONECHAMB:
			LoadPreL2Dungeon("Levels\\L2Data\\Bonecha2.DUN", 69, 39);
			LoadL2Dungeon("Levels\\L2Data\\Bonecha1.DUN", 69, 39);
			LoadPalette("Levels\\L2Data\\L2_2.pal");
			DRLG_ListTrans(5, (unsigned char *)&QSRects[16]);
			DRLG_AreaTrans(2, (unsigned char *)&QSRects[21]);
			DRLG_ListTrans(9, (unsigned char *)&QSRects[23]);
			AddL2Objs(0, 0, 112, 112);
			AddSChamObjs();
			InitSChambTriggers();
			break;
		case SL_MAZE:
			LoadPreL1Dungeon("Levels\\L1Data\\Lv1MazeA.DUN", 20, 50);
			LoadL1Dungeon("Levels\\L1Data\\Lv1MazeB.DUN", 20, 50);
			LoadPalette("Levels\\L1Data\\L1_5.pal");
			AddL1Objs(0, 0, 112, 112);
			DRLG_SetMapTrans("Levels\\L1Data\\Lv1MazeA.DUN");
			break;
		case SL_POISONWATER:
			if ( quests[13]._qactive == 1 )
				quests[13]._qactive = 2;
			LoadPreL3Dungeon("Levels\\L3Data\\Foulwatr.DUN", 19, 50);
			LoadL3Dungeon("Levels\\L3Data\\Foulwatr.DUN", 20, 50);
			LoadPalette("Levels\\L3Data\\L3pfoul.pal");
			InitPWaterTriggers();
			break;
		case SL_VILEBETRAYER:
			if ( quests[15]._qactive == 3 )
			{
				quests[15]._qvar2 = 4;
			}
			else if ( quests[15]._qactive == 2 )
			{
				quests[15]._qvar2 = 3;
			}
			LoadPreL1Dungeon("Levels\\L1Data\\Vile1.DUN", 35, 36);
			LoadL1Dungeon("Levels\\L1Data\\Vile2.DUN", 35, 36);
			LoadPalette("Levels\\L1Data\\L1_2.pal");
			AddL1Objs(0, 0, 112, 112);
			AddVileObjs();
			DRLG_SetMapTrans("Levels\\L1Data\\Vile1.DUN");
			InitNoTriggers();
			break;
	}
}
// 5CCB10: using guessed type char setlvlnum;
