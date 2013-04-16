#ifndef __KERNEL__HANDLER__SPI_H
#define __kERNEL__HANDLER__SPI_H

#include <stdint.h>

#define KERNEL__EVENT__TX1_COMPLETE (1<<3)
#define KERNEL__EVENT__TX2_COMPLETE (1<<4)

/**
 * Must be implemented by the application to handle all requests except that for admin interface.
 */
extern void kernel__out__handle(const uint8_t filter, const uint8_t is_get) __attribute__((section(".progmem.gcc\\"))) __attribute__((noinline));

#endif