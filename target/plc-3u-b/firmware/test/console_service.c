#include "console_service.h"
#include "parse.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/util/debug.h"


uint8_t input_buffer[16];
uint16_t input_length;


inline void readLine (void) {
    input_length=0;
    while (1) {
        register uint8_t c = usart0__in__read();

        if (c==13 || c==10) break;
        if (input_length < 16) input_buffer[input_length++] = c;
    }
}


void console_service__run(void) {
    while(1) {
        debug__putc('>');
        debug__putc(13);
        debug__putc(10);

        readLine();
        
        if (input_length == 2) {
            uint8_t addr = parseByte(input_buffer);
            register uint16_t a = addr;
            register uint8_t v = *((uint8_t*)a);

            debug__print_byte_as_hex(addr);
            debug__putc('=');
            debug__print_byte_as_hex(v);
        }
        if (input_length == 5 && input_buffer[2] == '=') {
            register uint8_t addr = parseByte(input_buffer);
            register uint8_t value = parseByte(input_buffer + 3);
            
            register uint16_t a = addr;
            *((uint8_t*)a) = value;
        }

        debug__putc(13);
        debug__putc(10);
    }
}
