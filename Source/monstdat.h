//HEADER_GOES_HERE
#ifndef __MONSTDAT_H__
#define __MONSTDAT_H__

extern MonsterData monsterdata[];
extern char MonstConvTbl[128];
#ifdef HELLFIRE
extern int MonstAvailTbl[];
#else
extern BYTE MonstAvailTbl[];
#endif
extern UniqMonstStruct UniqMonst[];

#endif /* __MONSTDAT_H__ */
