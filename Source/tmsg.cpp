//HEADER_GOES_HERE

#include "../types.h"

TMsg *sgpTimedMsgHead;

int __fastcall tmsg_get(unsigned char *pbMsg, char bLen)
{
	unsigned char *v2; // ebx
	DWORD v3; // eax
	TMsg *v4; // esi
	size_t dwMaxLen; // edi

	v2 = pbMsg;
	if ( !sgpTimedMsgHead )
		return 0;
	v3 = GetTickCount();
	v4 = sgpTimedMsgHead;
	if ( (signed int)(*(_DWORD *)&sgpTimedMsgHead[1] - v3) >= 0 )
		return 0;
	//sgpTimedMsgHead = (TMsg *)*sgpTimedMsgHead; /* fix */
	dwMaxLen = (unsigned char)v4[2].hdr.next;
	memcpy(v2, (char *)&v4[2] + 1, dwMaxLen);
	mem_free_dbg(v4);
	return dwMaxLen;
}

void __fastcall tmsg_add(unsigned char *pbMsg, char bLen)
{
	char v2; // bl
	unsigned char *v3; // ebp
	size_t v4; // edi
	TMsg *v5; // eax
	TMsg *v6; // esi
	TMsg *v8; // ecx
	TMsg **v9; // eax

	v2 = bLen;
	v3 = pbMsg;
	v4 = (unsigned char)bLen;
	v5 = (TMsg *)DiabloAllocPtr((unsigned char)bLen + 12);
	v6 = v5;
	// *v5 = 0; /* fix */
	v6[2].hdr.next = v2;
	v6[1].hdr.next = GetTickCount() + 500;
	memcpy((char *)&v6[2] + 1, v3, v4);
	v8 = sgpTimedMsgHead;
	v9 = &sgpTimedMsgHead;
	/*while ( v8 )
	{
		v9 = (TMsg **)v8;
		v8 = (TMsg *)*v8;
	} fix */
	*v9 = v6;
}

void __cdecl tmsg_cleanup()
{
	TMsg *v0; // eax
	//TMsg *v1; // esi

	v0 = sgpTimedMsgHead;
	if ( sgpTimedMsgHead )
	{
		/* do
		{
			v1 = (TMsg *)*v0;
			sgpTimedMsgHead = 0;
			mem_free_dbg(v0);
			v0 = v1;
			sgpTimedMsgHead = v1;
		}
		while ( v1 ); fix */
	}
}
