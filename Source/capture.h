//HEADER_GOES_HERE
#ifndef __CAPTURE_H__
#define __CAPTURE_H__

void __cdecl CaptureScreen();
BOOL __fastcall CaptureHdr(HANDLE hFile, short width, short height);
BOOL __fastcall CapturePal(HANDLE hFile, PALETTEENTRY *palette);
BOOL __fastcall CapturePix(HANDLE hFile, WORD width, WORD height, WORD stride, BYTE *pixels);
BYTE *__fastcall CaptureEnc(BYTE *src, BYTE *dst, int width);
HANDLE __fastcall CaptureFile(char *dst_path);
void __fastcall RedPalette(PALETTEENTRY *pal);

#endif /* __CAPTURE_H__ */
