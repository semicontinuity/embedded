#include "endpoints/comm__binary__1.h"

#include "flags/notifications_pending__comm__binary__1.h"
#include "flags/notifications_pending.h"
#include "drivers/out/siren2.h"
#include "drivers/net/can/mcp251x/tx.h"


void comm__binary__1__broadcast(void) {
    notifications_pending__comm__binary__1__set(1);
    notifications_pending__set(1);
}

void comm__binary__1__do_broadcast(void) {
    notifications_pending__comm__binary__1__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__COMM__BINARY, 1, &siren2__state);
}
