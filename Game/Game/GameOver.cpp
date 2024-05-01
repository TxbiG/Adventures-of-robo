#include "GameOver.h"

GameOver::GameOver(const char* msg, SDL_Renderer * ren)
{
	if (!ren)
	{
		std::cout << "Failed to find renderer" << std::endl;
		return;
	};

	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	TTF_Font* m_font = TTF_OpenFont("assets/font.ttf", 50);

	UI* splash1 = new UI("Game Over!", 640, 480, m_font);
	UI* splash2 = new UI(msg, 640, 580, m_font);

	splash1->render(ren);
	splash2->render(ren);

	SDL_RenderPresent(ren);
}
