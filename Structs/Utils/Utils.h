#ifndef HELPERS_H
#define HELPERS_H

#define BORDER 5
#define WINDOW_WIDTH 640 + 2 * BORDER
#define WINDOW_HEIGHT 480 + 2 * BORDER

#define SPRITE_SIZE 32

#define MAX_BULLETS_ON_SCREEN 5

#define ALIEN_BLOCK_ROWS 5
#define ALIEN_BLOCK_COLUMNS 10

#define ALIENIGENAS 20

#define PLAYER_STARTING_X 325 //WINDOW_WIDTH/2 doesnt work, and I have no idea why fml
#define PLAYER_STARTING_Y WINDOW_HEIGHT - SPRITE_SIZE - BORDER

#define BULLET_SPEED 5
#define PLAYER_SPEED 7

#define FPS 60

typedef struct {
  int x;
  int y;
} position;

typedef enum {
  PLAYER,
  ALIEN,
  BULLET
} character;

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN
} direction;




#endif
