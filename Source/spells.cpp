//HEADER_GOES_HERE

#include "../types.h"

SpellData spelldata[37] =
{
	{ 0,               0,   0,               NULL,              NULL,             0,  0,  0, 0, 0,   0,        { 0,               0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_FIREBOLT,    6,   STYPE_FIRE,      "Firebolt",        "Firebolt",       1,  1,  1, 0, 15,  IS_CAST2, { MIS_FIREBOLT,    0,          0 }, 1, 3,   40, 80, 1000,  50 },
	{ SPL_HEAL,        5,   STYPE_MAGIC,     "Healing",         NULL,             1,  1,  0, 1, 17,  IS_CAST8, { MIS_HEAL,        0,          0 }, 3, 1,   20, 40, 1000,  50 },
	{ SPL_LIGHTNING,   10,  STYPE_LIGHTNING, "Lightning",       NULL,             4,  3,  1, 0, 20,  IS_CAST4, { MIS_LIGHTCTRL,   0,          0 }, 1, 6,   20, 60, 3000,  150 },
	{ SPL_FLASH,       30,  STYPE_LIGHTNING, "Flash",           NULL,             5,  4,  0, 0, 33,  IS_CAST4, { MIS_FLASH,       MIS_FLASH2, 0 }, 2, 16,  20, 40, 7500,  500 },
	{ SPL_IDENTIFY,    13,  STYPE_MAGIC,     "Identify",        "Identify",       -1, -1, 0, 1, 23,  IS_CAST6, { MIS_IDENTIFY,    0,          0 }, 2, 1,   8,  12, 0,     100 },
	{ SPL_FIREWALL,    28,  STYPE_FIRE,      "Fire Wall",       NULL,             3,  2,  1, 0, 27,  IS_CAST2, { MIS_FIREWALLC,   0,          0 }, 2, 16,  8,  16, 6000,  400 },
	{ SPL_TOWN,        35,  STYPE_MAGIC,     "Town Portal",     NULL,             3,  3,  1, 0, 20,  IS_CAST6, { MIS_TOWN,        0,          0 }, 3, 18,  8,  12, 3000,  200 },
	{ SPL_STONE,       60,  STYPE_MAGIC,     "Stone Curse",     NULL,             6,  5,  1, 0, 51,  IS_CAST2, { MIS_STONE,       0,          0 }, 3, 40,  8,  16, 12000, 800 },
	{ SPL_INFRA,       40,  STYPE_MAGIC,     "Infravision",     NULL,             -1, -1, 0, 0, 36,  IS_CAST8, { MIS_INFRA,       0,          0 }, 5, 20,  0,  0,  0,     600 },
	{ SPL_RNDTELEPORT, 12,  STYPE_MAGIC,     "Phasing",         NULL,             7,  6,  0, 0, 39,  IS_CAST2, { MIS_RNDTELEPORT, 0,          0 }, 2, 4,   40, 80, 3500,  200 },
	{ SPL_MANASHIELD,  33,  STYPE_MAGIC,     "Mana Shield",     NULL,             6,  5,  0, 0, 25,  IS_CAST2, { MIS_MANASHIELD,  0,          0 }, 0, 33,  4,  10, 16000, 1200 },
	{ SPL_FIREBALL,    16,  STYPE_FIRE,      "Fireball",        NULL,             8,  7,  1, 0, 48,  IS_CAST2, { MIS_FIREBALL,    0,          0 }, 1, 10,  40, 80, 8000,  300 },
	{ SPL_GUARDIAN,    50,  STYPE_FIRE,      "Guardian",        NULL,             9,  8,  1, 0, 61,  IS_CAST2, { MIS_GUARDIAN,    0,          0 }, 2, 30,  16, 32, 14000, 950 },
	{ SPL_CHAIN,       30,  STYPE_LIGHTNING, "Chain Lightning", NULL,             8,  7,  0, 0, 54,  IS_CAST2, { MIS_CHAIN,       0,          0 }, 1, 18,  20, 60, 11000, 750 },
	{ SPL_WAVE,        35,  STYPE_FIRE,      "Flame Wave",      NULL,             9,  8,  1, 0, 54,  IS_CAST2, { MIS_WAVE,        0,          0 }, 3, 20,  20, 40, 10000, 650 },
	{ SPL_DOOMSERP,    0,   STYPE_LIGHTNING, "Doom Serpents",   NULL,             -1, -1, 0, 0, 0,   IS_CAST2, { 0,               0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_BLODRIT,     0,   STYPE_MAGIC,     "Blood Ritual",    NULL,             -1, -1, 0, 0, 0,   IS_CAST2, { 0,               0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_NOVA,        60,  STYPE_MAGIC,     "Nova",            NULL,             -1, 10, 0, 0, 87,  IS_CAST4, { MIS_NOVA,        0,          0 }, 3, 35,  16, 32, 21000, 1300 },
	{ SPL_INVISIBIL,   0,   STYPE_MAGIC,     "Invisibility",    NULL,             -1, -1, 0, 0, 0,   IS_CAST2, { 0,               0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_FLAME,       11,  STYPE_FIRE,      "Inferno",         NULL,             3,  2,  1, 0, 20,  IS_CAST2, { MIS_FLAMEC,      0,          0 }, 1, 6,   20, 40, 2000,  100 },
	{ SPL_GOLEM,       100, STYPE_FIRE,      "Golem",           NULL,             11, 9,  0, 0, 81,  IS_CAST2, { MIS_GOLEM,       0,          0 }, 6, 60,  16, 32, 18000, 1100 },
	{ SPL_BLODBOIL,    0,   STYPE_LIGHTNING, "Blood Boil",      NULL,             -1, -1, 1, 0, 0,   IS_CAST8, { 0,               0,          0 }, 0, 0,   0,  0,  0,     0 },
	{ SPL_TELEPORT,    35,  STYPE_MAGIC,     "Teleport",        NULL,             14, 12, 1, 0, 105, IS_CAST6, { MIS_TELEPORT,    0,          0 }, 3, 15,  16, 32, 20000, 1250 },
	{ SPL_APOCA,       150, STYPE_FIRE,      "Apocalypse",      NULL,             -1, 15, 0, 0, 149, IS_CAST2, { MIS_APOCA,       0,          0 }, 6, 90,  8,  12, 30000, 2000 },
	{ SPL_ETHEREALIZE, 100, STYPE_MAGIC,     "Etherealize",     NULL,             -1, -1, 0, 0, 93,  IS_CAST2, { MIS_ETHEREALIZE, 0,          0 }, 0, 100, 2,  6,  26000, 1600 },
	{ SPL_REPAIR,      0,   STYPE_MAGIC,     "Item Repair",     "Item Repair",    -1, -1, 0, 1, -1,  IS_CAST6, { MIS_REPAIR,      0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_RECHARGE,    0,   STYPE_MAGIC,     "Staff Recharge",  "Staff Recharge", -1, -1, 0, 1, -1,  IS_CAST6, { MIS_RECHARGE,    0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_DISARM,      0,   STYPE_MAGIC,     "Trap Disarm",     "Trap Disarm",    -1, -1, 0, 0, -1,  IS_CAST6, { MIS_DISARM,      0,          0 }, 0, 0,   40, 80, 0,     0 },
	{ SPL_ELEMENT,     35,  STYPE_FIRE,      "Elemental",       NULL,             8,  6,  0, 0, 68,  IS_CAST2, { MIS_ELEMENT,     0,          0 }, 2, 20,  20, 60, 10500, 700 },
	{ SPL_CBOLT,       6,   STYPE_LIGHTNING, "Charged Bolt",    NULL,             1,  1,  1, 0, 25,  IS_CAST2, { MIS_CBOLT,       0,          0 }, 1, 6,   40, 80, 1000,  50 },
	{ SPL_HBOLT,       7,   STYPE_MAGIC,     "Holy Bolt",       NULL,             1,  1,  1, 0, 20,  IS_CAST2, { MIS_HBOLT,       0,          0 }, 1, 3,   40, 80, 1000,  50 },
	{ SPL_RESURRECT,   20,  STYPE_MAGIC,     "Resurrect",       NULL,             -1, 5,  0, 1, 30,  IS_CAST8, { MIS_RESURRECT,   0,          0 }, 0, 20,  4,  10, 4000,  250 },
	{ SPL_TELEKINESIS, 15,  STYPE_MAGIC,     "Telekinesis",     NULL,             2,  2,  0, 0, 33,  IS_CAST2, { MIS_TELEKINESIS, 0,          0 }, 2, 8,   20, 40, 2500,  200 },
	{ SPL_HEALOTHER,   5,   STYPE_MAGIC,     "Heal Other",      NULL,             1,  1,  0, 1, 17,  IS_CAST8, { MIS_HEALOTHER,   0,          0 }, 3, 1,   20, 40, 1000,  50 },
	{ SPL_FLARE,       25,  STYPE_MAGIC,     "Blood Star",      NULL,             14, 13, 0, 0, 70,  IS_CAST2, { MIS_FLARE,       0,          0 }, 2, 14,  20, 60, 27500, 1800 },
	{ SPL_BONESPIRIT,  24,  STYPE_MAGIC,     "Bone Spirit",     NULL,             9,  7,  0, 0, 34,  IS_CAST2, { MIS_BONESPIRIT,  0,          0 }, 1, 12,  20, 60, 11500, 800 }
};

// int __fastcall GetManaAmount(int id, spell_id sn)
int __fastcall GetManaAmount(int id, int sn)
{
	int adj; // mana adjust
	int sl; // spell level
	int i; // "raw" mana cost
	int ma; // mana amount

	adj = 0;
	sl = plr[id]._pSplLvl[sn] + plr[id]._pISplLvlAdd - 1;
	if ( sl < 0 )
		sl = 0;

	if ( sl > 0 )
		adj = sl * spelldata[sn].sManaAdj;
	if ( sn == SPL_FIREBOLT )
		adj >>= 1;
	if ( sn == SPL_RESURRECT && sl > 0 )
		adj = sl * (spelldata[SPL_RESURRECT].sManaCost / 8);

	if ( spelldata[sn].sManaCost == 255 ) /* check sign */
		i = plr[id]._pMaxManaBase;
	else
		i = spelldata[sn].sManaCost;

	ma = (i - adj) << 6;

	if ( sn == SPL_HEAL )
		ma = (spelldata[SPL_HEAL].sManaCost + 2 * plr[id]._pLevel - adj) << 6;
	if ( sn == SPL_HEALOTHER )
		ma = (spelldata[SPL_HEAL].sManaCost + 2 * plr[id]._pLevel - adj) << 6;

	if ( plr[id]._pClass == 1 )
		ma -= ma >> 2;

	if ( spelldata[sn].sMinMana > ma >> 6 )
		ma = spelldata[sn].sMinMana << 6;

	return ma * (100 - plr[id]._pISplCost) / 100;
}

// void __fastcall UseMana(int id, spell_id sn)
void __fastcall UseMana(int id, int sn)
{
	int ma; // mana cost

	if ( id == myplr )
	{
		switch ( plr[id]._pSplType )
		{
		case RSPLTYPE_SPELL:
#ifdef _DEBUG
			if ( !debug_mode_key_inverted_v )
			{
#endif
				ma = GetManaAmount(id, sn);
				plr[id]._pMana -= ma;
				plr[id]._pManaBase -= ma;
				drawmanaflag = 1;
#ifdef _DEBUG
			}
#endif
			break;
		case RSPLTYPE_SCROLL:
			RemoveScroll(id);
			break;
		case RSPLTYPE_CHARGES:
			// TODO: this should be inlined
			UseStaffCharge(id);
			break;
		}
	}
}

// BOOL __fastcall CheckSpell(int id, spell_id sn, spell_type st, BOOL manaonly)
BOOL __fastcall CheckSpell(int id, int sn, int st, BOOL manaonly)
{
#ifdef _DEBUG
	if ( debug_mode_key_inverted_v )
		return true;
#endif

	// TODO: the first few instructions are encoded differently.
	// It seems that the original compiler liked using EAX more.

	BOOL result = true;
	if ( !manaonly && pcurs != 1 )
	{
		result = false;
	}
	else
	{
		// TODO: switch the type of st to spell_type, which would probably allow to remove the (_BYTE)
		if ( (_BYTE)st != RSPLTYPE_SKILL )
		{
			if ( GetSpellLevel(id, sn) <= 0 )
			{
				return false;
			}
			else
			{
				return plr[id]._pMana >= GetManaAmount(id, sn);
			}
		}
	}

	return result;
}

// void __fastcall CastSpell(int id, spell_id spl, int sx, int sy, int dx, int dy, BOOL caster, int spllvl)
void __fastcall CastSpell(int id, int spl, int sx, int sy, int dx, int dy, int caster, int spllvl)
{

	int dir; // missile direction

	if ( caster )
	{
		if ( caster == 1 )
			dir = monster[id]._mdir;

		// note: dir is uninitialized when caster != 0 && caster != 1.
		// in older patches there was a
		// else
		//     dir = caster;
		// here it seems, but it's completely gone in 1.09
		// (traced the assembly manually to make sure IDA didn't miss something)
	}
	else
	{
		// see notes below.
		// caster = 0;

		dir = plr[id]._pdir;

		if ( spl == SPL_FIREWALL )
			dir = plr[id]._pVar3;

		// note: logically, this line seems to make no sense, since caster has to be 0 to
		// get into this branch, but every version back to the beta has this statement.

		// note: based on the code generation and the position in the beta version, this has to be here,
		// since only with the line here ebx is used as zero register in the whole function.
		// e.g. the zero in AddMissile is a `push ebx` instead of `push 0`. Saves a single byte per change.
		// Code flow wise it happens before the first statement in this else block.

		// TODO: investigate after more functions have been cleaned up to see if some optimization changes cause this
		caster = 0;
	}

	int i;
	for ( i = 0; spelldata[spl].sMissiles[i] && i < 3; ++i )
	{
		AddMissile(sx, sy, dx, dy, dir, spelldata[spl].sMissiles[i], caster, id, 0, spllvl);
	}

	if ( *spelldata[spl].sMissiles == MIS_TOWN )
		UseMana(id, SPL_TOWN);
	if ( *spelldata[spl].sMissiles == MIS_CBOLT )
	{
		UseMana(id, SPL_CBOLT);
		if ( (spllvl >> 1) + 3 > 0 )
		{
			for ( i = (spllvl >> 1) + 3; i > 0; --i )
			{
				AddMissile(sx, sy, dx, dy, dir, MIS_CBOLT, caster, id, 0, spllvl);
			}
		}
	}
}

// pnum: player index
// rid: target player index
void __fastcall DoResurrect(int pnum, int rid)
{

	if ( (_BYTE)rid != LOBYTE(-1) )
		AddMissile(plr[rid].WorldX, plr[rid].WorldY, plr[rid].WorldX, plr[rid].WorldY, 0, MIS_RESURRECTBEAM, 0, pnum, 0, 0);

	if ( pnum == myplr )
		j_SetCursor(CURSOR_HAND);

	if ( (_BYTE)rid != LOBYTE(-1) && plr[rid]._pHitPoints == 0 )
	{

		if ( rid == myplr )
		{
			deathflag = 0;
			gamemenu_off();
			drawhpflag = 1;
			drawmanaflag = 1;
		}

		ClrPlrPath(rid);
		plr[rid].destAction = -1;
		plr[rid]._pInvincible = 0;
		PlacePlayer(rid);

		if ( plr[rid]._pMaxHPBase < 640 )
			SetPlayerHitPoints(rid, plr[rid]._pMaxHPBase);
		else
			SetPlayerHitPoints(rid, 640);

		plr[rid]._pMana = 0;
		plr[rid]._pHPBase = plr[rid]._pHitPoints + (plr[rid]._pMaxHPBase - plr[rid]._pMaxHP);
		plr[rid]._pManaBase = plr[rid]._pMaxManaBase - plr[rid]._pMaxMana;

		CalcPlrInv(rid, TRUE);

		if ( plr[rid].plrlevel == currlevel )
			StartStand(rid, plr[rid]._pdir);
		else
			plr[rid]._pmode = 0;
	}
}

void __fastcall PlacePlayer(int pnum)
{
	int nx;
	int ny;

	if ( plr[pnum].plrlevel == currlevel )
	{
		for ( unsigned int i = 0; i < 8; ++i )
		{
			nx = plr[pnum].WorldX + plrxoff2[i];
			ny = plr[pnum].WorldY + plryoff2[i];

			if ( PosOkPlayer(pnum, nx, ny) )
				break;
		}

		if ( !PosOkPlayer(pnum, nx, ny) )
		{
			BOOL done = FALSE;

			for ( int max = 1, min = -1; !done && min > -50; ++max, --min )
			{
				for ( int y = min; y <= max && !done; ++y )
				{
					ny = y + plr[pnum].WorldY;

					for ( int x = min; x <= max && !done; ++x )
					{
						nx = x + plr[pnum].WorldX;

						if ( PosOkPlayer(pnum, nx, ny) )
							done = TRUE;
					}
				}
			}
		}

		plr[pnum].WorldX = nx;
		plr[pnum].WorldY = ny;

		dPlayer[nx][ny] = pnum + 1;

		if ( pnum == myplr )
		{
			ViewX = nx;
			ViewY = ny;
		}
	}
}

void __fastcall DoHealOther(int pnum, int rid)
{
	int i;
	int j;

	if ( pnum == myplr )
		j_SetCursor(CURSOR_HAND);

	if ( (_BYTE)rid != LOBYTE(-1) && (plr[rid]._pHitPoints >> 6) > 0 )
	{
		i = 0;
		for ( j = (random(57, 10) + 1) << 6; i < plr[pnum]._pLevel; ++i )
		{
			j += (random(57, 4) + 1) << 6;
		}

		for ( i = 0; i < GetSpellLevel(pnum, SPL_HEALOTHER); ++i )
		{
			j += (random(57, 6) + 1) << 6;
		}

		if ( plr[pnum]._pClass == UI_WARRIOR )
			j *= 2;

		if ( plr[pnum]._pClass == UI_ROGUE )
			j += j >> 1;

		plr[rid]._pHitPoints += j;

		if ( plr[rid]._pHitPoints > plr[rid]._pMaxHP )
			plr[rid]._pHitPoints = plr[rid]._pMaxHP;

		plr[rid]._pHPBase += j;

		if ( plr[rid]._pHPBase > plr[rid]._pMaxHPBase )
			plr[rid]._pHPBase = plr[rid]._pMaxHPBase;

		drawhpflag = 1;
	}
}
