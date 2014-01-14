// =============================================================================
// The driver for 6 watched and driven buttons BUTTONS.
// Buttons pins are Wired-Anded with pool controller buttons:
// When watched:
//   High level => button depressed
//   Low level  => button pressed
// When driven:
//   Simulate button pressed => drive low (via 1K resistor)
//   Simulate button depressed => do not drive
// The buttons must connected to the same port in the continuous block.
// =============================================================================

#include "drivers/buttons.h"
#include "cpu/avr/asm.h"


/**
 * Initialize button pins.
 */
void buttons__init(void) {
    // Do nothing, assume that pins are inputs on startup
    // Do nothing, assume that PORT register bits are 0 on startup
}

/**
 * Drive the buttons.
 * Every set bit (for bits 0-5) will simulate button press of the corresponding button.
 * Bits 6 and 7 must be 0.
 */
void buttons__set(const uint8_t value) {
    // If a bit is 0: pin is input, button state unaffected
    // If a bit is 1: pin is output, driven low, simulating button press
    __OUT(DATA_DIR_REG(BUTTONS__PORT), value);
}
