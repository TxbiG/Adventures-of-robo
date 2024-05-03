
#include "splashscreen.h"


splashscreen::splashscreen(SDL_Renderer* ren)
{
	if (!ren)
	{
		std::cout << "Failed to find renderer" << std::endl;
		return;
	}

	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	this->title = TTF_OpenFont("assets/font.ttf", 50);
	this->subtitle = TTF_OpenFont("assets/font.ttf", 30);
	this->text = TTF_OpenFont("assets/font.ttf", 18);

	UI* splash1 = new UI("Adventures of robo", 640, 480, title);

	splash1->render(ren);

	SDL_RenderPresent(ren);
}
