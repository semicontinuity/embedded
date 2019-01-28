#ifndef __UCAN_CLASS_H
#define __UCAN_CLASS_H

#include "device.h"
#include "ucan.h"
#include "bitops.h"

// =============================================================================
// Constants for UCAN_CLASS field
//
// 000	EMERGENCY
//	Emergency messages.
//	Examples: fire detected, water leak detected, gas leak detected
// 001	REALTIME
//	Real-time messages.
//	Examples: network real-time clock broadcasts
// 010	SYSTEM
//	System state and control messages.
//	Examples: alarm state, day/night/custom mode..
// 011	SENSOR
//	Environment sensors' messages.
//	Examples: temperature/pressure/humidity/raindrop/motion/presense/door state/window state...
// 100	LIGHTING
//	Lighting-related control
//	Examples: lights state/control, dimming
// 101	HID
//	Human-interface devices.
//	Examples: LCD panels, buttons, card readers, IR receivers, TV out, phone/GSM gateway
// 110	INFRASTRUCTURE
//	Home infrastracture control.
//	Examples: HVAC,motors,pumps,blinds,garage doors,locks,valves,power distribution,...
// 111	APPLIANCE
//	Complex appliances control
//	Examples: AV-switches,AV players,FM radio,Satellite tuner,TV, other complex appliances
// =============================================================================

#define UCAN_CLASS_MASKED__EMERGENCY \
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__REALTIME \
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__SYSTEM \
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__SENSOR \
	(\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__LIGHTING \
	(\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__HID \
	(\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__INFRASTRUCTURE \
	(\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(0 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)
#define UCAN_CLASS_MASKED__APPLIANCE \
	(\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_2))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_1))) |\
		(1 << (UINT32_BIGENDIAN_BIT_IN_BYTE(UCAN_TOPIC_0))) \
	)

#endif // __UCAN_CLASS_H