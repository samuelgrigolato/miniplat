#include <memory>
#include "../data/CompAttrs.h"
#include "registry.h"
#include "Player.h"
#include "Shot.h"


const int32_t MILLIS_PER_SHOT = 500;


namespace game {
namespace components {

void Player::digest_event(SDL_Event *event) {
    int8_t key_code;
    switch (event->type) {
        case SDL_KEYDOWN:
            key_code = event->key.keysym.sym;
            if (key_code == this->key_map.up) {
                this->vel.y = -1;
                this->facing_direction.y = -1;
                this->facing_direction.x = 0;
            } else if (key_code == this->key_map.down) {
                this->vel.y = 1;
                this->facing_direction.y = 1;
                this->facing_direction.x = 0;
            } else if (key_code == this->key_map.right) {
                this->vel.x = 1;
                this->facing_direction.y = 0;
                this->facing_direction.x = 1;
            } else if (key_code == this->key_map.left) {
                this->vel.x = -1;
                this->facing_direction.y = 0;
                this->facing_direction.x = -1;
            } else if (key_code == this->key_map.fire) {
                this->firing = true;
            }
            break;
        case SDL_KEYUP:
            key_code = event->key.keysym.sym;
            if (key_code == this->key_map.up || key_code == this->key_map.down) {
                this->vel.y = 0;
            } else if (key_code == this->key_map.left || key_code == this->key_map.right) {
                this->vel.x = 0;
            } else if (key_code == this->key_map.fire) {
                this->firing = false;
            }
            break;
        default:
            break;
    }
}

bool Player::tick(int32_t &elapsed_time) {
    ColoredBox::tick(elapsed_time);

    this->ms_since_last_shot += elapsed_time;
    if (this->ms_since_last_shot >= MILLIS_PER_SHOT) {
        if (this->firing) {
            this->ms_since_last_shot = 0;
            std::shared_ptr<Shot> shot(new Shot());
            shot->pos = this->pos;
            shot->pos.x += BOX_SIZE() * this->facing_direction.x;
            shot->pos.y += BOX_SIZE() * this->facing_direction.y;
            shot->vel = this->facing_direction;
            shot->color = this->color;
            add_component(shot);
        }
    } else {
        this->ms_since_last_shot += elapsed_time;
    }

    return this->alive;
}

void Player::process_collision(std::shared_ptr<Component> other) {
    if (other->has_attribute(CompAttrs::projectile)) {
        this->alive = false;
    }
}

void Player::render(SDL_Renderer *renderer) {
    ColoredBox::render(renderer);

    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, 255);
    if (this->facing_direction.x == 1) {
        this->direction_mark_rect.x = this->rect.x + BOX_SIZE();
    } else if (this->facing_direction.x == -1) {
        this->direction_mark_rect.x = this->rect.x - BOX_SIZE()/2;
    } else {
        this->direction_mark_rect.x = this->rect.x + BOX_SIZE()/4;
    }
    if (this->facing_direction.y == 1) {
        this->direction_mark_rect.y = this->rect.y + BOX_SIZE();
    } else if (this->facing_direction.y == -1) {
        this->direction_mark_rect.y = this->rect.y - BOX_SIZE()/2;
    } else {
        this->direction_mark_rect.y = this->rect.y + BOX_SIZE()/4;
    }
    SDL_RenderFillRect(renderer, &this->direction_mark_rect);

}

}}
