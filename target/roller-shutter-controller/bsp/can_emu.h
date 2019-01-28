// =============================================================================
// CAN Controller driver emulator.
// =============================================================================

#ifndef __CAN_H
#define __CAN_H

#include <string.h>
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"


extern mcp251x_message_buffer can__txb0;
extern mcp251x_message_buffer can__txb1;
extern mcp251x_message_buffer can__txb2;



// TXB0 functions
// -----------------------------------------------------------------------------

inline static void can__txb0__load_response(const uint8_t dlc, const uint8_t* id, const uint8_t* data) {
    memcpy((void*)&can__txb0.header, id, 4);
    can__txb0.header.dlc = dlc;
    memcpy((void*)can__txb0.data, data, dlc);
}

inline static void can__txb0__request_to_send(void) {
    usart0__out__send((const char *)&can__txb0, sizeof(can__txb0));
}

// TXB1 functions
// -----------------------------------------------------------------------------

inline static void can__txb1__load_report(const uint8_t report_id, const uint8_t count, const uint8_t* data) {
    can__txb1.header.id.eid0 = report_id;
    can__txb1.header.dlc = count;
    memcpy((void*)can__txb1.data, data, count);    
}

inline static void can__txb1__load_response(const uint8_t sidh, const uint8_t sidl, const uint8_t eid8, const uint8_t eid0, const uint8_t dlc, const uint8_t* data) {
    can__txb1.header.id.sidh = sidh;
    can__txb1.header.id.sidl = sidl;
    can__txb1.header.id.eid8 = eid8;
    can__txb1.header.id.eid0 = eid0;
    can__txb1.header.dlc = dlc;
    memcpy((void*)can__txb1.data, data, dlc);
}

inline static void can__txb1__request_to_send(void) {
    usart0__out__send((const char *)&can__txb1, sizeof(can__txb1));
}



// TXB2 functions
// -----------------------------------------------------------------------------

inline static void can__txb2__request_to_send(void) {
    usart0__out__send((const char *)&can__txb2, sizeof(can__txb2));
}


#endif