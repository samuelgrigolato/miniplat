#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <SDL.h>
#include "../data/InputStatus.h"
#include "../data/Rect.h"
#include "../data/CompAttrs.h"

namespace game {
namespace components {

using namespace data;

class Component {
public:
    virtual ~Component() {};
    virtual void init() {};
    virtual bool tick(int32_t &elapsed_time) { return true; };
    virtual void render(SDL_Renderer *renderer) {};
    virtual bool has_attribute(CompAttrs attr) const { return false; };
    virtual Rect* get_bounding_box() { return NULL; }
    virtual void process_collision(std::shared_ptr<Component> other) {};
};

}}

#endif
