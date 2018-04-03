#include <memory>
#include "ColoredBox.h"


namespace game {
namespace components {

void ColoredBox::init() {
    this->rect.w = this->BOX_SIZE();
    this->rect.h = this->BOX_SIZE();
}

void ColoredBox::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, 255);
    this->rect.x = this->pos.x - BOX_SIZE()/2;
    this->rect.y = this->pos.y - BOX_SIZE()/2;
    SDL_RenderFillRect(renderer, &this->rect);
}

}}
