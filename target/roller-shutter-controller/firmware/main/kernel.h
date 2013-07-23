// =============================================================================
// Communications service.
// =============================================================================
#ifndef __KERNEL_H
#define __KERNEL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#include "drivers/net/can/mcp251x/rx.h"
#include "drivers/net/can/mcp251x/tx.h"
#include "drivers/net/can/mcp251x/int_handler.h"
#include "drivers/out/mcp251x_select.h"

#include "cpu/avr/int0.h"
#include "cpu/avr/spi.h"
#include "cpu/avr/bootloader.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"


extern mcp251x_message_buffer kernel__frame __attribute__((section(".noinit")));
extern void kernel__send_response(const uint8_t count, const uint8_t* data) KERNEL__ATTR;
extern void kernel__send(const uint8_t* data, const uint8_t size, const uint8_t dst, const uint8_t obj_id, const uint8_t port) KERNEL__ATTR;
extern void kernel__read_eeprom_block(void *dst, const void *src, int8_t length) KERNEL__ATTR;
extern void kernel__write_eeprom_block(void *dst, const void *src, int8_t length) KERNEL__ATTR;



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
 * Sets the kernel mode.
 */
inline static void kernel__mode__set(const uint8_t mode) {
    bootloader__set_place_int_vectors_at_beginning(mode); // use IVSEL to indicate KERNEL_ONLY mode
}

/**
 * Get the kernel mode.
 */
inline static bool kernel__mode__get(void) {
    return bootloader__is_place_int_vectors_at_beginning();
}

#endif


inline static void kernel__init(void) {
    spi__init(SPI_CLKDIV_4);
    spi__double_speed__set(1);

    mcp251x_select__init();
    mcp251x__init();
    mcp251x__rx__init();
    mcp251x__tx__init();

    int0__init();
}


inline static void kernel__start(void) {
    mcp251x__tx__start();
    mcp251x__int_handler__start();

    int0__start();
}


#endif