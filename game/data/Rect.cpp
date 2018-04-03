#include "Rect.h"


namespace game {
namespace data {

bool colliding(Rect &r1, Rect &r2) {
    int32_t c1_x1 = r1.x, c1_x2 = r1.x + r1.w;
    int32_t c2_x1 = r2.x, c2_x2 = r2.x + r2.w;
    int32_t c1_y1 = r1.y, c1_y2 = r1.y + r1.h;
    int32_t c2_y1 = r2.y, c2_y2 = r2.y + r2.h;
    return (c1_x1 < c2_x2 && c1_x2 > c2_x1) &&
           (c1_y1 < c2_y2 && c1_y2 > c2_y1);
}

}}
