#ifndef __UCAN_MSG_TYPES_H
#define __UCAN_MSG_TYPES_H

#include "ucan.h"

// Known message types for UCAN-DP and UCAN-SDP protocols
// -----------------------------------------------------------------------------

// Masked value for DP_FIRST=100 message type (datagram protocol, first segment)
#define UCAN_MSG_TYPE_MASKED__DP_FIRST	\
	(\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_2))) |\
		(0 << (UCAN_REG_BIT(UCAN_MSG_TYPE_1))) |\
		(0 << (UCAN_REG_BIT(UCAN_MSG_TYPE_0)))  \
	)

// Masked value for DP_NEXT=101 message type (datagram protocol, next segment)
#define UCAN_MSG_TYPE_MASKED__DP_NEXT	\
	(\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_2))) |\
		(0 << (UCAN_REG_BIT(UCAN_MSG_TYPE_1))) |\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_0)))  \
	)

// Masked value for DP_NEXT=110 message type (datagram protocol, last segment)
#define UCAN_MSG_TYPE_MASKED__DP_LAST	\
	(\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_2))) |\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_1))) |\
		(0 << (UCAN_REG_BIT(UCAN_MSG_TYPE_0)))  \
	)

// Masked value for SDP=111 message type (short datagram protocol)
#define UCAN_MSG_TYPE_MASKED__SDP	\
	(\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_2))) |\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_1))) |\
		(1 << (UCAN_REG_BIT(UCAN_MSG_TYPE_0)))  \
	)


#endif // __UCAN_MSG_TYPES_H