// =============================================================================
// MODBUS RTU driver.
// USART transmitter module.
// =============================================================================

#include "buffer.h"
#include "modbus_rtu_driver__usart_tx.h"

#include <avr/interrupt.h>
#include "cpu/avr/usart0.h"


void modbus_rtu_driver__usart_tx__start(void) {
    usart0__tx__enabled__set(1);    
}


void modbus_rtu_driver__usart_tx__stop(void) {
    usart0__tx__enabled__set(0);    
}


void modbus_rtu_driver__usart_tx__signal(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(1);
}


ISR(usart0__tx__data_register_empty__interrupt__VECTOR) {
    if (!buffer__is_empty()) {
        usart0__putc(buffer__get_u8());
    }
    else {
        // Assuming, that this interrupt is handled fast enough,
        // so that the last bit is not completely transmitted yet.

        // Clear TX Complete flag by writing 1 (almost certainly it is set, and interrupt will be triggered immediately)
        // The TX Complete interrupt will be triggered when the byte is completely transmitted.
        usart0__tx__complete__value__set(1);
        usart0__tx__complete__interrupt__enabled__set(1);
        usart0__tx__data_register_empty__interrupt__enabled__set(0);    // prevent re-triggering
    }
}


/**
 * Triggered when the last byte of the packed is transmitted completely.
 */
ISR(usart0__tx__complete__interrupt__VECTOR) {
    usart0__tx__complete__interrupt__enabled__set(0);   // quite heavyweight on ATMegaX8
    modbus_rtu_driver__usart_tx__on_frame_sent();   // in NAKED int, must not corrupt CPU state!
}
