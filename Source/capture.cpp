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

#include "../types.h"

//----- (0040311B) --------------------------------------------------------
void __cdecl CaptureScreen()
{
	int v4; // edi
	PALETTEENTRY palette[256]; // [esp+0h] [ebp-508h]
	char FileName[260]; // [esp+400h] [ebp-108h]
	HANDLE hObject; // [esp+504h] [ebp-4h]

	hObject = CaptureFile(FileName);
	if ( hObject != (HANDLE)-1 )
	{
		DrawAndBlit();
		IDirectDrawPalette_GetEntries(lpDDPalette, 0, 0, 256, palette);
		RedPalette(palette);
		dx_lock_mutex();
		v4 = CaptureHdr(hObject, 640, 480);
		if ( v4 )
		{
			v4 = CapturePix(hObject, 640, 480, 768, gpBuffer->row[0].pixels);
			if ( v4 )
			{
				v4 = CapturePal(hObject, palette);
			}
		}
		dx_unlock_mutex();
		CloseHandle(hObject);
		if ( !v4 )
			DeleteFileA(FileName);
		Sleep(300);
		IDirectDrawPalette_SetEntries(lpDDPalette, 0, 0, 256, palette);
	}
}
// 40311B: could not find valid save-restore pair for ebx
// 40311B: could not find valid save-restore pair for edi
// 40311B: could not find valid save-restore pair for esi

//----- (00403204) --------------------------------------------------------
bool __fastcall CaptureHdr(HANDLE hFile, short width, int height)
{
	short v3; // si
	HANDLE v4; // ebx
	PCXHeader Buffer; // [esp+Ch] [ebp-84h]
	DWORD lpNumBytes; // [esp+8Ch] [ebp-4h]

	v3 = width;
	v4 = hFile;
	memset(&Buffer, 0, 0x80u);
	Buffer.xmax = v3 - 1;
	Buffer.vertRes = height;
	Buffer.manufacturer = 10;
	Buffer.version = 5;
	Buffer.encoding = 1;
	Buffer.bitsPerPixel = 8;
	Buffer.ymax = height - 1;
	Buffer.horzRes = v3;
	Buffer.numColorPlanes = 1;
	Buffer.bytesPerScanLine = v3;
	return WriteFile(v4, &Buffer, 0x80u, &lpNumBytes, NULL) && lpNumBytes == 128;
}

//----- (00403294) --------------------------------------------------------
bool __fastcall CapturePal(HANDLE hFile, PALETTEENTRY *palette)
{
	BYTE *v2; // eax
	char *v3; // esi
	signed int v4; // edx
	char Buffer[772]; // [esp+8h] [ebp-308h]
	DWORD lpNumBytes; // [esp+30Ch] [ebp-4h]

	v2 = &palette->peBlue;
	Buffer[0] = 12;
	v3 = &Buffer[2];
	v4 = 256;
	do
	{
		*(v3 - 1) = *(v2 - 2);
		*v3 = *(v2 - 1);
		v3[1] = *v2;
		v2 += 4;
		v3 += 3;
		--v4;
	}
	while ( v4 );
	return WriteFile(hFile, Buffer, 0x301u, &lpNumBytes, 0) && lpNumBytes == 769;
}

//----- (004032FD) --------------------------------------------------------
bool __fastcall CapturePix(HANDLE hFile, short width, short height, short stride, char *pixels)
{
	int v5; // esi
	char *v6; // edi
	char *v7; // eax
	int v8; // ebx
	DWORD lpNumBytes; // [esp+Ch] [ebp-8h]
	HANDLE hFilea; // [esp+10h] [ebp-4h]

	v5 = (unsigned short)width;
	hFilea = hFile;
	v6 = (char *)DiabloAllocPtr(2 * (unsigned short)width);
	do
	{
		if ( !height )
		{
			mem_free_dbg(v6);
			return 1;
		}
		*(_DWORD *)&height = height + 0xFFFF;
		v7 = CaptureEnc(pixels, v6, v5);
		pixels += (unsigned short)stride;
		v8 = v7 - v6;
	}
	while ( WriteFile(hFilea, v6, v7 - v6, &lpNumBytes, 0) && lpNumBytes == v8 );
	return 0;
}

//----- (0040336A) --------------------------------------------------------
char *__fastcall CaptureEnc(char *src, char *dst, int width)
{
	int v3; // esi
	char v4; // bl
	signed int v5; // eax

	v3 = width;
	do
	{
		v4 = *src++;
		v5 = 1;
		--v3;
		if ( v4 == *src )
		{
			do
			{
				if ( v5 >= 63 )
					break;
				if ( !v3 )
					break;
				++v5;
				--v3;
				++src;
			}
			while ( v4 == *src );
			if ( v5 > 1 )
				goto LABEL_13;
		}
		if ( (unsigned char)v4 > 0xBFu )
LABEL_13:
			*dst++ = v5 | 0xC0;
		*dst++ = v4;
	}
	while ( v3 );
	return dst;
}

//----- (004033A8) --------------------------------------------------------
HANDLE __fastcall CaptureFile(char *dst_path)
{
	char *v1; // edi
	__int32 v2; // esi
	int v3; // eax
	int v5; // [esp-4h] [ebp-18Ch]
	struct _finddata_t v6; // [esp+Ch] [ebp-17Ch]
	char v7[100]; // [esp+124h] [ebp-64h]

	v1 = dst_path;
	memset(v7, 0, 0x64u);
	v2 = _findfirst("screen??.PCX", &v6);
	if ( v2 != -1 )
	{
		do
		{
			if ( isdigit(v6.name[6]) )
			{
				if ( isdigit(v6.name[7]) )
					v7[10 * v6.name[6] - 528 + v6.name[7]] = 1;
			}
		}
		while ( !_findnext(v2, &v6) );
	}
	v3 = 0;
	while ( v7[v3] )
	{
		if ( ++v3 >= 100 )
			return (HANDLE)-1;
	}
	v5 = v3;
	sprintf(v1, "screen%02d.PCX", v3);
	return CreateFileA(v1, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}
// 4033A8: using guessed type char var_64[100];

//----- (00403470) --------------------------------------------------------
void __fastcall RedPalette(PALETTEENTRY *pal)
{
	int i; // eax
	PALETTEENTRY red[256]; // [esp+Ch] [ebp-400h]

	for(i = 0; i < 256; i++)
	{
		red[i].peRed = pal[i].peRed;
		red[i].peGreen = 0;
		red[i].peBlue = 0;
		red[i].peFlags = 0;
	}

	IDirectDrawPalette_SetEntries(lpDDPalette, 0, 0, 256, red);
}
