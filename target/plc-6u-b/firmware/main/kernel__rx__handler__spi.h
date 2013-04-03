#ifndef __KERNEL__RX__HANDLER__SPI_H
#define __kERNEL__RX__HANDLER__SPI_H

#include <stdint.h>

/**
 * Must be implemented by the application to handle all requests except that for admin interface.
 */
extern void kernel__rx__handle_delegate(const uint8_t filter, const uint8_t is_get) __attribute__((section(".progmem.data\\")));

#endif