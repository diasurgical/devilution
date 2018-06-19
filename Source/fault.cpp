//HEADER_GOES_HERE

#include "../types.h"

LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter; // idb

//----- (004182AD) --------------------------------------------------------
struct exception_cpp_init
{
	exception_cpp_init()
	{
		exception_install_filter();
		j_exception_init_filter();
	}
} _exception_cpp_init;

//----- (004182B7) --------------------------------------------------------
void __cdecl exception_install_filter()
{
	exception_set_filter();
}

//----- (004182C1) --------------------------------------------------------
void __cdecl j_exception_init_filter()
{
	atexit(exception_init_filter);
}

//----- (004182CD) --------------------------------------------------------
void __cdecl exception_init_filter()
{
	exception_set_filter_ptr();
}

//----- (004182D7) --------------------------------------------------------
LONG __stdcall TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	PEXCEPTION_RECORD v1; // esi
	char *v2; // eax
	PCONTEXT v3; // esi
	LONG result; // eax
	CHAR v5[260]; // [esp+Ch] [ebp-210h]
	char String1[260]; // [esp+110h] [ebp-10Ch]
	int a5; // [esp+214h] [ebp-8h]
	int a4; // [esp+218h] [ebp-4h]

	log_dump_computer_info();
	v1 = ExceptionInfo->ExceptionRecord;
	v2 = exception_get_error_type(ExceptionInfo->ExceptionRecord->ExceptionCode, v5, 0x104u);
	log_printf("Exception code: %08X %s\r\n", v1->ExceptionCode, v2);
	exception_unknown_module(v1->ExceptionAddress, String1, 260, (int)&a4, (int)&a5);
	log_printf("Fault address:\t%08X %02X:%08X %s\r\n", v1->ExceptionAddress, a4, a5, String1);
	v3 = ExceptionInfo->ContextRecord;
	log_printf("\r\nRegisters:\r\n");
	log_printf(
		"EAX:%08X\r\nEBX:%08X\r\nECX:%08X\r\nEDX:%08X\r\nESI:%08X\r\nEDI:%08X\r\n",
		v3->Eax,
		v3->Ebx,
		v3->Ecx,
		v3->Edx,
		v3->Esi,
		v3->Edi);
	log_printf("CS:EIP:%04X:%08X\r\n", v3->SegCs, v3->Eip);
	log_printf("SS:ESP:%04X:%08X EBP:%08X\r\n", v3->SegSs, v3->Esp, v3->Ebp);
	log_printf("DS:%04X ES:%04X FS:%04X GS:%04X\r\n", v3->SegDs, v3->SegEs, v3->SegFs, v3->SegGs);
	log_printf("Flags:%08X\r\n", v3->EFlags);
	exception_call_stack((void *)v3->Eip, (LPVOID)v3->Ebp);
	log_printf("Stack bytes:\r\n");
	exception_hex_format((char *)v3->Esp, 0);
	log_printf("Code bytes:\r\n");
	exception_hex_format((char *)v3->Eip, 16);
	log_printf("\r\n");
	log_flush(1);
	if ( lpTopLevelExceptionFilter )
		result = lpTopLevelExceptionFilter(ExceptionInfo);
	else
		result = 0;
	return result;
}

//----- (00418455) --------------------------------------------------------
void __fastcall exception_hex_format(char *a1, char a2)
{
	unsigned int v2; // ebp
	char *v3; // edi
	unsigned int v4; // ebx
	unsigned int v5; // esi
	char *v6; // eax
	int v7; // ST04_4
	unsigned int v8; // esi
	unsigned char v9; // al

	v2 = a2;
	v3 = a1;
	if ( a2 )
	{
		do
		{
			v4 = 16;
			if ( v2 < 0x10 )
				v4 = v2;
			if ( IsBadReadPtr(v3, v4) )
				break;
			log_printf("0x%08x: ");
			v5 = 0;
			do
			{
				v6 = "%02x ";
				if ( v5 >= v4 )
					v6 = "   ";
				v7 = (unsigned char)v3[v5];
				log_printf(v6);
				if ( (v5 & 3) == 3 )
					log_printf(" ");
				++v5;
			}
			while ( v5 < 0x10 );
			v8 = 0;
			if ( v4 )
			{
				do
				{
					if ( isprint((unsigned char)v3[v8]) )
						v9 = v3[v8];
					else
						v9 = 46;
					log_printf("%c", v9);
					++v8;
				}
				while ( v8 < v4 );
			}
			log_printf("\r\n");
			v3 += v4;
			v2 -= v4;
		}
		while ( v2 );
	}
	log_printf("\r\n");
}

//----- (00418518) --------------------------------------------------------
void __fastcall exception_unknown_module(LPCVOID lpAddress, LPSTR lpString1, int iMaxLength, int a4, int a5)
{
	int v6; // eax
	char *v7; // eax
	unsigned int v8; // edi
	unsigned int v9; // esi
	char *v10; // eax
	int v11; // edx
	unsigned int v12; // ecx
	struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+Ch] [ebp-24h]
	LPSTR lpFilename; // [esp+28h] [ebp-8h]
	HMODULE hModule; // [esp+2Ch] [ebp-4h]
	unsigned int iMaxLengtha; // [esp+38h] [ebp+8h]

	lpFilename = lpString1;
	lstrcpynA(lpString1, "*unknown*", iMaxLength);
	*(_DWORD *)a4 = 0;
	*(_DWORD *)a5 = 0;
	if ( VirtualQuery(lpAddress, &Buffer, 0x1Cu) )
	{
		hModule = (HMODULE)Buffer.AllocationBase;
		if ( !Buffer.AllocationBase )
			hModule = GetModuleHandleA(0);
		if ( GetModuleFileNameA(hModule, lpFilename, iMaxLength) )
		{
			if ( hModule )
			{
				if ( *(_WORD *)hModule == 'ZM' )
				{
					v6 = *((_DWORD *)hModule + 15);
					if ( v6 )
					{
						v7 = (char *)hModule + v6;
						if ( *(_DWORD *)v7 == 'EP' )
						{
							v8 = *((unsigned __int16 *)v7 + 3);
							iMaxLengtha = 0;
							v9 = (_BYTE *)lpAddress - (_BYTE *)hModule;
							if ( *((_WORD *)v7 + 3) )
							{
								v10 = &v7[*((unsigned __int16 *)v7 + 10) + 40];
								while ( 1 )
								{
									v11 = *(_DWORD *)v10;
									v12 = *((_DWORD *)v10 - 1);
									if ( *(_DWORD *)v10 <= *((_DWORD *)v10 - 2) )
										v11 = *((_DWORD *)v10 - 2);
									if ( v9 >= v12 && v9 <= v12 + v11 )
										break;
									++iMaxLengtha;
									v10 += 40;
									if ( iMaxLengtha >= v8 )
										return;
								}
								*(_DWORD *)a4 = iMaxLengtha + 1;
								*(_DWORD *)a5 = v9 - v12;
							}
						}
					}
				}
			}
		}
		else
		{
			lstrcpynA(lpFilename, "*unknown*", iMaxLength);
		}
	}
}

//----- (004185FF) --------------------------------------------------------
void __fastcall exception_call_stack(void *a1, LPVOID lp)
{
	_DWORD *v2; // ebx
	void *v3; // edi
	_DWORD *v4; // eax
	char String1[260]; // [esp+Ch] [ebp-10Ch]
	int a5; // [esp+110h] [ebp-8h]
	int a4; // [esp+114h] [ebp-4h]

	v2 = (unsigned int *)lp;
	v3 = a1;
	log_printf("Call stack:\r\nAddress  Frame    Logical addr  Module\r\n");
	do
	{
		exception_unknown_module(v3, String1, 260, (int)&a4, (int)&a5);
		log_printf("%08X %08X %04X:%08X %s\r\n", v3, v2, a4, a5, String1);
		if ( IsBadWritePtr(v2, 8u) )
			break;
		v3 = (void *)v2[1];
		v4 = v2;
		v2 = (_DWORD *)*v2;
		if ( (unsigned char)v2 & 3 )
			break;
	}
	while ( v2 > v4 && !IsBadWritePtr(v2, 8u) );
	log_printf("\r\n");
}

//----- (00418688) --------------------------------------------------------
char *__fastcall exception_get_error_type(DWORD dwMessageId, LPSTR lpString1, DWORD nSize)
{
	CHAR *v3; // esi
	const CHAR *v4; // eax
	CHAR *v5; // ST10_4
	DWORD v6; // ST08_4
	HMODULE v7; // eax

	v3 = lpString1;
	if ( dwMessageId > EXCEPTION_FLT_DENORMAL_OPERAND )
	{
		if ( dwMessageId <= EXCEPTION_STACK_OVERFLOW )
		{
			if ( dwMessageId == EXCEPTION_STACK_OVERFLOW )
			{
				v4 = "STACK_OVERFLOW";
				goto LABEL_42;
			}
			switch ( dwMessageId )
			{
				case EXCEPTION_FLT_DIVIDE_BY_ZERO:
					v4 = "FLT_DIVIDE_BY_ZERO";
					goto LABEL_42;
				case EXCEPTION_FLT_INEXACT_RESULT:
					v4 = "FLT_INEXACT_RESULT";
					goto LABEL_42;
				case EXCEPTION_FLT_INVALID_OPERATION:
					v4 = "FLT_INVALID_OPERATION";
					goto LABEL_42;
				case EXCEPTION_FLT_OVERFLOW:
					v4 = "FLT_OVERFLOW";
					goto LABEL_42;
				case EXCEPTION_FLT_STACK_CHECK:
					v4 = "FLT_STACK_CHECK";
					goto LABEL_42;
				case EXCEPTION_FLT_UNDERFLOW:
					v4 = "FLT_UNDERFLOW";
					goto LABEL_42;
				case EXCEPTION_INT_DIVIDE_BY_ZERO:
					v4 = "INT_DIVIDE_BY_ZERO";
					goto LABEL_42;
				case EXCEPTION_INT_OVERFLOW:
					v4 = "INT_OVERFLOW";
					goto LABEL_42;
				case EXCEPTION_PRIV_INSTRUCTION:
					v4 = "PRIV_INSTRUCTION";
					goto LABEL_42;
				default:
					break;
			}
		}
	}
	else
	{
		if ( dwMessageId == EXCEPTION_FLT_DENORMAL_OPERAND )
		{
			v4 = "FLT_DENORMAL_OPERAND";
			goto LABEL_42;
		}
		if ( dwMessageId > EXCEPTION_IN_PAGE_ERROR )
		{
			switch ( dwMessageId )
			{
				case EXCEPTION_INVALID_HANDLE:
					v4 = "INVALID_HANDLE";
					goto LABEL_42;
				case EXCEPTION_ILLEGAL_INSTRUCTION:
					v4 = "ILLEGAL_INSTRUCTION";
					goto LABEL_42;
				case EXCEPTION_NONCONTINUABLE_EXCEPTION:
					v4 = "NONCONTINUABLE_EXCEPTION";
					goto LABEL_42;
				case EXCEPTION_INVALID_DISPOSITION:
					v4 = "INVALID_DISPOSITION";
					goto LABEL_42;
				case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
					v4 = "ARRAY_BOUNDS_EXCEEDED";
					goto LABEL_42;
			}
		}
		else
		{
			switch ( dwMessageId )
			{
				case EXCEPTION_IN_PAGE_ERROR:
					v4 = "IN_PAGE_ERROR";
					goto LABEL_42;
				case EXCEPTION_GUARD_PAGE:
					v4 = "GUARD_PAGE";
					goto LABEL_42;
				case EXCEPTION_DATATYPE_MISALIGNMENT:
					v4 = "DATATYPE_MISALIGNMENT";
					goto LABEL_42;
				case EXCEPTION_BREAKPOINT:
					v4 = "BREAKPOINT";
					goto LABEL_42;
				case EXCEPTION_SINGLE_STEP:
					v4 = "SINGLE_STEP";
					goto LABEL_42;
				case EXCEPTION_ACCESS_VIOLATION:
					v4 = "ACCESS_VIOLATION";
LABEL_42:
					lstrcpynA(v3, v4, nSize);
					return v3;
			}
		}
	}
	v5 = lpString1;
	v6 = dwMessageId;
	v7 = GetModuleHandleA("NTDLL.DLL");
	if ( !FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE|FORMAT_MESSAGE_IGNORE_INSERTS, v7, v6, 0, v5, nSize, NULL) )
	{
		v4 = "*unknown*";
		goto LABEL_42;
	}
	return v3;
}

//----- (0041883C) --------------------------------------------------------
void __fastcall exception_set_filter()
{
	lpTopLevelExceptionFilter = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)TopLevelExceptionFilter);
}

//----- (00418853) --------------------------------------------------------
LPTOP_LEVEL_EXCEPTION_FILTER __cdecl exception_set_filter_ptr()
{
	return SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}

//----- (00418860) --------------------------------------------------------
LPTOP_LEVEL_EXCEPTION_FILTER __cdecl exception_get_filter()
{
	return lpTopLevelExceptionFilter;
}
