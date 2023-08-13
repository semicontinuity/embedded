// =============================================================================
// Modbus communications.
// Implementations of prototypes from modbus_rtu_driver.h and modbus_server.h
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"


void modbus_rtu_driver__on_char_received(void) {
}

void modbus_rtu_driver__on_char_buffered(void) {
}

void modbus_rtu_driver__on_buffer_overflow(void) {
}

void modbus_rtu_driver__on_char_timeout(void) {
}

void modbus_rtu_driver__on_char_format_error(void) {
}

void modbus_rtu_driver__on_char_lost(void) {
}

void modbus_rtu_driver__on_frame_timeout(void) {
}

void modbus_rtu_driver__on_frame_processing(void) {
}

void modbus_rtu_driver__on_response(void) {
}

void modbus_rtu_driver__on_no_response(void) {
}

void modbus_rtu_driver__on_frame_sent(void) {
}

void modbus_rtu_driver__on_protocol_error(void) {
}

void modbus_server__on_valid_frame_received(void) {
}

void modbus_server__on_invalid_frame_received(void) {
}
