#pragma once

/** @file
 * Utilities for SDL.
 */

#include <assert.h>

#include <SDL2/SDL.h>

#define SDL_CHECK(e) assert(e == 0)
