/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

int __fastcall GetManaAmount(int id, int sn);
void __fastcall UseMana(int id, int sn);
bool __fastcall CheckSpell(int id, int sn, char st, bool manaonly);
void __fastcall CastSpell(int id, int spl, int sx, int sy, int dx, int dy, int caster, int spllvl);
void __fastcall DoResurrect(int pnum, int rid);
void __fastcall PlacePlayer(int pnum);
void __fastcall DoHealOther(int pnum, int rid);

/* rdata */

extern SpellData spelldata[37];
