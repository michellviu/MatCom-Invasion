#ifndef RENDER_H
#define RENDER_H

#include "./Game.h"
#include <SDL2/SDL.h>

//Funcion para renderizar el juego
void render_game(game* game, SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* player_texture, SDL_Texture* bullet_texture, SDL_Texture* alien_texture[ALIENIGENAS]);
//Funcion para renderizar el fondo
void render_bg(SDL_Renderer* renderer, SDL_Texture* bg_texture);
//Funcion para renderizar la ventana de pausa
void render_paused(SDL_Renderer* renderer, game* game);
//Funcion para renderizar la pantalla de inicio
void render_start(SDL_Renderer* renderer, game* game);
//Funcion para renderizar la pantalla de fin del juego
void render_over(SDL_Renderer* renderer, game* game);
//Funcion para limpiar los recursos de renderizacion
void render_cleanup(SDL_Texture* bg_texture, SDL_Texture* player_texture, SDL_Texture* bullet_texture, SDL_Texture* alien_texture[ALIENIGENAS]);

#endif
