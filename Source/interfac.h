//HEADER_GOES_HERE
#ifndef __INTERFAC_H__
#define __INTERFAC_H__

extern void *sgpBackCel;
extern int sgdwProgress;
extern int progress_id; // idb

void __cdecl interfac_cpp_init();
void __cdecl interface_msg_pump();
BOOL __cdecl IncProgress();
void __cdecl DrawCutscene();
void __fastcall DrawProgress(int screen_x, int screen_y, int progress_id);
void __fastcall ShowProgress(unsigned int uMsg);
void __cdecl FreeInterface();
void __fastcall InitCutscene(unsigned int uMsg);

/* rdata */

extern const int interfac_inf; // weak
extern const unsigned char progress_bar_colours[3];
extern const int progress_bar_screen_pos[3][2];

#endif /* __INTERFAC_H__ */
