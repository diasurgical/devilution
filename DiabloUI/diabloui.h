//HEADER_GOES_HERE
#ifndef __DIABLOUI_H__
#define __DIABLOUI_H__

#ifdef __GNUC__
extern "C" {
#endif

struct FontStruct
{
	unsigned char fontbin[258];
	HANDLE fonttrans[256];
	BOOL active;
};

struct ProfileStruct
{
	char *name;
	char field_4;
	int msg;
	int field_C;
};

struct ProfFntStruct
{
	int size;
	char *fontname;
	int field_8;
};

void __cdecl UiDestroy();
BOOL __stdcall UiTitleDialog(int a1);
void __cdecl UiInitialize();
void __stdcall UiCopyProtError(int a1);
void __stdcall UiAppActivate(BOOL bActive);
int __stdcall UiValidPlayerName(char *a1);
int __stdcall UiSelHeroMultDialog(void *fninfo, void *fncreate, void *fnremove, void *fnstats, int *a5, int *a6, char *name);
int __stdcall UiSelHeroSingDialog(void *fninfo, void *fncreate, void *fnremove, void *fnstats, int *a5, char *name, int *difficulty);
void __stdcall UiCreditsDialog(int a1);
BOOL __stdcall UiMainMenuDialog(char *name, int *pdwResult, void (__stdcall *fnSound)(char *file), int a4);
int __stdcall UiProgressDialog(HWND window, char *msg, int a3, void *fnfunc, int a5);
int __cdecl UiProfileGetString();
void __cdecl UiProfileCallback();
void __cdecl UiProfileDraw();
void __cdecl UiCategoryCallback();
void __cdecl UiGetDataCallback();
void __cdecl UiAuthCallback();
void __cdecl UiSoundCallback();
void __cdecl UiMessageBoxCallback();
void __cdecl UiDrawDescCallback();
void __cdecl UiCreateGameCallback();
void __cdecl UiArtCallback();
int __stdcall UiSelectGame(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info, _SNETVERSIONDATA *file_info, int *a6);
int __stdcall UiSelectProvider(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info, _SNETVERSIONDATA *file_info, int *type);
int __stdcall UiCreatePlayerDescription(_uiheroinfo *info, int mode, char *desc);
int __stdcall UiSetupPlayerInfo(char *str, _uiheroinfo *info, int mode);

#ifdef __GNUC__
}
#endif

#endif /* __DIABLOUI_H__ */
