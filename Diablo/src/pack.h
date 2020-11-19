/**
 * @file pack.h
 *
 * Interface of functions for minifying player data structure.
 */
#ifndef __PACK_H__
#define __PACK_H__

void PackPlayer(PkPlayerStruct *pPack, int pnum, BOOL manashield);
void UnPackPlayer(PkPlayerStruct *pPack, int pnum, BOOL killok);
#ifdef HELLFIRE
void PackItem(PkItemStruct *id, ItemStruct *is);
void UnPackItem(PkItemStruct *is, ItemStruct *id);
#endif

/* rdata */

#endif /* __PACK_H__ */
