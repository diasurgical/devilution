#include <stddef.h>
#include <valgrind/memcheck.h>

#include "../types.h"
#include "Absolute/absolute.h"
#include "stubs.h"

static void valgrind_init()
{
	char *start = &__start_bss;
	unsigned len = (char *)&__end_bss - start;
	VALGRIND_MAKE_MEM_UNDEFINED(start, len);

	// Global destructors in msgcmd_cleanup_chatcmd() read this
	VALGRIND_MAKE_MEM_DEFINED(&sgChat_Cmd, sizeof(sgChat_Cmd));
}

static void init()
{
	valgrind_init();

	init_archives();

	encrypt_init_lookup_table();
	diablo_init_screen();

	InitLightTable();

	gdwNormalMsgSize = 512;

	gbMaxPlayers = 1;

	light4flag = 0; // VALGRIND
}

static void test_levelgen()
{
	init();

	SetRndSeed(123);
	int v2 = 0;
	do {
		glSeedTbl[v2] = GetRndSeed();
		gnLevelTypeTbl[v2] = InitNewSeed(v2);
		++v2;
	} while (v2 < 17);

	setlevel = 0; // VALGRIND
	currlevel = 2;
	leveltype = DTYPE_CATACOMBS;

	pHallList = 0; // VALGRIND: Linked list initialized to 0
	pSetPiece_2 = 0; // VALGRIND: Always freed, even when it is not loaded

	nSx1 = nSx2 = nSy1 = nSy2 = 0; // VALGRIND: Looks like the DRLG code assumes these can be 0

	InitLighting();

	InitQuests();

	DRLG_Init_Globals(); // VALGRIND: Initialize the d* arrays. This is also called by DRLG_L2() but *after* it touches
	                     // them.

	LoadLvlGFX();

	CreateLevel(0);

	// LoadGameLevel(TRUE, 0);
}

static void test_newgame()
{
	init();

	start_game(WM_DIABNEWGAME);
}

int main(int argc, char **argv)
{
	test_levelgen();
	// test_newgame();

	eprintf("Done!\n");

	return 0;
}
