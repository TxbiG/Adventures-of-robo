#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>

class audio
{
public:
	audio();
	~audio();

	void load(const char* filename);
	void play();

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceID;
};
#endif //AUDIO_H