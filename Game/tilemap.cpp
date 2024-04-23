#include "tilemap.h"

void tilemap::loadmap(const char* filename, SDL_Renderer* ren)
{
	object tmp{};
	int current, mx, my, mw, mh;
	ifstream file(filename);
	if (!file.is_open())
	{
		return;
	}

	file >> mw;
	file >> mh;
	file >> mx;
	file >> my;

	for (int i = 0; i < mh; i++)
	{
		for (int j = 0; j < mw; j++)
		{
			if (file.eof())
			{
				return;
			}
			file >> current;
			if (current != 0)
			{
				tmp.setImage("assets/Tilemap.png", ren);
				tmp.setSource((current - 1) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
				tmp.setDest(Vector2D((j * TILE_SIZE) + mx, (i * TILE_SIZE) + my), TILE_SIZE, TILE_SIZE);
				tmp.setID(current);
				tmp.setSolid(true);
				map.push_back(tmp);
			}
		}
	}
	file.close();
}

void tilemap::drawMap(SDL_Renderer* ren)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].getDX() >= 0 - 32 && map[i].getDY() >= 0 - 32 && map[i].getDX() <= 0 + 640 + 32 && map[i].getDY() <= 0 + 480 + 32)
		{
			drawTiles(map[i], ren);
		}
	}

}

void tilemap::drawTiles(object o, SDL_Renderer* ren)
{
	SDL_Rect dest = o.getDest();
	SDL_Rect src = o.getSource();
	SDL_RenderCopyEx(ren, o.getTexture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}