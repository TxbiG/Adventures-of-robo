#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "object.h"
#include "Vector2D.h"
#include "tilemap.h"

using namespace std;

class entity : public object
{
public:

    void updateEntity(tilemap* map);
    bool onCollision(object* a, object b);

    void renderEntity(bool b, SDL_Renderer* ren);

    SDL_Rect updateEntityBox(SDL_Rect r) { return r; }

    SDL_Rect EntityBox(SDL_Renderer* ren, int x, int y, SDL_Rect rect);

    Vector2D getCheckPoint() const { return vec; }
    Vector2D setCheckPoint(Vector2D vect) { return vec = vect; }

    bool is_on_floor() const { return isOnFloor; }
    bool is_on_wallL() const { return isOnWallL; }
    bool is_on_wallR() const { return isOnWallR; }
    bool is_on_ceiling() const { return isOnCeiling; }


    object* CollDestFloor = new object();
    object* CollDestWallL = new object();
    object* CollDestWallR = new object();
    object* CollDestCeiling = new object();

private:
    void set_on_floor(bool b) { isOnFloor = b; }
    bool isOnFloor = false;
    bool isOnWallL = false;
    bool isOnWallR = false;
    bool isOnCeiling = false;

    Vector2D vec;
    bool hasCheckPoint = false;

};

#endif //ENTITY_H