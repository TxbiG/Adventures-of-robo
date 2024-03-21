#include "object.h"

void object::update()
{
	updateAnimation();
}

void object::render(SDL_Renderer* ren)
{
	SDL_Rect dest = getDest();
	SDL_Rect src = getSource();
	SDL_RenderCopyEx(ren, texture, &src, &dest, NULL, NULL, flip);
}

int object::createAnimation(int r, int w, int h, int a, int s)
{
	cycle temp{};
	temp.row = r-1;
	temp.width = w;
	temp.height = h;
	temp.amount = a;
	temp.tick = 0;
	temp.speed = s;
	Animation.push_back(temp);
	return static_cast<int>(Animation.size()-1);
}

void object::updateAnimation()
{
	setSource(Animation[currentAnim].width * Animation[currentAnim].tick, Animation[currentAnim].row * Animation[currentAnim].height, Animation[currentAnim].width, Animation[currentAnim].height);
	if (beginAnim > Animation[currentAnim].speed) { Animation[currentAnim].tick++; beginAnim = 0; }
	beginAnim++;

	if (Animation[currentAnim].tick >= Animation[currentAnim].amount) { Animation[currentAnim].tick = 0; }
}

void object::setImage(string filename, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(ren, surf);
}

void object::setDest(int x, int y, int w, int h)
{
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
}

void object::setDest(int x, int y)
{
	dest.x = x;
	dest.y = y;
}

void object::setSource(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
}