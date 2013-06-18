#ifndef __ENDPOINTS__SECURITY__AUTH_H
#define __ENDPOINTS__SECURITY__AUTH_H


#include "flags/notifications_pending__security__auth.h"
#include "flags/notifications_pending.h"

#include "drivers/net/can/mcp251x/tx.h"
#include "services/alarm__auth.h"


INLINE void security__auth__broadcast(void) {
    notifications_pending__security__auth__set(1);
    notifications_pending__set(1);
}


INLINE void security__auth__do_broadcast(void) {
    notifications_pending__security__auth__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__SECURITY__AUTH, alarm__auth__password.length, alarm__auth__password.data);
}


#endif