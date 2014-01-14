// =============================================================================
// USART transmitter
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
    modbus_rtu_driver__dir_control__tx();
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
        modbus_rtu_driver__dir_control__rx();
        modbus_rtu_driver__usart_tx__on_frame_sent();
    }
}
