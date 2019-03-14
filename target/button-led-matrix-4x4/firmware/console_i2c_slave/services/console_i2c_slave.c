// =============================================================================
// I2C Slave console.
//
// Supported commands:
//
// "B":      print buffer
// "B":      print RX pointer
// =============================================================================

#include <avr/io.h>
#include <stdlib.h>
#include "comm.h"
#include "services/console_i2c_slave.h"
#include "services/console__in.h"
#include "services/console__out.h"



void console__i2c_slave__init(void) {
}


uint8_t console__i2c_slave__run(void) {
    if (console__input_length == 1 && console__input_buffer[0] == 'B') {
        console__print_bytes_as_hex(comm__data, 3*16);
        console__println();
        return EXIT_SUCCESS;
    }

    if (console__input_length == 1 && console__input_buffer[0] == 'R') {
        console__print_byte_as_hex((const uint8_t) (((const uint16_t) comm__rx__ptr) >> 8));
        console__print_byte_as_hex((const uint8_t) (((const uint16_t) comm__rx__ptr) & 0xFF));
        console__println();
        return EXIT_SUCCESS;
    }

    return  EXIT_FAILURE;
}
