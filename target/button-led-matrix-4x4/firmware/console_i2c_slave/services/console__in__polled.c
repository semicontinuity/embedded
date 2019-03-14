#include "services/console__in.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


uint8_t console__input_buffer[CONSOLE__BUFFER_LENGTH];
volatile uint16_t console__input_length;


void console__in__init(void) {
    usart0__rx__enabled__set(1);
}

void console__in__start(void) {
}


void console__read_line(void) {
    console__input_length = 0;
    while (1) {
        uint8_t c = usart0__in__read();

        if (c == 13 || c == 10) break;
        if (console__input_length < CONSOLE__BUFFER_LENGTH) console__input_buffer[console__input_length++] = c;
    }
}
