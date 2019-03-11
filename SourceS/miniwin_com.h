#pragma once

namespace dvl {

#define DEVILUTION_MINIWIN_COM

#ifndef DEVILUTION_ENGINE
#pragma push_macro("DECLARE_INTERFACE_")
#pragma push_macro("STDMETHOD")
#pragma push_macro("STDMETHOD_")
#pragma push_macro("THIS_")
#pragma push_macro("THIS")
#pragma push_macro("PURE")
#pragma push_macro("REFIID")
#endif

//
// COM
//
#define DECLARE_INTERFACE_(name, base) struct name : public base
#define THIS_
#define THIS
#define PURE = 0

#define STDMETHOD(name) STDMETHOD_(HRESULT, name)
#define STDMETHOD_(type, name) virtual WINAPI type name

typedef void *DVL_REFIID;
#define REFIID DVL_REFIID

struct IUnknown {
	// clang-format off
	STDMETHOD(QueryInterface)(THIS_ REFIID, LPVOID *) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;
	// clang-format on
};

#include "miniwin_ddraw.h"
#include "miniwin_dsound.h"

#ifndef DEVILUTION_ENGINE
#pragma pop_macro("DECLARE_INTERFACE_")
#pragma pop_macro("STDMETHOD")
#pragma pop_macro("STDMETHOD_")
#pragma pop_macro("THIS_")
#pragma pop_macro("THIS")
#pragma pop_macro("PURE")
#pragma pop_macro("REFIID")
#endif

#undef DEVILUTION_MINIWIN_COM

static constexpr HRESULT DVL_E_FAIL = 0x80004005L;
static constexpr HRESULT DVL_S_OK = 0;

}
