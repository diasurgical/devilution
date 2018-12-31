//HEADER_GOES_HERE
#ifndef __NTHREAD_H__
#define __NTHREAD_H__

extern char byte_679704;           // weak
extern int gdwMsgLenTbl[4];
extern int gdwDeltaBytesSec;    // weak
extern char nthread_should_run; // weak
extern DWORD gdwTurnsInTransit; // weak
extern int glpMsgTbl[4];
extern unsigned int glpNThreadId;
extern char sgbSyncCountdown;   // weak
extern int turn_upper_bit;      // weak
extern char byte_679758;        // weak
extern char sgbPacketCountdown; // weak
extern char sgbThreadIsRunning; // weak
extern int gdwLargestMsgSize;   // weak
extern int gdwNormalMsgSize;    // weak
extern int last_tick;           // weak

void __cdecl nthread_init_mutex();
void __cdecl nthread_cleanup_mutex_atexit();
void __cdecl nthread_cleanup_mutex(void);
void __fastcall nthread_terminate_game(const char *pszFcn);
int __fastcall nthread_send_and_recv_turn(int cur_turn, int turn_delta);
int __fastcall nthread_recv_turns(int *pfSendAsync);
void __cdecl nthread_set_turn_upper_bit();
void __fastcall nthread_start(BOOLEAN set_turn_upper_bit);
unsigned int __stdcall nthread_handler(void *a1);
void __cdecl nthread_cleanup();
void __fastcall nthread_ignore_mutex(BOOL bStart);
BOOL __fastcall nthread_has_500ms_passed(BOOL unused);

/* rdata */

#endif /* __NTHREAD_H__ */
