// =============================================================================
// MODBUS RTU driver.
// USART receiver module.
// =============================================================================

#include "buffer.h"
#include "modbus_rtu_driver__usart_rx.h"

#include "cpu/avr/usart0.h"
#include <avr/interrupt.h>


/** Enabled flag */
#if defined(MODBUS_RTU_DRIVER__USART_RX__ENABLED__HOST) && defined(MODBUS_RTU_DRIVER__USART_RX__ENABLED__BIT)
DEFINE_BITVAR(modbus_rtu_driver__usart_rx__enabled, MODBUS_RTU_DRIVER__USART_RX__ENABLED__HOST, MODBUS_RTU_DRIVER__USART_RX__ENABLED__BIT);
#else
volatile uint8_t modbus_rtu_driver__usart_rx__enabled;
DEFINE_BITVAR(modbus_rtu_driver__usart_rx__enabled, modbus_rtu_driver__usart_rx__enabled, 0);
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
