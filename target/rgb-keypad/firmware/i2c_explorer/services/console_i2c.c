#include <stdlib.h>

#include "services/console_i2c.h"
#include "services/console.h"
#include "drivers/i2c_master.h"

#include <util/delay.h>
#include "util/parser.h"

#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"


#define CONSOLE__I2C__BUFFER_LENGTH 62
uint8_t console__i2c__buffer[CONSOLE__I2C__BUFFER_LENGTH];


void console__i2c__init(void) {
    i2c_init();
}


/**
 * @return EXIT_SUCCESS or EXIT_FAILURE; if success, length bytes are placed into console__i2c__buffer
 */
uint8_t console__i2c__read(uint8_t address_byte, uint8_t length) {
    led2__set(1);
    if (i2c_start(address_byte)) {
        i2c_stop();
        return EXIT_FAILURE;
    }

    if (length > 0) {
        led3__set(1);
        if (i2c_receive(address_byte, console__i2c__buffer, length)) {
            i2c_stop();
            return EXIT_FAILURE;
        }
    }

    led4__set(1);
    i2c_stop();

    led2__set(0);
    led3__set(0);
    led4__set(0);

    return EXIT_SUCCESS;
}


uint8_t console__i2c__write(uint8_t address_byte) {
    uint8_t *bytes_ptr = console__i2c__buffer;
    uint8_t src_index = 3;
    for (;;) {
        if ((uint8_t) src_index >= (uint8_t) console__input_length) {
            break;
        }

        uint8_t c1 = console__input_buffer[src_index++];
        uint8_t c2 = console__input_buffer[src_index++];

        uint16_t parsed_byte = parser__parse_hex_chars(c1, c2);
        if ((uint8_t) (parsed_byte >> 8)) {
            return EXIT_FAILURE;
        }

        *bytes_ptr++ = (uint8_t) parsed_byte;
    }

    uint8_t length = (uint8_t) (src_index - 3);
    length = length >> 1;

    led2__set(1);
    if (i2c_start(address_byte)) {
        i2c_stop();
        return EXIT_FAILURE;
    }

    led2__set(2);
    if (i2c_transmit(address_byte, console__i2c__buffer, length)) {
        i2c_stop();
        return EXIT_FAILURE;
    }

    led3__set(1);
    i2c_stop();

    led2__set(0);
    led3__set(0);
    led4__set(0);

    console__print_ok();
    console__println();
    return EXIT_SUCCESS;
}


//uint8_t console__i2c__detect(void) __attribute__ ((noinline));
uint8_t console__i2c__detect(void) {
    uint8_t address = 0;
    for (;;) {
        uint8_t result = console__i2c__read(address << 1, 1);

        uint16_t hex = formatter__byte_to_hex_chars(address);
        if (result != EXIT_SUCCESS) {
            hex = ('-' << 8) | '-';
        }
        console__print((uint8_t) (hex >> 8));
        console__print((uint8_t) (hex & 0xFF));

        ++address;
        if ((address & 0x0F) == 0) {
            console__println();
        } else {
            console__print(' ');
        }

        if (++address == 0x80) break;
        _delay_ms(20);
    }
    return EXIT_SUCCESS;
}


/**
 * Supported commands:
 *
 * NN?LL
 *  Read LL bytes from I2C device with address NN
 * NN=B0B1B2..BN
 *  Write bytes to I2C device with address NN
 *
 * All numbers are in hex format
 */

uint8_t console__i2c__run(void) __attribute__ ((noinline));
uint8_t console__i2c__run(void) {
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

    if (console__input_length == 1 && console__input_buffer[0] == 'D') {
        return console__i2c__detect();
    }

    if (console__input_length < 5) {
        return EXIT_FAILURE;
    }

    uint16_t parsed_address_byte = parser__parse_hex_byte(console__input_buffer);
    if ((uint8_t) (parsed_address_byte >> 8)) {
        return EXIT_FAILURE;
    }
    uint8_t address_byte = (uint8_t) parsed_address_byte;

    if (console__input_length == 5 && console__input_buffer[2] == '?') {
        uint16_t parsed_length_byte = parser__parse_hex_byte(console__input_buffer + 3);
        if ((uint8_t) (parsed_length_byte >> 8)) {
            return EXIT_FAILURE;
        }

        uint8_t length = (uint8_t) parsed_length_byte;
        uint8_t result = console__i2c__read(address_byte, length);
        if (result == EXIT_SUCCESS) {
            console__print_bytes_as_hex(console__i2c__buffer, length);
            console__println();
        }
        return result;
    } else if (console__input_buffer[2] == '=' && (console__input_length & 1) != 0) {
        return console__i2c__write(address_byte);
    } else {
        return EXIT_FAILURE;
    }
}
