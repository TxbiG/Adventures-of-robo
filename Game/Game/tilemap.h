#ifndef TILEMAP_H
#define TILEMAP_H

#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "object.h"

class tilemap : public object
{
public:
    void loadmap(const char* filename, SDL_Renderer* ren);      // Load map

    void drawMap(SDL_Renderer* ren);                            // Render map
    void drawTiles(object o, SDL_Renderer* ren);                // draw the position of the tiles on screen

    vector<object> map;                     // Tilemaps data

private:
    const int TILE_SIZE = 32;       // Tile size is set to 32 pixels
};
#endif //TILEMAP_H