//HEADER_GOES_HERE
#ifndef __SETMAPS_H__
#define __SETMAPS_H__

int ObjIndex(int x, int y);
void AddSKingObjs();
void AddSChamObjs();
void AddVileObjs();
void DRLG_SetMapTrans(char *sFileName);
void LoadSetMap();

/* rdata */
extern unsigned char SkelKingTrans1[8];
extern unsigned char SkelKingTrans2[8];
extern unsigned char SkelKingTrans3[20];
extern unsigned char SkelKingTrans4[28];
extern unsigned char SkelChamTrans1[20];
extern unsigned char SkelChamTrans2[8];
extern unsigned char SkelChamTrans3[36];
extern char *quest_level_names[];

#endif /* __SETMAPS_H__ */
