#include "comm.h"

#include <avr/interrupt.h>
#include <cpu/avr/twi.h>
#include "drivers/comm/twi_slave.h"

void comm__init(void) {
    PORTC |= ((1<<PINC4) | (1<<PINC5));
    TWDR = 0x00;            // Default Initial Value

    twi__slave_address__set(TWI__SLAVE__ADDRESS);
    twi__slave__thread__init();
}

void comm__start(void) {
    twi__slave__thread__start();
}


ISR(TWI_vect) {
    twi__slave__thread__run();
}
