#ifndef RECT_H
#define RECT_H

#include <SDL.h>


namespace game {
namespace data {

typedef SDL_Rect Rect;

bool colliding(Rect &r1, Rect &r2);

}}

#endif
