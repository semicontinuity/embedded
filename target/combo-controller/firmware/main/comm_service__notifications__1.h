#ifndef __COMM_SERVICE__NOTIFICATIONS__1_H
#define __COMM_SERVICE__NOTIFICATIONS__1_H

#include "kernel.h"
#include "cpu/avr/asm.h"
#include CAN_H


#include "water_leak_sensors_scanner.h"

#include "out/water_valve.h"
#include "out/amplifier_relay.h"
#include "out/siren1.h"
#include "out/siren2.h"

#include "flags/notifications__pending.h"
#include "flags/amplifier_relay__changed.h"
#include "flags/siren1__changed.h"
#include "flags/siren2__changed.h"
#include "flags/water_valve__changed.h"
#include "flags/water_leak_sensors__changed.h"
#include "flags/alarm__state__changed.h"


inline static void comm_service__notifications__1__run(void) {
    if (can__txb1__available__is_set() && notifications__pending__is_set()) {
        uint8_t report_id;
        uint8_t *data = kernel__frame.data;
//        FIX_POINTER(data);

        uint8_t value = 0;
        if (water_leak_sensors__changed__is_set()) {
            water_leak_sensors__changed__set(0);
            report_id = CANP_REPORT__WATER_LEAK_SENSORS_SCANNER__VALUE;
            data = &water_leak_sensors_scanner__status.state;
        }
        else if (water_valve__changed__is_set()) {
            water_valve__changed__set(0);
            report_id = CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE;
            if (out__water_valve__is_on()) value = 1;
            *data = value;
        }
        else if (amplifier_relay__changed__is_set()) {
            amplifier_relay__changed__set(0);
            report_id = CANP_REPORT__AMPLIFIER_RELAY_CONTROLLER__VALUE;
            if (out__amplifier_relay__is_on()) value = 1;
            *data = value;
        }
        else if (siren1__changed__is_set()) {
            siren1__changed__set(0);
            report_id = CANP_REPORT__SIREN1__VALUE;
            if (out__siren2__is_on()) value = 1;
            *data = value;
        }
        else if (siren2__changed__is_set()) {
            siren2__changed__set(0);
            report_id = CANP_REPORT__SIREN2__VALUE;
            if (out__siren2__is_on()) value = 1;
            *data = value;
        }
        else if (alarm__state__changed__is_set()) {
            alarm__state__changed__set(0);
            report_id = CANP_REPORT__ALARM__STATE;
            value = alarm__state;
            *data = value;
        }
        else {
            notifications__pending__set(0);
            return;
        }

        can__txb1__load_report(report_id, 1, data);
        can__txb1__request_to_send();
    }
}
#endif