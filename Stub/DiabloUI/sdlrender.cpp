#include "../../types.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int LogoWidth;
int LogoHeight;

int fadeValue = 0;
int SelectedItem = 1;

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

char *errorTitle[] = {
	"Direct Draw Error",
	"Out of Memory Error",
	"Direct Draw Error",
	"Data File Error",
	"Direct Sound Error",
	"Out of Disk Space",
	"Direct Draw Error",
	"Data File Error",
	"Windows 2000 Restricted User Advisory",
	"Read-Only Directory Error",
};
char *errorMessages[] = {
	"Diablo was unable to properly initialize your video card using DirectX.\nPlease try the following solutions to correct the problem:\n\n    Use the Diablo setup program \"SETUP.EXE\" provided on the Diablo CD-ROM to install DirectX 3.0.\n\n    Install the most recent DirectX video drivers provided by the manufacturer of your video card.\nA list of video card manufactuers can be found at: http://www.blizzard.com/support/vendors.htm\n\nIf you continue to have problems with DirectX, please contact Microsoft's Technical Support at:\n\n\nIf you continue to have problems, we have also included Microsoft DirectX 2.0 drivers on the Diablo CD-ROM.\nThis older version of DirectX may work in cases where DirectX 3.0 does not.\n\n    USA telephone: 1-800-426-9400\n    International telephone: 206-882-8080\n    http://www.microsoft.com\n\n\nThe error encountered while trying to initialize the video card was:\n\n    %s",
	"Diablo has exhausted all the memory on your system.\nThis problem can likely be corrected by changing the virtual memory settings for Windows.\nEnsure that your system has at least 10 megabytes of free disk space, then check your virtual memory settings:\n\nFor Windows 95:\n    Select \"Settings - Control Panel\" from the \"Start\" menu\n    Run the \"System\" control panel applet\n    Select the \"Performance\" tab, and press \"Virtual Memory\"\n    Use the \"Let Windows manage my virtual memory...\" option\n\nFor Windows NT:\n    Select \"Settings - Control Panel\" from the \"Start\" menu\n    Run the \"System\" control panel applet\n    Select the \"Performance\" tab\n    Press \"Change\" in \"Virtual Memory\" settings\n    Ensure that the virtual memory file is at least 32 megabytes\n\nThe error encountered was:\n\n    %s",
	"Diablo was unable to open a required file.\nPlease ensure that the Diablo disc is in the CDROM drive.\nIf this problem persists, try uninstalling and reinstalling Diablo using the program \"SETUP.EXE\" on the Diablo CD-ROM.\n\n\nThe problem occurred while trying to load a file\n\n    %s",
	"Diablo was unable to find the file \"ddraw.dll\", which is a component of Microsoft DirectX.\nPlease run the program \"SETUP.EXE\" on the Diablo CD-ROM and install Microsoft DirectX.\n\nIf you continue to have problems with DirectX, please contact Microsoft's Technical Support at:\n\n    USA telephone: 1-800-426-9400\n    International telephone: 206-882-8080\n    http://www.microsoft.com\n\n\nThe error encountered while trying to initialize DirectX was:\n\n    %s",
	"Diablo was unable to find the file \"dsound.dll\", which is a component of Microsoft DirectX.\nPlease run the program \"SETUP.EXE\" on the Diablo CD-ROM and install Microsoft DirectX.\n\nIf you continue to have problems with DirectX, please contact Microsoft's Technical Support at:\n\n    USA telephone: 1-800-426-9400\n    International telephone: 206-882-8080\n    http://www.microsoft.com\n\n\nThe error encountered while trying to initialize DirectX was:\n\n    %s",
	"Diablo requires at least 10 megabytes of free disk space to run properly.\nThe disk:\n\n%s\n\nhas less than 10 megabytes of free space left.\n\nPlease free some space on your drive and run Diablo again.",
	"Diablo was unable to switch video modes.\nThis is a common problem for computers with more than one video card.\nTo correct this problem, please set your video resolution to 640 x 480 and try running Diablo again.\n\nFor Windows 95 and Windows NT\n    Select \"Settings - Control Panel\" from the \"Start\" menu\n    Run the \"Display\" control panel applet\n    Select the \"Settings\" tab\n    Set the \"Desktop Area\" to \"640 x 480 pixels\"\n\n\nThe error encountered while trying to switch video modes was:\n\n    %s",
	"Diablo cannot read a required data file.\nYour Diablo CD may not be in the CDROM drive.\nPlease ensure that the Diablo disc is in the CDROM drive and press OK.\nTo leave the program, press Exit.\n    %s",
	"In order to install, play or patch Diablo using the Windows 2000 operating system,\nyou will need to log in as either an Administrator or as a Power User.\n\nUsers, also known as Restricted Users, do not have sufficient access to install or play the game properly.\n\nIf you have further questions regarding User Rights in Windows 2000, please refer to your Windows 2000 documentation or contact your system administrator.",
	"Diablo is being run from:\n\n    %s\n\n\nDiablo or the current user does not seem to have write privilages in this directory. Contact your system administrator.\n\nNote that Windows 2000 Restricted Users can not write to the Windows or Program Files directory hierarchies.",
};

DWORD FormatMessage(
    DWORD dwFlags,
    LPCVOID lpSource,
    DWORD dwMessageId,
    DWORD dwLanguageId,
    char *lpBuffer,
    DWORD nSize,
    va_list *Arguments)
{
	DUMMY();
	return 0;
}

int MAKEINTRESOURCE(int i)
{
	switch (i) {
	case IDD_DIALOG1:
		return 0;
	case IDD_DIALOG2:
		return 1;
	case IDD_DIALOG3:
		return 2;
	case IDD_DIALOG4:
		return 3;
	case IDD_DIALOG5:
		return 4;
	case IDD_DIALOG7:
		return 5;
	case IDD_DIALOG8:
		return 6;
	case IDD_DIALOG9:
		return 7;
	case IDD_DIALOG10:
		return 8;
	case IDD_DIALOG11:
		return 9;
	}
}

int DialogBoxParam(HINSTANCE hInstance, int msgId, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
	char text[1024];
	snprintf(text, 1024, errorMessages[msgId], dwInitParam);

	return SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, errorTitle[msgId], text, window) < 0 ? -1 : 0;
}

BOOL SetDlgItemText(HWND hDlg, int nIDDlgItem, LPCSTR lpString)
{
	return FALSE;
}

BOOL EndDialog(HWND hDlg, INT_PTR nResult)
{
	return FALSE;
}

BOOL SetWindowPos(
    HWND hWnd,
    HWND hWndInsertAfter,
    int X,
    int Y,
    int cx,
    int cy,
    UINT uFlags)
{
	SDL_SetWindowPosition(window, X, Y);

	return TRUE;
}

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

	int flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (!fullscreen) {
		flags = SDL_WINDOW_RESIZABLE;
	}
	window = SDL_CreateWindow("Diablo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	printf("Window And Renderer Created!\n");

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
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

int frameEnd = 0;
void CapFPS()
{
	int now = SDL_GetTicks();
	frameEnd += 1000 / 60;
	if (now < frameEnd) {
		SDL_Delay(frameEnd - now);
	}
}

bool UiFadeIn(int steps)
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
