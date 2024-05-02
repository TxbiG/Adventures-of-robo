#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "UI.h"

using namespace std;

class splashscreen
{
public:
	splashscreen(SDL_Renderer* ren);		// Splash screen constructor

private:
	TTF_Font* title;		// SDL font 
};
#endif // SPLASHSCREEN_H