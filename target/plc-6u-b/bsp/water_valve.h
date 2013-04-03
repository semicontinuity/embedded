// =============================================================================
// Water valve driver.
//
// If the MOTOR_UP signal is set to 1, the motor rotates 'up'.
// If the MOTOR_DOWN signal is set to 1, the motor rotates 'down'.
// It is prohibited to set both MOTOR_UP and MOTOR_DOWN to 1 at the same time.
// =============================================================================

#ifndef __WATER_VALVE_H
#define __WATER_VALVE_H

#include <stdint.h>
#include "cpu/avr/gpio.h"



inline static void water_valve__on(void) {
    OUT_1(WATER_VALVE);
}

inline static void water_valve__off(void) {
    OUT_0(WATER_VALVE);
}

/**
 * Initialize the water valve driver.
 * The valve control pin is forcibly driven low,
 * to ensure that valve is open (for the case of reset or brown-out).
 */
inline static void water_valve__init(void) {
    USE_AS_OUTPUT(WATER_VALVE);
    water_valve__off();
}

#endif