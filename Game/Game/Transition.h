#ifndef TRANSITION_H
#define TRANSITION_H

#include <iostream>
#include <string>
#include <SDL.h>

class Transition
{
public:
	Transition(int DELTA_TIME, int x, int y);

	void render(SDL_Renderer* ren);

	int StartTransition() { return transitionValue = 0; }
	int getTransitionValue() const { return alpha_Channel; }

private:
	Uint8 alpha_Channel;
	int time_delta;
	int transitionValue;
	int x;
	int y;
};
#endif // TRANSITION_H