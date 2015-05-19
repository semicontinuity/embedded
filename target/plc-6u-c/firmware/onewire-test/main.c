// =============================================================================
// one wire test 
// =============================================================================
#include "onewire.h"
#include "onewire__bus.h"
#include "drivers/out/rts.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/util/debug.h"

#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#include <stdio.h>


//int usart_putchar(char c, FILE *stream) {
//    usart0__out__write(c);
//    return 0;
//}

// main
// -----------------------------------------------------------------------------
#define OW_SKIP_ROM	        0xCC
#define DS18X20_CONVERT_T       0x44
#define DS18X20_READ	        0xBE
#define DS18X20_SP_SIZE         9

uint8_t command[] = {OW_SKIP_ROM, DS18X20_READ};
uint8_t response[DS18X20_SP_SIZE];


void main__thread__run(void) {
    onewire__command(sizeof(command), sizeof(response), command, response);
    do {
        if (onewire__thread__is_runnable())
            onewire__thread__run();
        else
            sleep_cpu();
    }
    while (onewire__thread__is_alive());

    display__render_packed(response[0]);
/*
    display__render_packed(4);

    uint8_t *r = response;
    for(uint8_t i = 0; i < DS18X20_SP_SIZE; i++) {
        debug__print_byte_as_hex(*r++);
    }

    display__render_packed(5);
    debug__print_P(PSTR("CRC: "));
    debug__print_byte_as_hex(onewire__crc__get());
    debug__putc('\n');
*/
}


int main(void) {
    display__init();

    rts__init();
    rts__set(1);

    usart0__rate__set(USART0__BAUD_RATE);
    usart0__tx__enabled__set(1);

//    FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
//    stdout = &usart_out;

    onewire__bus__init();
    onewire__init();
    
    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    display__init();
    display__render_packed(1);

    _delay_ms(1000);

//    debug__print_P(PSTR("Reset pulse\n"));
//    display__render_packed(2);

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        main__thread__run();
    }
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
    return 0;
}
