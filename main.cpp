#include <list>
#include <queue>
#include <SDL.h>
#include "game/data/KeyMap.h"
#include "game/data/arena.h"
#include "game/data/Rect.h"
#include "game/data/InputStatus.h"
#include "game/components/registry.h"
#include "game/components/Component.h"
#include "game/components/Player.h"


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

    int8_t num_players = 2;
    KeyMap *key_maps = new KeyMap[num_players];
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
    InputStatus *input_statuses = new InputStatus[num_players];
    std::shared_ptr<Player> *players = new std::shared_ptr<Player>[2];
    players[0] = std::shared_ptr<Player>(new Player());
    players[0]->number = 0;
    players[0]->pos.x = ARENA_WIDTH / 10;
    players[0]->pos.y = ARENA_HEIGHT / 10;
    players[0]->color.r = 255;
    players[0]->color.g = 100;
    players[0]->color.b = 100;
    add_component(players[0]);
    players[1] = std::shared_ptr<Player>(new Player());
    players[1]->number = 0;
    players[1]->pos.x = (ARENA_WIDTH / 10) * 9;
    players[1]->pos.y = (ARENA_HEIGHT / 10) * 9;
    players[1]->color.r = 100;
    players[1]->color.g = 100;
    players[1]->color.b = 255;
    add_component(players[1]);

    SDL_Event event;
    auto running = true;
    int32_t last_time = SDL_GetTicks();
    int32_t current_time;
    int32_t elapsed_time;
    while (running) {

        // digest UI events (update input status)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                for (int8_t i = 0; i < num_players; i++) {
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

        // TODO: send input_statuses to the server (this can happen locally or across the network)
        // TODO: digest network packets (receives updated input_statuses)

        // process input statuses
        for (int8_t i = 0; i < num_players; i++) {
            auto input_status = input_statuses[i];
            auto player = players[i];
            player->process_input(input_status);
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

        // TODO: broadcast state changes (this can happen across the network)
        // TODO: receive state changes (this can happen across the network)

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
