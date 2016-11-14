// =============================================================================
// MODBUS RTU driver.
// USART receiver module.
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.h"

#include "cpu/avr/usart0.h"


volatile bool modbus_rtu_driver__usart_rx__enabled;


void modbus_rtu_driver__usart_rx__start(void) {
    modbus_rtu_driver__usart_rx__enable();    
    usart0__rx__enabled__set(1);    
    usart0__rx__complete__interrupt__enabled__set(1);
}


void modbus_rtu_driver__usart_rx__stop(void) {
    modbus_rtu_driver__usart_rx__disable();    
    usart0__rx__enabled__set(0);    
    usart0__rx__complete__interrupt__enabled__set(0);    
}


void modbus_rtu_driver__usart_rx__disable(void) {
    modbus_rtu_driver__usart_rx__enabled = false;
}


void modbus_rtu_driver__usart_rx__enable(void) {
    modbus_rtu_driver__usart_rx__enabled = true;
}


ISR(usart0__rx__complete__interrupt__VECTOR) {
    const uint8_t c = usart0__getc(); // read character in any case
    modbus_rtu_driver__usart_rx__on_char_received();
    if (modbus_rtu_driver__usart_rx__enabled) {
        if (!buffer__is_full()) {
            buffer__put_u8(c);
            modbus_rtu_driver__usart_rx__on_char_buffered();
        }
        else {
            modbus_rtu_driver__usart_rx__on_buffer_overflow();
        }
    }
    else {
        modbus_rtu_driver__usart_rx__on_unexpected_data();
    }
}
