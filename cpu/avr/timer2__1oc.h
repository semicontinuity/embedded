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


inline static void timer2__compare_a__value__set(const uint16_t value) {
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


inline static void timer2__init(void) {
#ifdef TIMER2__COMPARE_A__INTERRUPT__ENABLED
    timer2__compare_a__interrupt__enabled__set(1);
#endif

#ifdef TIMER2__COMPARE_B__INTERRUPT__ENABLED
    timer2__compare_b__interrupt__enabled__set(1);
#endif
}


#if defined(TIMER2__CONF) || defined(TIMER2__PERIOD)
inline static void timer2__start(void) {
    timer2__value__set(0);
#if defined(TIMER2__CONF)
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF);
#elif defined(TIMER2__PERIOD)
#  if TIMER2__PERIOD <= 0
#    error "Invalid period setting for Timer 2"
#  elif TIMER2__PERIOD <= 256
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_NO_PRESCALER | TIMER2_CONF_TOP(TIMER2__PERIOD-1));
#  elif TIMER2__PERIOD <= 256*8
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_8 | TIMER2_CONF_TOP((TIMER2__PERIOD/8)-1));
#  elif TIMER2__PERIOD <= 256*32
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_32 | TIMER2_CONF_TOP((TIMER2__PERIOD/32)-1));
#  elif TIMER2__PERIOD <= 256*64
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_64 | TIMER2_CONF_TOP((TIMER2__PERIOD/64)-1));
#  elif TIMER2__PERIOD <= 256*128
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_128 | TIMER2_CONF_TOP((TIMER2__PERIOD/128)-1));
#  elif TIMER2__PERIOD <= 256*256
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_256 | TIMER2_CONF_TOP((TIMER2__PERIOD/256)-1));
#  elif TIMER2__PERIOD <= 256*1024
    timer2__switch_conf(TIMER2_CONF_DEFAULT, TIMER2_CONF_WGM_CTC | TIMER2_CONF_PRESCALER_1024 | TIMER2_CONF_TOP((TIMER2__PERIOD/1024)-1));
#  else
#    error "Period setting for Timer 2 is out of range"
#  endif
#endif
}
#endif


inline static void timer2__stop(void) {
    TCCR2 = TIMER2_CONF_DEFAULT;
}


#endif