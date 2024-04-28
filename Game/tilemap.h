#ifndef TILEMAP_H
#define TILEMAP_H

#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "object.h"

#define TILE_SIZE 32

enum class Tile
{
    Floor = 0,
    Wall = 1,
    Ceiling = 2
};

class tilemap : public object
{
public:
    void loadmap(const char* filename, SDL_Renderer* ren);
    void drawMap(SDL_Renderer* ren);
    void drawTiles(object o, SDL_Renderer* ren);

    int getDX() const { return dest.x; }
    int getDY() const { return dest.y; }
    vector<object> map;
private:
    SDL_Rect dest{};
};
#endif //TILEMAP_H