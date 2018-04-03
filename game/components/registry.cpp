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

void for_each_component_pair(std::function<bool(std::shared_ptr<Component>)> applies_for,
                             std::function<void(std::shared_ptr<Component>, std::shared_ptr<Component>)> action) {
    std::list<std::shared_ptr<Component>>::iterator it1 = components_list.begin();
    while (it1 != components_list.end()) {
        if (applies_for(*it1)) {
            std::list<std::shared_ptr<Component>>::iterator it2 = it1;
            it2++;
            while (it2 != components_list.end()) {
                if (applies_for(*it2)) {
                    action(*it1, *it2);
                }
                it2++;
            }
        }
        it1++;
    }
}

void add_component(std::shared_ptr<Component> component) {
    component->init();
    components_list.push_back(component);
}

}}
