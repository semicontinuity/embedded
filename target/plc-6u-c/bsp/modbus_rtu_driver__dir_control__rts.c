// =============================================================================
// MODBUS RTU driver.
// Direction control implementation with RTS pin.
// =============================================================================

#include "drivers/out/rts.h"
#include "modbus_rtu_driver__dir_control.h"

#include "cpu/avr/usart0.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


void modbus_rtu_driver__dir_control__init(void) {
    rts__init();
}


void modbus_rtu_driver__dir_control__tx(void) {
    rts__set(1);
}


void modbus_rtu_driver__dir_control__rx(void) {
    // TX completed interrupt will be triggered only when the last byte of the frame has been transmitted
    usart0__tx__complete__interrupt__enabled__set(1);
}


/**
 * Enabled only for the last byte of the frame
 */
ISR(usart0__tx__complete__interrupt__VECTOR, ISR_NAKED) {
    rts__set(0);
    usart0__tx__complete__interrupt__enabled__set(0);
    reti();
}
