#include "device.h"
#include <avr/io.h>

#include "device.h"
#include "debug.h"

#include "router.h"
#include "can_tx_q.h"
#include "packet.h"

#include "cpu/avr/asm.h"

/*
 *****************************************************************************************************
 * Routing module
 * Provides function router__process_packet()
 *****************************************************************************************************
 */


/**
 * Copy the packet
 * @param register Y - source
 * @param register Z - destination
 */
inline static void router__copy_packet(void) {
    // Create response: (header = copy of request header) + (data = memory contents)

    // Copy header (5 bytes)
    // -------------------------------------------------------------------------------------------

    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();

    // Copy the payload.
    // -------------------------------------------------------------------------------------------
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
}


/**
 * Route the packet
 * @param Y register - the pointer to the packet
 */
void router__process_packet(void) {
    can_tx_q__put_if_not_full(router__copy_packet());
}
