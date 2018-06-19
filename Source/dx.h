//HEADER_GOES_HERE

//dx
extern void *sgpBackBuf;
extern int dx_cpp_init_value; // weak
extern IDirectDraw *lpDDInterface;
extern IDirectDrawPalette *lpDDPalette; // idb
extern int sgdwLockCount;
extern Screen *gpBuffer;
extern IDirectDrawSurface *lpDDSBackBuf;
extern IDirectDrawSurface *lpDDSPrimary;
extern char gbBackBuf; // weak
extern char gbEmulate; // weak
extern HMODULE ghDiabMod; // idb

void __cdecl dx_cpp_init_1();
void __cdecl dx_cpp_init_2();
void __cdecl dx_init_mutex();
void __cdecl dx_cleanup_mutex_atexit();
void __cdecl dx_cleanup_mutex();
void __fastcall dx_init(HWND hWnd);
void __cdecl dx_create_back_buffer();
void __cdecl dx_create_primary_surface();
HRESULT __fastcall dx_DirectDrawCreate(GUID *guid, IDirectDraw **DD, void *unknown);
void __cdecl j_dx_lock_mutex();
void __cdecl dx_lock_mutex();
void __cdecl j_dx_unlock_mutex();
void __cdecl dx_unlock_mutex();
void __cdecl dx_cleanup();
void __cdecl dx_reinit();
void __cdecl j_dx_reinit();

/* data */

extern int dx_inf; // weak
