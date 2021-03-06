#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
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
