#include "Transition.h"

Transition::Transition(int DELTA_TIME, int x, int y)
{
	this->alpha_Channel = 0;
	this->time_delta = DELTA_TIME;
	this->transitionValue = 2;
	this->x = x;
	this->y = y;
}

void Transition::render(SDL_Renderer* ren)
{
	switch (transitionValue)
	{
	case 0:
		alpha_Channel += time_delta / 4;
		if (alpha_Channel >= 255) { transitionValue = 1; }
		break;
	case 1:
		alpha_Channel -= time_delta / 4;
		if (alpha_Channel <= 0) { transitionValue = 2; }
		break;
	case 2:
		alpha_Channel = 0;
		break;
	}
	SDL_SetRenderDrawColor(ren, 0, 0, 0, alpha_Channel);
	SDL_Rect rect{};
	rect.x = rect.y = 0;
	rect.w = x;
	rect.h = y;
	SDL_RenderFillRect(ren, &rect);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
}