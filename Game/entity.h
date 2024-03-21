#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "object.h"

using namespace std;

class entity
{
public:
    int getHealth() const { return health; }
    int getHealthMax() const { return healthMax; }
    int setHealth(int h) { health = h; }
    int setHealthMax(int h) { healthMax = h; }

private:
    int health;
    int healthMax;
};

#endif //ENTITY_H