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

	int StartTransition() { return transitionValue = 0; } // starts transision
	int getTransitionValue() const { return alpha_Channel; } // Checks for the right time to switch change/restart world

private:
	Uint8 alpha_Channel;				// Used to get the alpha channel of transition
	int time_delta;						// Used to set how fast transition will be
	int transitionValue;				// Used for starting transition
	int x;								// Used for the width of screen
	int y;								// USed for the height of screen
};
#endif // TRANSITION_H