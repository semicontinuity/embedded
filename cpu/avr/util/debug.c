#include "cpu/avr/util/debug.h"
#include <stdint.h>
#include <avr/pgmspace.h>



void debug__print_string_progmem(const char * PROGMEM str) {
    for(;;) {
        uint8_t data = pgm_read_byte(str++);
        if (data == 0) break;
        debug__putc(data);
    }
}


// Prefer to spend flash and CPU, save RAM.
void debug__print_byte_as_hex(const uint8_t value) {
    debug__putc(debug__lower_nibble_to_hex(value >> 4));
    debug__putc(debug__lower_nibble_to_hex(value & 0x0F));
}
