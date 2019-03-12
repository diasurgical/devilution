#pragma once

#include <ctype.h>
#include <math.h>
// work around https://reviews.llvm.org/D51265
#ifdef __APPLE__
#include "macos_stdarg.h"
#else
#include <stdarg.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// For _rotr()
#ifdef DEVILUTION_ENGINE
#include <x86intrin.h>
#endif

// Constants
#define CONST const
#define TRUE true
#define FALSE false

#define NO_ERROR 0

#ifndef _WIN32
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long __attribute__((aligned(8)))
#endif

#include "miniwin_misc.h"
#include "miniwin_com.h"
#include "miniwin_ui.h"
#include "miniwin_thread.h"
#include "miniwin_rand.h"

#ifdef DEVILUTION_ENGINE
#include "miniwin_macro.h"
//#include "miniwin_com_macro.h"
#include "miniwin_ddraw_macro.h"
#endif

#include "miniwin_com_macro.h" // fix later
