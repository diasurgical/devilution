/**
 * @file sync.h
 *
 * Interface of functionality for syncing game state with other players.
 */
#ifndef __SYNC_H__
#define __SYNC_H__

DWORD sync_all_monsters(const BYTE *pbBuf, DWORD dwMaxLen);
DWORD sync_update(int pnum, const BYTE *pbBuf);
void sync_init();

#endif /* __SYNC_H__ */
