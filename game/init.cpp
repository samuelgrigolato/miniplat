#include <memory>
#include <list>
#include "data/arena.h"
#include "components/registry.h"
#include "components/Player.h"


namespace game {

using namespace components;

void init() {

    std::shared_ptr<Player> p1(new Player());
    p1->number = 0;
    p1->pos.x = data::ARENA_WIDTH / 10;
    p1->pos.y = data::ARENA_HEIGHT / 10;
    p1->color.r = 255;
    p1->color.g = 100;
    p1->color.b = 100;
    add_component(p1);

    std::shared_ptr<Player> p2(new Player());
    p2->number = 1;
    p2->pos.x = (data::ARENA_WIDTH / 10) * 9;
    p2->pos.y = (data::ARENA_HEIGHT / 10) * 9;
    p2->color.r = 100;
    p2->color.g = 100;
    p2->color.b = 255;
    add_component(p2);

}

}
