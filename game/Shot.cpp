#include "Shot.h"


namespace game {

const int32_t Shot::HALF_RECT_SIZE = Shot::RECT_SIZE / 2;
const int32_t MOV_PX_PER_MILLI = 1;

void Shot::digest_event(SDL_Event *event) {
}

bool Shot::tick(int32_t &elapsed_time, ComponentRegistry *registry) {
    this->pos.x += MOV_PX_PER_MILLI * elapsed_time;
    this->pos.y += MOV_PX_PER_MILLI * elapsed_time;
    
    bool keep_me_alive = this->pos.x > 50 && this->pos.x < 950 &&
                         this->pos.y > 50 && this->pos.y < 950;
    return keep_me_alive;
}

void Shot::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, 255);
    this->rect.x = this->pos.x - HALF_RECT_SIZE;
    this->rect.y = this->pos.y - HALF_RECT_SIZE;
    SDL_RenderFillRect(renderer, &this->rect);
}

}
