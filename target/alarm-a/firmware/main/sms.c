#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#include "cpu/avr/usart0.h"


const uint8_t PROGMEM MESSAGE[] = {
    'A','T','+','C','M','S','S','='
};


void sms__send(const uint8_t index) {
    const uint8_t* PROGMEM ptr = MESSAGE;
    const uint8_t* PROGMEM end = MESSAGE + sizeof(MESSAGE);
    while (ptr <= end) {
        usart0__out__write(pgm_read_byte(ptr));
        ptr++;
    }
    usart0__out__write(index);
    usart0__out__write(10);
}
    