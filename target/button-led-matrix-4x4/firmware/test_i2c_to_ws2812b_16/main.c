// =============================================================================
// I2C -> WS2812B test
// =============================================================================


#include "comm.h"
#include "drivers/comm/ws2812b.h"
#include "drivers/out/alarm.h"


// comm callbacks
// -----------------------------------------------------------------------------

uint8_t led[16*3];
uint8_t *led_ptr = led;

void twi__slave__on_data_byte_received(const uint8_t value) {
    alarm__toggle();
    *led_ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    ws2812_sendarray_mask((uint8_t *) led, 3, _BV(1));
    led_ptr = led;
}

void twi__slave__on_data_reception_aborted(void) {
    led_ptr = led;
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    alarm__init();
    comm__init();
}

void application__start(void) {
    comm__start();
}


// main
// -----------------------------------------------------------------------------

int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();
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
