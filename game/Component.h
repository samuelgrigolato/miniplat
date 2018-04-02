#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL.h>

namespace game {

class Component;

}

#include "ComponentRegistry.h"


namespace game {

class Component {
public:
    virtual ~Component() {};
    virtual void digest_event(SDL_Event *event) = 0;
    virtual bool tick(int32_t &elapsed_time, ComponentRegistry *registry) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
};

}

#endif
