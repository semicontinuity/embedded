// =============================================================================
// Motor driver.
//
// If the MOTOR_UP signal is set to 1, the motor rotates 'up'.
// If the MOTOR_DOWN signal is set to 1, the motor rotates 'down'.
// It is prohibited to set both MOTOR_UP and MOTOR_DOWN to 1 at the same time.
// =============================================================================

#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>
#include "cpu/avr/gpio.h"


inline static void motor__up__init(void) {
    USE_AS_OUTPUT(MOTOR_UP);
}

inline static void motor__up__on(void) {
    OUT_1(MOTOR_UP);
}

inline static void motor__up__off(void) {
    OUT_0(MOTOR_UP);
}


inline static void motor__down__init(void) {
    USE_AS_OUTPUT(MOTOR_DOWN);
}

inline static void motor__down__on(void) {
    OUT_1(MOTOR_DOWN);
}

inline static void motor__down__off(void) {
    OUT_0(MOTOR_DOWN);
}


/**
 * Initialize the motor driver.
 * The motor control pins are forcibly driven low,
 * to ensure that motor is stopped (for the case of reset or brown-out).
 */
inline static void motor__init(void) {
    motor__up__init();
    motor__up__off();

    motor__down__init();
    motor__down__off();
}


#ifndef motor__on_up
INLINE void motor__on_up(void);
#endif

inline static void motor__up(void) {
    motor__up__on();
    motor__on_up();
}

#ifndef motor__on_down
INLINE void motor__on_down(void);
#endif

inline static void motor__down(void) {
    motor__down__on();
    motor__on_down();
}

#ifndef motor__on_stop
INLINE void motor__on_stop(void);
#endif

inline static void motor__stop(void) {
    motor__up__off();
    motor__down__off();
    motor__on_stop();
}


#endif