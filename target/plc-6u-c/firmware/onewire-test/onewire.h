// =============================================================================
// Driver for OneWire bus on the specified ONEWIRE pin.
// Implemented with bit-banging and timer 2.
// Logical 1 is driven by external pull-up resistor
// (pin is switched to input).
// =============================================================================

#include <stdint.h>
#include <stdbool.h>


/** Allow thread to be scheduled */
void onewire__thread__start(void);

/** Disallow thread to be scheduled */
void onewire__thread__stop(void);

/** Check whether the thread is running */
bool onewire__thread__is_running(void);

/** Check whether the thread can be scheduled */
bool onewire__thread__is_runnable(void);

/** Thread function */
void onewire__thread__run(void);


void onewire__init(void);

void onewire__shutdown(void);

/**
 * Perform 1-wire transaction.
 * Poll onewire__thread__is_running() for completion status.
 */
void onewire__command(uint8_t command_length, uint8_t response_length, uint8_t *command, uint8_t *response);
