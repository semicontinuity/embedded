// =============================================================================
// Application handler for incoming packets.
//
// Dispatches the incoming packets, based on the matched filter number.
// =============================================================================

#include <stdint.h>
#include "kernel.h"
#include "kernel__handler.h"

#include "endpoints/emergency__water_actuators__0.h"
#include "endpoints/emergency__water_sensors__0.h"
#include "endpoints/security__auth.h"
#include "endpoints/security__state.h"
#include "endpoints/presense__motion_sensors__0.h"
#include "endpoints/comm__binary__0.h"
#include "endpoints/comm__binary__1.h"
#include "endpoints/media__amplifier__0.h"


/**
 * Dispatches the incoming packets, based on the matched filter number.
 * The code must be consistent with CAN masks and filters.
 */
void comm_service__handle(const uint8_t event, const uint8_t message_type) {
    if (event < UCAN_FILTER__SYSTEM) {
        // Received frame into RXB0 or RXB1
        const uint8_t report = UCAN_PORT_BITS(kernel__frame.header.id);

        if (report == UCAN__PID__EMERGENCY__WATER_SENSORS) {
            if (message_type == UCAN_MSG_TYPE_GET)
                emergency__water_sensors__0__request_broadcast();
        }
        else if (report == UCAN__PID__EMERGENCY__WATER_ACTUATORS) {
            if (message_type == UCAN_MSG_TYPE_GET)
                emergency__water_actuators__0__request_broadcast();
            else if (message_type == UCAN_MSG_TYPE_VALUE)
                emergency__water_actuators__0__set_data(kernel__frame.data);
        }
        else if (report == UCAN__PID__PRESENSE__MOTION_SENSORS) {
            if (message_type == UCAN_MSG_TYPE_GET)
                presense__motion_sensors__0__request_broadcast();
            else if (message_type == UCAN_MSG_TYPE_VALUE)
                presense__motion_sensors__0__handle(kernel__frame.data);
        }
        else if (report == UCAN__PID__SECURITY__AUTH) {
            if (message_type == UCAN_MSG_TYPE_GET)
                security__auth__request_broadcast();
        }
        else if (report == UCAN__PID__SECURITY__STATE) {
            if (message_type == UCAN_MSG_TYPE_GET)
                security__state__request_broadcast();
            else if (message_type == UCAN_MSG_TYPE_POST)
                security__state__set_data(kernel__frame.data);
        }
        else if (report == UCAN__PID__COMM__BINARY) {
            const uint8_t obj_id = UCAN_OBJ_ID(kernel__frame.header.id);
            if (obj_id == 0) {
                if (message_type == UCAN_MSG_TYPE_GET)
                    comm__binary__0__request_broadcast();
                else if (message_type == UCAN_MSG_TYPE_VALUE)
                    comm__binary__0__set_data(kernel__frame.data);
            }
            else if (obj_id == 1) {
                if (message_type == UCAN_MSG_TYPE_GET)
                    comm__binary__1__request_broadcast();
                else if (message_type == UCAN_MSG_TYPE_VALUE)
                    comm__binary__1__set_data(kernel__frame.data);
            }
        }
        else if (report == UCAN__PID__MEDIA__AMPLIFIER) {
            if (message_type == UCAN_MSG_TYPE_GET)
                media__amplifier__0__request_broadcast();
            else if (message_type == UCAN_MSG_TYPE_VALUE)
                media__amplifier__0__set_data(kernel__frame.data);
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
