#include "Screen.h"
#include "Shot.h"


const int32_t MOV_PX_PER_MILLI = 2;


namespace game {

void Shot::digest_event(SDL_Event *event) {
}

bool Shot::tick(int32_t &elapsed_time, ComponentRegistry *registry) {
    this->pos.x += this->vel.x * MOV_PX_PER_MILLI * elapsed_time;
    this->pos.y += this->vel.y * MOV_PX_PER_MILLI * elapsed_time;
    
    bool keep_me_alive = this->pos.x > 0 && this->pos.x < SCREEN_WINDOW_WIDTH - RECT_SIZE &&
                         this->pos.y > 0 && this->pos.y < SCREEN_WINDOW_HEIGHT - RECT_SIZE;
    return keep_me_alive;
}

void Shot::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, 255);
    this->rect.x = this->pos.x - RECT_SIZE/2;
    this->rect.y = this->pos.y - RECT_SIZE/2;
    SDL_RenderFillRect(renderer, &this->rect);
}

}
