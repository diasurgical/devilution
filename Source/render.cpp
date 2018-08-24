//HEADER_GOES_HERE

#include "../types.h"

int WorldBoolFlag = 0;
unsigned int gdwCurrentMask = 0;
// char world_4B3264 = 0;
unsigned char *gpCelFrame = NULL;
unsigned int *gpDrawMask = NULL;
// char world_4B326D[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

unsigned int RightMask[32] =
{
	0xEAAAAAAA, 0xF5555555, 0xFEAAAAAA, 0xFF555555, 0xFFEAAAAA, 0xFFF55555, 0xFFFEAAAA, 0xFFFF5555,
	0xFFFFEAAA, 0xFFFFF555, 0xFFFFFEAA, 0xFFFFFF55, 0xFFFFFFEA, 0xFFFFFFF5, 0xFFFFFFFE, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

unsigned int LeftMask[32] =
{
	0xAAAAAAAB, 0x5555555F, 0xAAAAAABF, 0x555555FF, 0xAAAAABFF, 0x55555FFF, 0xAAAABFFF, 0x5555FFFF,
	0xAAABFFFF, 0x555FFFFF, 0xAABFFFFF, 0x55FFFFFF, 0xABFFFFFF, 0x5FFFFFFF, 0xBFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

unsigned int WallMask[32] =
{
	0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555,
	0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555,
	0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555,
	0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0x55555555
};

int WorldTbl3x16[48] =
{
	0, 0, 0,
	4, 4, 4,
	8, 8, 8,
	12, 12, 12,
	16, 16, 16,
	20, 20, 20,
	24, 24, 24,
	28, 28, 28,
	32, 32, 32,
	36, 36, 36,
	40, 40, 40,
	44, 44, 44,
	48, 48, 48,
	52, 52, 52,
	56, 56, 56,
	60, 60, 60
};

// slope/angle tables, left and right
int WorldTbl17_1[17] = { 0, 4, 8, 16, 24, 36, 48, 64, 80, 100, 120, 144, 168, 196, 224, 256, 288 };
int WorldTbl17_2[17] = { 0, 32, 60, 88, 112, 136, 156, 176, 192, 208, 220, 232, 240, 248, 252, 256, 288 };

/*
 32x32 arch types
 add 8 if light index is 0

	|-| 0x8 (0)
	|-|

	/\  0x9 (1)
	\/

	 /| 0xA (2)
	 \|

	|\  0xB (3)
	|/

	|-| 0xC (4)
	 \|

	|-| 0xD (5)
	|/
*/

void __fastcall drawTopArchesUpperScreen(unsigned char *pbDst)
{
	char *tmp_pbDst; // edi MAPDST
	char *l_tbl; // ebx
	char *pdung_cels; // esi MAPDST
	short cel_type_16; // ax MAPDST
	unsigned int cel_type_16_tmp; // eax MAPDST
	int cel_type_32; // eax
	signed int xx_32; // ebp MAPDST
	signed int yy_32; // edx MAPDST
	unsigned int dung_and80; // eax MAPDST
	char l_index; // edx MAPDST
	unsigned int chk_sh_and; // ecx MAPDST
	unsigned char chk_andone; // cf
	unsigned int n_draw_shift; // ecx MAPDST
	unsigned int temp32; // eax MAPDST
	unsigned int x_minus; // ecx MAPDST
	unsigned int y_minus; // ecx MAPDST
	char *tmp_dst; // edi MAPDST
	signed int junk_v134; // ebp
	char *junk_v139; // esi
	char temp8; // al MAPDST
	short temp16; // ax MAPDST
	char junk_minus; // bp
	int junk_v180; // ebp
	signed int i; // edx MAPDST
	signed int j; // ecx MAPDST
	int y32_temp; // [esp-14h] [ebp-18h] MAPDST

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	tmp_pbDst = (char *)pbDst;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16_tmp = level_cel_block;
		_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
		cel_type_16 = ((cel_type_16_tmp >> 4) & 7) + 8;
		goto LABEL_11;
	}
	if ( (_BYTE)light_table_index != lightmax )
	{
		if ( !(level_cel_block & 0x8000) )
		{
			pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			l_tbl = &pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
			switch ( cel_type_16 )
			{
				case 0:
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						j = 8;
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = BYTE1(temp32);
							temp32 >>= 16;
							tmp_pbDst[1] = l_tbl[l_index];
							l_index = BYTE1(temp32);
							tmp_pbDst += 4;
							--j;
							*(tmp_pbDst - 1) = l_tbl[l_index];
						}
						while ( j );
						tmp_pbDst -= 800;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						j = 8;
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = temp32;
							*tmp_pbDst = l_tbl[l_index];
							l_index = BYTE2(temp32);
							tmp_pbDst += 4;
							--j;
							*(tmp_pbDst - 2) = l_tbl[l_index];
						}
						while ( j );
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					break;
				case 1:
					WorldBoolFlag = (unsigned char)pbDst & 1;
					xx_32 = 32;
					do
					{
						yy_32 = 32;
						do
						{
							while ( 1 )
							{
								dung_and80 = (unsigned char)*pdung_cels++;
								if ( (dung_and80 & 0x80u) == 0 )
									break;
								_LOBYTE(dung_and80) = -(char)dung_and80;
								tmp_pbDst += dung_and80;
								yy_32 -= dung_and80;
								if ( !yy_32 )
									goto LABEL_67;
							}
							l_index = yy_32 - dung_and80;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								return;
							if ( ((unsigned char)tmp_pbDst & 1) == WorldBoolFlag )
							{
								y32_temp = l_index;
								chk_sh_and = dung_and80 >> 1;
								if ( dung_and80 & 1 )
								{
									++pdung_cels;
									++tmp_pbDst;
									chk_andone = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( chk_andone )
									{
										l_index = *pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									chk_andone = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( chk_andone )
									{
										l_index = pdung_cels[1];
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								yy_32 = y32_temp;
							}
							else
							{
								y32_temp = l_index;
								chk_sh_and = dung_and80 >> 1;
								if ( dung_and80 & 1 )
								{
									l_index = *pdung_cels++;
									*tmp_pbDst++ = l_tbl[l_index];
									chk_andone = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( chk_andone )
									{
										l_index = pdung_cels[1];
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									chk_andone = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( chk_andone )
									{
										l_index = *pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								yy_32 = y32_temp;
							}
						}
						while ( yy_32 );
LABEL_67:
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						tmp_pbDst -= 800;
						--xx_32;
					}
					while ( xx_32 );
					break;
				case 2:
					WorldBoolFlag = 0;
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							l_index = x_minus & 2;
							pdung_cels += l_index;
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								++pdung_cels;
								++tmp_pbDst;
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
						}
						else
						{
							l_index = x_minus & 2;
							pdung_cels += l_index;
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								l_index = *pdung_cels++;
								*tmp_pbDst++ = l_tbl[l_index];
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 2;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								tmp_pbDst += yy_32;
								y_minus = 32 - yy_32;
								WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
								if ( WorldBoolFlag )
								{
									l_index = y_minus & 2;
									pdung_cels += l_index;
									chk_andone = y_minus & 1;
									chk_sh_and = y_minus >> 1;
									if ( chk_andone )
									{
										++pdung_cels;
										++tmp_pbDst;
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = *pdung_cels;
											pdung_cels += 2;
											*tmp_pbDst = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = temp32;
												*tmp_pbDst = l_tbl[l_index];
												l_index = BYTE2(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 2) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
									else
									{
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = pdung_cels[1];
											pdung_cels += 2;
											tmp_pbDst[1] = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = BYTE1(temp32);
												temp32 >>= 16;
												tmp_pbDst[1] = l_tbl[l_index];
												l_index = BYTE1(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 1) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
								}
								else
								{
									l_index = y_minus & 2;
									pdung_cels += l_index;
									chk_andone = y_minus & 1;
									chk_sh_and = y_minus >> 1;
									if ( chk_andone )
									{
										l_index = *pdung_cels++;
										*tmp_pbDst++ = l_tbl[l_index];
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = pdung_cels[1];
											pdung_cels += 2;
											tmp_pbDst[1] = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = BYTE1(temp32);
												temp32 >>= 16;
												tmp_pbDst[1] = l_tbl[l_index];
												l_index = BYTE1(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 1) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
									else
									{
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = *pdung_cels;
											pdung_cels += 2;
											*tmp_pbDst = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = temp32;
												*tmp_pbDst = l_tbl[l_index];
												l_index = BYTE2(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 2) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
								}
								tmp_pbDst -= 800;
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
					}
					break;
				case 3:
					WorldBoolFlag = 0;
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								++pdung_cels;
								++tmp_pbDst;
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							l_index = (unsigned char)pdung_cels & 2;
							pdung_cels += l_index;
						}
						else
						{
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								l_index = *pdung_cels++;
								*tmp_pbDst++ = l_tbl[l_index];
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							l_index = (unsigned char)pdung_cels & 2;
							pdung_cels += l_index;
						}
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 2;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								y_minus = 32 - yy_32;
								WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
								if ( WorldBoolFlag )
								{
									chk_andone = y_minus & 1;
									chk_sh_and = y_minus >> 1;
									if ( chk_andone )
									{
										++pdung_cels;
										++tmp_pbDst;
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = *pdung_cels;
											pdung_cels += 2;
											*tmp_pbDst = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = temp32;
												*tmp_pbDst = l_tbl[l_index];
												l_index = BYTE2(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 2) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
									else
									{
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = pdung_cels[1];
											pdung_cels += 2;
											tmp_pbDst[1] = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = BYTE1(temp32);
												temp32 >>= 16;
												tmp_pbDst[1] = l_tbl[l_index];
												l_index = BYTE1(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 1) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
									l_index = (unsigned char)pdung_cels & 2;
									pdung_cels += l_index;
								}
								else
								{
									chk_andone = y_minus & 1;
									chk_sh_and = y_minus >> 1;
									if ( chk_andone )
									{
										l_index = *pdung_cels++;
										*tmp_pbDst++ = l_tbl[l_index];
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = pdung_cels[1];
											pdung_cels += 2;
											tmp_pbDst[1] = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = BYTE1(temp32);
												temp32 >>= 16;
												tmp_pbDst[1] = l_tbl[l_index];
												l_index = BYTE1(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 1) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
									else
									{
										chk_andone = chk_sh_and & 1;
										n_draw_shift = chk_sh_and >> 1;
										if ( chk_andone )
										{
											l_index = *pdung_cels;
											pdung_cels += 2;
											*tmp_pbDst = l_tbl[l_index];
											tmp_pbDst += 2;
										}
										if ( (_BYTE)n_draw_shift )
										{
											do
											{
												temp32 = *(_DWORD *)pdung_cels;
												pdung_cels += 4;
												l_index = temp32;
												*tmp_pbDst = l_tbl[l_index];
												l_index = BYTE2(temp32);
												tmp_pbDst += 4;
												--n_draw_shift;
												*(tmp_pbDst - 2) = l_tbl[l_index];
											}
											while ( n_draw_shift );
										}
									}
									l_index = (unsigned char)pdung_cels & 2;
									pdung_cels += l_index;
								}
								tmp_pbDst = &tmp_pbDst[yy_32 - 800];
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
					}
					break;
				case 4:
					WorldBoolFlag = 0;
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							l_index = x_minus & 2;
							pdung_cels += l_index;
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								++pdung_cels;
								++tmp_pbDst;
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
						}
						else
						{
							l_index = x_minus & 2;
							pdung_cels += l_index;
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								l_index = *pdung_cels++;
								*tmp_pbDst++ = l_tbl[l_index];
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							i = 8;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( j );
								tmp_pbDst -= 800;
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( j );
								tmp_pbDst -= 800;
								--i;
							}
							while ( i );
							return;
						}
					}
					break;
				default:
					WorldBoolFlag = 0;
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								++pdung_cels;
								++tmp_pbDst;
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							l_index = (unsigned char)pdung_cels & 2;
							pdung_cels += l_index;
						}
						else
						{
							chk_andone = x_minus & 1;
							chk_sh_and = x_minus >> 1;
							if ( chk_andone )
							{
								l_index = *pdung_cels++;
								*tmp_pbDst++ = l_tbl[l_index];
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = pdung_cels[1];
									pdung_cels += 2;
									tmp_pbDst[1] = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = BYTE1(temp32);
										temp32 >>= 16;
										tmp_pbDst[1] = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 1) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								chk_andone = chk_sh_and & 1;
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_andone )
								{
									l_index = *pdung_cels;
									pdung_cels += 2;
									*tmp_pbDst = l_tbl[l_index];
									tmp_pbDst += 2;
								}
								if ( (_BYTE)n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										*tmp_pbDst = l_tbl[l_index];
										l_index = BYTE2(temp32);
										tmp_pbDst += 4;
										--n_draw_shift;
										*(tmp_pbDst - 2) = l_tbl[l_index];
									}
									while ( n_draw_shift );
								}
							}
							l_index = (unsigned char)pdung_cels & 2;
							pdung_cels += l_index;
						}
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							i = 8;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( j );
								tmp_pbDst -= 800;
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( j );
								tmp_pbDst -= 800;
								--i;
							}
							while ( i );
							return;
						}
					}
					break;
			}
			return;
		}
		pdung_cels = (char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
LABEL_11:

		switch ( cel_type_16 )
		{
			case 8:
				i = 16;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						break;
					j = 8;
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						temp32 = __ROR4__(temp32, 8);
						*tmp_dst = temp32;
						tmp_dst += 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 1;
						--j;
					}
					while ( j );
					tmp_pbDst -= 800;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						break;
					j = 8;
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*tmp_pbDst = temp32;
						tmp_dst = tmp_pbDst + 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 2;
						--j;
					}
					while ( j );
					tmp_pbDst -= 800;
					--i;
				}
				while ( i );
				break;
			case 9:
				WorldBoolFlag = (unsigned char)pbDst & 1;
				junk_v134 = 32;
LABEL_251:
				xx_32 = 32;
				while ( 1 )
				{
					while ( 1 )
					{
						dung_and80 = (unsigned char)*pdung_cels++;
						if ( (dung_and80 & 0x80u) == 0 )
							break;
						_LOBYTE(dung_and80) = -(char)dung_and80;
						tmp_pbDst += dung_and80;
						xx_32 -= dung_and80;
						if ( !xx_32 )
						{
LABEL_271:
							WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
							tmp_pbDst -= 800;
							if ( !--junk_v134 )
								return;
							goto LABEL_251;
						}
					}
					xx_32 -= dung_and80;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						return;
					if ( ((unsigned char)tmp_pbDst & 1) == WorldBoolFlag )
					{
						chk_sh_and = dung_and80 >> 1;
						if ( !(dung_and80 & 1) )
							goto LABEL_258;
						++pdung_cels;
						++tmp_pbDst;
						if ( chk_sh_and )
						{
LABEL_265:
							n_draw_shift = chk_sh_and >> 1;
							if ( chk_sh_and & 1 )
							{
								temp8 = *pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = temp8;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									*tmp_pbDst = temp32;
									tmp_dst = tmp_pbDst + 2;
									*tmp_dst = __ROR4__(temp32, 16);
									tmp_pbDst = tmp_dst + 2;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
							goto LABEL_268;
						}
					}
					else
					{
						chk_sh_and = dung_and80 >> 1;
						if ( !(dung_and80 & 1) )
							goto LABEL_265;
						temp8 = *pdung_cels++;
						*tmp_pbDst++ = temp8;
						if ( chk_sh_and )
						{
LABEL_258:
							n_draw_shift = chk_sh_and >> 1;
							if ( chk_sh_and & 1 )
							{
								junk_v139 = pdung_cels + 1;
								tmp_dst = tmp_pbDst + 1;
								temp8 = *junk_v139;
								pdung_cels = junk_v139 + 1;
								*tmp_dst = temp8;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									tmp_dst = tmp_pbDst + 1;
									temp32 = __ROR4__(temp32, 8);
									*tmp_dst = temp32;
									tmp_dst += 2;
									*tmp_dst = __ROR4__(temp32, 16);
									tmp_pbDst = tmp_dst + 1;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
							goto LABEL_268;
						}
					}
LABEL_268:
					if ( !xx_32 )
						goto LABEL_271;
				}
				break;
			case 10:
				WorldBoolFlag = 0;
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					tmp_pbDst += xx_32;
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						n_draw_shift = x_minus >> 2;
						if ( x_minus & 2 )
						{
							temp16 = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							*tmp_dst = __ROR4__(temp16, 8);
							tmp_pbDst = tmp_dst + 1;
						}
						if ( n_draw_shift )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								temp32 = __ROR4__(temp32, 8);
								*tmp_dst = temp32;
								tmp_dst += 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 1;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
					}
					else
					{
						n_draw_shift = x_minus >> 2;
						if ( x_minus & 2 )
						{
							temp16 = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							*tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*tmp_pbDst = temp32;
								tmp_dst = tmp_pbDst + 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 2;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						yy_32 = 2;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							tmp_pbDst += yy_32;
							y_minus = 32 - yy_32;
							WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
							if ( WorldBoolFlag )
							{
								n_draw_shift = y_minus >> 2;
								if ( y_minus & 2 )
								{
									temp16 = *((_WORD *)pdung_cels + 1);
									pdung_cels += 4;
									tmp_dst = tmp_pbDst + 1;
									*tmp_dst = __ROR4__(temp16, 8);
									tmp_pbDst = tmp_dst + 1;
								}
								if ( n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										tmp_dst = tmp_pbDst + 1;
										temp32 = __ROR4__(temp32, 8);
										*tmp_dst = temp32;
										tmp_dst += 2;
										*tmp_dst = __ROR4__(temp32, 16);
										tmp_pbDst = tmp_dst + 1;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
							}
							else
							{
								n_draw_shift = y_minus >> 2;
								if ( y_minus & 2 )
								{
									temp16 = *((_WORD *)pdung_cels + 1);
									pdung_cels += 4;
									*tmp_pbDst = temp16;
									tmp_pbDst += 2;
								}
								if ( n_draw_shift )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										*tmp_pbDst = temp32;
										tmp_dst = tmp_pbDst + 2;
										*tmp_dst = __ROR4__(temp32, 16);
										tmp_pbDst = tmp_dst + 2;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
							}
							tmp_pbDst -= 800;
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
				}
				break;
			case 11:
				WorldBoolFlag = 0;
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					x_minus = 32 - xx_32;
					junk_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							temp32 = __ROR4__(temp32, 8);
							*tmp_dst = temp32;
							tmp_dst += 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 1;
						}
						junk_v180 = junk_minus & 2;
						if ( junk_v180 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							*tmp_dst = __ROR4__(temp16, 8);
							tmp_pbDst = tmp_dst + 1;
						}
					}
					else
					{
						for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp32;
							tmp_dst = tmp_pbDst + 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 2;
						}
						junk_v180 = junk_minus & 2;
						if ( junk_v180 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						yy_32 = 2;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							y_minus = 32 - yy_32;
							WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
							if ( WorldBoolFlag )
							{
								for ( n_draw_shift = y_minus >> 2; n_draw_shift; --n_draw_shift )
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									tmp_dst = tmp_pbDst + 1;
									temp32 = __ROR4__(temp32, 8);
									*tmp_dst = temp32;
									tmp_dst += 2;
									*tmp_dst = __ROR4__(temp32, 16);
									tmp_pbDst = tmp_dst + 1;
								}
								junk_v180 &= 2u;
								if ( junk_v180 )
								{
									temp16 = *(_WORD *)pdung_cels;
									pdung_cels += 4;
									tmp_dst = tmp_pbDst + 1;
									*tmp_dst = __ROR4__(temp16, 8);
									tmp_pbDst = tmp_dst + 1;
								}
							}
							else
							{
								for ( n_draw_shift = y_minus >> 2; n_draw_shift; --n_draw_shift )
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									*tmp_pbDst = temp32;
									tmp_dst = tmp_pbDst + 2;
									*tmp_dst = __ROR4__(temp32, 16);
									tmp_pbDst = tmp_dst + 2;
								}
								junk_v180 &= 2u;
								if ( junk_v180 )
								{
									temp16 = *(_WORD *)pdung_cels;
									pdung_cels += 4;
									*tmp_pbDst = temp16;
									tmp_pbDst += 2;
								}
							}
							tmp_pbDst = &tmp_pbDst[yy_32 - 800];
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
				}
				break;
			case 12:
				WorldBoolFlag = 0;
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					tmp_pbDst += xx_32;
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						n_draw_shift = x_minus >> 2;
						if ( x_minus & 2 )
						{
							temp16 = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							*tmp_dst = __ROR4__(temp16, 8);
							tmp_pbDst = tmp_dst + 1;
						}
						if ( n_draw_shift)
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								temp32 = __ROR4__(temp32, 8);
								*tmp_dst = temp32;
								tmp_dst += 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 1;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
					}
					else
					{
						n_draw_shift = x_minus >> 2;
						if ( x_minus & 2 )
						{
							temp16 = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							*tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*tmp_pbDst = temp32;
								tmp_dst = tmp_pbDst + 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 2;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						i = 8;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								temp32 = __ROR4__(temp32, 8);
								*tmp_dst = temp32;
								tmp_dst += 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 1;
								--j;
							}
							while ( j );
							tmp_pbDst -= 800;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*tmp_pbDst = temp32;
								tmp_dst = tmp_pbDst + 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 2;
								--j;
							}
							while ( j );
							tmp_pbDst -= 800;
							--i;
						}
						while ( i );
						return;
					}
				}
				break;
			default:
				WorldBoolFlag = 0;
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							temp32 = __ROR4__(temp32, 8);
							*tmp_dst = temp32;
							tmp_dst += 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 1;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							*tmp_dst = __ROR4__(temp16, 8);
							tmp_pbDst = tmp_dst + 1;
						}
					}
					else
					{
						for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp32;
							tmp_dst = tmp_pbDst + 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 2;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						i = 8;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								temp32 = __ROR4__(temp32, 8);
								*tmp_dst = temp32;
								tmp_dst += 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 1;
								--j;
							}
							while ( j );
							tmp_pbDst -= 800;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*tmp_pbDst = temp32;
								tmp_dst = tmp_pbDst + 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 2;
								--j;
							}
							while ( j );
							tmp_pbDst -= 800;
							--i;
						}
						while ( i );
						return;
					}
				}
				break;
		}
		return;
	}
	if ( level_cel_block & 0x8000 )
		level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
						+ (unsigned short)(level_cel_block & 0xF000);
	pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
	cel_type_16_tmp = level_cel_block;
	_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
	cel_type_32 = (cel_type_16_tmp >> 4) & 7;
	switch ( (_WORD)cel_type_32 )
	{
		case 0:
			i = 16;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					tmp_pbDst[1] = 0;
					tmp_pbDst[3] = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					*tmp_pbDst = 0;
					tmp_pbDst[2] = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				--i;
			}
			while ( i );
			break;
		case 1:
			WorldBoolFlag = (unsigned char)pbDst & 1;
			xx_32 = 32;
			while ( 1 )
			{
				yy_32 = 32;
				do
				{
					while ( 1 )
					{
						dung_and80 = (unsigned char)*pdung_cels++;
						if ( (dung_and80 & 0x80u) != 0 )
							break;
						yy_32 -= dung_and80;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							return;
						pdung_cels += dung_and80;
						if ( ((unsigned char)tmp_pbDst & 1) == WorldBoolFlag )
						{
							chk_sh_and = dung_and80 >> 1;
							if ( !(dung_and80 & 1) )
								goto LABEL_378;
							++tmp_pbDst;
							if ( chk_sh_and )
							{
LABEL_385:
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_sh_and & 1 )
								{
									*tmp_pbDst = 0;
									tmp_pbDst += 2;
								}
								if ( n_draw_shift )
								{
									do
									{
										*tmp_pbDst = 0;
										tmp_pbDst[2] = 0;
										tmp_pbDst += 4;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
								goto LABEL_388;
							}
						}
						else
						{
							chk_sh_and = dung_and80 >> 1;
							if ( !(dung_and80 & 1) )
								goto LABEL_385;
							*tmp_pbDst++ = 0;
							if ( chk_sh_and )
							{
LABEL_378:
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_sh_and & 1 )
								{
									tmp_dst = tmp_pbDst + 1;
									*tmp_dst = 0;
									tmp_pbDst = tmp_dst + 1;
								}
								if ( n_draw_shift )
								{
									do
									{
										tmp_pbDst[1] = 0;
										tmp_pbDst[3] = 0;
										tmp_pbDst += 4;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
								goto LABEL_388;
							}
						}
LABEL_388:
						if ( !yy_32 )
							goto LABEL_391;
					}
					_LOBYTE(dung_and80) = -(char)dung_and80;
					tmp_pbDst += dung_and80;
					yy_32 -= dung_and80;
				}
				while ( yy_32 );
LABEL_391:
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				tmp_pbDst -= 800;
				if ( !--xx_32 )
					return;
			}
		case 2:
			WorldBoolFlag = 0;
			for ( xx_32 = 30; ; xx_32 -= 2 )
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					return;
				tmp_pbDst += xx_32;
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = 0;
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						*tmp_pbDst = 0;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift)
					{
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
					break;
			}
			yy_32 = 2;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				tmp_pbDst += yy_32;
				y_minus = 32 - yy_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = y_minus >> 2;
					if ( y_minus & 2 )
					{
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = 0;
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = y_minus >> 2;
					if ( y_minus & 2 )
					{
						*tmp_pbDst = 0;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift)
					{
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				yy_32 += 2;
			}
			while ( yy_32 != 32 );
			break;
		case 3:
			WorldBoolFlag = 0;
			for ( xx_32 = 30; ; xx_32 -= 2 )
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					return;
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = 0;
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						*tmp_pbDst = 0;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
					break;
				tmp_pbDst += xx_32;
			}
			yy_32 = 2;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				y_minus = 32 - yy_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = y_minus >> 2;
					if ( y_minus & 2 )
					{
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = 0;
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = y_minus >> 2;
					if ( y_minus & 2 )
					{
						*tmp_pbDst = 0;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst = &tmp_pbDst[yy_32 - 800];
				yy_32 += 2;
			}
			while ( yy_32 != 32 );
			break;
		case 4:
			WorldBoolFlag = 0;
			for ( xx_32 = 30; ; xx_32 -= 2 )
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					return;
				tmp_pbDst += xx_32;
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = 0;
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						*tmp_pbDst = 0;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
					break;
			}
			i = 8;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					tmp_pbDst[1] = 0;
					tmp_pbDst[3] = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					*tmp_pbDst = 0;
					tmp_pbDst[2] = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				--i;
			}
			while ( i );
			break;
		default:
			WorldBoolFlag = 0;
			for ( xx_32 = 30; ; xx_32 -= 2 )
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					return;
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = 0;
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						*tmp_pbDst = 0;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
					break;
				tmp_pbDst += xx_32;
			}
			i = 8;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					tmp_pbDst[1] = 0;
					tmp_pbDst[3] = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					*tmp_pbDst = 0;
					tmp_pbDst[2] = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				--i;
			}
			while ( i );
			break;
	}
}

void __fastcall drawBottomArchesUpperScreen(unsigned char *pbDst, unsigned int *pMask)
{
	char *tmp_pbDst; // edi MAPDST
	char *pdung_cels; // esi MAPDST
	short cel_type_16; // ax MAPDST
	unsigned int cel_type_16_tmp; // eax MAPDST
	int cel_type_32; // eax
	int xx_32; // edx MAPDST
	unsigned int left_shift; // edx MAPDST
	char temp8; // al MAPDST
	int yy_32; // edx MAPDST
	int dung_and80; // eax MAPDST
	int y_minus; // edx MAPDST
	int and80_i; // ecx MAPDST
	unsigned int n_draw_shift; // ecx MAPDST
	short temp16; // ax MAPDST
	int temp32; // eax MAPDST
	signed int i; // ecx MAPDST
	int y32_temp; // [esp-8h] [ebp-14h] MAPDST
	int x32_temp; // [esp-4h] [ebp-10h] MAPDST
	int _EAX;
	char *_EBX;

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	tmp_pbDst = (char *)pbDst;
	gpDrawMask = pMask;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16_tmp = level_cel_block;
		_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
		cel_type_16 = ((cel_type_16_tmp >> 4) & 7) + 8;
LABEL_12:
		switch ( cel_type_16 )
		{
			case 8:
				xx_32 = 32;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						break;
					x32_temp = xx_32;
					left_shift = *gpDrawMask;
					i = 32;
					do
					{
						temp8 = *pdung_cels++;
						if ( left_shift & 0x80000000 )
							*tmp_pbDst = temp8;
						left_shift *= 2;
						++tmp_pbDst;
						--i;
					}
					while ( i );
					tmp_pbDst -= 800;
					--gpDrawMask;
					xx_32 = x32_temp - 1;
				}
				while ( x32_temp != 1 );
				break;
			case 9:
				xx_32 = 32;
				do
				{
					x32_temp = xx_32;
					gdwCurrentMask = *gpDrawMask;
					yy_32 = 32;
					do
					{
						while ( 1 )
						{
							dung_and80 = (unsigned char)*pdung_cels++;
							if ( (dung_and80 & 0x80u) == 0 )
								break;
							_LOBYTE(dung_and80) = -(char)dung_and80;
							tmp_pbDst += dung_and80;
							if ( dung_and80 & 0x1F )
								gdwCurrentMask <<= dung_and80 & 0x1F;
							yy_32 -= dung_and80;
							if ( !yy_32 )
								goto LABEL_129;
						}
						y_minus = yy_32 - dung_and80;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							return;
						y32_temp = y_minus;
						left_shift = gdwCurrentMask;
						and80_i = dung_and80;
						do
						{
							temp8 = *pdung_cels++;
							if ( left_shift & 0x80000000 )
								*tmp_pbDst = temp8;
							left_shift *= 2;
							++tmp_pbDst;
							--and80_i;
						}
						while ( and80_i );
						gdwCurrentMask = left_shift;
						yy_32 = y32_temp;
					}
					while ( y32_temp );
LABEL_129:
					tmp_pbDst -= 800;
					--gpDrawMask;
					xx_32 = x32_temp - 1;
				}
				while ( x32_temp != 1 );
				break;
			case 10:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					tmp_pbDst += xx_32;
					n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
					if ( (32 - xx_32) & 2 )
					{
						temp16 = *((_WORD *)pdung_cels + 1);
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*(_DWORD *)tmp_pbDst = temp32;
							--n_draw_shift;
							tmp_pbDst += 4;
						}
						while ( n_draw_shift );
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						yy_32 = 2;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							tmp_pbDst += yy_32;
							n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
							if ( (32 - yy_32) & 2 )
							{
								temp16 = *((_WORD *)pdung_cels + 1);
								pdung_cels += 4;
								*(_WORD *)tmp_pbDst = temp16;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									*(_DWORD *)tmp_pbDst = temp32;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
							tmp_pbDst -= 800;
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
				}
				break;
			case 11:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						yy_32 = 2;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							for ( n_draw_shift = (unsigned int)(32 - yy_32) >> 2; n_draw_shift; --n_draw_shift )
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
							}
							if ( (32 - (_BYTE)yy_32) & 2 )
							{
								temp16 = *(_WORD *)pdung_cels;
								pdung_cels += 4;
								*(_WORD *)tmp_pbDst = temp16;
								tmp_pbDst += 2;
							}
							tmp_pbDst = &tmp_pbDst[yy_32 - 800];
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
				}
				break;
			case 12:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					tmp_pbDst += xx_32;
					n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
					if ( (32 - xx_32) & 2 )
					{
						temp16 = *((_WORD *)pdung_cels + 1);
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*(_DWORD *)tmp_pbDst = temp32;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						gpDrawMask -= 16;
						yy_32 = 16;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								temp8 = *pdung_cels++;
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = temp8;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							tmp_pbDst -= 800;
							--gpDrawMask;
							yy_32 = y32_temp - 1;
						}
						while ( y32_temp != 1 );
						return;
					}
				}
				break;
			default:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						gpDrawMask -= 16;
						yy_32 = 16;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								temp8 = *pdung_cels++;
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = temp8;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							pdung_cels += (unsigned char)pdung_cels & 2;
							tmp_pbDst -= 800;
							--gpDrawMask;
							yy_32 = y32_temp - 1;
						}
						while ( y32_temp != 1 );
						return;
					}
				}
				break;
		}
		return;
	}
	if ( (_BYTE)light_table_index != lightmax )
	{
		if ( !(level_cel_block & 0x8000) )
		{
			pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			_EBX = &pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
			switch ( cel_type_16 )
			{
				case 0:
					xx_32 = 32;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						x32_temp = xx_32;
						left_shift = *gpDrawMask;
						i = 32;
						do
						{
							_EAX = *pdung_cels++;
							if ( left_shift & 0x80000000 )
							{
								ASM_XLAT(_EAX,_EBX);
								*tmp_pbDst = _EAX;
							}
							left_shift *= 2;
							++tmp_pbDst;
							--i;
						}
						while ( i );
						tmp_pbDst -= 800;
						--gpDrawMask;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 1:
					xx_32 = 32;
					do
					{
						x32_temp = xx_32;
						gdwCurrentMask = *gpDrawMask;
						yy_32 = 32;
						do
						{
							while ( 1 )
							{
								dung_and80 = (unsigned char)*pdung_cels++;
								if ( (dung_and80 & 0x80u) == 0 )
									break;
								_LOBYTE(dung_and80) = -(char)dung_and80;
								tmp_pbDst += dung_and80;
								if ( dung_and80 & 0x1F )
									gdwCurrentMask <<= dung_and80 & 0x1F;
								yy_32 -= dung_and80;
								if ( !yy_32 )
									goto LABEL_50;
							}
							y_minus = yy_32 - dung_and80;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								return;
							and80_i = dung_and80;
							y32_temp = y_minus;
							left_shift = gdwCurrentMask;
							do
							{
								_EAX = *pdung_cels++;
								if ( left_shift & 0x80000000 )
								{
									ASM_XLAT(_EAX,_EBX);
									*tmp_pbDst = _EAX;
								}
								left_shift *= 2;
								++tmp_pbDst;
								--and80_i;
							}
							while ( and80_i );
							gdwCurrentMask = left_shift;
							yy_32 = y32_temp;
						}
						while ( y32_temp );
LABEL_50:
						tmp_pbDst -= 800;
						--gpDrawMask;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 2:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tmp_pbDst += xx_32;
						n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
						if ( (32 - xx_32) & 2 )
						{
							_EAX = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								_EAX = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 2;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								tmp_pbDst += yy_32;
								n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
								if ( (32 - yy_32) & 2 )
								{
									_EAX = *((_WORD *)pdung_cels + 1);
									pdung_cels += 4;
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR2__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
									tmp_pbDst += 2;
								}
								if ( n_draw_shift )
								{
									do
									{
										_EAX = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										ASM_XLAT(_EAX,_EBX);
										_EAX = __ROR4__(_EAX, 8);
										ASM_XLAT(_EAX,_EBX);
										_EAX = __ROR4__(_EAX, 8);
										ASM_XLAT(_EAX,_EBX);
										_EAX = __ROR4__(_EAX, 8);
										ASM_XLAT(_EAX,_EBX);
										*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
										tmp_pbDst += 4;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
								tmp_pbDst -= 800;
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
					}
					break;
				case 3:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
						{
							_EAX = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
							tmp_pbDst += 4;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							_EAX = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 2;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								for ( n_draw_shift = (unsigned int)(32 - yy_32) >> 2; n_draw_shift; --n_draw_shift )
								{
									_EAX = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR4__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR4__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR4__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
									tmp_pbDst += 4;
								}
								if ( (32 - (_BYTE)yy_32) & 2 )
								{
									_EAX = *(_WORD *)pdung_cels;
									pdung_cels += 4;
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR2__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
									tmp_pbDst += 2;
								}
								tmp_pbDst = &tmp_pbDst[yy_32 - 800];
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
					}
					break;
				case 4:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tmp_pbDst += xx_32;
						n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
						if ( (32 - xx_32) & 2 )
						{
							_EAX = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								_EAX = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							gpDrawMask -= 16;
							yy_32 = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								y32_temp = yy_32;
								left_shift = *gpDrawMask;
								i = 32;
								pdung_cels += (unsigned char)pdung_cels & 2;
								do
								{
									_EAX = *pdung_cels++;
									if ( left_shift & 0x80000000 )
									{
										ASM_XLAT(_EAX,_EBX);
										*tmp_pbDst = _EAX;
									}
									left_shift *= 2;
									++tmp_pbDst;
									--i;
								}
								while ( i );
								tmp_pbDst -= 800;
								--gpDrawMask;
								yy_32 = y32_temp - 1;
							}
							while ( y32_temp != 1 );
							return;
						}
					}
					break;
				default:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
						{
							_EAX = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
							tmp_pbDst += 4;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							_EAX = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							gpDrawMask -= 16;
							yy_32 = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								y32_temp = yy_32;
								left_shift = *gpDrawMask;
								i = 32;
								do
								{
									_EAX = *pdung_cels++;
									if ( left_shift & 0x80000000 )
									{
										ASM_XLAT(_EAX,_EBX);
										*tmp_pbDst = _EAX;
									}
									left_shift *= 2;
									++tmp_pbDst;
									--i;
								}
								while ( i );
								pdung_cels += (unsigned char)pdung_cels & 2;
								tmp_pbDst -= 800;
								--gpDrawMask;
								yy_32 = y32_temp - 1;
							}
							while ( y32_temp != 1 );
							return;
						}
					}
					break;
			}
			return;
		}
		pdung_cels = (char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
		goto LABEL_12;
	}
	if ( level_cel_block & 0x8000 )
		level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
						+ (unsigned short)(level_cel_block & 0xF000);
	pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
	cel_type_16_tmp = level_cel_block;
	_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
	cel_type_32 = (cel_type_16_tmp >> 4) & 7;
	switch ( (_WORD)cel_type_32 )
	{
		case 0:
			xx_32 = 32;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				x32_temp = xx_32;
				left_shift = *gpDrawMask;
				i = 32;
				do
				{
					if ( left_shift & 0x80000000 )
						*tmp_pbDst = 0;
					left_shift *= 2;
					++tmp_pbDst;
					--i;
				}
				while ( i );
				tmp_pbDst -= 800;
				--gpDrawMask;
				xx_32 = x32_temp - 1;
			}
			while ( x32_temp != 1 );
			break;
		case 1:
			xx_32 = 32;
			do
			{
				x32_temp = xx_32;
				gdwCurrentMask = *gpDrawMask;
				yy_32 = 32;
				do
				{
					while ( 1 )
					{
						dung_and80 = (unsigned char)*pdung_cels++;
						if ( (dung_and80 & 0x80u) == 0 )
							break;
						_LOBYTE(dung_and80) = -(char)dung_and80;
						tmp_pbDst += dung_and80;
						if ( dung_and80 & 0x1F )
							gdwCurrentMask <<= dung_and80 & 0x1F;
						yy_32 -= dung_and80;
						if ( !yy_32 )
							goto LABEL_208;
					}
					y_minus = yy_32 - dung_and80;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						return;
					y32_temp = y_minus;
					left_shift = gdwCurrentMask;
					and80_i = dung_and80;
					pdung_cels += dung_and80;
					do
					{
						if ( left_shift & 0x80000000 )
							*tmp_pbDst = 0;
						left_shift *= 2;
						++tmp_pbDst;
						--and80_i;
					}
					while ( and80_i );
					gdwCurrentMask = left_shift;
					yy_32 = y32_temp;
				}
				while ( y32_temp );
LABEL_208:
				tmp_pbDst -= 800;
				--gpDrawMask;
				xx_32 = x32_temp - 1;
			}
			while ( x32_temp != 1 );
			break;
		case 2:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					yy_32 = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						tmp_pbDst += yy_32;
						n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
						if ( (32 - yy_32) & 2 )
						{
							*(_WORD *)tmp_pbDst = 0;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						yy_32 += 2;
					}
					while ( yy_32 != 32 );
					return;
				}
				xx_32 -= 2;
			}
			break;
		case 3:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					yy_32 = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
						if ( (32 - yy_32) & 2 )
						{
							*(_WORD *)tmp_pbDst = 0;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst = &tmp_pbDst[yy_32 - 800];
						yy_32 += 2;
					}
					while ( yy_32 != 32 );
					return;
				}
				tmp_pbDst += xx_32;
				xx_32 -= 2;
			}
			break;
		case 4:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					gpDrawMask -= 16;
					yy_32 = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						y32_temp = yy_32;
						left_shift = *gpDrawMask;
						i = 32;
						do
						{
							if ( left_shift & 0x80000000 )
								*tmp_pbDst = 0;
							left_shift *= 2;
							++tmp_pbDst;
							--i;
						}
						while ( i );
						tmp_pbDst -= 800;
						--gpDrawMask;
						yy_32 = y32_temp - 1;
					}
					while ( y32_temp != 1 );
					return;
				}
				xx_32 -= 2;
			}
			break;
		default:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					gpDrawMask -= 16;
					yy_32 = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						y32_temp = yy_32;
						left_shift = *gpDrawMask;
						i = 32;
						do
						{
							if ( left_shift & 0x80000000 )
								*tmp_pbDst = 0;
							left_shift *= 2;
							++tmp_pbDst;
							--i;
						}
						while ( i );
						tmp_pbDst -= 800;
						--gpDrawMask;
						yy_32 = y32_temp - 1;
					}
					while ( y32_temp != 1 );
					return;
				}
				tmp_pbDst += xx_32;
				xx_32 -= 2;
			}
			break;
	}
}

void __fastcall drawUpperScreen(unsigned char *pbDst)
{
	char junk_v2; // al MAPDST
	unsigned char *tmp_pbDst; // edi MAPDST
	char *l_tbl; // ebx
	unsigned char *pdung_cels; // esi MAPDST
	short cel_type_16; // ax MAPDST
	unsigned int cel_type_16_tmp; // eax
	unsigned int cel_type_32; // eax
	char l_index; // edx MAPDST
	char base_4; // cl MAPDST
	unsigned char dstbyte; // ch MAPDST
	char x_minus; // cl MAPDST
	char y_minus; // cl
	int temp32; // eax MAPDST
	signed int xx_32; // ebp MAPDST
	signed int yy_32; // edx MAPDST
	unsigned int dung_and80; // eax MAPDST
	unsigned int chk_sh_and; // ecx MAPDST
	unsigned char temp8; // al MAPDST
	unsigned int n_draw_shift; // ecx MAPDST
	short temp16; // ax MAPDST
	signed int i; // edx MAPDST
	signed int j; // ecx MAPDST
	int y32_temp; // [esp-14h] [ebp-18h] MAPDST

	l_index = cel_transparency_active;
	if ( cel_transparency_active )
	{
		if ( !arch_draw_type )
		{
			drawTopArchesUpperScreen(pbDst);
			return;
		}
		if ( arch_draw_type == 1 )
		{
			junk_v2 = block_lvid[level_piece_id];
			if ( junk_v2 == 1 || junk_v2 == 3 )
			{
				drawBottomArchesUpperScreen(pbDst, &LeftMask[31]);
				return;
			}
		}
		if ( arch_draw_type == 2 )
		{
			junk_v2 = block_lvid[level_piece_id];
			if ( junk_v2 == 2 || junk_v2 == 3 )
			{
				drawBottomArchesUpperScreen(pbDst, &RightMask[31]);
				return;
			}
		}
	}
	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	tmp_pbDst = pbDst;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16_tmp = level_cel_block;
		_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
		cel_type_16 = ((cel_type_16_tmp >> 4) & 7) + 8;
LABEL_22:
		switch ( cel_type_16 )
		{
			case 8:
				i = 32;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						break;
					j = 8;
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
						--j;
					}
					while ( j );
					tmp_pbDst -= 800;
					--i;
				}
				while ( i );
				break;
			case 9:
				xx_32 = 32;
				do
				{
					yy_32 = 32;
					do
					{
						while ( 1 )
						{
							dung_and80 = *pdung_cels++;
							if ( (dung_and80 & 0x80u) == 0 )
								break;
							_LOBYTE(dung_and80) = -(char)dung_and80;
							tmp_pbDst += dung_and80;
							yy_32 -= dung_and80;
							if ( !yy_32 )
								goto LABEL_133;
						}
						yy_32 -= dung_and80;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							return;
						chk_sh_and = dung_and80 >> 1;
						if ( dung_and80 & 1 )
						{
							temp8 = *pdung_cels++;
							*tmp_pbDst++ = temp8;
							if ( !chk_sh_and )
								continue;
						}
						temp8 = chk_sh_and & 1;
						n_draw_shift = chk_sh_and >> 1;
						if ( temp8 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 2;
							*(_WORD *)tmp_pbDst = temp16;
							tmp_pbDst += 2;
							if ( !n_draw_shift )
								continue;
						}
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*(_DWORD *)tmp_pbDst = temp32;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
					while ( yy_32 );
LABEL_133:
					tmp_pbDst -= 800;
					--xx_32;
				}
				while ( xx_32 );
				break;
			case 10:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					tmp_pbDst += xx_32;
					n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
					if ( (32 - xx_32) & 2 )
					{
						temp16 = *((_WORD *)pdung_cels + 1);
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*(_DWORD *)tmp_pbDst = temp32;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						yy_32 = 2;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							tmp_pbDst += yy_32;
							n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
							if ( (32 - yy_32) & 2 )
							{
								temp16 = *((_WORD *)pdung_cels + 1);
								pdung_cels += 4;
								*(_WORD *)tmp_pbDst = temp16;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									*(_DWORD *)tmp_pbDst = temp32;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
							tmp_pbDst -= 800;
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
				}
				break;
			case 11:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						yy_32 = 2;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							for ( n_draw_shift = (unsigned int)(32 - yy_32) >> 2; n_draw_shift; --n_draw_shift )
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
							}
							if ( (32 - (_BYTE)yy_32) & 2 )
							{
								temp16 = *(_WORD *)pdung_cels;
								pdung_cels += 4;
								*(_WORD *)tmp_pbDst = temp16;
								tmp_pbDst += 2;
							}
							tmp_pbDst = &tmp_pbDst[yy_32 - 800];
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
				}
				break;
			case 12:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					tmp_pbDst += xx_32;
					n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
					if ( (32 - xx_32) & 2 )
					{
						temp16 = *((_WORD *)pdung_cels + 1);
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*(_DWORD *)tmp_pbDst = temp32;
							tmp_pbDst += 4;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						i = 16;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
							tmp_pbDst -= 800;
							--i;
						}
						while ( i );
						return;
					}
				}
				break;
			default:
				xx_32 = 30;
				while ( (unsigned int)tmp_pbDst >= screen_buf_end )
				{
					for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
					if ( xx_32 < 0 )
					{
						i = 16;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								break;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
							tmp_pbDst -= 800;
							--i;
						}
						while ( i );
						return;
					}
				}
				break;
		}
		return;
	}
	if ( (_BYTE)light_table_index != lightmax )
	{
		if ( !(level_cel_block & 0x8000) )
		{
			pdung_cels = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			l_tbl = &pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned short)level_cel_block >> 12;
			switch ( cel_type_16 )
			{
				case 0:
					l_index = 32;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						base_4 = 32;
						y32_temp = l_index;
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = temp32;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							temp32 = __ROR4__(temp32, 16);
							*tmp_pbDst = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = temp32;
							tmp_pbDst[1] = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							tmp_pbDst[2] = dstbyte;
							tmp_pbDst[3] = l_tbl[l_index];
							tmp_pbDst += 4;
							base_4 -= 4;
						}
						while ( base_4 >= 4 );
						tmp_pbDst -= 800;
						l_index = y32_temp - 1;
					}
					while ( y32_temp != 1 );
					break;
				case 1:
					xx_32 = 32;
					do
					{
						yy_32 = 32;
						do
						{
							while ( 1 )
							{
								dung_and80 = *pdung_cels++;
								if ( (dung_and80 & 0x80u) == 0 )
									break;
								_LOBYTE(dung_and80) = -(char)dung_and80;
								tmp_pbDst += dung_and80;
								yy_32 -= dung_and80;
								if ( !yy_32 )
									goto LABEL_58;
							}
							l_index = yy_32 - dung_and80;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
								return;
							base_4 = dung_and80;
							for ( y32_temp = l_index; base_4 >= 4; base_4 -= 4 )
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								l_index = temp32;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								temp32 = __ROR4__(temp32, 16);
								*tmp_pbDst = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = temp32;
								tmp_pbDst[1] = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								tmp_pbDst[2] = dstbyte;
								tmp_pbDst[3] = l_tbl[l_index];
								tmp_pbDst += 4;
							}
							if ( base_4 >= 2 )
							{
								l_index = *pdung_cels;
								*tmp_pbDst = l_tbl[l_index];
								l_index = pdung_cels[1];
								tmp_pbDst[1] = l_tbl[l_index];
								pdung_cels += 2;
								tmp_pbDst += 2;
							}
							if ( base_4 & 1 )
							{
								l_index = *pdung_cels++;
								*tmp_pbDst++ = l_tbl[l_index];
							}
							yy_32 = y32_temp;
						}
						while ( y32_temp );
LABEL_58:
						tmp_pbDst -= 800;
						--xx_32;
					}
					while ( xx_32 );
					break;
				case 2:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						l_index = (32 - (_BYTE)xx_32) & 2;
						pdung_cels += l_index;
						if ( (char)(32 - xx_32) >= 4 )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								l_index = temp32;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								temp32 = __ROR4__(temp32, 16);
								*tmp_pbDst = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = temp32;
								tmp_pbDst[1] = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								tmp_pbDst[2] = dstbyte;
								tmp_pbDst[3] = l_tbl[l_index];
								tmp_pbDst += 4;
								x_minus -= 4;
							}
							while ( x_minus >= 4 );
						}
						if ( x_minus >= 2 )
						{
							l_index = *pdung_cels;
							*tmp_pbDst = l_tbl[l_index];
							l_index = pdung_cels[1];
							tmp_pbDst[1] = l_tbl[l_index];
							pdung_cels += 2;
							tmp_pbDst += 2;
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 2;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								tmp_pbDst += yy_32;
								y_minus = 32 - yy_32;
								l_index = (32 - (_BYTE)yy_32) & 2;
								pdung_cels += l_index;
								if ( (char)(32 - yy_32) >= 4 )
								{
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										temp32 = __ROR4__(temp32, 16);
										*tmp_pbDst = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = temp32;
										tmp_pbDst[1] = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst[2] = dstbyte;
										tmp_pbDst[3] = l_tbl[l_index];
										tmp_pbDst += 4;
										y_minus -= 4;
									}
									while ( y_minus >= 4 );
								}
								if ( y_minus >= 2 )
								{
									l_index = *pdung_cels;
									*tmp_pbDst = l_tbl[l_index];
									l_index = pdung_cels[1];
									tmp_pbDst[1] = l_tbl[l_index];
									pdung_cels += 2;
									tmp_pbDst += 2;
								}
								tmp_pbDst -= 800;
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
					}
					break;
				case 3:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						for ( base_4 = 32 - xx_32; base_4 >= 4; base_4 -= 4 )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = temp32;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							temp32 = __ROR4__(temp32, 16);
							*tmp_pbDst = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = temp32;
							tmp_pbDst[1] = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							tmp_pbDst[2] = dstbyte;
							tmp_pbDst[3] = l_tbl[l_index];
							tmp_pbDst += 4;
						}
						if ( base_4 >= 2 )
						{
							l_index = *pdung_cels;
							*tmp_pbDst = l_tbl[l_index];
							l_index = pdung_cels[1];
							tmp_pbDst[1] = l_tbl[l_index];
							pdung_cels += 2;
							tmp_pbDst += 2;
						}
						l_index = (unsigned char)pdung_cels & 2;
						pdung_cels += l_index;
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 2;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								for ( base_4 = 32 - yy_32; base_4 >= 4; base_4 -= 4 )
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									dstbyte = l_tbl[l_index];
									l_index = BYTE1(temp32);
									temp32 = __ROR4__(temp32, 16);
									*tmp_pbDst = dstbyte;
									dstbyte = l_tbl[l_index];
									l_index = temp32;
									tmp_pbDst[1] = dstbyte;
									dstbyte = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst[2] = dstbyte;
									tmp_pbDst[3] = l_tbl[l_index];
									tmp_pbDst += 4;
								}
								if ( base_4 >= 2 )
								{
									l_index = *pdung_cels;
									*tmp_pbDst = l_tbl[l_index];
									l_index = pdung_cels[1];
									tmp_pbDst[1] = l_tbl[l_index];
									pdung_cels += 2;
									tmp_pbDst += 2;
								}
								l_index = (unsigned char)pdung_cels & 2;
								pdung_cels += l_index;
								tmp_pbDst = &tmp_pbDst[yy_32 - 800];
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
					}
					break;
				case 4:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						l_index = (32 - (_BYTE)xx_32) & 2;
						pdung_cels += l_index;
						if ( (char)(32 - xx_32) >= 4 )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								l_index = temp32;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								temp32 = __ROR4__(temp32, 16);
								*tmp_pbDst = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = temp32;
								tmp_pbDst[1] = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								tmp_pbDst[2] = dstbyte;
								tmp_pbDst[3] = l_tbl[l_index];
								tmp_pbDst += 4;
								x_minus -= 4;
							}
							while ( x_minus >= 4 );
						}
						if ( x_minus >= 2 )
						{
							l_index = *pdung_cels;
							*tmp_pbDst = l_tbl[l_index];
							l_index = pdung_cels[1];
							tmp_pbDst[1] = l_tbl[l_index];
							pdung_cels += 2;
							tmp_pbDst += 2;
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								base_4 = 32;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									dstbyte = l_tbl[l_index];
									l_index = BYTE1(temp32);
									temp32 = __ROR4__(temp32, 16);
									*tmp_pbDst = dstbyte;
									dstbyte = l_tbl[l_index];
									l_index = temp32;
									tmp_pbDst[1] = dstbyte;
									dstbyte = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst[2] = dstbyte;
									tmp_pbDst[3] = l_tbl[l_index];
									tmp_pbDst += 4;
									base_4 -= 4;
								}
								while ( base_4 >= 4 );
								tmp_pbDst -= 800;
								--yy_32;
							}
							while ( yy_32 );
							return;
						}
					}
					break;
				default:
					xx_32 = 30;
					while ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						for ( base_4 = 32 - xx_32; base_4 >= 4; base_4 -= 4 )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = temp32;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							temp32 = __ROR4__(temp32, 16);
							*tmp_pbDst = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = temp32;
							tmp_pbDst[1] = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							tmp_pbDst[2] = dstbyte;
							tmp_pbDst[3] = l_tbl[l_index];
							tmp_pbDst += 4;
						}
						if ( base_4 >= 2 )
						{
							l_index = *pdung_cels;
							*tmp_pbDst = l_tbl[l_index];
							l_index = pdung_cels[1];
							tmp_pbDst[1] = l_tbl[l_index];
							pdung_cels += 2;
							tmp_pbDst += 2;
						}
						l_index = (unsigned char)pdung_cels & 2;
						pdung_cels += l_index;
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
						if ( xx_32 < 0 )
						{
							yy_32 = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
									break;
								base_4 = 32;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									dstbyte = l_tbl[l_index];
									l_index = BYTE1(temp32);
									temp32 = __ROR4__(temp32, 16);
									*tmp_pbDst = dstbyte;
									dstbyte = l_tbl[l_index];
									l_index = temp32;
									tmp_pbDst[1] = dstbyte;
									dstbyte = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst[2] = dstbyte;
									tmp_pbDst[3] = l_tbl[l_index];
									tmp_pbDst += 4;
									base_4 -= 4;
								}
								while ( base_4 >= 4 );
								tmp_pbDst -= 800;
								--yy_32;
							}
							while ( yy_32 );
							return;
						}
					}
					break;
			}
			return;
		}
		pdung_cels = (unsigned char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned short)level_cel_block >> 12;
		goto LABEL_22;
	}
	if ( level_cel_block & 0x8000 )
		level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
						+ (unsigned short)(level_cel_block & 0xF000);
	pdung_cels = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
	cel_type_32 = ((unsigned int)level_cel_block >> 12) & 7;
	switch ( (_WORD)cel_type_32 )
	{
		case 0:
			i = 32;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
					break;
				j = 8;
				do
				{
					*(_DWORD *)tmp_pbDst = 0;
					tmp_pbDst += 4;
					--j;
				}
				while ( j );
				tmp_pbDst -= 800;
				--i;
			}
			while ( i );
			break;
		case 1:
			xx_32 = 32;
			do
			{
				yy_32 = 32;
				do
				{
					while ( 1 )
					{
						dung_and80 = *pdung_cels++;
						if ( (dung_and80 & 0x80u) == 0 )
							break;
						_LOBYTE(dung_and80) = -(char)dung_and80;
						tmp_pbDst += dung_and80;
						yy_32 -= dung_and80;
						if ( !yy_32 )
							goto LABEL_205;
					}
					yy_32 -= dung_and80;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
						return;
					pdung_cels += dung_and80;
					chk_sh_and = dung_and80 >> 1;
					if ( dung_and80 & 1 )
					{
						*tmp_pbDst++ = 0;
						if ( !chk_sh_and )
							continue;
					}
					temp8 = chk_sh_and & 1;
					n_draw_shift = dung_and80 >> 2;
					if ( temp8 )
					{
						*(_WORD *)tmp_pbDst = 0;
						tmp_pbDst += 2;
						if ( !n_draw_shift )
							continue;
					}
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				while ( yy_32 );
LABEL_205:
				tmp_pbDst -= 800;
				--xx_32;
			}
			while ( xx_32 );
			break;
		case 2:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					yy_32 = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						tmp_pbDst += yy_32;
						n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
						if ( (32 - yy_32) & 2 )
						{
							*(_WORD *)tmp_pbDst = 0;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						yy_32 += 2;
					}
					while ( yy_32 != 32 );
					return;
				}
				xx_32 -= 2;
			}
			break;
		case 3:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					yy_32 = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
						if ( (32 - yy_32) & 2 )
						{
							*(_WORD *)tmp_pbDst = 0;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst = &tmp_pbDst[yy_32 - 800];
						yy_32 += 2;
					}
					while ( yy_32 != 32 );
					return;
				}
				tmp_pbDst += xx_32;
				xx_32 -= 2;
			}
			break;
		case 4:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						j = 8;
						do
						{
							*(_DWORD *)tmp_pbDst = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					return;
				}
				xx_32 -= 2;
			}
			break;
		default:
			xx_32 = 30;
			while ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					*(_WORD *)tmp_pbDst = 0;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						*(_DWORD *)tmp_pbDst = 0;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				if ( !xx_32 )
				{
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
							break;
						j = 8;
						do
						{
							*(_DWORD *)tmp_pbDst = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					return;
				}
				tmp_pbDst += xx_32;
				xx_32 -= 2;
			}
			break;
	}
}

void __fastcall drawTopArchesLowerScreen(unsigned char *pbDst)
{
	char l_index; // edx MAPDST
	char *tmp_pbDst; // edi MAPDST
	char *l_tbl; // ebx
	int pdung_cels; // esi MAPDST
	short cel_type_16; // ax MAPDST
	unsigned int cel_type_16_tmp; // eax MAPDST
	int cel_type_32; // eax
	unsigned int temp32; // eax MAPDST
	unsigned char junk_ror; // cf
	signed int tile_42_45; // eax MAPDST
	unsigned int world_tbl; // ecx MAPDST
	int world_192; // eax MAPDST
	char *junk_v155; // esi
	char temp8; // al MAPDST
	short temp16; // ax MAPDST
	unsigned int dung_and80; // eax MAPDST
	unsigned int chk_sh_and; // ecx MAPDST
	int xx_32; // edx MAPDST
	unsigned int x_minus; // ecx MAPDST
	unsigned int n_draw_shift; // ecx MAPDST
	char *tmp_dst; // edi MAPDST
	int yy_32; // edx MAPDST
	unsigned int y_minus; // ecx MAPDST
	signed int i; // edx MAPDST
	signed int j; // ecx MAPDST
	int x32_temp; // [esp-14h] [ebp-18h] MAPDST

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	tmp_pbDst = (char *)pbDst;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (int)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16_tmp = level_cel_block;
		_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
		cel_type_16 = ((cel_type_16_tmp >> 4) & 7) + 8;
		goto LABEL_11;
	}
	if ( (_BYTE)light_table_index == lightmax )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (int)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16_tmp = level_cel_block;
		_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
		cel_type_32 = (cel_type_16_tmp >> 4) & 7;
		switch ( (_WORD)cel_type_32 )
		{
			case 0:
				i = 16;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					--i;
				}
				while ( i );
				break;
			case 1:
				WorldBoolFlag = (unsigned char)pbDst & 1;
				xx_32 = 32;
LABEL_412:
				x32_temp = xx_32;
				yy_32 = 32;
				while ( 1 )
				{
					while ( 1 )
					{
						dung_and80 = *(unsigned char *)pdung_cels++;
						if ( (dung_and80 & 0x80u) == 0 )
							break;
						_LOBYTE(dung_and80) = -(char)dung_and80;
						tmp_pbDst += dung_and80;
						yy_32 -= dung_and80;
						if ( !yy_32 )
						{
LABEL_433:
							WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
							tmp_pbDst -= 800;
							xx_32 = x32_temp - 1;
							if ( x32_temp == 1 )
								return;
							goto LABEL_412;
						}
					}
					yy_32 -= dung_and80;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						pdung_cels += dung_and80;
						if ( ((unsigned char)tmp_pbDst & 1) == WorldBoolFlag )
						{
							chk_sh_and = dung_and80 >> 1;
							if ( !(dung_and80 & 1) )
								goto LABEL_420;
							++tmp_pbDst;
							if ( chk_sh_and )
							{
LABEL_427:
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_sh_and & 1 )
								{
									*tmp_pbDst = 0;
									tmp_pbDst += 2;
								}
								if ( n_draw_shift )
								{
									do
									{
										*tmp_pbDst = 0;
										tmp_pbDst[2] = 0;
										tmp_pbDst += 4;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
								goto LABEL_430;
							}
						}
						else
						{
							chk_sh_and = dung_and80 >> 1;
							if ( !(dung_and80 & 1) )
								goto LABEL_427;
							*tmp_pbDst++ = 0;
							if ( chk_sh_and )
							{
LABEL_420:
								n_draw_shift = chk_sh_and >> 1;
								if ( chk_sh_and & 1 )
								{
									tmp_dst = tmp_pbDst + 1;
									*tmp_dst = 0;
									tmp_pbDst = tmp_dst + 1;
								}
								if ( n_draw_shift )
								{
									do
									{
										tmp_pbDst[1] = 0;
										tmp_pbDst[3] = 0;
										tmp_pbDst += 4;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
								goto LABEL_430;
							}
						}
					}
					else
					{
						pdung_cels += dung_and80;
						tmp_pbDst += dung_and80;
					}
LABEL_430:
					if ( !yy_32 )
						goto LABEL_433;
				}
				break;
			case 2:
				WorldBoolFlag = 0;
				for ( xx_32 = 30; ; xx_32 -= 2 )
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = 0;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									tmp_pbDst[1] = 0;
									tmp_pbDst[3] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								*tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*tmp_pbDst = 0;
									tmp_pbDst[2] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels = pdung_cels + 32 - xx_32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					if ( !xx_32 )
						break;
				}
				yy_32 = 2;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						tmp_pbDst += yy_32;
						y_minus = 32 - yy_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = y_minus >> 2;
							if ( y_minus & 2 )
							{
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = 0;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									tmp_pbDst[1] = 0;
									tmp_pbDst[3] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = y_minus >> 2;
							if ( y_minus & 2 )
							{
								*tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*tmp_pbDst = 0;
									tmp_pbDst[2] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels = pdung_cels + 32 - yy_32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					yy_32 += 2;
				}
				while ( yy_32 != 32 );
				break;
			case 3:
				WorldBoolFlag = 0;
				for ( xx_32 = 30; ; xx_32 -= 2 )
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = 0;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									tmp_pbDst[1] = 0;
									tmp_pbDst[3] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								*tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*tmp_pbDst = 0;
									tmp_pbDst[2] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels = pdung_cels + 32 - xx_32;
						tmp_pbDst = &tmp_pbDst[-xx_32 + 32];
					}
					tmp_pbDst -= 800;
					if ( !xx_32 )
						break;
					tmp_pbDst += xx_32;
				}
				yy_32 = 2;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						y_minus = 32 - yy_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = y_minus >> 2;
							if ( y_minus & 2 )
							{
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = 0;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									tmp_pbDst[1] = 0;
									tmp_pbDst[3] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = y_minus >> 2;
							if ( y_minus & 2 )
							{
								*tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*tmp_pbDst = 0;
									tmp_pbDst[2] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels = pdung_cels + 32 - yy_32;
						tmp_pbDst = &tmp_pbDst[-yy_32 + 32];
					}
					tmp_pbDst = &tmp_pbDst[yy_32 - 800];
					yy_32 += 2;
				}
				while ( yy_32 != 32 );
				break;
			case 4:
				WorldBoolFlag = 0;
				for ( xx_32 = 30; ; xx_32 -= 2 )
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = 0;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									tmp_pbDst[1] = 0;
									tmp_pbDst[3] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								*tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*tmp_pbDst = 0;
									tmp_pbDst[2] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels = pdung_cels + 32 - xx_32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					if ( !xx_32 )
						break;
				}
				i = 8;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					--i;
				}
				while ( i );
				break;
			default:
				WorldBoolFlag = 0;
				for ( xx_32 = 30; ; xx_32 -= 2 )
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						x_minus = 32 - xx_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = 0;
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									tmp_pbDst[1] = 0;
									tmp_pbDst[3] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = x_minus >> 2;
							if ( x_minus & 2 )
							{
								*tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*tmp_pbDst = 0;
									tmp_pbDst[2] = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels = pdung_cels + 32 - xx_32;
						tmp_pbDst = &tmp_pbDst[-xx_32 + 32];
					}
					tmp_pbDst -= 800;
					if ( !xx_32 )
						break;
					tmp_pbDst += xx_32;
				}
				i = 8;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							tmp_pbDst[1] = 0;
							tmp_pbDst[3] = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							*tmp_pbDst = 0;
							tmp_pbDst[2] = 0;
							tmp_pbDst += 4;
							--j;
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					--i;
				}
				while ( i );
				break;
		}
		return;
	}
	if ( !(level_cel_block & 0x8000) )
	{
		pdung_cels = (int)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		l_tbl = &pLightTbl[256 * light_table_index];
		cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
		switch ( cel_type_16 )
		{
			case 0:
				i = 16;
				do
				{
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = BYTE1(temp32);
							temp32 >>= 16;
							tmp_pbDst[1] = l_tbl[l_index];
							l_index = BYTE1(temp32);
							tmp_pbDst += 4;
							--j;
							*(tmp_pbDst - 1) = l_tbl[l_index];
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						j = 8;
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = temp32;
							*tmp_pbDst = l_tbl[l_index];
							l_index = BYTE2(temp32);
							tmp_pbDst += 4;
							--j;
							*(tmp_pbDst - 2) = l_tbl[l_index];
						}
						while ( j );
					}
					else
					{
						pdung_cels += 32;
						tmp_pbDst += 32;
					}
					tmp_pbDst -= 800;
					--i;
				}
				while ( i );
				break;
			case 1:
				WorldBoolFlag = (unsigned char)pbDst & 1;
				xx_32 = 32;
				do
				{
					x32_temp = xx_32;
					yy_32 = 32;
					do
					{
						while ( 1 )
						{
							dung_and80 = *(unsigned char *)pdung_cels++;
							if ( (dung_and80 & 0x80u) == 0 )
								break;
							_LOBYTE(dung_and80) = -(char)dung_and80;
							tmp_pbDst += dung_and80;
							yy_32 -= dung_and80;
							if ( !yy_32 )
								goto LABEL_69;
						}
						yy_32 -= dung_and80;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							if ( ((unsigned char)tmp_pbDst & 1) == WorldBoolFlag )
							{
								chk_sh_and = dung_and80 >> 1;
								if ( dung_and80 & 1 )
								{
									++pdung_cels;
									++tmp_pbDst;
									junk_ror = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									junk_ror = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)(pdung_cels + 1);
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
							}
							else
							{
								chk_sh_and = dung_and80 >> 1;
								if ( dung_and80 & 1 )
								{
									l_index = *(_BYTE *)pdung_cels++;
									*tmp_pbDst++ = l_tbl[l_index];
									junk_ror = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)(pdung_cels + 1);
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									junk_ror = chk_sh_and & 1;
									n_draw_shift = dung_and80 >> 2;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
							}
						}
						else
						{
							pdung_cels += dung_and80;
							tmp_pbDst += dung_and80;
						}
					}
					while ( yy_32 );
LABEL_69:
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					tmp_pbDst -= 800;
					xx_32 = x32_temp - 1;
				}
				while ( x32_temp != 1 );
				break;
			case 2:
				WorldBoolFlag = 0;
				xx_32 = 30;
				if ( (unsigned int)pbDst >= screen_buf_end )
				{
					tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
					if ( tile_42_45 > 45 )
					{
						tmp_pbDst = (char *)(pbDst - 12288);
						pdung_cels += 288;
LABEL_98:
						yy_32 = 2;
						if ( (unsigned int)tmp_pbDst >= screen_buf_end )
						{
							tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
							if ( tile_42_45 > 42 )
								return;
							world_tbl = WorldTbl3x16[tile_42_45];
							pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
							world_192 = 192 * world_tbl;
							world_tbl >>= 1;
							tmp_pbDst -= world_192;
							yy_32 = world_tbl + 2;
							WorldBoolFlag += world_tbl >> 1;
						}
						do
						{
							tmp_pbDst += yy_32;
							y_minus = 32 - yy_32;
							WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
							if ( WorldBoolFlag )
							{
								l_index = y_minus & 2;
								pdung_cels += l_index;
								junk_ror = y_minus & 1;
								chk_sh_and = y_minus >> 1;
								if ( junk_ror )
								{
									++pdung_cels;
									++tmp_pbDst;
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)(pdung_cels + 1);
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
							}
							else
							{
								l_index = y_minus & 2;
								pdung_cels += l_index;
								junk_ror = y_minus & 1;
								chk_sh_and = y_minus >> 1;
								if ( junk_ror )
								{
									l_index = *(_BYTE *)pdung_cels++;
									*tmp_pbDst++ = l_tbl[l_index];
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)(pdung_cels + 1);
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
							}
							tmp_pbDst -= 800;
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
					world_tbl = WorldTbl3x16[tile_42_45];
					pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
					world_192 = 192 * world_tbl;
					world_tbl >>= 1;
					tmp_pbDst -= world_192;
					xx_32 = 30 - world_tbl;
					WorldBoolFlag += world_tbl >> 1;
				}
				do
				{
					tmp_pbDst += xx_32;
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						l_index = x_minus & 2;
						pdung_cels += l_index;
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							++pdung_cels;
							++tmp_pbDst;
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						l_index = x_minus & 2;
						pdung_cels += l_index;
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							l_index = *(_BYTE *)pdung_cels++;
							*tmp_pbDst++ = l_tbl[l_index];
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_98;
			case 3:
				WorldBoolFlag = 0;
				xx_32 = 30;
				if ( (unsigned int)pbDst >= screen_buf_end )
				{
					tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
					if ( tile_42_45 > 45 )
					{
						tmp_pbDst = (char *)(pbDst - 12288);
						pdung_cels += 288;
LABEL_154:
						yy_32 = 2;
						if ( (unsigned int)tmp_pbDst >= screen_buf_end )
						{
							tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
							if ( tile_42_45 > 42 )
								return;
							world_tbl = WorldTbl3x16[tile_42_45];
							pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
							world_192 = 192 * world_tbl;
							world_tbl >>= 1;
							tmp_pbDst -= world_192;
							yy_32 = world_tbl + 2;
							WorldBoolFlag += world_tbl >> 1;
						}
						do
						{
							y_minus = 32 - yy_32;
							WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
							if ( WorldBoolFlag )
							{
								junk_ror = y_minus & 1;
								chk_sh_and = y_minus >> 1;
								if ( junk_ror )
								{
									++pdung_cels;
									++tmp_pbDst;
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)(pdung_cels + 1);
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								l_index = pdung_cels & 2;
								pdung_cels += l_index;
							}
							else
							{
								junk_ror = y_minus & 1;
								chk_sh_and = y_minus >> 1;
								if ( junk_ror )
								{
									l_index = *(_BYTE *)pdung_cels++;
									*tmp_pbDst++ = l_tbl[l_index];
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)(pdung_cels + 1);
										pdung_cels += 2;
										tmp_pbDst[1] = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = BYTE1(temp32);
											temp32 >>= 16;
											tmp_pbDst[1] = l_tbl[l_index];
											l_index = BYTE1(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 1) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								else
								{
									junk_ror = chk_sh_and & 1;
									n_draw_shift = chk_sh_and >> 1;
									if ( junk_ror )
									{
										l_index = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = l_tbl[l_index];
										tmp_pbDst += 2;
									}
									if ( (_BYTE)n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											l_index = temp32;
											*tmp_pbDst = l_tbl[l_index];
											l_index = BYTE2(temp32);
											tmp_pbDst += 4;
											--n_draw_shift;
											*(tmp_pbDst - 2) = l_tbl[l_index];
										}
										while ( n_draw_shift );
									}
								}
								l_index = pdung_cels & 2;
								pdung_cels += l_index;
							}
							tmp_pbDst = &tmp_pbDst[yy_32 - 800];
							yy_32 += 2;
						}
						while ( yy_32 != 32 );
						return;
					}
					world_tbl = WorldTbl3x16[tile_42_45];
					pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
					world_192 = 192 * world_tbl;
					world_tbl >>= 1;
					tmp_pbDst -= world_192;
					xx_32 = 30 - world_tbl;
					WorldBoolFlag += world_tbl >> 1;
				}
				do
				{
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							++pdung_cels;
							++tmp_pbDst;
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						l_index = pdung_cels & 2;
						pdung_cels += l_index;
					}
					else
					{
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							l_index = *(_BYTE *)pdung_cels++;
							*tmp_pbDst++ = l_tbl[l_index];
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						l_index = pdung_cels & 2;
						pdung_cels += l_index;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_154;
			case 4:
				WorldBoolFlag = 0;
				xx_32 = 30;
				if ( (unsigned int)pbDst >= screen_buf_end )
				{
					tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
					if ( tile_42_45 > 45 )
					{
						tmp_pbDst = (char *)(pbDst - 12288);
						pdung_cels += 288;
LABEL_210:
						i = 8;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
							{
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( j );
							}
							else
							{
								pdung_cels += 32;
								tmp_pbDst += 32;
							}
							tmp_pbDst -= 800;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
							{
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( j );
							}
							else
							{
								pdung_cels += 32;
								tmp_pbDst += 32;
							}
							tmp_pbDst -= 800;
							--i;
						}
						while ( i );
						return;
					}
					world_tbl = WorldTbl3x16[tile_42_45];
					pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
					world_192 = 192 * world_tbl;
					world_tbl >>= 1;
					tmp_pbDst -= world_192;
					xx_32 = 30 - world_tbl;
					WorldBoolFlag += world_tbl >> 1;
				}
				do
				{
					tmp_pbDst += xx_32;
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						l_index = x_minus & 2;
						pdung_cels += l_index;
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							++pdung_cels;
							++tmp_pbDst;
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						l_index = x_minus & 2;
						pdung_cels += l_index;
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							l_index = *(_BYTE *)pdung_cels++;
							*tmp_pbDst++ = l_tbl[l_index];
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
					}
					tmp_pbDst -= 800;
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_210;
			default:
				WorldBoolFlag = 0;
				xx_32 = 30;
				if ( (unsigned int)pbDst >= screen_buf_end )
				{
					tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
					if ( tile_42_45 > 45 )
					{
						tmp_pbDst = (char *)(pbDst - 12288);
						pdung_cels += 288;
LABEL_249:
						i = 8;
						do
						{
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
							{
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( j );
							}
							else
							{
								pdung_cels += 32;
								tmp_pbDst += 32;
							}
							tmp_pbDst -= 800;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
							{
								j = 8;
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--j;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( j );
							}
							else
							{
								pdung_cels += 32;
								tmp_pbDst += 32;
							}
							tmp_pbDst -= 800;
							--i;
						}
						while ( i );
						return;
					}
					world_tbl = WorldTbl3x16[tile_42_45];
					pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
					world_192 = 192 * world_tbl;
					world_tbl >>= 1;
					tmp_pbDst -= world_192;
					xx_32 = 30 - world_tbl;
					WorldBoolFlag += world_tbl >> 1;
				}
				do
				{
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							++pdung_cels;
							++tmp_pbDst;
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						l_index = pdung_cels & 2;
						pdung_cels += l_index;
					}
					else
					{
						junk_ror = x_minus & 1;
						chk_sh_and = x_minus >> 1;
						if ( junk_ror )
						{
							l_index = *(_BYTE *)pdung_cels++;
							*tmp_pbDst++ = l_tbl[l_index];
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)(pdung_cels + 1);
								pdung_cels += 2;
								tmp_pbDst[1] = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = BYTE1(temp32);
									temp32 >>= 16;
									tmp_pbDst[1] = l_tbl[l_index];
									l_index = BYTE1(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 1) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							junk_ror = chk_sh_and & 1;
							n_draw_shift = chk_sh_and >> 1;
							if ( junk_ror )
							{
								l_index = *(_BYTE *)pdung_cels;
								pdung_cels += 2;
								*tmp_pbDst = l_tbl[l_index];
								tmp_pbDst += 2;
							}
							if ( (_BYTE)n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									l_index = temp32;
									*tmp_pbDst = l_tbl[l_index];
									l_index = BYTE2(temp32);
									tmp_pbDst += 4;
									--n_draw_shift;
									*(tmp_pbDst - 2) = l_tbl[l_index];
								}
								while ( n_draw_shift );
							}
						}
						l_index = pdung_cels & 2;
						pdung_cels += l_index;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_249;
		}
		return;
	}
	pdung_cels = (int)pSpeedCels + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
	cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
LABEL_11:
	switch ( cel_type_16 )
	{
		case 8:
			i = 16;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
				{
					j = 8;
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						temp32 = __ROR4__(temp32, 8);
						*tmp_dst = temp32;
						tmp_dst += 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 1;
						--j;
					}
					while ( j );
				}
				else
				{
					pdung_cels += 32;
					tmp_pbDst += 32;
				}
				tmp_pbDst -= 800;
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
				{
					j = 8;
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*tmp_pbDst = temp32;
						tmp_dst = tmp_pbDst + 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 2;
						--j;
					}
					while ( j );
				}
				else
				{
					pdung_cels += 32;
					tmp_pbDst += 32;
				}
				tmp_pbDst -= 800;
				--i;
			}
			while ( i );
			break;
		case 9:
			WorldBoolFlag = (unsigned char)pbDst & 1;
			xx_32 = 32;
			while ( 1 )
			{
				x32_temp = xx_32;
				yy_32 = 32;
				do
				{
					while ( 1 )
					{
						dung_and80 = *(unsigned char *)pdung_cels++;
						if ( (dung_and80 & 0x80u) != 0 )
							break;
						yy_32 -= dung_and80;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							if ( ((unsigned char)tmp_pbDst & 1) == WorldBoolFlag )
							{
								chk_sh_and = dung_and80 >> 1;
								if ( !(dung_and80 & 1) )
									goto LABEL_280;
								++pdung_cels;
								++tmp_pbDst;
								if ( chk_sh_and )
								{
LABEL_287:
									n_draw_shift = chk_sh_and >> 1;
									if ( chk_sh_and & 1 )
									{
										temp8 = *(_BYTE *)pdung_cels;
										pdung_cels += 2;
										*tmp_pbDst = temp8;
										tmp_pbDst += 2;
									}
									if ( n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											*tmp_pbDst = temp32;
											tmp_dst = tmp_pbDst + 2;
											*tmp_dst = __ROR4__(temp32, 16);
											tmp_pbDst = tmp_dst + 2;
											--n_draw_shift;
										}
										while ( n_draw_shift );
									}
									goto LABEL_290;
								}
							}
							else
							{
								chk_sh_and = dung_and80 >> 1;
								if ( !(dung_and80 & 1) )
									goto LABEL_287;
								temp8 = *(_BYTE *)pdung_cels++;
								*tmp_pbDst++ = temp8;
								if ( chk_sh_and )
								{
LABEL_280:
									n_draw_shift = chk_sh_and >> 1;
									if ( chk_sh_and & 1 )
									{
										junk_v155 = (char *)(pdung_cels + 1);
										tmp_dst = tmp_pbDst + 1;
										temp8 = *junk_v155;
										pdung_cels = (int)(junk_v155 + 1);
										*tmp_dst = temp8;
										tmp_pbDst = tmp_dst + 1;
									}
									if ( n_draw_shift )
									{
										do
										{
											temp32 = *(_DWORD *)pdung_cels;
											pdung_cels += 4;
											tmp_dst = tmp_pbDst + 1;
											temp32 = __ROR4__(temp32, 8);
											*tmp_dst = temp32;
											tmp_dst += 2;
											*tmp_dst = __ROR4__(temp32, 16);
											tmp_pbDst = tmp_dst + 1;
											--n_draw_shift;
										}
										while ( n_draw_shift );
									}
									goto LABEL_290;
								}
							}
						}
						else
						{
							pdung_cels += dung_and80;
							tmp_pbDst += dung_and80;
						}
LABEL_290:
						if ( !yy_32 )
							goto LABEL_293;
					}
					_LOBYTE(dung_and80) = -(char)dung_and80;
					tmp_pbDst += dung_and80;
					yy_32 -= dung_and80;
				}
				while ( yy_32 );
LABEL_293:
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				tmp_pbDst -= 800;
				xx_32 = x32_temp - 1;
				if ( x32_temp == 1 )
					return;
			}
		case 10:
			WorldBoolFlag = 0;
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = (char *)(pbDst - 12288);
					pdung_cels += 288;
LABEL_308:
					yy_32 = 2;
					if ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 42 )
							return;
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
						world_192 = 192 * world_tbl;
						world_tbl >>= 1;
						tmp_pbDst -= world_192;
						yy_32 = world_tbl + 2;
						WorldBoolFlag += world_tbl >> 1;
					}
					do
					{
						tmp_pbDst += yy_32;
						y_minus = 32 - yy_32;
						WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
						if ( WorldBoolFlag )
						{
							n_draw_shift = y_minus >> 2;
							if ( y_minus & 2 )
							{
								temp16 = *(_WORD *)(pdung_cels + 2);
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								*tmp_dst = __ROR4__(temp16, 8);
								tmp_pbDst = tmp_dst + 1;
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									tmp_dst = tmp_pbDst + 1;
									temp32 = __ROR4__(temp32, 8);
									*tmp_dst = temp32;
									tmp_dst += 2;
									*tmp_dst = __ROR4__(temp32, 16);
									tmp_pbDst = tmp_dst + 1;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							n_draw_shift = y_minus >> 2;
							if ( y_minus & 2 )
							{
								temp16 = *(_WORD *)(pdung_cels + 2);
								pdung_cels += 4;
								*tmp_pbDst = temp16;
								tmp_pbDst += 2;
								--n_draw_shift; /* check */
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									*tmp_pbDst = temp32;
									tmp_dst = tmp_pbDst + 2;
									*tmp_dst = __ROR4__(temp32, 16);
									tmp_pbDst = tmp_dst + 2;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						tmp_pbDst -= 800;
						yy_32 += 2;
					}
					while ( yy_32 != 32 );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				world_192 = 192 * world_tbl;
				world_tbl >>= 1;
				tmp_pbDst -= world_192;
				xx_32 = 30 - world_tbl;
				WorldBoolFlag += world_tbl >> 1;
			}
			do
			{
				tmp_pbDst += xx_32;
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						temp16 = *(_WORD *)(pdung_cels + 2);
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = __ROR4__(temp16, 8);
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							temp32 = __ROR4__(temp32, 8);
							*tmp_dst = temp32;
							tmp_dst += 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 1;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						temp16 = *(_WORD *)(pdung_cels + 2);
						pdung_cels += 4;
						*tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp32;
							tmp_dst = tmp_pbDst + 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 2;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_308;
		case 11:
			WorldBoolFlag = 0;
			xx_32 = 30;
			if ( (unsigned int)pbDst < screen_buf_end )
				goto LABEL_326;
			tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
			if ( tile_42_45 <= 45 )
			{
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				world_192 = 192 * world_tbl;
				world_tbl >>= 1;
				tmp_pbDst -= world_192;
				xx_32 = 30 - world_tbl;
				WorldBoolFlag += world_tbl >> 1;
				do
				{
LABEL_326:
					x_minus = 32 - xx_32;
					WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
					if ( WorldBoolFlag )
					{
						for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							temp32 = __ROR4__(temp32, 8);
							*tmp_dst = temp32;
							tmp_dst += 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 1;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							*tmp_dst = __ROR4__(temp16, 8);
							tmp_pbDst = tmp_dst + 1;
						}
					}
					else
					{
						for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp32;
							tmp_dst = tmp_pbDst + 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 2;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							temp16 = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_336;
			}
			tmp_pbDst = (char *)(pbDst - 12288);
			pdung_cels += 288;
LABEL_336:
			yy_32 = 2;
			if ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 42 )
					return;
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
				world_192 = 192 * world_tbl;
				world_tbl >>= 1;
				tmp_pbDst -= world_192;
				yy_32 = world_tbl + 2;
				WorldBoolFlag += world_tbl >> 1;
			}
			do
			{
				y_minus = 32 - yy_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					for ( n_draw_shift = y_minus >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						temp32 = __ROR4__(temp32, 8);
						*tmp_dst = temp32;
						tmp_dst += 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 1;
					}
					if ( (32 - (_BYTE)yy_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = __ROR4__(temp16, 8);
						tmp_pbDst = tmp_dst + 1;
					}
				}
				else
				{
					for ( n_draw_shift = y_minus >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*tmp_pbDst = temp32;
						tmp_dst = tmp_pbDst + 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 2;
					}
					if ( (32 - (_BYTE)yy_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
				}
				tmp_pbDst = &tmp_pbDst[yy_32 - 800];
				yy_32 += 2;
			}
			while ( yy_32 != 32 );
			break;
		case 12:
			WorldBoolFlag = 0;
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = (char *)(pbDst - 12288);
					pdung_cels += 288;
LABEL_364:
					i = 8;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								temp32 = __ROR4__(temp32, 8);
								*tmp_dst = temp32;
								tmp_dst += 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 1;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*tmp_pbDst = temp32;
								tmp_dst = tmp_pbDst + 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 2;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				world_192 = 192 * world_tbl;
				world_tbl >>= 1;
				tmp_pbDst -= world_192;
				xx_32 = 30 - world_tbl;
				WorldBoolFlag += world_tbl >> 1;
			}
			do
			{
				tmp_pbDst += xx_32;
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						temp16 = *(_WORD *)(pdung_cels + 2);
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = __ROR4__(temp16, 8);
						tmp_pbDst = tmp_dst + 1;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							tmp_dst = tmp_pbDst + 1;
							temp32 = __ROR4__(temp32, 8);
							*tmp_dst = temp32;
							tmp_dst += 2;
							*tmp_dst = __ROR4__(temp32, 16);
							tmp_pbDst = tmp_dst + 1;
							--n_draw_shift;
						}
						while ( n_draw_shift );
					}
				}
				else
				{
					n_draw_shift = x_minus >> 2;
					if ( x_minus & 2 )
					{
						temp16 = *(_WORD *)(pdung_cels + 2);
						pdung_cels += 4;
						*tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					if ( n_draw_shift )
					{
						do
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							*tmp_pbDst = temp32;
							tmp_dst = tmp_pbDst + 2;
							*tmp_dst = __ROR4__(temp32, 16);
							--n_draw_shift;
							tmp_pbDst = tmp_dst + 2;
						}
						while ( n_draw_shift );
					}
				}
				tmp_pbDst -= 800;
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_364;
		default:
			WorldBoolFlag = 0;
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = (char *)(pbDst - 12288);
					pdung_cels += 288;
LABEL_389:
					i = 8;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								tmp_dst = tmp_pbDst + 1;
								temp32 = __ROR4__(temp32, 8);
								*tmp_dst = temp32;
								tmp_dst += 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 1;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*tmp_pbDst = temp32;
								tmp_dst = tmp_pbDst + 2;
								*tmp_dst = __ROR4__(temp32, 16);
								tmp_pbDst = tmp_dst + 2;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				world_192 = 192 * world_tbl;
				world_tbl >>= 1;
				tmp_pbDst -= world_192;
				xx_32 = 30 - world_tbl;
				WorldBoolFlag += world_tbl >> 1;
			}
			do
			{
				x_minus = 32 - xx_32;
				WorldBoolFlag = ((_BYTE)WorldBoolFlag + 1) & 1;
				if ( WorldBoolFlag )
				{
					for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						temp32 = __ROR4__(temp32, 8);
						*tmp_dst = temp32;
						tmp_dst += 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 1;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						tmp_dst = tmp_pbDst + 1;
						*tmp_dst = __ROR4__(temp16, 8);
						tmp_pbDst = tmp_dst + 1;
					}
				}
				else
				{
					for ( n_draw_shift = x_minus >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*tmp_pbDst = temp32;
						tmp_dst = tmp_pbDst + 2;
						*tmp_dst = __ROR4__(temp32, 16);
						tmp_pbDst = tmp_dst + 2;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
				}
				tmp_pbDst = &tmp_pbDst[xx_32 - 800];
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_389;
	}
}

void __fastcall drawBottomArchesLowerScreen(unsigned char *pbDst, unsigned int *pMask)
{
	char *tmp_pbDst; // edi MAPDST
	short cel_type_16; // ax MAPDST
	char *pdung_cels; // esi MAPDST
	unsigned int cel_type_16_tmp; // eax MAPDST
	int cel_type_32; // eax
	int and80_i; // ecx MAPDST
	signed int tile_42_45; // eax MAPDST
	unsigned int world_tbl; // ecx MAPDST
	char temp8; // al MAPDST
	short temp16; // ax MAPDST
	int temp32; // eax MAPDST
	int xx_32; // ecx MAPDST
	int yy_32; // edx MAPDST
	int dung_and80; // eax MAPDST
	unsigned int left_shift; // edx MAPDST
	signed int i; // edx MAPDST
	unsigned int n_draw_shift; // ecx MAPDST
	int y32_temp; // [esp-8h] [ebp-14h] MAPDST
	int x32_temp; // [esp-4h] [ebp-10h] MAPDST
	int _EAX;
	char *_EBX;

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	tmp_pbDst = (char *)pbDst;
	gpDrawMask = pMask;
	if ( (_BYTE)light_table_index )
	{
		if ( (_BYTE)light_table_index == lightmax )
		{
			if ( level_cel_block & 0x8000 )
				level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
								+ (unsigned short)(level_cel_block & 0xF000);
			pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			cel_type_16_tmp = level_cel_block;
			_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
			cel_type_32 = (cel_type_16_tmp >> 4) & 7;
			switch ( (_WORD)cel_type_32 )
			{
				case 0:
					yy_32 = 32;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = 0;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							yy_32 = y32_temp;
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--gpDrawMask;
						--yy_32;
					}
					while ( yy_32 );
					break;
				case 1:
					xx_32 = 32;
					do
					{
						x32_temp = xx_32;
						gdwCurrentMask = *gpDrawMask;
						yy_32 = 32;
						do
						{
							while ( 1 )
							{
								dung_and80 = (unsigned char)*pdung_cels++;
								if ( (dung_and80 & 0x80u) != 0 )
									break;
								yy_32 -= dung_and80;
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									and80_i = dung_and80;
									pdung_cels += dung_and80;
									y32_temp = yy_32;
									left_shift = gdwCurrentMask;
									do
									{
										if ( left_shift & 0x80000000 )
											*tmp_pbDst = 0;
										left_shift *= 2;
										++tmp_pbDst;
										--and80_i;
									}
									while ( and80_i );
									gdwCurrentMask = left_shift;
									yy_32 = y32_temp;
								}
								else
								{
									pdung_cels += dung_and80;
									tmp_pbDst += dung_and80;
								}
								if ( !yy_32 )
									goto LABEL_252;
							}
							_LOBYTE(dung_and80) = -(char)dung_and80;
							tmp_pbDst += dung_and80;
							if ( dung_and80 & 0x1F )
								gdwCurrentMask <<= dung_and80 & 0x1F;
							yy_32 -= dung_and80;
						}
						while ( yy_32 );
LABEL_252:
						tmp_pbDst -= 800;
						--gpDrawMask;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 2:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							tmp_pbDst += i;
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
					}
					i = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							tmp_pbDst += i;
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						i += 2;
					}
					while ( i != 32 );
					break;
				case 3:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst = &tmp_pbDst[-i + 32];
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
						tmp_pbDst += i;
					}
					i = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst = &tmp_pbDst[-i + 32];
						}
						tmp_pbDst = &tmp_pbDst[i - 800];
						i += 2;
					}
					while ( i != 32 );
					break;
				case 4:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							tmp_pbDst += i;
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
					}
					gpDrawMask -= 16;
					yy_32 = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = 0;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							yy_32 = y32_temp;
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--gpDrawMask;
						--yy_32;
					}
					while ( yy_32 );
					break;
				default:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst = &tmp_pbDst[-i + 32];
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
						tmp_pbDst += i;
					}
					gpDrawMask -= 16;
					yy_32 = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = 0;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							yy_32 = y32_temp;
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--gpDrawMask;
						--yy_32;
					}
					while ( yy_32 );
					break;
			}
			return;
		}
		if ( !(level_cel_block & 0x8000) )
		{
			pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			_EBX = &pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
			switch ( cel_type_16 )
			{
				case 0:
					yy_32 = 32;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								_EAX = *pdung_cels++;
								if ( left_shift & 0x80000000 )
								{
									ASM_XLAT(_EAX,_EBX);
									*tmp_pbDst = _EAX;
								}
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--gpDrawMask;
						--yy_32;
					}
					while ( yy_32 );
					break;
				case 1:
					xx_32 = 32;
					do
					{
						x32_temp = xx_32;
						gdwCurrentMask = *gpDrawMask;
						yy_32 = 32;
						do
						{
							while ( 1 )
							{
								dung_and80 = (unsigned char)*pdung_cels++;
								if ( (dung_and80 & 0x80u) != 0 )
									break;
								yy_32 -= dung_and80;
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									and80_i = dung_and80;
									y32_temp = yy_32;
									left_shift = gdwCurrentMask;
									do
									{
										_EAX = *pdung_cels++;
										if ( left_shift & 0x80000000 )
										{
											ASM_XLAT(_EAX,_EBX);
											*tmp_pbDst = _EAX;
										}
										left_shift *= 2;
										++tmp_pbDst;
										--and80_i;
									}
									while ( and80_i );
									gdwCurrentMask = left_shift;
									yy_32 = y32_temp;
								}
								else
								{
									pdung_cels += dung_and80;
									tmp_pbDst += dung_and80;
								}
								if ( !yy_32 )
									goto LABEL_52;
							}
							_LOBYTE(dung_and80) = -(char)dung_and80;
							tmp_pbDst += dung_and80;
							if ( dung_and80 & 0x1F )
								gdwCurrentMask <<= dung_and80 & 0x1F;
							yy_32 -= dung_and80;
						}
						while ( yy_32 );
LABEL_52:
						tmp_pbDst -= 800;
						--gpDrawMask;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 2:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = (char *)(pbDst - 12288);
							pdung_cels += 288;
LABEL_62:
							yy_32 = 2;
							if ( (unsigned int)tmp_pbDst >= screen_buf_end )
							{
								tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
								if ( tile_42_45 > 42 )
									return;
								world_tbl = WorldTbl3x16[tile_42_45];
								pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
								tmp_pbDst -= 192 * world_tbl;
								yy_32 = (world_tbl >> 1) + 2;
							}
							do
							{
								tmp_pbDst += yy_32;
								n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
								if ( (32 - yy_32) & 2 )
								{
									_EAX = *((_WORD *)pdung_cels + 1);
									pdung_cels += 4;
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR2__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
									tmp_pbDst += 2;
								}
								if ( n_draw_shift )
								{
									do
									{
										_EAX = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										ASM_XLAT(_EAX,_EBX);
										_EAX = __ROR4__(_EAX, 8);
										ASM_XLAT(_EAX,_EBX);
										_EAX = __ROR4__(_EAX, 8);
										ASM_XLAT(_EAX,_EBX);
										_EAX = __ROR4__(_EAX, 8);
										ASM_XLAT(_EAX,_EBX);
										*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
										tmp_pbDst += 4;
										--n_draw_shift;
									}
									while ( n_draw_shift );
								}
								tmp_pbDst -= 800;
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						tmp_pbDst += xx_32;
						n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
						if ( (32 - xx_32) & 2 )
						{
							_EAX = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								_EAX = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_62;
				case 3:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = (char *)(pbDst - 12288);
							pdung_cels += 288;
LABEL_80:
							yy_32 = 2;
							if ( (unsigned int)tmp_pbDst >= screen_buf_end )
							{
								tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
								if ( tile_42_45 > 42 )
									return;
								world_tbl = WorldTbl3x16[tile_42_45];
								pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
								tmp_pbDst -= 192 * world_tbl;
								yy_32 = (world_tbl >> 1) + 2;
							}
							do
							{
								for ( n_draw_shift = (unsigned int)(32 - yy_32) >> 2; n_draw_shift; --n_draw_shift )
								{
									_EAX = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR4__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR4__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR4__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
									tmp_pbDst += 4;
								}
								if ( (32 - (_BYTE)yy_32) & 2 )
								{
									_EAX = *(_WORD *)pdung_cels;
									pdung_cels += 2;
									ASM_XLAT(_EAX,_EBX);
									_EAX = __ROR2__(_EAX, 8);
									ASM_XLAT(_EAX,_EBX);
									*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
									tmp_pbDst += 2;
								}
								tmp_pbDst = &tmp_pbDst[yy_32 - 800];
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
						{
							_EAX = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
							tmp_pbDst += 4;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							_EAX = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_80;
				case 4:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = (char *)(pbDst - 12288);
							pdung_cels += 288;
LABEL_98:
							gpDrawMask -= 16;
							yy_32 = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									y32_temp = yy_32;
									left_shift = *gpDrawMask;
									i = 32;
									do
									{
										_EAX = *pdung_cels++;
										if ( left_shift & 0x80000000 )
										{
											ASM_XLAT(_EAX,_EBX);
											*tmp_pbDst = _EAX;
										}
										left_shift *= 2;
										++tmp_pbDst;
										--i;
									}
									while ( i );
									yy_32 = y32_temp;
								}
								else
								{
									pdung_cels += 32;
									tmp_pbDst += 32;
								}
								tmp_pbDst -= 800;
								--gpDrawMask;
								--yy_32;
							}
							while ( yy_32 );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						tmp_pbDst += xx_32;
						n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
						if ( (32 - xx_32) & 2 )
						{
							_EAX = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								_EAX = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								_EAX = __ROR4__(_EAX, 8);
								ASM_XLAT(_EAX,_EBX);
								*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_98;
				default:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = (char *)(pbDst - 12288);
							pdung_cels += 288;
LABEL_117:
							gpDrawMask -= 16;
							yy_32 = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									y32_temp = yy_32;
									left_shift = *gpDrawMask;
									i = 32;
									do
									{
										_EAX = *pdung_cels++;
										if ( left_shift & 0x80000000 )
										{
											ASM_XLAT(_EAX,_EBX);
											*tmp_pbDst = _EAX;
										}
										left_shift *= 2;
										++tmp_pbDst;
										--i;
									}
									while ( i );
									pdung_cels += (unsigned char)pdung_cels & 2;
									yy_32 = y32_temp;
								}
								else
								{
									pdung_cels += 32;
									tmp_pbDst += 32;
								}
								tmp_pbDst -= 800;
								--gpDrawMask;
								--yy_32;
							}
							while ( yy_32 );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
						{
							_EAX = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR4__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_DWORD *)tmp_pbDst = __ROR4__(_EAX, 8);
							tmp_pbDst += 4;
						}
						if ( (32 - (_BYTE)xx_32) & 2 )
						{
							_EAX = *(_WORD *)pdung_cels;
							pdung_cels += 4;
							ASM_XLAT(_EAX,_EBX);
							_EAX = __ROR2__(_EAX, 8);
							ASM_XLAT(_EAX,_EBX);
							*(_WORD *)tmp_pbDst = __ROR2__(_EAX, 8);
							tmp_pbDst += 2;
						}
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_117;
			}
			return;
		}
		pdung_cels = (char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned char)(BYTE1(level_cel_block) >> 4);
	}
	else
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16_tmp = level_cel_block;
		_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
		cel_type_16 = ((cel_type_16_tmp >> 4) & 7) + 8;
	}
	switch ( cel_type_16 )
	{
		case 8:
			yy_32 = 32;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
				{
					y32_temp = yy_32;
					left_shift = *gpDrawMask;
					i = 32;
					do
					{
						temp8 = *pdung_cels++;
						if ( left_shift & 0x80000000 )
							*tmp_pbDst = temp8;
						left_shift *= 2;
						++tmp_pbDst;
						--i;
					}
					while ( i );
					yy_32 = y32_temp;
				}
				else
				{
					pdung_cels += 32;
					tmp_pbDst += 32;
				}
				tmp_pbDst -= 800;
				--gpDrawMask;
				--yy_32;
			}
			while ( yy_32 );
			break;
		case 9:
			xx_32 = 32;
			do
			{
				x32_temp = xx_32;
				gdwCurrentMask = *gpDrawMask;
				yy_32 = 32;
				do
				{
					while ( 1 )
					{
						dung_and80 = (unsigned char)*pdung_cels++;
						if ( (dung_and80 & 0x80u) != 0 )
							break;
						yy_32 -= dung_and80;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							and80_i = dung_and80;
							y32_temp = yy_32;
							left_shift = gdwCurrentMask;
							do
							{
								temp8 = *pdung_cels++;
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = temp8;
								left_shift *= 2;
								++tmp_pbDst;
								--and80_i;
							}
							while ( and80_i );
							gdwCurrentMask = left_shift;
							yy_32 = y32_temp;
						}
						else
						{
							pdung_cels += dung_and80;
							tmp_pbDst += dung_and80;
						}
						if ( !yy_32 )
							goto LABEL_152;
					}
					_LOBYTE(dung_and80) = -(char)dung_and80;
					tmp_pbDst += dung_and80;
					if ( dung_and80 & 0x1F )
						gdwCurrentMask <<= dung_and80 & 0x1F;
					yy_32 -= dung_and80;
				}
				while ( yy_32 );
LABEL_152:
				tmp_pbDst -= 800;
				--gpDrawMask;
				xx_32 = x32_temp - 1;
			}
			while ( x32_temp != 1 );
			break;
		case 10:
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = (char *)(pbDst - 12288);
					pdung_cels += 288;
LABEL_162:
					yy_32 = 2;
					if ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 42 )
							return;
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						yy_32 = (world_tbl >> 1) + 2;
					}
					do
					{
						tmp_pbDst += yy_32;
						n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
						if ( (32 - yy_32) & 2 )
						{
							temp16 = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							*(_WORD *)tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						tmp_pbDst -= 800;
						yy_32 += 2;
					}
					while ( yy_32 != 32 );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
			}
			do
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					temp16 = *((_WORD *)pdung_cels + 1);
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_162;
		case 11:
			xx_32 = 30;
			if ( (unsigned int)pbDst < screen_buf_end )
				goto LABEL_175;
			tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
			if ( tile_42_45 <= 45 )
			{
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
				do
				{
LABEL_175:
					for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_180;
			}
			tmp_pbDst = (char *)(pbDst - 12288);
			pdung_cels += 288;
LABEL_180:
			yy_32 = 2;
			if ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 42 )
					return;
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				yy_32 = (world_tbl >> 1) + 2;
			}
			do
			{
				for ( n_draw_shift = (unsigned int)(32 - yy_32) >> 2; n_draw_shift; --n_draw_shift )
				{
					temp32 = *(_DWORD *)pdung_cels;
					pdung_cels += 4;
					*(_DWORD *)tmp_pbDst = temp32;
					tmp_pbDst += 4;
				}
				if ( (32 - (_BYTE)yy_32) & 2 )
				{
					temp16 = *(_WORD *)pdung_cels;
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				tmp_pbDst = &tmp_pbDst[yy_32 - 800];
				yy_32 += 2;
			}
			while ( yy_32 != 32 );
			break;
		case 12:
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = (char *)(pbDst - 12288);
					pdung_cels += 288;
LABEL_198:
					gpDrawMask -= 16;
					yy_32 = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								temp8 = *pdung_cels++;
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = temp8;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							yy_32 = y32_temp;
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--gpDrawMask;
						--yy_32;
					}
					while ( yy_32 );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
			}
			do
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					temp16 = *((_WORD *)pdung_cels + 1);
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_198;
		default:
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = (char *)(pbDst - 12288);
					pdung_cels += 288;
LABEL_217:
					gpDrawMask -= 16;
					yy_32 = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							y32_temp = yy_32;
							left_shift = *gpDrawMask;
							i = 32;
							do
							{
								temp8 = *pdung_cels++;
								if ( left_shift & 0x80000000 )
									*tmp_pbDst = temp8;
								left_shift *= 2;
								++tmp_pbDst;
								--i;
							}
							while ( i );
							pdung_cels += (unsigned char)pdung_cels & 2;
							yy_32 = y32_temp;
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--gpDrawMask;
						--yy_32;
					}
					while ( yy_32 );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
			}
			do
			{
				for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
				{
					temp32 = *(_DWORD *)pdung_cels;
					pdung_cels += 4;
					*(_DWORD *)tmp_pbDst = temp32;
					tmp_pbDst += 4;
				}
				if ( (32 - (_BYTE)xx_32) & 2 )
				{
					temp16 = *(_WORD *)pdung_cels;
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				tmp_pbDst = &tmp_pbDst[xx_32 - 800];
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_217;
	}
}

void __fastcall drawLowerScreen(unsigned char *pbDst)
{
	char junk_v2; // al MAPDST
	unsigned char *tmp_pbDst; // edi MAPDST
	char *pdung_cels; // esi MAPDST
	char *l_tbl; // ebx
	short cel_type_16; // ax MAPDST
	unsigned int cel_type_16_tmp; // eax
	int cel_type_32; // eax
	int xx_32; // edx MAPDST
	char l_index; // edx MAPDST
	int yy_32; // ebp MAPDST
	char block_4; // cl MAPDST
	unsigned char dstbyte; // ch MAPDST
	int x_minus; // ecx MAPDST
	int y_minus; // ecx MAPDST
	unsigned int chk_sh_and; // ecx MAPDST
	unsigned char temp8; // cf MAPDST
	signed int tile_42_45; // eax MAPDST
	unsigned int world_tbl; // ecx MAPDST
	unsigned int n_draw_shift; // ecx MAPDST
	int temp32; // eax MAPDST
	short temp16; // ax MAPDST
	unsigned int dung_and80; // eax MAPDST
	signed int i; // edx MAPDST
	signed int j; // ecx MAPDST
	int x32_temp; // [esp-14h] [ebp-18h] MAPDST

	l_index = cel_transparency_active;
	if ( cel_transparency_active )
	{
		if ( !arch_draw_type )
		{
			drawTopArchesLowerScreen(pbDst);
			return;
		}
		if ( arch_draw_type == 1 )
		{
			junk_v2 = block_lvid[level_piece_id];
			if ( junk_v2 == 1 || junk_v2 == 3 )
			{
				drawBottomArchesLowerScreen(pbDst, &LeftMask[31]);
				return;
			}
		}
		if ( arch_draw_type == 2 )
		{
			junk_v2 = block_lvid[level_piece_id];
			if ( junk_v2 == 2 || junk_v2 == 3 )
			{
				drawBottomArchesLowerScreen(pbDst, &RightMask[31]);
				return;
			}
		}
	}
	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	tmp_pbDst = pbDst;
	if ( (_BYTE)light_table_index )
	{
		if ( (_BYTE)light_table_index == lightmax )
		{
			if ( level_cel_block & 0x8000 )
				level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
								+ (unsigned short)(level_cel_block & 0xF000);
			pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			cel_type_16_tmp = level_cel_block;
			_LOBYTE(cel_type_16_tmp) = BYTE1(cel_type_16_tmp);
			cel_type_32 = (cel_type_16_tmp >> 4) & 7;
			switch ( (_WORD)cel_type_32 )
			{
				case 0:
					i = 32;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					break;
				case 1:
					xx_32 = 32;
					do
					{
						x32_temp = xx_32;
						yy_32 = 32;
						do
						{
							while ( 1 )
							{
								dung_and80 = (unsigned char)*pdung_cels++;
								if ( (dung_and80 & 0x80u) == 0 )
									break;
								_LOBYTE(dung_and80) = -(char)dung_and80;
								tmp_pbDst += dung_and80;
								yy_32 -= dung_and80;
								if ( !yy_32 )
									goto LABEL_232;
							}
							yy_32 -= dung_and80;
							if ( (unsigned int)tmp_pbDst < screen_buf_end )
							{
								pdung_cels += dung_and80;
								chk_sh_and = dung_and80 >> 1;
								if ( dung_and80 & 1 )
								{
									*tmp_pbDst = 0;
									++tmp_pbDst;
								}
								if ( chk_sh_and )
								{
									n_draw_shift = dung_and80 >> 2;
									if ( chk_sh_and & 1 )
									{
										*(_WORD *)tmp_pbDst = 0;
										tmp_pbDst += 2;
									}
									if ( n_draw_shift )
									{
										do
										{
											*(_DWORD *)tmp_pbDst = 0;
											tmp_pbDst += 4;
											--n_draw_shift;
										}
										while ( n_draw_shift );
									}
								}
							}
							else
							{
								pdung_cels += dung_and80;
								tmp_pbDst += dung_and80;
							}
						}
						while ( yy_32 );
LABEL_232:
						tmp_pbDst -= 800;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 2:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							tmp_pbDst += i;
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
					}
					i = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							tmp_pbDst += i;
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						i += 2;
					}
					while ( i != 32 );
					break;
				case 3:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst = &tmp_pbDst[-i + 32];
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
						tmp_pbDst += i;
					}
					i = 2;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst = &tmp_pbDst[-i + 32];
						}
						tmp_pbDst = &tmp_pbDst[i - 800];
						i += 2;
					}
					while ( i != 32 );
					break;
				case 4:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							tmp_pbDst += i;
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
					}
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					break;
				default:
					for ( i = 30; ; i -= 2 )
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							n_draw_shift = (unsigned int)(32 - i) >> 2;
							if ( (32 - i) & 2 )
							{
								*(_WORD *)tmp_pbDst = 0;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									*(_DWORD *)tmp_pbDst = 0;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
						else
						{
							pdung_cels = &pdung_cels[-i + 32];
							tmp_pbDst = &tmp_pbDst[-i + 32];
						}
						tmp_pbDst -= 800;
						if ( !i )
							break;
						tmp_pbDst += i;
					}
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								*(_DWORD *)tmp_pbDst = 0;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					break;
			}
			return;
		}
		if ( !(level_cel_block & 0x8000) )
		{
			pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			l_tbl = &pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned short)level_cel_block >> 12;
			switch ( cel_type_16 )
			{
				case 0:
					xx_32 = 32;
					do
					{
						x32_temp = xx_32;
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							l_index = 0;
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								temp32 = __ROR4__(temp32, 16);
								l_index = temp32;
								_LOBYTE(pbDst) = l_tbl[l_index];
								l_index = BYTE1(temp32);
								BYTE1(pbDst) = l_tbl[l_index];
								temp32 = __ROR4__(temp32, 16);
								pbDst = (unsigned char *)((_DWORD)pbDst << 16);
								l_index = temp32;
								_LOBYTE(pbDst) = l_tbl[l_index];
								l_index = BYTE1(temp32);
								BYTE1(pbDst) = l_tbl[l_index];
								*(_DWORD *)tmp_pbDst = (unsigned int)pbDst; /* check */
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 1:
					xx_32 = 32;
					do
					{
						x32_temp = xx_32;
						yy_32 = 32;
						do
						{
							dung_and80 = (unsigned char)*pdung_cels++;
							if ( (dung_and80 & 0x80u) == 0 )
							{
								yy_32 -= dung_and80;
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									for ( block_4 = dung_and80; block_4 >= 4; block_4 -= 4 )
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										temp32 = __ROR4__(temp32, 16);
										*tmp_pbDst = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = temp32;
										tmp_pbDst[1] = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst[2] = dstbyte;
										tmp_pbDst[3] = l_tbl[l_index];
										tmp_pbDst += 4;
									}
									if ( block_4 >= 2 )
									{
										l_index = *pdung_cels;
										*tmp_pbDst = l_tbl[l_index];
										l_index = pdung_cels[1];
										tmp_pbDst[1] = l_tbl[l_index];
										pdung_cels += 2;
										tmp_pbDst += 2;
									}
									if ( block_4 & 1 )
									{
										l_index = *pdung_cels++;
										*tmp_pbDst++ = l_tbl[l_index];
									}
								}
								else
								{
									pdung_cels += dung_and80;
									tmp_pbDst += dung_and80;
								}
							}
							else
							{
								_LOBYTE(dung_and80) = -(char)dung_and80;
								tmp_pbDst += dung_and80;
								yy_32 -= dung_and80;
							}
						}
						while ( yy_32 );
						tmp_pbDst -= 800;
						xx_32 = x32_temp - 1;
					}
					while ( x32_temp != 1 );
					break;
				case 2:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = pbDst - 12288;
							pdung_cels += 288;
LABEL_68:
							yy_32 = 2;
							if ( (unsigned int)tmp_pbDst >= screen_buf_end )
							{
								tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
								if ( tile_42_45 > 42 )
									return;
								world_tbl = WorldTbl3x16[tile_42_45];
								pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
								tmp_pbDst -= 192 * world_tbl;
								yy_32 = (world_tbl >> 1) + 2;
							}
							do
							{
								tmp_pbDst += yy_32;
								y_minus = 32 - yy_32;
								l_index = (32 - (_BYTE)yy_32) & 2;
								pdung_cels += l_index;
								do
								{
									l_index = *pdung_cels++;
									*tmp_pbDst++ = l_tbl[l_index];
									--y_minus;
								}
								while ( y_minus );
								yy_32 += 2;
								tmp_pbDst -= 800;
							}
							while ( yy_32 != 32 );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						tmp_pbDst += xx_32;
						x_minus = 32 - xx_32;
						l_index = (32 - (_BYTE)xx_32) & 2;
						pdung_cels += l_index;
						do
						{
							l_index = *pdung_cels++;
							*tmp_pbDst++ = l_tbl[l_index];
							--x_minus;
						}
						while ( x_minus );
						tmp_pbDst -= 800;
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_68;
				case 3:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = pbDst - 12288;
							pdung_cels += 288;
LABEL_83:
							yy_32 = 2;
							if ( (unsigned int)tmp_pbDst >= screen_buf_end )
							{
								tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
								if ( tile_42_45 > 42 )
									return;
								world_tbl = WorldTbl3x16[tile_42_45];
								pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
								tmp_pbDst -= 192 * world_tbl;
								yy_32 = (world_tbl >> 1) + 2;
							}
							do
							{
								y_minus = 32 - yy_32;
								do
								{
									l_index = *pdung_cels++;
									*tmp_pbDst++ = l_tbl[l_index];
									--y_minus;
								}
								while ( y_minus );
								l_index = (unsigned char)pdung_cels & 2;
								pdung_cels += l_index;
								tmp_pbDst = &tmp_pbDst[yy_32 - 800];
								yy_32 += 2;
							}
							while ( yy_32 != 32 );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						x_minus = 32 - xx_32;
						do
						{
							l_index = *pdung_cels++;
							*tmp_pbDst++ = l_tbl[l_index];
							--x_minus;
						}
						while ( x_minus );
						l_index = (unsigned char)pdung_cels & 2;
						pdung_cels += l_index;
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_83;
				case 4:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = pbDst - 12288;
							pdung_cels += 288;
LABEL_100:
							i = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									block_4 = 32;
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										temp32 = __ROR4__(temp32, 16);
										*tmp_pbDst = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = temp32;
										tmp_pbDst[1] = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst[2] = dstbyte;
										tmp_pbDst[3] = l_tbl[l_index];
										tmp_pbDst += 4;
										block_4 -= 4;
									}
									while ( block_4 >= 4 );
								}
								else
								{
									pdung_cels += 32;
									tmp_pbDst += 32;
								}
								tmp_pbDst -= 800;
								--i;
							}
							while ( i );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						tmp_pbDst += xx_32;
						block_4 = 32 - xx_32;
						l_index = (32 - (_BYTE)xx_32) & 2;
						pdung_cels += l_index;
						if ( (char)(32 - xx_32) >= 4 )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								l_index = temp32;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								temp32 = __ROR4__(temp32, 16);
								*tmp_pbDst = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = temp32;
								tmp_pbDst[1] = dstbyte;
								dstbyte = l_tbl[l_index];
								l_index = BYTE1(temp32);
								tmp_pbDst[2] = dstbyte;
								tmp_pbDst[3] = l_tbl[l_index];
								tmp_pbDst += 4;
								block_4 -= 4;
							}
							while ( block_4 >= 4 );
						}
						if ( block_4 >= 2 )
						{
							l_index = *pdung_cels;
							*tmp_pbDst = l_tbl[l_index];
							l_index = pdung_cels[1];
							tmp_pbDst[1] = l_tbl[l_index];
							pdung_cels += 2;
							tmp_pbDst += 2;
						}
						tmp_pbDst -= 800;
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_100;
				default:
					xx_32 = 30;
					if ( (unsigned int)pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 45 )
						{
							tmp_pbDst = pbDst - 12288;
							pdung_cels += 288;
LABEL_116:
							j = 16;
							do
							{
								if ( (unsigned int)tmp_pbDst < screen_buf_end )
								{
									block_4 = 32;
									do
									{
										temp32 = *(_DWORD *)pdung_cels;
										pdung_cels += 4;
										l_index = temp32;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										temp32 = __ROR4__(temp32, 16);
										*tmp_pbDst = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = temp32;
										tmp_pbDst[1] = dstbyte;
										dstbyte = l_tbl[l_index];
										l_index = BYTE1(temp32);
										tmp_pbDst[2] = dstbyte;
										tmp_pbDst[3] = l_tbl[l_index];
										tmp_pbDst += 4;
										block_4 -= 4;
									}
									while ( block_4 >= 4 );
								}
								else
								{
									pdung_cels += 32;
									tmp_pbDst += 32;
								}
								tmp_pbDst -= 800;
								--j;
							}
							while ( j );
							return;
						}
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						xx_32 = 30 - (world_tbl >> 1);
					}
					do
					{
						for ( block_4 = 32 - xx_32; block_4 >= 4; block_4 -= 4 )
						{
							temp32 = *(_DWORD *)pdung_cels;
							pdung_cels += 4;
							l_index = temp32;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							temp32 = __ROR4__(temp32, 16);
							*tmp_pbDst = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = temp32;
							tmp_pbDst[1] = dstbyte;
							dstbyte = l_tbl[l_index];
							l_index = BYTE1(temp32);
							tmp_pbDst[2] = dstbyte;
							tmp_pbDst[3] = l_tbl[l_index];
							tmp_pbDst += 4;
						}
						if ( block_4 >= 2 )
						{
							l_index = *pdung_cels;
							*tmp_pbDst = l_tbl[l_index];
							l_index = pdung_cels[1];
							tmp_pbDst[1] = l_tbl[l_index];
							pdung_cels += 2;
							tmp_pbDst += 2;
						}
						l_index = (unsigned char)pdung_cels & 2;
						pdung_cels += l_index;
						tmp_pbDst = &tmp_pbDst[xx_32 - 800];
						xx_32 -= 2;
					}
					while ( xx_32 >= 0 );
					goto LABEL_116;
			}
			return;
		}
		pdung_cels = (char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned short)level_cel_block >> 12;
	}
	else
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		pdung_cels = (char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = (((unsigned int)level_cel_block >> 12) & 7) + 8;
	}
	switch ( cel_type_16 )
	{
		case 8:
			i = 32;
			do
			{
				if ( (unsigned int)tmp_pbDst < screen_buf_end )
				{
					j = 8;
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
						--j;
					}
					while ( j );
				}
				else
				{
					pdung_cels += 32;
					tmp_pbDst += 32;
				}
				tmp_pbDst -= 800;
				--i;
			}
			while ( i );
			break;
		case 9:
			xx_32 = 32;
			do
			{
				x32_temp = xx_32;
				yy_32 = 32;
				do
				{
					while ( 1 )
					{
						dung_and80 = (unsigned char)*pdung_cels++;
						if ( (dung_and80 & 0x80u) == 0 )
							break;
						_LOBYTE(dung_and80) = -(char)dung_and80;
						tmp_pbDst += dung_and80;
						yy_32 -= dung_and80;
						if ( !yy_32 )
							goto LABEL_143;
					}
					yy_32 -= dung_and80;
					if ( (unsigned int)tmp_pbDst < screen_buf_end )
					{
						chk_sh_and = dung_and80 >> 1;
						if ( dung_and80 & 1 )
						{
							temp8 = *pdung_cels;
							++pdung_cels;
							*tmp_pbDst = temp8;
							++tmp_pbDst;
						}
						if ( chk_sh_and )
						{
							n_draw_shift = chk_sh_and >> 1;
							if ( chk_sh_and & 1 )
							{
								temp16 = *(_WORD *)pdung_cels;
								pdung_cels += 2;
								*(_WORD *)tmp_pbDst = temp16;
								tmp_pbDst += 2;
							}
							if ( n_draw_shift )
							{
								do
								{
									temp32 = *(_DWORD *)pdung_cels;
									pdung_cels += 4;
									*(_DWORD *)tmp_pbDst = temp32;
									tmp_pbDst += 4;
									--n_draw_shift;
								}
								while ( n_draw_shift );
							}
						}
					}
					else
					{
						pdung_cels += dung_and80;
						tmp_pbDst += dung_and80;
					}
				}
				while ( yy_32 );
LABEL_143:
				tmp_pbDst -= 800;
				xx_32 = x32_temp - 1;
			}
			while ( x32_temp != 1 );
			break;
		case 10:
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = pbDst - 12288;
					pdung_cels += 288;
LABEL_153:
					yy_32 = 2;
					if ( (unsigned int)tmp_pbDst >= screen_buf_end )
					{
						tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
						if ( tile_42_45 > 42 )
							return;
						world_tbl = WorldTbl3x16[tile_42_45];
						pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
						tmp_pbDst -= 192 * world_tbl;
						yy_32 = (world_tbl >> 1) + 2;
					}
					do
					{
						tmp_pbDst += yy_32;
						n_draw_shift = (unsigned int)(32 - yy_32) >> 2;
						if ( (32 - yy_32) & 2 )
						{
							temp16 = *((_WORD *)pdung_cels + 1);
							pdung_cels += 4;
							*(_WORD *)tmp_pbDst = temp16;
							tmp_pbDst += 2;
						}
						if ( n_draw_shift )
						{
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
								--n_draw_shift;
							}
							while ( n_draw_shift );
						}
						yy_32 += 2;
						tmp_pbDst -= 800;
					}
					while ( yy_32 < 32 );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
			}
			do
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					temp16 = *((_WORD *)pdung_cels + 1);
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_153;
		case 11:
			xx_32 = 30;
			if ( (unsigned int)pbDst < screen_buf_end )
				goto LABEL_166;
			tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
			if ( tile_42_45 <= 45 )
			{
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
				do
				{
LABEL_166:
					for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
					}
					if ( (32 - (_BYTE)xx_32) & 2 )
					{
						temp16 = *(_WORD *)pdung_cels;
						pdung_cels += 4;
						*(_WORD *)tmp_pbDst = temp16;
						tmp_pbDst += 2;
					}
					tmp_pbDst = &tmp_pbDst[xx_32 - 800];
					xx_32 -= 2;
				}
				while ( xx_32 >= 0 );
				goto LABEL_171;
			}
			tmp_pbDst = pbDst - 12288;
			pdung_cels += 288;
LABEL_171:
			yy_32 = 2;
			if ( (unsigned int)tmp_pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&tmp_pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 42 )
					return;
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_2 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				yy_32 = (world_tbl >> 1) + 2;
			}
			do
			{
				for ( n_draw_shift = (unsigned int)(32 - yy_32) >> 2; n_draw_shift; --n_draw_shift )
				{
					temp32 = *(_DWORD *)pdung_cels;
					pdung_cels += 4;
					*(_DWORD *)tmp_pbDst = temp32;
					tmp_pbDst += 4;
				}
				if ( (32 - (_BYTE)yy_32) & 2 )
				{
					temp16 = *(_WORD *)pdung_cels;
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				tmp_pbDst += yy_32;
				yy_32 += 2;
				tmp_pbDst -= 800;
			}
			while ( yy_32 < 32 );
			break;
		case 12:
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = pbDst - 12288;
					pdung_cels += 288;
LABEL_189:
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
			}
			do
			{
				tmp_pbDst += xx_32;
				n_draw_shift = (unsigned int)(32 - xx_32) >> 2;
				if ( (32 - xx_32) & 2 )
				{
					temp16 = *((_WORD *)pdung_cels + 1);
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				if ( n_draw_shift )
				{
					do
					{
						temp32 = *(_DWORD *)pdung_cels;
						pdung_cels += 4;
						*(_DWORD *)tmp_pbDst = temp32;
						tmp_pbDst += 4;
						--n_draw_shift;
					}
					while ( n_draw_shift );
				}
				tmp_pbDst -= 800;
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_189;
		default:
			xx_32 = 30;
			if ( (unsigned int)pbDst >= screen_buf_end )
			{
				tile_42_45 = (unsigned int)&pbDst[-screen_buf_end + 1023] >> 8;
				if ( tile_42_45 > 45 )
				{
					tmp_pbDst = pbDst - 12288;
					pdung_cels += 288;
LABEL_205:
					i = 16;
					do
					{
						if ( (unsigned int)tmp_pbDst < screen_buf_end )
						{
							j = 8;
							do
							{
								temp32 = *(_DWORD *)pdung_cels;
								pdung_cels += 4;
								*(_DWORD *)tmp_pbDst = temp32;
								tmp_pbDst += 4;
								--j;
							}
							while ( j );
						}
						else
						{
							pdung_cels += 32;
							tmp_pbDst += 32;
						}
						tmp_pbDst -= 800;
						--i;
					}
					while ( i );
					return;
				}
				world_tbl = WorldTbl3x16[tile_42_45];
				pdung_cels += *(int *)((char *)WorldTbl17_1 + world_tbl);
				tmp_pbDst -= 192 * world_tbl;
				xx_32 = 30 - (world_tbl >> 1);
			}
			do
			{
				for ( n_draw_shift = (unsigned int)(32 - xx_32) >> 2; n_draw_shift; --n_draw_shift )
				{
					temp32 = *(_DWORD *)pdung_cels;
					pdung_cels += 4;
					*(_DWORD *)tmp_pbDst = temp32;
					tmp_pbDst += 4;
				}
				if ( (32 - (_BYTE)xx_32) & 2 )
				{
					temp16 = *(_WORD *)pdung_cels;
					pdung_cels += 4;
					*(_WORD *)tmp_pbDst = temp16;
					tmp_pbDst += 2;
				}
				tmp_pbDst = &tmp_pbDst[xx_32 - 800];
				xx_32 -= 2;
			}
			while ( xx_32 >= 0 );
			goto LABEL_205;
	}
}

void __fastcall world_draw_black_tile(unsigned char *pbDst)
{
	unsigned char *tmp_pbDst; // edi MAPDST
	signed int xx_32; // edx
	signed int i; // ebx MAPDST
	signed int j; // ecx MAPDST
	signed int yy_32; // edx

	tmp_pbDst = pbDst;
	xx_32 = 30;
	for ( i = 1; ; ++i )
	{
		tmp_pbDst += xx_32;
		j = i;
		do
		{
			*(_DWORD *)tmp_pbDst = 0;
			tmp_pbDst += 4;
			--j;
		}
		while ( j );
		tmp_pbDst = &tmp_pbDst[xx_32 - 832];
		if ( !xx_32 )
			break;
		xx_32 -= 2;
	}
	yy_32 = 2;
	i = 15;
	do
	{
		tmp_pbDst += yy_32;
		j = i;
		do
		{
			*(_DWORD *)tmp_pbDst = 0;
			tmp_pbDst += 4;
			--j;
		}
		while ( j );
		tmp_pbDst = &tmp_pbDst[yy_32 - 832];
		--i;
		yy_32 += 2;
	}
	while ( yy_32 != 32 );
}
