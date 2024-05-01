#ifndef GAME_H
#define GAME_H

#pragma once

#include <iostream>
#include <string>

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

	void loop();
	void input();
	void update();
	void render();

private:
	const int WIDTH = 640;								// Game Width Window
	const int HEIGHT = 480;								// Game Height Window
	const int DELTA_TIME = 20;							// Game DELTA_TIME

	int seconds = 0;									// Used as in milliseconds for count down
	int timer = 60;										// Used for the 60 "seconds" count down
	bool bonusTime = true;

	bool isFullscreen = true;							// Used to switch from minimised or to fullscreen
	bool running = true;								// Used to running the game

	Timer m_Timer;										// Timer used for FPS
	SDL_Window* m_window;								// SDL window setup
	static SDL_Renderer* renderer;						// The SDL Renderer
};
#endif //GAME_H