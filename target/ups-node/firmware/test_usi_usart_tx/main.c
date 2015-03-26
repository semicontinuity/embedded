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

void led_on(void) {
//    led_red__set(1);
}

unsigned char __builtin_avr_insert_bits (unsigned long map, unsigned char bits, unsigned char val);


ISR(USI_OVF_vect, ISR_NAKED) {
    USICR = 0;  // disable USI, will output 1 on DO line
    USISR |= (1<<USIOIF);
    reti();
}


int main(void) {
    led_red__init();

    usi_usart__timer__init();
    usi_usart__tx__init();

    _delay_ms(10000);
    USICR = (1 << USIOIE) | (0 << USIWM1) | (1 << USIWM0) | (0 << USICS1) | (1 << USICS0); // 3-wire mode; Timer 0 Compare Match clock; OVF interrupt enabled
    USIDR = 0x23;	// 23 = 0010 0011, sent as : S 010 0011 ?  = ?1100010, ? = 0
    USISR = 8;		// counter = 8, send 1 start bit + 7 data bits

    usi_usart__timer__start();
    sei();

    while(1) {
        if (USISR & (1<<USIOIF)) break; // wait int flag
    }
    while(1) {
        if (USISR & (1<<USIOIF)) continue; // wait int flag cleared
        break;
    }
    led_red__set(1);
    

    return 0;
}
