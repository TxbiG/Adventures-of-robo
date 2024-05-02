
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
	UI* splash2 = new UI("Controls", 610, 610, subtitle);
	UI* splash3 = new UI("Left: A", 570, 670, text);
	UI* splash4 = new UI("Right: D", 560, 730, text);
	UI* splash5 = new UI("Jump: Space", 590, 790, text);

	splash1->render(ren);
	splash2->render(ren);
	splash3->render(ren);
	splash4->render(ren);
	splash5->render(ren);

	SDL_RenderPresent(ren);
}