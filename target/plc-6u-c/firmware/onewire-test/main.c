// =============================================================================
// one wire test 
// =============================================================================
#include "onewire.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


int usart_putchar(char c, FILE *stream) {
    usart0__out__write(c);
    return 0;
}

// main
// -----------------------------------------------------------------------------
#define OW_SKIP_ROM	        0xCC
#define DS18X20_CONVERT_T       0x44
#define DS18X20_READ	        0xBE
#define DS18X20_SP_SIZE         9

uint8_t command[] = {OW_SKIP_ROM, DS18X20_READ};
uint8_t response[DS18X20_SP_SIZE];


int main(void) {

    usart0__rate__set(USART_BAUD_RATE);
    FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &usart_out;

    // 1-wire
    onewire__init();
    
    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    sei();

    printf_P(PSTR("Reading scratch\n"));

    onewire__command(sizeof(command), sizeof(response), command, response);

    // schedule onewire__thread until it is alive
    for(;;) {
        if (!onewire__thread__is_running()) break;

        if (onewire__thread__is_runnable())
            onewire__thread__run();
        else
            sleep_cpu();
    }

    uint8_t *r = response;
    for(uint8_t i = 0; i < DS18X20_SP_SIZE; i++) {
        printf(PSTR("%02X "), *r++);
    }

    printf(PSTR("CRC: %02X\n"), onewire__crc__get());

    for(;;) {
        sleep_cpu();
    }

    return 0;
}
