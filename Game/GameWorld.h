#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <SDL.h>
#include <iostream>

#include "object.h"
#include "entity.h"
#include "tilemap.h"

#define GRAVITY 15
/*
	Game world, used to load in Tilemap, Player, Coin(s), and Enemy(s)
*/

class GameWorld
{
public:
	GameWorld(SDL_Renderer* ren);

	bool init(SDL_Renderer* ren);

	void input(SDL_Event event);
	void update();
	void render(SDL_Renderer* ren);
};
#endif // GAMEWORLD_H