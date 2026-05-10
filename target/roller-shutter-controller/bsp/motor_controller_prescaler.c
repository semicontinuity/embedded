// =============================================================================
// Motor controller prescaler.
// =============================================================================

#include <stdint.h>
#include "motor_controller_prescaler.h"

uint8_t EEMEM ee__motor_controller__prescaler__value  = MOTOR_CONTROLLER__PRESCALER;

uint8_t motor_controller__prescaler__value;
uint8_t motor_controller__prescaler__time;
