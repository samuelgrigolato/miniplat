#ifndef ACTIOn_H
#define ACTIOn_H

#include <memory>
#include <stdint.h>


namespace game {
namespace data {

enum ActionType {

    // params: single char representing the direction, i.e.:
    // U: up, D: down, R: right, L: left
    start_moving,
    stop_moving,

    // no params
    start_firing,
    stop_firing

};

struct Action {
    uint8_t player;
    ActionType type;
    const char* params;
};

}}

#endif
