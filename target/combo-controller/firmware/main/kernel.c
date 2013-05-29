#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/eeprom.h"

#include "drivers/net/can/mcp251x/tx.h"


struct kernel__status kernel__status;

mcp251x_message_buffer kernel__frame;


void kernel__send_response(const uint8_t count, const uint8_t* data) {
    kernel__frame.header.id.eid8 = CANP_EID8(CANP_TXB0_HOST_NET, CANP_TXB0_HOST_ADDR);
    mcp2515__tx__txb0__load_response(
        count,
        (const uint8_t*)&kernel__frame.header.id.sidh,
        data
    );
    mcp2515__tx__txb0__request_to_send();
}


void kernel__read_eeprom_block(void *dst, const void *src, int8_t length) {
    uint8_t *r_ptr = (uint8_t*)src;
    uint8_t *w_ptr = (uint8_t*)dst;
    do {
        *w_ptr++ = eeprom__read_byte(r_ptr++);
    }
    while (--length);
}


void kernel__write_eeprom_block(void *dst, const void *src, int8_t length) {
    uint8_t *r_ptr = (uint8_t*)src;
    uint8_t *w_ptr = (uint8_t*)dst;
    do {
        eeprom__write_byte(w_ptr++, *r_ptr++);
    }
    while (--length);
}