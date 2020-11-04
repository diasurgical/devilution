/**
 * @file nthread.h
 *
 * Interface of functions for managing game ticks.
 */
#ifndef __NTHREAD_H__
#define __NTHREAD_H__

extern BYTE sgbNetUpdateRate;
extern DWORD gdwMsgLenTbl[MAX_PLRS];
extern DWORD gdwDeltaBytesSec;
extern DWORD gdwTurnsInTransit;
extern int glpMsgTbl[MAX_PLRS];
extern int turn_upper_bit;
extern DWORD gdwLargestMsgSize;
extern DWORD gdwNormalMsgSize;

void nthread_terminate_game(const char *pszFcn);
DWORD nthread_send_and_recv_turn(DWORD cur_turn, int turn_delta);
BOOL nthread_recv_turns(BOOL *pfSendAsync);
void nthread_set_turn_upper_bit();
void nthread_start(BOOL set_turn_upper_bit);
void nthread_cleanup();
void nthread_ignore_mutex(BOOL bStart);
BOOL nthread_has_500ms_passed(BOOL unused);

#endif /* __NTHREAD_H__ */
