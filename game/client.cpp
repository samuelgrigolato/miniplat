#include <memory>
#include <SDL.h>
#include "client.h"
#include "data/arena.h"
#include "data/InputStatus.h"
#include "data/KeyMap.h"
#include "components/registry.h"
#include "components/Component.h"


namespace game {
namespace client {

using namespace components;
using namespace data;

const int8_t MAX_LOCAL_PLAYERS = 3;

int run(server::Server *server) {

    // asserts num of local players
    int8_t num_local_players = server->get_num_local_players();
    if (num_local_players > MAX_LOCAL_PLAYERS) {
        printf("This client supports a maximum of %d local players.", MAX_LOCAL_PLAYERS);
        return -1;
    }

    // hardcode key maps
    // in the future this can be improved to allow
    // customization in a GUI menu
    KeyMap *key_maps = new KeyMap[MAX_LOCAL_PLAYERS];
    key_maps[0].up = SDLK_w;
    key_maps[0].down = SDLK_s;
    key_maps[0].left = SDLK_a;
    key_maps[0].right = SDLK_d;
    key_maps[0].fire = SDLK_SPACE;
    key_maps[1].up = SDLK_UP;
    key_maps[1].down = SDLK_DOWN;
    key_maps[1].left = SDLK_LEFT;
    key_maps[1].right = SDLK_RIGHT;
    key_maps[1].fire = SDLK_KP_0;
    key_maps[2].up = SDLK_i;
    key_maps[2].down = SDLK_k;
    key_maps[2].left = SDLK_j;
    key_maps[2].right = SDLK_l;
    key_maps[2].fire = SDLK_RCTRL;

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
    SDL_RenderSetLogicalSize(renderer, ARENA_WIDTH, ARENA_HEIGHT);

    InputStatus *input_statuses = new InputStatus[num_local_players];
    SDL_Event event;
    auto running = true;
    while (running) {

        // digest UI events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                for (int8_t i = 0; i < num_local_players; i++) {
                    auto key_map = &key_maps[i];
                    auto input_status = &input_statuses[i];
                    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                        int32_t key_code = event.key.keysym.sym;
                        InputType input_type = InputType::none;
                        if (key_code == key_map->up) {
                            input_type = InputType::move_up;
                        } else if (key_code == key_map->down) {
                            input_type = InputType::move_down;
                        } else if (key_code == key_map->left) {
                            input_type = InputType::move_left;
                        } else if (key_code == key_map->right) {
                            input_type = InputType::move_right;
                        } else if (key_code == key_map->fire) {
                            input_type = InputType::fire;
                        }
                        if (input_type != InputType::none) {
                            if (event.type == SDL_KEYDOWN) {
                                input_status->set(input_type);
                            } else if (event.type == SDL_KEYUP) {
                                input_status->unset(input_type);
                            }
                        }
                    }
                }
            }
        }

        server->tick(input_statuses);

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

}}
