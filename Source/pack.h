/**
 * @file pack.h
 *
 * Interface of functions for minifying player data structure.
 */
#ifndef __PACK_H__
#define __PACK_H__

void PackPlayer(PkPlayerStruct *pPack, int pnum, BOOL manashield);
void VerifyGoldSeeds(PlayerStruct *pPlayer);
void UnPackPlayer(PkPlayerStruct *pPack, int pnum, BOOL killok);

/* rdata */

#endif /* __PACK_H__ */
