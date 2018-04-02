#include "Game.h"


namespace game {

Game::Game() {

    this->player1.pos.x = 100;
    this->player1.pos.y = 100;
    this->player1.color.r = 255;
    this->player1.color.g = 100;
    this->player1.color.b = 100;
    this->player1.key_map.up = SDLK_w;
    this->player1.key_map.left = SDLK_a;
    this->player1.key_map.down = SDLK_s;
    this->player1.key_map.right = SDLK_d;
    this->player1.key_map.fire = SDLK_SPACE;

    this->player2.pos.x = 900;
    this->player2.pos.y = 900;
    this->player2.color.r = 100;
    this->player2.color.g = 100;
    this->player2.color.b = 255;
    this->player2.key_map.up = (int8_t)SDLK_UP;
    this->player2.key_map.left = (int8_t)SDLK_LEFT;
    this->player2.key_map.down = (int8_t)SDLK_DOWN;
    this->player2.key_map.right = (int8_t)SDLK_RIGHT;
    this->player2.key_map.fire = SDLK_0;

}

void Game::digest_event(SDL_Event *event) {
    this->player1.digest_event(event);
    this->player2.digest_event(event);
    if (this->shot != NULL) {
        this->shot->digest_event(event);
    }
}

void Game::tick(int &elapsed_time) {
    this->player1.tick(elapsed_time, this);
    this->player2.tick(elapsed_time, this);
    if (this->shot != NULL) {
        this->shot->tick(elapsed_time, this);
    }
}

void Game::render(SDL_Renderer *renderer) {
    this->player1.render(renderer);
    this->player2.render(renderer);
    if (this->shot != NULL) {
        this->shot->render(renderer);
    }
}

void Game::register_component(Component *component) {
    this->shot = (Shot*)component;
}

}
