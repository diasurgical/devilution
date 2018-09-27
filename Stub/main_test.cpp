#include <initializer_list>
#include <stddef.h>
#include <valgrind/memcheck.h>

#include "../types.h"
#include "stubs.h"
#include "test_utils.h"

#ifdef HAVE_HARNESS
#include "Absolute/absolute.h"

#define H(name) d_##name
#else
#define H(name) name
#endif

static void valgrind_init()
{
#ifdef HAVE_HARNESS
	char *start = &__start_bss;
	unsigned len = (char *)&__end_bss - start;
	VALGRIND_MAKE_MEM_UNDEFINED(start, len);

	// Global destructors in msgcmd_cleanup_chatcmd() read this
	VALGRIND_MAKE_MEM_DEFINED(&sgChat_Cmd, sizeof(sgChat_Cmd));
#endif
}

static void test_levelgen()
{
	test_init_common();

	setlevel = 0; // VALGRIND

	leveltype = DTYPE_CATACOMBS; // This is loaded from gnLevelTypeTbl[] in the game

	pHallList = 0; // VALGRIND: Linked list initialized to 0
	pSetPiece_2 = 0; // VALGRIND: Always freed, even when it is not loaded

	nSx1 = nSx2 = nSy1 = nSy2 = 0; // VALGRIND: Looks like the DRLG code assumes these can be 0

	H(LoadLvlGFX)();

	for (int l : {2, 5, 6, 7, 8}) {
		currlevel = l;
		for (int entry : {0, 1}) {
			for (int seed = 0; seed < 5; seed++) {
				test_set_seeds(seed * 23);

				H(InitLighting)();

				H(InitQuests)();

				// VALGRIND: Initialize the d* arrays. This is also called by DRLG_L2() but *after* it touches them.
				H(DRLG_Init_Globals)();

				H(CreateLevel)(entry);

				assert(pHallList == 0);
			}
		}
	}

	for (int y = 0; y < 40; y++) {
		printf(": ");
		for (int x = 0; x < 40; x++) {
			printf("%c", predungeon[x][y]);
		}
		printf("\n");
	}

	// LoadGameLevel(TRUE, 0);
}

static void test_newgame()
{
	test_init_common();

	start_game(WM_DIABNEWGAME);
}

int main(int argc, char **argv)
{
#ifdef HAVE_HARNESS
	init_absolute();
#endif

	valgrind_init();

	test_levelgen();
	// test_newgame();

	eprintf("Done!\n");

	return 0;
}
