// =============================================================================
// Minimalistic TWI Slave handler.
// Master states are not checked, because only Slave mode is used.
// Arbitration loss is not checked, because there is only one master.
// Only 1-byte reads are supported.
// =============================================================================

#include "cpu/avr/twi.h"
#include "twi_slave_callbacks.h"
#include "twi_slave__handler.h"
#include "util/twi.h"


void twi__slave__handler__start(void) {
    twi__slave__start(false);
}


bool twi__slave__handler__is_runnable(void) {
    return twi__is_software_action_required();
}


void twi__slave__handler__run(void) {
    __asm__ __volatile__("twi__slave__handler__run:");
    uint8_t status = twi__status__get();
    if (status != TWI__STATUS__BUS_ERROR) {
        if (status < TWI__STATUS__SLAVE_READ_ACKNOWLEDGED) {
            // Slave receiver states
            __asm__ __volatile__("twi__slave__handler__slave_receiver:");
            uint8_t value = twi__data__get();
            twi__continue(true, false);
            if (status == TWI__STATUS__SLAVE_RECEIVED_DATA_BYTE_ACKNOWLEDGED) {
                twi__slave__on_data_byte_received(value);
            } else {
                twi__slave__on_data_reception_started();
            }
        } else {
            // Slave transmitter
            __asm__ __volatile__("twi__slave__handler__slave_transmitter:");
            if (status == TWI__STATUS__SLAVE_READ_ACKNOWLEDGED) {
                twi__slave__on_data_byte_requested();
                // handler must set data byte to be transmitted with twi__data__set(),
                // and then call twi__continue(true, false); if non-last data byte has to be transmitted
                // or twi__continue(false, false); if last data byte has to be transmitted
            }
        }
    } else {
        __asm__ __volatile__("twi__slave__handler__bus_error:");
        twi__recover_from_bus_error(true);
    }
}
