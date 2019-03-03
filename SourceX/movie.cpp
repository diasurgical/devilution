#include "../3rdParty/libsmacker/smacker.h"
#include "pch.h"

PALETTEENTRY previousPalette[256];
BYTE movie_playing;
BOOL loop_movie; // TODO

void __fastcall play_movie(char *pszMovie, BOOL user_can_close)
{
	DUMMY_PRINT("%s", pszMovie);

	void *video_stream;

	movie_playing = TRUE;
	sound_disable_music(TRUE);
	sfx_stop();
	effects_play_sound("Sfx\\Misc\\blank.wav");

	HANDLE directsound;
	SFileOpenFile(pszMovie, &directsound);

	BYTE *fileBuffer;

	int bytestoread = SFileGetFileSize(directsound, 0);
	fileBuffer = DiabloAllocPtr(bytestoread);
	SFileReadFile(directsound, fileBuffer, bytestoread, NULL, 0);

	/* file meta-info */
	unsigned long width, height, nFrames;
	unsigned char a_channels[7], a_depth[7];
	unsigned long a_rate[7];
	unsigned char *palette_data;

	smk smacker;

	smacker = smk_open_memory(fileBuffer, bytestoread);
	if (smacker != NULL) {
		double usPerFrame;
		smk_info_all(smacker, NULL, &nFrames, &usPerFrame);
		smk_info_video(smacker, &width, &height, NULL);

		smk_info_audio(smacker, NULL, a_channels, a_depth, a_rate);
		SDL_AudioDeviceID deviceId;
		if (a_depth[0] != 0) {
			SDL_AudioSpec audioFormat;
			SDL_zero(audioFormat);
			audioFormat.freq = a_rate[0];
			audioFormat.format = a_depth[0] == 16 ? AUDIO_S16 : AUDIO_U8;
			audioFormat.channels = a_channels[0];

			deviceId = SDL_OpenAudioDevice(NULL, 0, &audioFormat, NULL, 0);
			if (deviceId == 0) {
				printf("SDL_OpenAudioDevice: %s\n", SDL_GetError());
				movie_playing = false;
			} else {
				SDL_PauseAudioDevice(deviceId, 0); /* start audio playing. */
			}
		}

		smk_enable_all(smacker, -1);
		smk_first(smacker); // Decode first frame

		smk_info_video(smacker, &width, &height, NULL);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		SDL_RenderSetLogicalSize(renderer, width, height);

		memcpy(previousPalette, orig_palette, 1024);


		// Copy frame to buffer
		SDL_Surface *videoSurface = SDL_CreateRGBSurfaceWithFormatFrom(
		    smk_get_video(smacker),
		    width,
		    height,
		    8,
		    width,
		    SDL_PIXELFORMAT_INDEX8);

		SDL_Rect src_rect = { 64, 160, 0, 0 };
		SDL_Color colors[256];
		SDL_Palette *vpalette = SDL_AllocPalette(256);
		if (SDL_SetSurfacePalette(videoSurface, vpalette) != 0) {
			SDL_Log("SDL_SetSurfacePalette: %s\n", SDL_GetError());
			movie_playing = false;
		}

		int now;
		SDL_Event event;
		double frameEnd = SDL_GetTicks() * 1000 + usPerFrame;

		do {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONDOWN:
					if (user_can_close) {
						movie_playing = false;
					}
					break;
				case SDL_QUIT:
					exit(0);
				}
			}

			if (a_depth[0] != 0 && SDL_QueueAudio(deviceId, smk_get_audio(smacker, 0), smk_get_audio_size(smacker, 0)) == -1) {
				printf("SDL_QueueAudio: %s\n", SDL_GetError());
			}

			now = SDL_GetTicks() * 1000;
			if (now >= frameEnd) {
				continue; // Skip video if the system is to slow
			}

			if (smk_palette_updated(smacker)) {
				palette_data = smk_get_palette(smacker);
				for (int i = 0; i < 256; i++) {
					colors[i].r = palette_data[i * 3 + 0];
					colors[i].g = palette_data[i * 3 + 1];
					colors[i].b = palette_data[i * 3 + 2];
					colors[i].a = SDL_ALPHA_OPAQUE;

					orig_palette[i].peFlags = 0;
					orig_palette[i].peRed = palette_data[i * 3 + 0];
					orig_palette[i].peGreen = palette_data[i * 3 + 1];
					orig_palette[i].peBlue = palette_data[i * 3 + 2];
				}
				memcpy(logical_palette, orig_palette, 1024);

				if (SDL_SetPaletteColors(vpalette, colors, 0, 256) != 0) {
					SDL_Log("SDL_SetPaletteColors: %s\n", SDL_GetError());
					break;
				}
			}

			if (SDL_BlitSurface(videoSurface, NULL, pal_surface, &src_rect) != 0) {
				SDL_Log("SDL_BlitSurface: %s\n", SDL_GetError());
				break;
			}

			SetFadeLevel(256); // present frame

			now = SDL_GetTicks() * 1000;
			if (now < frameEnd) {
				usleep(frameEnd - now); // wait with next frame if the system is to fast
			}

			frameEnd += usPerFrame;
			if (smk_next(smacker) == SMK_DONE) {
				if (loop_movie)
					smk_first(smacker);
				else
					movie_playing = false;
			}
		} while (movie_playing);

		if (a_depth[0] != 0) {
			SDL_ClearQueuedAudio(deviceId);
			SDL_CloseAudioDevice(deviceId);
		}
		smk_close(smacker);

		memcpy(orig_palette, previousPalette, 1024);

		SDL_DestroyTexture(texture);
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}
