#ifndef __CPU_AVR_TIMER2_M8_H
#define __CPU_AVR_TIMER2_M8_H

#include <avr/io.h>
#include <stdint.h>

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

#define TIMER2_CONF_STOPPED		                (0)
#define TIMER2_CONF_NO_PRESCALER	                (                        _BV(CS20))
#define TIMER2_CONF_PRESCALER_8                         (            _BV(CS21)            )
#define TIMER2_CONF_PRESCALER_32	                (            _BV(CS21) | _BV(CS20))
#define TIMER2_CONF_PRESCALER_64	                (_BV(CS22)                        )
#define TIMER2_CONF_PRESCALER_128                       (_BV(CS22)             | _BV(CS20))
#define TIMER2_CONF_PRESCALER_256	                (_BV(CS22) | _BV(CS21)            )
#define TIMER2_CONF_PRESCALER_1024                      (_BV(CS22) | _BV(CS21) | _BV(CS20))

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


inline static void timer2__compare__interrupt_enable(void) {
    TIMSK |= _BV(OCIE2);
}

inline static void timer2__compare__interrupt_disable(void) {
    TIMSK &= ~_BV(OCIE2);
}


inline static void timer2__overflow_interrupt_enable(void) {
    TIMSK |= _BV(TOIE2);
}

inline static void timer2__overflow_interrupt_disable(void) {
    TIMSK &= ~_BV(TOIE2);
}


inline static void timer2__ctc__interrupt__enable(void) {
    timer2__compare__interrupt_enable();
}

inline static void timer2__ctc__interrupt__disable(void) {
    timer2__compare__interrupt_disable();
}

#define timer2__start(mode) do {\
    TCCR2 = mode;	/* start timer in the user-defined mode  */\
} while(0)

#define timer2__stop() do {\
    TCCR2 = TIMER2_MODE_STOPPED; /* stop timer 0 */\
} while(0)


#endif