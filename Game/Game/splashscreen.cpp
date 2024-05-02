#include "splashscreen.h"


splashscreen::splashscreen(SDL_Renderer* ren)
{
	if (!ren)
	{
		std::cout << "Failed to find renderer" << std::endl;
		return;
	}

	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0,0,0,255);

	title = TTF_OpenFont("assets/font.ttf", 50);

	UI* splash1 = new UI("Adventures of robo", 640, 480, title);

	splash1->render(ren);

	SDL_RenderPresent(ren);
}