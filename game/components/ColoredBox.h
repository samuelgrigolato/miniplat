#ifndef COLOREDBOX_H
#define COLOREDBOX_H


#include "PhysicalBody.h"
#include "../data/Color.h"
#include "../data/Rect.h"


namespace game {
namespace components {

using namespace data;

class ColoredBox : public PhysicalBody {
public:
    void init() override;
    //render
    Color color{0, 0, 0};
    void render(SDL_Renderer *renderer) override;
    Rect* get_bounding_box() override { return &this->rect; }
protected:
    //render
    Rect rect{0, 0, 0, 0};
private:
    //game logic
    virtual int32_t BOX_SIZE() const = 0;
};

}}

#endif
