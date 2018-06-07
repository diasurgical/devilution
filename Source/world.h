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

void __fastcall drawTopArchesUpperScreen(void *a1);
void __fastcall drawBottomArchesUpperScreen(void *a1, int a2);
void __fastcall drawUpperScreen(void *a1);
void __fastcall drawTopArchesLowerScreen(void *a1);
void __fastcall drawBottomArchesLowerScreen(void *a1, int a2);
void __fastcall drawLowerScreen(void *a1);
void __fastcall world_draw_black_tile(char *dst_buf);

/* rdata */

extern int world_4B325C;
extern unsigned char world_4B3260[5];
extern int world_4B3265;
extern int world_4B3269[5];
extern int tile_draw_masks[3][32];
extern int world_4B33FD[48];
extern int world_4B34BD[17];
extern int world_4B3501[17];
