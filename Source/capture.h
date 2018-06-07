/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

void __cdecl CaptureScreen();
bool __fastcall CaptureHdr(HANDLE hFile, short width, int height);
bool __fastcall CapturePal(HANDLE hFile, PALETTEENTRY *palette);
bool __fastcall CapturePix(HANDLE hFile, short width, short height, short stride, char *pixels);
char *__fastcall CaptureEnc(char *src, char *dst, int width);
HANDLE __fastcall CaptureFile(char *dst_path);
void __fastcall RedPalette(PALETTEENTRY *pal);