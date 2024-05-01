#include "object.h"

void object::update()
{
	if (visible) 
	{ 
		updateAnimation();
	}
}

void object::render(SDL_Renderer* ren)
{
	if (visible)
	{
		SDL_Rect dest = getDest();
		SDL_Rect src = getSource();
		SDL_RenderCopyEx(ren, texture, &src, &dest, NULL, NULL, flip);
	}
}

int object::createAnimation(int r, int a, int s)
{
	cycle temp{};
	temp.row = r - 1;
	temp.width = getDW();
	temp.height = getDH();
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

void object::setBlock(Uint8 R, Uint8 G, Uint8 B, Uint8 A, SDL_Renderer* ren) const
{
	SDL_SetRenderDrawColor(ren, R, G, B, A);
	SDL_RenderFillRect(ren, &dest);
}

void object::setDest(Vector2D vec, int w, int h)
{
	dest.x = vec.x;
	dest.y = vec.y;
	dest.w = w;
	dest.h = h;
	this->x;
	this->y;
}

void object::setDest(Vector2D vec)
{
	dest.x = vec.x;
	dest.y = vec.y;
	this->x;
	this->y;
}

void object::setSource(int x, int y, int w, int h)
{
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
	this->x;
	this->y;
}