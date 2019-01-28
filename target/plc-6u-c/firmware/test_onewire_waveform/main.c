// =============================================================================
// Test generation of complex waveform with vthread
// =============================================================================
#include "cpu/avr/timer0.h"
#include "cpu/avr/timer2.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/util/vthreads.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "onewire__bus.h"


#include "util/bitops.h"

//DEFINE_BITVAR(onewire__thread__alive, SIGNAL_PORT_REG(DISPLAY_DIGIT0), SIGNAL_PIN(DISPLAY_SEGMENT_DP));
DEFINE_BITVAR(onewire__thread__alive, PORTD, 3);

/** Check whether the thread is alive */
bool onewire__thread__is_alive(void) {
    return onewire__thread__alive__get();
}



/** Generates 0->1 transition */
ISR(timer2__compare_a__interrupt__VECTOR, ISR_NAKED) {
    onewire__bus__set(1);
    reti();
}


/** Reads the bit value from the bus */
ISR(timer2__overflow__interrupt__VECTOR, ISR_NAKED) {
//    if onewire__bus__get() data__set(); else data__clear();
//    if (onewire__bus__get()) OUT_1(LED); else OUT_0(LED);
//OUT_1(LED);
//OUT_0(LED);

    reti();
}




#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


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

void led__toggle(void) {
    PORT_REG(SIGNAL_PORT(LED)) ^= SIGNAL_MASK(LED);
}

/**
 * 1-wire thread function.
 * Invoked when it's time to render new bit on the bus.
 * Other interrupts in the system should not take much time (say, less than 3uS) not to skrew up 1-wire timings.
 */
void onewire__thread__run(void) {
    timer0__overflow__interrupt__pending__clear();

    VT_BEGIN(onewire__thread, onewire__thread__ip);
//    timer0__conf__set(TIMER0_CONF_DEFAULT);

    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);
    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);
    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);
    led__toggle();
    VT_YIELD(onewire__thread, onewire__thread__ip);

    timer0__conf__set(TIMER0_CONF_DEFAULT);

/*
    onewire__bus__set(0);
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);
    VT_YIELD(onewire__thread, onewire__thread__ip);

    onewire__bus__set(1);
    timer0__conf__set(TIMER0_CONF_DEFAULT);
*/

/*
    onewire__bus__set(0);
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);
    VT_YIELD(onewire__thread, onewire__thread__ip);
    onewire__bus__set(1);
    timer0__conf__set(TIMER0_CONF_DEFAULT);
    
    onewire__bus__set(0);
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);
    VT_YIELD(onewire__thread, onewire__thread__ip);
    onewire__bus__set(1);
    timer0__conf__set(TIMER0_CONF_DEFAULT);
    
    onewire__bus__set(0);
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);
    VT_YIELD(onewire__thread, onewire__thread__ip);
    onewire__bus__set(1);
    timer0__conf__set(TIMER0_CONF_DEFAULT);
*/    

/*
    //Render "0" bit
    onewire__bus__set(0);
    timer2__compare_a__value__set(238); // 238
    timer2__value__set(118); // start from 118, count till 238 = 120, 60uS
    timer2__conf__set(ONEWIRE__BIT_FORM_TIMER__FAST_CONF);
    timer2__compare_a__interrupt__enable();
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);

    VT_YIELD(onewire__thread, onewire__thread__ip);

    timer0__conf__set(TIMER0_CONF_DEFAULT);
    timer2__conf__set(TIMER2_CONF_DEFAULT);
    timer2__compare_a__interrupt__disable();


    // Render 32uS low pulse
    onewire__bus__set(0);
    timer2__compare_a__value__set(238);
    timer2__value__set(174); // start from 174, count till 238 = 64, 32uS
    timer2__conf__set(ONEWIRE__BIT_FORM_TIMER__FAST_CONF);
    timer2__compare_a__interrupt__enable();
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);

    VT_YIELD(onewire__thread, onewire__thread__ip);


    timer0__conf__set(TIMER0_CONF_DEFAULT);
    timer2__conf__set(TIMER2_CONF_DEFAULT);
    timer2__compare_a__interrupt__disable();


    // Render "1" bit
    onewire__bus__set(0);
    timer2__compare_a__value__set(238); // 238
    timer2__value__set(226); // start from 226, count till 238 = 12, 6uS
    timer2__conf__set(ONEWIRE__BIT_FORM_TIMER__FAST_CONF);
    timer2__compare_a__interrupt__enable();
    timer0__value__set(0); // 0.5uS * 256 = 128uS timeout
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);

    VT_YIELD(onewire__thread, onewire__thread__ip);


    timer0__conf__set(TIMER0_CONF_DEFAULT);
    timer2__conf__set(TIMER2_CONF_DEFAULT);
    timer2__compare_a__interrupt__disable();
*/
    onewire__thread__alive__set(false);
    VT_END(onewire__thread);
}

/** Check whether the thread can be scheduled (applicable only if the thread is alive) */
bool onewire__thread__is_runnable(void) {
    return timer0__overflow__interrupt__pending__get();
}

/** Starts the thread */
void onewire__thread__start(void) {
    VT_INIT(onewire__thread, onewire__thread__ip);
    onewire__thread__alive__set(true);
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);
}


void main__thread__run(void) {
    onewire__thread__start();
    do {
        if (onewire__thread__is_runnable())
            onewire__thread__run();
    }
    while (onewire__thread__is_alive());
}


int main(void) {
//    USE_AS_OUTPUT(LED);
//    USE_AS_OUTPUT(LED2); 
    onewire__bus__init();
    onewire__bus__set(1);
    _delay_ms(1);
    
    sei();
    for(;;) {
        main__thread__run();
        _delay_ms(100);
    }

}
