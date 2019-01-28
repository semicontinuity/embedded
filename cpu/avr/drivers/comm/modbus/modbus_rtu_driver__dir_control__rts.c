// =============================================================================
// MODBUS RTU driver.
// Direction control implementation with RTS pin.
// =============================================================================

#include "drivers/out/rts.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver__dir_control.h"

#include "cpu/avr/usart0.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


void modbus_rtu_driver__dir_control__init(void) {
    rts__init(); // in RX mode 
}


/**
 * Switch the transceiver to transmit mode.
 * Should only be called when the tranceiver is in receive mode.
 */
void modbus_rtu_driver__dir_control__tx(void) {
    rts__set(1);
}


/**
 * Switch the transceiver to receive mode.
 */
void modbus_rtu_driver__dir_control__rx(void) {
    rts__set(0);
}
