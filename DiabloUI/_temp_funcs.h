void UNKCALL artfont_10001058(char *arg);
int artfont_10001098();
int artfont_100010C8();
int UNKCALL artfont_10001120(_DWORD *arg);
signed int artfont_10001159();
void __fastcall artfont_100011FB(int ecx0, int edx0, const char *a1);
int artfont_100012F6();
int artfont_10001310();
int __fastcall artfont_10001329(unsigned char *a1);
signed int artfont_1000136C();
int __fastcall artfont_10001377(unsigned char *a1);
BOOL __cdecl artfont_100013B3(void *location);
void __fastcall artfont_100013CD(unsigned char *a1, _DWORD *a2, int a3, int a4);


signed int bn_prof_100014E8();
//const char *UiProfileGetString();
//BOOL __stdcall UiProfileCallback(int a1, int a2, int a3, int a4, LPARAM a5, int a6, int a7, int a8, int (__stdcall *a9)(_DWORD, _DWORD, _DWORD, _DWORD));
HGDIOBJ __stdcall bn_prof_1000155F(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void UNKCALL bn_prof_100016DD(HWND arg);
void __fastcall bn_prof_100018CE(int a1, int a2);
int __fastcall bn_prof_10001938(HDC a1, _DWORD *a2, char *a3, int a4, int a5);
int __fastcall bn_prof_10001A10(HWND a1, HWND a2);
HINSTANCE __fastcall bn_prof_10001B0A(HWND a1, const CHAR *a2);
HWND UNKCALL bn_prof_10001C0E(HWND hWnd);
void __fastcall bn_prof_10001CB9(_DWORD *a1, int a2, void (__fastcall *a3)(_BYTE *, _DWORD, int), int a4);
BOOL UNKCALL bn_prof_10001CF3(HWND hWnd);
HFONT __fastcall bn_prof_10001D81(HWND hWnd, int a2, int a3);
void UNKCALL bn_prof_10001E34(void *arg);
void __fastcall bn_prof_10001E4C(char *a1, LPARAM lParam, HWND hDlg);
void __fastcall bn_prof_10001ED0(char *a1, _BYTE *a2, int a3);
void *bn_prof_10001F29();
BYTE *bn_prof_10001F84();
//int __stdcall UiProfileDraw(int, int, int, int, HGDIOBJ ho, int, int, int, int, int, int); // idb
BOOL bn_prof_100021C4();
void *bn_prof_10002247();
int j_bn_prof_10002282();
_DWORD *bn_prof_10002282();
void __cdecl bn_prof_10002298(); // idb
int UNKCALL bn_prof_100022A2(HWND hWnd); // idb
int UNKCALL bn_prof_10002353(HGDIOBJ h); // idb
HGDIOBJ bn_prof_100023D8();
_DWORD *__fastcall bn_prof_10002410(HDC hdc, _DWORD *a2);
signed int __fastcall bn_prof_10002456(int a1, const CHAR *a2, char a3, _DWORD *a4);
signed int bn_prof_100026B9();
signed int UNKCALL bn_prof_100026C4(_DWORD *arg);
void UNKCALL bn_prof_100026F0(_DWORD *arg);
int UNKCALL bn_prof_10002749(_DWORD *arg, _DWORD *location);
_DWORD *UNKCALL bn_prof_10002782(int *arg, int a2, int a3, char a4);
_DWORD *UNKCALL bn_prof_100027CE(_DWORD *arg);
void UNKCALL bn_prof_100027D8(_DWORD *arg);
_DWORD *UNKCALL bn_prof_1000280C(int *arg, _DWORD *a2, int a3, _DWORD *a4);
void UNKCALL bn_prof_1000287D(_DWORD *arg);
void UNKCALL bn_prof_10002890(_DWORD *arg);


void UNKCALL BNetGW_100028C2(_DWORD *arg);
void UNKCALL BNetGW_100029BF(_DWORD *arg, int a2);
void *UNKCALL BNetGW_10002A07(_DWORD *arg);
_DWORD *UNKCALL BNetGW_10002A84(_DWORD *arg, signed int a2);
signed int BNetGW_10002AE5();
int UNKCALL BNetGW_10002AF0(_DWORD *arg, char *a2);
_BYTE *UNKCALL BNetGW_10002B21(_DWORD *arg, signed int a2);
void UNKCALL BNetGW_10002B51(_DWORD *arg, signed int a2);
char *UNKCALL BNetGW_10002B78(void *arg, char *a2);
char *UNKCALL BNetGW_10002C23(_DWORD *arg);
int UNKCALL BNetGW_10002C51(_DWORD *arg);
int UNKCALL BNetGW_10002DBF(_DWORD *arg);
char *__stdcall BNetGW_10002DEB(char *a1, unsigned int a2);
char *__stdcall BNetGW_10002E0B(char *a1, unsigned int a2);


void *Connect_10002E2B();
signed int Connect_10002EC4();
//BOOL __stdcall UiArtCallback(int a1, unsigned int a2, PALETTEENTRY *pPalette, void *pBuffer, DWORD dwBuffersize, DWORD *pdwWidth, DWORD *dwHeight, DWORD *pdwBpp);
signed int Connect_100033D1();
//BOOL __stdcall UiGetDataCallback(int a1, int a2, void *a3, int a4, int a5);
//int __stdcall UiSoundCallback(int a1, int a2, int a3);
//int __stdcall UiAuthCallback(int, int, char *, char, char *, LPSTR lpBuffer, int cchBufferMax); // idb
//int __stdcall UiDrawDescCallback(int, COLORREF color, LPCSTR lpString, char *, int, UINT align, time_t, int); // idb
//signed int __stdcall UiCategoryCallback(int a1, int a2, int a3, int a4, int a5, _DWORD *a6, _DWORD *a7);
int UNKCALL Connect_10003D04(char *); // idb
int __fastcall Connect_10003DAF(char *a1, int a2, int a3, int a4);
char *__fastcall Connect_10003E0C(int a1, const char *a2, char *a3, char *a4, int a5);
signed int __fastcall Connect_10003E61(const char *a1, _BYTE *a2);
int __fastcall Connect_10003F6F(int a1, int a2, size_t a3);
//int __stdcall UiCreateGameCriteria(int, char *); // idb
//signed int __stdcall UiCreatePlayerDescription(int a1, int a2, int a3);
//int __stdcall UiSetupPlayerInfo(int a1, int a2, int a3);
int __fastcall Connect_10004028(int a1, int a2, int a3, int a4);


//signed int __stdcall UiCopyProtError(int *a1);
int __stdcall CopyProt_100040AF(int, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HGLOBAL CopyProt_10004173();
signed int __fastcall CopyProt_100041B5(HWND a1, const CHAR *edx0);
int __fastcall CopyProt_1000430C(int a1, int a2);
signed int CopyProt_10004329();


signed int cr8game_10004339();
int UNKCALL cr8game_10004344(HWND arg);
//int __stdcall UiCreateGameCallback(int a1, int a2, int a3, int a4, int a5, int a6);
HGDIOBJ __stdcall cr8game_10004506(HWND hDlg, UINT Msg, WPARAM wParam, HWND hWnd);
BYTE *cr8game_10004828();
BOOL __fastcall cr8game_1000487F(HWND hWnd);
void **UNKCALL cr8game_10004914(HWND hDlg);
_DWORD *UNKCALL cr8game_1000497F(HWND arg);
_DWORD *__fastcall cr8game_10004A34(HWND hWnd, int a2, int a3);
LRESULT UNKCALL cr8game_10004A93(HWND hDlg);
_DWORD *__fastcall cr8game_10004ABA(HWND hDlg, int a2);
BOOL __fastcall cr8game_10004B02(HWND hWnd, int a2, int a3);
int UNKCALL cr8game_10004B3F(char *); // idb
HFONT UNKCALL cr8game_10004BA8(HWND hWnd);


void UNKCALL CreaDung_10004C33(void *arg);
signed int CreaDung_10004C3F();
int __stdcall CreaDung_10004C4A(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
int __fastcall CreaDung_10004D75(HWND a1, int a2);
void UNKCALL CreaDung_10004E2E(HWND hDlg);
int UNKCALL CreaDung_10004E8B(HWND hWnd); // idb
int __fastcall CreaDung_10004F40(int a1, int a2);
HWND USERCALL CreaDung_10004F5D(HWND a1, int a2);
HWND UNKCALL CreaDung_10005037(HWND arg);
HWND USERPURGE CreaDung_1000517E(HWND hWnd, int a2, int a3, int height);
int __fastcall CreaDung_100051D8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);


//signed int __stdcall UiGetDefaultStats(int a1, _WORD *a2);
signed int CreaStat_10005287();


signed int credits_10005297();
//signed int __stdcall UiCreditsDialog(int a1);
int __fastcall credits_100052C7(int a1, int a2, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HGLOBAL __fastcall credits_100053D9(HWND hWnd, int a2);
int __fastcall credits_1000543A(HWND a1, int a2);
BOOL UNKCALL credits_100055C0(HWND hWnd);
signed int UNKCALL credits_10005660(void *arg);
signed int __fastcall credits_10005736(_BYTE *a1);
int __fastcall credits_10005755(int a1, int a2);


BOOL UNKCALL DiabEdit_10005765(HWND hWnd);
signed int DiabEdit_1000579B();
ATOM DiabEdit_100057A6();
HANDLE __fastcall DiabEdit_100057E8(int a1, int a2, HWND hWnd, UINT Msg, HANDLE hData, LPARAM lParam);
LRESULT __fastcall DiabEdit_1000591C(LPARAM lParam, unsigned short a2);
LRESULT UNKCALL DiabEdit_1000594E(LPARAM lParam);
char *__fastcall DiabEdit_10005A0A(HWND a1, unsigned char a2, int a3);
int __fastcall DiabEdit_10005AF4(LPARAM lParam, int a2, int a3);
char *__fastcall DiabEdit_10005B70(HWND hWnd, char *a2);
BOOL __fastcall DiabEdit_10005B9F(HWND hWnd, int a2);
HANDLE UNKCALL DiabEdit_10005BE7(HWND hWnd);


int DiabloUI_10005C2A();
//int __stdcall UiSetBackgroundBitmap(int a1, int a2, int a3, int a4, int a5);
//int __stdcall UiSetSpawned(int a1);
//BOOL UiInitialize();
//void *UiDestroy();
//int __stdcall UiAppActivate(int a1);
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
signed int DiabloUI_10005CEA();


signed int DirLink_10005CFA();
BOOL __fastcall DirLink_10005D05(int a1, int a2, int a3, _DWORD *a4, int a5, int a6);
int __stdcall DirLink_10005D63(HWND hWnd, UINT Msg, WPARAM wParam, unsigned int lParam);
int __fastcall DirLink_10005EB2(HWND hDlg, int a2);
int UNKCALL DirLink_10005F1F(HWND hDlg); // idb
int UNKCALL DirLink_10005F7B(HWND hWnd); // idb
int __fastcall DirLink_10006047(int a1, int a2);
void UNKCALL DirLink_10006073(void *arg);
HWND UNKCALL DirLink_100060D1(HWND arg);
int UNKCALL DirLink_10006141(void *arg);
int UNKCALL DirLink_100061E1(void *arg);
int UNKCALL DirLink_100062BF(void *arg, int a2, char *a3, char *a4);
signed int __stdcall DirLink_1000632B(int a1, char *a2, char *a3);
HWND __fastcall DirLink_10006359(HWND hWnd, int a2, int height);


//signed int __stdcall UiBetaDisclaimer(int a1);
int __stdcall disclaim_100063DA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
void UNKCALL disclaim_100064C9(HWND hDlg);
int UNKCALL disclaim_100064F3(HWND hWnd); // idb
int UNKCALL disclaim_10006552(void *arg);
signed int disclaim_10006571();


signed int Doom_10006581();
int __fastcall Doom_1000658C(HWND hWnd, int *a2, int a3, int a4);
void __fastcall Doom_100065BB(HWND hWnd, HWND a2, int a3, int a4);
_DWORD *__fastcall Doom_1000663F(HWND hWnd, int a2);
BOOL __fastcall Doom_10006719(int a1, HWND a2, int flags);
_DWORD *__fastcall Doom_1000678A(HWND hWnd, HWND a2);
int __fastcall Doom_1000680A(HWND hDlg, int *a2, int a3, int a4);
void __fastcall Doom_10006839(HWND a1, HWND a2, char *a3, int a4);
int __fastcall Doom_100068AB(HWND hWnd, int *a2, int a3);
void __fastcall Doom_100068D6(HWND hWnd, HWND a2, int a3);
_DWORD *__fastcall Doom_1000695D(HWND hWnd, int a2);
int __fastcall Doom_10006A13(HWND hDlg, int *a2, int a3);
void __fastcall Doom_10006A3E(HWND a1, HWND a2, char *a3);
int __fastcall Doom_10006AB8(HWND hWnd, int *a2, int a3);
void __fastcall Doom_10006AE3(HWND hWnd, HWND a2, int a3);
void UNKCALL Doom_10006B12(HWND hWnd);
int __fastcall Doom_10006C08(HWND hDlg, int *a2, int a3);
void __fastcall Doom_10006C33(HWND a1, HWND a2, char *a3);
int __fastcall Doom_10006C53(HWND hDlg, int *a2);


int __stdcall EntDial_10006C96(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND UNKCALL EntDial_10006D78(HWND hDlg);
HWND USERCALL EntDial_10006DB8(HWND hWnd, int a2);
int __fastcall EntDial_10006EA7(HWND hDlg, int a2);
void __fastcall EntDial_10006EE8(HWND hWnd, unsigned int a2, int a3);
int __fastcall EntDial_10006F16(HWND hDlg, int, int); // idb
signed int EntDial_10006F71();


int __stdcall EntName_10006F7C(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND UNKCALL EntName_1000709E(HWND hDlg);
int UNKCALL EntName_100070DB(HWND hWnd); // idb
int __fastcall EntName_100071AC(HWND hDlg, int a2);
void __fastcall EntName_100071ED(HWND hWnd, unsigned int a2, int a3);
signed int EntName_10007220();


int __fastcall Fade_1000722B(int a1, int a2);
int __fastcall Fade_100072BE(int a1);
signed int Fade_1000739F();
signed int Fade_100073B4();
void __fastcall Fade_100073C5(HWND hWnd, int a2);
BOOL UNKCALL Fade_100073EF(HWND hWnd);
int __fastcall Fade_100073FD(int a1, int a2, int a3);
int __stdcall Fade_10007420(int a1, int a2, int a3, int a4);
signed int Fade_1000744D();


int (__stdcall *UNKCALL Focus_10007458(void *arg))(_DWORD);
int Focus_10007482();
_DWORD *__fastcall Focus_10007492(HWND hWnd, HWND a2);
BOOL UNKCALL Focus_10007566(HWND hWnd);
_DWORD *__fastcall Focus_100075B7(HWND hWnd, HWND a2);
int __fastcall Focus_100075DC(HWND hWnd, HWND a2); // idb
int Focus_100076C3();
void Focus_100076FA();
signed int Focus_1000770E();
void UNKCALL Focus_10007719(const char *arg);
int __fastcall Focus_100077E9(int a1, const char *a2, HWND hWnd);
int __stdcall Focus_10007804(HWND hWnd, int a2, int a3, int a4);
int UNKCALL Focus_10007818(void *arg);


void __cdecl local_InitUiPalette();
void __cdecl local_DelUiPalette();
tagPALETTEENTRY *__fastcall local_GetArtPalEntry(int entry);
void __fastcall local_ClearPalette(PALETTEENTRY *pPal);
void __cdecl local_ClearSurface();
BOOL __fastcall local_LoadArtImage(const char *pszFileName, BYTE **pBuffer, DWORD *pdwSize);
BOOL __fastcall local_LoadArtWithPal(HWND hWnd, int a2, char *src, int mask, int flags, const char *pszFileName, BYTE **pBuffer, DWORD *pdwSize, BOOL a9);
void __fastcall local_AdjustRectSize(tagRECT *pRect, int a2, int a3);
BOOL __fastcall local_SetStaticBmp(HWND hWnd, int nIDDlgItem, BYTE *pBuffer, DWORD *pdwSize);
void __cdecl j_local_cpp_init();
void __cdecl local_cpp_init();
BOOL __fastcall local_SetButtonBmp(HWND hWnd, int flags, int a7, void *pBuffer, DWORD *pdwSize);
void __fastcall local_FitButtonDlg(HWND hWnd, int *a2, void *pBuffer, DWORD *pdwSize);
void __fastcall local_SetWhiteText(HDC hdc);
BOOL __fastcall local_GetBottomRect(HWND hWnd1, HWND hWnd2, int width, int height);
void __fastcall local_DlgDoPaint(HWND hWnd);
void __fastcall local_DoUiWndProc(HWND hWnd, DWORD *pdwMsgTbl);
LRESULT __stdcall local_PostUiWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void __fastcall local_DoUiWndProc2(HWND hWnd, DWORD *pdwMsgTbl);
LRESULT __stdcall local_PostUiWndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL __fastcall local_DisableKeyWaitMouse(HWND hWnd);
DWORD *__cdecl local_AllocWndLongData();
void __fastcall local_FreeMemPtr(void **p);
void __fastcall local_SetWndLongStr(int WndLongData, const char *pszStr);
void __cdecl local_LoadArtCursor();
void __cdecl local_InitArtCursor();
void __cdecl local_FreeArtCursor();
void __cdecl local_SetCursorArt();
void __cdecl local_SetCursorDefault();
void __fastcall local_SetDiabloCursor(HWND hWnd);


signed int MainMenu_10008164();
//int __stdcall UiMainMenuDialog(char *, int, int, int); // idb
int __fastcall MainMenu_100081E3(int a1, int a2, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void UNKCALL MainMenu_10008354(HWND hDlg);
int __fastcall MainMenu_10008391(int a1, int a2);
void UNKCALL MainMenu_100083A8(HWND hWnd);
int __fastcall MainMenu_1000845A(int a1, int a2, int a3);
BOOL MainMenu_100084D5();
LRESULT __fastcall MainMenu_100084FA(HWND hWnd, int a2);


int Modem_1000855D();
HWND __fastcall Modem_10008563(HWND hDlg, const char *edx0, int a2);
int __stdcall Modem_100085D8(int, char *, char *); // idb
BOOL Modem_10008606();
char *Modem_1000863D();
signed int Modem_10008648();
int Modem_10008653();
int Modem_10008659();
int UNKCALL Modem_1000865F(char *); // idb
BOOL __fastcall Modem_10008680(int a1, int a2, int a3, _DWORD *a4, int a5, int a6);
int __stdcall Modem_100086DE(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
void **UNKCALL Modem_1000879E(HWND hDlg);
BOOL UNKCALL Modem_100087DB(HWND hWnd);
int Modem_10008888();
int UNKCALL Modem_100088DB(HWND hWnd); // idb
int UNKCALL Modem_1000893D(HWND hWnd); // idb
int __fastcall Modem_10008A38(HWND hWnd, int); // idb
void __cdecl Modem_10008B42(char *a1);
int UNKCALL Modem_10008BB7(HWND hWnd); // idb
int UNKCALL Modem_10008BFE(HWND hWnd); // idb


int __stdcall ModmStat_10008C62(char *, int, int, int, int); // idb
int UNKCALL ModmStat_10008C87(void *arg);
int __stdcall ModmStat_10008CA0(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
int UNKCALL ModmStat_10008DB3(HWND hDlg); // idb
BOOL UNKCALL ModmStat_10008DE4(HWND hWnd);
int __fastcall ModmStat_10008E89(int a1, int a2);
void UNKCALL ModmStat_10008EBF(HWND hDlg);
signed int ModmStat_10008F26();


int __fastcall OkCancel_10008F31(HWND hWnd, const CHAR *a2);
signed int OkCancel_10008FEC();
HGDIOBJ __stdcall OkCancel_10008FF7(HWND a1, UINT Msg, WPARAM wParam, HWND hWnd);
void **UNKCALL OkCancel_10009117(HWND hWnd);
signed int __fastcall OkCancel_10009161(HWND a1, int a2);
int __fastcall OkCancel_100092F5(int a1, int a2);
int __fastcall OkCancel_1000930A(int a1, int a2, int a3);
//LPCSTR __stdcall UiMessageBoxCallback(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);


signed int Progress_10009480();
//BOOL __stdcall UiProgressDialog(int a1, int a2, BOOL a3, int (*a4)(void), int a5);
int __stdcall Progress_100094F4(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
void *Progress_100095EC();
BOOL __fastcall Progress_10009675(HWND hWnd, const CHAR *edx0);
BOOL __fastcall Progress_10009805(HWND hWnd, int a2);
void Progress_100098B0();
void UNKCALL Progress_100098C5(HWND hWnd);
BOOL UNKCALL Progress_1000991C(HWND hWnd);


signed int Sbar_100099B5();
int UNKCALL Sbar_100099C0(HWND hWnd); // idb
int __fastcall Sbar_100099DC(HWND hWnd, LONG a2, int a3);
HWND __fastcall Sbar_10009A99(HWND hDlg, int nIDDlgItem, int a3, int a4);
HWND __fastcall Sbar_10009BF1(HWND hDlg, int nIDDlgItem);
signed int Sbar_10009CC7();
HWND __fastcall Sbar_10009CD2(HWND hDlg, int nIDDlgItem);


int __stdcall SelClass_10009D66(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND UNKCALL SelClass_10009EC0(HWND hDlg);
int UNKCALL SelClass_10009EFD(HWND hWnd); // idb
int __fastcall SelClass_10009FA2(HWND hWnd, int a2);
int __fastcall SelClass_1000A00D(int a1, LONG a2);
signed int SelClass_1000A077();


void *SelConn_1000A082();
signed int SelConn_1000A09B();
int __stdcall SelConn_1000A0A6(HWND hWnd, UINT Msg, WPARAM wParam, unsigned int lParam);
HWND __fastcall SelConn_1000A226(HWND hDlg, int nIDDlgItem);
HWND UNKCALL SelConn_1000A3E2(HWND hDlg);
int SelConn_1000A3FF();
void UNKCALL SelConn_1000A43A(HWND hDlg);
BOOL __fastcall SelConn_1000A4B9(_DWORD *a1);
BOOL UNKCALL SelConn_1000A4CD(void *location);
HWND UNKCALL SelConn_1000A4E4(HWND hWnd, char *a2, int a3);
signed int __stdcall SelConn_1000A5F3(int a1, char *a2, char *a3, int a4);
int __fastcall SelConn_1000A670(HWND a1, const char *a2);
void UNKCALL SelConn_1000A6EC(HWND hDlg);
LRESULT __stdcall SelConn_1000A73E(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND UNKCALL SelConn_1000A866(HWND hWnd);
HWND UNKCALL SelConn_1000A8D7(HWND hWnd);
HWND UNKCALL SelConn_1000A948(HWND hWnd);
int UNKCALL SelConn_1000A9F3(HWND hWnd); // idb
_DWORD *__fastcall SelConn_1000AA28(int a1);
HWND UNKCALL SelConn_1000AA3B(HWND hWnd);
HWND UNKCALL SelConn_1000AAEB(HWND hWnd);
HWND UNKCALL SelConn_1000AB83(HWND hWnd);
int __fastcall SelConn_1000AC07(int a1, int a2);
int UNKCALL SelConn_1000AC30(HWND arg);
int UNKCALL SelConn_1000AC9E(HWND hWnd); // idb
int UNKCALL SelConn_1000ADA8(HWND hWnd); // idb
BOOL UNKCALL SelConn_1000ADD0(HWND hWnd);
int __fastcall SelConn_1000AE19(int a1, UINT a2);
HWND __fastcall SelConn_1000AE59(HWND hWnd, int a2, int height);
//signed int __stdcall UiSelectProvider(int a1, int a2, int a3, int a4, char *a5, int *a6);


int UNKCALL SelDial_1000B011(char *arg);
signed int SelDial_1000B0C4();
int __stdcall SelDial_1000B0CF(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND __fastcall SelDial_1000B1FB(HWND hWnd, int a2);
HWND UNKCALL SelDial_1000B29A(HWND hDlg);
int __fastcall SelDial_1000B2D8(int a1, int a2);
HWND UNKCALL SelDial_1000B354(HWND hDlg);
HWND UNKCALL SelDial_1000B3D8(HWND hDlg);
HWND UNKCALL SelDial_1000B44C(HWND hDlg);
HWND USERCALL SelDial_1000B483(HWND hWnd, int a2);
int SelDial_1000B5D9();
int __fastcall SelDial_1000B614(HWND hWnd, int, int); // idb


void UNKCALL SelGame_1000B66A(void *arg);
int SelGame_1000B671();
void UNKCALL SelGame_1000B677(void *arg);
int SelGame_1000B67E();
//int __stdcall UiSelectGame(int, int, void *, int, int, int); // idb
signed int SelGame_1000B795();


int SelHero_1000B7A0();
int SelHero_1000B7A6();
void UNKCALL SelHero_1000B7AC(void *arg);
char *SelHero_1000B7B3();
void *SelHero_1000B7B9();
int SelHero_1000B7CA();
int __fastcall SelHero_1000B7D0(int a1, int a2);
signed int SelHero_1000B7DE();
BOOL __fastcall SelHero_1000B899(HWND hDlg, int a2);
int __fastcall SelHero_1000B905(HWND hDlg, int a2);
HWND __fastcall SelHero_1000BA7B(HWND hDlg, const char *a2);
char *UNKCALL SelHero_1000BAB4(char *arg);
char __fastcall SelHero_1000BB26(char *a1);
int __fastcall SelHero_1000BB34(char *, char *); // idb
//int UNKCALL UiValidPlayerName(char *); // idb
//int __stdcall UiSelHeroMultDialog(int, int, int, int, int, int, char *); // idb
int __stdcall SelHero_1000BC46(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
BOOL UNKCALL SelHero_1000BDAD(HWND arg);
int *__fastcall SelHero_1000BEDB(int *a1, char *a2);
BOOL UNKCALL SelHero_1000BF33(void *location);
const char *__fastcall SelHero_1000BF4A(const char *a1, const char *a2);
int UNKCALL SelHero_1000BF6D(HWND hWnd); // idb
int UNKCALL SelHero_1000BFF9(HWND hWnd); // idb
int UNKCALL SelHero_1000C09B(HWND hWnd); // idb
signed int __fastcall SelHero_1000C0F9(int a1, char *a2);
BOOL UNKCALL SelHero_1000C21A(HWND hWnd);
int UNKCALL SelHero_1000C269(HWND hWnd); // idb
void UNKCALL SelHero_1000C364(HWND hDlg);
BOOL __fastcall SelHero_1000C3CE(_DWORD *a1);
int __fastcall SelHero_1000C3E2(int a1, int a2);
int UNKCALL SelHero_1000C3FF(HWND hWnd); // idb
BOOL UNKCALL SelHero_1000C49F(HWND hWnd, void *a2);
signed int __stdcall SelHero_1000C541(void *a1);
//int __stdcall UiSelHeroSingDialog(int, int, int, int, int, char *, int); // idb


void *SelIPX_1000C610();
signed int SelIPX_1000C629();
BOOL __fastcall SelIPX_1000C634(int a1, int a2, int a3, _DWORD *a4, int a5, int a6);
int __stdcall SelIPX_1000C692(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
LONG __fastcall SelIPX_1000C818(HWND hDlg, int nIDDlgItem);
HWND UNKCALL SelIPX_1000C982(HWND hDlg);
int SelIPX_1000C99F();
const char *UNKCALL SelIPX_1000C9DA(HWND hDlg);
void __fastcall SelIPX_1000CA64(_DWORD *a1);
_DWORD **__fastcall SelIPX_1000CA71(_DWORD *a1);
BOOL UNKCALL SelIPX_1000CAC1(void *location);
void *__stdcall SelIPX_1000CAD5(int a1, char *a2, char *a3);
_DWORD *__fastcall SelIPX_1000CB50(_DWORD *a1, _DWORD *a2);
_DWORD *__fastcall SelIPX_1000CB73(_DWORD *a1, int a2);
int __fastcall SelIPX_1000CB83(HWND a1, const char *a2);
int UNKCALL SelIPX_1000CC41(HWND hDlg); // idb
BOOL __fastcall SelIPX_1000CCC5(_DWORD *a1);
HWND UNKCALL SelIPX_1000CCD9(HWND hWnd);
HWND UNKCALL SelIPX_1000CD4A(HWND hWnd);
void UNKCALL SelIPX_1000CEE6(HWND hDlg);
LRESULT __stdcall SelIPX_1000CF38(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND UNKCALL SelIPX_1000D070(HWND hWnd);
HWND UNKCALL SelIPX_1000D0E1(HWND hWnd);
int UNKCALL SelIPX_1000D18C(HWND hWnd); // idb
_DWORD *__fastcall SelIPX_1000D1C1(int a1);
HWND UNKCALL SelIPX_1000D1D4(HWND hWnd);
HWND UNKCALL SelIPX_1000D284(HWND hWnd);
HWND UNKCALL SelIPX_1000D31C(HWND hWnd);
int __fastcall SelIPX_1000D3A0(int a1, int a2);
HWND USERCALL SelIPX_1000D3C5(HWND hDlg, int a2);
BOOL __fastcall SelIPX_1000D4CA(HWND hDlg, int a2);
char *UNKCALL SelIPX_1000D520(char *arg);
const char *__fastcall SelIPX_1000D58D(const char *a1, const char *a2);
int __fastcall SelIPX_1000D5B0(int a1, int a2);
HWND __fastcall SelIPX_1000D696(HWND hDlg, int a2, int height);


signed int SelList_1000D769();
int __stdcall SelList_1000D774(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND UNKCALL SelList_1000D916(HWND hDlg);
HWND __fastcall SelList_1000D964(HWND hDlg, int nIDDlgItem);
HWND UNKCALL SelList_1000D9CF(HWND hDlg);
int UNKCALL SelList_1000D9F4(HWND hWnd); // idb
int UNKCALL SelList_1000DA2D(void *arg);
int UNKCALL SelList_1000DA48(void *arg);
int UNKCALL SelList_1000DA55(HWND hWnd); // idb
int __fastcall SelList_1000DB2C(HWND a1, const char *a2);
void UNKCALL SelList_1000DBAC(HWND hDlg);
LRESULT __stdcall SelList_1000DBFE(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND UNKCALL SelList_1000DD36(HWND hWnd);
HWND UNKCALL SelList_1000DDA7(HWND hWnd);
HWND UNKCALL SelList_1000DE18(HWND hWnd);
_DWORD *UNKCALL SelList_1000DEDD(char *arg);
HWND UNKCALL SelList_1000DEF4(HWND hWnd);
HWND UNKCALL SelList_1000DFAB(HWND hWnd);
HWND UNKCALL SelList_1000E043(HWND hWnd);
int __fastcall SelList_1000E0CA(HWND hWnd, int, int); // idb


int __stdcall SelLoad_1000E1C2(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND UNKCALL SelLoad_1000E30E(HWND hDlg);
int UNKCALL SelLoad_1000E34B(HWND hWnd); // idb
int __fastcall SelLoad_1000E3E2(int a1, LONG a2);
signed int SelLoad_1000E41A();


signed int SelModem_1000E42A();
int __fastcall SelModem_1000E435(void *a1, int a2, int a3, char *a4, char *a5);
char *__stdcall SelModem_1000E497(int a1, char *a2, char *a3);
void *SelModem_1000E4EC();
_DWORD *__fastcall SelModem_1000E500(int a1, _DWORD *a2);
signed int UNKCALL SelModem_1000E505(void *arg);
signed int SelModem_1000E51E();
BOOL __fastcall SelModem_1000E553(_DWORD *a1);
BOOL UNKCALL SelModem_1000E567(void *location);
int __fastcall SelModem_1000E57B(int a1, int a2);
signed int SelModem_1000E5CC();
int __stdcall SelModem_1000E63E(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
void UNKCALL SelModem_1000E783(HWND hDlg);
HWND UNKCALL SelModem_1000E7E9(HWND hDlg);
int UNKCALL SelModem_1000E80E(HWND hWnd); // idb
HWND UNKCALL SelModem_1000E843(HWND hWnd);
int __fastcall SelModem_1000E932(HWND a1, const char *a2);
void UNKCALL SelModem_1000E9B2(HWND hDlg);
LRESULT __stdcall SelModem_1000EA04(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND UNKCALL SelModem_1000EB2C(HWND hWnd);
HWND UNKCALL SelModem_1000EB9D(HWND hWnd);
HWND UNKCALL SelModem_1000EC0E(HWND hWnd);
_DWORD *__fastcall SelModem_1000EC9F(int a1);
HWND UNKCALL SelModem_1000ECB2(HWND hWnd);
HWND UNKCALL SelModem_1000ED3B(HWND hWnd);
HWND UNKCALL SelModem_1000EDBC(HWND hWnd);
int __fastcall SelModem_1000EE29(int a1, int a2);
HWND __fastcall SelModem_1000EE78(HWND hWnd, int a2, int height);


void *SelRegn_1000EF42();
_DWORD *__fastcall SelRegn_1000EF56(int a1, _DWORD *a2);
signed int SelRegn_1000EF60();
int __stdcall SelRegn_1000EF6B(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND __fastcall SelRegn_1000F0D7(HWND hDlg, int nIDDlgItem);
HWND UNKCALL SelRegn_1000F109(HWND hDlg);
int SelRegn_1000F126();
void UNKCALL SelRegn_1000F161(HWND hDlg);
BOOL __fastcall SelRegn_1000F1D4(_DWORD *a1);
BOOL UNKCALL SelRegn_1000F1E8(void *location);
HWND UNKCALL SelRegn_1000F1FC(HWND hWnd);
signed int SelRegn_1000F2ED();
int __fastcall SelRegn_1000F346(HWND a1, const char *a2);
void UNKCALL SelRegn_1000F3C2(HWND hDlg);
LRESULT __stdcall SelRegn_1000F414(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
HWND UNKCALL SelRegn_1000F53C(HWND hWnd);
HWND UNKCALL SelRegn_1000F5AD(HWND hWnd);
HWND UNKCALL SelRegn_1000F61E(HWND hWnd);
int UNKCALL SelRegn_1000F6C9(HWND hWnd); // idb
_DWORD *__fastcall SelRegn_1000F6FE(int a1);
HWND UNKCALL SelRegn_1000F711(HWND hWnd);
HWND UNKCALL SelRegn_1000F7C1(HWND hWnd);
HWND UNKCALL SelRegn_1000F859(HWND hWnd);
signed int UNKCALL SelRegn_1000F8DD(void *arg);
signed int SelRegn_1000F8F6();
HWND __fastcall SelRegn_1000F929(HWND hWnd, int a2, int height);
//signed int __stdcall UiSelectRegion(_DWORD *a1);


int __fastcall SelYesNo_1000FA49(int a1, const CHAR *a2, int a3, int a4);
int __stdcall SelYesNo_1000FA87(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
HWND UNKCALL SelYesNo_1000FBC7(HWND hDlg);
void UNKCALL SelYesNo_1000FC1C(HWND hWnd);
int __fastcall SelYesNo_1000FCF6(int a1, LONG a2);
int __fastcall SelYesNo_1000FD39(int a1, const CHAR *a2, int a3, int a4);
int __fastcall SelYesNo_1000FD77(int a1, UINT a2, int a3);
signed int SelYesNo_1000FDE3();


_DWORD *UNKCALL Title_1000FDEE(HWND hWnd);
int Title_1000FEED();
void **UNKCALL Title_1000FF0F(HWND hWnd);
HWND UNKCALL Title_1000FF51(HWND arg);
_DWORD *__fastcall Title_1000FFE8(HWND hWnd, const char *edx0);
int __fastcall Title_1001009E(HWND hWnd, const char *a2, HWND hWnda);
_DWORD *__stdcall Title_100100CB(HWND hWnd, int a2, int a3, int a4);
signed int Title_100100DC();
void **UNKCALL Title_100100E7(HWND hWnd);
//signed int __stdcall UiTitleDialog(int a1);
int __stdcall Title_10010126(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam); // idb
void UNKCALL Title_10010235(HWND hDlg);
int __fastcall Title_1001025A(HWND hWnd, int a2);
int UNKCALL Title_100102D7(void *arg);


void UNKCALL TitleSnd_10010306(void *arg);
void TitleSnd_1001030D();
int (__stdcall *TitleSnd_10010315())(_DWORD);
int (__stdcall *TitleSnd_1001031F())(_DWORD);
signed int TitleSnd_1001032E();
