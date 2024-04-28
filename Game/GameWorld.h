#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <iostream>
#include <SDL.h>

#include "object.h"
#include "entity.h"
#include "tilemap.h"

#define MAX_KEYS (256)
/*
	Game world, used to load in Tilemap, Player, Coin(s), and Enemy(s)
*/

class GameWorld
{
public:
	GameWorld();
	void init(SDL_Renderer* ren);

	void input(SDL_Event event);
	void update();
	void render(SDL_Renderer* ren);


	int get_score() const { return score; }
	void load_scene(SDL_Renderer* ren);
	bool setTransition() const { return canSwitch; }

	bool gKeys[MAX_KEYS];

private:
	bool collisionTile(object* a, object b);
	bool collision(object* a, object* b);

	// Coin anim
	bool spin = false;

	// Player anim
	bool idle = false;
	bool run = false;
	bool jump = false;
	bool fall = false;
	bool grab = false;

	// Player mechanics
	int speed = 5;
	int jumpSpeed = 25;
	bool isFalling;
	bool isWall = false;
	//bool isGrabbing;
	bool disableInput = false;

	bool dash = false;

	int score = 0;								// Player point score

	// Number of levels
	int Levelnum = 0;
	bool canSwitch = true;

	bool isOnFlag = true;

	bool StartNewLevel = false;

	const int GRAVITY = 8;
};
#endif // GAMEWORLD_H