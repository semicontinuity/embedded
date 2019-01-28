// =============================================================================
// Test for soft USART RX
// =============================================================================

#include "soft_usart__timer.h"
#include "soft_usart__rx.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu/avr/int0.h>

void soft_usart__rx__on_data(void) {
//    usart0__putc(soft_usart__rx__data);
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    PORTD |= (1<<1);
    DDRD |= (1<<1);

    DDRB |= (1<<5);
//    usart0__init();
//    usart0__tx__enabled__set(1);
//    usart0__out__write('T');
//    usart0__out__write('E');
//    usart0__out__write('S');
//    usart0__out__write('T');
//    usart0__out__write('\n');

    soft_usart__rx__init();
    soft_usart__rx__detector__init();
    soft_usart__timer__init();
    soft_usart__timer__start();
    soft_usart__rx__detector__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    _delay_ms(1000);
    PINB |= (1<<5);
    _delay_ms(1000);
    PINB |= (1<<5);


    for(;;) {
/*
        if (soft_usart__rx__data == 'a') {
            PORTB &= ~(1<<5);
        } else {
            PORTB |= (1<<5);
        }
*/
        if (PORTB & 1) {
//            uint8_t c = soft_usart__rx__data;
            PORTB &= ~(1<<0);
//            usart0__putc(soft_usart__rx__data);

            _delay_ms(300);
            EIFR |= (1<<INTF0);
            soft_usart__rx__detector__start();
            PORTD |= (1<<1);
        }
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
}
