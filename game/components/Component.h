#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL.h>

namespace game {
namespace components {

class Component {
public:
    virtual ~Component() {};
    virtual void init() {};
    virtual void digest_event(SDL_Event *event) {};
    virtual bool tick(int32_t &elapsed_time) { return true; };
    virtual void render(SDL_Renderer *renderer) {};
};

}}

#endif
