#include "pch.h"
#include "../3rdParty/libsmacker/smacker.h"

BYTE movie_playing;
BOOL loop_movie; // TODO

void __fastcall play_movie(char *pszMovie, BOOL user_can_close)
{
	DUMMY_PRINT("%s", pszMovie);

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 320, 156);
	SDL_RenderSetLogicalSize(renderer, 320, 156);
	void *video_stream;

	movie_playing = TRUE;
	//sound_disable_music(TRUE);
	sfx_stop();
	effects_play_sound("Sfx\\Misc\\blank.wav");

	HANDLE directsound;
	SFileOpenFile(pszMovie, &directsound);

	char *fileBuffer;

	int bytestoread = SFileGetFileSize(directsound, 0);
	fileBuffer = DiabloAllocPtr(bytestoread);
	SFileReadFile(directsound, fileBuffer, bytestoread, NULL, 0);
	if (Mix_OpenAudio(22050, AUDIO_S16LSB, 1, 512) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	/* file meta-info */
	unsigned long width, height, nFrames;
	/* arrays for audio track metadata */
	unsigned char a_trackmask, a_channels[7], a_depth[7];
	unsigned long a_rate[7];

	unsigned char *palette_data;

	smk smacker;

	smacker = smk_open_memory(fileBuffer, bytestoread);
	if (smacker != NULL) {
		int now;
		double usPerFrame;

		smk_enable_all(smacker, -1);
		smk_info_all(smacker, NULL, &nFrames, &usPerFrame);
		smk_info_video(smacker, &width, &height, NULL);
		smk_info_audio(smacker, &a_trackmask, a_channels, a_depth, a_rate);

		printf("Audio info for track 0: bit-depth %u, channels %u, rate %u\n", a_depth[0], a_channels[0], a_rate[0]);

		smk_first(smacker);

		SDL_Event event;
		double frameEnd = SDL_GetTicks() * 1000 + usPerFrame;
		for (int f = 0; f < nFrames && movie_playing; f++) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONDOWN:
					movie_playing = false;
					break;
				case SDL_QUIT:
					exit(0);
				}
			}

			now = SDL_GetTicks() * 1000;
			if (now >= frameEnd) {
				continue; // Skip audio and video if the system is to slow
			}

			Mix_Chunk *Song = Mix_QuickLoad_RAW(smk_get_audio(smacker, 0), smk_get_audio_size(smacker, 0));
			Mix_PlayChannel(-1, Song, 0);
			now = SDL_GetTicks() * 1000;
			if (now >= frameEnd) {
				continue; // Skip video if system is to slow
			}

			/* Retrieve the palette and image */
			palette_data = smk_get_palette(smacker);
			for (int i = 0; i < 256; i++) {
				orig_palette[i].peFlags = 0;
				orig_palette[i].peRed = palette_data[i * 3 + 0];
				orig_palette[i].peGreen = palette_data[i * 3 + 1];
				orig_palette[i].peBlue = palette_data[i * 3 + 2];
			}
			ApplyGamma(logical_palette, orig_palette, 256);

			// Copy frame to buffer
			BYTE *src = (BYTE *)smk_get_video(smacker);
			BYTE *dst = (BYTE *)&gpBuffer->row[0].pixels[0];
			for (int i = 0; i < height && i < SCREEN_HEIGHT; i++, src += width, dst += ROW_PITCH) {
				for (int j = 0; j < width && j < SCREEN_WIDTH; j++) {
					dst[j] = src[j];
				}
			}

			SetFadeLevel(256); // present frame

			smk_next(smacker); // Decode next frame
			now = SDL_GetTicks() * 1000;
			if (now < frameEnd) {
				usleep(frameEnd - now); // wait with next frame if the system is to fast
			}
			frameEnd += usPerFrame;
		}

		smk_close(smacker);
	}

	Mix_CloseAudio();
	if (Mix_OpenAudio(44100, AUDIO_S16LSB, 2, 1024) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
