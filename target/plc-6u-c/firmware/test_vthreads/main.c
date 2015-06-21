// =============================================================================
// Test vthreads
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
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);

    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);

    VT_END(onewire__thread);
}


/** Starts the thread */
void onewire__thread__start(void) {
    VT_INIT(onewire__thread, onewire__thread__ip);
}




int main(void) {
    led__init();
    
    for(;;) {
        onewire__thread__start();

        _delay_ms(100);
        onewire__thread__run();
        _delay_ms(100);
        onewire__thread__run();
        _delay_ms(100);
        onewire__thread__run();
        _delay_ms(100);
        onewire__thread__run();
        
        _delay_ms(200);
    }

}
