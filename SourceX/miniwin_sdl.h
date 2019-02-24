#pragma once

#include <SDL.h>

#define SDL_CHECK(e) assert(e == 0)

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern SDL_Surface *surface;
extern SDL_Palette *palette;
extern SDL_Surface *pal_surface;

void sdl_present_surface();

#ifdef __WINDOWS__
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

void sdl_update_entire_surface();
