#include <list>
#include <memory>
#include <functional>
#include "Component.h"


namespace game {
namespace components {

namespace {
std::list<std::shared_ptr<Component>> components_list;
}

void for_each_component(std::function<bool(std::shared_ptr<Component>)> action) {
    std::list<std::shared_ptr<Component>>::iterator it = components_list.begin();
    while (it != components_list.end()) {
        auto keep_me = action(*it);
        if (keep_me) {
            ++it;
        } else {
            it = components_list.erase(it);
        }
    }
}

void add_component(std::shared_ptr<Component> component) {
    component->init();
    components_list.push_back(component);
}

}}
