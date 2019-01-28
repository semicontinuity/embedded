// =============================================================================
// Seconds timer.
// Divides the output of the system timer to get 1 Hz frequency.
//
// Inject symbols:
// SYSTEM_TIMER__FREQUENCY
//
// Call seconds_timer__run() from system_timer__out__run() to use the timer.
// =============================================================================

#include <stdint.h>
#include "seconds_timer.h"

uint8_t seconds_timer__value = SYSTEM_TIMER__FREQUENCY;
