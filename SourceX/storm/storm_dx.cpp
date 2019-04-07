#include <SDL.h>

#include "devilution.h"
#include "miniwin/ddraw.h"
#include "stubs.h"

namespace dvl {

BOOL SDrawManualInitialize(
    HWND hWnd,
    LPDIRECTDRAW ddInterface,
    LPDIRECTDRAWSURFACE primarySurface,
    LPDIRECTDRAWSURFACE surface2,
    LPDIRECTDRAWSURFACE surface3,
    LPDIRECTDRAWSURFACE backSurface,
    LPDIRECTDRAWPALETTE ddPalette,
    HPALETTE hPalette)
{
	DUMMY();
	return true;
}

/** Copy the palette surface to the main backbuffer */
void sdl_update_entire_surface()
{
	assert(surface && pal_surface);
	SDL_Rect src_rect = { 64, 160, 640, 480 };
	if (SDL_BlitSurface(pal_surface, &src_rect, surface, NULL) != 0) {
		SDL_Log("SDL_BlitSurface: %s\n", SDL_GetError());
	}
}

BOOL SDrawUpdatePalette(unsigned int firstentry, unsigned int numentries, PALETTEENTRY *pPalEntries, int a4)
{
	assert(firstentry == 0);
	assert(numentries == 256);

	SDL_Color colors[256];
	for (unsigned int i = firstentry; i < numentries; i++) {
		SDL_Color *c = &colors[i];
		PALETTEENTRY *p = &pPalEntries[i];
		c->r = p->peRed;
		c->g = p->peGreen;
		c->b = p->peBlue;
		c->a = SDL_ALPHA_OPAQUE;
	}

	assert(palette);
	if (SDL_SetPaletteColors(palette, colors, firstentry, numentries) != 0) {
		SDL_Log("SDL_SetPaletteColors: %s\n", SDL_GetError());
		return false;
	}

	if (pal_surface) {
		sdl_update_entire_surface();
		lpDDSPrimary->Unlock(NULL);
	}

	return true;
}

} // namespace dvl
