//HEADER_GOES_HERE
#ifndef __INTERFAC_H__
#define __INTERFAC_H__

extern int progress_id;

void interface_msg_pump();
BOOL IncProgress();
void DrawCutscene();
void DrawProgress(int screen_x, int screen_y, int progress_id);
void ShowProgress(unsigned int uMsg);
void FreeInterface();
void InitCutscene(unsigned int uMsg);

/* rdata */

extern const BYTE BarColor[3];
extern const int BarPos[3][2];

#endif /* __INTERFAC_H__ */
