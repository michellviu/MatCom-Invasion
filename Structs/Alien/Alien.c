#include <stdio.h>
#include <stdlib.h>

#include <Utils/Utils.h>

#include <Alien/Alien.h>


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
        newpos.x += SPRITE_SIZE;
        break;
    default:
    }
}

void alien_spawn(alien *alien, position pos)
{
    alien->pos = pos;
    alien->status = ALIVE;
}