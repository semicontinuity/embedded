#ifndef __MOTOR_CONTROLLER_H
#define __MOTOR_CONTROLLER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"


#define MOTOR_CONTROLLER__POSITION__UP          (0)
#define MOTOR_CONTROLLER__POSITION__DOWN        (100)
#define MOTOR_CONTROLLER__POSITION__MIDDLE      (50)


struct motor_controller__control {
    int8_t final_position;
};
extern struct motor_controller__control motor_controller__control;
#define motor_controller__final_position        motor_controller__control.final_position


struct motor_controller__status {
    int8_t position;
    int8_t position_error;
};
extern struct motor_controller__status motor_controller__status;
#define motor_controller__position              motor_controller__status.position
#define motor_controller__position_error        motor_controller__status.position_error


/**
 * Called by motor_controller__run() when motor_controller__status.position has been changed.
 */
INLINE void motor_controller__status__on_change(void);


/**
 * Called every motor_controller_tick to implement the motor control logic
 * and generate signals to drive the motor.
 */
INLINE void motor_controller__run(void);


/**
 * Instructs the motor controller to move to the shutter to the specified position.
 * (Can trigger the motion)
 */
void motor_controller__final_position__set(const uint8_t position);
 

/**
 * Instructs the motor controller to stop the motion, if any.
 */
void motor_controller__stop(void);


/**
 * Sets the control structure.
 * (Can trigger the motion)
 */
inline void motor_controller__control__set(struct motor_controller__control* control) {
    motor_controller__final_position__set(control->final_position);
}


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