//HEADER_GOES_HERE
#ifndef __SPELLS_H__
#define __SPELLS_H__

int __fastcall GetManaAmount(int id, int sn);
void __fastcall UseMana(int id, int sn);
bool __fastcall CheckSpell(int id, int sn, char st, bool manaonly);
void __fastcall CastSpell(int id, int spl, int sx, int sy, int dx, int dy, int caster, int spllvl);
void __fastcall DoResurrect(int pnum, int rid);
void __fastcall PlacePlayer(int pnum);
void __fastcall DoHealOther(int pnum, int rid);

/* rdata */

extern SpellData spelldata[37];

#endif /* __SPELLS_H__ */
