#include "PhysicalBody.h"


const int32_t MOV_PX_PER_MILLI = 1;


namespace game {
namespace components {

bool PhysicalBody::tick(int32_t &elapsed_time) {
    this->pos.x += MOV_PX_PER_MILLI * elapsed_time * this->vel.x;
    this->pos.y += MOV_PX_PER_MILLI * elapsed_time * this->vel.y;
    return true;
}

}}
