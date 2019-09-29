/**
 * @file objdat.h
 *
 * Interface of all object data.
 */
#ifndef __OBJDAT_H__
#define __OBJDAT_H__

extern int ObjTypeConv[];
extern ObjDataStruct AllObjects[];
extern const char *const ObjMasterLoadList[];
#ifdef HELLFIRE
extern char *ObjCryptLoadList[];
extern char *ObjHiveLoadList[];
#endif

#endif /* __OBJDAT_H__ */
