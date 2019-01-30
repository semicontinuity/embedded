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

#define TIMER0_CONF_STOPPED                             (0)
#define TIMER0_CONF_NO_PRESCALER                        (                        _BV(CS00))
#define TIMER0_CONF_PRESCALER_8                         (            _BV(CS01)            )
#define TIMER0_CONF_PRESCALER_64                        (            _BV(CS01) | _BV(CS00))
#define TIMER0_CONF_PRESCALER_256                       (_BV(CS02)                        )
#define TIMER0_CONF_PRESCALER_1024                      (_BV(CS02)             | _BV(CS00))
#define TIMER0_CONF_EXT_CLK_FALLING                     (_BV(CS02) | _BV(CS01)            )
#define TIMER0_CONF_EXT_CLK_RISING                      (_BV(CS02) | _BV(CS01) | _BV(CS00))

#define TIMER0_CONF_TOP(value)                          ((value) << 8)
#define TIMER0_CONF_OCR(value)                          ((value) << 8)

#define TIMER0_CONF_DEFAULT                             (0)


inline static void timer0__conf__set(uint8_t conf) {
    TCCR0 = conf;
}

inline void timer0__switch_conf(uint16_t old_conf, uint16_t new_conf) {
    uint8_t old_tccr = old_conf & 0xFF;
    uint8_t new_tccr = new_conf & 0xFF;
    if (old_tccr != new_tccr) TCCR0 = new_tccr;

    uint8_t old_ocr = (old_conf >> 8) & 0xFF;
    uint8_t new_ocr = (new_conf >> 8) & 0xFF;
    if (old_ocr != new_ocr) OCR0 = new_ocr;
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


#if defined(TIMER0__PERIOD) && !defined(TIMER0__CONF__INITIALIZED)
#  if TIMER0__PERIOD <= 0
#    error "Invalid period setting for Timer 2"
#  elif TIMER0__PERIOD <= 256
#    define TIMER0__CONF__INITIALIZED  (TIMER0_CONF_STOPPED | TIMER0_CONF_TOP((TIMER0__PERIOD) - 1))
#  elif TIMER0__PERIOD <= 256*8
#    define TIMER0__CONF__INITIALIZED  (TIMER0_CONF_STOPPED | TIMER0_CONF_TOP((TIMER0__PERIOD/8) - 1))
#  elif TIMER0__PERIOD <= 256*64
#    define TIMER0__CONF__INITIALIZED  (TIMER0_CONF_STOPPED | TIMER0_CONF_TOP((TIMER0__PERIOD/64) - 1))
#  elif TIMER0__PERIOD <= 256*256
#    define TIMER0__CONF__INITIALIZED  (TIMER0_CONF_STOPPED | TIMER0_CONF_TOP((TIMER0__PERIOD/256) - 1))
#  elif TIMER0__PERIOD <= 256*1024
#    define TIMER0__CONF__INITIALIZED  (TIMER0_CONF_STOPPED | TIMER0_CONF_TOP((TIMER0__PERIOD/1024) - 1))
#  else
#    error "Period setting for Timer 2 is out of range"
#  endif
#endif

#if defined(TIMER0__PERIOD) && !defined(TIMER0__CONF__STARTED)
#  if TIMER0__PERIOD <= 0
#    error "Invalid period setting for Timer 2"
#  elif TIMER0__PERIOD <= 256
#    define TIMER0__CONF__STARTED  (TIMER0_CONF_WGM_CTC | TIMER0_CONF_NO_PRESCALER | TIMER0_CONF_TOP((TIMER0__PERIOD) - 1))
#  elif TIMER0__PERIOD <= 256*8
#    define TIMER0__CONF__STARTED  (TIMER0_CONF_WGM_CTC | TIMER0_CONF_PRESCALER_8 | TIMER0_CONF_TOP((TIMER0__PERIOD/8) - 1))
#  elif TIMER0__PERIOD <= 256*64
#    define TIMER0__CONF__STARTED  (TIMER0_CONF_WGM_CTC | TIMER0_CONF_PRESCALER_64 | TIMER0_CONF_TOP((TIMER0__PERIOD/64) - 1))
#  elif TIMER0__PERIOD <= 256*256
#    define TIMER0__CONF__STARTED  (TIMER0_CONF_WGM_CTC | TIMER0_CONF_PRESCALER_256 | TIMER0_CONF_TOP((TIMER0__PERIOD/256) - 1))
#  elif TIMER0__PERIOD <= 256*1024
#    define TIMER0__CONF__STARTED  (TIMER0_CONF_WGM_CTC | TIMER0_CONF_PRESCALER_1024 | TIMER0_CONF_TOP((TIMER0__PERIOD/1024) - 1))
#  else
#    error "Period setting for Timer 2 is out of range"
#  endif
#endif


inline static void timer0__init(void) {
#ifdef TIMER0__COMPARE_A__INTERRUPT__ENABLED
    timer0__compare_a__interrupt__enabled__set(1);
#endif

#ifdef TIMER0__COMPARE_B__INTERRUPT__ENABLED
    timer0__compare_b__interrupt__enabled__set(1);
#endif

#if defined(TIMER0__CONF__INITIALIZED)
    timer0__switch_conf(TIMER0_CONF_DEFAULT, TIMER0__CONF__INITIALIZED);
#endif
}


#if defined(TIMER0__CONF__INITIALIZED) && defined(TIMER0__CONF__STARTED)
inline static void timer0__start(void) {
    timer0__value__set(0);
    timer0__switch_conf(TIMER0__CONF__INITIALIZED, TIMER0__CONF__STARTED);
}

inline static void timer0__stop(void) {
    timer0__switch_conf(TIMER0__CONF__STARTED, TIMER0__CONF__INITIALIZED);
}
#endif


#endif