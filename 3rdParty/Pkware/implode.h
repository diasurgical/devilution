/***************************************************************
 PKWARE Data Compression Library (R) for Win32
 Copyright 1991,1992,1994,1995 PKWARE Inc.  All Rights Reserved.
 PKWARE Data Compression Library Reg. U.S. Pat. and Tm. Off.
***************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

unsigned int __cdecl implode(
   unsigned int (__cdecl *read_buf)(char *buf, unsigned int *size, void *param),
   void         (__cdecl *write_buf)(char *buf, unsigned int *size, void *param),
   char         *work_buf,
   void         *param,
   unsigned int *type,
   unsigned int *dsize);


unsigned int __cdecl explode(
   unsigned int (__cdecl *read_buf)(char *buf, unsigned  int *size, void *param),
   void         (__cdecl *write_buf)(char *buf, unsigned  int *size, void *param),
   char         *work_buf,
   void         *param);

unsigned long __cdecl crc32(char *buffer, unsigned int *size, unsigned long *old_crc);

#ifdef __cplusplus
   }                         // End of 'extern "C"' declaration
#endif


#define CMP_BUFFER_SIZE    36312
#define EXP_BUFFER_SIZE    12596

#define CMP_BINARY             0
#define CMP_ASCII              1

#define CMP_NO_ERROR           0
#define CMP_INVALID_DICTSIZE   1
#define CMP_INVALID_MODE       2
#define CMP_BAD_DATA           3
#define CMP_ABORT              4

