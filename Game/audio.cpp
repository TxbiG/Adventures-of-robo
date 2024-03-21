#include "audio.h"

audio::audio()
{
}

// Deconstructor of the audio
audio::~audio()
{
	SDL_CloseAudioDevice(deviceID);
	SDL_FreeWAV(wavBuffer);
}

// load WAV file
void audio::load(const char* filename)
{
	SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
	deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

// Play WAV File
void audio::play()
{
	SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceID, 0);
}
