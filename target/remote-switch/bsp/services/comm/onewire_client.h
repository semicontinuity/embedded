// =============================================================================
// 1-wire client service: transaction setup and execution.
// =============================================================================
#ifndef SERVICES__COMM__ONEWIRE_CLIENT_H
#define SERVICES__COMM__ONEWIRE_CLIENT_H

#include <stdint.h>
#include "drivers/comm/onewire.h"

/**
 * Setup 1-wire transaction.
 */
void onewire__setup_transaction(uint8_t command_length, uint8_t response_length, uint8_t *command, uint8_t *response);

/**
 * Perform 1-wire transaction.
 * Poll onewire__thread__is_alive() for completion status.
 */
void onewire__transaction(void);

#endif
