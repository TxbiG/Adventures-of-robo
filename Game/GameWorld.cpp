#include "GameWorld.h"

tilemap* map = new tilemap();

object* coin = new object();
object* flag = new object();

object* player = new object();
//entity enemy;

GameWorld::GameWorld()
{
	gKeys[SDLK_a] = false;
	gKeys[SDLK_d] = false;
	gKeys[SDLK_SPACE] = false;
	isFalling = false;
	Levelnum = 0;
}

void GameWorld::init(SDL_Renderer* ren)
{
	//map->loadmap("assets/level1.map", ren);
	load_scene(ren);

	// Get Coin(s)
	coin->setImage("assets/coin.png", ren);
	coin->setID(2);
	coin->setSource(0, 0, 32, 32);
	coin->setDest(Vector2D(542, 190), 32, 32);
	spin = coin->createAnimation(1, 32, 32, 4, 10);
	coin->setCurrectAnimation(spin);
	//flag
	flag->setImage("assets/Flag.png", ren);
	flag->setID(3);
	flag->setSource(0, 0, 32, 32);
	//flag->setDest(Vector2D(542, 96), 32, 32);
	// get Player
	player->setImage("assets/Player.png", ren);
	player->setID(1);
	//player.setSource(0, 0, 32, 32);
	player->setDest(Vector2D(150, 286), 32, 32);
	idle = player->createAnimation(1, 32, 32, 4, 10);
	run = player->createAnimation(2, 32, 32, 4, 10);
	jump = player->createAnimation(3, 32, 32, 0, 0);
	fall = player->createAnimation(3, 32, 32, 1, 0);

}
void GameWorld::input(SDL_Event _event)
{
	if (_event.type == SDL_KEYDOWN && _event.key.repeat == NULL) {
		switch (_event.key.keysym.sym)
		{
		case SDLK_a:
			gKeys[SDLK_a] = true;
			break;
		case SDLK_d:
			gKeys[SDLK_d] = true;
			break;
		case SDLK_SPACE:
			gKeys[SDLK_SPACE] = true;
			break;
		}
	}
	// Checks if user has stopped pressing a key
	if (_event.type == SDL_KEYUP && _event.key.repeat == NULL) {
		switch (_event.key.keysym.sym)
		{
		case SDLK_a:
			gKeys[SDLK_a] = false; 
			player->setCurrectAnimation(idle);
			break;
		case SDLK_d:
			gKeys[SDLK_d] = false; 
			player->setCurrectAnimation(idle);
			break;
		case SDLK_SPACE:
			gKeys[SDLK_SPACE] = false;
			break;
		}
	}
}

void GameWorld::update()
{
	isFalling = true;
	isWall = true;
	canSwitch = false;

	for (int i = 0; i < map->map.size(); i++)
	{
		if (collisionTile(player, map->map[i]))
		{
			// WARNING: Only get floor not ceiling or wall
			if (map->map[i].getSolid()) {
				isFalling = false; isWall = false;
			}
			else
			{
				isFalling = true;  isWall = true;
			}
		}
	}

	if (collision(player, coin))
	{
		// Delete coin object
		score += 10;
	}
	if (collision(player, flag))
	{
		if (isOnFlag)
		{
			// Change level
			canSwitch = true;
			setTransition();
		}
		isOnFlag = false;
	}

	if (isFalling) { player->setDest(Vector2D(player->getDX(), player->getDY() + GRAVITY)); player->setCurrectAnimation(fall); }
	if (isWall) { player->setDest(Vector2D(player->getDX(), player->getDY())); player->setCurrectAnimation(idle); }
	if (gKeys[SDLK_a]) { if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_HORIZONTAL; } player->setDest(Vector2D(player->getDX() - speed, player->getDY())); }
	if (gKeys[SDLK_d]) { if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_NONE; } player->setDest(Vector2D(player->getDX() + speed, player->getDY())); }
	if (gKeys[SDLK_SPACE]) { if (player->getCurrentAnimation() != jump) { player->setCurrectAnimation(jump); } player->setDest(Vector2D(player->getDX(), player->getDY() - jumpSpeed)); }
	//else { player->setCurrectAnimation(fall); }
	// Set based on WASD also make a grab mechanic
	//if (dash) { if (player->getCurrentAnimation() != dash) { player->setCurrectAnimation(dash); } player->setDest(Vector2D(player->getDX(), player->getDY())); }
	coin->updateAnimation();
	player->updateAnimation();
}

void GameWorld::render(SDL_Renderer* ren)
{
	// TileMap layer
	map->drawMap(ren);

	// Object layer
	coin->render(ren);
	flag->render(ren);

	// Enemy layer
	
	// Player layer
	player->render(ren);
}

bool GameWorld::collision(object* a, object* b)
{
	if ((a->getDX() < (b->getDX() + b->getDW())) && ((a->getDX() + a->getDW()) > b->getDX()) && (a->getDY() < (b->getDY() + b->getDH())) && ((a->getDY() + a->getDH()) > b->getDY())) {
		return true;
	}
	else {
		return false;
	}
}

void GameWorld::load_scene(SDL_Renderer* ren)
{
	// Use switch
	switch (Levelnum)
	{
	case 0:
		map->loadmap("assets/level1.map", ren);
		flag->setDest(Vector2D(542, 96), 32, 32);
		player->setDest(Vector2D(150, 286), 32, 32);
		coin->setDest(Vector2D(542, 190), 32, 32);
		Levelnum = 1;
		isOnFlag = true;
		break;
	case 1:
		map->loadmap("assets/level2.map", ren);
		flag->setDest(Vector2D(68, 96), 32, 32);
		player->setDest(Vector2D(150, 286), 32, 32);
		coin->setDest(Vector2D(542, 190), 32, 32);
		Levelnum = 2;
		isOnFlag = true;
		break;
	case 2:
		map->loadmap("assets/level3.map", ren);
		flag->setDest(Vector2D(68, 96), 32, 32);
		player->setDest(Vector2D(150, 286), 32, 32);
		coin->setDest(Vector2D(542, 190), 32, 32);
		break;
	case 3:
		map->loadmap("assets/level4.map", ren);
		flag->setDest(Vector2D(68, 96), 32, 32);
		player->setDest(Vector2D(150, 286), 32, 32);
		coin->setDest(Vector2D(542, 190), 32, 32);
		break;
	case 4:
		map->loadmap("assets/level5.map", ren);
		flag->setDest(Vector2D(68, 96), 32, 32);
		player->setDest(Vector2D(150, 286), 32, 32);
		coin->setDest(Vector2D(542, 190), 32, 32);
		break;
	}
}

bool GameWorld::collisionTile(object* a, object b)
{
	if ((a->getDX() < (b.getDX() + b.getDW())) && ((a->getDX() + a->getDW()) > b.getDX()) && (a->getDY() < (b.getDY() + b.getDH())) && ((a->getDY() + a->getDH()) > b.getDY())) {
		return true;
	}
	else {
		return false;
	}
}