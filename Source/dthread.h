//HEADER_GOES_HERE
#ifndef __DTHREAD_H__
#define __DTHREAD_H__

extern unsigned int glpDThreadId; // idb
extern BOOLEAN dthread_running;

void dthread_init_mutex();
void dthread_cleanup_mutex_atexit();
void __cdecl dthread_cleanup_mutex(void);
void dthread_remove_player(int pnum);
void dthread_send_delta(int pnum, char cmd, void *pbSrc, int dwLen);
void dthread_start();
unsigned int __stdcall dthread_handler(void *unused);
void dthread_cleanup();

/* data */
extern int dthread_inf; // weak

#endif /* __DTHREAD_H__ */
