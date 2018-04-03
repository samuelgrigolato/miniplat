#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>


namespace game {
namespace data {

/**
 * This is a logical measure (as opposed to physical,
 * i.e representing device pixels), so it can be safely
 * used to derive game logic distances.
 */
const int32_t ARENA_WIDTH = 1366;

/**
 * This is a logical measure (as opposed to physical,
 * i.e representing device pixels), so it can be safely
 * used to derive game logic distances.
 */
const int32_t ARENA_HEIGHT = 768;

}}

#endif
