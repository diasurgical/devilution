#pragma once

#include <ctype.h>
#include <fcntl.h>
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
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
// For _rotr()
#include <x86intrin.h>

// Constants
#define CONST const
#define TRUE true
#define FALSE false

#define NO_ERROR 0

// Remove calling conventions (original calling conventions confuse address-sanitizer and aren't supported by all compilers)
#define __cdecl
#define __fastcall
#define __stdcall
#define CALLBACK
#define APIENTRY
#define WINAPI
#define WINAPIV
#define WINUSERAPI

#define VOID void

#include "miniwin_misc.h"
#include "miniwin_com.h"
#include "miniwin_ddraw.h"
#include "miniwin_dsound.h"
#include "miniwin_ui.h"
#include "miniwin_thread.h"
#include "miniwin_rand.h"

#include "miniwin_macro.h"
