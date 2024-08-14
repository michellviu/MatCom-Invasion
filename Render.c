#include <stdio.h>

// SDL header
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// custom headers
#include "./Utils.h"
#include "./Alien.h"
#include "./Player.h"
#include "./Bullet.h"
#include "./Game.h"
#include "./Render.h"

// This function destroys the given textures used for rendering the background, player, bullets, and aliens.
void render_cleanup(SDL_Texture *bg_texture, SDL_Texture *player_texture, SDL_Texture *bullet_texture, SDL_Texture *alien_texture[ALIENIGENAS])
{
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(bullet_texture);
    for (int i = 0; i < ALIENIGENAS; ++i)
    {
        SDL_DestroyTexture(alien_texture[i]);
    }
}

// Función que renderiza las vidas del jugador en la pantalla
void render_player_lives(SDL_Renderer *renderer, game *game)
{
    SDL_Surface *life_surface; // Superficie para cargar la imagen de la vida del jugador
    SDL_Texture *life_texture; // Textura para la imagen de la vida del jugador

    // Carga la imagen de la vida del jugador desde un archivo BMP
    life_surface = SDL_LoadBMP("./Media/Player.jpg");
    // Crea una textura a partir de la superficie cargada
    life_texture = SDL_CreateTextureFromSurface(renderer, life_surface);
    // Libera la superficie ya que no se necesita más
    SDL_FreeSurface(life_surface);

    // Itera sobre el número de vidas del jugador
    for (int i = 1; i <= game->player->lives; ++i)
    {
        SDL_Rect liferect;                     // Rectángulo para definir la posición y tamaño de la vida en la pantalla
        liferect.w = liferect.h = SPRITE_SIZE; // Establece el ancho y alto del rectángulo al tamaño del sprite
        // Calcula la posición x del rectángulo de vida
        liferect.x = WINDOW_WIDTH - (i * SPRITE_SIZE) - (i * BORDER);
        liferect.y = BORDER; // Establece la posición y del rectángulo de vida

        // Copia la textura de vida al renderizador en la posición especificada por liferect
        SDL_RenderCopy(renderer, life_texture, NULL, &liferect);
    }

    // Destruye la textura de vida para liberar memoria
    SDL_DestroyTexture(life_texture);
}

void render_over(SDL_Renderer *renderer, game *game)
{
    SDL_Rect over_rect = {100, 80, 450, 100};
    SDL_Rect winner_rect = {150, 200, 350, 60};
    SDL_Rect exit_rect = {150, 300, 350, 45};

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./Media/ARCADECLASSIC.TTF", 40);
    SDL_Color fontcolor = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *font_surface = TTF_RenderText_Solid(font, "GAME  OVER", fontcolor);
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &over_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    if (game->winner == PLAYER)
    {
        font_surface = TTF_RenderText_Solid(font, "YOU  WIN", fontcolor);
    }
    else if (game->winner == ALIEN)
    {
        font_surface = TTF_RenderText_Solid(font, "YOU  LOSE", fontcolor);
    }
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &winner_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    font_surface = TTF_RenderText_Solid(font, "PRESS  E  TO  EXIT", fontcolor);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &exit_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    SDL_RenderPresent(renderer);

    TTF_CloseFont(font);
    TTF_Quit();
}

void render_start(SDL_Renderer *renderer, game *game)
{
    SDL_Rect title_rect = {100, 80, 450, 100};
    SDL_Rect start_rect = {50, 200, 550, 45};
    SDL_Rect exit_rect = {150, 280, 350, 45};

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./Media/ARCADECLASSIC.TTF", 40);
    SDL_Color fontcolor = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *font_surface = TTF_RenderText_Solid(font, "SPACE  INVADERS", fontcolor);
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &title_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    font_surface = TTF_RenderText_Solid(font, "PRESS  SPACE  TO  START", fontcolor);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &start_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    font_surface = TTF_RenderText_Solid(font, "PRESS  E  TO  EXIT", fontcolor);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &exit_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    SDL_RenderPresent(renderer);

    TTF_CloseFont(font);
    TTF_Quit();
}
// render pause menu screen
void render_paused(SDL_Renderer *renderer, game *game)
{
    SDL_Rect paused_rect = {175, 80, 300, 75};
    SDL_Rect resume_rect = {50, 200, 550, 45};
    SDL_Rect exit_rect = {150, 280, 350, 45};

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./Media/ARCADECLASSIC.TTF", 40);
    SDL_Color fontcolor = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *font_surface = TTF_RenderText_Solid(font, "PAUSED", fontcolor);
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &paused_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    font_surface = TTF_RenderText_Solid(font, "PRESS  SPACE  TO  RESUME", fontcolor);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &resume_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    font_surface = TTF_RenderText_Solid(font, "PRESS  E  TO  EXIT", fontcolor);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_RenderCopy(renderer, font_texture, NULL, &exit_rect);
    SDL_FreeSurface(font_surface);
    SDL_DestroyTexture(font_texture);

    SDL_RenderPresent(renderer);

    TTF_CloseFont(font);
    TTF_Quit();
}

// render background
void render_bg(SDL_Renderer *renderer, SDL_Texture *bg_texture)
{
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
}

// render player at its pos
void render_player(player *player, SDL_Renderer *renderer, SDL_Texture *player_texture)
{
    SDL_Rect player_rect;
    player_rect.h = player_rect.w = SPRITE_SIZE;
    player_rect.x = player->pos.x;
    player_rect.y = player->pos.y;

    SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);
}

// render alien if it is alive, choosing the sprite depending on its index(row)
void render_alien(alien *alien, SDL_Renderer *renderer, SDL_Texture *alien_texture)
{
    SDL_Rect alien_rect;
    alien_rect.h = alien_rect.w = SPRITE_SIZE;
    alien_rect.x = alien->pos.x;
    alien_rect.y = alien->pos.y;
    SDL_RenderCopy(renderer, alien_texture, NULL, &alien_rect);
}

// render bullet if it is active
void render_bullet(bullet *bullet, SDL_Renderer *renderer, SDL_Texture *bullet_texture)
{
    SDL_Rect bullet_rect;
    bullet_rect.h = bullet_rect.y = SPRITE_SIZE;
    bullet_rect.x = bullet->pos.x;
    bullet_rect.y = bullet->pos.y;

    SDL_RenderCopy(renderer, bullet_texture, NULL, &bullet_rect);
}

// render game
void render_game(game *game, SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *player_texture, SDL_Texture *bullet_texture, SDL_Texture *alien_texture[ALIENIGENAS])
{
    render_player(game->player, renderer, player_texture);

    render_player_lives(renderer, game);

    // render all aliens
    for (int i = 0; i < ALIENIGENAS; ++i)
    {
        if (game->aliens[i]->status == ALIVE)
        {
            render_alien(game->aliens[i], renderer, alien_texture[i]);
        }
    }

    // render all bullets
    for (int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i)
    {
        if (game->bullets[i]->status == ACTIVE)
        {
            render_bullet(game->bullets[i], renderer, bullet_texture);
        }
    }
}
