#include <stdio.h>
#include <stdlib.h>

#include "all.h"

void write_file(char *path, void *buf, int size);

// drlg_l1.cpp

#define SL_NONE 0
#define Q_INVALID -1

void gen_drlg_l1_tests(void) {
	printf("gen_drlg_l1_tests\n");

	typedef struct {
		// meta.
		char *dungeon_name;
		// pre.
		BYTE dlvl;
		BYTE dtype;
		BYTE quest_id;
		DWORD seed;
		BYTE setlvl;
	} Golden;

	// Golden test cases.
	Golden golden[] = {
		{
			"Cathedral",     // dungeon_name
			1,               // dlvl
			DTYPE_CATHEDRAL, // dtype
			Q_INVALID,       // quest_id
			123,             // seed
			SL_NONE,         // setlvl
		},
		{
			"Cathedral (fix corners)", // dungeon_name
			1,                         // dlvl
			DTYPE_CATHEDRAL,           // dtype
			Q_INVALID,                 // quest_id
			35,                        // seed
			SL_NONE,                   // setlvl
		},
		{
			"The Butcher",                 // dungeon_name
			questlist[Q_BUTCHER]._qdlvl,   // dlvl
			DTYPE_CATHEDRAL,               // dtype
			Q_BUTCHER,                     // quest_id
			123,                           // seed
			SL_NONE,                       // setlvl
		},
		{
			"Poisoned Water Supply",    // dungeon_name
			questlist[Q_PWATER]._qdlvl, // dlvl
			DTYPE_CATHEDRAL,            // dtype
			Q_PWATER,                   // quest_id
			123,                        // seed
			SL_NONE,                    // setlvl
		},
		{
			"Ogden's Sign",               // dungeon_name
			questlist[Q_LTBANNER]._qdlvl, // dlvl
			DTYPE_CATHEDRAL,              // dtype
			Q_LTBANNER,                   // quest_id
			123,                          // seed
			SL_NONE,                      // setlvl
		},
		{
			"Skeleton King's Lair (entrance)", // dungeon_name
			questlist[Q_SKELKING]._qdlvl,      // dlvl
			DTYPE_CATHEDRAL,                   // dtype
			Q_SKELKING,                        // quest_id
			123,                               // seed
			SL_NONE,                           // setlvl
		},
		{
			"Skeleton King's Lair",       // dungeon_name
			questlist[Q_SKELKING]._qdlvl, // dlvl
			DTYPE_CATHEDRAL,              // dtype
			Q_SKELKING,                   // quest_id
			123,                          // seed
			SL_SKELKING,                  // setlvl
		},
		// Broken seeds.
		{
			"Cathedral (broken seed)",// dungeon_name
			1,                        // dlvl
			DTYPE_CATHEDRAL,          // dtype
			Q_INVALID,                // quest_id
			2588,                     // seed
			SL_NONE,                  // setlvl
		},
		{
			"Cathedral (broken seed)",// dungeon_name
			1,                        // dlvl
			DTYPE_CATHEDRAL,          // dtype
			Q_INVALID,                // quest_id
			4743,                     // seed
			SL_NONE,                  // setlvl
		},
		{
			"Cathedral (broken seed)",// dungeon_name
			1,                        // dlvl
			DTYPE_CATHEDRAL,          // dtype
			Q_INVALID,                // quest_id
			7281,                     // seed
			SL_NONE,                  // setlvl
		},
		{
			"Cathedral (broken seed)",// dungeon_name
			1,                        // dlvl
			DTYPE_CATHEDRAL,          // dtype
			Q_INVALID,                // quest_id
			9345,                     // seed
			SL_NONE,                  // setlvl
		},
		{
			"Cathedral (broken seed)",// dungeon_name
			1,                        // dlvl
			DTYPE_CATHEDRAL,          // dtype
			Q_INVALID,                // quest_id
			15236,                     // seed
			SL_NONE,                  // setlvl
		},
	};

	// extra.
	int in_entry        = 0;
	BYTE in_max_players = 1; // single

	// Load MPQ archives.
	init_archives();

	// Load level graphics.
	//diablo.LoadLevelGraphics();
	leveltype = DTYPE_CATHEDRAL;
	LoadLvlGFX(); // TODO: only load level graphics once per dtype.

	for (int i = 0; i < sizeof(golden) / sizeof(Golden); i++) {
		Golden g = golden[i];

		// Reset globals (not needed).
		memset(pdungeon, 0, sizeof(pdungeon));
		memset(dungeon, 0, sizeof(dungeon));
		memset(dPiece, 0, sizeof(dPiece));
		memset(dSpecial, 0, sizeof(dSpecial));
		memset(dTransVal, 0, sizeof(dTransVal));

		//*gendung.DType = g.dtype;
		leveltype = g.dtype;

		// Establish pre-conditions.
		//*gendung.DLvl = g.dlvl;
		currlevel = g.dlvl;
		//*multi.MaxPlayers = 1;
		gbMaxPlayers = in_max_players;
		//for i := range quests.Quests {
		//	quests.Quests[i].ID = quests.QuestID(i);
		//	quests.Quests[i].Active = false;
		//}
		for (int quest_id = 0; quest_id < MAXQUESTS; quest_id++) {
			quests[quest_id]._qtype   = quest_id;
			quests[quest_id]._qactive = false;
		}

		//*gendung.IsQuestLevel = false;
		if (g.setlvl != SL_NONE) {
			setlevel = true;
			setlvlnum = g.setlvl;
		} else {
			setlevel = false;
			setlvlnum = SL_NONE;
		}

		//if g.questID != quests.Invalid {
		//	quests.Quests[g.questID].Active = true;
		//	quests.Quests[g.questID].DLvl = g.dlvl;
		//}
		if (g.quest_id != Q_INVALID) {
			quests[g.quest_id]._qlevel  = g.dlvl;
			quests[g.quest_id]._qactive = true;
		}

		// Generate dungeon based on the given seed.
		//l1.CreateDungeon(g.seed, 0);

		if (g.setlvl != SL_NONE) {
			LoadSetMap();
		} else {
			CreateL5Dungeon(g.seed, in_entry);
		}

		// Dump pre-dungeon tiles.
		char output_path[MAX_PATH];
		//sprintf(output_path, "testdata/pre-tiles_%d.bin", g.seed);
		//write_file(output_path, pdungeon, sizeof(pdungeon));

		// Dump tiles.
		sprintf(output_path, "testdata/dlvl=%d,quest_id=%d,seed=%d,setlvl=%d_tiles.bin", g.dlvl, g.quest_id, g.seed, g.setlvl);
		printf("creating '%s'\n", output_path);
		write_file(output_path, dungeon, sizeof(dungeon));

		// Dungeon dungeon pieces.
		sprintf(output_path, "testdata/dlvl=%d,quest_id=%d,seed=%d,setlvl=%d_dpieces.bin", g.dlvl, g.quest_id, g.seed, g.setlvl);
		printf("creating '%s'\n", output_path);
		write_file(output_path, dPiece, sizeof(dPiece));

		// Dungeon arches.
		sprintf(output_path, "testdata/dlvl=%d,quest_id=%d,seed=%d,setlvl=%d_arches.bin", g.dlvl, g.quest_id, g.seed, g.setlvl);
		printf("creating '%s'\n", output_path);
		write_file(output_path, dSpecial, sizeof(dSpecial));

		// Dungeon transparency.
		sprintf(output_path, "testdata/dlvl=%d,quest_id=%d,seed=%d,setlvl=%d_transparency.bin", g.dlvl, g.quest_id, g.seed, g.setlvl);
		printf("creating '%s'\n", output_path);
		write_file(output_path, dTransVal, sizeof(dTransVal));
	}
}

void testgen() {
	printf("testgen\n");
	gen_drlg_l1_tests();
}

void write_file(char *path, void *buf, int size) {
	FILE *f = fopen(path, "wb");
	if (f == NULL) {
		fprintf(stderr, "unable to create file %s", path);
		exit(1);
	}
	if (fwrite(buf, 1, size, f) != size) {
		fprintf(stderr, "unable to write to file %s", path);
		exit(1);
	}
	fclose(f);
}
