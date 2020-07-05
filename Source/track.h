/**
 * @file track.h
 *
 * Interface of functionality tracking what the mouse cursor is pointing at.
 */
#ifndef __TRACK_H__
#define __TRACK_H__

void track_process();
void track_repeat_walk(BOOL rep);
BOOL track_isscrolling();

#endif /* __TRACK_H__ */
