//HEADER_GOES_HERE
#ifndef __DX_H__
#define __DX_H__

extern IDirectDraw *lpDDInterface;
extern IDirectDrawPalette *lpDDPalette; // idb
extern BYTE *gpBuffer;
extern IDirectDrawSurface *lpDDSBackBuf;
extern IDirectDrawSurface *lpDDSPrimary;
extern char gbBackBuf;    // weak
extern char gbEmulate;    // weak
extern HMODULE ghDiabMod; // idb

void dx_init_mutex();
void dx_cleanup_mutex_atexit();
void __cdecl dx_cleanup_mutex(void);
void dx_init(HWND hWnd);
void dx_create_back_buffer();
void dx_create_primary_surface();
HRESULT dx_DirectDrawCreate(LPGUID guid, LPDIRECTDRAW *lplpDD, LPUNKNOWN pUnkOuter);
void j_lock_buf_priv(BYTE idx);
void lock_buf_priv();
void j_unlock_buf_priv(BYTE idx);
void unlock_buf_priv();
void dx_cleanup();
void dx_reinit();
void j_dx_reinit();

/* data */

extern int dx_inf; // weak

#endif /* __DX_H__ */
