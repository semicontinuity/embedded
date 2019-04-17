// =============================================================================
// Firmware for Button LED Matrix board.
// =============================================================================

#include <cpu/avr/asm.h>
#include <util/delay.h>
#include "comm.h"
#include "drivers/comm/twi_slave_callbacks.h"
#include "drivers/comm/ws2812b.h"
#include "services/tx_ring_buffer.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


// keyboard callbacks
// -----------------------------------------------------------------------------

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-15)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline void keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
    }
}


// comm callbacks
// -----------------------------------------------------------------------------

volatile uint8_t refresh;
uint8_t *led_ptr;
uint8_t leds[16*3];

void twi__slave__on_data_byte_received(const uint8_t value) {
    *led_ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    refresh = 1;
    //    ws2812_sendarray_mask((uint8_t *) leds, 16*3, _BV(1));
//    led_ptr = leds;
}

void twi__slave__on_data_reception_aborted(void) {
    led_ptr = leds;
}


// application
// -----------------------------------------------------------------------------
struct cRGB led[16];

void application__init(void) {
    led_ptr = leds;

    DDRD |= _BV(1);
    _delay_ms(500);

    led[0].r = 0x01;
    led[0].g = 0x00;
    led[0].b = 0x00;
    led[1].r = 0x00;
    led[1].g = 0x01;
    led[1].b = 0x00;
    led[2].r = 0x00;
    led[2].g = 0x00;
    led[2].b = 0x01;
    led[3].r = 0x00;
    led[3].g = 0x00;
    led[3].b = 0x00;
    led[0x04].r = 0x02;
    led[0x04].g = 0x00;
    led[0x04].b = 0x00;
    led[0x05].r = 0x00;
    led[0x05].g = 0x02;
    led[0x05].b = 0x00;
    led[0x06].r = 0x00;
    led[0x06].g = 0x00;
    led[0x06].b = 0x02;
    led[0x07].r = 0x00;
    led[0x07].g = 0x00;
    led[0x07].b = 0x00;

    led[0x08].r = 0x04;
    led[0x08].g = 0x00;
    led[0x08].b = 0x00;
    led[0x09].r = 0x00;
    led[0x09].g = 0x04;
    led[0x09].b = 0x00;
    led[0x0a].r = 0x00;
    led[0x0a].g = 0x00;
    led[0x0a].b = 0x04;
    led[0x0b].r = 0x00;
    led[0x0b].g = 0x00;
    led[0x0b].b = 0x00;
    led[0x0c].r = 0x06;
    led[0x0c].g = 0x00;
    led[0x0c].b = 0x00;
    led[0x0d].r = 0x00;
    led[0x0d].g = 0x06;
    led[0x0d].b = 0x00;
    led[0x0e].r = 0x00;
    led[0x0e].g = 0x00;
    led[0x0e].b = 0x06;
    led[0x0f].r = 0x00;
    led[0x0f].g = 0x00;
    led[0x0f].b = 0x00;

    ws2812_setleds(led, 16);
    _delay_ms(500);

    led[0].r = 0x01;
    led[0].g = 0x01;
    led[0].b = 0x00;
    led[1].r = 0x00;
    led[1].g = 0x01;
    led[1].b = 0x01;
    led[2].r = 0x01;
    led[2].g = 0x00;
    led[2].b = 0x01;
    led[3].r = 0x01;
    led[3].g = 0x01;
    led[3].b = 0x01;
    led[0x04].r = 0x02;
    led[0x04].g = 0x02;
    led[0x04].b = 0x00;
    led[0x05].r = 0x00;
    led[0x05].g = 0x02;
    led[0x05].b = 0x02;
    led[0x06].r = 0x02;
    led[0x06].g = 0x00;
    led[0x06].b = 0x02;
    led[0x07].r = 0x02;
    led[0x07].g = 0x02;
    led[0x07].b = 0x02;

    led[0x08].r = 0x04;
    led[0x08].g = 0x04;
    led[0x08].b = 0x00;
    led[0x09].r = 0x00;
    led[0x09].g = 0x04;
    led[0x09].b = 0x04;
    led[0x0a].r = 0x04;
    led[0x0a].g = 0x00;
    led[0x0a].b = 0x04;
    led[0x0b].r = 0x04;
    led[0x0b].g = 0x04;
    led[0x0b].b = 0x04;
    led[0x0c].r = 0x02;
    led[0x0c].g = 0x00;
    led[0x0c].b = 0x00;
    led[0x0d].r = 0x00;
    led[0x0d].g = 0x02;
    led[0x0d].b = 0x00;
    led[0x0e].r = 0x00;
    led[0x0e].g = 0x00;
    led[0x0e].b = 0x02;
    led[0x0f].r = 0x02;
    led[0x0f].g = 0x02;
    led[0x0f].b = 0x02;

    ws2812_setleds(led, 16);
    _delay_ms(500);

    refresh = 0;
    comm__init();

    usart0__init();
    usart0__tx__enabled__set(1);
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
        if (refresh) {
            uint8_t i = 16*3;
            uint8_t *ptr = leds;

            for (;;) {
                usart0__putc(*ptr++);
                if (--i == 0) break;
            }
            led_ptr = leds;
            refresh = 0;
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
