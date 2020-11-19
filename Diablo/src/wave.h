/**
 * @file wave.h
 *
 * Interface of functionality for loading files and processing wave files.
 */
#ifndef __WAVE_H__
#define __WAVE_H__

void WCloseFile(HANDLE file);
LONG WGetFileSize(HANDLE hsFile, DWORD *lpFileSizeHigh);
BOOL WOpenFile(const char *FileName, HANDLE *phsFile, BOOL mayNotExist);
void WReadFile(HANDLE hsFile, LPVOID buf, DWORD to_read);
int WSetFilePointer(HANDLE file1, int offset, HANDLE file2, int whence);
BOOL LoadWaveFormat(HANDLE hsFile, WAVEFORMATEX *pwfx);
void AllocateMemFile(HANDLE hsFile, MEMFILE *pMemFile, DWORD dwPos);
BYTE *LoadWaveFile(HANDLE hsFile, WAVEFORMATEX *pwfx, CKINFO *chunk);

#endif /* __WAVE_H__ */
