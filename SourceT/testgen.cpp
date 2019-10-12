#include <stdio.h>
#include <stdlib.h>

#include "diablo.h"

void write_file(char *path, void *buf, int size);

// drlg_l1.cpp

void gen_drlg_l1_tests(void) {
	printf("gen_drlg_l1_tests\n");

	// pre.
	BYTE in_dlvl = 1;
	BYTE in_dtype = DTYPE_CATHEDRAL;
	BYTE in_quest_id = QTYPE_INVALID;
	DWORD in_seed = 123;
	// extra.
	int in_entry = 0;
	BYTE in_max_players = 1; // single

	// Load MPQ archives.
	init_archives();

	// Load level graphics.
	//*gendung.DType = g.dtype;
	leveltype = in_dtype;
	//diablo.LoadLevelGraphics();
	LoadLvlGFX();

	// Establish pre-conditions.
	//*gendung.DLvl = g.dlvl;
	currlevel = in_dlvl;
	//*multi.MaxPlayers = 1;
	gbMaxPlayers = in_max_players;
	//for i := range quests.Quests {
	//	quests.Quests[i].ID = quests.QuestID(i);
	//	quests.Quests[i].Active = false;
	//}
	for (int quest_id = 0; quest_id < MAXQUESTS; quest_id++) {
		quests[quest_id]._qtype = quest_id;
		quests[quest_id]._qactive = false;
	}
	//*gendung.IsQuestLevel = false;
	setlevel = false;
	//if g.questID != quests.Invalid {
	//	quests.Quests[g.questID].Active = true;
	//	quests.Quests[g.questID].DLvl = g.dlvl;
	//}
	if (in_quest_id != QTYPE_INVALID) {
		quests[in_quest_id]._qlevel = in_dlvl;
		quests[in_quest_id]._qactive = true;
	}

	// Generate dungeon based on the given seed.
	//l1.CreateDungeon(g.seed, 0);

	CreateL5Dungeon(in_seed, in_entry);

	// Dump pre-dungeon tiles.
	char output_path[MAX_PATH];
	//sprintf(output_path, "testdata/pre-tiles_%d.bin", in_seed);
	//write_file(output_path, pdungeon, sizeof(pdungeon));

	// Dump tiles.
	sprintf(output_path, "testdata/tiles_%d.bin", in_seed);
	write_file(output_path, dungeon, sizeof(dungeon));

	// Dungeon dungeon pieces.
	sprintf(output_path, "testdata/dpieces_%d.bin", in_seed);
	write_file(output_path, dPiece, sizeof(dPiece));

	// Dungeon arches.
	sprintf(output_path, "testdata/arches_%d.bin", in_seed);
	write_file(output_path, dArch, sizeof(dArch));

	// Dungeon transparency.
	sprintf(output_path, "testdata/transparency_%d.bin", in_seed);
	write_file(output_path, dTransVal, sizeof(dTransVal));
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
