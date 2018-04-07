#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>


namespace game {
namespace data {

struct KeyMap {
    int32_t up;
    int32_t left;
    int32_t down;
    int32_t right;
    int32_t fire;
};

}}

#endif
