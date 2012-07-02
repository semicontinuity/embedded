#ifndef __CONFIG__CAN_H
#define __CONFIG__CAN_H

#include <avr/sfr_defs.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"

#include "mcp251x/bitdefs.h"
#include "mcp251x/registers.h"
#include "mcp251x/operations.h"
#include "mcp251x/opmodes.h"
#include "mcp251x/struct.h"

#define CANP_DEVICE_NET			(0x01)
#define CANP_DEVICE_ADDR		(0x01)


#define WITH_SS(op) do {\
    DRIVE_LOW(SS);\
    op;\
    DRIVE_HIGH(SS);\
} while(0)

// Masks and filters work as follows:
// Compare message bits with filter bits only when mask bit is 1.


#define CANP_RXF_APPLY_TO_STD		(0)
#define CANP_RXF_APPLY_TO_EXT		(1)

// Masks of individual fields in their bytes
// ----------------------------------------------------------

// .sidh (tag + counterparty address)
#define CANP_SIDH_MASK_TAG              (0xE0)
#define CANP_SIDH_MASK_CPTY_ADDR        (0x1F)

// .sidl (tag + counterparty address)
#define CANP_SIDL_MASK_CPTY_NET         (0xE0)
#define CANP_SIDL_MASK_FLAGS            (0x03)
#define CANP_SIDL_MASK_OWNER            (0x02)
#define CANP_SIDL_MASK_AUX              (0x01)

// .eid8 
#define CANP_SIDL_MASK_HOST_NET         (0xE0)
#define CANP_SIDH_MASK_HOST_ADDR        (0x1F)

// Macros for extraction of bits of the individual fields
// ----------------------------------------------------------
#define CANP_TAG_BITS(message) ((message).sidh & CANP_SIDH_MASK_TAG)
#define CANP_CPTY_ADDR_BITS(message) ((message).sidh & CANP_SIDH_MASK_CPTY_ADDR)
#define CANP_CPTY_NET_BITS(message) ((message).sidl & CANP_SIDL_MASK_CPTY_NET)
#define CANP_OWNER_BITS(message) ((message).sidl & CANP_SIDL_MASK_OWNER)
#define CANP_AUX_BITS(message) ((message).sidl & CANP_SIDL_MASK_AUX)
#define CANP_HOST_NET_BITS(message) ((message).eid8 & CANP_SIDL_MASK_HOST_NET)
#define CANP_HOST_ADDR_BITS(message) ((message).eid8 & CANP_SIDL_MASK_HOST_ADDR)
#define CANP_SLOT_BITS(message) ((message).eid0)


#define CANP_COMPARE_TAG		(0x07)
#define CANP_COMPARE_CPTY_ADDR		(0x1F)
#define CANP_COMPARE_CPTY_NET		(0x07)
#define CANP_COMPARE_HOST_ADDR		(0x1F)
#define CANP_COMPARE_HOST_NET		(0x07)
#define CANP_COMPARE_OWNER		(0x01)
#define CANP_COMPARE_AUX		(0x01)
#define CANP_COMPARE_SLOT		(0xFF)


// Helper macros for mcp251x_message structures
// ----------------------------------------------------------

#define CANP_MASK(tag, cpty_net, cpty_addr, host_net, host_addr, owner, aux, slot) {		\
  .sidh=(uint8_t) (((tag) << 5) | (cpty_addr)),							\
  .sidl=(uint8_t) (((cpty_net) << 5) | ((owner) << 1) | ((aux) << 0)),				\
  .eid8=(uint8_t) (((host_net) << 5) | (host_addr)),						\
  .eid0=(uint8_t) ((slot))									\
}

#define CANP_FILT_STD(tag, cpty_net, cpty_addr, host_net, host_addr, owner, aux, slot) {	\
  .sidh=(uint8_t) (((tag) << 5) | (cpty_addr)),							\
  .sidl=(uint8_t) (((cpty_net) << 5) | ((owner) << 1) | ((aux) << 0)),				\
  .eid8=(uint8_t) (((host_net) << 5) | (host_addr)),						\
  .eid0=(uint8_t) ((slot))									\
}

#define CANP_FILT_EXT(tag, cpty_net, cpty_addr, host_net, host_addr, owner, aux, slot) {	\
  .sidh=(uint8_t) (((tag) << 5) | (cpty_addr)),							\
  .sidl=(uint8_t) (((cpty_net) << 5) | (1 << 3) | ((owner) << 1) | ((aux) << 0)),		\
  .eid8=(uint8_t) (((host_net) << 5) | (host_addr)),						\
  .eid0=(uint8_t) ((slot))									\
}



// Filters and mask for RX Buffer 0
#define RXM0	CANP_MASK	(0, 0, 0, CANP_COMPARE_HOST_NET,	CANP_COMPARE_HOST_ADDR,	0, 0, 0)
#define RXF0	CANP_FILT_EXT	(0, 0, 0, CANP_DEVICE_NET,		CANP_DEVICE_ADDR,	0, 0, 0) /* All EXT frames addressed to device */
#define RXF1	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */


// Filters and mask for RX Buffer 1
#define RXM1	CANP_MASK	(0, 0, 0, 0, 0, 0, 0, 0) /* Don't compare */
#define RXF2	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF3	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF4	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF5	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */


// RX Filters 0-2
static mcp251x_message_id rxf0_2[3] = {
    RXF0, RXF1, RXF2
};

// RX Filters 3-5
static mcp251x_message_id rxf3_5[3] = {
    RXF3, RXF4, RXF5
};

// RX Masks 0 and 1
static mcp251x_message_id rxm0_1[2] = {
    RXM0, RXM1
};



static inline void can_init(void) {
    spi__init();
    
    // Rely on HW reset 
    WITH_SS (mcp251x_reset());
    _delay_us(50); // >2
    WITH_SS (mcp251x_write_byte (MCP251X_REGISTER_CNF1, 0x07));
    WITH_SS (mcp251x_write_byte (MCP251X_REGISTER_CNF2, 0x90));
    WITH_SS (mcp251x_write_byte (MCP251X_REGISTER_CNF3, 0x02));
}


static inline void can_conf(void) {
    WITH_SS (mcp251x_write_bytes ((uint8_t*)rxf0_2, MCP251X_REGISTER_RXF0SIDH, sizeof(rxf0_2)));
    WITH_SS (mcp251x_write_bytes ((uint8_t*)rxf3_5, MCP251X_REGISTER_RXF3SIDH, sizeof(rxf3_5)));
    WITH_SS (mcp251x_write_bytes ((uint8_t*)rxm0_1, MCP251X_REGISTER_RXM0SIDH, sizeof(rxm0_1)));
}


static inline void can_start(void) {
    // enable external interrupt from INT1 pin, falling edge
    MCUCR = _BV(ISC11);
    GICR  = _BV(INT1);
    WITH_SS (mcp251x_write_byte (MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)));
    WITH_SS (mcp251x_write_byte (MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL));
}

#endif