//#include "drivers/out/led1.h"
#include "drivers/comm/ws2812b.h"

#include <compat/twi.h>

#define I2CSLAVE_ADDR       0x11*2

uint8_t data[3];
uint8_t *data_ptr = data;

ISR(TWI_vect) {
    // Get TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
    uint8_t twi_status = (uint8_t) (TWSR & 0xF8);

    switch (twi_status) {
    case TW_SR_SLA_ACK: // 0x60: SLA+W received, ACK returned
        break;

    case TW_SR_DATA_ACK:    // 0x80: data received, ACK returned
//        *data_ptr++ = TWDR;
        break;

    case TW_ST_SLA_ACK: // 0xA8: SLA+R received, ACK returned
    case TW_ST_DATA_ACK:    // 0xB8: data transmitted, ACK received
        break;

    case TW_ST_DATA_NACK:   // 0xC0: data transmitted, NACK received
    case TW_ST_LAST_DATA:   // 0xC8: last data byte transmitted, ACK received
        break;

    case TW_SR_STOP:    // 0xA0: stop or repeated start condition received while selected
//        ws2812_sendarray_mask(data, 3, _BV(1));

    case TW_BUS_ERROR:  // 0x00: illegal start or stop condition
    default:
//        data_ptr = data;
        break;
    }
    // Clear TWINT Flag
    TWCR |= (1 << TWINT) | (1 << TWEA);
}


int main(void) {
    //led1__init();

    // TWI Pull UP
    PORTC |= ((1 << PINC4) | (1 << PINC5));

    // Initial I2C Slave
    TWAR = I2CSLAVE_ADDR & 0xFE;    // Set I2C Address, Ignore I2C General Address 0x00
    TWDR = 0x00;            // Default Initial Value

    // Start Slave Listening: Clear TWINT Flag, Enable ACK, Enable TWI, TWI Interrupt Enable
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);

    // Enable Global Interrupt
    sei();

    while (1) {

    }
}