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

	int createAnimation(int r, int a, int s);
	void setCurrectAnimation(int c) { beginAnim = 0; currentAnim = c; }
	void updateAnimation();

	SDL_Rect getDest() const { return dest; }
	Vector2D getDestV() const { return Vector2D(dest.x, dest.y); }
	SDL_Rect getSource() const { return src; }
	bool getCurrentAnimation() const { return currentAnim; }
	int getDX() const { return dest.x; }
	int getDY() const { return dest.y; }
	int getDW() const { return dest.w; }
	int getDH() const { return dest.h; }
	bool getSolid() const { return isSolid; }
	SDL_Texture* getTexture() const { return texture; }

	void setImage(string filename, SDL_Renderer* ren);
	//void setSpriteSheet(string filename, SDL_Renderer* ren);
	void setBlock(Uint8 R, Uint8 G, Uint8 B, Uint8 A, SDL_Renderer* ren) const;

	void setSolid(bool s) { isSolid = s; }
	void setDest(Vector2D vec, int w, int h);
	void setDest(Vector2D vec);
	void setSource(int x, int y, int w, int h);
	void setVisible(bool b) { visible = b; }

	bool getVisible() const { return visible; }
	bool visible = true;

	Vector2D velocity;
	Vector2D postition;

	int x = 0;
	int y = 0;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect dest = { 0, 0, 0, 0 };
private:
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
	bool isSolid = false;
};
#endif //OBJECT_H