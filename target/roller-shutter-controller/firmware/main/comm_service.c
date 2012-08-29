#include "comm_service.h"
#include CAN_H

volatile mcp251x_message_buffer comm_service__buffer;


void comm_service__send_response(const uint8_t report_id, const uint8_t count, const uint8_t* data) {
    can__txb0__load_response(
        comm_service__buffer.header.id.sidh,
        comm_service__buffer.header.id.sidl,
        CANP_EID8(CANP_TXB0_HOST_NET, CANP_TXB0_HOST_ADDR),
        report_id,
        count,
        data
    );
    can__txb0__request_to_send();
}
