#include "UI.h"

UI::UI(int x, int y, TTF_Font* font)
{
	if (!font) { std::cout << "Failed to find font path" << std::endl; return; }
	m_font = font;
	this->x = x;
	this->y = y;
}
// Draws the UI
UI::UI(const char* word, int x, int y, TTF_Font* font)
{
	if (!font) { std::cout << "Failed to find font path" << std::endl; return; }
	m_font = font;

	this->surface = TTF_RenderText_Solid(m_font, word, text_colour);

	this->x = x;
	this->y = y;
}

UI::~UI()
{
	TTF_CloseFont(m_font);
}

void UI::update(const char* words)
{
	surface = TTF_RenderText_Solid(m_font, words, text_colour);
}

void UI::render(SDL_Renderer* ren)
{
	rect = { (x - surface->w) / 2, (y - surface->h) / 2, surface->w, surface->h };
	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_RenderCopy(ren, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

