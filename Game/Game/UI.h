#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class UI
{
public:
	UI(const char* word, int x, int y, TTF_Font* font);
	~UI();

	void update(const char* words);
	void render(SDL_Renderer* ren);

	SDL_Color text_colour = { 255, 255, 255 };
	SDL_Rect rect = {};
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	TTF_Font* m_font = nullptr;
};
#endif // UI_H