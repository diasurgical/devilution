//HEADER_GOES_HERE

#include "../types.h"

// unused, this was probably for blood boil/burn
int spurtndx; // weak

DeadStruct dead[MAXDEAD];
int stonendx;

void __cdecl InitDead()
{
	int i, j;
	int mtypes[MAXMONSTERS];
	int idx;

	for (i = 0; i < MAXMONSTERS; i++)
		mtypes[i] = 0;

	idx = 0;
	for (i = 0; i < nummtypes; i++) {
		if (!mtypes[Monsters[i].mtype]) {
			for (j = 0; j < 8; j++)
				dead[idx]._deadData[j] = Monsters[i].Anims[MA_DEATH].Data[j];
			dead[idx]._deadFrame = Monsters[i].Anims[MA_DEATH].Frames;
			dead[idx]._deadWidth = Monsters[i].flags_1;
			dead[idx]._deadWidth2 = Monsters[i].flags_2;
			dead[idx]._deadtrans = 0;
			Monsters[i].mdeadval = idx + 1;
			mtypes[Monsters[i].mtype] = ++idx;
		}
	}

	for (j = 0; j < 8; j++)
		dead[idx]._deadData[j] = misfiledata[MFILE_BLODBUR].mAnimData[0];
	dead[idx]._deadtrans = 0;
	dead[idx]._deadFrame = 8;
	spurtndx = idx + 1;
	dead[idx]._deadWidth = 128;
	dead[idx]._deadWidth2 = 32;
	idx = spurtndx;

	for (j = 0; j < 8; j++)
		dead[idx]._deadData[j] = misfiledata[MFILE_SHATTER1].mAnimData[0];
	dead[idx]._deadtrans = 0;
	dead[idx]._deadFrame = 12;
	stonendx = idx + 1;
	dead[idx]._deadWidth = 128;
	dead[idx]._deadWidth2 = 32;
	idx++;

	for (i = 0; i < nummonsters; i++) {
		int ii = monstactive[i];
		if (monster[ii]._uniqtype) {
			for (j = 0; j < 8; j++)
				dead[idx]._deadData[j] = monster[ii].MType->Anims[MA_DEATH].Data[j];
			dead[idx]._deadFrame = monster[ii].MType->Anims[MA_DEATH].Frames;
			dead[idx]._deadWidth = monster[ii].MType->flags_1;
			dead[idx]._deadWidth2 = monster[ii].MType->flags_2;
			dead[idx]._deadtrans = monster[ii]._uniqtrans + 4;
			monster[ii]._udeadval = idx + 1;
			idx++;
		}
	}
}
// 4B8CD8: using guessed type int spurtndx;

void __fastcall AddDead(int dx, int dy, char dv, int ddir)
{
	dDead[dx][dy] = (dv & 0x1F) + (ddir << 5);
}

void __cdecl SetDead()
{
	for (int i = 0; i < nummonsters; i++) {
		int m = monstactive[i];
		if (monster[m]._uniqtype) {
			for (int x = 0; x < MAXDUNX; x++) {
				for (int y = 0; y < MAXDUNY; y++) {
					if ((dDead[x][y] & 0x1F) == monster[m]._udeadval)
						ChangeLightXY(monster[m].mlid, x, y);
				}
			}
		}
	}
}
