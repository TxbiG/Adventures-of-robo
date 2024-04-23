#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2D.h"

using namespace std;

class object
{
public:
	void update();
	void render(SDL_Renderer* ren);

	int createAnimation(int r, int w, int h, int a, int s);
	void setCurrectAnimation(int c) { beginAnim = 0; currentAnim = c; }
	void updateAnimation();

	SDL_Rect getDest() const { return dest; }
	SDL_Rect getSource() const { return src; }
	bool getCurrentAnimation() const { return currentAnim; }
	int getDX() const { return dest.x; }
	int getDY() const { return dest.y; }
	int getDW() const { return dest.w; }
	int getDH() const { return dest.h; }
	bool getSolid() const { return isSolid; }
	int getID() const { return id; }
	SDL_Texture* getTexture() const { return texture; }

	void setImage(string filename, SDL_Renderer* ren);
	void setSolid(bool s) { isSolid = s; }
	void setDest(Vector2D vec, int w, int h);
	void setDest(Vector2D vec);
	void setSource(int x, int y, int w, int h);
	void setID(int i) { id = i; }

	SDL_RendererFlip flip = SDL_FLIP_NONE;
private:
	SDL_Rect dest = { 0, 0, 0, 0 };
	SDL_Rect src = { 0, 0, 0, 0 };
	SDL_Texture* texture = nullptr;

	struct cycle
	{
		int row;
		int width;
		int height;
		int amount;
		int speed;
		int tick;
	};
	vector<cycle> Animation;

	int beginAnim = 0;
	int currentAnim = 0;
	int id = 0;
	bool isSolid = false;
};

#endif //OBJECT_H