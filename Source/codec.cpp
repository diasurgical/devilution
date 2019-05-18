#include "diablo.h"

int codec_decode(BYTE *pbSrcDst, DWORD size, char *pszPassword)
{
	char buf[128];
	char dst[20];
	int i;

	codec_init_key(0, pszPassword);
	if (size <= 8)
		return 0;
	size = size - 8;
	if (size % 64 != 0)
		return 0;
	for (i = size; i != 0; pbSrcDst += 64, i -= 64) {
		memcpy(buf, pbSrcDst, 64);
		SHA1Result(0, dst);
		for (int j = 0; j < 64; j++) {
			buf[j] ^= dst[j % 20];
		}
		SHA1Calculate(0, buf, NULL);
		memset(dst, 0, sizeof(dst));
		memcpy(pbSrcDst, buf, 64);
	}

	memset(buf, 0, sizeof(buf));
	if (pbSrcDst[4] > 0) {
		size = 0;
		SHA1Clear();
	} else {
		SHA1Result(0, dst);
		if (*(DWORD *)pbSrcDst != *(DWORD *)dst) {
			memset(dst, 0, sizeof(dst));
			size = 0;
			SHA1Clear();
		} else {
			size += pbSrcDst[5] - 64;
			SHA1Clear();
		}
	}
	return size;
}

void codec_init_key(int unused, char *pszPassword)
{
	int i, ch, n;
	char key[136]; // last 64 bytes are the SHA1
	char pw[64];
	char digest[SHA1HashSize];
	char *keyInit;

	srand(0x7058);

	keyInit = key;
	for (i = 0; i < 136; i++) {
		*keyInit = rand();
		keyInit++;
	}
	ch = 0;
	for (i = 0; i < 64; i++) {
		if (!pszPassword[ch])
			ch = 0;
		pw[i] = pszPassword[ch];
		ch++;
	}
	SHA1Reset(0);
	SHA1Calculate(0, pw, digest);
	SHA1Clear();
	for (i = 0; (DWORD)i < 136; i++)
		key[i] ^= digest[i % 20];
	memset(pw, 0, sizeof(pw));
	memset(digest, 0, sizeof(digest));
	for (n = 0; n < 3; n++) {
		SHA1Reset(n);
		SHA1Calculate(n, &key[72], NULL);
	}
	memset(key, 0, sizeof(key));
}
// 4035DB: using guessed type char var_E0[72];
// 4035DB: using guessed type char var_58[64];
// 4035DB: using guessed type char dst[20];

int codec_get_encoded_len(int dwSrcBytes)
{
	if (dwSrcBytes & 0x3F)
		dwSrcBytes += 64 - (dwSrcBytes & 0x3F);
	return dwSrcBytes + 8;
}

void codec_encode(void *pbSrcDst, int size, int size_64, char *pszPassword)
{
	char *v4;      // esi
	char v5;       // bl
	size_t v6;     // edi
	signed int v7; // ecx
	char v9[128];  // [esp+8h] [ebp-ACh]
	char v10[20];  // [esp+88h] [ebp-2Ch]
	char dst[20];  // [esp+9Ch] [ebp-18h]
	size_t v12;    // [esp+B0h] [ebp-4h]

	v4 = (char *)pbSrcDst;
	v12 = size;
	if (size_64 != codec_get_encoded_len(size))
		app_fatal("Invalid encode parameters");
	codec_init_key(1, pszPassword);
	v5 = 0;
	if (v12) {
		do {
			v6 = v12;
			if (v12 >= 0x40)
				v6 = 64;
			memcpy(v9, v4, v6);
			if (v6 < 0x40)
				memset(&v9[v6], 0, 64 - v6);
			SHA1Result(0, dst);
			SHA1Calculate(0, v9, NULL);
			v7 = 0;
			do {
				v9[v7] ^= dst[v7 % 20];
				++v7;
			} while (v7 < 64);
			memset(dst, 0, sizeof(dst));
			memcpy(v4, v9, 0x40u);
			v4 += 64;
			v12 -= v6;
		} while (v12);
		v5 = v6;
	}
	memset(v9, 0, sizeof(v9));
	SHA1Result(0, v10);
	v4[4] = 0;
	*((_WORD *)v4 + 3) = 0;
	*(_DWORD *)v4 = *(_DWORD *)v10;
	v4[5] = v5;
	SHA1Clear();
}
// 4036BE: using guessed type char var_AC[128];
// 4036BE: using guessed type char dst[20];
