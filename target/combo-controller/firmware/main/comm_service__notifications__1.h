#ifndef __COMM_SERVICE__NOTIFICATIONS__1_H
#define __COMM_SERVICE__NOTIFICATIONS__1_H

#include "kernel.h"
#include "cpu/avr/asm.h"
#include CAN_H


#include "water_leak_sensors_scanner.h"

#include "drivers/out/water_valve.h"
#include "drivers/out/amplifier_relay.h"
#include "drivers/out/siren1.h"
#include "drivers/out/siren2.h"

#include "flags/notifications_pending.h"
#include "flags/notifications_pending__amplifier_relay.h"
#include "flags/notifications_pending__siren1.h"
#include "flags/notifications_pending__siren2.h"
#include "flags/notifications_pending__water_valve.h"
#include "flags/notifications_pending__water_leak_sensors.h"
#include "flags/notifications_pending__alarm__state.h"
#include "flags/notifications_pending__alarm__auth.h"


inline static void comm_service__notifications__1__run(void) {
    if (can__txb1__available__is_set() && notifications_pending__is_set()) {

        uint8_t report_id;
        uint8_t length = 1;
        uint8_t *data = kernel__frame.data;
//        FIX_POINTER(data);

        uint8_t value = 0;
        if (notifications_pending__water_leak_sensors__is_set()) {
            notifications_pending__water_leak_sensors__set(0);
            report_id = CANP_REPORT__WATER_LEAK_SENSORS_SCANNER__VALUE;
            data = &water_leak_sensors_scanner__status.state;
        }
        else if (notifications_pending__water_valve__is_set()) {
            notifications_pending__water_valve__set(0);
            report_id = CANP_REPORT__WATER_VALVE_CONTROLLER__VALUE;
            if (water_valve__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__amplifier_relay__is_set()) {
            notifications_pending__amplifier_relay__set(0);
            report_id = CANP_REPORT__AMPLIFIER_RELAY_CONTROLLER__VALUE;
            if (amplifier_relay__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__siren1__is_set()) {
            notifications_pending__siren1__set(0);
            report_id = CANP_REPORT__SIREN1__VALUE;
            if (siren2__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__siren2__is_set()) {
            notifications_pending__siren2__set(0);
            report_id = CANP_REPORT__SIREN2__VALUE;
            if (siren2__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__alarm__state__is_set()) {
            notifications_pending__alarm__state__set(0);
            report_id = CANP_REPORT__ALARM__STATE;
//            *data = alarm__state;
            data = &alarm__state;
        }
        else if (notifications_pending__alarm__auth__is_set()) {
            notifications_pending__alarm__auth__set(0);
            report_id = CANP_REPORT__ALARM__AUTH;
            length = alarm__auth__password.length;
            data = alarm__auth__password.data;
        }
        else {
            notifications_pending__set(0);
            return;
        }

        can__txb1__load_report(report_id, length, data);
        can__txb1__request_to_send();
    }
}
#endif