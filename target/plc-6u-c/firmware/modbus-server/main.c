// =============================================================================
// Sample MODBUS server.
// =============================================================================


#include "buffer.h"
#include "delay_timer.h"
#include "modbus_server.h"
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdint.h>


// main
// -----------------------------------------------------------------------------

int main(void) {
    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    modbus_server__init();

    sleep_enable();
    modbus_server__start();

    for(;;) {
        if (!modbus_server__run()) {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}


#define SERVER__REGISTER1 (40000)
uint16_t register1;

#define SERVER__REGISTER2 (40001)
uint16_t register2;


/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__handle_read_holding_registers(void) {
    const uint16_t length = buffer__limit__get();
    if (length != MODBUS_FRAME_SIZE_MIN + MODBUS_FUNCTION__READ_HOLDING_REGISTERS__PAYLOAD_SIZE)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    buffer__position__set(MODBUS_FRAME_OFFSET_DATA);
    uint16_t register_address = buffer__get_u16();
    uint16_t register_count = buffer__get_u16();

    if (register_count == 0 || register_count > MODBUS_FUNCTION__READ_HOLDING_REGISTERS__MAX_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    if (register_address < MODBUS_SERVER__HOLDING_REGISTERS_START
        || register_address + register_count >= MODBUS_SERVER__HOLDING_REGISTERS_START + MODBUS_SERVER__HOLDING_REGISTERS_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;


    buffer__limit__set(MODBUS_FRAME_OFFSET_DATA);
    buffer__put_u16((uint8_t) register_count << 1); // byte count
    do {
        switch (register_address++) {
        case SERVER__REGISTER1:
            buffer__put_u16(register1);
            break;
        case SERVER__REGISTER2:
            buffer__put_u16(register2);
            break;
        }
    }
    while (--register_count);   
    
    return MODBUS_EXCEPTION__NONE;
}
