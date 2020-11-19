/**
 * @file movie.cpp
 *
 * Implementation of video playback.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

/** Should the movie continue playing. */
BYTE movie_playing;
/** Should the movie play in a loop. */
BOOL loop_movie;

/**
 * @brief Start playback of a given video.
 * @param pszMovie The file name of the video
 * @param user_can_close Set to false to make the video unskippable.
 */
void play_movie(const char *pszMovie, BOOL user_can_close)
{
	WNDPROC saveProc;
	HANDLE video_stream;

	if (!gbActive) {
		return;
	}

	saveProc = SetWindowProc(MovieWndProc);
	InvalidateRect(ghMainWnd, NULL, 0);
	UpdateWindow(ghMainWnd);
	movie_playing = TRUE;
	sound_disable_music(TRUE);
	stream_stop();
	effects_play_sound("Sfx\\Misc\\blank.wav");

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

/**
 * @brief Input handler for use during video playback.
 * @see WNDPROC
 */
LRESULT __stdcall MovieWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
	case WM_KEYDOWN:
	case WM_CHAR:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		movie_playing = FALSE;
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			movie_playing = FALSE;
			return 0;
		}
		break;
	}

	return MainWndProc(hWnd, Msg, wParam, lParam);
}
