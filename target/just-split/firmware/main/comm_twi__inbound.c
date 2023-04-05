// =============================================================================
// Places I2C write payload to the leds_bar
// =============================================================================

#include <cpu/avr/twi.h>
#include "twi_slave__handler__callbacks.h"

#include "leds_bar__data.h"
#include <cpu/avr/asm.h>


// Handlers for TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
    leds_bar__data__put_position_reset();
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
    twi__continue(true, false);
    leds_bar__data__put(value);
}
