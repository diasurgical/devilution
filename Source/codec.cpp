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

DWORD codec_get_encoded_len(DWORD dwSrcBytes)
{
	if (dwSrcBytes % 64 != 0)
		dwSrcBytes += 64 - (dwSrcBytes % 64);
	return dwSrcBytes + 8;
}

void codec_encode(BYTE* pbSrcDst, DWORD size, int size_64, char *pszPassword)
{
	char buf[128];
	char tmp[20];
	char dst[20];
	DWORD chunk;
	WORD last_chunk;

	if (size_64 != codec_get_encoded_len(size))
		app_fatal("Invalid encode parameters");
	codec_init_key(1, pszPassword);

	last_chunk = 0;
	while (size != 0) {
		chunk = size < 64 ? size : 64;
		memcpy(buf, pbSrcDst, chunk);
		if (chunk < 64)
			memset(buf + chunk, 0, 64 - chunk);
		SHA1Result(0, dst);
		SHA1Calculate(0, buf, NULL);
		for (int j = 0; j < 64; j++) {
			buf[j] ^= dst[j % 20];
		}
		memset(dst, 0, sizeof(dst));
		memcpy(pbSrcDst, buf, 64);
		last_chunk = chunk;
		pbSrcDst += 64;
		size -= chunk;
	}
	memset(buf, 0, sizeof(buf));
	SHA1Result(0, tmp);
	pbSrcDst[4] = 0;
	((WORD *)pbSrcDst)[3] = 0;
	((DWORD *)pbSrcDst)[0] = ((DWORD *)tmp)[0];
	pbSrcDst[5] = last_chunk;
	SHA1Clear();
}
