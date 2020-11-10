/**
 * @file monstdat.h
 *
 * Interface of all monster data.
 */
#ifndef __MONSTDAT_H__
#define __MONSTDAT_H__

extern MonsterData monsterdata[];
#ifdef HELLFIRE
extern int MonstConvTbl[];
extern int MonstAvailTbl[];
#else
extern char MonstConvTbl[];
extern char MonstAvailTbl[];
#endif
extern UniqMonstStruct UniqMonst[];

#endif /* __MONSTDAT_H__ */
