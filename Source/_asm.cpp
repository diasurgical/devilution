static __inline void asm_cel_light_edge(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_cel_light_square(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_trans_light_cel_0_2(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_trans_light_edge_0_2(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_trans_light_square_0_2(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_trans_light_cel_1_3(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_trans_light_edge_1_3(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline void asm_trans_light_square_1_3(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src);
static __inline unsigned int asm_trans_light_mask(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src, unsigned int mask);

static __inline void asm_cel_light_edge(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	unsigned char l = w >> 1;

	if (w & 1) {
		(*dst)[0] = tbl[(*src)[0]];
		(*src)++;
		(*dst)++;
	}
	if (l & 1) {
		(*dst)[0] = tbl[(*src)[0]];
		(*dst)[1] = tbl[(*src)[1]];
		*src += 2;
		*dst += 2;
	}

	asm_cel_light_square(l >> 1, tbl, dst, src);
}

static __inline void asm_cel_light_square(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	for (; w; --w) {
		(*dst)[0] = tbl[(*src)[0]];
		(*dst)[1] = tbl[(*src)[1]];
		(*dst)[2] = tbl[(*src)[2]];
		(*dst)[3] = tbl[(*src)[3]];
		*src += 4;
		*dst += 4;
	}
}

static __inline void asm_trans_light_cel_0_2(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	if (!(w & 1)) {
		asm_trans_light_edge_1_3(w >> 1, tbl, dst, src);
	} else {
		(*src)++;
		(*dst)++;
		asm_trans_light_edge_0_2(w >> 1, tbl, dst, src);
	}
}

static __inline void asm_trans_light_edge_0_2(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	unsigned char l = w >> 1;

	if (w & 1) {
		(*dst)[0] = tbl[(*src)[0]];
		*src += 2;
		*dst += 2;
	}
	if (l) {
		asm_trans_light_square_0_2(l, tbl, dst, src);
	}
}

static __inline void asm_trans_light_square_0_2(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	for (; w; --w) {
		(*dst)[0] = tbl[(*src)[0]];
		(*dst)[2] = tbl[(*src)[2]];
		*src += 4;
		*dst += 4;
	}
}

static __inline void asm_trans_light_cel_1_3(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	if (!(w & 1)) {
		asm_trans_light_edge_0_2(w >> 1, tbl, dst, src);
	} else {
		(*dst)[0] = tbl[(*src)[0]];
		(*src)++;
		(*dst)++;
		asm_trans_light_edge_1_3(w >> 1, tbl, dst, src);
	}
}

static __inline void asm_trans_light_edge_1_3(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	unsigned char l = w >> 1;

	if (w & 1) {
		(*dst)[1] = tbl[(*src)[1]];
		*src += 2;
		*dst += 2;
	}
	if (l) {
		asm_trans_light_square_1_3(l, tbl, dst, src);
	}
}

static __inline void asm_trans_light_square_1_3(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src)
{
	for (; w; --w) {
		(*dst)[1] = tbl[(*src)[1]];
		(*dst)[3] = tbl[(*src)[3]];
		*src += 4;
		*dst += 4;
	}
}

static __inline unsigned int asm_trans_light_mask(unsigned char w, BYTE *tbl, BYTE **dst, BYTE **src, unsigned int mask)
{
	for (; w; --w, (*src)++, (*dst)++, mask *= 2) {
		if (mask & 0x80000000)
			(*dst)[0] = tbl[(*src)[0]];
	}

	return mask;
}
