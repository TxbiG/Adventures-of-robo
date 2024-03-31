#ifndef GAME_H
#define GAME_H

// Add a Cyote jump
#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "GameWorld.h"

#include "audio.h"
#include "object.h"
#include "entity.h"
#include "tilemap.h"

#define WIDTH 640
#define HEIGHT 480

using namespace std;

class game
{
public:
	game();
	~game();
	void init();

	void loop();
	void update();
	void render();
	void input();

	bool collisionTile(object a, object b);
	bool collision(object a, object* b);
	static SDL_Renderer* renderer;
private:
	SDL_Window* window;
	Uint32 Startframe;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	TTF_Font* font;
	audio effect;
	int frameTime; // FPS

	bool running;
	static int Level;

	//bool idle, run, jump, fall, spin;
	//bool isFalling;
	//bool l, r, u;
	bool isFullscreen;
	//int speed = 10;
	int jumpSpeed = 50;
	int switchLevel = 0;

	int timer;
	int score;
};

#endif //GAME_H