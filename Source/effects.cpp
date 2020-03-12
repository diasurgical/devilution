/**
 * @file effects.cpp
 *
 * Implementation of functions for loading and playing sounds.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

int sfxdelay;
int sfxdnum;
HANDLE sfx_stream;
TSFX *sfx_data_cur;

/**
 * Monster sound type prefix
 * a: Attack
 * h: Hit
 * d: Death
 * s: Special
 */
const char MonstSndChar[] = { 'a', 'h', 'd', 's' };

/* data */
/** List of all sounds, except monsters and music */
TSFX sgSFX[] = {
#ifdef SPAWN
#include "Data/Spawn/xl_sfx.cpp"
#else
#include "Data/xl_sfx.cpp"
#endif
};

BOOL effect_is_playing(int nSFX)
{
	TSFX *sfx = &sgSFX[nSFX];
	if (sfx->pSnd)
		return snd_playing(sfx->pSnd);

	if (sfx->bFlags & SFX_STREAM)
		return sfx == sfx_data_cur;

	return FALSE;
}

void sfx_stop()
{
	if (sfx_stream) {
		SFileDdaEnd(sfx_stream);
		SFileCloseFile(sfx_stream);
		sfx_stream = NULL;
		sfx_data_cur = NULL;
	}
}

void InitMonsterSND(int monst)
{
	TSnd *pSnd;
	char name[MAX_PATH];
	char *path;
	int mtype, i, j;

	if (!gbSndInited) {
		return;
	}

	mtype = Monsters[monst].mtype;
	for (i = 0; i < 4; i++) {
		if (MonstSndChar[i] != 's' || monsterdata[mtype].snd_special) {
			for (j = 0; j < 2; j++) {
				sprintf(name, monsterdata[mtype].sndfile, MonstSndChar[i], j + 1);
				path = (char *)DiabloAllocPtr(strlen(name) + 1);
				strcpy(path, name);
				pSnd = sound_file_load(path);
				Monsters[monst].Snds[i][j] = pSnd;
				if (!pSnd)
					mem_free_dbg(path);
			}
		}
	}
}

void FreeEffects()
{
	int mtype, i, j, k;
	char *file;
	TSnd *pSnd;

	for (i = 0; i < nummtypes; i++) {
		mtype = Monsters[i].mtype;
		for (j = 0; j < 4; ++j) {
			for (k = 0; k < 2; ++k) {
				pSnd = Monsters[i].Snds[j][k];
				if (pSnd) {
					Monsters[i].Snds[j][k] = NULL;
					file = pSnd->sound_path;
					pSnd->sound_path = NULL;
					sound_file_cleanup(pSnd);
					mem_free_dbg(file);
				}
			}
		}
	}
}

void PlayEffect(int i, int mode)
{
	int sndIdx, mi, lVolume, lPan;
	TSnd *snd;

	if (plr[myplr].pLvlLoad) {
		return;
	}

	sndIdx = random_(164, 2);
	if (!gbSndInited || !gbSoundOn || gbBufferMsgs) {
		return;
	}

	mi = monster[i]._mMTidx;
	snd = Monsters[mi].Snds[mode][sndIdx];
	if (!snd || snd_playing(snd)) {
		return;
	}

	if (!calc_snd_position(monster[i]._mx, monster[i]._my, &lVolume, &lPan))
		return;

	snd_play_snd(snd, lVolume, lPan);
}

BOOL calc_snd_position(int x, int y, int *plVolume, int *plPan)
{
	int pan, volume;

	x -= plr[myplr].WorldX;
	y -= plr[myplr].WorldY;

	pan = (x - y) << 8;
	*plPan = pan;

	if (abs(pan) > 6400)
		return FALSE;

	volume = abs(x) > abs(y) ? abs(x) : abs(y);
	volume <<= 6;
	*plVolume = volume;

	if (volume >= 6400)
		return FALSE;

	*plVolume = -volume;

	return TRUE;
}

void PlaySFX(int psfx)
{
	psfx = RndSFX(psfx);
	PlaySFX_priv(&sgSFX[psfx], FALSE, 0, 0);
}

void PlaySFX_priv(TSFX *pSFX, BOOL loc, int x, int y)
{
	int lPan, lVolume;

	if (plr[myplr].pLvlLoad && gbMaxPlayers != 1) {
		return;
	}
	if (!gbSndInited || !gbSoundOn || gbBufferMsgs) {
		return;
	}

	if (!(pSFX->bFlags & (SFX_STREAM | SFX_MISC)) && pSFX->pSnd != 0 && snd_playing(pSFX->pSnd)) {
		return;
	}

	lPan = 0;
	lVolume = 0;
	if (loc && !calc_snd_position(x, y, &lVolume, &lPan)) {
		return;
	}

	if (pSFX->bFlags & SFX_STREAM) {
		stream_play(pSFX, lVolume, lPan);
		return;
	}

	if (!pSFX->pSnd)
		pSFX->pSnd = sound_file_load(pSFX->pszName);

	if (pSFX->pSnd)
		snd_play_snd(pSFX->pSnd, lVolume, lPan);
}

void stream_play(TSFX *pSFX, int lVolume, int lPan)
{
	BOOL success;

	/// ASSERT: assert(pSFX);
	/// ASSERT: assert(pSFX->bFlags & sfx_STREAM);
	sfx_stop();
	lVolume += sound_get_or_set_sound_volume(1);
	if (lVolume >= VOLUME_MIN) {
		if (lVolume > VOLUME_MAX)
			lVolume = VOLUME_MAX;
#ifdef _DEBUG
		SFileEnableDirectAccess(FALSE);
#endif
		success = SFileOpenFile(pSFX->pszName, &sfx_stream);
#ifdef _DEBUG
		SFileEnableDirectAccess(TRUE);
#endif
		if (!success) {
			sfx_stream = 0;
		} else {
			if (!SFileDdaBeginEx(sfx_stream, 0x40000, 0, 0, lVolume, lPan, 0))
				sfx_stop();
			else
				sfx_data_cur = pSFX;
		}
	}
}

int RndSFX(int psfx)
{
	int nRand;

	if (psfx == PS_WARR69)
		nRand = 2;
	else if (psfx == PS_WARR14)
		nRand = 3;
	else if (psfx == PS_WARR15)
		nRand = 3;
	else if (psfx == PS_WARR16)
		nRand = 3;
#ifndef SPAWN
	else if (psfx == PS_MAGE69)
		nRand = 2;
	else if (psfx == PS_ROGUE69)
		nRand = 2;
#endif
	else if (psfx == PS_SWING)
		nRand = 2;
	else if (psfx == LS_ACID)
		nRand = 2;
	else if (psfx == IS_FMAG)
		nRand = 2;
	else if (psfx == IS_MAGIC)
		nRand = 2;
	else if (psfx == IS_BHIT)
		nRand = 2;
#ifndef SPAWN
	else if (psfx == PS_WARR2)
		nRand = 3;
#endif
	else
		return psfx;
	return psfx + random_(165, nRand);
}

void PlaySfxLoc(int psfx, int x, int y)
{
	TSnd *pSnd;

	psfx = RndSFX(psfx);

	if (psfx >= 0 && psfx <= 3) {
		pSnd = sgSFX[psfx].pSnd;
		if (pSnd)
			pSnd->start_tc = 0;
	}

	PlaySFX_priv(&sgSFX[psfx], TRUE, x, y);
}

void FreeMonsterSnd()
{
	int i, j, k;

	snd_update(TRUE);
	sfx_stop();
	sound_stop();

	for (i = 0; i < nummtypes; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 2; k++) {
				snd_stop_snd(Monsters[i].Snds[j][k]);
			}
		}
	}
}

void sound_stop()
{
	int i;
	TSFX *snd;

	snd = &sgSFX[0];
	for (i = 0; i < sizeof(sgSFX) / sizeof(TSFX); i++) {
		if (snd->pSnd)
			snd_stop_snd(snd->pSnd);
		snd++;
	}
}

void sound_update()
{
	if (!gbSndInited) {
		return;
	}

	snd_update(FALSE);
	effects_update();
}

void effects_update()
{
	DWORD current, end;

	if (sfx_stream != NULL && SFileDdaGetPos(sfx_stream, &current, &end) && current >= end) {
		sfx_stop();
	}
}

void effects_cleanup_sfx()
{
	DWORD i;

	FreeMonsterSnd();

	for (i = 0; i < sizeof(sgSFX) / sizeof(TSFX); i++) {
		if (sgSFX[i].pSnd) {
			sound_file_cleanup(sgSFX[i].pSnd);
			sgSFX[i].pSnd = NULL;
		}
	}
}

void stream_update()
{
	BYTE mask = 0;
	if (gbMaxPlayers > 1) {
		mask = SFX_WARRIOR | SFX_ROGUE | SFX_SORCEROR;
	} else if (plr[myplr]._pClass == PC_WARRIOR) {
		mask = SFX_WARRIOR;
	} else if (plr[myplr]._pClass == PC_ROGUE) {
		mask = SFX_ROGUE;
	} else if (plr[myplr]._pClass == PC_SORCERER) {
		mask = SFX_SORCEROR;
	} else {
		app_fatal("effects:1");
	}

	priv_sound_init(mask);
}

void priv_sound_init(BYTE bLoadMask)
{
	BYTE pc;
	DWORD i;

	if (!gbSndInited) {
		return;
	}

	pc = bLoadMask & (SFX_ROGUE | SFX_WARRIOR | SFX_SORCEROR);
	bLoadMask ^= pc;

	for (i = 0; i < sizeof(sgSFX) / sizeof(TSFX); i++) {
		if (sgSFX[i].pSnd) {
			continue;
		}

		if (sgSFX[i].bFlags & SFX_STREAM) {
			continue;
		}

		if (bLoadMask && !(sgSFX[i].bFlags & bLoadMask)) {
			continue;
		}

		if (sgSFX[i].bFlags & (SFX_ROGUE | SFX_WARRIOR | SFX_SORCEROR) && !(sgSFX[i].bFlags & pc)) {
			continue;
		}

		sgSFX[i].pSnd = sound_file_load(sgSFX[i].pszName);
	}
}

void sound_init()
{
	priv_sound_init(SFX_UI);
}

void __stdcall effects_play_sound(char *snd_file)
{
	DWORD i;

	if (!gbSndInited || !gbSoundOn) {
		return;
	}

	for (i = 0; i < sizeof(sgSFX) / sizeof(TSFX); i++) {
		if (!_strcmpi(sgSFX[i].pszName, snd_file) && sgSFX[i].pSnd) {
			if (!snd_playing(sgSFX[i].pSnd))
				snd_play_snd(sgSFX[i].pSnd, 0, 0);

			return;
		}
	}
}
