#ifndef __CPU_AVR_TIMER2_1OC_H
#define __CPU_AVR_TIMER2_1OC_H

#include <avr/io.h>
#include <stdint.h>

#define TIMER2_CONF_STOPPED		                (TIMER2_MODE_STOPPED)
#define TIMER2_CONF_NO_PRESCALER	                (TIMER2_MODE_RUN_NO_PRESCALER)
#define TIMER2_CONF_PRESCALER_8                         (TIMER2_MODE_RUN_PRESCALER_8)
#define TIMER2_CONF_PRESCALER_32                        (TIMER2_MODE_RUN_PRESCALER_32)
#define TIMER2_CONF_PRESCALER_64                        (TIMER2_MODE_RUN_PRESCALER_64)
#define TIMER2_CONF_PRESCALER_128                       (TIMER2_MODE_RUN_PRESCALER_128)
#define TIMER2_CONF_PRESCALER_256                       (TIMER2_MODE_RUN_PRESCALER_256)
#define TIMER2_CONF_PRESCALER_1024                      (TIMER2_MODE_RUN_PRESCALER_1024)

#define TIMER2_CONF_OC2_DISCONNECTED                    (0)
#define TIMER2_CONF_OC2_TOGGLE                          (              _BV(COM20))
#define TIMER2_CONF_OC2_CLEAR                           (_BV(COM21)              )
#define TIMER2_CONF_OC2_SET                             (_BV(COM21) | _BV(COM20))

#define TIMER2_CONF_FAST_PWM_OC2_DISCONNECTED           (0)
#define TIMER2_CONF_FAST_PWM_OC2_RESERVED               (              _BV(COM2B0))
#define TIMER2_CONF_FAST_PWM_OC2_NON_INVERTING          (_BV(COM2B1)              )
#define TIMER2_CONF_FAST_PWM_OC2_INVERTING              (_BV(COM2B1) | _BV(COM2B0))

#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2_DISCONNECTED  (0)
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2_RESERVED      (              _BV(COM2B0))
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2_NON_INVERTING (_BV(COM2B1)              )
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2_INVERTING     (_BV(COM2B1) | _BV(COM2B0))

#define TIMER2_CONF_WGM_NORMAL                          (0)
#define TIMER2_CONF_WGM_PHASE_CORRECT_PWM               (             _BV(WGM20))
#define TIMER2_CONF_WGM_CTC                             (_BV(WGM21)             )
#define TIMER2_CONF_WGM_FAST_PWM                        (_BV(WGM21) | _BV(WGM20))


#define TIMER2_CONF_TOP(value)                          ((value) << 8)
#define TIMER2_CONF_OCR(value)                          ((value) << 8)

#define TIMER2_CONF_DEFAULT                             (0)


inline static void timer2__switch_conf(uint16_t old_conf, uint16_t new_conf) {
    uint8_t old_tccr = old_conf & 0xFF;
    uint8_t new_tccr = new_conf & 0xFF;
    if (old_tccr != new_tccr) TCCR2 = new_tccr;

    uint8_t old_ocr = (old_conf >> 8) & 0xFF;
    uint8_t new_ocr = (new_conf >> 8) & 0xFF;
    if (old_ocr != new_ocr) OCR2 = new_ocr;
}


inline static void timer2__compare_a__value__set(const uint8_t value) {
    OCR2 = value;
}

inline static uint16_t timer2__compare_a__value__get(void) {
    return OCR2;
}



inline static void timer2__overflow_interrupt__enable(void) {
    TIMSK |= _BV(TOIE2);
}

inline static void timer2__overflow_interrupt__disable(void) {
    TIMSK &= ~_BV(TOIE2);
}


#endif