#include "audio.h"

void audio::loadSound(const char* filename)
{
	Mix_Chunk* sfx = NULL;
	sfx = Mix_LoadWAV(filename);

	if (sfx == NULL) { printf("Failed to load mix chunk audio file: %s\n", Mix_GetError()); return; }

	soundBank = sfx;
}

void audio::loadMusic(const char* filename)
{
	Mix_Chunk* music = NULL;
	music = Mix_LoadWAV(filename);

	if (music == NULL) { printf("Failed to load mix music audio file: %s\n", Mix_GetError()); return; }

	musicBank = music;
}

void audio::playSound()
{
	Mix_PlayChannel(-1, soundBank, 0);
}

void audio::playMusic()
{
	musicBank->volume = 6;
	Mix_PlayChannel(1, musicBank, 1);
}
