#ifndef PHYSICALBODY_H
#define PHYSICALBODY_H


#include "Component.h"
#include "../data/Vec2.h"


namespace game {
namespace components {

using namespace data;

class PhysicalBody : public Component {
public:
    //game logic
    Vec2 pos{0, 0};
    Vec2 vel{0, 0};
    bool tick(int32_t &elapsed_time) override;
};

}}

#endif
