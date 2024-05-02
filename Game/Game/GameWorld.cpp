#include "GameWorld.h"
#include "UI.h"

// Audio
audio* CoinSFX = new audio();
audio* BuffSFX = new audio();
audio* DoorSFX = new audio();
audio* DamageSFX = new audio();
audio* Music = new audio();

// Graphics
tilemap* map = new tilemap();
object* DeathBox = new object();
object* coin = new object();
object* door = new object();
object* Buff = new object();
entity* Enemy = new entity();
entity* player = new entity();

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
	Music->loadMusic("assets/sounds/backgroundmusic.wav");
	load_scene(ren);

	// Load Coin(s)
	coin->setImage("assets/sprites/coin.png", ren);
	coin->setCurrectAnimation(coin->createAnimation(1, 4, 10));
	CoinSFX->loadSound("assets/sounds/Coin.wav");

	// Load Door
	door->setImage("assets/sprites/Door.png", ren);
	doorClosed = door->createAnimation(1, 1, 0);
	doorOpening = door->createAnimation(1, 3, 50);
	door->setCurrectAnimation(doorClosed);
	DoorSFX->loadSound("assets/sounds/DoorOpen.wav");

	// Death box
	DeathBox->setImage("assets/sprites/DeathBox.png", ren);
	DeathBox->setCurrectAnimation(DeathBox->createAnimation(1, 2, 10));

	// Buff
	BuffSFX->loadSound("assets/sounds/Buff.wav");
	Buff->setImage("assets/sprites/Buff.png", ren);
	disapperBuff = Buff->createAnimation(1, 3, 20);
	Buffidle = Buff->createAnimation(1, 1, 0);
	Buff->setCurrectAnimation(Buffidle);

	// Enemy
	Enemy->setImage("assets/sprites/Spike.png", ren);
	Enemy->setCurrectAnimation(Enemy->createAnimation(1, 1, 0));
	
	// Load Player
	player->setImage("assets/sprites/Player.png", ren);
	idle = player->createAnimation(1, 4, 10);
	run = player->createAnimation(2, 4, 10);
	jump = player->createAnimation(3, 1, 0);
	fall = player->createAnimation(4, 1, 0);
	death = player->createAnimation(5, 2, 10);

	DamageSFX->loadSound("assets/sounds/Damage.wav");
}
void GameWorld::input(SDL_Event _event)
{
	if (isCol)
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
				player->velocity.x = 0;
				player->velocity.y = 0;
				break;
			case SDLK_d:
				gKeys[SDLK_d] = false;
				player->velocity.x = 0;
				player->velocity.y = 0;
				break;
			case SDLK_SPACE:
				gKeys[SDLK_SPACE] = false;
				player->velocity.x = 0;
				player->velocity.y = 0;
				break;
			}
		}
	}
	else
	{	// Helps Stops player input when transitioning starts
		gKeys[SDLK_a] = false;
		gKeys[SDLK_d] = false;
		gKeys[SDLK_SPACE] = false;
		player->velocity.x = 0;
		player->velocity.y = 0;
	}
}

void GameWorld::update()
{
	isFalling = true;
	canTransition = false;

	if (!player->is_on_floor() && player->velocity.y <= 2) { player->velocity.y = player->velocity.y + 1; }

	// Get Coin collision
	if (collision(player, coin))
	{
		// Hide coin object(s)
		if (coin->getVisible())
		{
			debug.get_Debug("Player: Collided with coin.");
			score += 10;
			CoinSFX->playSound();
			coin->setVisible(false);
		}
	}

	// Get Player Buff collision
	if (collision(player, Buff))
	{
		// Hide buff object
		if (Buff->getVisible() && !BuffUsed)
		{
			Buff->setCurrectAnimation(disapperBuff);
			BuffUsed = true;
			canJump = true;
			CyoteJump = 10;
			debug.get_Debug("Player: Collided with buff.");
			BuffSFX->playSound();
		}
	}

	// Checks if buff has been used if has takes few seconds for it to appear back
	if (BuffUsed) { BuffLifeTime--; if (BuffLifeTime <=50) { Buff->setVisible(false); } if (BuffLifeTime <= 0) { Buff->setVisible(true); BuffUsed = false; BuffLifeTime = 80; Buff->setCurrectAnimation(Buffidle); } }

	// Get Door Collision
	if (collision(player, door))
	{
		if (isCol)
		{
			// Change level
			debug.get_Debug("Player: Collided with door.");
			canSwitch = true;
			DoorSFX->playSound();
			canTransition = true;
			setTransition();
		}
		isCol = false;
	}

	// Get Enemy Collision
	if (collision(player, Enemy))
	{
		if (isCol)
		{
			if (Enemy->getVisible())
			{
				debug.get_Debug("Player: Collided with enemy.");
				DamageSFX->playSound();
				isCol = false;
				canTransition = true;
				setTransition();
			};
		}
	}

	// Get Death box Collision
	if (collision(player, DeathBox))
	{
		if (isCol)
		{
			if (DeathBox->getVisible())
			{
				debug.get_Debug("Player: Collided with the void.");
				DamageSFX->playSound();
				isCol = false;
				player->setCurrectAnimation(death);
				canTransition = true;
				player->setCurrectAnimation(death);
				setTransition();
			}
		}
	}

	if (!isCol)
	{
		if (canSwitch) { if (door->getCurrentAnimation() != doorOpening) { door->setCurrectAnimation(doorOpening); } }
		else { player->setCurrectAnimation(death); }
	}
	else
	{
		if (gKeys[SDLK_a] && !player->is_on_wallL()) { player->velocity.x = -speed; }
		if (gKeys[SDLK_d] && !player->is_on_wallR()) { player->velocity.x = +speed; }

		if (gKeys[SDLK_SPACE] && !player->is_on_ceiling() && canJump)
		{
			if (player->is_on_floor())
			{
				player->velocity.y = player->velocity.y - jumpSpeed;
				debug.get_Debug("Player: Jumping");
			}
			else 
			{
				if (CyoteJump >= 0)
				{
					player->velocity.y -=  player->velocity.y + jumpSpeed;
					debug.get_Debug("Player: Cyote Jumping");
				}
			}
			CyoteJump = -1;
			canJump = false;
		}
		// State machine
		// Jump & Fall
		if (player->velocity.y <= -1 && !player->is_on_floor()) 
		{ 
			if (player->getCurrentAnimation() != jump) { player->setCurrectAnimation(jump); } 
		}
		if (player->velocity.y >= 1 && !player->is_on_floor()) 
		{ 
			if (player->getCurrentAnimation() != fall) { player->setCurrectAnimation(fall); } 
		}

		// Idle
		if (player->velocity.x == 0 && player->velocity.y == 0) 
		{ 
			if (player->getCurrentAnimation() != idle) { player->setCurrectAnimation(idle); } 
		}

		// Run
		if (player->velocity.x <= -1 && player->is_on_floor()) 
		{ 
			if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_HORIZONTAL; } 
		}
		if (player->velocity.x >= 1 && player->is_on_floor()) 
		{ 
			if (player->getCurrentAnimation() != run) { player->setCurrectAnimation(run); player->flip = SDL_FLIP_NONE; } 
		}

		// Flip sprite
		if (player->velocity.x <= -1) { player->flip = SDL_FLIP_HORIZONTAL; }
		if (player->velocity.x >= 1) { player->flip = SDL_FLIP_NONE; }
	}

	// Checks if player is colliding through Floor
	if (player->is_on_floor()) 
	{ 
		canJump = true; 
		if (!gKeys[SDLK_SPACE]) { player->velocity.y = player->velocity.y - 1; 
		if (player->velocity.y != 0) { player->velocity.y = player->velocity.y - player->velocity.y; } } 
		if (CyoteJump != 10) { CyoteJump = 10; } 
	}
	else { if (CyoteJump >= 0) { CyoteJump--; } }

	// Checks if player is colliding through Ceiling
	if (player->is_on_ceiling()) 
	{ 
		player->velocity.y = player->velocity.y - player->velocity.y;  
		if (player->velocity.y == 0) { player->velocity.y = player->velocity.y + 1; } 
	}

	// Checks if playr is colliding through Left wall
	if (player->is_on_wallL()) 
	{ 
		if (!gKeys[SDLK_d]) 
		{ 
			player->velocity.x = player->velocity.x - 1; 
			if (player->velocity.x != 0) { player->velocity.x = player->velocity.x - player->velocity.x; } 
		} 
	}

	// Stops player from colliding through Right wall
	if (player->is_on_wallR()) 
	{ 
		if (!gKeys[SDLK_a]) 
		{ 
			player->velocity.x = player->velocity.x + 1; 
			if (player->velocity.x != 0) 
			{ player->velocity.x = player->velocity.x - player->velocity.x; } 
		} 
	}

	// Checks if players all collisions are colliding then resets world
	if (player->is_on_ceiling() && player->is_on_wallR() && player->is_on_wallL() && player->is_on_floor()) { resetWorld(); }

	// Enemy Mechanic
	if (Enemy->getVisible())
	{
		// Check if enemy has hit wall and returns the direction it needs to go next.
		if (Enemy->is_on_wallL()) { flipDir = true; }
		if (Enemy->is_on_wallR()) { flipDir = false; }
		// Flips the direction it goes based on true false statment
		if (flipDir) { Enemy->velocity.x = +2; Enemy->flip = SDL_FLIP_HORIZONTAL; } 
		else { Enemy->velocity.x = -2; Enemy->flip = SDL_FLIP_NONE; }
	}

	door->update();
	Buff->update();
	coin->update();
	player->updateEntity(map);

	if (Levelnum == 2 || Levelnum == 3) { DeathBox->update(); }
	if (Levelnum == 2 || Levelnum == 3 || Levelnum == 4 || Levelnum == 5) { Enemy->updateEntity(map); }
}

void GameWorld::render(SDL_Renderer* ren)
{
	// TileMap layer
	map->drawMap(ren);

	// Render Deathbox based on level
	if (Levelnum == 2 || Levelnum == 3) { DeathBox->render(ren); DeathBox->setVisible(true); } else { DeathBox->setVisible(false); }
	
	// Object layer
	coin->render(ren);
	door->render(ren);
	Buff->render(ren);

	// Render Player buff based on level
	if (Levelnum == 1 || Levelnum == 3) { Buff->render(ren); }

	// Render Enemy based on level
	if (Levelnum == 2 || Levelnum == 3 || Levelnum == 4 || Levelnum == 5) { Enemy->renderEntity(debug.get_Debugger(), ren); Enemy->setVisible(true); } else{ Enemy->setVisible(false); }
	
	// Player layer
	player->renderEntity(debug.get_Debugger(), ren);
}

bool GameWorld::collision(object* a, object* b)
{
	if ((a->getDX() < (b->getDX() + b->getDW())) && ((a->getDX() + a->getDW()) > b->getDX()) && (a->getDY() < (b->getDY() + b->getDH())) && ((a->getDY() + a->getDH()) > b->getDY())) {
		return true;
	}
	else { return false; }
}

// Used to load levels in and change position of entitys and objects
void GameWorld::load_scene(SDL_Renderer* ren)
{
	switch (Levelnum)
	{
	case 0:
		map->loadmap("assets/levels/1.map", ren);
		door->setDest(Vector2D(542, 128), 32, 32);
		player->setDest(Vector2D(150, 384), 32, 32);
		coin->setDest(Vector2D(64, 190), 32, 32);
		Enemy->setDest(Vector2D(0, 0), 32, 32);
		DeathBox->setDest(Vector2D(0, 0), 96, 32);
		Buff->setDest(Vector2D(386, 168), 32, 32);
		Buff->setVisible(true);
		break;
	case 1:
		map->loadmap("assets/levels/2.map", ren);
		door->setDest(Vector2D(128, 96), 32, 32);
		player->setDest(Vector2D(542, 384), 32, 32);
		coin->setDest(Vector2D(288, 128), 32, 32);
		DeathBox->setDest(Vector2D(319, 425), 96, 32);
		Enemy->setDest(Vector2D(96, 384), 32, 32);
		Buff->setDest(Vector2D(-32, -32), 32, 32);
		Buff->setVisible(false);
		break;
	case 2:
		map->loadmap("assets/levels/3.map", ren);
		door->setDest(Vector2D(542, 128));
		player->setDest(Vector2D(542, 384));
		coin->setDest(Vector2D(64, 128));
		DeathBox->setDest(Vector2D(319, 425), 96, 32);
		Enemy->setDest(Vector2D(96, 384), 32, 32);
		Buff->setDest(Vector2D(384, 168), 32, 32);
		Buff->setVisible(true);
		break;
	case 3:
		map->loadmap("assets/levels/4.map", ren);
		door->setDest(Vector2D(446, 128), 32, 32);
		player->setDest(Vector2D(150, 286), 32, 32);
		coin->setDest(Vector2D(64, 128), 32, 32);
		Enemy->setDest(Vector2D(384, 384), 32, 32);
		Buff->setDest(Vector2D(-32, -32), 32, 32);
		Buff->setVisible(false);
		break;
	case 4:
		map->loadmap("assets/levels/5.map", ren);
		door->setDest(Vector2D(480, 128), 32, 32);
		player->setDest(Vector2D(96, 346), 32, 32);
		coin->setDest(Vector2D(416, 128), 32, 32);
		Enemy->setDest(Vector2D(384, 384), 32, 32);
		Buff->setDest(Vector2D(448, 300), 32, 32);
		Buff->setVisible(true);
		break;
	case 5:
		canDestroy = true;
	}

	isCol = true;

	coin->setVisible(true);
	Buff->setVisible(true);
	player->setCheckPoint(player->getDestV());
	canSwitch = false;
	player->setCurrectAnimation(idle);
	door->setCurrectAnimation(doorClosed);

	Music->playMusic();

	if (Levelnum <= 5) { Levelnum += 1; }

	debug.get_Debug("Level: " + to_string(Levelnum));
}

void GameWorld::resetWorld()
{
	debug.get_Debug("Resetting world");
	Vector2D tmp = player->getCheckPoint();
	player->setDest(Vector2D(tmp.x, tmp.y));
	isCol = true;
}