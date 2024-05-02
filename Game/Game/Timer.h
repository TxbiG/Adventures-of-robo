#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <SDL.h>

class Timer
{
public:
	Timer();						// Timer constructor

	void resetTicks();				// resets timer to zero
	int getTicks() const;			// returns how much time has passed since timer has been reset

private:
	int startTicks;					// SDL timer
};
#endif // TIMER_H