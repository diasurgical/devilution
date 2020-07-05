/**
 * @file wave.h
 *
 * Interface of functionality for loading fies and processing wave files.
 */
#ifndef __WAVE_H__
#define __WAVE_H__

void WCloseFile(HANDLE file);
LONG WGetFileSize(HANDLE hsFile, DWORD *lpFileSizeHigh);
void WGetFileArchive(HANDLE hsFile, DWORD *retry, const char *FileName);
BOOL WOpenFile(const char *FileName, HANDLE *phsFile, BOOL mayNotExist);
void WReadFile(HANDLE hsFile, LPVOID buf, DWORD to_read);
int WSetFilePointer(HANDLE file1, int offset, HANDLE file2, int whence);
BOOL LoadWaveFormat(HANDLE hsFile, WAVEFORMATEX *pwfx);
void AllocateMemFile(HANDLE hsFile, MEMFILE *pMemFile, DWORD dwPos);
void FreeMemFile(MEMFILE *pMemFile);
BOOL ReadWaveFile(MEMFILE *pMemFile, WAVEFORMATEX *pwfx, CKINFO *chunk);
BOOL ReadMemFile(MEMFILE *pMemFile, void *lpBuf, size_t length);
void FillMemFile(MEMFILE *pMemFile);
int SeekMemFile(MEMFILE *pMemFile, ULONG lDist, DWORD dwMethod);
BOOL ReadWaveSection(MEMFILE *pMemFile, DWORD id, CKINFO *chunk);
BYTE *LoadWaveFile(HANDLE hsFile, WAVEFORMATEX *pwfx, CKINFO *chunk);

#endif /* __WAVE_H__ */
