// =============================================================================
// Communications service.
//
// Abstract.
// Implementations must provide:
// - comm_service__rx__init()
// - comm_service__rx__start()
// =============================================================================
#ifndef __COMM_SERVICE_H
#define __COMM_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"

#include "can_selector.h"
#include "cpu/avr/spi.h"
#include "cpu/avr/bootloader.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

extern volatile mcp251x_message_buffer kernel__frame __attribute__((section(".noinit")));
extern void kernel__send_response(const uint8_t count, const uint8_t* data) __attribute__((section(".kernel")));

struct kernel__status {
    uint16_t watchdog_reset_count;
    uint16_t brownout_reset_count;
    uint16_t rx_error_count;
    uint16_t tx_error_count;
};
extern struct kernel__status kernel__status __attribute__((section(".noinit")));


// In ATMEGA48, bits 0 (IVCE) and 1 (IVSEL) have no effect.
// So, IVSEL bit is used to indicate KERNEL mode.
// The IVSEL bit can be changed as described in the datasheet, with setting IVCE bit first.
#if defined (__AVR_ATmega48__) || defined (__AVR_ATmega16__)

/**
 * Activates the kernel only mode.
 */
inline static void kernel__mode__set(void) {
    bootloader__set_place_int_vectors_at_beginning(true); // use IVSEL to indicate KERNEL_ONLY mode
}

/**
 * Activates the normal mode.
 */
inline static void kernel__mode__clear(void) {
    bootloader__set_place_int_vectors_at_beginning(false); // use IVSEL to indicate KERNEL_ONLY mode
}

/**
 * Checks if in the kernel only mode.
 */
inline static bool kernel__mode__is_set(void) {
    return bootloader__is_place_int_vectors_at_beginning();
}

#endif


#include CAN_SERVICE_H


inline static void kernel__init(void) {
    spi__init(SPI_CLKDIV_4);
    spi__double_speed__set(1);
    can_selector__init();
    mcp251x__init();

    comm_service__rx__init();
    comm_service__rx__start();
}

inline static void kernel__start(void) {
    comm_service__rx__start();
}


#endif