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

LocalServer::LocalServer() {
    this->last_time = SDL_GetTicks();
}

bool LocalServer::add_local_player() {
    if (this->get_num_local_players() >= 3) {
        return false;
    }
    auto player = std::shared_ptr<Player>(new Player());
    player->number = this->players.size();
    player->pos.x = rand() % (ARENA_WIDTH + 1);
    player->pos.y = rand() % (ARENA_HEIGHT + 1);
    player->color = {
        (uint8_t)(rand() % (255 + 1)),
        (uint8_t)(rand() % (255 + 1)),
        (uint8_t)(rand() % (255 + 1))
    };
    this->players.push_back(player);
    add_component(player);
    return true;
}

void LocalServer::tick(std::vector<data::InputStatus> *input_statuses) {

    // process input statuses
    int8_t player_i = 0;
    for (auto player : this->players) {
        auto input_status = (*input_statuses)[player_i];
        player->process_input(input_status);
        player_i++;
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

NetworkMasterServer::NetworkMasterServer() {

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, 7890) == -1) {
        printf("Unable to resolve host 0.0.0.0:7890: %s\n", SDLNet_GetError());
        exit(1);
    }
    this->server_socket = SDLNet_TCP_Open(&ip);
    if (!this->server_socket) {
        printf("Unable to open TCP server socket at 0.0.0.0:7890: %s\n", SDLNet_GetError());
        exit(1);
    }

}

void NetworkMasterServer::tick(std::vector<data::InputStatus> *input_statuses) {

    TCPsocket socket = SDLNet_TCP_Accept(this->server_socket);
    if (socket) {
        this->sockets.push_back(socket);
        // send current state
    }

    // TODO: receive remote input statuses

    LocalServer::tick(input_statuses);

    // broadcast state changes to each socket

}

int8_t NetworkMasterServer::get_num_local_players() {
    return LocalServer::get_num_local_players();
}

NetworkClientServer::NetworkClientServer() {

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, "localhost", 7890) == -1) {
        printf("Unable to resolve host localhost:7890: %s\n", SDLNet_GetError());
        exit(1);
    }
    this->socket = SDLNet_TCP_Open(&ip);
    if (!this->socket) {
        printf("Unable to connect to 0.0.0.0:7890: %s\n", SDLNet_GetError());
        exit(1);
    }

    // read current state

}

void NetworkClientServer::tick(std::vector<data::InputStatus> *input_statuses) {

    // TODO: send input statuses

    // receive state changes

}

int8_t NetworkClientServer::get_num_local_players() {
    return 0;
}

bool NetworkClientServer::add_local_player() {
    return false;
}

}}
