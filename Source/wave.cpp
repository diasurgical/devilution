/**
 * @file wave.cpp
 *
 * Implementation of functionality for loading and processing wave files.

 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

static void WGetFileArchive(HANDLE hsFile, DWORD *retries, const char *FileName)
{
	HANDLE archive;

	if (*retries >= 5)
		FileErrDlg(FileName);

	if (hsFile && SFileGetFileArchive(hsFile, &archive) && archive != ghsMainArchive) {
		Sleep(20);
		(*retries)++;
	} else if (!InsertCDDlg())
		FileErrDlg(FileName);
}

void WCloseFile(HANDLE file)
{
	SFileCloseFile(file);
}

LONG WGetFileSize(HANDLE hsFile, DWORD *lpFileSizeHigh)
{
	DWORD retry = 0;
	LONG ret;

	while ((ret = SFileGetFileSize(hsFile, lpFileSizeHigh)) == 0)
		WGetFileArchive(hsFile, &retry, NULL);

	return ret;
}

BOOL WOpenFile(const char *FileName, HANDLE *phsFile, BOOL mayNotExist)
{
	DWORD retry = 0;

	while (1) {
		if (SFileOpenFile(FileName, phsFile))
			return TRUE;
		if (mayNotExist && DERROR() == ERROR_FILE_NOT_FOUND)
			break;
		WGetFileArchive(NULL, &retry, FileName);
	}
	return FALSE;
}

void WReadFile(HANDLE hsFile, LPVOID buf, DWORD to_read)
{
	DWORD retry = 0;
	DWORD readed;
	int initial_pos = WSetFilePointer(hsFile, 0, NULL, FILE_CURRENT);

	while (!SFileReadFile(hsFile, buf, to_read, &readed, NULL)) {
		WGetFileArchive(hsFile, &retry, NULL);
		WSetFilePointer(hsFile, initial_pos, NULL, FILE_BEGIN);
	}
}

int WSetFilePointer(HANDLE file1, int offset, HANDLE file2, int whence)
{
	DWORD retry = 0;
	int result;

	while (1) {
		result = SFileSetFilePointer(file1, offset, file2, whence);
		if (result != -1)
			break;
		WGetFileArchive(file1, &retry, NULL);
	}
	return result;
}

// 1.09b order: these come after LoadWaveFormat and AllocateMemFile
static void FreeMemFile(MEMFILE *pMemFile);
static BOOL ReadWaveFile(MEMFILE *pMemFile, WAVEFORMATEX *pwfx, CKINFO *chunk);
static BOOL ReadMemFile(MEMFILE *pMemFile, void *lpBuf, size_t length);
static void FillMemFile(MEMFILE *pMemFile);
static int SeekMemFile(MEMFILE *pMemFile, ULONG lDist, DWORD dwMethod);
static BOOL ReadWaveSection(MEMFILE *pMemFile, DWORD id, CKINFO *chunk);

BOOL LoadWaveFormat(HANDLE hsFile, WAVEFORMATEX *pwfx)
{
	BOOL ret;
	MEMFILE wave_file;

	AllocateMemFile(hsFile, &wave_file, 0);
	ret = ReadWaveFile(&wave_file, pwfx, NULL);
	FreeMemFile(&wave_file);
	return ret;
}

void AllocateMemFile(HANDLE hsFile, MEMFILE *pMemFile, DWORD dwPos)
{
	DWORD length;

	memset(pMemFile, 0, sizeof(*pMemFile));
	pMemFile->end = WGetFileSize(hsFile, NULL);
	length = 4096;
	if (dwPos > length)
		length = dwPos;
	pMemFile->buf_len = length;
	if (length >= pMemFile->end)
		length = pMemFile->end;
	pMemFile->buf_len = length;
	pMemFile->buf = DiabloAllocPtr(length);
	pMemFile->file = hsFile;
}

static void FreeMemFile(MEMFILE *pMemFile)
{
	MemFreeDbg(pMemFile->buf);
}

static BOOL ReadWaveFile(MEMFILE *pMemFile, WAVEFORMATEX *pwfx, CKINFO *chunk)
{
	MMCKINFO hdr;
	CKINFO fmt;
	PCMWAVEFORMAT wf;

	if (!ReadMemFile(pMemFile, &hdr, 12))
		return FALSE;
	if (hdr.ckid != FOURCC_RIFF || hdr.fccType != MAKEFOURCC('W', 'A', 'V', 'E'))
		return FALSE;
	if (!ReadWaveSection(pMemFile, MAKEFOURCC('f', 'm', 't', ' '), &fmt))
		return FALSE;
	if (fmt.dwSize < sizeof(PCMWAVEFORMAT))
		return FALSE;
	if (!ReadMemFile(pMemFile, &wf, sizeof(wf)))
		return FALSE;
	if (SeekMemFile(pMemFile, fmt.dwSize - sizeof(wf), FILE_CURRENT) == -1)
		return FALSE;

	pwfx->cbSize = 0;
	pwfx->wFormatTag = wf.wf.wFormatTag;
	pwfx->nChannels = wf.wf.nChannels;
	pwfx->nSamplesPerSec = wf.wf.nSamplesPerSec;
	pwfx->nAvgBytesPerSec = wf.wf.nAvgBytesPerSec;
	pwfx->nBlockAlign = wf.wf.nBlockAlign;
	pwfx->wBitsPerSample = wf.wBitsPerSample;
	if (chunk == NULL)
		return TRUE;
	return ReadWaveSection(pMemFile, MAKEFOURCC('d', 'a', 't', 'a'), chunk);
}

static BOOL ReadMemFile(MEMFILE *pMemFile, void *lpBuf, size_t length)
{
	while (length) {
		size_t to_copy;
		if (!pMemFile->bytes_to_read)
			FillMemFile(pMemFile);
		to_copy = pMemFile->bytes_to_read;
		if (length < to_copy)
			to_copy = length;
		if (!to_copy)
			return FALSE;
		memcpy(lpBuf, &pMemFile->buf[pMemFile->dist], to_copy);
		pMemFile->offset += to_copy;
		pMemFile->dist += to_copy;
		pMemFile->bytes_to_read -= to_copy;
		// BUGFIX: lpBuf is not incremented, next read will overwrite data
		length -= to_copy;
	}
	return TRUE;
}

static void FillMemFile(MEMFILE *pMemFile)
{
	DWORD to_read;
	WSetFilePointer(pMemFile->file, pMemFile->offset, NULL, FILE_BEGIN);
	to_read = pMemFile->end - pMemFile->offset;
	if (pMemFile->buf_len < to_read)
		to_read = pMemFile->buf_len;
	if (to_read)
		WReadFile(pMemFile->file, pMemFile->buf, to_read);
	pMemFile->dist = 0;
	pMemFile->bytes_to_read = to_read;
}

static int SeekMemFile(MEMFILE *pMemFile, ULONG lDist, DWORD dwMethod)
{
	if (lDist < pMemFile->bytes_to_read) {
		pMemFile->bytes_to_read -= lDist;
		pMemFile->dist += lDist;
	} else
		pMemFile->bytes_to_read = 0;
	pMemFile->offset += lDist;
	return pMemFile->offset;
}

static BOOL ReadWaveSection(MEMFILE *pMemFile, DWORD id, CKINFO *chunk)
{
	DWORD hdr[2];

	while (1) {
		if (!ReadMemFile(pMemFile, hdr, sizeof(hdr)))
			return FALSE;
		if (hdr[0] == id)
			break;
		if (SeekMemFile(pMemFile, hdr[1], FILE_CURRENT) == -1)
			return FALSE;
	}

	chunk->dwSize = hdr[1];
	chunk->dwOffset = SeekMemFile(pMemFile, 0, FILE_CURRENT);
	return chunk->dwOffset != (DWORD)-1;
}

BYTE *LoadWaveFile(HANDLE hsFile, WAVEFORMATEX *pwfx, CKINFO *chunk)
{
	MEMFILE wave_file;

	AllocateMemFile(hsFile, &wave_file, (DWORD)-1);
	if (!ReadWaveFile(&wave_file, pwfx, chunk)) {
		FreeMemFile(&wave_file);
		return NULL;
	}
	return wave_file.buf;
}

/* In 1.09b this call goes through a one-line wrapper here (name not known). */
void j_mem_free_dbg(void *p)
{
	mem_free_dbg(p);
}

#ifndef HELLFIRE
/*
 * Unused placeholders (the linker drops them). The linker folds identical functions (/OPT:ICF) and which copy
 * it keeps depends on all the functions it sees, including unused ones; 1.09b had unused code we do not know.
 * These 14 stand in for it, so that the C runtime keeps the same copies as in 1.09b.
 */
extern "C" int zzdummy0(int a)
{
	return a * 13 + 5;
}
extern "C" int zzdummy1(int a)
{
	return a * 20 + 36;
}
extern "C" int zzdummy2(int a)
{
	return a * 27 + 67;
}
extern "C" int zzdummy3(int a)
{
	return a * 34 + 98;
}
extern "C" int zzdummy4(int a)
{
	return a * 41 + 129;
}
extern "C" int zzdummy5(int a)
{
	return a * 48 + 160;
}
extern "C" int zzdummy6(int a)
{
	return a * 55 + 191;
}
extern "C" int zzdummy7(int a)
{
	return a * 62 + 222;
}
extern "C" int zzdummy8(int a)
{
	return a * 69 + 253;
}
extern "C" int zzdummy9(int a)
{
	return a * 76 + 284;
}
extern "C" int zzdummy10(int a)
{
	return a * 83 + 315;
}
extern "C" int zzdummy11(int a)
{
	return a * 90 + 346;
}
extern "C" int zzdummy12(int a)
{
	return a * 97 + 377;
}
extern "C" int zzdummy13(int a)
{
	return a * 104 + 408;
}
#endif
