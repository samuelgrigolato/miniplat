#include "Game.h"


namespace game {

Game::Game() {

    Player *p1 = new Player();
    p1->pos.x = 100;
    p1->pos.y = 100;
    p1->color.r = 255;
    p1->color.g = 100;
    p1->color.b = 100;
    p1->key_map.up = SDLK_w;
    p1->key_map.left = SDLK_a;
    p1->key_map.down = SDLK_s;
    p1->key_map.right = SDLK_d;
    p1->key_map.fire = SDLK_SPACE;
    this->register_component(p1);

    Player *p2 = new Player();
    p2->pos.x = 900;
    p2->pos.y = 900;
    p2->color.r = 100;
    p2->color.g = 100;
    p2->color.b = 255;
    p2->key_map.up = (int8_t)SDLK_UP;
    p2->key_map.left = (int8_t)SDLK_LEFT;
    p2->key_map.down = (int8_t)SDLK_DOWN;
    p2->key_map.right = (int8_t)SDLK_RIGHT;
    p2->key_map.fire = SDLK_0;
    this->register_component(p2);

}

void Game::digest_event(SDL_Event *event) {
    for (Component *comp : this->components) {
        comp->digest_event(event);
    }
}

void Game::tick(int &elapsed_time) {
    std::list<Component*>::iterator it = this->components.begin();
    while (it != this->components.end()) {
        auto keep_me_alive = (*it)->tick(elapsed_time, this);
        if (keep_me_alive) {
            ++it;
        } else {
            it = this->components.erase(it);
        }
    }
}

void Game::render(SDL_Renderer *renderer) {
    for (Component *comp : this->components) {
        comp->render(renderer);
    }
}

void Game::register_component(Component *component) {
    this->components.push_back(component);
}

}
