#include <stdio.h>
#include <stdlib.h>

#include "./Utils.h"
#include "./Alien.h"

void alien_move(alien *alien, direction direction)
{
    position newpos = alien->pos;

    switch (direction)
    {
    case LEFT:
        newpos.x -= SPRITE_SIZE;
        break;
    case RIGHT:
        newpos.x += SPRITE_SIZE;
        break;
    case UP:
        newpos.y -= SPRITE_SIZE;
        break;
    case DOWN:
        newpos.y += SPRITE_SIZE;
        break;
    default:
    }
    alien->pos = newpos;
}

void alien_spawn(alien *alien, position pos, int index)
{
    alien->pos = pos;
    alien->status = ALIVE;
    alien->index = index;
}