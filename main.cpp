#include <SDL.h>
#include "game/Game.h"


int main() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // the 0, 0 here means "give me all the screen real state"
    // we then set a "logical" resolution so we can more easily
    // code our game
    SDL_Window *window = SDL_CreateWindow("Miniplat",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          0, 0,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return 1;
    }

    // this gives us a logical viewport no matter
    // what the actual resolution is
    SDL_RenderSetLogicalSize(renderer, 1000, 1000);

    game::Game game;

    SDL_Event event;
    auto running = true;
    int32_t last_time = SDL_GetTicks();
    int32_t current_time;
    int32_t elapsed_time;
    while (running) {

        // digest events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                game.digest_event(&event);
            }
        }

        // run game logic
        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        game.tick(elapsed_time);
        last_time = current_time;

        // render the next frame
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        game.render(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
