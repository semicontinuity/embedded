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

#define MOTOR_CONTROLLER__POSITION__UP          (0)
#define MOTOR_CONTROLLER__POSITION__DOWN        (100)
#define MOTOR_CONTROLLER__POSITION__MIDDLE      (50)


#define MOTOR_CONTROLLER__STATE__OFF            (0)
#define MOTOR_CONTROLLER__STATE__PRE_DELAY      (1)


uint8_t motor_controller__state         = MOTOR_CONTROLLER__STATE__OFF;
uint8_t motor_controller__pre_delay     = 0;
uint8_t motor_controller__port_value    = 0;
uint8_t motor_controller__post_delay    = 0;


/**
 * Called at every system tick to generate proper signals to control the motor.
 */
inline void motor_controller__run(void) {
}


/**
 * Instruct the motor controller to move to the shutter all the way down.
 */
inline void motor_controller__down(void) {
}


/**
 * Instruct the motor controller to move to the shutter all the way up.
 */
inline void motor_controller__up(void) {
}
