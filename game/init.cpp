#include <memory>
#include <list>
#include "data/arena.h"
#include "components/registry.h"
#include "components/Player.h"


namespace game {

using namespace components;

void init() {

    std::shared_ptr<Player> p1(new Player());
    p1->pos.x = data::ARENA_WIDTH / 10;
    p1->pos.y = data::ARENA_HEIGHT / 10;
    p1->color.r = 255;
    p1->color.g = 100;
    p1->color.b = 100;
    p1->key_map.up = SDLK_w;
    p1->key_map.left = SDLK_a;
    p1->key_map.down = SDLK_s;
    p1->key_map.right = SDLK_d;
    p1->key_map.fire = SDLK_SPACE;
    add_component(p1);

    std::shared_ptr<Player> p2(new Player());
    p2->pos.x = (data::ARENA_WIDTH / 10) * 9;
    p2->pos.y = (data::ARENA_HEIGHT / 10) * 9;
    p2->color.r = 100;
    p2->color.g = 100;
    p2->color.b = 255;
    p2->key_map.up = (int8_t)SDLK_UP;
    p2->key_map.left = (int8_t)SDLK_LEFT;
    p2->key_map.down = (int8_t)SDLK_DOWN;
    p2->key_map.right = (int8_t)SDLK_RIGHT;
    p2->key_map.fire = (int8_t)SDLK_KP_0;
    add_component(p2);

}

}
