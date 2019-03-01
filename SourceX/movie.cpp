#include "../3rdParty/libsmacker/smacker.h"
#include "pch.h"

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
	/* arrays for audio track metadata */
	unsigned char a_trackmask, a_channels[7], a_depth[7];
	unsigned long a_rate[7];

	unsigned char *palette_data;

	smk smacker;

	smacker = smk_open_memory(fileBuffer, bytestoread);
	if (smacker != NULL) {
		double usPerFrame;
		smk_info_all(smacker, NULL, &nFrames, &usPerFrame);
		smk_info_audio(smacker, &a_trackmask, a_channels, a_depth, a_rate);

		if (a_depth[0] && Mix_OpenAudio(a_rate[0], a_depth[0] == 16 ? AUDIO_S16LSB : AUDIO_U8, a_channels[0], 1024) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		smk_enable_audio(smacker, 0, true);
		smk_first(smacker); // Decode first frame

		char *audioBuffer = (char *)DiabloAllocPtr((nFrames + 15) * 3000); // first frame is 16x, 3000 looks like a safe perframe size
		unsigned char *chunkBuffer = smk_get_audio(smacker, 0);
		int audioIdx = 0;
		do {
			for (int i = 0; i < smk_get_audio_size(smacker, 0); i++, audioIdx++) {
				audioBuffer[audioIdx] = chunkBuffer[i];
			}
		} while (smk_next(smacker) != SMK_DONE);

		Mix_Chunk *Song = Mix_QuickLoad_RAW(audioBuffer, audioIdx);

		smk_enable_audio(smacker, 0, false);
		smk_enable_video(smacker, true);
		smk_first(smacker); // Rewind

		smk_info_video(smacker, &width, &height, NULL);
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		SDL_RenderSetLogicalSize(renderer, width, height);

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

		Mix_PlayChannel(-1, Song, 0);

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
				ApplyGamma(logical_palette, orig_palette, 256);

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
		} while (smk_next(smacker) != SMK_DONE && movie_playing);

		smk_close(smacker);

		SDL_DestroyTexture(texture);
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (a_depth[0] && Mix_OpenAudio(44100, AUDIO_S16LSB, 2, 1024) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
}
