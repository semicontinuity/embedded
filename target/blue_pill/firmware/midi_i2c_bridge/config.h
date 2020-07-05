#ifndef __CONFIG
#define __CONFIG

#include <Wire.h>

#define BLM_SCALAR_NUM_COLOURS 2
#define BLM_SCALAR_NUM_BOARDS_X 1
#define BLM_SCALAR_NUM_BOARDS_Y 1
#define BLM_SCALAR_NUM_BOARDS (BLM_SCALAR_NUM_BOARDS_X*BLM_SCALAR_NUM_BOARDS_Y)
#define BLM_BOARDS_BASE_ADDRESS 0x30

// For Blue Pill Board
#define PIN_LED_HOST_CONNECTED PC13
#define PIN_LED_HOST_CONNECTED_ON LOW
#define PIN_LED_HOST_CONNECTED_OFF HIGH
#define PIN_LED_DEBUG PC13

// For Olimexino board
//#define PIN_LED_HOST_CONNECTED PA1
//#define PIN_LED_DEBUG PA5


TwoWire Wire2(2);
#define WIRE Wire2

#endif
