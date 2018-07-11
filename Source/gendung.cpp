//HEADER_GOES_HERE

#include "../types.h"

short level_frame_types[2048];
int themeCount;
char nTransTable[2049];
//int dword_52D204;
int dMonster[112][112];
char dungeon[40][40];
char dObject[112][112];
void *pSpeedCels;
int nlevel_frames; // weak
char pdungeon[40][40];
char dDead[112][112];
short dpiece_defs_map_1[16][112][112];
char dTransVal2[112][112];
char TransVal; // weak
int dword_5A5594;
char dflags[40][40];
int dPiece[112][112];
char dTransVal[112][112];
int setloadflag_2; // weak
Tile tile_defs[1024];
void *pMegaTiles;
void *pLevelPieces;
int gnDifficulty; // idb
char block_lvid[2049];
//char byte_5B78EB;
char dung_map[112][112];
char nTrapTable[2049];
char leveltype; // weak
unsigned char currlevel; // idb
char TransList[256];
char nSolidTable[2049];
int level_frame_count[2048];
ScrollStruct ScrollInfo;
void *pDungeonCels;
int speed_cel_frame_num_from_light_index_frame_num[16][128];
THEME_LOC themeLoc[50];
char dPlayer[112][112];
int dword_5C2FF8; // weak
int dword_5C2FFC; // weak
int scr_pix_width; // weak
int scr_pix_height; // weak
char dArch[112][112];
char nBlockTable[2049];
void *level_special_cel;
char dFlags[112][112];
char dItem[112][112];
char setlvlnum; // weak
int level_frame_sizes[2048];
char nMissileTable[2049];
char *pSetPiece_2;
char setlvltype; // weak
char setlevel; // weak
int LvlViewY; // weak
int LvlViewX; // weak
int dmaxx; // weak
int dmaxy; // weak
int setpc_h; // weak
int setpc_w; // weak
int setpc_x; // idb
int ViewX; // idb
int ViewY; // idb
int setpc_y; // idb
char dMissile[112][112];
int dminx; // weak
int dminy; // weak
short dpiece_defs_map_2[16][112][112];

void __cdecl FillSolidBlockTbls()
{
	unsigned char *v0; // eax
	char *v1; // ecx
	unsigned char *v2; // esi
	int v3; // edx
	unsigned char v4; // bl
	int size; // [esp+8h] [ebp-4h]

	memset(nBlockTable, 0, 0x801u);
	memset(nSolidTable, 0, 0x801u);
	memset(nTransTable, 0, 0x801u);
	memset(nMissileTable, 0, 0x801u);
	memset(nTrapTable, 0, 0x801u);
	if ( leveltype != DTYPE_TOWN )
	{
		switch ( leveltype )
		{
			case DTYPE_CATHEDRAL:
				v1 = "Levels\\L1Data\\L1.SOL";
				break;
			case DTYPE_CATACOMBS:
				v1 = "Levels\\L2Data\\L2.SOL";
				break;
			case DTYPE_CAVES:
				v1 = "Levels\\L3Data\\L3.SOL";
				break;
			case DTYPE_HELL:
				v1 = "Levels\\L4Data\\L4.SOL";
				break;
			default:
				TermMsg("FillSolidBlockTbls");
				// v0 = (unsigned char *)size; /* check error */
				goto LABEL_13;
		}
	}
	else
	{
		v1 = "Levels\\TownData\\Town.SOL";
	}
	v0 = LoadFileInMem(v1, &size);
LABEL_13:
	v2 = v0;
	if ( (unsigned int)size >= 1 )
	{
		v3 = 0;
		do
		{
			v4 = *v2++;
			if ( v4 & 1 )
				nSolidTable[v3 + 1] = 1;
			if ( v4 & 2 )
				nBlockTable[v3 + 1] = 1;
			if ( v4 & 4 )
				nMissileTable[v3 + 1] = 1;
			if ( v4 & 8 )
				nTransTable[v3 + 1] = 1;
			if ( (v4 & 0x80u) != 0 )
				nTrapTable[v3 + 1] = 1;
			block_lvid[v3++ + 1] = (v4 >> 4) & 7;
		}
		while ( v3 + 1 <= (unsigned int)size );
	}
	mem_free_dbg(v0);
}
// 5BB1ED: using guessed type char leveltype;

void __cdecl SetupDungeon()
{
	//indexing variables
	int i;
	int j;
	int k;
	int l;

	int dungeon_type_iterations; //12 if hell else 10
	int map_length; //112
	int map_length_times_thirty_two; //112 * 32 (0xE00)
	short* dpiece_defs_map_2_ptr; //iterating through map entries
	short level_cel_block; //http://sanctuary.github.io/notes/#variable/level_cel_block
	short frame_num; // map_block_info & 0x0FFF
	short frame_type; //map_block_info & 0x7000 >> 12

	int* dungeon_cel; //same as pDungeonCels, but casted to int*
	int frame_size; // calculated from dungeon_cel[i + 1] - dungeon_cel[i], stored into level_frame_sizes

	int level_frame_types_index; //used to index level_frame_types
	char set_level_frame_count_zero; //bool used to check whether or not we should set current index into level frame count to zero
	char* level_cel_ptr; //ptr to pDungeonCels (moved around)
	char level_cel_index; //index into dungeon_cel_ptr
	unsigned char frame_num2; //used to check if the value from *level_cel_ptr is > 0 and < 32

	int total_level_frame_size; //used as a threshold to increment level_frame_size_index
	int level_frame_size_index; //index into level_frame_size
	int frame_multiplier; //a multipler that used in calculating total_level_frame_size and is 2 if light4flag else 14

	int ligthing_flag_enable; //0 if light4flag == 0 else -1
	int level_frame_total_size; //an index into pSpeedCel computed by adding level_frame_sizes
	int lighting_flag_index; //computed from light4flags & 0xF4 + 0xF. Will be either 15 or 0x103 (259). Used for array looping condition
	int speed_light_index; // used as an indexer in pSpeedCel until lighting_flag_index
	char* light_table_ptr; //
	int level_frame_size_val; //level_frame_size_val = level_frame_sizes[level_frame_types_index]; used as a array looping condition for copying
	int speed_light_multiplier_index; //used as a 16*i in accessing pSpeedCel
	int(*speed_cel_frame_num_from_light_index_frame_num_ptr)[128]; //
	int tile_defs_val; //value from tile_defs

	int dpieces_defs_map2_val; //value from dpieces_def_map2
	int(*dpiece_def_map_ptr)[112]; //ptr to dPiece
	int(*dpiece_defs_map_ptr2)[112];
	short* dpieces_defs_map3_ptr; //short* version
	short* dpieces_defs_map4_ptr;

	char* speed_cel_ptr; //ptr to pSpeedCel
	char level_cel_val; //val from level_cel_ptr

	memset(level_frame_types, 0, sizeof(level_frame_types));
	memset(level_frame_count, 0, sizeof(level_frame_count));

	//set tile_defs to be 1,2,3,...
	for (i = 0; i < sizeof(tile_defs)/sizeof(*tile_defs); i++)
	{
		tile_defs[i].top = i * 2;
		tile_defs[i].left = i * 2 + 1;
	}

	/*
	 * Iterates through dpiece_defs_map_2 and updates level_frame_types with the fetched value from dpiece_defs_map_2
	 */
	dungeon_type_iterations = 2 * (leveltype == DTYPE_HELL) + 10; //12 if in HELL else 10
	map_length = sizeof(dpiece_defs_map_2[0][0]) / sizeof(dpiece_defs_map_2[0][0][0]);
	map_length_times_thirty_two = map_length * 32;
	dpiece_defs_map_2_ptr = dpiece_defs_map_2[0][0];
	for (i = 0; i < map_length_times_thirty_two; i++)
	{
		for(j = 0; j < map_length; j++)
		{
			for (k = 0; k < dungeon_type_iterations; k++)
			{
				level_cel_block = dpiece_defs_map_2_ptr[k + j * map_length_times_thirty_two/2];
				if (level_cel_block)
				{
					frame_num = level_cel_block & 0x0FFF;
					frame_type = level_cel_block & 0x7000;
					++level_frame_count[frame_num];
					level_frame_types[frame_num] = frame_type;
				}
			}
		}
		dpiece_defs_map_2_ptr += 16;
	}

	/*
	 * Iterates through pDungeonCels and updates level_frame_size with the fetched values from pDungeonCels
	 */
	dungeon_cel = (int*)pDungeonCels;
	nlevel_frames = dungeon_cel[0] & 0xFFFF;
	for (i = 1; i < nlevel_frames; i++)
	{
		frame_size = dungeon_cel[i + 1] - dungeon_cel[i];
		level_frame_sizes[i] = frame_size & 0xFFFF;
	}

	/*
	 * This block updates level_frame_count (ONLY IN HELL ENVIRONMENT)
	 * The loops try to set set_level_frame_count_zero to 0. This is attempted by looping through dungeon_cel and checking if *dungeon_cel is > 0 and < 32.
	 * if set_level_frame_count_zero == 0, then level_frame_count[level_frame_types_index] = 0;
	 */
	level_frame_sizes[0] = 0;
	if (leveltype == DTYPE_HELL)
	{
		level_frame_count[0] = 0;
		for (level_frame_types_index = 0; level_frame_types_index < nlevel_frames; level_frame_types_index++)
		{
			set_level_frame_count_zero = 1;
			if (level_frame_count[level_frame_types_index])
			{
				if (level_frame_types[level_frame_types_index] == 4096)
				{
					level_cel_ptr = (char*)dungeon_cel + dungeon_cel[level_frame_types_index];
					for (j = 0; j < 32; j++)
					{
						for (k = 32; k != 0; k -= level_cel_index)
						{
							while (1)
							{
								level_cel_index = *level_cel_ptr++;
								//check msb (0 is valid)
								if ((level_cel_index & 0x80u) == 0)
									break;
								//else iterate and go to next dungeon cel ptr
								level_cel_index = -level_cel_index;
								k -= level_cel_index;
								if (!k)
								{
									break;
								}
							}
							if (!k)
							{
								break;
							}

							//if msb is 0, use the remaining level_cel_index to iterate and go to next level_cel_ptr
							for (l = 0; l < level_cel_index; l++)
							{
								frame_num2 = *level_cel_ptr++;
								if (frame_num2 < 32 && frame_num2 > 0) //check frame type
								{
									set_level_frame_count_zero = 0;
								}
							}
						}
					}
				}
				else
				{
					level_cel_ptr = (char*)dungeon_cel + dungeon_cel[level_frame_types_index];
					for (j = 0; j < level_frame_sizes[level_frame_types_index]; j++)
					{
						frame_num2 = *level_cel_ptr++;
						if (frame_num2 < 32 && frame_num2 > 0) //check frame type
						{
							set_level_frame_count_zero = 0;
						}
					}
				}
				if (!set_level_frame_count_zero)
				{
					level_frame_count[level_frame_types_index] = 0;
				}
			}
		}
	}

	//did not decompile gendung_4191BF
	gendung_4191BF(2047);

	/*
	 * This block updates level_frame_size_index (used to index level_frame_size), until total_level_frame_size >= 0x100000
	 */
	total_level_frame_size = 0;
	level_frame_size_index = 0;
	frame_multiplier = light4flag ? 2 : 14;
	while (total_level_frame_size < 0x100000)
	{
		total_level_frame_size += frame_multiplier * level_frame_sizes[level_frame_size_index++];
	}

	/*
	 * level_frame_size_index is capped at 128. 
	 * This block updates speed_cel_frame_num_from_light_index_frame_num, pSpeedCels
	 * speed_cel_frame_num_from_light_index_frame_num is updated by an element in tile_defs and level_frame_total_size (computed by elements in level_frame_sizes)
	 * pSpeedCels is updated by an element in pLightTbl using an element from dungeon_cel as an index.
	 */
	if (--level_frame_size_index > 128)// limit the index to 128
	{
		level_frame_size_index = 128;
	}
	ligthing_flag_enable = -(light4flag != 0); // 0 if 0 else -1
	level_frame_total_size = 0;
	lighting_flag_index = (ligthing_flag_enable & 0xF4) + 0xF;
	level_frame_types_index = 0;
	if (level_frame_size_index > 0)
	{
		speed_light_multiplier_index = 0;
		speed_cel_frame_num_from_light_index_frame_num_ptr = speed_cel_frame_num_from_light_index_frame_num;
		for(level_frame_types_index = 0; level_frame_types_index < level_frame_size_index; level_frame_types_index++)
		{
			tile_defs_val = *((_DWORD *)&tile_defs[0].top + level_frame_types_index);
			(*speed_cel_frame_num_from_light_index_frame_num_ptr)[0] = tile_defs_val;
			if (level_frame_types[level_frame_types_index] == 4096)
			{
				for(speed_light_index = 1; speed_light_index < lighting_flag_index; speed_light_index++)
				{
					speed_cel_frame_num_from_light_index_frame_num[0][speed_light_index + speed_light_multiplier_index] = level_frame_total_size;
					level_cel_ptr = (char*)dungeon_cel + dungeon_cel[tile_defs_val];
					speed_cel_ptr  = (char *)pSpeedCels + level_frame_total_size;
					light_table_ptr = (char *)pLightTbl + 0x100 * speed_light_index;
					for (i = 0; i < 32; i++)
					{
						for(j = 32; j != 0; j-= level_cel_val)
						{
							while (1)
							{
								level_cel_val = *level_cel_ptr++;
								*speed_cel_ptr++ = level_cel_val;
								if ((level_cel_val & 0x80u) == 0)
									break;
								level_cel_val = -level_cel_val;
								j -= level_cel_val;
								if (!j)
								{
									break;
								}
							}
							if (!j)
							{
								break;
							}

							for(k = 0; k < level_cel_val; k++)
							{
								*speed_cel_ptr++ = light_table_ptr[*level_cel_ptr++];
							}
						}
					}
					level_frame_total_size += level_frame_sizes[level_frame_types_index];
				}
			}
			else
			{
				level_frame_size_val = level_frame_sizes[level_frame_types_index];
				for(speed_light_index = 1; speed_light_index < lighting_flag_index; speed_light_index++)
				{
					speed_cel_frame_num_from_light_index_frame_num[0][speed_light_index + speed_light_multiplier_index] = level_frame_total_size;
					level_cel_ptr = (char*)dungeon_cel + dungeon_cel[tile_defs_val];
					light_table_ptr = (char *)pLightTbl + 0x100 * speed_light_index;
					speed_cel_ptr = (char *)pSpeedCels + level_frame_total_size;
					for (i = 0; i < level_frame_size_val; i++)
					{
						*speed_cel_ptr++ = light_table_ptr[*level_cel_ptr++];
					}
					level_frame_total_size += level_frame_size_val;
				}
			}
			speed_cel_frame_num_from_light_index_frame_num_ptr = (int(*)[128])((char *)speed_cel_frame_num_from_light_index_frame_num_ptr + 64);
			speed_light_multiplier_index += 16;
		}
	}

	/*
	 * This block updates dPiece (by checking values on multiple levels dPiece
	 * dPiece is updated by checking frame_num (0x0FFF) with tile_defs and then, copying an elment from level_frame_types into dPiece
	 */
	dpieces_defs_map2_val = 0;
	dpiece_def_map_ptr = dPiece;
	for (i = 0; i < map_length_times_thirty_two; i++)
	{
		dpieces_defs_map3_ptr = dpiece_defs_map_2[0][0];
		dpiece_defs_map_ptr2 = dpiece_def_map_ptr;
		for(j = 0; j < map_length; j++)
		{
			if ((*dpiece_defs_map_ptr2)[0] && (dungeon_type_iterations > 0))
			{
				dpieces_defs_map4_ptr = dpieces_defs_map3_ptr;
				for (k = 0; k < dungeon_type_iterations; k++)
				{
					dpieces_defs_map2_val = *dpieces_defs_map4_ptr;
					if (*dpieces_defs_map4_ptr)
					{
						if (level_frame_types_index > 0)
						{
							for (l = 0; l < level_frame_size_index; l++)
							{
								if ((dpieces_defs_map2_val & 0xFFF) == *((_DWORD *)&tile_defs[0].top + l))
								{
									level_frame_types_index = l;
									dpieces_defs_map2_val = l + level_frame_types[l] + -32768;
								}
							}
							*dpieces_defs_map4_ptr = dpieces_defs_map2_val;
						}
					}
					++dpieces_defs_map4_ptr;
					--dungeon_type_iterations;
				}
			}
			++dpiece_defs_map_ptr2;
			dpieces_defs_map3_ptr += map_length_times_thirty_two/2;
		}
		dpiece_def_map_ptr = (int(*)[112])((char *)dpiece_def_map_ptr + 4);
	}
}
// 525728: using guessed type int light4flag;
// 53CD4C: using guessed type int nlevel_frames;
// 5BB1ED: using guessed type char leveltype;

void __fastcall gendung_4191BF(int frames)
{
	int v1; // edi
	signed int v2; // eax
	int i; // esi

	v1 = frames;
	v2 = 0;
	while ( v1 > 0 && !v2 )
	{
		v2 = 1;
		for ( i = 0; i < v1; ++i )
		{
			if ( level_frame_count[i] < level_frame_count[i + 1] )
			{
				gendung_4191FB(i, i + 1);
				v2 = 0;
			}
		}
		--v1;
	}
}

void __fastcall gendung_4191FB(int a1, int a2)
{
	int v2; // esi
	int *v3; // edi
	short *v4; // edx
	int v5; // ST10_4
	int *v6; // edi
	int *v7; // eax
	int v8; // ST10_4
	short *v9; // ecx
	int v10; // edx

	v2 = a2;
	v3 = &level_frame_count[a1];
	v4 = &level_frame_types[a2];
	v2 *= 4;
	v5 = *v3;
	*v3 = *(int *)((char *)level_frame_count + v2);
	v6 = (int *)((char *)tile_defs + 4 * a1);
	*(int *)((char *)level_frame_count + v2) = v5;
	v7 = &level_frame_sizes[a1];
	v8 = *v6;
	*v6 = *(_DWORD *)((char *)&tile_defs[0].top + v2);
	*(_DWORD *)((char *)&tile_defs[0].top + v2) = v8;
	v9 = &level_frame_types[a1];
	_LOWORD(v6) = *v9;
	*v9 = *v4;
	*v4 = (signed short)v6;
	v10 = *v7;
	*v7 = *(int *)((char *)level_frame_sizes + v2);
	*(int *)((char *)level_frame_sizes + v2) = v10;
}

int __fastcall gendung_get_dpiece_num_from_coord(int x, int y)
{
	__int64 v3; // rax

	if ( x < 112 - y )
		return (y * (y + 1) + x * (x + 2 * y + 3)) / 2;
	v3 = (111 - y) * (111 - y + 1) + (111 - x) * (111 - x + 2 * (111 - y) + 3);
	return 12543 - (((signed int)v3 - HIDWORD(v3)) >> 1);
}

void __cdecl gendung_4192C2()
{
	short (*v0)[112][112]; // ebx
	int v1; // ebp
	short (*v2)[112][112]; // esi
	char *v3; // edi
	int x; // [esp+10h] [ebp-4h]

	x = 0;
	v0 = dpiece_defs_map_2;
	do
	{
		v1 = 0;
		do
		{
			v2 = v0;
			v3 = (char *)dpiece_defs_map_1 + 32 * gendung_get_dpiece_num_from_coord(x, v1++);
			v0 = (short (*)[112][112])((char *)v0 + 32);
			qmemcpy(v3, v2, 0x20u);
		}
		while ( v1 < 112 );
		++x;
	}
	while ( (signed int)v0 < (signed int)&dpiece_defs_map_2[16][0][0] );
}

void __cdecl SetDungeonMicros()
{
	signed int v0; // esi
	short (*v1)[112][112]; // edx
	int (*v2)[112]; // ebp
	int v3; // eax
	char *v4; // eax
	signed int i; // ecx
	_WORD *v6; // edi
	int j; // ecx
	short (*v8)[112][112]; // [esp+8h] [ebp-Ch]
	int (*v9)[112]; // [esp+Ch] [ebp-8h]
	signed int v10; // [esp+10h] [ebp-4h]

	if ( leveltype == DTYPE_HELL )
	{
		dword_5A5594 = 12;
		v0 = 16;
	}
	else
	{
		dword_5A5594 = 10;
		v0 = 10;
	}
	v9 = dPiece;
	v8 = dpiece_defs_map_2;
	do
	{
		v1 = v8;
		v2 = v9;
		v10 = 112;
		do
		{
			if ( (*v2)[0] )
			{
				v3 = (*v2)[0] - 1;
				if ( leveltype == DTYPE_HELL )
					v4 = (char *)pLevelPieces + 32 * v3;
				else
					v4 = (char *)pLevelPieces + 20 * v3;
				for ( i = 0; i < v0; ++i )
					(*v1)[0][i] = *(_WORD *)&v4[2 * (v0 + (i & 1) - (i & 0xE)) - 4];
			}
			else if ( v0 > 0 )
			{
				memset(v1, 0, 4 * ((unsigned int)v0 >> 1));
				v6 = (_WORD *)((char *)v1 + 4 * ((unsigned int)v0 >> 1));
				for ( j = v0 & 1; j; --j )
				{
					*v6 = 0;
					++v6;
				}
			}
			++v2;
			v1 = (short (*)[112][112])((char *)v1 + 3584);
			--v10;
		}
		while ( v10 );
		v8 = (short (*)[112][112])((char *)v8 + 32);
		v9 = (int (*)[112])((char *)v9 + 4);
	}
	while ( (signed int)v8 < (signed int)dpiece_defs_map_2[0][16] ); /* check */
	SetupDungeon();
	gendung_4192C2();
	if ( zoomflag )
	{
		scr_pix_width = 640;
		scr_pix_height = 352;
		dword_5C2FF8 = 10;
		dword_5C2FFC = 11;
	}
	else
	{
		scr_pix_width = 384;
		scr_pix_height = 224;
		dword_5C2FF8 = 6;
		dword_5C2FFC = 7;
	}
}
// 52569C: using guessed type int zoomflag;
// 5BB1ED: using guessed type char leveltype;
// 5C2FF8: using guessed type int dword_5C2FF8;
// 5C2FFC: using guessed type int dword_5C2FFC;
// 5C3000: using guessed type int scr_pix_width;
// 5C3004: using guessed type int scr_pix_height;

void __cdecl DRLG_InitTrans()
{
	memset(dung_map, 0, 0x3100u);
	memset(TransList, 0, 0x100u);
	TransVal = 1;
}
// 5A5590: using guessed type char TransVal;

void __fastcall DRLG_MRectTrans(int x1, int y1, int x2, int y2)
{
	int v4; // esi
	int v5; // edi
	int i; // eax
	char *v7; // edx
	int j; // ecx
	int ty_enda; // [esp+10h] [ebp+8h]

	v4 = 2 * x1 + 17;
	v5 = 2 * x2 + 16;
	i = 2 * y1 + 17;
	for ( ty_enda = 2 * y2 + 16; i <= ty_enda; ++i )
	{
		if ( v4 <= v5 )
		{
			v7 = &dung_map[v4][i];
			j = v5 - v4 + 1;
			do
			{
				*v7 = TransVal;
				v7 += 112;
				--j;
			}
			while ( j );
		}
	}
	++TransVal;
}
// 5A5590: using guessed type char TransVal;

void __fastcall DRLG_RectTrans(int x1, int y1, int x2, int y2)
{
	int i; // esi
	char *v5; // edx
	int j; // eax

	for ( i = y1; i <= y2; ++i )
	{
		if ( x1 <= x2 )
		{
			v5 = &dung_map[x1][i];
			j = x2 - x1 + 1;
			do
			{
				*v5 = TransVal;
				v5 += 112;
				--j;
			}
			while ( j );
		}
	}
	++TransVal;
}
// 5A5590: using guessed type char TransVal;

void __fastcall DRLG_CopyTrans(int sx, int sy, int dx, int dy)
{
	dung_map[dx][dy] = dung_map[sx][sy];
}

void __fastcall DRLG_ListTrans(int num, unsigned char *List)
{
	unsigned char *v2; // esi
	int v3; // edi
	unsigned char v4; // al
	unsigned char *v5; // esi
	unsigned char v6; // cl
	unsigned char v7; // dl
	unsigned char v8; // bl

	v2 = List;
	if ( num > 0 )
	{
		v3 = num;
		do
		{
			v4 = *v2;
			v5 = v2 + 1;
			v6 = *v5++;
			v7 = *v5++;
			v8 = *v5;
			v2 = v5 + 1;
			DRLG_RectTrans(v4, v6, v7, v8);
			--v3;
		}
		while ( v3 );
	}
}

void __fastcall DRLG_AreaTrans(int num, unsigned char *List)
{
	unsigned char *v2; // esi
	int v3; // edi
	unsigned char v4; // al
	unsigned char *v5; // esi
	unsigned char v6; // cl
	unsigned char v7; // dl
	unsigned char v8; // bl

	v2 = List;
	if ( num > 0 )
	{
		v3 = num;
		do
		{
			v4 = *v2;
			v5 = v2 + 1;
			v6 = *v5++;
			v7 = *v5++;
			v8 = *v5;
			v2 = v5 + 1;
			DRLG_RectTrans(v4, v6, v7, v8);
			--TransVal;
			--v3;
		}
		while ( v3 );
	}
	++TransVal;
}
// 5A5590: using guessed type char TransVal;

void __cdecl DRLG_InitSetPC()
{
	setpc_x = 0;
	setpc_y = 0;
	setpc_w = 0;
	setpc_h = 0;
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

void __cdecl DRLG_SetPC()
{
	int v0; // ebx
	int v1; // edx
	int v2; // ecx
	int v3; // esi
	int i; // eax
	int v5; // ebp
	char *v6; // edi

	v0 = 0;
	v1 = 2 * setpc_w;
	v2 = 2 * setpc_h;
	v3 = 2 * setpc_x + 16;
	for ( i = 2 * setpc_y + 16; v0 < v2; ++v0 )
	{
		if ( v1 > 0 )
		{
			v5 = v1;
			v6 = &dFlags[v3][v0 + i];
			do
			{
				*v6 |= 8u;
				v6 += 112;
				--v5;
			}
			while ( v5 );
		}
	}
}
// 5CF330: using guessed type int setpc_h;
// 5CF334: using guessed type int setpc_w;

void __fastcall Make_SetPC(int x, int y, int w, int h)
{
	int v4; // eax
	int v5; // esi
	int v6; // ebx
	int i; // eax
	int v8; // edx
	char *v9; // ecx
	int wa; // [esp+14h] [ebp+8h]

	v4 = w;
	wa = 0;
	v5 = 2 * v4;
	v6 = 2 * x + 16;
	for ( i = 2 * y + 16; wa < 2 * h; ++wa )
	{
		if ( v5 > 0 )
		{
			v8 = v5;
			v9 = &dFlags[v6][wa + i];
			do
			{
				*v9 |= 8u;
				v9 += 112;
				--v8;
			}
			while ( v8 );
		}
	}
}

bool __fastcall DRLG_WillThemeRoomFit(int floor, int x, int y, int minSize, int maxSize, int *width, int *height)
{
	int v7; // esi
	int v8; // edi
	int v10; // ebx
	int v11; // edx
	unsigned char *v12; // eax
	int v13; // eax
	int i; // eax
	int v15; // eax
	int v16; // esi
	int v17; // eax
	int v18; // edx
	int v19; // ecx
	int v21; // eax
	int v22; // esi
	int yArray[20]; // [esp+8h] [ebp-BCh]
	int xArray[20]; // [esp+58h] [ebp-6Ch]
	int v25; // [esp+A8h] [ebp-1Ch]
	int v26; // [esp+ACh] [ebp-18h]
	int v27; // [esp+B0h] [ebp-14h]
	int v28; // [esp+B4h] [ebp-10h]
	char *v29; // [esp+B8h] [ebp-Ch]
	int v30; // [esp+BCh] [ebp-8h]
	int v31; // [esp+C0h] [ebp-4h]

	v28 = 1;
	v27 = 1;
	v7 = x;
	v8 = 0;
	v25 = floor;
	v31 = 0;
	v30 = 0;
	if ( x > 40 - maxSize && y > 40 - maxSize )
		return 0;
	if ( !SkipThemeRoom(x, y) )
		return 0;
	memset(xArray, 0, 0x50u);
	memset(yArray, 0, 0x50u);
	if ( maxSize > 0 )
	{
		v10 = 40 * v7;
		v26 = 40 * v7;
		v29 = dungeon[v7];
		do
		{
			if ( v27 )
			{
				v11 = v7;
				if ( v7 < v7 + maxSize )
				{
					v12 = (unsigned char *)dungeon + v8 + v10 + y;
					do
					{
						if ( *v12 == v25 )
						{
							++v31;
						}
						else
						{
							if ( v11 >= minSize )
								break;
							v27 = 0;
						}
						++v11;
						v12 += 40;
					}
					while ( v11 < v7 + maxSize );
					v10 = v26;
				}
				if ( v27 )
				{
					v13 = v31;
					v31 = 0;
					xArray[v8] = v13;
				}
			}
			if ( v28 )
			{
				for ( i = y; i < y + maxSize; ++i )
				{
					if ( (unsigned char)v29[i] == v25 )
					{
						++v30;
					}
					else
					{
						if ( i >= minSize )
							break;
						v28 = 0;
					}
				}
				if ( v28 )
				{
					v15 = v30;
					v30 = 0;
					yArray[v8] = v15;
				}
			}
			v29 += 40;
			++v8;
		}
		while ( v8 < maxSize );
		v8 = 0;
	}
	v16 = minSize;
	v17 = 0;
	if ( minSize > 0 )
	{
		while ( xArray[v17] >= minSize && yArray[v17] >= minSize )
		{
			if ( ++v17 >= minSize )
				goto LABEL_32;
		}
		return 0;
	}
LABEL_32:
	v18 = xArray[0];
	v19 = yArray[0];
	if ( maxSize > 0 )
	{
		while ( 1 )
		{
			v21 = xArray[v8];
			if ( v21 < v16 )
				break;
			v22 = yArray[v8];
			if ( v22 < minSize )
				break;
			if ( v21 < v18 )
				v18 = xArray[v8];
			if ( v22 < v19 )
				v19 = yArray[v8];
			if ( ++v8 >= maxSize )
				break;
			v16 = minSize;
		}
	}
	*width = v18 - 2;
	*height = v19 - 2;
	return 1;
}
// 41965B: using guessed type int var_6C[20];
// 41965B: using guessed type int var_BC[20];

void __fastcall DRLG_CreateThemeRoom(int themeIndex)
{
	int v1; // esi
	int v2; // eax
	int v3; // edi
	int v4; // ebx
	int v5; // ecx
	int v6; // ecx
	int v7; // ebx
	int v8; // edx
	int v9; // ebx
	int v10; // edx
	int v11; // ebx
	int v12; // edx
	int v13; // eax
	int v14; // eax
	int v15; // eax
	int v16; // ecx
	char *v17; // eax
	int v18; // ecx
	char *v19; // eax
	int v20; // [esp+Ch] [ebp-8h]
	char *v21; // [esp+10h] [ebp-4h]

	v1 = themeIndex;
	v2 = themeLoc[themeIndex].y;
	v3 = themeLoc[themeIndex].height;
	v4 = v2;
	v5 = v3 + v2;
	if ( v2 < v3 + v2 )
	{
		v20 = themeLoc[v1].x + themeLoc[v1].width;
		while ( 1 )
		{
			v6 = themeLoc[v1].x;
			if ( v6 < v20 )
				break;
LABEL_52:
			++v4;
			v5 = v3 + v2;
			if ( v4 >= v3 + v2 )
				goto LABEL_53;
		}
		v21 = &dungeon[v6][v4];
		while ( 1 )
		{
			if ( leveltype != DTYPE_CATACOMBS )
				goto LABEL_21;
			if ( v4 == v2 && v6 >= themeLoc[v1].x && v6 <= v20 )
				goto LABEL_12;
			if ( v4 != v3 + v2 - 1 )
				goto LABEL_13;
			if ( v6 >= themeLoc[v1].x )
				break;
LABEL_16:
			if ( v6 == v20 - 1 && v4 >= v2 && v4 <= v3 + v2 )
				goto LABEL_19;
			*v21 = 3;
LABEL_21:
			if ( leveltype == DTYPE_CAVES )
			{
				if ( v4 == v2 && v6 >= themeLoc[v1].x && v6 <= v20 )
				{
LABEL_28:
					*v21 = -122;
					goto LABEL_51;
				}
				if ( v4 == v3 + v2 - 1 )
				{
					if ( v6 >= themeLoc[v1].x )
					{
						if ( v6 <= v20 )
							goto LABEL_28;
						goto LABEL_29;
					}
				}
				else
				{
LABEL_29:
					if ( v6 == themeLoc[v1].x && v4 >= v2 && v4 <= v3 + v2 )
					{
LABEL_35:
						*v21 = -119;
						goto LABEL_51;
					}
				}
				if ( v6 == v20 - 1 && v4 >= v2 && v4 <= v3 + v2 )
					goto LABEL_35;
				*v21 = 7;
			}
			if ( leveltype != DTYPE_HELL )
				goto LABEL_51;
			if ( v4 != v2 || v6 < themeLoc[v1].x || v6 > v20 )
			{
				if ( v4 != v3 + v2 - 1 )
					goto LABEL_44;
				if ( v6 < themeLoc[v1].x )
					goto LABEL_47;
				if ( v6 > v20 )
				{
LABEL_44:
					if ( v6 != themeLoc[v1].x || v4 < v2 || v4 > v3 + v2 )
					{
LABEL_47:
						if ( v6 != v20 - 1 || v4 < v2 || v4 > v3 + v2 )
						{
							*v21 = 6;
							goto LABEL_51;
						}
					}
LABEL_19:
					*v21 = 1;
					goto LABEL_51;
				}
			}
LABEL_12:
			*v21 = 2;
LABEL_51:
			v21 += 40;
			if ( ++v6 >= v20 )
				goto LABEL_52;
		}
		if ( v6 <= v20 )
			goto LABEL_12;
LABEL_13:
		if ( v6 == themeLoc[v1].x && v4 >= v2 && v4 <= v3 + v2 )
			goto LABEL_19;
		goto LABEL_16;
	}
LABEL_53:
	if ( leveltype == DTYPE_CATACOMBS )
	{
		v7 = themeLoc[v1].x;
		v8 = 10 * (v7 + themeLoc[v1].width);
		dungeon[v7][v2] = 8;
		v5 = v3 + 40 * v7;
		dungeon[-1][v8 * 4 + v2] = 7; // *((_BYTE *)&dMonster[111][v8 + 102] + v2) = 7; /* check */
		dungeon[0][v5 + v2 - 1] = 9; // *((_BYTE *)&dMonster[111][111] + v5 + v2 + 3) = 9;
		dungeon[-1][v3 + v8 * 4 + v2 - 1] = 6; // *((_BYTE *)&dMonster[111][101] + v3 + v8 * 4 + v2 + 3) = 6;
	}
	if ( leveltype == DTYPE_CAVES )
	{
		v9 = themeLoc[v1].x;
		v10 = 10 * (v9 + themeLoc[v1].width);
		dungeon[v9][v2] = 150;
		v5 = v3 + 40 * v9;
		dungeon[-1][v10 * 4 + v2] = 151; // *((_BYTE *)&dMonster[111][v10 + 102] + v2) = -105;
		dungeon[0][v5 + v2 - 1] = 152; // *((_BYTE *)&dMonster[111][111] + v5 + v2 + 3) = -104;
		dungeon[-1][v3 + v10 * 4 + v2 - 1] = 138; // *((_BYTE *)&dMonster[111][101] + v3 + v10 * 4 + v2 + 3) = -118;
	}
	if ( leveltype == DTYPE_HELL )
	{
		v11 = themeLoc[v1].x;
		v12 = 10 * (v11 + themeLoc[v1].width);
		dungeon[v11][v2] = 9;
		v5 = v3 + 40 * v11;
		dungeon[-1][v12 * 4 + v2] = 16; // *((_BYTE *)&dMonster[111][v12 + 102] + v2) = 16;
		dungeon[0][v5 + v2 - 1] = 15; // *((_BYTE *)&dMonster[111][111] + v5 + v2 + 3) = 15;
		dungeon[-1][v3 + v12 * 4 + v2 - 1] = 12; // *((_BYTE *)&dMonster[111][101] + v3 + v12 * 4 + v2 + 3) = 12;
	}
	if ( leveltype == DTYPE_CATACOMBS )
	{
		_LOBYTE(v5) = 0;
		v13 = random(v5, 2);
		if ( v13 )
		{
			if ( v13 == 1 )
			{
				v5 = themeLoc[v1].height;
				dungeon[themeLoc[v1].x + themeLoc[v1].width / 2][themeLoc[v1].y + v5 - 1] = 5; /*
				*((_BYTE *)&dMonster[111][10 * (themeLoc[v1].x + themeLoc[v1].width / 2) + 111] + themeLoc[v1].y
																								+ v5
																								+ 3) = 5; */
			}
		}
		else
		{
			v5 = themeLoc[v1].y;
			dungeon[themeLoc[v1].x + themeLoc[v1].width -1][themeLoc[v1].height / 2 + v5] = 4;
			// *((_BYTE *)&dMonster[111][10 * (themeLoc[v1].x + themeLoc[v1].width) + 102] + themeLoc[v1].height / 2 + v5) = 4;
		}
	}
	if ( leveltype == DTYPE_CAVES )
	{
		_LOBYTE(v5) = 0;
		v14 = random(v5, 2);
		if ( v14 )
		{
			if ( v14 == 1 )
			{
				v5 = themeLoc[v1].height;
				dungeon[themeLoc[v1].x + themeLoc[v1].width / 2][themeLoc[v1].y + v5 - 1] = 146; /*
				*((_BYTE *)&dMonster[111][10 * (themeLoc[v1].x + themeLoc[v1].width / 2) + 111] + themeLoc[v1].y
																								+ v5
																								+ 3) = -110; */
			}
		}
		else
		{
			v5 = themeLoc[v1].y;
			dungeon[themeLoc[v1].x + themeLoc[v1].width -1][themeLoc[v1].height / 2 + v5] = 147;
			// *((_BYTE *)&dMonster[111][10 * (themeLoc[v1].x + themeLoc[v1].width) + 102] + themeLoc[v1].height / 2 + v5) = -109;
		}
	}
	if ( leveltype == DTYPE_HELL )
	{
		_LOBYTE(v5) = 0;
		v15 = random(v5, 2);
		if ( v15 )
		{
			if ( v15 == 1 )
			{
				v16 = themeLoc[v1].y + 40 * (themeLoc[v1].x + themeLoc[v1].width / 2) + themeLoc[v1].height;
				v17 = (char *)dungeon + v16;
				*(v17 - 41) = 57;
				*(v17 - 1) = 6;
				dungeon[0][v16 + 39] = 56;
				*(v17 - 2) = 59;
				*(v17 - 42) = 58;
			}
		}
		else
		{
			v18 = themeLoc[v1].height / 2 + 40 * (themeLoc[v1].x + themeLoc[v1].width) + themeLoc[v1].y;
			v19 = (char *)dungeon + v18;
			*(v19 - 41) = 53;
			*(v19 - 40) = 6;
			dungeon[0][v18 - 39] = 52; // *((_BYTE *)&dMonster[111][102] + v18 + 1) = 52;
			*(v19 - 81) = 54;
		}
	}
}
// 5BB1ED: using guessed type char leveltype;

void __fastcall DRLG_PlaceThemeRooms(int minSize, int maxSize, int floor, int freq, int rndSize)
{
	int v5; // ebx
	int v6; // ecx
	//int v7; // eax
	int v8; // esi
	int v9; // edi
	int v10; // eax
	int v11; // ecx
	int v12; // eax
	int v13; // ecx
	int v14; // eax
	int v15; // ecx
	int v16; // eax
	int v17; // edi
	int v18; // esi
	int v19; // ecx
	int v20; // ecx
	int v21; // eax
	int minSize2; // [esp+10h] [ebp-1Ch]
	int maxSize2; // [esp+14h] [ebp-18h]
	unsigned char *v24; // [esp+18h] [ebp-14h]
	signed int x_start; // [esp+1Ch] [ebp-10h]
	int x; // [esp+20h] [ebp-Ch]
	int width; // [esp+24h] [ebp-8h]
	int height; // [esp+28h] [ebp-4h]

	v5 = 0;
	maxSize2 = maxSize;
	minSize2 = minSize;
	themeCount = 0;
	memset(themeLoc, 0, 0x14u);
	do
	{
		x = 0;
		x_start = 20;
		v24 = (unsigned char *)dungeon + v5;
		do
		{
			if ( *v24 == floor )
			{
				_LOBYTE(v6) = 0;
				if ( !random(v6, freq) )
				{
					//_LOBYTE(v7) = DRLG_WillThemeRoomFit(floor, x, v5, minSize2, maxSize2, &width, &height);
					if ( DRLG_WillThemeRoomFit(floor, x, v5, minSize2, maxSize2, &width, &height) )
					{
						if ( rndSize )
						{
							v8 = minSize2 - 2;
							v9 = maxSize2 - 2;
							_LOBYTE(v6) = 0;
							v10 = random(v6, width - (minSize2 - 2) + 1);
							_LOBYTE(v11) = 0;
							v12 = minSize2 - 2 + random(v11, v10);
							if ( v12 < minSize2 - 2 || (width = v12, v12 > v9) )
								width = minSize2 - 2;
							_LOBYTE(v13) = 0;
							v14 = random(v13, height - v8 + 1);
							_LOBYTE(v15) = 0;
							v16 = v8 + random(v15, v14);
							if ( v16 < v8 || v16 > v9 )
								v16 = minSize2 - 2;
							height = v16;
						}
						else
						{
							v16 = height;
						}
						v17 = themeCount;
						v18 = themeCount;
						themeLoc[v18].x = x + 1;
						themeLoc[v18].y = v5 + 1;
						v19 = width;
						themeLoc[v18].width = width;
						themeLoc[v18].height = v16;
						v20 = x + v19;
						v21 = v5 + v16;
						if ( leveltype == DTYPE_CAVES )
							DRLG_RectTrans(x_start, 2 * v5 + 20, 2 * v20 + 15, 2 * v21 + 15);
						else
							DRLG_MRectTrans(x + 1, v5 + 1, v20, v21);
						themeLoc[v18].ttval = TransVal - 1;
						DRLG_CreateThemeRoom(v17);
						++themeCount;
					}
				}
			}
			x_start += 2;
			++x;
			v24 += 40;
		}
		while ( x_start < 100 );
		++v5;
	}
	while ( v5 < 40 );
}
// 5A5590: using guessed type char TransVal;
// 5BB1ED: using guessed type char leveltype;

void __cdecl DRLG_HoldThemeRooms()
{
	int *v0; // esi
	int v1; // edi
	int v2; // edx
	int v3; // ebx
	int v4; // edi
	int v5; // ecx
	int v6; // eax
	int v7; // [esp+0h] [ebp-Ch]
	int v8; // [esp+4h] [ebp-8h]
	int v9; // [esp+8h] [ebp-4h]

	if ( themeCount > 0 )
	{
		v0 = &themeLoc[0].height;
		v8 = themeCount;
		do
		{
			v1 = *(v0 - 3);
			if ( v1 < v1 + *v0 - 1 )
			{
				v2 = *(v0 - 4);
				v3 = 2 * v1 + 16;
				v7 = v2 + *(v0 - 1) - 1;
				v9 = *v0 - 1;
				do
				{
					if ( v2 < v7 )
					{
						v4 = 224 * (v2 + 8);
						v5 = v7 - v2;
						do
						{
							v6 = v3 + v4;
							v4 += 224;
							dFlags[0][v6] |= 8u;
							dFlags[1][v6] |= 8u;
							dFlags[0][v6 + 1] |= 8u;
							dFlags[1][v6 + 1] |= 8u;
							--v5;
						}
						while ( v5 );
					}
					v3 += 2;
					--v9;
				}
				while ( v9 );
			}
			v0 += 5;
			--v8;
		}
		while ( v8 );
	}
}

bool __fastcall SkipThemeRoom(int x, int y)
{
	int i; // ebx
	THEME_LOC *v3; // eax
	int v4; // esi

	i = 0;
	if ( themeCount <= 0 )
		return 1;
	v3 = themeLoc;
	while ( 1 )
	{
		if ( x >= v3->x - 2 && x <= v3->x + v3->width + 2 )
		{
			v4 = v3->y;
			if ( y >= v4 - 2 && y <= v4 + v3->height + 2 )
				break;
		}
		++i;
		++v3;
		if ( i >= themeCount )
			return 1;
	}
	return 0;
}

void __cdecl InitLevels()
{
	if ( !leveldebug )
	{
		currlevel = 0;
		leveltype = 0;
		setlevel = 0;
	}
}
// 52572C: using guessed type int leveldebug;
// 5BB1ED: using guessed type char leveltype;
// 5CF31D: using guessed type char setlevel;
