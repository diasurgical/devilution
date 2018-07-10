//HEADER_GOES_HERE

#include "../types.h"

SpellData spelldata[37] =
{
	{ SPL_NULL,		0,   STYPE_FIRE,	  NULL,			  NULL,			 0,  0,  0, 0, 0,   0,		{ 0,			   0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_FIREBOLT,	6,   STYPE_FIRE,	  "Firebolt",		"Firebolt",	   1,  1,  1, 0, 15,  IS_CAST2, { MIS_FIREBOLT,	0,		  0 }, 1, 3,   40, 80, 1000,  50 },
	{ SPL_HEAL,		5,   STYPE_MAGIC,	 "Healing",		 NULL,			 1,  1,  0, 1, 17,  IS_CAST8, { MIS_HEAL,		0,		  0 }, 3, 1,   20, 40, 1000,  50 },
	{ SPL_LIGHTNING,   10,  STYPE_LIGHTNING, "Lightning",	   NULL,			 4,  3,  1, 0, 20,  IS_CAST4, { MIS_LIGHTCTRL,   0,		  0 }, 1, 6,   20, 60, 3000,  150 },
	{ SPL_FLASH,	   30,  STYPE_LIGHTNING, "Flash",		   NULL,			 5,  4,  0, 0, 33,  IS_CAST4, { MIS_FLASH,	   MIS_FLASH2, 0 }, 2, 16,  20, 40, 7500,  500 },
	{ SPL_IDENTIFY,	13,  STYPE_MAGIC,	 "Identify",		"Identify",	   -1, -1, 0, 1, 23,  IS_CAST6, { MIS_IDENTIFY,	0,		  0 }, 2, 1,   8,  12, 0,	 100 },
	{ SPL_FIREWALL,	28,  STYPE_FIRE,	  "Fire Wall",	   NULL,			 3,  2,  1, 0, 27,  IS_CAST2, { MIS_FIREWALLC,   0,		  0 }, 2, 16,  8,  16, 6000,  400 },
	{ SPL_TOWN,		35,  STYPE_MAGIC,	 "Town Portal",	 NULL,			 3,  3,  1, 0, 20,  IS_CAST6, { MIS_TOWN,		0,		  0 }, 3, 18,  8,  12, 3000,  200 },
	{ SPL_STONE,	   60,  STYPE_MAGIC,	 "Stone Curse",	 NULL,			 6,  5,  1, 0, 51,  IS_CAST2, { MIS_STONE,	   0,		  0 }, 3, 40,  8,  16, 12000, 800 },
	{ SPL_INFRA,	   40,  STYPE_MAGIC,	 "Infravision",	 NULL,			 -1, -1, 0, 0, 36,  IS_CAST8, { MIS_INFRA,	   0,		  0 }, 5, 20,  0,  0,  0,	 600 },
	{ SPL_RNDTELEPORT, 12,  STYPE_MAGIC,	 "Phasing",		 NULL,			 7,  6,  0, 0, 39,  IS_CAST2, { MIS_RNDTELEPORT, 0,		  0 }, 2, 4,   40, 80, 3500,  200 },
	{ SPL_MANASHIELD,  33,  STYPE_MAGIC,	 "Mana Shield",	 NULL,			 6,  5,  0, 0, 25,  IS_CAST2, { MIS_MANASHIELD,  0,		  0 }, 0, 33,  4,  10, 16000, 1200 },
	{ SPL_FIREBALL,	16,  STYPE_FIRE,	  "Fireball",		NULL,			 8,  7,  1, 0, 48,  IS_CAST2, { MIS_FIREBALL,	0,		  0 }, 1, 10,  40, 80, 8000,  300 },
	{ SPL_GUARDIAN,	50,  STYPE_FIRE,	  "Guardian",		NULL,			 9,  8,  1, 0, 61,  IS_CAST2, { MIS_GUARDIAN,	0,		  0 }, 2, 30,  16, 32, 14000, 950 },
	{ SPL_CHAIN,	   30,  STYPE_LIGHTNING, "Chain Lightning", NULL,			 8,  7,  0, 0, 54,  IS_CAST2, { MIS_CHAIN,	   0,		  0 }, 1, 18,  20, 60, 11000, 750 },
	{ SPL_WAVE,		35,  STYPE_FIRE,	  "Flame Wave",	  NULL,			 9,  8,  1, 0, 54,  IS_CAST2, { MIS_WAVE,		0,		  0 }, 3, 20,  20, 40, 10000, 650 },
	{ SPL_DOOMSERP,	0,   STYPE_LIGHTNING, "Doom Serpents",   NULL,			 -1, -1, 0, 0, 0,   IS_CAST2, { 0,			   0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_BLODRIT,	 0,   STYPE_MAGIC,	 "Blood Ritual",	NULL,			 -1, -1, 0, 0, 0,   IS_CAST2, { 0,			   0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_NOVA,		60,  STYPE_MAGIC,	 "Nova",			NULL,			 -1, 10, 0, 0, 87,  IS_CAST4, { MIS_NOVA,		0,		  0 }, 3, 35,  16, 32, 21000, 1300 },
	{ SPL_INVISIBIL,   0,   STYPE_MAGIC,	 "Invisibility",	NULL,			 -1, -1, 0, 0, 0,   IS_CAST2, { 0,			   0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_FLAME,	   11,  STYPE_FIRE,	  "Inferno",		 NULL,			 3,  2,  1, 0, 20,  IS_CAST2, { MIS_FLAMEC,	  0,		  0 }, 1, 6,   20, 40, 2000,  100 },
	{ SPL_GOLEM,	   100, STYPE_FIRE,	  "Golem",		   NULL,			 11, 9,  0, 0, 81,  IS_CAST2, { MIS_GOLEM,	   0,		  0 }, 6, 60,  16, 32, 18000, 1100 },
	{ SPL_BLODBOIL,	0,   STYPE_LIGHTNING, "Blood Boil",	  NULL,			 -1, -1, 1, 0, 0,   IS_CAST8, { 0,			   0,		  0 }, 0, 0,   0,  0,  0,	 0 },
	{ SPL_TELEPORT,	35,  STYPE_MAGIC,	 "Teleport",		NULL,			 14, 12, 1, 0, 105, IS_CAST6, { MIS_TELEPORT,	0,		  0 }, 3, 15,  16, 32, 20000, 1250 },
	{ SPL_APOCA,	   150, STYPE_FIRE,	  "Apocalypse",	  NULL,			 -1, 15, 0, 0, 149, IS_CAST2, { MIS_APOCA,	   0,		  0 }, 6, 90,  8,  12, 30000, 2000 },
	{ SPL_ETHEREALIZE, 100, STYPE_MAGIC,	 "Etherealize",	 NULL,			 -1, -1, 0, 0, 93,  IS_CAST2, { MIS_ETHEREALIZE, 0,		  0 }, 0, 100, 2,  6,  26000, 1600 },
	{ SPL_REPAIR,	  0,   STYPE_MAGIC,	 "Item Repair",	 "Item Repair",	-1, -1, 0, 1, -1,  IS_CAST6, { MIS_REPAIR,	  0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_RECHARGE,	0,   STYPE_MAGIC,	 "Staff Recharge",  "Staff Recharge", -1, -1, 0, 1, -1,  IS_CAST6, { MIS_RECHARGE,	0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_DISARM,	  0,   STYPE_MAGIC,	 "Trap Disarm",	 "Trap Disarm",	-1, -1, 0, 0, -1,  IS_CAST6, { MIS_DISARM,	  0,		  0 }, 0, 0,   40, 80, 0,	 0 },
	{ SPL_ELEMENT,	 35,  STYPE_FIRE,	  "Elemental",	   NULL,			 8,  6,  0, 0, 68,  IS_CAST2, { MIS_ELEMENT,	 0,		  0 }, 2, 20,  20, 60, 10500, 700 },
	{ SPL_CBOLT,	   6,   STYPE_LIGHTNING, "Charged Bolt",	NULL,			 1,  1,  1, 0, 25,  IS_CAST2, { MIS_CBOLT,	   0,		  0 }, 1, 6,   40, 80, 1000,  50 },
	{ SPL_HBOLT,	   7,   STYPE_MAGIC,	 "Holy Bolt",	   NULL,			 1,  1,  1, 0, 20,  IS_CAST2, { MIS_HBOLT,	   0,		  0 }, 1, 3,   40, 80, 1000,  50 },
	{ SPL_RESURRECT,   20,  STYPE_MAGIC,	 "Resurrect",	   NULL,			 -1, 5,  0, 1, 30,  IS_CAST8, { MIS_RESURRECT,   0,		  0 }, 0, 20,  4,  10, 4000,  250 },
	{ SPL_TELEKINESIS, 15,  STYPE_MAGIC,	 "Telekinesis",	 NULL,			 2,  2,  0, 0, 33,  IS_CAST2, { MIS_TELEKINESIS, 0,		  0 }, 2, 8,   20, 40, 2500,  200 },
	{ SPL_HEALOTHER,   5,   STYPE_MAGIC,	 "Heal Other",	  NULL,			 1,  1,  0, 1, 17,  IS_CAST8, { MIS_HEALOTHER,   0,		  0 }, 3, 1,   20, 40, 1000,  50 },
	{ SPL_FLARE,	   25,  STYPE_MAGIC,	 "Blood Star",	  NULL,			 14, 13, 0, 0, 70,  IS_CAST2, { MIS_FLARE,	   0,		  0 }, 2, 14,  20, 60, 27500, 1800 },
	{ SPL_BONESPIRIT,  24,  STYPE_MAGIC,	 "Bone Spirit",	 NULL,			 9,  7,  0, 0, 34,  IS_CAST2, { MIS_BONESPIRIT,  0,		  0 }, 1, 12,  20, 60, 11500, 800 }
};

int __fastcall GetManaAmount(int player_index, int spell_number)
{
	int spLvlManaAdjust; // esi
	int spellLevel; // ecx
	int rawManaCost; // ecx
	int manaCost; // ecx

	spLvlManaAdjust = 0;
	spellLevel = plr[player_index]._pSplLvl[spell_number] + plr[player_index]._pISplLvlAdd - 1;
	if (spellLevel < 0)
		spellLevel = 0;

	if ( spellLevel > 0 )
		spLvlManaAdjust = spellLevel * spelldata[spell_number].sManaAdj;
	if ( spell_number == SPL_FIREBOLT )
		spLvlManaAdjust >>= 1;
	if ( spell_number == SPL_RESURRECT && spellLevel > 0 )
		spLvlManaAdjust = spellLevel * (spelldata[SPL_RESURRECT].sManaCost / 8);

	if (spelldata[spell_number].sManaCost == 255 )
		rawManaCost = (unsigned char)plr[player_index]._pMaxManaBase;
	else
		rawManaCost = spelldata[spell_number].sManaCost;

	manaCost = (rawManaCost - spLvlManaAdjust) << 6;

	if ( spell_number == SPL_HEAL )
		manaCost = (spelldata[SPL_HEAL].sManaCost + 2 * plr[player_index]._pLevel - spLvlManaAdjust) << 6;
	if ( spell_number == SPL_HEALOTHER )
		manaCost = (spelldata[SPL_HEAL].sManaCost + 2 * plr[player_index]._pLevel - spLvlManaAdjust) << 6;

	if ( plr[player_index]._pClass == 1 )
		manaCost -= manaCost >> 2;

	if (spelldata[spell_number].sMinMana > manaCost >> 6 )
		manaCost = spelldata[spell_number].sMinMana << 6;

	return manaCost * (100 - plr[player_index]._pISplCost) / 100;
}

void __fastcall UseMana(int id, int sn)
{
	int v2; // esi
	int v3; // eax

	if ( id == myplr )
	{
		v2 = id;
		switch ( plr[id]._pSplType )
		{
			case RSPLTYPE_SPELL:
#ifdef _DEBUG
				if ( !debug_mode_key_inverted_v )
				{
#endif
					v3 = GetManaAmount(id, sn);
					plr[v2]._pMana -= v3;
					plr[v2]._pManaBase -= v3;
					drawmanaflag = 1;
#ifdef _DEBUG
				}
#endif
				break;
			case RSPLTYPE_SCROLL:
				RemoveScroll(id);
				break;
			case RSPLTYPE_CHARGES:
				UseStaffCharge(id);
				break;
		}
	}
}

bool __fastcall CheckSpell(int id, int sn, char st, bool manaonly)
{
	bool result; // al
	int v5; // edi
	int v6; // esi

	result = 1;
	v5 = sn;
	v6 = id;
#ifdef _DEBUG
	if ( debug_mode_key_inverted_v )
		return 1;
#endif
	if ( !manaonly && pcurs != 1 )
		return 0;
	if ( st )
	{
		if ( GetSpellLevel(id, sn) <= 0 )
			return 0;
		result = plr[v6]._pMana >= GetManaAmount(v6, v5);
	}
	return result;
}

void __fastcall CastSpell(int id, int spl, int sx, int sy, int dx, int dy, int caster, int spllvl)
{
	int v8; // eax
	signed int v9; // edi
	unsigned char *v10; // esi
	int v11; // esi
	int midir; // [esp+8h] [ebp-8h]
	int ids; // [esp+Ch] [ebp-4h]

	ids = id;
	if ( caster )
	{
		if ( caster != 1 )
			goto LABEL_7;
		v8 = monster[id]._mdir;
	}
	else
	{
		caster = 0;
		midir = plr[id]._pdir;
		if ( spl != SPL_FIREWALL )
			goto LABEL_7;
		v8 = plr[id]._pVar3;
	}
	midir = v8;
LABEL_7:
	v9 = 0;
	v10 = spelldata[spl].sMissiles;
	if ( *v10 )
	{
		do
		{
			if ( v9 >= 3 )
				break;
			AddMissile(sx, sy, dx, dy, midir, (unsigned char)v10[v9++], caster, ids, 0, spllvl);
		}
		while ( v10[v9] );
	}
	if ( *v10 == MIS_TOWN )
		UseMana(ids, SPL_TOWN);
	if ( *v10 == MIS_CBOLT )
	{
		UseMana(ids, SPL_CBOLT);
		if ( (spllvl >> 1) + 3 > 0 )
		{
			v11 = (spllvl >> 1) + 3;
			do
			{
				AddMissile(sx, sy, dx, dy, midir, MIS_CBOLT, caster, ids, 0, spllvl);
				--v11;
			}
			while ( v11 );
		}
	}
}

void __fastcall DoResurrect(int pnum, int rid)
{
	int v2; // ebx
	int v3; // esi
	int v4; // esi
	signed int v5; // edx
	int v6; // eax

	v2 = rid;
	v3 = pnum;
	if ( (_BYTE)rid != LOBYTE(-1) )
		AddMissile(plr[rid].WorldX, plr[rid].WorldY, plr[rid].WorldX, plr[rid].WorldY, 0, MIS_RESURRECTBEAM, 0, pnum, 0, 0);
	if ( v3 == myplr )
		SetCursor(CURSOR_HAND);
	if ( (_BYTE)v2 != LOBYTE(-1) )
	{
		v4 = v2;
		if ( !plr[v2]._pHitPoints )
		{
			if ( v2 == myplr )
			{
				deathflag = 0;
				gamemenu_off();
				drawhpflag = 1;
				drawmanaflag = 1;
			}
			ClrPlrPath(v2);
			plr[v4].destAction = -1;
			plr[v4]._pInvincible = 0;
			PlacePlayer(v2);
			v5 = 640;
			if ( plr[v4]._pMaxHPBase < 640 )
				v5 = plr[v4]._pMaxHPBase;
			SetPlayerHitPoints(v2, v5);
			v6 = plr[v4]._pMaxHPBase - plr[v4]._pMaxHP;
			plr[v4]._pMana = 0;
			plr[v4]._pHPBase = plr[v4]._pHitPoints + v6;
			plr[v4]._pManaBase = plr[v4]._pMaxManaBase - plr[v4]._pMaxMana;
			CalcPlrInv(v2, 1u);
			if ( plr[v4].plrlevel == currlevel )
				StartStand(v2, plr[v4]._pdir);
			else
				plr[v4]._pmode = 0;
		}
	}
}

void __fastcall PlacePlayer(int pnum)
{
	int v1; // ebx
	unsigned int v2; // eax
	int v3; // edi
	int v4; // esi
	int v5; // eax
	bool v6; // zf
	signed int v7; // [esp+Ch] [ebp-18h]
	int p; // [esp+10h] [ebp-14h]
	int v9; // [esp+14h] [ebp-10h]
	signed int v10; // [esp+18h] [ebp-Ch]
	signed int v11; // [esp+1Ch] [ebp-8h]
	unsigned int i; // [esp+20h] [ebp-4h]
	signed int v13; // [esp+20h] [ebp-4h]

	p = pnum;
	v1 = pnum;
	if ( plr[pnum].plrlevel == currlevel )
	{
		v2 = 0;
		for ( i = 0; ; v2 = i )
		{
			v3 = plr[v1].WorldX + *(int *)((char *)plrxoff2 + v2);
			v4 = plr[v1].WorldY + *(int *)((char *)plryoff2 + v2);
			if ( PosOkPlayer(p, v3, v4) )
				break;
			i += 4;
			if ( i >= 0x20 )
				break;
		}
		if ( !PosOkPlayer(p, v3, v4) )
		{
			v11 = 0;
			v5 = -1;
			v13 = 1;
			v7 = -1;
			do
			{
				if ( v11 )
					break;
				v9 = v5;
				while ( v5 <= v13 && !v11 )
				{
					v4 = v9 + plr[v1].WorldY;
					v10 = v7;
					do
					{
						if ( v11 )
							break;
						v3 = v10 + plr[v1].WorldX;
						if ( PosOkPlayer(p, v10 + plr[v1].WorldX, v4) )
							v11 = 1;
						++v10;
					}
					while ( v10 <= v13 );
					v5 = ++v9;
				}
				++v13;
				v5 = v7-- - 1;
			}
			while ( v7 > -50 );
		}
		plr[v1].WorldX = v3;
		v6 = p == myplr;
		plr[v1].WorldY = v4;
		dPlayer[v3][v4] = p + 1;
		if ( v6 )
		{
			ViewX = v3;
			ViewY = v4;
		}
	}
}

void __fastcall DoHealOther(int pnum, int rid)
{
	int v2; // ebx
	int v3; // esi
	int v4; // ebx
	int v5; // ecx
	int v6; // edi
	int v7; // ecx
	char v8; // bl
	int v9; // eax
	int *v10; // eax
	int v11; // esi
	int id; // [esp+8h] [ebp-8h]
	int v13; // [esp+Ch] [ebp-4h]
	signed int v14; // [esp+Ch] [ebp-4h]
	int i; // [esp+Ch] [ebp-4h]

	v2 = pnum;
	v13 = rid;
	id = pnum;
	if ( pnum == myplr )
		SetCursor(CURSOR_HAND);
	if ( (_BYTE)v13 != LOBYTE(-1) )
	{
		v3 = v13;
		if ( (signed int)(plr[v13]._pHitPoints & 0xFFFFFFC0) > 0 )
		{
			_LOBYTE(pnum) = 57;
			v4 = v2;
			v14 = 0;
			v6 = (random(pnum, 10) + 1) << 6;
			if ( plr[v4]._pLevel > 0 )
			{
				do
				{
					_LOBYTE(v5) = 57;
					v6 += (random(v5, 4) + 1) << 6;
					++v14;
				}
				while ( v14 < plr[v4]._pLevel );
			}
			for ( i = 0; i < GetSpellLevel(id, SPL_HEALOTHER); ++i )
			{
				_LOBYTE(v7) = 57;
				v6 += (random(v7, 6) + 1) << 6;
			}
			v8 = plr[v4]._pClass;
			if ( !v8 )
				v6 *= 2;
			if ( v8 == 1 )
				v6 += v6 >> 1;
			plr[v3]._pHitPoints += v6;
			v9 = plr[v3]._pMaxHP;
			if ( plr[v3]._pHitPoints > v9 )
				plr[v3]._pHitPoints = v9;
			v10 = &plr[v3]._pHPBase;
			v11 = plr[v3]._pMaxHPBase;
			*v10 += v6;
			if ( *v10 > v11 )
				*v10 = v11;
			drawhpflag = 1;
		}
	}
}
