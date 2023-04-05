// =============================================================================
// On I2C Read request, responds with the 1-byte keyboard event, or 0 if none
// =============================================================================

#include <cpu/avr/asm.h>

#include "services/tx_ring_buffer.h"

#include <cpu/avr/twi.h>
#include "twi_slave__handler__callbacks.h"


// Handler for TWI Slave callback
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    __asm__ __volatile__("twi__slave__on_data_byte_requested:");
    uint8_t value = 0;
    if (tx_ring_buffer__is_readable()) {
        value = tx_ring_buffer__get();
    }
    twi__data__set(value);
    twi__continue(/*false*/true, false);
}
