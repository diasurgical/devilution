//HEADER_GOES_HERE

#include "../types.h"

// unused, this was probably for blood boil/burn
int spurtndx;
DeadStruct dead[MAXDEAD];
int stonendx;

void InitDead()
{
	int mtypes[MAXMONSTERS];
	int i;
	int nd;
	int mi;
	int d;

	for (i = 0; i < MAXMONSTERS; i++)
		mtypes[i] = 0;

	nd = 0;

	for (i = 0; i < nummtypes; i++) {
		if (!mtypes[Monsters[i].mtype]) {
			for (d = 0; d < 8; d++)
				dead[nd]._deadData[d] = Monsters[i].Anims[MA_DEATH].Data[d];
			dead[nd]._deadFrame = Monsters[i].Anims[MA_DEATH].Frames;
			dead[nd]._deadWidth = Monsters[i].width;
			dead[nd]._deadWidth2 = Monsters[i].width2;
			dead[nd]._deadtrans = 0;
			Monsters[i].mdeadval = nd + 1;
			mtypes[Monsters[i].mtype] = nd + 1;
			nd++;
		}
	}

	for (d = 0; d < 8; d++)
		dead[nd]._deadData[d] = misfiledata[MFILE_BLODBUR].mAnimData[0];
	dead[nd]._deadFrame = 8;
	dead[nd]._deadWidth = 128;
	dead[nd]._deadWidth2 = 32;
	dead[nd]._deadtrans = 0;
	spurtndx = nd + 1;
	nd++;

	for (d = 0; d < 8; d++)
		dead[nd]._deadData[d] = misfiledata[MFILE_SHATTER1].mAnimData[0];
	dead[nd]._deadFrame = 12;
	dead[nd]._deadWidth = 128;
	dead[nd]._deadWidth2 = 32;
	dead[nd]._deadtrans = 0;
	stonendx = nd + 1;
	nd++;

	for (i = 0; i < nummonsters; i++) {
		mi = monstactive[i];
		if (monster[mi]._uniqtype) {
			for (d = 0; d < 8; d++)
				dead[nd]._deadData[d] = monster[mi].MType->Anims[MA_DEATH].Data[d];
			dead[nd]._deadFrame = monster[mi].MType->Anims[MA_DEATH].Frames;
			dead[nd]._deadWidth = monster[mi].MType->width;
			dead[nd]._deadWidth2 = monster[mi].MType->width2;
			dead[nd]._deadtrans = monster[mi]._uniqtrans + 4;
			monster[mi]._udeadval = nd + 1;
			nd++;
		}
	}

	/// ASSERT: assert(nd <= MAXDEAD);
}

void AddDead(int dx, int dy, char dv, int ddir)
{
	dDead[dx][dy] = (dv & 0x1F) + (ddir << 5);
}

void SetDead()
{
	int mi;
	int i;
	int dx, dy;

	for (i = 0; i < nummonsters; i++) {
		mi = monstactive[i];
		if (monster[mi]._uniqtype) {
			for (dx = 0; dx < MAXDUNX; dx++) {
				for (dy = 0; dy < MAXDUNY; dy++) {
					if ((dDead[dx][dy] & 0x1F) == monster[mi]._udeadval)
						ChangeLightXY(monster[mi].mlid, dx, dy);
				}
			}
		}
	}
}
