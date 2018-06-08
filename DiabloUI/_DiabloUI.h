/*
 * Diablo(TM)
 *
 * Copyright (C) 1996 Blizzard Entertainment
 * All Rights Reserved.
 *
 * DiabloUI.h
 *   definitions for DiabloUI
 */


extern "C" void UiDestroy(); // { return; }
extern "C" void __stdcall UiTitleDialog(int a1); // { return; }
extern "C" void __cdecl UiInitialize(); // { return; }
extern "C" void __stdcall UiCopyProtError(int a1); // { return; }
extern "C" void __stdcall UiAppActivate(int a1); // { return; }
extern "C" int __stdcall UiValidPlayerName(char *a1); // { return 0; }
extern "C" int __stdcall UiSelHeroMultDialog(void *fninfo, void *fncreate, void *fnremove, void *fnstats, int *a5, int *a6, char *name); // { return 0; }
extern "C" int __stdcall UiSelHeroSingDialog(void *fninfo, void *fncreate, void *fnremove, void *fnstats, int *a5, char *name, int *difficulty); // { return 0; }
extern "C" void __stdcall UiCreditsDialog(int a1); // { return; }
extern "C" int __stdcall UiMainMenuDialog(char *name, int *a2, void *fnSound, int a4); // { return 0; }
extern "C" int __stdcall UiProgressDialog(HWND window, char *msg, int a3, void *fnfunc, int a5); // { return 0; }
extern "C" int __cdecl UiProfileGetString(); // { return; }
extern "C" void __cdecl UiProfileCallback(); // { return; }
extern "C" void __cdecl UiProfileDraw(); // { return; }
extern "C" void __cdecl UiCategoryCallback(); // { return; }
extern "C" void __cdecl UiGetDataCallback(); // { return; }
extern "C" void __cdecl UiAuthCallback(); // { return; }
extern "C" void __cdecl UiSoundCallback(); // { return; }
extern "C" void __cdecl UiMessageBoxCallback(); // { return; }
extern "C" void __cdecl UiDrawDescCallback(); // { return; }
extern "C" void __cdecl UiCreateGameCallback(); // { return; }
extern "C" void __cdecl UiArtCallback(); // { return; }
extern "C" int __stdcall UiSelectGame(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info, _SNETVERSIONDATA *file_info, int *a6); // { return 0; }
extern "C" int __stdcall UiSelectProvider(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info, _SNETVERSIONDATA *file_info, int *type); // { return 0; }
extern "C" int __stdcall UiCreatePlayerDescription(_uiheroinfo *info, int mode, char *desc); // { return 0; }
extern "C" int __stdcall UiSetupPlayerInfo(char *str, _uiheroinfo *info, int mode); // { return 0; }
