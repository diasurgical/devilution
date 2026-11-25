/**
 * @file dx.cpp
 *
 * Implementation of functions setting up the graphics pipeline.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

BYTE *sgpBackBuf;
LPDIRECTDRAW lpDD;
IDirectDrawPalette *lpDDPal;
int sgdwLockCount;
BYTE *gpBuffer;
IDirectDrawSurface *lpDDSBackBuf;
IDirectDrawSurface *lpDDSPrimary;
#ifdef _DEBUG
int locktbl[256];
#endif
static CCritSect sgDrawCrit;
char gbForceBackBuf = 0;
char gbUseDDEmulation = 0;
HMODULE sghDDlib = 0;

static void dx_create_back_buffer()
{
	DDSCAPS caps;
	HRESULT error_code;
	DDSURFACEDESC ddsd;

	error_code = lpDDSPrimary->GetCaps(&caps);
	if (error_code != DD_OK)
		DDErrMsg(error_code, 59, "C:\\Src\\Diablo\\Source\\dx.cpp");

	if (!gbForceBackBuf) {
		ddsd.dwSize = sizeof(ddsd);
		error_code = lpDDSPrimary->Lock(NULL, &ddsd, DDLOCK_WRITEONLY | DDLOCK_WAIT, NULL);
		if (error_code == DD_OK) {
			lpDDSPrimary->Unlock(NULL);
			sgpBackBuf = (BYTE *)DiabloAllocPtr(BUFFER_HEIGHT * BUFFER_WIDTH);
			return;
		}
		if (error_code != DDERR_CANTLOCKSURFACE)
			ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 81);
	}

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_PIXELFORMAT | DDSD_PITCH | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight = BUFFER_HEIGHT;
	ddsd.dwWidth = BUFFER_WIDTH;
	ddsd.lPitch = BUFFER_WIDTH;
	ddsd.ddpfPixelFormat.dwSize = sizeof(ddsd.ddpfPixelFormat);
	error_code = lpDDSPrimary->GetPixelFormat(&ddsd.ddpfPixelFormat);
	if (error_code != DD_OK)
		ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 94);
	error_code = lpDD->CreateSurface(&ddsd, &lpDDSBackBuf, NULL);
	if (error_code != DD_OK)
		ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 96);
}

static void dx_create_primary_surface()
{
	DDSURFACEDESC ddsd;
	HRESULT error_code;

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	error_code = lpDD->CreateSurface(&ddsd, &lpDDSPrimary, NULL);
	if (error_code != DD_OK)
		ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 109);
}

static HRESULT dx_DirectDrawCreate(LPGUID guid, LPDIRECTDRAW *lplpDD, LPUNKNOWN pUnkOuter)
{
	HRESULT(WINAPI * DirectDrawCreate)
	(LPGUID lpGuid, LPDIRECTDRAW * lplpDD, LPUNKNOWN pUnkOuter);

	if (sghDDlib == NULL) {
		sghDDlib = LoadLibrary("ddraw.dll");
	}
	if (sghDDlib == NULL) {
		ErrDlg(IDD_DIALOG4, GetLastError(), "C:\\Src\\Diablo\\Source\\dx.cpp", 122);
	}

	DirectDrawCreate = (HRESULT(WINAPI *)(LPGUID, LPDIRECTDRAW *, LPUNKNOWN))GetProcAddress(sghDDlib, "DirectDrawCreate");
	if (DirectDrawCreate == NULL) {
		ErrDlg(IDD_DIALOG4, GetLastError(), "C:\\Src\\Diablo\\Source\\dx.cpp", 127);
	}
	return DirectDrawCreate(guid, lplpDD, pUnkOuter);
}

void dx_init(HWND hWnd)
{
	HRESULT hDDVal;
	int winw, winh;
	BOOL bSuccess;
	GUID *lpGUID;

	assert(!gpBuffer);
	assert(!sgdwLockCount);
	assert(!sgpBackBuf);

	SetFocus(hWnd);
	ShowWindow(hWnd, SW_SHOWNORMAL);

	lpGUID = NULL;
	if (gbUseDDEmulation) {
		lpGUID = (GUID *)DDCREATE_EMULATIONONLY;
	}
	hDDVal = dx_DirectDrawCreate(lpGUID, &lpDD, NULL);
	if (hDDVal != DD_OK) {
		ErrDlg(IDD_DIALOG1, hDDVal, "C:\\Src\\Diablo\\Source\\dx.cpp", 149);
	}

#ifdef COLORFIX
#ifdef __DDRAWI_INCLUDED__
	((LPDDRAWI_DIRECTDRAW_INT)lpDD)->lpLcl->dwAppHackFlags |= 0x800;
#else
	((DWORD **)lpDD)[1][18] |= 0x800;
#endif
#endif

#ifndef _DEBUG
	fullscreen = TRUE;
#endif
	if (!fullscreen) {
		hDDVal = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL | DDSCL_ALLOWREBOOT);
		if (hDDVal == DDERR_EXCLUSIVEMODEALREADYSET) {
			TriggerBreak();
		} else if (hDDVal != DD_OK) {
			ErrDlg(IDD_DIALOG1, hDDVal, "C:\\Diablo\\Direct\\dx.cpp", 155);
		}
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
	} else {
		hDDVal = lpDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT | DDSCL_FULLSCREEN);
		if (hDDVal == DDERR_EXCLUSIVEMODEALREADYSET) {
			TriggerBreak();
		} else if (hDDVal != DD_OK) {
			ErrDlg(IDD_DIALOG1, hDDVal, "C:\\Src\\Diablo\\Source\\dx.cpp", 170);
		}
		hDDVal = lpDD->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
		if (hDDVal != DD_OK) {
			winw = GetSystemMetrics(SM_CXSCREEN);
			winh = GetSystemMetrics(SM_CYSCREEN);
			hDDVal = lpDD->SetDisplayMode(winw, winh, SCREEN_BPP);
		}
		if (hDDVal != DD_OK) {
			ErrDlg(IDD_DIALOG1, hDDVal, "C:\\Src\\Diablo\\Source\\dx.cpp", 183);
		}
	}

	dx_create_primary_surface();
	palette_init();
	GdiSetBatchLimit(1);
	dx_create_back_buffer();
	bSuccess = SDrawManualInitialize(hWnd, lpDD, lpDDSPrimary, NULL, NULL, lpDDSBackBuf, lpDDPal, NULL);
	assert(bSuccess);
}

static void lock_buf_priv()
{
	DDSURFACEDESC ddsd;
	HRESULT error_code;

	sgDrawCrit.Enter();
	if (sgpBackBuf != NULL) {
		gpBuffer = sgpBackBuf;
		sgdwLockCount++;
		return;
	}

	if (lpDDSBackBuf == NULL) {
		Sleep(20000);
		app_fatal("lock_buf_priv");
		sgdwLockCount++;
		return;
	}

	if (sgdwLockCount != 0) {
		sgdwLockCount++;
		return;
	}
	ddsd.dwSize = sizeof(ddsd);
	error_code = lpDDSBackBuf->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	if (error_code != DD_OK)
		DDErrMsg(error_code, 235, "C:\\Src\\Diablo\\Source\\dx.cpp");

	gpBuffer = (BYTE *)ddsd.lpSurface;
	glClipY += (size_t)ddsd.lpSurface;
	sgdwLockCount++;
}

void lock_buf(BYTE idx)
{
#ifdef _DEBUG
	++locktbl[idx];
#endif
	lock_buf_priv();
}

static void unlock_buf_priv()
{
	HRESULT error_code;

	if (sgdwLockCount == 0)
		app_fatal("draw main unlock error");
	if (gpBuffer == NULL)
		app_fatal("draw consistency error");

	sgdwLockCount--;
	if (sgdwLockCount == 0) {
		glClipY -= (size_t)gpBuffer;
		gpBuffer = NULL;
		if (sgpBackBuf == NULL) {
			error_code = lpDDSBackBuf->Unlock(NULL);
			if (error_code != DD_OK)
				DDErrMsg(error_code, 273, "C:\\Src\\Diablo\\Source\\dx.cpp");
		}
	}
	sgDrawCrit.Leave();
}

void unlock_buf(BYTE idx)
{
#ifdef _DEBUG
	if (!locktbl[idx])
		app_fatal("Draw lock underflow: 0x%x", idx);
	--locktbl[idx];
#endif
	unlock_buf_priv();
}

void dx_cleanup()
{
	if (ghMainWnd)
		ShowWindow(ghMainWnd, SW_HIDE);
	SDrawDestroy();
	sgDrawCrit.Enter();
	if (sgpBackBuf != NULL) {
		MemFreeDbg(sgpBackBuf);
	} else if (lpDDSBackBuf != NULL) {
		lpDDSBackBuf->Release();
		lpDDSBackBuf = NULL;
	}
	sgdwLockCount = 0;
	gpBuffer = NULL;
	sgDrawCrit.Leave();
	if (lpDDSPrimary) {
		lpDDSPrimary->Release();
		lpDDSPrimary = NULL;
	}
	if (lpDDPal) {
		lpDDPal->Release();
		lpDDPal = NULL;
	}
	if (lpDD) {
		lpDD->Release();
		lpDD = NULL;
	}
}

void dx_reinit()
{
	int lockCount;

	sgDrawCrit.Enter();
	ClearCursor();
	lockCount = sgdwLockCount;

	while (sgdwLockCount != 0)
		unlock_buf_priv();

	dx_cleanup();

	force_redraw = 255;

	dx_init(ghMainWnd);

	while (lockCount-- != 0) {
		lock_buf_priv();
	}

	sgDrawCrit.Leave();
}

/* check extern remove stub */
void j_dx_reinit()
{
	dx_reinit();
}
