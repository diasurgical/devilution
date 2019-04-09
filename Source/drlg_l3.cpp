//HEADER_GOES_HERE

#include "../types.h"

char lavapool;  // weak
int abyssx;     // weak
int lockoutcnt; // weak
char lockout[40][40];

const unsigned char L3ConvTbl[16] = { 8, 11, 3, 10, 1, 9, 12, 12, 6, 13, 4, 13, 2, 14, 5, 7 };
const unsigned char L3UP[20] = { 3, 3, 8, 8, 0, 10, 10, 0, 7, 7, 0, 51, 50, 0, 48, 49, 0, 0, 0, 0 };
const unsigned char L3DOWN[20] = { 3, 3, 8, 9, 7, 8, 9, 7, 0, 0, 0, 0, 47, 0, 0, 46, 0, 0, 0, 0 };
const unsigned char L3HOLDWARP[20] = { 3, 3, 8, 8, 0, 10, 10, 0, 7, 7, 0, 125, 125, 0, 125, 125, 0, 0, 0, 0 };
const unsigned char L3TITE1[34] = { 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 57, 58, 0, 0, 56, 55, 0, 0, 0, 0, 0 };
const unsigned char L3TITE2[34] = { 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 61, 62, 0, 0, 60, 59, 0, 0, 0, 0, 0 };
const unsigned char L3TITE3[34] = { 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 65, 66, 0, 0, 64, 63, 0, 0, 0, 0, 0 };
const unsigned char L3TITE6[42] = { 5, 4, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 77, 78, 0, 0, 0, 76, 74, 75, 0, 0, 0, 0, 0, 0 };
const unsigned char L3TITE7[42] = { 4, 5, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 83, 0, 0, 0, 82, 80, 0, 0, 81, 79, 0, 0, 0, 0, 0 };
const unsigned char L3TITE8[20] = { 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 52, 0, 0, 0, 0 };
const unsigned char L3TITE9[20] = { 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 53, 0, 0, 0, 0 };
const unsigned char L3TITE10[20] = { 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 54, 0, 0, 0, 0 };
const unsigned char L3TITE11[20] = { 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 67, 0, 0, 0, 0 };
const unsigned char L3TITE12[6] = { 2u, 1u, 9u, 7u, 68u, 0u };
const unsigned char L3TITE13[6] = { 1u, 2u, 10u, 7u, 69u, 0u };
const unsigned char L3CREV1[6] = { 2u, 1u, 8u, 7u, 84u, 85u };
const unsigned char L3CREV2[6] = { 2u, 1u, 8u, 11u, 86u, 87u };
const unsigned char L3CREV3[6] = { 1u, 2u, 8u, 10u, 89u, 88u };
const unsigned char L3CREV4[6] = { 2u, 1u, 8u, 7u, 90u, 91u };
const unsigned char L3CREV5[6] = { 1u, 2u, 8u, 11u, 92u, 93u };
const unsigned char L3CREV6[6] = { 1u, 2u, 8u, 10u, 95u, 94u };
const unsigned char L3CREV7[6] = { 2u, 1u, 8u, 7u, 96u, 101u };
const unsigned char L3CREV8[6] = { 1u, 2u, 2u, 8u, 102u, 97u };
const unsigned char L3CREV9[6] = { 2u, 1u, 3u, 8u, 103u, 98u };
const unsigned char L3CREV10[6] = { 2u, 1u, 4u, 8u, 104u, 99u };
const unsigned char L3CREV11[6] = { 1u, 2u, 6u, 8u, 105u, 100u };
const unsigned char L3ISLE1[14] = { 2u, 3u, 5u, 14u, 4u, 9u, 13u, 12u, 7u, 7u, 7u, 7u, 7u, 7u };
const unsigned char L3ISLE2[14] = { 3u, 2u, 5u, 2u, 14u, 13u, 10u, 12u, 7u, 7u, 7u, 7u, 7u, 7u };
const unsigned char L3ISLE3[14] = { 2u, 3u, 5u, 14u, 4u, 9u, 13u, 12u, 29u, 30u, 25u, 28u, 31u, 32u };
const unsigned char L3ISLE4[14] = { 3u, 2u, 5u, 2u, 14u, 13u, 10u, 12u, 29u, 26u, 30u, 31u, 27u, 32u };
const unsigned char L3ISLE5[10] = { 2u, 2u, 5u, 14u, 13u, 12u, 7u, 7u, 7u, 7u };
const unsigned char L3XTRA1[4] = { 1u, 1u, 7u, 106u };
const unsigned char L3XTRA2[4] = { 1u, 1u, 7u, 107u };
const unsigned char L3XTRA3[4] = { 1u, 1u, 7u, 108u };
const unsigned char L3XTRA4[4] = { 1u, 1u, 9u, 109u };
const unsigned char L3XTRA5[4] = { 1u, 1u, 10u, 110u };
const unsigned char L3ANVIL[244] = {
	11, 11, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 29, 26, 26, 26,
	26, 26, 30, 0, 0, 0, 29, 34, 33, 33,
	37, 36, 33, 35, 30, 0, 0, 25, 33, 37,
	27, 32, 31, 36, 33, 28, 0, 0, 25, 37,
	32, 7, 7, 7, 31, 27, 32, 0, 0, 25,
	28, 7, 7, 7, 7, 2, 2, 2, 0, 0,
	25, 35, 30, 7, 7, 7, 29, 26, 30, 0,
	0, 25, 33, 35, 26, 30, 29, 34, 33, 28,
	0, 0, 31, 36, 33, 33, 35, 34, 33, 37,
	32, 0, 0, 0, 31, 27, 27, 27, 27, 27,
	32, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0
};

void AddFenceDoors()
{
	signed int v0;    // esi
	char *v1;         // eax
	signed int v2;    // ebx
	unsigned char v3; // cl
	char v4;          // cl
	char v5;          // cl

	v0 = 0;
	do {
		v1 = (char *)&dungeon[-1][v0 + 39];
		v2 = 40;
		do {
			if (v1[1] == 7) {
				v3 = *(v1 - 39);
				if (v3 > 0x98u
				    || v3 < 0x82u
				    || (v4 = v1[41], (unsigned char)v4 > 0x98u)
				    || (unsigned char)v4 < 0x82u) {
					if ((unsigned char)*v1 <= 0x98u && (unsigned char)*v1 >= 0x82u) {
						v5 = v1[2];
						if ((unsigned char)v5 <= 0x98u && (unsigned char)v5 >= 0x82u)
							v1[1] = -109;
					}
				} else {
					v1[1] = -110;
				}
			}
			v1 += 40;
			--v2;
		} while (v2);
		++v0;
	} while (v0 < 40);
}

void FenceDoorFix()
{
	signed int v0;    // edi
	char *v1;         // eax
	signed int v2;    // esi
	char v3;          // bl
	char v4;          // cl
	unsigned char v5; // cl
	char v6;          // dl
	char v7;          // cl
	char v8;          // cl
	char v9;          // dl

	v0 = 0;
	do {
		v1 = (char *)&dungeon[-1][v0 + 39];
		v2 = 40;
		do {
			v3 = v1[1];
			if (v3 == -110
			        && ((v4 = v1[41], (unsigned char)v4 > 0x98u)
			               || (unsigned char)v4 < 0x82u
			               || (v5 = *(v1 - 39), v5 > 0x98u)
			               || v5 < 0x82u
			               || (v6 = v1[41], v6 != -126)
			                   && v5 != -126
			                   && v6 != -124
			                   && v5 != -124
			                   && v6 != -123
			                   && v5 != -123
			                   && v6 != -122
			                   && v5 != -122
			                   && v6 != -120
			                   && v5 != -120
			                   && v6 != -118
			                   && v5 != -118
			                   && v6 != -116
			                   && v5 != -116)
			    || v3 == -109
			        && ((v7 = v1[2], (unsigned char)v7 > 0x98u)
			               || (unsigned char)v7 < 0x82u
			               || (v8 = *v1, (unsigned char)*v1 > 0x98u)
			               || (unsigned char)v8 < 0x82u
			               || (v9 = v1[2], v9 != -125)
			                   && v8 != -125
			                   && v9 != -124
			                   && v8 != -124
			                   && v9 != -123
			                   && v8 != -123
			                   && v9 != -121
			                   && v8 != -121
			                   && v9 != -119
			                   && v8 != -119
			                   && v9 != -118
			                   && v8 != -118
			                   && v9 != -117
			                   && v8 != -117)) {
				v1[1] = 7;
			}
			v1 += 40;
			--v2;
		} while (v2);
		++v0;
	} while (v0 < 40);
}

int DRLG_L3Anvil()
{
	int v0;            // esi
	signed int v1;     // edi
	signed int v2;     // ebx
	signed int v3;     // eax
	int v4;            // ecx
	unsigned char v5;  // dl
	signed int v7;     // ebx
	int v8;            // edi
	int v9;            // ecx
	signed int v10;    // eax
	unsigned char v11; // dl
	signed int v12;    // [esp+Ch] [ebp-Ch]
	signed int v13;    // [esp+Ch] [ebp-Ch]
	signed int v14;    // [esp+10h] [ebp-8h]
	int v15;           // [esp+14h] [ebp-4h]

	v0 = random(0, 29);
	v1 = 0;
	v15 = random(0, 29);
	v12 = 0;
	while (1) {
		if (v12 >= 200)
			return 1;
		++v12;
		v14 = 1;
		v2 = 2;
		do {
			if (v14 != 1)
				break;
			v3 = 0;
			v4 = v15 + v1 + 40 * v0;
			do {
				if (v14 != 1)
					break;
				v5 = L3ANVIL[v2];
				if (v5 && dungeon[0][v4] != v5)
					v14 = 0;
				if (dflags[0][v4])
					v14 = 0;
				++v2;
				++v3;
				v4 += 40;
			} while (v3 < 11);
			++v1;
		} while (v1 < 11);
		v1 = 0;
		if (v14)
			break;
		if (++v0 == 29) {
			v0 = 0;
			if (++v15 == 29)
				v15 = 0;
		}
	}
	if (v12 >= 200)
		return 1;
	v13 = 11;
	v7 = 123;
	v8 = v15 + 40 * v0;
	do {
		v9 = v8;
		v10 = 11;
		do {
			v11 = L3ANVIL[v7];
			if (v11)
				dungeon[0][v9] = v11;
			dflags[0][v9] |= DFLAG_EXPLORED;
			++v7;
			v9 += 40;
			--v10;
		} while (v10);
		++v8;
		--v13;
	} while (v13);
	setpc_y = v15;
	setpc_w = 11;
	setpc_h = 11;
	setpc_x = v0;
	return 0;
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

void FixL3Warp()
{
	int i, j;

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 125 && dungeon[i + 1][j] == 125 && dungeon[i][j + 1] == 125 && dungeon[i + 1][j + 1] == 125) {
				dungeon[i][j] = 156;
				dungeon[i + 1][j] = 155;
				dungeon[i][j + 1] = 153;
				dungeon[i + 1][j + 1] = 154;
				return;
			}
			if(dungeon[i][j] == 5 && dungeon[i + 1][j + 1] == 7) {
				dungeon[i][j] = 7;
			}
		}
	}
}

void FixL3HallofHeroes()
{
	int i, j;

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 5 && dungeon[i + 1][j + 1] == 7) {
				dungeon[i][j] = 7;
			}
		}
	}
	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 5 && dungeon[i + 1][j + 1] == 12 && dungeon[i + 1][j] == 7) {
				dungeon[i][j] = 7;
				dungeon[i][j + 1] = 7;
				dungeon[i + 1][j + 1] = 7;
			}
			if(dungeon[i][j] == 5 && dungeon[i + 1][j + 1] == 12 && dungeon[i][j + 1] == 7) {
				dungeon[i][j] = 7;
				dungeon[i + 1][j] = 7;
				dungeon[i + 1][j + 1] = 7;
			}
		}
	}
}

void DRLG_L3LockRec(int x, int y)
{
	int v2;   // esi
	int v3;   // edi
	char *v4; // eax
	char *v5; // ebp

	v2 = x;
	v3 = y;
	v4 = &lockout[x][y];
	if (*v4) {
		v5 = &lockout[x][y];
		do {
			*v4 = 0;
			++lockoutcnt;
			DRLG_L3LockRec(v2, v3 - 1);
			DRLG_L3LockRec(v2, v3 + 1);
			DRLG_L3LockRec(v2 - 1, v3);
			v5 += 40;
			++v2;
			v4 = v5;
		} while (*v5);
	}
}
// 528380: using guessed type int lockoutcnt;

BOOLEAN DRLG_L3Lockout()
{
	int v0;        // esi
	signed int v1; // edx
	signed int v2; // ecx
	signed int v3; // eax
	int x;         // [esp+4h] [ebp-8h]
	int y;         // [esp+8h] [ebp-4h]

	v0 = 0;
	v1 = 0;
	do {
		v2 = 0;
		v3 = v1;
		do {
			if (dungeon[0][v3]) {
				lockout[0][v3] = 1;
				x = v2;
				y = v1;
				++v0;
			} else {
				lockout[0][v3] = 0;
			}
			++v2;
			v3 += 40;
		} while (v2 < 40);
		++v1;
	} while (v1 < 40);
	lockoutcnt = 0;
	DRLG_L3LockRec(x, y);
	return v0 == lockoutcnt;
}
// 528380: using guessed type int lockoutcnt;

void CreateL3Dungeon(unsigned int rseed, int entry)
{
	int i, j;

	SetRndSeed(rseed);
	dminx = 16;
	dminy = 16;
	dmaxx = 96;
	dmaxy = 96;
	DRLG_InitTrans();
	DRLG_InitSetPC();
	DRLG_L3(entry);
	DRLG_L3Pass3();

	for(j = 0; j < 112; j++) {
		for(i = 0; i < 112; i++) {
			if(dPiece[i][j] >= 56 && dPiece[i][j] <= 147) {
				DoLighting(i, j, 7, -1);
			} else if(dPiece[i][j] >= 154 && dPiece[i][j] <= 161) {
				DoLighting(i, j, 7, -1);
			} else if(dPiece[i][j] == 150) {
				DoLighting(i, j, 7, -1);
			} else if(dPiece[i][j] == 152) {
				DoLighting(i, j, 7, -1);
			}
		}
	}

	DRLG_SetPC();
}
// 5CF328: using guessed type int dmaxx;
// 5CF32C: using guessed type int dmaxy;
// 5D2458: using guessed type int dminx;
// 5D245C: using guessed type int dminy;

void DRLG_L3(int entry)
{
	int x1;       // esi
	int y1;       // eax
	int x2;       // edi
	int y2;       // eax
	int found;    // eax
	int genok;    // eax
	signed int i; // ecx
	signed int j; // esi
	BOOLEAN v24;  // [esp-8h] [ebp-20h]

	lavapool = 0;
	do {
		do {
			do {
				InitL3Dungeon();
				x1 = random(0, 20) + 10;
				y1 = random(0, 20);
				DRLG_L3FillRoom(x1, y1 + 10, x1 + 2, y1 + 12);
				DRLG_L3CreateBlock(x1, y1 + 10, 2, 0);
				DRLG_L3CreateBlock(x1 + 2, y1 + 10, 2, 1);
				DRLG_L3CreateBlock(x1, y1 + 12, 2, 2);
				DRLG_L3CreateBlock(x1, y1 + 10, 2, 3);

				if (QuestStatus(QTYPE_ANVIL)) {
					x2 = random(0, 10) + 10;
					y2 = random(0, 10);
					DRLG_L3FloorArea(x2, y2 + 10, x2 + 12, y2 + 22);
				}
				DRLG_L3FillDiags();
				DRLG_L3FillSingles();
				DRLG_L3FillStraights();
				DRLG_L3FillDiags();
				DRLG_L3Edges();
				if (DRLG_L3GetFloorArea() < 600)
					found = 0;
				else
					found = DRLG_L3Lockout();
			} while (!found);
			DRLG_L3MakeMegas();
			if (!entry) {
				genok = DRLG_L3PlaceMiniSet(L3UP, 1, 1, -1, -1, 1, 0);
				if (genok)
					continue;
				genok = DRLG_L3PlaceMiniSet(L3DOWN, 1, 1, -1, -1, 0, 1);
				if (genok)
					continue;
				if (currlevel != 9)
					goto LABEL_24;
				genok = DRLG_L3PlaceMiniSet(L3HOLDWARP, 1, 1, -1, -1, 0, 6);
				goto LABEL_23;
			}
			genok = DRLG_L3PlaceMiniSet(L3UP, 1, 1, -1, -1, 0, 0);
			if (entry == 1) {
				if (genok)
					continue;
				genok = DRLG_L3PlaceMiniSet(L3DOWN, 1, 1, -1, -1, 1, 1);
				ViewX += 2;
				ViewY -= 2;
				if (genok)
					continue;
				if (currlevel != 9)
					goto LABEL_24;
				v24 = 0;
			LABEL_22:
				genok = DRLG_L3PlaceMiniSet(L3HOLDWARP, 1, 1, -1, -1, v24, 6);
			LABEL_23:
				if (genok)
					continue;
				goto LABEL_24;
			}
			if (genok)
				continue;
			genok = DRLG_L3PlaceMiniSet(L3DOWN, 1, 1, -1, -1, 0, 1);
			if (genok)
				continue;
			if (currlevel == 9) {
				v24 = 1;
				goto LABEL_22;
			}
		LABEL_24:
			if (!QuestStatus(QTYPE_ANVIL))
				break;
			genok = DRLG_L3Anvil();
		} while (genok == 1);
		DRLG_L3Pool();
	} while (!lavapool);
	DRLG_L3PoolFix();
	FixL3Warp();
	DRLG_L3PlaceRndSet(L3ISLE1, 70);
	DRLG_L3PlaceRndSet(L3ISLE2, 70);
	DRLG_L3PlaceRndSet(L3ISLE3, 30);
	DRLG_L3PlaceRndSet(L3ISLE4, 30);
	DRLG_L3PlaceRndSet(L3ISLE1, 100);
	DRLG_L3PlaceRndSet(L3ISLE2, 100);
	DRLG_L3PlaceRndSet(L3ISLE5, 90);
	FixL3HallofHeroes();
	DRLG_L3River();

	if (QuestStatus(QTYPE_ANVIL)) {
		dungeon[setpc_x + 7][setpc_y + 5] = 7;
		dungeon[setpc_x + 8][setpc_y + 5] = 7;
		dungeon[setpc_x + 9][setpc_y + 5] = 7;
		if (dungeon[setpc_x + 10][setpc_y + 5] == 17
		    || dungeon[setpc_x + 10][setpc_y + 5] == 18)
			dungeon[setpc_x + 10][setpc_y + 5] = 45;
	}

	DRLG_PlaceThemeRooms(5, 10, 7, 0, 0);
	DRLG_L3Wood();
	DRLG_L3PlaceRndSet(L3TITE1, 10);
	DRLG_L3PlaceRndSet(L3TITE2, 10);
	DRLG_L3PlaceRndSet(L3TITE3, 10);
	DRLG_L3PlaceRndSet(L3TITE6, 20);
	DRLG_L3PlaceRndSet(L3TITE7, 20);
	DRLG_L3PlaceRndSet(L3TITE8, 20);
	DRLG_L3PlaceRndSet(L3TITE9, 20);
	DRLG_L3PlaceRndSet(L3TITE10, 20);
	DRLG_L3PlaceRndSet(L3TITE11, 30);
	DRLG_L3PlaceRndSet(L3TITE12, 20);
	DRLG_L3PlaceRndSet(L3TITE13, 20);
	DRLG_L3PlaceRndSet(L3CREV1, 30);
	DRLG_L3PlaceRndSet(L3CREV2, 30);
	DRLG_L3PlaceRndSet(L3CREV3, 30);
	DRLG_L3PlaceRndSet(L3CREV4, 30);
	DRLG_L3PlaceRndSet(L3CREV5, 30);
	DRLG_L3PlaceRndSet(L3CREV6, 30);
	DRLG_L3PlaceRndSet(L3CREV7, 30);
	DRLG_L3PlaceRndSet(L3CREV8, 30);
	DRLG_L3PlaceRndSet(L3CREV9, 30);
	DRLG_L3PlaceRndSet(L3CREV10, 30);
	DRLG_L3PlaceRndSet(L3CREV11, 30);
	DRLG_L3PlaceRndSet(L3XTRA1, 25);
	DRLG_L3PlaceRndSet(L3XTRA2, 25);
	DRLG_L3PlaceRndSet(L3XTRA3, 25);
	DRLG_L3PlaceRndSet(L3XTRA4, 25);
	DRLG_L3PlaceRndSet(L3XTRA5, 25);

	for (i = 0; i < 40; i++) {
		for (j = 0; j < 40; j++)
			pdungeon[i][j] = dungeon[i][j];
	}

	DRLG_Init_Globals();
}
// 528378: using guessed type char lavapool;

void InitL3Dungeon()
{
	int i, j;

	memset(dungeon, 0, sizeof(dungeon));

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			dungeon[i][j] = 0;
			dflags[i][j] = 0;
		}
	}
}

BOOL DRLG_L3FillRoom(int x1, int y1, int x2, int y2)
{
	int i, j, v;

	if(x1 <= 1 || x2 >= 34 || y1 <= 1 || y2 >= 38) {
		return FALSE;
	}

	v = 0;
	for(j = y1; j <= y2; j++) {
		for(i = x1; i <= x2; i++) {
			v += dungeon[i][j];
		}
	}

	if(v != 0) {
		return FALSE;
	}

	for(j = y1 + 1; j < y2; j++) {
		for(i = x1 + 1; i < x2; i++) {
			dungeon[i][j] = 1;
		}
	}
	for(j = y1; j <= y2; j++) {
		if(random(0, 2) != 0) {
			dungeon[x1][j] = 1;
		}
		if(random(0, 2) != 0) {
			dungeon[x2][j] = 1;
		}
	}
	for(i = x1; i <= x2; i++) {
		if(random(0, 2) != 0) {
			dungeon[i][y1] = 1;
		}
		if(random(0, 2) != 0) {
			dungeon[i][y2] = 1;
		}
	}

	return TRUE;
}

void DRLG_L3CreateBlock(int x, int y, int obs, int dir)
{
	int blksizex, blksizey, x1, y1, x2, y2;
	BOOL contflag;

	blksizex = random(0, 2) + 3;
	blksizey = random(0, 2) + 3;

	if(dir == 0) {
		y2 = y - 1;
		y1 = y2 - blksizey;
		if(blksizex < obs) {
			x1 = random(0, blksizex) + x;
		}
		if(blksizex == obs) {
			x1 = x;
		}
		if(blksizex > obs) {
			x1 = x - random(0, blksizex);
		}
		x2 = blksizex + x1;
	}
	if(dir == 3) {
		x2 = x - 1;
		x1 = x2 - blksizex;
		if(blksizey < obs) {
			y1 = random(0, blksizey) + y;
		}
		if(blksizey == obs) {
			y1 = y;
		}
		if(blksizey > obs) {
			y1 = y - random(0, blksizey);
		}
		y2 = y1 + blksizey;
	}
	if(dir == 2) {
		y1 = y + 1;
		y2 = y1 + blksizey;
		if(blksizex < obs) {
			x1 = random(0, blksizex) + x;
		}
		if(blksizex == obs) {
			x1 = x;
		}
		if(blksizex > obs) {
			x1 = x - random(0, blksizex);
		}
		x2 = blksizex + x1;
	}
	if(dir == 1) {
		x1 = x + 1;
		x2 = x1 + blksizex;
		if(blksizey < obs) {
			y1 = random(0, blksizey) + y;
		}
		if(blksizey == obs) {
			y1 = y;
		}
		if(blksizey > obs) {
			y1 = y - random(0, blksizey);
		}
		y2 = y1 + blksizey;
	}

	if(DRLG_L3FillRoom(x1, y1, x2, y2) == TRUE) {
		contflag = random(0, 4);
		if(contflag && dir != 2) {
			DRLG_L3CreateBlock(x1, y1, blksizey, 0);
		}
		if(contflag && dir != 3) {
			DRLG_L3CreateBlock(x2, y1, blksizex, 1);
		}
		if(contflag && dir != 0) {
			DRLG_L3CreateBlock(x1, y2, blksizey, 2);
		}
		if(contflag && dir != 1) {
			DRLG_L3CreateBlock(x1, y1, blksizex, 3);
		}
	}
}

void DRLG_L3FloorArea(int x1, int y1, int x2, int y2)
{
	int i;    // esi
	char *v5; // edx
	int v6;   // eax

	for (i = y1; i <= y2; ++i) {
		if (x1 <= x2) {
			v5 = (char *)&dungeon[x1][i];
			v6 = x2 - x1 + 1;
			do {
				*v5 = 1;
				v5 += 40;
				--v6;
			} while (v6);
		}
	}
}

void DRLG_L3FillDiags()
{
	int i, j, v;

	for(j = 0; j < 39; j++) {
		for(i = 0; i < 39; i++) {
			v = dungeon[i + 1][j + 1] + 2 * dungeon[i][j + 1] + 4 * dungeon[i + 1][j] + 8 * dungeon[i][j];
			if(v == 6) {
				if(random(0, 2) == 0) {
					dungeon[i][j] = 1;
				} else {
					dungeon[i + 1][j + 1] = 1;
				}
			}
			if(v == 9) {
				if(random(0, 2) == 0) {
					dungeon[i + 1][j] = 1;
				} else {
					dungeon[i][j + 1] = 1;
				}
			}
		}
	}
}

void DRLG_L3FillSingles()
{
	int i, j;

	for(j = 1; j < 39; j++) {
		for(i = 1; i < 39; i++) {
			if(dungeon[i][j] == 0
			&& dungeon[i][j - 1] + dungeon[i - 1][j - 1] + dungeon[i + 1][j - 1] == 3
			&& dungeon[i + 1][j] + dungeon[i - 1][j] == 2
			&& dungeon[i][j + 1] + dungeon[i - 1][j + 1] + dungeon[i + 1][j + 1] == 3) {
				dungeon[i][j] = 1;
			}
		}
	}
}

void DRLG_L3FillStraights()
{
	int i, j, xc, xs, yc, ys, k;

	for(j = 0; j < 39; j++) {
		xs = 0;
		for(i = 0; i < 37; i++) {
			if(dungeon[i][j] == 0 && dungeon[i][j + 1] == 1) {
				if(xs == 0) {
					xc = i;
				}
				xs++;
			} else {
				if(xs > 3 && random(0, 2) != 0) {
					for(k = xc; k < i; k++) {
						dungeon[k][j] = random(0, 2);
					}
				}
				xs = 0;
			}
		}
	}
	for(j = 0; j < 39; j++) {
		xs = 0;
		for(i = 0; i < 37; i++) {
			if(dungeon[i][j] == 1 && dungeon[i][j + 1] == 0) {
				if(xs == 0) {
					xc = i;
				}
				xs++;
			} else {
				if(xs > 3 && random(0, 2) != 0) {
					for(k = xc; k < i; k++) {
						dungeon[k][j + 1] = random(0, 2);
					}
				}
				xs = 0;
			}
		}
	}
	for(i = 0; i < 39; i++) {
		ys = 0;
		for(j = 0; j < 37; j++) {
			if(dungeon[i][j] == 0 && dungeon[i + 1][j] == 1) {
				if(ys == 0) {
					yc = j;
				}
				ys++;
			} else {
				if(ys > 3 && random(0, 2) != 0) {
					for(k = yc; k < j; k++) {
						dungeon[i][k] = random(0, 2);
					}
				}
				ys = 0;
			}
		}
	}
	for(i = 0; i < 39; i++) {
		ys = 0;
		for(j = 0; j < 37; j++) {
			if(dungeon[i][j] == 1 && dungeon[i + 1][j] == 0) {
				if(ys == 0) {
					yc = j;
				}
				ys++;
			} else {
				if(ys > 3 && random(0, 2) != 0) {
					for(k = yc; k < j; k++) {
						dungeon[i + 1][k] = random(0, 2);
					}
				}
				ys = 0;
			}
		}
	}
}

void DRLG_L3Edges()
{
	int i, j;

	for(j = 0; j < 40; j++) {
		dungeon[39][j] = 0;
	}
	for(i = 0; i < 40; i++) {
		dungeon[i][39] = 0;
	}
}

int DRLG_L3GetFloorArea()
{
	int i, j, gfa;

	gfa = 0;

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			gfa += dungeon[i][j];
		}
	}

	return gfa;
}

void DRLG_L3MakeMegas()
{
	int i, j, v;

	for(j = 0; j < 39; j++) {
		for(i = 0; i < 39; i++) {
			v = dungeon[i + 1][j + 1] + 2 * dungeon[i][j + 1] + 4 * dungeon[i + 1][j] + 8 * dungeon[i][j];
			if(v == 6) {
				if(random(0, 2) == 0) {
					v = 12;
				} else {
					v = 5;
				}
			}
			if(v == 9) {
				if(random(0, 2) == 0) {
					v = 13;
				} else {
					v = 14;
				}
			}
			dungeon[i][j] = L3ConvTbl[v];
		}
		dungeon[39][j] = 8;
	}
	for(i = 0; i < 40; i++) {
		dungeon[i][39] = 8;
	}
}

void DRLG_L3River()
{
	int rx, ry, px, py, dir, pdir, nodir, nodir2, dircheck;
	int river[3][100];
	int rivercnt, riveramt;
	int i, trys, found, bridge, lpcnt;
	BOOL bail;

	rivercnt = 0;
	bail = FALSE;
	trys = 0;

	while(trys < 200 && rivercnt < 4) {
		bail = FALSE;
		while(!bail && trys < 200) {
			trys++;
			rx = 0;
			ry = 0;
			i = 0;
			while((dungeon[rx][ry] < 25 || dungeon[rx][ry] > 28) && i < 100) {
				rx = random(0, 40);
				ry = random(0, 40);
				i++;
				while((dungeon[rx][ry] < 25 || dungeon[rx][ry] > 28) && ry < 40) {
					rx++;
					if(rx >= 40) {
						rx = 0;
						ry++;
					}
				}
			}
			if(i >= 100) {
				return;
			}
			switch(dungeon[rx][ry]) {
			case 25:
				dir = 3;
				nodir = 2;
				river[2][0] = 40;
				break;
			case 26:
				dir = 0;
				nodir = 1;
				river[2][0] = 38;
				break;
			case 27:
				dir = 1;
				nodir = 0;
				river[2][0] = 41;
				break;
			case 28:
				dir = 2;
				nodir = 3;
				river[2][0] = 39;
				break;
			}
			river[0][0] = rx;
			river[1][0] = ry;
			riveramt = 1;
			nodir2 = 4;
			dircheck = 0;
			while(dircheck < 4 && riveramt < 100) {
				px = rx;
				py = ry;
				if(dircheck == 0) {
					dir = random(0, 4);
				} else {
					dir = (dir + 1) & 3;
				}
				dircheck++;
				while(dir == nodir || dir == nodir2) {
					dir = (dir + 1) & 3;
					dircheck++;
				}
				if(dir == 0 && ry > 0) {
					ry--;
				}
				if(dir == 1 && ry < 40) {
					ry++;
				}
				if(dir == 2 && rx < 40) {
					rx++;
				}
				if(dir == 3 && rx > 0) {
					rx--;
				}
				if(dungeon[rx][ry] == 7) {
					dircheck = 0;
					if(dir < 2) {
						river[2][riveramt] = (BYTE)random(0, 2) + 17;
					}
					if(dir > 1) {
						river[2][riveramt] = (BYTE)random(0, 2) + 15;
					}
					river[0][riveramt] = rx;
					river[1][riveramt] = ry;
					riveramt++;
					if(dir == 0 && pdir == 2 || dir == 3 && pdir == 1) {
						if(riveramt > 2) {
							river[2][riveramt - 2] = 22;
						}
						if(dir == 0) {
							nodir2 = 1;
						} else {
							nodir2 = 2;
						}
					}
					if(dir == 0 && pdir == 3 || dir == 2 && pdir == 1) {
						if(riveramt > 2) {
							river[2][riveramt - 2] = 21;
						}
						if(dir == 0) {
							nodir2 = 1;
						} else {
							nodir2 = 3;
						}
					}
					if(dir == 1 && pdir == 2 || dir == 3 && pdir == 0) {
						if(riveramt > 2) {
							river[2][riveramt - 2] = 20;
						}
						if(dir == 1) {
							nodir2 = 0;
						} else {
							nodir2 = 2;
						}
					}
					if(dir == 1 && pdir == 3 || dir == 2 && pdir == 0) {
						if(riveramt > 2) {
							river[2][riveramt - 2] = 19;
						}
						if(dir == 1) {
							nodir2 = 0;
						} else {
							nodir2 = 3;
						}
					}
					pdir = dir;
				} else {
					rx = px;
					ry = py;
				}
			}
			if(dir == 0 && dungeon[rx][ry - 1] == 10 && dungeon[rx][ry - 2] == 8) {
				river[0][riveramt] = rx;
				river[1][riveramt] = ry - 1;
				river[2][riveramt] = 24;
				if(pdir == 2) {
					river[2][riveramt - 1] = 22;
				}
				if(pdir == 3) {
					river[2][riveramt - 1] = 21;
				}
				bail = TRUE;
			}
			if(dir == 1 && dungeon[rx][ry + 1] == 2 && dungeon[rx][ry + 2] == 8) {
				river[0][riveramt] = rx;
				river[1][riveramt] = ry + 1;
				river[2][riveramt] = 42;
				if(pdir == 2) {
					river[2][riveramt - 1] = 20;
				}
				if(pdir == 3) {
					river[2][riveramt - 1] = 19;
				}
				bail = TRUE;
			}
			if(dir == 2 && dungeon[rx + 1][ry] == 4 && dungeon[rx + 2][ry] == 8) {
				river[0][riveramt] = rx + 1;
				river[1][riveramt] = ry;
				river[2][riveramt] = 43;
				if(pdir == 0) {
					river[2][riveramt - 1] = 19;
				}
				if(pdir == 1) {
					river[2][riveramt - 1] = 21;
				}
				bail = TRUE;
			}
			if(dir == 3 && dungeon[rx - 1][ry] == 9 && dungeon[rx - 2][ry] == 8) {
				river[0][riveramt] = rx - 1;
				river[1][riveramt] = ry;
				river[2][riveramt] = 23;
				if(pdir == 0) {
					river[2][riveramt - 1] = 20;
				}
				if(pdir == 1) {
					river[2][riveramt - 1] = 22;
				}
				bail = TRUE;
			}
		}
		if(bail == TRUE && riveramt < 7) {
			bail = FALSE;
		}
		if(bail == TRUE) {
			found = 0;
			lpcnt = 0;
			while(found == 0 && lpcnt < 30) {
				lpcnt++;
				bridge = random(0, riveramt);
				if((river[2][bridge] == 15 || river[2][bridge] == 16)
				&& dungeon[river[0][bridge]][river[1][bridge] - 1] == 7
				&& dungeon[river[0][bridge]][river[1][bridge] + 1] == 7) {
					found = 1;
				}
				if((river[2][bridge] == 17 || river[2][bridge] == 18)
				&& dungeon[river[0][bridge] - 1][river[1][bridge]] == 7
				&& dungeon[river[0][bridge] + 1][river[1][bridge]] == 7) {
					found = 2;
				}
				for(i = 0; i < riveramt && found != 0; i++) {
					if(found == 1
					&& (river[1][bridge] - 1 == river[1][i] || river[1][bridge] + 1 == river[1][i])
					&& river[0][bridge] == river[0][i]) {
						found = 0;
					}
					if(found == 2
					&& (river[0][bridge] - 1 == river[0][i] || river[0][bridge] + 1 == river[0][i])
					&& river[1][bridge] == river[1][i]) {
						found = 0;
					}
				}
			}
			if(found != 0) {
				if(found == 1) {
					river[2][bridge] = 44;
				} else {
					river[2][bridge] = 45;
				}
				rivercnt++;
				for(bridge = 0; bridge <= riveramt; bridge++) {
					dungeon[river[0][bridge]][river[1][bridge]] = river[2][bridge];
				}
			} else {
				bail = FALSE;
			}
		}
	}
}

void DRLG_L3Pool()
{
	int i, j, dunx, duny, totarea, poolchance;
	BOOL found;
	unsigned char k;
	static unsigned char poolsub[15] = { 0, 35, 26, 36, 25, 29, 34, 7, 33, 28, 27, 37, 32, 31, 30 };

	for(duny = 0; duny < 40; duny++) {
		for(dunx = 0; dunx < 40; dunx++) {
			if(dungeon[dunx][duny] != 8) {
				continue;
			}
			dungeon[dunx][duny] |= 0x80;
			totarea = 1;
			if(dunx + 1 < 40) {
				found = DRLG_L3SpawnEdge(dunx + 1, duny, &totarea);
			} else {
				found = TRUE;
			}
			if(dunx - 1 > 0 && !found) {
				found = DRLG_L3SpawnEdge(dunx - 1, duny, &totarea);
			} else {
				found = TRUE;
			}
			if(duny + 1 < 40 && !found) {
				found = DRLG_L3SpawnEdge(dunx, duny + 1, &totarea);
			} else {
				found = TRUE;
			}
			if(duny - 1 > 0 && !found) {
				found = DRLG_L3SpawnEdge(dunx, duny - 1, &totarea);
			} else {
				found = TRUE;
			}
			poolchance = random(0, 100);
			for(j = duny - totarea; j < duny + totarea; j++) {
				for(i = dunx - totarea; i < dunx + totarea; i++) {
					if(dungeon[i][j] & 0x80 && j >= 0 && j < 40 && i >= 0 && i < 40) {
						dungeon[i][j] &= ~0x80;
						if(totarea > 4 && poolchance < 25 && !found) {
							k = poolsub[dungeon[i][j]];
							if(k != 0 && k <= 37) {
								dungeon[i][j] = k;
							}
							lavapool = 1;
						}
					}
				}
			}
		}
	}
}
// 528378: using guessed type char lavapool;

BOOL DRLG_L3SpawnEdge(int x, int y, int *totarea)
{
	unsigned char i;
	static unsigned char spawntable[15] = { 0, 10, 3, 5, 12, 6, 9, 0, 0, 12, 3, 6, 9, 10, 5 };

	if(*totarea > 40) {
		return TRUE;
	}
	if(x < 0 || y < 0 || x >= 40 || y >= 40) {
		return TRUE;
	}
	if(dungeon[x][y] & 0x80) {
		return FALSE;
	}
	if(dungeon[x][y] > 15) {
		return TRUE;
	}

	i = dungeon[x][y];
	dungeon[x][y] |= 0x80;
	*totarea += 1;

	if(i != 8) {
		if(spawntable[i] & 8 && DRLG_L3Spawn(x, y - 1, totarea) == TRUE) {
			return TRUE;
		}
		if(spawntable[i] & 4 && DRLG_L3Spawn(x, y + 1, totarea) == TRUE) {
			return TRUE;
		}
		if(spawntable[i] & 2 && DRLG_L3Spawn(x + 1, y, totarea) == TRUE) {
			return TRUE;
		}
		if(spawntable[i] & 1 && DRLG_L3Spawn(x - 1, y, totarea) == TRUE) {
			return TRUE;
		}
	} else {
		if(DRLG_L3SpawnEdge(x + 1, y, totarea) == TRUE) {
			return TRUE;
		}
		if(DRLG_L3SpawnEdge(x - 1, y, totarea) == TRUE) {
			return TRUE;
		}
		if(DRLG_L3SpawnEdge(x, y + 1, totarea) == TRUE) {
			return TRUE;
		}
		if(DRLG_L3SpawnEdge(x, y - 1, totarea) == TRUE) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL DRLG_L3Spawn(int x, int y, int *totarea)
{
	unsigned char i;
	static unsigned char spawntable[15] = { 0, 10, 67, 5, 44, 6, 9, 0, 0, 28, 131, 6, 9, 10, 5 };

	if(*totarea > 40) {
		return TRUE;
	}
	if(x < 0 || y < 0 || x >= 40 || y >= 40) {
		return TRUE;
	}
	if(dungeon[x][y] & 0x80) {
		return FALSE;
	}
	if(dungeon[x][y] > 15) {
		return TRUE;
	}

	i = dungeon[x][y];
	dungeon[x][y] |= 0x80;
	*totarea += 1;

	if(spawntable[i] & 8 && DRLG_L3Spawn(x, y - 1, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 4 && DRLG_L3Spawn(x, y + 1, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 2 && DRLG_L3Spawn(x + 1, y, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 1 && DRLG_L3Spawn(x - 1, y, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 0x80 && DRLG_L3SpawnEdge(x, y - 1, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 0x40 && DRLG_L3SpawnEdge(x, y + 1, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 0x20 && DRLG_L3SpawnEdge(x + 1, y, totarea) == TRUE) {
		return TRUE;
	}
	if(spawntable[i] & 0x10 && DRLG_L3SpawnEdge(x - 1, y, totarea) == TRUE) {
		return TRUE;
	}

	return FALSE;
}

void DRLG_L3PoolFix()
{
	signed int v0;    // esi
	char *v1;         // eax
	char *v2;         // edi
	unsigned char v3; // cl
	char v4;          // cl
	char v5;          // cl
	char v6;          // cl
	char v7;          // cl
	char v8;          // cl
	char v9;          // al
	BOOLEAN v10;      // zf
	signed int v11;   // [esp+10h] [ebp-4h]

	v0 = 0;
	do {
		v1 = (char *)&dungeon[-1][v0];
		v11 = 40;
		do {
			v2 = v1 + 40;
			if (v1[40] == 8) {
				v3 = *(v1 - 1);
				if (v3 >= 0x19u && v3 <= 0x29u && (unsigned char)*v1 >= 0x19u && (unsigned char)*v1 <= 0x29u) {
					v4 = v1[1];
					if ((unsigned char)v4 >= 0x19u && (unsigned char)v4 <= 0x29u) {
						v5 = v1[39];
						if ((unsigned char)v5 >= 0x19u && (unsigned char)v5 <= 0x29u) {
							v6 = v1[41];
							if ((unsigned char)v6 >= 0x19u && (unsigned char)v6 <= 0x29u) {
								v7 = v1[79];
								if ((unsigned char)v7 >= 0x19u && (unsigned char)v7 <= 0x29u) {
									v8 = v1[80];
									if ((unsigned char)v8 >= 0x19u && (unsigned char)v8 <= 0x29u) {
										v9 = v1[81];
										if ((unsigned char)v9 >= 0x19u && (unsigned char)v9 <= 0x29u)
											*v2 = 33;
									}
								}
							}
						}
					}
				}
			}
			v10 = v11-- == 1;
			v1 = v2;
		} while (!v10);
		++v0;
	} while (v0 < 40);
}

BOOL DRLG_L3PlaceMiniSet(const unsigned char *miniset, int tmin, int tmax, int cx, int cy, BOOL setview, int ldir)
{
	int sx, sy, sw, sh, xx, yy, i, ii, numt, trys;
	BOOL found;

	sw = miniset[0];
	sh = miniset[1];

	if(tmax - tmin == 0) {
		numt = 1;
	} else {
		numt = random(0, tmax - tmin) + tmin;
	}

	for(i = 0; i < numt; i++) {
		sx = random(0, 40 - sw);
		sy = random(0, 40 - sh);
		found = FALSE;
		trys = 0;
		while(!found && trys < 200) {
			trys++;
			found = TRUE;
			if(cx != -1 && sx >= cx - sw && sx <= cx + 12) {
				sx = random(0, 40 - sw);
				sy = random(0, 40 - sh);
				found = FALSE;
			}
			if(cy != -1 && sy >= cy - sh && sy <= cy + 12) {
				sx = random(0, 40 - sw);
				sy = random(0, 40 - sh);
				found = FALSE;
			}
			ii = 2;
			for(yy = 0; yy < sh && found == TRUE; yy++) {
				for(xx = 0; xx < sw && found == TRUE; xx++) {
					if(miniset[ii] != 0 && dungeon[xx + sx][yy + sy] != miniset[ii]) {
						found = FALSE;
					}
					if(dflags[xx + sx][yy + sy] != 0) {
						found = FALSE;
					}
					ii++;
				}
			}
			if(!found) {
				sx++;
				if(sx == 40 - sw) {
					sx = 0;
					sy++;
					if(sy == 40 - sh) {
						sy = 0;
					}
				}
			}
		}
		if(trys >= 200) {
			return TRUE;
		}
		ii = sw * sh + 2;
		for(yy = 0; yy < sh; yy++) {
			for(xx = 0; xx < sw; xx++) {
				if(miniset[ii] != 0) {
					dungeon[xx + sx][yy + sy] = miniset[ii];
				}
				ii++;
			}
		}
	}

	if(setview == TRUE) {
		ViewX = 2 * sx + 17;
		ViewY = 2 * sy + 19;
	}
	if(ldir == 0) {
		LvlViewX = 2 * sx + 17;
		LvlViewY = 2 * sy + 19;
	}

	return FALSE;
}
// 5CF320: using guessed type int LvlViewY;
// 5CF324: using guessed type int LvlViewX;

void DRLG_L3PlaceRndSet(const unsigned char *miniset, int rndper)
{
	int sx, sy, sw, sh, xx, yy, ii, kk;
	BOOL found;

	sw = miniset[0];
	sh = miniset[1];

	for(sy = 0; sy < 40 - sh; sy++) {
		for(sx = 0; sx < 40 - sw; sx++) {
			found = TRUE;
			ii = 2;
			for(yy = 0; yy < sh && found == TRUE; yy++) {
				for(xx = 0; xx < sw && found == TRUE; xx++) {
					if(miniset[ii] != 0 && dungeon[xx + sx][yy + sy] != miniset[ii]) {
						found = FALSE;
					}
					if(dflags[xx + sx][yy + sy] != 0) {
						found = FALSE;
					}
					ii++;
				}
			}
			kk = sw * sh + 2;
			if(miniset[kk] >= 84 && miniset[kk] <= 100 && found == TRUE) {
				if(dungeon[sx - 1][sy] >= 84 && dungeon[sx - 1][sy] <= 100) {
					found = FALSE;
				}
				if(dungeon[sx + 1][sy] >= 84 && dungeon[sx - 1][sy] <= 100) {
					found = FALSE;
				}
				if(dungeon[sx][sy + 1] >= 84 && dungeon[sx - 1][sy] <= 100) {
					found = FALSE;
				}
				if(dungeon[sx][sy - 1] >= 84 && dungeon[sx - 1][sy] <= 100) {
					found = FALSE;
				}
			}
			if(found == TRUE && random(0, 100) < rndper) {
				for(yy = 0; yy < sh; yy++) {
					for(xx = 0; xx < sw; xx++) {
						if(miniset[kk] != 0) {
							dungeon[xx + sx][yy + sy] = miniset[kk];
						}
						kk++;
					}
				}
			}
		}
	}
}

void DRLG_L3Wood()
{
	char *v0;      // edi
	int v1;        // edx
	_BYTE *v2;     // eax
	int v3;        // edx
	_BYTE *v4;     // ebx
	int v5;        // esi
	int v6;        // esi
	int v7;        // ebx
	int v8;        // ebx
	signed int v9; // esi
	_BYTE *v10;    // eax
	int v11;       // esi
	int v12;       // ebx
	int v13;       // eax
	_BYTE *v14;    // ecx
	int v15;       // ecx
	int v16;       // eax
	int v17;       // esi
	int v18;       // esi
	//int v19; // eax
	int v20;        // edi
	int v21;        // esi
	int i;          // edx
	int v23;        // esi
	int v24;        // edi
	signed int v25; // ecx
	int v26;        // ebx
	char *v27;      // esi
	int v28;        // ecx
	int v29;        // edi
	int v30;        // ecx
	int v31;        // edi
	int v32;        // ebx
	int v33;        // ebx
	char *v34;      // esi
	signed int v35; // ecx
	int v36;        // [esp+Ch] [ebp-14h]
	int v37;        // [esp+10h] [ebp-10h]
	int v38;        // [esp+10h] [ebp-10h]
	int v39;        // [esp+10h] [ebp-10h]
	int v40;        // [esp+10h] [ebp-10h]
	int v41;        // [esp+10h] [ebp-10h]
	int x;          // [esp+14h] [ebp-Ch]
	int xa;         // [esp+14h] [ebp-Ch]
	signed int v44; // [esp+18h] [ebp-8h]
	signed int v45; // [esp+18h] [ebp-8h]
	int y;          // [esp+1Ch] [ebp-4h]
	signed int ya;  // [esp+1Ch] [ebp-4h]

	y = 0;
	do {
		x = 0;
		v44 = 1;
		v0 = (char *)dungeon + y;
		do {
			if (*v0 == 10 && random(0, 2)) {
				v1 = v44 - 1;
				if (*v0 == 10) {
					v2 = (unsigned char *)v0;
					do {
						v2 += 40;
						++v1;
					} while (*v2 == 10);
				}
				v3 = v1 - 1;
				v37 = v3;
				if (v3 - (v44 - 1) > 0) {
					*v0 = 127;
					if (v44 < v3) {
						v4 = (unsigned char *)v0 + 40;
						v5 = v3 - v44;
						do {
							*v4 = random(0, 2) != 0 ? 126 : -127;
							v4 += 40;
							--v5;
						} while (v5);
					}
					dungeon[v37][y] = -128;
				}
			}
			if (*v0 == 9 && random(0, 2)) {
				v6 = y;
				v7 = y;
				if (*v0 == 9) {
					do
						++v7;
					while (dungeon[x][v7] == 9);
				}
				v8 = v7 - 1;
				if (v8 - y > 0) {
					*v0 = 123;
					while (++v6 < v8) {
						if (random(0, 2))
							dungeon[x][v6] = 121;
						else
							dungeon[x][v6] = 124;
					}
					dungeon[x][v8] = 122;
				}
			}
			if (*v0 == 11 && v0[40] == 10 && v0[1] == 9 && random(0, 2)) {
				v9 = v44;
				*v0 = 125;
				if (v0[40] == 10) {
					v10 = (unsigned char *)v0 + 40;
					do {
						v10 += 40;
						++v9;
					} while (*v10 == 10);
				}
				v11 = v9 - 1;
				if (v44 < v11) {
					v38 = (int)(v0 + 40);
					v12 = v11 - v44;
					do {
						v13 = random(0, 2);
						v14 = (_BYTE *)v38;
						v38 += 40;
						--v12;
						*v14 = v13 != 0 ? 126 : -127;
					} while (v12);
				}
				v15 = v11;
				v16 = y + 1;
				v17 = v16;
				for (dungeon[v15][v16 - 1] = 128; dungeon[x][v17] == 9; ++v17) /* check  *((_BYTE *)&dMonster[111][2 * v15 + 111] + v16 + 3) */
					;
				v18 = v17 - 1;
				v39 = y + 1;
				if (v16 < v18) {
					do {
						if (random(0, 2))
							dungeon[x][v39] = 121;
						else
							dungeon[x][v39] = 124;
						++v39;
					} while (v39 < v18);
				}
				dungeon[x][v18] = 122;
			}
			++v44;
			++x;
			v0 += 40;
		} while (v44 - 1 < 39);
		++y;
	} while (y < 39);
	ya = 0;
	do {
		xa = 0;
		v45 = 0;
		do {
			if (dungeon[v45][ya] != 7)
				goto LABEL_112;
			if (random(0, 1))
				goto LABEL_112;
			//_LOBYTE(v19) = SkipThemeRoom(xa, ya);
			if (!SkipThemeRoom(xa, ya))
				goto LABEL_112;
			v36 = random(0, 2);
			if (!v36) {
				v20 = ya;
				v21 = ya;
				for (i = ya; WoodVertU(xa, i); i = v21)
					--v21;
				v23 = v21 + 1;
				while (WoodVertD(xa, v20))
					++v20;
				v24 = v20 - 1;
				v25 = 1;
				if (dungeon[v45][v23] == 7)
					v25 = 0;
				if (dungeon[v45][v24] == 7)
					v25 = 0;
				if (v24 - v23 <= 1)
					goto LABEL_112;
				if (!v25)
					goto LABEL_112;
				v40 = random(0, v24 - v23 - 1) + v23 + 1;
				v26 = v23;
				if (v23 > v24)
					goto LABEL_112;
				do {
					if (v26 != v40) {
						v27 = (char *)&dungeon[v45][v26];
						if (*v27 == 7)
							*v27 = random(0, 2) != 0 ? -121 : -119;
						if (*v27 == 10)
							*v27 = -125;
						if (*v27 == 126)
							*v27 = -123;
						if (*v27 == -127)
							*v27 = -123;
						if (*v27 == 2)
							*v27 = -117;
						if (*v27 == -122)
							*v27 = -118;
						if (*v27 == -120)
							*v27 = -118;
					}
					++v26;
				} while (v26 <= v24);
			}
			if (v36 == 1) {
				v28 = xa;
				v29 = xa;
				while (WoodHorizL(v28, ya))
					v28 = --v29;
				v30 = xa;
				v31 = v29 + 1;
				v32 = xa;
				while (WoodHorizR(v30, ya))
					v30 = ++v32;
				v33 = v32 - 1;
				v34 = (char *)&dungeon[v31][ya];
				v35 = 1;
				if (*v34 == 7)
					v35 = 0;
				if (dungeon[v33][ya] == 7)
					v35 = 0;
				if (v33 - v31 > 1 && v35) {
					v41 = random(0, v33 - v31 - 1) + v31 + 1;
					while (1) {
						if (v31 > v33)
							break;
						if (v31 != v41) {
							if (*v34 == 7) {
								if (random(0, 2)) {
									*v34 = -122;
									goto LABEL_110;
								}
								*v34 = -120;
							}
							if (*v34 == 9)
								*v34 = -126;
							if (*v34 == 121)
								*v34 = -124;
							if (*v34 == 124)
								*v34 = -124;
							if (*v34 == 4)
								*v34 = -116;
							if (*v34 == -121)
								*v34 = -118;
							if (*v34 == -119)
								*v34 = -118;
						}
					LABEL_110:
						++v31;
						v34 += 40;
					}
				}
			}
		LABEL_112:
			++v45;
			++xa;
		} while (v45 < 40);
		++ya;
	} while (ya < 40);
	AddFenceDoors();
	FenceDoorFix();
}

BOOL WoodVertU(int i, int y)
{
	if((dungeon[i + 1][y] > 152 || dungeon[i + 1][y] < 130)
	&& (dungeon[i - 1][y] > 152 || dungeon[i - 1][y] < 130)) {
		if(dungeon[i][y] == 7) {
			return TRUE;
		}
		if(dungeon[i][y] == 10) {
			return TRUE;
		}
		if(dungeon[i][y] == 126) {
			return TRUE;
		}
		if(dungeon[i][y] == 129) {
			return TRUE;
		}
		if(dungeon[i][y] == 134) {
			return TRUE;
		}
		if(dungeon[i][y] == 136) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL WoodVertD(int i, int y)
{
	if((dungeon[i + 1][y] > 152 || dungeon[i + 1][y] < 130)
	&& (dungeon[i - 1][y] > 152 || dungeon[i - 1][y] < 130)) {
		if(dungeon[i][y] == 7) {
			return TRUE;
		}
		if(dungeon[i][y] == 2) {
			return TRUE;
		}
		if(dungeon[i][y] == 134) {
			return TRUE;
		}
		if(dungeon[i][y] == 136) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL WoodHorizL(int x, int j)
{
	if((dungeon[x][j + 1] > 152 || dungeon[x][j + 1] < 130)
	&& (dungeon[x][j - 1] > 152 || dungeon[x][j - 1] < 130)) {
		if(dungeon[x][j] == 7) {
			return TRUE;
		}
		if(dungeon[x][j] == 9) {
			return TRUE;
		}
		if(dungeon[x][j] == 121) {
			return TRUE;
		}
		if(dungeon[x][j] == 124) {
			return TRUE;
		}
		if(dungeon[x][j] == 135) {
			return TRUE;
		}
		if(dungeon[x][j] == 137) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL WoodHorizR(int x, int j)
{
	if((dungeon[x][j + 1] > 152 || dungeon[x][j + 1] < 130)
	&& (dungeon[x][j - 1] > 152 || dungeon[x][j - 1] < 130)) {
		if(dungeon[x][j] == 7) {
			return TRUE;
		}
		if(dungeon[x][j] == 4) {
			return TRUE;
		}
		if(dungeon[x][j] == 135) {
			return TRUE;
		}
		if(dungeon[x][j] == 137) {
			return TRUE;
		}
	}

	return FALSE;
}

void DRLG_L3Pass3()
{
	int i, j, xx, yy;
	long v1, v2, v3, v4, lv;

	lv = 8 - 1;

#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
	__asm {
		mov		esi, pMegaTiles
		mov		eax, lv
		shl		eax, 3
		add		esi, eax
		xor		eax, eax
		lodsw
		inc		eax
		mov		v1, eax
		lodsw
		inc		eax
		mov		v2, eax
		lodsw
		inc		eax
		mov		v3, eax
		lodsw
		inc		eax
		mov		v4, eax
	}
#else
	v1 = *((WORD *)&pMegaTiles[lv * 8]) + 1;
	v2 = *((WORD *)&pMegaTiles[lv * 8] + 1) + 1;
	v3 = *((WORD *)&pMegaTiles[lv * 8] + 2) + 1;
	v4 = *((WORD *)&pMegaTiles[lv * 8] + 3) + 1;
#endif

	for (j = 0; j < MAXDUNY; j += 2)
	{
		for (i = 0; i < MAXDUNX; i += 2) {
			dPiece[i][j] = v1;
			dPiece[i + 1][j] = v2;
			dPiece[i][j + 1] = v3;
			dPiece[i + 1][j + 1] = v4;
		}
	}

	yy = 16;
	for (j = 0; j < DMAXY; j++) {
		xx = 16;
		for (i = 0; i < DMAXX; i++) {
			lv = (unsigned char)dungeon[i][j] - 1;
#if (_MSC_VER >= 800) && (_MSC_VER <= 1200)
			if (lv >= 0) {
				__asm {
					mov		esi, pMegaTiles
					mov		eax, lv
					shl		eax, 3
					add		esi, eax
					xor		eax, eax
					lodsw
					inc		eax
					mov		v1, eax
					lodsw
					inc		eax
					mov		v2, eax
					lodsw
					inc		eax
					mov		v3, eax
					lodsw
					inc		eax
					mov		v4, eax
				}
			} else {
				v1 = 0;
				v2 = 0;
				v3 = 0;
				v4 = 0;
			}
#else
			if (lv >= 0) {
				v1 = *((WORD *)&pMegaTiles[lv * 8]) + 1;
				v2 = *((WORD *)&pMegaTiles[lv * 8] + 1) + 1;
				v3 = *((WORD *)&pMegaTiles[lv * 8] + 2) + 1;
				v4 = *((WORD *)&pMegaTiles[lv * 8] + 3) + 1;
			} else {
				v1 = 0;
				v2 = 0;
				v3 = 0;
				v4 = 0;
			}
#endif
			dPiece[xx][yy] = v1;
			dPiece[xx + 1][yy] = v2;
			dPiece[xx][yy + 1] = v3;
			dPiece[xx + 1][yy + 1] = v4;
			xx += 2;
		}
		yy += 2;
	}
}

void LoadL3Dungeon(char *sFileName, int vx, int vy)
{
	int i, j, rw, rh;
	BYTE *pLevelMap, *lm;

	InitL3Dungeon();
	dminx = 16;
	dminy = 16;
	dmaxx = 96;
	dmaxy = 96;
	DRLG_InitTrans();
	pLevelMap = LoadFileInMem(sFileName, 0);

	lm = pLevelMap;
	rw = *lm;
	lm += 2;
	rh = *lm;
	lm += 2;

	for(j = 0; j < rh; j++) {
		for(i = 0; i < rw; i++) {
			if(*lm != 0) {
				dungeon[i][j] = *lm;
			} else {
				dungeon[i][j] = 7;
			}
			lm += 2;
		}
	}
	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 0) {
				dungeon[i][j] = 8;
			}
		}
	}

	abyssx = 112;
	DRLG_L3Pass3();
	DRLG_Init_Globals();
	ViewX = 31;
	ViewY = 83;
	SetMapMonsters(pLevelMap, 0, 0);
	SetMapObjects(pLevelMap, 0, 0);

	for(j = 0; j < 112; j++) {
		for(i = 0; i < 112; i++) {
			if(dPiece[i][j] >= 56 && dPiece[i][j] <= 147) {
				DoLighting(i, j, 7, -1);
			} else if(dPiece[i][j] >= 154 && dPiece[i][j] <= 161) {
				DoLighting(i, j, 7, -1);
			} else if(dPiece[i][j] == 150) {
				DoLighting(i, j, 7, -1);
			} else if(dPiece[i][j] == 152) {
				DoLighting(i, j, 7, -1);
			}
		}
	}

	mem_free_dbg(pLevelMap);
}
// 52837C: using guessed type int abyssx;
// 5CF328: using guessed type int dmaxx;
// 5CF32C: using guessed type int dmaxy;
// 5D2458: using guessed type int dminx;
// 5D245C: using guessed type int dminy;

void LoadPreL3Dungeon(char *sFileName, int vx, int vy)
{
	int i, j, rw, rh;
	BYTE *pLevelMap, *lm;

	InitL3Dungeon();
	DRLG_InitTrans();
	pLevelMap = LoadFileInMem(sFileName, 0);

	lm = pLevelMap;
	rw = *lm;
	lm += 2;
	rh = *lm;
	lm += 2;

	for(j = 0; j < rh; j++) {
		for(i = 0; i < rw; i++) {
			if(*lm != 0) {
				dungeon[i][j] = *lm;
			} else {
				dungeon[i][j] = 7;
			}
			lm += 2;
		}
	}
	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 0) {
				dungeon[i][j] = 8;
			}
		}
	}

	memcpy(pdungeon, dungeon, sizeof(pdungeon));
	mem_free_dbg(pLevelMap);
}
