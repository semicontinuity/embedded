// =============================================================================
// UCAN Protocol support.
//
// Contains definitions for encoding of UCAN fields
// into 4-byte CAN ID of MCP251X controllers.
//
// =============================================================================

#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__UCAN_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__UCAN_H

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"


// Values for individual bits
// ----------------------------------------------------------

#define UCAN_STD_ID                     (0)
#define UCAN_EXT_ID                     (1)

// PARAM bit
#define UCAN_PARAM_0                    (0)
#define UCAN_PARAM_1                    (1)

// MCAST bit
#define UCAN_UCAST                      (0)
#define UCAN_MCAST                      (1)


// Masks of individual fields in their bytes
// ----------------------------------------------------------

// .sidh (destination address)
#define UCAN_SIDH_MASK_DEST_ADDR        (0xFF)

// .sidl (object id + flags)
#define UCAN_SIDL_MASK_OBJ_ID           (0xE0)
#define UCAN_SIDL_MASK_FLAGS            (0x03)
#define UCAN_SIDL_MASK_PARAM            (0x02)
#define UCAN_SIDL_MASK_MCAST            (0x01)

// .eid8 
#define UCAN_EID8_MASK_SRC_ADDR         (0xFF)

// .eid0
#define UCAN_EID0_MASK_PORT             (0xFF)

// .dlc
#define UCAN_DLC_MASK_RTR               (1 << MCP251X_RTR)


// Macros for extraction of bits of the individual fields
// -----------------------------------------------------------------------------
#define UCAN_OBJ_ID_BITS(id)            ((id).sidl & UCAN_SIDL_MASK_DEST_ADDR_EXT)
#define UCAN_PARAM_BITS(id)             ((id).sidl & UCAN_SIDL_MASK_PARAM)
#define UCAN_MCAST_BITS(id)             ((id).sidl & UCAN_SIDL_MASK_MCAST)
#define UCAN_SRC_ADDR_BITS(id)          ((id).eid8 & UCAN_EID8_MASK_SRC_ADDR)
#define UCAN_PORT_BITS(id)              ((id).eid0)


// Macros for mcp251x_message structures
// -----------------------------------------------------------------------------
#define UCAN_RTR_BITS(header)           ((header).dlc & UCAN_DLC_MASK_RTR)
#define UCAN_DATA_LENGTH_BITS(header)   ((header).dlc & 0x0F)


// Macros for UCAN message types. Message type is defined by PARAM and RTR bits.
// -----------------------------------------------------------------------------
#define UCAN_MSG_TYPE(header)           (UCAN_RTR_BITS((header)) | UCAN_PARAM_BITS((header).id))

#define UCAN_MSG_TYPE_POST              (0)
#define UCAN_MSG_TYPE_VALUE             (                    UCAN_SIDL_MASK_PARAM)
#define UCAN_MSG_TYPE_STATUS            (UCAN_DLC_MASK_RTR                       )
#define UCAN_MSG_TYPE_GET               (UCAN_DLC_MASK_RTR | UCAN_SIDL_MASK_PARAM)


// SID10 ..     SID3 SID2..0 IDE EID17 EID15  ..    EID8 EID7    ..   EID0
// +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
// |10            3| |2 1 0| | | |   | |               | |               |
// +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
// |dest address   | |objid|     |P|M| | src address   | | port          |
// +-----+---------+ +-----+     +-+-+ +-----+---------+ +---------------+
#define UCAN_HEADER(exide, dest_addr, src_addr, port, param, mcast, obj_id) {                   \
  .sidh=(uint8_t) ((dest_addr)),                                                                \
  .sidl=(uint8_t) (((obj_id) << 5) | ((exide) << 3) | ((param) << 1) | ((mcast) << 0)),	        \
  .eid8=(uint8_t) ((src_addr)),                                                                 \
  .eid0=(uint8_t) ((port))                                                                      \
}


// Macros and constants to define masks and filters
// Masks and filters work as follows:
// Compare message bits with filter bits only when mask bit is 1.
// -----------------------------------------------------------------------------

#define UCAN_MASK(dest_addr, src_addr, port, param, mcast, obj_id)              \
        UCAN_HEADER(0, dest_addr, src_addr, port, param, mcast, obj_id)

// filter is applied only to standard frames
#define UCAN_FILT_STD(dest_addr, src_addr, port, param, mcast, obj_id)          \
        UCAN_HEADER(0, dest_addr, src_addr, port, param, mcast, obj_id)

// filter is applied only to extended frames
#define UCAN_FILT_EXT(dest_addr, src_addr, port, param, mcast, obj_id)          \
        UCAN_HEADER(0, dest_addr, src_addr, port, param, mcast, obj_id)


#define UCAN_COMPARE_DEST_ADDR		(UCAN_EID8_MASK_SRC_ADDR)
#define UCAN_COMPARE_SRC_ADDR		(UCAN_EID8_MASK_SRC_ADDR)
#define UCAN_COMPARE_PARAM              (UCAN_SIDL_MASK_PARAM)
#define UCAN_COMPARE_MCAST              (UCAN_SIDL_MASK_MCASST)
#define UCAN_COMPARE_PORT               (UCAN_EID0_MASK_PORT)

#define UCAN_DONT_COMPARE               (0x00)
#define UCAN_DONT_CARE                  (0x00)


#endif