/**
 * @file codec.cpp
 *
 * Implementation of save game encryption algorithm.
 */
#include "all.h"

typedef struct CodecSignature {
	DWORD checksum;
	BYTE error;
	BYTE last_chunk_size;
	WORD unused;
} CodecSignature;

#define BLOCKSIZE 64

static void codec_init_key(int unused, char *pszPassword)
{
	int i, ch, n;
	char key[136]; // last 64 bytes are the SHA1
	char pw[64];
	char digest[SHA1HashSize];
	char *keyInit;

	srand(0x7058);

	keyInit = key;
	for (i = 0; i < sizeof(key); i++) {
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
	for (i = 0; i < sizeof(key); i++)
		key[i] ^= digest[i % SHA1HashSize];
	memset(pw, 0, sizeof(pw));
	memset(digest, 0, sizeof(digest));
	for (n = 0; n < 3; n++) {
		SHA1Reset(n);
		SHA1Calculate(n, &key[72], NULL);
	}
	memset(key, 0, sizeof(key));
}

int codec_decode(BYTE *pbSrcDst, DWORD size, char *pszPassword)
{
	char buf[128];
	char dst[SHA1HashSize];
	int i;
	CodecSignature *sig;

	codec_init_key(0, pszPassword);
	if (size <= sizeof(CodecSignature))
		return 0;
	size -= sizeof(CodecSignature);
	if (size % BLOCKSIZE != 0)
		return 0;
	for (i = size; i != 0; pbSrcDst += BLOCKSIZE, i -= BLOCKSIZE) {
		memcpy(buf, pbSrcDst, BLOCKSIZE);
		SHA1Result(0, dst);
		for (int j = 0; j < BLOCKSIZE; j++) {
			buf[j] ^= dst[j % SHA1HashSize];
		}
		SHA1Calculate(0, buf, NULL);
		memset(dst, 0, sizeof(dst));
		memcpy(pbSrcDst, buf, BLOCKSIZE);
	}

	memset(buf, 0, sizeof(buf));
	sig = (CodecSignature *)pbSrcDst;
	if (sig->error > 0) {
		goto error;
	}

	SHA1Result(0, dst);
	if (sig->checksum != *(DWORD *)dst) {
		memset(dst, 0, sizeof(dst));
		goto error;
	}

	size += sig->last_chunk_size - BLOCKSIZE;
	SHA1Clear();
	return size;
error:
	SHA1Clear();
	return 0;
}

DWORD codec_get_encoded_len(DWORD dwSrcBytes)
{
	if (dwSrcBytes % BLOCKSIZE != 0)
		dwSrcBytes += BLOCKSIZE - (dwSrcBytes % BLOCKSIZE);
	return dwSrcBytes + sizeof(CodecSignature);
}

void codec_encode(BYTE *pbSrcDst, DWORD size, int size_64, char *pszPassword)
{
	char buf[128];
	char tmp[SHA1HashSize];
	char dst[SHA1HashSize];
	DWORD chunk;
	WORD last_chunk;
	CodecSignature *sig;

	if (size_64 != codec_get_encoded_len(size))
		app_fatal("Invalid encode parameters");
	codec_init_key(1, pszPassword);

	last_chunk = 0;
	while (size != 0) {
		chunk = size < BLOCKSIZE ? size : BLOCKSIZE;
		memcpy(buf, pbSrcDst, chunk);
		if (chunk < BLOCKSIZE)
			memset(buf + chunk, 0, BLOCKSIZE - chunk);
		SHA1Result(0, dst);
		SHA1Calculate(0, buf, NULL);
		for (int j = 0; j < BLOCKSIZE; j++) {
			buf[j] ^= dst[j % SHA1HashSize];
		}
		memset(dst, 0, sizeof(dst));
		memcpy(pbSrcDst, buf, BLOCKSIZE);
		last_chunk = chunk;
		pbSrcDst += BLOCKSIZE;
		size -= chunk;
	}
	memset(buf, 0, sizeof(buf));
	SHA1Result(0, tmp);
	sig = (CodecSignature *)pbSrcDst;
	sig->error = 0;
	sig->unused = 0;
	sig->checksum = *(DWORD *)&tmp[0];
	sig->last_chunk_size = last_chunk;
	SHA1Clear();
}
