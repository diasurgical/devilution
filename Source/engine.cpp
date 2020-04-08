/**
 * @file engine.cpp
 *
 * Implementation of basic engine helper functions:
 * - Sprite blitting
 * - Drawing
 * - Angle calculation
 * - RNG
 * - Memory allocation
 * - File loading
 * - Video playback
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

#ifdef USE_ASM
#pragma warning(disable : 4731) // frame pointer register 'ebp' modified by inline assembly code
#endif

char gbPixelCol;  // automap pixel color 8-bit (palette entry)
BOOL gbRotateMap; // flip - if y < x
int orgseed;
/** Width of sprite being blitted */
int sgnWidth;
/** Current game seed */
int sglGameSeed;
static CCritSect sgMemCrit;
int SeedCount;
BOOL gbNotInView; // valid - if x/y are in bounds

/**
 * Specifies the increment used in the Borland C/C++ pseudo-random.
 */
const int RndInc = 1;

/**
 * Specifies the multiplier used in the Borland C/C++ pseudo-random number generator algorithm.
 */
const int RndMult = 0x015A4E35;

/**
 * @brief Find the start of a CEL frame
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nDataSize Will be set to frame size
 */
__FINLINE BYTE *CelGetFrame(BYTE *pCelBuff, int nCel, int *nDataSize)
{
	DWORD *pFrameTable;
	DWORD nCellStart;

	pFrameTable = (DWORD *)pCelBuff;
	nCellStart = SwapLE32(pFrameTable[nCel]);
	*nDataSize = SwapLE32(pFrameTable[nCel + 1]) - nCellStart;

	return pCelBuff + nCellStart;
}

/**
 * @brief Calculate the size of a CEL frame
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @return Size of CEL in bytes
 */
__FINLINE int CelGetFrameSize(BYTE *pCelBuff, int nCel)
{
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)pCelBuff;

	return SwapLE32(pFrameTable[nCel + 1]) - SwapLE32(pFrameTable[nCel]);
}

/**
 * @brief Blit CEL sprite to the given buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CEL pixel stream (run-length encoded)
 * @param nDataSize Size of CEL in bytes
 * @param nWidth Width of sprite
 */
void CelBlit(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
	int w;

	/// ASSERT: assert(pDecodeTo != NULL);
	if (pDecodeTo == NULL)
		return;
	/// ASSERT: assert(pRLEBytes != NULL);
	if (pRLEBytes == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		esi, pRLEBytes
		mov		edi, pDecodeTo
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label6
		sub		edx, eax
		mov		ecx, eax
		shr		ecx, 1
		jnb		label3
		movsb
		jecxz	label5
	label3:
		shr		ecx, 1
		jnb		label4
		movsw
		jecxz	label5
	label4:
		rep movsd
	label5:
		or		edx, edx
		jz		label7
		jmp		label2
	label6:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label7:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	}
#else
	int i;
	BYTE width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;

	for (; src != &pRLEBytes[nDataSize]; dst -= BUFFER_WIDTH + w) {
		for (i = w; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (width & 1) {
					dst[0] = src[0];
					src++;
					dst++;
				}
				width >>= 1;
				if (width & 1) {
					dst[0] = src[0];
					dst[1] = src[1];
					src += 2;
					dst += 2;
				}
				width >>= 1;
				for (; width; width--) {
					dst[0] = src[0];
					dst[1] = src[1];
					dst[2] = src[2];
					dst[3] = src[3];
					src += 4;
					dst += 4;
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Blit CEL sprite to the back buffer at the given coordinates
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 */
void CelDraw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth)
{
	int nDataSize;
	BYTE *pRLEBytes;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pRLEBytes = CelGetFrame(pCelBuff, nCel, &nDataSize);
	CelBlit(&gpBuffer[sx + PitchTbl[sy]], pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Blit a given CEL frame to the given buffer
 * @param pBuff Target buffer
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 */
void CelBlitFrame(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth)
{
	int nDataSize;
	BYTE *pRLEBytes;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(pBuff != NULL);
	if (pBuff == NULL)
		return;

	pRLEBytes = CelGetFrame(pCelBuff, nCel, &nDataSize);
	CelBlit(pBuff, pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Same as CelDraw but with the option to skip parts of the top and bottom of the sprite
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedDraw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	BYTE *pRLEBytes;
	DWORD *pFrameTable;
	int nDataStart, nDataSize, nDataCap;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	CelBlit(
	    &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]],
	    pRLEBytes + nDataStart,
	    nDataSize,
	    nWidth);
}

/**
 * @brief Same as CelBlit but with the option to skip parts of the top and bottom of the sprite
 * @param pBuff Target buffer
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedBlit(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	BYTE *pRLEBytes;
	DWORD *pFrameTable;
	int nDataStart, nDataSize, nDataCap;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(pBuff != NULL);
	if (pBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	CelBlit(pBuff, pRLEBytes + nDataStart, nDataSize, nWidth);
}

/**
 * @brief Blit CEL sprite, and apply lighting, to the given buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CEL pixel stream (run-length encoded)
 * @param nDataSize Size of CEL in bytes
 * @param nWidth Width of sprite
 */
void CelBlitLight(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
	int w;
	BYTE *tbl;

	/// ASSERT: assert(pDecodeTo != NULL);
	if (pDecodeTo == NULL)
		return;
	/// ASSERT: assert(pRLEBytes != NULL);
	if (pRLEBytes == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		eax, light_table_index
		shl		eax, 8
		add		eax, pLightTbl
		mov		tbl, eax
		mov		esi, pRLEBytes
		mov		edi, pDecodeTo
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label3
		push	ebx
		mov		ebx, tbl
		sub		edx, eax
		mov		ecx, eax
		push	edx
		call	CelBlitLightEntry
		pop		edx
		pop		ebx
		or		edx, edx
		jnz		label2
		jmp		label4
	label3:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label4:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
		jmp		labexit
	}

	/* Assembly Macro */
	// clang-format off
	__asm {
	CelBlitLightEntry:
		shr		cl, 1
		jnb		label5
		mov		dl, [esi]
		mov		dl, [ebx+edx]
		mov		[edi], dl
		add		esi, 1
		add		edi, 1
	label5:
		shr		cl, 1
		jnb		label6
		mov		dl, [esi]
		mov		ch, [ebx+edx]
		mov		[edi], ch
		mov		dl, [esi+1]
		mov		ch, [ebx+edx]
		mov		[edi+1], ch
		add		esi, 2
		add		edi, 2
	label6:
		test	cl, cl
		jz		labret
	label7:
		mov		eax, [esi]
		add		esi, 4
		mov		dl, al
		mov		ch, [ebx+edx]
		mov		dl, ah
		ror		eax, 10h
		mov		[edi], ch
		mov		ch, [ebx+edx]
		mov		dl, al
		mov		[edi+1], ch
		mov		ch, [ebx+edx]
		mov		dl, ah
		mov		[edi+2], ch
		mov		ch, [ebx+edx]
		mov		[edi+3], ch
		add		edi, 4
		dec		cl
		jnz		label7
	labret:
		retn
	}
	// clang-format on

	__asm {
	labexit:
	}
#else
	int i;
	BYTE width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	tbl = &pLightTbl[light_table_index * 256];
	w = nWidth;

	for (; src != &pRLEBytes[nDataSize]; dst -= BUFFER_WIDTH + w) {
		for (i = w; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (width & 1) {
					dst[0] = tbl[src[0]];
					src++;
					dst++;
				}
				width >>= 1;
				if (width & 1) {
					dst[0] = tbl[src[0]];
					dst[1] = tbl[src[1]];
					src += 2;
					dst += 2;
				}
				width >>= 1;
				for (; width; width--) {
					dst[0] = tbl[src[0]];
					dst[1] = tbl[src[1]];
					dst[2] = tbl[src[2]];
					dst[3] = tbl[src[3]];
					src += 4;
					dst += 4;
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Blit CEL sprite, and apply lighting, to the given buffer, with transparancy applied
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CEL pixel stream (run-length encoded)
 * @param nDataSize Size of CEL in bytes
 * @param nWidth Width of sprite
 */
void CelBlitLightTrans(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
	int w;
	BOOL shift;
	BYTE *tbl;

	/// ASSERT: assert(pDecodeTo != NULL);
	if (pDecodeTo == NULL)
		return;
	/// ASSERT: assert(pRLEBytes != NULL);
	if (pRLEBytes == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		eax, light_table_index
		shl		eax, 8
		add		eax, pLightTbl
		mov		tbl, eax
		mov		esi, pRLEBytes
		mov		edi, pDecodeTo
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
		mov		eax, edi
		and		eax, 1
		mov		shift, eax
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label9
		push	ebx
		mov		ebx, tbl
		sub		edx, eax
		mov		ecx, eax
		mov		eax, edi
		and		eax, 1
		cmp		eax, shift
		jnz		label5
		shr		ecx, 1
		jnb		label3
		inc		esi
		inc		edi
		jecxz	label8
		jmp		label6
	label3:
		shr		ecx, 1
		jnb		label4
		inc		esi
		inc		edi
		lodsb
		xlat
		stosb
		jecxz	label8
	label4:
		lodsd
		inc		edi
		ror		eax, 8
		xlat
		stosb
		ror		eax, 10h
		inc		edi
		xlat
		stosb
		loop	label4
		jmp		label8
	label5:
		shr		ecx, 1
		jnb		label6
		lodsb
		xlat
		stosb
		jecxz	label8
		jmp		label3
	label6:
		shr		ecx, 1
		jnb		label7
		lodsb
		xlat
		stosb
		inc		esi
		inc		edi
		jecxz	label8
	label7:
		lodsd
		xlat
		stosb
		inc		edi
		ror		eax, 10h
		xlat
		stosb
		inc		edi
		loop	label7
	label8:
		pop		ebx
		or		edx, edx
		jz		label10
		jmp		label2
	label9:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label10:
		sub		edi, w
		mov		eax, shift
		inc		eax
		and		eax, 1
		mov		shift, eax
		cmp		ebx, esi
		jnz		label1
	}
#else
	int i;
	BYTE width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	tbl = &pLightTbl[light_table_index * 256];
	w = nWidth;
	shift = (BYTE)dst & 1;

	for (; src != &pRLEBytes[nDataSize]; dst -= BUFFER_WIDTH + w, shift = (shift + 1) & 1) {
		for (i = w; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (((BYTE)dst & 1) == shift) {
					if (!(width & 1)) {
						goto L_ODD;
					} else {
						src++;
						dst++;
					L_EVEN:
						width >>= 1;
						if (width & 1) {
							dst[0] = tbl[src[0]];
							src += 2;
							dst += 2;
						}
						width >>= 1;
						for (; width; width--) {
							dst[0] = tbl[src[0]];
							dst[2] = tbl[src[2]];
							src += 4;
							dst += 4;
						}
					}
				} else {
					if (!(width & 1)) {
						goto L_EVEN;
					} else {
						dst[0] = tbl[src[0]];
						src++;
						dst++;
					L_ODD:
						width >>= 1;
						if (width & 1) {
							dst[1] = tbl[src[1]];
							src += 2;
							dst += 2;
						}
						width >>= 1;
						for (; width; width--) {
							dst[1] = tbl[src[1]];
							dst[3] = tbl[src[3]];
							src += 4;
							dst += 4;
						}
					}
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Blit CEL sprite, and apply lighting, to the back buffer at the given coordinates
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 */
void CelDrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth)
{
	int nDataSize;
	BYTE *pDecodeTo, *pRLEBytes;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pRLEBytes = CelGetFrame(pCelBuff, nCel, &nDataSize);
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy]];

	if (light_table_index)
		CelBlitLight(pDecodeTo, pRLEBytes, nDataSize, nWidth);
	else
		CelBlit(pDecodeTo, pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Same as CelDrawLight but with the option to skip parts of the top and bottom of the sprite
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedDrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nDataCap;
	BYTE *pRLEBytes, *pDecodeTo;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	if (light_table_index)
		CelBlitLight(pDecodeTo, pRLEBytes, nDataSize, nWidth);
	else
		CelBlit(pDecodeTo, pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Same as CelBlitLightTrans but with the option to skip parts of the top and bottom of the sprite
 * @param pBuff Target buffer
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedBlitLightTrans(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nDataCap;
	BYTE *pRLEBytes;
	DWORD *pFrameTable;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(pBuff != NULL);
	if (pBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;

	if (cel_transparency_active)
		CelBlitLightTrans(pBuff, pRLEBytes, nDataSize, nWidth);
	else if (light_table_index)
		CelBlitLight(pBuff, pRLEBytes, nDataSize, nWidth);
	else
		CelBlit(pBuff, pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Blit CEL sprite, and apply lighting, to the back buffer at the given coordinates, translated to a red hue
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 * @param light Light shade to use
 */
void CelDrawLightRed(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light)
{
	int nDataStart, nDataSize, nDataCap, w, idx;
	BYTE *pRLEBytes, *dst, *tbl;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;
	dst = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	idx = light4flag ? 1024 : 4096;
	if (light == 2)
		idx += 256; // gray colors
	if (light >= 4)
		idx += (light - 1) << 8;

#ifdef USE_ASM
	__asm {
		mov		eax, pLightTbl
		add		eax, idx
		mov		tbl, eax
		mov		esi, pRLEBytes
		mov		edi, dst
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax /* use C for w? w = BUFFER_WIDTH + nWidth */
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		mov		al, [esi]
		inc		esi
		test	al, al
		js		label4
		push	ebx
		mov		ebx, tbl
		sub		edx, eax
		mov		ecx, eax
	label3:
		mov		al, [esi]
		inc		esi
		mov		al, [ebx+eax]
		mov		[edi], al
		dec		ecx
		lea		edi, [edi+1]
		jnz		label3
		pop		ebx
		test	edx, edx
		jz		label5
		jmp		label2
	label4:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label5:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	}
#else
	BYTE width;
	BYTE *end;

	tbl = &pLightTbl[idx];
	end = &pRLEBytes[nDataSize];

	for (; pRLEBytes != end; dst -= BUFFER_WIDTH + nWidth) {
		for (w = nWidth; w;) {
			width = *pRLEBytes++;
			if (!(width & 0x80)) {
				w -= width;
				while (width) {
					*dst = tbl[*pRLEBytes];
					pRLEBytes++;
					dst++;
					width--;
				}
			} else {
				width = -(char)width;
				dst += width;
				w -= width;
			}
		}
	}
#endif
}

/**
 * @brief Same as CelBlit but checks for drawing outside the buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CEL pixel stream (run-length encoded)
 * @param nDataSize Size of CEL in bytes
 * @param nWidth Width of sprite
 */
void CelBlitSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
	int w;

	/// ASSERT: assert(pDecodeTo != NULL);
	if (pDecodeTo == NULL)
		return;
	/// ASSERT: assert(pRLEBytes != NULL);
	if (pRLEBytes == NULL)
		return;
	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		esi, pRLEBytes
		mov		edi, pDecodeTo
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label7
		sub		edx, eax
		cmp		edi, gpBufEnd
		jb		label3
		add		esi, eax
		add		edi, eax
		jmp		label6
	label3:
		mov		ecx, eax
		shr		ecx, 1
		jnb		label4
		movsb
		jecxz	label6
	label4:
		shr		ecx, 1
		jnb		label5
		movsw
		jecxz	label6
	label5:
		rep movsd
	label6:
		or		edx, edx
		jz		label8
		jmp		label2
	label7:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label8:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	}
#else
	int i;
	BYTE width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;

	for (; src != &pRLEBytes[nDataSize]; dst -= BUFFER_WIDTH + w) {
		for (i = w; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (dst < gpBufEnd) {
					if (width & 1) {
						dst[0] = src[0];
						src++;
						dst++;
					}
					width >>= 1;
					if (width & 1) {
						dst[0] = src[0];
						dst[1] = src[1];
						src += 2;
						dst += 2;
					}
					width >>= 1;
					for (; width; width--) {
						dst[0] = src[0];
						dst[1] = src[1];
						dst[2] = src[2];
						dst[3] = src[3];
						src += 4;
						dst += 4;
					}
				} else {
					src += width;
					dst += width;
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Same as CelClippedDraw but checks for drawing outside the buffer
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedDrawSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	BYTE *pRLEBytes;
	DWORD *pFrameTable;
	int nDataStart, nDataSize, nDataCap;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	CelBlitSafe(
	    &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]],
	    pRLEBytes + nDataStart,
	    nDataSize,
	    nWidth);
}

/**
 * @brief Same as CelClippedBlit but checks for drawing outside the buffer
 * @param pBuff Target buffer
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedBlitSafe(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	BYTE *pRLEBytes;
	DWORD *pFrameTable;
	int nDataStart, nDataSize, nDataCap;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(pBuff != NULL);
	if (pBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (CelCap == 8)
		nDataCap = 0;

	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	CelBlitSafe(pBuff, pRLEBytes + nDataStart, nDataSize, nWidth);
}

/**
 * @brief Same as CelBlitLight but checks for drawing outside the buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CEL pixel stream (run-length encoded)
 * @param nDataSize Size of CEL in bytes
 * @param nWidth Width of sprite
 */
void CelBlitLightSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
	int w;
	BYTE *tbl;

	/// ASSERT: assert(pDecodeTo != NULL);
	if (pDecodeTo == NULL)
		return;
	/// ASSERT: assert(pRLEBytes != NULL);
	if (pRLEBytes == NULL)
		return;
	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		eax, light_table_index
		shl		eax, 8
		add		eax, pLightTbl
		mov		tbl, eax
		mov		esi, pRLEBytes
		mov		edi, pDecodeTo
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label5
		push	ebx
		mov		ebx, tbl
		sub		edx, eax
		cmp		edi, gpBufEnd
		jb		label3
		add		esi, eax
		add		edi, eax
		jmp		label4
	label3:
		mov		ecx, eax
		push	edx
		call	Cel2DecDatLightEntry
		pop		edx
	label4:
		pop		ebx
		or		edx, edx
		jz		label6
		jmp		label2
	label5:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label6:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
		jmp		labexit
	}

	/* Assembly Macro */
	// clang-format off
	__asm {
	Cel2DecDatLightEntry:
		shr		cl, 1
		jnb		label7
		mov		dl, [esi]
		mov		dl, [ebx+edx]
		mov		[edi], dl
		add		esi, 1
		add		edi, 1
	label7:
		shr		cl, 1
		jnb		label8
		mov		dl, [esi]
		mov		ch, [ebx+edx]
		mov		[edi], ch
		mov		dl, [esi+1]
		mov		ch, [ebx+edx]
		mov		[edi+1], ch
		add		esi, 2
		add		edi, 2
	label8:
		test	cl, cl
		jz		labret
	label9:
		mov		eax, [esi]
		add		esi, 4
		mov		dl, al
		mov		ch, [ebx+edx]
		mov		dl, ah
		ror		eax, 10h
		mov		[edi], ch
		mov		ch, [ebx+edx]
		mov		dl, al
		mov		[edi+1], ch
		mov		ch, [ebx+edx]
		mov		dl, ah
		mov		[edi+2], ch
		mov		ch, [ebx+edx]
		mov		[edi+3], ch
		add		edi, 4
		dec		cl
		jnz		label9
	labret:
		retn
	}
	// clang-format on

	__asm {
	labexit:
	}
#else
	int i;
	BYTE width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	tbl = &pLightTbl[light_table_index * 256];
	w = nWidth;

	for (; src != &pRLEBytes[nDataSize]; dst -= BUFFER_WIDTH + w) {
		for (i = w; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (dst < gpBufEnd) {
					if (width & 1) {
						dst[0] = tbl[src[0]];
						src++;
						dst++;
					}
					width >>= 1;
					if (width & 1) {
						dst[0] = tbl[src[0]];
						dst[1] = tbl[src[1]];
						src += 2;
						dst += 2;
					}
					width >>= 1;
					for (; width; width--) {
						dst[0] = tbl[src[0]];
						dst[1] = tbl[src[1]];
						dst[2] = tbl[src[2]];
						dst[3] = tbl[src[3]];
						src += 4;
						dst += 4;
					}
				} else {
					src += width;
					dst += width;
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Same as CelBlitLightTrans but checks for drawing outside the buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CEL pixel stream (run-length encoded)
 * @param nDataSize Size of CEL in bytes
 * @param nWidth Width of sprite
 */
void CelBlitLightTransSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
	int w;
	BOOL shift;
	BYTE *tbl;

	/// ASSERT: assert(pDecodeTo != NULL);
	if (pDecodeTo == NULL)
		return;
	/// ASSERT: assert(pRLEBytes != NULL);
	if (pRLEBytes == NULL)
		return;
	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		eax, light_table_index
		shl		eax, 8
		add		eax, pLightTbl
		mov		tbl, eax
		mov		esi, pRLEBytes
		mov		edi, pDecodeTo
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
		mov		eax, edi
		and		eax, 1
		mov		shift, eax
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label10
		push	ebx
		mov		ebx, tbl
		sub		edx, eax
		cmp		edi, gpBufEnd
		jb		label3
		add		esi, eax
		add		edi, eax
		jmp		label9
	label3:
		mov		ecx, eax
		mov		eax, edi
		and		eax, 1
		cmp		eax, shift
		jnz		label6
		shr		ecx, 1
		jnb		label4
		inc		esi
		inc		edi
		jecxz	label9
		jmp		label7
	label4:
		shr		ecx, 1
		jnb		label5
		inc		esi
		inc		edi
		lodsb
		xlat
		stosb
		jecxz	label9
	label5:
		lodsd
		inc		edi
		ror		eax, 8
		xlat
		stosb
		ror		eax, 10h
		inc		edi
		xlat
		stosb
		loop	label5
		jmp		label9
	label6:
		shr		ecx, 1
		jnb		label7
		lodsb
		xlat
		stosb
		jecxz	label9
		jmp		label4
	label7:
		shr		ecx, 1
		jnb		label8
		lodsb
		xlat
		stosb
		inc		esi
		inc		edi
		jecxz	label9
	label8:
		lodsd
		xlat
		stosb
		inc		edi
		ror		eax, 10h
		xlat
		stosb
		inc		edi
		loop	label8
	label9:
		pop		ebx
		or		edx, edx
		jz		label11
		jmp		label2
	label10:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label11:
		sub		edi, w
		mov		eax, shift
		inc		eax
		and		eax, 1
		mov		shift, eax
		cmp		ebx, esi
		jnz		label1
	}
#else
	int i;
	BYTE width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	tbl = &pLightTbl[light_table_index * 256];
	w = nWidth;
	shift = (BYTE)dst & 1;

	for (; src != &pRLEBytes[nDataSize]; dst -= BUFFER_WIDTH + w, shift = (shift + 1) & 1) {
		for (i = w; i;) {
			width = *src++;
			if (!(width & 0x80)) {
				i -= width;
				if (dst < gpBufEnd) {
					if (((BYTE)dst & 1) == shift) {
						if (!(width & 1)) {
							goto L_ODD;
						} else {
							src++;
							dst++;
						L_EVEN:
							width >>= 1;
							if (width & 1) {
								dst[0] = tbl[src[0]];
								src += 2;
								dst += 2;
							}
							width >>= 1;
							for (; width; width--) {
								dst[0] = tbl[src[0]];
								dst[2] = tbl[src[2]];
								src += 4;
								dst += 4;
							}
						}
					} else {
						if (!(width & 1)) {
							goto L_EVEN;
						} else {
							dst[0] = tbl[src[0]];
							src++;
							dst++;
						L_ODD:
							width >>= 1;
							if (width & 1) {
								dst[1] = tbl[src[1]];
								src += 2;
								dst += 2;
							}
							width >>= 1;
							for (; width; width--) {
								dst[1] = tbl[src[1]];
								dst[3] = tbl[src[3]];
								src += 4;
								dst += 4;
							}
						}
					}
				} else {
					src += width;
					dst += width;
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Same as CelDrawLight but checks for drawing outside the buffer
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of cel
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelDrawLightSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nDataCap;
	BYTE *pRLEBytes, *pDecodeTo;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (CelCap == 8)
		nDataCap = 0;

	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	if (light_table_index)
		CelBlitLightSafe(pDecodeTo, pRLEBytes, nDataSize, nWidth);
	else
		CelBlitSafe(pDecodeTo, pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Same as CelClippedBlitLightTrans but checks for drawing outside the buffer
 * @param pBuff Target buffer
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of cel
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelClippedBlitLightTransSafe(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nDataCap;
	BYTE *pRLEBytes;
	DWORD *pFrameTable;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (CelCap == 8)
		nDataCap = 0;

	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;

	if (cel_transparency_active)
		CelBlitLightTransSafe(pBuff, pRLEBytes, nDataSize, nWidth);
	else if (light_table_index)
		CelBlitLightSafe(pBuff, pRLEBytes, nDataSize, nWidth);
	else
		CelBlitSafe(pBuff, pRLEBytes, nDataSize, nWidth);
}

/**
 * @brief Same as CelDrawLightRed but checks for drawing outside the buffer
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of cel
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 * @param light Light shade to use
 */
void CelDrawLightRedSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light)
{
	int nDataStart, nDataSize, nDataCap, w, idx;
	BYTE *pRLEBytes, *dst, *tbl;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;

	pFrameTable = (DWORD *)pCelBuff;

	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];
	if (CelCap == 8)
		nDataCap = 0;
	else
		nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;
	dst = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	idx = light4flag ? 1024 : 4096;
	if (light == 2)
		idx += 256; // gray colors
	if (light >= 4)
		idx += (light - 1) << 8;

	tbl = &pLightTbl[idx];

#ifdef USE_ASM
	w = BUFFER_WIDTH + nWidth;

	__asm {
		mov		esi, pRLEBytes
		mov		edi, dst
		mov		ecx, nDataSize
		add		ecx, esi
	label1:
		push	ecx
		mov		edx, nWidth
		xor		ecx, ecx
	label2:
		xor		eax, eax
		mov		al, [esi]
		inc		esi
		test	al, al
		js		label5
		mov		ebx, tbl
		sub		edx, eax
		cmp		edi, gpBufEnd
		jb		label3
		add		esi, eax
		add		edi, eax
		jmp		label4
	label3:
		mov		cl, [esi]
		inc		esi
		mov		cl, [ebx+ecx]
		mov		[edi], cl
		dec		eax
		lea		edi, [edi+1]
		jnz		label3
	label4:
		test	edx, edx
		jz		label6
		jmp		label2
	label5:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label6:
		pop		ecx
		sub		edi, w
		cmp		ecx, esi
		jnz		label1
	}
#else
	BYTE width;
	BYTE *end;

	end = &pRLEBytes[nDataSize];

	for (; pRLEBytes != end; dst -= BUFFER_WIDTH + nWidth) {
		for (w = nWidth; w;) {
			width = *pRLEBytes++;
			if (!(width & 0x80)) {
				w -= width;
				if (dst < gpBufEnd) {
					while (width) {
						*dst = tbl[*pRLEBytes];
						pRLEBytes++;
						dst++;
						width--;
					}
				} else {
					pRLEBytes += width;
					dst += width;
				}
			} else {
				width = -(char)width;
				dst += width;
				w -= width;
			}
		}
	}
#endif
}

/**
 * @brief Blit to a buffer at given coordinates
 * @param pBuff Target buffer
 * @param x Cordinate in pBuff buffer
 * @param y Cordinate in pBuff buffer
 * @param wdt Width of pBuff
 * @param pCelBuff Cel data
 * @param nCel CEL frame number
 * @param nWidth Width of cel
 */
void CelBlitWidth(BYTE *pBuff, int x, int y, int wdt, BYTE *pCelBuff, int nCel, int nWidth)
{
	BYTE *pRLEBytes, *dst, *end;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(pBuff != NULL);
	if (pBuff == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		ebx, pCelBuff
		mov		eax, nCel
		shl		eax, 2
		add		ebx, eax
		mov		eax, [ebx+4]
		sub		eax, [ebx]
		mov		end, eax
		mov		eax, pCelBuff
		add		eax, [ebx]
		mov		pRLEBytes, eax
	}

	dst = &pBuff[y * wdt + x];

	__asm {
		mov		esi, pRLEBytes
		mov		edi, dst
		mov		eax, wdt
		add		eax, nWidth
		mov		wdt, eax
		mov		ebx, end
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label6
		sub		edx, eax
		mov		ecx, eax
		shr		ecx, 1
		jnb		label3
		movsb
		jecxz	label5
	label3:
		shr		ecx, 1
		jnb		label4
		movsw
		jecxz	label5
	label4:
		rep movsd
	label5:
		or		edx, edx
		jz		label7
		jmp		label2
	label6:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label7:
		sub		edi, wdt
		cmp		ebx, esi
		jnz		label1
	}
#else
	int i, nDataSize;
	BYTE width;

	pRLEBytes = CelGetFrame(pCelBuff, nCel, &nDataSize);
	end = &pRLEBytes[nDataSize];
	dst = &pBuff[y * wdt + x];

	for (; pRLEBytes != end; dst -= wdt + nWidth) {
		for (i = nWidth; i;) {
			width = *pRLEBytes++;
			if (!(width & 0x80)) {
				i -= width;
				if (width & 1) {
					dst[0] = pRLEBytes[0];
					pRLEBytes++;
					dst++;
				}
				width >>= 1;
				if (width & 1) {
					dst[0] = pRLEBytes[0];
					dst[1] = pRLEBytes[1];
					pRLEBytes += 2;
					dst += 2;
				}
				width >>= 1;
				while (width) {
					dst[0] = pRLEBytes[0];
					dst[1] = pRLEBytes[1];
					dst[2] = pRLEBytes[2];
					dst[3] = pRLEBytes[3];
					pRLEBytes += 4;
					dst += 4;
					width--;
				}
			} else {
				width = -(char)width;
				dst += width;
				i -= width;
			}
		}
	}
#endif
}

/**
 * @brief Blit a solid colder shape one pixel larger then the given sprite shape, to the back buffer at the given coordianates
 * @param col Color index from current palette
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CEL buffer
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelBlitOutline(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nDataCap, w;
	BYTE *pRLEBytes, *dst;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		ebx, pCelBuff
		mov		eax, nCel
		shl		eax, 2
		add		ebx, eax
		mov		eax, [ebx+4]
		sub		eax, [ebx]
		mov		nDataSize, eax
		mov		edx, pCelBuff
		add		edx, [ebx]
		mov		pRLEBytes, edx
		add		edx, CelSkip
		xor		eax, eax
		mov		ax, [edx]
		mov		nDataStart, eax
		mov		edx, pRLEBytes
		add		edx, CelCap
		mov		ax, [edx]
		mov		nDataCap, eax
	}

	if (nDataStart == 0) return;

	if (CelCap == 8)
		nDataCap = 0;
	if (nDataCap != 0)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;
	dst = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	__asm {
		mov		esi, pRLEBytes
		mov		edi, dst
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label5
		sub		edx, eax
		mov		ecx, eax
		mov		ah, col
	label3:
		lodsb
		or		al, al
		jz		label4
		mov		[edi-BUFFER_WIDTH], ah
		mov		[edi-1], ah
		mov		[edi+1], ah
		mov		[edi+BUFFER_WIDTH], ah
	label4:
		inc		edi
		loop	label3
		or		edx, edx
		jz		label6
		jmp		label2
	label5:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label6:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	}
#else
	BYTE width;
	BYTE *end, *src;
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)&pCelBuff[4 * nCel];
	pRLEBytes = &pCelBuff[pFrameTable[0]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (CelCap == 8)
		nDataCap = 0;

	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize = pFrameTable[1] - pFrameTable[0] - nDataStart;

	src = pRLEBytes + nDataStart;
	end = &src[nDataSize];
	dst = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	for (; src != end; dst -= BUFFER_WIDTH + nWidth) {
		for (w = nWidth; w;) {
			width = *src++;
			if (!(width & 0x80)) {
				w -= width;
				while (width) {
					if (*src++) {
						dst[-BUFFER_WIDTH] = col;
						dst[-1] = col;
						dst[1] = col;
						dst[BUFFER_WIDTH] = col;
					}
					dst++;
					width--;
				}
			} else {
				width = -(char)width;
				dst += width;
				w -= width;
			}
		}
	}
#endif
}

/**
 * @brief Same as CelBlitOutline but checks for drawing outside the buffer
 * @param col Color index from current palette
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CEL buffer
 * @param nCel CEL frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void CelBlitOutlineSafe(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nDataCap, w;
	BYTE *pRLEBytes, *dst;

	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	/// ASSERT: assert(gpBuffer);
	if (gpBuffer == NULL)
		return;

#ifdef USE_ASM
	__asm {
		mov		ebx, pCelBuff
		mov		eax, nCel
		shl		eax, 2
		add		ebx, eax
		mov		eax, [ebx+4]
		sub		eax, [ebx]
		mov		nDataSize, eax
		mov		edx, pCelBuff
		add		edx, [ebx]
		mov		pRLEBytes, edx
		add		edx, CelSkip
		xor		eax, eax
		mov		ax, [edx]
		mov		nDataStart, eax
		mov		edx, pRLEBytes
		add		edx, CelCap
		mov		ax, [edx]
		mov		nDataCap, eax
	}

	if (nDataStart == 0) return;

	if (CelCap == 8)
		nDataCap = 0;
	if (nDataCap != 0)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize -= nDataStart;

	pRLEBytes += nDataStart;
	dst = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	__asm {
		mov		esi, pRLEBytes
		mov		edi, dst
		mov		eax, BUFFER_WIDTH
		add		eax, nWidth
		mov		w, eax
		mov		ebx, nDataSize
		add		ebx, esi
	label1:
		mov		edx, nWidth
	label2:
		xor		eax, eax
		lodsb
		or		al, al
		js		label10
		sub		edx, eax
		mov		ecx, gpBufEnd
		cmp		edi, ecx
		jb		label3
		add		esi, eax
		add		edi, eax
		jmp		label9
	label3:
		sub		ecx, BUFFER_WIDTH
		cmp		edi, ecx
		jnb		label6
		mov		ecx, eax
		mov		ah, col
	label4:
		lodsb
		or		al, al
		jz		label5
		mov		[edi-BUFFER_WIDTH], ah
		mov		[edi-1], ah
		mov		[edi+1], ah
		mov		[edi+BUFFER_WIDTH], ah
	label5:
		inc		edi
		loop	label4
		jmp		label9
	label6:
		mov		ecx, eax
		mov		ah, col
	label7:
		lodsb
		or		al, al
		jz		label8
		mov		[edi-BUFFER_WIDTH], ah
		mov		[edi-1], ah
		mov		[edi+1], ah
	label8:
		inc		edi
		loop	label7
	label9:
		or		edx, edx
		jz		label11
		jmp		label2
	label10:
		neg		al
		add		edi, eax
		sub		edx, eax
		jnz		label2
	label11:
		sub		edi, w
		cmp		ebx, esi
		jnz		label1
	}
#else
	BYTE width;
	BYTE *end, *src;
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)&pCelBuff[4 * nCel];
	pRLEBytes = &pCelBuff[pFrameTable[0]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	nDataCap = *(WORD *)&pRLEBytes[CelCap];
	if (CelCap == 8)
		nDataCap = 0;

	if (nDataCap)
		nDataSize = nDataCap - nDataStart;
	else
		nDataSize = pFrameTable[1] - pFrameTable[0] - nDataStart;

	src = pRLEBytes + nDataStart;
	end = &src[nDataSize];
	dst = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	for (; src != end; dst -= BUFFER_WIDTH + nWidth) {
		for (w = nWidth; w;) {
			width = *src++;
			if (!(width & 0x80)) {
				w -= width;
				if (dst < gpBufEnd) {
					if (dst >= gpBufEnd - BUFFER_WIDTH) {
						while (width) {
							if (*src++) {
								dst[-BUFFER_WIDTH] = col;
								dst[-1] = col;
								dst[1] = col;
							}
							dst++;
							width--;
						}
					} else {
						while (width) {
							if (*src++) {
								dst[-BUFFER_WIDTH] = col;
								dst[-1] = col;
								dst[1] = col;
								dst[BUFFER_WIDTH] = col;
							}
							dst++;
							width--;
						}
					}
				} else {
					src += width;
					dst += width;
				}
			} else {
				width = -(char)width;
				dst += width;
				w -= width;
			}
		}
	}
#endif
}

/**
 * @brief Set the value of a single pixel in the back buffer, checks bounds
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param col Color index from current palette
 */
void ENG_set_pixel(int sx, int sy, BYTE col)
{
	BYTE *dst;

	/// ASSERT: assert(gpBuffer);

	if (sy < 0 || sy >= SCREEN_HEIGHT + SCREEN_Y || sx < SCREEN_X || sx >= SCREEN_WIDTH + SCREEN_X)
		return;

	dst = &gpBuffer[sx + PitchTbl[sy]];

#ifdef USE_ASM
	__asm {
		mov		edi, dst
		cmp		edi, gpBufEnd
		jnb		label1
		mov		al, col
		mov		[edi], al
	label1:
	}
#else
	if (dst < gpBufEnd)
		*dst = col;
#endif
}

/**
 * @brief Set the value of a single pixel in the back buffer to that of gbPixelCol, checks bounds
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 */
void engine_draw_pixel(int sx, int sy)
{
	BYTE *dst;

	/// ASSERT: assert(gpBuffer);

	if (gbRotateMap) {
		if (gbNotInView && (sx < 0 || sx >= SCREEN_HEIGHT + SCREEN_Y || sy < SCREEN_X || sy >= SCREEN_WIDTH + SCREEN_X))
			return;
		dst = &gpBuffer[sy + PitchTbl[sx]];
	} else {
		if (gbNotInView && (sy < 0 || sy >= SCREEN_HEIGHT + SCREEN_Y || sx < SCREEN_X || sx >= SCREEN_WIDTH + SCREEN_X))
			return;
		dst = &gpBuffer[sx + PitchTbl[sy]];
	}

#ifdef USE_ASM
	__asm {
		mov		edi, dst
		cmp		edi, gpBufEnd
		jnb		label1
		mov		al, gbPixelCol
		mov		[edi], al
	label1:
	}
#else
	if (dst < gpBufEnd)
		*dst = gbPixelCol;
#endif
}

/** Macro used in DrawLine() */
#define GG_SWAP(A, B) \
	{                 \
		(A) ^= (B);   \
		(B) ^= (A);   \
		(A) ^= (B);   \
	}
/** Macro used in DrawLine() */
#define GG_ABSOLUTE(I, J, K) (((I) - (J)) * ((K) = (((I) - (J)) < 0 ? -1 : 1)))

/**
 * Symmetric Double Step Line Algorithm
 * by Brian Wyvill
 * from "Graphics Gems", Academic Press, 1990
 *
 * Exact copy from https://github.com/erich666/GraphicsGems/blob/dad26f941e12c8bf1f96ea21c1c04cd2206ae7c9/gems/DoubleLine.c
 * Except:
 * - not in view checks
 * - global variable instead of reverse flag
 * - condition for pixels_left < 0 removed
 *
 * @brief Draw a line on the back buffer
 * @param x0 Back buffer coordinate
 * @param y0 Back buffer coordinate
 * @param x1 Back buffer coordinate
 * @param y1 Back buffer coordinate
 * @param col Color index from current palette
 */
void DrawLine(int x0, int y0, int x1, int y1, BYTE col)
{
	int dx, dy, incr1, incr2, D, x, y, xend, c, pixels_left;
	int sign_x, sign_y, step, i;
	int x1_, y1_;

	gbPixelCol = col;

	gbNotInView = FALSE;
	if (x0 < 0 + SCREEN_X || x0 >= SCREEN_WIDTH + SCREEN_X) {
		gbNotInView = TRUE;
	}
	if (x1 < 0 + SCREEN_X || x1 >= SCREEN_WIDTH + SCREEN_X) {
		gbNotInView = TRUE;
	}
	if (y0 < 0 + SCREEN_Y || y0 >= PANEL_Y) {
		gbNotInView = TRUE;
	}
	if (y1 < 0 + SCREEN_Y || y1 >= PANEL_Y) {
		gbNotInView = TRUE;
	}

	dx = GG_ABSOLUTE(x1, x0, sign_x);
	dy = GG_ABSOLUTE(y1, y0, sign_y);
	/* decide increment sign by the slope sign */
	if (sign_x == sign_y)
		step = 1;
	else
		step = -1;

	if (dy > dx) { /* chooses axis of greatest movement (make
						* dx) */
		GG_SWAP(x0, y0);
		GG_SWAP(x1, y1);
		GG_SWAP(dx, dy);
		gbRotateMap = TRUE;
	} else
		gbRotateMap = FALSE;
	/* note error check for dx==0 should be included here */
	if (x0 > x1) { /* start from the smaller coordinate */
		x = x1;
		y = y1;
		x1_ = x0;
		y1_ = y0;
	} else {
		x = x0;
		y = y0;
		x1_ = x1;
		y1_ = y1;
	}

	/* Note dx=n implies 0 - n or (dx+1) pixels to be set */
	/* Go round loop dx/4 times then plot last 0,1,2 or 3 pixels */
	/* In fact (dx-1)/4 as 2 pixels are already plotted */
	xend = (dx - 1) / 4;
	pixels_left = (dx - 1) % 4; /* number of pixels left over at the end */
	engine_draw_pixel(x, y);
	engine_draw_pixel(x1_, y1_); /* plot first two points */
	incr2 = 4 * dy - 2 * dx;
	if (incr2 < 0) { /* slope less than 1/2 */
		c = 2 * dy;
		incr1 = 2 * c;
		D = incr1 - dx;

		for (i = 0; i < xend; i++) { /* plotting loop */
			++x;
			--x1_;
			if (D < 0) {
				/* pattern 1 forwards */
				engine_draw_pixel(x, y);
				engine_draw_pixel(++x, y);
				/* pattern 1 backwards */
				engine_draw_pixel(x1_, y1_);
				engine_draw_pixel(--x1_, y1_);
				D += incr1;
			} else {
				if (D < c) {
					/* pattern 2 forwards */
					engine_draw_pixel(x, y);
					engine_draw_pixel(++x, y += step);
					/* pattern 2 backwards */
					engine_draw_pixel(x1_, y1_);
					engine_draw_pixel(--x1_, y1_ -= step);
				} else {
					/* pattern 3 forwards */
					engine_draw_pixel(x, y += step);
					engine_draw_pixel(++x, y);
					/* pattern 3 backwards */
					engine_draw_pixel(x1_, y1_ -= step);
					engine_draw_pixel(--x1_, y1_);
				}
				D += incr2;
			}
		} /* end for */

		/* plot last pattern */
		if (pixels_left) {
			if (D < 0) {
				engine_draw_pixel(++x, y); /* pattern 1 */
				if (pixels_left > 1)
					engine_draw_pixel(++x, y);
				if (pixels_left > 2)
					engine_draw_pixel(--x1_, y1_);
			} else {
				if (D < c) {
					engine_draw_pixel(++x, y); /* pattern 2  */
					if (pixels_left > 1)
						engine_draw_pixel(++x, y += step);
					if (pixels_left > 2)
						engine_draw_pixel(--x1_, y1_);
				} else {
					/* pattern 3 */
					engine_draw_pixel(++x, y += step);
					if (pixels_left > 1)
						engine_draw_pixel(++x, y);
					if (pixels_left > 2)
						engine_draw_pixel(--x1_, y1_ -= step);
				}
			}
		} /* end if pixels_left */
	}
	/* end slope < 1/2 */
	else { /* slope greater than 1/2 */
		c = 2 * (dy - dx);
		incr1 = 2 * c;
		D = incr1 + dx;
		for (i = 0; i < xend; i++) {
			++x;
			--x1_;
			if (D > 0) {
				/* pattern 4 forwards */
				engine_draw_pixel(x, y += step);
				engine_draw_pixel(++x, y += step);
				/* pattern 4 backwards */
				engine_draw_pixel(x1_, y1_ -= step);
				engine_draw_pixel(--x1_, y1_ -= step);
				D += incr1;
			} else {
				if (D < c) {
					/* pattern 2 forwards */
					engine_draw_pixel(x, y);
					engine_draw_pixel(++x, y += step);

					/* pattern 2 backwards */
					engine_draw_pixel(x1_, y1_);
					engine_draw_pixel(--x1_, y1_ -= step);
				} else {
					/* pattern 3 forwards */
					engine_draw_pixel(x, y += step);
					engine_draw_pixel(++x, y);
					/* pattern 3 backwards */
					engine_draw_pixel(x1_, y1_ -= step);
					engine_draw_pixel(--x1_, y1_);
				}
				D += incr2;
			}
		} /* end for */
		/* plot last pattern */
		if (pixels_left) {
			if (D > 0) {
				engine_draw_pixel(++x, y += step); /* pattern 4 */
				if (pixels_left > 1)
					engine_draw_pixel(++x, y += step);
				if (pixels_left > 2)
					engine_draw_pixel(--x1_, y1_ -= step);
			} else {
				if (D < c) {
					engine_draw_pixel(++x, y); /* pattern 2  */
					if (pixels_left > 1)
						engine_draw_pixel(++x, y += step);
					if (pixels_left > 2)
						engine_draw_pixel(--x1_, y1_);
				} else {
					/* pattern 3 */
					engine_draw_pixel(++x, y += step);
					if (pixels_left > 1)
						engine_draw_pixel(++x, y);
					if (pixels_left > 2) {
						if (D > c) /* step 3 */
							engine_draw_pixel(--x1_, y1_ -= step);
						else /* step 2 */
							engine_draw_pixel(--x1_, y1_);
					}
				}
			}
		}
	}
}

/**
 * @brief Calculate the best fit direction between two points
 * @param x1 Tile coordinate
 * @param y1 Tile coordinate
 * @param x2 Tile coordinate
 * @param y2 Tile coordinate
 * @return A value from the direction enum
 */
int GetDirection(int x1, int y1, int x2, int y2)
{
	int mx, my;
	int md, ny;

	mx = x2 - x1;
	my = y2 - y1;

	if (mx >= 0) {
		if (my >= 0) {
			md = DIR_S;
			if (2 * mx < my)
				md = DIR_SW;
		} else {
			my = -my;
			md = DIR_E;
			if (2 * mx < my)
				md = DIR_NE;
		}
		if (2 * my < mx)
			return DIR_SE;
	} else {
		if (my >= 0) {
			ny = -mx;
			md = DIR_W;
			if (2 * ny < my)
				md = DIR_SW;
		} else {
			ny = -mx;
			my = -my;
			md = DIR_N;
			if (2 * ny < my)
				md = DIR_NE;
		}
		if (2 * my < ny)
			return DIR_NW;
	}

	return md;
}

/**
 * @brief Set the RNG seed
 * @param s RNG seed
 */
void SetRndSeed(int s)
{
	SeedCount = 0;
	sglGameSeed = s;
	orgseed = s;
}

/**
 * @brief Get the current RNG seed
 * @return RNG seed
 */
int GetRndSeed()
{
	SeedCount++;
	sglGameSeed = RndMult * sglGameSeed + RndInc;
	return abs(sglGameSeed);
}

/**
 * @brief Main RNG function
 * @param idx Unused
 * @param v The upper limit for the return value
 * @return A random number from 0 to (v-1)
 */
int random_(BYTE idx, int v)
{
	if (v <= 0)
		return 0;
	if (v < 0xFFFF)
		return (GetRndSeed() >> 16) % v;
	return GetRndSeed() % v;
}

/**
 * @brief Unallocate all remaining pointers
 * @param show_cursor unused
 */
void engine_debug_trap(BOOL show_cursor)
{
	/*
	TMemBlock *pCurr;

	sgMemCrit.Enter();
	while(sgpMemBlock != NULL) {
		pCurr = sgpMemBlock->pNext;
		SMemFree(sgpMemBlock, "C:\\Diablo\\Direct\\ENGINE.CPP", 1970);
		sgpMemBlock = pCurr;
	}
	sgMemCrit.Leave();
*/
}

/**
 * @brief Multithreaded safe malloc
 * @param dwBytes Byte size to allocate
 */
BYTE *DiabloAllocPtr(DWORD dwBytes)
{
	BYTE *buf;

	sgMemCrit.Enter();
	buf = (BYTE *)SMemAlloc(dwBytes, "C:\\Src\\Diablo\\Source\\ENGINE.CPP", 2236, 0);
	sgMemCrit.Leave();

	if (buf == NULL) {
		ErrDlg(IDD_DIALOG2, GetLastError(), "C:\\Src\\Diablo\\Source\\ENGINE.CPP", 2269);
	}

	return buf;
}

/**
 * @brief Multithreaded safe memfree
 * @param p Memory pointer to free
 */
void mem_free_dbg(void *p)
{
	if (p) {
		sgMemCrit.Enter();
		SMemFree(p, "C:\\Src\\Diablo\\Source\\ENGINE.CPP", 2317, 0);
		sgMemCrit.Leave();
	}
}

/**
 * @brief Load a file in to a buffer
 * @param pszName Path of file
 * @param pdwFileLen Will be set to file size if non-NULL
 * @return Buffer with content of file
 */
BYTE *LoadFileInMem(char *pszName, DWORD *pdwFileLen)
{
	HANDLE file;
	BYTE *buf;
	int fileLen;

	WOpenFile(pszName, &file, FALSE);
	fileLen = WGetFileSize(file, NULL);

	if (pdwFileLen)
		*pdwFileLen = fileLen;

	if (!fileLen)
		app_fatal("Zero length SFILE:\n%s", pszName);

	buf = (BYTE *)DiabloAllocPtr(fileLen);

	WReadFile(file, buf, fileLen);
	WCloseFile(file);

	return buf;
}

/**
 * @brief Load a file in to the given buffer
 * @param pszName Path of file
 * @param p Target buffer
 * @return Size of file
 */
DWORD LoadFileWithMem(const char *pszName, BYTE *p)
{
	DWORD dwFileLen;
	HANDLE hsFile;

	/// ASSERT: assert(pszName);
	if (p == NULL) {
		app_fatal("LoadFileWithMem(NULL):\n%s", pszName);
	}

	WOpenFile(pszName, &hsFile, FALSE);

	dwFileLen = WGetFileSize(hsFile, NULL);
	if (dwFileLen == 0) {
		app_fatal("Zero length SFILE:\n%s", pszName);
	}

	WReadFile(hsFile, p, dwFileLen);
	WCloseFile(hsFile);

	return dwFileLen;
}

/**
 * @brief Apply the color swaps to a CL2 sprite
 * @param p CL2 buffer
 * @param ttbl Palette translation table
 * @param nCel Frame number in CL2 file
 */
void Cl2ApplyTrans(BYTE *p, BYTE *ttbl, int nCel)
{
	int i, nDataSize;
	char width;
	BYTE *dst;
	DWORD *pFrameTable;

	/// ASSERT: assert(p != NULL);
	/// ASSERT: assert(ttbl != NULL);

	for (i = 1; i <= nCel; i++) {
		pFrameTable = (DWORD *)&p[4 * i];
		dst = &p[pFrameTable[0] + 10];
		nDataSize = CelGetFrameSize(p, i) - 10;
		while (nDataSize) {
			width = *dst++;
			nDataSize--;
			/// ASSERT: assert(nDataSize >= 0);
			if (width < 0) {
				width = -width;
				if (width > 65) {
					nDataSize--;
					/// ASSERT: assert(nDataSize >= 0);
					*dst = ttbl[*dst];
					dst++;
				} else {
					nDataSize -= width;
					/// ASSERT: assert(nDataSize >= 0);
					while (width) {
						*dst = ttbl[*dst];
						dst++;
						width--;
					}
				}
			}
		}
	}
}

/**
 * @brief Blit CL2 sprite, to the back buffer at the given coordianates
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void Cl2Draw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	BYTE *pRLEBytes;
	DWORD *pFrameTable;
	int nDataStart, nDataSize;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	Cl2Blit(
	    &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]],
	    pRLEBytes + nDataStart,
	    nDataSize - nDataStart,
	    nWidth);
}

/**
 * @brief Blit CL2 sprite to the given buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CL2 pixel stream (run-length encoded)
 * @param nDataSize Size of CL2 in bytes
 * @param nWidth Width of sprite
 */
void Cl2Blit(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
#ifdef USE_ASM
	__asm {
		push	ebx
		push	esi
		push	edi
		mov		esi, edx /// UNSAFE: use 'mov esi, pRLEBytes'
		mov		edi, ecx /// UNSAFE: use 'mov edi, pDecodeTo'
		xor		eax, eax
		mov		ebx, nWidth
		mov		ecx, nDataSize
	label1:
		mov		al, [esi]
		inc		esi
		dec		ecx
		test	al, al
		jns		label6
		neg		al
		cmp		al, 41h
		jle		label3
		sub		al, 41h
		dec		ecx
		mov		dl, [esi]
		inc		esi
		sub		ebx, eax
	label2:
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label2
		jmp		label5
	label3:
		sub		ecx, eax
		sub		ebx, eax
	label4:
		mov		dl, [esi]
		inc		esi
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label4
	label5:
		test	ebx, ebx
		jnz		label10
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
		jmp		label10
	label6:
		cmp		eax, ebx
		jle		label7
		mov		edx, ebx
		add		edi, ebx
		sub		eax, ebx
		jmp		label8
	label7:
		mov		edx, eax
		add		edi, eax
		xor		eax, eax
	label8:
		sub		ebx, edx
		jnz		label9
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
	label9:
		test	eax, eax
		jnz		label6
	label10:
		test	ecx, ecx
		jnz		label1
		pop		edi
		pop		esi
		pop		ebx
	}
#else
	int w;
	char width;
	BYTE fill;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;

	while (nDataSize) {
		width = *src++;
		nDataSize--;
		if (width < 0) {
			width = -width;
			if (width > 65) {
				width -= 65;
				nDataSize--;
				fill = *src++;
				w -= width;
				while (width) {
					*dst = fill;
					dst++;
					width--;
				}
				if (!w) {
					w = nWidth;
					dst -= BUFFER_WIDTH + w;
				}
				continue;
			} else {
				nDataSize -= width;
				w -= width;
				while (width) {
					*dst = *src;
					src++;
					dst++;
					width--;
				}
				if (!w) {
					w = nWidth;
					dst -= BUFFER_WIDTH + w;
				}
				continue;
			}
		}
		while (width) {
			if (width > w) {
				dst += w;
				width -= w;
				w = 0;
			} else {
				dst += width;
				w -= width;
				width = 0;
			}
			if (!w) {
				w = nWidth;
				dst -= BUFFER_WIDTH + w;
			}
		}
	}
#endif
}

/**
 * @brief Blit a solid colder shape one pixel larger then the given sprite shape, to the back buffer at the given coordianates
 * @param col Color index from current palette
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void Cl2DrawOutline(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize;
	BYTE *pRLEBytes;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	Cl2BlitOutline(
	    &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]],
	    pRLEBytes + nDataStart,
	    nDataSize - nDataStart,
	    nWidth,
	    col);
}

/**
 * @brief Blit a solid colder shape one pixel larger then the given sprite shape, to the given buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CL2 pixel stream (run-length encoded)
 * @param nDataSize Size of CL2 in bytes
 * @param nWidth Width of sprite
 * @param col Color index from current palette
 */
void Cl2BlitOutline(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, char col)
{
#ifdef USE_ASM
	__asm {
		push	ebx
		push	esi
		push	edi
		mov		esi, edx /// UNSAFE: use 'mov esi, pRLEBytes'
		mov		edi, ecx /// UNSAFE: use 'mov edi, pDecodeTo'
		xor		eax, eax
		mov		ebx, nWidth
		xor		edx, edx
		mov		ecx, nDataSize
		mov		dl, col
	label1:
		mov		al, [esi]
		inc		esi
		dec		ecx
		test	al, al
		jns		label7
		neg		al
		cmp		al, 41h
		jle		label3
		sub		al, 41h
		dec		ecx
		mov		dh, [esi]
		inc		esi
		test	dh, dh
		jz		label7
		mov		[edi-1], dl
		sub		ebx, eax
		mov		[edi+eax], dl
	label2:
		mov		[edi-BUFFER_WIDTH], dl
		mov		[edi+BUFFER_WIDTH], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label2
		jmp		label6
	label3:
		sub		ecx, eax
		sub		ebx, eax
	label4:
		mov		dh, [esi]
		inc		esi
		test	dh, dh
		jz		label5
		mov		[edi-1], dl
		mov		[edi+1], dl
		mov		[edi-BUFFER_WIDTH], dl
		mov		[edi+BUFFER_WIDTH], dl
	label5:
		dec		eax
		lea		edi, [edi+1]
		jnz		label4
	label6:
		test	ebx, ebx
		jnz		label11
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
		jmp		label11
	label7:
		cmp		eax, ebx
		jle		label8
		mov		edx, ebx
		add		edi, ebx
		sub		eax, ebx
		jmp		label9
	label8:
		mov		edx, eax
		add		edi, eax
		xor		eax, eax
	label9:
		sub		ebx, edx
		jnz		label10
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
	label10:
		test	eax, eax
		jnz		label7
		mov		dl, col
	label11:
		test	ecx, ecx
		jnz		label1
		pop		edi
		pop		esi
		pop		ebx
	}
#else
	int w;
	char width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;

	while (nDataSize) {
		width = *src++;
		nDataSize--;
		if (width < 0) {
			width = -width;
			if (width > 65) {
				width -= 65;
				nDataSize--;
				if (*src++) {
					w -= width;
					dst[-1] = col;
					dst[width] = col;
					while (width) {
						dst[-BUFFER_WIDTH] = col;
						dst[BUFFER_WIDTH] = col;
						dst++;
						width--;
					}
					if (!w) {
						w = nWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				}
			} else {
				nDataSize -= width;
				w -= width;
				while (width) {
					if (*src++) {
						dst[-1] = col;
						dst[1] = col;
						dst[-BUFFER_WIDTH] = col;
						dst[BUFFER_WIDTH] = col;
					}
					dst++;
					width--;
				}
				if (!w) {
					w = nWidth;
					dst -= BUFFER_WIDTH + w;
				}
				continue;
			}
		}
		while (width) {
			if (width > w) {
				dst += w;
				width -= w;
				w = 0;
			} else {
				dst += width;
				w -= width;
				width = 0;
			}
			if (!w) {
				w = nWidth;
				dst -= BUFFER_WIDTH + w;
			}
		}
	}
#endif
}

/**
 * @brief Blit CL2 sprite, and apply a given lighting, to the back buffer at the given coordianates
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 * @param light Light shade to use
 */
void Cl2DrawLightTbl(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light)
{
	int nDataStart, nDataSize, idx, nSize;
	BYTE *pRLEBytes, *pDecodeTo;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	nSize = nDataSize - nDataStart;
	pRLEBytes += nDataStart;
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	idx = light4flag ? 1024 : 4096;
	if (light == 2)
		idx += 256; // gray colors
	if (light >= 4)
		idx += (light - 1) << 8;

	Cl2BlitLight(
	    pDecodeTo,
	    pRLEBytes,
	    nSize,
	    nWidth,
	    &pLightTbl[idx]);
}

/**
 * @brief Blit CL2 sprite, and apply lighting, to the given buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CL2 pixel stream (run-length encoded)
 * @param nDataSize Size of CL2 in bytes
 * @param nWidth Width of sprite
 * @param pTable Light color table
 */
void Cl2BlitLight(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, BYTE *pTable)
{
#ifdef USE_ASM
	__asm {
		push	ebx
		push	esi
		push	edi
		mov		esi, edx /// UNSAFE: use 'mov esi, pRLEBytes'
		mov		edi, ecx /// UNSAFE: use 'mov edi, pDecodeTo'
		mov		ebx, nWidth
		mov		ecx, nDataSize
		mov		edx, pTable
		push	ebp
		mov		sgnWidth, ebx
		mov		ebp, edx
		xor		eax, eax
		xor		edx, edx
	label1:
		mov		al, [esi]
		inc		esi
		dec		ecx
		test	al, al
		jns		label6
		neg		al
		cmp		al, 41h
		jle		label3
		sub		al, 41h
		dec		ecx
		sub		ebx, eax
		mov		dl, [esi]
		inc		esi
		mov		dl, [ebp+edx]
	label2:
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label2
		jmp		label5
	label3:
		sub		ecx, eax
		sub		ebx, eax
	label4:
		mov		dl, [esi]
		inc		esi
		mov		dl, [ebp+edx]
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label4
	label5:
		test	ebx, ebx
		jnz		label10
		mov		ebx, sgnWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
		jmp		label10
	label6:
		cmp		eax, ebx
		jle		label7
		mov		edx, ebx
		add		edi, ebx
		sub		eax, ebx
		jmp		label8
	label7:
		mov		edx, eax
		add		edi, eax
		xor		eax, eax
	label8:
		sub		ebx, edx
		jnz		label9
		mov		ebx, sgnWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
	label9:
		test	eax, eax
		jnz		label6
	label10:
		test	ecx, ecx
		jnz		label1
		pop		ebp
		pop		edi
		pop		esi
		pop		ebx
	}
#else
	int w;
	char width;
	BYTE fill;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;
	sgnWidth = nWidth;

	while (nDataSize) {
		width = *src++;
		nDataSize--;
		if (width < 0) {
			width = -width;
			if (width > 65) {
				width -= 65;
				nDataSize--;
				fill = pTable[*src++];
				w -= width;
				while (width) {
					*dst = fill;
					dst++;
					width--;
				}
				if (!w) {
					w = sgnWidth;
					dst -= BUFFER_WIDTH + w;
				}
				continue;
			} else {
				nDataSize -= width;
				w -= width;
				while (width) {
					*dst = pTable[*src];
					src++;
					dst++;
					width--;
				}
				if (!w) {
					w = sgnWidth;
					dst -= BUFFER_WIDTH + w;
				}
				continue;
			}
		}
		while (width) {
			if (width > w) {
				dst += w;
				width -= w;
				w = 0;
			} else {
				dst += width;
				w -= width;
				width = 0;
			}
			if (!w) {
				w = sgnWidth;
				dst -= BUFFER_WIDTH + w;
			}
		}
	}
#endif
}

/**
 * @brief Blit CL2 sprite, and apply lighting, to the back buffer at the given coordinates
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void Cl2DrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nSize;
	BYTE *pRLEBytes, *pDecodeTo;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	nSize = nDataSize - nDataStart;
	pRLEBytes += nDataStart;
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	if (light_table_index)
		Cl2BlitLight(pDecodeTo, pRLEBytes, nSize, nWidth, &pLightTbl[light_table_index * 256]);
	else
		Cl2Blit(pDecodeTo, pRLEBytes, nSize, nWidth);
}

/**
 * @brief Same as Cl2Draw but checks for drawing outside the buffer
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void Cl2DrawSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	BYTE *pRLEBytes;
	DWORD *pFrameTable;
	int nDataStart, nDataSize;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	Cl2BlitSafe(
	    &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]],
	    pRLEBytes + nDataStart,
	    nDataSize - nDataStart,
	    nWidth);
}

/**
 * @brief Same as Cl2Blit but checks for drawing outside the buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CL2 pixel stream (run-length encoded)
 * @param nDataSize Size of CL2 in bytes
 * @param nWidth Width of sprite
 */
void Cl2BlitSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth)
{
#ifdef USE_ASM
	__asm {
		push	ebx
		push	esi
		push	edi
		mov		esi, edx /// UNSAFE: use 'mov esi, pRLEBytes'
		mov		edi, ecx /// UNSAFE: use 'mov edi, pDecodeTo'
		xor		eax, eax
		mov		ebx, nWidth
		mov		ecx, nDataSize
	label1:
		mov		al, [esi]
		inc		esi
		dec		ecx
		test	al, al
		jns		label7
		neg		al
		cmp		al, 41h
		jle		label3
		sub		al, 41h
		dec		ecx
		mov		dl, [esi]
		inc		esi
		cmp		edi, gpBufEnd
		jge		label7
		sub		ebx, eax
	label2:
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label2
		jmp		label6
	label3:
		sub		ecx, eax
		cmp		edi, gpBufEnd
		jl		label4
		add		esi, eax
		jmp		label7
	label4:
		sub		ebx, eax
	label5:
		mov		dl, [esi]
		inc		esi
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label5
	label6:
		test	ebx, ebx
		jnz		label11
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
		jmp		label11
	label7:
		cmp		eax, ebx
		jle		label8
		mov		edx, ebx
		add		edi, ebx
		sub		eax, ebx
		jmp		label9
	label8:
		mov		edx, eax
		add		edi, eax
		xor		eax, eax
	label9:
		sub		ebx, edx
		jnz		label10
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
	label10:
		test	eax, eax
		jnz		label7
	label11:
		test	ecx, ecx
		jnz		label1
		pop		edi
		pop		esi
		pop		ebx
	}
#else
	int w;
	char width;
	BYTE fill;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;

	while (nDataSize) {
		width = *src++;
		nDataSize--;
		if (width < 0) {
			width = -width;
			if (width > 65) {
				width -= 65;
				nDataSize--;
				fill = *src++;
				if (dst < gpBufEnd) {
					w -= width;
					while (width) {
						*dst = fill;
						dst++;
						width--;
					}
					if (!w) {
						w = nWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				}
			} else {
				nDataSize -= width;
				if (dst < gpBufEnd) {
					w -= width;
					while (width) {
						*dst = *src;
						src++;
						dst++;
						width--;
					}
					if (!w) {
						w = nWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				} else {
					src += width;
				}
			}
		}
		while (width) {
			if (width > w) {
				dst += w;
				width -= w;
				w = 0;
			} else {
				dst += width;
				w -= width;
				width = 0;
			}
			if (!w) {
				w = nWidth;
				dst -= BUFFER_WIDTH + w;
			}
		}
	}
#endif
}

/**
 * @brief Same as Cl2DrawOutline but checks for drawing outside the buffer
 * @param col Color index from current palette
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void Cl2DrawOutlineSafe(char col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize;
	BYTE *pRLEBytes;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	gpBufEnd -= BUFFER_WIDTH;
	Cl2BlitOutlineSafe(
	    &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]],
	    pRLEBytes + nDataStart,
	    nDataSize - nDataStart,
	    nWidth,
	    col);
	gpBufEnd += BUFFER_WIDTH;
}

/**
 * @brief Same as Cl2BlitOutline but checks for drawing outside the buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CL2 pixel stream (run-length encoded)
 * @param nDataSize Size of CL2 in bytes
 * @param nWidth Width of sprite
 * @param col Color index from current palette
 */
void Cl2BlitOutlineSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, char col)
{
#ifdef USE_ASM
	__asm {
		push	ebx
		push	esi
		push	edi
		mov		esi, edx /// UNSAFE: use 'mov esi, pRLEBytes'
		mov		edi, ecx /// UNSAFE: use 'mov edi, pDecodeTo'
		xor		eax, eax
		mov		ebx, nWidth
		xor		edx, edx
		mov		ecx, nDataSize
		mov		dl, col
	label1:
		mov		al, [esi]
		inc		esi
		dec		ecx
		test	al, al
		jns		label9
		neg		al
		cmp		al, 41h
		jle		label3
		sub		al, 41h
		dec		ecx
		mov		dh, [esi]
		inc		esi
		test	dh, dh
		jz		label9
		cmp		edi, gpBufEnd
		jge		label9
		mov		[edi-1], dl
		sub		ebx, eax
		mov		[edi+eax], dl
	label2:
		mov		[edi-BUFFER_WIDTH], dl
		mov		[edi+BUFFER_WIDTH], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label2
		jmp		label7
	label3:
		sub		ecx, eax
		cmp		edi, gpBufEnd
		jl		label4
		add		esi, eax
		jmp		label9
	label4:
		sub		ebx, eax
	label5:
		mov		dh, [esi]
		inc		esi
		test	dh, dh
		jz		label6
		mov		[edi-1], dl
		mov		[edi+1], dl
		mov		[edi-BUFFER_WIDTH], dl
		mov		[edi+BUFFER_WIDTH], dl
	label6:
		dec		eax
		lea		edi, [edi+1]
		jnz		label5
	label7:
		test	ebx, ebx
		jnz		label13
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
		jmp		label13
	label9:
		cmp		eax, ebx
		jle		label10
		mov		edx, ebx
		add		edi, ebx
		sub		eax, ebx
		jmp		label11
	label10:
		mov		edx, eax
		add		edi, eax
		xor		eax, eax
	label11:
		sub		ebx, edx
		jnz		label12
		mov		ebx, nWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
	label12:
		test	eax, eax
		jnz		label9
		mov		dl, col
	label13:
		test	ecx, ecx
		jnz		label1
		pop		edi
		pop		esi
		pop		ebx
	}
#else
	int w;
	char width;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;

	while (nDataSize) {
		width = *src++;
		nDataSize--;
		if (width < 0) {
			width = -width;
			if (width > 65) {
				width -= 65;
				nDataSize--;
				if (*src++ && dst < gpBufEnd) {
					w -= width;
					dst[-1] = col;
					dst[width] = col;
					while (width) {
						dst[-BUFFER_WIDTH] = col;
						dst[BUFFER_WIDTH] = col;
						dst++;
						width--;
					}
					if (!w) {
						w = nWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				}
			} else {
				nDataSize -= width;
				if (dst < gpBufEnd) {
					w -= width;
					while (width) {
						if (*src++) {
							dst[-1] = col;
							dst[1] = col;
							dst[-BUFFER_WIDTH] = col;
							dst[BUFFER_WIDTH] = col;
						}
						dst++;
						width--;
					}
					if (!w) {
						w = nWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				} else {
					src += width;
				}
			}
		}
		while (width) {
			if (width > w) {
				dst += w;
				width -= w;
				w = 0;
			} else {
				dst += width;
				w -= width;
				width = 0;
			}
			if (!w) {
				w = nWidth;
				dst -= BUFFER_WIDTH + w;
			}
		}
	}
#endif
}

/**
 * @brief Same as Cl2DrawLightTbl but checks for drawing outside the buffer
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 * @param light light shade to use
 */
void Cl2DrawLightTblSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap, char light)
{
	int nDataStart, nDataSize, idx, nSize;
	BYTE *pRLEBytes, *pDecodeTo;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	nSize = nDataSize - nDataStart;
	pRLEBytes += nDataStart;
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	idx = light4flag ? 1024 : 4096;
	if (light == 2)
		idx += 256; // gray colors
	if (light >= 4)
		idx += (light - 1) << 8;

	Cl2BlitLightSafe(
	    pDecodeTo,
	    pRLEBytes,
	    nSize,
	    nWidth,
	    &pLightTbl[idx]);
}

/**
 * @brief Same as Cl2BlitLight but checks for drawing outside the buffer
 * @param pDecodeTo The output buffer
 * @param pRLEBytes CL2 pixel stream (run-length encoded)
 * @param nDataSize Size of CL2 in bytes
 * @param nWidth With of CL2 sprite
 * @param pTable Light color table
 */
void Cl2BlitLightSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, BYTE *pTable)
{
#ifdef USE_ASM
	__asm {
		push	ebx
		push	esi
		push	edi
		mov		esi, edx /// UNSAFE: use 'mov esi, pRLEBytes'
		mov		edi, ecx /// UNSAFE: use 'mov edi, pDecodeTo'
		mov		ebx, nWidth
		mov		ecx, nDataSize
		mov		edx, pTable
		push	ebp
		mov		sgnWidth, ebx
		mov		ebp, edx
		xor		eax, eax
		xor		edx, edx
	label1:
		mov		al, [esi]
		inc		esi
		dec		ecx
		test	al, al
		jns		label7
		neg		al
		cmp		al, 41h
		jle		label3
		sub		al, 41h
		dec		ecx
		mov		dl, [esi]
		inc		esi
		mov		dl, [ebp+edx]
		cmp		edi, gpBufEnd
		jge		label7
		sub		ebx, eax
	label2:
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label2
		jmp		label6
	label3:
		sub		ecx, eax
		cmp		edi, gpBufEnd
		jl		label4
		add		esi, eax
		jmp		label7
	label4:
		sub		ebx, eax
	label5:
		mov		dl, [esi]
		inc		esi
		mov		dl, [ebp+edx]
		mov		[edi], dl
		dec		eax
		lea		edi, [edi+1]
		jnz		label5
	label6:
		test	ebx, ebx
		jnz		label11
		mov		ebx, sgnWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
		jmp		label11
	label7:
		cmp		eax, ebx
		jle		label8
		mov		edx, ebx
		add		edi, ebx
		sub		eax, ebx
		jmp		label9
	label8:
		mov		edx, eax
		add		edi, eax
		xor		eax, eax
	label9:
		sub		ebx, edx
		jnz		label10
		mov		ebx, sgnWidth
		sub		edi, BUFFER_WIDTH
		sub		edi, ebx
	label10:
		test	eax, eax
		jnz		label7
	label11:
		test	ecx, ecx
		jnz		label1
		pop		ebp
		pop		edi
		pop		esi
		pop		ebx
	}
#else
	int w;
	char width;
	BYTE fill;
	BYTE *src, *dst;

	src = pRLEBytes;
	dst = pDecodeTo;
	w = nWidth;
	sgnWidth = nWidth;

	while (nDataSize) {
		width = *src++;
		nDataSize--;
		if (width < 0) {
			width = -width;
			if (width > 65) {
				width -= 65;
				nDataSize--;
				fill = pTable[*src++];
				if (dst < gpBufEnd) {
					w -= width;
					while (width) {
						*dst = fill;
						dst++;
						width--;
					}
					if (!w) {
						w = sgnWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				}
			} else {
				nDataSize -= width;
				if (dst < gpBufEnd) {
					w -= width;
					while (width) {
						*dst = pTable[*src];
						src++;
						dst++;
						width--;
					}
					if (!w) {
						w = sgnWidth;
						dst -= BUFFER_WIDTH + w;
					}
					continue;
				} else {
					src += width;
				}
			}
		}
		while (width) {
			if (width > w) {
				dst += w;
				width -= w;
				w = 0;
			} else {
				dst += width;
				w -= width;
				width = 0;
			}
			if (!w) {
				w = sgnWidth;
				dst -= BUFFER_WIDTH + w;
			}
		}
	}
#endif
}

/**
 * @brief Same as Cl2DrawLight but checks for drawing outside the buffer
 * @param sx Back buffer coordinate
 * @param sy Back buffer coordinate
 * @param pCelBuff CL2 buffer
 * @param nCel CL2 frame number
 * @param nWidth Width of sprite
 * @param CelSkip Skip lower parts of sprite, must be multiple of 2, max 8
 * @param CelCap Amount of sprite to render from lower to upper, must be multiple of 2, max 8
 */
void Cl2DrawLightSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, int CelSkip, int CelCap)
{
	int nDataStart, nDataSize, nSize;
	BYTE *pRLEBytes, *pDecodeTo;
	DWORD *pFrameTable;

	/// ASSERT: assert(gpBuffer != NULL);
	if (gpBuffer == NULL)
		return;
	/// ASSERT: assert(pCelBuff != NULL);
	if (pCelBuff == NULL)
		return;
	assert(nCel > 0);
	if (nCel <= 0)
		return;

	pFrameTable = (DWORD *)pCelBuff;
	assert(nCel <= (int)pFrameTable[0]);
	pRLEBytes = &pCelBuff[pFrameTable[nCel]];
	nDataStart = *(WORD *)&pRLEBytes[CelSkip];
	if (!nDataStart)
		return;

	if (CelCap == 8)
		nDataSize = 0;
	else
		nDataSize = *(WORD *)&pRLEBytes[CelCap];
	if (!nDataSize)
		nDataSize = pFrameTable[nCel + 1] - pFrameTable[nCel];

	nSize = nDataSize - nDataStart;
	pRLEBytes += nDataStart;
	pDecodeTo = &gpBuffer[sx + PitchTbl[sy - 16 * CelSkip]];

	if (light_table_index)
		Cl2BlitLightSafe(pDecodeTo, pRLEBytes, nSize, nWidth, &pLightTbl[light_table_index * 256]);
	else
		Cl2BlitSafe(pDecodeTo, pRLEBytes, nSize, nWidth);
}

/**
 * @brief Fade to black and play a video
 * @param pszMovie file path of movie
 */
void PlayInGameMovie(char *pszMovie)
{
	PaletteFadeOut(8);
	play_movie(pszMovie, FALSE);
	ClearScreenBuffer();
	force_redraw = 255;
	scrollrt_draw_game_screen(TRUE);
	PaletteFadeIn(8);
	force_redraw = 255;
}
