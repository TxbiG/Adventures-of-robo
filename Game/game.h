#ifndef GAME_H
#define GAME_H

#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Timer.h"
#include "splashscreen.h"
#include "Transition.h"
#include "GameWorld.h"

using namespace std;

class game
{
public:
	game();
	~game();
	void init();

	void loop();
	void input();
	void update();
	void render();

	static SDL_Renderer* renderer;						// The SDL Renderer

private:
	const int WIDTH = 640;
	const int HEIGHT = 480;

	int seconds;										// Used as in milliseconds for count down
	int timer;											// Used for the 60 "seconds" count down

	bool isFullscreen;									// Used to switch from minimised or to fullscreen
	bool running;										// Used to running the game

	const int DELTA_TIME = 15;							// Game DELTA_TIME
	Timer m_Timer;										// Timer used for FPS

	SDL_Event m_event;									// SDL input
	SDL_Window* m_window;								// SDL window setup
	TTF_Font* m_font;									// SDL font 
};
#endif //GAME_H