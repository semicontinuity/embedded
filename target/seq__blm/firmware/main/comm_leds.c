// =============================================================================
// Receives 4-byte messages via I2C with color data.
// Datagram format: {button index: 1 byte + 3-byte color value}
// =============================================================================

#include <cpu/avr/twi.h>
#include "twi_slave_callbacks.h"

#include "leds.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>


#ifdef COMM_LEDS__DATA__INDEX__REG
register volatile uint8_t comm_leds__data__index asm(QUOTE(COMM_LEDS__DATA__INDEX__REG));
#else
volatile uint8_t comm_leds__data__index;
#endif


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
    comm_leds__data__index = 0;
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
    if (comm_leds__data__index == 0) {
        // LED index byte
        leds__data__position__set(value + value + value);
    } else {
        leds__data__put(value);
    }

    if (++comm_leds__data__index == 4) {
        leds__refresh();
    }

    twi__continue(/*false*/true, false);
    // TODO: check that space remains for just 1 byte and invoke twi__continue(false, false);
}
