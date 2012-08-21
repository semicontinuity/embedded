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
#include "cpu/avr/gpio.h"

#define MOTOR_CONTROLLER__REVERSE_DELAY         (2)
#define MOTOR_CONTROLLER__ERROR                 (2)

#define MOTOR_CONTROLLER__PORT_VALUE_UP         (SIGNAL_MASK(MOTOR_UP))
#define MOTOR_CONTROLLER__PORT_VALUE_DOWN       (SIGNAL_MASK(MOTOR_DOWN))
#define MOTOR_CONTROLLER__PORT_VALUE_OFF        (0)

#define MOTOR_CONTROLLER__STATE__OFF            (0)
#define MOTOR_CONTROLLER__STATE__REVERSE_DELAY  (1)
#define MOTOR_CONTROLLER__STATE__MOTOR_START    (2)
#define MOTOR_CONTROLLER__STATE__MOTOR_RUN      (3)
#define MOTOR_CONTROLLER__STATE__END_DELAY      (4)


uint8_t motor_controller__final_position        = MOTOR_CONTROLLER__POSITION__MIDDLE;
uint8_t motor_controller__position              = MOTOR_CONTROLLER__POSITION__MIDDLE;
uint8_t motor_controller__state                 = MOTOR_CONTROLLER__STATE__OFF;
uint8_t motor_controller__port_value            = 0;
uint8_t motor_controller__timer                 = 0;
 int8_t motor_controller__position_delta        = 0;
uint8_t motor_controller__error                 = MOTOR_CONTROLLER__POSITION__MIDDLE;


/**
 * Called every motor_controller_tick to implement the motor control logic
 * and generate signals to drive the motor.
 */
inline void motor_controller__run(void) {
    switch (motor_controller__state) {
    case MOTOR_CONTROLLER__STATE__REVERSE_DELAY:
        if (--motor_controller__timer != 0) {
            break;
        }
        // if motor_controller__timer has reached 0, fall thru to start motor.
    case MOTOR_CONTROLLER__STATE__MOTOR_START:
        if (motor_controller__position_delta != 0) {
            OUT(MOTOR, motor_controller__port_value);
            motor_controller__state = MOTOR_CONTROLLER__STATE__MOTOR_RUN;
        }
        else {
            // Abort motor start, already at the proper position.
            motor_controller__state = MOTOR_CONTROLLER__STATE__OFF;
        }
        break;
    case MOTOR_CONTROLLER__STATE__MOTOR_RUN:      
        motor_controller__position += motor_controller__position_delta;
        if (motor_controller__position == motor_controller__final_position) {
            OUT(MOTOR, MOTOR_CONTROLLER__PORT_VALUE_OFF);
            if (motor_controller__position == MOTOR_CONTROLLER__POSITION__DOWN ||
                motor_controller__position == MOTOR_CONTROLLER__POSITION__UP) {
                motor_controller__state = MOTOR_CONTROLLER__STATE__END_DELAY;
            }
            else {
                motor_controller__state = MOTOR_CONTROLLER__STATE__REVERSE_DELAY;
            }
        }
        break;
    case MOTOR_CONTROLLER__STATE__END_DELAY:
        if (--motor_controller__error == 0) {
            motor_controller__error = MOTOR_CONTROLLER__ERROR;
            motor_controller__state = MOTOR_CONTROLLER__STATE__OFF;
        }
        break;
    }
    // MOTOR_CONTROLLER__STATE__OFF not matched, do nothing.
}


/**
 * Instructs the motor controller to move to the shutter to the specified position.
 * (Setting final_position property can trigger the motion)
 */
void motor_controller__final_position__set(const uint8_t final_position) {
    int8_t new_delta;

    // Calculate new_delta and new motor_controller__port_value.
    if (motor_controller__position == final_position) {
        // Moving and just reached final position, or stopped and setting final_position to current position
        new_delta = 0; // if motor is running, it will cause it to stop
    }
    else {
        if (motor_controller__position > final_position) {
            // Parameters to make the motor move the shutter up.
            new_delta = -1;
            motor_controller__port_value = MOTOR_CONTROLLER__PORT_VALUE_UP;
        }
        else {  // motor_controller__position < final_position
            // Parameters to make the motor move the shutter down.
            new_delta = 1;
            motor_controller__port_value = MOTOR_CONTROLLER__PORT_VALUE_DOWN;
        }
    }

    motor_controller__final_position = final_position;
    // If moving to the different position, but in the same direction,
    // or if no change in final position (that could have been already reached).
    if (new_delta == motor_controller__position_delta) return;
    motor_controller__position_delta = new_delta;

    
    // Program new parameters
    switch (motor_controller__state) {
    case MOTOR_CONTROLLER__STATE__MOTOR_RUN:      
        // Stop the motor
        OUT(MOTOR, MOTOR_CONTROLLER__PORT_VALUE_OFF);
        motor_controller__timer = MOTOR_CONTROLLER__REVERSE_DELAY;
        motor_controller__state = MOTOR_CONTROLLER__STATE__REVERSE_DELAY;
    case MOTOR_CONTROLLER__STATE__REVERSE_DELAY:
        // The direction in which the motor was moving
        // could have been overwritten with the opposite one and again with the same one.
        // For simplification, let the delay elapse anyway.
        break;
    case MOTOR_CONTROLLER__STATE__END_DELAY:
        if (motor_controller__position_delta != 0) {
            motor_controller__state = MOTOR_CONTROLLER__STATE__MOTOR_START;
        }
        break;
    }
}
