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
	splashscreen(SDL_Renderer* ren);

private:
	TTF_Font* title;	// SDL font 
	TTF_Font* subtitle;	// SDL font 
	TTF_Font* text;	// SDL font 
};
#endif // SPLASHSCREEN_H