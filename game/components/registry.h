#ifndef REGISTRY_H
#define REGISTRY_H

#include <memory>
#include <functional>
#include "Component.h"


namespace game {
namespace components {

void for_each_component(std::function<bool(std::shared_ptr<Component>)> action);

void add_component(std::shared_ptr<components::Component> component);

}}

#endif
