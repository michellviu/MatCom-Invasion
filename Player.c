#include <stdio.h>
#include <stdlib.h>

#include "./Utils.h"
#include "./Player.h"

void player_move(player *player, direction direction)
{
    position newpos = player->pos;

    switch (direction)
    {
    case LEFT:
        newpos.x -= PLAYER_SPEED;
        break;
    case RIGHT:
        newpos.x += PLAYER_SPEED;
        break;
    default:
    }

    player->pos = newpos;
}

void player_spawn(player *player)
{
    position pos = {.x = PLAYER_STARTING_X, .y = PLAYER_STARTING_Y};

    player->lives = 3;
    player->pos = pos;
}
