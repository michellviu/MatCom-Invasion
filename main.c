#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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

struct Datos_Hilo1
{
    int playerleft;
    int playerright;
    int quit;
    SDL_Event event;
    game *game0;
};

void *eventos(void *arg)
{
    struct Datos_Hilo1 *datos = (struct Datos_Hilo1 *)arg;

    // polling for event started
    while (SDL_PollEvent(&datos->event))
    {
        if (datos->event.type == SDL_QUIT)
        {
            datos->quit = 1;
            break;
        }

        // checking keypresses while game is running
        else if (datos->event.type == SDL_KEYDOWN && datos->game0->state == RUNNING)
        {

            if (datos->event.key.keysym.sym == SDLK_LEFT)
            {
                datos->playerright = 0;
                datos->playerleft = 1;
            }
            else if (datos->event.key.keysym.sym == SDLK_RIGHT)
            {
                datos->playerleft = 0;
                datos->playerright = 1;
            }
            if (datos->event.key.keysym.sym == SDLK_SPACE)
            {
                bullet_spawn(PLAYER, datos->game0->player->pos, datos->game0->bullets);
            }
            if (datos->event.key.keysym.sym == SDLK_ESCAPE)
            {
                game_pause(datos->game0);
            }
        }

        // checking keyups while game is running
        else if (datos->event.type == SDL_KEYUP && datos->game0->state == RUNNING)
        {
            if (datos->event.key.keysym.sym == SDLK_LEFT)
            {
                datos->playerleft = 0;
            }
            if (datos->event.key.keysym.sym == SDLK_RIGHT)
            {
                datos->playerright = 0;
            }
        }
    } // polling for event ended

    // do player movement based on values of variables
    // putting player_move() directly in the event polling loop causes it to be called
    // irregularly and upredictably, making movement choppy
    if (datos->playerleft == 1)
    {
        player_move(datos->game0->player, LEFT);
    }
    if (datos->playerright == 1)
    {
        player_move(datos->game0->player, RIGHT);
    }
}

int main(int argc, char *argv[])
{
    // initialize the game variable and allocate memory to it
    // this holds everything related to the current game,
    // including state, level, player, aliens, and bullets
    game *game0 = malloc(sizeof(game));
    game_init(game0);

    // initialize the SDL_VIDEO subsystem
    // also automatically inits the 2 default SDL subsystems, file i/o and threading
    SDL_Init(SDL_INIT_VIDEO);

    // create the renderer and window
    SDL_Window *window = SDL_CreateWindow("MatCom Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // create event to listen for keypresses and SDL_QUIT
    SDL_Event event;

    // draw a black screen, just in case
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *bg_surface = SDL_LoadBMP("./Media/Fondo.bmp");
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    SDL_Surface *player_surface = SDL_LoadBMP("./Media/Player_BMP.bmp");
    SDL_Texture *player_texture = SDL_CreateTextureFromSurface(renderer, player_surface);
    SDL_FreeSurface(player_surface);

    SDL_Surface *bullet_surface = SDL_LoadBMP("./Media/invaders_sword.bmp");
    SDL_Texture *bullet_texture = SDL_CreateTextureFromSurface(renderer, bullet_surface);
    SDL_FreeSurface(bullet_surface);

    SDL_Texture *alien_texture[ALIENIGENAS];

    SDL_Surface *alien_surface = SDL_LoadBMP("./Media/Alien_BMP.bmp");
    for (int i = 0; i < ALIENIGENAS; i++)
    {
        alien_texture[i] = SDL_CreateTextureFromSurface(renderer, alien_surface);
    }
    SDL_FreeSurface(alien_surface);

    
    int quit = 0;
    int starttimer;
    int alienmovecounter = 0;

    struct Datos_Hilo1 datos;
    datos.event = event;
    datos.game0 = game0;
    datos.playerleft = 0;
    datos.playerright = 0;
    datos.quit = 0;

    while (1)
    {
        if (game0->state == PAUSED)
        {
            paused(renderer, window, game0, bg_texture, player_texture, bullet_texture, alien_texture);
        }
        else if (game0->state == OVER)
        {
            over(renderer, window, game0, bg_texture, player_texture, bullet_texture, alien_texture);
        }
        else if (game0->state == START)
        {
            start(renderer, window, game0, bg_texture, player_texture, bullet_texture, alien_texture);
        }
        else
        {

            quit = 0;

            // initializing startimer for every iteration to count the time taken
            // by the loop, to facilitate FPS capping using SDL_Delay at the end
            // of the loop
            starttimer = SDL_GetTicks();

            ++alienmovecounter;

            pthread_t hilo_eventos;
            pthread_create(&hilo_eventos, NULL, eventos, (void *)&datos);
            if (datos.quit)
            {
                break;
            }
            // break out from gameloop if quit

            // check if any aliens are still alive
            // if all are dead, game over, with player as winner
            int alien_left = 0;
            for (int i = 0; i < ALIENIGENAS; ++i)
            {
                if (game0->aliens[i]->status == ALIVE)
                {
                    alien_left = 1;
                    if (game0->aliens[i]->pos.y + SPRITE_SIZE > game0->player->pos.y)
                    {
                        game0->winner = ALIEN;
                        game0->state = OVER;
                    }
                }
            }
            if (alien_left == 0)
            {
                game0->winner = PLAYER;
                game0->state = OVER;
            }

            // check if player is dead
            // if player dead, call game over with winner alien
            if (game0->player->lives <= 0)
            {
                game0->winner = ALIEN;
                game0->state = OVER;
            }

            // render background
            render_bg(renderer, bg_texture);
            // update entire game variable
            game_update(game0, alienmovecounter);
            // render player, aliens, and bullets using the game variable
            render_game(game0, renderer, window, player_texture, bullet_texture, alien_texture);
            // present renderer
            SDL_RenderPresent(renderer);

            // cap framerate to FPS
            // 1000/FPS is the number of ms for one frame
            // if current iteration of the loop has run for less time than
            // this (running time is given by SDL_GetTicks() - starttimer),
            // then we delay until that time
            if (SDL_GetTicks() - starttimer < 1000 / FPS)
            {
                SDL_Delay(1000 / FPS - (SDL_GetTicks() - starttimer));
            }
        }
    }

    // clean up game, renderer and window
    game_cleanup(game0);
    free(game0);
    render_cleanup(bg_texture, player_texture, bullet_texture, alien_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
