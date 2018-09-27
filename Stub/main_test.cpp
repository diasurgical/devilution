#include "../types.h"
#include "stubs.h"

#include <stddef.h>

extern "C" const char *__asan_default_options()
{
	return "halt_on_error=0:print_legend=0";
}

static void init()
{
	init_archives();

	InitHash();
	diablo_init_screen();

	InitLightTable();

	gdwNormalMsgSize = 512;
}

static void test_levelgen()
{
	init();

	SetRndSeed(123);

	currlevel = 2;
	leveltype = DTYPE_CATACOMBS;

	// DRLG_Init_Globals();
	// LoadLvlGFX();
	// CreateLevel(0);

	// LoadGameLevel(TRUE, 0);
}

static void test_newgame()
{
	init();

	start_game(WM_DIABNEWGAME);
}

int main(int argc, char **argv)
{
	//#define O(f) fprintf(stderr, "offsetof(%s) = %d\n", #f, offsetof(PlayerStruct, f))
	//
	//	O(_pRSplType);
	//	O(_pSBkSplType);
	//	O(_pSplLvl);
	//	O(_pMemSpells64);
	//	O(_pAblSpells64);
	//	O(_pSpellFlags);
	//	O(_pClass);
	//	O(_pVar8);
	//	O(_pIBonusDamMod);
	//	O(_pISpells64);
	//	O(_pBData);
	//
	//	printf("s %d\n", sizeof(UINT64));

	// test_levelgen();
	// test_newgame();

	WinMain(NULL, NULL, argc > 1 ? argv[1] : (char*)"", 0);

	eprintf("Done!\n");

	return 0;
}
