#include "UI.h"

// Draws the UI
UI::UI(const char* word, int X, int Y, TTF_Font* font)
{
	if (!font) { std::cout << "Failed to find font path" << std::endl; return; }
	m_font = font;

	surface = TTF_RenderText_Solid(m_font, word, text_colour);

	rect = { (X - surface->w) / 2, (Y - surface->h) / 2, surface->w, surface->h };
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
	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_RenderCopy(ren, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

