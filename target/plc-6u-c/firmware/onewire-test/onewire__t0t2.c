// =============================================================================
// 1-wire client.
// Implemented with bit-banging, timer 0 and timer 2:
//
// Theory of operation:
// --------------------
// For 16MHz crystal, use prescaler 8 for both timers (64 for reset pulse).
// The bit is started with 1->0 transition at T=0.
//
// READ and WRITE1 waveforms:
// ---+   +------------------------------------------------------+------+
//    |   |      read                                         eof    next 
//    +---+       *
//    0   6us    15us                                           60us   70us
//
// 0->1 transition at 6us is generated in OC2 interrupt handler.
// Reading bus at 15uS in T2OVF interrupt handler (disabled for WRITE1).
// Signal the possibility to handle next bit by OC0 interrupt.
//
// WRITE0 waveform:
// ---+                                                          +------+
//    |                                                       eof|    next 
//    +----------------------------------------------------------+
//    0   6us    15us                                           60us   70us
//
// 0->1 transition at 60us is generated in OC2 interrupt handler.
// Reading bus at 15uS in T2OVF interrupt handler is disabled for WRITE0.
// Signal the possibility to handle next bit by OC0 interrupt.
//
// RESET and presence pulse waveform:
// ---+                            +------+   +-------------------------+
//    |                            |      | * |                        done
//    +----------------------------+      +---+
//    0                          480us     552us                      960us
//
// 0->1 transition at 480us is generated in OC2 interrupt handler.
// Reading bus at 552uS in T2OVF interrupt handler.
// Signal completion by OC0 interrupt.
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
    timer2__compare_a__interrupt__enabled__set(1);
}

void onewire__timer__shutdown(void) {
    timer2__compare_a__interrupt__enabled__set(0);
}


void onewire__timer__start(const uint8_t conf) {
    timer2__value__set(0);
    timer2__switch_conf(TIMER2_CONF_DEFAULT, conf);
}


void onewire__timer__stop(void) {
    timer2__switch_conf(ONEWIRE__TIMER__FAST_CONF, TIMER2_CONF_DEFAULT);
}


void onewire__timer__clear(void) {
    timer2__value__set(0);
}

void onewire__timer__timeout__set(const uint8_t tq) {
    timer2__compare_a__value__set(tq);
}

// -----------------------------------------------------------------------------
// 1-wire interrupt handlers.
// -----------------------------------------------------------------------------

/** Generates 0->1 transition */
ISR(timer2__compare_a__interrupt__VECTOR, ISR_NAKED) {
}

/** Reads the bit value from the bus */
ISR(timer2__overflow__interrupt__VECTOR, ISR_NAKED) {
}

// -----------------------------------------------------------------------------
// 1-wire bit-bang thread.
// Receives and transmits individual bits
// -----------------------------------------------------------------------------

/** Data exchanged */
#ifdef ONEWIRE__BITBANG_THREAD__DATA__REG
register uint8_t onewire__bitbang_thread__data asm(QUOTE(ONEWIRE__BITBANG_THREAD__DATA__REG));
#else
volatile uint8_t onewire__bitbang_thread__data;
#endif

/** Remaining number of bits to render */
#ifdef ONEWIRE__BITBANG_THREAD__BIT_COUNT__REG
register uint8_t onewire__bitbang_thread__bit_count asm(QUOTE(ONEWIRE__BITBANG_THREAD__BIT_COUNT__REG));
#else
volatile uint8_t onewire__bitbang_thread__bit_count;
#endif


void onewire__bitbang_thread__stop(void) {
    onewire__timer__stop();
    onewire__bitbang_thread__alive__set(false);
}


void onewire__bitbang_thread__data__set(const uint8_t data) {
    onewire__bitbang_thread__data = data;
}

uint8_t onewire__bitbang_thread__data__get(void) {
    return onewire__bitbang_thread__data;
}



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


/** Terminates the thread */
void onewire__thread__stop(void) {
    onewire__thread__alive__set(false);
}


/** Check whether the thread is alive */
bool onewire__thread__is_alive(void) {
    return onewire__thread__alive__get();
}

/** Check whether the thread can be scheduled (applicable only if the thread is alive) */
bool onewire__thread__is_runnable(void) {
    return !onewire__bitbang_thread__alive__get();
}


/**
 * Send a byte over the 1-wire bus.
 * Wait (yield) until onewire__bitbang_thread__alive__get() returns false.
 */
void onewire__thread__write_byte(const uint8_t value) {
    onewire__bitbang_thread__data__set(value);
    onewire__bitbang_thread__bit_count = 8;
    onewire__bitbang_thread__alive__set(true);

    onewire__bus__set(0);
    onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__timer__start(ONEWIRE__TIMER__FAST_CONF);
}


/**
 * Receive a byte over the 1-wire bus.
 * Wait (yield) until onewire__bitbang_thread__alive__get() returns false.
 * Call onewire__bitbang_thread__data__get() to get the received byte.
 */
void onewire__thread__read_byte(void) {
    onewire__bitbang_thread__bit_count = 8;
    onewire__bitbang_thread__alive__set(true);

    onewire__bus__set(0);
    onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__timer__start(ONEWIRE__TIMER__FAST_CONF);
}


/**
 * Reset 1-wire bus.
 * Wait (yield) until onewire__bitbang_thread__alive__get() returns false.
 * The result is available via onewire__bitbang_thread__data__get().
 * If presence pulse is generated, onewire__bitbang_thread__data will be false.
 */
void onewire__thread__reset_bus(void) {
    onewire__bitbang_thread__alive__set(true);

    onewire__bus__set(0);
    onewire__timer__timeout__set(8*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__timer__start(ONEWIRE__TIMER__SLOW_CONF);
}


void onewire__thread__run(void) {
    VT_BEGIN(onewire__thread, onewire__thread__ip);

    onewire__thread__reset_bus();
    // wait until bitbang thread finishes reset pulse.
    VT_YIELD(onewire__thread, onewire__thread__ip);

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

    onewire__thread__stop();
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
}


/** Returns CRC of received data */
uint8_t onewire__crc__get(void) {
    return onewire__thread__crc;
}
