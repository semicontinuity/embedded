// =============================================================================
// Test (transmit 8 bits with USI)
// =============================================================================
#include "drivers/out/led_red.h"
#include "usi_usart__tx.h"
#include "usi_usart__timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

void end_of_start_bit(void) {
    USICR = (1 << USIOIE) | (0 << USIWM1) | (1 << USIWM0) | (0 << USICS1) | (1 << USICS0); // 3-wire mode; Timer 0 Compare Match clock; OVF interrupt enabled

    led_red__set(1);
    timer0__compare_a__interrupt__disable();
}


ISR(USI_OVF_vect, ISR_NAKED) {
    USICR = 0;  // disable USI, will output 1 on DO line
    USISR |= (1<<USIOIF);
    reti();
}


int main(void) {
    led_red__init();

    usi_usart__timer__init();
    usi_usart__tx__init();


    USIDR = 0x23;	// 23 = 0010 0011, bitswapped 1100 0100
    USISR = 8;		// counter = 8, send 1 start bit + 7 data bits

    _delay_ms(10000);

    timer0__compare_a__interrupt__enable();
    PORTB &= ~(1<<1); // B1=0, start bit edge
    usi_usart__timer__start();

    sei();

    while(1) {
    }    

    return 0;
}
