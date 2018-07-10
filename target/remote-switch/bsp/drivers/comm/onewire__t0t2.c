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
// Bus is read and T2 stopped (if realtime requirements are not met) at 15uS in T2OVF interrupt handler.
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
// Bus is read and T2 stopped (if realtime requirements are not met) at 69uS in T2OVF interrupt handler.
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
// Bus is read and T2 stopped (if realtime requirements are not met) at 552uS in T2OVF interrupt handler.
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
// 1-wire thread
// Handles one 1-wire transaction.
// -----------------------------------------------------------------------------

/** Alive flag */
#if defined(ONEWIRE__THREAD__ALIVE__HOST) && defined(ONEWIRE__THREAD__ALIVE__BIT)
DEFINE_BITVAR(onewire__thread__alive, ONEWIRE__THREAD__ALIVE__HOST, ONEWIRE__THREAD__ALIVE__BIT);
#else
volatile uint8_t onewire__thread__alive;
DEFINE_BITVAR(onewire__thread__alive, onewire__thread__alive, 0);
#endif


/** TX data pointer */
#ifdef ONEWIRE__THREAD__TX__PTR__REG
register uint8_t* onewire__thread__tx__ptr asm(QUOTE(ONEWIRE__THREAD__TX__PTR__REG));
#else
volatile uint8_t* onewire__thread__tx__ptr;
#endif

void onewire__thread__tx__ptr__set(uint8_t * const ptr) {
    onewire__thread__tx__ptr = ptr;
}


/** Remaining TX data length */
volatile uint8_t onewire__thread__tx__remaining;

void onewire__thread__tx__remaining__set(const uint8_t value) {
    onewire__thread__tx__remaining = value;
}


/** RX data pointer */
#ifdef ONEWIRE__THREAD__RX__PTR__REG
register uint8_t* onewire__thread__rx__ptr asm(QUOTE(ONEWIRE__THREAD__RX__PTR__REG));
#else
volatile uint8_t* onewire__thread__rx__ptr;
#endif

void onewire__thread__rx__ptr__set(uint8_t * const ptr) {
    onewire__thread__rx__ptr = ptr;
}


/** Remaining RX data length */
volatile uint8_t onewire__thread__rx__remaining;

void onewire__thread__rx__remaining__set(const uint8_t value) {
    onewire__thread__rx__remaining = value;
}


/** Data exchanged */
#ifdef ONEWIRE__THREAD__DATA__REG
register uint8_t onewire__thread__data asm(QUOTE(ONEWIRE__THREAD__DATA__REG));
#else
volatile uint8_t onewire__thread__data;
#endif

void onewire__thread__data__set(const uint8_t data) {
    onewire__thread__data = data;
}

uint8_t onewire__thread__data__get(void) {
    asm volatile("" :"+r"(onewire__thread__data));
    return onewire__thread__data;
}

/** Loads onewire__thread__data with the next byte from TX buffer */
void onewire__thread__data__load(void) {
#if defined(ONEWIRE__THREAD__TX__PTR__REG) && ONEWIRE__THREAD__TX__PTR__REG==26
    LD_XPLUS(onewire__thread__data, onewire__thread__tx__ptr);
#elif defined(ONEWIRE__THREAD__TX__PTR__REG) && ONEWIRE__THREAD__TX__PTR__REG==28
    LD_YPLUS(onewire__thread__data, onewire__thread__tx__ptr);
#elif defined(ONEWIRE__THREAD__TX__PTR__REG) && ONEWIRE__THREAD__TX__PTR__REG==30
    LD_ZPLUS(onewire__thread__data, onewire__thread__tx__ptr);
#elif defined(ONEWIRE__THREAD__TX__PTR__REG)
    LD_ZPLUS(onewire__thread__data, onewire__thread__tx__ptr);
#else
    onewire__thread__data = *onewire__thread__tx__ptr++;
#endif
}


/** Stores onewire__thread__data into RX buffer */
void onewire__thread__data__store(void) {
#if defined(ONEWIRE__THREAD__RX__PTR__REG) && ONEWIRE__THREAD__RX__PTR__REG==26
    STORE_XPLUS(onewire__thread__rx__ptr, onewire__thread__data);
#elif defined(ONEWIRE__THREAD__RX__PTR__REG) && ONEWIRE__THREAD__RX__PTR__REG==28
    STORE_YPLUS(onewire__thread__rx__ptr, onewire__thread__data);
#elif defined(ONEWIRE__THREAD__RX__PTR__REG) && ONEWIRE__THREAD__RX__PTR__REG==30
    STORE_ZPLUS(onewire__thread__rx__ptr, onewire__thread__data);
#elif defined(ONEWIRE__THREAD__RX__PTR__REG)
    STORE_PLUS_VIA_Z(onewire__thread__rx__ptr, onewire__thread__data);
#else
    *onewire__thread__rx__ptr++ = onewire__thread__data;
#endif
}


/** Remaining number of bits to render */
#ifdef ONEWIRE__THREAD__BIT_COUNT__REG
register uint8_t onewire__thread__bit_count asm(QUOTE(ONEWIRE__THREAD__BIT_COUNT__REG));
#else
volatile uint8_t onewire__thread__bit_count;
#endif

/** Reload value (8) for onewire__thread__bit_count */
#ifdef ONEWIRE__THREAD__BIT_COUNT_MAX__REG
register uint8_t onewire__thread__bit_count_max asm(QUOTE(ONEWIRE__THREAD__BIT_COUNT_MAX__REG));
#endif

/** Initializes onewire__thread__bit_count_max to 8 (if available) */
void onewire__thread__bit_count__init(void) {
#if defined(ONEWIRE__THREAD__BIT_COUNT__REG) && defined(ONEWIRE__THREAD__BIT_COUNT_MAX__REG)
    onewire__thread__bit_count_max = 8;
#endif
}

void onewire__thread__bit_count__reload(void) {
#if defined(ONEWIRE__THREAD__BIT_COUNT__REG) && defined(ONEWIRE__THREAD__BIT_COUNT_MAX__REG)
    onewire__thread__bit_count = onewire__thread__bit_count_max;
#else
    onewire__thread__bit_count = 8;
#endif
}


/** Instruction pointer */
#ifdef ONEWIRE__THREAD__IP__REG
register void* onewire__thread__ip asm(QUOTE(ONEWIRE__THREAD__IP__REG));
#else
volatile void *onewire__thread__ip;
#endif


/** CRC of RX data */
volatile uint8_t onewire__thread__crc;

/** Initializes CRC of received data */
void onewire__thread__crc__set(const uint8_t crc) {
    onewire__thread__crc = crc;
}

/** Returns CRC of received data */
uint8_t onewire__thread__crc__get(void) {
    return onewire__thread__crc;
}


/** Initializes the thread */
void onewire__thread__init(void) {
    __asm__ __volatile__( "onewire__thread__init:");
    onewire__thread__bit_count__init();    
}

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
    return (bool)timer0__overflow__interrupt__pending__get();
}

/** Generates 0->1 transition */
ISR(timer2__compare_a__interrupt__VECTOR, ISR_NAKED) {
    onewire__bus__set(1);
    reti();
}

/** Reads the bit value from the bus */
ISR(timer2__overflow__interrupt__VECTOR, ISR_NAKED) {
    // r0 is clobbered (assume that is used only in interrupt handlers, than it's ok)
    asm volatile("in r0, %0\n\r" :: "I"(_SFR_IO_ADDR(SREG)));
    if (onewire__bus__get()) onewire__thread__data |= 0x80;
    asm volatile("out %0, r0\n\r" :: "I"(_SFR_IO_ADDR(SREG)));
    reti();
}


/**
 * Reset 1-wire bus.
 * The result is available via onewire__bitbang_thread__data__get().
 * If presence pulse is generated, onewire__thread__data will be false.
 */
void onewire__thread__reset_bus(void) {
    onewire__bus__set(0);
    timer2__compare_a__interrupt__enable();
    timer2__overflow__interrupt__enable();
    timer2__value__set(256 - ONEWIRE__BIT_FORM_TIMER__RESET_READ_TIME);
    timer2__compare_a__value__set(
        256 - ONEWIRE__BIT_FORM_TIMER__RESET_READ_TIME + ONEWIRE__BIT_FORM_TIMER__RESET_DRIVE_HIGH_TIME);
    timer2__conf__set(ONEWIRE__BIT_FORM_TIMER__SLOW_CONF);

    timer0__value__set(256 - ONEWIRE__BIT_SPAN_TIMER__SLOW_CONF_TIMEOUT);
    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__SLOW_CONF);
    onewire__thread__data = 0;  // explain why set to 0
}


/**
 * 1-wire thread function.
 * Invoked multiple times to perform transaction on the bus until the thread is not alive.
 * Other interrupts in the system should not take much time (say, less than 3uS) not to skrew up 1-wire timings.
 */
void onewire__thread__run(void) {
    VT_BEGIN(onewire__thread, onewire__thread__ip);

    timer0__overflow__interrupt__pending__clear(); // reset pulse has just finished
    onewire__thread__data = 0;

    timer2__compare_a__value__set(
        256 - ONEWIRE__BIT_FORM_TIMER__WRITE1_READ_TIME + ONEWIRE__BIT_FORM_TIMER__WRITE1_DRIVE_HIGH_TIME);
    timer2__conf__set(ONEWIRE__BIT_FORM_TIMER__FAST_CONF);


    timer0__conf__set(ONEWIRE__BIT_SPAN_TIMER__FAST_CONF);
    timer2__overflow__interrupt__disable();
    VT_MARK(onewire__thread, SENDING);
    do {
        onewire__thread__data__load();
        onewire__thread__bit_count__reload();
        do {
            uint8_t start_value = 256 - ONEWIRE__BIT_FORM_TIMER__WRITE0_READ_TIME;
            if (0x01 & onewire__thread__data) {
                start_value = 256 - ONEWIRE__BIT_FORM_TIMER__WRITE1_READ_TIME;
            }
            onewire__bus__set(0);
            timer2__value__set(start_value);
            timer0__value__set(256 - ONEWIRE__BIT_SPAN_TIMER__FAST_CONF_TIMEOUT);
            VT_YIELD_WITH_MARK(onewire__thread, onewire__thread__ip, BIT_SENT);
            timer0__overflow__interrupt__pending__clear();
            onewire__thread__data >>= 1;
        }
        while (--onewire__thread__bit_count);
    }
    while (--onewire__thread__tx__remaining);
    timer2__overflow__interrupt__enable();

    VT_MARK(onewire__thread, RECEIVING);
    if (onewire__thread__rx__remaining) {
        do {
            onewire__thread__bit_count__reload();
            do {
                onewire__thread__data >>= 1;
                onewire__bus__set(0);
                timer2__value__set(256 - ONEWIRE__BIT_FORM_TIMER__WRITE1_READ_TIME);
                timer0__value__set(256 - ONEWIRE__BIT_SPAN_TIMER__FAST_CONF_TIMEOUT);
                VT_YIELD_WITH_MARK(onewire__thread, onewire__thread__ip, BIT_RECEIVED);
                timer0__overflow__interrupt__pending__clear();
            }
            while (--onewire__thread__bit_count);

            onewire__thread__data__store();
#if defined(ONEWIRE__THREAD__CHECK_CRC) && ONEWIRE__THREAD__CHECK_CRC == 1
            onewire__thread__crc__set(crc8_ow_update(onewire__thread__crc, onewire__thread__data));
#endif
        }
        while (--onewire__thread__rx__remaining);
    }
    VT_MARK(onewire__thread, STOPPING);

    timer0__conf__set(TIMER0_CONF_DEFAULT);
    timer2__conf__set(TIMER2_CONF_DEFAULT);

    timer2__overflow__interrupt__disable();
    timer2__compare_a__interrupt__disable();
    onewire__thread__alive__set(false);
    VT_END(onewire__thread);
}


// -----------------------------------------------------------------------------
// 1-wire client
// -----------------------------------------------------------------------------

/**
 * Perform 1-wire transaction.
 */
void onewire__transaction(void) {
    onewire__thread__data__set(0);  // start with 0; received 1 bits are ORed with it
    onewire__thread__crc__set(0);
    onewire__thread__start();
    onewire__thread__reset_bus();
}
