#include "entity.h"

void entity::updateEntity(tilemap* map)
{
	isOnFloor = false;
	isOnCeiling = false;
	isOnWallL = false;
	isOnWallR = false;


	for (int i = 0; i < map->map.size(); i++)
	{
		if (onCollision(CollDestFloor, map->map[i])) 
		{ 
			isOnFloor = true;
		}

		if (onCollision(CollDestCeiling, map->map[i])) 
		{
			isOnCeiling = true;
		}

		if (onCollision(CollDestWallL, map->map[i])) 
		{
			isOnWallL = true;
		}

		if (onCollision(CollDestWallR, map->map[i])) {
			isOnWallR = true;
		}
	};

	this->setDest(Vector2D(getDX() + velocity.x, getDY() + velocity.y));
	postition.x = this->dest.x;
	postition.y = this->dest.y;

	CollDestFloor->setDest(Vector2D(dest.x + 11, dest.y + 32), 11, 5);
	CollDestCeiling->setDest(Vector2D(dest.x + 11, dest.y - 5), 11, 5);
	CollDestWallL->setDest(Vector2D(dest.x - 5, dest.y + 11), 5, 11);
	CollDestWallR->setDest(Vector2D(dest.x + 32, dest.y + 11), 5, 11);

	update();
}

void entity::renderEntity(bool b, SDL_Renderer* ren)
{
	if (b)
	{
		CollDestFloor->setBlock(255, 0, 0, 255, ren);
		CollDestCeiling->setBlock(255, 0, 0, 255, ren);
		CollDestWallL->setBlock(255, 0, 0, 255, ren);
		CollDestWallR->setBlock(255, 0, 0, 255, ren);
	}

	render(ren);
}

bool entity::onCollision(object* a, object b)
{
	if ((a->getDX() < (b.getDX() + b.getDW())) && ((a->getDX() + a->getDW()) > b.getDX()) && (a->getDY() < (b.getDY() + b.getDH())) && ((a->getDY() + a->getDH()) > b.getDY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}