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

//track
extern bool sgbIsScrolling; // weak
extern int track_cpp_init_value; // weak
extern int sgdwLastWalk; // weak
extern bool sgbIsWalking; // weak

void __cdecl track_cpp_init();
void __cdecl track_process();
void __fastcall track_repeat_walk(bool rep);
bool __cdecl track_isscrolling();

/* data */

extern int track_inf; // weak
