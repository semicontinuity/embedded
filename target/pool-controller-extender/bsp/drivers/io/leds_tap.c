// =============================================================================
// The driver for LEDs tap.
// =============================================================================

#include "drivers/io/leds_tap.h"


/**
 * Initialize button pins.
 */
void leds_tap__init(void) {
    // Do nothing, assume that pins are inputs on startup
}

/**
 * Read the LEDs state.
 * Every set bit (for bits 0-5) corresponds to press of the corresponding button.
 * Bits 6 and 7 will be undefined.
 */
uint8_t leds_tap__get(void) {
    return PORT_VALUE(LEDS_TAP);
}
