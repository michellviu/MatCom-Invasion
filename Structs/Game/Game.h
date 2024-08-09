#ifndef GAME_H

#define GAME_H
#include <Utils/Utils.h>
#include <Player/Player.h>
#include <Alien/Alien.h>
#include <Bullet/Bullet.h>

typedef enum
{
    RUNNING,
    PAUSED,
    OVER,
    START
} gamestate;

typedef struct
{
    gamestate state;
    int level;
    player *player;
    alien *aliens[ALIENIGENAS];
    bullet *bullets[MAX_BULLETS_ON_SCREEN];
    character winner;
} game;

void game_pause(game *game);
void game_resume(game *game);
void game_init(game *game);
void game_update(game *game, int alienmovecounter);
void game_cleanup(game *game);

#endif