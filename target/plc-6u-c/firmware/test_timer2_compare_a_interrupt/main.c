// =============================================================================
// Test for Timer2 compare interrupt (and overflow interrupt).
// Toggles PD2 and PD3 whenever corresponding interrupt has occurred.
// =============================================================================
#include "cpu/avr/timer2.h"
#include "cpu/avr/gpio.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



/** Toggles PD2 pin */
ISR(timer2__compare_a__interrupt__VECTOR, ISR_NAKED) {
    PIND |= _BV(2);
    reti();
}

/** Toggles PD3 pin */
ISR(timer2__overflow__interrupt__VECTOR, ISR_NAKED) {
    PIND |= _BV(3);
    reti();
}

register uint16_t test asm("r16");

int main(void) {
    DDRD |= _BV(2) | _BV(3) | _BV(4);
        PORTD |= _BV(4);
/*

    _delay_ms(500);
    PIND |= _BV(2);
    PIND |= _BV(3);

    _delay_ms(500);
    PIND |= _BV(2);
    PIND |= _BV(3);

    _delay_ms(500);
    PIND |= _BV(2);
    PIND |= _BV(3);

    _delay_ms(500);
    PIND |= _BV(2);
    PIND |= _BV(3);

    _delay_ms(500);
    PIND |= _BV(2);
    PIND |= _BV(3);
    timer2__overflow__interrupt__enable();

    timer2__compare_a__value__set(64);
    timer2__conf__set(TIMER2_CONF_NO_PRESCALER|TIMER2_CONF_WGM_NORMAL);
    timer2__compare_a__interrupt__enable();
    
    sei();
*/
    // reference 100ms pulses on PD4
    for(;;) {
//        _delay_ms(100);
//        PIND |= _BV(4);

        _delay_ms(500);
        PORTD |= _BV(4);
        _delay_ms(500);
        PORTD &= ~_BV(4);

    }
}
