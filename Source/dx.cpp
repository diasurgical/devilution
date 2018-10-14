//HEADER_GOES_HERE

#include "../types.h"

Screen *sgpBackBuf;
int dx_cpp_init_value; // weak
LPDIRECTDRAW lpDDInterface;
IDirectDrawPalette *lpDDPalette; // idb
int sgdwLockCount;
Screen *gpBuffer;
IDirectDrawSurface *lpDDSBackBuf;
IDirectDrawSurface *lpDDSPrimary;
#ifdef _DEBUG
int locktbl[256];
#endif
static CRITICAL_SECTION sgMemCrit;
char gbBackBuf; // weak
char gbEmulate; // weak
HMODULE ghDiabMod; // idb

int dx_inf = 0x7F800000; // weak

struct dx_cpp_init_1
{
	dx_cpp_init_1()
	{
		dx_cpp_init_value = dx_inf;
	}
} _dx_cpp_init_1;
// 47A464: using guessed type int dx_inf;
// 52A514: using guessed type int dx_cpp_init_value;

struct dx_cpp_init_2
{
	dx_cpp_init_2()
	{
		dx_init_mutex();
		dx_cleanup_mutex_atexit();
	}
} _dx_cpp_init_2;

void __cdecl dx_init_mutex()
{
	InitializeCriticalSection(&sgMemCrit);
}

void __cdecl dx_cleanup_mutex_atexit()
{
	atexit(dx_cleanup_mutex);
}

void __cdecl dx_cleanup_mutex()
{
	DeleteCriticalSection(&sgMemCrit);
}

void __fastcall dx_init(HWND hWnd)
{
	HWND v1; // esi
	GUID *v2; // ecx
	int v3; // eax
	int v4; // eax
	//int v5; // ecx
	int v6; // edi
	int v7; // eax
	int v8; // eax
	HWND hWnda; // [esp+1Ch] [ebp-4h]

	v1 = hWnd;
	hWnda = hWnd;
	SetFocus(hWnd);
	ShowWindow(v1, SW_SHOWNORMAL);
	v2 = NULL;
	if ( gbEmulate )
		v2 = (GUID *)DDCREATE_EMULATIONONLY;
	v3 = dx_DirectDrawCreate(v2, &lpDDInterface, NULL);
	if ( v3 )
		ErrDlg(IDD_DIALOG1, v3, "C:\\Src\\Diablo\\Source\\dx.cpp", 149);
	fullscreen = 1;
	v4 = lpDDInterface->SetCooperativeLevel(v1, DDSCL_EXCLUSIVE|DDSCL_ALLOWREBOOT|DDSCL_FULLSCREEN);
	if ( v4 == DDERR_EXCLUSIVEMODEALREADYSET )
	{
		MI_Dummy(0); // v5
	}
	else if ( v4 )
	{
		ErrDlg(IDD_DIALOG1, v4, "C:\\Src\\Diablo\\Source\\dx.cpp", 170);
	}
	if ( lpDDInterface->SetDisplayMode(640, 480, 8) )
	{
		v6 = GetSystemMetrics(SM_CXSCREEN);
		v7 = GetSystemMetrics(SM_CYSCREEN);
		v8 = lpDDInterface->SetDisplayMode(v6, v7, 8);
		if ( v8 )
			ErrDlg(IDD_DIALOG1, v8, "C:\\Src\\Diablo\\Source\\dx.cpp", 183);
	}
	dx_create_primary_surface();
	palette_init();
	GdiSetBatchLimit(1);
	dx_create_back_buffer();
	SDrawManualInitialize(hWnda, lpDDInterface, lpDDSPrimary, 0, 0, lpDDSBackBuf, lpDDPalette, 0);
}
// 52A549: using guessed type char gbEmulate;

void __cdecl dx_create_back_buffer()
{
	DDSCAPS caps;
	HRESULT error_code = lpDDSPrimary->GetCaps(&caps);
	if ( error_code != DD_OK )
		DDErrMsg(error_code, 59, "C:\\Src\\Diablo\\Source\\dx.cpp");

	DDSURFACEDESC ddsd;
	if ( gbBackBuf == NULL ) {
		ddsd.dwSize = sizeof(ddsd);
		error_code = lpDDSPrimary->Lock(NULL, &ddsd, DDLOCK_WRITEONLY|DDLOCK_WAIT, NULL);
		if ( error_code == DD_OK ) {
			lpDDSPrimary->Unlock(NULL);
			sgpBackBuf = (Screen *)DiabloAllocPtr(sizeof(Screen));
			return;
		}
		if ( error_code != DDERR_CANTLOCKSURFACE )
			ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 81);
	}

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwWidth = 768;
	ddsd.lPitch = 768;
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_PIXELFORMAT|DDSD_PITCH|DDSD_WIDTH|DDSD_HEIGHT|DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY|DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwHeight = 656;
	ddsd.ddpfPixelFormat.dwSize = sizeof(ddsd.ddpfPixelFormat);
	error_code = lpDDSPrimary->GetPixelFormat(&ddsd.ddpfPixelFormat);
	if ( error_code != DD_OK )
		ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 94);
	error_code = lpDDInterface->CreateSurface(&ddsd, &lpDDSBackBuf, NULL);
	if ( error_code != DD_OK )
		ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 96);
}
// 52A548: using guessed type char gbBackBuf;

void __cdecl dx_create_primary_surface()
{
	DDSURFACEDESC ddsd;
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	HRESULT error_code = lpDDInterface->CreateSurface(&ddsd, &lpDDSPrimary, NULL);
	if ( error_code != DD_OK )
		ErrDlg(IDD_DIALOG1, error_code, "C:\\Src\\Diablo\\Source\\dx.cpp", 109);
}

HRESULT __fastcall dx_DirectDrawCreate(LPGUID guid, LPDIRECTDRAW *lplpDD, LPUNKNOWN pUnkOuter)
{
	if (ghDiabMod == NULL) {
		ghDiabMod = LoadLibrary("ddraw.dll");
		if (ghDiabMod == NULL) {
			ErrDlg(IDD_DIALOG4, GetLastError(), "C:\\Src\\Diablo\\Source\\dx.cpp", 122);
		}
	}

	HRESULT(WINAPI * DirectDrawCreate)
	(LPGUID lpGuid, LPDIRECTDRAW * lplpDD, LPUNKNOWN pUnkOuter);
	DirectDrawCreate = (HRESULT(WINAPI *)(LPGUID, LPDIRECTDRAW *, LPUNKNOWN))GetProcAddress(ghDiabMod, "DirectDrawCreate");
	if (DirectDrawCreate == NULL) {
		ErrDlg(IDD_DIALOG4, GetLastError(), "C:\\Src\\Diablo\\Source\\dx.cpp", 127);
	}
	return DirectDrawCreate(guid, lplpDD, pUnkOuter);
}

void __fastcall j_lock_buf_priv(BYTE idx) {
#ifdef _DEBUG
	++locktbl[idx];
#endif
	lock_buf_priv();
}

void __cdecl lock_buf_priv()
{
	EnterCriticalSection(&sgMemCrit);
	if ( sgpBackBuf != NULL ) {
		gpBuffer = sgpBackBuf;
		sgdwLockCount++;
		return;
	}

	if ( lpDDSBackBuf == NULL ) {
		Sleep(20000);
		TermMsg("lock_buf_priv");
		sgdwLockCount++;
		return;
	}

	if ( sgdwLockCount != 0 ) {
		sgdwLockCount++;
		return;
	}
	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof(ddsd);
	HRESULT error_code = lpDDSBackBuf->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	if ( error_code != DD_OK )
		DDErrMsg(error_code, 235, "C:\\Src\\Diablo\\Source\\dx.cpp");

	gpBufEnd += (int)ddsd.lpSurface;
	gpBuffer = (Screen *)ddsd.lpSurface;
	sgdwLockCount++;
}

void __fastcall j_unlock_buf_priv(BYTE idx) {
#ifdef _DEBUG
	if ( !locktbl[idx] )
		TermMsg("Draw lock underflow: 0x%x", idx);
	--locktbl[idx];
#endif
	unlock_buf_priv();
}

void __cdecl unlock_buf_priv()
{
	if ( sgdwLockCount == 0 )
		TermMsg("draw main unlock error");
	if ( !gpBuffer )
		TermMsg("draw consistency error");

	sgdwLockCount--;
	if ( sgdwLockCount == 0 ) {
		gpBufEnd -= (int)gpBuffer;
		gpBuffer = NULL;
		if ( sgpBackBuf == NULL ) {
			HRESULT error_code = lpDDSBackBuf->Unlock(NULL);
			if ( error_code != DD_OK )
				DDErrMsg(error_code, 273, "C:\\Src\\Diablo\\Source\\dx.cpp");
		}
	}
	LeaveCriticalSection(&sgMemCrit);
}

void __cdecl dx_cleanup()
{
	Screen *v0; // ecx

	if ( ghMainWnd )
		ShowWindow(ghMainWnd, SW_HIDE);
	SDrawDestroy();
	EnterCriticalSection(&sgMemCrit);
	if ( sgpBackBuf != NULL ) {
		v0 = sgpBackBuf;
		sgpBackBuf = 0;
		mem_free_dbg(v0);
	}
	else if ( lpDDSBackBuf != NULL )
	{
		lpDDSBackBuf->Release();
		lpDDSBackBuf = NULL;
	}
	sgdwLockCount = 0;
	gpBuffer = 0;
	LeaveCriticalSection(&sgMemCrit);
	if ( lpDDSPrimary )
	{
		lpDDSPrimary->Release();
		lpDDSPrimary = 0;
	}
	if ( lpDDPalette )
	{
		lpDDPalette->Release();
		lpDDPalette = 0;
	}
	if ( lpDDInterface )
	{
		lpDDInterface->Release();
		lpDDInterface = 0;
	}
}

void __cdecl dx_reinit()
{
	EnterCriticalSection(&sgMemCrit);
	ClearCursor();
	int lockCount = sgdwLockCount;

	while ( sgdwLockCount != 0 )
		unlock_buf_priv();

	dx_cleanup();

	drawpanflag = 255;

	dx_init(ghMainWnd);

	while (lockCount != 0) {
		lock_buf_priv();
		lockCount--;
	}

	LeaveCriticalSection(&sgMemCrit);
}
