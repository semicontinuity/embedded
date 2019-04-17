#include "drivers/out/led1.h"

#include <compat/twi.h>
#include <avr/interrupt.h>

#define I2CSLAVE_ADDR       0x4E

//#define PORT_DDR            0xB0 // PORTB Settings
//#define PORT_IN             0xB1 // Get PINB
//#define PORT_OUT            0xB2 // Set PORTB

uint8_t regaddr; // Store the Requested Register Address
uint8_t regdata; // Store the Register Address Data

void i2c_slave_action(unsigned char rw_status) {
    led1__toggle();
}

ISR(TWI_vect) {
    static uint8_t i2c_state;
    uint8_t twi_status;

    // Disable Global Interrupt
    cli();

    // Get TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
    twi_status = (uint8_t) (TWSR & 0xF8);

    switch (twi_status) {
    case TW_SR_SLA_ACK: // 0x60: SLA+W received, ACK returned
        i2c_state = 0;    // Start I2C State for Register Address required
        break;

    case TW_SR_DATA_ACK:    // 0x80: data received, ACK returned
        if (i2c_state == 0) {
            regaddr = TWDR; // Save data to the register address
            i2c_state = 1;
        } else {
            regdata = TWDR; // Save to the register data
            i2c_state = 2;
        }
        break;

    case TW_SR_STOP:    // 0xA0: stop or repeated start condition received while selected
        if (i2c_state == 2) {
            i2c_slave_action(1);    // Call Write I2C Action (rw_status = 1)
            i2c_state = 0;      // Reset I2C State
        }
        break;

    case TW_ST_SLA_ACK: // 0xA8: SLA+R received, ACK returned
    case TW_ST_DATA_ACK:    // 0xB8: data transmitted, ACK received
        if (i2c_state == 1) {
            i2c_slave_action(0);    // Call Read I2C Action (rw_status = 0)
            TWDR = regdata;     // Store data in TWDR register
            i2c_state = 0;      // Reset I2C State
        }
        break;

    case TW_ST_DATA_NACK:   // 0xC0: data transmitted, NACK received
    case TW_ST_LAST_DATA:   // 0xC8: last data byte transmitted, ACK received
    case TW_BUS_ERROR:  // 0x00: illegal start or stop condition
    default:i2c_state = 0;  // Back to the Begining State
    }
    // Clear TWINT Flag
    TWCR |= (1 << TWINT);
    // Enable Global Interrupt
    sei();
}


int main(void) {
    led1__init();

    // TWI Pull UP
    PORTC |= ((1 << PINC4) | (1 << PINC5));

    // Initial I2C Slave
    TWAR = I2CSLAVE_ADDR & 0xFE;    // Set I2C Address, Ignore I2C General Address 0x00
    TWDR = 0x00;            // Default Initial Value

    // Start Slave Listening: Clear TWINT Flag, Enable ACK, Enable TWI, TWI Interrupt Enable
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);

    // Enable Global Interrupt
    sei();

    // Initial Variable Used
    regaddr = 0;
    regdata = 0;

    while (1) {

    }
}