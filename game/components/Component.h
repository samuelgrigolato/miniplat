#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL.h>

namespace game {
namespace components {

class Component {
public:
    virtual ~Component() {};
    virtual void digest_event(SDL_Event *event) = 0;
    virtual bool tick(int32_t &elapsed_time) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
};

}}

#endif
