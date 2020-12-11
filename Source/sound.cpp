/**
 * @file sound.cpp
 *
 * Implementation of functions setting up the audio pipeline.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

/** Contains the audio channels used for playback of sounds. */
LPDIRECTSOUNDBUFFER DSBs[8];
LPDIRECTSOUND sglpDS;
BOOLEAN gbSndInited;
int sglMusicVolume;
int sglSoundVolume;
/** Provides a handle to the dynamic library dsound.dll. */
HMODULE hDsound_dll;
/** Specifies whether background music is enabled. */
HANDLE sghMusic;
LPDIRECTSOUNDBUFFER sglpDSB;

/* data */

BOOLEAN gbMusicOn = TRUE;
/** Specifies whether sound effects are enabled. */
BOOLEAN gbSoundOn = TRUE;
/** Specifies that no duplicate audio channel should be used. */
BOOLEAN gbDupSounds = TRUE;
/** Specifies the active background music track id. */
int sgnMusicTrack = NUM_MUSIC;
/** Maps from track ID to track name. */
const char *const sgszMusicTracks[NUM_MUSIC] = {
#ifdef SPAWN
	"Music\\sTowne.wav",
	"Music\\sLvlA.wav",
	"Music\\sLvlA.wav",
	"Music\\sLvlA.wav",
	"Music\\sLvlA.wav",
#ifdef HELLFIRE
	"Music\\sLvlA.wav",
	"Music\\sLvlA.wav",
#endif
	"Music\\sintro.wav",
#else
	"Music\\DTowne.wav",
	"Music\\DLvlA.wav",
	"Music\\DLvlB.wav",
	"Music\\DLvlC.wav",
	"Music\\DLvlD.wav",
#ifdef HELLFIRE
	"Music\\DLvlE.wav",
	"Music\\DLvlF.wav",
#endif
	"Music\\Dintro.wav",
#endif
};
char unk_volume[4][2] = {
	{ 15, -16 },
	{ 15, -16 },
	{ 30, -31 },
	{ 30, -31 }
};

void snd_update(BOOL bStopAll)
{
	DWORD dwStatus, i;

	for (i = 0; i < 8; i++) {
		if (!DSBs[i])
			continue;

		if (!bStopAll && DSBs[i]->GetStatus(&dwStatus) == DS_OK && dwStatus == DSBSTATUS_PLAYING)
			continue;

		DSBs[i]->Stop();
		DSBs[i]->Release();

		DSBs[i] = NULL;
	}
}

static LPDIRECTSOUNDBUFFER sound_dup_channel(LPDIRECTSOUNDBUFFER DSB)
{
	DWORD i;

	if (!gbDupSounds) {
		return NULL;
	}

	for (i = 0; i < 8; i++) {
		if (!DSBs[i]) {
			if (sglpDS->DuplicateSoundBuffer(DSB, &DSBs[i]) != DS_OK) {
				return NULL;
			}

			return DSBs[i];
		}
	}

	return NULL;
}

static void snd_get_volume(const char *value_name, int *value)
{
	int v = *value;
	if (!SRegLoadValue(APP_NAME, value_name, 0, &v)) {
		v = VOLUME_MAX;
	}
	*value = v;

	if (*value < VOLUME_MIN) {
		*value = VOLUME_MIN;
	} else if (*value > VOLUME_MAX) {
		*value = VOLUME_MAX;
	}
	*value -= *value % 100;
}

static void snd_set_volume(const char *key, int value)
{
	SRegSaveValue(APP_NAME, key, 0, value);
}

static BOOL sound_file_reload(TSnd *sound_file, LPDIRECTSOUNDBUFFER DSB)
{
	HANDLE file;
	LPVOID buf1, buf2;
	DWORD size1, size2;
	BOOL rv;
	HRESULT error_code;

	if (DSB->Restore() != DS_OK)
		return FALSE;

	rv = FALSE;

	WOpenFile(sound_file->sound_path, &file, FALSE);
	WSetFilePointer(file, sound_file->chunk.dwOffset, NULL, FILE_BEGIN);

	error_code = DSB->Lock(0, sound_file->chunk.dwSize, &buf1, &size1, &buf2, &size2, 0);
	if (error_code == DS_OK) {
		WReadFile(file, buf1, size1);
		error_code = DSB->Unlock(buf1, size1, buf2, size2);
		if (error_code == DS_OK)
			rv = TRUE;
	}

	WCloseFile(file);

	return rv;
}

void snd_stop_snd(TSnd *pSnd)
{
	if (pSnd && pSnd->DSB)
		pSnd->DSB->Stop();
}

BOOL snd_playing(TSnd *pSnd)
{
	DWORD dwStatus;

	if (!pSnd)
		return FALSE;

	if (pSnd->DSB == NULL)
		return FALSE;

	if (pSnd->DSB->GetStatus(&dwStatus) != DS_OK)
		return FALSE;

	return dwStatus == DSBSTATUS_PLAYING;
}

void snd_play_snd(TSnd *pSnd, int lVolume, int lPan)
{
	LPDIRECTSOUNDBUFFER DSB;
	DWORD tc;
	HRESULT error_code;

	if (!pSnd || !gbSoundOn) {
		return;
	}

	DSB = pSnd->DSB;
	if (DSB == NULL) {
		return;
	}

	tc = GetTickCount();
	if (tc - pSnd->start_tc < 80) {
		GetTickCount(); // BUGFIX: unnecessary GetTickCount
		return;
	}

	if (snd_playing(pSnd)) {
		DSB = sound_dup_channel(pSnd->DSB);
		if (DSB == NULL) {
			return;
		}
	}

	lVolume += sglSoundVolume;
	if (lVolume < VOLUME_MIN) {
		lVolume = VOLUME_MIN;
	} else if (lVolume > VOLUME_MAX) {
		lVolume = VOLUME_MAX;
	}
	DSB->SetVolume(lVolume);
	DSB->SetPan(lPan);

	error_code = DSB->Play(0, 0, 0);

	if (error_code != DSERR_BUFFERLOST) {
		if (error_code != DS_OK) {
			DSErrMsg(error_code, 261, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
		}
	} else if (sound_file_reload(pSnd, DSB)) {
		DSB->Play(0, 0, 0);
	}

	pSnd->start_tc = tc;
}

static void sound_CreateSoundBuffer(TSnd *sound_file)
{
	DSBUFFERDESC DSB;
	HRESULT error_code;
	memset(&DSB, 0, sizeof(DSBUFFERDESC));

	DSB.dwSize = sizeof(DSBUFFERDESC);
	DSB.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_STATIC;
	DSB.dwBufferBytes = sound_file->chunk.dwSize;
	DSB.lpwfxFormat = &sound_file->fmt;
	error_code = sglpDS->CreateSoundBuffer(&DSB, &sound_file->DSB, NULL);
	if (error_code != ERROR_SUCCESS)
		DSErrMsg(error_code, 282, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
}

TSnd *sound_file_load(const char *path)
{
	HANDLE file;
	BYTE *wave_file;
	TSnd *pSnd;
	LPVOID buf1, buf2;
	DWORD size1, size2;
	HRESULT error_code;

	if (!sglpDS)
		return NULL;

	WOpenFile(path, &file, FALSE);
	pSnd = (TSnd *)DiabloAllocPtr(sizeof(TSnd));
	memset(pSnd, 0, sizeof(TSnd));
	pSnd->sound_path = path;
	pSnd->start_tc = GetTickCount() - 80 - 1;

	wave_file = LoadWaveFile(file, &pSnd->fmt, &pSnd->chunk);
	if (!wave_file)
		app_fatal("Invalid sound format on file %s", pSnd->sound_path);

	sound_CreateSoundBuffer(pSnd);

	error_code = pSnd->DSB->Lock(0, pSnd->chunk.dwSize, &buf1, &size1, &buf2, &size2, 0);
	if (error_code != DS_OK)
		DSErrMsg(error_code, 318, "C:\\Src\\Diablo\\Source\\SOUND.CPP");

	memcpy(buf1, wave_file + pSnd->chunk.dwOffset, size1);

	error_code = pSnd->DSB->Unlock(buf1, size1, buf2, size2);
	if (error_code != DS_OK)
		DSErrMsg(error_code, 325, "C:\\Src\\Diablo\\Source\\SOUND.CPP");

	mem_free_dbg((void *)wave_file);
	WCloseFile(file);

	return pSnd;
}

void sound_file_cleanup(TSnd *sound_file)
{
	if (sound_file) {
		if (sound_file->DSB) {
			sound_file->DSB->Stop();
			sound_file->DSB->Release();
			sound_file->DSB = NULL;
		}

		mem_free_dbg(sound_file);
	}
}

static void sound_create_primary_buffer(HANDLE music_track)
{
	HRESULT error_code;
	DSBUFFERDESC dsbuf;
	WAVEFORMATEX format;

	if (music_track == NULL) {
		memset(&dsbuf, 0, sizeof(DSBUFFERDESC));
		dsbuf.dwSize = sizeof(DSBUFFERDESC);
		dsbuf.dwFlags = DSBCAPS_PRIMARYBUFFER;

		error_code = sglpDS->CreateSoundBuffer(&dsbuf, &sglpDSB, NULL);
		if (error_code != DS_OK)
			DSErrMsg(error_code, 375, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
	}

	if (sglpDSB) {
		DSCAPS dsbcaps;
		dsbcaps.dwSize = sizeof(DSCAPS);

		error_code = sglpDS->GetCaps(&dsbcaps);
		if (error_code != DS_OK)
			DSErrMsg(error_code, 383, "C:\\Src\\Diablo\\Source\\SOUND.CPP");

		if (!music_track || !LoadWaveFormat(music_track, &format)) {
			memset(&format, 0, sizeof(WAVEFORMATEX));
			format.wFormatTag = WAVE_FORMAT_PCM;
			format.nSamplesPerSec = 22050;
			format.wBitsPerSample = 16;
			format.cbSize = 0;
		}

		format.nChannels = 2;
		format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
		format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

		sglpDSB->SetFormat(&format);
	}
}

static HRESULT sound_DirectSoundCreate(LPGUID lpGuid, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
{
	HRESULT(WINAPI * DirectSoundCreate)
	(LPGUID lpGuid, LPDIRECTSOUND * ppDS, LPUNKNOWN pUnkOuter);

	if (hDsound_dll == NULL) {
		hDsound_dll = LoadLibrary("dsound.dll");
	}
	if (hDsound_dll == NULL) {
		ErrDlg(IDD_DIALOG5, GetLastError(), "C:\\Src\\Diablo\\Source\\SOUND.CPP", 422);
	}

	DirectSoundCreate = (HRESULT(WINAPI *)(LPGUID, LPDIRECTSOUND *, LPUNKNOWN))GetProcAddress(hDsound_dll, "DirectSoundCreate");
	if (DirectSoundCreate == NULL) {
		ErrDlg(IDD_DIALOG5, GetLastError(), "C:\\Src\\Diablo\\Source\\SOUND.CPP", 427);
	}
	return DirectSoundCreate(lpGuid, ppDS, pUnkOuter);
}

void snd_init(HWND hWnd)
{
	int error_code;
	snd_get_volume("Sound Volume", &sglSoundVolume);
	gbSoundOn = sglSoundVolume > VOLUME_MIN;

	snd_get_volume("Music Volume", &sglMusicVolume);
	gbMusicOn = sglMusicVolume > VOLUME_MIN;

	error_code = sound_DirectSoundCreate(NULL, &sglpDS, NULL);
	if (error_code != DS_OK)
		sglpDS = NULL;

	if (sglpDS && sglpDS->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE) == DS_OK)
		sound_create_primary_buffer(NULL);

	SVidInitialize(sglpDS);
	SFileDdaInitialize(sglpDS);

	gbSndInited = sglpDS != NULL;
}

void sound_cleanup()
{
	snd_update(TRUE);
	SVidDestroy();
	SFileDdaDestroy();

	if (sglpDS) {
		sglpDS->Release();
		sglpDS = NULL;
	}

	if (gbSndInited) {
		gbSndInited = FALSE;
		snd_set_volume("Sound Volume", sglSoundVolume);
		snd_set_volume("Music Volume", sglMusicVolume);
	}
}

void music_stop()
{
	if (sghMusic) {
		SFileDdaEnd(sghMusic);
		SFileCloseFile(sghMusic);
		sghMusic = NULL;
		sgnMusicTrack = NUM_MUSIC;
	}
}

void music_start(int nTrack)
{
	BOOL success;

	assert((DWORD)nTrack < NUM_MUSIC);
	music_stop();
	if (sglpDS && gbMusicOn) {
#ifdef _DEBUG
		SFileEnableDirectAccess(FALSE);
#endif
		success = SFileOpenFile(sgszMusicTracks[nTrack], &sghMusic);
#ifdef _DEBUG
		SFileEnableDirectAccess(TRUE);
#endif
		sound_create_primary_buffer(sghMusic);
		if (!success) {
			sghMusic = NULL;
		} else {
			SFileDdaBeginEx(sghMusic, 0x40000, 0x40000, 0, sglMusicVolume, 0, 0);
			sgnMusicTrack = nTrack;
		}
	}
}

void sound_disable_music(BOOL disable)
{
	if (disable) {
		music_stop();
	} else if (sgnMusicTrack != NUM_MUSIC) {
		music_start(sgnMusicTrack);
	}
}

int sound_get_or_set_music_volume(int volume)
{
	if (volume == 1)
		return sglMusicVolume;

	sglMusicVolume = volume;

	if (sghMusic)
		SFileDdaSetVolume(sghMusic, volume, 0);

	return sglMusicVolume;
}

int sound_get_or_set_sound_volume(int volume)
{
	if (volume == 1)
		return sglSoundVolume;

	sglSoundVolume = volume;

	return sglSoundVolume;
}
