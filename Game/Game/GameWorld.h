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

	const int GRAVITY = 3;			// Worlds gravity
	int score = 0;					// Player point score

	int Levelnum = 0;				// Used for checking what level player is on
	bool isCol = true;				// Used to check if player is colliding with Enemies or buffs or Door

	// Door anim
	int doorClosed = 0;				// Used for door staying closed
	int doorOpening = 0;			// Used for door opening


	// Player anim
	int idle = 0;					// Player idle
	int run = 0;					// Player run
	int jump = 0;					// Player jumping
	int fall = 0;					// Player falling
	int death = 0;					// Player  death

	// Player mechanics
	int speed = 5;					// Players walk speed
	int jumpSpeed = 12;				// Players jump speed
	int CyoteJump = 10;				// CyoteJump timer before not being able to use it
	bool canJump = false;			// Check if player can jump
	bool canCyoteJump = false;		// Check if player can Cyote jump
	bool isFalling;					// Check if player is falling


	// Enemy movement
	bool flipDir = false;		// Used for flipping enemy sprite

	// Buff mechanic
	bool BuffUsed = false;		// Check if Player buff has been used
	int BuffLifeTime = 80;		// Life time of player buff before respawn
	int Buffidle = 0;			// Player buff idle animation
	int disapperBuff = 0;		// Player buff fading out animation
};
#endif // GAMEWORLD_H