#include "Timer.h"

Timer::Timer()
{
	this->startTicks = 0;
}

void Timer::resetTicks()
{
	startTicks = SDL_GetTicks();			// set the numbers of milli-seconds since start of SDL program
}

int Timer::getTicks() const
{
	return (SDL_GetTicks() - startTicks);	// returns the current time minus the start time
}
