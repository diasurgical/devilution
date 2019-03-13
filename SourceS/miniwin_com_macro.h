#pragma once

#define CS_HREDRAW 0x0001
#define CS_VREDRAW 0x0002

#define IDC_ARROW (LPCSTR)0x1 // Dummy value

#define CSIDL_STARTMENU 0x000b

#define SW_HIDE DVL_SW_HIDE
#define SW_SHOWNORMAL DVL_SW_SHOWNORMAL

#define BLACK_BRUSH 4

#define LR_DEFAULTCOLOR 0x0000

#define IMAGE_ICON 1

#define SM_CXSCREEN DVL_SM_CXSCREEN
#define SM_CYSCREEN DVL_SM_CYSCREEN

#define GW_HWNDNEXT 2

#define E_FAIL DVL_E_FAIL
#define S_OK DVL_S_OK

#define MAKE_HRESULT(sev, fac, code) ((HRESULT)(((uint32_t)(sev) << 31) | ((uint32_t)(fac) << 16) | ((uint32_t)(code))))

#include "miniwin_com_macro_ddraw.h"
#include "miniwin_com_macro_dsound.h"
