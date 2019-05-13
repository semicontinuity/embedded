// =============================================================================
// Receives 4-byte messages via I2C with raw color data (1 byte per column)
// and renders 1-bit colors on LEDS (3 bits RGB + 3 bits RGB + 1 bit button LED)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <cpu/avr/twi.h>
#include "twi_slave_callbacks.h"

#include "data.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
    data__leds__put_position_reset();
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
//    twi__continue(data__leds__put(value), false);

    data__leds__put(value);
    twi__continue(/*false*/true, false);
    // TODO: check that space remains for just 1 byte and invoke twi__continue(false, false);
}
