#ifndef __COMM_SERVICE__NOTIFICATIONS__1_H
#define __COMM_SERVICE__NOTIFICATIONS__1_H

#include "kernel.h"

#include "drivers/out/siren1.h"
#include "drivers/out/siren2.h"

#include "flags/notifications_pending.h"
#include "flags/notifications_pending__media__amplifier__0.h"
#include "flags/notifications_pending__siren1.h"
#include "flags/notifications_pending__siren2.h"
#include "flags/notifications_pending__emergency__water_actuators__0.h"
#include "flags/notifications_pending__emergency__water_sensors__0.h"
#include "flags/notifications_pending__presense__motion_sensors__0.h"
#include "flags/notifications_pending__alarm__state.h"
#include "flags/notifications_pending__alarm__auth.h"


inline static void comm_service__notifications__1__run(void) {
    if (mcp2515__tx__txb1__available__is_set() && notifications_pending__is_set()) {

        uint8_t report_id;
        uint8_t length = 1;
        uint8_t *data = kernel__frame.data;
//        FIX_POINTER(data);

        uint8_t value = 0;
        if (notifications_pending__emergency__water_sensors__0__is_set()) {
            notifications_pending__emergency__water_sensors__0__set(0);
            report_id = UCAN__PID__EMERGENCY__WATER_SENSORS;
            data = emergency__water_sensors__0__get_data();
        }
        else if (notifications_pending__emergency__water_actuators__0__is_set()) {
            notifications_pending__emergency__water_actuators__0__set(0);
            report_id = UCAN__PID__EMERGENCY__WATER_ACTUATORS;
            data = emergency__water_actuators__0__get_data();
        }
        else if (notifications_pending__media__amplifier__0__is_set()) {
            notifications_pending__media__amplifier__0__set(0);
            report_id = UCAN__PID__MEDIA__AMPLIFIER;
            if (amplifier_relay__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__siren1__is_set()) { // fix
            notifications_pending__siren1__set(0);
            report_id = UCAN__PID__COMM__BINARY;
            if (siren2__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__siren2__is_set()) { // fix
            notifications_pending__siren2__set(0);
            report_id = UCAN__PID__COMM__BINARY;
            if (siren2__is_on()) value = 1;
            *data = value;
        }
        else if (notifications_pending__alarm__state__is_set()) {
            notifications_pending__alarm__state__set(0);
            report_id = UCAN__PID__SECURITY__STATE;
//            *data = alarm__state;
            data = (uint8_t*)&alarm__state;
        }
        else if (notifications_pending__alarm__auth__is_set()) {
            notifications_pending__alarm__auth__set(0);
            report_id = UCAN__PID__SECURITY__AUTH;
            length = alarm__auth__password.length;
            data = alarm__auth__password.data;
        }
        else {
            notifications_pending__set(0);
            return;
        }

        mcp2515__tx__txb1__load_report(report_id, length, data);
        mcp2515__tx__txb1__request_to_send();
    }
}
#endif