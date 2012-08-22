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


inline static void motor__up__on(void) {
    OUT_1(MOTOR_UP);
}

inline static void motor__up__off(void) {
    OUT_0(MOTOR_UP);
}

inline static void motor__down__on(void) {
    OUT_1(MOTOR_DOWN);
}

inline static void motor__down__off(void) {
    OUT_0(MOTOR_DOWN);
}


INLINE void motor__on_up(void);

inline static void motor__up(void) {
    motor__mode = MOTOR__MODE__RUNNING_UP;
    motor__up__on();
    motor__on_up();
}


INLINE void motor__on_down(void);

inline static void motor__down(void) {
    motor__mode = MOTOR__MODE__RUNNING_DOWN;
    motor__down__on();
    motor__on_down();
}


INLINE void motor__on_stop(void);

inline static void motor__stop(void) {
    motor__mode = MOTOR__MODE__STOPPED;
    motor__up__off();
    motor__down__off();
    motor__on_stop();
}


#endif