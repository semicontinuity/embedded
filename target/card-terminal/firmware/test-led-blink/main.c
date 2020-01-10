#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

int main(int argc, char **argv) {
    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    DDRD |= _BV(DDD0);

    while(1) {
        PORTD |= _BV(PD0);
        _delay_ms(1000);
        PORTD &= ~_BV(PD0);
        _delay_ms(1000);
    }

    return 0;
}
