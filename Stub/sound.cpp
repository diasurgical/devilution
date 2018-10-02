#include "../types.h"
#include "stubs.h"

#ifndef NO_GLOBALS
char gbSndInited;
char gbDupSounds;
UCHAR gbMusicOn;
UCHAR gbSoundOn;
#endif

void __fastcall snd_init(HWND hWnd)
{
	DUMMY();
}

void __fastcall music_start(int nTrack)
{
	DUMMY();
}

void __cdecl music_stop()
{
	DUMMY();
}

BOOL __fastcall snd_playing(TSnd *pSnd)
{
	UNIMPLEMENTED();
}

void __fastcall snd_play_snd(TSnd *pSnd, int lVolume, int lPan)
{
	UNIMPLEMENTED();
}

void __fastcall snd_stop_snd(TSnd *pSnd)
{
	DUMMY();
}

TSnd *__fastcall sound_file_load(char *path)
{
	UNIMPLEMENTED();
}

void __fastcall sound_file_cleanup(TSnd *sound_file)
{
	UNIMPLEMENTED();
}

int __fastcall sound_get_or_set_sound_volume(int volume)
{
	DUMMY_PRINT("volume: %d", volume);
	return volume;
}

int __fastcall sound_get_or_set_music_volume(int volume)
{
	DUMMY_PRINT("volume: %d", volume);
	return volume;
}

void __fastcall snd_update(BOOL bStopAll)
{
	DUMMY_PRINT("stopall: %d", bStopAll);
}
