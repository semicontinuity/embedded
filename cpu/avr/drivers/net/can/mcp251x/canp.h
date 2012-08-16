#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__CANP_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__CANP_H


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


#endif