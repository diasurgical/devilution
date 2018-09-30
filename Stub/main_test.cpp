#include "xxhash.h"
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <random>
#include <stddef.h>
#include <tuple>
#include <valgrind/memcheck.h>

#include "../types.h"
#include "asserts.h"
#include "sanitize_coverage.h"
#include "stubs.h"
#include "test_utils.h"

#ifdef HAVE_HARNESS
#include "Absolute/absolute.h"

static bool use_harness;

#define H(name) (use_harness ? d_##name : name)
#endif

#ifndef H
#define H(name) name
#endif

using std::endl;
using std::ostream;

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

static void oprintf(ostream &os, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	char buf[256];
	vsnprintf(buf, sizeof(buf), format, args);
	buf[sizeof(buf) - 1] = 0;
	os << buf;
}

#define O(x) out << #x << "=" << x << endl

static void print_dungeon(ostream &out)
{
	if (leveltype != DTYPE_CATHEDRAL) {
		out << "predungeon:" << endl;
		for (int y = 0; y < DMAXY; y++) {
			for (int x = 0; x < DMAXX; x++) {
				auto v = predungeon[x][y];
				out << (v ? v : '~');
			}
			out << endl;
		}
	} else {
		O(VR1);
		O(VR2);
		O(VR3);
		O(HR1);
		O(HR2);
		O(HR3);

		out << "L5dungeon:" << endl;
		for (int y = 0; y < 80; y++) {
			oprintf(out, "%2d: ", y);
			for (int x = 0; x < 80; x++) {
				BYTE v = L5dungeon[x][y];
				if (!v)
					out << '.';
				else
					oprintf(out, "%X", (int)v);
			}
			out << endl;
		}
	}

	out << "dungeon:" << endl;
	for (int y = 0; y < DMAXY; y++) {
		oprintf(out, "%2d: ", y);
		for (int x = 0; x < DMAXX; x++) {
			BYTE v = dungeon[x][y];
			if (v == 0x16)
				out << ".. ";
			else
				oprintf(out, "%02X ", (int)v);
		}
		out << endl;
	}

	out << "mydflags:" << endl;
	for (int y = 0; y < DMAXY; y++) {
		oprintf(out, "%2d: ", y);
		for (int x = 0; x < DMAXX; x++) {
			BYTE v = mydflags[x][y];
			if (!v)
				out << " .";
			else
				oprintf(out, "%02X", (int)v);
		}
		out << endl;
	}

	O(setpc_w);
	O(setpc_h);
	O(setpc_x);
	O(setpc_y);
}

static uint32_t mix32(uint32_t x)
{
	x ^= x >> 16;
	x *= UINT32_C(0x85ebca6b);
	x ^= x >> 13;
	x *= UINT32_C(0xc2b2ae35);
	x ^= x >> 16;
	return x;
}

template <typename T> static uint32_t hash(const T &obj)
{
	return XXH32(&obj, sizeof(obj), 123);
}

struct DGHashes {
	uint32_t h_predungeon = hash(predungeon);
	uint32_t h_dungeon = hash(dungeon);
	uint32_t h_dPiece = hash(dPiece);

	auto to_tuple() { return std::tie(h_predungeon, h_dungeon, h_dPiece); }
	void print() { printf("H: predungeon=%08X dungeon=%08X dPiece=%08X\n", h_predungeon, h_dungeon, h_dPiece); }
};

struct DGTestCase {
	int currlevel;
	int seed;
	int entry;

	void run()
	{
		::currlevel = currlevel;

		test_set_seeds(seed);

		H(InitLighting)();

		H(InitQuests)();

		for (int q = 0; q < MAXQUESTS; q++) {
			if (quests[q]._qactive) {
				// printf("Quest %2d active, status = %d\n", q, QuestStatus(q));
			}
		}

		// VALGRIND: Initialize the d* arrays. This is also called by DRLG_L2() but *after* it touches them.
		H(DRLG_Init_Globals)();

		H(CreateLevel)(entry);

		ASSERT(pHallList == 0);
	};

	void run_original()
	{
#ifdef HAVE_HARNESS
		use_harness = true;
		run();
		use_harness = false;
#else
		fprintf(stderr, "Comparison disabled\b");
#endif
	}

	bool run_original_and_compare()
	{
		DGHashes h1;

		run_original();

		DGHashes horig;

		if (h1.to_tuple() != horig.to_tuple()) {
			h1.print();
			horig.print();

			return false;
		}
		return true;
	}

	void run_and_print_dungeons()
	{
		run();
		{
			std::ofstream fnew("dungeon.new.txt");
			print_dungeon(fnew);
		}

		run_original();
		{
			std::ofstream fnew("dungeon.original.txt");
			print_dungeon(fnew);
		}
	}

	void print(std::ostream &os) const { os << "currlevel=" << currlevel << " entry=" << entry << " seed=" << seed; };
};

template <class T> auto operator<<(std::ostream &os, const T &t) -> decltype(t.print(os), os)
{
	t.print(os);
	return os;
}

static void test_init_drlg(dungeon_type dt)
{
	setlevel = 0; // VALGRIND

	leveltype = dt; // This is loaded from gnLevelTypeTbl[] in the game

	pHallList = 0; // VALGRIND: Linked list initialized to 0
	pSetPiece_2 = 0; // VALGRIND: Always freed, even when it is not loaded

	nSx1 = nSx2 = nSy1 = nSy2 = 0; // VALGRIND: Looks like the DRLG code assumes these can be 0

	H(LoadLvlGFX)();
}

static void test_levelgen()
{
	// std::minstd_rand gen(123);
	// std::uniform_int_distribution<> dis;

	test_init_common();

	// test_init_drlg(DTYPE_CATACOMBS);
	// std::vector<int> levels{2, 5, 6, 7, 8};
	test_init_drlg(DTYPE_CATHEDRAL);
	std::vector<int> levels{1, 2, 3, 4};

	DGTestCase testcase;
	for (int iter = 0; iter < 1000000; iter++) {
		testcase.seed = mix32(iter);
		for (auto currlevel : levels) {
			testcase.currlevel = currlevel;
			for (auto entry : {0, 1}) {
				testcase.entry = entry;

				coverage_start_round();

				testcase.run();

				if (coverage_found_new()) {
					std::cout << "new coverage, " << testcase << std::endl;
				}

				testcase.run_original_and_compare();
			}
		}
	}

	// LoadGameLevel(TRUE, 0);
}

static void test_newgame()
{
	test_init_common();

	start_game(WM_DIABNEWGAME);
}

static void test_levelgen_example()
{
	test_init_common();
	test_init_drlg(DTYPE_CATHEDRAL);

	DGTestCase testcase;
	testcase.currlevel = 5;
	testcase.entry = 0;
	testcase.seed = 1364076727;

	testcase.run();
	testcase.run_original_and_compare();
	testcase.run_and_print_dungeons();
}

int main(int argc, char **argv)
{
#ifdef HAVE_HARNESS
	init_absolute();
#endif

	valgrind_init();

	coverage_init();

	// test_levelgen();
	test_levelgen_example();
	// test_newgame();

	eprintf("Done!\n");

	return 0;
}
