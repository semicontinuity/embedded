// =============================================================================
// CAN service.
// Handles CAN communications (services incoming requests).
// Extends comm_service.
//
// The device is designed for the system with one super-node ("master").
// The master is the only device that can send messages to the node.
//
// If master has sent GET request to the node,
// it should not send other GET requests to the node until it receives response.
// If the responce is not received in certain time,
// the master assumes that the node is malfunctioning.
// =============================================================================
#include "can_service.h"



INLINE void int1__run(void) {
    can_service__rx__run();
}
