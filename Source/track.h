//HEADER_GOES_HERE

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
