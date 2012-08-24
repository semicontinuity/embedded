// =============================================================================
// Motor driver.
// =============================================================================

#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>
#include "cpu/avr/gpio.h"


// bit 0 is 1 if UP motor is on, bit 1 is 1 if DOWN motor is on
#define MOTOR__MODE__STOPPED            (0)
#define MOTOR__MODE__RUNNING_UP         (1)
#define MOTOR__MODE__RUNNING_DOWN       (2)

extern uint8_t motor__mode;

void motor__mode__on_change(void);


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



INLINE void motor__on_up(void);

inline static void motor__up(void) {
    motor__up__on();
    motor__on_up();

    motor__mode = MOTOR__MODE__RUNNING_UP;
    motor__mode__on_change();
}


INLINE void motor__on_down(void);

inline static void motor__down(void) {
    motor__down__on();
    motor__on_down();
    
    motor__mode = MOTOR__MODE__RUNNING_DOWN;
    motor__mode__on_change();
}


INLINE void motor__on_stop(void);

inline static void motor__stop(void) {
    motor__up__off();
    motor__down__off();
    motor__on_stop();

    motor__mode = MOTOR__MODE__STOPPED;
    motor__mode__on_change();
}


#endif