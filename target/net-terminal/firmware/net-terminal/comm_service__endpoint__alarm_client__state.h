#ifndef __COMM_SERVICE__ENDPOINT__ALARM_CLIENT__STATE_H
#define __COMM_SERVICE__ENDPOINT__ALARM_CLIENT__STATE_H

#include "alarm_client__state.h"
#include CAN_H


INLINE void comm_service__endpoint__alarm_client__state__handle(void) {
    alarm_client__state__set(kernel__frame.data[0]);
    alarm_client__state__on_changed();
}

INLINE void comm_service__endpoint__alarm_client__state__send(void) {
    can__txb2__load_report(CANP_REPORT__ALARM__STATE, sizeof(alarm_client__new_state), (const uint8_t*)&alarm_client__new_state);
    can__txb2__request_to_send();
}

INLINE void comm_service__endpoint__alarm_client__state__request(void) {
    can__txb2__load_request(CANP_REPORT__ALARM__STATE);
    can__txb2__request_to_send();
}


#endif