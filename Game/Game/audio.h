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
	void loadSound(const char* filename);			// load sound from file path
	void loadMusic(const char* filename);			// load music from file path


	void playSound();							// Play sound audio
	void playMusic();			// Play music audio

private:
	Mix_Chunk* soundBank;						// Sound bank
	Mix_Chunk* musicBank;			// Music bank

};
#endif //AUDIO_H