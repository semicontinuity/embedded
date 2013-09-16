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
// onewire__bitbang_thread:
//   description: thread that handles transmission and reception of bits.
//   parameters:
//     ONEWIRE__BITBANG_THREAD__TIMER__CONF: Timer 2 configuration
//     ONEWIRE__BITBANG_THREAD__TIMER__TIME_QUANTUM: Timeout value for 1 TQ
// onewire__thread:
//   description: handles frame transmission and reception.
// =============================================================================

#include "onewire.h"

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
// 1-wire bit-bang thread.
// Receives and transmits individual bits (to reduce ISR stack overhead).
// -----------------------------------------------------------------------------
/** Flag that indicates that the thread is running */
volatile uint8_t onewire__bitbang_thread__running;
/** Instruction pointer */
volatile void *onewire__bitbang_thread__ip;
/** Byte to be transmitted */
volatile uint8_t onewire__bitbang_thread__data_out;
/** Byte received */
volatile uint8_t onewire__bitbang_thread__data_in;


uint8_t onewire__bitbang_thread__is_running(void) {
    return onewire__bitbang_thread__running;
}


void onewire__bitbang_thread__init(void) {    
    timer2__compare_a__interrupt__enabled__set(1);
}


void onewire__bitbang_thread__shutdown(void) {
    timer2__compare_a__interrupt__enabled__set(0);
}


void onewire__bitbang_thread__start(void) {
    timer2__value__set(0);
    timer2__switch_conf(TIMER2_CONF_DEFAULT, ONEWIRE__BITBANG_THREAD__TIMER__CONF);
    onewire__bitbang_thread__running = 1;
}


void onewire__bitbang_thread__stop(void) {
    timer2__switch_conf(ONEWIRE__BITBANG_THREAD__TIMER__CONF, TIMER2_CONF_DEFAULT);
    onewire__bitbang_thread__running = 0;
}


void onewire__bitbang_thread__timeout__set(const uint8_t tq) {
    timer2__compare_a__value__set(tq);
}


/**
 * Called when bitbang_thread thread timeout expired (certain amount of time quants programmed).
 */
ISR(timer2__compare_a__interrupt__VECTOR) {

    VT_BEGIN(onewire__bitbang_thread, onewire__bitbang_thread__ip);

    // -------------------------------------------------------------------------
    VT_MARK(onewire__bitbang_thread, RECEIVE);
    // 1 for 1 TQ
    onewire__bitbang_thread__timeout__set(1);
    onewire__bus__set(1);
    VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    // sample bit
    uint8_t data = onewire__bitbang_thread__data_in >> 1;
    if (onewire__bus__get()) data |= 0x80;
    onewire__bitbang_thread__data_in = data;
    // 1 for 7 TQ (bus is 1 already)
    onewire__bitbang_thread__timeout__set(7);
    goto done;

    // -------------------------------------------------------------------------
    VT_MARK(onewire__bitbang_thread, SEND_1TQ_1);
    onewire__bitbang_thread__timeout__set(1);
    onewire__bus__set(1);
    goto done;

    // -------------------------------------------------------------------------
    VT_MARK(onewire__bitbang_thread, SEND_8TQ_1);
    onewire__bitbang_thread__timeout__set(8);
    onewire__bus__set(1);
    goto done;

    // -------------------------------------------------------------------------
done:
    VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    onewire__bitbang_thread__stop();

    // -------------------------------------------------------------------------
    VT_END(onewire__bitbang_thread);
}


// -----------------------------------------------------------------------------
// 1-wire thread
// -----------------------------------------------------------------------------

/** Flag that indicates that the thread is running */
volatile uint8_t onewire__thread__running;

/** Instruction pointer */
volatile void *onewire__thread__ip;

/** TX data pointer */
volatile uint8_t *onewire__thread__tx__ptr;

/** Remaining TX data length */
volatile uint8_t *onewire__thread__tx__remaining;

/** RX data pointer */
volatile uint8_t *onewire__thread__rx__ptr;

/** Remaining RX data length */
volatile uint8_t *onewire__thread__rx__remaining;


void onewire__thread__start(void) {
}


void onewire__thread__stop(void) {
}


void onewire__thread__run(void) {
    VT_BEGIN(onewire__thread, onewire__thread__ip);
    VT_END(onewire__thread);
}


// -----------------------------------------------------------------------------
// 1-wire client
// -----------------------------------------------------------------------------

void onewire__init(void) {    
    onewire__bitbang_thread__init();
}


void onewire__shutdown(void) {    
    onewire__bitbang_thread__shutdown();
}

/**
 * Send bit 0.
 *
 * --+               +-+-
 *   |0 0 0 0 0 0 0 0|1
 *   +-+-+-+-+-+-+-+-+
 *
 * Waveform: 0 for 8 TQ (1 TQ = 8ms), then guard time (stop bit) for 1 TQ.
 */
void onewire__send_bit_0(void) {
    // generate 0 for 8 TQ    
    onewire__bitbang_thread__timeout__set(8);
    onewire__bus__set(0);

    // after timeout, proceed at SEND_1TQ_1 that will generate guard time for 1 TQ.
    VT_SEEK(onewire__bitbang_thread, onewire__bitbang_thread__ip, SEND_1TQ_1);
    onewire__bitbang_thread__start();
    // poll onewire__bitbang_thread__is_running() for the end of operation
}


/**
 * Send bit 1.
 *
 * --+ +-+-+-+-+-+-+-+---
 *   |0|1 1 1 1 1 1 1 1
 *   +-+             +
 *
 * Waveform: 0 for 1 TQ (1 TQ = 8ms), then 1 for 7 TQ + guard time (stop bit) for 1 TQ.
 */
void onewire__send_bit_1(void) {
    // generate 0 for 1 TQ    
    onewire__bitbang_thread__timeout__set(1);
    onewire__bus__set(0);

    // after timeout, proceed at SEND_8TQ_1 that will generate guard time for 1 TQ.
    VT_SEEK(onewire__bitbang_thread, onewire__bitbang_thread__ip, SEND_8TQ_1);
    onewire__bitbang_thread__start();
    // poll onewire__bitbang_thread__is_running() for the end of operation
}


/**
 * Receive bit.
 *
 * --+ +-+-+-+-+-+-+-+---
 *   |0|1 1 1 1 1 1 1 1
 *   +-+ S           +
 *
 * Waveform: 0 for 1 TQ (1 TQ = 8ms), then 1 for 1 TQ, sample bus, 1 for 6 TQ + guard time (stop bit) for 1 TQ.
 */
void onewire__receive_bit(void) {    
    // generate 0 for 1 TQ
    onewire__bitbang_thread__timeout__set(1);
    onewire__bus__set(0);

    // after timeout, proceed at RECEIVE.
    VT_SEEK(onewire__bitbang_thread, onewire__bitbang_thread__ip, RECEIVE);
    onewire__bitbang_thread__start();
    // poll onewire__bitbang_thread__is_running() for the end of operation
}
