#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "Component.h"
#include "../data/Vec2.h"
#include "../data/Color.h"
#include "../data/KeyMap.h"


namespace game {
namespace components {

using namespace data;

class Player : public Component {
public:
    Vec2 pos{0, 0};
    Color color{0, 0, 0};
    KeyMap key_map{-1, -1, -1, -1, -1};
    void digest_event(SDL_Event *event) override;
    bool tick(int32_t &elapsed_time) override;
    void render(SDL_Renderer *renderer) override;
private:
    static const int32_t RECT_SIZE = 20;
    SDL_Rect rect{0, 0, RECT_SIZE, RECT_SIZE};
    SDL_Rect direction_mark_rect{0, 0, RECT_SIZE/2, RECT_SIZE/2};
    Vec2 mov{0, 0};
    bool firing;
    int32_t ms_since_last_shot;
    Vec2 facing_direction{1, 0};
};

}}

#endif
