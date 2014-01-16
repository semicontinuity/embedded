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

#ifndef __DRIVERS__POOL_CONTROLLER__BUTTONS_H
#define __DRIVERS__POOL_CONTROLLER__BUTTONS_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize button pins.
 */
void buttons__init(void);


/**
 * Drive the buttons.
 * Every set bit (for bits 0-5) will simulate button press of the corresponding button.
 * Bits 6 and 7 must be 0.
 */
void buttons__set(const uint8_t value);


#endif