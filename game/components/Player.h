#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "ColoredBox.h"
#include "../data/Vec2.h"
#include "../data/Rect.h"
#include "../data/KeyMap.h"


namespace game {
namespace components {

using namespace data;

class Player : public ColoredBox {
public:
    KeyMap key_map{-1, -1, -1, -1, -1};
    void digest_event(SDL_Event *event) override;
    bool tick(int32_t &elapsed_time) override;
    void render(SDL_Renderer *renderer) override;
    void process_collision(std::shared_ptr<Component> other) override;
private:
    //game logic
    int32_t BOX_SIZE() const override { return 25; }
    bool alive = true;
    bool firing;
    int32_t ms_since_last_shot;
    Vec2 facing_direction{1, 0};
    //render
    Rect direction_mark_rect{0, 0, BOX_SIZE()/2, BOX_SIZE()/2};
};

}}

#endif
