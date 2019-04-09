//HEADER_GOES_HERE
#ifndef __NTHREAD_H__
#define __NTHREAD_H__

extern char byte_679704; // weak
extern int gdwMsgLenTbl[MAX_PLRS];
extern int gdwDeltaBytesSec;    // weak
extern char nthread_should_run; // weak
extern DWORD gdwTurnsInTransit; // weak
extern int glpMsgTbl[MAX_PLRS];
extern unsigned int glpNThreadId;
extern int turn_upper_bit;    // weak
extern char byte_679758;      // weak
extern int gdwLargestMsgSize; // weak
extern int gdwNormalMsgSize;  // weak
extern int last_tick;         // weak

void nthread_init_mutex();
void nthread_cleanup_mutex_atexit();
void __cdecl nthread_cleanup_mutex(void);
void nthread_terminate_game(const char *pszFcn);
int nthread_send_and_recv_turn(int cur_turn, int turn_delta);
int nthread_recv_turns(int *pfSendAsync);
void nthread_set_turn_upper_bit();
void nthread_start(BOOL set_turn_upper_bit);
unsigned int __stdcall nthread_handler(void *a1);
void nthread_cleanup();
void nthread_ignore_mutex(BOOL bStart);
BOOL nthread_has_500ms_passed(BOOL unused);

/* rdata */

#endif /* __NTHREAD_H__ */
