#ifndef COMPONENTREGISTRY_H
#define COMPONENTREGISTRY_H

#include "Component.h"


namespace game {

class ComponentRegistry {
public:
    virtual void register_component(Component *component) = 0;
};

}

#endif
