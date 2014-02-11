// =============================================================================
// The driver for watched and driven buttons BUTTONS_TAP.
// Buttons pins are Wired-Anded with pool controller buttons:
// When watched:
//   High level => button depressed
//   Low level  => button pressed
// When driven:
//   Simulate button pressed => drive low (via 1K resistor)
//   Simulate button depressed => do not drive
// The buttons must connected to the same port in the continuous block.
// =============================================================================

#include "drivers/io/buttons_tap.h"
#include "cpu/avr/asm.h"


/**
 * Initialize the button tap pins.
 */
void buttons_tap__init(void) {
    // Do nothing, assume that pins are inputs on startup
    // Do nothing, assume that PORT register bits are 0 on startup
}

/**
 * Drive the buttons.
 * Every set bit (for bits 0-5) will simulate button press of the corresponding button.
 * Bits 6 and 7 must be 0.
 */
void buttons_tap__set(const uint8_t value) {
    // If a bit is 0: pin is input, button state unaffected
    // If a bit is 1: pin is output, driven low, simulating button press
    __OUT(DATA_DIR_REG(BUTTONS_TAP__PORT), value);
}

/**
 * Read the buttons state.
 * Every set bit (for bits BUTTONS_TAP__PIN .. BUTTONS_TAP__PIN+5) corresponds to press of the corresponding button.
 * Remaining bits will be undefined.
 */
uint8_t buttons_tap__get(void) {
    return ~PORT_VALUE(BUTTONS_TAP);
}
