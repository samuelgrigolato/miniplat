#include <list>
#include <queue>
#include <SDL.h>
#include "game/data/KeyMap.h"
#include "game/data/arena.h"
#include "game/data/Rect.h"
#include "game/data/Action.h"
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

    using namespace game::components;
    using namespace game::data;

    // this gives us a logical viewport no matter
    // what the actual resolution is
    SDL_RenderSetLogicalSize(renderer, ARENA_WIDTH, ARENA_HEIGHT);

    game::init();

    std::list<KeyMap> key_maps;
    key_maps.push_back(KeyMap{
        0, // player;
        SDLK_w, // up;
        SDLK_a, // left;
        SDLK_s, // down;
        SDLK_d, // right;
        SDLK_SPACE // fire;
    });
    key_maps.push_back(KeyMap{
        1, // player;
        (int8_t)SDLK_UP, // up;
        (int8_t)SDLK_LEFT, // left;
        (int8_t)SDLK_DOWN, // down;
        (int8_t)SDLK_RIGHT, // right;
        (int8_t)SDLK_KP_0 // fire;
    });

    SDL_Event event;
    std::queue<Action> pending_actions;
    auto running = true;
    int32_t last_time = SDL_GetTicks();
    int32_t current_time;
    int32_t elapsed_time;
    while (running) {

        // AS CLIENT
        // digest UI events (generate actions)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                for (auto key_map : key_maps) {
                    int8_t key_code;
                    switch (event.type) {
                        case SDL_KEYDOWN:
                            key_code = event.key.keysym.sym;
                            if (key_code == key_map.up) {
                                pending_actions.push(Action{ key_map.player, ActionType::start_moving, "U" });
                            } else if (key_code == key_map.down) {
                                pending_actions.push(Action{ key_map.player, ActionType::start_moving, "D" });
                            } else if (key_code == key_map.left) {
                                pending_actions.push(Action{ key_map.player, ActionType::start_moving, "L" });
                            } else if (key_code == key_map.right) {
                                pending_actions.push(Action{ key_map.player, ActionType::start_moving, "R" });
                            } else if (key_code == key_map.fire) {
                                pending_actions.push(Action{ key_map.player, ActionType::start_firing, NULL });
                            }
                            break;
                        case SDL_KEYUP:
                            key_code = event.key.keysym.sym;
                            if (key_code == key_map.up) {
                                pending_actions.push(Action{ key_map.player, ActionType::stop_moving, "U" });
                            } else if (key_code == key_map.down) {
                                pending_actions.push(Action{ key_map.player, ActionType::stop_moving, "D" });
                            } else if (key_code == key_map.left) {
                                pending_actions.push(Action{ key_map.player, ActionType::stop_moving, "L" });
                            } else if (key_code == key_map.right) {
                                pending_actions.push(Action{ key_map.player, ActionType::stop_moving, "R" });
                            } else if (key_code == key_map.fire) {
                                pending_actions.push(Action{ key_map.player, ActionType::stop_firing, NULL });
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        // TODO: send actions to the server (this can be happening across the network)

        // AS SERVER
        // TODO: digest network packets (this also generates actions)
        // process all pending actions
        while (!pending_actions.empty()) {
            for_each_component([&pending_actions](std::shared_ptr<Component> comp) {
                comp->digest_action(&pending_actions.front());
                return true;
            });
            pending_actions.pop();
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
                Rect &bbox1 = *c1->get_bounding_box();
                Rect &bbox2 = *c2->get_bounding_box();
                if (colliding(bbox1, bbox2)) {
                    c1->process_collision(c2);
                    c2->process_collision(c1);
                }
            });
        // TODO: broadcast state changes (this can be happening across the network)

        // AS CLIENT
        // TODO: receive state changes (this can be happening across the network)
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
