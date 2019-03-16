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
#undef DECLARE_INTERFACE_
#undef STDMETHOD
#undef STDMETHOD_
#undef THIS_
#undef THIS
#undef PURE
#undef REFIID
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
	STDMETHOD_(ULONG, Release)(THIS) PURE;
	// clang-format on
};

template<class T, class U, class V> constexpr HRESULT DVL_MAKE_HRESULT(T&& sev, U&& fac, V&& code)
{
        return (((uint32_t)(sev) << 31) | ((uint32_t)(fac) << 16) | ((uint32_t)(code)));
}


#include "miniwin/com/ddraw.inc"
#include "miniwin/com/dsound.inc"

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

constexpr HRESULT DVL_E_FAIL = 0x80004005L;
constexpr HRESULT DVL_S_OK = 0;

constexpr auto DVL_SW_HIDE = 0;
constexpr auto DVL_SW_SHOWNORMAL = 1;
constexpr auto DVL_SM_CXSCREEN = 0;
constexpr auto DVL_SM_CYSCREEN = 1;

}  // namespace dvl
