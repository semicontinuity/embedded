// =============================================================================
// 1-wire client.
// Implemented with bit-banging and timer 2.
// Logical 1 is driven by external pull-up resistor
// (pin is switched to input).
//
// Sub-modules:
//
// onewire__bus:
//   description: low-level bus driver
//   parameters:
//     ONEWIRE__PORT: AVR port to which 1-wire bus is attached
//     ONEWIRE__PIN: Pin number of the AVR port
// onewire__timer:
//   description: timer that provides the necessary 1-wire timing
//   parameters:
//     ONEWIRE__TIMER__FAST_CONF: Timer 2 configuration for bit IO
//     ONEWIRE__TIMER__SLOW_CONF: Timer 2 configuration for reset pulse handling
//     ONEWIRE__TIMER__TIME_QUANTUM: Timer 2 timeout value for 1 TQ
// onewire__bitbang_thread:
//   description: thread that receives and transmits one byte and handles reset.
// onewire__thread:
//   description: handles frame transmission and reception.
// =============================================================================

#include "onewire.h"

#include "util/crc8_ow.h"
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/timer2.h"
#include "cpu/avr/gpio.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


// -----------------------------------------------------------------------------
// 1-wire bus driver.
// -----------------------------------------------------------------------------

void onewire__bus__set(const uint8_t value) {
    if (value) {
        USE_AS_INPUT(ONEWIRE);  // External pull-up pulls up line high.
    }
    else {
        USE_AS_OUTPUT(ONEWIRE);  // OUT bit is 0
    }
}


bool onewire__bus__get(void) {
    return IS_1(ONEWIRE);
}


// -----------------------------------------------------------------------------
// 1-wire timer.
// -----------------------------------------------------------------------------
void onewire__timer__start(const uint8_t conf) {
    timer2__value__set(0);
    timer2__switch_conf(TIMER2_CONF_DEFAULT, conf);
}


void onewire__timer__stop(void) {
    timer2__stop();
}


void onewire__timer__init(void) {    
    timer2__compare_a__interrupt__enabled__set(1);
}


void onewire__timer__shutdown(void) {
    timer2__compare_a__interrupt__enabled__set(0);
}


void onewire__timer__timeout__set(const uint8_t tq) {
    timer2__compare_a__value__set(tq);
}


// -----------------------------------------------------------------------------
// 1-wire bit-bang thread.
// Receives and transmits individual byte
// -----------------------------------------------------------------------------

/** Flag that indicates that the thread is running */
volatile bool onewire__bitbang_thread__running;

/** Thread instruction pointer */
volatile void *onewire__bitbang_thread__ip;

/** Data exchanged */
volatile uint8_t onewire__bitbang_thread__data;

/** Remaining number of bits to render */
volatile uint8_t onewire__bitbang_thread__bit_count;


bool onewire__bitbang_thread__is_running(void) {
    return onewire__bitbang_thread__running;
}


void onewire__bitbang_thread__start(void) {
    VT_INIT(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    onewire__bitbang_thread__bit_count = 8;
    onewire__bitbang_thread__running = 1;
}


void onewire__bitbang_thread__stop(void) {
    onewire__timer__stop();
    onewire__bitbang_thread__running = 0;
}


void onewire__bitbang_thread__data__set(const uint8_t data) {
    onewire__bitbang_thread__data = data;
}

uint8_t onewire__bitbang_thread__data__get(void) {
    return onewire__bitbang_thread__data;
}


/**
 * Called when 1-wire timer timeout expired (certain amount of time quants programmed).
 */
ISR(timer2__compare_a__interrupt__VECTOR) {

    VT_BEGIN(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    // -------------------------------------------------------------------------
    do {
        // generate 0 for 1 TQ
        onewire__bus__set(0);
        onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);

        // generate 0 or 1 on the bus, depending on the data bit
        if (onewire__bitbang_thread__data & 0x01) onewire__bus__set(1);

        // wait for 1 TQ (timeout is valid already)
        onewire__bus__set(1);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);

        // sample bit
        uint8_t data = onewire__bitbang_thread__data >> 1;
        if (onewire__bus__get()) data |= 0x80;
        onewire__bitbang_thread__data = data;

        // wait for 6 TQ
        onewire__timer__timeout__set(6*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);

        // generate 1 for 1 TQ (guard time)
        onewire__bus__set(1);
        onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    }
    while (--onewire__bitbang_thread__bit_count);

    onewire__bitbang_thread__stop();
    // -------------------------------------------------------------------------
    VT_END(onewire__bitbang_thread);
}


// -----------------------------------------------------------------------------
// 1-wire thread
// Handles one 1-wire transaction.
// -----------------------------------------------------------------------------

/** Flag that indicates that the thread is running */
volatile uint8_t onewire__thread__running;

/** Instruction pointer */
volatile void *onewire__thread__ip;

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


/** Allow thread to be scheduled */
void onewire__thread__start(void) {
    VT_INIT(onewire__thread, onewire__thread__ip);
    onewire__thread__running = true; 
}


/** Disallow thread to be scheduled */
void onewire__thread__stop(void) {
    onewire__thread__running = false;
}


/** Check whether the thread can be scheduled (if the thread is running) */
bool onewire__thread__is_running(void) {
    return onewire__thread__running;
}

/** Check whether the thread can be scheduled (if the thread is running) */
bool onewire__thread__is_runnable(void) {
    return !onewire__bitbang_thread__is_running();
}


/**
 * Exchange the byte on the 1-wire bus.
 * When sending byte, ignore the result.
 * When receiving byte, call with argument 0xFF and read result with onewire__bitbang_thread__data__get().
 * Poll onewire__bitbang_thread__is_running() for the end of operation.
 */
void onewire__thread__exchange_byte(const uint8_t value) {
    onewire__bitbang_thread__data__set(value);
    onewire__bus__set(0);
    
    onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__bitbang_thread__start();
    onewire__timer__start(ONEWIRE__TIMER__FAST_CONF);
}


/**
 * Reset 1-wire bus.
 * Poll onewire__bitbang_thread__is_running() for the end of operation.
 * The result is available via onewire__bitbang_thread__data__get().
 * If presense pulse is generated, onewire__bitbang_thread__data will not equal to 0xFF.
 */
void onewire__thread__reset_bus(void) {
    onewire__bitbang_thread__data__set(0xFF);
    onewire__bus__set(0);
    
    onewire__timer__timeout__set(8*ONEWIRE__TIMER__TIME_QUANTUM);
    onewire__bitbang_thread__start();
    onewire__timer__start(ONEWIRE__TIMER__SLOW_CONF);    
}


void onewire__thread__run(void) {
    VT_BEGIN(onewire__thread, onewire__thread__ip);

    onewire__thread__reset_bus();
    // wait until bitbang thread finishes reset pulse.
    VT_YIELD(onewire__thread, onewire__thread__ip);

    do {
        onewire__thread__exchange_byte(*onewire__thread__tx__ptr++);
        VT_YIELD(onewire__thread, onewire__thread__ip);
    }
    while (--onewire__thread__rx__remaining);

    while (onewire__thread__rx__remaining--) {
        onewire__thread__exchange_byte(0xFF);
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
