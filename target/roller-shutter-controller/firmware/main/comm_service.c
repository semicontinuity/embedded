// =============================================================================
// Communications service.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__handler.h"

#include "endpoints/comm__bits__0.h"
#include "endpoints/mechatronics__linear_actuator_current_value__0.h"
#include "endpoints/mechatronics__linear_actuator_target_value__0.h"
#include "endpoints/mechatronics__linear_actuator_mode__0.h"
#include "endpoints/mechatronics__linear_actuator_precision__0.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 * @param event         KERNEL__EVENT__TX1_COMPLETE, KERNEL__EVENT__TX2_COMPLETE or matched filter number.
 * @param message_type  message type of incoming packet.
 */
void comm_service__handle(const uint8_t event, const uint8_t message_type) {
    if (event < UCAN_FILTER__SYSTEM) {
        // Received frame into RXB0
        const uint8_t report = UCAN_PORT_BITS(kernel__frame.header.id);

        if (report == UCAN__PID__COMM__BITS) {
            if (message_type == UCAN_MSG_TYPE_GET)
                comm__bits__0__broadcast();
        }
        else if (report == UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_CURRENT_VALUE) {
            if (message_type == UCAN_MSG_TYPE_GET)
                mechatronics__linear_actuator_current_value__0__broadcast();
            else if (message_type == UCAN_MSG_TYPE_POST)
                mechatronics__linear_actuator_current_value__0__handle_post();
        }
        else if (report == UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_TARGET_VALUE) {
            if (message_type == UCAN_MSG_TYPE_GET)
                mechatronics__linear_actuator_target_value__0__broadcast();
            else if (message_type == UCAN_MSG_TYPE_POST)
                mechatronics__linear_actuator_target_value__0__handle_post();
        }
        else if (report == UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_MODE) {
            if (message_type == UCAN_MSG_TYPE_GET)
                mechatronics__linear_actuator_mode__0__broadcast();
            else if (message_type == UCAN_MSG_TYPE_POST)
                mechatronics__linear_actuator_mode__0__handle_post();
        }
        else if (report == UCAN__PID__MECHATRONICS__LINEAR_ACTUATOR_PRECISION) {
            if (message_type == UCAN_MSG_TYPE_GET)
                mechatronics__linear_actuator_precision__0__broadcast();
            else if (message_type == UCAN_MSG_TYPE_POST)
                mechatronics__linear_actuator_precision__0__handle_post();
        }
    }
#if defined(mcp2515__tx__txb1__available__HOST) && defined(mcp2515__tx__txb1__available__BIT)
    else if (event == KERNEL__EVENT__TX1_COMPLETE) {
        mcp2515__tx__txb1__available__set(1);
    }
#endif
#if defined(mcp2515__tx__txb2__available__HOST) && defined(mcp2515__tx__txb2__available__BIT)
    else if (event == KERNEL__EVENT__TX2_COMPLETE) {
        mcp2515__tx__txb2__available__set(1);
    }
#endif
}
