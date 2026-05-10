// =============================================================================
// 1-wire client service: transaction execution.
// =============================================================================

#include "services/comm/onewire_client.h"

/**
 * Setup 1-wire transaction.
 */
void inline __attribute__((always_inline)) onewire__setup_transaction(uint8_t command_length, uint8_t response_length, uint8_t *command, uint8_t *response) {
    onewire__thread__tx__ptr__set(command);
    onewire__thread__tx__remaining__set(command_length);
    onewire__thread__rx__ptr__set(response);
    onewire__thread__rx__remaining__set(response_length);
}

/**
 * Perform 1-wire transaction.
 */
void onewire__transaction(void) {
    onewire__thread__data__set(0);  // start with 0; received 1 bits are ORed with it
    onewire__thread__crc__set(0);
    onewire__thread__start();
    onewire__thread__reset_bus();
}
