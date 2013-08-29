// =============================================================================
// Timer 0 driver for parts with 2 Output Compare modules
// and the following configuration registers:
//
// TCCR0
//
// The 32-bit value, created by concatenation of the values of these registers,
// is referred to as "configuration value" of the timer.
// To get the particular configuration value,
// combine the appropriate with TIMER0_CONF_* constants with logical OR.
//
// Timer configurations can be switched with timer0__switch_conf().
// It produces optimal code, if configuration values are compile-time constants.
// =============================================================================
#ifndef __CPU_AVR_TIMER0_0OC_H
#define __CPU_AVR_TIMER0_0OC_H

#include <avr/io.h>

#define TIMER0_CONF_STOPPED		                (0)
#define TIMER0_CONF_NO_PRESCALER	                (                        _BV(CS00))
#define TIMER0_CONF_PRESCALER_8                         (            _BV(CS01)            )
#define TIMER0_CONF_PRESCALER_64                        (            _BV(CS01) | _BV(CS00))
#define TIMER0_CONF_PRESCALER_256                       (_BV(CS02)                        )
#define TIMER0_CONF_PRESCALER_1024                      (_BV(CS02)             | _BV(CS00))
#define TIMER0_CONF_EXT_CLK_FALLING                     (_BV(CS02) | _BV(CS01)            )
#define TIMER0_CONF_EXT_CLK_RISING                      (_BV(CS02) | _BV(CS01) | _BV(CS00))

#define TIMER0_CONF_DEFAULT                             (0)


inline void timer0__switch_conf(const uint16_t old_conf, const uint16_t new_conf) {
    const uint8_t old_tccr = old_conf & 0xFF;
    const uint8_t new_tccr = new_conf & 0xFF;
    if (old_tccr != new_tccr) TCCR0 = new_tccr;
}


inline void timer0__overflow__interrupt__enable(void) {
    TIMSK |= _BV(TOIE0);
}

inline void timer0__overflow__interrupt__disable(void) {
    TIMSK &= ~_BV(TOIE0);
}


#endif