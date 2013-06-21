#include "endpoints/comm__binary__0.h"

#include "flags/notifications_pending__comm__binary__0.h"
#include "flags/notifications_pending.h"
#include "drivers/out/siren1.h"
#include "kernel.h"


void comm__binary__0__broadcast(void) {
    notifications_pending__comm__binary__0__set(1);
    notifications_pending__set(1);
}


void comm__binary__0__do_broadcast(void) {
    notifications_pending__comm__binary__0__set(0);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 0);
    UCAN_SET_PORT(*id, UCAN__PID__COMM__BINARY);
    kernel__send_response(1, &siren1__state);
}


void comm__binary__0__set_data(const uint8_t* data) {
    siren1__set(data[0]);
}
