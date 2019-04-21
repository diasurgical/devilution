#include "diablo.h"
#include "../3rdParty/Storm/Source/storm.h"

int sgdwMpqOffset; // idb
char mpq_buf[4096];
_HASHENTRY *sgpHashTbl;
BOOL save_archive_modified; // weak
_BLOCKENTRY *sgpBlockTbl;
BOOLEAN save_archive_open; // weak

//note: 32872 = 32768 + 104 (sizeof(_FILEHEADER))

/* data */

HANDLE sghArchive = (HANDLE)0xFFFFFFFF; // idb

BOOL mpqapi_set_hidden(const char *pszArchive, BOOL hidden)
{
	DWORD dwFileAttributes;
	DWORD dwFileAttributesToSet;

	dwFileAttributes = GetFileAttributes(pszArchive);
	if (dwFileAttributes == INVALID_FILE_ATTRIBUTES)
		return GetLastError() == ERROR_FILE_NOT_FOUND;
	dwFileAttributesToSet = hidden ? FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN : 0;
	if (dwFileAttributes == dwFileAttributesToSet)
		return TRUE;
	else
		return SetFileAttributes(pszArchive, dwFileAttributesToSet);
}

void mpqapi_store_creation_time(const char *pszArchive, int dwChar)
{
	int v2;                                // esi
	const char *v3;                        // ebx
	HANDLE v4;                             // eax
	int v5;                                // esi
	struct _WIN32_FIND_DATAA FindFileData; // [esp+8h] [ebp-1E0h]
	char dst[160];                         // [esp+148h] [ebp-A0h]

	v2 = dwChar;
	v3 = pszArchive;
	if (gbMaxPlayers != 1) {
		mpqapi_reg_load_modification_time(dst, 160);
		v4 = FindFirstFile(v3, &FindFileData);
		if (v4 != (HANDLE)-1) {
			FindClose(v4);
			v5 = 16 * v2;
			*(_DWORD *)&dst[v5] = FindFileData.ftCreationTime.dwLowDateTime;
			*(_DWORD *)&dst[v5 + 4] = FindFileData.ftCreationTime.dwHighDateTime;
			mpqapi_reg_store_modification_time(dst, 160);
		}
	}
}
// 679660: using guessed type char gbMaxPlayers;

BOOL mpqapi_reg_load_modification_time(char *dst, int size)
{
	unsigned int iSize;
	char *pszDst;
	char *pbData;
	int nbytes_read;

	iSize = size;
	pszDst = dst;
	memset(dst, 0, size);
	if (!SRegLoadData("Diablo", "Video Player ", 0, (unsigned char *)pszDst, iSize, (LPDWORD)&nbytes_read)) {
		return FALSE;
	}

	if (nbytes_read != size)
		return FALSE;

	for (; iSize >= 8; iSize -= 8) {
		pbData = pszDst;
		pszDst += 8;
		mpqapi_xor_buf(pbData);
	}

	return TRUE;
}

void mpqapi_xor_buf(char *pbData)
{
	signed int v1; // eax
	char *v2;      // esi
	signed int v3; // edi

	v1 = 0xF0761AB;
	v2 = pbData;
	v3 = 8;
	do {
		*v2 ^= v1;
		++v2;
		v1 = _rotl(v1, 1);
		--v3;
	} while (v3);
}

void mpqapi_update_multi_creation_time(DWORD dwChar)
{
}

BOOLEAN mpqapi_reg_store_modification_time(char *pbData, DWORD dwLen)
{
	char *pbCurrentData;
	DWORD i;
	char *pbDataToXor;

	pbCurrentData = pbData;
	if (dwLen >= 8) {
		i = dwLen >> 3;
		do {
			pbDataToXor = pbCurrentData;
			pbCurrentData += 8;
			mpqapi_xor_buf(pbDataToXor);
			--i;
		} while (i);
	}

	return SRegSaveData("Diablo", "Video Player ", 0, (unsigned char *)pbData, dwLen);
}

void mpqapi_remove_hash_entry(const char *pszName)
{
	int v1;          // eax
	_HASHENTRY *v2;  // ecx
	_BLOCKENTRY *v3; // eax
	int v4;          // esi
	int v5;          // edi

	v1 = mpqapi_get_hash_index_of_path(pszName);
	if (v1 != -1) {
		v2 = &sgpHashTbl[v1];
		v3 = &sgpBlockTbl[v2->block];
		v2->block = -2;
		v4 = v3->offset;
		v5 = v3->sizealloc;
		memset(v3, 0, 0x10u);
		mpqapi_free_block(v4, v5);
		save_archive_modified = 1;
	}
}
// 65AB0C: using guessed type int save_archive_modified;

void mpqapi_free_block(int block_offset, int block_size)
{
	int v2;          // esi
	int v3;          // edi
	_BLOCKENTRY *v4; // eax
	signed int v5;   // edx
	signed int v6;   // ecx
	int v7;          // ecx
	BOOLEAN v8;      // zf
	_BLOCKENTRY *v9; // eax

	v2 = block_size;
	v3 = block_offset;
LABEL_2:
	v4 = sgpBlockTbl;
	v5 = 2048;
	while (1) {
		v6 = v5--;
		if (!v6)
			break;
		v7 = v4->offset;
		if (v4->offset && !v4->flags && !v4->sizefile) {
			if (v7 + v4->sizealloc == v3) {
				v3 = v4->offset;
			LABEL_11:
				v2 += v4->sizealloc;
				memset(v4, 0, 0x10u);
				goto LABEL_2;
			}
			if (v3 + v2 == v7)
				goto LABEL_11;
		}
		++v4;
	}
	v8 = v3 + v2 == sgdwMpqOffset;
	if (v3 + v2 > sgdwMpqOffset) {
		app_fatal("MPQ free list error");
		v8 = v3 + v2 == sgdwMpqOffset;
	}
	if (v8) {
		sgdwMpqOffset = v3;
	} else {
		v9 = mpqapi_new_block(0);
		v9->offset = v3;
		v9->sizealloc = v2;
		v9->sizefile = 0;
		v9->flags = 0;
	}
}

_BLOCKENTRY *mpqapi_new_block(int *block_index)
{
	_BLOCKENTRY *result; // eax
	unsigned int v2;     // edx

	result = sgpBlockTbl;
	v2 = 0;
	while (result->offset || result->sizealloc || result->flags || result->sizefile) {
		++v2;
		++result;
		if (v2 >= 0x800) {
			app_fatal("Out of free block entries");
			return 0;
		}
	}
	if (block_index)
		*block_index = v2;
	return result;
}

int mpqapi_get_hash_index_of_path(const char *pszName) // FetchHandle
{
	return mpqapi_get_hash_index(Hash(pszName, 0), Hash(pszName, 1), Hash(pszName, 2), 0);
}

int mpqapi_get_hash_index(short index, int hash_a, int hash_b, int locale)
{
	int v4;         // ecx
	signed int v5;  // eax
	signed int v6;  // edx
	_HASHENTRY *v7; // ecx
	int v8;         // edi
	int v10;        // [esp+Ch] [ebp-8h]
	int i;          // [esp+10h] [ebp-4h]

	v4 = index & 0x7FF;
	v10 = hash_a;
	v5 = 2048;
	for (i = v4;; i = (i + 1) & 0x7FF) {
		v7 = &sgpHashTbl[v4];
		v8 = v7->block;
		if (v8 == -1)
			return -1;
		v6 = v5--;
		if (!v6)
			return -1;
		if (v7->hashcheck[0] == v10 && v7->hashcheck[1] == hash_b && v7->lcid == locale && v8 != -2)
			break;
		v4 = (i + 1) & 0x7FF;
	}
	return i;
}

void mpqapi_remove_hash_entries(BOOL(__stdcall *fnGetName)(DWORD, char *))
{
	DWORD dwIndex;
	BOOL i;
	char pszFileName[MAX_PATH];

	dwIndex = 1;
	for (i = fnGetName(0, pszFileName); i; i = fnGetName(dwIndex++, pszFileName)) {
		mpqapi_remove_hash_entry(pszFileName);
	}
}

BOOL mpqapi_write_file(const char *pszName, const BYTE *pbData, DWORD dwLen)
{
	_BLOCKENTRY *blockEntry;

	save_archive_modified = TRUE;
	mpqapi_remove_hash_entry(pszName);
	blockEntry = mpqapi_add_file(pszName, 0, 0);
	if (!mpqapi_write_file_contents(pszName, pbData, dwLen, blockEntry)) {
		mpqapi_remove_hash_entry(pszName);
		return FALSE;
	}
	return TRUE;
}
// 65AB0C: using guessed type int save_archive_modified;

_BLOCKENTRY *mpqapi_add_file(const char *pszName, _BLOCKENTRY *pBlk, int block_index)
{
	const char *v3;   // edi
	short v4;         // si
	int v5;           // ebx
	signed int v6;    // edx
	int v7;           // esi
	int v8;           // ecx
	int v9;           // esi
	int v11;          // [esp+Ch] [ebp-8h]
	_BLOCKENTRY *v12; // [esp+10h] [ebp-4h]

	v12 = pBlk;
	v3 = pszName;
	v4 = Hash(pszName, 0);
	v5 = Hash(v3, 1);
	v11 = Hash(v3, 2);
	if (mpqapi_get_hash_index(v4, v5, v11, 0) != -1)
		app_fatal("Hash collision between \"%s\" and existing file\n", v3);
	v6 = 2048;
	v7 = v4 & 0x7FF;
	while (1) {
		--v6;
		v8 = sgpHashTbl[v7].block;
		if (v8 == -1 || v8 == -2)
			break;
		v7 = (v7 + 1) & 0x7FF;
		if (!v6) {
			v6 = -1;
			break;
		}
	}
	if (v6 < 0)
		app_fatal("Out of hash space");
	if (!v12)
		v12 = mpqapi_new_block(&block_index);
	v9 = v7;
	sgpHashTbl[v9].hashcheck[0] = v5;
	sgpHashTbl[v9].hashcheck[1] = v11;
	sgpHashTbl[v9].lcid = 0;
	sgpHashTbl[v9].block = block_index;
	return v12;
}

BOOL mpqapi_write_file_contents(const char *pszName, const BYTE *pbData, int dwLen, _BLOCKENTRY *pBlk)
{
	const char *v4;              // esi
	const char *v5;              // eax
	unsigned int destsize;       // ebx
	const char *v7;              // eax
	unsigned int v8;             // esi
	_BLOCKENTRY *v9;             // edi
	int v10;                     // eax
	signed int v11;              // eax
	unsigned int v13;            // eax
	unsigned int v14;            // eax
	int v15;                     // ecx
	int size;                    // [esp+Ch] [ebp-10h]
	const BYTE *v17;             // [esp+10h] [ebp-Ch]
	int v18;                     // [esp+14h] [ebp-8h]
	DWORD nNumberOfBytesToWrite; // [esp+18h] [ebp-4h]

	v4 = pszName;
	v17 = pbData;
	v5 = strchr(pszName, ':');
	destsize = 0;
	while (v5) {
		v4 = v5 + 1;
		v5 = strchr(v5 + 1, ':');
	}
	while (1) {
		v7 = strchr(v4, '\\');
		if (!v7)
			break;
		v4 = v7 + 1;
	}
	Hash(v4, 3);
	v8 = dwLen;
	v9 = pBlk;
	size = 4 * ((unsigned int)(dwLen + 4095) >> 12) + 4;
	nNumberOfBytesToWrite = 4 * ((unsigned int)(dwLen + 4095) >> 12) + 4;
	v10 = mpqapi_find_free_block(size + dwLen, &pBlk->sizealloc);
	v9->offset = v10;
	v9->sizefile = v8;
	v9->flags = 0x80000100;
	if (SetFilePointer(sghArchive, v10, NULL, FILE_BEGIN) == -1)
		return 0;
	pBlk = 0;
	v18 = 0;
	while (v8) {
		v11 = 0;
		do
			mpq_buf[v11++] -= 86;
		while (v11 < 4096);
		dwLen = v8;
		if (v8 >= 0x1000)
			dwLen = 4096;
		memcpy(mpq_buf, v17, dwLen);
		v17 += dwLen;
		dwLen = PkwareCompress(mpq_buf, dwLen);
		if (!v18) {
			nNumberOfBytesToWrite = size;
			pBlk = (_BLOCKENTRY *)DiabloAllocPtr(size);
			memset(pBlk, 0, nNumberOfBytesToWrite);
			if (!WriteFile(sghArchive, pBlk, nNumberOfBytesToWrite, &nNumberOfBytesToWrite, 0))
				goto LABEL_25;
			destsize += nNumberOfBytesToWrite;
		}
		*(&pBlk->offset + v18) = destsize;
		if (!WriteFile(sghArchive, mpq_buf, dwLen, (LPDWORD)&dwLen, 0))
			goto LABEL_25;
		++v18;
		if (v8 <= 0x1000)
			v8 = 0;
		else
			v8 -= 4096;
		destsize += dwLen;
	}
	*(&pBlk->offset + v18) = destsize;
	if (SetFilePointer(sghArchive, -destsize, NULL, FILE_CURRENT) == -1
	    || !WriteFile(sghArchive, pBlk, nNumberOfBytesToWrite, &nNumberOfBytesToWrite, 0)
	    || SetFilePointer(sghArchive, destsize - nNumberOfBytesToWrite, NULL, FILE_CURRENT) == -1) {
	LABEL_25:
		if (pBlk)
			mem_free_dbg(pBlk);
		return 0;
	}
	mem_free_dbg(pBlk);
	v13 = v9->sizealloc;
	if (destsize < v13) {
		v14 = v13 - destsize;
		if (v14 >= 0x400) {
			v15 = destsize + v9->offset;
			v9->sizealloc = destsize;
			mpqapi_free_block(v15, v14);
		}
	}
	return 1;
}

int mpqapi_find_free_block(int size, int *block_size)
{
	_BLOCKENTRY *v2; // eax
	signed int v3;   // esi
	int result;      // eax
	int v5;          // esi
	BOOLEAN v6;      // zf

	v2 = sgpBlockTbl;
	v3 = 2048;
	while (1) {
		--v3;
		if (v2->offset) {
			if (!v2->flags && !v2->sizefile && v2->sizealloc >= (unsigned int)size)
				break;
		}
		++v2;
		if (!v3) {
			*block_size = size;
			result = sgdwMpqOffset;
			sgdwMpqOffset += size;
			return result;
		}
	}
	v5 = v2->offset;
	*block_size = size;
	v2->offset += size;
	v6 = v2->sizealloc == size;
	v2->sizealloc -= size;
	if (v6)
		memset(v2, 0, 0x10u);
	return v5;
}

void mpqapi_rename(char *pszOld, char *pszNew)
{
	int index, block;
	_HASHENTRY *hashEntry;
	_BLOCKENTRY *blockEntry;

	index = mpqapi_get_hash_index_of_path(pszOld);
	if (index != -1) {
		hashEntry = &sgpHashTbl[index];
		block = hashEntry->block;
		blockEntry = &sgpBlockTbl[block];
		hashEntry->block = -2;
		mpqapi_add_file(pszNew, blockEntry, block);
		save_archive_modified = TRUE;
	}
}
// 65AB0C: using guessed type int save_archive_modified;

BOOL mpqapi_has_file(const char *pszName)
{
	return mpqapi_get_hash_index_of_path(pszName) != -1;
}

BOOL mpqapi_open_archive(const char *pszArchive, BOOL hidden, int dwChar) // OpenMPQ
{
	const char *v3;         // ebp
	BOOL v4;                // esi
	DWORD v6;               // edi
	int v8;                 // eax
	int v10;                // eax
	const char *lpFileName; // [esp+10h] [ebp-70h]
	DWORD dwTemp;           // [esp+14h] [ebp-6Ch]
	_FILEHEADER fhdr;       // [esp+18h] [ebp-68h]

	v3 = pszArchive;
	v4 = hidden;
	lpFileName = pszArchive;
	InitHash();
	if (!mpqapi_set_hidden(v3, v4))
		return 0;
	v6 = (unsigned char)gbMaxPlayers > 1u ? FILE_FLAG_WRITE_THROUGH : 0;
	save_archive_open = 0;
	sghArchive = CreateFile(v3, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, v6, NULL);
	if (sghArchive == (HANDLE)-1) {
		sghArchive = CreateFile(lpFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, v6 | (v4 != 0 ? FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN : 0), NULL);
		if (sghArchive == (HANDLE)-1)
			return 0;
		save_archive_open = 1;
		save_archive_modified = 1;
	}
	if (!sgpBlockTbl || !sgpHashTbl) {
		memset(&fhdr, 0, 0x68u);
		if (!mpqapi_parse_archive_header(&fhdr, &sgdwMpqOffset)) {
		LABEL_15:
			mpqapi_close_archive(lpFileName, 1, dwChar);
			return 0;
		}
		sgpBlockTbl = (_BLOCKENTRY *)DiabloAllocPtr(0x8000);
		memset(sgpBlockTbl, 0, 0x8000u);
		if (fhdr.blockcount) {
			if (SetFilePointer(sghArchive, 104, NULL, FILE_BEGIN) == -1
			    || !ReadFile(sghArchive, sgpBlockTbl, 0x8000u, &dwTemp, NULL)) {
				goto LABEL_15;
			}
			v8 = Hash("(block table)", 3);
			Decrypt(sgpBlockTbl, 0x8000, v8);
		}
		sgpHashTbl = (_HASHENTRY *)DiabloAllocPtr(0x8000);
		memset(sgpHashTbl, 255, 0x8000u);
		if (fhdr.hashcount) {
			if (SetFilePointer(sghArchive, 32872, NULL, FILE_BEGIN) == -1
			    || !ReadFile(sghArchive, sgpHashTbl, 0x8000u, &dwTemp, NULL)) {
				goto LABEL_15;
			}
			v10 = Hash("(hash table)", 3);
			Decrypt(sgpHashTbl, 0x8000, v10);
		}
	}
	return 1;
}
// 65AB0C: using guessed type int save_archive_modified;
// 65AB14: using guessed type char save_archive_open;
// 679660: using guessed type char gbMaxPlayers;

BOOLEAN mpqapi_parse_archive_header(_FILEHEADER *pHdr, int *pdwNextFileStart) // ParseMPQHeader
{
	int *v2;                 // ebp
	_FILEHEADER *v3;         // esi
	DWORD v4;                // eax
	DWORD v5;                // edi
	DWORD NumberOfBytesRead; // [esp+10h] [ebp-4h]

	v2 = pdwNextFileStart;
	v3 = pHdr;
	v4 = GetFileSize(sghArchive, 0);
	v5 = v4;
	*v2 = v4;
	if (v4 == -1
	    || v4 < 0x68
	    || !ReadFile(sghArchive, v3, 0x68u, &NumberOfBytesRead, NULL)
	    || NumberOfBytesRead != 104
	    || v3->signature != '\x1AQPM'
	    || v3->headersize != 32
	    || v3->version > 0u
	    || v3->sectorsizeid != 3
	    || v3->filesize != v5
	    || v3->hashoffset != 32872
	    || v3->blockoffset != 104
	    || v3->hashcount != 2048
	    || v3->blockcount != 2048) {
		if (SetFilePointer(sghArchive, 0, NULL, FILE_BEGIN) == -1 || !SetEndOfFile(sghArchive))
			return 0;
		memset(v3, 0, 0x68u);
		v3->signature = '\x1AQPM';
		v3->headersize = 32;
		v3->sectorsizeid = 3;
		v3->version = 0;
		*v2 = 0x10068;
		save_archive_modified = 1;
		save_archive_open = 1;
	}
	return 1;
}
// 65AB0C: using guessed type int save_archive_modified;
// 65AB14: using guessed type char save_archive_open;

void mpqapi_close_archive(const char *pszArchive, BOOL bFree, int dwChar) // CloseMPQ
{
	_BLOCKENTRY *blockEntry;
	_HASHENTRY *hashEntry;

	if (bFree) {
		blockEntry = sgpBlockTbl;
		sgpBlockTbl = NULL;
		mem_free_dbg(blockEntry);
		hashEntry = sgpHashTbl;
		sgpHashTbl = NULL;
		mem_free_dbg(hashEntry);
	}
	if (sghArchive != INVALID_HANDLE_VALUE) {
		CloseHandle(sghArchive);
		sghArchive = INVALID_HANDLE_VALUE;
	}
	if (save_archive_modified) {
		save_archive_modified = FALSE;
		mpqapi_store_modified_time(pszArchive, dwChar);
	}
	if (save_archive_open) {
		save_archive_open = FALSE;
		mpqapi_store_creation_time(pszArchive, dwChar);
	}
}
// 65AB0C: using guessed type int save_archive_modified;
// 65AB14: using guessed type char save_archive_open;

void mpqapi_store_modified_time(const char *pszArchive, int dwChar)
{
	int v2;                                // esi
	const char *v3;                        // ebx
	HANDLE v4;                             // eax
	int v5;                                // esi
	struct _WIN32_FIND_DATAA FindFileData; // [esp+8h] [ebp-1E0h]
	char dst[160];                         // [esp+148h] [ebp-A0h]

	v2 = dwChar;
	v3 = pszArchive;
	if (gbMaxPlayers != 1) {
		mpqapi_reg_load_modification_time(dst, 160);
		v4 = FindFirstFile(v3, &FindFileData);
		if (v4 != (HANDLE)-1) {
			FindClose(v4);
			v5 = 16 * v2;
			*(_DWORD *)&dst[v5 + 8] = FindFileData.ftLastWriteTime.dwLowDateTime;
			*(_DWORD *)&dst[v5 + 12] = FindFileData.ftLastWriteTime.dwHighDateTime;
			mpqapi_reg_store_modification_time(dst, 160);
		}
	}
}
// 679660: using guessed type char gbMaxPlayers;

void mpqapi_flush_and_close(const char *pszArchive, BOOL bFree, int dwChar)
{
	if (sghArchive != (HANDLE)-1) {
		if (save_archive_modified) {
			if (mpqapi_can_seek()) {
				if (mpqapi_write_header()) {
					if (mpqapi_write_block_table())
						mpqapi_write_hash_table();
				}
			}
		}
	}
	mpqapi_close_archive(pszArchive, bFree, dwChar);
}
// 65AB0C: using guessed type int save_archive_modified;

BOOLEAN mpqapi_write_header() // WriteMPQHeader
{
	BOOLEAN result;             // al
	_FILEHEADER fhdr;           // [esp+8h] [ebp-6Ch]
	DWORD NumberOfBytesWritten; // [esp+70h] [ebp-4h]

	memset(&fhdr, 0, 0x68u);
	fhdr.signature = '\x1AQPM';
	fhdr.headersize = 32;
	fhdr.filesize = GetFileSize(sghArchive, 0);
	fhdr.version = 0;
	fhdr.sectorsizeid = 3;
	fhdr.hashoffset = 32872;
	fhdr.blockoffset = 104;
	fhdr.hashcount = 2048;
	fhdr.blockcount = 2048;
	if (SetFilePointer(sghArchive, 0, NULL, FILE_BEGIN) != -1 && WriteFile(sghArchive, &fhdr, 0x68u, &NumberOfBytesWritten, 0))
		result = NumberOfBytesWritten == 104;
	else
		result = 0;
	return result;
}

BOOL mpqapi_write_block_table()
{
	BOOL success;
	DWORD NumberOfBytesWritten;

	if (SetFilePointer(sghArchive, 104, NULL, FILE_BEGIN) == -1)
		return FALSE;

	Encrypt(sgpBlockTbl, 0x8000, Hash("(block table)", 3));
	success = WriteFile(sghArchive, sgpBlockTbl, 0x8000, &NumberOfBytesWritten, 0);
	Decrypt(sgpBlockTbl, 0x8000, Hash("(block table)", 3));
	return success && NumberOfBytesWritten == 0x8000;
}

BOOL mpqapi_write_hash_table()
{
	BOOL success;
	DWORD NumberOfBytesWritten;

	if (SetFilePointer(sghArchive, 32872, NULL, FILE_BEGIN) == -1)
		return FALSE;

	Encrypt(sgpHashTbl, 0x8000, Hash("(hash table)", 3));
	success = WriteFile(sghArchive, sgpHashTbl, 0x8000, &NumberOfBytesWritten, 0);
	Decrypt(sgpHashTbl, 0x8000, Hash("(hash table)", 3));
	return success && NumberOfBytesWritten == 0x8000;
}

BOOL mpqapi_can_seek()
{
	if (SetFilePointer(sghArchive, sgdwMpqOffset, NULL, FILE_BEGIN) == -1)
		return FALSE;
	return SetEndOfFile(sghArchive);
}
