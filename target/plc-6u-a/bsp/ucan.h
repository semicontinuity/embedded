#ifndef __UCAN_H
#define __UCAN_H

#include "bitops.h"

// =============================================================================
// Frame structure
// Header bit numbers in the frame, as transmitted over the wire.
// Bits  0.. 7 correspond to SIDH[7..0]
// Bits  8..15 correspond to SIDL[7..0]
// Bits 16..23 correspond to EID8[7..0]
// Bits 24..31  correspond to EID0[7..0]
// =============================================================================

#define UCAN_CLASS1_2		(0)
#define UCAN_CLASS1_1		(1)
#define UCAN_CLASS1_0		(2)
#define UCAN_DST_NODE_4		(3)
#define UCAN_DST_NODE_3		(4)
#define UCAN_DST_NODE_2		(5)
#define UCAN_DST_NODE_1		(6)
#define UCAN_DST_NODE_0		(7)
#define UCAN_DST_NET_2		(8)
#define UCAN_DST_NET_1		(9)
#define UCAN_DST_NET_0		(10)
// 11th bit is SIDL[4], ignored
#define UCAN_EIDE		(12)
// 13th bit is SIDL[2], ignored
#define UCAN_RESERVED1_1	(14)
#define UCAN_RESERVED1_0	(15)
#define UCAN_RESERVED2_1	(16)
#define UCAN_RESERVED2_0	(17)
#define UCAN_BROADCAST		(18)
#define UCAN_SRC_NODE_4		(19)
#define UCAN_SRC_NODE_3		(20)
#define UCAN_SRC_NODE_2		(21)
#define UCAN_SRC_NODE_1		(22)
#define UCAN_SRC_NODE_0		(23)
#define UCAN_SRC_NET_2		(24)
#define UCAN_SRC_NET_1		(25)
#define UCAN_SRC_NET_0		(26)
#define UCAN_TOPIC_4		(27)
#define UCAN_TOPIC_3		(28)
#define UCAN_TOPIC_2		(29)
#define UCAN_TOPIC_1		(30)
#define UCAN_TOPIC_0		(31)


// =============================================================================
// Helper macros for TOPIC field
// intended for higher-level protocol message type
// =============================================================================

// offset of register inside message buffer containing TOPIC field
// (assume that all TOPIC bits are in the same register)
#define UCAN_TOPIC_REG_OFFSET		(UINT32_BIGENDIAN_BYTE_OFFSET(UCAN_TOPIC_0))

// mask to select TOPIC field inside register containg TOPIC field
// (assume that all TOPIC bits are in the same register)
#define UCAN_TOPIC_REG_MASK		\
	(\
		1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_4)) |\
		1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_3)) |\
		1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2)) |\
		1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1)) |\
		1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))  \
	)

// macro to select TOPIC field inside register containg TOPIC field
// (assume that all TOPIC bits are in the same register)
#define UCAN_TOPIC_MASKED(v)		((v) & UCAN_TOPIC_REG_MASK)


#endif // __UCAN_H