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

//interfac
extern void *sgpBackCel;
extern float interfac_cpp_init_value;
extern int sgdwProgress;
extern int progress_id; // idb

void __cdecl interfac_cpp_init();
void __cdecl interface_msg_pump();
bool __cdecl IncProgress();
void __cdecl DrawCutscene();
void __fastcall DrawProgress(int screen_x, int screen_y, int progress_id);
void __fastcall ShowProgress(int uMsg);
void __cdecl FreeInterface();
void __fastcall InitCutscene(int interface_mode);

/* data */

extern int interfac_inf; // weak
extern unsigned char progress_bar_colours[3];
extern POINT32 progress_bar_screen_pos[3];
