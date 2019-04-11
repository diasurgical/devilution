//HEADER_GOES_HERE

#include "../types.h"

int nSx1;
int nSx2; // weak
int nSy1;
int nSy2; // weak
int nRoomCnt;
unsigned char predungeon[40][40];
ROOMNODE RoomList[81];
HALLNODE *pHallList;

int Area_Min = 2;  // weak
int Room_Max = 10; // weak
int Room_Min = 4;  // weak
int Dir_Xadd[5] = { 0, 0, 1, 0, -1 };
int Dir_Yadd[5] = { 0, -1, 0, 1, 0 };
ShadowStruct SPATSL2[2] = { { 6u, 3u, 0u, 3u, 48u, 0u, 50u }, { 9u, 3u, 0u, 3u, 48u, 0u, 50u } };
//short word_48489A = 0; // weak
unsigned char BTYPESL2[161] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 17, 18, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char BSTYPESL2[161] = { 0, 1, 2, 3, 0, 0, 6, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 6, 6, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 0, 0, 1, 1, 1, 1, 6, 2, 2, 2, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 2, 2, 3, 3, 3, 3, 1, 1, 2, 2, 3, 3, 3, 3, 1, 1, 3, 3, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char VARCH1[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 7, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH2[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 8, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH3[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 6, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH4[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 9, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH5[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 14, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH6[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 13, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH7[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 16, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH8[] = { 2, 4, 3, 0, 3, 1, 3, 4, 0, 15, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH9[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 7, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH10[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 8, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH11[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 6, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH12[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 9, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH13[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 14, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH14[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 13, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH15[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 16, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH16[] = { 2, 4, 3, 0, 3, 8, 3, 4, 0, 15, 48, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH17[] = { 2, 3, 2, 7, 3, 4, 0, 7, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH18[] = { 2, 3, 2, 7, 3, 4, 0, 8, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH19[] = { 2, 3, 2, 7, 3, 4, 0, 6, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH20[] = { 2, 3, 2, 7, 3, 4, 0, 9, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH21[] = { 2, 3, 2, 7, 3, 4, 0, 14, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH22[] = { 2, 3, 2, 7, 3, 4, 0, 13, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH23[] = { 2, 3, 2, 7, 3, 4, 0, 16, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH24[] = { 2, 3, 2, 7, 3, 4, 0, 15, 141, 39, 47, 44, 0, 0 };
unsigned char VARCH25[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 7, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH26[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 8, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH27[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 6, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH28[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 9, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH29[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 14, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH30[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 13, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH31[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 16, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH32[] = { 2, 4, 3, 0, 3, 4, 3, 1, 0, 15, 48, 0, 51, 39, 47, 44, 0, 0 };
unsigned char VARCH33[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 7, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH34[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 8, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH35[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 6, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH36[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 9, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH37[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 14, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH38[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 13, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH39[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 16, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char VARCH40[] = { 2, 4, 2, 0, 3, 8, 3, 4, 0, 15, 142, 0, 51, 42, 47, 44, 0, 0 };
unsigned char HARCH1[] = { 3, 2, 3, 3, 0, 2, 5, 9, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH2[] = { 3, 2, 3, 3, 0, 2, 5, 6, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH3[] = { 3, 2, 3, 3, 0, 2, 5, 8, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH4[] = { 3, 2, 3, 3, 0, 2, 5, 7, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH5[] = { 3, 2, 3, 3, 0, 2, 5, 15, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH6[] = { 3, 2, 3, 3, 0, 2, 5, 16, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH7[] = { 3, 2, 3, 3, 0, 2, 5, 13, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH8[] = { 3, 2, 3, 3, 0, 2, 5, 14, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH9[] = { 3, 2, 3, 3, 0, 8, 5, 9, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH10[] = { 3, 2, 3, 3, 0, 8, 5, 6, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH11[] = { 3, 2, 3, 3, 0, 8, 5, 8, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH12[] = { 3, 2, 3, 3, 0, 8, 5, 7, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH13[] = { 3, 2, 3, 3, 0, 8, 5, 15, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH14[] = { 3, 2, 3, 3, 0, 8, 5, 16, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH15[] = { 3, 2, 3, 3, 0, 8, 5, 13, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH16[] = { 3, 2, 3, 3, 0, 8, 5, 14, 49, 46, 0, 43, 45, 0 };
unsigned char HARCH17[] = { 3, 2, 1, 3, 0, 8, 5, 9, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH18[] = { 3, 2, 1, 3, 0, 8, 5, 6, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH19[] = { 3, 2, 1, 3, 0, 8, 5, 8, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH20[] = { 3, 2, 1, 3, 0, 8, 5, 7, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH21[] = { 3, 2, 1, 3, 0, 8, 5, 15, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH22[] = { 3, 2, 1, 3, 0, 8, 5, 16, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH23[] = { 3, 2, 1, 3, 0, 8, 5, 13, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH24[] = { 3, 2, 1, 3, 0, 8, 5, 14, 140, 46, 0, 43, 45, 0 };
unsigned char HARCH25[] = { 3, 2, 3, 3, 0, 5, 2, 9, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH26[] = { 3, 2, 3, 3, 0, 5, 2, 6, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH27[] = { 3, 2, 3, 3, 0, 5, 2, 8, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH28[] = { 3, 2, 3, 3, 0, 5, 2, 7, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH29[] = { 3, 2, 3, 3, 0, 5, 2, 15, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH30[] = { 3, 2, 3, 3, 0, 5, 2, 16, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH31[] = { 3, 2, 3, 3, 0, 5, 2, 13, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH32[] = { 3, 2, 3, 3, 0, 5, 2, 14, 49, 46, 0, 40, 45, 0 };
unsigned char HARCH33[] = { 3, 2, 1, 3, 0, 9, 5, 9, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH34[] = { 3, 2, 1, 3, 0, 9, 5, 6, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH35[] = { 3, 2, 1, 3, 0, 9, 5, 8, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH36[] = { 3, 2, 1, 3, 0, 9, 5, 7, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH37[] = { 3, 2, 1, 3, 0, 9, 5, 15, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH38[] = { 3, 2, 1, 3, 0, 9, 5, 16, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH39[] = { 3, 2, 1, 3, 0, 9, 5, 13, 140, 46, 0, 40, 45, 0 };
unsigned char HARCH40[] = { 3, 2, 1, 3, 0, 9, 5, 14, 140, 46, 0, 40, 45, 0 };
unsigned char USTAIRS[] = { 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 72, 77, 0, 0, 76, 0, 0, 0, 0, 0, 0 };
unsigned char DSTAIRS[] = { 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 48, 71, 0, 0, 50, 78, 0, 0, 0, 0, 0 };
unsigned char WARPSTAIRS[] = { 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 158, 160, 0, 0, 159, 0, 0, 0, 0, 0, 0 };
unsigned char CRUSHCOL[] = { 3, 3, 3, 1, 3, 2, 6, 3, 3, 3, 3, 0, 0, 0, 0, 83, 0, 0, 0, 0 };
unsigned char BIG1[] = { 2, 2, 3, 3, 3, 3, 113, 0, 112, 0 };
unsigned char BIG2[] = { 2, 2, 3, 3, 3, 3, 114, 115, 0, 0 };
unsigned char BIG3[] = { 1, 2, 1, 1, 117, 116 };
unsigned char BIG4[] = { 2, 1, 2, 2, 118, 119 };
unsigned char BIG5[] = { 2, 2, 3, 3, 3, 3, 120, 122, 121, 123 };
unsigned char BIG6[] = { 1, 2, 1, 1, 125, 124 };
unsigned char BIG7[] = { 2, 1, 2, 2, 126, 127 };
unsigned char BIG8[] = { 2, 2, 3, 3, 3, 3, 128, 130, 129, 131 };
unsigned char BIG9[] = { 2, 2, 1, 3, 1, 3, 133, 135, 132, 134 };
unsigned char BIG10[] = { 2, 2, 2, 2, 3, 3, 136, 137, 3, 3 };
unsigned char RUINS1[] = { 1, 1, 1, 80 };
unsigned char RUINS2[] = { 1, 1, 1, 81 };
unsigned char RUINS3[] = { 1, 1, 1, 82 };
unsigned char RUINS4[] = { 1, 1, 2, 84 };
unsigned char RUINS5[] = { 1, 1, 2, 85 };
unsigned char RUINS6[] = { 1, 1, 2, 86 };
unsigned char RUINS7[] = { 1, 1, 8, 87 };
unsigned char PANCREAS1[] = { 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 108, 0, 0, 0, 0, 0, 0, 0 };
unsigned char PANCREAS2[] = { 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 0 };
unsigned char CTRDOOR1[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 9, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR2[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 8, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR3[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 6, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR4[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 7, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR5[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 15, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR6[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 13, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR7[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 16, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
unsigned char CTRDOOR8[] = { 3, 3, 3, 1, 3, 0, 4, 0, 0, 14, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0 };
int Patterns[100][10] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
	{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 3 },
	{ 0, 7, 0, 0, 1, 0, 0, 5, 0, 2 },
	{ 0, 5, 0, 0, 1, 0, 0, 7, 0, 2 },
	{ 0, 0, 0, 7, 1, 5, 0, 0, 0, 1 },
	{ 0, 0, 0, 5, 1, 7, 0, 0, 0, 1 },
	{ 0, 1, 0, 0, 3, 0, 0, 1, 0, 4 },
	{ 0, 0, 0, 1, 3, 1, 0, 0, 0, 5 },
	{ 0, 6, 0, 6, 1, 0, 0, 0, 0, 6 },
	{ 0, 6, 0, 0, 1, 6, 0, 0, 0, 9 },
	{ 0, 0, 0, 6, 1, 0, 0, 6, 0, 7 },
	{ 0, 0, 0, 0, 1, 6, 0, 6, 0, 8 },
	{ 0, 6, 0, 6, 6, 0, 8, 6, 0, 7 },
	{ 0, 6, 8, 6, 6, 6, 0, 0, 0, 9 },
	{ 0, 6, 0, 0, 6, 6, 0, 6, 8, 8 },
	{ 6, 6, 6, 6, 6, 6, 0, 6, 0, 8 },
	{ 2, 6, 6, 6, 6, 6, 0, 6, 0, 8 },
	{ 7, 7, 7, 6, 6, 6, 0, 6, 0, 8 },
	{ 6, 6, 2, 6, 6, 6, 0, 6, 0, 8 },
	{ 6, 2, 6, 6, 6, 6, 0, 6, 0, 8 },
	{ 2, 6, 6, 6, 6, 6, 0, 6, 0, 8 },
	{ 6, 7, 7, 6, 6, 6, 0, 6, 0, 8 },
	{ 4, 4, 6, 6, 6, 6, 2, 6, 2, 8 },
	{ 2, 2, 2, 2, 6, 2, 2, 6, 2, 7 },
	{ 2, 2, 2, 2, 6, 2, 6, 6, 6, 7 },
	{ 2, 2, 6, 2, 6, 6, 2, 2, 6, 9 },
	{ 2, 6, 2, 2, 6, 2, 2, 2, 2, 6 },
	{ 2, 2, 2, 2, 6, 6, 2, 2, 2, 9 },
	{ 2, 2, 2, 6, 6, 2, 2, 2, 2, 6 },
	{ 2, 2, 0, 2, 6, 6, 2, 2, 0, 9 },
	{ 0, 0, 0, 0, 4, 0, 0, 0, 0, 12 },
	{ 0, 1, 0, 0, 1, 4, 0, 1, 0, 10 },
	{ 0, 0, 0, 1, 1, 1, 0, 4, 0, 11 },
	{ 0, 0, 0, 6, 1, 4, 0, 1, 0, 14 },
	{ 0, 6, 0, 1, 1, 0, 0, 4, 0, 16 },
	{ 0, 6, 0, 0, 1, 1, 0, 4, 0, 15 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 4, 13 },
	{ 8, 8, 8, 8, 1, 1, 0, 1, 1, 13 },
	{ 8, 8, 4, 8, 1, 1, 0, 1, 1, 10 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 11 },
	{ 1, 1, 1, 1, 1, 1, 2, 2, 8, 2 },
	{ 0, 1, 0, 1, 1, 4, 1, 1, 0, 16 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 4, 11 },
	{ 1, 1, 4, 1, 1, 1, 0, 2, 2, 2 },
	{ 1, 1, 1, 1, 1, 1, 6, 2, 6, 2 },
	{ 4, 1, 1, 1, 1, 1, 6, 2, 6, 2 },
	{ 2, 2, 2, 1, 1, 1, 4, 1, 1, 11 },
	{ 4, 1, 1, 1, 1, 1, 2, 2, 2, 2 },
	{ 1, 1, 4, 1, 1, 1, 2, 2, 1, 2 },
	{ 4, 1, 1, 1, 1, 1, 1, 2, 2, 2 },
	{ 2, 2, 6, 1, 1, 1, 4, 1, 1, 11 },
	{ 4, 1, 1, 1, 1, 1, 2, 2, 6, 2 },
	{ 1, 2, 2, 1, 1, 1, 4, 1, 1, 11 },
	{ 0, 1, 1, 0, 1, 1, 0, 1, 1, 10 },
	{ 2, 1, 1, 3, 1, 1, 2, 1, 1, 14 },
	{ 1, 1, 0, 1, 1, 2, 1, 1, 0, 1 },
	{ 0, 4, 0, 1, 1, 1, 0, 1, 1, 14 },
	{ 4, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
	{ 0, 1, 0, 4, 1, 1, 0, 1, 1, 15 },
	{ 1, 1, 1, 1, 1, 1, 0, 2, 2, 2 },
	{ 0, 1, 1, 2, 1, 1, 2, 1, 4, 10 },
	{ 2, 1, 1, 1, 1, 1, 0, 4, 0, 16 },
	{ 1, 1, 4, 1, 1, 2, 0, 1, 2, 1 },
	{ 2, 1, 1, 2, 1, 1, 1, 1, 4, 10 },
	{ 1, 1, 2, 1, 1, 2, 4, 1, 8, 1 },
	{ 2, 1, 4, 1, 1, 1, 4, 4, 1, 16 },
	{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 16 },
	{ 1, 1, 2, 1, 1, 1, 1, 1, 1, 15 },
	{ 1, 1, 1, 1, 1, 1, 2, 1, 1, 14 },
	{ 4, 1, 1, 1, 1, 1, 2, 1, 1, 14 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 2, 8 },
	{ 0, 0, 0, 0, 255, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void InitDungeon()
{
	signed int v0; // edx
	signed int v1; // eax
	signed int v2; // ecx

	v0 = 0;
	do {
		v1 = v0;
		v2 = 40;
		do {
			dflags[0][v1] = 0;
			predungeon[0][v1] = 32;
			v1 += 40;
			--v2;
		} while (v2);
		++v0;
	} while (v0 < 40);
}

void L2LockoutFix()
{
	signed int v0;   // ecx
	char *v1;        // eax
	signed int v2;   // edx
	signed int v3;   // ecx
	signed int v4;   // edi
	signed int v5;   // eax
	char *v6;        // esi
	signed int v7;   // edx
	char v8;         // al
	unsigned int v9; // ecx
	signed int v10;  // eax
	char v11;        // dl
	signed int v12;  // esi
	char v13;        // bl
	char *v14;       // edx

	v0 = 0;
	do {
		v1 = (char *)dungeon + v0;
		v2 = 40;
		do {
			if (*v1 == 4 && *(v1 - 40) != 3)
				*v1 = 1;
			if (*v1 == 5 && *(v1 - 1) != 3)
				*v1 = 2;
			v1 += 40;
			--v2;
		} while (v2);
		++v0;
	} while (v0 < 40);
	v3 = 1;
	do {
		v4 = 1;
		do {
			v5 = v4;
			if (dflags[v4][v3] >= 0) {
				v6 = (char *)&dungeon[v5][v3];
				if ((*v6 == 2 || *v6 == 5) && *(v6 - 1) == 3 && dungeon[v5][v3 + 1] == 3) {
					v7 = 0;
					while (1) {
						v8 = *v6;
						if (*v6 != 2 && v8 != 5)
							break;
						if (*(v6 - 1) != 3 || v6[1] != 3)
							break;
						if (v8 == 5)
							v7 = 1;
						++v4;
						v6 += 40;
					}
					if (!v7 && dflags[v4 - 1][v3] >= 0) // dflags[-1][]
						dungeon[v4 - 1][v3] = 5;        // dungeon[-1][]
				}
			}
			++v4;
		} while (v4 < 39);
		++v3;
	} while (v3 < 39);
	v9 = 1;
	do {
		v10 = 1;
		do {
			if (dflags[v9][v10] >= 0) {
				v11 = dungeon[v9][v10];
				if ((v11 == 1 || v11 == 4)
				    && dungeon[v9 - 1][v10] == 3 // dungeon[-1][]
				    && dungeon[v9 + 1][v10] == 3) {
					v12 = 0;
					while (1) {
						v13 = dungeon[v9][v10];
						if (v13 != 1 && v13 != 4)
							break;
						v14 = (char *)&dungeon[v9 + 1][v10];
						if (*(v14 - 80) != 3 || *v14 != 3)
							break;
						if (v13 == 4)
							v12 = 1;
						++v10;
					}
					if (!v12 && dflags[v9][v10 - 1] >= 0) // dflags[][-1]
						dungeon[v9][v10 - 1] = 4;         // dungeon[][-1]
				}
			}
			++v10;
		} while (v10 < 39);
		++v9;
	} while (v9 < 39);
}

void L2DoorFix()
{
	int i, j;

	for(j = 1; j < 40; j++) {
		for(i = 1; i < 40; i++) {
			if(dungeon[i][j] == 4 && dungeon[i][j - 1] == 3) {
				dungeon[i][j] = 7;
			}
			if(dungeon[i][j] == 5 && dungeon[i - 1][j] == 3) {
				dungeon[i][j] = 9;
			}
		}
	}
}

void LoadL2Dungeon(char *sFileName, int vx, int vy)
{
	int i, j, rw, rh, pc;
	BYTE *pLevelMap, *lm;

	InitDungeon();
	DRLG_InitTrans();
	pLevelMap = LoadFileInMem(sFileName, 0);

	for (j = 0; j < DMAXY; j++) {
		for (i = 0; i < DMAXX; i++) {
			dungeon[i][j] = 12;
			dflags[i][j] = 0;
		}
	}

	lm = pLevelMap;
	rw = *lm;
	lm += 2;
	rh = *lm;
	lm += 2;

	for (j = 0; j < rh; j++) {
		for (i = 0; i < rw; i++) {
			if (*lm != 0) {
				dungeon[i][j] = *lm;
				dflags[i][j] |= DFLAG_EXPLORED;
			} else {
				dungeon[i][j] = 3;
			}
			lm += 2;
		}
	}
	for (j = 0; j < DMAXY; j++) {
		for (i = 0; i < DMAXX; i++) {
			if (dungeon[i][j] == 0) {
				dungeon[i][j] = 12;
			}
		}
	}

	DRLG_L2Pass3();
	DRLG_Init_Globals();

	for (j = 0; j < MAXDUNY; j++) {
		for (i = 0; i < MAXDUNX; i++) {
			pc = 0;
			if (dPiece[i][j] == 541) {
				pc = 5;
			}
			if (dPiece[i][j] == 178) {
				pc = 5;
			}
			if (dPiece[i][j] == 551) {
				pc = 5;
			}
			if (dPiece[i][j] == 542) {
				pc = 6;
			}
			if (dPiece[i][j] == 553) {
				pc = 6;
			}
			if (dPiece[i][j] == 13) {
				pc = 5;
			}
			if (dPiece[i][j] == 17) {
				pc = 6;
			}
			dArch[i][j] = pc;
		}
	}
	for (j = 0; j < MAXDUNY; j++) {
		for (i = 0; i < MAXDUNX; i++) {
			if (dPiece[i][j] == 132) {
				dArch[i][j + 1] = 2;
				dArch[i][j + 2] = 1;
			} else if (dPiece[i][j] == 135 || dPiece[i][j] == 139) {
				dArch[i + 1][j] = 3;
				dArch[i + 2][j] = 4;
			}
		}
	}

	ViewX = vx;
	ViewY = vy;
	SetMapMonsters(pLevelMap, 0, 0);
	SetMapObjects(pLevelMap, 0, 0);
	mem_free_dbg(pLevelMap);
}

void DRLG_L2Pass3()
{
	int i, j, xx, yy;
	long v1, v2, v3, v4, lv;

	lv = 12 - 1;

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
			dPiece[xx][yy] = v1;
			dPiece[xx + 1][yy] = v2;
			dPiece[xx][yy + 1] = v3;
			dPiece[xx + 1][yy + 1] = v4;
			xx += 2;
		}
		yy += 2;
	}
}

void LoadPreL2Dungeon(char *sFileName, int vx, int vy)
{
	int i, j, rw, rh;
	BYTE *pLevelMap, *lm;

	InitDungeon();
	DRLG_InitTrans();
	pLevelMap = LoadFileInMem(sFileName, 0);

	for (j = 0; j < DMAXY; j++) {
		for (i = 0; i < DMAXX; i++) {
			dungeon[i][j] = 12;
			dflags[i][j] = 0;
		}
	}

	lm = pLevelMap;
	rw = *lm;
	lm += 2;
	rh = *lm;
	lm += 2;

	for (j = 0; j < rh; j++) {
		for (i = 0; i < rw; i++) {
			if (*lm != 0) {
				dungeon[i][j] = *lm;
				dflags[i][j] |= DFLAG_EXPLORED;
			} else {
				dungeon[i][j] = 3;
			}
			lm += 2;
		}
	}
	for (j = 0; j < DMAXY; j++) {
		for (i = 0; i < DMAXX; i++) {
			if (dungeon[i][j] == 0) {
				dungeon[i][j] = 12;
			}
		}
	}
	for (j = 0; j < DMAXY; j++) {
		for (i = 0; i < DMAXX; i++) {
			pdungeon[i][j] = dungeon[i][j];
		}
	}

	mem_free_dbg(pLevelMap);
}

void CreateL2Dungeon(unsigned int rseed, int entry)
{
	if(gbMaxPlayers == 1) {
		if(currlevel == 7 && !quests[8]._qactive) {
			currlevel = 6;
			CreateL2Dungeon(glSeedTbl[6], 4);
			currlevel = 7;
		}
		if(currlevel == 8) {
			if(!quests[8]._qactive) {
				currlevel = 6;
				CreateL2Dungeon(glSeedTbl[6], 4);
				currlevel = 8;
			} else {
				currlevel = 7;
				CreateL2Dungeon(glSeedTbl[7], 4);
				currlevel = 8;

			}
		}
	}

	SetRndSeed(rseed);

	dminx = 16;
	dminy = 16;
	dmaxx = 96;
	dmaxy = 96;

	DRLG_InitTrans();
	DRLG_InitSetPC();
	DRLG_LoadL2SP();
	DRLG_L2(entry);
	DRLG_L2Pass3();
	DRLG_FreeL2SP();
	DRLG_InitL2Vals();
	DRLG_SetPC();
}
// 5CF328: using guessed type int dmaxx;
// 5CF32C: using guessed type int dmaxy;
// 5D2458: using guessed type int dminx;
// 5D245C: using guessed type int dminy;
// 679660: using guessed type char gbMaxPlayers;

void DRLG_LoadL2SP()
{
	char *v1; // ecx

	setloadflag_2 = 0;
	if (QuestStatus(QTYPE_BLIND)) {
		v1 = "Levels\\L2Data\\Blind2.DUN";
	} else {
		if (QuestStatus(QTYPE_BLOOD)) {
			v1 = "Levels\\L2Data\\Blood1.DUN";
		} else {
			if (!QuestStatus(QTYPE_BONE))
				return;
			v1 = "Levels\\L2Data\\Bonestr2.DUN";
		}
	}
	pSetPiece_2 = (char *)LoadFileInMem(v1, 0);
	setloadflag_2 = 1;
}
// 5B50D8: using guessed type int setloadflag_2;

void DRLG_FreeL2SP()
{
	char *ptr;

	ptr = pSetPiece_2;
	pSetPiece_2 = NULL;
	mem_free_dbg(ptr);
}

void DRLG_L2(int entry)
{
	int i, j;
	BOOL doneflag;

	doneflag = FALSE;
	while(!doneflag) {
		nRoomCnt = 0;
		InitDungeon();
		DRLG_InitTrans();
		if(!CreateDungeon()) {
			continue;
		}
		L2TileFix();
		if(setloadflag_2) {
			DRLG_L2SetRoom(nSx1, nSy1);
		}
		DRLG_L2FloodTVal();
		DRLG_L2TransFix();
		if(entry == 0) {
			doneflag = DRLG_L2PlaceMiniSet(USTAIRS, 1, 1, -1, -1, 1, 0);
			if(doneflag) {
				doneflag = DRLG_L2PlaceMiniSet(DSTAIRS, 1, 1, -1, -1, 0, 1);
				if(doneflag && currlevel == 5) {
					doneflag = DRLG_L2PlaceMiniSet(WARPSTAIRS, 1, 1, -1, -1, 0, 6);
				}
			}
			ViewY -= 2;
		} else if(entry == 1) {
			doneflag = DRLG_L2PlaceMiniSet(USTAIRS, 1, 1, -1, -1, 0, 0);
			if(doneflag) {
				doneflag = DRLG_L2PlaceMiniSet(DSTAIRS, 1, 1, -1, -1, 1, 1);
				if(doneflag && currlevel == 5) {
					doneflag = DRLG_L2PlaceMiniSet(WARPSTAIRS, 1, 1, -1, -1, 0, 6);
				}
			}
			ViewX--;
		} else {
			doneflag = DRLG_L2PlaceMiniSet(USTAIRS, 1, 1, -1, -1, 0, 0);
			if(doneflag) {
				doneflag = DRLG_L2PlaceMiniSet(DSTAIRS, 1, 1, -1, -1, 0, 1);
				if(doneflag && currlevel == 5) {
					doneflag = DRLG_L2PlaceMiniSet(WARPSTAIRS, 1, 1, -1, -1, 1, 6);
				}
			}
			ViewY -= 2;
		}
	}

	L2LockoutFix();
	L2DoorFix();
	L2DirtFix();

	DRLG_PlaceThemeRooms(6, 10, 3, 0, 0);
	DRLG_L2PlaceRndSet(CTRDOOR1, 100);
	DRLG_L2PlaceRndSet(CTRDOOR2, 100);
	DRLG_L2PlaceRndSet(CTRDOOR3, 100);
	DRLG_L2PlaceRndSet(CTRDOOR4, 100);
	DRLG_L2PlaceRndSet(CTRDOOR5, 100);
	DRLG_L2PlaceRndSet(CTRDOOR6, 100);
	DRLG_L2PlaceRndSet(CTRDOOR7, 100);
	DRLG_L2PlaceRndSet(CTRDOOR8, 100);
	DRLG_L2PlaceRndSet(VARCH33, 100);
	DRLG_L2PlaceRndSet(VARCH34, 100);
	DRLG_L2PlaceRndSet(VARCH35, 100);
	DRLG_L2PlaceRndSet(VARCH36, 100);
	DRLG_L2PlaceRndSet(VARCH37, 100);
	DRLG_L2PlaceRndSet(VARCH38, 100);
	DRLG_L2PlaceRndSet(VARCH39, 100);
	DRLG_L2PlaceRndSet(VARCH40, 100);
	DRLG_L2PlaceRndSet(VARCH1, 100);
	DRLG_L2PlaceRndSet(VARCH2, 100);
	DRLG_L2PlaceRndSet(VARCH3, 100);
	DRLG_L2PlaceRndSet(VARCH4, 100);
	DRLG_L2PlaceRndSet(VARCH5, 100);
	DRLG_L2PlaceRndSet(VARCH6, 100);
	DRLG_L2PlaceRndSet(VARCH7, 100);
	DRLG_L2PlaceRndSet(VARCH8, 100);
	DRLG_L2PlaceRndSet(VARCH9, 100);
	DRLG_L2PlaceRndSet(VARCH10, 100);
	DRLG_L2PlaceRndSet(VARCH11, 100);
	DRLG_L2PlaceRndSet(VARCH12, 100);
	DRLG_L2PlaceRndSet(VARCH13, 100);
	DRLG_L2PlaceRndSet(VARCH14, 100);
	DRLG_L2PlaceRndSet(VARCH15, 100);
	DRLG_L2PlaceRndSet(VARCH16, 100);
	DRLG_L2PlaceRndSet(VARCH17, 100);
	DRLG_L2PlaceRndSet(VARCH18, 100);
	DRLG_L2PlaceRndSet(VARCH19, 100);
	DRLG_L2PlaceRndSet(VARCH20, 100);
	DRLG_L2PlaceRndSet(VARCH21, 100);
	DRLG_L2PlaceRndSet(VARCH22, 100);
	DRLG_L2PlaceRndSet(VARCH23, 100);
	DRLG_L2PlaceRndSet(VARCH24, 100);
	DRLG_L2PlaceRndSet(VARCH25, 100);
	DRLG_L2PlaceRndSet(VARCH26, 100);
	DRLG_L2PlaceRndSet(VARCH27, 100);
	DRLG_L2PlaceRndSet(VARCH28, 100);
	DRLG_L2PlaceRndSet(VARCH29, 100);
	DRLG_L2PlaceRndSet(VARCH30, 100);
	DRLG_L2PlaceRndSet(VARCH31, 100);
	DRLG_L2PlaceRndSet(VARCH32, 100);
	DRLG_L2PlaceRndSet(HARCH1, 100);
	DRLG_L2PlaceRndSet(HARCH2, 100);
	DRLG_L2PlaceRndSet(HARCH3, 100);
	DRLG_L2PlaceRndSet(HARCH4, 100);
	DRLG_L2PlaceRndSet(HARCH5, 100);
	DRLG_L2PlaceRndSet(HARCH6, 100);
	DRLG_L2PlaceRndSet(HARCH7, 100);
	DRLG_L2PlaceRndSet(HARCH8, 100);
	DRLG_L2PlaceRndSet(HARCH9, 100);
	DRLG_L2PlaceRndSet(HARCH10, 100);
	DRLG_L2PlaceRndSet(HARCH11, 100);
	DRLG_L2PlaceRndSet(HARCH12, 100);
	DRLG_L2PlaceRndSet(HARCH13, 100);
	DRLG_L2PlaceRndSet(HARCH14, 100);
	DRLG_L2PlaceRndSet(HARCH15, 100);
	DRLG_L2PlaceRndSet(HARCH16, 100);
	DRLG_L2PlaceRndSet(HARCH17, 100);
	DRLG_L2PlaceRndSet(HARCH18, 100);
	DRLG_L2PlaceRndSet(HARCH19, 100);
	DRLG_L2PlaceRndSet(HARCH20, 100);
	DRLG_L2PlaceRndSet(HARCH21, 100);
	DRLG_L2PlaceRndSet(HARCH22, 100);
	DRLG_L2PlaceRndSet(HARCH23, 100);
	DRLG_L2PlaceRndSet(HARCH24, 100);
	DRLG_L2PlaceRndSet(HARCH25, 100);
	DRLG_L2PlaceRndSet(HARCH26, 100);
	DRLG_L2PlaceRndSet(HARCH27, 100);
	DRLG_L2PlaceRndSet(HARCH28, 100);
	DRLG_L2PlaceRndSet(HARCH29, 100);
	DRLG_L2PlaceRndSet(HARCH30, 100);
	DRLG_L2PlaceRndSet(HARCH31, 100);
	DRLG_L2PlaceRndSet(HARCH32, 100);
	DRLG_L2PlaceRndSet(HARCH33, 100);
	DRLG_L2PlaceRndSet(HARCH34, 100);
	DRLG_L2PlaceRndSet(HARCH35, 100);
	DRLG_L2PlaceRndSet(HARCH36, 100);
	DRLG_L2PlaceRndSet(HARCH37, 100);
	DRLG_L2PlaceRndSet(HARCH38, 100);
	DRLG_L2PlaceRndSet(HARCH39, 100);
	DRLG_L2PlaceRndSet(HARCH40, 100);
	DRLG_L2PlaceRndSet(CRUSHCOL, 99);
	DRLG_L2PlaceRndSet(RUINS1, 10);
	DRLG_L2PlaceRndSet(RUINS2, 10);
	DRLG_L2PlaceRndSet(RUINS3, 10);
	DRLG_L2PlaceRndSet(RUINS4, 10);
	DRLG_L2PlaceRndSet(RUINS5, 10);
	DRLG_L2PlaceRndSet(RUINS6, 10);
	DRLG_L2PlaceRndSet(RUINS7, 50);
	DRLG_L2PlaceRndSet(PANCREAS1, 1);
	DRLG_L2PlaceRndSet(PANCREAS2, 1);
	DRLG_L2PlaceRndSet(BIG1, 3);
	DRLG_L2PlaceRndSet(BIG2, 3);
	DRLG_L2PlaceRndSet(BIG3, 3);
	DRLG_L2PlaceRndSet(BIG4, 3);
	DRLG_L2PlaceRndSet(BIG5, 3);
	DRLG_L2PlaceRndSet(BIG6, 20);
	DRLG_L2PlaceRndSet(BIG7, 20);
	DRLG_L2PlaceRndSet(BIG8, 3);
	DRLG_L2PlaceRndSet(BIG9, 20);
	DRLG_L2PlaceRndSet(BIG10, 20);
	DRLG_L2Subs();
	DRLG_L2Shadows();

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			pdungeon[i][j] = dungeon[i][j];
		}
	}

	DRLG_Init_Globals();
	DRLG_CheckQuests(nSx1, nSy1);
}
// 5B50D8: using guessed type int setloadflag_2;

BOOL DRLG_L2PlaceMiniSet(unsigned char *miniset, int tmin, int tmax, int cx, int cy, BOOL setview, int ldir)
{
	int sx, sy, sw, sh, xx, yy, i, ii, numt, bailcnt;
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
		for(bailcnt = 0; !found && bailcnt < 200; bailcnt++) {
			found = TRUE;
			if(sx >= nSx1 && sx <= nSx2 && sy >= nSy1 && sy <= nSy2) {
				found = FALSE;
			}
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
		if(bailcnt >= 200) {
			return FALSE;
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
		ViewX = 2 * sx + 21;
		ViewY = 2 * sy + 22;
	}
	if(ldir == 0) {
		LvlViewX = 2 * sx + 21;
		LvlViewY = 2 * sy + 22;
	}
	if(ldir == 6) {
		LvlViewX = 2 * sx + 21;
		LvlViewY = 2 * sy + 22;
	}

	return TRUE;
}
// 5276CC: using guessed type int nSx2;
// 5276D4: using guessed type int nSy2;
// 5CF320: using guessed type int LvlViewY;
// 5CF324: using guessed type int LvlViewX;

void DRLG_L2PlaceRndSet(unsigned char *miniset, int rndper)
{
	int sx, sy, sw, sh, xx, yy, ii, kk;
	BOOL found;

	sw = miniset[0];
	sh = miniset[1];

	for(sy = 0; sy < 40 - sh; sy++) {
		for(sx = 0; sx < 40 - sw; sx++) {
			found = TRUE;
			ii = 2;
			if(sx >= nSx1 && sx <= nSx2 && sy >= nSy1 && sy <= nSy2) {
				found = FALSE;
			}
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
			if(found == TRUE) {
				for(yy = sy - sh; yy < sy + 2 * sh && found == TRUE; yy++) {
					for(xx = sx - sw; xx < sx + 2 * sw; xx++) {
						if(dungeon[xx][yy] == miniset[kk]) {
							found = FALSE;
						}
					}
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
// 5276CC: using guessed type int nSx2;
// 5276D4: using guessed type int nSy2;

void DRLG_L2Subs()
{
	int x, y, i, j, k, rv;
	unsigned char c;

	for(y = 0; y < 40; y++) {
		for(x = 0; x < 40; x++) {
			if((x < nSx1 || x > nSx2) && (y < nSy1 || y > nSy2) && random(0, 4) == 0) {
				c = BTYPESL2[dungeon[x][y]];
				if(c != 0) {
					rv = random(0, 16);
					k = -1;
					while(rv >= 0) {
						k++;
						if(k == sizeof(BTYPESL2)) {
							k = 0;
						}
						if(c == BTYPESL2[k]) {
							rv--;
						}
					}
					for(j = y - 2; j < y + 2; j++) {
						for(i = x - 2; i < x + 2; i++) {
							if(dungeon[i][j] == k) {
								j = y + 3;
								i = x + 2;
							}
						}
					}
					if(j < y + 3) {
						dungeon[x][y] = k;
					}
				}
			}
		}
	}
}
// 5276CC: using guessed type int nSx2;
// 5276D4: using guessed type int nSy2;

void DRLG_L2Shadows()
{
	int x, y, i;
	BOOL patflag;
	unsigned char sd[2][2];

	for(y = 1; y < 40; y++) {
		for(x = 1; x < 40; x++) {
			sd[0][0] = BSTYPESL2[dungeon[x][y]];
			sd[1][0] = BSTYPESL2[dungeon[x - 1][y]];
			sd[0][1] = BSTYPESL2[dungeon[x][y - 1]];
			sd[1][1] = BSTYPESL2[dungeon[x - 1][y - 1]];
			for(i = 0; i < 2; i++) {
				if(SPATSL2[i].strig == sd[0][0]) {
					patflag = TRUE;
					if(SPATSL2[i].s1 != 0 && SPATSL2[i].s1 != sd[1][1]) {
						patflag = FALSE;
					}
					if(SPATSL2[i].s2 != 0 && SPATSL2[i].s2 != sd[0][1]) {
						patflag = FALSE;
					}
					if(SPATSL2[i].s3 != 0 && SPATSL2[i].s3 != sd[1][0]) {
						patflag = FALSE;
					}
					if(patflag == TRUE) {
						if(SPATSL2[i].nv1 != 0) {
							dungeon[x - 1][y - 1] = SPATSL2[i].nv1;
						}
						if(SPATSL2[i].nv2 != 0) {
							dungeon[x][y - 1] = SPATSL2[i].nv2;
						}
						if(SPATSL2[i].nv3 != 0) {
							dungeon[x - 1][y] = SPATSL2[i].nv3;
						}
					}
				}
			}
		}
	}
}
// 48489A: using guessed type short word_48489A;

void DRLG_L2SetRoom(int rx1, int ry1)
{
	int rw, rh, i, j;
	unsigned char *sp;

	rw = (unsigned char)pSetPiece_2[0];
	rh = (unsigned char)pSetPiece_2[2];

	setpc_x = rx1;
	setpc_y = ry1;
	setpc_w = rw;
	setpc_h = rh;

	sp = (unsigned char *)&pSetPiece_2[4];

	for(j = 0; j < rh; j++) {
		for(i = 0; i < rw; i++) {
			if(*sp != 0) {
				dungeon[i + rx1][j + ry1] = *sp;
				dflags[i + rx1][j + ry1] |= 0x80;
			} else {
				dungeon[i + rx1][j + ry1] = 3;
			}
			sp += 2;
		}
	}
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

void L2TileFix()
{
	int i, j;

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 1 && dungeon[i][j + 1] == 3) {
				dungeon[i][j + 1] = 1;
			}
			if(dungeon[i][j] == 3 && dungeon[i][j + 1] == 1) {
				dungeon[i][j + 1] = 3;
			}
			if(dungeon[i][j] == 3 && dungeon[i + 1][j] == 7) {
				dungeon[i + 1][j] = 3;
			}
			if(dungeon[i][j] == 2 && dungeon[i + 1][j] == 3) {
				dungeon[i + 1][j] = 2;
			}
			if(dungeon[i][j] == 11 && dungeon[i + 1][j] == 14) {
				dungeon[i + 1][j] = 16;
			}
		}
	}
}

BOOL CreateDungeon()
{
	int v0;         // esi
	int v1;         // edx
	int v2;         // ecx
	signed int v3;  // esi
	char *v4;       // eax
	signed int v5;  // ebx
	_BYTE *v6;      // ecx
	BOOL v7;     // zf
	BOOL v8;     // eax
	int v9;         // edi
	int v10;        // esi
	signed int v12; // [esp-4h] [ebp-20h]
	int nX1;        // [esp+8h] [ebp-14h]
	int nY1;        // [esp+Ch] [ebp-10h]
	int nX2;        // [esp+10h] [ebp-Ch]
	int nY2;        // [esp+14h] [ebp-8h]
	int nHd;        // [esp+18h] [ebp-4h]

	v0 = 0;
	v1 = 0;
	v2 = 0;
	if (currlevel == 5) {
		if (!quests[QTYPE_BLOOD]._qactive)
			goto LABEL_12;
		v1 = 20;
		v0 = 14;
	} else {
		if (currlevel == 6) {
			if (!quests[QTYPE_BONE]._qactive)
				goto LABEL_12;
			v12 = 10;
		} else {
			if (currlevel != 7 || !quests[QTYPE_BLIND]._qactive)
				goto LABEL_12;
			v12 = 15;
		}
		v0 = v12;
		v1 = v12;
	}
	v2 = 1;
LABEL_12:
	CreateRoom(2, 2, 39, 39, 0, 0, v2, v1, v0);
	while (pHallList) {
		GetHall(&nX1, &nY1, &nX2, &nY2, &nHd);
		ConnectHall(nX1, nY1, nX2, nY2, nHd);
	}
	v3 = 0;
	do {
		v4 = (char *)&predungeon[-1][v3];
		v5 = 41;
		do {
			v6 = (unsigned char *)v4 + 40;
			if (v4[40] == 67)
				*v6 = 35;
			if (*v6 == 66)
				*v6 = 35;
			if (*v6 == 69)
				*v6 = 35;
			if (*v6 == 65)
				*v6 = 35;
			if (*v6 == 44) {
				v7 = *(v4 - 1) == 32;
				*v6 = 46;
				if (v7)
					*(v4 - 1) = 35;
				if (*v4 == 32)
					*v4 = 35;
				if (v4[1] == 32)
					v4[1] = 35;
				if (v4[79] == 32)
					v4[79] = 35;
				if (v4[80] == 32)
					v4[80] = 35;
				if (v4[81] == 32)
					v4[81] = 35;
				if (v4[39] == 32)
					v4[39] = 35;
				if (v4[41] == 32)
					v4[41] = 35;
			}
			--v5;
			v4 += 40;
		} while (v5);
		++v3;
	} while (v3 <= 40);
	v8 = DL2_FillVoids();
	if (v8) {
		v9 = 0;
		do {
			v10 = 0;
			do
				DoPatternCheck(v10++, v9);
			while (v10 < 40);
			++v9;
		} while (v9 < 40);
		v8 = 1;
	}
	return v8;
}

void CreateRoom(int nX1, int nY1, int nX2, int nY2, int nRDest, int nHDir, int ForceHW, int nH, int nW)
{
	int v9;        // esi
	int v10;       // ebx
	int v11;       // edx
	int v12;       // eax
	int v13;       // edx
	int v14;       // edx
	int v15;       // edi
	int v17;       // esi
	int v18;       // ebx
	int v19;       // edx
	int v20;       // ecx
	int v21;       // eax
	int v23;       // eax
	int v24;       // eax
	int v26;       // eax
	int *v27;      // ecx
	int v28;       // eax
	int v29;       // eax
	int *v30;      // ecx
	int v31;       // eax
	int nX1a;      // [esp+Ch] [ebp-30h]
	int v33;       // [esp+10h] [ebp-2Ch]
	int v34;       // [esp+14h] [ebp-28h]
	int v35;       // [esp+18h] [ebp-24h]
	int v36;       // [esp+1Ch] [ebp-20h]
	int v37;       // [esp+20h] [ebp-1Ch]
	int nY1a;      // [esp+24h] [ebp-18h]
	int v39;       // [esp+28h] [ebp-14h]
	int v40;       // [esp+2Ch] [ebp-10h]
	int v41;       // [esp+30h] [ebp-Ch]
	int v42;       // [esp+34h] [ebp-8h]
	int v43;       // [esp+38h] [ebp-4h]
	int *ForceHWa; // [esp+54h] [ebp+18h]
	int *ForceHWb; // [esp+54h] [ebp+18h]

	v39 = nY1;
	v37 = nX1;
	if (nRoomCnt < 80) {
		v40 = nX2 - 2;
		nY1a = nY1 + 2;
		while (1) {
			v9 = nX2 - v37;
			v10 = nY2 - v39;
			if (nX2 - v37 < Area_Min || v10 < Area_Min)
				return;
			if (v9 > Room_Max)
				break;
			nX1 = Room_Min;
			if (v9 > Room_Min) {
				v11 = v9 - Room_Min;
				goto LABEL_7;
			}
			v41 = nX2 - v37;
		LABEL_11:
			v13 = Room_Max;
			if (v10 <= Room_Max) {
				if (v10 <= nX1) {
					v36 = nY2 - v39;
					goto LABEL_16;
				}
				v13 = nY2 - v39;
			}
			v14 = v13 - nX1;
			v36 = Room_Min + random(0, v14);
		LABEL_16:
			if (ForceHW == 1) {
				v41 = nW;
				v36 = nH;
			}
			v15 = v37 + random(0, v9);
			v17 = v39 + random(0, v10);
			v18 = v15 + v41;
			v43 = v17 + v36;
			if (v15 + v41 > nX2) {
				v18 = nX2;
				v15 = nX2 - v41;
			}
			if (v17 + v36 > nY2) {
				v43 = nY2;
				v17 = nY2 - v36;
			}
			if (v15 >= 38)
				v15 = 38;
			if (v17 >= 38)
				v17 = 38;
			if (v15 <= 1)
				v15 = 1;
			if (v17 <= 1)
				v17 = 1;
			if (v18 >= 38)
				v18 = 38;
			if (v43 >= 38)
				v43 = 38;
			if (v18 <= 1)
				v18 = 1;
			if (v43 <= 1)
				v43 = 1;
			DefineRoom(v15, v17, v18, v43, ForceHW);
			if (ForceHW == 1) {
				nSx2 = v18;
				nSx1 = v15 + 2;
				nSy1 = v17 + 2;
				nSy2 = v43;
			}
			v19 = nRoomCnt;
			v20 = nRDest;
			v42 = nRoomCnt;
			RoomList[nRoomCnt].nRoomDest = nRDest;
			if (nRDest) {
				if (nHDir == 1) {
					v21 = random(0, v18 - v15 - 2);
					nX1a = v21 + v15 + 1;
					v33 = v17;
					v23 = random(0, RoomList[nRDest].nRoomx2 - RoomList[nRDest].nRoomx1 - 2);
					v20 = 20 * nRDest;
					v34 = v23 + RoomList[nRDest].nRoomx1 + 1;
					v35 = RoomList[nRDest].nRoomy2;
				}
				if (nHDir == 3) {
					v24 = random(0, v18 - v15 - 2);
					nX1a = v24 + v15 + 1;
					v33 = v43;
					v26 = random(0, RoomList[nRDest].nRoomx2 - RoomList[nRDest].nRoomx1 - 2);
					v20 = 20 * nRDest;
					v34 = v26 + RoomList[nRDest].nRoomx1 + 1;
					v35 = RoomList[nRDest].nRoomy1;
				}
				if (nHDir == 2) {
					nX1a = v18;
					v33 = random(0, v43 - v17 - 2) + v17 + 1;
					v34 = RoomList[nRDest].nRoomx1;
					v27 = &RoomList[nRDest].nRoomy1;
					ForceHWa = v27;
					v28 = RoomList[nRDest].nRoomy2 - *v27;
					v29 = random(0, v28 - 2);
					v20 = *ForceHWa;
					v35 = v29 + *ForceHWa + 1;
				}
				if (nHDir == 4) {
					nX1a = v15;
					v33 = random(0, v43 - v17 - 2) + v17 + 1;
					v34 = RoomList[nRDest].nRoomx2;
					v30 = &RoomList[nRDest].nRoomy1;
					ForceHWb = v30;
					v31 = RoomList[nRDest].nRoomy2 - *v30;
					v35 = random(0, v31 - 2) + *ForceHWb + 1;
				}
				AddHall(nX1a, v33, v34, v35, nHDir);
				v19 = v42;
			}
			if (v36 <= v41) {
				CreateRoom(v37 + 2, nY1a, v18 - 2, v17 - 2, v19, 3, 0, 0, 0);
				CreateRoom(v15 + 2, v43 + 2, v40, nY2 - 2, v42, 1, 0, 0, 0);
				CreateRoom(v37 + 2, v17 + 2, v15 - 2, nY2 - 2, v42, 2, 0, 0, 0);
				nHDir = 4;
				nW = 0;
				nH = 0;
				ForceHW = 0;
				nRDest = v42;
				nY2 = v43 - 2;
				nX2 -= 2;
				v40 -= 2;
				v39 += 2;
				nY1a += 2;
				v37 = v18 + 2;
			} else {
				CreateRoom(v37 + 2, nY1a, v15 - 2, v43 - 2, v19, 2, 0, 0, 0);
				CreateRoom(v18 + 2, v17 + 2, v40, nY2 - 2, v42, 4, 0, 0, 0);
				CreateRoom(v37 + 2, v43 + 2, v18 - 2, nY2 - 2, v42, 1, 0, 0, 0);
				nW = 0;
				nH = 0;
				ForceHW = 0;
				nRDest = v42;
				nHDir = 3;
				nX2 -= 2;
				v40 -= 2;
				v39 += 2;
				nY1a += 2;
				nY2 = v17 - 2;
				v37 = v15 + 2;
			}
			if (nRoomCnt >= 80)
				return;
		}
		v11 = Room_Max - Room_Min;
	LABEL_7:
		v12 = random(0, v11);
		nX1 = Room_Min;
		v41 = Room_Min + v12;
		goto LABEL_11;
	}
}
// 484858: using guessed type int Area_Min;
// 48485C: using guessed type int Room_Max;
// 484860: using guessed type int Room_Min;
// 5276CC: using guessed type int nSx2;
// 5276D4: using guessed type int nSy2;

void DefineRoom(int nX1, int nY1, int nX2, int nY2, int ForceHW)
{
	int v5;         // esi
	int v6;         // edi
	int v7;         // eax
	int i;          // eax
	BOOLEAN v9;     // zf
	int v10;        // ecx
	char *v11;      // eax
	char *v12;      // ebx
	int v13;        // eax
	int v14;        // [esp+10h] [ebp-4h]
	int v15;        // [esp+10h] [ebp-4h]
	int nY2a;       // [esp+20h] [ebp+Ch]
	char *ForceHWa; // [esp+24h] [ebp+10h]

	v5 = nX1;
	v6 = nX2;
	predungeon[v5][nY1] = 67;
	predungeon[v5][nY2] = 69;
	predungeon[v6][nY1] = 66;
	predungeon[v6][nY2] = 65;
	v7 = nRoomCnt + 1;
	nRoomCnt = v7;
	v7 *= 20;
	*(int *)((char *)&RoomList[0].nRoomx1 + v7) = nX1;
	*(int *)((char *)&RoomList[0].nRoomx2 + v7) = nX2;
	*(int *)((char *)&RoomList[0].nRoomy1 + v7) = nY1;
	*(int *)((char *)&RoomList[0].nRoomy2 + v7) = nY2;
	if (ForceHW == 1) {
		for (i = nX1; i < nX2; ++i) {
			if (i < nY2) {
				ForceHWa = &dflags[i][nY1];
				v14 = nY2 - i;
				i = nY2;
				do {
					*ForceHWa |= DFLAG_EXPLORED;
					v9 = v14-- == 1;
					ForceHWa += 40;
				} while (!v9);
			}
		}
	}
	v10 = nX1 + 1;
	if (v10 <= nX2 - 1) {
		v15 = nX2 - v10;
		v11 = (char *)&predungeon[v10][nY2];
		do {
			v11[nY1 - nY2] = 35;
			*v11 = 35;
			v11 += 40;
			--v15;
		} while (v15);
	}
	nY2a = nY2 - 1;
	while (++nY1 <= nY2a) {
		predungeon[v5][nY1] = 35;
		predungeon[v6][nY1] = 35;
		if (v10 < nX2) {
			v12 = (char *)&predungeon[v10][nY1];
			v13 = nX2 - v10;
			do {
				*v12 = 46;
				v12 += 40;
				--v13;
			} while (v13);
		}
	}
}

void AddHall(int nX1, int nY1, int nX2, int nY2, int nHd)
{
	int v5;       // edi
	int v6;       // esi
	HALLNODE *v7; // eax
	HALLNODE *i;  // ecx

	v5 = nX1;
	v6 = nY1;
	if (pHallList) {
		v7 = (HALLNODE *)DiabloAllocPtr(24);
		v7->pNext = 0;
		v7->nHallx2 = nX2;
		v7->nHally2 = nY2;
		v7->nHallx1 = v5;
		v7->nHally1 = v6;
		v7->nHalldir = nHd;
		for (i = pHallList; i->pNext; i = i->pNext)
			;
		i->pNext = v7;
	} else {
		pHallList = (HALLNODE *)DiabloAllocPtr(24);
		pHallList->nHallx1 = v5;
		pHallList->nHally1 = v6;
		pHallList->nHallx2 = nX2;
		pHallList->nHally2 = nY2;
		pHallList->nHalldir = nHd;
		pHallList->pNext = 0;
	}
}

void GetHall(int *nX1, int *nY1, int *nX2, int *nY2, int *nHd)
{
	HALLNODE *p1;
	HALLNODE *p2;

	p1 = pHallList->pNext;
	*nX1 = pHallList->nHallx1;
	*nY1 = pHallList->nHally1;
	*nX2 = pHallList->nHallx2;
	*nY2 = pHallList->nHally2;
	*nHd = pHallList->nHalldir;

	p2 = pHallList;
	pHallList = NULL;
	mem_free_dbg(p2);

	pHallList = p1;
}

void ConnectHall(int nX1, int nY1, int nX2, int nY2, int nHd)
{
	int v5;        // edi
	signed int v6; // esi
	int v7;        // eax
	int v9;        // edi
	int v10;       // ebx
	int v11;       // ecx
	char v12;      // al
	int v13;       // eax
	int v14;       // ecx
	char *v15;     // ebx
	int v16;       // ecx
	int v17;       // edx
	int v18;       // ecx
	int v19;       // edx
	int v20;       // eax
	//int v21; // ST04_4
	int v23;        // ebx
	int v24;        // ebx
	BOOLEAN v25;    // zf
	signed int v26; // [esp-4h] [ebp-34h]
	signed int v27; // [esp-4h] [ebp-34h]
	signed int v28; // [esp-4h] [ebp-34h]
	signed int v29; // [esp-4h] [ebp-34h]
	int v30;        // [esp+Ch] [ebp-24h]
	int v31;        // [esp+10h] [ebp-20h]
	int v32;        // [esp+14h] [ebp-1Ch]
	signed int v33; // [esp+18h] [ebp-18h]
	signed int v34; // [esp+1Ch] [ebp-14h]
	signed int v35; // [esp+20h] [ebp-10h]
	int v36;        // [esp+24h] [ebp-Ch]
	char *v37;      // [esp+28h] [ebp-8h]
	signed int nY;  // [esp+2Ch] [ebp-4h]
	int nX2a;       // [esp+38h] [ebp+8h]
	int nY2a;       // [esp+3Ch] [ebp+Ch]
	int nHda;       // [esp+40h] [ebp+10h]

	v34 = 0;
	v5 = nY1;
	v6 = nX1;
	nY = nY1;
	v7 = random(0, 100);
	v33 = v7;
	v32 = random(0, 100);
	v31 = v6;
	v30 = v5;
	CreateDoorType(v6, v5);
	CreateDoorType(nX2, nY2);
	abs(nX2 - v6);
	abs(nY2 - v5);
	v9 = nHd;
	v10 = nX2 - Dir_Xadd[nHd];
	v11 = nY2 - Dir_Yadd[nHd];
	nHda = 0;
	nY2a = v11;
	nX2a = v10;
	predungeon[v10][v11] = 44;
	v37 = (char *)&predungeon[v6][nY];
	do {
		if (v6 >= 38 && v9 == 2)
			v9 = 4;
		if (nY >= 38 && v9 == 3)
			v9 = 1;
		if (v6 <= 1 && v9 == 4)
			v9 = 2;
		if (nY <= 1 && v9 == 1)
			v9 = 3;
		v12 = *v37;
		if (*v37 == 67 && (v9 == 1 || v9 == 4))
			v9 = 2;
		if (v12 == 66 && (v9 == 1 || v9 == 2))
			v9 = 3;
		if (v12 == 69 && (v9 == 4 || v9 == 3))
			v9 = 1;
		if (v12 == 65 && (v9 == 2 || v9 == 3))
			v9 = 4;
		v13 = Dir_Xadd[v9];
		v14 = Dir_Yadd[v9];
		nY += v14;
		v6 += v13;
		v15 = (char *)&predungeon[v6][nY];
		v37 = v15;
		if (*v15 == 32) {
			if (nHda) {
				CreateDoorType(v6 - v13, nY - v14);
			} else {
				if (v33 < 50) {
					if (v9 == 1 || v9 == 3) {
						v17 = nY;
						v16 = v6 - 1;
					} else {
						v16 = v6;
						v17 = nY - 1;
					}
					PlaceHallExt(v16, v17);
				}
				if (v32 < 50) {
					if (v9 == 1 || v9 == 3) {
						v19 = nY;
						v18 = v6 + 1;
					} else {
						v18 = v6;
						v19 = nY + 1;
					}
					PlaceHallExt(v18, v19);
				}
			}
			nHda = 0;
			*v15 = 44;
		} else {
			if (!nHda && *v15 == 35)
				CreateDoorType(v6, nY);
			if (*v15 != 44)
				nHda = 1;
		}
		v36 = abs(nX2a - v6);
		v20 = abs(nY2a - nY);
		//v22 = v21;
		v35 = v20;
		if (v36 <= v20) {
			v24 = 5 * v20;
			if (5 * v20 > 80)
				v24 = 80;
			if (random(0, 100) < v24) {
				if (nY2a <= nY || nY >= 40) {
					v9 = 1;
					goto LABEL_67;
				}
				v26 = 3;
				goto LABEL_58;
			}
		} else {
			v23 = 2 * v36;
			if (2 * v36 > 30)
				v23 = 30;
			if (random(0, 100) < v23) {
				if (nX2a <= v6 || v6 >= 40)
					v26 = 4;
				else
					v26 = 2;
			LABEL_58:
				v9 = v26;
				goto LABEL_67;
			}
		}
	LABEL_67:
		if (v35 < 10 && v6 == nX2a && (v9 == 2 || v9 == 4)) {
			if (nY2a <= nY || nY >= 40)
				v9 = 1;
			else
				v9 = 3;
		}
		if (v36 < 10 && nY == nY2a && (v9 == 1 || v9 == 3)) {
			if (nX2a <= v6 || v6 >= 40)
				v27 = 4;
			else
				v27 = 2;
			v9 = v27;
		}
		if (v35 == 1) {
			v25 = v36 == 1;
			if (v36 <= 1)
				goto LABEL_94;
			if (v9 == 1 || v9 == 3) {
				if (nX2a <= v6 || v6 >= 40)
					v28 = 4;
				else
					v28 = 2;
				v9 = v28;
			}
		}
		v25 = v36 == 1;
	LABEL_94:
		if (v25) {
			if (v35 <= 1 || v9 != 2 && v9 != 4)
				goto LABEL_109;
			if (nY2a > nY && v6 < 40)
				goto LABEL_100;
			v9 = 1;
		}
		if (!v36 && *v37 != 32 && (v9 == 2 || v9 == 4)) {
			if (nX2a <= v31 || v6 >= 40) {
				v9 = 1;
				goto LABEL_109;
			}
		LABEL_100:
			v9 = 3;
		}
	LABEL_109:
		if (!v35 && *v37 != 32 && (v9 == 1 || v9 == 3)) {
			if (nY2a <= v30 || nY >= 40)
				v29 = 4;
			else
				v29 = 2;
			v9 = v29;
		}
		if (v6 == nX2a && nY == nY2a)
			v34 = 1;
	} while (!v34);
}

void CreateDoorType(int nX, int nY)
{
	BOOL fDoneflag;

	fDoneflag = FALSE;

	if(predungeon[nX - 1][nY] == 68) {
		fDoneflag = TRUE;
	}
	if(predungeon[nX + 1][nY] == 68) {
		fDoneflag = TRUE;
	}
	if(predungeon[nX][nY - 1] == 68) {
		fDoneflag = TRUE;
	}
	if(predungeon[nX][nY + 1] == 68) {
		fDoneflag = TRUE;
	}
	if(predungeon[nX][nY] == 66 || predungeon[nX][nY] == 67 || predungeon[nX][nY] == 65 || predungeon[nX][nY] == 69) {
		fDoneflag = TRUE;
	}

	if(!fDoneflag) {
		predungeon[nX][nY] = 68;
	}
}

void PlaceHallExt(int nX, int nY)
{
	if(predungeon[nX][nY] == 32) {
		predungeon[nX][nY] = 44;
	}
}

void DoPatternCheck(int i, int j)
{
	int k, l, x, y, nOk;

	for(k = 0; Patterns[k][4] != 255; k++) {
		x = i - 1;
		y = j - 1;
		nOk = 254;
		for(l = 0; l < 9 && nOk == 254; l++) {
			nOk = 255;
			if(l == 3 || l == 6) {
				y++;
				x = i - 1;
			}
			if(x >= 0 && x < 40 && y >= 0 && y < 40) {
				switch(Patterns[k][l]) {
				case 0:
					nOk = 254;
					break;
				case 1:
					if(predungeon[x][y] == 35) {
						nOk = 254;
					}
					break;
				case 2:
					if(predungeon[x][y] == 46) {
						nOk = 254;
					}
					break;
				case 4:
					if(predungeon[x][y] == 32) {
						nOk = 254;
					}
					break;
				case 3:
					if(predungeon[x][y] == 68) {
						nOk = 254;
					}
					break;
				case 5:
					if(predungeon[x][y] == 68 || predungeon[x][y] == 46) {
						nOk = 254;
					}
					break;
				case 6:
					if(predungeon[x][y] == 68 || predungeon[x][y] == 35) {
						nOk = 254;
					}
					break;
				case 7:
					if(predungeon[x][y] == 32 || predungeon[x][y] == 46) {
						nOk = 254;
					}
					break;
				case 8:
					if(predungeon[x][y] == 68 || predungeon[x][y] == 35 || predungeon[x][y] == 46) {
						nOk = 254;
					}
					break;
				}
			} else {
				nOk = 254;
			}
			x++;
		}
		if(nOk == 254) {
			dungeon[i][j] = Patterns[k][9];
		}
	}
}

BOOL DL2_FillVoids()
{
	int ii, jj, xx, yy, x1, x2, y1, y2;
	BOOL xf1, xf2, yf1, yf2;
	int to;

	to = 0;
	while(DL2_NumNoChar() > 700 && to < 100) {
		xx = random(0, 38) + 1;
		yy = random(0, 38) + 1;
		if(predungeon[xx][yy] != 35) {
			continue;
		}
		yf2 = FALSE;
		yf1 = FALSE;
		xf2 = FALSE;
		xf1 = FALSE;
		if(predungeon[xx - 1][yy] == 32 && predungeon[xx + 1][yy] == 46) {
			if(predungeon[xx + 1][yy - 1] == 46
			&& predungeon[xx + 1][yy + 1] == 46
			&& predungeon[xx - 1][yy - 1] == 32
			&& predungeon[xx - 1][yy + 1] == 32) {
				yf2 = TRUE;
				yf1 = TRUE;
				xf1 = TRUE;
			}
		} else if(predungeon[xx + 1][yy] == 32 && predungeon[xx - 1][yy] == 46) {
			if(predungeon[xx - 1][yy - 1] == 46
			&& predungeon[xx - 1][yy + 1] == 46
			&& predungeon[xx + 1][yy - 1] == 32
			&& predungeon[xx + 1][yy + 1] == 32) {
				yf2 = TRUE;
				yf1 = TRUE;
				xf2 = TRUE;
			}
		} else if(predungeon[xx][yy - 1] == 32 && predungeon[xx][yy + 1] == 46) {
			if(predungeon[xx - 1][yy + 1] == 46
			&& predungeon[xx + 1][yy + 1] == 46
			&& predungeon[xx - 1][yy - 1] == 32
			&& predungeon[xx + 1][yy - 1] == 32) {
				xf2 = TRUE;
				xf1 = TRUE;
				yf1 = TRUE;
			}
		} else if(predungeon[xx][yy + 1] == 32 && predungeon[xx][yy - 1] == 46) {
			if(predungeon[xx - 1][yy - 1] == 46
			&& predungeon[xx + 1][yy - 1] == 46
			&& predungeon[xx - 1][yy + 1] == 32
			&& predungeon[xx + 1][yy + 1] == 32) {
				xf2 = TRUE;
				xf1 = TRUE;
				yf2 = TRUE;
			}
		}
		if(DL2_Cont(xf1, yf1, xf2, yf2)) {
			if(xf1) {
				x1 = xx - 1;
			} else {
				x1 = xx;
			}
			if(xf2) {
				x2 = xx + 1;
			} else {
				x2 = xx;
			}
			if(yf1) {
				y1 = yy - 1;
			} else {
				y1 = yy;
			}
			if(yf2) {
				y2 = yy + 1;
			} else {
				y2 = yy;
			}
			if(!xf1) {
				while(yf1 || yf2) {
					if(y1 == 0) {
						yf1 = FALSE;
					}
					if(y2 == 39) {
						yf2 = FALSE;
					}
					if(y2 - y1 >= 14) {
						yf1 = FALSE;
						yf2 = FALSE;
					}
					if(yf1) {
						y1--;
					}
					if(yf2) {
						y2++;
					}
					if(predungeon[x2][y1] != 32) {
						yf1 = FALSE;
					}
					if(predungeon[x2][y2] != 32) {
						yf2 = FALSE;
					}
				}
				y1 += 2;
				y2 -= 2;
				if(y2 - y1 > 5) {
					while(xf2) {
						if(x2 == 39) {
							xf2 = FALSE;
						}
						if(x2 - x1 >= 12) {
							xf2 = FALSE;
						}
						for(jj = y1; jj <= y2; jj++) {
							if(predungeon[x2][jj] != 32) {
								xf2 = FALSE;
							}
						}
						if(xf2) {
							x2++;
						}
					}
					x2 -= 2;
					if(x2 - x1 > 5) {
						DL2_DrawRoom(x1, y1, x2, y2);
						DL2_KnockWalls(x1, y1, x2, y2);
					}
				}
			} else if(!xf2) {
				while(yf1 || yf2) {
					if(y1 == 0) {
						yf1 = FALSE;
					}
					if(y2 == 39) {
						yf2 = FALSE;
					}
					if(y2 - y1 >= 14) {
						yf1 = FALSE;
						yf2 = FALSE;
					}
					if(yf1) {
						y1--;
					}
					if(yf2) {
						y2++;
					}
					if(predungeon[x1][y1] != 32) {
						yf1 = FALSE;
					}
					if(predungeon[x1][y2] != 32) {
						yf2 = FALSE;
					}
				}
				y1 += 2;
				y2 -= 2;
				if(y2 - y1 > 5) {
					while(xf1) {
						if(x1 == 0) {
							xf1 = FALSE;
						}
						if(x2 - x1 >= 12) {
							xf1 = FALSE;
						}
						for(jj = y1; jj <= y2; jj++) {
							if(predungeon[x1][jj] != 32) {
								xf1 = FALSE;
							}
						}
						if(xf1) {
							x1--;
						}
					}
					x1 += 2;
					if(x2 - x1 > 5) {
						DL2_DrawRoom(x1, y1, x2, y2);
						DL2_KnockWalls(x1, y1, x2, y2);
					}
				}
			} else if(!yf1) {
				while(xf1 || xf2) {
					if(x1 == 0) {
						xf1 = FALSE;
					}
					if(x2 == 39) {
						xf2 = FALSE;
					}
					if(x2 - x1 >= 14) {
						xf1 = FALSE;
						xf2 = FALSE;
					}
					if(xf1) {
						x1--;
					}
					if(xf2) {
						x2++;
					}
					if(predungeon[x1][y2] != 32) {
						xf1 = FALSE;
					}
					if(predungeon[x2][y2] != 32) {
						xf2 = FALSE;
					}
				}
				x1 += 2;
				x2 -= 2;
				if(x2 - x1 > 5) {
					while(yf2) {
						if(y2 == 39) {
							yf2 = FALSE;
						}
						if(y2 - y1 >= 12) {
							yf2 = FALSE;
						}
						for(ii = x1; ii <= x2; ii++) {
							if(predungeon[ii][y2] != 32) {
								yf2 = FALSE;
							}
						}
						if(yf2) {
							y2++;
						}
					}
					y2 -= 2;
					if(y2 - y1 > 5) {
						DL2_DrawRoom(x1, y1, x2, y2);
						DL2_KnockWalls(x1, y1, x2, y2);
					}
				}
			} else if(!yf2) {
				while(xf1 || xf2) {
					if(x1 == 0) {
						xf1 = FALSE;
					}
					if(x2 == 39) {
						xf2 = FALSE;
					}
					if(x2 - x1 >= 14) {
						xf1 = FALSE;
						xf2 = FALSE;
					}
					if(xf1) {
						x1--;
					}
					if(xf2) {
						x2++;
					}
					if(predungeon[x1][y1] != 32) {
						xf1 = FALSE;
					}
					if(predungeon[x2][y1] != 32) {
						xf2 = FALSE;
					}
				}
				x1 += 2;
				x2 -= 2;
				if(x2 - x1 > 5) {
					while(yf1) {
						if(y1 == 0) {
							yf1 = FALSE;
						}
						if(y2 - y1 >= 12) {
							yf1 = FALSE;
						}
						for(ii = x1; ii <= x2; ii++) {
							if(predungeon[ii][y1] != 32) {
								yf1 = FALSE;
							}
						}
						if(yf1) {
							y1--;
						}
					}
					y1 += 2;
					if(y2 - y1 > 5) {
						DL2_DrawRoom(x1, y1, x2, y2);
						DL2_KnockWalls(x1, y1, x2, y2);
					}
				}
			}
		}
		to++;
	}

	return DL2_NumNoChar() <= 700;
}

BOOL DL2_Cont(BOOL x1f, BOOL y1f, BOOL x2f, BOOL y2f)
{
	if(x1f && x2f && y1f && y2f) {
		return FALSE;
	}
	if(x1f && x2f && (y1f || y2f)) {
		return TRUE;
	}
	if(y1f && y2f && (x1f || x2f)) {
		return TRUE;
	}

	return FALSE;
}

int DL2_NumNoChar()
{
	int t, ii, jj;

	t = 0;
	for(jj = 0; jj < 40; jj++) {
		for(ii = 0; ii < 40; ii++) {
			if(predungeon[ii][jj] == 32) {
				t++;
			}
		}
	}

	return t;
}

void DL2_DrawRoom(int x1, int y1, int x2, int y2)
{
	int ii, jj;

	for(jj = y1; jj <= y2; jj++) {
		for(ii = x1; ii <= x2; ii++) {
			predungeon[ii][jj] = 46;
		}
	}
	for(jj = y1; jj <= y2; jj++) {
		predungeon[x1][jj] = 35;
		predungeon[x2][jj] = 35;
	}
	for(ii = x1; ii <= x2; ii++) {
		predungeon[ii][y1] = 35;
		predungeon[ii][y2] = 35;
	}
}

void DL2_KnockWalls(int x1, int y1, int x2, int y2)
{
	int ii, jj;

	for(ii = x1 + 1; ii < x2; ii++) {
		if(predungeon[ii][y1 - 1] == 46 && predungeon[ii][y1 + 1] == 46) {
			predungeon[ii][y1] = 46;
		}
		if(predungeon[ii][y2 - 1] == 46 && predungeon[ii][y2 + 1] == 46) {
			predungeon[ii][y2] = 46;
		}
		if(predungeon[ii][y1 - 1] == 68) {
			predungeon[ii][y1 - 1] = 46;
		}
		if(predungeon[ii][y2 + 1] == 68) {
			predungeon[ii][y2 + 1] = 46;
		}
	}
	for(jj = y1 + 1; jj < y2; jj++) {
		if(predungeon[x1 - 1][jj] == 46 && predungeon[x1 + 1][jj] == 46) {
			predungeon[x1][jj] = 46;
		}
		if(predungeon[x2 - 1][jj] == 46 && predungeon[x2 + 1][jj] == 46) {
			predungeon[x2][jj] = 46;
		}
		if(predungeon[x1 - 1][jj] == 68) {
			predungeon[x1 - 1][jj] = 46;
		}
		if(predungeon[x2 + 1][jj] == 68) {
			predungeon[x2 + 1][jj] = 46;
		}
	}
}

void DRLG_L2FloodTVal()
{
	int i, j, xx, yy;

	yy = 16;
	for(j = 0; j < 40; j++) {
		xx = 16;
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 3 && dTransVal[xx][yy] == 0) {
				DRLG_L2FTVR(i, j, xx, yy, 0);
				TransVal++;
			}
			xx += 2;
		}
		yy += 2;
	}
}
// 5A5590: using guessed type char TransVal;

void DRLG_L2FTVR(int i, int j, int x, int y, int d)
{
	if(dTransVal[x][y] != 0 || dungeon[i][j] != 3) {
		if(d == 1) {
			dTransVal[x][y] = TransVal;
			dTransVal[x][y + 1] = TransVal;
		}
		if(d == 2) {
			dTransVal[x + 1][y] = TransVal;
			dTransVal[x + 1][y + 1] = TransVal;
		}
		if(d == 3) {
			dTransVal[x][y] = TransVal;
			dTransVal[x + 1][y] = TransVal;
		}
		if(d == 4) {
			dTransVal[x][y + 1] = TransVal;
			dTransVal[x + 1][y + 1] = TransVal;
		}
		if(d == 5) {
			dTransVal[x + 1][y + 1] = TransVal;
		}
		if(d == 6) {
			dTransVal[x][y + 1] = TransVal;
		}
		if(d == 7) {
			dTransVal[x + 1][y] = TransVal;
		}
		if(d == 8) {
			dTransVal[x][y] = TransVal;
		}
	} else {
		dTransVal[x][y] = TransVal;
		dTransVal[x + 1][y] = TransVal;
		dTransVal[x][y + 1] = TransVal;
		dTransVal[x + 1][y + 1] = TransVal;
		DRLG_L2FTVR(i + 1, j, x + 2, y, 1);
		DRLG_L2FTVR(i - 1, j, x - 2, y, 2);
		DRLG_L2FTVR(i, j + 1, x, y + 2, 3);
		DRLG_L2FTVR(i, j - 1, x, y - 2, 4);
		DRLG_L2FTVR(i - 1, j - 1, x - 2, y - 2, 5);
		DRLG_L2FTVR(i + 1, j - 1, x + 2, y - 2, 6);
		DRLG_L2FTVR(i - 1, j + 1, x - 2, y + 2, 7);
		DRLG_L2FTVR(i + 1, j + 1, x + 2, y + 2, 8);
	}
}
// 5A5590: using guessed type char TransVal;

void DRLG_L2TransFix()
{
	int i, j, xx, yy;

	yy = 16;
	for(j = 0; j < 40; j++) {
		xx = 16;
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 14 && dungeon[i][j - 1] == 10) {
				dTransVal[xx + 1][yy] = dTransVal[xx][yy];
				dTransVal[xx + 1][yy + 1] = dTransVal[xx][yy];
			}
			if(dungeon[i][j] == 15 && dungeon[i + 1][j] == 11) {
				dTransVal[xx][yy + 1] = dTransVal[xx][yy];
				dTransVal[xx + 1][yy + 1] = dTransVal[xx][yy];
			}
			if(dungeon[i][j] == 10) {
				dTransVal[xx + 1][yy] = dTransVal[xx][yy];
				dTransVal[xx + 1][yy + 1] = dTransVal[xx][yy];
			}
			if(dungeon[i][j] == 11) {
				dTransVal[xx][yy + 1] = dTransVal[xx][yy];
				dTransVal[xx + 1][yy + 1] = dTransVal[xx][yy];
			}
			if(dungeon[i][j] == 16) {
				dTransVal[xx + 1][yy] = dTransVal[xx][yy];
				dTransVal[xx][yy + 1] = dTransVal[xx][yy];
				dTransVal[xx + 1][yy + 1] = dTransVal[xx][yy];
			}
			xx += 2;
		}
		yy += 2;
	}
}

void L2DirtFix()
{
	int i, j;

	for(j = 0; j < 40; j++) {
		for(i = 0; i < 40; i++) {
			if(dungeon[i][j] == 13 && dungeon[i + 1][j] != 11) {
				dungeon[i][j] = 146;
			}
			if(dungeon[i][j] == 11 && dungeon[i + 1][j] != 11) {
				dungeon[i][j] = 144;
			}
			if(dungeon[i][j] == 15 && dungeon[i + 1][j] != 11) {
				dungeon[i][j] = 148;
			}
			if(dungeon[i][j] == 10 && dungeon[i][j + 1] != 10) {
				dungeon[i][j] = 143;
			}
			if(dungeon[i][j] == 13 && dungeon[i][j + 1] != 10) {
				dungeon[i][j] = 146;
			}
			if(dungeon[i][j] == 14 && dungeon[i][j + 1] != 15) {
				dungeon[i][j] = 147;
			}
		}
	}
}

void DRLG_InitL2Vals()
{
	int i, j, pc;

	for(j = 0; j < 112; j++) {
		for(i = 0; i < 112; i++) {
			if(dPiece[i][j] == 541) {
				pc = 5;
			} else if(dPiece[i][j] == 178) {
				pc = 5;
			} else if(dPiece[i][j] == 551) {
				pc = 5;
			} else if(dPiece[i][j] == 542) {
				pc = 6;
			} else if(dPiece[i][j] == 553) {
				pc = 6;
			} else if(dPiece[i][j] == 13) {
				pc = 5;
			} else if(dPiece[i][j] == 17) {
				pc = 6;
			} else {
				continue;
			}
			dArch[i][j] = pc;
		}
	}
	for(j = 0; j < 112; j++) {
		for(i = 0; i < 112; i++) {
			if(dPiece[i][j] == 132) {
				dArch[i][j + 1] = 2;
				dArch[i][j + 2] = 1;
			} else if(dPiece[i][j] == 135 || dPiece[i][j] == 139) {
				dArch[i + 1][j] = 3;
				dArch[i + 2][j] = 4;
			}
		}
	}
}
