
#define STRICT // for WNDPROC. ref: Remarks in
               // https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-callwindowproca
#include <ddraw.h>
#include <dsound.h>
#include <io.h>
#include <math.h>
#include <process.h>
#include <shlobj.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#ifdef _MSC_VER
#pragma warning(disable : 4018) // signed/unsigned mismatch
#endif

#include "shared/defs.h"
#include "shared/enums.h"
#include "shared/structs.h"
#include "storm/storm.h"
#include "../include/ui/diabloui.h"

#define UNKCALL __fastcall
#define USERCALL __fastcall
#define USERPURGE __fastcall

#include "_temp_funcs.h"

extern ProfileStruct bnprofiles[4];
extern int profilemsg1[6];
extern int profilemsg2[6];
extern int Connect_cpp_float_value;
extern int CopyProt_cpp_float_value;
extern int cr8game_cpp_float_value;
extern int CreaDung_cpp_float_value;
extern int CreaStat_cpp_float_value;
extern int credits_cpp_float_value;
extern int DiabEdit_cpp_float_value;
extern int DiabloUI_cpp_float_value;
extern int disclaim_cpp_float_value;
extern int doom_cpp_float_value;
extern int EntName_cpp_float_value;
extern int fade_cpp_float_value;
extern int focus_cpp_float_value;
extern int local_cpp_float_value;
extern int mainmenu_cpp_float_value;
extern int OkCancel_cpp_float_value;
extern int Sbar_cpp_float_value;
extern int Sbar_cpp_float_value2;
extern int SelClass_cpp_float_value;
extern int SelHero_cpp_float_value;
extern int SelList_cpp_float_value;
extern int SelLoad_cpp_float_value;
extern int SelYesNo_cpp_float_value;
extern int Title_cpp_float_value;
extern int titlesnd_cpp_float_value;
extern int dword_10022258;
extern ProfFntStruct proffnts[4];
extern unsigned char connect_subnet_ip[4][4];
extern int creadung_msgtbl1[3];
extern int creadung_msgtbl2[2];
extern int creadung_msgtbl3[2];
extern int creadung_msgtbl4[3];
extern int creadung_msgtbl5[4];
extern short defstats[3][4];
extern int dword_10022A2C[3];
extern int dword_10022A38[2];
extern int dword_10022A40[2];
extern int dword_10022A48[3];
extern int dword_10022A54[3];
extern int disclaim_msgtbl1[3];
extern int disclaim_msgtbl2[4];
extern int dword_10022AFC[2];
extern int dword_10022B04[3];
extern int dword_10022B10[2];
extern int entname_msgtbl1[2];
extern int entname_msgtbl2[3];
extern int entname_msgtbl3[2];
extern int menumsgs_1option[2];
extern int menumsgs_5options[6];
extern int dword_10022C4C[2];
extern int dword_10022C54[2];
extern int dword_10022C5C[2];
extern int dword_10022CAC[2];
extern int dword_10022CB4[2];
extern int selclass_msgtbl1[2];
extern int selclass_msgtbl2[3];
extern int selclass_msgtbl3[4];
extern int dword_10022ED8[3];
extern int dword_10022EE4[3];
extern int dword_10022EF0[4];
extern int dword_10022F00[2];
extern int dword_10022F08[4];
extern int dword_10022F18[7];
extern const char* off_10022F8C[4];
extern int dword_10022F9C[2];
extern int dword_10022FA4[3];
extern int dword_10022FB0[7];
extern int selhero_msgtbl_string[2];
extern int selhero_msgtbl_3[6];
extern int selhero_msgtbl_info[6];
extern int dword_100230F0[3];
extern int dword_100230FC[2];
extern int dword_10023104[2];
extern int dword_1002310C[3];
extern int dword_10023118[7];
extern int sellist_msgtbl1[2];
extern int sellist_msgtbl2[3];
extern int sellist_msgtbl3[2];
extern int sellist_msgtbl4[7];
extern int selload_msgtbl1[2];
extern int selload_msgtbl2[3];
extern int selload_msgtbl3[3];
extern int dword_100231CC[2];
extern int dword_100231D4[3];
extern int dword_100231E0[2];
extern int dword_100231E8[3];
extern int dword_100231F4[7];
extern int dword_10023244[3];
extern int dword_10023250[2];
extern int dword_10023258[2];
extern int dword_10023260[3];
extern int dword_1002326C[7];
extern int yesno_msgtbl2[2];
extern int yesno_msgtbl1[3];
extern int titlemsgtbl[2];

// data+bss
extern int artfont_cpp_float;
extern FontStruct font42g;
extern FontStruct* sgpCurrFont;
extern FontStruct font30g;
extern FontStruct font16s;
extern FontStruct font24s;
extern FontStruct font16g;
extern FontStruct font24g;
extern FontStruct font30s;
extern FontStruct font42y;
extern LPARAM dword_10029400;                                      // idb
extern int dword_10029404;                                         // weak
extern int dword_10029408;                                         // weak
extern int dword_1002940C;                                         // weak
extern BYTE* dword_10029410;                                       // idb
extern int dword_10029414;                                         // weak
extern int dword_10029418;                                         // weak
extern int dword_1002941C;                                         // weak
extern HGDIOBJ dword_10029420;                                     // idb
extern HGDIOBJ dword_10029424;                                     // idb
extern BYTE* dword_10029428;                                       // idb
extern void* dword_1002942C;                                       // idb
extern int(__stdcall* dword_10029430)(DWORD, DWORD, DWORD, DWORD); // weak
extern void* dword_10029434;                                       // idb
extern int dword_10029438[4];                                      // weak
extern char nullcharacter;                                         /* check */
extern HGDIOBJ dword_10029450;                                     // idb
extern int dword_10029454;                                         // weak
extern int dword_10029458;                                         // weak
extern int dword_10029460[3];                                      // idb
extern int dword_1002946C;                                         // weak
extern HGDIOBJ dword_10029470;                                     // idb
extern int dword_10029478;                                         // weak
extern int dword_10029480;                                         // weak
extern int dword_10029488;                                         // weak
extern int dword_1002948C;                                         // weak
extern int Connect_cpp_float;                                      // weak
extern int special_frames;                                         // weak
extern DWORD heroport_data[2];
extern char connect_categorystr[128];
extern char connect_plrinfostr[128];
extern int heronum_frames2; // weak
extern DWORD special_data[2];
extern int heroport_frames; // weak
extern DWORD heronum_data[2];
extern int heronum_frames;      // idb
extern int connect_draw_height; // idb
extern BYTE* connect_data1;     // idb
extern BYTE* connect_data2;     // idb
extern BYTE* connect_data3;     // idb
extern void* connect_data4;     // idb
extern HANDLE connect_trans[10];
extern char* connect_charname;
extern int connect_color_text;    // weak
extern HGLOBAL copyprot_popupart; // idb
extern HGLOBAL copyprot_artpal;   // idb
extern int CopyProt_cpp_float;    // weak
extern HGLOBAL copyprot_btnart;   // idb
extern HGDIOBJ cr8game_hobject;   // idb
extern int cr8game_cpp_float;     // weak
extern int cr8_playercount;       // weak
extern DWORD* cr8_somegamestruct;
extern int cr8_dword_10029638; // weak
extern int cr8_dword_1002963C; // weak
extern int cr8_dword_10029640; // weak
extern int* cr8game_playerID;  // idb
extern _gamedata cr8_gamedata;
extern HWND cr8_sendmsg1;      // idb
extern HWND cr8_sendmsg2;      // idb
extern int cr8_dword_10029658; // weak
extern DWORD cr8diffbtns_size[2];
extern int cr8_dword_10029668; // weak
extern int cr8_dword_1002966C; // idb
extern char cr8_gamename[32];
extern char cr8_gamepassword[32];
extern BYTE* cr8_creat_bg_ptr;
extern BYTE* cr8_but_xsm_ptr;       // idb
extern BYTE* cr8_diffbtns_ptr;      // idb
extern int creadung_playername;     // weak
extern int* creadung_playerID;      // idb
extern int CreaDung_cpp_float;      // weak
extern int creadung_dword_100296C8; // weak
extern int creadung_delspinners;    // weak
extern DWORD* crea_somegamestruct;
extern int creadung_lasterror;      // weak
extern int creadung_dword_100296D8; // weak
extern char* creadung_gamename;
extern int CreaStat_cpp_float;   // weak
extern int credittext_size;      // weak
extern int credits_cpp_float;    // weak
extern HGLOBAL credittext_rsrc;  // idb
extern int credit_vertical_pos2; // idb
extern int credit_horz_pos;      // idb
extern int credit_vertical_pos1; // weak
extern int credit_line_count;    // weak
extern void* credit_back_img;    // idb
extern HANDLE creditsobj;        // idb
extern int DiabEdit_cpp_float;   // weak
extern int DiabloUI_cpp_float;   // weak
extern int sgbUiIsInitialized;   // weak
extern HINSTANCE ghUiInst;       // idb
extern int backbmp_flag1;        // weak
extern int backbmp_flag2;        // weak
extern int backbmp_flag3;        // weak
extern int app_is_active;        // weak
extern int sgbIsSpawn;           // weak
extern int dword_10029730;       // weak
extern int dword_10029738;       // weak
extern char byte_1002973C;       // idb
extern char byte_100297BC;       // idb
extern int dword_1002983C;       // weak
extern int dword_10029840;       // weak
extern int gnDlinkPlayerid;      // weak
extern void* dword_10029848;     // idb
extern int dword_1002984C;       // weak
extern int disclaim_cpp_float;   // weak
extern int doom_cpp_float;       // weak
extern LPSTR dword_10029858;     // idb
extern int dword_1002985C;       // weak
extern int EntName_cpp_float;    // weak
extern char* entname_charname;
extern int fade_cpp_float; // weak
extern int sgbFadeRange;   // idb
extern tagPALETTEENTRY fadepal[256];
extern int sgbIsFading; // weak
extern HANDLE SpinnerTransOut[8];
extern int focus_spin_width;  // idb
extern int focus_spin_height; // weak
extern int focus_cpp_float;   // weak
extern int sgbSpinnersLoaded; // weak
extern int dword_10029CA8;    // weak
extern int dword_10029CAC;    // weak
extern int sgnSpinnerFrame;   // weak
extern int local_cpp_float;   // weak
extern DWORD gdwCursData[2];  // weak
extern tagPALETTEENTRY artpal[256];
extern HGDIOBJ objPalette; // idb
extern BYTE* gpCursorArt;
extern BYTE* gpCursorArt2;
extern int mainmenu_cpp_float; // weak
extern char menu_version_str[64];
extern int menu_item_timer;         // weak
extern int dword_1002A120;          // weak
extern int dword_1002A124;          // weak
extern int dword_1002A128;          // weak
extern int dword_1002A12C;          // weak
extern int dword_1002A130;          // weak
extern int dword_1002A134;          // weak
extern int dword_1002A138;          // weak
extern int dword_1002A13C;          // weak
extern int gnModemPlayerid;         // weak
extern int dword_1002A144;          // weak
extern int dword_1002A148;          // weak
extern void* dword_1002A14C;        // idb
extern int dword_1002A150;          // weak
extern char byte_1002A154;          // idb
extern char byte_1002A1D4;          // idb
extern int dword_1002A254;          // weak
extern int dword_1002A258;          // weak
extern int dword_1002A25C;          // weak
extern int (*dword_1002A260)(void); // weak
extern char byte_1002A264;          // idb
extern int OkCancel_cpp_float;      // weak
extern int dword_1002A2E8;          // weak
extern int dword_1002A2EC;          // weak
extern int dword_1002A2F0;          // weak
extern int (*dword_1002A2F4)(void); // weak
extern int dword_1002A2F8;          // weak
extern BOOL dword_1002A2FC;         // idb
extern int dword_1002A300;          // weak
extern int dword_1002A304;          // weak
extern DWORD dword_1002A308;        // idb
extern DWORD dword_1002A310;        // idb
extern BYTE* dword_1002A318;        // idb
extern BYTE* dword_1002A31C;        // idb
extern BYTE* dword_1002A320;        // idb
extern BYTE* dword_1002A324;        // idb
extern void* dword_1002A328;        // idb
extern int Sbar_cpp_float;          // weak
extern int Sbar_cpp_float2;         // weak
extern int SelClass_cpp_float;      // weak
extern int dword_1002A34C;          // idb
extern int dword_1002A350;          // weak
extern int dword_1002A354;          // weak
extern char* dword_1002A358;        // idb
extern int dword_1002A35C;          // weak
extern int dword_1002A360;          // idb
extern int dword_1002A364;          // weak
extern int dword_1002A368;          // weak
extern int dword_1002A36C;          // weak
extern int dword_1002A370;          // weak
extern int dword_1002A374;          // weak
extern char* dword_1002A378;        // idb
extern int dword_1002A37C;          // weak
extern char byte_1002A380[128];     // weak
extern int dword_1002A400;          // weak
extern int dword_1002A404;          // weak
extern int dword_1002A408;          // weak
extern BOOL(__stdcall* selhero_fnstats)(unsigned int, _uidefaultstats*);
extern int SelHero_cpp_float;     // weak
extern DWORD selhero_sizedata[2]; // idb
extern int selhero_difficulty;    // weak
extern int selhero_hero_hassaved; // weak
extern int selhero_numheroesleft; // weak
extern char selhero_herolevel[4];
extern BOOL(__stdcall* selhero_fnremove)(_uiheroinfo*);
extern BOOL(__stdcall* selhero_fninfo)(BOOL(__stdcall* fninfo)(_uiheroinfo*));
extern char selhero_heromag[4];
extern char selhero_heronamestr[16];
extern BOOL(__stdcall* selhero_fncreate)(_uiheroinfo*);
extern char selhero_herodex[4];
extern _uiheroinfo* sgpHeroInfo;
extern int selhero_is_created; // weak
extern _uiheroinfo heroinfo_create;
extern int selhero_is_good; // idb
extern char selhero_herostr[4];
extern char selhero_herovit[4];
extern BYTE* selhero_buffer;
extern int dword_1002A49C;    // weak
extern void* dword_1002A4A0;  // idb
extern int dword_1002A4A4;    // weak
extern int gnIpxPlayerid;     // weak
extern int dword_1002A4AC;    // weak
extern int dword_1002A4B0;    // weak
extern int dword_1002A4B4;    // weak
extern int dword_1002A4B8;    // idb
extern int dword_1002A4BC;    // weak
extern int SelList_cpp_float; // weak
extern _uiheroinfo* sellist_pheroinfo;
extern int SelLoad_cpp_float;       // weak
extern int dword_1002A4CC;          // weak
extern int dword_1002A4D0;          // weak
extern void* dword_1002A4D4;        // idb
extern int dword_1002A4D8;          // idb
extern int dword_1002A4DC;          // weak
extern int dword_1002A4E0;          // weak
extern int dword_1002A4E4;          // weak
extern int dword_1002A4E8;          // weak
extern _uiheroinfo* dword_1002A4EC; // idb
extern int dword_1002A4F0;          // weak
extern int dword_1002A4F4;          // idb
extern char* yesno_dialog_string;
extern int SelYesNo_cpp_float; // weak
extern int yesno_remove_focus; // weak
extern char* yesno_hero_name;
extern int (*YesNoFunc)(void); // weak
extern int yesno_is_popup;     // weak
extern HANDLE titlePHTrans[30];
extern int Title_cpp_float;    // weak
extern int titleTransIdx;      // weak
extern int titlesnd_cpp_float; // weak
extern void(__stdcall* gfnSoundFunction)(const char* file);
