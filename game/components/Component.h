#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <SDL.h>
#include "../data/Rect.h"

namespace game {
namespace components {

using namespace data;

class Component {
public:
    virtual ~Component() {};
    virtual void init() {};
    virtual void digest_event(SDL_Event *event) {};
    virtual bool tick(int32_t &elapsed_time) { return true; };
    virtual void render(SDL_Renderer *renderer) {};

    virtual Rect* get_bounding_box() { return NULL; }
    virtual void process_collision(std::shared_ptr<Component> other) {};
};

}}

#endif
