#ifndef SHOT_H
#define SHOT_H

#include "../data/CompAttrs.h"
#include "ColoredBox.h"


namespace game {
namespace components {

using namespace data;

class Shot : public ColoredBox {
public:
    bool tick(int32_t &elapsed_time) override;
private:
    //game logic
    int32_t BOX_SIZE() const override { return 10; }
    bool has_attribute(CompAttrs attr) const override {
        return attr == CompAttrs::projectile;
    }
};

}}

#endif
