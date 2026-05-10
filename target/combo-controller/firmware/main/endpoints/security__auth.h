#ifndef __ENDPOINTS__SECURITY__AUTH_H
#define __ENDPOINTS__SECURITY__AUTH_H


#include "flags/notifications_pending__security__auth.h"
#include "flags/notifications_pending.h"

#include "drivers/net/can/mcp251x/tx.h"
#include "services/alarm__auth.h"
#include "kernel.h"


INLINE void security__auth__request_broadcast(void) {
    notifications_pending__security__auth__set(1);
    notifications_pending__set(1);
}


INLINE void security__auth__broadcast(void) {
    notifications_pending__security__auth__set(0);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 0);
    UCAN_SET_PORT(*id, UCAN__PID__SECURITY__AUTH);
    kernel__send_response(alarm__auth__password.length, alarm__auth__password.data);
}


#endif