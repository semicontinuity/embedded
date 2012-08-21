// =============================================================================
// Motor controller prescaler.
// =============================================================================

#ifndef __MOTOR_CONTROLLER_PRESCALER_H
#define __MOTOR_CONTROLLER_PRESCALER_H

#include <stdint.h>
#include "motor_controller.h"

extern uint8_t motor_controller__prescaler__time;


/**
 * Called every system tick to generate motor_controller_tick.
 */
inline void motor_controller__prescaler__run(void) {
    if (--motor_controller__prescaler__time == 0) {
        motor_controller__prescaler__time = MOTOR_CONTROLLER__PRESCALER;
        motor_controller__run();
    }
}


#endif