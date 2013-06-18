#include "endpoints/comm__binary__0.h"

#include "flags/notifications_pending__comm__binary__0.h"
#include "flags/notifications_pending.h"
#include "drivers/out/siren1.h"
#include "drivers/net/can/mcp251x/tx.h"


void comm__binary__0__broadcast(void) {
    notifications_pending__comm__binary__0__set(1);
    notifications_pending__set(1);
}


void comm__binary__0__do_broadcast(void) {
    notifications_pending__comm__binary__0__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__COMM__BINARY, 1, &siren1__state);
}


void comm__binary__0__set_data(const uint8_t* data) {
    siren1__set(data[0]);
}
