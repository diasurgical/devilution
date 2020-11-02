/**
 * @file fault.h
 *
 * Interface of exception logging functionality.
 */
#ifndef __FAULT_H__
#define __FAULT_H__

extern LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter;

LONG __stdcall TopLevelExceptionFilter(PEXCEPTION_POINTERS ExceptionInfo);
LPTOP_LEVEL_EXCEPTION_FILTER fault_get_filter();

#endif /* __FAULT_H__ */
