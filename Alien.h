#ifndef ALIENS_H

#define ALIENS_H
#include "./Utils.h"
typedef enum
{
    DEAD,
    ALIVE
} alienstatus;

typedef struct
{
    position pos;
    alienstatus status;
    direction direction;

} alien;

void alien_move(alien *alien, direction direction);
void alien_spawn(alien *alien, position pos);

#endif