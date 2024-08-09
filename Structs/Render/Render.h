#ifndef RENDER_H
#define RENDER_H

#include <Game/Game.h>
#include <SDL2/SDL.h>
void render_game(game* game, SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* player_texture, SDL_Texture* bullet_texture, SDL_Texture* alien_texture[ALIENIGENAS]);
void render_bg(SDL_Renderer* renderer, SDL_Texture* bg_texture);
void render_paused(SDL_Renderer* renderer, game* game);
void render_start(SDL_Renderer* renderer, game* game);
void render_over(SDL_Renderer* renderer, game* game);
void render_cleanup(SDL_Texture* bg_texture, SDL_Texture* player_texture, SDL_Texture* bullet_texture, SDL_Texture* alien_texture[ALIENIGENAS]);

#endif
