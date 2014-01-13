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

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize button pins.
 */
inline void buttons__init(void) {
    // Do nothing, assume that pins are inputs on startup
}


#endif