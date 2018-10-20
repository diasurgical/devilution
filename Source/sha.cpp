//HEADER_GOES_HERE

#include "../types.h"

SHA1Context sgSHA1[3];

void __cdecl SHA1Clear()
{
    memset(sgSHA1, 0, sizeof(sgSHA1));
}

void __fastcall SHA1Result(int n, char Message_Digest[SHA1HashSize])
{
    DWORD *Message_Digest_Block = (DWORD *)Message_Digest;
    if (Message_Digest) {
        for (int i = 0; i < 5; i++) {
            *Message_Digest_Block = sgSHA1[n].state[i];
            Message_Digest_Block++;
        }
    }
}

void __fastcall SHA1Calculate(int n, const char *data, char Message_Digest[SHA1HashSize])
{
    SHA1Input(&sgSHA1[n], data, 64);
    if (Message_Digest)
        SHA1Result(n, Message_Digest);
}

void __fastcall SHA1Input(SHA1Context *context, const char *message_array, int len)
{
	SHA1Context *v3; // esi
	const char *v4; // ebx
	int v5; // ecx
	int v6; // edx
	unsigned int v7; // ebp

	v3 = context;
	v4 = message_array;
	v5 = context->count[0];
	v6 = v5 + 8 * len;
	if ( v6 < v5 )
		++v3->count[1];
	v3->count[0] = v6;
	v3->count[1] += len >> 29;
	if ( len >= 64 )
	{
		v7 = (unsigned int)len >> 6;
		do
		{
			memcpy(v3->buffer, v4, 0x40u);
			SHA1ProcessMessageBlock(v3);
			v4 += 64;
			--v7;
		}
		while ( v7 );
	}
}

void __fastcall SHA1ProcessMessageBlock(SHA1Context *context)
{
    int i;
    int temp;
    int W[80];
    int A, B, C, D, E;

    qmemcpy(W, context->buffer, sizeof(context->buffer));

    for (i = 16; i < 80; i++) {
        W[i] = W[i - 16] ^ W[i - 14] ^ W[i - 8] ^ W[i - 3];
    }

    A = context->state[0];
    B = context->state[1];
    C = context->state[2];
    D = context->state[3];
    E = context->state[4];

    for (i = 0; i < 20; i++) {
        temp = SHA1CircularShift(5, A) + ((B & C) | ((~B) & D)) + E + W[i] + 0x5A827999;
        E = D;
        D = C;
        C = SHA1CircularShift(30, B);
        B = A;
        A = temp;
    }

    for (i = 20; i < 40; i++) {
        temp = SHA1CircularShift(5, A) + (B ^ C ^ D) + E + W[i] + 0x6ED9EBA1;
        E = D;
        D = C;
        C = SHA1CircularShift(30, B);
        B = A;
        A = temp;
    }

    for (i = 40; i < 60; i++) {
        temp = SHA1CircularShift(5, A) + ((B & C) | (B & D) | (C & D)) + E + W[i] + 0x8F1BBCDC;
        E = D;
        D = C;
        C = SHA1CircularShift(30, B);
        B = A;
        A = temp;
    }

    for (i = 60; i < 80; i++) {
        temp = SHA1CircularShift(5, A) + (B ^ C ^ D) + E + W[i] + 0xCA62C1D6;
        E = D;
        D = C;
        C = SHA1CircularShift(30, B);
        B = A;
        A = temp;
    }

    context->state[0] += A;
    context->state[1] += B;
    context->state[2] += C;
    context->state[3] += D;
    context->state[4] += E;
}

void __fastcall SHA1Reset(int n)
{
    SHA1Init(&sgSHA1[n]);
}

void __fastcall SHA1Init(SHA1Context *context)
{
    context->count[0] = 0;
    context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
}
