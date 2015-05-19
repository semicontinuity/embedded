// =============================================================================
// 1-wire client.
// Implemented with bit-banging, timer 0 and timer 2:
//
// Theory of operation:
// --------------------
// For 16MHz crystal, use prescaler 8 for both timers (64 for reset pulse).
// Thus, 1uS=2TQ (1TQ=4uS for reset pulse).
//
// The bit is started with 1->0 transition at T=0.
//
// READ and WRITE1 waveforms:
// ---+   +------------------------------------------------------+------+
//    |   |      read                                         eof        done
//    +---+       *
//    0   6us    15us                                           60us   70us
//    0   12TQ   30TQ                                          120TQ  140TQ
//        T2CA   T2OVF                                                T0CA
// 0->1 transition at 6us is generated in OC2 interrupt handler.
// Bus is read and T2 stopped at 15uS in T2OVF interrupt handler.
// Signal the possibility to handle next bit by OC0 interrupt at 70uS.
//
// WRITE0 waveform:
// ---+                                                          +------+
//    |                                                       eof|    *  done
//    +----------------------------------------------------------+
//    0                                                        60us 69us 70us
//    0                                                       120TQ 138TQ 140TQ
//                                                            T2CA  T2OVF T0CA
//
// 0->1 transition at 60us is generated in OC2 interrupt handler.
// Bus is read and T2 stopped at 69uS in T2OVF interrupt handler.
// Signal the possibility to handle next bit by OC0 interrupt at 70uS.
//
// RESET and presence pulse waveform:
// ---+                            +------+   +-------------------------+
//    |                            |      | * |                        done
//    +----------------------------+      +---+
//    0                          480us     552us                      960us
//    0                          120TQ     138TQ                      240TQ
//                               T2CA      T2OVF                      T0CA
//
// 0->1 transition at 480us is generated in OC2 interrupt handler.
// Bus is read and T2 stopped at 552uS in T2OVF interrupt handler.
// Signal completion by OC0 interrupt at 960uS (240TQ).
// =============================================================================

#include "onewire.h"
#include "onewire__bus.h"

#include "util/crc8_ow.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/timer0.h"
#include "cpu/avr/timer2.h"
#include "cpu/avr/util/vthreads.h"

#include <avr/interrupt.h>



#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


// -----------------------------------------------------------------------------
// Abstract 1-wire timer, composed of Timer0 and Timer2.
// -----------------------------------------------------------------------------
void onewire__timer__init(void) {
    timer2__compare_a__interrupt__enable();
    timer2__overflow__interrupt__enable();
    timer0__compare_a__interrupt__enable();
}

void onewire__timer__shutdown(void) {
    timer0__compare_a__interrupt__disable();
    timer2__overflow__interrupt__disable();
    timer2__compare_a__interrupt__disable();
}

inline static void onewire__timer__start(
    const uint16_t form_timer_conf,
    const uint8_t form_timer_start_value,
    const uint8_t form_timer_drive_high_value,
    const uint16_t span_timer_conf,
    const uint8_t span_timer_value)
{
    timer2__value__set(form_timer_start_value);
    timer2__compare_a__value__set(form_timer_drive_high_value);
    timer2__conf__set(form_timer_conf);
    timer0__value__set(0);
    timer0__compare_a__value__set(span_timer_value);
    timer0__conf__set(span_timer_conf);
}

bool onewire__timer__overrun__get(void) {
    return timer0__compare_a__interrupt__pending__get();
}

void onewire__timer__overrun__clear(void) {
    timer0__compare_a__interrupt__pending__clear();
}

// -----------------------------------------------------------------------------
// 1-wire interrupt handlers.
// -----------------------------------------------------------------------------

/** Generates 0->1 transition */
ISR(timer2__compare_a__interrupt__VECTOR, ISR_NAKED) {
    onewire__bus__set(1);
    reti();
}

/** Reads the bit value from the bus and stops the 'form' timer */
ISR(timer2__overflow__interrupt__VECTOR, ISR_NAKED) {
    timer2__conf__set(TIMER2_CONF_DEFAULT);
    reti();
}


// -----------------------------------------------------------------------------
// 1-wire thread
// Handles one 1-wire transaction.
// -----------------------------------------------------------------------------

/** Data exchanged */
#ifdef ONEWIRE__THREAD__DATA__REG
register uint8_t onewire__thread__data asm(QUOTE(ONEWIRE__THREAD__DATA__REG));
#else
volatile uint8_t onewire__thread__data;
#endif

/** Remaining number of bits to render */
#ifdef ONEWIRE__THREAD__BIT_COUNT__REG
register uint8_t onewire__thread__bit_count asm(QUOTE(ONEWIRE__THREAD__BIT_COUNT__REG));
#else
volatile uint8_t onewire__thread__bit_count;
#endif

/** Instruction pointer */
#ifdef ONEWIRE__THREAD__IP__REG
register void* onewire__thread__ip asm(QUOTE(ONEWIRE__THREAD__IP__REG));
#else
volatile void *onewire__thread__ip;
#endif

/** TX data pointer */
volatile uint8_t *onewire__thread__tx__ptr;

/** Remaining TX data length */
volatile uint8_t onewire__thread__tx__remaining;

/** RX data pointer */
volatile uint8_t *onewire__thread__rx__ptr;

/** Remaining RX data length */
volatile uint8_t onewire__thread__rx__remaining;

/** CRC of RX data */
volatile uint8_t onewire__thread__crc;


/** Starts the thread */
void onewire__thread__start(void) {
    VT_INIT(onewire__thread, onewire__thread__ip);
    onewire__thread__alive__set(true);
}

/** Check whether the thread is alive */
bool onewire__thread__is_alive(void) {
    return onewire__thread__alive__get();
}

/** Check whether the thread can be scheduled (applicable only if the thread is alive) */
bool onewire__thread__is_runnable(void) {
    return onewire__timer__overrun__get();
}


/**
 * Send a byte over the 1-wire bus.
 * Wait (yield) until onewire__bitbang_thread__alive__get() returns false.
 */
void onewire__thread__write_byte(const uint8_t value) {
/*
    onewire__bitbang_thread__data__set(value);
    onewire__thread__bit_count = 8;
    onewire__bitbang_thread__alive__set(true);

    onewire__bus__set(0);
    onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__timer__start(ONEWIRE__TIMER__FAST_CONF);
*/
}


/**
 * Receive a byte over the 1-wire bus.
 * Wait (yield) until onewire__bitbang_thread__alive__get() returns false.
 * Call onewire__bitbang_thread__data__get() to get the received byte.
 */
void onewire__thread__read_byte(void) {
/*
    onewire__thread__bit_count = 8;
    onewire__bitbang_thread__alive__set(true);

    onewire__bus__set(0);
    onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__timer__start(ONEWIRE__TIMER__FAST_CONF);
*/
}


/**
 * Reset 1-wire bus.
 * The result is available via onewire__bitbang_thread__data__get().
 * If presence pulse is generated, onewire__thread__data will be false.
 */
void onewire__thread__reset_bus(void) {
    onewire__bus__set(0);
    onewire__timer__start(
        ONEWIRE__BIT_FORM_TIMER__SLOW_CONF,
        256 - ONEWIRE__BIT_FORM_TIMER__RESET_READ_TIME,
        256 - ONEWIRE__BIT_FORM_TIMER__RESET_READ_TIME + ONEWIRE__BIT_FORM_TIMER__RESET_DRIVE_HIGH_TIME,
        ONEWIRE__BIT_SPAN_TIMER__SLOW_CONF,
        ONEWIRE__BIT_SPAN_TIMER__SLOW_CONF_TIMEOUT
    );
}


void onewire__thread__run(void) {
    VT_BEGIN(onewire__thread, onewire__thread__ip);

/*
    while (onewire__thread__tx__remaining--) {
        onewire__thread__write_byte(*onewire__thread__tx__ptr++);
        VT_YIELD(onewire__thread, onewire__thread__ip);
    }

    while (onewire__thread__rx__remaining--) {
        onewire__thread__read_byte();
        VT_YIELD(onewire__thread, onewire__thread__ip);
        uint8_t data = onewire__bitbang_thread__data__get();
        *onewire__thread__rx__ptr++ = data;
        onewire__thread__crc = crc8_ow_update(onewire__thread__crc, data);
    }
*/

    onewire__timer__overrun__clear();
    VT_END(onewire__thread);
}


// -----------------------------------------------------------------------------
// 1-wire client
// -----------------------------------------------------------------------------

void onewire__init(void) {
    onewire__timer__init();
}


void onewire__shutdown(void) {
    onewire__timer__shutdown();
}


/**
 * Perform 1-wire transaction.
 * Poll onewire__thread__is_running() for completion status.
 */
void onewire__command(uint8_t command_length, uint8_t response_length, uint8_t *command, uint8_t *response) {
    onewire__thread__tx__ptr = command;
    onewire__thread__tx__remaining = command_length;
    onewire__thread__rx__ptr = response;
    onewire__thread__rx__remaining = response_length;
    onewire__thread__crc = 0;
    onewire__thread__start();
    onewire__thread__reset_bus();
}


/** Returns CRC of received data */
uint8_t onewire__crc__get(void) {
    return onewire__thread__crc;
}
