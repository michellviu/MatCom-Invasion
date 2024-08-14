#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// sdl headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// custom headers
#include "./Alien.h"
#include "./Player.h"
#include "./Bullet.h"
#include "./Game.h"
#include "./Render.h"

void paused(SDL_Renderer *renderer, SDL_Window *window, game *game, SDL_Texture *bg_texture, SDL_Texture *player_texture, SDL_Texture *bullet_texture, SDL_Texture *alien_texture[ALIENIGENAS])
{
    SDL_Event event;

    int quit = 0;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = 1;
            break;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_e:
                game_cleanup(game);
                game_init(game);
                break;
            case SDLK_SPACE:
                game->state = RUNNING;
                break;
            default:
            {
            }
            }
        }
    }

    if (quit)
    {
        game_cleanup(game);
        free(game);
        render_cleanup(bg_texture, player_texture, bullet_texture, alien_texture);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(EXIT_SUCCESS);
    }

    render_paused(renderer, game);
}

void over(SDL_Renderer *renderer, SDL_Window *window, game *game, SDL_Texture *bg_texture, SDL_Texture *player_texture, SDL_Texture *bullet_texture, SDL_Texture *alien_texture[ALIENIGENAS])
{
    SDL_Event event;

    int quit = 0;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = 1;
            break;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_e:
                quit = 1;
                break;
            case SDLK_SPACE:
                game_cleanup(game);
                game_init(game);
                break;
            default:
            {
            }
            }
        }
    }

    if (quit)
    {
        game_cleanup(game);
        free(game);
        render_cleanup(bg_texture, player_texture, bullet_texture, alien_texture);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(EXIT_SUCCESS);
    }

    render_over(renderer, game);
}

void start(SDL_Renderer *renderer, SDL_Window *window, game *game, SDL_Texture *bg_texture, SDL_Texture *player_texture, SDL_Texture *bullet_texture, SDL_Texture *alien_texture[ALIENIGENAS])
{
    SDL_Event event;

    int quit = 0;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = 1;
            break;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_e:
                quit = 1;
                break;
            case SDLK_SPACE:
                game->state = RUNNING;
                break;
            default:
            {
            }
            }
        }
    }

    if (quit)
    {
        game_cleanup(game);
        free(game);
        render_cleanup(bg_texture, player_texture, bullet_texture, alien_texture);
        SDL_DestroyTexture(bg_texture);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        exit(EXIT_SUCCESS);
    }

    render_start(renderer, game);
}

int main(int argc, char *argv[])
{
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crear una ventana
    SDL_Window *window = SDL_CreateWindow("Ventana SDL2",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("No se pudo crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear un renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("No se pudo crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Establecer el color del renderer (rojo)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

    // Limpiar el renderer
    SDL_RenderClear(renderer);

    // Presentar el renderer
    SDL_RenderPresent(renderer);

    // Esperar 5 segundos
    SDL_Delay(5000);

    // Limpiar y cerrar SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}