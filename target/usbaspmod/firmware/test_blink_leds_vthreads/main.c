// =============================================================================
// Test (blinking LEDs)
// =============================================================================

#include "drivers/out/led_green.h"
#include "drivers/out/led_red.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/timer2.h"


#define SYSTEM_TIMER__CONF__DEFAULT     (TIMER2_CONF_DEFAULT)
#define SYSTEM_TIMER__CONF__INITIALIZED (TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(125) | TIMER2_CONF_STOPPED)
#define SYSTEM_TIMER__CONF__STARTED     (TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(125) | TIMER2_CONF_PRESCALER_256)

INLINE void system_timer__on_system_tick(void);


inline static void system_timer__init(void) {
    timer2__switch_conf(SYSTEM_TIMER__CONF__DEFAULT, SYSTEM_TIMER__CONF__INITIALIZED);
}


inline static void system_timer__start(void) {
    timer2__ctc__interrupt__enable();
    timer2__switch_conf(SYSTEM_TIMER__CONF__INITIALIZED, SYSTEM_TIMER__CONF__STARTED);
}


inline static void system_timer__stop(void) {
    timer2__ctc__interrupt__disable();
    timer2__switch_conf(SYSTEM_TIMER__CONF__STARTED, SYSTEM_TIMER__CONF__INITIALIZED);
}


volatile uint8_t counter;
volatile bool phase;

#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif

#ifdef BLINK_THREAD__IP__REG
register uint8_t* blink_thread__ip asm(QUOTE(BLINK_THREAD__IP__REG));
#else
volatile uint8_t* blink_thread__ip;
#endif

static inline void blink_thread__init(void) {
    VT_INIT(blink_thread, blink_thread__ip);
}


void blink_thread__run(void) {
    VT_BEGIN(blink_thread, blink_thread__ip);

    for(;;) {
        VT_MARK(blink_thread, OFF);
        PORTC &= ~(1<<0);
        VT_YIELD(blink_thread, blink_thread__ip);


        VT_MARK(blink_thread, ON);
        PORTC |= (1<<0);
        VT_GOTO(blink_thread, blink_thread__ip, BEGIN);
    }

    VT_UNREACHEABLE_END(blink_thread);
}


/**
 * Callback function, called by system_timer__run() on every system tick.
 */
void system_timer__on_system_tick(void) {
    if (--counter == 0) {	// div 256
        blink_thread__run();
    }
}



int main(void) {
    led_red__init();
    led_green__init();
    system_timer__init();
    blink_thread__init();

    system_timer__start();

    sei();
    for(;;) {
    }

    return 0;
}
