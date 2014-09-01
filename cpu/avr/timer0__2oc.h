// =============================================================================
// Timer 0 driver for parts with 2 Output Compare modules
// and the following configuration registers:
//
// TCCR0A
// TCCR0B
// OCR0A
// OCR0B
//
// The 32-bit value, created by concatenation of the values of these registers,
// is referred to as "configuration value" of the timer.
// To get the particular configuration value,
// combine the appropriate with TIMER0_CONF_* constants with logical OR.
//
// Timer configurations can be switched with timer0__switch_conf().
// It produces optimal code, if configuration values are compile-time constants.
// =============================================================================

#ifndef __CPU_AVR_TIMER0_H
# error "Include timer0.h instead"
#endif


#ifndef __CPU_AVR_TIMER0_2OC_H
#define __CPU_AVR_TIMER0_2OC_H

#include <avr/io.h>
#include <stdint.h>

#define TIMER0_CONF_WGM_NORMAL                          (0)
#define TIMER0_CONF_WGM_PHASE_CORRECT_PWM               (             _BV(WGM00))
#define TIMER0_CONF_WGM_CTC                             (_BV(WGM01)             )
#define TIMER0_CONF_WGM_FAST_PWM                        (_BV(WGM01) | _BV(WGM00))
#define TIMER0_CONF_WGM_NORMAL_RESERVED                 (0                       | _BV(8+WGM02))
#define TIMER0_CONF_WGM_PHASE_CORRECT_PWM_USE_OCRA      (             _BV(WGM00) | _BV(8+WGM02))
#define TIMER0_CONF_WGM_CTC_RESERVED                    (_BV(WGM01)              | _BV(8+WGM02))
#define TIMER0_CONF_WGM_FAST_PWM_USE_OCRA               (_BV(WGM01) | _BV(WGM00) | _BV(8+WGM02))

#define TIMER0_CONF_STOPPED		                (0)
#define TIMER0_CONF_NO_PRESCALER	                ((                        _BV(CS00)) << 8)
#define TIMER0_CONF_PRESCALER_8                         ((            _BV(CS01)            ) << 8)
#define TIMER0_CONF_PRESCALER_64	                ((            _BV(CS01) | _BV(CS00)) << 8)
#define TIMER0_CONF_PRESCALER_256	                ((_BV(CS02)                        ) << 8)
#define TIMER0_CONF_PRESCALER_1024                      ((_BV(CS02)             | _BV(CS00)) << 8)
#define TIMER0_CONF_EXT_CLK_FALLING                     ((_BV(CS02) | _BV(CS01)            ) << 8)
#define TIMER0_CONF_EXT_CLK_RISING                      ((_BV(CS02) | _BV(CS01) | _BV(CS00)) << 8)

#define TIMER0_CONF_OC0A_DISCONNECTED                   (0)
#define TIMER0_CONF_OC0A_TOGGLE                         (              _BV(COM0A0))
#define TIMER0_CONF_OC0A_CLEAR                          (_BV(COM0A1)              )
#define TIMER0_CONF_OC0A_SET                            (_BV(COM0A1) | _BV(COM0A0))

#define TIMER0_CONF_FAST_PWM_OC0A_DISCONNECTED          (0)
#define TIMER0_CONF_FAST_PWM_OC0A_TOGGLE                (              _BV(COM0A0) | _BV(8+WGM02))
#define TIMER0_CONF_FAST_PWM_OC0A_NON_INVERTING         (_BV(COM0A1)              )
#define TIMER0_CONF_FAST_PWM_OC0A_INVERTING             (_BV(COM0A1) | _BV(COM0A0))

#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0A_DISCONNECTED (0)
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0A_TOGGLE       (              _BV(COM0A0) | _BV(8+WGM02))
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0A_NON_INVERTING (_BV(COM0A1)              )
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0A_INVERTING    (_BV(COM0A1) | _BV(COM0A0))

#define TIMER0_CONF_OC0B_DISCONNECTED                   (0)
#define TIMER0_CONF_OC0B_TOGGLE                         (              _BV(COM0B0))
#define TIMER0_CONF_OC0B_CLEAR                          (_BV(COM0B1)              )
#define TIMER0_CONF_OC0B_SET                            (_BV(COM0B1) | _BV(COM0B0))

#define TIMER0_CONF_FAST_PWM_OC0B_DISCONNECTED          (0)
#define TIMER0_CONF_FAST_PWM_OC0B_RESERVED              (              _BV(COM0B0))
#define TIMER0_CONF_FAST_PWM_OC0B_NON_INVERTING         (_BV(COM0B1)              )
#define TIMER0_CONF_FAST_PWM_OC0B_INVERTING             (_BV(COM0B1) | _BV(COM0B0))

#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0B_DISCONNECTED (0)
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0B_RESERVED     (              _BV(COM0B0))
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0B_NON_INVERTING (_BV(COM0B1)              )
#define TIMER0_CONF_PHASE_CORRECT_PWM_OC0B_INVERTING    (_BV(COM0B1) | _BV(COM0B0))

#define TIMER0_CONF_TOP(value)                          ((value) * 65536L)
#define TIMER0_CONF_OCRA(value)                         ((value) * 65536L)
#define TIMER0_CONF_OCRB(value)                         ((value) * 65536L * 256L)


#define TIMER0_CONF_DEFAULT                             (0)


inline void timer0__switch_conf(uint32_t old_conf, uint32_t new_conf) {
    uint8_t old_tccra = old_conf & 0xFF;
    uint8_t new_tccra = new_conf & 0xFF;
    if (old_tccra != new_tccra) TCCR0A = new_tccra;

    uint8_t old_tccrb = (old_conf >> 8) & 0xFF;
    uint8_t new_tccrb = (new_conf >> 8) & 0xFF;
    if (old_tccrb != new_tccrb) TCCR0B = new_tccrb;

    uint8_t old_ocra = (old_conf >> 16) & 0xFF;
    uint8_t new_ocra = (new_conf >> 16) & 0xFF;
    if (old_ocra != new_ocra) OCR0A = new_ocra;

    uint8_t old_ocrb = (old_conf >> 24) & 0xFF;
    uint8_t new_ocrb = (new_conf >> 24) & 0xFF;
    if (old_ocrb != new_ocrb) OCR0B = new_ocrb;
}


inline void timer0__compare_b__interrupt__enable(void) {
    TIMSK0 |= _BV(OCIE0B);
}

inline void timer0__compare_b__interrupt__disable(void) {
    TIMSK0 &= ~_BV(OCIE0B);
}

inline void timer0__compare_b__interrupt__enabled__set(const uint8_t enable) {
    if (enable)
        timer0__compare_b__interrupt__enable();
    else
        timer0__compare_b__interrupt__disable();
}


inline void timer0__overflow__interrupt__enable(void) {
    TIMSK0 |= _BV(TOIE0);
}

inline void timer0__overflow__interrupt__disable(void) {
    TIMSK0 &= ~_BV(TOIE0);
}

inline void timer0__overflow_interrupt__enabled__set(const uint8_t enable) {
    if (enable)
        timer0__overflow__interrupt__enable();
    else
        timer0__overflow__interrupt__disable();
}


inline uint8_t timer0__conf__ctc_compare_a_value(const uint32_t period) {
    if (period <= 256UL)           return (uint8_t)(period      - 1);
    else if (period <= 256UL*8)    return (uint8_t)(period/8    - 1);
    else if (period <= 256UL*64)   return (uint8_t)(period/64   - 1);
    else if (period <= 256UL*256)  return (uint8_t)(period/256  - 1);
    else if (period <= 256UL*1024) return (uint8_t)(period/1024 - 1);
    else return 0xFF; // should never be invoked with large period argument
}

inline uint16_t timer0__conf__ctc_prescaler_mask(const uint32_t period) {
    if (period <= 256UL) return TIMER0_CONF_NO_PRESCALER;
    else if (period <= 256UL*8) return TIMER0_CONF_PRESCALER_8;
    else if (period <= 256UL*64) return TIMER0_CONF_PRESCALER_64;
    else if (period <= 256UL*256) return TIMER0_CONF_PRESCALER_256;
    else if (period <= 256UL*1024) return TIMER0_CONF_PRESCALER_1024;
    else return TIMER0_CONF_PRESCALER_1024; // should never be invoked with large period argument
}

inline uint16_t timer0__conf__default(void) {
     return TIMER0_CONF_DEFAULT;
}

inline uint16_t timer0__conf__ctc_initialized(const uint8_t compare_a_value) {
     return TIMER0_CONF_STOPPED | TIMER0_CONF_TOP(compare_a_value);
}

inline uint16_t timer0__conf__ctc_started(const uint8_t compare_a_value, const uint16_t prescaler_mask) {
     return TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(compare_a_value) | prescaler_mask;
}


#ifdef timer0__comp_a__run

#ifndef timer0__comp_a__run__attrs
#define timer0__comp_a__run__attrs
#endif

INLINE void timer0__comp_a__run(void) timer0__comp_a__run__attrs;

#endif



#ifdef timer0__comp_b__run

#ifndef timer0__comp_b__run__attrs
#define timer0__comp_b__run__attrs
#endif

INLINE void timer0__comp_b__run(void) timer0__comp_b__run__attrs;

#endif


#endif
