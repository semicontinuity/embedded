#include "cpu/avr/asm.h"
#include "cpu/avr/util/debug.h"
#include <stdint.h>
#include <avr/pgmspace.h>



void debug__print_P(const char * PROGMEM str) {
    for (;;) {
        char c = __LPM_increment__(str);
        if (!c) break;
        usart0__out__write(c);
    }
}

void debug__print_string_progmem(const char * PROGMEM str) {
    for(;;) {
        uint8_t data = pgm_read_byte(str++);
        if (data == 0) break;
        debug__putc(data);
    }
}


inline uint8_t debug__lower_nibble_to_hex(uint8_t value) {
    if (value > 9) value += ('A' - ('9' + 1));
    return value += '0';
}

// Prefer to spend flash and CPU, save RAM.
void debug__print_byte_as_hex(const uint8_t value) {
    debug__putc(debug__lower_nibble_to_hex(value >> 4));
    debug__putc(debug__lower_nibble_to_hex(value & 0x0F));
}
