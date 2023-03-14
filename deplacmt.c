#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WODTH 640
#define WINDOW_HEIGHT 480

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* bg_texture = NULL;
SDL_Texture* player_texture = NULL;
SDL_Rect player_rect = { 0, 0, 32, 64 };
float player_x = 0;
float player_y = WINDOW_HEIGHT - player_rect.h;
float player_velocity_y = 0;
float jump_velocity = -10.0f;
float gravity = 0.5f;
bool is_jumping = false;
float max_jump_height = 200.0f;

SDL_Surface* platform_surface = NULL;
SDL_Texture* platform_texture = NULL;
SDL_Rect platform_rect = { 0, WINDOW_HEIGHT - 32, WINDOW_WODTH, 32 };

bool quit = false;

void cleanup() {
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(platform_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void load_textures() {
    SDL_Surface* bg_surface = IMG_Load("IMG/fond_map.png");
    if (bg_surface == NULL) {
        printf("Error loading background image: %s\n", SDL_GetError());
        cleanup();
        exit(1);
    }
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    SDL_Surface* player_surface = IMG_Load("IMG/dep1.png");
    if (player_surface == NULL) {
        printf("Error loading player image: %s\n", SDL_GetError());
        cleanup();
        exit(1);
    }
    player_texture = SDL_CreateTextureFromSurface(renderer, player_surface);
    SDL_FreeSurface(player_surface);

    platform_surface = IMG_Load("IMG/sol.jpg");
    if (platform_surface == NULL) {
        printf("Error loading platform image: %s\n", SDL_GetError());
        cleanup();
        exit(1);
    }
    platform_texture = SDL_CreateTextureFromSurface(renderer, platform_surface);
    SDL_FreeSurface(platform_surface);
}

void handle_input(SDL_Event* event) {
    switch (event->type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_SPACE:
                    if (!is_jumping) {
                        is_jumping = true;
                        player_velocity_y = jump_velocity;
                    }
                    break;
                case SDLK_d:
                    player_x += 5;
                    if (player_x > WINDOW_WODTH - player_rect.w) {
                        player_x = WINDOW_WODTH - player_rect.w;
                    }
                    break;
                case SDLK_q:
                    player_x -= 5;
                    if (player_x < 0) {
                        player_x = 0;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void update() {
    // Update player position
    player_y += player_velocity_y;
    if (is_jumping) {
        player_velocity_y += gravity;
        if (player_velocity_y >= 0) {
            is_jumping = false;
        }
    }
    if (player_y > WINDOW_HEIGHT - player_rect.h) {
        player_y = WINDOW_HEIGHT - player_rect.h;
        player_velocity_y = 0;
        is_jumping = false;
    }
    // Check for collision with platform
    if (player_y + player_rect.h >= platform_rect.y && player_y < platform_rect.y + platform_rect.h &&
        player_x + player_rect.w >= platform_rect.x && player_x < platform_rect.x + platform_rect.w) {
      player_y = platform_rect.y - player_rect.h;
      player_velocity_y = 0;
      is_jumping = false;
    }

    // Update platform position
    platform_rect.x -= 1;
    if (platform_rect.x < -platform_rect.w) {
      platform_rect.x = WINDOW_WODTH;
    }

}

void render() {
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
  SDL_RenderCopy(renderer, platform_texture, NULL, &platform_rect);
  player_rect.x = player_x;
  player_rect.y = player_y;
  SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);
  SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    printf("Error initializing SDL_image: %s\n", IMG_GetError());
    return 1;
  }

  window = SDL_CreateWindow("Pingouin sur une plateforme",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WODTH, WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
    cleanup();
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error creating renderer: %s\n", SDL_GetError());
    cleanup();
    return 1;
  }

  load_textures();

  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      handle_input(&event);
    }

    update();
    render();
  }

  cleanup();

  return 0;
}