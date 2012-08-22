// =============================================================================
// Motor controller.
// Assumes that there is a dedicated port (MOTOR__PORT) for the motor control.
// If the MOTOR_UP signal is set to 1, the motor rotates 'up'.
// If the MOTOR_DOWN signal is set to 1, the motor rotates 'down'.
// It is prohibited to set both MOTOR_UP and MOTOR_DOWN to 1 at the same time.
// 
// The motor controller has properties 'position' and 'final_position',
// that can take values from 0 to 100, inclusive.
// =============================================================================

#include <stdint.h>
#include "motor_controller.h"
#include "motor.h"


#define MOTOR_CONTROLLER__STATE__OFF            (0)
#define MOTOR_CONTROLLER__STATE__DEAD_TIME      (1)
#define MOTOR_CONTROLLER__STATE__CHECK_START    (2)
#define MOTOR_CONTROLLER__STATE__RUN            (3)
#define MOTOR_CONTROLLER__STATE__OVERRUN        (4)
#define MOTOR_CONTROLLER__STATE__CHECK_REVERSE  (5)
#define MOTOR_CONTROLLER__STATE__STOP           (6)


uint8_t motor_controller__final_position        = MOTOR_CONTROLLER__POSITION__MIDDLE;
uint8_t motor_controller__position              = MOTOR_CONTROLLER__POSITION__MIDDLE;
uint8_t motor_controller__state                 = MOTOR_CONTROLLER__STATE__OFF;
uint8_t motor_controller__timer                 = 0;
 int8_t motor_controller__position_delta        = 0;
uint8_t motor_controller__position_error        = MOTOR_CONTROLLER__POSITION__MIDDLE;


/**
 * Called every motor_controller_tick to implement the motor control logic
 * and generate signals to drive the motor.
 */
INLINE void motor_controller__run(void) {
    // MOTOR_CONTROLLER__STATE__OFF not matched, do nothing.
    switch (motor_controller__state) {
    case MOTOR_CONTROLLER__STATE__DEAD_TIME:
        if (--motor_controller__timer != 0) break;
    case MOTOR_CONTROLLER__STATE__CHECK_START:
        if (motor_controller__position == motor_controller__final_position) {
            motor_controller__state = MOTOR_CONTROLLER__STATE__OFF;
            break;
        }
        else {
            if (motor_controller__position > motor_controller__final_position) {
                // Need to start moving up
                motor_controller__position_delta = -1;
                motor__up();
            }
            else {  // motor_controller__position < motor_controller__final_position
                // Need to start moving down
                motor_controller__position_delta = 1;
                motor__down();
            }
            motor_controller__state = MOTOR_CONTROLLER__STATE__RUN;
        }
    case MOTOR_CONTROLLER__STATE__RUN:      
        motor_controller__position += motor_controller__position_delta;
        if (motor_controller__position == motor_controller__final_position) {
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
            if (motor_controller__position > motor_controller__final_position) {
                // Need to move up
                if (motor_controller__position_delta == -1) break;      // if no reverse needed, continue to run motor.
                // Otherwise stop the motor, wait, and later reverse the motor
            }
            else {  // motor_controller__position < motor_controller__final_position
                // Need to move down
                if (motor_controller__position_delta == 1) break;       // if no reverse needed, continue to run motor.
                // Otherwise stop the motor, wait, and later reverse the motor
            }
        }
    case MOTOR_CONTROLLER__STATE__STOP:
        motor__stop();
        motor_controller__timer = MOTOR_CONTROLLER__DEAD_TIME;
        motor_controller__state = MOTOR_CONTROLLER__STATE__DEAD_TIME;
        break;
    }
}


/**
 * Instructs the motor controller to move to the shutter to the specified position.
 * (Setting final_position property can trigger the motion)
 */
void motor_controller__final_position__set(const uint8_t final_position) {

    if (final_position == motor_controller__final_position) return;

    if (motor_controller__state == MOTOR_CONTROLLER__STATE__OVERRUN) {
        motor_controller__state = MOTOR_CONTROLLER__STATE__CHECK_REVERSE;
    }
    else if (motor_controller__state == MOTOR_CONTROLLER__STATE__OFF) {
        motor_controller__state = MOTOR_CONTROLLER__STATE__CHECK_START;
    }
    // If in MOTOR_CONTROLLER__STATE__DEAD_TIME, let it elapse.
    // If in MOTOR_CONTROLLER__STATE__RUN or MOTOR_CONTROLLER__STATE__CHECK_REVERSE, let it check for new position.


    motor_controller__final_position = final_position;
}
