#ifndef REGISTRY_H
#define REGISTRY_H

#include <memory>
#include <functional>
#include "Component.h"


namespace game {
namespace components {

void for_each_component(std::function<bool(std::shared_ptr<Component>)> action);

void for_each_component_pair(std::function<bool(std::shared_ptr<Component>)> applies_for,
                             std::function<void(std::shared_ptr<Component>, std::shared_ptr<Component>)> action);

void add_component(std::shared_ptr<components::Component> component);

}}

#endif
