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
    void updateEntity(tilemap* map);                    // Entity update
    void renderEntity(bool b, SDL_Renderer* ren);       // Entity render

    bool onCollision(object* a, object b);      // Used for checking if entity is Colliding with collisions

    Vector2D getCheckPoint() const { return vec; }                  // Get entitys Checkpoint
    Vector2D setCheckPoint(Vector2D vect) { return vec = vect; }    // Set entitys Checkpoint

    bool is_on_floor() const { return isOnFloor; }                  // Check if is on floor
    bool is_on_wallL() const { return isOnWallL; }                  // Check if is on Left Wall
    bool is_on_wallR() const { return isOnWallR; }                  // Check if is on Right Wall
    bool is_on_ceiling() const { return isOnCeiling; }              // Check if is on Ceiling


    // Collision
    object* CollDestFloor = new object();           // Used for detecting collision Floor
    object* CollDestWallL = new object();           // Used for detecting collision Left Wall
    object* CollDestWallR = new object();           // Used for detecting collision Right Wall
    object* CollDestCeiling = new object();         // Used for detecting collision Ceiling

private:
    bool isOnFloor = false;                    // Check if on Floor
    bool isOnWallL = false;                    // Check if on Left Wall
    bool isOnWallR = false;                    // Check if on Right Wall
    bool isOnCeiling = false;                  // Check if on Ceiling

    Vector2D vec;                               // Vector 2D
    bool hasCheckPoint = false;                 // Check if entity has a check point

};

#endif //ENTITY_H