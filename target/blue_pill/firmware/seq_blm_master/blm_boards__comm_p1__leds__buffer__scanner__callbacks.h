#include <stdint.h>

/**
 * Callback function, invoked by the scanner, representing I2C command to be sent to a BLM board to update LEDs
 */
void blm_boards__comm_p1__leds__buffer__scanner__update_one(
    uint8_t matrix,
    uint8_t led,
    uint8_t r,
    uint8_t g,
    uint8_t b);
