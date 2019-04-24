#include <util/twi.h>
#include <avr/interrupt.h>

#include "I2CSlave.h"
#include "twi_slave_callbacks.h"

//static void (*I2C_recv)(uint8_t);
//
//static void (*I2C_req)(void);
//
//static void (*I2C_finished)(void);
//
//static void (*I2C_aborted)(void);

//void I2C_setCallbacks(void (*recv)(uint8_t), void (*req)(void)) {
//    I2C_recv = recv;
//    I2C_req = req;
//}
//
//void I2C_setMoreCallbacks(void (*finished)(void), void (*aborted)(void)) {
//    I2C_finished = finished;
//    I2C_aborted = aborted;
//}


void I2C_init(uint8_t address) {
    cli();
    // load address into TWI address register
    TWAR = address << 1;
    // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
    TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
    sei();
}

void I2C_stop(void) {
    // clear acknowledge and enable bits
    cli();
    TWCR = 0;
    TWAR = 0;
    sei();
}

ISR(TWI_vect) {
    uint8_t value;

//    console__print_byte_as_hex(TWSR);
    switch (TW_STATUS) {
    case TW_SR_DATA_ACK:

        // received data from master, call the receive callback
        value = TWDR;
//        console__print(':');
//        console__print_byte_as_hex(value);
        twi__slave__on_data_byte_received(value);
//      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
        break;
    case TW_ST_SLA_ACK:
    case TW_ST_DATA_ACK:

        // master is requesting data, call the request callback
        twi__slave__on_data_byte_requested();
//      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
        break;
//    case TW_ST_DATA_ACK:
        // master is requesting data, call the request callback
//      I2C_req();
//      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
//      break;
    case TW_BUS_ERROR:
        // some sort of erroneous state, prepare TWI to be readdressed
        TWCR = 0;
//      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
        twi__slave__on_data_reception_aborted();
        break;
    default:
        twi__slave__on_data_reception_finished/*I2C_finished*/();
        break;
//    default:
//      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
//      break;
    }
    TWCR = (1 << TWIE) | (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
}
