// =============================================================================
// CAN service.
// Handles CAN communications (services incoming requests).
// Implements comm_service.
//
// The device is designed for the system with one super-node ("master").
// The master is the only device that can send messages to the node.
//
// If master has sent GET request to the node,
// it should not send other GET requests to the node until it receives response.
// If the responce is not received in certain time,
// the master assumes that the node is malfunctioning.
// =============================================================================
#include "can_service.h"

void can_service__send_response(const uint8_t report_id, const uint8_t count, const uint8_t* data) {
    can__load_txb_response(
        MCP251X_REGISTER_TXB0SIDH,
        comm_service__buffer.header.id.sidh,
        comm_service__buffer.header.id.sidl,
        CANP_EID8(CANP_TXB0_HOST_NET, CANP_TXB0_HOST_ADDR),
        report_id,
        count,
        data
    );
    can__txb0__request_to_send();
}

INLINE void int1__run(void) {
    can_service__run();
}
