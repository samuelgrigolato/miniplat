#ifndef COMPONENTREGISTRY_H
#define COMPONENTREGISTRY_H

#include <memory>
#include "Component.h"


namespace game {

class ComponentRegistry {
public:
    virtual void register_component(std::shared_ptr<Component> component) = 0;
};

}

#endif
