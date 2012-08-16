// =============================================================================
// Motor controller.
// Assumes that there is a dedicated port (MOTOR__PORT) for the motor control.
// If the MOTOR_UP is set to logical 1, the motor rotates 'up'.
// If the MOTOR_DOWN is set to logical 1, the motor rotates 'down'.
// It is prohibited to set both MOTOR_UP and MOTOR_DOWN to 1 at the same time.
// 
// The motor controller has a property 'position',
// that can have values from 0 to 100, inclusive.
// =============================================================================

#include <stdint.h>
#include "motor_controller.h"
#include "cpu/avr/gpio.h"

#define MOTOR_CONTROLLER__TICK_PERIOD           (10)
#define MOTOR_CONTROLLER__REVERSE_DELAY         (2)
#define MOTOR_CONTROLLER__ERROR                 (2)

#define MOTOR_CONTROLLER__PORT_VALUE_UP         (SIGNAL_MASK(MOTOR_UP))
#define MOTOR_CONTROLLER__PORT_VALUE_DOWN       (SIGNAL_MASK(MOTOR_DOWN))
#define MOTOR_CONTROLLER__PORT_VALUE_OFF        (0)

#define MOTOR_CONTROLLER__POSITION__UP          (0)
#define MOTOR_CONTROLLER__POSITION__DOWN        (100)
#define MOTOR_CONTROLLER__POSITION__MIDDLE      (50)


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
 * Called every motor_controller_tick to generate proper signals to control the motor.
 */
inline void motor_controller__on_tick(void) {
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
 * Called every system tick to generate motor_controller_tick.
 */
inline void motor_controller__run(void) {
    static int8_t t;
    if (--t == 0) {
        t = MOTOR_CONTROLLER__TICK_PERIOD;
        motor_controller__on_tick();
    }
}


inline void motor_controller__position__set(const uint8_t position) {

    // Need to move in other direction?
    int8_t new_delta;
    if (position == motor_controller__position) {
        new_delta = 0;
    }
    else {
        if (motor_controller__position > position) {
            new_delta = -1;
            motor_controller__port_value = MOTOR_CONTROLLER__PORT_VALUE_UP;
        }
        else {
            new_delta = 1;
            motor_controller__port_value = MOTOR_CONTROLLER__PORT_VALUE_DOWN;
        }
    }

    motor_controller__final_position = position;
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


/**
 * Instruct the motor controller to move to the shutter all the way down.
 */
inline void motor_controller__down(void) {
    motor_controller__position__set(MOTOR_CONTROLLER__POSITION__DOWN);
}


/**
 * Instruct the motor controller to move to the shutter all the way up.
 */
inline void motor_controller__up(void) {
    motor_controller__position__set(MOTOR_CONTROLLER__POSITION__UP);
}
