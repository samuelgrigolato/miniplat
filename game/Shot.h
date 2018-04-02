#ifndef SHOT_H
#define SHOT_H

#include "Component.h"
#include "Vec2.h"
#include "Color.h"
#include "KeyMap.h"


namespace game {

class Shot : public Component {
public:
    Vec2 pos{0, 0};
    Color color{0, 0, 0};
    void digest_event(SDL_Event *event);
    void tick(int32_t &elapsed_time, ComponentRegistry *registry);
    void render(SDL_Renderer *renderer);
private:
    static const int32_t RECT_SIZE = 20;
    static const int32_t HALF_RECT_SIZE;
    SDL_Rect rect{0, 0, RECT_SIZE, RECT_SIZE};
};

}

#endif
