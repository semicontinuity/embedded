#ifndef __KERNEL__HANDLER_H
#define __kERNEL__HANDLER_H

#include <stdint.h>

#define KERNEL__EVENT__TX1_COMPLETE (1<<3)
#define KERNEL__EVENT__TX2_COMPLETE (1<<4)

/**
 * Must be implemented by the application to handle all requests except that for admin interface.
 * Called:
 * - When the frame was received - then 'event' is the number of the filter matched, 'message_type' is the received message type.
 * - When the frame was transmitted - then 'event' is one of KERNEL__EVENT__TX* constants, 'message_type' is 0
 */
extern void kernel__out__handle(const uint8_t event, const uint8_t message_type) __attribute__((section(".progmem.gcc\\"))) __attribute__((noinline));

#endif