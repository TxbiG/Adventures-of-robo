#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

class audio
{
public:
	audio(const char* filename);

	void loadSound(const char* filename);
	void loadMusic(const char* filename);

	void playSound(const int value);
	void playMusic(const int value);

private:
	std::vector<Mix_Chunk*> soundBank;
	std::vector<Mix_Music*> musicBank;

};
#endif //AUDIO_H