#ifndef COLOREDBOX_H
#define COLOREDBOX_H


#include <SDL.h>
#include "PhysicalBody.h"
#include "../data/Color.h"


namespace game {
namespace components {

using namespace data;

class ColoredBox : public PhysicalBody {
public:
    void init() override;
    //render
    Color color{0, 0, 0};
    void render(SDL_Renderer *renderer) override;
protected:
    //render
    SDL_Rect rect{0, 0, 0, 0};
private:
    //game logic
    virtual int32_t BOX_SIZE() const = 0;
};

}}

#endif
