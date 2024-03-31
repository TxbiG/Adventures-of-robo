#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <SDL.h>
#include <iostream>
//#include "Vector2D.h"

#include "audio.h"
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

	void input(SDL_Event event);
	void update();
	void render(SDL_Renderer* ren);

	void loadWorld(const char* LevelName, SDL_Renderer* ren);
	void set_player_position(int x, int y) { player->setDest(x, y, 32, 32); }
	void set_coin_position(int x, int y) { coin->setDest(x, y, 32, 32); }
	void set_flag_position(int x, int y) { flag->setDest(x, y, 32, 32); }

	bool u = false;
	bool r = false;
	bool l = false;
	bool isFalling = false;
	bool idle, run, jump, fall, spin = false;
	bool disableInput;

	int speed = 10;
	int jumpSpeed = 50;

	audio effect;


	object* player;
	object* coin;
	object* flag;
};
#endif // GAMEWORLD_H
