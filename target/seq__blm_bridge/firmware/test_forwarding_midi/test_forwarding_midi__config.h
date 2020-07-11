#ifndef __SEQ_BLM_BRIDGE__CONFIG
#define __SEQ_BLM_BRIDGE__CONFIG

// For Blue Pill Board
#define PIN_LED_HOST_CONNECTED PC13
#define PIN_LED_HOST_CONNECTED_ON LOW
#define PIN_LED_HOST_CONNECTED_OFF HIGH
#define PIN_LED_DEBUG PC13

// For Olimexino board
//#define PIN_LED_HOST_CONNECTED PA1
//#define PIN_LED_DEBUG PA5

#define HOST_SERIAL_PORT Serial2
#define HOST_SERIAL_BAUD_RATE 38400

#define BRIDGE_HELPER_SERIAL_PORT Serial1
#define BRIDGE_HELPER_SERIAL_BAUD_RATE 38400

#endif
