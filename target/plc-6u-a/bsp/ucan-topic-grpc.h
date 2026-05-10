#ifndef __UCAN_TOPIC_GRPC_H
#define __UCAN_TOPIC_GRPC_H

#include "device.h"
#include "ucan.h"
#include "bitops.h"

// =============================================================================
// Constants for GRPC topics
//
// UCAN-GRPC uses topic field (UCAN_TOPIC) to encode commands:
// 00000	UCAN_GRPC_SET		SET Request
// 00001	UCAN_GRPC_GET		GET Request
// 00010	UCAN_GRPC_RESPONSE	Synchronous response to GET or SET request
// 00011	UCAN_GRPC_NOTIFICATION	Asynchronous notification
// 11xxx	extenders like MCP250xx
// other	reserved
// =============================================================================

// Masked value for SET Request
#define UCAN_TOPIC_MASKED__DP_GRPC_SET		\
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_4))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_3))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)

// Masked value for GET Request
#define UCAN_TOPIC_MASKED__DP_GRPC_GET		\
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_4))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_3))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)

// Masked value for Synchronous response to GET or SET request
#define UCAN_TOPIC_MASKED__DP_GRPC_RESPONSE	\
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_4))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_3))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)

// Masked value for Asynchronous notification
#define UCAN_TOPIC_MASKED__DP_GRPC_NOTIFICATION	\
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_4))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_3))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)

// Mask to check if a byte containing TOPIC field pertains to GRPC
#define UCAN_TOPIC_MASK__DP_GRPC			\
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_4))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_3))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0)))\
	)


// =============================================================================
// Helper macros for GRPC topics
// =============================================================================

#define UCAN_TOPIC_MASKED_IS_GRPC_SET(v)	\
	(UCAN_TOPIC_MASKED(v) == UCAN_TOPIC_MASKED__DP_GRPC_SET)

#define UCAN_TOPIC_MASKED_IS_GRPC_GET(v)	\
	(UCAN_TOPIC_MASKED(v) == UCAN_TOPIC_MASKED__DP_GRPC_GET)

#define UCAN_TOPIC_MASKED_IS_GRPC_RESPONSE(v)	\
	(UCAN_TOPIC_MASKED(v) == UCAN_TOPIC_MASKED__DP_GRPC_RESPONSE)

#define UCAN_TOPIC_MASKED_IS_GRPC_NOTIFICATION(v)	\
	(UCAN_TOPIC_MASKED(v) == UCAN_TOPIC_MASKED__DP_GRPC_NOTIFICATION)


// TODO!!! optimize
#define UCAN_TOPIC_MASKED_IS_GRPC_REQUEST(v)	\
	(\
		(UCAN_TOPIC_MASKED(v) == UCAN_TOPIC_MASKED__DP_GRPC_GET)\
	||\
		(UCAN_TOPIC_MASKED(v) == UCAN_TOPIC_MASKED__DP_GRPC_SET)\
	)


#endif // __UCAN_TOPIC_GRPC_H