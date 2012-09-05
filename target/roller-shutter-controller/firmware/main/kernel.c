#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include CAN_H

volatile mcp251x_message_buffer comm_service__packet;

void comm_service__send_response(const uint8_t count, const uint8_t* data) {
    comm_service__packet.header.id.eid8 = CANP_EID8(CANP_TXB0_HOST_NET, CANP_TXB0_HOST_ADDR);
    can__txb0__load_response_(
        count,
        (const uint8_t*)&comm_service__packet.header.id.sidh,
        data
    );
    can__txb0__request_to_send();
}
