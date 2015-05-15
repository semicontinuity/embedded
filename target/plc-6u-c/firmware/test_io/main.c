// =============================================================================
// I/O test
// =============================================================================

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include <cpu/avr/int0.h>
#include <cpu/avr/int1.h>
#include <cpu/avr/int2.h>

void int0__run(void) {
    display__render_packed(0x10);
}
void int1__run(void) {
    display__render_packed(0x11);
}
void int2__run(void) {
    display__render_packed(0x12);
}

// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {

    display__init();

    int0__init();
    int1__init();
    int2__init();

    display__render_packed(0); // ready

    //PORTB |= (1<<2);
    DDRD |= (1<<5);
    PORTD |= (1<<5);

    int0__start();
    int1__start();
    int2__start();
    
    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
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
