#ifndef GAME_H
#define GAME_H

#include <list>
#include "Component.h"
#include "Player.h"
#include "Shot.h"


namespace game {

class Game : public ComponentRegistry {
public:
    Game();
    void digest_event(SDL_Event *event);
    void tick(int32_t &elapsed_time);
    void render(SDL_Renderer *renderer);
    void register_component(Component *component);
private:
    std::list<Component*> components;
};

}

#endif
