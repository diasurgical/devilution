#include <windows.h>
#include <stdio.h>
#include <ddraw.h>
#include <dsound.h>
#include <io.h>
#include <math.h>
#include <time.h>
#include <process.h>
#include <shlobj.h>

#ifdef _MSC_VER
#pragma warning (disable : 4018) // signed/unsigned mismatch
#endif

#include "..\defs.h"
#include "..\structs.h"
#include "..\3rdParty\Storm\Source\storm.h"
#include "diabloui.h"

#define UNKCALL     __fastcall
#define USERCALL    __fastcall
#define USERPURGE   __fastcall

//temporarily include everything directly
#include "_temp_funcs.h"
#include "_temp_data.cpp"

#include "artfont.cpp"
#include "bnetgw.cpp"
#include "bn_prof.cpp"
#include "connect.cpp"
#include "copyprot.cpp"
#include "cr8game.cpp"
#include "creadung.cpp"
#include "creastat.cpp"
#include "credits.cpp"
#include "diabedit.cpp"
#include "dirlink.cpp"
#include "disclaim.cpp"
#include "doom.cpp"
#include "entdial.cpp"
#include "entname.cpp"
#include "fade.cpp"
#include "focus.cpp"
#include "local.cpp"
#include "mainmenu.cpp"
#include "modem.cpp"
#include "modmstat.cpp"
#include "okcancel.cpp"
#include "progress.cpp"
#include "sbar.cpp"
#include "selclass.cpp"
#include "selconn.cpp"
#include "seldial.cpp"
#include "selgame.cpp"
#include "selhero.cpp"
#include "selipx.cpp"
#include "sellist.cpp"
#include "selload.cpp"
#include "selmodem.cpp"
#include "selregn.cpp"
#include "selyesno.cpp"
#include "title.cpp"
#include "titlesnd.cpp"


// ref: 0x10005C2A
int DiabloUI_10005C2A() { return 0; }
/* {
	return dword_1002972C;
} */
// 1002972C: using guessed type int dword_1002972C;

// ref: 0x10005C30
void __stdcall UiOnPaint(int a1)
{
	return;
}

// ref: 0x10005C33
int __stdcall UiSetBackgroundBitmap(int a1, int a2, int a3, int a4, int a5) { return 0; }
/* {
	dword_1002971C = a3;
	dword_10029720 = a4;
	dword_10029724 = a5;
	return SDrawUpdatePalette(10, 236, a2 + 40, 0);
} */
// 100103FA: using guessed type int __stdcall SDrawUpdatePalette(_DWORD, _DWORD, _DWORD, _DWORD);
// 1002971C: using guessed type int dword_1002971C;
// 10029720: using guessed type int dword_10029720;
// 10029724: using guessed type int dword_10029724;

// ref: 0x10005C67
int __stdcall UiSetSpawned(int a1) { return 0; }
/* {
	int result; // eax

	result = a1;
	dword_1002972C = a1;
	return result;
} */
// 1002972C: using guessed type int dword_1002972C;

// ref: 0x10005C73
void __cdecl UiInitialize() { return; }
//int UiInitialize() { return 0; }
/* {
	dword_10029714 = 1;
	TitleSnd_1001030D();
	artfont_10001098();
	Connect_10002EC4();
	local_10007FD0();
	return bn_prof_100021C4();
} */
// 10029714: using guessed type int dword_10029714;

// ref: 0x10005C96
void __cdecl UiDestroy() { return; }
//int UiDestroy() { return 0; }
/* {
	int result; // eax

	bn_prof_10002247();
	local_100080AD();
	result = Connect_10002E2B();
	dword_10029714 = 0;
	return result;
} */
// 10029714: using guessed type int dword_10029714;

// ref: 0x10005CAD
void __stdcall UiAppActivate(int a1) { return; }
//int __stdcall UiAppActivate(int a1) { return 0; }
/* {
	int result; // eax

	result = a1;
	dword_10029728 = a1;
	return result;
} */
// 10029728: using guessed type int dword_10029728;

// ref: 0x10005CB9
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if ( fdwReason )
	{
		if ( fdwReason == 1 )
		{
			// hInstance = hinstDLL;
			DiabEdit_100057A6();
			local_InitUiPalette();
		}
	}
	else
	{
		local_DelUiPalette();
	}
	return 1;
}

// ref: 0x10005CEA
signed int DiabloUI_10005CEA() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_10029710 = 2139095040;
	return result;
} */
// 10029710: using guessed type int dword_10029710;
