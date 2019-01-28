#include "endpoints/comm__binary__1.h"

#include "flags/notifications_pending__comm__binary__1.h"
#include "flags/notifications_pending.h"
#include "drivers/out/siren2.h"
#include "kernel.h"


void comm__binary__1__request_broadcast(void) {
    notifications_pending__comm__binary__1__set(1);
    notifications_pending__set(1);
}

void comm__binary__1__broadcast(void) {
    notifications_pending__comm__binary__1__set(0);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 1);
    UCAN_SET_PORT(*id, UCAN__PID__COMM__BINARY);
    kernel__send_response(1, &siren2__state);
}

void comm__binary__1__set_data(const uint8_t* data) {
    siren2__set(data[0]);
}
