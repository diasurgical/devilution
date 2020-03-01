/**
 * @file capture.cpp
 *
 * Implementation of the screenshot function.
 */
#include "all.h"

/**
 * @brief Write the PCX-file header
 * @param hFile File handler for the PCX file.
 * @param width Image width
 * @param height Image height
 * @return True on success
 */
static BOOL CaptureHdr(HANDLE hFile, short width, short height)
{
	DWORD lpNumBytes;
	PCXHEADER Buffer;

	memset(&Buffer, 0, sizeof(Buffer));
	Buffer.Manufacturer = 10;
	Buffer.Version = 5;
	Buffer.Encoding = 1;
	Buffer.BitsPerPixel = 8;
	Buffer.Xmax = width - 1;
	Buffer.Ymax = height - 1;
	Buffer.HDpi = width;
	Buffer.VDpi = height;
	Buffer.NPlanes = 1;
	Buffer.BytesPerLine = width;

	return WriteFile(hFile, &Buffer, sizeof(Buffer), &lpNumBytes, NULL) && lpNumBytes == sizeof(Buffer);
}

static BOOL CapturePal(HANDLE hFile, PALETTEENTRY *palette)
{
	DWORD NumberOfBytesWritten;
	BYTE pcx_palette[769];
	int i;

	pcx_palette[0] = 12;
	for (i = 0; i < 256; i++) {
		pcx_palette[1 + 3 * i + 0] = palette[i].peRed;
		pcx_palette[1 + 3 * i + 1] = palette[i].peGreen;
		pcx_palette[1 + 3 * i + 2] = palette[i].peBlue;
	}

	return WriteFile(hFile, pcx_palette, 769, &NumberOfBytesWritten, 0) && NumberOfBytesWritten == 769;
}

static BYTE *CaptureEnc(BYTE *src, BYTE *dst, int width)
{
	int rleLength;

	do {
		BYTE rlePixel = *src;
		*src++;
		rleLength = 1;

		width--;

		while (rlePixel == *src) {
			if (rleLength >= 63)
				break;
			if (!width)
				break;
			rleLength++;

			width--;
			src++;
		}

		if (rleLength > 1 || rlePixel > 0xBF) {
			*dst = rleLength | 0xC0;
			*dst++;
		}

		*dst = rlePixel;
		*dst++;
	} while (width);

	return dst;
}

static BOOL CapturePix(HANDLE hFile, WORD width, WORD height, WORD stride, BYTE *pixels)
{
	int writeSize;
	DWORD lpNumBytes;
	BYTE *pBuffer, *pBufferEnd;

	pBuffer = (BYTE *)DiabloAllocPtr(2 * width);
	while (height--) {
		pBufferEnd = CaptureEnc(pixels, pBuffer, width);
		pixels += stride;
		writeSize = pBufferEnd - pBuffer;
		if (!(WriteFile(hFile, pBuffer, writeSize, &lpNumBytes, 0) && lpNumBytes == writeSize)) {
			return FALSE;
		}
	}
	mem_free_dbg(pBuffer);
	return TRUE;
}

static HANDLE CaptureFile(char *dst_path)
{
	BOOLEAN num_used[100];
	int free_num, hFind;
	struct _finddata_t finder;

	memset(num_used, FALSE, sizeof(num_used));
	hFind = _findfirst("screen??.PCX", &finder);
	if (hFind != -1) {
		do {
			if (isdigit(finder.name[6]) && isdigit(finder.name[7])) {
				free_num = 10 * (finder.name[6] - '0');
				free_num += (finder.name[7] - '0');
				num_used[free_num] = TRUE;
			}
		} while (_findnext(hFind, &finder) == 0);
	}

	for (free_num = 0; free_num < 100; free_num++) {
		if (!num_used[free_num]) {
			sprintf(dst_path, "screen%02d.PCX", free_num);
			return CreateFile(dst_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
	}

	return INVALID_HANDLE_VALUE;
}

static void RedPalette(PALETTEENTRY *pal)
{
	PALETTEENTRY red[256];
	int i;

	for (i = 0; i < 256; i++) {
		red[i].peRed = pal[i].peRed;
		red[i].peGreen = 0;
		red[i].peBlue = 0;
		red[i].peFlags = 0;
	}

#ifdef __cplusplus
	lpDDPalette->SetEntries(0, 0, 256, red);
#else
	lpDDPalette->lpVtbl->SetEntries(lpDDPalette, 0, 0, 256, red);
#endif
}

void CaptureScreen()
{
	HANDLE hObject;
	PALETTEENTRY palette[256];
	char FileName[MAX_PATH];
	BOOL success;

	hObject = CaptureFile(FileName);
	if (hObject != INVALID_HANDLE_VALUE) {
		DrawAndBlit();
#ifdef __cplusplus
		lpDDPalette->GetEntries(0, 0, 256, palette);
#else
		lpDDPalette->lpVtbl->GetEntries(lpDDPalette, 0, 0, 256, palette);
#endif
		RedPalette(palette);

		lock_buf(2);
		success = CaptureHdr(hObject, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (success) {
			success = CapturePix(hObject, SCREEN_WIDTH, SCREEN_HEIGHT, BUFFER_WIDTH, &gpBuffer[SCREENXY(0, 0)]);
		}
		if (success) {
			success = CapturePal(hObject, palette);
		}
		unlock_buf(2);
		CloseHandle(hObject);

		if (!success)
			DeleteFile(FileName);

		Sleep(300);
#ifdef __cplusplus
		lpDDPalette->SetEntries(0, 0, 256, palette);
#else
		lpDDPalette->lpVtbl->SetEntries(lpDDPalette, 0, 0, 256, palette);
#endif
	}
}
