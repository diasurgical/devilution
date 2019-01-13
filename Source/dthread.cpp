//HEADER_GOES_HERE

#include "../types.h"

static CRITICAL_SECTION sgMemCrit; // idb
unsigned int glpDThreadId;         // idb
TMegaPkt *sgpInfoHead;             /* may not be right struct */
char byte_52A508;                  // weak
HANDLE sghWorkToDoEvent;           // idb

/* rdata */
static HANDLE sghThread = (HANDLE)0xFFFFFFFF; // idb

#ifndef _MSC_VER
__attribute__((constructor))
#endif
static void dthread_c_init(void)
{
	dthread_init_mutex();
	dthread_cleanup_mutex_atexit();
}

SEG_ALLOCATE(SEGMENT_C_INIT)
_PVFV dthread_c_init_funcs[] = { &dthread_c_init };

void __cdecl dthread_init_mutex()
{
	InitializeCriticalSection(&sgMemCrit);
}

void __cdecl dthread_cleanup_mutex_atexit()
{
	atexit(dthread_cleanup_mutex);
}

void __cdecl dthread_cleanup_mutex()
{
	DeleteCriticalSection(&sgMemCrit);
}

void __fastcall dthread_remove_player(int pnum)
{
	int v1;      // edi
	TMegaPkt *i; // eax

	v1 = pnum;
	EnterCriticalSection(&sgMemCrit);
	for (i = sgpInfoHead; i; i = i->pNext) {
		if (i->dwSpaceLeft == v1)
			i->dwSpaceLeft = 4;
	}
	LeaveCriticalSection(&sgMemCrit);
}

void __fastcall dthread_send_delta(int pnum, char cmd, void *pbSrc, int dwLen)
{
	TMegaPkt *pkt;
	TMegaPkt *p;
	TMegaPkt **last;

	if (gbMaxPlayers != 1) {
		pkt = (TMegaPkt *)DiabloAllocPtr(dwLen + 20);
		pkt->pNext = 0;
		pkt->dwSpaceLeft = pnum;
		pkt->data[0] = cmd;
		*(_DWORD *)&pkt->data[4] = dwLen;
		memcpy(&pkt->data[8], pbSrc, dwLen);
		EnterCriticalSection(&sgMemCrit);
		last = &sgpInfoHead;
		for (p = sgpInfoHead; p != NULL; p = p->pNext) {
			last = &p->pNext;
		}
		*last = pkt;
		SetEvent(sghWorkToDoEvent);
		LeaveCriticalSection(&sgMemCrit);
	}
}
// 679660: using guessed type char gbMaxPlayers;

void __cdecl dthread_start()
{
	char *v0; // eax
	char *v1; // eax

	if (gbMaxPlayers != 1) {
		sghWorkToDoEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (!sghWorkToDoEvent) {
			v0 = TraceLastError();
			TermMsg("dthread:1\n%s", v0);
		}
		byte_52A508 = 1;
		sghThread = (HANDLE)_beginthreadex(NULL, 0, dthread_handler, NULL, 0, &glpDThreadId);
		if (sghThread == (HANDLE)-1) {
			v1 = TraceLastError();
			TermMsg("dthread2:\n%s", v1);
		}
	}
}
// 52A508: using guessed type char byte_52A508;
// 679660: using guessed type char gbMaxPlayers;

unsigned int __stdcall dthread_handler(void *a1)
{
	char *v1;        // eax
	TMegaPkt *v2;    // esi
	int v3;          // ecx
	unsigned int v4; // edi

	while (byte_52A508) {
		if (!sgpInfoHead && WaitForSingleObject(sghWorkToDoEvent, 0xFFFFFFFF) == -1) {
			v1 = TraceLastError();
			TermMsg("dthread4:\n%s", v1);
		}
		EnterCriticalSection(&sgMemCrit);
		v2 = sgpInfoHead;
		if (sgpInfoHead)
			sgpInfoHead = sgpInfoHead->pNext;
		else
			ResetEvent(sghWorkToDoEvent);
		LeaveCriticalSection(&sgMemCrit);
		if (v2) {
			v3 = v2->dwSpaceLeft;
			if (v3 != 4)
				multi_send_zero_packet(v3, v2->data[0], &v2->data[8], *(_DWORD *)&v2->data[4]);
			v4 = 1000 * *(_DWORD *)&v2->data[4] / (unsigned int)gdwDeltaBytesSec;
			if (v4 >= 1)
				v4 = 1;
			mem_free_dbg(v2);
			if (v4)
				Sleep(v4);
		}
	}
	return 0;
}
// 52A508: using guessed type char byte_52A508;
// 679730: using guessed type int gdwDeltaBytesSec;

void __cdecl dthread_cleanup()
{
	char *v0;     // eax
	TMegaPkt *v1; // eax
	TMegaPkt *v2; // esi

	if (sghWorkToDoEvent) {
		byte_52A508 = 0;
		SetEvent(sghWorkToDoEvent);
		if (sghThread != (HANDLE)-1 && glpDThreadId != GetCurrentThreadId()) {
			if (WaitForSingleObject(sghThread, 0xFFFFFFFF) == -1) {
				v0 = TraceLastError();
				TermMsg("dthread3:\n(%s)", v0);
			}
			CloseHandle(sghThread);
			sghThread = (HANDLE)-1;
		}
		CloseHandle(sghWorkToDoEvent);
		v1 = sgpInfoHead;
		sghWorkToDoEvent = 0;
		if (sgpInfoHead) {
			do {
				v2 = v1->pNext;
				sgpInfoHead = 0;
				mem_free_dbg(v1);
				v1 = v2;
				sgpInfoHead = v2;
			} while (v2);
		}
	}
}
// 52A508: using guessed type char byte_52A508;
