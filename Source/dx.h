/**
 * @file dx.h
 *
 * Interface of functions setting up the graphics pipeline.
 */
#ifndef __DX_H__
#define __DX_H__

extern IDirectDraw *lpDDInterface;
extern IDirectDrawPalette *lpDDPalette;
extern BYTE *gpBuffer;
extern IDirectDrawSurface *lpDDSBackBuf;
extern IDirectDrawSurface *lpDDSPrimary;
extern char gbBackBuf;
extern char gbEmulate;

void dx_init(HWND hWnd);
void lock_buf(BYTE idx);
void unlock_buf(BYTE idx);
void dx_cleanup();
void dx_reinit();
void j_dx_reinit();

#endif /* __DX_H__ */
