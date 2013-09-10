// =============================================================================
// USART receiver
// =============================================================================

#include "buffer.h"
#include "modbus_rtu_driver__delay_timer.h"
#include "modbus_rtu_driver__usart_rx.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/usart0.h"


volatile bool modbus_rtu_driver__usart_rx__enabled;


void modbus_rtu_driver__usart_rx__enable(void) {
    modbus_rtu_driver__usart_rx__enabled = true;
}


void modbus_rtu_driver__usart_rx__disable(void) {
    modbus_rtu_driver__usart_rx__enabled = false;
}


ISR(usart0__rx__complete__interrupt__VECTOR) {
    const uint8_t c = usart0__getc(); // read character in any case
    modbus_rtu_driver__delay_timer__start();
    if (modbus_rtu_driver__usart_rx__enabled) {
        if (!buffer__is_full()) {
            buffer__put_u8(c);
        }
        else {
            modbus_rtu_driver__usart_rx__on_buffer_overflow();            
        }
    }
    else {
        modbus_rtu_driver__usart_rx__on_unexpected_data();
    }
}
