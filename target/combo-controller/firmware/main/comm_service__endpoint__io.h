#ifndef __COMM_SERVICE__ENDPOINT__IO_H
#define __COMM_SERVICE__ENDPOINT__IO_H

#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/asm.h"
#include CAN_H


#include "water_leak_sensors_scanner.h"

#include "out/water_valve.h"
#include "out/amplifier_relay.h"
#include "out/siren1.h"
#include "out/siren2.h"


inline static void comm_service__endpoint__io__handle_input(const uint8_t is_get, const uint8_t report) {
    if (is_get) {
        if (report == CANP_REPORT__WATER_LEAK_SENSORS_SCANNER__VALUE) {
            kernel__send_response(1, &water_leak_sensors_scanner__status.state);
        }
    }
    else {
        // Handle PUT request
        // Should send error
    }
}


inline static void comm_service__endpoint__io__handle_output(const uint8_t is_get, const uint8_t report) {
    if (is_get) {
        uint8_t value = 0;
        if (report == CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE) {
            if (out__water_valve__is_on()) value = 1;
        }
        else if (report == CANP_REPORT__AMPLIFIER_RELAY_CONTROLLER__VALUE) {
            if (out__amplifier_relay__is_on()) value = 1;
        }
        else if (report == CANP_REPORT__SIREN1__VALUE) {
            if (out__siren1__is_on()) value = 1;
        }
        else if (report == CANP_REPORT__SIREN2__VALUE) {
            if (out__siren2__is_on()) value = 1;
        }

        kernel__frame.data[0] = value;
        kernel__send_response(1, kernel__frame.data);
    }
    else {
        // Handle PUT request
        // Should reject all values but 1
        // Should check DLC

        uint8_t value = kernel__frame.data[0];
        if (value == 0) {
            if (report == CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE) {
                out__water_valve__off();
            }
            else if (report == CANP_REPORT__AMPLIFIER_RELAY_CONTROLLER__VALUE) {
                out__amplifier_relay__off();
            }
            else if (report == CANP_REPORT__SIREN1__VALUE) {
                out__siren1__off();
            }
            else if (report == CANP_REPORT__SIREN2__VALUE) {
                out__siren2__off();
            }        
        }
        else {
            if (report == CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE) {
                out__water_valve__on();
            }
            else if (report == CANP_REPORT__AMPLIFIER_RELAY_CONTROLLER__VALUE) {
                out__amplifier_relay__on();
            }
            else if (report == CANP_REPORT__SIREN1__VALUE) {
                out__siren1__on();
            }
            else if (report == CANP_REPORT__SIREN2__VALUE) {
                out__siren2__on();
            }        
        }
    }
}

#endif