#ifndef __COMM_SERVICE__ENDPOINT__ALARM_CLIENT__AUTH_H
#define __COMM_SERVICE__ENDPOINT__ALARM_CLIENT__AUTH_H

#include "alarm_client__auth.h"
#include CAN_H
#include <stdint.h>


inline static void comm_service__endpoint__alarm_client__auth__handle(void) {
    alarm_client__auth__password__set(kernel__frame.header.dlc, kernel__frame.data);
}


#endif