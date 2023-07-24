#include <stdint.h>
#include "services/discrete_inputs.h"

#include "drivers/in/buttons.h"
#include "drivers/in/extra_inputs.h"
#include "drivers/in/valve_limit_switches.h"
#include "drivers/in/water_leak_sensors.h"

#include "cpu/avr/asm.h"


#ifndef discrete_inputs__byte0
uint8_t discrete_inputs__byte0;
#endif

#ifndef discrete_inputs__byte1
uint8_t discrete_inputs__byte1;
#endif

//int8_t discrete_inputs_debouncer__timeouts[16];


void discrete_inputs__init(void) {
    water_leak_sensor__a__init();
    water_leak_sensor__b__init();
    water_leak_sensor__c__init();
    water_leak_sensor__d__init();

    valve_limit_switch__a__init();
    valve_limit_switch__b__init();
    valve_limit_switch__c__init();
    valve_limit_switch__d__init();

    extra_input__a__init();
    extra_input__b__init();

    button__a__init();
    button__b__init();
    button__c__init();
    button__d__init();
    button__e__init();
    button__f__init();
}


void discrete_inputs__debouncer__run(void) {
//    int8_t *p_timeout = discrete_inputs_debouncer__timeouts;

//    int8_t timeout;

    uint8_t byte0;
    LOAD_CONST8(byte0, 0);
    if (water_leak_sensor__a__is_on()) byte0 |= _BV(0);
    if (water_leak_sensor__b__is_on()) byte0 |= _BV(1);
    if (water_leak_sensor__c__is_on()) byte0 |= _BV(2);
    if (water_leak_sensor__d__is_on()) byte0 |= _BV(3);
    if (valve_limit_switch__a__is_on()) byte0 |= _BV(4);
    if (valve_limit_switch__b__is_on()) byte0 |= _BV(5);
    if (valve_limit_switch__c__is_on()) byte0 |= _BV(6);
    if (valve_limit_switch__d__is_on()) byte0 |= _BV(7);
    discrete_inputs__byte0 = byte0;

    uint8_t byte1;
    LOAD_CONST8(byte1, 0);
    if (extra_input__a__is_on()) byte1 |= _BV(0);
    if (extra_input__b__is_on()) byte1 |= _BV(1);
    if (button__a__is_on()) byte1 |= _BV(2);
    if (button__b__is_on()) byte1 |= _BV(3);
    if (button__c__is_on()) byte1 |= _BV(4);
    if (button__d__is_on()) byte1 |= _BV(5);
    if (button__e__is_on()) byte1 |= _BV(6);
    if (button__f__is_on()) byte1 |= _BV(7);
    discrete_inputs__byte1 = byte1;
}
