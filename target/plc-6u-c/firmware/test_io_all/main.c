// =============================================================================
// Tests all I/O pins
// =============================================================================

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


static void application__init(void) {
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
}

static void application__start(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
}


int main(void) {
    application__init();
    application__start();

    uint8_t pin_number = 0;
    for (;;) {
        if (pin_number > 0x1F)
            pin_number = 0;

        switch (pin_number++) {
        case 0x00: PORTD |= (1<<0); break;
        case 0x01: PORTD |= (1<<1); break;
        case 0x02: PORTD |= (1<<2); break;
        case 0x03: PORTD |= (1<<3); break;
        case 0x04: PORTD |= (1<<4); break;
        case 0x05: PORTD |= (1<<5); break;
        case 0x06: PORTD |= (1<<6); break;
        case 0x07: PORTD |= (1<<7); break;

        case 0x08: PORTB |= (1<<0); break;
        case 0x09: PORTB |= (1<<1); break;
        case 0x0A: PORTB |= (1<<2); break; 
        case 0x0B: PORTB |= (1<<3); break; 
        case 0x0C: PORTB |= (1<<4); break;
        case 0x0D: PORTB |= (1<<5); break;
        case 0x0E: PORTB |= (1<<6); break;
        case 0x0F: PORTB |= (1<<7); break;

        case 0x10: PORTC |= (1<<0); break;
        case 0x11: PORTC |= (1<<1); break;
        case 0x12: PORTC |= (1<<2); break;
        case 0x13: PORTC |= (1<<3); break;
        case 0x14: PORTC |= (1<<4); break;
        case 0x15: PORTC |= (1<<5); break;
        case 0x16: PORTC |= (1<<6); break;
        case 0x17: PORTC |= (1<<7); break;

        case 0x18: PORTA |= (1<<0); break;
        case 0x19: PORTA |= (1<<1); break;
        case 0x1A: PORTA |= (1<<2); break;
        case 0x1B: PORTA |= (1<<3); break;
        case 0x1C: PORTA |= (1<<4); break;
        case 0x1D: PORTA |= (1<<5); break;
        case 0x1E: PORTA |= (1<<6); break;
        case 0x1F: PORTA |= (1<<7); break;
        }

        _delay_ms(500);

        PORTA = 0;
        PORTB = 0;
        PORTC = 0;
        PORTD = 0;

    }
}

