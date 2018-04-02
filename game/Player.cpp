#include "Player.h"
#include "Shot.h"


namespace game {

const int32_t Player::HALF_RECT_SIZE = Player::RECT_SIZE / 2;
const int32_t MOV_PX_PER_MILLI = 1;

void Player::digest_event(SDL_Event *event) {
    int8_t key_code;
    switch (event->type) {
        case SDL_KEYDOWN:
            key_code = event->key.keysym.sym;
            if (key_code == this->key_map.up) {
                this->mov.y = -1;
            } else if (key_code == this->key_map.down) {
                this->mov.y = 1;
            } else if (key_code == this->key_map.right) {
                this->mov.x = 1;
            } else if (key_code == this->key_map.left) {
                this->mov.x = -1;
            } else if (key_code == this->key_map.fire) {
                this->fire_requested = true;
            }
            break;
        case SDL_KEYUP:
            key_code = event->key.keysym.sym;
            if (key_code == this->key_map.up || key_code == this->key_map.down) {
                this->mov.y = 0;
            } else if (key_code == this->key_map.left || key_code == this->key_map.right) {
                this->mov.x = 0;
            }
            break;
        default:
            break;
    }
}

bool Player::tick(int32_t &elapsed_time, ComponentRegistry *registry) {
    this->pos.x += MOV_PX_PER_MILLI * elapsed_time * this->mov.x;
    this->pos.y += MOV_PX_PER_MILLI * elapsed_time * this->mov.y;
    this->ms_since_last_shot += elapsed_time;
    if (this->ms_since_last_shot >= 1000) {
        this->ms_since_last_shot %= 1000;
        if (this->fire_requested) {
            std::shared_ptr<Shot> shot(new Shot());
            shot->pos = this->pos;
            shot->color = this->color;
            registry->register_component(shot);
            this->fire_requested = false;
        }
    }
    return true;
}

void Player::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, 255);
    this->rect.x = this->pos.x - HALF_RECT_SIZE;
    this->rect.y = this->pos.y - HALF_RECT_SIZE;
    SDL_RenderFillRect(renderer, &this->rect);
}

}
