#ifndef PLAYER_H

#define PLAYER_H
#include <Utils/Utils.h>

typedef struct
{
    position pos;
    int lives;
} player;

void player_spawn(player *player);
void player_move(player *player, direction direction);

#endif
