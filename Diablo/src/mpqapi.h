/**
 * @file mpqapi.h
 *
 * Interface of functions for creating and editing MPQ files.
 */
#ifndef __MPQAPI_H__
#define __MPQAPI_H__

void mpqapi_store_default_time(DWORD dwChar);
void mpqapi_remove_hash_entry(const char *pszName);
void mpqapi_remove_hash_entries(BOOL(__stdcall *fnGetName)(DWORD, char *));
BOOL mpqapi_write_file(const char *pszName, const BYTE *pbData, DWORD dwLen);
void mpqapi_rename(char *pszOld, char *pszNew);
BOOL mpqapi_has_file(const char *pszName);
BOOL OpenMPQ(const char *pszArchive, BOOL hidden, DWORD dwChar);
BOOL mpqapi_flush_and_close(const char *pszArchive, BOOL bFree, DWORD dwChar);

#endif /* __MPQAPI_H__ */
