//HEADER_GOES_HERE

//fault
//int dword_52B9F4;
extern LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter; // idb

void __cdecl exception_cpp_init();
void __cdecl exception_install_filter();
void __cdecl j_exception_init_filter();
void __cdecl exception_init_filter();
LONG __stdcall TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo);
void __fastcall exception_hex_format(char *a1, char a2);
void __fastcall exception_unknown_module(LPCVOID lpAddress, LPSTR lpString1, int iMaxLength, int a4, int a5);
void __fastcall exception_call_stack(void *a1, LPVOID lp);
char *__fastcall exception_get_error_type(DWORD dwMessageId, LPSTR lpString1, DWORD nSize);
void __fastcall exception_set_filter();
LPTOP_LEVEL_EXCEPTION_FILTER __cdecl exception_set_filter_ptr();
LPTOP_LEVEL_EXCEPTION_FILTER __cdecl exception_get_filter();