#include "comm.h"

#include <avr/interrupt.h>
#include "drivers/comm/twi_slave_callbacks.h"
#include "I2CSlave.h"

// comm callbacks
// -----------------------------------------------------------------------------

volatile uint8_t *comm__rx__ptr;
uint8_t comm__data[16*3];


void twi__slave__on_data_byte_received(const uint8_t value) {
    *comm__rx__ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    comm__rx__ptr = comm__data;
}

void twi__slave__on_data_reception_aborted(void) {
    comm__rx__ptr = comm__data;
}

void twi__slave__on_data_byte_requested(void) {
    I2C_transmitByte(0xAA);
}


void comm__init(void) {
    // set received/requested callbacks
//    I2C_setCallbacks(twi__slave__on_data_byte_received, I2C_requested);
//    I2C_setMoreCallbacks(twi__slave__on_data_reception_finished, twi__slave__on_data_reception_aborted);

    // init I2C
    I2C_init(TWI__SLAVE__ADDRESS);
}

void comm__start(void) {
}
