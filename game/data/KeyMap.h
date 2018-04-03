#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>


namespace game {
namespace data {

struct KeyMap {
    int8_t up;
    int8_t left;
    int8_t down;
    int8_t right;
    int8_t fire;
};

}}

#endif
