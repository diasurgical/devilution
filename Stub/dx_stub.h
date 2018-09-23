#pragma once

#include <SDL2/SDL.h>

extern SDL_Window *sdl_window;
extern SDL_Renderer *sdl_renderer;
extern SDL_Texture *sdl_render_texture;
extern SDL_Surface *sdl_surface;

void sdl_present_surface();