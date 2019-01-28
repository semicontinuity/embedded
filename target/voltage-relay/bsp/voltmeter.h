// =============================================================================
// Mains voltmeter driver.
// Measures the mains voltage at the specified time moment
// after the zero cross event.
// Invoke voltmeter__delayed_run() with the proper delay parameter
// at the moment of the zero cross.
// The measured voltage (raw reading from ADC)
// will be reported to the on_voltage_measured() callback.
// =============================================================================

#ifndef __VOLTMETER_H
#define __VOLTMETER_H

#include <stdint.h>
#include "cpu/avr/gpio.h"

/**
 * Initialize the voltmeter.
 * Configures ADC and TIMER1.
 */
INLINE void voltmeter__init(void);

/**
 * Trigger voltage measurement after the specified delay.
 */
INLINE void voltmeter__delayed_run(uint16_t delay);

/**
 * The callback called when the voltage measurement is done.
 * Must be implemented by the client that consumes the voltage readings.
 * Parameter value: raw reading from ADC.
 */
INLINE void on_voltage_measured(uint16_t value);


#endif