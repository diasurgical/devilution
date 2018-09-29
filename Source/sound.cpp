//HEADER_GOES_HERE

#include "../types.h"

float sound_cpp_init_value;
LPDIRECTSOUNDBUFFER DSBs[8];
LPDIRECTSOUND sglpDS;
char gbSndInited;
int sglMusicVolume;
int sglSoundVolume;
HMODULE hDsound_dll; // idb
void *sgpMusicTrack;
LPDIRECTSOUNDBUFFER sglpDSB;

const int sound_inf = 0x7F800000; // weak

/* data */

UCHAR gbMusicOn = 1; // weak
UCHAR gbSoundOn = 1; // weak
char gbDupSounds = 1; // weak
int sgnMusicTrack = 6;
char *sgszMusicTracks[NUM_MUSIC] =
{
  "Music\\DTowne.wav",
  "Music\\DLvlA.wav",
  "Music\\DLvlB.wav",
  "Music\\DLvlC.wav",
  "Music\\DLvlD.wav",
  "Music\\Dintro.wav"
};
char unk_volume[4][2] =
{
	{ 15, -16 },
	{ 15, -16 },
	{ 30, -31 },
	{ 30, -31 }
};

struct sound_cpp_init
{
	sound_cpp_init()
	{
		sound_cpp_init_value = sound_inf;
	}
} _sound_cpp_init;
// 47F24C: using guessed type int sound_inf;

void __fastcall snd_update(BOOL bStopAll)
{
	unsigned long error_code;

	for (DWORD i = 0; i < 8; i++) {
		if ( !DSBs[i] )
			continue;

		if ( !bStopAll && !DSBs[i]->GetStatus(&error_code) && error_code == DSBSTATUS_PLAYING )
			continue;

		DSBs[i]->Stop();
		DSBs[i]->Release();
		DSBs[i] = 0;
	}
}

void __fastcall snd_stop_snd(TSnd *pSnd)
{
	if ( pSnd && pSnd->DSB )
		pSnd->DSB->Stop();
}

BOOL __fastcall snd_playing(TSnd *pSnd)
{
	unsigned long error_code;

	if ( !pSnd )
		return FALSE;

	if ( pSnd->DSB == NULL )
		return FALSE;

	if ( pSnd->DSB->GetStatus(&error_code) )
		return FALSE;

	return error_code == DSBSTATUS_PLAYING;
}

void __fastcall snd_play_snd(TSnd *pSnd, int lVolume, int lPan)
{
	if ( !pSnd || !gbSoundOn ) {
		return;
	}

	LPDIRECTSOUNDBUFFER DSB = pSnd->DSB;
	if ( !DSB ) {
		return;
	}

	DWORD tc = GetTickCount();
	if ( tc - pSnd->start_tc < 80 ) {
		pSnd->start_tc = GetTickCount();
		return;
	}

	if ( snd_playing(pSnd) ) {
		DSB = sound_dup_channel(pSnd->DSB);
		if (DSB == 0) {
			return;
		}
	}

	lVolume += sglSoundVolume;
	if ( lVolume < -1600 ) {
		lVolume = -1600;
	} else if ( lVolume > 0 ) {
		lVolume = 0;
	}
	DSB->SetVolume(lVolume);

	DSB->SetPan(lPan);

	int error_code = DSB->Play(0, 0, 0);
	if ( error_code != DSERR_BUFFERLOST) {
		if ( error_code != DS_OK ) {
			DSErrMsg(error_code, 261, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
		}
	} else if ( sound_file_reload(pSnd, DSB) ) {
		DSB->Play(0, 0, 0);
	}

	pSnd->start_tc = tc;
}
// 4A22D5: using guessed type char gbSoundOn;

LPDIRECTSOUNDBUFFER __fastcall sound_dup_channel(LPDIRECTSOUNDBUFFER DSB)
{
	LPDIRECTSOUNDBUFFER result; // eax
	LPDIRECTSOUNDBUFFER *v2; // esi

	result = 0;
	if ( gbDupSounds )
	{
		while ( DSBs[(_DWORD)result] )
		{
			result = (LPDIRECTSOUNDBUFFER )((char *)result + 1); // result++
			if ( (unsigned int)result >= 8 )
				return 0;
		}
		v2 = &DSBs[(_DWORD)result];
		if ( sglpDS->DuplicateSoundBuffer(DSB, &DSBs[(_DWORD)result]) )
		{
			return 0;
		}
		result = *v2;
	}

	return result;
}
// 4A22D6: using guessed type char gbDupSounds;

BOOL __fastcall sound_file_reload(TSnd *sound_file, LPDIRECTSOUNDBUFFER DSB)
{
	LPDIRECTSOUNDBUFFER v2; // edi
	TSnd *v3; // esi
	char *v5; // ecx
	void *aptr2; // [esp+8h] [ebp-18h]
	unsigned long asize2; // [esp+Ch] [ebp-14h]
	BOOL v8; // [esp+10h] [ebp-10h]
	void *aptr1; // [esp+14h] [ebp-Ch]
	unsigned long asize1; // [esp+18h] [ebp-8h]
	void *a1; // [esp+1Ch] [ebp-4h]

	v2 = DSB;
	v3 = sound_file;
	if ( DSB->Restore() )
		return 0;
	v5 = v3->sound_path;
	v8 = 0;
	WOpenFile(v5, &a1, 0);
	WSetFilePointer(a1, v3->offset, 0, 0);
	if ( !v2->Lock(0, v3->len, &aptr1, &asize1, &aptr2, &asize2, 0) )
	{
		WReadFile(a1, (char *)aptr1, asize1);
		if ( !v2->Unlock(aptr1, asize1, aptr2, asize2) )
			v8 = 1;
	}
	WCloseFile(a1);
	return v8;
}

TSnd *__fastcall sound_file_load(char *path)
{
//	int v1; // esi
	char *v2; // edi
	TSnd *v4; // esi
	int v5; // eax
	int v6; // eax
//	int v7; // [esp-4h] [ebp-24h]
	void *aptr2; // [esp+8h] [ebp-18h]
	unsigned long asize2; // [esp+Ch] [ebp-14h]
	void *a1; // [esp+10h] [ebp-10h]
	void *ptr; // [esp+14h] [ebp-Ch]
	void *aptr1; // [esp+18h] [ebp-8h]
	unsigned long asize1; // [esp+1Ch] [ebp-4h]

	v2 = path;
	if ( !sglpDS )
		return 0;
//	v7 = v1;
	WOpenFile(path, &a1, 0);
	v4 = (TSnd *)DiabloAllocPtr(40);
	memset(v4, 0, 0x28u);
	v4->sound_path = v2;
	v4->start_tc = GetTickCount() - 81;
	ptr = LoadWaveFile(a1, &v4->fmt, &v4->len);
	if ( !ptr )
		TermMsg("Invalid sound format on file %s", v4->sound_path);
	sound_CreateSoundBuffer(v4);
	v5 = v4->DSB->Lock(0, v4->len, &aptr1, &asize1, &aptr2, &asize2, 0); //v7);
	if ( v5 )
		DSErrMsg(v5, 318, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
	memcpy(aptr1, (char *)ptr + v4->offset, asize1);
	v6 = v4->DSB->Unlock(aptr1, asize1, aptr2, asize2);
	if ( v6 )
		DSErrMsg(v6, 325, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
	mem_free_dbg(ptr);
	WCloseFile(a1);
	return v4;
}
// 456F07: could not find valid save-restore pair for esi

void __fastcall sound_CreateSoundBuffer(TSnd *sound_file)
{
	DSBUFFERDESC DSB;
	memset(&DSB, 0, sizeof(DSBUFFERDESC));
	DSB.dwBufferBytes = sound_file->len;
	DSB.lpwfxFormat = &sound_file->fmt;
	DSB.dwSize = sizeof(DSBUFFERDESC);
	DSB.dwFlags = DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN|DSBCAPS_STATIC;
	HRESULT hr = sglpDS->CreateSoundBuffer(&DSB, &sound_file->DSB, NULL);

	if ( hr != ERROR_SUCCESS )
		DSErrMsg(hr, 282, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
}

void __fastcall sound_file_cleanup(TSnd *sound_file)
{
	if ( sound_file ) {
		if ( sound_file->DSB ) {
			sound_file->DSB->Stop();
			sound_file->DSB->Release();
			sound_file->DSB = NULL;
		}

		mem_free_dbg(sound_file);
	}
}

void __fastcall snd_init(HWND hWnd)
{
	sound_load_volume("Sound Volume", &sglSoundVolume);
	gbSoundOn = sglSoundVolume > -1600;

	sound_load_volume("Music Volume", &sglMusicVolume);
	gbMusicOn = sglMusicVolume > -1600;

	if ( sound_DirectSoundCreate(NULL, &sglpDS, NULL) != DS_OK )
		sglpDS = NULL;

	if ( sglpDS && !sglpDS->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE) )
		sound_create_primary_buffer(0);

	SVidInitialize(sglpDS);
	SFileDdaInitialize(sglpDS);

	gbSndInited = sglpDS != NULL;
}
// 4A22D4: using guessed type char gbMusicOn;
// 4A22D5: using guessed type char gbSoundOn;

void __fastcall sound_load_volume(char *value_name, int *value)
{
	int v = *value;
	if ( !SRegLoadValue("Diablo", value_name, 0, &v) ) {
		v = 0;
	}
	*value = v;

	if ( *value < -1600 ) {
		*value = -1600;
	} else if ( *value > 0 ) {
		*value = 0;//28
	}
	*value -= *value % 100;
}

void __fastcall sound_create_primary_buffer(int music_track)
{
	int v1; // eax
	int v2; // eax
	DSCAPS v3; // [esp+4h] [ebp-8Ch]
	DSBUFFERDESC v4; // [esp+64h] [ebp-2Ch]
	int a1; // [esp+78h] [ebp-18h]
	WAVEFORMATEX a2; // [esp+7Ch] [ebp-14h]

	a1 = music_track;
	if ( !music_track )
	{
		memset(&v4, 0, sizeof(DSBUFFERDESC));
		v4.dwSize = sizeof(DSBUFFERDESC);
		v4.dwFlags = DSBCAPS_PRIMARYBUFFER;
		v1 = sglpDS->CreateSoundBuffer(&v4, &sglpDSB, NULL);
		if ( v1 )
			DSErrMsg(v1, 375, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
	}
	if ( sglpDSB )
	{
		v3.dwSize = 96;
		v2 = sglpDS->GetCaps(&v3);
		if ( v2 )
			DSErrMsg(v2, 383, "C:\\Src\\Diablo\\Source\\SOUND.CPP");
		if ( !a1 || !LoadWaveFormat((HANDLE)a1, &a2) )
		{
			memset(&a2, 0, 0x12u);
			a2.wFormatTag = WAVE_FORMAT_PCM;
			a2.nSamplesPerSec = 22050;
			a2.wBitsPerSample = 16;
			a2.cbSize = 0;
		}
		a2.nChannels = 2;
		a2.nBlockAlign = 2 * a2.wBitsPerSample / 8; /// BUGFIX: should be `a2.nChannels * a2.wBitsPerSample / 8`
		a2.nAvgBytesPerSec = a2.nSamplesPerSec * a2.nBlockAlign;
		sglpDSB->SetFormat(&a2);
	}
}
// 69F100: using guessed type int sglpDSB;

int __fastcall sound_DirectSoundCreate(LPGUID lpGuid, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
{
	if ( hDsound_dll == NULL ) {
		hDsound_dll = LoadLibrary("dsound.dll");
		if ( hDsound_dll == NULL ) {
			ErrDlg(IDD_DIALOG5, GetLastError(), "C:\\Src\\Diablo\\Source\\SOUND.CPP", 422);
		}
	}

	HRESULT (WINAPI * DirectSoundCreate)(LPGUID lpGuid, LPDIRECTSOUND* ppDS, LPUNKNOWN pUnkOuter);
	DirectSoundCreate = (HRESULT(WINAPI*)(LPGUID, LPDIRECTSOUND*, LPUNKNOWN))GetProcAddress(hDsound_dll, "DirectSoundCreate");
	if ( DirectSoundCreate == NULL ) {
		ErrDlg(IDD_DIALOG5, GetLastError(), "C:\\Src\\Diablo\\Source\\SOUND.CPP", 427);
	}
	return DirectSoundCreate(lpGuid, ppDS, pUnkOuter);
}

void __cdecl sound_cleanup()
{
	snd_update(TRUE);
	SVidDestroy();
	SFileDdaDestroy();

	if ( sglpDS ) {
		sglpDS->Release();
		sglpDS = NULL;
	}

	if ( gbSndInited ) {
		gbSndInited = FALSE;
		sound_store_volume("Sound Volume", sglSoundVolume);
		sound_store_volume("Music Volume", sglMusicVolume);
	}
}

void __fastcall sound_store_volume(char *key, int value)
{
	SRegSaveValue("Diablo", key, 0, value);
}

void __cdecl music_stop()
{
	if ( sgpMusicTrack ) {
		SFileDdaEnd(sgpMusicTrack);
		SFileCloseFile(sgpMusicTrack);
		sgpMusicTrack = 0;
		sgnMusicTrack = 6;
	}
}

void __fastcall music_start(int nTrack)
{
	music_stop();
	if ( sglpDS && gbMusicOn ) {
		BOOL success = SFileOpenFile(sgszMusicTracks[nTrack], &sgpMusicTrack);
		sound_create_primary_buffer((int)sgpMusicTrack);
		if ( !success ) {
			sgpMusicTrack = 0;
		} else {
			SFileDdaBeginEx(sgpMusicTrack, 0x40000, 0x40000, 0, sglMusicVolume, 0, 0);
			sgnMusicTrack = nTrack;
		}
	}
}
// 4A22D4: using guessed type char gbMusicOn;

void __fastcall sound_disable_music(BOOL disable)
{
	if ( disable ) {
		music_stop();
	} else if ( sgnMusicTrack != 6 ) {
		music_start(sgnMusicTrack);
	}
}

int __fastcall sound_get_or_set_music_volume(int volume)
{
	if ( volume != 1 ) {
		sglMusicVolume = volume;
		if ( sgpMusicTrack )
			SFileDdaSetVolume(sgpMusicTrack, volume, 0);
	}

	return sglMusicVolume;
}

int __fastcall sound_get_or_set_sound_volume(int volume)
{
	int result = volume;
	if ( volume == 1 )
		return sglSoundVolume;

	sglSoundVolume = volume;
	return result;
}
