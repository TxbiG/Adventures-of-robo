#ifndef GAME_H
#define GAME_H

// Add a Cyote jump
#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include "object.h"
#include "entity.h"
#include "tilemap.h"

#define GRAVITY 15

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

	bool collisionTile(object* a, object b);
	bool collision(object* a, object* b);
	static SDL_Renderer* renderer;
private:
	int frameTime; // FPS
	int timer = 0;
	int score = 0;

	bool isFullscreen;
	bool running;

	bool u = false;
	bool r = false;
	bool l = false;
	bool isFalling;
	bool idle = false;
	bool run = false;
	bool jump = false;
	int fall = false;
	bool spin = false;
	bool disableInput = false;

	int speed = 10;
	int jumpSpeed = 50;

	int Levelnum;

	SDL_Window* window;
	Uint32 Startframe;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	TTF_Font* font;
};
#endif //GAME_H