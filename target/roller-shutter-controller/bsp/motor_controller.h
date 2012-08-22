#ifndef __MOTOR_CONTROLLER_H
#define __MOTOR_CONTROLLER_H

#include "cpu/avr/gpio.h"


#define MOTOR_CONTROLLER__POSITION__UP          (0)
#define MOTOR_CONTROLLER__POSITION__DOWN        (100)
#define MOTOR_CONTROLLER__POSITION__MIDDLE      (50)


/**
 * Initialize the motor controller.
 */
inline void motor_controller__init(void) {
    // Output port contains 0 by default.
    USE_AS_OUTPUT(MOTOR_UP);
    USE_AS_OUTPUT(MOTOR_DOWN);
}

/**
 * Called every motor_controller_tick to implement the motor control logic
 * and generate signals to drive the motor.
 */
INLINE void motor_controller__run(void);


/**
 * Instructs the motor controller to move to the shutter to the specified position.
 * (Setting final_position property can trigger the motion)
 */
void motor_controller__final_position__set(const uint8_t position);
 

/**
 * Instructs the motor controller to move to the shutter all the way down.
 */
inline void motor_controller__down(void) {
    motor_controller__final_position__set(MOTOR_CONTROLLER__POSITION__DOWN);
}


/**
 * Instructs the motor controller to move to the shutter all the way up.
 */
inline void motor_controller__up(void) {
    motor_controller__final_position__set(MOTOR_CONTROLLER__POSITION__UP);
}


#endif