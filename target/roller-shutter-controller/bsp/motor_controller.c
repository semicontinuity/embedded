// =============================================================================
// Motor controller service.
// =============================================================================

#include <stdint.h>
#include "motor_controller.h"
#include "motor.h"



typedef enum {
    MOTOR_CONTROLLER__STATE__OFF,
    MOTOR_CONTROLLER__STATE__DEAD_TIME,
    MOTOR_CONTROLLER__STATE__CHECK_START,
    MOTOR_CONTROLLER__STATE__RUN,
    MOTOR_CONTROLLER__STATE__OVERRUN,
    MOTOR_CONTROLLER__STATE__CHECK_REVERSE,
    MOTOR_CONTROLLER__STATE__STOP
} motor_controller__state_t;

struct motor_controller__control motor_controller__control = {
    .target_position    = MOTOR_CONTROLLER__POSITION__MIDDLE
};

struct motor_controller__status motor_controller__status = {
    .position           = MOTOR_CONTROLLER__POSITION__MIDDLE,
    .position_error     = MOTOR_CONTROLLER__POSITION__MIDDLE
};

motor_controller__state_t       motor_controller__state                 = MOTOR_CONTROLLER__STATE__OFF;
motor_controller__motor_mode_t  motor_controller__motor_mode            = MOTOR_CONTROLLER__MOTOR_MODE__STOPPED;
uint8_t                         motor_controller__timer                 = 0;
 int8_t                         motor_controller__position_delta        = 0;


/**
 * Called every motor_controller_tick to implement the motor control logic
 * and generate signals to drive the motor.
 */
INLINE void motor_controller__run(void) {
    switch (motor_controller__state) {
    case MOTOR_CONTROLLER__STATE__DEAD_TIME:
        if (--motor_controller__timer != 0) break;
    case MOTOR_CONTROLLER__STATE__CHECK_START:
        if (motor_controller__position == motor_controller__target_position) {
            motor_controller__state = MOTOR_CONTROLLER__STATE__OFF;
        }
        else {
            if (motor_controller__position > motor_controller__target_position) {
                // Need to start moving up
                motor_controller__position_delta = -1;
                motor__up();
                motor_controller__motor_mode = MOTOR_CONTROLLER__MOTOR_MODE__RUNNING_UP;
                motor_controller__motor_mode__on_change();
            }
            else {  // motor_controller__position < motor_controller__target_position
                // Need to start moving down
                motor_controller__position_delta = 1;
                motor__down();
                motor_controller__motor_mode = MOTOR_CONTROLLER__MOTOR_MODE__RUNNING_DOWN;
                motor_controller__motor_mode__on_change();
            }
            motor_controller__state = MOTOR_CONTROLLER__STATE__RUN;
        }
        break;
    case MOTOR_CONTROLLER__STATE__RUN:      
        motor_controller__position += motor_controller__position_delta;
        motor_controller__status__on_change();
        if (motor_controller__position == motor_controller__target_position) {
            if (motor_controller__position == MOTOR_CONTROLLER__POSITION__DOWN ||
                motor_controller__position == MOTOR_CONTROLLER__POSITION__UP) {
                motor_controller__state = MOTOR_CONTROLLER__STATE__OVERRUN;
                break;
    case MOTOR_CONTROLLER__STATE__OVERRUN:
                // In this state, the motor is kept on for some time
                // to make sure that roller shutter is fully open or closed.
                if (--motor_controller__position_error != 0) break;
                motor_controller__position_error = MOTOR_CONTROLLER__POSITION_ERROR;
    // end of case MOTOR_CONTROLLER__STATE__OVERRUN
            }
            // proceed to case MOTOR_CONTROLLER__STATE__STOP
        }
        else {
    case MOTOR_CONTROLLER__STATE__CHECK_REVERSE:
            if (motor_controller__position > motor_controller__target_position) {
                // Need to move up
                if (motor_controller__position_delta == -1) break;      // if no reverse needed, continue to run motor.
                // Otherwise stop the motor, wait, and later reverse the motor
            }
            else {  // motor_controller__position < motor_controller__target_position
                // Need to move down
                if (motor_controller__position_delta == 1) break;       // if no reverse needed, continue to run motor.
                // Otherwise stop the motor, wait, and later reverse the motor
            }
        }
    case MOTOR_CONTROLLER__STATE__STOP:
        motor__stop();
        motor_controller__motor_mode = MOTOR_CONTROLLER__MOTOR_MODE__STOPPED;
        motor_controller__motor_mode__on_change();

        motor_controller__timer = MOTOR_CONTROLLER__DEAD_TIME;
        motor_controller__state = MOTOR_CONTROLLER__STATE__DEAD_TIME;
        break;
    case MOTOR_CONTROLLER__STATE__OFF:
        // do nothing
        break;
    }
}


/**
 * Instructs the motor controller to move to the shutter to the specified position.
 * (Setting target_position property can trigger the motion)
 */
void motor_controller__move(const int8_t target_position) {        
    if (target_position == motor_controller__target_position) return;
    motor_controller__target_position = target_position;

    if (motor_controller__state == MOTOR_CONTROLLER__STATE__OVERRUN) {
        motor_controller__state = MOTOR_CONTROLLER__STATE__CHECK_REVERSE;
    }
    else if (motor_controller__state == MOTOR_CONTROLLER__STATE__OFF) {
        motor_controller__state = MOTOR_CONTROLLER__STATE__CHECK_START;
    }
    // MOTOR_CONTROLLER__STATE__OFF cannot happen.
    // If in MOTOR_CONTROLLER__STATE__DEAD_TIME, let it elapse.
    // If in MOTOR_CONTROLLER__STATE__CHECK_REVERSE, changing final position is ok.
    // If in MOTOR_CONTROLLER__STATE__CHECK_START, changing final position is ok.
    // If in MOTOR_CONTROLLER__STATE__RUN or MOTOR_CONTROLLER__STATE__CHECK_REVERSE, let it check for new position.
}


/**
 * Instructs the motor controller to stop the motion, if any.
 */
void motor_controller__stop(void) {
    switch (motor_controller__state) {
    case MOTOR_CONTROLLER__STATE__DEAD_TIME:
    case MOTOR_CONTROLLER__STATE__CHECK_START:
        motor_controller__target_position = motor_controller__position;
        motor_controller__state = MOTOR_CONTROLLER__STATE__OFF;
        break;
    case MOTOR_CONTROLLER__STATE__RUN:
        motor_controller__position += motor_controller__position_delta;
        motor_controller__target_position = motor_controller__position;
        // proceed further to switch to STOP state
    case MOTOR_CONTROLLER__STATE__OVERRUN:
    case MOTOR_CONTROLLER__STATE__CHECK_REVERSE:
        motor_controller__state = MOTOR_CONTROLLER__STATE__STOP;
        break;
    case MOTOR_CONTROLLER__STATE__OFF:
        // do nothing
        break;
    }
}
