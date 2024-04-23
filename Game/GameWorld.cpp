#include "GameWorld.h"

GameWorld::GameWorld(SDL_Renderer* ren)
{
}

bool GameWorld::init(SDL_Renderer* ren)
{
	
}
void GameWorld::input(SDL_Event event)
{

}

void GameWorld::update()
{
	/*
	for (int i = 0; i < map.map.size(); i++)
	{
		if (collisionTile(player, map.map[i]))
		{
			// WARNING: Only get floor not ceiling or wall
			if (map.map[i].getSolid()) { isFalling = false; }
			else { isFalling = true; }
		}
	}

	if (collision(player, coin))
	{
		// Delete coin object
		delete coin;
		score += 10;
	}
	if (collision(player, flag))
	{
		// Change level
	}
	*/
}

void GameWorld::render(SDL_Renderer* ren)
{
}