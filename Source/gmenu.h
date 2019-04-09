//HEADER_GOES_HERE
#ifndef __GMENU_H__
#define __GMENU_H__

extern void *optbar_cel;
extern BOOLEAN byte_634464; // weak
extern void *PentSpin_cel;
extern void *BigTGold_cel;
extern int dword_634474; // weak
extern char byte_634478; // weak
extern void(*dword_63447C)(TMenuItem *);
extern TMenuItem *dword_634480; // idb
extern void *option_cel;
extern int dword_63448C; // weak

void gmenu_draw_pause();
void gmenu_print_text(int x, int y, char *pszStr);
void FreeGMenu();
void gmenu_init_menu();
BOOL gmenu_exception();
void gmenu_call_proc(TMenuItem *pItem, void(*gmFunc)(TMenuItem *));
void gmenu_up_down(int a1);
void gmenu_draw();
void gmenu_draw_menu_item(TMenuItem *pItem, int a2);
void gmenu_clear_buffer(int x, int y, int width, int height);
int gmenu_get_lfont(TMenuItem *pItem);
BOOL gmenu_presskeys(int a1);
void gmenu_left_right(int a1);
BOOL gmenu_on_mouse_move();
BOOLEAN gmenu_valid_mouse_pos(int *plOffset);
int gmenu_left_mouse(int a1);
void gmenu_enable(TMenuItem *pMenuItem, BOOL enable);
void gmenu_slider_1(TMenuItem *pItem, int min, int max, int gamma);
int gmenu_slider_get(TMenuItem *pItem, int min, int max);
void gmenu_slider_3(TMenuItem *pItem, int dwTicks);

/* rdata */

extern const unsigned char lfontframe[127];
extern const unsigned char lfontkern[56];

#endif /* __GMENU_H__ */
