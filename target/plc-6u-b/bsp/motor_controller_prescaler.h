// =============================================================================
// Motor controller prescaler.
// =============================================================================

#ifndef __MOTOR_CONTROLLER_PRESCALER_H
#define __MOTOR_CONTROLLER_PRESCALER_H

#include <stdint.h>
#include <avr/eeprom.h>
#include "motor_controller.h"

extern uint8_t EEMEM ee__motor_controller__prescaler__value;

extern uint8_t motor_controller__prescaler__value;
extern uint8_t motor_controller__prescaler__time;


inline static void motor_controller__prescaler__init(void) {
    motor_controller__prescaler__value  = eeprom_read_byte(&ee__motor_controller__prescaler__value);
}


/**
 * Called every system tick to generate motor_controller_tick.
 */
inline static void motor_controller__prescaler__run(void) {
    if (--motor_controller__prescaler__time == 0) {
        motor_controller__prescaler__time = motor_controller__prescaler__value;
        motor_controller__run();
    }
}


#endif