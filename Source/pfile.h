/**
 * @file pfile.h
 *
 * Interface of the save game encoding functionality.
 */
#ifndef __PFILE_H__
#define __PFILE_H__

extern BOOL gbValidSaveFile;

void pfile_init_save_directory();
void pfile_write_hero();
BOOL pfile_create_player_description(char *dst, DWORD len);
BOOL pfile_rename_hero(const char *name_1, const char *name_2);
void pfile_flush_W();
void game_2_ui_player(const PlayerStruct *p, _uiheroinfo *heroinfo, BOOL bHasSaveFile);
BOOL __stdcall pfile_ui_set_hero_infos(BOOL(__stdcall *ui_add_hero_info)(_uiheroinfo *));
BOOL pfile_archive_contains_game(HANDLE hsArchive, DWORD save_num);
BOOL __stdcall pfile_ui_set_class_stats(unsigned int player_class_nr, _uidefaultstats *class_stats);
BOOL __stdcall pfile_ui_save_create(_uiheroinfo *heroinfo);
BOOL __stdcall pfile_get_file_name(DWORD lvl, char *dst);
BOOL __stdcall pfile_delete_save(_uiheroinfo *hero_info);
void pfile_read_player_from_save();
void GetTempLevelNames(char *szTemp);
void GetPermLevelNames(char *szPerm);
void pfile_get_game_name(char *dst);
void pfile_remove_temp_files();
void pfile_rename_temp_to_perm();
void pfile_write_save_file(const char *pszName, BYTE *pbData, DWORD dwLen, DWORD qwLen);
void pfile_strcpy(char *dst, const char *src);
BYTE *pfile_read(const char *pszName, DWORD *pdwLen);
void pfile_update(BOOL force_save);

#endif /* __PFILE_H__ */
