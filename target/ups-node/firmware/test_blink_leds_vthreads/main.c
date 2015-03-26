// =============================================================================
// Test (blinking LEDs)
// =============================================================================

#include "drivers/out/led_red.h"
#include "system_timer.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include "cpu/avr/util/vthreads.h"

volatile uint8_t counter = 25;
volatile uint8_t phase;


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
        led_red__set(1);
        VT_YIELD(blink_thread, blink_thread__ip);

        led_red__set(0);
        VT_YIELD(blink_thread, blink_thread__ip);


        led_red__set(1);
        VT_YIELD(blink_thread, blink_thread__ip);

        led_red__set(0);
        VT_YIELD(blink_thread, blink_thread__ip);


        led_red__set(1);
        VT_YIELD(blink_thread, blink_thread__ip);

        led_red__set(0);
        VT_YIELD(blink_thread, blink_thread__ip);


        VT_YIELD(blink_thread, blink_thread__ip);
        VT_YIELD(blink_thread, blink_thread__ip);
        VT_YIELD(blink_thread, blink_thread__ip);
        VT_YIELD(blink_thread, blink_thread__ip);
        VT_YIELD(blink_thread, blink_thread__ip);

        VT_GOTO(blink_thread, blink_thread__ip, BEGIN);
    }

    VT_UNREACHEABLE_END(blink_thread);
}


/**
 * Callback function, called by system_timer__run() on every system tick.
 */
void system_timer__on_system_tick(void) {
    if (--counter == 0) {
        counter = 25;
        blink_thread__run();
    }
}

int main(void) {
    led_red__init();
    blink_thread__init();
    system_timer__init();

    system_timer__start();

    sei();
    for(;;) {
    }

    return 0;
}
