// =============================================================================
// Timer 0 driver for parts with 2 Output Compare modules
// and the following configuration registers:
//
// TCCR0A
// TCCR0B
// OCR0A
// OCR0B
//
// The values of these registers, concatenated together into 32-bit value,
// is referrd to as "configuration value" of the timer.
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


inline static void timer0__switch_conf(uint32_t old_conf, uint32_t new_conf) {
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


inline static void timer0__compare_a__interrupt_enable(void) {
    TIMSK0 |= _BV(OCIE0A);
}

inline static void timer0__compare_a__interrupt_disable(void) {
    TIMSK0 &= ~_BV(OCIE0A);
}


inline static void timer0__compare_b__interrupt_enable(void) {
    TIMSK0 |= _BV(OCIE0B);
}

inline static void timer0__compare_b__interrupt_disable(void) {
    TIMSK0 &= ~_BV(OCIE0B);
}


inline static void timer0__overflow_interrupt_enable(void) {
    TIMSK0 |= _BV(TOIE0);
}

inline static void timer0__overflow_interrupt_disable(void) {
    TIMSK0 &= ~_BV(TOIE0);
}


inline static void timer0__ctc__interrupt__enable(void) {
    timer0__compare_a__interrupt_enable();
}

inline static void timer0__ctc__interrupt__disable(void) {
    timer0__compare_a__interrupt_disable();
}

#define timer0__start(mode) do {\
    TCCR0B = mode;	/* start timer in the user-defined mode  */\
} while(0)


#define timer0__stop() do {\
    TCCR0B = TIMER0_MODE_STOPPED;					\
} while(0)



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