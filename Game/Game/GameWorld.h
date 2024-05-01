#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <iostream>
#include <SDL.h>
#include "Debugger.h"
#include "Audio.h"

#include "object.h"
#include "entity.h"
#include "tilemap.h"

#define MAX_KEYS (256)

using namespace std;
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

	void load_scene(SDL_Renderer* ren);
	void resetWorld();

	int get_score() const { return score; }

	bool setTransition() const { return canTransition; }

	bool destroyWorld() const { return canDestroy; }

	bool gKeys[MAX_KEYS];

	bool canTransition = false;
	bool canSwitch = true;
	bool canDestroy = false;

	Debugger debug;

private:
	bool collision(object* a, object* b);

	const int GRAVITY = 3;

	// Number of levels
	int Levelnum = 0;
	bool isOnFlag = true;

	int score = 0;								// Player point score

	// Door anim
	bool doorClosed = false;
	bool doorOpening = false;

	// Player anim
	bool idle = false;
	bool run = false;
	bool jump = false;
	bool fall = false;
	bool grab = false;
	bool death = false;

	// Player mechanics
	int speed = 5;
	int jumpSpeed = 5;
	int CyoteJump = 5;
	bool canJump = false;
	bool canCyoteJump = false;
	bool isFalling;

	bool isWall = false;
	//bool isGrabbing;
	bool disableInput = false;

	bool dash = false;

	// Enemy movement
	bool flipDir = false;
};
#endif // GAMEWORLD_H