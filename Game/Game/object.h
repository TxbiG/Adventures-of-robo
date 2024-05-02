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
	void update();							// Object update
	void render(SDL_Renderer* ren);			// Object render

	int createAnimation(int r, int a, int s);					// Create Object animation
	void setCurrectAnimation(int c) { beginAnim = 0; currentAnim = c; }		// Set Objects current animation
	void updateAnimation();						// Update object animation

	SDL_Rect getDest() const { return dest; }
	Vector2D getDestV() const { return Vector2D(dest.x, dest.y); }	// Vectorised 
	SDL_Rect getSource() const { return src; }
	int getCurrentAnimation() const { return currentAnim; }		// Get current animation
	int getDX() const { return dest.x; }						// Get object X coords
	int getDY() const { return dest.y; }						// Get Object Y coords
	int getDW() const { return dest.w; }						// Get Object Width
	int getDH() const { return dest.h; }						// Get Object height
	bool getSolid() const { return isSolid; }					// Get if Object is solid or not
	SDL_Texture* getTexture() const { return texture; }			// Get Object texture
	bool getVisible() const { return visible; }					// Get Objects visiblity

	void setImage(string filename, SDL_Renderer* ren);
	//void setSpriteSheet(string filename, SDL_Renderer* ren);
	void setBlock(Uint8 R, Uint8 G, Uint8 B, Uint8 A, SDL_Renderer* ren) const; // Used for creating collision marks

	void setSolid(bool s) { isSolid = s; }			// Set Object solid or not
	void setDest(Vector2D vec, int w, int h);		// Set Objects Dest Vector form and Scale
	void setDest(Vector2D vec);						// Set Objects Dest in Vecoter form
	void setSource(int x, int y, int w, int h);		// Set Objects source
	void setVisible(bool b) { visible = b; }		// Set Objects visibility

	Vector2D velocity;				// Objects velocity
	Vector2D postition;				// Objects position

	SDL_RendererFlip flip = SDL_FLIP_NONE;			// Used for Flipping Objects image
	SDL_Rect dest = { 0, 0, 0, 0 };					// Objects dest
private:
	SDL_Rect src = { 0, 0, 0, 0 };					// Objects src
	SDL_Texture* texture = nullptr;					// Objects texture

	// Animation cycle
	struct cycle
	{
		int row;
		int width;
		int height;
		int amount;
		int speed;
		int tick;
	};

	vector<cycle> Animation;		// Object animation

	int beginAnim = 0;				// Begining of animation
	int currentAnim = 0;			// Current animation
	bool isSolid = false;			// if Object is solid
	bool visible = true;			// if Object is visible
};
#endif //OBJECT_H