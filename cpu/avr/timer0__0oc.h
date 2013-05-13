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


inline static void timer0__switch_conf(const uint16_t old_conf, const uint16_t new_conf) {
    const uint8_t old_tccr = old_conf & 0xFF;
    const uint8_t new_tccr = new_conf & 0xFF;
    if (old_tccr != new_tccr) TCCR0 = new_tccr;
}


inline static void timer0__overflow_interrupt_enable(void) {
    TIMSK |= _BV(TOIE0);
}

inline static void timer0__overflow_interrupt_disable(void) {
    TIMSK &= ~_BV(TOIE0);
}


#define timer0__start(mode) do {\
    TCCR0 = mode;	/* start timer in the user-defined mode  */\
} while(0)

#define timer0__stop() do {\
    TCCR0 = TIMER0_MODE_STOPPED; /* stop timer 0 */\
} while(0)


#endif