/**
 * @file monstdat.cpp
 *
 * Implementation of all monster data.
 */
#include "all.h"

MonsterData monsterdata[] = {
#include "Data/xl_monst.cpp"
};

char MonstConvTbl[128] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 29, 30,
	31, 32, 34, 35, 36, 37, 38, 40, 39, 41,
	42, 43, 44, 45, 46, 47, 48, 49, 50, 52,
	53, 54, 55, 56, 57, 59, 58, 60, 61, 62,
	63, 64, 65, 66, 67, 68, 69, 70, 71, 0,
	0, 0, 0, 72, 73, 74, 75, 0, 0, 0,
	0, 77, 76, 78, 79, 81, 82, 83, 84, 85,
	86, 87, 88, 89, 90, 92, 91, 93, 94, 95,
	96, 97, 98, 99, 100, 101, 102, 103, 104, 105,
	106, 107, 108, 0, 110, 0, 109, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 80, 111
};

/**
 * 0 = Never avalible
 * 1 = Avalible in retail and shareware
 * 2 = avalible in retail only
 */
BYTE MonstAvailTbl[] = {
	1, // Zombie
	1, // Ghoul
	1, // Rotting Carcass
	1, // Black Death
	1, // Fallen One
	1, // Carver
	1, // Devil Kin
	1, // Dark One
	1, // Skeleton
	1, // Corpse Axe
	1, // Burning Dead
	1, // Horror
	1, // Fallen One
	1, // Carver
	1, // Devil Kin
	1, // Dark One
	1, // Scavenger
	1, // Plague Eater
	1, // Shadow Beast
	1, // Bone Gasher
	1, // Skeleton
	1, // Corpse Bow
	1, // Burning Dead
	1, // Horror
	1, // Skeleton Captain
	1, // Corpse Captain
	1, // Burning Dead Captain
	1, // Horror Captain
	0, // Invisible Lord
	2, // Hidden
	2, // Stalker
	2, // Unseen
	2, // Illusion Weaver
	0, // Lord Sayter
	2, // Flesh Clan
	2, // Stone Clan
	2, // Fire Clan
	2, // Night Clan
	1, // Fiend
	1, // Blink
	1, // Gloom
	1, // Familiar
	2, // Flesh Clan
	2, // Stone Clan
	2, // Fire Clan
	2, // Night Clan
	2, // Acid Beast
	2, // Poison Spitter
	2, // Pit Beast
	2, // Lava Maw
	0, // Skeleton King
	0, // The Butcher
	2, // Overlord
	2, // Mud Man
	2, // Toad Demon
	2, // Flayed One
	0, // Wyrm
	0, // Cave Slug
	0, // Devil Wyrm
	0, // Devourer
	2, // Magma Demon
	2, // Blood Stone
	2, // Hell Stone
	2, // Lava Lord
	2, // Horned Demon
	2, // Mud Runner
	2, // Frost Charger
	2, // Obsidian Lord
	0, // Bone Demon (oldboned in Hellfire)
	0, // Red Death
	0, // Litch Demon
	0, // Undead Balrog
	0, // Incinerator
	0, // Flame Lord
	0, // Doom Fire
	0, // Hell Burner
	2, // Red Storm
	2, // Storm Rider
	2, // Storm Lord
	2, // Maelstorm
	0, // Devil Kin Brute
	2, // Winged-Demon
	2, // Gargoyle
	2, // Blood Claw
	2, // Death Wing
	2, // Slayer
	2, // Guardian
	2, // Vortex Lord
	2, // Balrog
	2, // Cave Viper
	2, // Fire Drake
	2, // Gold Viper
	2, // Azure Drake
	2, // Black Knight
	2, // Doom Guard
	2, // Steel Lord
	2, // Blood Knight
	0, // Unraveler
	0, // Hollow One
	0, // Pain Master
	0, // Reality Weaver
	2, // Succubus
	2, // Snow Witch
	2, // Hell Spawn
	2, // Soul Burner
	2, // Counselor
	2, // Magistrate
	2, // Cabalist
	2, // Advocate
	0, // Golem
	0, // The Dark Lord
	0, // The Arch-Litch Malignus
};

UniqMonstStruct UniqMonst[] = {
#include "Data/xl_umon.cpp"
};
