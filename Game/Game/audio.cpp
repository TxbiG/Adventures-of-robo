#include "audio.h"

audio::audio(const char* filename)
{
	Mix_Chunk* sfx = NULL;
	sfx = Mix_LoadWAV(filename);

	if (sfx == NULL) { printf("Failed to load mix chunk audio file: %s\n", Mix_GetError()); return; }

	soundBank.push_back(sfx);
}

void audio::loadSound(const char* filename)
{
	Mix_Chunk* sfx = NULL;
	sfx = Mix_LoadWAV(filename);

	if (sfx == NULL) { printf("Failed to load mix chunk audio file: %s\n", Mix_GetError()); return; }

	soundBank.push_back(sfx);
}

void audio::loadMusic(const char* filename)
{
	Mix_Music* music = NULL;
	music = Mix_LoadMUS(filename);

	if (music == NULL) { printf("Failed to load mix music audio file: %s\n", Mix_GetError()); return; }

	musicBank.push_back(music);
}

void audio::playSound(const int value)
{
	if (value > soundBank.size() - 1)
	{ std::cout << "Audio value is out of range for chunk audio" << std::endl; return; }

	Mix_PlayChannel(-1, soundBank[value], 0);
}

void audio::playMusic(const int value)
{
	if (value > musicBank.size() - 1)
	{ std::cout << "Audio value is out of range for Mix music" << std::endl; }
}
