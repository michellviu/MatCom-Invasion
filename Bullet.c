#include <stdio.h>

#include "./Utils.h"
#include "./Alien.h"
#include "./Player.h"
#include "./Bullet.h"

void bullet_spawn(character shooter, position pos, bullet *bullets[MAX_BULLETS_ON_SCREEN])
{
    for (int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i)
    {
        if (bullets[i]->status == INACTIVE)
        {
            bullets[i]->pos = pos;
            bullets[i]->shooter = shooter;
            bullets[i]->status = ACTIVE;
            break;
        }
    }
}

void bullet_move(bullet *bullet)
{
    switch (bullet->shooter)
    {
    case PLAYER:
        bullet->pos.y -= BULLET_SPEED;
        break;
    case ALIEN:
        bullet->pos.y += BULLET_SPEED;
        break;
    default:
    {
    }
    }
}

void check_alien_collision(bullet *bullet, alien *aliens[ALIENIGENAS], int aliens_muertos[ALIENIGENAS])
{
    int cont = 0;
    for (int i = 0; i < ALIENIGENAS; ++i)
    {
        if (bullet->shooter == PLAYER && aliens[i]->status == ALIVE && bullet->pos.y + SPRITE_SIZE >= aliens[i]->pos.y && bullet->pos.y <= aliens[i]->pos.y + SPRITE_SIZE && bullet->pos.x + SPRITE_SIZE >= aliens[i]->pos.x && bullet->pos.x <= aliens[i]->pos.x + SPRITE_SIZE)
        {   
            bullet->status = INACTIVE;
            aliens[i]->lives = aliens[i]->lives - 1;
            if (aliens[i]->lives == 0)
            {
                aliens[i]->status = DEAD;
                aliens_muertos[i] = 1;
                for (int j = 0; j < ALIENIGENAS; j++)
                {
                    if (aliens[j]->status == DEAD && !aliens_muertos[j])
                    {
                        aliens[j]->status = ALIVE;
                        cont++;
                        if (cont == 2)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void check_player_collision(bullet *bullet, player *player)
{
    if (bullet->shooter == ALIEN && bullet->pos.y + SPRITE_SIZE >= player->pos.y && bullet->pos.y <= player->pos.y + SPRITE_SIZE && bullet->pos.x + SPRITE_SIZE >= player->pos.x && bullet->pos.x <= player->pos.x + SPRITE_SIZE)
    {
        bullet->status = INACTIVE;
        player->lives -= 1;
    }
}
