// =============================================================================
// Firmware for Button LED Matrix board.
// =============================================================================

#include <cpu/avr/asm.h>
#include "cpu/avr/services/keyboard/keyboard.h"
#include "services/tx_ring_buffer.h"

#include "comm.h"
#include "I2CSlave.h"
#include "drivers/comm/twi_slave_callbacks.h"

#include "drivers/comm/ws2812b.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

#include <util/delay.h>


#if defined(REFRESH__HOST) && defined(REFRESH__BIT)
#include "util/bitops.h"
DEFINE_BITVAR(refresh, REFRESH__HOST, REFRESH__BIT);
#else
volatile uint8_t refresh;
DEFINE_BITVAR(refresh, refresh, 0);
#endif

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
inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    cli();
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
        alarm__set(1);
    }
    sei();
    return true;
}

// comm callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    uint8_t value = 0;
    if (tx_ring_buffer__is_readable()) {
        value = tx_ring_buffer__get();
        alarm__set(0);
    }
    I2C_transmitByte(value);
}

void twi__slave__on_data_transmission_finished(void) {
}


volatile uint8_t *led_ptr;
uint8_t leds[16*3];


void twi__slave__on_data_byte_received(const uint8_t value) {
    *led_ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    refresh__set(1);
    led_ptr = leds;
}

void twi__slave__on_data_reception_aborted(void) {
    led_ptr = leds;
}


// application
// -----------------------------------------------------------------------------
struct cRGB led[16];

void application__init(void) {
    alarm__init();
    led_a__init();
    led_b__init();

    keyboard__init();

    refresh__set(0);
    comm__init();
    led_ptr = leds;
}


void application__start(void) {
    tx_ring_buffer__start();
    comm__start();
}


// main
// -----------------------------------------------------------------------------

int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_us(2);
    application__start();
    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        if (refresh__is_set()) {
            ws2812_sendarray_mask((uint8_t *) leds, 16*3, _BV(1));
            refresh__set(0);
        }
        keyboard__run();
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
