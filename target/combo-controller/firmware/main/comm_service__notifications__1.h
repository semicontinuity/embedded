#ifndef __COMM_SERVICE__NOTIFICATIONS__1_H
#define __COMM_SERVICE__NOTIFICATIONS__1_H

#include "kernel.h"

#include "endpoints/emergency__water_sensors__0.h"
#include "endpoints/emergency__water_actuators__0.h"
#include "endpoints/security__state.h"
#include "endpoints/security__auth.h"
#include "endpoints/presense__motion_sensors__0.h"
#include "endpoints/comm__binary__0.h"
#include "endpoints/comm__binary__1.h"
#include "endpoints/media__amplifier__0.h"

#include "flags/notifications_pending.h"
#include "flags/notifications_pending__emergency__water_sensors__0.h"
#include "flags/notifications_pending__emergency__water_actuators__0.h"
#include "flags/notifications_pending__security__state.h"
#include "flags/notifications_pending__security__auth.h"
#include "flags/notifications_pending__presense__motion_sensors__0.h"
#include "flags/notifications_pending__comm__binary__0.h"
#include "flags/notifications_pending__comm__binary__1.h"
#include "flags/notifications_pending__media__amplifier__0.h"

#include <stdint.h>


inline static void comm_service__notifications__1__run(void) {
    if (mcp2515__tx__txb1__available__is_set() && notifications_pending__is_set()) {
        if (notifications_pending__emergency__water_sensors__0__is_set()) {
            emergency__water_sensors__0__broadcast();
        }
        else if (notifications_pending__emergency__water_actuators__0__is_set()) {
            emergency__water_actuators__0__broadcast();
        }
        else if (notifications_pending__security__state__is_set()) {
            security__state__broadcast();
        }
        else if (notifications_pending__security__auth__is_set()) {
            security__auth__broadcast();
        }
        else if (notifications_pending__presense__motion_sensors__0__is_set()) {
            presense__motion_sensors__0__broadcast();
        }
        else if (notifications_pending__comm__binary__0__is_set()) {            
            comm__binary__0__broadcast();
        }
        else if (notifications_pending__comm__binary__1__is_set()) {
            comm__binary__1__broadcast();
        }
        else if (notifications_pending__media__amplifier__0__is_set()) {
            media__amplifier__0__broadcast();
        }
        else {
            notifications_pending__set(0);
        }
    }
}
#endif