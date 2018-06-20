//HEADER_GOES_HERE

#include "../types.h"

int encrypt_table[1280];

void __fastcall encrypt_decrypt_block(void *block, int size, int key) // DecryptMPQBlock
{
	unsigned int v3; // edx
	int v4; // eax
	unsigned int v5; // edi
	unsigned int v6; // edx
	int v7; // eax
	int v8; // esi

	v3 = (unsigned int)size >> 2;
	v4 = 0xEEEEEEEE;
	if ( v3 )
	{
		v5 = v3;
		v6 = key;
		do
		{
			v7 = encrypt_table[(unsigned char)v6 + 1024] + v4;
			*(_DWORD *)block ^= v7 + v6;
			v8 = *(_DWORD *)block;
			block = (char *)block + 4;
			v4 = 33 * v7 + v8 + 3;
			v6 = ((~v6 << 21) + 0x11111111) | (v6 >> 11);
			--v5;
		}
		while ( v5 );
	}
}

void __fastcall encrypt_encrypt_block(void *block, int size, int key) // EncryptMPQBlock
{
	unsigned int v3; // edx
	int v4; // eax
	unsigned int v5; // edi
	unsigned int v6; // edx
	int v7; // eax
	int v8; // ebx

	v3 = (unsigned int)size >> 2;
	v4 = 0xEEEEEEEE;
	if ( v3 )
	{
		v5 = v3;
		v6 = key;
		do
		{
			v7 = encrypt_table[(unsigned char)v6 + 1024] + v4;
			v8 = *(_DWORD *)block ^ (v7 + v6);
			v4 = 33 * v7 + *(_DWORD *)block + 3;
			*(_DWORD *)block = v8;
			block = (char *)block + 4;
			v6 = ((~v6 << 21) + 0x11111111) | (v6 >> 11);
			--v5;
		}
		while ( v5 );
	}
}

int __fastcall encrypt_hash(char *s, int type) // HashStringSlash
{
	int v2; // ebp
	char *v3; // ebx
	signed int v4; // esi
	int v5; // edi
	int v6; // ST00_4
	char v7; // al

	v2 = type;
	v3 = s;
	v4 = 0x7FED7FED;
	v5 = 0xEEEEEEEE;
	while ( v3 && *v3 )
	{
		v6 = *v3++;
		v7 = toupper(v6);
		v4 = (v5 + v4) ^ encrypt_table[v7 + (v2 << 8)];
		v5 = v7 + 33 * v5 + v4 + 3;
	}
	return v4;
}

void __cdecl encrypt_init_lookup_table() // InitScratchSpace
{
	unsigned int v0; // eax
	int *v1; // edi
	unsigned int v2; // eax
	int v3; // ecx
	signed int v4; // [esp+Ch] [ebp-8h]
	int *v5; // [esp+10h] [ebp-4h]

	v0 = 0x100001;
	v5 = encrypt_table;
	do
	{
		v1 = v5;
		v4 = 5;
		do
		{
			v2 = (125 * v0 + 3) % 0x2AAAAB;
			v3 = (unsigned short)v2 << 16;
			v0 = (125 * v2 + 3) % 0x2AAAAB;
			*v1 = (unsigned short)v0 | v3;
			v1 += 256;
			--v4;
		}
		while ( v4 );
		++v5;
	}
	while ( (signed int)v5 < (signed int)&encrypt_table[256] );
}

int __fastcall encrypt_compress(void *buf, int size) // MPQCompress_PKWare
{
	unsigned char *v2; // ebx
	unsigned char *v3; // esi
	int v4; // ecx
	unsigned char *v5; // edi
	TDataInfo param; // [esp+Ch] [ebp-20h]
	unsigned int type; // [esp+20h] [ebp-Ch]
	unsigned int dsize; // [esp+24h] [ebp-8h]
	char *ptr; // [esp+28h] [ebp-4h]

	v2 = (unsigned char *)buf;
	v3 = (unsigned char *)size;
	ptr = (char *)DiabloAllocPtr(CMP_BUFFER_SIZE); // 36312
	v4 = 2 * (_DWORD)v3;
	if ( (unsigned int)(2 * (_DWORD)v3) < 0x2000 )
		v4 = 0x2000;
	v5 = (unsigned char *)DiabloAllocPtr(v4);
	param.pbInBuffEnd = 0;
	param.pbOutBuffEnd = 0;
	type = 0;
	param.pbInBuff = v2;
	param.pbOutBuff = v5;
	param.pbSize = v3;
	dsize = 4096;
	implode(
		encrypt_pkware_read,
		encrypt_pkware_write,
		ptr,
		&param,
		&type,
		&dsize);
	if ( param.pbOutBuffEnd < v3 )
	{
		memcpy(v2, v5, (size_t)param.pbOutBuffEnd);
		v3 = param.pbOutBuffEnd;
	}
	mem_free_dbg(ptr);
	mem_free_dbg(v5);
	return (int)v3;
}

unsigned int __cdecl encrypt_pkware_read(char *buf, unsigned int *size, void *param) // ReadPKWare
{
	TDataInfo * pInfo = (TDataInfo *)param;
	int v3; // edi
	unsigned char *v4; // ecx

	v3 = *size;
	v4 = pInfo->pbInBuffEnd;
	if ( *size >= (unsigned int)(pInfo->pbSize - v4) )
		v3 = pInfo->pbSize - v4;
	memcpy(buf, &v4[(unsigned int)pInfo->pbInBuff], v3);
	pInfo->pbInBuffEnd += v3;
	return v3;
}

void __cdecl encrypt_pkware_write(char *buf, unsigned int *size, void *param) // WritePKWare
{
	TDataInfo * pInfo = (TDataInfo *)param;

	memcpy(&pInfo->pbOutBuffEnd[(unsigned int)pInfo->pbOutBuff], buf, *size);
	pInfo->pbOutBuffEnd += *size;
}

void __fastcall encrypt_decompress(void *param, int recv_size, int dwMaxBytes) // MPQDecompress_PKWare
{
	unsigned char *v3; // edi
	unsigned char *v4; // ebx
	unsigned char *v5; // esi
	TDataInfo info; // [esp+Ch] [ebp-18h]
	char *ptr; // [esp+20h] [ebp-4h]

	v3 = (unsigned char *)param;
	v4 = (unsigned char *)recv_size;
	ptr = (char *)DiabloAllocPtr(CMP_BUFFER_SIZE); // 36312
	v5 = (unsigned char *)DiabloAllocPtr(dwMaxBytes);
	info.pbInBuffEnd = 0;
	info.pbOutBuffEnd = 0;
	info.pbInBuff = v3;
	info.pbOutBuff = v5;
	info.pbSize = v4;
	explode(
		encrypt_pkware_read,
		encrypt_pkware_write,
		ptr,
		&info);
	memcpy(v3, v5, (size_t)info.pbOutBuffEnd);
	mem_free_dbg(ptr);
	mem_free_dbg(v5);
}
