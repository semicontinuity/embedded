#ifndef __MOTOR_CONTROLLER_H
#define __MOTOR_CONTROLLER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"


// bit 0 is 1 if UP motor is on, bit 1 is 1 if DOWN motor is on
#define MOTOR__MODE__STOPPED            (0)
#define MOTOR__MODE__RUNNING_UP         (1)
#define MOTOR__MODE__RUNNING_DOWN       (2)

extern uint8_t motor__mode;

void motor__mode__on_change(void);



#define MOTOR_CONTROLLER__POSITION__STOP        (-1)
#define MOTOR_CONTROLLER__POSITION__UP          (0)
#define MOTOR_CONTROLLER__POSITION__DOWN        (100)
#define MOTOR_CONTROLLER__POSITION__MIDDLE      (50)


struct motor_controller__control {
    int8_t target_position;
};
extern struct motor_controller__control motor_controller__control;
#define motor_controller__target_position       motor_controller__control.target_position


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
void motor_controller__move(const int8_t position);
 

/**
 * Instructs the motor controller to stop the motion, if any.
 */
void motor_controller__stop(void);


/**
 * Instructs the motor controller to move to the shutter all the way down.
 */
inline void motor_controller__move_down(void) {
    motor_controller__move(MOTOR_CONTROLLER__POSITION__DOWN);
}


/**
 * Instructs the motor controller to move to the shutter all the way up.
 */
inline void motor_controller__move_up(void) {
    motor_controller__move(MOTOR_CONTROLLER__POSITION__UP);
}


/**
 * Sets the control structure.
 * (Can trigger the motion)
 */
inline void motor_controller__control__set(struct motor_controller__control* control) {
    int8_t target_position = control->target_position;
    if (target_position == MOTOR_CONTROLLER__POSITION__STOP) {
        motor_controller__stop();
    }
    else if (target_position >= MOTOR_CONTROLLER__POSITION__UP && target_position <= MOTOR_CONTROLLER__POSITION__DOWN) {
        motor_controller__move(control->target_position);
    }
}


#endif