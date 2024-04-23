#pragma once
#include "game.h"
#include "SDL_image.h"
class TextureManager
{
public:
	SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};