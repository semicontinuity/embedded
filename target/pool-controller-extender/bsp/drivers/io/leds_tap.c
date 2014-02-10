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
    uint8_t portValue = PORT_VALUE(LEDS_TAP);

    return ~__builtin_avr_insert_bits(
        avr_insert_bits_map(
            0xF,
            0xF,
            LEDS_TAP__PIN + 5,
            LEDS_TAP__PIN + 4,
            LEDS_TAP__PIN + 3,
            LEDS_TAP__PIN + 2,
            LEDS_TAP__PIN + 1,
            LEDS_TAP__PIN + 0),
        portValue,
        0
    );
}
