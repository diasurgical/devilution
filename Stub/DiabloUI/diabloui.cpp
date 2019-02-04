#include "../../types.h"

TTF_Font *font;
int SelectedItemMax = 1;
int submenu = 0;
BYTE *FontTables[4];
Art ArtFonts[4][2];
Art ArtLogos[3];
Art ArtFocus[3];
Art ArtBackground;
Art ArtCursor;
Art ArtHero;

void(__stdcall *gfnSoundFunction)(char *file);

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int fadeValue = 0;
int SelectedItem = 1;

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

BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
	SDL_SetWindowPosition(window, X, Y);

	return TRUE;
}

void __cdecl UiDestroy()
{
	DUMMY();
	mem_free_dbg(ArtHero.data);
	ArtHero.data = NULL;

	mem_free_dbg(font);
	font = NULL;
}

void UiFocuse(int itemIndex, bool wrap)
{
	SelectedItem = itemIndex;

	if (!wrap) {
		if (SelectedItem < 1) {
			SelectedItem = 1;
			return;
		} else if (SelectedItem > SelectedItemMax) {
			SelectedItem = SelectedItemMax ?: 1;
			return;
		}
	} else if (SelectedItem < 1) {
		SelectedItem = SelectedItemMax ?: 1;
	} else if (SelectedItem > SelectedItemMax) {
		SelectedItem = 1;
	}

	UiPlayMoveSound();
}

bool UiFocuseNavigation(SDL_Event *event, bool wrap)
{
	switch (event->key.keysym.sym) {
	case SDLK_UP:
		UiFocuse(SelectedItem - 1, wrap);
		return true;
	case SDLK_DOWN:
		UiFocuse(SelectedItem + 1, wrap);
		return true;
	case SDLK_TAB:
		if (SDL_GetModState() & KMOD_SHIFT)
			UiFocuse(SelectedItem - 1, wrap);
		else
			UiFocuse(SelectedItem + 1, wrap);
		return true;
	case SDLK_PAGEUP:
		SelectedItem = 1;
		return true;
	case SDLK_PAGEDOWN:
		SelectedItem = SelectedItemMax;
		return true;
	}

	return false;
}

void SetMenu(int MenuId)
{
	UiPlaySelectSound();

	submenu = MenuId;
	SelectedItem = 1;
	switch (MenuId) {
	case SELHERO_CLASSES:
	case SELHERO_DIFFICULTY:
		SelectedItemMax = 3;
		break;
	default:
		SelectedItemMax = 1;
		break;
	}
}

bool IsInsideRect(const SDL_Event *event, const SDL_Rect *rect)
{
	const SDL_Point point = { event->button.x, event->button.y };
	return SDL_PointInRect(&point, rect);
}

void LoadArt(char *pszFile, Art *art, int frames, PALETTEENTRY *pPalette)
{
	if (art == NULL || art->data != NULL)
		return;

	if (!SBmpLoadImage(pszFile, 0, 0, 0, &art->width, &art->height, 0))
		return;

	art->data = malloc(art->width * art->height);
	if (!SBmpLoadImage(pszFile, pPalette, art->data, art->width * art->height, 0, 0, 0))
		return;

	if (art->data == NULL)
		return;

	art->height /= frames;

	return art;
}

void LoadMaskedArtFont(char *pszFile, Art *art, int frames, int mask = 250)
{
	LoadArt(pszFile, art, frames);
	art->masked = true;
	art->mask = mask;
}

void LoadArtFont(char *pszFile, int size, int color)
{
	LoadMaskedArtFont(pszFile, &ArtFonts[size][color], 256, 32);
}

void LoadUiGFX()
{
	FontTables[AFT_SMALL] = LoadFileInMem("ui_art\\font16.bin", 0);
	FontTables[AFT_MED] = LoadFileInMem("ui_art\\font24.bin", 0);
	FontTables[AFT_BIG] = LoadFileInMem("ui_art\\font30.bin", 0);
	FontTables[AFT_HUGE] = LoadFileInMem("ui_art\\font42.bin", 0);
	LoadArtFont("ui_art\\font16s.pcx", AFT_SMALL, AFC_SILVER);
	LoadArtFont("ui_art\\font16g.pcx", AFT_SMALL, AFC_GOLD);
	LoadArtFont("ui_art\\font24s.pcx", AFT_MED, AFC_SILVER);
	LoadArtFont("ui_art\\font24g.pcx", AFT_MED, AFC_GOLD);
	LoadArtFont("ui_art\\font30s.pcx", AFT_BIG, AFC_SILVER);
	LoadArtFont("ui_art\\font30g.pcx", AFT_BIG, AFC_GOLD);
	LoadArtFont("ui_art\\font42g.pcx", AFT_HUGE, AFC_GOLD);

	LoadMaskedArtFont("ui_art\\logo.pcx", &ArtLogos[LOGO_BIG], 15);
	LoadMaskedArtFont("ui_art\\smlogo.pcx", &ArtLogos[LOGO_MED], 15);
	LoadMaskedArtFont("ui_art\\focus16.pcx", &ArtFocus[FOCUS_SMALL], 8);
	LoadMaskedArtFont("ui_art\\focus.pcx", &ArtFocus[FOCUS_MED], 8);
	LoadMaskedArtFont("ui_art\\focus42.pcx", &ArtFocus[FOCUS_BIG], 8);
	LoadMaskedArtFont("ui_art\\cursor.pcx", &ArtCursor, 1, 0);
	LoadArt("ui_art\\heros.pcx", &ArtHero, 4);
}

void InitFont()
{
	if (!TTF_WasInit() && TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}

	// TODO locate font dynamically, and use fallback font if missing
	font = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Times_New_Roman_Bold.ttf", 17);
	if (font == NULL) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return;
	}

	TTF_SetFontKerning(font, FALSE);
	TTF_SetFontHinting(font, TTF_HINTING_MONO);
}

void UiInitialize()
{
	LoadUiGFX();
	ShowCursor(FALSE);
	InitFont();
}

int __cdecl UiProfileGetString()
{
	DUMMY();
	return 0;
}

char connect_plrinfostr[128];
char connect_categorystr[128];
void __stdcall UiSetupPlayerInfo(char *infostr, _uiheroinfo *pInfo, DWORD type)
{
	DUMMY();
	SStrCopy(connect_plrinfostr, infostr, 128);
	char format[32] = "";
	strncpy(format, (char *)&type, 4);
	strcat(format, " %d %d %d %d %d %d %d %d %d");

	snprintf(
	    connect_categorystr,
	    128,
	    format,
	    pInfo->level,
	    pInfo->heroclass,
	    pInfo->herorank,
	    pInfo->strength,
	    pInfo->magic,
	    pInfo->dexterity,
	    pInfo->vitality,
	    pInfo->gold,
	    pInfo->spawned);
}

BOOL __stdcall UiCopyProtError(int *pdwResult)
{
	UNIMPLEMENTED();
}

void __stdcall UiAppActivate(BOOL bActive)
{
	UNIMPLEMENTED();
}

BOOL __fastcall UiValidPlayerName(char *name)
{
	if (!strlen(name))
		return FALSE;

	if (strpbrk(name, ",<>%&\\\"?*#/:") || strpbrk(name, " "))
		return FALSE;

	for (char *letter = name; *letter; letter++)
		if (letter < 0x20 || letter > 0x7E && letter < 0xC0)
			return FALSE;

	return TRUE;
}

void __cdecl UiProfileCallback()
{
	UNIMPLEMENTED();
}

void __cdecl UiProfileDraw()
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiCategoryCallback(int a1, int a2, int a3, int a4, int a5, _DWORD *a6, _DWORD *a7)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiGetDataCallback(int game_type, int data_code, void *a3, int a4, int a5)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiAuthCallback(int a1, char *a2, char *a3, char a4, char *a5, LPSTR lpBuffer, int cchBufferMax)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiSoundCallback(int a1, int type, int a3)
{
	UNIMPLEMENTED();
}

void UiPlayMoveSound()
{
	if (gfnSoundFunction)
		gfnSoundFunction("sfx\\items\\titlemov.wav");
}

void UiPlaySelectSound()
{
	if (gfnSoundFunction)
		gfnSoundFunction("sfx\\items\\titlslct.wav");
}

void __stdcall UiMessageBoxCallback(HWND hWnd, char *lpText, LPCSTR lpCaption, UINT uType)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiDrawDescCallback(int game_type, COLORREF color, LPCSTR lpString, char *a4, int a5, UINT align, time_t a7,
    HDC *a8)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiCreateGameCallback(int a1, int a2, int a3, int a4, int a5, int a6)
{
	UNIMPLEMENTED();
}

BOOL __stdcall UiArtCallback(int game_type, unsigned int art_code, PALETTEENTRY *pPalette, void *pBuffer,
    DWORD dwBuffersize, DWORD *pdwWidth, DWORD *pdwHeight, DWORD *pdwBpp)
{
	UNIMPLEMENTED();
}

int __stdcall UiSelectGame(int a1, _SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info,
    _SNETVERSIONDATA *file_info, int *playerId)
{
	SNetCreateGame(NULL, NULL, NULL, 0, NULL, 0, MAX_PLRS, NULL, NULL, playerId);
	return 1;
}

BOOL __stdcall UiCreatePlayerDescription(_uiheroinfo *info, DWORD mode, char *desc)
{
	char format[32] = "";
	strncpy(format, (char *)&mode, 4);
	strcat(format, " %d %d %d %d %d %d %d %d %d");

	snprintf(
	    desc,
	    128,
	    format,
	    info->level,
	    info->heroclass,
	    info->herorank,
	    info->strength,
	    info->magic,
	    info->dexterity,
	    info->vitality,
	    info->gold,
	    info->spawned);

	return TRUE;
}

void DrawArt(int screenX, int screenY, Art *art, int nFrame, int drawW)
{
	BYTE *src = (BYTE *)art->data + (art->width * art->height * nFrame);
	BYTE *dst = (BYTE *)&gpBuffer->row[screenY].pixels[screenX];
	drawW = drawW ?: art->width;

	for (int i = 0; i < art->height && i + screenY < SCREEN_HEIGHT; i++, src += art->width, dst += ROW_PITCH) {
		for (int j = 0; j < art->width && j + screenX < SCREEN_WIDTH; j++) {
			if (j < drawW && (!art->masked || src[j] != art->mask))
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

int GetStrWidth(BYTE *str, int size)
{
	int strWidth = 0;

	for (int i = 0; i < strlen(str); i++) {
		BYTE w = FontTables[size][str[i] + 2];
		if (w)
			strWidth += w;
		else
			strWidth += FontTables[size][0];
	}

	return strWidth;
}

int TextAlignment(char *text, TXT_JUST align, int bw, int size)
{
	if (align != JustLeft) {
		int w = GetStrWidth(text, size);
		if (align == JustCentre) {
			return GetCenterOffset(w, bw);
		} else if (align == JustRight) {
			return bw - w;
		}
	}

	return 0;
}

void DrawArtStr(int x, int y, int size, int color, BYTE *str, TXT_JUST align, int bw)
{
	x += TextAlignment(str, align, bw, size);

	for (int i = 0; i < strlen(str); i++) {
		BYTE w = FontTables[size][str[i] + 2];
		if (!w)
			w = FontTables[size][0];
		DrawArt(x, y, &ArtFonts[size][color], str[i], w);
		x += w;
	}
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

void LoadBackgroundArt(char *pszFile)
{
	PALETTEENTRY pPal[256];

	fadeValue = 0;
	LoadArt(pszFile, &ArtBackground, 1, pPal);
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

void DrawLogo(int t, int size)
{
	DrawArt(GetCenterOffset(ArtLogos[size].width), t, &ArtLogos[size], GetAnimationFrame(15));
}

void DrawMouse()
{
	SDL_GetMouseState(&MouseX, &MouseY);

	float scaleX;
	SDL_RenderGetScale(renderer, &scaleX, NULL);
	MouseX /= scaleX;
	MouseY /= scaleX;

	SDL_Rect view;
	SDL_RenderGetViewport(renderer, &view);
	MouseX -= view.x;
	MouseY -= view.y;

	DrawArt(MouseX, MouseY, &ArtCursor);
}

void DrawSelector(int x, int y, int width, int padding, int spacing, int size)
{
	width = width ? width : SCREEN_WIDTH;
	x += GetCenterOffset(ArtFocus[size].width, width);
	y += (SelectedItem - 1) * spacing;

	int frame = GetAnimationFrame(8);
	DrawArt(x - width / 2 + padding, y, &ArtFocus[size], frame);
	DrawArt(x + width / 2 - padding, y, &ArtFocus[size], frame);
}
