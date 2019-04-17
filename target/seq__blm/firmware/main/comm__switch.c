#include "comm.h"

#include <avr/interrupt.h>
#include "I2CSlave.h"


void comm__init(void) {
    // set received/requested callbacks
//    I2C_setCallbacks(twi__slave__on_data_byte_received, I2C_requested);
//    I2C_setMoreCallbacks(twi__slave__on_data_reception_finished, twi__slave__on_data_reception_aborted);

    // init I2C
    I2C_init(TWI__SLAVE__ADDRESS);
}

void comm__start(void) {
}
