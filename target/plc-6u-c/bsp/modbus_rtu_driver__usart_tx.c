// =============================================================================
// MODBUS RTU driver.
// USART transmitter module.
// =============================================================================

#include "buffer.h"
#include "modbus_rtu_driver__usart_tx.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/usart0.h"


void modbus_rtu_driver__usart_tx__start(void) {
    usart0__tx__enabled__set(1);    
}


void modbus_rtu_driver__usart_tx__stop(void) {
    usart0__tx__enabled__set(0);    
}


void modbus_rtu_driver__usart_tx__enable(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(1);
}


void modbus_rtu_driver__usart_tx__disable(void) {
    usart0__tx__data_register_empty__interrupt__enabled__set(0);
}


ISR(usart0__tx__data_register_empty__interrupt__VECTOR) {
    if (!buffer__is_empty()) {
        usart0__putc(buffer__get_u8());
    }
    else {
        usart0__tx__complete__interrupt__enabled__set(1);
    }
}


/**
 * Triggered when the last byte of the packed is transmitted completely.
 */
ISR(usart0__tx__complete__interrupt__VECTOR, ISR_NAKED) {
    usart0__tx__complete__interrupt__enabled__set(0);
    modbus_rtu_driver__usart_tx__on_frame_sent();
    reti();
}
