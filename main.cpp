#include <SDL.h>
#include "game/data/arena.h"
#include "game/data/Rect.h"
#include "game/init.h"
#include "game/components/registry.h"
#include "game/components/Component.h"


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
    SDL_RenderSetLogicalSize(renderer, game::data::ARENA_WIDTH, game::data::ARENA_HEIGHT);

    game::init();

    SDL_Event event;
    auto running = true;
    int32_t last_time = SDL_GetTicks();
    int32_t current_time;
    int32_t elapsed_time;
    while (running) {

        using namespace game::components;

        // digest events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                for_each_component([&event](std::shared_ptr<Component> comp) {
                    comp->digest_event(&event);
                    return true;
                });
            }
        }

        // run game logic
        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        for_each_component([&elapsed_time](std::shared_ptr<Component> comp) {
            return comp->tick(elapsed_time);
        });
        last_time = current_time;

        // process collisions
        for_each_component_pair(
            // that is collidable
            [](std::shared_ptr<Component> comp) {
                return comp->get_bounding_box() != NULL;
            },
            [](std::shared_ptr<Component> c1, std::shared_ptr<Component> c2) {
                game::data::Rect &bbox1 = *c1->get_bounding_box();
                game::data::Rect &bbox2 = *c2->get_bounding_box();
                if (game::data::colliding(bbox1, bbox2)) {
                    c1->process_collision(c2);
                    c2->process_collision(c1);
                }
            });

        // render the next frame
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for_each_component([&renderer](std::shared_ptr<Component> comp) {
            comp->render(renderer);
            return true;
        });
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
