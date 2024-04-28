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


	UI* splash1 = new UI("Adventures of robo", 640, 480, TTF_OpenFont("assets/font.ttf", 50));
	UI* splash2 = new UI("Controls", 610, 610, TTF_OpenFont("assets/font.ttf", 30));
	UI* splash3 = new UI("Left: A", 570, 670, TTF_OpenFont("assets/font.ttf", 18));
	UI* splash4 = new UI("Right: D", 560, 730, TTF_OpenFont("assets/font.ttf", 18));
	UI* splash5 = new UI("Jump: Space", 590, 790, TTF_OpenFont("assets/font.ttf", 18));
	UI* splash6 = new UI("Grab: LShift", 590, 850, TTF_OpenFont("assets/font.ttf", 18));
	UI* splash7 = new UI("Dash: Ctrl", 580, 910, TTF_OpenFont("assets/font.ttf", 18));

	splash1->render(ren);
	splash2->render(ren);
	splash3->render(ren);
	splash4->render(ren);
	splash5->render(ren);
	splash6->render(ren);
	splash7->render(ren);

	SDL_RenderPresent(ren);
}