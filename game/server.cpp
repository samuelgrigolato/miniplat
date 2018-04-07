#include <memory>
#include <SDL.h>
#include "server.h"
#include "data/arena.h"
#include "data/Color.h"
#include "components/registry.h"
#include "components/Player.h"


namespace game {
namespace server {

using namespace components;

Server::Server(int8_t num_local_players) {
    this->num_local_players = num_local_players;
    this->last_time = SDL_GetTicks();
    this->players = new std::shared_ptr<Player>[num_local_players];

    Color *player_colors = new Color[3];
    player_colors[0] = {255, 100, 100};
    player_colors[1] = {100, 255, 100};
    player_colors[2] = {100, 100, 255};

    for (int8_t i = 0; i < num_local_players; i++) {
        players[i] = std::shared_ptr<Player>(new Player());
        players[i]->number = 0;
        players[i]->pos.x = (ARENA_WIDTH / 10) * (i + 1);
        players[i]->pos.y = (ARENA_HEIGHT / 10) * (i + 1);
        players[i]->color = player_colors[i];
        add_component(players[i]);
    }

}

void Server::tick(data::InputStatus *input_statuses) {

    // process input statuses
    for (int8_t i = 0; i < this->num_local_players; i++) {
        auto input_status = input_statuses[i];
        auto player = players[i];
        player->process_input(input_status);
    }
    // run game logic
    this->current_time = SDL_GetTicks();
    this->elapsed_time = current_time - last_time;
    for_each_component([this](std::shared_ptr<Component> comp) {
        return comp->tick(this->elapsed_time);
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

}

}}
