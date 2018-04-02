#ifndef GAME_H
#define GAME_H

#include <memory>
#include <list>
#include "Component.h"
#include "Player.h"
#include "Shot.h"


namespace game {

class Game : public ComponentRegistry {
public:
    Game();
    void register_component(std::shared_ptr<Component> component) override;
    void digest_event(SDL_Event *event);
    void tick(int32_t &elapsed_time);
    void render(SDL_Renderer *renderer);
private:
    std::list<std::shared_ptr<Component>> components;
};

}

#endif
