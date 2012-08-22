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


inline void motor__up__on(void) {
    OUT_1(MOTOR_UP);
}

inline void motor__up__off(void) {
    OUT_0(MOTOR_UP);
}

inline void motor__down__on(void) {
    OUT_1(MOTOR_DOWN);
}

inline void motor__down__off(void) {
    OUT_0(MOTOR_DOWN);
}


inline void motor__up(void) {
    motor__mode = MOTOR__MODE__RUNNING_UP;
    motor__up__on();
}

inline void motor__down(void) {
    motor__mode = MOTOR__MODE__RUNNING_DOWN;
    motor__down__on();
}

inline void motor__stop(void) {
    motor__mode = MOTOR__MODE__STOPPED;
    motor__up__off();
    motor__down__off();
}


#endif