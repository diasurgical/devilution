//HEADER_GOES_HERE
#ifndef __PACK_H__
#define __PACK_H__

#ifdef HELLFIRE
void PackPlayer(PkPlayerStruct *pPack, int pnum);
#else
void PackPlayer(PkPlayerStruct *pPack, int pnum, BOOL manashield);
#endif
void PackItem(PkItemStruct *id, ItemStruct *is);
void VerifyGoldSeeds(PlayerStruct *pPlayer);
void UnPackPlayer(PkPlayerStruct *pPack, int pnum, BOOL killok);
void UnPackItem(PkItemStruct *is, ItemStruct *id);

/* rdata */

#endif /* __PACK_H__ */
