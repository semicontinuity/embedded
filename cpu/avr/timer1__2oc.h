// =============================================================================
// Driver for Timer 1 for parts where Time 2 has 2 Output Compare modules,
// and the following configuration registers:
//
// TCCR1A
// TCCR1B
// TCCR1C
// OCR1AH, OCR1AH
// OCR1BL, OCR1BH,
// ICR1
//
// The 64-bit value, created by concatenation of the values of these registers,
// except ICR1, is referred to as "configuration value" of the timer.
// To get the particular configuration value,
// combine the appropriate with TIMER1_CONF_* constants with logical OR.
//
// Timer configurations can be switched with timer1__switch_conf().
// It produces optimal code, if configuration values are compile-time constants.
// =============================================================================

#ifndef __CPU_AVR_TIMER1_2OC_H
#define __CPU_AVR_TIMER1_2OC_H

#include <avr/io.h>
#include <stdint.h>


#if defined(__AVR_AT90S8535__)

#define TIMER1_MASK_REGISTER TIMSK

#define TIMER1_CONF_WGM_NORMAL                          (            0 |            0 |          0 |          0 )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM8              (            0 |            0 |          0 | _BV(PWM10) )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM9              (            0 |            0 | _BV(PWM11) |          0 )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM10             (            0 |            0 | _BV(PWM11) | _BV(PWM10) )
#define TIMER1_CONF_WGM_CTC_USE_OCRA                    (            0 | _BV(8+ CTC1) |          0 |          0 )
#define TIMER1_CONF_WGM_FAST_PWM8                       (            0 | _BV(8+ CTC1) |          0 | _BV(PWM10) )
#define TIMER1_CONF_WGM_FAST_PWM9                       (            0 | _BV(8+ CTC1) | _BV(PWM11) |          0 )
#define TIMER1_CONF_WGM_FAST_PWM10                      (            0 | _BV(8+ CTC1) | _BV(PWM11) | _BV(PWM10) )


#else

#define TIMER1_MASK_REGISTER TIMSK1

#define TIMER1_CONF_WGM_NORMAL                          (            0 |            0 |          0 |          0 )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM8              (            0 |            0 |          0 | _BV(WGM10) )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM9              (            0 |            0 | _BV(WGM11) |          0 )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM10             (            0 |            0 | _BV(WGM11) | _BV(WGM10) )
#define TIMER1_CONF_WGM_CTC_USE_OCRA                    (            0 | _BV(8+WGM12) |          0 |          0 )
#define TIMER1_CONF_WGM_FAST_PWM8                       (            0 | _BV(8+WGM12) |          0 | _BV(WGM10) )
#define TIMER1_CONF_WGM_FAST_PWM9                       (            0 | _BV(8+WGM12) | _BV(WGM11) |          0 )
#define TIMER1_CONF_WGM_FAST_PWM10                      (            0 | _BV(8+WGM12) | _BV(WGM11) | _BV(WGM10) )
#define TIMER1_CONF_WGM_PHASE_FREQ_CORRECT_PWM_USE_ICR  ( _BV(8+WGM13) |            0 |          0 |          0 )
#define TIMER1_CONF_WGM_PHASE_FREQ_CORRECT_PWM_USE_OCRA ( _BV(8+WGM13) |            0 |          0 | _BV(WGM10) )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM_USE_ICR       ( _BV(8+WGM13) |            0 | _BV(WGM11) |          0 )
#define TIMER1_CONF_WGM_PHASE_CORRECT_PWM_USE_OCRA      ( _BV(8+WGM13) |            0 | _BV(WGM11) | _BV(WGM10) )
#define TIMER1_CONF_WGM_CTC_USE_ICR                     ( _BV(8+WGM13) | _BV(8+WGM12) |          0 |          0 )
#define TIMER1_CONF_WGM_RESERVED                        ( _BV(8+WGM13) | _BV(8+WGM12) |          0 | _BV(WGM10) )
#define TIMER1_CONF_WGM_FAST_PWM_USE_ICR                ( _BV(8+WGM13) | _BV(8+WGM12) | _BV(WGM11) |          0 )
#define TIMER1_CONF_WGM_FAST_PWM_USE_OCRA               ( _BV(8+WGM13) | _BV(8+WGM12) | _BV(WGM11) | _BV(WGM10) )

#endif


#define TIMER1_CONF_STOPPED		                (0)
#define TIMER1_CONF_NO_PRESCALER	                ((                        _BV(CS10)) << 8)
#define TIMER1_CONF_PRESCALER_8                         ((            _BV(CS11)            ) << 8)
#define TIMER1_CONF_PRESCALER_64                        ((            _BV(CS11) | _BV(CS10)) << 8)
#define TIMER1_CONF_PRESCALER_256	                ((_BV(CS12)                        ) << 8)
#define TIMER1_CONF_PRESCALER_1024	                ((_BV(CS12)             | _BV(CS10)) << 8)
#define TIMER1_CONF_EXT_CLK_FALLING	                ((_BV(CS12) | _BV(CS11)            ) << 8)
#define TIMER1_CONF_EXT_CLK_RISING	                ((_BV(CS12) | _BV(CS11) | _BV(CS10)) << 8)

#define TIMER1_CONF_DEFAULT                             (0)


inline static void timer1__switch_conf(const uint64_t old_conf, const uint64_t new_conf) {
    const uint8_t old_tccra = old_conf & 0xFF;
    const uint8_t new_tccra = new_conf & 0xFF;
    if (old_tccra != new_tccra) TCCR1A = new_tccra;

    const uint8_t old_tccrb = (old_conf >> 8) & 0xFF;
    const uint8_t new_tccrb = (new_conf >> 8) & 0xFF;
    if (old_tccrb != new_tccrb) TCCR1B = new_tccrb;

#if !defined(__AVR_AT90S8535__) 
    const uint8_t old_tccrc = (old_conf >> 16) & 0xFF;
    const uint8_t new_tccrc = (new_conf >> 16) & 0xFF;
    if (old_tccrc != new_tccrc) TCCR1C = new_tccrc;
#endif

    const uint16_t old_ocra = (old_conf >> 32) & 0xFFFF;
    const uint16_t new_ocra = (new_conf >> 32) & 0xFFFF;
    if (old_ocra != new_ocra) OCR1A = new_ocra;

    const uint16_t old_ocrb = (old_conf >> 48) & 0xFF;
    const uint16_t new_ocrb = (new_conf >> 48) & 0xFF;
    if (old_ocrb != new_ocrb) OCR1B = new_ocrb;
}


static inline uint8_t timer1__is_running(void) {
    return TCCR1B & (_BV(CS12) | _BV(CS11) | _BV(CS10));
}


static inline void timer1__compare_a__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) TIMER1_MASK_REGISTER |= (1<<OCIE1A); else TIMER1_MASK_REGISTER &= ~(1<<OCIE1A);
}

static inline uint8_t timer1__compare_a__interrupt__enabled__get(void) {
    return TIMER1_MASK_REGISTER & (1<<OCIE1A);
}


static inline void timer1__compare_b__interrupt__enabled__set(const uint8_t enabled) {
    if (enabled) TIMER1_MASK_REGISTER |= (1<<OCIE1B); else TIMER1_MASK_REGISTER &= ~(1<<OCIE1B);
}

static inline uint8_t timer1__compare_b__interrupt__enabled__get(void) {
    return TIMER1_MASK_REGISTER & (1<<OCIE1B);
}


static inline void timer1__compare_a__value__set(const uint16_t value) {
    OCR1A = value;
}

static inline uint16_t timer1__compare_a__value__get(void) {
    return OCR1A;
}


static inline void timer1__compare_b__value__set(const uint16_t value) {
    OCR1B = value;
}

static inline uint16_t timer1__compare_b__value__get(void) {
    return OCR1B;
}


static inline void timer1__value__set(const uint16_t value) {
    TCNT1 = value;
}

static inline uint16_t timer1__value__get(void) {
    return TCNT1;
}

#endif