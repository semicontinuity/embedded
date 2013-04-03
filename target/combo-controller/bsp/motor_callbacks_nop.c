// =============================================================================
// No-op motor callbacks.
// =============================================================================

#include "motor.h"

/**
 * Callback function, called by motor__up() when the motor is instructed to rotate "up".
 */
INLINE void motor__on_up(void) {
}


/**
 * Callback function, called by motor__down() when the motor is instructed to rotate "down".
 */
INLINE void motor__on_down(void) {
}


/**
 * Callback function, called by motor__stop() when the motor is instructed to stop.
 */
INLINE void motor__on_stop(void) {
}
