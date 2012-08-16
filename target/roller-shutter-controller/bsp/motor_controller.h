#ifndef __RELAY_H
#define __RELAY_H

#include "cpu/avr/gpio.h"


inline void motor_controller__init(void) {
    // Output port contains 0 by default.
    USE_AS_OUTPUT(MOTOR_UP);
    USE_AS_OUTPUT(MOTOR_DOWN);
}


/**
 * Called at every system tick to generate proper signals to control the motor.
 */
inline void motor_controller__prescaler__run(void);


/**
 * Instruct the motor controller to move to the shutter all the way down.
 */
inline void motor_controller__down(void);


/**
 * Instruct the motor controller to move to the shutter all the way up.
 */
inline void motor_controller__up(void);
 

#endif