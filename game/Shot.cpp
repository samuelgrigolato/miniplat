#include "Shot.h"


namespace game {

const int32_t Shot::HALF_RECT_SIZE = Shot::RECT_SIZE / 2;
const int32_t MOV_PX_PER_MILLI = 1;

void Shot::digest_event(SDL_Event *event) {
}

void Shot::tick(int32_t &elapsed_time, ComponentRegistry *registry) {
    this->pos.x += MOV_PX_PER_MILLI * elapsed_time;
    this->pos.y += MOV_PX_PER_MILLI * elapsed_time;
}

void Shot::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, 255);
    this->rect.x = this->pos.x - HALF_RECT_SIZE;
    this->rect.y = this->pos.y - HALF_RECT_SIZE;
    SDL_RenderFillRect(renderer, &this->rect);
}

}
