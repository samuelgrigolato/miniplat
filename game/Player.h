#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "Component.h"
#include "Vec2.h"
#include "Color.h"
#include "KeyMap.h"


namespace game {

class Player : public Component {
public:
    Vec2 pos{0, 0};
    Color color{0, 0, 0};
    KeyMap key_map{-1, -1, -1, -1, -1};
    void digest_event(SDL_Event *event);
    bool tick(int32_t &elapsed_time, ComponentRegistry *registry);
    void render(SDL_Renderer *renderer);
private:
    static const int32_t RECT_SIZE = 50;
    static const int32_t HALF_RECT_SIZE;
    SDL_Rect rect{0, 0, RECT_SIZE, RECT_SIZE};
    Vec2 mov{0, 0};
    bool fire_requested;
    int32_t ms_since_last_shot;
};

}

#endif
