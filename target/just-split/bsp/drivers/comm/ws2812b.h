/*
 * Original copyright:
 *
 * light weight WS2812 lib include
 *
 * Version 2.3  - Nev 29th 2015
 * Author: Tim (cpldcpu@gmail.com) 
 *
 * Please do not change this file! All configuration is handled in "ws2812_config.h"
 *
 * License: GNU GPL v2+ (see License.txt)
 +
 */ 

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

#include <avr/io.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////
// Define Reset time in µs.
//
// This is the time the library spends waiting after writing the data.
//
// WS2813 needs 300 µs reset time
// WS2812 and clones only need 50 µs
//
///////////////////////////////////////////////////////////////////////
#if !defined(ws2812_resettime)
#define ws2812_resettime    300
#endif

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////
#if !defined(ws2812_port)
#define ws2812_port D   // Data port
#endif

#if !defined(ws2812_pin)
#define ws2812_pin  1   // Data out pin
#endif

void ws2812_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask);


/*
 * Internal defines
 */

#ifndef CONCAT
#define CONCAT2(s1, s2)                 s1##s2
#define CONCAT(s1, s2)                  CONCAT2(s1, s2)
#endif

#define ws2812_PORTREG  CONCAT(PORT,ws2812_port)
#define ws2812_DDRREG   CONCAT(DDR,ws2812_port)

#endif /* LIGHT_WS2812_H_ */
