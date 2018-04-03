#include "../data/arena.h"
#include "Shot.h"


namespace game {
namespace components {

bool Shot::tick(int32_t &elapsed_time) {
    ColoredBox::tick(elapsed_time);
    return this->pos.x > 0 && this->pos.x < data::ARENA_WIDTH - BOX_SIZE() &&
           this->pos.y > 0 && this->pos.y < data::ARENA_HEIGHT - BOX_SIZE();
}

}}
