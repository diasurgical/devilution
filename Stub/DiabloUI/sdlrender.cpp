#include "../../types.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int LogoWidth;
int LogoHeight;

int fadeValue = 0;
int SelectedItem = 1;
int TotalPlayers = 0;

void *pPcxLogoImage;
int gdwLogoWidth;
int gdwLogoHeight;
void *pPcxLogoSmImage;
int gdwLogoSmWidth;
int gdwLogoSmHeight;

void *pPcxTitleImage;

int gdwCursorWidth;
int gdwCursorHeight;
void *pPcxCursorImage;

int gdwHeroHeight;
int gdwHeroWidth;
void *pPcxHeroImage;

int gdwFont16Width;
int gdwFont16Height;
void *pPcxFont16sImage;
void *pPcxFont16gImage;
unsigned char *pFont16;

int gdwFont24Width;
int gdwFont24Height;
void *pPcxFont24sImage;
void *pPcxFont24gImage;
unsigned char *pFont24;

int gdwFont30Width;
int gdwFont30Height;
void *pPcxFont30sImage;
void *pPcxFont30gImage;
unsigned char *pFont30;

int gdwFont42Width;
int gdwFont42Height;
void *pPcxFont42gImage;
void *pPcxFont42yImage;
unsigned char *pFont42;

void *MenuPentegram16;
void *MenuPentegram;
void *MenuPentegram42;

char HeroUndecidedName[17];

_uiheroinfo heroarray[10];

bool LoadArtImage(char *pszFile, void **pBuffer, int frames, DWORD *data, PALETTEENTRY *pPalette = NULL)
{
	DWORD width;
	DWORD height;

	*pBuffer = NULL;

	if (!SBmpLoadImage(pszFile, 0, 0, 0, &width, &height, 0))
		return 0;
	*pBuffer = malloc(height * width);
	if (!SBmpLoadImage(pszFile, pPalette, *pBuffer, height * width, 0, 0, 0))
		return 0;
	if (pBuffer && data) {
		data[0] = width;
		data[1] = height / frames;
	}

	return 1;
}

void FreeMenuItems()
{
	void *tmp;

	tmp = pPcxFont42yImage;
	pPcxFont42yImage = NULL;
	mem_free_dbg(tmp);
}

void SdlDiabloMainWindow()
{
	atexit(SDL_Quit);
	atexit(TTF_Quit);
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Diablo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	printf("Window And Renderer Created!\n");

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	assert(surface);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
	assert(texture);

	palette = SDL_AllocPalette(256);

	j_lock_buf_priv(0); //FIXME 0?
}

void DrawArtImage(int SX, int SY, int SW, int SH, int nFrame, void *pBuffer, BYTE *bMask = NULL)
{
	BYTE *src = (BYTE *)pBuffer + (SW * SH * nFrame);
	BYTE *dst = (BYTE *)&gpBuffer->row[SY].pixels[SX];

	for (int i = 0; i < SH && i + SY < SCREEN_HEIGHT; i++, src += SW, dst += 768) {
		for (int j = 0; j < SW && j + SX < SCREEN_WIDTH; j++) {
			if (bMask == NULL || src[j] != *bMask)
				dst[j] = src[j];
		}
	}
}

int GetCenterOffset(int w, int bw = 0)
{
	if (bw == 0) {
		bw = SCREEN_WIDTH;
	}

	return bw / 2 - w / 2;
}

void DrawPCXString(int x, int y, int w, int h, BYTE *str, BYTE *font, void *pBuff)
{
	int len = 0;
	BYTE mask = 32;
	BYTE chr;
	int i;

	for (i = 0; i < strlen(str); i++) {
		DrawArtImage(x + len, y, w, h, str[i], pBuff, &mask);
		chr = font[str[i] + 2];
		if (chr)
			len += chr;
		else
			len += *font;
	}
}

int GetPCXFontWidth(unsigned char *str, BYTE *font)
{
	int i;
	int len = 0;
	BYTE chr;
	for (i = 0; i < strlen(str); i++) {
		chr = font[str[i] + 2];
		if (chr)
			len += chr;
		else
			len += *font;
	}

	return len;
}

int TextAlignment(char *text, TXT_JUST align, int bw, BYTE *pFont)
{
	if (align != JustLeft) {
		int w = GetPCXFontWidth(text, pFont);
		if (align == JustCentre) {
			return GetCenterOffset(w, bw);
		} else if (align == JustRight) {
			return bw - w;
		}
	}

	return 0;
}

void PrintText16Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont16);

	DrawPCXString(x, y, gdwFont16Width, gdwFont16Height, text, pFont16, pPcxFont16gImage);
}

void PrintText16Silver(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont16);

	DrawPCXString(x, y, gdwFont16Width, gdwFont16Height, text, pFont16, pPcxFont16sImage);
}

void PrintText24Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont24);

	DrawPCXString(x, y, gdwFont24Width, gdwFont24Height, text, pFont24, pPcxFont24gImage);
}

void PrintText24Silver(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont24);

	DrawPCXString(x, y, gdwFont24Width, gdwFont24Height, text, pFont24, pPcxFont24sImage);
}

void PrintText30Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont30);

	DrawPCXString(x, y, gdwFont30Width, gdwFont30Height, text, pFont30, pPcxFont30gImage);
}

void PrintText30Silver(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont30);

	DrawPCXString(x, y, gdwFont30Width, gdwFont30Height, text, pFont30, pPcxFont30sImage);
}

void PrintText42Gold(int x, int y, char *text, TXT_JUST align = JustLeft, int bw = 0)
{
	x += TextAlignment(text, align, bw, pFont42);

	DrawPCXString(x, y, gdwFont42Width, gdwFont42Height, text, pFont42, pPcxFont42gImage);
}

void LoadPalInMem(PALETTEENTRY *pPal)
{
	for (int i = 0; i < 256; i++) {
		orig_palette[i].peFlags = 0;
		orig_palette[i].peRed = pPal[i].peRed;
		orig_palette[i].peGreen = pPal[i].peGreen;
		orig_palette[i].peBlue = pPal[i].peBlue;
	}
}

void LoadTitelArt(char *pszFile)
{
	PALETTEENTRY pPal[256];

	fadeValue = 0;
	LoadArtImage(pszFile, &pPcxTitleImage, 1, NULL, pPal);
	LoadPalInMem(pPal);
	ApplyGamma(logical_palette, orig_palette, 256);
}

int GetAnimationFrame(int frames, int fps = 60)
{
	int frame = (SDL_GetTicks() / fps) % frames;

	return frame > frames ? 0 : frame;
}

void UiFadeIn(int steps)
{
	if (fadeValue < 256) {
		fadeValue += steps;
		if (fadeValue > 256) {
			fadeValue = 256;
		}
	}

	SetFadeLevel(fadeValue);

	return fadeValue == 256;
}

bool UiFadeOut(int steps)
{
	if (fadeValue > 0) {
		fadeValue -= 256 / steps;
		if (fadeValue < 0) {
			fadeValue = 0;
		}
	}

	SetFadeLevel(fadeValue);

	return fadeValue == 0;
}

///////////////////////////Renders

void AnimateDiabloLogo(int t, int w, int h, void *pBuffer)
{
	BYTE mask = 250;
	int frame = GetAnimationFrame(15);

	DrawArtImage(GetCenterOffset(w), t, w, h, frame, pBuffer, &mask);
}

void RenderDiabloLogo()
{
	AnimateDiabloLogo(182, gdwLogoWidth, gdwLogoHeight, pPcxLogoImage);
}

void RenderDiabloLogoSm()
{
	AnimateDiabloLogo(0, gdwLogoSmWidth, gdwLogoSmHeight, pPcxLogoSmImage);
}

void DrawMouse()
{
	BYTE mask = 0;

	SDL_GetMouseState(&MouseX, &MouseY);

	float scaleX;
	SDL_RenderGetScale(renderer, &scaleX, NULL);
	MouseX /= scaleX;
	MouseY /= scaleX;

	SDL_Rect view;
	SDL_RenderGetViewport(renderer, &view);
	MouseX -= view.x;
	MouseY -= view.y;

	DrawArtImage(MouseX, MouseY, gdwCursorWidth, gdwCursorHeight, 0, pPcxCursorImage, &mask);
}

void AnimateSelector(int x, int y, int width, int padding, int spacing, int swidth, void *pBuffer)
{
	BYTE mask = 250;

	width = width ? width : SCREEN_WIDTH;
	x += GetCenterOffset(swidth, width);
	y += (SelectedItem - 1) * spacing;

	int frame = GetAnimationFrame(8);
	DrawArtImage(x - width / 2 + padding, y, swidth, swidth, frame, pBuffer, &mask);
	DrawArtImage(x + width / 2 - padding, y, swidth, swidth, frame, pBuffer, &mask);
}

void DrawSelector16(int x, int y, int width, int padding, int spacing)
{
	AnimateSelector(x, y, width, padding, spacing, 20, MenuPentegram16);
}

void DrawSelector(int x, int y, int width, int padding, int spacing)
{
	AnimateSelector(x, y, width, padding, spacing, 30, MenuPentegram);
}

void DrawSelector42(int x, int y, int width, int padding, int spacing)
{
	AnimateSelector(x, y, width, padding, spacing, 42, MenuPentegram42);
}

void SetHeroStats(_uiheroinfo *a1)
{
	memcpy(&heroarray[TotalPlayers], a1, sizeof(_uiheroinfo));
}

void LoadHeroStats()
{
	pfile_ui_set_hero_infos(SetHeroStats);
}
