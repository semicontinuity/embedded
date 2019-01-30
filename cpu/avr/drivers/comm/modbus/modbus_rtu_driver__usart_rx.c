// =============================================================================
// MODBUS RTU driver.
// USART receiver module.
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__usart_rx.h"

#include "cpu/avr/usart0.h"
#include <avr/interrupt.h>


/** modbus_rtu_driver__usart_rx__enabled flag */
#if defined(MODBUS_RTU_DRIVER__USART_RX__ENABLED__HOST) && defined(MODBUS_RTU_DRIVER__USART_RX__ENABLED__BIT)
DEFINE_BITVAR(modbus_rtu_driver__usart_rx__enabled, MODBUS_RTU_DRIVER__USART_RX__ENABLED__HOST, MODBUS_RTU_DRIVER__USART_RX__ENABLED__BIT);
#else
volatile bool modbus_rtu_driver__usart_rx__enabled;

void modbus_rtu_driver__usart_rx__enabled__set(const bool value) {
    modbus_rtu_driver__usart_rx__enabled = value;
}

bool modbus_rtu_driver__usart_rx__enabled__get() {
    return modbus_rtu_driver__usart_rx__enabled;
}
#endif


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
    modbus_rtu_driver__usart_rx__enabled__set(false);
}


void modbus_rtu_driver__usart_rx__enable(void) {
    modbus_rtu_driver__usart_rx__enabled__set(true);
}


ISR(usart0__rx__complete__interrupt__VECTOR) {
    if (usart0__rx__frame_error__get()) {
        modbus_rtu_driver__usart_rx__on_char_format_error();
    }
    if (usart0__rx__data_overrun__get()) {
        modbus_rtu_driver__usart_rx__on_char_lost();
    }

    const uint8_t c = usart0__getc(); // read character in any case
    modbus_rtu_driver__usart_rx__on_char_received();
    if (modbus_rtu_driver__usart_rx__enabled__get()) {
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
