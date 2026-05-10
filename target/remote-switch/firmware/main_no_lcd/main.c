// =============================================================================
// Remote switch (without LCD)
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include "drivers/out/debug_led_lcd_d7.h"
#include "drivers/out/debug_led_lcd_d6.h"
#include "drivers/out/debug_led_lcd_d5.h"
#include "drivers/out/debug_led_lcd_d4.h"

#include "drivers/comm/onewire__bus.h"
#include "drivers/comm/onewire.h"

#include "cpu/avr/eeprom.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"

#include "services/comm/modbus_server.h"
#include "services/temperature_reader.h"
#include "services/buttons_handler.h"

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define EEPROM_ADDRESS__BAUD_RATE (0)


void temperature_reader__reading__on_changed(void) {
}

// =============================================================================
// Application
// =============================================================================

// better to use U2X mode, it is more accurate
#define USART_DIVISORS__COUNT (15)
const uint16_t PROGMEM USART_DIVISORS[USART_DIVISORS__COUNT] = {
    [BUTTONS_HANDLER__STATE(1, 1, 1, 0)] = USART0_DIVISOR(1200L),
    [BUTTONS_HANDLER__STATE(1, 1, 0, 1)] = USART0_DIVISOR(2400L),
    [BUTTONS_HANDLER__STATE(1, 1, 0, 0)] = USART0_DIVISOR(4800L),
    [BUTTONS_HANDLER__STATE(1, 0, 1, 1)] = USART0_DIVISOR(9600L),
    [BUTTONS_HANDLER__STATE(1, 0, 1, 0)] = USART0_DIVISOR(14400L),
    [BUTTONS_HANDLER__STATE(1, 0, 0, 1)] = USART0_DIVISOR(19200L),
    [BUTTONS_HANDLER__STATE(1, 0, 0, 0)] = USART0_DIVISOR(28800L),
    [BUTTONS_HANDLER__STATE(0, 1, 1, 1)] = USART0_DIVISOR(31250L),
    [BUTTONS_HANDLER__STATE(0, 1, 1, 0)] = USART0_DIVISOR(38400L),
    [BUTTONS_HANDLER__STATE(0, 1, 0, 1)] = USART0_DIVISOR(57600L),
    [BUTTONS_HANDLER__STATE(0, 1, 0, 0)] = USART0_DIVISOR(62500L),
    [BUTTONS_HANDLER__STATE(0, 0, 1, 1)] = USART0_DIVISOR(76800L),
    [BUTTONS_HANDLER__STATE(0, 0, 1, 0)] = USART0_DIVISOR(115200L),
    [BUTTONS_HANDLER__STATE(0, 0, 0, 1)] = USART0_DIVISOR(125000L),
    [BUTTONS_HANDLER__STATE(0, 0, 0, 0)] = USART0_DIVISOR(250000L)
};


// If some buttons are pressed, use buttons combination to specify baud rate, and save it to EEPROM.
// Otherwise, use configuration, saved in EEPROM
static const uint16_t application__determine_divisor(void) {
    __asm__ __volatile__( "main__config:");

    uint8_t buttons_state = buttons_handler__to_state(buttons_handler__read_state_raw());
    if (buttons_state < USART_DIVISORS__COUNT) {
        eeprom__write_byte(EEPROM_ADDRESS__BAUD_RATE, buttons_state);
        // wait until all buttons are depressed
        while (buttons_handler__read_state_raw() != BUTTONS_HANDLER__RAW_STATE__ALL_DEPRESSED);
    } else {
        buttons_state = eeprom__read_byte(EEPROM_ADDRESS__BAUD_RATE);
        if (buttons_state >= USART_DIVISORS__COUNT) {
            buttons_state = CONFIG__FALLBACK_BUTTONS_STATE; // if value in EEPROM was corrupted
        }
    }
    return pgm_read_word(&USART_DIVISORS[buttons_state]);
}

static void application__init(void) {
    USE_AS_OUTPUT(MODBUS_RTU_DRIVER__FRAME_PROCESSING__LED);
    USE_AS_OUTPUT(MODBUS_RTU_DRIVER__USART_RX__ENABLED__LED);
    USE_AS_OUTPUT(MODBUS_RTU_DRIVER__FRAME_RECEIVED__LED);
    USE_AS_OUTPUT(ONEWIRE__THREAD__ALIVE__LED);

    led1__init();
    led2__init();
    led3__init();
    led4__init();

    debug_led_lcd_d7__init();
    debug_led_lcd_d6__init();
    debug_led_lcd_d5__init();
    debug_led_lcd_d4__init();

    buttons_handler__init();

    modbus_rtu_driver__configure(application__determine_divisor());

    onewire__bus__init();
    onewire__thread__init();
    temperature_reader__thread__start();
}

static void application__start(void) {
    buttons_handler__start();
    modbus_rtu_driver__start();
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
//    for(;;) {
//        if (modbus_rtu_driver__is_runnable()) {
//            modbus_rtu_driver__run();
//        }
//        else {
//            sei();
//            sleep_cpu();
//            cli();
//        }
//    }
    __asm__ __volatile__( "main__loop:");
    for(;;) {
        __asm__ __volatile__( "main__modbus_rtu_driver:");
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
        }
        __asm__ __volatile__( "main__temperature_reader__thread:");
        if (temperature_reader__thread__is_runnable()) {
            temperature_reader__thread__run();
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
