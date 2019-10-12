#include <stdio.h>
#include <stdlib.h>

#include "diablo.h"

void write_file(char *path, void *buf, int size);

// drlg_l1.cpp

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
	} Golden;

	// Golden test cases.
	Golden golden[] = {
		{
			"Cathedral",     // dungeon_name
			1,               // dlvl
			DTYPE_CATHEDRAL, // dtype
			QTYPE_INVALID,   // quest_id
			123              // seed
		}
	};

	// extra.
	int in_entry = 0;
	BYTE in_max_players = 1; // single

	// Load MPQ archives.
	init_archives();

	for (int i = 0; i < sizeof(golden)/sizeof(Golden); i++) {
		Golden g = golden[i];

		// Load level graphics.
		//*gendung.DType = g.dtype;
		leveltype = g.dtype;
		//diablo.LoadLevelGraphics();
		LoadLvlGFX();

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
		setlevel = false;
		//if g.questID != quests.Invalid {
		//	quests.Quests[g.questID].Active = true;
		//	quests.Quests[g.questID].DLvl = g.dlvl;
		//}
		if (g.quest_id != QTYPE_INVALID) {
			quests[g.quest_id]._qlevel  = g.dlvl;
			quests[g.quest_id]._qactive = true;
		}

		// Generate dungeon based on the given seed.
		//l1.CreateDungeon(g.seed, 0);

		CreateL5Dungeon(g.seed, in_entry);

		// Dump pre-dungeon tiles.
		char output_path[MAX_PATH];
		//sprintf(output_path, "testdata/pre-tiles_%d.bin", g.seed);
		//write_file(output_path, pdungeon, sizeof(pdungeon));

		// Dump tiles.
		sprintf(output_path, "testdata/tiles_%d.bin", g.seed);
		write_file(output_path, dungeon, sizeof(dungeon));

		// Dungeon dungeon pieces.
		sprintf(output_path, "testdata/dpieces_%d.bin", g.seed);
		write_file(output_path, dPiece, sizeof(dPiece));

		// Dungeon arches.
		sprintf(output_path, "testdata/arches_%d.bin", g.seed);
		write_file(output_path, dArch, sizeof(dArch));

		// Dungeon transparency.
		sprintf(output_path, "testdata/transparency_%d.bin", g.seed);
		write_file(output_path, dTransVal, sizeof(dTransVal));
	}
}

void testgen()
{
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
