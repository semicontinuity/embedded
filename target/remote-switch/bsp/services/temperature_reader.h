// =============================================================================
// Temperature Reader Service
//
// Continuously reads temperature from a DS18X20 1-wire sensor using a
// virtual thread (non-blocking cooperative multitasking).
//
// Timer0 usage (shared with onewire driver):
//   - During 1-wire transactions: onewire__t0t2 driver owns timer0,
//     reconfiguring it as a fast bit-span timer (prescaler 8 or 64).
//   - After each transaction: temperature_reader reconfigures timer0 to
//     slow tick mode (prescaler 1024, normal WGM) to time the DS18B20
//     conversion wait (~750ms = TEMPERATURE_READER__CONVERSION_DELAY_COUNT
//     overflow periods at 16MHz) and to drive thread scheduling via
//     timer0 overflow pending flag.
// =============================================================================
#ifndef __SERVICES__TEMPERATURE_READER_H
#define __SERVICES__TEMPERATURE_READER_H

#include <stdint.h>
#include <stdbool.h>

extern uint16_t temperature_reader__reading;

void temperature_reader__reading__on_changed(void);

void temperature_reader__thread__start(void);

bool temperature_reader__thread__is_runnable(void);

void temperature_reader__thread__run(void);

#endif