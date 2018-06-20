//HEADER_GOES_HERE
#ifndef __CAPTURE_H__
#define __CAPTURE_H__

void __cdecl CaptureScreen();
bool __fastcall CaptureHdr(HANDLE hFile, short width, int height);
bool __fastcall CapturePal(HANDLE hFile, PALETTEENTRY *palette);
bool __fastcall CapturePix(HANDLE hFile, short width, short height, short stride, char *pixels);
char *__fastcall CaptureEnc(char *src, char *dst, int width);
HANDLE __fastcall CaptureFile(char *dst_path);
void __fastcall RedPalette(PALETTEENTRY *pal);

#endif /* __CAPTURE_H__ */
