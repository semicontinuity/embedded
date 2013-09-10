// =============================================================================
// Support for direction control on RTS pin
// =============================================================================

#include "drivers/out/rts.h"
#include "modbus_rtu_driver.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/usart0.h"


void modbus_rtu_driver__on_transmission_begin(void) {
    rts__set(1);
}


void modbus_rtu_driver__on_transmission_end(void) {
    // TX completed interrupt will be triggered once the last byte has been tranmitted
    usart0__tx__complete__interrupt__enabled__set(1);
}


ISR(usart0__tx__complete__interrupt__VECTOR) {
    // It is assumed that this interrupt will only be served when
    // all bytes are transmitted.
    // During frame transmission, Data Register Interrupt  
    rts__set(0);
    usart0__tx__complete__interrupt__enabled__set(0);
}

