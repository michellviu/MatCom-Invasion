#ifndef BULLETS_H

#define BULLETS_H

#include <Utils.h>
#include <Alien.h>
#include <Player.h>

typedef enum
{
    INACTIVE,
    ACTIVE
} bulletstatus;

typedef struct
{
    position pos;
    character shooter;
    bulletstatus status;
} bullet;

void bullet_spawn(character shooter, position pos, bullet *bullets[MAX_BULLETS_ON_SCREEN]);
void bullet_move(bullet *bullet);
void check_alien_collision(bullet *bullet, alien *alien[ALIENIGENAS]);
void check_player_collision(bullet *bullet, player *player);

#endif