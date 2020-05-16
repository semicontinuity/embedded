/**
 * Interactive I2C Master console.
 * Supported commands:
 *
 * [AA]?[LL]
 *   Read LL bytes from I2C device with address AA
 * [AA]=[B0B1B2..BN]
 *   Write bytes B0..BN to I2C device with address AA
 * S[AA]
 *   Send SLA+W or SLA+R (Start condition and WRITE AA or READ AA; AA byte contains address and R/W bit)
 * P
 *   Send STOP condition
 * W[XX]
 *   Write byte XX to slave as part of WRITE transaction
 * R
 *   Read byte from slave as part of READ transaction
 *
 * All numbers are in hex format.
 * Addresses used in commands are multiplied by 2!
 */
#include <stdlib.h>

#include "services/console_i2c.h"
#include "services/console.h"
#include "drivers/i2c_master.h"

#include <util/delay.h>
#include "util/parser.h"

#include "drivers/out/led2.h"   // set when start condition sent but stop condition to sent
#include "drivers/out/led3.h"   // set when writing byte
#include "drivers/out/led4.h"   // set when reading byte


#define CONSOLE__I2C__BUFFER_LENGTH 62
uint8_t console__i2c__buffer[CONSOLE__I2C__BUFFER_LENGTH];


void console__i2c__init(void) {
    i2c_init();
}


uint8_t console__i2c__start(void) {
    uint16_t parsed_address_byte = parser__parse_hex_byte(console__input_buffer + 1);   // first char is 'S'
    if ((uint8_t) (parsed_address_byte >> 8U)) {
        return EXIT_FAILURE;
    }
    uint8_t address_byte = (uint8_t) parsed_address_byte;

    led2__set(1);   // indicate START
    if (i2c_start(address_byte)) {
        console__print('N');
    }

    console__print('A');
    console__print('C');
    console__print('K');
    console__println();
    return EXIT_SUCCESS;
}

uint8_t console__i2c__stop(void) {
    i2c_stop();
    led2__set(0);   // indicate STOP
    console__print_ok();
    console__println();
    return EXIT_SUCCESS;
}


uint8_t console__i2c__write_byte(void) {
    uint16_t parsed_byte = parser__parse_hex_byte(console__input_buffer + 1);   // first char is 'W'
    if ((uint8_t) (parsed_byte >> 8U)) {
        return EXIT_FAILURE;
    }
    uint8_t byte_value = (uint8_t) parsed_byte;

    led3__set(1);   // indicate WRITE
    if (i2c_write(byte_value)) {
        console__print('N');
    }
    led3__set(0);

    console__print('A');
    console__print('C');
    console__print('K');
    console__println();
    return EXIT_SUCCESS;
}

uint8_t console__i2c__write_buffer(uint8_t address_byte, uint8_t length) {
    led2__set(1);   // indicate START
    if (i2c_start(address_byte)) {
        i2c_stop();
        return EXIT_FAILURE;
    }

    led3__set(1);
    for (uint16_t i = 0; i < length; i++) {
        if (i2c_write(console__i2c__buffer[i])) {
            i2c_stop();
            return EXIT_FAILURE;
        }
    }
    led3__set(0);

    i2c_stop();
    led2__set(0);   // indicate STOP

    console__print_ok();
    console__println();
    return EXIT_SUCCESS;
}

uint8_t console__i2c__write(void) {
    uint16_t parsed_address_byte = parser__parse_hex_byte(console__input_buffer);   // command starts with address
    if ((uint8_t) (parsed_address_byte >> 8U)) {
        return EXIT_FAILURE;
    }
    uint8_t address_byte = (uint8_t) parsed_address_byte;

    uint8_t *bytes_ptr = console__i2c__buffer;
    uint8_t src_index = 3;  // after '='
    for (;;) {
        if ((uint8_t) src_index >= (uint8_t) console__input_length) {
            break;
        }

        uint8_t c1 = console__input_buffer[src_index++];
        uint8_t c2 = console__input_buffer[src_index++];

        uint16_t parsed_byte = parser__parse_hex_chars(c1, c2);
        if ((uint8_t) (parsed_byte >> 8U)) {
            return EXIT_FAILURE;
        }

        *bytes_ptr++ = (uint8_t) parsed_byte;
    }

    uint8_t length = (uint8_t) (src_index - 3);
    length = length >> 1U;

    return console__i2c__write_buffer(address_byte, length);
}



uint8_t console__i2c__read_ack(void) {
    led4__set(1);   // indicate READ
    uint8_t value  = i2c_read_ack();
    led4__set(0);

    uint16_t hex = formatter__byte_to_hex_chars(value);
    console__print((uint8_t) (hex >> 8U));
    console__print((uint8_t) (hex & 0xFFU));
    console__println();
    return EXIT_SUCCESS;
}

uint8_t console__i2c__read_nack(void) {
    led4__set(1);   // indicate READ
    uint8_t value  = i2c_read_nack();
    led4__set(0);

    uint16_t hex = formatter__byte_to_hex_chars(value);
    console__print((uint8_t) (hex >> 8U));
    console__print((uint8_t) (hex & 0xFFU));
    console__println();
    return EXIT_SUCCESS;
}

/**
 * Read 'length' bytes from I2C slave, having 'address_byte'.
 * All read bytes except the last one are ACKed.
 * @return EXIT_SUCCESS or EXIT_FAILURE; if success, 'length' bytes are placed into console__i2c__buffer.
 */
uint8_t console__i2c__read_buffer(uint8_t address_byte, uint8_t length) {
    led2__set(1);   // indicate START
    if (i2c_start(address_byte)) {
        i2c_stop();
        return EXIT_FAILURE;
    }

    led4__set(1);   // indicate READ
    if (length > 0) {
        if (i2c_receive(address_byte, console__i2c__buffer, length)) {
            i2c_stop();
            return EXIT_FAILURE;
        }
    }
    led4__set(0);

    i2c_stop();
    led2__set(0);   // indicate STOP

    return EXIT_SUCCESS;
}

uint8_t console__i2c__read(void) {
    uint16_t parsed_address_byte = parser__parse_hex_byte(console__input_buffer);   // command starts with address
    if ((uint8_t) (parsed_address_byte >> 8U)) {
        return EXIT_FAILURE;
    }
    uint8_t address_byte = (uint8_t) parsed_address_byte;

    uint16_t parsed_length_byte = parser__parse_hex_byte(console__input_buffer + 3);
    if ((uint8_t) (parsed_length_byte >> 8U)) {
        return EXIT_FAILURE;
    }
    uint8_t length = (uint8_t) parsed_length_byte;

    uint8_t result = console__i2c__read_buffer(address_byte, length);
    if (result == EXIT_SUCCESS) {
        console__print_bytes_as_hex(console__i2c__buffer, length);
        console__println();
    }
    return result;
}


uint8_t console__i2c__detect(void) {
    uint8_t address = 0;
    for (;;) {
        uint8_t result = console__i2c__read_buffer(address << 1U, 1);

        uint16_t hex = formatter__byte_to_hex_chars(address);
        if (result != EXIT_SUCCESS) {
            hex = (uint16_t) (('-' << 8U) | '-');
        }
        console__print((uint8_t) (hex >> 8U));
        console__print((uint8_t) (hex & 0xFFU));

        ++address;
        if ((address & 0x0FU) == 0) {
            console__println();
        } else {
            console__print(' ');
        }

        _delay_ms(20);
        if (address == 0x80) break;
    }
    return EXIT_SUCCESS;
}


uint8_t console__i2c__run(void) __attribute__ ((noinline)); // no inlining to free up some registers, otherwise will not fit.
uint8_t console__i2c__run(void) {
    if (console__input_length == 1) {
        if (console__input_buffer[0] == 'D') {
            return console__i2c__detect();
        } else if (console__input_buffer[0] == 'R') {
            return console__i2c__read_ack();
        } else if (console__input_buffer[0] == 'r') {
            return console__i2c__read_nack();
        } else if (console__input_buffer[0] == 'P') {
            return console__i2c__stop();
        }
    }

    if (console__input_length == 2 && console__input_buffer[0] == 'I') {
        uint8_t rate_code = console__input_buffer[1];
        if (rate_code == '2') {
            i2c_set_baud_rate(20000UL);
        } else if (rate_code == '4') {
            i2c_set_baud_rate(400000UL);
        } else {
            i2c_set_baud_rate(100000UL);
        }
        return EXIT_SUCCESS;
    }


    if (console__input_length == 3 && console__input_buffer[0] == 'S') {
        return console__i2c__start();
    }
    if (console__input_length == 3 && console__input_buffer[0] == 'W') {
        return console__i2c__write_byte();
    }

    if (console__input_length >= 3) {
        if (console__input_length == 5 && console__input_buffer[2] == '?') {
            return console__i2c__read();
        } else if ((console__input_length & 1U) != 0 && console__input_buffer[2] == '=') {
            return console__i2c__write();
        }
    }
    return EXIT_FAILURE;
}
