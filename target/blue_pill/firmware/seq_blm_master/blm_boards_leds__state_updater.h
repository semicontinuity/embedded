// Updates LED state data structures on LED update commands.
// -----------------------------------------------------------------------------

#include <stdint.h>
#include "blm_boards_leds.h"
#include "blm_boards_leds__state.h"


void blm_boards_leds__init() {
    for (int i = 0; i < sizeof(blm_boards_leds__state__current); i++) {
        blm_boards_leds__state__current[i] = 0U;
    }
    for (int i = 0; i < sizeof(blm_boards_leds__state__requested); i++) {
        blm_boards_leds__state__requested[i] = 0U;
    }
    blm_boards_leds__state__dirty = 0U;
}


void blm_boards_leds__update_one(
        uint8_t matrix_x,
        uint8_t matrix_y,
        uint8_t local_x,
        uint8_t local_y,
        uint8_t r,
        uint8_t g,
        uint8_t b)
{
    uint8_t matrix = (matrix_y << 2U) + matrix_x;
    uint8_t led = (local_y << 2U) + local_x;
    uint32_t requested = blm_boards_leds__state__requested[matrix];
    if (g) { requested |= (1U << led); } else { requested &= ~(1U << led);}
    if (r) { requested |= (1U << (led + 16U)); } else { requested &= ~(1U << (led + 16U));}
    blm_boards_leds__state__requested[matrix] = requested;
    blm_boards_leds__state__dirty |= (1U << matrix);
}
