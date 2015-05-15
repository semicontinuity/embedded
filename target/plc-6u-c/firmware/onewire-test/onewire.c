// =============================================================================
// 1-wire client.
// Implemented with bit-banging and timer 2:
//
// Theory of operation:
// --------------------
// The bit waveform is divided into 32 quantums (TQ), 1 Time quantum is ~2 uS
// The bit is started with 1->0 transition.
// For Write0 and Read0 operations, the bus is held low for 2TQ (~4uS)
// For Read operations, the bus is read at 6TQ (~12uS)
// The total bit time (end of bit) is 32TQ ~= 64uS (>~ 60uS as per spec).
// After the bit, 1TQ of guard time is inserted (~2uS, > 1uS per spec).

// ---+   +-----------------------------------------------------------+-+
//    |   |      read                                                end
//    +---+       *
//    0   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30  32 33
//
// Reset pulse and presence pulse handling is implemented using overflow interrupt.
//
// Sub-modules:
// ------------
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
#include "onewire__bus.h"

#include "util/crc8_ow.h"
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/timer2.h"

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>


#ifndef QUOTE
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif


// -----------------------------------------------------------------------------
// 1-wire timer.
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
// 1-wire reset thread.
// Generates reset pulse and checks the presence pulse
// -----------------------------------------------------------------------------


ISR(timer2__overflow__interrupt__VECTOR) {
}

// -----------------------------------------------------------------------------
// 1-wire bit-bang thread.
// Receives and transmits individual bits
// -----------------------------------------------------------------------------

/** Thread instruction pointer */
#ifdef ONEWIRE__BITBANG_THREAD__IP__REG
register void* onewire__bitbang_thread__ip asm(QUOTE(ONEWIRE__BITBANG_THREAD__IP__REG));
#else
volatile void *onewire__bitbang_thread__ip;
#endif

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


void onewire__bitbang_thread__seek_read(void) {
    VT_SEEK(onewire__bitbang_thread, onewire__bitbang_thread__ip, READ);
}

void onewire__bitbang_thread__seek_write(void) {
    VT_SEEK(onewire__bitbang_thread, onewire__bitbang_thread__ip, WRITE);
}

void onewire__bitbang_thread__seek_reset(void) {
    VT_SEEK(onewire__bitbang_thread, onewire__bitbang_thread__ip, RESET);
}


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


/**
 * Called when 1-wire timer timeout expired (certain amount of time quants programmed).
 */
ISR(timer2__compare_a__interrupt__VECTOR) {
    VT_BEGIN(onewire__bitbang_thread, onewire__bitbang_thread__ip);

    // -------------------------------------------------------------------------
    VT_MARK(onewire__bitbang_thread, RESET);                        // at the end of RESET pulse

    onewire__bus__set(1);                                           // end RESET pulse
    onewire__timer__timeout__set(35*ONEWIRE__TIMER__TIME_QUANTUM);  // read presence pulse in ~70us
    VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    onewire__bitbang_thread__data = (uint8_t) onewire__bus__get();
    onewire__timer__clear();                                        // start from 0, ~70ms delay
    VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    onewire__bitbang_thread__stop();
    VT_BREAK(onewire__bitbang_thread);

    // -------------------------------------------------------------------------
    do {
        // generate 0 for 1 TQ (2mS)
        onewire__bus__set(0);
        onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
        onewire__timer__clear();
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip); // wait until T=2mS

        VT_MARK(onewire__bitbang_thread, WRITE);
        uint8_t data = onewire__bitbang_thread__data;
        if (data & 0x01) onewire__bus__set(1);  // optimize with T bit?
        onewire__bitbang_thread__data = data >> 1;

        onewire__timer__timeout__set(30*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip); // wait until T=60uS

        // produce ~2uS inter-bit space
        onewire__bus__set(1);
        onewire__timer__timeout__set(32*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip); // wait until T=64uS
    }
    while (--onewire__bitbang_thread__bit_count);
    VT_BREAK(onewire__bitbang_thread);

    // -------------------------------------------------------------------------
    do {
        // generate 0 for 1 TQ (2mS)
        onewire__bus__set(0);
        onewire__timer__timeout__set(1*ONEWIRE__TIMER__TIME_QUANTUM);
        onewire__timer__clear();
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip); // wait until T=2mS

        VT_MARK(onewire__bitbang_thread, READ);
        onewire__bus__set(1);                   // end 2ms low-level pulse from master

        onewire__timer__timeout__set(6*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip); // wait until T=12mS

        // sample bit
//        uint8_t data = onewire__bitbang_thread__data >> 1;
//        if (onewire__bus__get()) data |= 0x80;  // optimize with T bit?
//        if (onewire__bus__get()) ORI(data, 0x80);
//        onewire__bitbang_thread__data = data;
//        if (onewire__bus__get()) ORI(onewire__bitbang_thread__data, 0x80);
        LSR(onewire__bitbang_thread__data);
        if (onewire__bus__get()) onewire__bitbang_thread__data |= 0x80;

        // wait until T=64uS (inter-bit space included)
        onewire__timer__timeout__set(32*ONEWIRE__TIMER__TIME_QUANTUM);
        VT_YIELD(onewire__bitbang_thread, onewire__bitbang_thread__ip);
    }
    while (--onewire__bitbang_thread__bit_count);

    VT_END(onewire__bitbang_thread);
    // -------------------------------------------------------------------------

    onewire__bitbang_thread__stop();
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
    onewire__bitbang_thread__seek_write();
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
    onewire__bitbang_thread__seek_read();
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
    onewire__bitbang_thread__seek_reset();
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
