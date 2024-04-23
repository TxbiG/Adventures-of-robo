#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
	SDL_Surface* surface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(game::renderer, surface);
	SDL_FreeSurface(surface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(game::renderer, texture, &src, &dest);
}