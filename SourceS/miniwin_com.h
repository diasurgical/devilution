#pragma once

namespace dvl {

//
// COM
//
#define DECLARE_INTERFACE_(name, base) struct name : public base
#define THIS_
#define THIS
#define PURE = 0

#define CS_HREDRAW 0x0001
#define CS_VREDRAW 0x0002

#define IDC_ARROW (LPCSTR)0x1 // Dummy value

#define CSIDL_STARTMENU 0x000b

#define SW_HIDE 0
#define SW_SHOWNORMAL 1

#define BLACK_BRUSH 4

#define LR_DEFAULTCOLOR 0x0000

#define IMAGE_ICON 1

#define SM_CXSCREEN 0
#define SM_CYSCREEN 1

#define GW_HWNDNEXT 2

#define STDMETHOD(name) STDMETHOD_(HRESULT, name)
#define STDMETHOD_(type, name) virtual WINAPI type name

typedef void *REFIID;

struct IUnknown {
	// clang-format off
	STDMETHOD(QueryInterface)(THIS_ REFIID, LPVOID *) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;
	// clang-format on
};

#define MAKE_HRESULT(sev, fac, code) ((HRESULT)(((uint32_t)(sev) << 31) | ((uint32_t)(fac) << 16) | ((uint32_t)(code))))
#define E_FAIL ((HRESULT)0x80004005L)
#define S_OK ((HRESULT)0)

}
