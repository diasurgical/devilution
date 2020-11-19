/**
 * @file movie.h
 *
 * Interface of video playback.
 */
#ifndef __MOVIE_H__
#define __MOVIE_H__

extern BOOL loop_movie;

void play_movie(const char *pszMovie, BOOL user_can_close);
LRESULT __stdcall MovieWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#endif /* __MOVIE_H__ */
