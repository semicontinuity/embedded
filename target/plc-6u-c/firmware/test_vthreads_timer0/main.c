// =============================================================================
// Test vthread, runnable on timeout of timer0.
// Works on ATMEGA8535, PD3
// =============================================================================
#include "cpu/avr/timer0.h"
#include "cpu/avr/timer2.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/util/vthreads.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// -----------------------------------------------------------------------------
// 1-wire thread
// Handles one 1-wire transaction.
// -----------------------------------------------------------------------------

/** Instruction pointer */
#ifdef ONEWIRE__THREAD__IP__REG
register void* onewire__thread__ip asm(QUOTE(ONEWIRE__THREAD__IP__REG));
#else
volatile void *onewire__thread__ip;
#endif

volatile bool done;

void led__init(void) {
    USE_AS_OUTPUT(LED);
}

void led__toggle(void) {
    PORT_REG(SIGNAL_PORT(LED)) ^= SIGNAL_MASK(LED);
}

/**
 * thread function.
 */
void onewire__thread__run(void) {
    VT_BEGIN(onewire__thread, onewire__thread__ip);

    led__toggle();
    timer0__value__set(0);
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();
    timer0__value__set(64);
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();
    timer0__value__set(128);
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();
    timer0__value__set(192);
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();

    done = true;
    VT_END(onewire__thread);
}


/** Starts the thread */
void onewire__thread__start(void) {
    VT_INIT(onewire__thread, onewire__thread__ip);
    done = false;
    timer0__conf__set(TIMER0_CONF_PRESCALER_8|TIMER0_CONF_WGM_NORMAL);
}


int main(void) {
    led__init();

    for(;;) {
        onewire__thread__start();

        for(;;) {
            if (done) break;
            if (timer0__overflow__interrupt__pending__get()) {
                timer0__overflow__interrupt__pending__clear();
                onewire__thread__run();
            }
        }
        timer0__conf__set(TIMER0_CONF_DEFAULT);
        
        _delay_ms(100);
    }
}
