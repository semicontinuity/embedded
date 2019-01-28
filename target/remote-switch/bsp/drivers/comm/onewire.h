// =============================================================================
// Driver for OneWire bus on the specified ONEWIRE pin.
// Implemented with bit-banging and timer 2.
// Logical 1 is driven by external pull-up resistor
// (pin is switched to input).
// =============================================================================
#ifndef DRIVERS__COMM__ONEWIRE_H
#define DRIVERS__COMM__ONEWIRE_H

#include <stdint.h>
#include <stdbool.h>
#include "util/bitops.h"
#include "cpu/avr/gpio.h"

// Injected bit variables
DECLARE_BITVAR(onewire__thread__alive);

void onewire__thread__tx__ptr__set(uint8_t * const ptr);

void onewire__thread__tx__remaining__set(const uint8_t value);

void onewire__thread__rx__ptr__set(uint8_t * const ptr);

void onewire__thread__rx__remaining__set(const uint8_t value);

void onewire__thread__data__set(const uint8_t data);

void onewire__thread__crc__set(const uint8_t crc);


/** Initializes the thread */
void onewire__thread__init(void);

/** Allow thread to be scheduled */
void onewire__thread__start(void);

/** Disallow thread to be scheduled */
void onewire__thread__stop(void);

/** Check whether the thread is alive */
bool onewire__thread__is_alive(void);

/** Check whether the thread can be scheduled */
bool onewire__thread__is_runnable(void);

/** Thread function */
void onewire__thread__run(void);


/** Check whether the thread can be scheduled */
bool onewire__bitbang_thread__runnable__get(void);

/** Thread function */
void onewire__bitbang_thread__run(void);

/** Callback to be implemented */
void onewire__bitbang_thread__terminated(void);


void onewire__init(void);

void onewire__shutdown(void);

/**
 * Setup 1-wire transaction.
 */
//void onewire__setup_transaction(uint8_t command_length, uint8_t response_length, uint8_t *command, uint8_t *response);
/**
 * Setup 1-wire transaction.
 */
inline void onewire__setup_transaction(uint8_t command_length, uint8_t response_length, uint8_t *command, uint8_t *response) {
    onewire__thread__tx__ptr__set(command);
    onewire__thread__tx__remaining__set(command_length);
    onewire__thread__rx__ptr__set(response);
    onewire__thread__rx__remaining__set(response_length);
}

/**
 * Perform 1-wire transaction.
 * Poll onewire__thread__is_running() for completion status.
 */
void onewire__transaction(void);

/** Returns CRC of received data */
uint8_t onewire__crc__get(void);

#endif
