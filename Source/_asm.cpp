// black/void
inline void asm_cel_black_edge(unsigned char w, BYTE *&dst);
inline void asm_cel_black_square(unsigned char w, BYTE *&dst);
inline void asm_trans_black_mask(unsigned char w, BYTE *&dst, unsigned int mask);
inline void asm_trans_black_cel_0_2(unsigned char w, BYTE *&dst);
inline void asm_trans_black_edge_0_2(unsigned char w, BYTE *&dst);
inline void asm_trans_black_square_0_2(unsigned char w, BYTE *&dst);
inline void asm_trans_black_cel_1_3(unsigned char w, BYTE *&dst);
inline void asm_trans_black_edge_1_3(unsigned char w, BYTE *&dst);
inline void asm_trans_black_square_1_3(unsigned char w, BYTE *&dst);

inline void asm_cel_black_edge(unsigned char w, BYTE *&dst)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[0] = 0;
		dst++;
	}
	if ( l & 1 )
	{
		dst[0] = 0;
		dst[1] = 0;
		dst += 2;
	}

	asm_cel_black_square(l >> 1, dst);
}

inline void asm_cel_black_square(unsigned char w, BYTE *&dst)
{
	for ( ; w; --w )
	{
		dst[0] = 0;
		dst[1] = 0;
		dst[2] = 0;
		dst[3] = 0;
		dst += 4;
	}
}

inline void asm_trans_black_mask(unsigned char w, BYTE *&dst, unsigned int mask)
{
	for ( ; w; --w, dst++, mask *= 2 )
	{
		if ( mask & 0x80000000 )
			dst[0] = 0;
	}
}

inline void asm_trans_black_cel_0_2(unsigned char w, BYTE *&dst)
{
	if ( !(w & 1) )
	{
		asm_trans_black_edge_1_3(w >> 1, dst);
	}
	else
	{
		dst++;
		asm_trans_black_edge_0_2(w >> 1, dst);
	}
}

inline void asm_trans_black_edge_0_2(unsigned char w, BYTE *&dst)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[0] = 0;
		dst += 2;
	}
	if ( l )
	{
		asm_trans_black_square_0_2(l, dst);
	}
}

inline void asm_trans_black_square_0_2(unsigned char w, BYTE *&dst)
{
	for ( ; w; --w )
	{
		dst[0] = 0;
		dst[2] = 0;
		dst += 4;
	}
}

inline void asm_trans_black_cel_1_3(unsigned char w, BYTE *&dst)
{
	if ( !(w & 1) )
	{
		asm_trans_black_edge_0_2(w >> 1, dst);
	}
	else
	{
		dst[0] = 0;
		dst++;
		asm_trans_black_edge_1_3(w >> 1, dst);
	}
}

inline void asm_trans_black_edge_1_3(unsigned char w, BYTE *&dst)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[1] = 0;
		dst += 2;
	}
	if ( l )
	{
		asm_trans_black_square_1_3(l, dst);
	}
}

inline void asm_trans_black_square_1_3(unsigned char w, BYTE *&dst)
{
	for ( ; w; --w )
	{
		dst[1] = 0;
		dst[3] = 0;
		dst += 4;
	}
}

// without lighting
inline void asm_cel_solid_edge(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_cel_solid_square(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_trans_solid_mask(unsigned char w, BYTE *&dst, BYTE *&src, unsigned int mask);
inline void asm_trans_solid_cel_0_2(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_trans_solid_edge_0_2(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_trans_solid_square_0_2(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_trans_solid_cel_1_3(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_trans_solid_edge_1_3(unsigned char w, BYTE *&dst, BYTE *&src);
inline void asm_trans_solid_square_1_3(unsigned char w, BYTE *&dst, BYTE *&src);

inline void asm_cel_solid_edge(unsigned char w, BYTE *&dst, BYTE *&src)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[0] = src[0];
		src++;
		dst++;
	}
	if ( l & 1 )
	{
		dst[0] = src[0];
		dst[1] = src[1];
		src += 2;
		dst += 2;
	}

	asm_cel_solid_square(l >> 1, dst, src);
}

inline void asm_cel_solid_square(unsigned char w, BYTE *&dst, BYTE *&src)
{
	for ( ; w; --w )
	{
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];
		dst[3] = src[3];
		src += 4;
		dst += 4;
	}
}

inline void asm_trans_solid_mask(unsigned char w, BYTE *&dst, BYTE *&src, unsigned int mask)
{
	for ( ; w; --w, src++, dst++, mask *= 2 )
	{
		if ( mask & 0x80000000 )
			dst[0] = src[0];
	}
}

inline void asm_trans_solid_cel_0_2(unsigned char w, BYTE *&dst, BYTE *&src)
{
	if ( !(w & 1) )
	{
		asm_trans_solid_edge_1_3(w >> 1, dst, src);
	}
	else
	{
		src++;
		dst++;
		asm_trans_solid_edge_0_2(w >> 1, dst, src);
	}
}

inline void asm_trans_solid_edge_0_2(unsigned char w, BYTE *&dst, BYTE *&src)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[0] = src[0];
		src += 2;
		dst += 2;
	}
	if ( l )
	{
		asm_trans_solid_square_0_2(l, dst, src);
	}
}

inline void asm_trans_solid_square_0_2(unsigned char w, BYTE *&dst, BYTE *&src)
{
	for ( ; w; --w )
	{
		dst[0] = src[0];
		dst[2] = src[2];
		src += 4;
		dst += 4;
	}
}

inline void asm_trans_solid_cel_1_3(unsigned char w, BYTE *&dst, BYTE *&src)
{
	if ( !(w & 1) )
	{
		asm_trans_solid_edge_0_2(w >> 1, dst, src);
	}
	else
	{
		dst[0] = src[0];
		src++;
		dst++;
		asm_trans_solid_edge_1_3(w >> 1, dst, src);
	}
}

inline void asm_trans_solid_edge_1_3(unsigned char w, BYTE *&dst, BYTE *&src)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[1] = src[1];
		src += 2;
		dst += 2;
	}
	if ( l )
	{
		asm_trans_solid_square_1_3(l, dst, src);
	}
}

inline void asm_trans_solid_square_1_3(unsigned char w, BYTE *&dst, BYTE *&src)
{
	for ( ; w; --w )
	{
		dst[1] = src[1];
		dst[3] = src[3];
		src += 4;
		dst += 4;
	}
}

// with lighting
inline void asm_cel_light_edge(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_cel_light_square(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_trans_light_mask(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src, unsigned int mask);
inline void asm_trans_light_cel_0_2(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_trans_light_edge_0_2(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_trans_light_square_0_2(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_trans_light_cel_1_3(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_trans_light_edge_1_3(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);
inline void asm_trans_light_square_1_3(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src);

inline void asm_cel_light_edge(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[0] = tbl[src[0]];
		src++;
		dst++;
	}
	if ( l & 1 )
	{
		dst[0] = tbl[src[0]];
		dst[1] = tbl[src[1]];
		src += 2;
		dst += 2;
	}

	asm_cel_light_square(l >> 1, tbl, dst, src);
}

inline void asm_cel_light_square(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	for ( ; w; --w )
	{
		dst[0] = tbl[src[0]];
		dst[1] = tbl[src[1]];
		dst[2] = tbl[src[2]];
		dst[3] = tbl[src[3]];
		src += 4;
		dst += 4;
	}
}

inline void asm_trans_light_mask(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src, unsigned int mask)
{
	for ( ; w; --w, src++, dst++, mask *= 2 )
	{
		if ( mask & 0x80000000 )
			dst[0] = tbl[src[0]];
	}
}

inline void asm_trans_light_cel_0_2(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	if ( !(w & 1) )
	{
		asm_trans_light_edge_1_3(w >> 1, tbl, dst, src);
	}
	else
	{
		src++;
		dst++;
		asm_trans_light_edge_0_2(w >> 1, tbl, dst, src);
	}
}

inline void asm_trans_light_edge_0_2(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[0] = tbl[src[0]];
		src += 2;
		dst += 2;
	}
	if ( l )
	{
		asm_trans_light_square_0_2(l, tbl, dst, src);
	}
}

inline void asm_trans_light_square_0_2(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	for ( ; w; --w )
	{
		dst[0] = tbl[src[0]];
		dst[2] = tbl[src[2]];
		src += 4;
		dst += 4;
	}
}

inline void asm_trans_light_cel_1_3(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	if ( !(w & 1) )
	{
		asm_trans_light_edge_0_2(w >> 1, tbl, dst, src);
	}
	else
	{
		dst[0] = tbl[src[0]];
		src++;
		dst++;
		asm_trans_light_edge_1_3(w >> 1, tbl, dst, src);
	}
}

inline void asm_trans_light_edge_1_3(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	unsigned char l = w >> 1;

	if ( w & 1 )
	{
		dst[1] = tbl[src[1]];
		src += 2;
		dst += 2;
	}
	if ( l )
	{
		asm_trans_light_square_1_3(l, tbl, dst, src);
	}
}

inline void asm_trans_light_square_1_3(unsigned char w, BYTE *tbl, BYTE *&dst, BYTE *&src)
{
	for ( ; w; --w )
	{
		dst[1] = tbl[src[1]];
		dst[3] = tbl[src[3]];
		src += 4;
		dst += 4;
	}
}
