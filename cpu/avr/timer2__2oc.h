// =============================================================================
// Driver for Timer 2 for parts where Time 2 has 2 Output Compare modules,
// and the following configuration registers:
//
// TCCR2A
// TCCR2B
// OCR2A
// OCR2B
//
// The 32-bit value, created by concatenation of the values of these registers,
// is referred to as "configuration value" of the timer.
// To get the particular configuration value,
// combine the appropriate with TIMER2_CONF_* constants with logical OR.
//
// Timer configurations can be switched with timer2__switch_conf().
// It produces optimal code, if configuration values are compile-time constants.
// =============================================================================

#ifndef __CPU_AVR_TIMER2_2OC_H
#define __CPU_AVR_TIMER2_2OC_H

#include <avr/io.h>
#include <stdint.h>

#define TIMER2_CONF_STOPPED		                (TIMER2_MODE_STOPPED)
#define TIMER2_CONF_RUN_NO_PRESCALER	                (TIMER2_MODE_RUN_NO_PRESCALER)
#define TIMER2_CONF_RUN_PRESCALER_8	                (TIMER2_MODE_RUN_PRESCALER_8)
#define TIMER2_CONF_RUN_PRESCALER_32	                (TIMER2_MODE_RUN_PRESCALER_32)
#define TIMER2_CONF_RUN_PRESCALER_64	                (TIMER2_MODE_RUN_PRESCALER_64)
#define TIMER2_CONF_RUN_PRESCALER_128	                (TIMER2_MODE_RUN_PRESCALER_128)
#define TIMER2_CONF_RUN_PRESCALER_256	                (TIMER2_MODE_RUN_PRESCALER_256)
#define TIMER2_CONF_RUN_PRESCALER_1024	                (TIMER2_MODE_RUN_PRESCALER_1024)

#define TIMER2_CONF_WGM_NORMAL                          (0)
#define TIMER2_CONF_WGM_PHASE_CORRECT_PWM               (             _BV(WGM20))
#define TIMER2_CONF_WGM_CTC                             (_BV(WGM21)             )
#define TIMER2_CONF_WGM_FAST_PWM                        (_BV(WGM21) | _BV(WGM20))
#define TIMER2_CONF_WGM_NORMAL_RESERVED                 (0                       | _BV(8+WGM22))
#define TIMER2_CONF_WGM_PHASE_CORRECT_PWM_USE_OCRA      (             _BV(WGM20) | _BV(8+WGM22))
#define TIMER2_CONF_WGM_CTC_RESERVED                    (_BV(WGM21)              | _BV(8+WGM22))
#define TIMER2_CONF_WGM_FAST_PWM_USE_OCRA               (_BV(WGM21) | _BV(WGM20) | _BV(8+WGM22))

#define TIMER2_CONF_OC2A_DISCONNECTED                   (0)
#define TIMER2_CONF_OC2A_TOGGLE                         (              _BV(COM2A0))
#define TIMER2_CONF_OC2A_CLEAR                          (_BV(COM2A1)              )
#define TIMER2_CONF_OC2A_SET                            (_BV(COM2A1) | _BV(COM2A0))

#define TIMER2_CONF_FAST_PWM_OC2A_DISCONNECTED          (0)
#define TIMER2_CONF_FAST_PWM_OC2A_TOGGLE                (              _BV(COM2A0) | _BV(8+WGM22))
#define TIMER2_CONF_FAST_PWM_OC2A_NON_INVERTING         (_BV(COM2A1)              )
#define TIMER2_CONF_FAST_PWM_OC2A_INVERTING             (_BV(COM2A1) | _BV(COM2A0))

#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2A_DISCONNECTED (0)
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2A_TOGGLE       (              _BV(COM2A0) | _BV(8+WGM22))
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2A_NON_INVERTING (_BV(COM2A1)              )
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2A_INVERTING    (_BV(COM2A1) | _BV(COM2A0))

#define TIMER2_CONF_OC2B_DISCONNECTED                   (0)
#define TIMER2_CONF_OC2B_TOGGLE                         (              _BV(COM2B0))
#define TIMER2_CONF_OC2B_CLEAR                          (_BV(COM2B1)              )
#define TIMER2_CONF_OC2B_SET                            (_BV(COM2B1) | _BV(COM2B0))

#define TIMER2_CONF_FAST_PWM_OC2B_DISCONNECTED          (0)
#define TIMER2_CONF_FAST_PWM_OC2B_RESERVED              (              _BV(COM2B0))
#define TIMER2_CONF_FAST_PWM_OC2B_NON_INVERTING         (_BV(COM2B1)              )
#define TIMER2_CONF_FAST_PWM_OC2B_INVERTING             (_BV(COM2B1) | _BV(COM2B0))

#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2B_DISCONNECTED (0)
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2B_RESERVED     (              _BV(COM2B0))
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2B_NON_INVERTING (_BV(COM2B1)              )
#define TIMER2_CONF_PHASE_CORRECT_PWM_OC2B_INVERTING    (_BV(COM2B1) | _BV(COM2B0))

#define TIMER2_CONF_TOP(value)                          ((value) * 65536L)
#define TIMER2_CONF_OCRA(value)                         ((value) * 65536L)
#define TIMER2_CONF_OCRB(value)                         ((value) * 65536L * 256L)

#define TIMER2_CONF_DEFAULT                             (0)


inline static void timer2__switch_conf(uint32_t old_conf, uint32_t new_conf) {
    uint8_t old_tccra = old_conf & 0xFF;
    uint8_t new_tccra = new_conf & 0xFF;
    if (old_tccra != new_tccra) TCCR2A = new_tccra;

    uint8_t old_tccrb = (old_conf >> 8) & 0xFF;
    uint8_t new_tccrb = (new_conf >> 8) & 0xFF;
    if (old_tccrb != new_tccrb) TCCR2B = new_tccrb;

    uint8_t old_ocra = (old_conf >> 16) & 0xFF;
    uint8_t new_ocra = (new_conf >> 16) & 0xFF;
    if (old_ocra != new_ocra) OCR2A = new_ocra;

    uint8_t old_ocrb = (old_conf >> 24) & 0xFF;
    uint8_t new_ocrb = (new_conf >> 24) & 0xFF;
    if (old_ocrb != new_ocrb) OCR2B = new_ocrb;
}


inline static void timer2__compare_b__interrupt__enable(void) {
    TIMSK2 |= _BV(OCIE2B);
}

inline static void timer2__compare_b__interrupt__disable(void) {
    TIMSK2 &= ~_BV(OCIE2B);
}


inline static void timer2__overflow_interrupt__enable(void) {
    TIMSK2 |= _BV(TOIE2);
}

inline static void timer2__overflow_interrupt__disable(void) {
    TIMSK2 &= ~_BV(TOIE2);
}


#endif