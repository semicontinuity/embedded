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

#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"

#include "services/eeprom_config.h"
#include "services/temperature_reader.h"
#include "services/buttons_handler.h"

#include <avr/interrupt.h>


void temperature_reader__reading__on_changed(void) {
}

// =============================================================================
// Application
// =============================================================================

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

    modbus_rtu_driver__configure(config__get_usart_divisor());

    onewire__bus__init();
    onewire__thread__init();
    temperature_reader__thread__start();
}

static void application__start(void) {
    buttons_handler__start();
    modbus_rtu_driver__start();
}

static void application__loop(void) {
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
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
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();
    sei();
    application__loop();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}
