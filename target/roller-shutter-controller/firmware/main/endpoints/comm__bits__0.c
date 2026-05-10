#include "endpoints/comm__bits__0.h"
#include "buttons_scanner.h"
#include "kernel.h"


void comm__bits__0__broadcast(void) {
    kernel__send(
        (const uint8_t*)&buttons_scanner__status,
        sizeof(buttons_scanner__status),
        UCAN_CHANNEL_ID,
        0,
        UCAN__PID__COMM__BITS
    );
}
