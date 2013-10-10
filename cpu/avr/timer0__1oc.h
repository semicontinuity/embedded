#ifndef __CPU_AVR_TIMER0_1OC_H
#define __CPU_AVR_TIMER0_1OC_H

#include <avr/io.h>

#define TIMER0_CONF_OC2_DISCONNECTED                    (0)
#define TIMER0_CONF_OC2_TOGGLE                          (              _BV(COM00))
#define TIMER0_CONF_OC2_CLEAR                           (_BV(COM01)              )
#define TIMER0_CONF_OC2_SET                             (_BV(COM01) | _BV(COM00))

#define TIMER0_CONF_FAST_PWM_OC2_DISCONNECTED           (0)
#define TIMER0_CONF_FAST_PWM_OC2_RESERVED               (              _BV(COM0B0))
#define TIMER0_CONF_FAST_PWM_OC2_NON_INVERTING          (_BV(COM0B1)              )
#define TIMER0_CONF_FAST_PWM_OC2_INVERTING              (_BV(COM0B1) | _BV(COM0B0))

#define TIMER0_CONF_PHASE_CORRECT_PWM_OC2_DISCONNECTED  (0)
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC2_RESERVED      (              _BV(COM0B0))
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC2_NON_INVERTING (_BV(COM0B1)              )
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC2_INVERTING     (_BV(COM0B1) | _BV(COM0B0))

#define TIMER0_CONF_WGM_NORMAL                          (0)
#define TIMER0_CONF_WGM_PHASE_CORRECT_PWM               (             _BV(WGM00))
#define TIMER0_CONF_WGM_CTC                             (_BV(WGM01)             )
#define TIMER0_CONF_WGM_FAST_PWM                        (_BV(WGM01) | _BV(WGM00))

#define TIMER0_CONF_STOPPED		                (0)
#define TIMER0_CONF_NO_PRESCALER	                (                        _BV(CS00))
#define TIMER0_CONF_PRESCALER_8                         (            _BV(CS01)            )
#define TIMER0_CONF_PRESCALER_64                        (            _BV(CS01) | _BV(CS00))
#define TIMER0_CONF_PRESCALER_256                       (_BV(CS02)                        )
#define TIMER0_CONF_PRESCALER_1024                      (_BV(CS02)             | _BV(CS00))
#define TIMER0_CONF_EXT_CLK_FALLING                     (_BV(CS02) | _BV(CS01)            )
#define TIMER0_CONF_EXT_CLK_RISING                      (_BV(CS02) | _BV(CS01) | _BV(CS00))

#define TIMER0_CONF_TOP(value)                          ((value) << 8)
#define TIMER0_CONF_OCR(value)                          ((value) << 8)

#define TIMER0_CONF_DEFAULT                             (0)


inline void timer0__switch_conf(uint16_t old_conf, uint16_t new_conf) {
    uint8_t old_tccr = old_conf & 0xFF;
    uint8_t new_tccr = new_conf & 0xFF;
    if (old_tccr != new_tccr) TCCR0 = new_tccr;

    uint8_t old_ocr = (old_conf >> 8) & 0xFF;
    uint8_t new_ocr = (new_conf >> 8) & 0xFF;
    if (old_ocr != new_ocr) OCR0 = new_ocr;
}


inline void timer0__compare__interrupt__enable(void) {
    TIMSK |= _BV(OCIE0);
}

inline void timer0__compare__interrupt__disable(void) {
    TIMSK &= ~_BV(OCIE0);
}


inline void timer0__overflow__interrupt__enable(void) {
    TIMSK |= _BV(TOIE0);
}

inline void timer0__overflow__interrupt__disable(void) {
    TIMSK &= ~_BV(TOIE0);
}


inline void timer0__ctc__interrupt__enable(void) {
    timer0__compare__interrupt__enable();
}

inline void timer0__ctc__interrupt__disable(void) {
    timer0__compare__interrupt__disable();
}


#endif