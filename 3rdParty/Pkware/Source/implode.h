/*
PKWARE Data Compression Library (R) for Win32
Copyright 1994-95 PKWARE Inc.  All Rights Reserved.
*/

#ifdef __cplusplus
   extern "C" {
#endif

unsigned int implode(
   unsigned int (*read_buf)(char *buf, unsigned int *size, void *param),
   void         (*write_buf)(char *buf, unsigned int *size, void *param),
   char         *work_buf,
   void         *param,
   unsigned int *type,
   unsigned int *dsize);


unsigned int explode(
   unsigned int (*read_buf)(char *buf, unsigned  int *size, void *param),
   void         (*write_buf)(char *buf, unsigned  int *size, void *param),
   char         *work_buf,
   void         *param);

unsigned long crc32(char *buffer, unsigned int *size, unsigned long *old_crc);

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

