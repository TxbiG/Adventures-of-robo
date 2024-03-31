#include "GameWorld.h"

tilemap* Level;

GameWorld::GameWorld(SDL_Renderer* ren)
{
	// Get Coin(s)
	l, r, u, isFalling, disableInput = false;
	coin->setImage("assets/coin.png", ren);
	coin->setID(2);
	coin->setSource(0, 0, 32, 32);
	spin = coin->createAnimation(1, 32, 32, 4, 5);
	coin->setCurrectAnimation(spin);
	//flag
	flag->setImage("assets/Flag.png", ren);
	flag->setID(3);
	flag->setSource(0, 0, 32, 32);
	// get Player
	player->setImage("assets/Player.png", ren);
	player->setID(1);
	//player.setSource(0, 0, 32, 32);
	idle = player->createAnimation(1, 32, 32, 4, 5);
	run = player->createAnimation(2, 32, 32, 4, 5);
	jump = player->createAnimation(3, 32, 32, 0, 0);
	fall = player->createAnimation(3, 32, 32, 1, 0);
}

void GameWorld::input(SDL_Event event)
{
	if (!disableInput)
	{
		// Checks if user has pressed a key
		if (event.type == SDL_KEYDOWN) {

			if (event.key.keysym.sym == SDLK_a) { l = true; r = false; }
			else if (event.key.keysym.sym == SDLK_d) { l = false; r = true; }
			else if (event.key.keysym.sym == SDLK_SPACE && isFalling == false) { u = true; isFalling = true; }

		}
		// Checks if user has stopped pressing a key
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_a) { l = false; player->setCurrectAnimation(idle); }
			if (event.key.keysym.sym == SDLK_d) { r = false; player->setCurrectAnimation(idle); }
			if (event.key.keysym.sym == SDLK_SPACE) { u = false; }
		}
	}
}

void GameWorld::update()
{
	isFalling = true;
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
	if (isFalling) { player->setDest(player->getDX(), player->getDY() + GRAVITY); player->setCurrectAnimation(fall); }
	if (l) { if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_HORIZONTAL; } player->setDest(player->getDX() - speed, player->getDY()); }
	if (r) { if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_NONE; } player->setDest(player->getDX() + speed, player->getDY()); }
	if (u) { if (player->getCurrentAnimation() != jump) { player->setCurrectAnimation(jump); } player->setDest(player->getDX(), player->getDY() - jumpSpeed); }
	//else { player.setCurrectAnimation(fall); }

	coin->updateAnimation();
	player->updateAnimation();
}

void GameWorld::render(SDL_Renderer* ren)
{
	// World layer
	Level->drawMap(ren); // Level

	// Object layer
	coin->render(ren); // Coin
	flag->render(ren); // Change to a door
	
	// Enemy layer

	// Player layer
	player->render(ren);
}

void GameWorld::loadWorld(const char* LevelName, SDL_Renderer* ren)
{
	Level->loadmap(LevelName, ren); // Get map
}
