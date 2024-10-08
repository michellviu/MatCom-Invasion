#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "./Utils.h"
#include "./Alien.h"
#include "./Player.h"
#include "./Bullet.h"
#include "./Game.h"

void game_cleanup(game *game)
{
  free(game->player);

  for (int i = 0; i < ALIENIGENAS; ++i)
  {
    free(game->aliens[i]);
  }

  for (int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i)
  {
    free(game->bullets[i]);
  }
}

void game_pause(game *game)
{
  game->state = PAUSED;
}

void game_resume(game *game)
{
  game->state = RUNNING;
}

// initialize game
void game_init(game *game)
{
  // Inicializar el generador de números aleatorios
  srand(time(NULL));
  game->state = START;

  game->level = 1;

  // allocate memory to player
  game->player = malloc(sizeof(player));

  // spawn player
  player_spawn(game->player);

  // spawn all aliens and move them once (because they spawn at the border and end up moving
  // down right at the beginning)
  int alien_lives;
  for (int i = 0; i < ALIENIGENAS; ++i)
  {
    game->aliens[i] = malloc(sizeof(alien));
    position pos = {.x = BORDER + rand() % (WINDOW_WIDTH - 2 * BORDER), .y = 0};
    if ( i < 8)
    {
      alien_lives = 1;
    }
    else if ( i < 16)
    {
      alien_lives = 2;
    }
    else
    {
      alien_lives = 3;
    }

    alien_spawn(game->aliens[i], pos, i, alien_lives);
    game->aliens[i]->status = DEAD;
    game->aliens_muertos[i] = 0;
    // alien_move(game->aliens[i], DOWN);
  }
  game->aliens[0]->status = ALIVE;
  game->aliens[1]->status = ALIVE;

  // initialize all bullets and set them as inactive
  for (int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i)
  {
    game->bullets[i] = malloc(sizeof(bullet));
    game->bullets[i]->status = INACTIVE;
  }
}

// update game
void game_update(game *game, int alienmovecounter)
{

  // get position of first alien, to be used to check wall collisions
  // position alienpos = game->aliens[0]->pos;

  // move all aliens once a second (since FPS=60),
  // moving them down and changing direction if they collide with walls
  if (alienmovecounter % 60 == 0)
  {
    for (int i = 0; i < ALIENIGENAS; ++i)
    {

      if (game->aliens[i]->status == ALIVE)
      {
        alien_move(game->aliens[i], DOWN);
      }
    }
  }

  // make a random aline fire a bullet every second
  if (alienmovecounter % 60 == 0)
  {
    int x = rand() % ALIENIGENAS;
    if (game->aliens[x]->status == ALIVE)
    {
      bullet_spawn(ALIEN, game->aliens[x]->pos, game->bullets);
    }
  }

  // move all active bullets, check their collisions with aliens and player
  for (int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i)
  {
    if (game->bullets[i]->status == INACTIVE)
    {
      continue;
    }
    else if (game->bullets[i]->status == ACTIVE)
    {
      bullet_move(game->bullets[i]);
      check_player_collision(game->bullets[i], game->player);
      check_alien_collision(game->bullets[i], game->aliens, game->aliens_muertos);
    }
    if (game->bullets[i]->status == ACTIVE && (game->bullets[i]->pos.y < 0 || game->bullets[i]->pos.y > WINDOW_HEIGHT))
    {
      game->bullets[i]->status = INACTIVE;
    }
  }

  // check if player is going outside window
  if (game->player->pos.x < BORDER)
  {
    game->player->pos.x = BORDER;
  }
  if (game->player->pos.x + SPRITE_SIZE > WINDOW_WIDTH - BORDER)
  {
    game->player->pos.x = WINDOW_WIDTH - SPRITE_SIZE - BORDER;
  }

  int alien_left = 0;
  for (int i = 0; i < ALIENIGENAS; ++i)
  {
    if (game->aliens[i]->status == ALIVE)
    {
      alien_left = 1;
      break;
    }
  }

  if (alien_left == 0)
  {
    game->state = OVER;
  }
}
