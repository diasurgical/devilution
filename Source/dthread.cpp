/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

#include "../types.h"

int dthread_cpp_init_value; // weak
static CRITICAL_SECTION sgMemCrit; // idb
unsigned int glpDThreadId; // idb
TMegaPkt *sgpInfoHead; /* may not be right struct */
char byte_52A508; // weak
HANDLE sghWorkToDoEvent; // idb

int dthread_inf = 0x7F800000; // weak

/* rdata */
static HANDLE sghThread = (HANDLE)0xFFFFFFFF; // idb

//----- (0041509D) --------------------------------------------------------
struct dthread_cpp_init_1
{
	dthread_cpp_init_1()
	{
		dthread_cpp_init_value = dthread_inf;
	}
} _dthread_cpp_init_1;
// 47A460: using guessed type int dthread_inf;
// 52A4E0: using guessed type int dthread_cpp_init_value;

//----- (004150A8) --------------------------------------------------------
struct dthread_cpp_init_2
{
	dthread_cpp_init_2()
	{
		dthread_init_mutex();
		dthread_cleanup_mutex_atexit();
	}
} _dthread_cpp_init_2;

//----- (004150B2) --------------------------------------------------------
void __cdecl dthread_init_mutex()
{
	InitializeCriticalSection(&sgMemCrit);
}

//----- (004150BE) --------------------------------------------------------
void __cdecl dthread_cleanup_mutex_atexit()
{
	atexit(dthread_cleanup_mutex);
}

//----- (004150CA) --------------------------------------------------------
void __cdecl dthread_cleanup_mutex()
{
	DeleteCriticalSection(&sgMemCrit);
}

//----- (004150D6) --------------------------------------------------------
void __fastcall dthread_remove_player(int pnum)
{
	int v1; // edi
	TMegaPkt *i; // eax

	v1 = pnum;
	EnterCriticalSection(&sgMemCrit);
	for ( i = sgpInfoHead; i; i = i->pNext )
	{
		if ( i->dwSpaceLeft == v1 )
			i->dwSpaceLeft = 4;
	}
	LeaveCriticalSection(&sgMemCrit);
}

//----- (00415109) --------------------------------------------------------
void __fastcall dthread_send_delta(int pnum, int cmd, void *pbSrc, int dwLen)
{
	char v4; // bl
	TMegaPkt *v5; // eax
	TMegaPkt *v6; // esi
	TMegaPkt *v7; // eax
	TMegaPkt **v8; // ecx
	int v9; // [esp+4h] [ebp-4h]

	v4 = cmd;
	v9 = pnum;
	if ( gbMaxPlayers != 1 )
	{
		v5 = (TMegaPkt *)DiabloAllocPtr(dwLen + 20);
		v6 = v5;
		v5->pNext = 0;
		v5->dwSpaceLeft = v9;
		v5->data[0] = v4;
		*(_DWORD *)&v5->data[4] = dwLen;
		memcpy(&v5->data[8], pbSrc, dwLen);
		EnterCriticalSection(&sgMemCrit);
		v7 = sgpInfoHead;
		v8 = &sgpInfoHead;
		while ( v7 )
		{
			v8 = &v7->pNext;
			v7 = v7->pNext;
		}
		*v8 = v6;
		SetEvent(sghWorkToDoEvent);
		LeaveCriticalSection(&sgMemCrit);
	}
}
// 679660: using guessed type char gbMaxPlayers;

//----- (00415186) --------------------------------------------------------
void __cdecl dthread_start()
{
	char *v0; // eax
	char *v1; // eax

	if ( gbMaxPlayers != 1 )
	{
		sghWorkToDoEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
		if ( !sghWorkToDoEvent )
		{
			v0 = GetLastErr();
			TermMsg("dthread:1\n%s", v0);
		}
		byte_52A508 = 1;
		sghThread = (HANDLE)_beginthreadex(NULL, 0, dthread_handler, NULL, 0, &glpDThreadId);
		if ( sghThread == (HANDLE)-1 )
		{
			v1 = GetLastErr();
			TermMsg("dthread2:\n%s", v1);
		}
	}
}
// 52A508: using guessed type char byte_52A508;
// 679660: using guessed type char gbMaxPlayers;

//----- (004151F3) --------------------------------------------------------
unsigned int __stdcall dthread_handler(void *a1)
{
	char *v1; // eax
	TMegaPkt *v2; // esi
	int v3; // ecx
	unsigned int v4; // edi

	while ( byte_52A508 )
	{
		if ( !sgpInfoHead && WaitForSingleObject(sghWorkToDoEvent, 0xFFFFFFFF) == -1 )
		{
			v1 = GetLastErr();
			TermMsg("dthread4:\n%s", v1);
		}
		EnterCriticalSection(&sgMemCrit);
		v2 = sgpInfoHead;
		if ( sgpInfoHead )
			sgpInfoHead = sgpInfoHead->pNext;
		else
			ResetEvent(sghWorkToDoEvent);
		LeaveCriticalSection(&sgMemCrit);
		if ( v2 )
		{
			v3 = v2->dwSpaceLeft;
			if ( v3 != 4 )
				multi_send_zero_packet(v3, v2->data[0], &v2->data[8], *(_DWORD *)&v2->data[4]);
			v4 = 1000 * *(_DWORD *)&v2->data[4] / (unsigned int)gdwDeltaBytesSec;
			if ( v4 >= 1 )
				v4 = 1;
			mem_free_dbg(v2);
			if ( v4 )
				Sleep(v4);
		}
	}
	return 0;
}
// 52A508: using guessed type char byte_52A508;
// 679730: using guessed type int gdwDeltaBytesSec;

//----- (004152C0) --------------------------------------------------------
void __cdecl dthread_cleanup()
{
	char *v0; // eax
	TMegaPkt *v1; // eax
	TMegaPkt *v2; // esi

	if ( sghWorkToDoEvent )
	{
		byte_52A508 = 0;
		SetEvent(sghWorkToDoEvent);
		if ( sghThread != (HANDLE)-1 && glpDThreadId != GetCurrentThreadId() )
		{
			if ( WaitForSingleObject(sghThread, 0xFFFFFFFF) == -1 )
			{
				v0 = GetLastErr();
				TermMsg("dthread3:\n(%s)", v0);
			}
			CloseHandle(sghThread);
			sghThread = (HANDLE)-1;
		}
		CloseHandle(sghWorkToDoEvent);
		v1 = sgpInfoHead;
		sghWorkToDoEvent = 0;
		if ( sgpInfoHead )
		{
			do
			{
				v2 = v1->pNext;
				sgpInfoHead = 0;
				mem_free_dbg(v1);
				v1 = v2;
				sgpInfoHead = v2;
			}
			while ( v2 );
		}
	}
}
// 52A508: using guessed type char byte_52A508;
