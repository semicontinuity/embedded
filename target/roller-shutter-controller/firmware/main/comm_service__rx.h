// =============================================================================
// Communications service.
//
// Services incoming requests.
// =============================================================================
#ifndef __COMM_SERVICE_RX_H
#define __COMM_SERVICE_RX_H

#include <stdint.h>
#include "comm_service.h"
#include "comm_service__admin.h"
#include "comm_service__descriptor_memory.h"
#include "comm_service__buttons_scanner.h"
#include "comm_service__motor_controller.h"


static inline void comm_service__handle_rx(uint8_t filter) {
    switch (filter) {
    case CANP_FILTER__DESCRIPTOR_MEMORY:
        comm_service__descriptor_memory__handle();
        break;
    case CANP_FILTER__ADMIN:
        comm_service__handle__admin();
        break;
    case CANP_FILTER__USER:
    case CANP_FILTER__USER_MCAST:
        switch (CANP_SLOT_BITS(comm_service__buffer.header.id)) {
        case CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE:
            comm_service__handle__motor_controller__motor_mode();
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__CONTROL:
            comm_service__handle_motor_controller_control();
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__STATUS:
            comm_service__handle_motor_controller_status();
            break;
        case CANP_REPORT__BUTTONS_SCANNER__STATUS:
            comm_service__handle_buttons_scanner_status();
            break;
        }
    }
}

#endif