//HEADER_GOES_HERE

#include "../types.h"

int movie_cpp_init_value; // weak
BYTE movie_playing;
BOOL loop_movie;

const int movie_inf = 0x7F800000; // weak

struct movie_cpp_init {
	movie_cpp_init()
	{
		movie_cpp_init_value = movie_inf;
	}
} _movie_cpp_init;
// 47F144: using guessed type int movie_inf;
// 659AF4: using guessed type int movie_cpp_init_value;

void __fastcall play_movie(char *pszMovie, BOOL user_can_close)
{
	if (!gbActive) {
		return;
	}

	WNDPROC saveProc = SetWindowProc(MovieWndProc);
	InvalidateRect(ghMainWnd, 0, 0);
	UpdateWindow(ghMainWnd);
	movie_playing = TRUE;
	sound_disable_music(TRUE);
	sfx_stop();
	effects_play_sound("Sfx\\Misc\\blank.wav");

	void *video_stream;
	SVidPlayBegin(pszMovie, 0, 0, 0, 0, loop_movie ? 0x100C0808 : 0x10280808, &video_stream);
	if (video_stream) {
		MSG Msg;
		while (video_stream) {
			if (!gbActive || user_can_close && !movie_playing)
				break;
			while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
				if (Msg.message != WM_QUIT) {
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
			}
			if (!SVidPlayContinue())
				break;
		}
		if (video_stream)
			SVidPlayEnd(video_stream);
	}
	SetWindowProc(saveProc);
	sound_disable_music(FALSE);
}
// 634980: using guessed type int gbActive;

LRESULT __stdcall MovieWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
	case WM_KEYFIRST:
	case WM_CHAR:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		movie_playing = FALSE;
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			movie_playing = FALSE;
			return NULL;
		}
		break;
	}

	return MainWndProc(hWnd, Msg, wParam, lParam);
}
